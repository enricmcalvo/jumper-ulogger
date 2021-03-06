#ifndef NETWORK_LOG_HANDLER
#define NETWORK_LOG_HANDLER

#include <stdbool.h>
#include "compilers.h"
#include "ubuffer.h"

typedef struct {
    uint8_t version;
    EventType event_type;
    timestamp time;
    uint8_t data_length;
} __PACKED uLoggerEventHeader;

typedef int (*send_to_network)(void * network_context, uint8_t * data, uint32_t length);
typedef bool (*can_send_to_network)(void * network_context);
typedef void (*periodic_callback_function)(void * config);
typedef int (*formatter)(void * formatter_context, uLoggerEventHeader * event,
                        uint8_t ** formatted_event, size_t * formatted_event_length);

typedef struct {
    uint32_t log_send_period; 
    void * context;
    send_to_network send;
    can_send_to_network can_send;
    periodic_callback_function callback;
    uBuffer buffer;
    formatter format_method;
    void * formatter_context;
} network_log_config;

#define NETWORK_LOGGER_VERSION 1

int network_logger_init(network_log_config * config, uint8_t * buffer, size_t buffer_size);

void netowork_logger_periodic_callback(void * data);

HandlerReturnType network_handler_log(void * context, LogLevel level, EventType event_type, timestamp time, void * log_data, size_t data_length);

#endif
