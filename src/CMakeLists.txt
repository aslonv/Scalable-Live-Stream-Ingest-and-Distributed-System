add_library(ingest
    ingest/rtmp_server.c
    ingest/load_balancer.c
)

add_library(transcoding
    transcoding/transcoder.c
    transcoding/scheduler.c
)

add_library(distribution
    distribution/webrtc_server.c
    distribution/edge_node.c
)

add_library(common
    common/utils.c
)