/**
  ******************************************************************************
  * @file    LogicInput.hpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    10.07.2022
  * @brief   LogicInput
  *          Класс для управления логическим выходом
  ******************************************************************************
  */

#ifndef LOGIC_INPUT_HPP                             //< Avoid multiple inclusion
#define LOGIC_INPUT_HPP

#include "stdint.h"
#include "gpio.h"
#include "ILogicInput.hpp"
#include "IObserver.hpp"
  
class LogicInput : public ILogicInput, 
                   public IObserver {
  
  public:
  
  /**
   * @brief Конструктор
   */
  LogicInput();
  
  /**
   * @brief Метод интерфейса ILogicInput
   *        Получить состояние активации.
   * @return Состояние активации
   */  
  virtual bool getActivation() override;
  
  /**
   * @brief Метод интерфейса ILogicInput
   *        Получить состояние длительной активации.
   * @return Состояние длительной активации
   */  
  virtual bool getLongActivation() override;
  
  /**
   * @brief Метод интерфейса IObserver
   *        Периодическая процедура: процедура калибровки.
   */  
  virtual void observe() override;
  
  /**
   * @brief Зарегистрировать GPIO
   * @param port - порт gpio
   * @param pin - пин gpio
   */
  void registerOutput(GPIO_TypeDef* port, uint16_t pin);
  
  private:
  
  /// Объект семафора
  GPIO_TypeDef*                 _port;
  
  /// Время ожидания семафора
  uint16_t                      _pin;
  
  /// Текущее состояние активации
  bool                          _stateActivation;
  
  /// Текущее состояние длительной активации
  bool                          _stateLongActivation;
  
  /// Текущее количество тиков до активации
  uint16_t                      _activationTicks;
  
  /// Текущее количество тиков до снятия активации
  uint16_t                      _resetTicks;
  
  /// Количество тиков до активации
  static const uint16_t          ACTIVATION_TIME = 0x500;
  
  /// Количество тиков до длительной активации
  static const uint16_t          LONG_ACTIVATION_TIME = 0x5000;
  
  /// Количество тиков до снятия активации
  static const uint16_t          RESET_TIME = 0x100;
};

#endif //LOGIC_INPUT_HPP

/**
  ******************************************************************************
  *  Вер. |   гггг-ммм-дд   | Внес изменения | Описание изменений
  *  =====|=================|================|==================================
  *   1.0 |   10.07.2022    | Мударисов Т.Р. | Первый релиз
  *  -----|-----------------|----------------|----------------------------------
  ******************************************************************************
  */
