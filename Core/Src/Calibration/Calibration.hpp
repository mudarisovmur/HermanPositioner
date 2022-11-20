/**
  ******************************************************************************
  * @file    Calibration.hpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    16.07.2022
  * @brief   Calibration
  *          Класс реализации калибровки устройства
  ******************************************************************************
  */
  
#ifndef CALIBRATION_HPP                             //< Avoid multiple inclusion
#define CALIBRATION_HPP

#include "ILed.hpp"
#include "IStorage.hpp"
#include "IObserver.hpp"
#include "ILogicInput.hpp"
#include "ICalibration.hpp"
#include "IPositionComplete.hpp"
#include "EnumLed.hpp"

class Calibration : public IObserver, 
                    public ICalibration,
                    public ILogicInput {
  
  public:
  
  /**
   * @brief Конструктор
   * @param iLogicInputOpen - интерфейс ILogicInput
   * @param iLogicInputClose - интерфейс ILogicInput
   * @param iPositionComplete - интерфейс IPositionComplete
   * @param iStorage - интерфейс IStorage
   * @param iLogicOutputReleOpen - интерфейс ILogicOutput
   * @param iLogicOutputReleClose - интерфейс ILogicOutput
   */
  Calibration(ILogicInput* iLogicInputOpen = nullptr,
              ILogicInput* iLogicInputClose = nullptr,
              IPositionComplete* iPositionComplete = nullptr,
              IStorage* iStorage = nullptr,
              ILogicOutput* iLogicOutputReleOpen = nullptr,
              ILogicOutput* iLogicOutputReleClose = nullptr);
  
  /**
   * @brief Метод интерфейса IObserver
   *        Периодическая процедура: процедура калибровки.
   */  
  virtual void observe() override;
  
  /**
   * @brief Метод интерфейса ICalibration
   *        Получить имеющуюся структуру калибровки.
   * @return структура Calibration
   */  
  virtual ICalibration::Calibration getCalibrationStruct() override;
  
  /**
   * @brief Метод интерфейса ILogicInput
   *        Получить состояние активации.
   * @return Состояние активации
   */  
  virtual bool getActivation() override;
  
  /**
   * @brief Метод интерфейса ILogicInput
   *        Получить состояние длительной активации.
   * @return Состояние длительной активации
   */  
  virtual bool getLongActivation() override;
  
  /**
   * @brief Методы класса
   */
  
  /**
   * @brief Инициализация - чтение регистров из Flash памяти
   */ 
  void init();
  
  /// Описание состояний класса
  enum CalibrationState {
    CALIBRATION_INACTIVE = 0x00,
    CALIBRATION_ACTIVE
  };
  
  /// Описание состояний класса
  enum CalibrationActivity {
    ACTIVITY_START_INACTIVATION_AWAITING = 0x00,
    ACTIVITY_CALIBRATION_ROUTINE,
    ACTIVITY_FINISH_INACTIVATION_AWAITING
  };
  
  /**
   * @brief Задать интерфейс состояния входа OPEN
   * @param iLogicInput - интерфейс ILogicInput
   */
  void setILogicInputOpen(ILogicInput* iLogicInput);
  
  /**
   * @brief Задать интерфейс состояния входа CLOSE
   * @param iLogicInput - интерфейс ILogicInput
   */
  void setILogicInputClose(ILogicInput* iLogicInput);
  
  /**
   * @brief Задать интерфейс управления выходом реле "Открыто"
   * @param iLogicOutput - интерфейс ILogicOutput
   */
  void setILogicOutputOpen(ILogicOutput* iLogicOutput);
  
  /**
   * @brief Задать интерфейс управления выходом реле "Закрыто"
   * @param iLogicOutput - интерфейс ILogicOutput
   */
  void setILogicOutputClose(ILogicOutput* iLogicOutput);
  
  /**
   * @brief Задать интерфейс получения текущей позиции и диапазона
   * @param iPositionComplete - интерфейс IPositionComplete
   */
  void setIPositionComplete(IPositionComplete* iPositionComplete);
  
  /**
   * @brief Задать интерфейс сохранения параметров
   * @param iStorage - интерфейс IStorage
   */
  void setIStorage(IStorage* iStorage);
  
  /**
   * @brief Задать интерфейс управления светодиодом
   * @param ledId - идентификатор светодиода
   * @param iLed - интерфейс ILed
   */
  void setILed(LedId ledId, ILed* iLed);
  
  ILogicOutput*                 _positionActivation;
  
  private:
  
  /// Интерфейс состоянии входа OPEN
  ILogicInput*                  _iLogicInputOpen;
  
  /// Интерфейс состоянии входа CLOSE
  ILogicInput*                  _iLogicInputClose;
  
  /// Интерфейсы управления светодиодами
  ILed*                         _iLed[LED_LIMIT];
  
  /// Интерфейс управления выходом реле "Открыто"
  ILogicOutput*                 _iLogicOutputReleOpen;
  
  /// Интерфейс управления выходом реле "Закрыто"
  ILogicOutput*                 _iLogicOutputReleClose;
  
  /// Интерфейс получения текущей позиции и диапазона
  IPositionComplete*            _iPositionComplete;
  
  /// Интерфейс сохранения параметров
  IStorage*                     _iStorage;
  
  /// Текущее состояние класса
  CalibrationState              _calibrationState;
  
  /// Текущее состояние активности внутри калибровки
  CalibrationActivity           _calibrationActivity;
  
  /// Структура калибровки
  ICalibration::Calibration     _calibration;
  
  /// Локальная структура калибровки
  ICalibration::Calibration     _calibrationLocal;
  
  /// Размер диапазона
  static const uint16_t         RANGE_SIZE = 0x2000;
  
  bool _isCalibratedOpen;
  bool _isCalibratedClose;
  
  /**
   * @brief Приватные методы класса
   */
    
  /**
   * @brief Получить состояние допустимости продолжения калибровки
   */
  bool getAllowability();
  
  /**
   * @brief Установить состояния светодиодов
   * @param stateOpen - состояние Светодиодов
   */
  void setLedState(ILed* iLed, ILed::State state);
  
  /**
   * @brief Установить состояния Реле
   * @param state - состояние реле
   */
  void setReleStates(bool state);
};

#endif // CALIBRATION_HPP

/**
  ******************************************************************************
  *  Вер. |   гггг-ммм-дд   | Внес изменения | Описание изменений
  *  =====|=================|================|==================================
  *   1.0 |   11.07.2022    | Мударисов Т.Р. | Первый релиз
  *  -----|-----------------|----------------|----------------------------------
  ******************************************************************************
  */
