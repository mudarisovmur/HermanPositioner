/**
  ******************************************************************************
  * @file    Kernel.cpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    24.07.2022
  * @brief   Kernel
  *          Класс управления ядром устройства
  ******************************************************************************
  */

#include "Kernel.hpp"

/**
 * @brief Конструктор
 * @param iPercent - интерфейс IPercent
 * @param iLed - интерфейс ILed
 * @param iLogicInput - интерфейс ILogicInput
 * @param iLogicOutputReleOpen - интерфейс ILogicOutput
 * @param iLogicOutputReleClose - интерфейс ILogicOutput
 */
Kernel :: Kernel(IPercent* iPercent,
                 ILed* iLed,
                 ILogicInput* iLogicInput,
                 ILogicOutput* iLogicOutputReleOpen,
                 ILogicOutput* iLogicOutputReleClose) 
{
  setIPercent(iPercent);
  setILed(LED_ONE, iLed);
  setILed(LED_TWO, iLed);
  setILed(LED_THREE, iLed);
  setILed(LED_FOUR, iLed);
  setILed(LED_FIVE, iLed);
  setILogicInput(iLogicInput);
  setILogicOutputOpen(iLogicOutputReleOpen);
  setILogicOutputClose(iLogicOutputReleClose);
  _isActive = false;
  _isBlockedOpen = false;
  _isBlockedClose = false;
  observeDelay = 0;
}

/**
 * @brief Метод интерфейса IObserver
 *        Периодическая процедура
 */  
void Kernel :: observe() {
  
  if (observeDelay++ > 0x20) {
  
    // В зависимости от состояния активации
    if (_iLogicInput->getActivation() == true) {
      
      // Перевыставляем состояние активации
      _isActive = true;
      
      // Получаем процент заполнения положения
      float percent = _iPercent->getPercent();
      
      // Вызываем отображение состояния в зависимости от процента заполнения
      if (percent == 0.0f) {
        
        _isBlockedOpen = true;
        _isBlockedClose = false;
        setReleStates(_isBlockedOpen, _isBlockedClose);
        setLedStates(true, false, false, false, false);
      } else if (percent > 0.0f && percent < 20.0f) {
        
        // Гистерезис для реле блокировки начала диапазона
        if (percent >= 5.0f) {
          _isBlockedOpen = false;
          _isBlockedClose = false;
        }
        setReleStates(_isBlockedOpen, _isBlockedClose);
        setLedStates(true, false, false, false, false);
      } else if (percent >= 20.0f && percent < 40.0f) {
        
        setReleStates(false, false);
        setLedStates(false, true, false, false, false);
      } else if (percent >= 40.0f && percent < 60.0f) {
        
        setReleStates(false, false);
        setLedStates(false, false, true, false, false);
      } else if (percent >= 60.0f && percent < 80.0f) {
        
        setReleStates(false, false);
        setLedStates(false, false, false, true, false);
      } else if (percent >= 80.0f && percent < 100.0f) {
        
        // Гистерезис для реле блокировки начала диапазона
        if (percent < 95.0f) {
          _isBlockedOpen = false;
          _isBlockedClose = false;
        }
        setReleStates(_isBlockedOpen, _isBlockedClose);
        setLedStates(false, false, false, false, true);
      }else if (percent == 100.0f) {
        
        _isBlockedOpen = false;
        _isBlockedClose = true;
        setReleStates(_isBlockedOpen, _isBlockedClose);
        setLedStates(false, false, false, false, true);
      }
    } else {
      
      // Только в первый раз вылючаем все светодиоды
      if (_isActive == true) {
        
        // Выключаем все светодиоды
        setLedStates(false, false, false, false, false);
        
        // Снимаем состояние активации
        _isActive = false;
      }
    }
  }
}

/**
 * @brief Методы класса
 */

/**
 * @brief Задать интерфейс получения процента положения
 * @param iPercent - интерфейс IPercent
 */
void Kernel :: setIPercent(IPercent* iPercent) {
  
  _iPercent = iPercent;
}

/**
 * @brief Задать интерфейс управления светодиодом
 * @param ledId - идентификатор светодиода
 * @param iLed - интерфейс ILed
 */
void Kernel :: setILed(LedId ledId, ILed* iLed) {
  
  _iLed[ledId] = iLed;
}
  
/**
 * @brief Задать интерфейс состояния допустимости отработки анимации
 * @param iLogicInput - интерфейс ILogicInput
 */
void Kernel :: setILogicInput(ILogicInput* iLogicInput) {
  
  _iLogicInput = iLogicInput;
}

/**
 * @brief Задать интерфейс управления выходом реле "Открыто"
 * @param iLogicOutput - интерфейс ILogicOutput
 */
void Kernel :: setILogicOutputOpen(ILogicOutput* iLogicOutput) {
  
  _iLogicOutputReleOpen = iLogicOutput;
}

/**
 * @brief Задать интерфейс управления выходом реле "Закрыто"
 * @param iLogicOutput - интерфейс ILogicOutput
 */
void Kernel :: setILogicOutputClose(ILogicOutput* iLogicOutput) {
  
  _iLogicOutputReleClose = iLogicOutput;
}

/**
 * @brief Приватные методы класса
 */
  
/**
 * @brief Задать Состояния светодиодов
 * @param iLed1 - интерфейс ILed 1го интервала
 * @param iLed2 - интерфейс ILed 2го интервала
 * @param iLed3 - интерфейс ILed 3го интервала
 * @param iLed4 - интерфейс ILed 4го интервала
 * @param iLed5 - интерфейс ILed 5го интервала
 * @param LedOpen - интерфейс ILed "открыто"
 * @param LedClose - интерфейс ILed "закрыто"
 */
void Kernel :: setLedStates(bool Led1, bool Led2, bool Led3, bool Led4, bool Led5/*, bool LedOpen, bool LedClose*/) {
  
  // Отработка светодиодов
  Led1 ? _iLed[LED_ONE]->activate() : _iLed[LED_ONE]->deactivate();
  Led2 ? _iLed[LED_TWO]->activate() : _iLed[LED_TWO]->deactivate();
  Led3 ? _iLed[LED_THREE]->activate() : _iLed[LED_THREE]->deactivate();
  Led4 ? _iLed[LED_FOUR]->activate() : _iLed[LED_FOUR]->deactivate();
  Led5 ? _iLed[LED_FIVE]->activate() : _iLed[LED_FIVE]->deactivate();
}

/**
 * @brief Задать cостояния реле
 * @param LedOpen - интерфейс ILed "открыто"
 * @param LedClose - интерфейс ILed "закрыто"
 */
void Kernel :: setReleStates(bool releOpen, bool releClose) {
  
  releOpen ? _iLogicOutputReleOpen->activate() : _iLogicOutputReleOpen->deactivate();
  releClose ? _iLogicOutputReleClose->activate() : _iLogicOutputReleClose->deactivate();
}
