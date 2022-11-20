//********************************80 symbols************************************
#include "ObjectsDefinitions.hpp"
#include <tim.h>

static void period200mksElapsedCallback();
static void flashEraseFinished();

extern "C" void HAL_TIMx_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  
  if(deviceGlobal == nullptr) {
    // Выход если не создан deviceGlobal
    return;
  }
  
  if (htim == deviceGlobal->getTimer200mksHandle()) {
    if (deviceGlobal->getReady() == true) {
      period200mksElapsedCallback();
    }    
  }  
}

extern "C" void HAL_FLASH_EndOfOperationCallback(uint32_t ReturnValue) {
  
  if(deviceGlobal == nullptr) {
    // Выход если не создан deviceGlobal
    return;
  }
  flashEraseFinished();
}

/**
 * @brief Callback TIMx - период 200 мкс
 */
static void period200mksElapsedCallback() {
  
  // Инкремент семафора
  deviceGlobal->activate200mksTskSem->release();
}

void flashEraseFinished() {
  
  deviceGlobal->flashEraseSem->release();
}
