/**
  ******************************************************************************
  * @file    SemaphoreWrapper.cpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    10.07.2022
  * @brief   SemaphoreWrapper
  *          Класс-обертка для семафора
  ******************************************************************************
  */

#include "SemaphoreWrapper.hpp"

/**
 * @brief Конструктор
 * @brief timeWait - время ожидания семафора
 */
SemaphoreWrapper :: SemaphoreWrapper(uint32_t timeWait) {
  
  osSemaphoreDef(semaphoreName);
  
  _semaphore = osSemaphoreCreate(osSemaphore(semaphoreName), 5u);
}

/**
 * @brief Ожидание установки семафора
 * @return результат установки по окончанию ожидания
 */
bool SemaphoreWrapper :: wait() {
  
  bool isSuccess = osSemaphoreWait(_semaphore, osWaitForever) == osOK;
  
  return isSuccess;
}

/**
 * @brief Освобождение семафора
 * @return результат освобождения семафора
 */
bool SemaphoreWrapper :: release() {
  
  bool isSuccess = osSemaphoreRelease (_semaphore) == osOK;
    
  return isSuccess;
}

/**
 * @brief Установка времени ожидания семафора
 * @param msec - время в мс
 */
void SemaphoreWrapper :: setTimeWait(uint32_t msec) {
  
  _timeWait = msec;
}
