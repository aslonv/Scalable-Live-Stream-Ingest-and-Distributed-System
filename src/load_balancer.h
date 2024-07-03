#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

#include <stddef.h>

typedef struct TranscodingServer {
    char* ip_address;
    int port;
    int current_load;
} TranscodingServer;

typedef struct LoadBalancer {
    TranscodingServer** servers;
    size_t server_count;
    size_t current_server;
} LoadBalancer;

LoadBalancer* load_balancer_create(size_t initial_capacity);
void load_balancer_destroy(LoadBalancer* lb);
int load_balancer_add_server(LoadBalancer* lb, const char* ip_address, int port);
TranscodingServer* load_balancer_get_next_server(LoadBalancer* lb);
void load_balancer_update_server_load(LoadBalancer* lb, TranscodingServer* server, int new_load);

#endif // LOAD_BALANCER_H