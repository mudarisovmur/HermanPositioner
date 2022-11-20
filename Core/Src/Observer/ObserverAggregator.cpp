/**
  ******************************************************************************
  * @file    ObserverAggregator.cpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    10.07.2022
  * @brief   ObserverAggregator
  *          Класс для хранения и периодического оповещения по интерфейсу
  ******************************************************************************
  */
#include "ObserverAggregator.hpp"

/**
 * @brief Конструктор
 * @brief maxObserver - максимальное количество наблюдателей
 */
ObserverAggregator :: ObserverAggregator(uint8_t maxObserver) {
  
  _maxQuantity = maxObserver;
  _currentQuantity = 0x00;
  _iObserverArray = new IObserver* [maxObserver];
}

/**
 * @brief Метод интерфейса IObserver
 *        Периодическая процедура.
 */  
void ObserverAggregator :: observe() {
  
  // Проходимся по всему массиву
  for (uint8_t i = 0; i < _currentQuantity; i++) {
    
    // Вызываем периодическое выполнение
    _iObserverArray[i]->observe();
  }
}

/**
 * @brief Регистрация интерфейса в массиве
 * @param iObserver - интерфейс IObserver
 */
void ObserverAggregator :: registerIObserver(IObserver* iObserver) {
  
  if (iObserver == 0) {
    return;
  }
  
  for (uint16_t i = 0; i < _currentQuantity; i++) {
    // Проверка на дублирование
    if (_iObserverArray[i] == iObserver) {
    // Уже зарегестрировано
      return;
    }
  }
  
  if (_currentQuantity >= _maxQuantity) {
    // Размера текущего буфера недостаточно
    IObserver** newBuf;
    // Выделяем память для нового буфера
    newBuf = new IObserver* [_maxQuantity + 1];
    // Копируем в него данные старого буфера.
    memcpy(newBuf, _iObserverArray, _maxQuantity * sizeof(IObserver*));
    // Удаляем предыдущий массив
    delete [] _iObserverArray;
    // Замещаем массивы
    _iObserverArray = newBuf;
    // Увеличиваем максимальный размер массива
    _maxQuantity++;    
  }

  if (_iObserverArray != 0) {
    _iObserverArray[_currentQuantity] = iObserver;
    _currentQuantity++;
  }
}
