/**
  ******************************************************************************
  * @file    LogicControl.hpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    27.07.2022
  * @brief   LogicControl
  *          Класс для управления логическим выходом по логическому входу
  ******************************************************************************
  */

#ifndef LOGIC_CONTROL_HPP                           //< Avoid multiple inclusion
#define LOGIC_CONTROL_HPP

#include "stdint.h"
#include "IObserver.hpp"
#include "ILogicInput.hpp"
#include "ILogicOutput.hpp"

  
class LogicControl : public IObserver {
  
  public:
  
  /**
   * @brief Конструктор
   * @param iLogicInput - интерфейс ILogicInput
   * @param iLogicOutput - интерфейс ILogicOutput
   */
  LogicControl(ILogicInput* iLogicInput = nullptr,
               ILogicOutput* iLogicOutput = nullptr);
  
  /**
   * @brief Метод интерфейса IObserver
   *        Периодическая процедура
   */  
  virtual void observe() override;
  
  /**
   * @brief Задать интерфейс логического входа
   * @param iLogicInput - интерфейс ILogicInput
   */
  void setILogicInput(ILogicInput* iLogicInput);
  
  /**
   * @brief Задать интерфейс логичесокго выхода
   * @param iLogicOutput - интерфейс ILogicOutput
   */
  void setILogicOutput(ILogicOutput* iLogicOutput);
  
  private:
  
  /// Интерфейс логического входа
  ILogicInput*                  _iLogicInput;
  
  /// Интерфейс логичесокго выхода
  ILogicOutput*                 _iLogicOutput;
};

#endif //LOGIC_CONTROL_HPP

/**
  ******************************************************************************
  *  Вер. |   гггг-ммм-дд   | Внес изменения | Описание изменений
  *  =====|=================|================|==================================
  *   1.0 |   27.07.2022    | Мударисов Т.Р. | Первый релиз
  *  -----|-----------------|----------------|----------------------------------
  ******************************************************************************
  */
