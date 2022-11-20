/**
  ******************************************************************************
  * @file    PositionControl.hpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    23.07.2022
  * @brief   PositionControl
  *          Класс обработки данных позиции
  ******************************************************************************
  */

#ifndef POSITION_CONTROL_HPP                        //< Avoid multiple inclusion
#define POSITION_CONTROL_HPP

#include "IPositionComplete.hpp"
#include "ILogicOutput.hpp"
#include "ICalibration.hpp"
#include "IProcess.hpp"
#include "IPercent.hpp"
#include "ILed.hpp"
  
class PositionControl : public IPositionComplete,
                        public ILogicOutput,
                        public IProcess,
                        public IPercent {
  
  public:
  
  /**
   * @brief Конструктор
   * @param iPosition - интерфейс IPosition
   * @param iCalibration - интерфейс ICalibration
   * @param iLed - интерфейс ILed
   */
  PositionControl(IPosition* iPosition = nullptr,
                  ICalibration* iCalibration = nullptr,
                  ILed* iLed = nullptr);
  
  /**
   * @brief Метод интерфейса IPositionComplete
   *        Получить код положения.
   * @return код положения в HEX
   */  
  virtual uint16_t getPosition() override;
  
  /**
   * @brief Метод интерфейса IPositionComplete
   *        Получить диапазон положения.
   * @return код положения в HEX
   */  
  virtual uint16_t getRange() override;
  
  /**
   * @brief Метод интерфейса IProcess
   *        Выполнить операцию - обработать значение.
   */  
  virtual void process() override;
  
  /**
   * @brief Метод интерфейса IPercent
   *        Получить значение в процентах
   * @return значение в процентах
   */  
  virtual float getPercent() override;
  
  /**
   * @brief Метод интерфейса ILogicOutput
   *        Активировать логической выход.
   */  
  virtual void activate() override;
  
  /**
   * @brief Метод интерфейса ILogicOutput
   *        Деактивировать логической выход.
   */  
  virtual void deactivate() override;
  
  
  /**
   * @brief Методы класса
   */
  
  /**
   * @brief Задать интерфейс получения необработанной позиции
   * @param iPosition - интерфейс IPosition
   */
  void setIPosition(IPosition* iPosition);
  
  /**
   * @brief Задать интерфейс получения калибровки
   * @param iCalibration - интерфейс ICalibration
   */
  void setICalibration(ICalibration* iCalibration);
  
  /**
   * @brief Задать интерфейс управления светодиодом "Нулевая точка" 
   * @param iLed - интерфейс ILed
   */
  void setILed(ILed* iLed);
  
  private:
  
  /// Интерфейс управления выходом
  IPosition*                    _iPosition;
  
  /// Интерфейс получения калибровки
  ICalibration*                 _iCalibration;
  
  /// Интерфейс управления светодиодом "Нулевая точка" 
  ILed*                         _iLedNul;
  
  /// Порог перехода
  static const uint16_t         REFRESH_THRESHOLD = 0x1800;
  
  /// Гистерезис установки блинка после
  static const uint16_t         HYSTERESIS_THRESHOLD = 0x20;
  
  /// Размер диапазона
  static const uint16_t         RANGE_SIZE = 0x2000;
  
  /// Полная текущая позиция
  ICalibration::Calibration     _currentPosition;
  
  /// Текущая позиция
  uint16_t                      _position;
  
  /// Текущий диапазон
  uint16_t                      _range;
  
  /// Флаг инициализации
  bool                          _isInited;
  
  /// Отметка положения блинка гистерезиса
  uint32_t                      _hysteresisBlinkValue;
  
  /// Направление счёта блинка гистерезиса
  bool                          _hysteresisBlinkDirection;
  
  /// Текущий процент шкалы диапазона
  float                         _currentPercent;
  
  /**
   * @brief Приватные методы класса
   */
   
  /**
   * @brief Активировать блинк через гистерезис
   * @param direction - направление
   * @param value - значение
   */
  void activateHysteresisBlink(bool direction, uint32_t value);
  
  /**
   * @brief Проверить блинк
   */
  void checkHysteresisBlink();
   
};

#endif //PROTOCOL_HPP

/**
  ******************************************************************************
  *  Вер. |   гггг-ммм-дд   | Внес изменения | Описание изменений
  *  =====|=================|================|==================================
  *   1.0 |   23.07.2022    | Мударисов Т.Р. | Первый релиз
  *  -----|-----------------|----------------|----------------------------------
  ******************************************************************************
  */
