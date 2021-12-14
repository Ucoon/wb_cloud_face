#ifndef _YT_COMMON_H_
#define _YT_COMMON_H_

typedef void *yt_handle;

typedef enum {
    YT_IMG_BGR_8UC3,
    YT_IMG_RGB_8UC3,
    YT_IMG_GRAY_8UC1,
    YT_IMG_DEPTH_16UC1,
    YT_IMG_BGRA_8UC4,
    YT_IMG_RGBA_8UC4,
    YT_IMG_NV21,
    YT_IMG_NV12,
    YT_IMG_UNKNOWN,
} yt_img_type;

typedef struct yt_image_t {
    unsigned char *data;
    int width;
    int height;
    yt_img_type type;
} yt_image;

typedef struct yt_rect_t {
    int x;
    int y;
    int width;
    int height;
} yt_rect;

typedef struct yt_pointf_t {
    float x;
    float y;
} yt_pointf;

typedef struct yt_point3f_t {
    float x;
    float y;
    float z;
} yt_point3f;

#endif  // _YT_COMMON_H_
