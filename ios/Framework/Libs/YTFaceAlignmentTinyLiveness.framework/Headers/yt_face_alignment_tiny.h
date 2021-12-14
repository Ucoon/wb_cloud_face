#ifndef _YT_FACE_ALIGNMENT_TINY_H_
#define _YT_FACE_ALIGNMENT_TINY_H_

#include "yt_common.h"
#include "yt_defines.h"

// 人脸配准模式
#define YT_FACE_ALIGNMENT_MODE_SPARSE 1
#define YT_FACE_ALIGNMENT_MODE_DENSE 2

// 人脸追踪过程，置信度不满足阈值要求时的失败结果
#define YT_ERROR_FACE_ALIGNMENT_TRACK_CONF -10000

// 人脸稠密点点位数量
// 左眉毛，右眉毛，左眼，右眼
// 鼻子，嘴巴，轮廓，前额，瞳孔
#define YT_DENSE_EYEBROW_POINTS_NUM 16
#define YT_DENSE_EYE_POINTS_NUM 24
#define YT_DENSE_NOSE_POINTS_NUM 22
#define YT_DENSE_MOUTH_POINTS_NUM 72
#define YT_DENSE_PROFILE_POINTS_NUM 41
#define YT_DENSE_FOREHEAD_POINTS_NUM 7
#define YT_DENSE_PUPIL_POINTS_NUM 34


typedef struct yt_face_shape_tiny_t_liveness {
    int eye_size;       ///< 眼睛点数（左眼，右眼）
    int eyebrow_size;   ///< 眉毛点数（左眉，右眉）
    int nose_size;      ///< 鼻子点数
    int mouth_size;     ///< 嘴巴点数
    int profile_size;   ///< 轮廓点数
    int forehead_size;  ///< 前额点数
    int pupil_size;     ///< 瞳孔点数

    yt_pointf left_eyebrow[YT_DENSE_EYEBROW_POINTS_NUM];
    yt_pointf right_eyebrow[YT_DENSE_EYEBROW_POINTS_NUM];
    yt_pointf left_eye[YT_DENSE_EYE_POINTS_NUM];
    yt_pointf right_eye[YT_DENSE_EYE_POINTS_NUM];
    yt_pointf nose[YT_DENSE_NOSE_POINTS_NUM];
    yt_pointf mouth[YT_DENSE_MOUTH_POINTS_NUM];
    yt_pointf profile[YT_DENSE_PROFILE_POINTS_NUM];
    yt_pointf forehead[YT_DENSE_FOREHEAD_POINTS_NUM];
    yt_pointf pupil[YT_DENSE_PUPIL_POINTS_NUM];

    float left_eyebrow_vis[YT_DENSE_EYEBROW_POINTS_NUM];
    float right_eyebrow_vis[YT_DENSE_EYEBROW_POINTS_NUM];
    float left_eye_vis[YT_DENSE_EYE_POINTS_NUM];
    float right_eye_vis[YT_DENSE_EYE_POINTS_NUM];
    float nose_vis[YT_DENSE_NOSE_POINTS_NUM];
    float mouth_vis[YT_DENSE_MOUTH_POINTS_NUM];
    float profile_vis[YT_DENSE_PROFILE_POINTS_NUM];
    float forehead_vis[YT_DENSE_FOREHEAD_POINTS_NUM];
    float pupil_vis[YT_DENSE_PUPIL_POINTS_NUM];

    float confidence; ///< 置信度
    float occuRatio;  ///< 遮挡比例
} Yt_face_shape_tiny_liveness;

typedef struct yt_face_shape_3d_tiny_t_liveness {
    yt_point3f dense_points[1000];  // 三维姿态点位

    float pitch;  // Up < 0 | Down > 0, 范围在 [-60 ~ 60 ] 内会更加准确
    float yaw;    // Left > 0 | Right < 0, 范围在 [-60 ~ 60] 内会更加准确
    float roll;   // Anti-clockwise < 0 | Clockwise > 0

    float transform[4][4];
} Yt_face_shape_3d_tiny_liveness;

