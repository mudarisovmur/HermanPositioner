/**
  ******************************************************************************
  * @file    Protocol.cpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    11.07.2022
  * @brief   Protocol
  *          Класс управления протоколом передачи данных
  ******************************************************************************
  */

#include "Protocol.hpp"

/**
 * @brief Конструктор
 * @param iLogicOutputDE - выход управления DE
 * @param handle - указатель на хэндл уарта
 * @param iProcess - интерфейс IProcess
 */
Protocol :: Protocol(ILogicOutput* iLogicOutput, 
                     UART_HandleTypeDef* handle,
                     IProcess* iProcess) {
  setILogicOutput(iLogicOutput);
  setIProcess(iProcess);
  setUartHandle(handle);
  _delayCounter = 0u;
  _delayTicks = 1;
  _isAnswerSending = false;
}

/**
 * @brief Метод интерфейса IObserver
 *        Периодическая процедура
 */  
void Protocol :: observe() {
  
  // Если время пришло
  if (_delayCounter++ >= _delayTicks) {
    
    // Зажимаем линию DE
    _iLogicOutput->activate();
    
    // Передаём команду запроса данных
    transmit(CMD_DATA);
    
    // Передаём стоп
    transmit(CMD_STOP);
    
    // Отпускаем линию DE
    _iLogicOutput->deactivate();
    
    // Активируем получение данных из прерывания
    activateResponseWaiting();
    
    // Обнуляем счётчик отправки
    _delayCounter = 0u;
  }
  
  // Если выставлен флаг, отправляем ответ
  if (_isAnswerSending == true) {
    
    // Отправляем ответ
    sendResponse();
    
    // Снимаем флаг
    _isAnswerSending = false;
  }
}

/**
 * @brief Метод интерфейса IPosition
 *        Получить код положения
 * @return код положения в HEX
 */  
uint16_t Protocol :: getPosition() {
  
  // Формируем позицию
  uint16_t position = _sensorResponseBuffer[1] << 8;
  position |= _sensorResponseBuffer[2];
  
  // Возвращаем результат
  return position;
}

/**
 * @brief Метод интерфейса IProcess
 *        Выполнить операцию - ответ на ответ датчика положения
 */  
void Protocol :: process() {
  
  _isAnswerSending = true;
}

/**
 * @brief Методы класса
 */

/**
 * @brief Передать команду по уарту
 * @param command - команда
 * @return результат передачи
 */
bool Protocol :: transmit(uint8_t command) {
  
  HAL_StatusTypeDef status = HAL_UART_Transmit(_uart, &command, 1, 9);
  
  bool result = static_cast<bool>(status == HAL_OK);
  
  return result;
}

/**
 * @brief Активировать ожидание приёма данных
 */
void Protocol :: activateResponseWaiting() {
  
  HAL_UART_Receive_IT(_uart, _sensorResponseBuffer, BUFFER_SIZE);
}

/**
 * @brief Отправить ответ датчику
 */
void Protocol :: sendResponse() {
  
  // Зажимаем линию DE
  _iLogicOutput->activate();
  
  // Передаём команду запроса данных
  transmit(CMD_RESPONSE);
  
  // Передаём стоп
  transmit(CMD_STOP);
  
  // Отпускаем линию DE
  _iLogicOutput->deactivate();
  
  // Отправляем команду расчёта новых значений
  _iProcess->process();
}

/**
 * @brief Задать интерфейс управления выходом
 * @param iLogicOutput - интерфейс ILogicOutput
 * @param pin - пин gpio
 */
void Protocol :: setILogicOutput(ILogicOutput* iLogicOutput) {
  
  _iLogicOutput = iLogicOutput;
}

/**
 * @brief Задать интерфейс расчёта полной позиции
 * @param iProcess - интерфейс IProcess
 */
void Protocol :: setIProcess(IProcess* iProcess) {
  
  _iProcess = iProcess;
}

/**
 * @brief Задать интерфейс управления выходом
 * @param handle - указатель на хэндл уарта
 */
void Protocol :: setUartHandle(UART_HandleTypeDef* handle) {
  
  _uart = handle;
}
