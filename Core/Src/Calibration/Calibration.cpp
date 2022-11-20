/**
  ******************************************************************************
  * @file    Calibration.cpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    16.07.2022
  * @brief   Calibration
  *          Класс реализации калибровки устройства
  ******************************************************************************
  */

#include "Calibration.hpp"
#include "EnumFlashRegisters.hpp"
#include "stm32f1xx.h"

/**
 * @brief Конструктор
 * @param iLogicInputOpen - интерфейс ILogicInput
 * @param iLogicInputClose - интерфейс ILogicInput
 * @param iPositionComplete - интерфейс IPositionComplete
 * @param iStorage - интерфейс IStorage.
 * @param iLogicOutputReleOpen - интерфейс ILogicOutput
 * @param iLogicOutputReleClose - интерфейс ILogicOutput
 */
Calibration :: Calibration(ILogicInput* iLogicInputOpen,
                           ILogicInput* iLogicInputClose,
                           IPositionComplete* iPositionComplete,
                           IStorage* iStorage,
                           ILogicOutput* iLogicOutputReleOpen,
                           ILogicOutput* iLogicOutputReleClose) 
{
  setILogicInputOpen(iLogicInputOpen);
  setILogicInputClose(iLogicInputClose);
  setIPositionComplete(iPositionComplete);
  setIStorage(iStorage);
  setILogicOutputOpen(iLogicOutputReleOpen);
  setILogicOutputClose(iLogicOutputReleClose);
  
  setILed(LED_ONE, nullptr);
  setILed(LED_TWO, nullptr);
  setILed(LED_THREE, nullptr);
  setILed(LED_FOUR, nullptr);
  setILed(LED_FIVE, nullptr);
  
  // Устанавливаем состояние неинициализированности
  _calibration.valueMin = 0xFFFF;
  _calibration.valueMax = 0xFFFF;
  _calibration.rangeMin = 0xFFFF;
  _calibration.rangeMax = 0xFFFF;
  
  _isCalibratedOpen = true;
  _isCalibratedClose = true;
}

/**
 * @brief Метод интерфейса IObserver
 *        Периодическая процедура: процедура калибровки.
 */  