/**
 * @brief 获取版本
 *
 * @param[in] handle 实例句柄，获得 SDK 版本
 * @return SDK 版本
 */
// YT_PUBLIC const char *yt_face_alignment_tiny_get_version();
YT_PUBLIC const char *Yt_face_alignment_tiny_get_version_liveness();

/**
 * @brief 初始化SDK，每个进程只需调用一次
 *
 * @param[in] model_dirpath 传入模型绝对路径或者相对路径，例如：`./model/face-xxx`
 * @param[in] config_filename 传入模型路径下的配置文件名称，例如：`config.ini`
 * @return YT_SUCCESS：成功，其他：失败
 */
// YT_PUBLIC int yt_face_alignment_tiny_create_handle(yt_handle *handle, const char *model_dirpath, const char *config_filename);
YT_PUBLIC int Yt_face_alignment_tiny_create_handle_liveness(yt_handle *handle, const char *model_dirpath, const char *config_filename);

#ifdef __ANDROID__
#include <android/asset_manager.h>
/**
 * @brief 初始化SDK，每个进程只需调用一次，该接口用于 android 加载 assets 目录下模型文件
 *        如有 jni 开发需求，可以通过此接口加载模型
 *
 * @param[in] mgr 通过 `AAssetManager *mgr = AAssetManager_fromJava(env, assetManager);` 获得
 * @param[in] assets_model_dirpath 传入模型相对于 `assets` 目录的路径，例如：`models/face-xxx`
 * @param[in] assets_config_filename 传入模型路径下的配置文件名称，例如：`config.ini`
 * @return YT_SUCCESS：成功，其他：失败
 */
YT_PUBLIC int Yt_face_alignment_tiny_create_handle_android_liveness(yt_handle *handle, AAssetManager *mgr, const char *model_dirpath, const char *config_filename);
// YT_PUBLIC int yt_face_alignment_tiny_create_handle_android(yt_handle *handle, AAssetManager *mgr, const char *model_dirpath, const char *config_filename);
#endif

/**
 * @brief 销毁实例
 *
 * @param[in] handle 实例句柄
 * @return
 */
YT_PUBLIC void Yt_face_alignment_tiny_destroy_handle_liveness(yt_handle handle);
// YT_PUBLIC void yt_face_alignment_tiny_destroy_handle(yt_handle handle);

/**
 * @brief 设置实例出来的人脸配准点的置信度阈值
 *
 * @param[in] handle 实例句柄
 * @param[in] threshold 人脸配准置信度阈值
 * @return YT_SUCCESS：成功，其他：失败
 */
YT_PUBLIC int Yt_face_alignment_tiny_set_threshold_liveness(yt_handle handle, float threshold);
// YT_PUBLIC int yt_face_alignment_tiny_set_threshold(yt_handle handle, float threshold);

/**
 * @brief 设置实例align和track接口的配准模式
 *
 * @param[in] handle 实例句柄
 * @param[in] mode 1：代表 SPARSE/130 点配准，2：代表 DENSE/256 点配准
 *            可选择模式取决于初始化时 config 文件中的 type，DENSE兼容模式：1、2，SPARSE只支持模式：1
 * @return YT_SUCCESS：成功，其他：失败
 */
YT_PUBLIC int Yt_face_alignment_tiny_set_mode_liveness(yt_handle handle, int mode);
// YT_PUBLIC int yt_face_alignment_tiny_set_mode(yt_handle handle, int mode);

/**
 * @brief 配准接口，用于人脸框得到人脸信息
 *
 * @param[in] handle 实例句柄
 * @param[in] image 图片，推荐 YT_IMG_BGR_8UC3 / YT_IMG_RGB_8UC3 / YT_IMG_GRAY_8UC1
 * @param[in] rect 人脸框
 * @param[out] face 人脸信息
 * @return YT_PUBLIC yt_face_alignment_tiny_align
 */
YT_PUBLIC int Yt_face_alignment_tiny_align_liveness(yt_handle handle, const yt_image image, const yt_rect rect, Yt_face_shape_tiny_liveness *face);
// YT_PUBLIC int yt_face_alignment_tiny_align(yt_handle handle, const yt_image image, const yt_rect rect, yt_face_shape_tiny *face);

