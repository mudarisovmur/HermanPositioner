/**
  ******************************************************************************
  * @file    StorageFlashDefault.hpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    24.07.2022
  * @brief   StorageFlashDefault
  *          Класс хранилища данных во внутренней Flash памяти
  ******************************************************************************
  */

#include "EnumFlashRegisters.hpp"

#ifndef STORAGE_FLASH_DEFAULT_HPP                   //< Avoid multiple inclusion
#define STORAGE_FLASH_DEFAULT_HPP

// Дефолтные регистры флешки
uint16_t defaultFlashRegisters[FLASH_REG_LIMIT] = {
  
  0x0000, //< FLASH_REG_CAL_VALUE_MIN
  0x1FFF, //< FLASH_REG_CAL_VALUE_MAX,
  0x20,   //< FLASH_REG_CAL_RANGE_MIN,
  0x20    //< FLASH_REG_CAL_RANGE_MAX,
};


#endif // STORAGE_FLASH_DEFAULT_HPP

/**
  ******************************************************************************
  *  Вер. |   гггг-ммм-дд   | Внес изменения | Описание изменений
  *  =====|=================|================|==================================
  *   1.0 |   24.07.2022    | Мударисов Т.Р. | Первый релиз
  *  -----|-----------------|----------------|----------------------------------
  ******************************************************************************
  */