void Calibration :: observe() {
  
  // В зависимости от текущего состояния класса
  if (getActivation() == false) {
    
    // В зависимости от внутреннего состояния
    switch (_calibrationActivity) {
      
      // Состояние ожидания снятия активности нажатий
      case ACTIVITY_START_INACTIVATION_AWAITING : {
        
        // Отправляем светодиодам состояние мигания
        setLedState(_iLed[LED_ONE], ILed::STATE_BLINK);
        setLedState(_iLed[LED_FIVE], ILed::STATE_BLINK);
        
        // Получаем флаг необходимости смены состояния для начала
        bool isActivityNone = true;
        isActivityNone &= (_iLogicInputOpen->getActivation() == false);
        isActivityNone &= (_iLogicInputClose->getActivation() == false);
        
        if (isActivityNone == true) {
          _calibrationActivity = ACTIVITY_CALIBRATION_ROUTINE;
          
        }
        break;
      }
      
      // Состояние ожидания калибровки
      case ACTIVITY_CALIBRATION_ROUTINE : {
        
        // Получаем состояния кнопки "Открыть"
        bool isPressedOpen = _iLogicInputOpen->getActivation();
        bool isLongPressedOpen = _iLogicInputOpen->getLongActivation();
        
        // Получаем состояния кнопки "Закрыть"
        bool isPressedClose = _iLogicInputClose->getActivation();
        bool isLongPressedClose = _iLogicInputClose->getLongActivation();
        
        // Если зажали кнопку "закрыто" и не нажали открыто
        if ((isLongPressedClose == true) && (isPressedOpen == false)) {
          // Забираем значения калибровки мин
          _calibrationLocal.valueMax = _iPositionComplete->getPosition();
          _calibrationLocal.rangeMax = _iPositionComplete->getRange();
          _isCalibratedClose = true;
          
        }
        
        // Если нажали кнопку "открыто" - забираем значения калибровки макс
        if ((isLongPressedOpen == true) && (isPressedClose == false)) {
          _calibrationLocal.valueMin = _iPositionComplete->getPosition();
          _calibrationLocal.rangeMin = _iPositionComplete->getRange();
          _isCalibratedOpen = true;
          setLedState(_iLed[LED_ONE], ILed::STATE_ON);
        }
        
        if (getAllowability() == true) {
          
          // Реакция на нормальный ренж калибровки
          if (_isCalibratedOpen == false) {
            setLedState(_iLed[LED_ONE], ILed::STATE_BLINK);
          } else {
            setLedState(_iLed[LED_ONE], ILed::STATE_ON);
          }
          if (_isCalibratedClose == false) {
            setLedState(_iLed[LED_FIVE], ILed::STATE_BLINK);
          } else {
            setLedState(_iLed[LED_FIVE], ILed::STATE_ON);
          }
          
          // Если зажали обе кнопки, то применяем калибровку
          if ((isLongPressedOpen == true) && (isLongPressedClose == true)) {
            
            // Получаем состояние калибровки
            bool isRecalibrated = true;
            isRecalibrated &= _calibrationLocal.valueMin != 0xFFFF;
            isRecalibrated &= _calibrationLocal.valueMax != 0xFFFF;
            
            // Только если перекалибровались
            if (isRecalibrated == true) {
              
              // Устанавливаем калибровку во структуру для выдачи
              _calibration.valueMin = _calibrationLocal.valueMin;
              _calibration.valueMax = _calibrationLocal.valueMax;
              _calibration.rangeMin = _calibrationLocal.rangeMin;
              _calibration.rangeMax = _calibrationLocal.rangeMax;
              
              // Сохраняем параметры во флеш
              _iStorage->writeRegister(FLASH_REG_CAL_VALUE_MIN, _calibration.valueMin);
              _iStorage->writeRegister(FLASH_REG_CAL_VALUE_MAX, _calibration.valueMax);
              _iStorage->writeRegister(FLASH_REG_CAL_RANGE_MIN, _calibration.rangeMin);
              _iStorage->writeRegister(FLASH_REG_CAL_RANGE_MAX, _calibration.rangeMax);
            }
            
            // Изменяем состояние класса
            _calibrationActivity = ACTIVITY_FINISH_INACTIVATION_AWAITING;
            
            // Мигаем единожды всеми доступными светодиодами
            for (uint8_t i = 0; i < LED_LIMIT; i++) {
              _iLed[i]->blinkOnce();
            }
          }
        } else {
          
          // Реакция на превышение диапазона калибровки
          setLedState(_iLed[LED_ONE], ILed::STATE_BLINK_ALARM);
          setLedState(_iLed[LED_FIVE], ILed::STATE_BLINK_ALARM);
        }
        break;
      }
      
      // Состояние ожидания снятия активности нажатий для завершения
      case ACTIVITY_FINISH_INACTIVATION_AWAITING : {
        
        // Получаем флаг необходимости смены состояния
        bool isActivityNone = true;
        isActivityNone &= (_iLogicInputOpen->getActivation() == false);
        isActivityNone &= (_iLogicInputClose->getActivation() == false);
        
        if (isActivityNone == true) {
          
          // Отправляем светодиодам состояние мигания
          setLedState(_iLed[LED_ONE], ILed::STATE_OFF);
          setLedState(_iLed[LED_FIVE], ILed::STATE_OFF);
          
          // Изменяем состояние класса
          _calibrationState = CALIBRATION_INACTIVE;
          
          _positionActivation->deactivate();
          
          // Выключаем реле блокировки
          setReleStates(false);
          
          // Выполняем перезагрузку устройства
          HAL_NVIC_SystemReset();
        }
        break;
      }
      
      default : {
        __nop();
      }
    }
  } else {
    // Ожидаем длительной активации OPEN и CLOSE
    bool isActivateCalibration = _iLogicInputOpen->getLongActivation();
    isActivateCalibration &= _iLogicInputClose->getLongActivation();
    
    // Проверяем флаг необходимости изменить состояние класса
    if (isActivateCalibration == true) {
      // Задаём состояние активности калибровки
      _calibrationState = CALIBRATION_ACTIVE;
      // Задаём внутреннее состояние калибровки
      _calibrationActivity = ACTIVITY_START_INACTIVATION_AWAITING;
      // Отправляем светодиодам состояние включения
      setLedState(_iLed[LED_ONE], ILed::STATE_ON);
      setLedState(_iLed[LED_FIVE], ILed::STATE_ON);
      
      // Устанавливаем состояния остуствия калибровки
      _calibrationLocal.valueMin = 0xFFFF;
      _calibrationLocal.valueMax = 0xFFFF;
      _calibrationLocal.rangeMin = 0xFFFF;
      _calibrationLocal.rangeMax = 0xFFFF;
      // Включаем реле блокировки
      setReleStates(true);
      
      _isCalibratedOpen = false;
      _isCalibratedClose = false;
    }
  }
}

