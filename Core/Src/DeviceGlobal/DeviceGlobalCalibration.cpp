/**
  ******************************************************************************
  * @file    DeviceLogicOutputs.cpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    10.07.2022
  * @brief   DeviceLogicOutputs
  *          Часть объекта для глобального взаимодействия с устройством
  ******************************************************************************
  */
  
#include "DeviceGlobal.hpp"

/**
 * @brief Инициализация калибровки
 */
void DeviceGlobal :: initCalibration() {
  
  // Инициализируем объект расчёта полной позиции
  _positionControl.setIPosition(&_protocol);
  _positionControl.setICalibration(&_calibration);
  _positionControl.setILed(&_ledNul);
  
  // Инициализируем объект калибровки
  _calibration.setILogicOutputClose(&_adapterILogicOutputILogicInputCalibrationClose);
  _calibration.setILogicOutputOpen(&_adapterILogicOutputILogicInputCalibrationOpen);
  _calibration.setILogicInputClose(&_logicInputCloseBtn);
  _calibration.setILogicInputOpen(&_logicInputOpenBtn);
  _calibration.setIPositionComplete(&_positionControl);
  _calibration.setIStorage(&_storageFlash);
  _calibration.setILed(LED_ONE, &_ledOpen);
  _calibration.setILed(LED_TWO, &_ledPercent[0]);
  _calibration.setILed(LED_THREE, &_ledPercent[1]);
  _calibration.setILed(LED_FOUR, &_ledPercent[2]);
  _calibration.setILed(LED_FIVE, &_ledClose);
  _calibration._positionActivation = &_positionControl;
  _calibration.init();
  observerAggregator->registerIObserver(&_calibration);
} 
