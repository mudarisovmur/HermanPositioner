/**
  ******************************************************************************
  * @file    ICalibration.hpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    16.07.2022
  * @brief   ICalibration
  *          Интерфейс получения данных калибровки
  ******************************************************************************
  */

#ifndef I_CALIBRATION_HPP                           //< Avoid multiple inclusion
#define I_CALIBRATION_HPP

#include "stdint.h"

class ICalibration {
  
  public:
  
  // Структура калибровки
  struct Calibration {
    uint16_t valueMin;
    uint16_t valueMax;
    uint16_t rangeMin;
    uint16_t rangeMax;
    bool isCalibrated() {
      bool result = true;
      result &= (valueMin != 0xFFFF);
      result &= (valueMax != 0xFFFF);
      result &= (rangeMin != 0xFFFF);
      result &= (rangeMax != 0xFFFF);
      return result;
    }
  };
  
  /**
   * @brief Получить имеющуюся структуру калибровки
   * @return структура Calibration
   */  
  virtual Calibration getCalibrationStruct() = 0;
  
};

#endif  // I_CALIBRATION_HPP

/**
  ******************************************************************************
  *  Вер. |   гггг-ммм-дд   | Внес изменения | Описание изменений
  *  =====|=================|================|==================================
  *   1.0 |   16.07.2022    | Мударисов Т.Р. | Первый релиз
  *  -----|-----------------|----------------|----------------------------------
  ******************************************************************************
  */
