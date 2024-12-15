/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "sessions.h"
#include "usart.h"
#include "HelloWorld.h"
#include <stdio.h>
#include <uxr/client/client.h>
#include <ucdr/microcdr.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
osThreadId_t uartSessionTaskHandle;
uint32_t uartTaskBuffer[ 2048 ];
osStaticThreadDef_t uartTaskControlBlock;
const osThreadAttr_t uartSessionTask_attributes = {
    .name = "uartSessionTask",
    .priority = (osPriority_t)osPriorityHigh,
    .cb_mem = &uartTaskControlBlock,
    .cb_size = sizeof(uartTaskControlBlock),
    .stack_mem = &uartTaskBuffer[0],
    .stack_size = sizeof(uartTaskBuffer),
};
osThreadId_t udpSessionTaskHandle;
uint32_t udpTaskBuffer[ 2048 ];
osStaticThreadDef_t udpTaskControlBlock;
const osThreadAttr_t udpSessionTask_attributes = {
    .name = "udpSessionTask",
    .priority = (osPriority_t)osPriorityHigh,
    .cb_mem = &udpTaskControlBlock,
    .cb_size = sizeof(udpTaskControlBlock),
    .stack_mem = &udpTaskBuffer[0],
    .stack_size = sizeof(udpTaskBuffer),
};

