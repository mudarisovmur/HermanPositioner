/**
  ******************************************************************************
  * @file    EnumLed.hpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    03.08.2022
  * @brief   EnumLed
  *          Нумераторы для работы со светодиодами
  ******************************************************************************
  */

#ifndef ENUM_LED_HPP                           //< Avoid multiple inclusion
#define ENUM_LED_HPP

#include "stdint.h"

enum LedId {
  LED_ONE,
  LED_TWO,
  LED_THREE,
  LED_FOUR,
  LED_FIVE,
  LED_LIMIT
};

#endif  // ENUM_LED_HPP

/**
  ******************************************************************************
  *  Вер. |   гггг-ммм-дд   | Внес изменения | Описание изменений
  *  =====|=================|================|==================================
  *   1.0 |   03.08.2022    | Мударисов Т.Р. | Первый релиз
  *  -----|-----------------|----------------|----------------------------------
  ******************************************************************************
  */
