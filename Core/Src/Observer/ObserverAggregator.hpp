/**
  ******************************************************************************
  * @file    ObserverAggregator.hpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    10.07.2022
  * @brief   ObserverAggregator
  *          Класс для хранения и периодического оповещения по интерфейсу
  ******************************************************************************
  */

#ifndef OBSERVER_AGGREGATOR_HPP                     //< Avoid multiple inclusion
#define OBSERVER_AGGREGATOR_HPP

#include "stdint.h"
#include "string.h"
#include "cmsis_os.h"
#include "IObserver.hpp"
  
class ObserverAggregator : public IObserver {
  
  public:
  
  /**
   * @brief Конструктор
   * @brief maxObserver - максимальное количество наблюдателей
   */
  ObserverAggregator(uint8_t maxObserver = 0x10);
  
  /**
   * @brief Метод интерфейса IObserver
   *        Периодическая процедура.
   */  
  virtual void observe() override;
  
  /**
   * @brief Регистрация интерфейса в массиве
   * @param iObserver - интерфейс IObserver
   */
  void registerIObserver(IObserver* iObserver);  
  
  private:
  
  /// Массив указателей на интерфейсы IObserver
  IObserver**                   _iObserverArray;
  
  /// Максимальное количество интерфейсов
  uint8_t                       _maxQuantity; 
  
  /// Текущее количество интерфейсов
  uint8_t                       _currentQuantity; 
};

#endif //SEMAPHORE_WRAPPER_HPP

/**
  ******************************************************************************
  *  Вер. |   гггг-ммм-дд   | Внес изменения | Описание изменений
  *  =====|=================|================|==================================
  *   1.0 |   10.07.2022    | Мударисов Т.Р. | Первый релиз
  *  -----|-----------------|----------------|----------------------------------
  ******************************************************************************
  */