osSemaphoreId_t semaphoreHandle;
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
uint32_t defaultTaskBuffer[ 256 ];
osStaticThreadDef_t defaultTaskControlBlock;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .cb_mem = &defaultTaskControlBlock,
  .cb_size = sizeof(defaultTaskControlBlock),
  .stack_mem = &defaultTaskBuffer[0],
  .stack_size = sizeof(defaultTaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void uartSessionTask(void *argument);
void udpSessionTask(void *argument);

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

extern void MX_USB_DEVICE_Init(void);
extern void MX_LWIP_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  semaphoreHandle = osSemaphoreNew(2, 0, NULL);
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  uartSessionTaskHandle = osThreadNew(uartSessionTask, NULL, &uartSessionTask_attributes);
  // udpSessionTaskHandle = osThreadNew(udpSessionTask, NULL, &udpSessionTask_attributes);
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();

  /* init code for LWIP */
  MX_LWIP_Init();
  /* USER CODE BEGIN StartDefaultTask */
  osSemaphoreRelease(semaphoreHandle);
  // uartSessionTask(NULL);
  osSemaphoreRelease(semaphoreHandle);
  while (1)
  {
    osDelay(100000);
  }
  
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void uartSessionTask(void *argument)
{
  osSemaphoreAcquire(semaphoreHandle, osWaitForever);
  // osThreadTerminate(defaultTaskHandle);
  session_info_t info;
  if (usart_session_open(&info, huart1) < 0)
  {
    printf("usart session open error!");
    HAL_GPIO_TogglePin(LD_USER1_GPIO_Port, LD_USER1_Pin);
  }
  osDelay(1000);
  // Write topics
  uint32_t count = 0;
  /* Infinite loop */
  while (count < 20)
  {
    HelloWorld topic;
    if(count % 2 == 0) {
      topic.index = count++;
      memset(topic.message, 0, 255);
      memcpy(topic.message, "LED_ON", 7);
    } else {
      topic.index = count++;
      memset(topic.message, 0, 255);
      memcpy(topic.message, "LED_OFF", 7);
    }
    

    ucdrBuffer ub;
    uint32_t topic_size = HelloWorld_size_of_topic(&topic, 0);
    uxr_prepare_output_stream(&(info.session), info.reliable_out, info.datawriter_id, &ub, topic_size);
    HelloWorld_serialize_topic(&ub, &topic);
    if(!uxr_run_session_time(&(info.session), 1000)){
      // HAL_GPIO_TogglePin(LD_USER1_GPIO_Port, LD_USER1_Pin);
    }
    vTaskDelay(1000);
  }
  // Delete resources
  uxr_delete_session(&(info.session));
  uxr_close_custom_transport(&(info.transport));
}

void udpSessionTask(void *argument)
{
  osSemaphoreAcquire(semaphoreHandle, osWaitForever);
  char* ip = "10.2.25.98";
  char* port = "1234";
  uint32_t max_topics = 15;

  // Transport
  uxrUDPTransport transport;
  if (!uxr_init_udp_transport(&transport, UXR_IPv4, ip, port))
  {
      while (1) {
        /* code */
      }
      
  }

  // Session
  uxrSession session;
  uxr_init_session(&session, &transport.comm, 0xAAAABBBB);
  if (!uxr_create_session(&session))
  {
      // printf("Error at create session.\n");
      while (1) {
        /* code */
      }
      
      // return 1;
  }

  // Streams
  uint8_t output_reliable_stream_buffer[BUFFER_SIZE];
  uxrStreamId reliable_out = uxr_create_output_reliable_stream(&session, output_reliable_stream_buffer, BUFFER_SIZE,
                  STREAM_HISTORY);
  uint8_t input_reliable_stream_buffer[BUFFER_SIZE];
  uxr_create_input_reliable_stream(&session, input_reliable_stream_buffer, BUFFER_SIZE, STREAM_HISTORY);

  // Create entities
  uxrObjectId participant_id = uxr_object_id(0x01, UXR_PARTICIPANT_ID);
  const char* participant_xml = "<dds>"
          "<participant>"
          "<rtps>"
          "<name>default_xrce_participant</name>"
          "</rtps>"
          "</participant>"
          "</dds>";
  uint16_t participant_req = uxr_buffer_create_participant_xml(&session, reliable_out, participant_id, 0,
                  participant_xml, UXR_REPLACE);

  uxrObjectId topic_id = uxr_object_id(0x01, UXR_TOPIC_ID);
  const char* topic_xml = "<dds>"
          "<topic>"
          "<name>HelloWorldTopic</name>"
          "<dataType>HelloWorld</dataType>"
          "</topic>"
          "</dds>";
  uint16_t topic_req = uxr_buffer_create_topic_xml(&session, reliable_out, topic_id, participant_id, topic_xml,
                  UXR_REPLACE);

  uxrObjectId publisher_id = uxr_object_id(0x01, UXR_PUBLISHER_ID);
  const char* publisher_xml = "";
  uint16_t publisher_req = uxr_buffer_create_publisher_xml(&session, reliable_out, publisher_id, participant_id,
                  publisher_xml, UXR_REPLACE);

  uxrObjectId datawriter_id = uxr_object_id(0x01, UXR_DATAWRITER_ID);
  const char* datawriter_xml = "<dds>"
          "<data_writer>"
          "<topic>"
          "<kind>NO_KEY</kind>"
          "<name>HelloWorldTopic</name>"
          "<dataType>HelloWorld</dataType>"
          "</topic>"
          "</data_writer>"
          "</dds>";
  uint16_t datawriter_req = uxr_buffer_create_datawriter_xml(&session, reliable_out, datawriter_id, publisher_id,
                  datawriter_xml, UXR_REPLACE);

  // Send create entities message and wait its status
  uint8_t status[4];
  uint16_t requests[4] = {
      participant_req, topic_req, publisher_req, datawriter_req
  };
  if (!uxr_run_session_until_all_status(&session, 1000, requests, status, 4))
  {
      printf("Error at create entities: participant: %i topic: %i publisher: %i datawriter: %i\n", status[0],
              status[1], status[2], status[3]);
      // return 1;
  }
  // Write topics
  bool connected = true;
  uint32_t count = 0;
  while (connected && count < max_topics)
  {
      HelloWorld topic = {
          ++count, "Hello DDS world!"
      };

      ucdrBuffer ub;
      uint32_t topic_size = HelloWorld_size_of_topic(&topic, 0);
      uxr_prepare_output_stream(&session, reliable_out, datawriter_id, &ub, topic_size);
      HelloWorld_serialize_topic(&ub, &topic);

      // printf("Send topic: %s, id: %li\n", topic.message, topic.index);
      connected = uxr_run_session_time(&session, 1000);
      osDelay(1000);
  }

  // Delete resources
  uxr_delete_session(&session);
  uxr_close_udp_transport(&transport);
}
/* USER CODE END Application */

