#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "HelloWorld.h"
#include "lwip/dhcp.h"
#include "sessions.h"

uint8_t output_reliable_stream_buffer[BUFFER_SIZE];
uint8_t input_reliable_stream_buffer[BUFFER_SIZE];
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

int usart_session_open(session_info_t *info,UART_HandleTypeDef huart)
{
    
    uxr_set_custom_transport_callbacks(
      &(info->transport),
      true,
      my_custom_transport_open,
      my_custom_transport_close,
      my_custom_transport_write,
      my_custom_transport_read);
    if (!uxr_init_custom_transport(&(info->transport), &huart))
    {
        printf("transport error!\n");
        return -1;
    }
    uxr_init_session(&(info->session), &(info->transport.comm), 0xAAAABBBB);
    if (!uxr_create_session(&(info->session)))
    {
        printf("open session error!\n");
        return -1;
    }
    // Streams

    info->reliable_out = uxr_create_output_reliable_stream(&(info->session), output_reliable_stream_buffer, BUFFER_SIZE,
                    STREAM_HISTORY);


    uxr_create_input_reliable_stream(&(info->session), input_reliable_stream_buffer, BUFFER_SIZE, STREAM_HISTORY);

    // Create entities
    uxrObjectId participant_id = uxr_object_id(0x01, UXR_PARTICIPANT_ID);

    uint16_t participant_req = uxr_buffer_create_participant_xml(&(info->session), info->reliable_out, participant_id, 0,
                    participant_xml, UXR_REPLACE);

    uxrObjectId topic_id = uxr_object_id(0x01, UXR_TOPIC_ID);

    uint16_t topic_req = uxr_buffer_create_topic_xml(&(info->session), info->reliable_out, topic_id, participant_id, topic_xml,
                    UXR_REPLACE);

    uxrObjectId publisher_id = uxr_object_id(0x01, UXR_PUBLISHER_ID);
    const char* publisher_xml = "";
    uint16_t publisher_req = uxr_buffer_create_publisher_xml(&(info->session), info->reliable_out, publisher_id, participant_id,
                    publisher_xml, UXR_REPLACE);

    info->datawriter_id = uxr_object_id(0x01, UXR_DATAWRITER_ID);

    uint16_t datawriter_req = uxr_buffer_create_datawriter_xml(&(info->session), info->reliable_out, info->datawriter_id, publisher_id,
                    datawriter_xml, UXR_REPLACE);

    // Send create entities message and wait its status
    uint8_t status[4];
    uint16_t requests[4] = {
        participant_req, topic_req, publisher_req, datawriter_req
    };
    if (!uxr_run_session_until_all_status(&(info->session), 1000, requests, status, 4))
    {
        printf("Error at create entities: participant: %i topic: %i publisher: %i darawriter: %i\n", status[0],
                status[1], status[2], status[3]);
        return -1;
    }
    return 0;
    // Write topics
    // uint32_t count = 0;
    // /* Infinite loop */
    // for(;;)
    // {
    //     HelloWorld topic = {
    //         ++count, "Hello DDS world!"
    //     };

    //     ucdrBuffer ub;
    //     uint32_t topic_size = HelloWorld_size_of_topic(&topic, 0);
    //     uxr_prepare_output_stream(&session, reliable_out, datawriter_id, &ub, topic_size);
    //     HelloWorld_serialize_topic(&ub, &topic);

    //     // printf("Send topic: %s, id: %li\n", topic.message, topic.index);
    //     HAL_GPIO_TogglePin(LD_USER1_GPIO_Port, LD_USER1_Pin);
    //     uxr_run_session_time(&session, 1000);
    // }
    // Delete resources
    // uxr_delete_session(&session);
    // uxr_close_custom_transport(&transport);
}