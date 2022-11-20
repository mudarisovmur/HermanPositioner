/**
  ******************************************************************************
  * @file    Led.hpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    23.07.2022
  * @brief   Led
  *          Класс для управления светодидом
  ******************************************************************************
  */

#ifndef LED_HPP                                     //< Avoid multiple inclusion
#define LED_HPP

#include "stdint.h"
#include "gpio.h"
#include "ILed.hpp"
#include "IObserver.hpp"
  
class Led : public ILed, 
            public IObserver {
  
  public:
  
  /**
   * @brief Конструктор
   */
  Led();
  
  /**
   * @brief Метод интерфейса ILed
   *        Активировать логической выход.
   */  
  virtual void activate() override;
  
  /**
   * @brief Метод интерфейса ILed
   *        Деактивировать логической выход.
   */  
  virtual void deactivate() override;
  
  /**
   * @brief Метод интерфейса ILed
   *        Активировать мигание.
   */  
  virtual void blink() override;
  
  /**
   * @brief Метод интерфейса ILed
   *        Активировать сигнальное мигание.
   */  
  virtual void blinkAlarm() override;
  
  /**
   * @brief Метод интерфейса ILed
   *        Активировать одноразовое мигание
   */  
  virtual void blinkOnce() override;
  
  /**
   * @brief Метод интерфейса IObserver
   *        Периодическая процедура: отработка мигания
   */  
  virtual void observe() override;
  
  /**
   * @brief Методы класса
   */
  
  /**
   * @brief Зарегистрировать GPIO
   * @param port - порт gpio
   * @param pin - пин gpio
   */
  void registerOutput(GPIO_TypeDef* port, uint16_t pin);
  
  /**
   * @brief Установить количество тиков до смены состояния
   * @param delay - количество тиков
   */
  void setBlinkDelay(uint16_t delay);
  
  /**
   * @brief Установить состояние инвертированности
   * @param state - состояние
   */
  void setInverted(bool state);
  
  /**
   * @brief Установить указатель на интерфейс оповещения
   * @param iLed - интерфейс ILed
   */
  static void setILed(ILed* iLed);
  
  private:
  
  /// Порт выхода
  GPIO_TypeDef*                 _port;
  
  /// Указатель на объект изменяющий значения счётчиков
  static ILed*                  _iLed;
  
  /// Номер выхода
  uint16_t                      _pin;
  
  /// Состояние класса
  ILed::State                   _state;
  
  /// Время ожидания перед миганием
  static uint16_t               _blinkDelay;
  
  /// Переменная для хранения общего состояния активации
  static bool                   _blinkState;
  
  /// Переменная для хранения общего состояния активации аварий
  static bool                   _blinkStateAlarm;
  
  /// Счетчик времени мигания
  static uint16_t               _blinkCounter;
  
  /// Счетчик времени мигания
  static uint16_t               _blinkCounterAlarm;
  
  /// Счетчик времени мигания
  uint16_t                      _blinkCounterOnce;
  
  /// Флаг инвертации
  bool                          _isInverted;
};

#endif //LOGIC_OUTPUT_HPP

/**
  ******************************************************************************
  *  Вер. |   гггг-ммм-дд   | Внес изменения | Описание изменений
  *  =====|=================|================|==================================
  *   1.0 |   10.07.2022    | Мударисов Т.Р. | Первый релиз
  *  -----|-----------------|----------------|----------------------------------
  ******************************************************************************
  */