/**
 * @brief 追踪配准接口
 * @example 当配合 YTFaceDetector SDK 使用时候的调用示例
 *
 * ```c++
 *  int ret;
 *  // step 1: 获取输入图片上检测到的人脸
 *  yt_rect *rects;
 *  int rect_count = 0;
 *  ret = yt_face_detector_detect(yt_detect_handle, image, param, &rects, &rect_count);
 *
 *  // step 2: 使用 rect 进行配准，首帧时要求 rect 准确
 *  yt_face_shape_tiny *face_shapes = new yt_face_shape_tiny[rect_count];
 *  for (int i = 0; i < rect_count; i++) {
 *      int face_id = i;
 *      yt_rect face_rect = rect[face_id];
 *      ret = yt_face_alignment_tiny_track(yt_align_hanele, image, face_id, face_rect, &face_shapes[face_id]);
 *  }
 *
 *  // step 3: 释放
 *  delete[] rects;
 *  for (int i = 0; i < rect_count; i++) {
 *      yt_face_alignment_tiny_release(face_shapes[i]);
 *  }
 *  delete[] face_shapes;
 * ```c++
 *
 * @param[in] handle 实例句柄
 * @param[in] image 图片，推荐 YT_IMG_BGR_8UC3 / YT_IMG_RGB_8UC3 / YT_IMG_GRAY_8UC1
 * @param[in] face_id 需要追踪的人脸框 ID
 * @param[in] face_rect 追踪的人脸框
 * @param[out] faces 每个框对应的人脸配准点
 * @return YT_SUCCESS：成功
 *         -10000：人脸追踪过程，置信度不满足阈值要求时的失败结果
 *         其他：失败
 */
YT_PUBLIC int Yt_face_alignment_tiny_track_liveness(yt_handle handle, const yt_image image, const int face_id, const yt_rect face_rect, Yt_face_shape_tiny_liveness *face_shape);
// YT_PUBLIC int yt_face_alignment_tiny_track(yt_handle handle, const yt_image image, const int face_id, const yt_rect face_rect,
//                                       yt_face_shape_tiny *face_shape);

// /**
//  * @brief 释放检测结果
//  *
//  * @param[in] yt_face_shape_tiny
//  */
// YT_PUBLIC void yt_face_alignment_tiny_release(yt_face_shape_tiny *face);

/**
 * @brief 重置追踪状态
 *
 * @param[in] handle 实例句柄
 * @return YT_SUCCESS：成功，其他：失败
 */
YT_PUBLIC int Yt_face_alignment_tiny_reset_liveness(yt_handle handle);
// YT_PUBLIC int yt_face_alignment_tiny_reset(yt_handle handle);

/**
 * @brief 人脸透视投影姿态估计接口函数，输出三维角度
 *
 * @param[in] handle 实例句柄
 * @param[in] face_shape 人脸配准点
 * @param[in] focal    摄像头像素焦距，如 600
 * @param[in] center_x 图像中点x，如 image.width / 2
 * @param[in] center_y 图像中点y，如 image.height / 2
 * @param[in] is_deg  true  : 以角度形式输出
 *                    false : 以弧度形式输出
 * @param[out] face_shape_3d 三维角度及3D平移shape
 * @return YT_SUCCESS：成功，其他：失败
 */
YT_PUBLIC int Yt_face_alignment_tiny_get_face_shape_3d_liveness(yt_handle handle, const Yt_face_shape_tiny_liveness face_shape, float focal, float center_x, float center_y, bool is_deg, Yt_face_shape_3d_tiny_liveness *face_shape_3d);
// YT_PUBLIC int yt_face_alignment_tiny_get_face_shape_3d(yt_handle handle, const yt_face_shape_tiny face_shape,
//                                                   float focal, float center_x, float center_y, bool is_deg,
//                                                   yt_face_shape_3d_tiny *face_shape_3d);

#endif  // _YT_FACE_ALIGNMENT_H_
