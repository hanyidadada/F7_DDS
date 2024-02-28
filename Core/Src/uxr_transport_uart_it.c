#include <uxr/client/transport.h>
#include <uxr/client/util/time.h>
#include "main.h"
#include "uxr_transport.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#ifdef RMW_UXRCE_TRANSPORT_CUSTOM_SERIAL_IT

// --- micro-ROS Transports ---
#define UART_IT_BUFFER_SIZE 2048

uint8_t RxBuffer[UART_IT_BUFFER_SIZE];
uint8_t RxByte;
size_t RxCount = 0;
int RxFlag = 0;

extern UART_HandleTypeDef huart1;
bool my_custom_transport_open(struct uxrCustomTransport * transport){
    UART_HandleTypeDef * uart = (UART_HandleTypeDef*) transport->args;
    // HAL_UART_Receive_IT(uart, &RxByte, 1);
    return true;
}

bool my_custom_transport_close(struct uxrCustomTransport * transport){
    UART_HandleTypeDef * uart = (UART_HandleTypeDef*) transport->args;
    HAL_UART_Abort_IT(uart);
    return true;
}

size_t my_custom_transport_write(struct uxrCustomTransport* transport, uint8_t * buf, size_t len, uint8_t * err){
    UART_HandleTypeDef * uart = (UART_HandleTypeDef*) transport->args;

    HAL_StatusTypeDef ret;
    if (uart->gState == HAL_UART_STATE_READY){
        ret = HAL_UART_Transmit(uart, buf, len, HAL_MAX_DELAY);
        while (ret == HAL_OK && uart->gState != HAL_UART_STATE_READY);

        return (ret == HAL_OK) ? len : 0;
    }else{
        return 0;
    }
}

size_t my_custom_transport_read(struct uxrCustomTransport* transport, uint8_t* buf, size_t len, int timeout, uint8_t* err){
    size_t wrote = 0;
    uint32_t start_time = uxr_millis();
    uint32_t end_time;
    HAL_UART_Receive_IT(&huart1, &RxByte, 1);
    while (wrote < len) {
        // end_time = uxr_millis();
        // if (end_time - start_time > timeout) {
        //     break;
        // }
    	if(RxFlag == 1) {
    		memcpy(buf, RxBuffer, RxCount);
    		wrote += RxCount;
    		RxCount = 0;
    		RxFlag = 0;
    	}
    }
    return wrote;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance == USART1) // 判断是由哪个串口触发的中断
 {
      RxBuffer[RxCount] = RxByte;//将接收到的数据放进RxBuffer1缓冲区中
      RxCount++; //RxBuffer1下标累加
      if (RxCount == UART_IT_BUFFER_SIZE)
      {
        RxCount = 0;
      }
      HAL_UART_Receive_IT(&huart1, (uint8_t *)&RxByte, 1);
    //   while(HAL_UART_Receive_IT(&huart1, (uint8_t *)&RxByte, 1) != HAL_OK){
    //     huart1.RxState = HAL_UART_STATE_READY;
    //     __HAL_UNLOCK(&huart1);
    //   }
  }
}

// void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
// {
//  if(huart->Instance == USART1){
//    HAL_UART_Receive_IT(&huart1,&RxByte,1);
//  }
// }

#endif
