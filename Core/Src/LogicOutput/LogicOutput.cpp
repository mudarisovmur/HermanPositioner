/**
  ******************************************************************************
  * @file    LogicOutput.cpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    10.07.2022
  * @brief   LogicOutput
  *          Класс для управления логическим выходом
  ******************************************************************************
  */

#include "LogicOutput.hpp"

/**
 * @brief Конструктор
 */
LogicOutput :: LogicOutput() {
  
  _pin = 0x0000;
  setInvert(false);
}

/**
 * @brief Метод интерфейса ILogicOutput
 *        Активировать логической выход.
 */  
void LogicOutput :: activate() {
  
  // Получаем результирующее состояние от инвертации
  GPIO_PinState state = _isInverted ? GPIO_PIN_RESET : GPIO_PIN_SET;
  
  // Отрабатываем только изменение состояния
  if (HAL_GPIO_ReadPin(_port, _pin) != state) {
    
    // Устанавливаем новое состояние
    HAL_GPIO_WritePin(_port, _pin, state);
  }
}

/**
 * @brief Метод интерфейса ILogicOutput
 *        Деактивировать логической выход.
 */  
void LogicOutput :: deactivate() {
  
  // Получаем результирующее состояние от инвертации
  GPIO_PinState state = _isInverted ? GPIO_PIN_SET : GPIO_PIN_RESET;
  
  // Отрабатываем только изменение состояния
  if (HAL_GPIO_ReadPin(_port, _pin) != state) {
    
    // Устанавливаем новое состояние
    HAL_GPIO_WritePin(_port, _pin, state);
  }
}

/**
 * @brief Зарегистрировать GPIO
 * @param port - порт gpio
 * @param pin - пин gpio
 */
void LogicOutput :: registerOutput(GPIO_TypeDef* port, uint16_t pin) {
  
  _port = port;
  _pin = pin;
}

/**
 * @brief Установить состояние инвертированности
 * @param isInvert - состояние
 */  
void LogicOutput :: setInvert(bool isInvert) {
  
  _isInverted = isInvert;
}
