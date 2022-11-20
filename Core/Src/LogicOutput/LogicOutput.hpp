/**
  ******************************************************************************
  * @file    LogicOutput.hpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    10.07.2022
  * @brief   LogicOutput
  *          Класс для управления логическим выходом
  ******************************************************************************
  */

#ifndef LOGIC_OUTPUT_HPP                            //< Avoid multiple inclusion
#define LOGIC_OUTPUT_HPP

#include "stdint.h"
#include "gpio.h"
#include "ILogicOutput.hpp"
#include "IObserver.hpp"
  
class LogicOutput : public ILogicOutput {
  
  public:
  
  /**
   * @brief Конструктор
   */
  LogicOutput();
  
  /**
   * @brief Метод интерфейса ILogicOutput
   *        Активировать логической выход.
   */  
  virtual void activate() override;
  
  /**
   * @brief Метод интерфейса ILogicOutput
   *        Деактивировать логической выход.
   */  
  virtual void deactivate() override;
  
  /**
   * @brief Зарегистрировать GPIO
   * @param port - порт gpio
   * @param pin - пин gpio
   */
  void registerOutput(GPIO_TypeDef* port, uint16_t pin);
  
  /**
   * @brief Установить состояние инвертированности
   * @param isInvert - состояние
   */  
  void setInvert(bool isInvert);
  
  private:
  
  /// Объект семафора
  GPIO_TypeDef*                 _port;
  
  /// Время ожидания семафора
  uint16_t                      _pin;
  
  /// Состояние инвертированности
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
