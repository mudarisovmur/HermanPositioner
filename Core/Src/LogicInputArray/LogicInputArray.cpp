/**
  ******************************************************************************
  * @file    LogicInputArray.hpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    27.07.2022
  * @brief   LogicInputArray
  *          Класс для хранения и выдачи результирующего состояния интерфейсов
  ******************************************************************************
  */
  
#include "LogicInputArray.hpp"

/**
 * @brief Конструктор
 * @brief maxInputs - максимальное количество интерфейсов
 */
LogicInputArray :: LogicInputArray(uint8_t maxInputs) {
  
  _maxQuantity = maxInputs;
  _currentQuantity = 0x00;
  _iLogicInputArray = new ILogicInput* [maxInputs];
  setLogic(LOGIC_AND);
  setInvertedState(false);
}


/**
 * @brief Метод интерфейса ILogicInput
 *        Получить состояние активации.
 * @return Состояние активации
 */  
bool LogicInputArray :: getActivation() {
  
  // Инициализируем результирующее состояние
  bool result = (_logic == LOGIC_OR) ? (false) : (true);
  
  // Проходимся по всему массиву
  for (uint8_t i = 0; i < _currentQuantity; i++) {
    
    // В зависимости от логики работы формируем состояние
    if (_logic == LOGIC_OR) {
      result |= _iLogicInputArray[i]->getActivation();
    } else {
      result &= _iLogicInputArray[i]->getActivation();
    }
  }
  // Возвращаем результат в зависимости от инвертации
  return (_isInverted) ? (!result): (result);
}


/**
 * @brief Метод интерфейса ILogicInput
 *        Получить состояние длительной активации.
 * @return Состояние длительной активации
 */  
bool LogicInputArray :: getLongActivation() {
  
  // Инициализируем результирующее состояние
  bool result = (_logic == LOGIC_OR) ? (false) : (true);
  
  // Проходимся по всему массиву
  for (uint8_t i = 0; i < _currentQuantity; i++) {
    
    // В зависимости от логики работы формируем состояние
    if (_logic == LOGIC_OR) {
      result |= _iLogicInputArray[i]->getLongActivation();
    } else {
      result &= _iLogicInputArray[i]->getLongActivation();
    }
  }
  // Возвращаем результат в зависимости от инвертации
  return (_isInverted) ? (!result): (result);
}


/**
 * @brief Регистрация интерфейса в массиве
 * @param iLogicInput - интерфейс ILogicInput
 */
void LogicInputArray :: registerILogicInput(ILogicInput* iLogicInput) {
  
  if (iLogicInput == 0) {
    return;
  }
  
  for (uint16_t i = 0; i < _currentQuantity; i++) {
    // Проверка на дублирование
    if (_iLogicInputArray[i] == iLogicInput) {
    // Уже зарегестрировано
      return;
    }
  }
  
  if (_currentQuantity >= _maxQuantity) {
    // Размера текущего буфера недостаточно
    ILogicInput** newBuf;
    // Выделяем память для нового буфера
    newBuf = new ILogicInput* [_maxQuantity + 1];
    // Копируем в него данные старого буфера.
    memcpy(newBuf, _iLogicInputArray, _maxQuantity * sizeof(ILogicInput*));
    // Удаляем предыдущий массив
    delete [] _iLogicInputArray;
    // Замещаем массивы
    _iLogicInputArray = newBuf;
    // Увеличиваем максимальный размер массива
    _maxQuantity++;    
  }

  if (_iLogicInputArray != 0) {
    _iLogicInputArray[_currentQuantity] = iLogicInput;
    _currentQuantity++;
  }
}


/**
 * @brief Задать логику работы класса
 * @param logic - значение из перечисления Logic
 */
void LogicInputArray :: setLogic(Logic logic) {
  
  _logic = logic;
}

/**
 * @brief Задать состояние инвертированности
 * @param isInverted - состояние инвертированности
 */
void LogicInputArray :: setInvertedState(bool isInverted) {
  
  _isInverted = isInverted;
}
