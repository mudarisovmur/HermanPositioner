//********************************80 symbols************************************
#include "ObjectsDefinitions.hpp"

extern "C" void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
  
  if(deviceGlobal == 0) {
    return;
  }
  // Response to DP in interruption
  deviceGlobal->responseDP();
}