/**
 * @brief Метод интерфейса ICalibration
 *        Получить имеющуюся структуру калибровки.
 * @return структура Calibration
 */  
ICalibration::Calibration Calibration :: getCalibrationStruct() {
  
  return _calibration;
}

/**
 * @brief Метод интерфейса ILogicInput
 *        Получить состояние активации.
 * @return Состояние активации
 */  
bool Calibration :: getActivation() {
  
  // Возвращаем состояние активности калибровки на текущий момент
  return static_cast<bool>(_calibrationState == CALIBRATION_INACTIVE);
}

/**
 * @brief Метод интерфейса ILogicInput
 *        Получить состояние длительной активации.
 * @return Состояние длительной активации
 */  
bool Calibration :: getLongActivation() {
  
  // Длительного нажатия не предусмотрено
  return false;
}

/**
 * @brief Методы класса
 */

/**
 * @brief Инициализация - чтение регистров из Flash памяти
 */ 
void Calibration :: init() {
  
  // Читаем параметры из флеш
  _calibration.valueMin = _iStorage->readRegister(FLASH_REG_CAL_VALUE_MIN);
  _calibration.valueMax = _iStorage->readRegister(FLASH_REG_CAL_VALUE_MAX);
  _calibration.rangeMin = _iStorage->readRegister(FLASH_REG_CAL_RANGE_MIN);
  _calibration.rangeMax = _iStorage->readRegister(FLASH_REG_CAL_RANGE_MAX);
}

/**
 * @brief Задать интерфейс состояния входа OPEN
 * @param iLogicInput - интерфейс ILogicInput
 */
void Calibration :: setILogicInputOpen(ILogicInput* iLogicInput) {
  
  _iLogicInputOpen = iLogicInput;
}

/**
 * @brief Задать интерфейс состояния входа CLOSE
 * @param iLogicInput - интерфейс ILogicInput
 */
void Calibration :: setILogicInputClose(ILogicInput* iLogicInput) {
  
  _iLogicInputClose = iLogicInput;
}

/**
 * @brief Задать интерфейс получения текущей позиции и диапазона
 * @param iPositionComplete - интерфейс IPositionComplete
 */
void Calibration :: setIPositionComplete(IPositionComplete* iPositionComplete) {
  
  _iPositionComplete = iPositionComplete;
}

/**
 * @brief Задать интерфейс сохранения параметров
 * @param iStorage - интерфейс IStorage
 */
void Calibration :: setIStorage(IStorage* iStorage) {
  
  _iStorage = iStorage;
}

/**
 * @brief Задать интерфейс управления выходом реле "Открыто"
 * @param iLogicOutput - интерфейс ILogicOutput
 */
void Calibration :: setILogicOutputOpen(ILogicOutput* iLogicOutput) {
  
  _iLogicOutputReleOpen = iLogicOutput;
}

/**
 * @brief Задать интерфейс управления выходом реле "Закрыто"
 * @param iLogicOutput - интерфейс ILogicOutput
 */
void Calibration :: setILogicOutputClose(ILogicOutput* iLogicOutput) {
  
  _iLogicOutputReleClose = iLogicOutput;
}

