#ifndef RTMP_INGEST_H
#define RTMP_INGEST_H

#include <stdint.h>

typedef struct RTMPConnection {
    int socket_fd;
    char* client_ip;
    uint16_t client_port;
} RTMPConnection;

typedef struct RTMPServer {
    int listen_fd;
    uint16_t port;
} RTMPServer;

RTMPServer* rtmp_server_create(uint16_t port);
void rtmp_server_destroy(RTMPServer* server);
int rtmp_server_start(RTMPServer* server);
RTMPConnection* rtmp_server_accept_connection(RTMPServer* server);
void rtmp_connection_close(RTMPConnection* conn);

#endif