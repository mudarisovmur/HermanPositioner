/**
  ******************************************************************************
  * @file    IPositionComplete.hpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    23.07.2022
  * @brief   IPositionComplete
  *          Интерфейс получения значения с датчика положения
  ******************************************************************************
  */

#ifndef I_POSITION_COMPLETE_HPP                     //< Avoid multiple inclusion
#define I_POSITION_COMPLETE_HPP

#include "IPosition.hpp"

class IPositionComplete : public IPosition {
  
  public:
  
  /**
   * @brief Получить код положения
   * @return код положения в HEX
   */  
  virtual uint16_t getPosition() = 0;
  
  /**
   * @brief Получить диапазон положения
   * @return код положения в HEX
   */  
  virtual uint16_t getRange() = 0;
};

#endif  // I_POSITION_COMPLETE_HPP

/**
  ******************************************************************************
  *  Вер. |   гггг-ммм-дд   | Внес изменения | Описание изменений
  *  =====|=================|================|==================================
  *   1.0 |   23.07.2022    | Мударисов Т.Р. | Первый релиз
  *  -----|-----------------|----------------|----------------------------------
  ******************************************************************************
  */
