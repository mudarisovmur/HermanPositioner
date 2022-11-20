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
 * @brief Инициализация
 */
void DeviceGlobal :: initStorages() {
  
  _storageFlash.setSemaphoreWrapper(flashEraseSem);
  _storageFlash.init();
} 
