#ifndef TRANSCODING_H
#define TRANSCODING_H

#include <stdint.h>

// Define our own simple versions of the structs we need
typedef struct AVFrame {
    uint8_t *data[4];
    int linesize[4];
    int width;
    int height;
    int format;
} AVFrame;

typedef struct AVPacket {
    uint8_t *data;
    int size;
} AVPacket;

typedef struct AVCodecContext {
    int width;
    int height;
    int time_base_num;
    int time_base_den;
    int framerate_num;
    int framerate_den;
    int pix_fmt;
    int bit_rate;
    int gop_size;
    int max_b_frames;
} AVCodecContext;

typedef struct TranscodingContext {
    AVCodecContext *decoder_ctx;
    AVCodecContext *encoder_ctx;
    AVFrame *frame;
    AVPacket *pkt;
    struct SwsContext *sws_ctx;
    int input_width;
    int input_height;
    int output_width;
    int output_height;
    int pix_fmt;
} TranscodingContext;

TranscodingContext* transcoding_context_create(int in_w, int in_h, int out_w, int out_h, const char* codec);
void transcoding_context_destroy(TranscodingContext* ctx);
int transcode_frame(TranscodingContext* ctx, const uint8_t* input_data, int input_size, uint8_t** output_data, int* output_size);

#endif // TRANSCODING_H