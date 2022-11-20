/**
  ******************************************************************************
  * @file    DeviceGlobalKernel.cpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    24.07.2022
  * @brief   DeviceGlobalKernel
  *          Часть объекта для глобального взаимодействия с устройством
  ******************************************************************************
  */
  
#include "DeviceGlobal.hpp"

/**
 * @brief Инициализация
 */
void DeviceGlobal :: initKernel() {
  
  _kernel.setIPercent(&_positionControl);
  _kernel.setILed(LED_ONE, &_ledOpen);
  _kernel.setILed(LED_TWO, &_ledPercent[0]);
  _kernel.setILed(LED_THREE, &_ledPercent[1]);
  _kernel.setILed(LED_FOUR, &_ledPercent[2]);
  _kernel.setILed(LED_FIVE, &_ledClose);
  _kernel.setILogicInput(&_calibration);
  _kernel.setILogicOutputClose(&_adapterILogicOutputILogicInputKernelClose);
  _kernel.setILogicOutputOpen(&_adapterILogicOutputILogicInputKernelOpen);
  observerAggregator->registerIObserver(&_kernel);
} 
