/**
  ******************************************************************************
  * @file    StorageFlash.cpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    20.07.2022
  * @brief   StorageFlash
  *          Класс хранилища данных во внутренней Flash памяти
  ******************************************************************************
  */

#include "StorageFlashDefault.hpp"
#include "StorageFlash.hpp"
#include "stm32f1xx_hal.h"
#include "string.h"

/**
 * @brief Конструктор
 */
StorageFlash :: StorageFlash() {
  
}

/**
 * @brief Метод интерфейса IStorage
 *        Записать значение регистра.
 * @param number - номер регистра
 * @param value - значение регистра
 */  
void StorageFlash :: writeRegister(uint16_t number, uint16_t value) {
  
  // Проверяем регистр
  if (number < STORAGE_MAX_SIZE - 1) {
  
    // Создаём массив страницы памяти
    uint32_t flashPage[STORAGE_MAX_SIZE];
    
    // Зануляем массив
    for (uint8_t i = 0; i < STORAGE_MAX_SIZE; i++) {
      flashPage[i] = 0x00000000;
    }
    // Рассчитываем размер считываемых данных
    uint32_t flashPageByteSize = STORAGE_MAX_SIZE * 4;
    
    // Считываем страницу памяти в массив
    memcpy((void*)flashPage, (void*)STORAGE_FLASH_ADDRESS, flashPageByteSize);
    
    // Инициализируем проверочное число
    uint32_t cotrolSumm = 0x00000000;
    
    // Устанавливаем значение регистра
    flashPage[number] = value;
    
    // Формируем новое проверочное число
    for (uint8_t i = 0; i < (STORAGE_MAX_SIZE - 1); i++) {
      cotrolSumm += (flashPage[i] & 0x000000FF);
    }
    // Устанавливаем новое проверочное число
    flashPage[STORAGE_MAX_SIZE - 1] = cotrolSumm;
    
    // Инициализируем структуру очищения памяти
    FLASH_EraseInitTypeDef EraseInitStruct;
    
    EraseInitStruct.TypeErase = TYPEERASE_PAGES;
    EraseInitStruct.Banks = FLASH_BANK_1;
    EraseInitStruct.PageAddress = STORAGE_FLASH_ADDRESS;
    EraseInitStruct.NbPages = 1;
    
    // Снимаем защиту с FLASH памяти, если она стояла
    HAL_FLASH_Unlock();
    
    // Отдаём команду на очистку памяти 
    HAL_FLASHEx_Erase_IT(&EraseInitStruct);
    
    // Ожидаем установки семафора
    _semaphoreWrapper->wait();
    
    // Перезаписываем все регистры
    for (uint8_t i = 0; i < STORAGE_MAX_SIZE; i++) {
      
      // Непосредственно запись в память
      HAL_StatusTypeDef status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, 
                                 STORAGE_FLASH_ADDRESS + i * 4, 
                                 flashPage[i]);
    }
  }
}

/**
 * @brief Метод интерфейса IStorage
 *        Считать значение регистра.
 * @param number - номер регистра
 * @return значение регистра
 */  
uint16_t StorageFlash :: readRegister(uint16_t number) {
  
  // Получаем конечный адрес регистра
  uint32_t finalAddress = STORAGE_FLASH_ADDRESS + number * 4;
  
  // Инициализируем результат
  uint16_t result;
  
  // Выполняем копирование памяти
  memcpy((void*)&result, (void*)finalAddress, 2);
  
  // Возвращаем результат
  return result;
}

/**
 * @brief Методы класса
 */

/**
 * @brief Метод инициализации: проверка работоспособности backup домена 
 */  
void StorageFlash :: init() {
  
  // Создаём массив страницы памяти
  uint32_t flashPage[STORAGE_MAX_SIZE];
  
  // Инициализируем проверочное число
  uint32_t controlValue = 0u;
  
  // Считываем в массив страницу и формируем проверочное число
  for (uint8_t i = 0; i < STORAGE_MAX_SIZE; i++) {
    
    flashPage[i] = static_cast<uint32_t>(readRegister(i));
    
    if (i < (STORAGE_MAX_SIZE - 1)) {
      controlValue += (flashPage[i] & 0x000000FF);
    }
  }
  // Проверяем совпадение проверочных чисел
  if (controlValue != flashPage[STORAGE_MAX_SIZE - 1]) {
    
    // При несовпадении обнуляем хранилище
    storageReset();
  }
}

/**
 * @brief Процедура сброса хранилища
 */
void StorageFlash :: storageReset() { 
  
  // Инициализируем структуру очищения памяти
  FLASH_EraseInitTypeDef EraseInitStruct;
  
  EraseInitStruct.TypeErase = TYPEERASE_PAGES;
  EraseInitStruct.Banks = FLASH_BANK_1;
  EraseInitStruct.PageAddress = STORAGE_FLASH_ADDRESS;
  EraseInitStruct.NbPages = 1;
  
  // Снимаем защиту с FLASH памяти, если она стояла
  HAL_FLASH_Unlock();
  
  // Отдаём команду на очистку памяти 
  HAL_FLASHEx_Erase_IT(&EraseInitStruct);
  
  // Ожидаем установки семафора
  _semaphoreWrapper->wait();
  
  uint32_t controlValue = 0u;
  
  // Перезаписываем все регистры
  for (uint8_t i = 0; i < STORAGE_MAX_SIZE; i++) {
    
    // Задаём регистры по-умолчанию
    uint32_t regValue = (i < FLASH_REG_LIMIT) ? defaultFlashRegisters[i] : 0u;
    
    // Считаем контрольное число
    controlValue += 0x000000FF & regValue;
    
    // В последний регистр записываем контрольное число
    if (i == STORAGE_MAX_SIZE - 1) {
      regValue = controlValue;
    }
    
    // Непосредственно запись в память
    HAL_StatusTypeDef status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, 
                               STORAGE_FLASH_ADDRESS + i * 4, 
                               regValue);
  }
}

/**
 * @brief Задать указатель на семафор для ожидания
 * @param semaphoreWrapper - указатель на SemaphoreWrapper
 */  
void StorageFlash :: setSemaphoreWrapper(SemaphoreWrapper* semaphoreWrapper) {
  
  _semaphoreWrapper = semaphoreWrapper;
}
