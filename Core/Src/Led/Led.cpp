/**
  ******************************************************************************
  * @file    Led.cpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    23.07.2022
  * @brief   Led
  *          Класс для управления светодидом
  ******************************************************************************
  */

#include "Led.hpp"

// Инициализируем статические поля
uint16_t Led :: _blinkDelay = 0x0000;
// Инициализируем переменную для хранения общего состояния активации
bool Led :: _blinkState = false;
// Инициализируем переменную для хранения общего состояния активации аварий
bool Led :: _blinkStateAlarm = false;
// Инициализируем cчетчик времени мигания
uint16_t Led :: _blinkCounter = 0x0000;
// Инициализируем cчетчик времени мигания
uint16_t Led :: _blinkCounterAlarm = 0x0000;
// Инициализируем указатель на объект изменяющий значения счётчиков
ILed* Led :: _iLed = nullptr;

/**
 * @brief Конструктор
 */
Led :: Led() {
  
  setInverted(false);
}

/**
 * @brief Метод интерфейса ILed
 *        Активировать логической выход.
 */  
void Led :: activate() {
  
  _state = STATE_ON;
}

/**
 * @brief Метод интерфейса ILed
 *        Деактивировать логической выход.
 */  
void Led :: deactivate() {
  
  _state = STATE_OFF;
}

/**
 * @brief Метод интерфейса ILed
 *        Активировать мигание.
 */  
void Led :: blink() {
  
  _state = STATE_BLINK;
}

/**
 * @brief Метод интерфейса ILed
 *        Активировать сигнальное мигание.
 */  
void Led :: blinkAlarm() {
  
  _state = STATE_BLINK_ALARM;
}

/**
 * @brief Метод интерфейса ILed
 *        Активировать одноразовое мигание
 */  
void Led :: blinkOnce() {
  
  _state = STATE_BLINK_ONCE;
}

/**
 * @brief Метод интерфейса IObserver
 *        Периодическая процедура: отработка мигания
 */  
void Led :: observe() {
  
  // Изменяем счётчики, если указатели совпадают
  if (this == _iLed) {
    
    if (_blinkCounter++ > _blinkDelay) {
      _blinkState = !_blinkState;
      _blinkCounter = 0;
    }
    
    if (_blinkCounterAlarm++ > (_blinkDelay / 4)) {
      _blinkStateAlarm = !_blinkStateAlarm;
      _blinkCounterAlarm = 0;
    }
  }
  
  switch(_state) {
    
    // Устанавливаем состояние неактивности
    case STATE_OFF : {
      GPIO_PinState state = (_isInverted) ? (GPIO_PIN_SET) : (GPIO_PIN_RESET);
      HAL_GPIO_WritePin(_port, _pin, state);
      _state = STATE_INACTIVE;
      break;
    }
    
    // Устанавливаем состояние активности
    case STATE_ON : {
      GPIO_PinState state = (_isInverted) ? (GPIO_PIN_RESET) : (GPIO_PIN_SET);
      HAL_GPIO_WritePin(_port, _pin, state);
      _state = STATE_INACTIVE;
      break;
    }
    
    // Устанавливаем мигание
    case STATE_BLINK : {
      GPIO_PinState state = (_blinkState) ? (GPIO_PIN_RESET) : (GPIO_PIN_SET);
      HAL_GPIO_WritePin(_port, _pin, state);
      break;
    }
    
    // Установить сигнальное мигание
    case STATE_BLINK_ALARM : {

      GPIO_PinState state = (_blinkStateAlarm) ? (GPIO_PIN_RESET) : (GPIO_PIN_SET);
      HAL_GPIO_WritePin(_port, _pin, state);
      break;
    }
    
    // Установить одноразовое мигание
    case STATE_BLINK_ONCE : {
      
      _blinkCounterOnce++;
      if (_blinkCounterOnce == _blinkDelay) {
        GPIO_PinState state = (_isInverted) ? (GPIO_PIN_RESET) : (GPIO_PIN_SET);
        HAL_GPIO_WritePin(_port, _pin, state);
      } else if (_blinkCounterOnce > (_blinkDelay * 2)) {
        GPIO_PinState state = (_isInverted) ? (GPIO_PIN_SET ) : (GPIO_PIN_RESET);
        HAL_GPIO_WritePin(_port, _pin, state);
        _blinkCounterOnce = 0;
        _state = STATE_INACTIVE;
      }
      break;
    }
    
    default : {
      _state = STATE_INACTIVE;
    }
  }
}

/**
 * @brief Методы класса
 */

/**
 * @brief Зарегистрировать GPIO
 * @param port - порт gpio
 * @param pin - пин gpio
 */
void Led :: registerOutput(GPIO_TypeDef* port, uint16_t pin) {
  
  _port = port;
  _pin = pin;
}

/**
 * @brief Установить количество тиков до смены состояния
 * @param delay - количество тиков
 */
void Led :: setBlinkDelay(uint16_t delay) {
  
  _blinkDelay = delay;
}

/**
 * @brief Установить состояние инвертированности
 * @param state - состояние
 */
void Led :: setInverted(bool state) {
  
  _isInverted = state;
}

/**
 * @brief Установить указатель на интерфейс оповещения
 * @param iLed - интерфейс ILed
 */
void Led :: setILed(ILed* iLed) {
  
  _iLed = iLed;
}
