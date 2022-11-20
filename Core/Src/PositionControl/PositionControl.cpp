/**
  ******************************************************************************
  * @file    PositionControl.hpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    23.07.2022
  * @brief   PositionControl
  *          Класс обработки данных позиции
  ******************************************************************************
  */

#include "PositionControl.hpp"

/**
 * @brief Конструктор
 * @param iPosition - интерфейс IPosition
 * @param iCalibration - интерфейс ICalibration
 * @param iLed - интерфейс ILed
 */
PositionControl :: PositionControl(IPosition* iPosition,
                                   ICalibration* iCalibration,
                                   ILed* iLed) 
{
  setICalibration(iCalibration);
  setIPosition(iPosition);
  activateHysteresisBlink(false, 0u);
  _isInited = false;
}

/**
 * @brief Метод интерфейса IPositionComplete
 *        Получить код положения
 * @return код положения в HEX
 */  
uint16_t PositionControl :: getPosition() {
  
  return _position;
}

/**
 * @brief Метод интерфейса IPositionComplete
 *        Получить диапазон положения.
 * @return код положения в HEX
 */  
uint16_t PositionControl :: getRange() {
  
  return _range;
}

/**
 * @brief Метод интерфейса IProcess
 *        Выполнить операцию - обработать значение
 */  
void PositionControl :: process() {
  
  // Получаем значение по интерфейсу
  uint16_t currentPosition = _iPosition->getPosition();
  
  // В зависимости от флага инициализации
  if (_isInited == true) {
    
    // Контролируем изменение диапазона
    if (currentPosition > _position) {
      // Если переходим через 0 влево
      if ((currentPosition - _position) >= REFRESH_THRESHOLD) {
        activateHysteresisBlink(false, _range * RANGE_SIZE + _position);
        _range--;
      }
    } else if (currentPosition <= _position) {
      // Если переходим через 0 вправо
      if ((_position - currentPosition) >= REFRESH_THRESHOLD) {
        activateHysteresisBlink(true, _range * RANGE_SIZE + _position);
        _range++;
      }
    }
    // Изменяем позицию
    _position = currentPosition;
    
    // Отрабатываем блинк гистерезисный через ноль
    checkHysteresisBlink();
    
  } else {
    
    // Получаем текущее значение позиции
    _position = currentPosition;
    
    // Получаем структуру калибровки
    ICalibration::Calibration сalibration = _iCalibration->getCalibrationStruct();
    
    // Если калибровка была произведена, значит мы находимся в диапазоне
    if (сalibration.valueMin != 0xFFFF && сalibration.valueMax != 0xFFFF) {
      
      // В зависимости от диапазона
      if (сalibration.rangeMin == сalibration.rangeMax) {
        
        // Все в пределах одного диапазона
        _range = сalibration.rangeMin;
        
      } else if (сalibration.rangeMin < сalibration.rangeMax) {
        
        // Определяем диапазон в зависимости от значения 
        if (_position >= сalibration.valueMin) {
          _range = сalibration.rangeMin;
        } else if (_position <= сalibration.valueMax) {
          _range = сalibration.rangeMax;
        } else {
          
          uint16_t valueNearMin;
          uint16_t valueNearMax;
          
          if (_position <= сalibration.valueMin) {
            valueNearMin = сalibration.valueMin - _position;
          } else {
            valueNearMin = _position - сalibration.valueMin;
          }
          
          if (_position >= сalibration.valueMax) {
            valueNearMax = _position - сalibration.valueMax;
          } else {
            valueNearMax = сalibration.valueMax - _position;
          }
          
          _range = valueNearMin < valueNearMax ? сalibration.rangeMin : сalibration.rangeMax;
        }
      } else if (сalibration.rangeMin > сalibration.rangeMax) {
        
        // Определяем диапазон в зависимости от значения 
        if (_position <= сalibration.valueMin) {
          _range = сalibration.rangeMin;
        } else if (_position >= сalibration.valueMax) {
          _range = сalibration.rangeMax;
        } else {
          
          uint16_t valueNearMin;
          uint16_t valueNearMax;
          
          if (_position <= сalibration.valueMin) {
            valueNearMin = сalibration.valueMin - _position;
          } else {
            valueNearMin = _position - сalibration.valueMin;
          }
          
          if (_position >= сalibration.valueMax) {
            valueNearMax = _position - сalibration.valueMax;
          } else {
            valueNearMax = сalibration.valueMax - _position;
          }
          
          _range = valueNearMin < valueNearMax ? сalibration.rangeMin : сalibration.rangeMax;
        }
      }
    } else {
      _range = 0x20;
    }
    // Завершаем инициализацию
    _isInited = true;
  }
}

