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
  
#include "AdapterILogicOutputILogicInput.hpp"
  
/**
 * @brief Конструктор
 * @param iLogicInput - интерфейс ILogicInput
 * @param iLogicOutput - интерфейс ILogicOutput
 */
AdapterILogicOutputILogicInput :: AdapterILogicOutputILogicInput() {
  
  _state = false;
}

/**
 * @brief Метод интерфейса ILogicInput
 *        Получить состояние активации.
 * @return Состояние активации
 */  
bool AdapterILogicOutputILogicInput :: getActivation() {
  
  return _state;
}

/**
 * @brief Метод интерфейса ILogicInput
 *        Получить состояние длительной активации.
 * @return Состояние длительной активации
 */  
bool AdapterILogicOutputILogicInput :: getLongActivation() {
  
  return false;
}

/**
 * @brief Метод интерфейса ILogicOutput
 *        Активировать логической выход.
 */  
void AdapterILogicOutputILogicInput :: activate() {
  
  _state = true;
}

/**
 * @brief Метод интерфейса ILogicOutput
 *        Деактивировать логической выход.
 */  
void AdapterILogicOutputILogicInput :: deactivate() {
  
  _state = false;
}
