/**
  ******************************************************************************
  * @file    AdapterILogicOutputILogicInput.hpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    27.07.2022
  * @brief   AdapterILogicOutputILogicInput
  *          Адаптер управления логическим входом по логическому выходу
  ******************************************************************************
  */

#ifndef ADAPTER_I_LOGIC_OUTPUT_I_LOGIC_INPUT_HPP    //< Avoid multiple inclusion
#define ADAPTER_I_LOGIC_OUTPUT_I_LOGIC_INPUT_HPP

#include "stdint.h"
#include "IObserver.hpp"
#include "ILogicInput.hpp"
#include "ILogicOutput.hpp"

class AdapterILogicOutputILogicInput : public ILogicInput,
                                       public ILogicOutput {
  
  public:
  
  /**
   * @brief Конструктор
   */
  AdapterILogicOutputILogicInput();
  
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
   * @brief Метод интерфейса ILogicOutput
   *        Активировать логической выход.
   */  
  virtual void activate() override;
  
  /**
   * @brief Метод интерфейса ILogicOutput
   *        Деактивировать логической выход.
   */  
  virtual void deactivate() override;
  
  private:
  
  /// Состояние класса
  bool                          _state;
};

#endif //ADAPTER_I_LOGIC_OUTPUT_I_LOGIC_INPUT_HPP

/**
  ******************************************************************************
  *  Вер. |   гггг-ммм-дд   | Внес изменения | Описание изменений
  *  =====|=================|================|==================================
  *   1.0 |   27.07.2022    | Мударисов Т.Р. | Первый релиз
  *  -----|-----------------|----------------|----------------------------------
  ******************************************************************************
  */
