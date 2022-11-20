/**
  ******************************************************************************
  * @file    DeviceGlobaLogicOutputs.hpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    10.07.2022
  * @brief   DeviceGlobaLogicOutputs
  *          Часть объекта для глобального взаимодействия с устройством
  ******************************************************************************
  */
  
#include "DeviceGlobal.hpp"

  public :
  
  /**
   * @brief Инициализация логических входов/выходов
   */
  void initLogicOutputs();
  
  private :
  
  /// Объект для управление выходом LED1
  Led                           _ledPercent[3];
  
  /// Объект для управление светодиодом "Открыто"
  Led                           _ledOpen;
  
  /// Объект для управление светодиодом "Закрыто"
  Led                           _ledClose;
  
  /// Объект для управление светодиодом "Нулевая точка"
  Led                           _ledNul;
  
  /// Объект для управление выходом Реле "Открыто"
  LogicOutput                   _logicOutputReleOpen;
  
  /// Объект для управление выходом Реле закрыто
  LogicOutput                   _logicOutputReleClose;
  
  /// Объект для получения состояния кнопки "Открыто"
  LogicInput                    _logicInputOpenBtn;
  
  /// Объект для получения состояния кнопки "Закрыто"
  LogicInput                    _logicInputCloseBtn;
  
  /// Объект для получения состояния кнопки "Ручное управление"
  LogicInput                    _logicInputManualBtn;
  
  /// Объект для управления выходом "Открыто" в зависимости от состояния
  LogicControl                  _logicControlOpen;
  
  /// Объект для управления выходом "Закрыто" в зависимости от состояния
  LogicControl                  _logicControlClose;
  
  /// Суммарное состояние для концевика "Открыто"
  LogicInputArray               _logicInputArrayOpen;
  
  /// Суммарное состояние для концевика "Закрыто"
  LogicInputArray               _logicInputArrayClose;
  
  /// Адаптер состояния ядра - выход реле "Открыто"
  AdapterILogicOutputILogicInput  _adapterILogicOutputILogicInputKernelOpen;
  
  /// Адаптер состояния ядра - выход реле "Закрыто"
  AdapterILogicOutputILogicInput  _adapterILogicOutputILogicInputKernelClose;
  
  /// Адаптер состояния калибровки - выход реле "Открыто"
  AdapterILogicOutputILogicInput  _adapterILogicOutputILogicInputCalibrationOpen;
  
  /// Адаптер состояния калибровки - выход реле "Закрыто"
  AdapterILogicOutputILogicInput  _adapterILogicOutputILogicInputCalibrationClose;
  
  
/**
  ******************************************************************************
  *  Вер. |   гггг-ммм-дд   | Внес изменения | Описание изменений
  *  =====|=================|================|==================================
  *   1.0 |   10.07.2022    | Мударисов Т.Р. | Первый релиз
  *  -----|-----------------|----------------|----------------------------------
  ******************************************************************************
  */

