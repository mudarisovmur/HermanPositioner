/**
  ******************************************************************************
  * @file    Protocol.hpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    11.07.2022
  * @brief   Protocol
  *          Класс управления протоколом передачи данных
  ******************************************************************************
  */

#ifndef PROTOCOL_HPP                            //< Avoid multiple inclusion
#define PROTOCOL_HPP

#include "usart.h"
#include "ILogicOutput.hpp"
#include "IObserver.hpp"
#include "IPosition.hpp"
#include "IProcess.hpp"
  
class Protocol : public IObserver, 
                 public IPosition,
                 public IProcess {
  
  public:
  
  /**
   * @brief Конструктор
   * @param iLogicOutputDE - выход управления DE
   * @param handle - указатель на хэндл уарта
   * @param iProcess - интерфейс IProcess
   */
  Protocol(ILogicOutput* iLogicOutput = nullptr,
           UART_HandleTypeDef* handle = nullptr,
           IProcess* iProcess = nullptr);
  
  /**
   * @brief Метод интерфейса IObserver
   *        Периодическая процедура
   */  
  virtual void observe() override;
  
  /**
   * @brief Метод интерфейса IPosition
   *        Получить код положения
   * @return код положения в HEX
   */  
  virtual uint16_t getPosition() override;
  
  /**
   * @brief Метод интерфейса IProcess
   *        Выполнить операцию - ответ на ответ датчика положения
   */  
  virtual void process() override;
  
  /**
   * @brief Методы класса
   */
   
  /**
   * @brief Передать команду по уарту
   * @param command - команда
   * @return результат передачи
   */
  bool transmit(uint8_t command);
  
  /**
   * @brief Активировать ожидание приёма данных
   */
  void activateResponseWaiting();
   
  /**
   * @brief Отправить ответ датчику
   */
  void sendResponse();
  
  /**
   * @brief Задать интерфейс управления выходом
   * @param iLogicOutput - интерфейс ILogicOutput
   * @param pin - пин gpio
   */
  void setILogicOutput(ILogicOutput* iLogicOutput);
  
  /**
   * @brief Задать интерфейс расчёта полной позиции
   * @param iProcess - интерфейс IProcess
   */
  void setIProcess(IProcess* iProcess);
  
  /**
   * @brief Задать интерфейс управления выходом
   * @param handle - указатель на хэндл уарта
   */
  void setUartHandle(UART_HandleTypeDef* handle);
  
  private:
  
  /// Интерфейс управления выходом
  ILogicOutput*                 _iLogicOutput;
  
  /// Интерфейс расчёта полной позиции
  IProcess*                     _iProcess;
  
  /// Указатель на хэндл уарта
  UART_HandleTypeDef*           _uart;
  
  /// Размер буфера для ответа от датчика положения
  static const uint8_t          BUFFER_SIZE = 0x03;
  
  /// Буфер хранения ответа от датчика положения
  uint8_t                       _sensorResponseBuffer[BUFFER_SIZE];
  
  /// Команды для передачи
  static const uint8_t          CMD_RESPONSE = 0xF2;
  static const uint8_t          CMD_DATA     = 0x22;
  static const uint8_t          CMD_STOP     = 0x10;
  
  /// Таймаут ожидания UART в блокирующем режиме
  static const uint8_t          TIMEOUT = 0x30;
  
  /// Счётчик ожидания для периодической отправки
  uint32_t                      _delayCounter;
  
  /// Количество тиков ожидания для периодической отправки
  uint32_t                      _delayTicks;
  
  /// Флаг необходимости отправить ответ
  bool                          _isAnswerSending;
};

#endif //PROTOCOL_HPP

/**
  ******************************************************************************
  *  Вер. |   гггг-ммм-дд   | Внес изменения | Описание изменений
  *  =====|=================|================|==================================
  *   1.0 |   11.07.2022    | Мударисов Т.Р. | Первый релиз
  *  -----|-----------------|----------------|----------------------------------
  ******************************************************************************
  */
