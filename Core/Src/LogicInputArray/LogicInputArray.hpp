/**
  ******************************************************************************
  * @file    LogicInputArray.hpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    27.07.2022
  * @brief   LogicInputArray
  *          Класс для хранения и выдачи результирующего состояния интерфейсов
  ******************************************************************************
  */

#ifndef LOGIC_INPUT_ARRAY_HPP                       //< Avoid multiple inclusion
#define LOGIC_INPUT_ARRAY_HPP

#include "stdint.h"
#include "string.h"
#include "cmsis_os.h"
#include "ILogicInput.hpp"
  
class LogicInputArray : public ILogicInput {
  
  public:
  
  /**
   * @brief Конструктор
   * @brief maxInputs - максимальное количество интерфейсов
   */
  LogicInputArray(uint8_t maxInputs = 8);
  
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
   * @brief Регистрация интерфейса в массиве
   * @param iLogicInput - интерфейс ILogicInput
   */
  void registerILogicInput(ILogicInput* iLogicInput);
  
  enum Logic {
    LOGIC_OR = 0x00,
    LOGIC_AND
  };
  
  /**
   * @brief Задать логику работы класса
   * @param logic - значение из перечисления Logic
   */
  void setLogic(Logic logic);
  
  /**
   * @brief Задать состояние инвертированности
   * @param isInverted - состояние инвертированности
   */
  void setInvertedState(bool isInverted);
  
  private:
  
  /// Массив указателей на интерфейсы IObserver
  ILogicInput**                 _iLogicInputArray;
  
  /// Максимальное количество интерфейсов
  uint8_t                       _maxQuantity; 
  
  /// Текущее количество интерфейсов
  uint8_t                       _currentQuantity; 
  
  /// Логика работы класса
  Logic                         _logic;
  
  /// Логическое состояние инвертации
  bool                          _isInverted;
};

#endif //LOGIC_INPUT_ARRAY_HPP

/**
  ******************************************************************************
  *  Вер. |   гггг-ммм-дд   | Внес изменения | Описание изменений
  *  =====|=================|================|==================================
  *   1.0 |   27.07.2022    | Мударисов Т.Р. | Первый релиз
  *  -----|-----------------|----------------|----------------------------------
  ******************************************************************************
  */
