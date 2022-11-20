/**
  ******************************************************************************
  * @file    Kernel.hpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    24.07.2022
  * @brief   Kernel
  *          Класс управления ядром устройства
  ******************************************************************************
  */
  
#ifndef KERNEL_HPP                                  //< Avoid multiple inclusion
#define KERNEL_HPP

#include "ILogicOutput.hpp"
#include "ILogicInput.hpp"
#include "IObserver.hpp"
#include "IPercent.hpp"
#include "ILed.hpp"
#include "EnumLed.hpp"
  
class Kernel : public IObserver {
  
  public:
  
  /**
   * @brief Конструктор
   * @param iPercent - интерфейс IPercent
   * @param iLed - интерфейс ILed
   * @param iLogicInput - интерфейс ILogicInput
   * @param iLogicOutputReleOpen - интерфейс ILogicOutput
   * @param iLogicOutputReleClose - интерфейс ILogicOutput
   */
  Kernel(IPercent* iPercent = nullptr,
         ILed* iLed = nullptr,
         ILogicInput* iLogicInput = nullptr,
         ILogicOutput* iLogicOutputReleOpen = nullptr,
         ILogicOutput* iLogicOutputReleClose = nullptr);
  
  /**
   * @brief Метод интерфейса IObserver
   *        Периодическая процедура
   */  
  virtual void observe() override;
  
  /**
   * @brief Методы класса
   */
  
  /**
   * @brief Задать интерфейс получения процента положения
   * @param iPercent - интерфейс IPercent
   */
  void setIPercent(IPercent* iPercent);
  
  /**
   * @brief Задать интерфейс управления светодиодом
   * @param ledId - идентификатор светодиода
   * @param iLed - интерфейс ILed
   */
  void setILed(LedId ledId, ILed* iLed);
  
  /**
   * @brief Задать интерфейс состояния допустимости отработки анимации
   * @param iLogicInput - интерфейс ILogicInput
   */
  void setILogicInput(ILogicInput* iLogicInput);
  
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
  
  private:
  
  /// Интерфейс получения процента положения
  IPercent*                     _iPercent;
  
  /// Интерфейсы управления светодиодами
  ILed*                         _iLed[LED_LIMIT];
  
  /// Интерфейс состояния допустимости отработки анимации
  ILogicInput*                  _iLogicInput;
  
  /// Интерфейс управления выходом реле "Открыто"
  ILogicOutput*                 _iLogicOutputReleOpen;
  
  /// Интерфейс управления выходом реле "Закрыто"
  ILogicOutput*                 _iLogicOutputReleClose;
  
  /// Состояние активации
  bool                          _isActive;
  
  bool                          _isBlockedOpen;
  bool                          _isBlockedClose;
  
  uint32_t                      observeDelay;
  
  /**
   * @brief Приватные методы класса
   */
  
  /**
   * @brief Задать cостояния светодиодов
   * @param iLed1 - интерфейс ILed 1го интервала
   * @param iLed2 - интерфейс ILed 2го интервала
   * @param iLed3 - интерфейс ILed 3го интервала
   * @param iLed4 - интерфейс ILed 4го интервала
   * @param iLed5 - интерфейс ILed 5го интервала
   */
  void setLedStates(bool Led1, bool Led2, bool Led3, bool Led4, bool Led5);
  
  /**
   * @brief Задать cостояния реле
   * @param LedOpen - интерфейс ILed "открыто"
   * @param LedClose - интерфейс ILed "закрыто"
   */
  void setReleStates(bool releOpen, bool releClose);
  
};

#endif //PROTOCOL_HPP

/**
  ******************************************************************************
  *  Вер. |   гггг-ммм-дд   | Внес изменения | Описание изменений
  *  =====|=================|================|==================================
  *   1.0 |   24.07.2022    | Мударисов Т.Р. | Первый релиз
  *  -----|-----------------|----------------|----------------------------------
  ******************************************************************************
  */