/**
 * @brief Задать интерфейс управления светодиодом
 * @param ledId - идентификатор светодиода
 * @param iLed - интерфейс ILed
 */
void Calibration :: setILed(LedId ledId, ILed* iLed) {
  
  _iLed[ledId] = iLed;
}

/**
 * @brief Приватные методы класса
 */

/**
 * @brief Получить состояние допустимости продолжения калибровки
 */
bool Calibration :: getAllowability() {
  
  // Проверяем текущее положение калибровки на соответствие диапазону
  bool isMinCalibrated = _calibrationLocal.valueMin != 0xFFFF;
  bool isMaxCalibrated = _calibrationLocal.valueMax != 0xFFFF;
  
  // Результат допустимости - интервал не должен превышать RANGE_SIZE
  bool result = false;
  
  // Получаем текущий код позиции
  uint16_t position = _iPositionComplete->getPosition();
  uint16_t range = _iPositionComplete->getRange();
  
  // В зависимости от текущего состояния калибровки высчитываем допустимость.
  if (isMinCalibrated == false && isMaxCalibrated == false) {
    
    // Ничего не скалибровано -> отдаём true
    result = true;
    
  } else if (isMinCalibrated == true && isMaxCalibrated == false) {
    
    // Получаем интервал от min с переходом через RANGE_SIZE
    uint32_t intervalCal = _calibrationLocal.rangeMin * RANGE_SIZE + _calibrationLocal.valueMin;
    uint32_t intervalCur = range * RANGE_SIZE + position;
    
    // Проверяем переход через размер диапазона
    if (intervalCal >= intervalCur) {
      result = ((intervalCal - intervalCur) < RANGE_SIZE);
    } else {
      result = ((intervalCur - intervalCal) < RANGE_SIZE);
    }
    
  } else if (isMinCalibrated == false && isMaxCalibrated == true) {
    
    // Получаем интервал от min с переходом через RANGE_SIZE
    uint32_t intervalCal = _calibrationLocal.rangeMax * RANGE_SIZE + _calibrationLocal.valueMax;
    uint32_t intervalCur = range * RANGE_SIZE + position;
    
    // Проверяем переход через размер диапазона
    if (intervalCal >= intervalCur) {
      result = ((intervalCal - intervalCur) < RANGE_SIZE);
    } else {
      result = ((intervalCur - intervalCal) < RANGE_SIZE);
    }
    
  } else {
    
    // Получаем интервал от min с переходом через RANGE_SIZE
    uint32_t intervalMin = _calibrationLocal.rangeMin * RANGE_SIZE + _calibrationLocal.valueMin;
    uint32_t intervalMax = _calibrationLocal.rangeMax * RANGE_SIZE + _calibrationLocal.valueMax;
    
    // Проверяем переход через размер диапазона
    if (intervalMax >= intervalMin) {
      result = ((intervalMax - intervalMin) < RANGE_SIZE);
    } else {
      result = ((intervalMin - intervalMax) < RANGE_SIZE);
    }
  }
  // Возвращаем результат
  return result;
}



void Calibration :: setLedState(ILed* iLed, ILed::State state) {
  
  switch(state) {
    
    // Устанавливаем состояние активности
    case ILed::STATE_ON : {
      iLed->activate();
      break;
    }
    
    // Устанавливаем состояние неактивности
    case ILed::STATE_OFF : {
      iLed->deactivate();
      break;
    }
    
    // Устанавливаем мигание
    case ILed::STATE_BLINK : {
      iLed->blink();
      break;
    }
    
    // Установить сигнальное мигание
    case ILed::STATE_BLINK_ALARM : {
      iLed->blinkAlarm();
      break;
    }
    default : {
      
    }
  }
}

/**
 * @brief Установить состояния Реле
 * @param state - состояние реле
 */
void Calibration :: setReleStates(bool state) {
  
  if (state == true) {
    _iLogicOutputReleOpen->activate();
    _iLogicOutputReleClose->activate();
  } else {
    _iLogicOutputReleOpen->deactivate();
    _iLogicOutputReleClose->deactivate();
  }
}