/**
 * @brief Метод интерфейса IPercent
 *        Получить значение в процентах
 * @return значение в процентах
 */  
float PositionControl :: getPercent() {
  
  // Результат
  float result;
  
  uint32_t minimum;
  uint32_t maximum;
  
  // Получаем структуру калибровки положения
  ICalibration::Calibration сalibration = _iCalibration->getCalibrationStruct();
  
  // Получаем значение минимальной калибровки положения
  uint32_t open = сalibration.rangeMin * RANGE_SIZE + сalibration.valueMin;
  
  // Получаем значение максимальной калибровки положения
  uint32_t close = сalibration.rangeMax * RANGE_SIZE + сalibration.valueMax;
  
  // Получаем флаг инвертированного диапазона
  bool isOpenLessThenClose = open > close;
  
  // В зависимости от флага получаем
  if (isOpenLessThenClose == true) {
    minimum = close;
    maximum = open;
  } else {
    minimum = open;
    maximum = close;
  }
  
  // Получаем текущее значенеие положения
  uint32_t current = _range * RANGE_SIZE + _position;
  
  // Ограничиваем результат в зависимости от положения
  if (current <= minimum) {
    result = 0.0f;
    } else if (current >= maximum) {
    result = 100.0f;
  } else {
    current -= minimum;
    maximum -= minimum;
    result = static_cast<float>(current) / static_cast<float>(maximum);
    result *= 100.0f;
  }
  
  if (isOpenLessThenClose == true) {
    _currentPercent = 100.0f - result;
    result = _currentPercent;
  } else {
    _currentPercent = result;
  }
  // Возвращаем результат
  return result;
}

/**
 * @brief Метод интерфейса ILogicOutput
 *        Активировать логической выход.
 */  
void PositionControl :: activate() {
  
  _isInited = true;
}

/**
 * @brief Метод интерфейса ILogicOutput
 *        Деактивировать логической выход.
 */  
void PositionControl :: deactivate() {
  
  _isInited = false;
}

/**
 * @brief Методы класса
 */

/**
 * @brief Задать интерфейс получения необработанной позиции
 * @param iPosition - интерфейс IPosition
 */
void PositionControl :: setIPosition(IPosition* iPosition) {
  
  _iPosition = iPosition;
}

/**
 * @brief Задать интерфейс получения калибровки
 * @param iCalibration - интерфейс ICalibration
 */
void PositionControl :: setICalibration(ICalibration* iCalibration) {
  
  _iCalibration = iCalibration;
}

/**
 * @brief Задать интерфейс управления светодиодом "Нулевая точка" 
 * @param iLed - интерфейс ILed
 */
void PositionControl :: setILed(ILed* iLed) {
  
  _iLedNul = iLed;
}

/**
 * @brief Приватные методы класса
 */
 
/**
 * @brief Активировать блинк через гистерезис
 * @param direction - направление
 * @param value - значение
 */
void PositionControl :: activateHysteresisBlink(bool direction, uint32_t value) {
  
  // Устанавливаем направление рассчёта
  _hysteresisBlinkDirection = direction;
  
  // Устанавливаем значение перехода
  _hysteresisBlinkValue = value;
}

/**
 * @brief Проверить блинк
 */
void PositionControl :: checkHysteresisBlink() {
  
  if (_hysteresisBlinkValue != 0u) {
    
    if (_hysteresisBlinkDirection == true) {
      
      if ((_range * RANGE_SIZE + _position) - _hysteresisBlinkValue >  HYSTERESIS_THRESHOLD) {
        
        _hysteresisBlinkValue = 0u;
        
        _iLedNul->blinkOnce();
      }
      
    } else {
      
      if (_hysteresisBlinkValue - (_range * RANGE_SIZE + _position) >  HYSTERESIS_THRESHOLD) {
        
        _hysteresisBlinkValue = 0u;
        
        _iLedNul->blinkOnce();
      }
    }
  }
}
