/**
  ******************************************************************************
  * @file    DeviceGlobalCalibration.hpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    23.07.2022
  * @brief   DeviceGlobalCalibration
  *          Часть объекта для глобального взаимодействия с устройством
  ******************************************************************************
  */
  
#include "DeviceGlobal.hpp"

  public :
  
  /**
   * @brief Инициализация калибровки
   */
  void initCalibration();
  
  private :
  
  /// Объект калибровки
  Calibration                   _calibration;
  
  /// Объект получения текущего положения и диапазона
  PositionControl               _positionControl;
  
/**
  ******************************************************************************
  *  Вер. |   гггг-ммм-дд   | Внес изменения | Описание изменений
  *  =====|=================|================|==================================
  *   1.0 |   23.07.2022    | Мударисов Т.Р. | Первый релиз
  *  -----|-----------------|----------------|----------------------------------
  ******************************************************************************
  */
