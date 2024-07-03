#include "rtmp_ingest.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")

RTMPServer* rtmp_server_create(uint16_t port) {
    RTMPServer* server = malloc(sizeof(RTMPServer));
    if (!server) return NULL;
    
    server->port = port;
    server->listen_fd = INVALID_SOCKET;
    return server;
}

void rtmp_server_destroy(RTMPServer* server) {
    if (server) {
        if (server->listen_fd != INVALID_SOCKET) {
            closesocket(server->listen_fd);
        }
        free(server);
    }
}

int rtmp_server_start(RTMPServer* server) {
    struct sockaddr_in addr;
    int opt = 1;

    server->listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->listen_fd == INVALID_SOCKET) {
        return -1;
    }

    if (setsockopt(server->listen_fd, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, (char*)&opt, sizeof(opt)) == SOCKET_ERROR) {
        return -1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(server->port);

    if (bind(server->listen_fd, (struct sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR) {
        return -1;
    }

    if (listen(server->listen_fd, 10) == SOCKET_ERROR) {
        return -1;
    }

    return 0;
}

RTMPConnection* rtmp_server_accept_connection(RTMPServer* server) {
    struct sockaddr_in client_addr;
    int client_len = sizeof(client_addr);
    SOCKET client_fd;

    client_fd = accept(server->listen_fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd == INVALID_SOCKET) {
        return NULL;
    }

    RTMPConnection* conn = malloc(sizeof(RTMPConnection));
    if (!conn) {
        closesocket(client_fd);
        return NULL;
    }

    conn->socket_fd = client_fd;
    conn->client_ip = _strdup(inet_ntoa(client_addr.sin_addr));
    conn->client_port = ntohs(client_addr.sin_port);

    return conn;
}

void rtmp_connection_close(RTMPConnection* conn) {
    if (conn) {
        closesocket(conn->socket_fd);
        free(conn->client_ip);
        free(conn);
    }
}