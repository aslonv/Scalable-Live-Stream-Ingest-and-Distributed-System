#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <librtmp/rtmp.h>
#include <pthread.h>

#define MAX_THREADS 10
#define PACKET_SIZE 1024 * 1024

volatile sig_atomic_t keep_running = 1;

void signal_handler(int sig) {
    printf("Caught signal %d. Shutting down...\n", sig);
    keep_running = 0;
}

void *handle_client(void *arg) {
    RTMP *rtmp = (RTMP *)arg;
    RTMPPacket packet = {0};

    while (RTMP_IsConnected(rtmp) && keep_running) {
        if (RTMP_ReadPacket(rtmp, &packet)) {
            if (RTMPPacket_IsReady(&packet)) {
                printf("Received packet of size %d, type %02X\n", packet.m_nBodySize, packet.m_packetType);
                
                // Process packet based on type
                switch (packet.m_packetType) {
                    case RTMP_PACKET_TYPE_AUDIO:
                        // Handle audio packet
                        break;
                    case RTMP_PACKET_TYPE_VIDEO:
                        // Handle video packet
                        break;
                    case RTMP_PACKET_TYPE_INFO:
                        // Handle metadata
                        break;
                    default:
                        // Handle other packet types
                        break;
                }
                
                RTMPPacket_Free(&packet);
            }
        } else {
            usleep(1000); // Sleep for 1ms to avoid busy-waiting
        }
    }

    RTMP_Close(rtmp);
    RTMP_Free(rtmp);
    return NULL;
}

int main() {
    RTMP *server_rtmp = RTMP_Alloc();
    if (!server_rtmp) {
        fprintf(stderr, "Failed to allocate RTMP server instance.\n");
        return EXIT_FAILURE;
    }

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    RTMP_Init(server_rtmp);
    if (!RTMP_SetupURL(server_rtmp, "rtmp://0.0.0.0:1935/live")) {
        fprintf(stderr, "Failed to set up RTMP URL.\n");
        RTMP_Free(server_rtmp);
        return EXIT_FAILURE;
    }

    RTMP_EnableWrite(server_rtmp);

    if (!RTMP_Connect(server_rtmp, NULL) || !RTMP_ConnectStream(server_rtmp, 0)) {
        fprintf(stderr, "Failed to connect to RTMP server.\n");
        RTMP_Free(server_rtmp);
        return EXIT_FAILURE;
    }

    printf("RTMP Server is running...\n");

    pthread_t threads[MAX_THREADS];
    int thread_count = 0;

    while (keep_running) {
        RTMP *client_rtmp = RTMP_Alloc();
        if (!client_rtmp) {
            fprintf(stderr, "Failed to allocate RTMP client instance.\n");
            continue;
        }

        RTMP_Init(client_rtmp);
        *client_rtmp = *server_rtmp;

        if (thread_count < MAX_THREADS) {
            if (pthread_create(&threads[thread_count], NULL, handle_client, client_rtmp) != 0) {
                fprintf(stderr, "Failed to create thread for client.\n");
                RTMP_Free(client_rtmp);
            } else {
                thread_count++;
            }
        } else {
            fprintf(stderr, "Maximum number of threads reached. Rejecting new connection.\n");
            RTMP_Free(client_rtmp);
        }

        usleep(10000); // Sleep for 10ms between connection attempts
    }

    // Wait for all threads to finish
    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }

    RTMP_Close(server_rtmp);
    RTMP_Free(server_rtmp);
    printf("RTMP Server shut down gracefully.\n");
    return EXIT_SUCCESS;
}
