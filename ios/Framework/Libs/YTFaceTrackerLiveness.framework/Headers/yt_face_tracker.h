#ifndef _YT_FACE_TRACKER_H_
#define _YT_FACE_TRACKER_H_

#include "yt_common.h"
#include "yt_defines.h"

typedef struct yt_face_tracker_param_t_liveness {
    int min_face_size;     ///< 最小物体大小，建议使用默认值
    int max_face_size;     ///< 最大物体大小，建议使用默认值
    int bigger_face_mode;  ///< 检测模式：0:完整检测, 1:快速检测
    bool non_square_rect;  ///< 检测框：是否为正方形框
    float threshold;       ///< 检测阈值：建议使用默认值
    int detect_interval;   ///< 检测间隔，默认6; detect_interval为-1时，只在第一帧或没有人时做检测
} Yt_face_tracker_param_liveness;

typedef struct yt_tracked_face_t_liveness {
    int shape_size;             ///< 人脸配准点有效位数 130 or 256
    yt_pointf face_shape[256];  ///< 人脸配准点
    float face_vis[256];        ///< 人脸配准点置信度
    yt_rect face_rect;          ///< 人脸框

    int frame_id;  ///< 帧ID
    int trace_id;  ///< 轨迹ID

    float pitch;  ///< 人脸俯仰角
    float yaw;    ///< 人脸偏航角
    float roll;   ///< 人脸翻滚角
} Yt_tracked_face_liveness;

/**
 * @brief 获取sdk版本
 *
 * @return yt_sdk_version
 */
YT_PUBLIC const char *Yt_face_tracker_get_version_liveness();

/**
 * @brief 创建实例，每个线程需要单独的实例
 * 
 * @param[out] handle 创建的handle，每个线程需要独立的handle
 * @param[in] model_dirpath 传入模型绝对路径或者相对路径，例如：./model/
 * @param[in] config_filename 传入模型绝对路径或者相对路径下的配置文件名称，例如：config.ini
 * @param[in] param 模型初始化参数，其中的image_width、image_height和image_pading属性要根据视频长宽调整
 * @return YT_SUCCESS：成功，其他：失败
 */
YT_PUBLIC int Yt_face_tracker_create_handle_liveness(yt_handle *handle, const char *model_dirpath, const char *config_filename);

#ifdef __ANDROID__
#include <android/asset_manager.h>
/**
 * @brief 创建实例，每个线程需要单独的实例，该接口用于 android 加载 assets 目录下模型文件
 *        如有 jni 开发需求，可以通过此接口加载模型
 *
 * @param[in] mgr 通过 `AAssetManager *mgr = AAssetManager_fromJava(env, assetManager);` 获得
 * @param[in] model_dirpath 传入模型相对于 `assets` 目录的路径，例如：`models/face-xxx`
 * @param[in] config_filename 传入模型路径下的配置文件名称，例如：`config.ini`
 * @return YT_SUCCESS：成功，其他：失败
 */
YT_PUBLIC int Yt_face_tracker_create_handle_android_liveness(yt_handle *handle, AAssetManager *mgr, const char *model_dirpath, const char *config_filename);
#endif

/**
 * @brief 销毁实例
 *
 * @param[in] handle 实例句柄
 */
YT_PUBLIC void Yt_face_tracker_destroy_handle_liveness(yt_handle handle);

/**
 * @brief 获取参数
 *
 * @param[in] handle 实例句柄
 * @param[out] param 当前实例的参数
 * @return YT_SUCCESS：成功，其他：失败
 */
YT_PUBLIC int Yt_face_tracker_get_param_liveness(yt_handle handle, Yt_face_tracker_param_liveness *param);

/**
 * @brief 设置参数，推荐先获取参数，再设置
 *
 * @param[in] handle 实例句柄
 * @param[in] param 自定义的参数
 * @return YT_SUCCESS：成功，其他：失败
 */
YT_PUBLIC int Yt_face_tracker_set_param_liveness(yt_handle handle, const Yt_face_tracker_param_liveness param);

/**
 * @brief 追踪接口，适合于视频流检测，内部封装了检测、5点配准、稳定模块，具有内部状态
 *
 * @param[in] handle 实例句柄
 * @param[in] image 图片，图片类型：YT_IMG_BGR_8UC3 or YT_IMG_RGB_8UC3
 * @param[out] tracked_faces 人脸追踪结果
 * @param[out] tracked_faces_count 检测到的人脸数量
 * @return YT_SUCCESS：成功，其他：失败
 */
YT_PUBLIC int Yt_face_tracker_track_liveness(yt_handle handle, const yt_image image, Yt_tracked_face_liveness **tracked_faces, int *tracked_faces_count);

/**
 * @brief 重置追踪接口，当对新的视频进行追踪时调用，用于清空追踪内部状态
 *
 * @param[in] handle 实例句柄
 * @return YT_SUCCESS：成功，其他：失败
 */
YT_PUBLIC int Yt_face_tracker_reset_liveness(yt_handle handle);

/**
 * @brief 释放人脸追踪结果
 *
 * @param[in] tracked_faces 人脸追踪结果
 */
YT_PUBLIC void Yt_face_tracker_release_tracked_faces_liveness(Yt_tracked_face_liveness *tracked_faces);

#endif  // _YT_FACE_TRACKER_H_
