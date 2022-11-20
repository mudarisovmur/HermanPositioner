/**
  ******************************************************************************
  * @file    LogicControl.hpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    27.07.2022
  * @brief   LogicControl
  *          Класс для управления логическим выходом по логическому входу
  ******************************************************************************
  */
  
#include "LogicControl.hpp"
  
/**
 * @brief Конструктор
 * @param iLogicInput - интерфейс ILogicInput
 * @param iLogicOutput - интерфейс ILogicOutput
 */
LogicControl :: LogicControl(ILogicInput* iLogicInput,
                             ILogicOutput* iLogicOutput) {
  setILogicInput(iLogicInput);
  setILogicOutput(iLogicOutput);
}

/**
 * @brief Метод интерфейса IObserver
 *        Периодическая процедура
 */  
void LogicControl :: observe() {
  
  if (_iLogicInput->getActivation() == true) {
    _iLogicOutput->activate();
  } else {
    _iLogicOutput->deactivate();
  }
}

/**
 * @brief Задать интерфейс логического входа
 * @param iLogicInput - интерфейс ILogicInput
 */
void LogicControl :: setILogicInput(ILogicInput* iLogicInput) {
  
  _iLogicInput = iLogicInput;
}

/**
 * @brief Задать интерфейс логичесокго выхода
 * @param iLogicOutput - интерфейс ILogicOutput
 */
void LogicControl :: setILogicOutput(ILogicOutput* iLogicOutput) {
  
  _iLogicOutput = iLogicOutput;
}