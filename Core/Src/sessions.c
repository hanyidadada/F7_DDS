#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "HelloWorld.h"
#include "lwip/dhcp.h"
#include "sessions.h"

uint8_t serial_output_reliable_stream_buffer[BUFFER_SIZE];
uint8_t serial_input_reliable_stream_buffer[BUFFER_SIZE];
const char* participant_xml = "<dds>"
        "<participant>"
        "<rtps>"
        "<name>default_xrce_participant</name>"
        "</rtps>"
        "</participant>"
        "</dds>";
const char* topic_xml = "<dds>"
        "<topic>"
        "<name>HelloWorldTopic</name>"
        "<dataType>HelloWorld</dataType>"
        "</topic>"
        "</dds>";
const char* datawriter_xml = "<dds>"
        "<data_writer>"
        "<topic>"
        "<kind>NO_KEY</kind>"
        "<name>HelloWorldTopic</name>"
        "<dataType>HelloWorld</dataType>"
        "</topic>"
        "</data_writer>"
        "</dds>";

const char* datareader_xml = "<dds>"
            "<data_reader>"
            "<topic>"
            "<kind>NO_KEY</kind>"
            "<name>HelloWorldTopic</name>"
            "<dataType>HelloWorld</dataType>"
            "</topic>"
            "</data_reader>"
            "</dds>";

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
    // uint32_t index = Clock_getTicks();
    HelloWorld_deserialize_topic(ub, &topic);
    HAL_GPIO_TogglePin(LD_USER1_GPIO_Port, LD_USER1_Pin);
    // uart_printf("delay: %d\n",index - topic.index);

}

int usart_session_open(session_info_t *info,UART_HandleTypeDef huart)
{
    
    uxr_set_custom_transport_callbacks(
      &(info->transport),
      true,
      serial_transport_open,
      serial_transport_close,
      serial_transport_write,
      serial_transport_read);
    if (!uxr_init_custom_transport(&(info->transport), &huart))
    {
        printf("transport error!\n");
        return -1;
    }
    uxr_init_session(&(info->session), &(info->transport.comm), 0xAAAABBCC);
    uxr_set_topic_callback(&(info->session), on_topic, NULL);
    if (!uxr_create_session(&(info->session)))
    {
        printf("open session error!\n");
        return -1;
    }
    // Streams

    info->reliable_out = uxr_create_output_reliable_stream(&(info->session), serial_output_reliable_stream_buffer, BUFFER_SIZE,
                    STREAM_HISTORY);


    info->reliable_in = uxr_create_input_reliable_stream(&(info->session), serial_input_reliable_stream_buffer, BUFFER_SIZE, STREAM_HISTORY);

    // Create entities
    info->participant_id = uxr_object_id(0x01, UXR_PARTICIPANT_ID);

    uint16_t participant_req = uxr_buffer_create_participant_xml(&(info->session), info->reliable_out, info->participant_id, 0, participant_xml, UXR_REPLACE);

    info->topic_id = uxr_object_id(0x01, UXR_TOPIC_ID);

    uint16_t topic_req = uxr_buffer_create_topic_xml(&(info->session), info->reliable_out, info->topic_id, info->participant_id, topic_xml, UXR_REPLACE);

    info->publisher_id = uxr_object_id(0x01, UXR_PUBLISHER_ID);
    const char* publisher_xml = "";
    uint16_t publisher_req = uxr_buffer_create_publisher_xml(&(info->session), info->reliable_out, info->publisher_id, info->participant_id, publisher_xml, UXR_REPLACE);

    info->datawriter_id = uxr_object_id(0x01, UXR_DATAWRITER_ID);

    uint16_t datawriter_req = uxr_buffer_create_datawriter_xml(&(info->session), info->reliable_out, info->datawriter_id, info->publisher_id, datawriter_xml, UXR_REPLACE);

    info->subscriber_id = uxr_object_id(0x01, UXR_SUBSCRIBER_ID);
    const char* subscriber_xml = "";
    uint16_t subscriber_req = uxr_buffer_create_subscriber_xml(&(info->session), info->reliable_out, info->subscriber_id , info->participant_id,
                    subscriber_xml, UXR_REUSE);

    info->datareader_id = uxr_object_id(0x01, UXR_DATAREADER_ID);
    
    uint16_t datareader_req = uxr_buffer_create_datareader_xml(&(info->session), info->reliable_out, info->datareader_id, info->subscriber_id,
                    datareader_xml, UXR_REUSE);


    // Send create entities message and wait its status
    uint8_t status[6];
    uint16_t requests[6] = {
        participant_req, topic_req, publisher_req, datawriter_req, subscriber_req, datareader_req
    };
    if (!uxr_run_session_until_all_status(&(info->session), 1000, requests, status, 6))
    {
        printf("Error at create entities: participant: %i topic: %i publisher: %i darawriter: %i\n", status[0],
                status[1], status[2], status[3]);
        return -1;
    }
    return 0;
}