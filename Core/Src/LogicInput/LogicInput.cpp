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

#include "LogicInput.hpp"

/**
 * @brief Конструктор
 */
LogicInput :: LogicInput() {
  
}

/**
 * @brief Метод интерфейса ILogicInput
 *        Получить состояние активации.
 * @return Состояние активации
 */  
bool LogicInput :: getActivation() {
  
  return _stateActivation;
}

/**
 * @brief Метод интерфейса ILogicInput
 *        Получить состояние длительной активации.
 * @return Состояние длительной активации
 */  
bool LogicInput :: getLongActivation() {
  
  return _stateLongActivation;
}

/**
 * @brief Метод интерфейса IObserver
 *        Периодическая процедура: процедура калибровки.
 */  
void LogicInput :: observe() {
  
  // Читаем состояние пина
  GPIO_PinState pinState = HAL_GPIO_ReadPin(_port, _pin);
  
  // Получаем моментальное состояние активности
  bool isActive = (pinState == GPIO_PIN_SET) ? (true) : (false);
  
  // Рассчитываем состояние активации
  if (isActive == true) {
    
    // Увеличиваем каунтер по необходимости
    if ((_stateActivation == false) || (_stateLongActivation == false)) {
      _activationTicks++;
    }
    
    // Условие активации обычного нажатия
    if (_activationTicks >= ACTIVATION_TIME) {
      // Устанавливаем результирующее активное состояние
      _stateActivation = true;
    }
    
    // Условие активации длительного нажатия
    if (_activationTicks >= LONG_ACTIVATION_TIME) {
      // Устанавливаем результирующее активное состояние
      _stateLongActivation = true;
    }
  } else {
    
    // Если активность была замечена
    if (_activationTicks != 0x0000) {
      
      // Увеличиваем количество тиков сброса
      _resetTicks++;
      
      // Если вход неактивен долее, чем время активации
      if (_resetTicks >= RESET_TIME) {
        
        // Сбрасываем счётчики
        _activationTicks = 0x0000;
        _resetTicks = 0x0000;
        
        // Сбрасываем состояние
        _stateActivation = false;
        _stateLongActivation = false;
      }
    } else {
      
    }
  }
}

/**
 * @brief Зарегистрировать GPIO
 * @param port - порт gpio
 * @param pin - пин gpio
 */
void LogicInput :: registerInput(GPIO_TypeDef* port, uint16_t pin) {
  
  _port = port;
  _pin = pin;
}
