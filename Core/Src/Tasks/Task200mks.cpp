//********************************80 symbols************************************
#include "ObjectsDefinitions.hpp"
#include <stdint.h>
#include <stdio.h>
#include "cmsis_os.h"
#include <tim.h>

//#include "stm32g4xx_hal_flash_ex.h"

// Externals Variables
extern IWDG_HandleTypeDef hiwdg;
// Externals Function prototypes

// Global Variables

// Device global

extern "C" void period200mksTsk(void) {

//В режиме отладки при остановке 
DBGMCU->CR |= 1<<5; //TRACE_MODE = 1; 
__HAL_DBGMCU_FREEZE_IWDG();

	//Создание объекта DeviceGlobal, и его инициализация.
  deviceGlobal = new DeviceGlobal();

  // Инициализация ПО (создание объектов)
  deviceGlobal->initializeSoftware();
  
  // Инициализация аппаратная (таймеры, компаратор...)
  deviceGlobal->initializeHardware();
  
  // Устройство полностью готово к работе
  deviceGlobal->setReady();
  
  /*
  #define DO_LED_CLOSE_Pin GPIO_PIN_13
#define DO_LED_CLOSE_GPIO_Port GPIOB
#define DO_LED3_Pin GPIO_PIN_14
#define DO_LED3_GPIO_Port GPIOB
#define DO_LED2_Pin GPIO_PIN_15
#define DO_LED2_GPIO_Port GPIOB
#define DO_LED1_Pin GPIO_PIN_8
#define DO_LED1_GPIO_Port GPIOA
#define DO_LED_OPEN_Pin GPIO_PIN_9
#define DO_LED_OPEN_GPIO_Port GPIOA
  */
  
  uint16_t delay = 30;
  
  for (uint8_t i = 0; i < 8; i++) {
    
    HAL_GPIO_WritePin(GPIOA, DO_LED_OPEN_Pin, GPIO_PIN_RESET );
    osDelay(delay);
    HAL_GPIO_WritePin(GPIOA, DO_LED_OPEN_Pin, GPIO_PIN_SET);
    
    HAL_GPIO_WritePin(GPIOA, DO_LED1_Pin, GPIO_PIN_RESET );
    osDelay(delay);
    HAL_GPIO_WritePin(GPIOA, DO_LED1_Pin, GPIO_PIN_SET);
    
    HAL_GPIO_WritePin(GPIOB, DO_LED2_Pin, GPIO_PIN_RESET);
    osDelay(delay);
    HAL_GPIO_WritePin(GPIOB, DO_LED2_Pin, GPIO_PIN_SET);
    
    HAL_GPIO_WritePin(GPIOB, DO_LED3_Pin, GPIO_PIN_RESET);
    osDelay(delay);
    HAL_GPIO_WritePin(GPIOB, DO_LED3_Pin, GPIO_PIN_SET);
    
    HAL_GPIO_WritePin(GPIOB, DO_LED_CLOSE_Pin, GPIO_PIN_RESET);
    osDelay(delay);
    HAL_GPIO_WritePin(GPIOB, DO_LED_CLOSE_Pin, GPIO_PIN_SET);
  }
  
  
  while(true) {
    
    // Ожидание установки семафора.
    deviceGlobal->activate200mksTskSem->wait();
    
    // Периодическое выполнение команд
    deviceGlobal->observerAggregator->observe();
    
    // Сбрасываем таймер
    __HAL_IWDG_RELOAD_COUNTER(&hiwdg);
  }
}
