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

#ifndef _DEVICE_GLOBAL_HPP                          //< Avoid multiple inclusion
#define _DEVICE_GLOBAL_HPP


#include <stdint.h>
#include <stddef.h>
#include <cmsis_os.h>
#include <tim.h>

#include "AdapterILogicOutputILogicInput.hpp"
#include "ObserverAggregator.hpp"
#include "SemaphoreWrapper.hpp"
#include "LogicInputArray.hpp"
#include "PositionControl.hpp"
#include "StorageFlash.hpp"
#include "Calibration.hpp"
#include "LogicControl.hpp"
#include "LogicOutput.hpp"
#include "LogicInput.hpp"
#include "Protocol.hpp"
#include "Kernel.hpp"
#include "Led.hpp"

extern UART_HandleTypeDef huart1;

class DeviceGlobal {

public:

  /**
   * @brief Конструктор
   */
  DeviceGlobal();

  /**
   * @brief Методы класса
   */

  /**
   * @brief Инициализация ПО (создание объектов)
   */
  void initializeSoftware();

  /**
   * @brief Инициализация аппаратная (таймеры, компаратор...)
   */
  void initializeHardware();

  /**
   * @brief Функция периодического оповещения 
   */
  void periodicObserver();


  /**
   * @brief Снять статус готовности  устройства для всех процессов
   */
  void clrReady();

  /**
   * @brief  Получить статус полной готовности устройства
   * @return Статус готовности устройства
   */
  bool getReady();

  /**
   * @brief Установить статус полной готовности устройства
   */
  void setReady();

  /**
   * @brief Создание и инициализация объектов семафоров для активации
   *        периодических процессов.
   */
  void activateRequirementsPeriodic();
  
  /**
   * @brief  Получить handle таймера для генерации 200 мкс интервалов
   * @return Указатель на структуру TIM_HandleTypeDef
   */
  TIM_HandleTypeDef* getTimer200mksHandle();
  
  /**
   * @brief Данные класса
   */
  
  /// Семафоры управления периодическим процессом 200мкс
  SemaphoreWrapper*             activate200mksTskSem;
  
  /// Семафоры управления процессом стирания флеш памяти
  SemaphoreWrapper*             flashEraseSem;
  
  /// Хранилище интерфейсов периодического оповещения
  ObserverAggregator*           observerAggregator;
  
  private:

  /**
   * @brief Закрытые методы класса
   */
  
  /// Handle таймера для генерации 200 мкс интервалов
  TIM_HandleTypeDef*            _htim200mks;
  
  /// Статус полной готовности устройства к работе
  bool                          _isReady;
  
  /// Статус готовности устройства к работе для 200 мкс процесса
  bool                          _isReady200mks;


  /// Инициализация протокола обмена данными
  #include "DeviceGlobalProtocol.hpp"
  
  /// Инициализация выходов
  #include "DeviceGlobaLogicOutputs.hpp"
  
  /// Инициализация выходов
  #include "DeviceGlobalStorages.hpp"
  
  /// Инициализация калибровки
  #include "DeviceGlobalCalibration.hpp"
  
  /// Инициализация ядра
  #include "DeviceGlobalKernel.hpp"
  
};

#endif //_DEVICE_GLOBAL_HPP

/**
  ******************************************************************************
  *  Вер. |   гггг-ммм-дд   | Внес изменения | Описание изменений
  *  =====|=================|================|==================================
  *   1.0 |   08.07.2022    | Мударисов Т.Р. | Первый релиз
  *  -----|-----------------|----------------|----------------------------------
  ******************************************************************************
  */

