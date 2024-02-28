#ifndef __SESSIONS_H
#define __SESSIONS_H
#include <uxr_transport.h>
#include "uxr/client/transport.h"
#include "uxr/client/client.h"

#define STREAM_HISTORY  4
#define BUFFER_SIZE     UXR_CONFIG_CUSTOM_TRANSPORT_MTU*STREAM_HISTORY

typedef struct session_info{
    uxrSession session;
    uxrCustomTransport transport;
    uxrObjectId datawriter_id;
    uxrStreamId reliable_out;
} session_info_t;

int usart_session_open(session_info_t *info, UART_HandleTypeDef huart);

// int tcp_session_open();
#endif
