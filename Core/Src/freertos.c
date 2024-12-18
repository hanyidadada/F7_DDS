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
osThreadId_t udpPubSessionTaskHandle;
uint32_t udpPubTaskBuffer[ 2048 ];
osStaticThreadDef_t udpPubTaskControlBlock;
const osThreadAttr_t udpPubSessionTask_attributes = {
    .name = "udpPubSessionTask",
    .priority = (osPriority_t)osPriorityHigh,
    .cb_mem = &udpPubTaskControlBlock,
    .cb_size = sizeof(udpPubTaskControlBlock),
    .stack_mem = &udpPubTaskBuffer[0],
    .stack_size = sizeof(udpPubTaskBuffer),
};
osThreadId_t udpSubSessionTaskHandle;
uint32_t udpSubTaskBuffer[ 2048 ];
osStaticThreadDef_t udpSubTaskControlBlock;
const osThreadAttr_t udpSubSessionTask_attributes = {
    .name = "udpSubSessionTask",
    .priority = (osPriority_t)osPriorityHigh,
    .cb_mem = &udpSubTaskControlBlock,
    .cb_size = sizeof(udpSubTaskControlBlock),
    .stack_mem = &udpSubTaskBuffer[0],
    .stack_size = sizeof(udpSubTaskBuffer),
};

osSemaphoreId_t semaphoreHandle;
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
uint32_t defaultTaskBuffer[ 2048 ];
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
void udpSubSessionTask(void *argument);
void udpPubSessionTask(void *argument);

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
  // uartSessionTaskHandle = osThreadNew(uartSessionTask, NULL, &uartSessionTask_attributes);
  udpSubSessionTaskHandle = osThreadNew(udpSubSessionTask, NULL, &udpSubSessionTask_attributes);
  udpPubSessionTaskHandle = osThreadNew(udpPubSessionTask, NULL, &udpPubSessionTask_attributes);
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
void on_topic(
        uxrSession* session,
        uxrObjectId object_id,
        uint16_t request_id,
        uxrStreamId stream_id,
        struct ucdrBuffer* ub,
        uint16_t length,
        void* args)
{
    (void) session; (void) object_id; (void) request_id; (void) stream_id; (void) length;
    // if(request_id != pubreqid) {
    //     return;
    // }
    HelloWorld topic;
    HelloWorld_deserialize_topic(ub, &topic);

//
//    uint32_t* count_ptr = (uint32_t*) args;
//    (*count_ptr)++;
}


void udpSubSessionTask(void *argument)
{
  osSemaphoreAcquire(semaphoreHandle, osWaitForever);
  // State
  char* ip = "192.168.1.3";
  char* port = "1235";

  // Transport
  uxrUDPTransport transport;
  if (!uxr_init_udp_transport(&transport, UXR_IPv4, ip, port))
  {
      // printf("Error at create transport.\n");
      while (1)
      {
        /* code */
      }
      
  }

  // Session
  uxrSession session;
  uxr_init_session(&session, &transport.comm, 0xCCCCDDDD);
  uxr_set_topic_callback(&session, on_topic, NULL);
  if (!uxr_create_session(&session))
  {
      // printf("Error at create session.\n");
      while (1)
      {
        /* code */
      }
  }

  // Streams
  uint8_t output_reliable_stream_buffer[BUFFER_SIZE];
  uxrStreamId reliable_out = uxr_create_output_reliable_stream(&session, output_reliable_stream_buffer, BUFFER_SIZE,
                  STREAM_HISTORY);

  uint8_t input_reliable_stream_buffer[BUFFER_SIZE];
  uxrStreamId reliable_in = uxr_create_input_reliable_stream(&session, input_reliable_stream_buffer, BUFFER_SIZE,
                  STREAM_HISTORY);

  // Create entities
  uxrObjectId participant_id = uxr_object_id(0x02, UXR_PARTICIPANT_ID);
  const char* participant_xml = "<dds>"
          "<participant>"
          "<rtps>"
          "<name>subscribe_xrce_participant</name>"
          "</rtps>"
          "</participant>"
          "</dds>";
  uint16_t participant_req = uxr_buffer_create_participant_xml(&session, reliable_out, participant_id, 0,
                  participant_xml, UXR_REUSE);

  uxrObjectId topic_id = uxr_object_id(0x02, UXR_TOPIC_ID);
  const char* topic_xml = "<dds>"
          "<topic>"
          "<name>HelloWorldTopic</name>"
          "<dataType>HelloWorld</dataType>"
          "</topic>"
          "</dds>";
  uint16_t topic_req = uxr_buffer_create_topic_xml(&session, reliable_out, topic_id, participant_id, topic_xml,
                                                    UXR_REUSE);

  uxrObjectId subscriber_id = uxr_object_id(0x02, UXR_SUBSCRIBER_ID);
  const char* subscriber_xml = "";
  uint16_t subscriber_req = uxr_buffer_create_subscriber_xml(&session, reliable_out, subscriber_id, participant_id,
                  subscriber_xml, UXR_REUSE);

  uxrObjectId datareader_id = uxr_object_id(0x02, UXR_DATAREADER_ID);
  const char* datareader_xml = "<dds>"
          "<data_reader>"
          "<topic>"
          "<kind>NO_KEY</kind>"
          "<name>HelloWorldTopic</name>"
          "<dataType>HelloWorld</dataType>"
          "</topic>"
          "</data_reader>"
          "</dds>";
  uint16_t datareader_req = uxr_buffer_create_datareader_xml(&session, reliable_out, datareader_id, subscriber_id,
                  datareader_xml, UXR_REUSE);

  // Send create entities message and wait its status
  uint8_t status[4];
  uint16_t requests[4] = {
      participant_req, topic_req, subscriber_req, datareader_req
  };
  if (!uxr_run_session_until_all_status(&session, 1000, requests, status, 4))
  {
      printf("Error at create entities2: participant: %i topic: %i subscriber: %i datareader: %i\n", status[0],
              status[1], status[2], status[3]);
      // return 1;
  }

  // Request topics
  uxrDeliveryControl delivery_control = {
      0
  };
  delivery_control.max_samples = UXR_MAX_SAMPLES_UNLIMITED;
  uint16_t request_id = uxr_buffer_request_data(&session, reliable_out, datareader_id, reliable_in, &delivery_control);
  // printf("sub:request id:%d\n", request_id);
  // Read topics
  bool connected = true;
  while (connected)
  {
      connected = uxr_run_session_time(&session, 1000);
  }

  // Delete resources
  uxr_delete_session(&session);
  uxr_close_udp_transport(&transport);

}

void udpPubSessionTask(void *argument)
{
  osSemaphoreAcquire(semaphoreHandle, osWaitForever);
  char* ip = "192.168.1.3";
  char* port = "1234";
  uint32_t max_topics = 20;

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
      HelloWorld topic = {};
      if(count %2 == 0) {
        topic.index = ++count;
        memcpy(topic.message, "LED_ON\0", 7);
      } else {
        topic.index = ++count;
        memcpy(topic.message, "LED_OFF", 7);
      }

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

