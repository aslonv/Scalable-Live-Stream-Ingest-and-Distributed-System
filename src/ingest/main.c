#include <stdio.h>
#include <stdlib.h>
#include <librtmp/rtmp.h>

int main() {
    RTMP *rtmp = RTMP_Alloc();
    if (!rtmp) {
        fprintf(stderr, "Failed to allocate RTMP instance.\n");
        return EXIT_FAILURE;
    }
    RTMP_Init(rtmp);

    if (!RTMP_SetupURL(rtmp, "rtmp://0.0.0.0:1935/live")) {
        fprintf(stderr, "Failed to set up RTMP URL.\n");
        RTMP_Free(rtmp);
        return EXIT_FAILURE;
    }

    RTMP_EnableWrite(rtmp);

    if (!RTMP_Connect(rtmp, NULL)) {
        fprintf(stderr, "Failed to connect to RTMP server.\n");
        RTMP_Free(rtmp);
        return EXIT_FAILURE;
    }

    if (!RTMP_ConnectStream(rtmp, 0)) {
        fprintf(stderr, "Failed to connect RTMP stream.\n");
        RTMP_Free(rtmp);
        return EXIT_FAILURE;
    }

    printf("RTMP Server is running...\n");

    while (RTMP_IsConnected(rtmp)) {
        // Handle incoming RTMP packets here
        RTMPPacket packet;
        if (RTMP_ReadPacket(rtmp, &packet)) {
            if (RTMPPacket_IsReady(&packet)) {
                // Process the packet
                printf("Received packet of size %d\n", packet.m_nBodySize);
                RTMPPacket_Free(&packet);
            }
        }
    }

    RTMP_Close(rtmp);
    RTMP_Free(rtmp);

    return EXIT_SUCCESS;
}
