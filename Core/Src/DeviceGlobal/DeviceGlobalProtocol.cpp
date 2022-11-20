/**
  ******************************************************************************
  * @file    DeviceGlobal.cpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    04.04.2022
  * @brief   DeviceGlobal
  *          Определение глобальных объектов устройства МДВ-16ДО
  ******************************************************************************
  */
  
#include "DeviceGlobal.hpp"

/**
 * @brief Инициализация
 */
void DeviceGlobal :: initProtocol() {
  
  // Регистрируем порт и пин GPIO
  _logicOutputDE.registerOutput(GPIOB, DO_DE_RS422_Pin);
  
  // Деактивируем пин
  _logicOutputDE.deactivate();
  
  // Инициализируем протокол передачи
  _protocol.setILogicOutput(&_logicOutputDE);
  _protocol.setIProcess(&_positionControl);
  _protocol.setUartHandle(_uart);
  
  // Регистрируем протокол в периодике
  observerAggregator->registerIObserver(&_protocol);
}

/**
 * @brief Функция ответа датчику положения
 */
void DeviceGlobal :: responseDP() {
  
  _protocol.process();
}
