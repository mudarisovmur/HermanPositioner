/**
  ******************************************************************************
  * @file    StorageFlash.hpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    20.07.2022
  * @brief   StorageFlash
  *          Класс хранилища данных во внутренней Flash памяти
  ******************************************************************************
  */

#ifndef STORAGE_FLASH_HPP                           //< Avoid multiple inclusion
#define STORAGE_FLASH_HPP

#include "IStorage.hpp"
#include "SemaphoreWrapper.hpp"
//#include "stm32f1xx_hal_flash.h"
  
class StorageFlash : public IStorage {
  
  public:
  
  /**
   * @brief Конструктор
   */
  StorageFlash();
  
  /**
   * @brief Метод интерфейса IStorage
   *        Записать значение регистра.
   * @param number - номер регистра
   * @param value - значение регистра
   */  
  virtual void writeRegister(uint16_t number, uint16_t value) override;
  
  /**
   * @brief Метод интерфейса IStorage
   *        Считать значение регистра.
   * @param number - номер регистра
   * @return значение регистра
   */  
  virtual uint16_t readRegister(uint16_t number) override;
  
  /**
   * @brief Методы класса
   */
  
  /**
   * @brief Метод инициализации: проверка валидности хранимых данных
   */  
  void init();
  
  /**
   * @brief Задать указатель на семафор для ожидания
   * @param semaphoreWrapper - указатель на SemaphoreWrapper
   */  
  void setSemaphoreWrapper(SemaphoreWrapper* semaphoreWrapper);
  
  /**
   * @brief Процедура сброса хранилища
   */  
  void storageReset();
  
  private:
  
  /// Адрес страницы флеш памяти для сохранения параметров
  static const uint32_t         STORAGE_FLASH_ADDRESS = 0x8007C00;
  
  /// Максимальный размер хранилища
  static const uint16_t         STORAGE_MAX_SIZE = 0x0020;
  
  /// Указатель на семафор для ожидания окончания стирания флеш памяти
  SemaphoreWrapper*             _semaphoreWrapper;
  
  /// Количество записанных регистров
  uint16_t                      _registersQuantity;
};

#endif // STORAGE_FLASH_HPP

/**
  ******************************************************************************
  *  Вер. |   гггг-ммм-дд   | Внес изменения | Описание изменений
  *  =====|=================|================|==================================
  *   1.0 |   20.07.2022    | Мударисов Т.Р. | Первый релиз
  *  -----|-----------------|----------------|----------------------------------
  ******************************************************************************
  */
