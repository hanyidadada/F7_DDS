#ifndef __SESSIONS_H
#define __SESSIONS_H

#include "serialtransport.h"

#define STREAM_HISTORY  4
#define BUFFER_SIZE     UXR_CONFIG_CUSTOM_TRANSPORT_MTU*STREAM_HISTORY

typedef struct session_info{
    uxrSession session;
    uxrCustomTransport transport;
    uxrStreamId reliable_in;
    uxrStreamId reliable_out;
    uxrObjectId participant_id;
    uxrObjectId topic_id;
    uxrObjectId subscriber_id;
    uxrObjectId datareader_id;
    uxrObjectId publisher_id;
    uxrObjectId datawriter_id;
} session_info_t;

int usart_session_open(session_info_t *info, UART_HandleTypeDef huart);

// int tcp_session_open();
#endif
