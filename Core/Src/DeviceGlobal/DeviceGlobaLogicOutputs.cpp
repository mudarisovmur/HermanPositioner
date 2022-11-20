/**
  ******************************************************************************
  * @file    DeviceGlobaLogicOutputs.cpp
  * @author  Мударисов Т.Р.
  * @version V1.0
  * @date    10.07.2022
  * @brief   DeviceGlobaLogicOutputs
  *          Часть объекта для глобального взаимодействия с устройством
  ******************************************************************************
  */
  
#include "DeviceGlobal.hpp"

/**
 * @brief Инициализация логических входов/выходов
 */
void DeviceGlobal :: initLogicOutputs() {
  
  // Устанавливаем ответственный за оповещение объект
  Led::setILed(&_ledOpen);
  
  // Объект для управление светодиодом "Открыто"
  _ledOpen.registerOutput(DO_LED_OPEN_GPIO_Port, DO_LED_OPEN_Pin);
  _ledOpen.setBlinkDelay(50);
  _ledOpen.setInverted(true);
  observerAggregator->registerIObserver(&_ledOpen);
  
  // Объект для управление светодиодом "Закрыто"
  _ledClose.registerOutput(DO_LED_CLOSE_GPIO_Port, DO_LED_CLOSE_Pin);
  _ledClose.setBlinkDelay(50);
  _ledClose.setInverted(true);
  observerAggregator->registerIObserver(&_ledClose);
  
  // Объект для управление светодиодом "Нулевая точка"
  _ledNul.registerOutput(GPIOA, GPIO_PIN_10);
  _ledNul.setBlinkDelay(50);
  _ledNul.setInverted(true);
  observerAggregator->registerIObserver(&_ledNul);
  
  // Объект для управление выходом LED1
  _logicOutputReleOpen.registerOutput(DO_RELE_OPEN_GPIO_Port, DO_RELE_OPEN_Pin);
  
  // Объект для управление выходом LED1
  _logicOutputReleClose.registerOutput(DO_RELE_CLOSE_GPIO_Port, DO_RELE_CLOSE_Pin);
  
  // Объект для получения состояния кнопки "Открыто"
  _logicInputOpenBtn.registerInput(DI_OPEN_GPIO_Port, DI_OPEN_Pin);
  observerAggregator->registerIObserver(&_logicInputOpenBtn);
  
  // Объект для получения состояния кнопки "Закрыто"
  _logicInputCloseBtn.registerInput(DI_CLOSE_GPIO_Port, DI_CLOSE_Pin);
  observerAggregator->registerIObserver(&_logicInputCloseBtn);
  
  // Объект для управление светодиодом 1го интервала
  _ledPercent[0].registerOutput(DO_LED1_GPIO_Port, DO_LED1_Pin);
  _ledPercent[0].setBlinkDelay(50);
  _ledPercent[0].setInverted(true);
  observerAggregator->registerIObserver(&_ledPercent[0]);
  
  // Объект для управление светодиодом 1го интервала
  _ledPercent[1].registerOutput(DO_LED2_GPIO_Port, DO_LED2_Pin);
  _ledPercent[1].setBlinkDelay(50);
  _ledPercent[1].setInverted(true);
  observerAggregator->registerIObserver(&_ledPercent[1]);
  
  // Объект для управление светодиодом 1го интервала
  _ledPercent[2].registerOutput(DO_LED3_GPIO_Port, DO_LED3_Pin);
  _ledPercent[2].setBlinkDelay(50);
  _ledPercent[2].setInverted(true);
  observerAggregator->registerIObserver(&_ledPercent[2]);
  
  // Объект для получения состояния кнопки "Ручное управление"
  _logicInputManualBtn.registerInput(DI_MANUAL_GPIO_Port, DI_MANUAL_Pin);
  observerAggregator->registerIObserver(&_logicInputManualBtn);
  
  
  // Инициализируем массив входных состояний для выхода реле "Открыто"
  _logicInputArrayOpen.registerILogicInput(&_adapterILogicOutputILogicInputCalibrationOpen);
  _logicInputArrayOpen.registerILogicInput(&_adapterILogicOutputILogicInputKernelOpen);
  _logicInputArrayOpen.registerILogicInput(&_logicInputManualBtn);
  _logicInputArrayOpen.setLogic(LogicInputArray::LOGIC_OR);
  _logicInputArrayOpen.setInvertedState(true);
  
  // Инициализируем массив входных состояний для выхода реле "Закрыто"
  _logicInputArrayClose.registerILogicInput(&_adapterILogicOutputILogicInputCalibrationClose);
  _logicInputArrayClose.registerILogicInput(&_adapterILogicOutputILogicInputKernelClose);
  _logicInputArrayClose.registerILogicInput(&_logicInputManualBtn);
  _logicInputArrayClose.setLogic(LogicInputArray::LOGIC_OR);
  _logicInputArrayClose.setInvertedState(true);
  
  
  // Инициализируем объект для управления выходом "Открыто" в зависимости от состояния
  _logicControlOpen.setILogicInput(&_logicInputArrayOpen);
  _logicControlOpen.setILogicOutput(&_logicOutputReleOpen);
  observerAggregator->registerIObserver(&_logicControlOpen);
  
  // Инициализируем объект для управления выходом "Закрыто" в зависимости от состояния
  _logicControlClose.setILogicInput(&_logicInputArrayClose);
  _logicControlClose.setILogicOutput(&_logicOutputReleClose);
  observerAggregator->registerIObserver(&_logicControlClose);
}
