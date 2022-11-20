/**
  ******************************************************************************
  * @file    DeviceGlobal.hpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    08.07.2022
  * @brief   DeviceGlobal
  *          Определение глобальных объектов устройства
  ******************************************************************************
  */

#include "DeviceGlobal.hpp"

/**
 * @brief Конструктор
 */
DeviceGlobal :: DeviceGlobal() {

  _htim200mks = &htim1;
  
  _uart = &huart1;
  
  clrReady();
}

/**
 * @brief Инициализация ПО (создание объектов)
 */
void DeviceGlobal::initializeSoftware() {

  // Создание объектов семафоров для активации периодических процессов
  activateRequirementsPeriodic();
  
  // Инициализация тестового протокола
  initProtocol();
  
  // Инициализация логических входов/выходов
  initLogicOutputs();
  
  // Инициализация хранилищ данных
  initStorages();
  
  // Инициализация калибровки
  initCalibration();
  
  // Инициализация ядра
  initKernel();
}


/**
 * @brief Инициализация аппаратная (таймеры, компаратор...)
 */
void DeviceGlobal :: initializeHardware() {  
  
  HAL_TIM_Base_Start_IT(&htim1);
}


/**
 * @brief Функция периодического оповещения 
 */
void DeviceGlobal :: periodicObserver() {
  
  
}


/**
 * @brief Снять статус готовности  устройства для всех процессов
 */
void DeviceGlobal :: clrReady() {
  
  _isReady = false;
}


/**
 * @brief  Получить статус полной готовности устройства
 * @return Статус готовности устройства
 */
bool DeviceGlobal::getReady() {
  
  return _isReady;
}


/**
 * @brief Установить статус полной готовности устройства
 */
void DeviceGlobal::setReady() {
  
  _isReady = true;
}


/**
 * @brief  Получить handle таймера для генерации 200 мкс интервалов
 * @return Указатель на структуру TIM_HandleTypeDef
 */
TIM_HandleTypeDef* DeviceGlobal :: getTimer200mksHandle() {
  
  return _htim200mks;
}

/**
 * @brief Создание и инициализация объектов семафоров для активации
 *        периодических процессов.
 */  
void DeviceGlobal :: activateRequirementsPeriodic() {
  
  // Создаём объект семафора управления периодическими процессами
  activate200mksTskSem = new SemaphoreWrapper(osWaitForever);
  
  flashEraseSem = new SemaphoreWrapper(osWaitForever);
  
  // Создаём объект для хранения интерфейсов периодического оповещения 
  observerAggregator = new ObserverAggregator(15);
}

/**
  ******************************************************************************
  *  Вер. |   гггг-ммм-дд   | Внес изменения | Описание изменений
  *  =====|=================|================|==================================
  *   1.0 |   04.04.2022    | Мударисов Т.Р. | Первый релиз
  *  -----|-----------------|----------------|----------------------------------
  ******************************************************************************
  */
