#include "load_balancer.h"
#include <stdlib.h>
#include <string.h>

LoadBalancer* load_balancer_create(size_t initial_capacity) {
    LoadBalancer* lb = malloc(sizeof(LoadBalancer));
    if (!lb) return NULL;

    lb->servers = malloc(sizeof(TranscodingServer*) * initial_capacity);
    if (!lb->servers) {
        free(lb);
        return NULL;
    }

    lb->server_count = 0;
    lb->current_server = 0;
    return lb;
}

void load_balancer_destroy(LoadBalancer* lb) {
    if (lb) {
        for (size_t i = 0; i < lb->server_count; i++) {
            free(lb->servers[i]->ip_address);
            free(lb->servers[i]);
        }
        free(lb->servers);
        free(lb);
    }
}

int load_balancer_add_server(LoadBalancer* lb, const char* ip_address, int port) {
    TranscodingServer* server = malloc(sizeof(TranscodingServer));
    if (!server) return -1;

    server->ip_address = strdup(ip_address);
    server->port = port;
    server->current_load = 0;

    lb->servers[lb->server_count++] = server;
    return 0;
}

TranscodingServer* load_balancer_get_next_server(LoadBalancer* lb) {
    if (lb->server_count == 0) return NULL;

    TranscodingServer* server = lb->servers[lb->current_server];
    lb->current_server = (lb->current_server + 1) % lb->server_count;
    return server;
}

void load_balancer_update_server_load(LoadBalancer* lb, TranscodingServer* server, int new_load) {
    server->current_load = new_load;
}