#ifndef _YT_DEFINES_H_
#define _YT_DEFINES_H_

// ----------------------------------------------------------------------------
// YouTu for cross platform defines export c api.
// windows @see: http://geoffair.net/ms/declspec.htm
// ----------------------------------------------------------------------------
#if (defined(WIN32) || defined(WIN64))
    #ifdef YT_EXPORT
        #define YT_PUBLIC_ __declspec(dllexport)
    #else
        #define YT_PUBLIC_ __declspec(dllimport)
    #endif
#else
    #ifdef YT_EXPORT
        #define YT_PUBLIC_ __attribute__((visibility("default")))
    #else
        #define YT_PUBLIC_
    #endif
#endif

#ifdef __cplusplus
    #define YT_PUBLIC extern "C" YT_PUBLIC_
#else
    #define YT_PUBLIC YT_PUBLIC_
#endif

// ----------------------------------------------------------------------------
// YouTu error code defines
// ----------------------------------------------------------------------------
#define YT_SUCCESS 0
#define YT_ERROR   -1

// init error code: [-10, -99]
#define YT_ERROR_OPEN_FILE  -10
#define YT_ERROR_READ_FILE  -11
#define YT_ERROR_FILE_EMPTY -12

#define YT_ERROR_RPN_NET_INIT      -20
#define YT_ERROR_RPN_NET_NOT_INIT  -21
#define YT_ERROR_RPN_INST_INIT     -22
#define YT_ERROR_RPN_INST_NOT_INIT -23
#define YT_ERROR_RPN_FORWARD       -24

#define YT_ERROR_INVALID_INSTANCE  -99

// arguments error code: [-100, -999]
#define YT_ERROR_MUST_NOT_NULL    -100

#define YT_ERROR_IMAGE_TYPE       -110
#define YT_ERROR_IMAGE_DATA       -111

#define YT_ERROR_FACE_POINTS        -120
#define YT_ERROR_FACE_FIVE_POINTS   -121
#define YT_ERROR_FACE_NINETY_POINTS -122
#define YT_ERROR_FACE_RECT          -123

#define YT_ERROR_INVALID_MODEL_VERSION -130
#define YT_ERROR_MODEL_THRESHOLDS_SIZE -131

// auth error code
#define YT_ERROR_AUTH_FAILED -1024

// ----------------------------------------------------------------------------
// YouTu common code defines
// ----------------------------------------------------------------------------
#define YT_FACE_FEATURE_SIZE_512  512
#define YT_FACE_FEATURE_SIZE_1024 1024

#define YT_FACE_FIVE_POINTS_SIZE   5
#define YT_FACE_NINETY_POINTS_SIZE 90

#endif // _YT_DEFINES_H_
