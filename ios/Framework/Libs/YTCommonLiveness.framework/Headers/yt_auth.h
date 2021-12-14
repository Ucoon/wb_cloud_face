/**
 * @file yt_auth.h
 * @author tencent
 * @brief 鉴权接口
 * @version 2.0
 * @date 2020-09-10
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef _YT_AUTH_H_
#define _YT_AUTH_H_

#include "yt_defines.h"

// license文件申请：https://docs.qq.com/doc/DZERXWmNYeVNyWlF0

/**
 * @brief 使用license文件初始化授权
 * @param `platform_context` Android平台输入JNIEnv*；其他平台输入NULL
 * @param `license_path` Android平台将license文件打包到assets中，传入文件名；其他平台传入文件完整路径
 * @param `secret_key` 传入license对应的secret_key，在申请的时候获得
 * @return 授权结果，0代表成功，错误码参考：[授权错误代码](#errorcode)
 */
YT_PUBLIC int ytliveness_auth_init_by_path(void* platform_context, const char* license_path, const char* secret_key);

/**
 * @brief 使用license字符串初始化鉴权，字符串获取方式：将license文件做base64即可
 * @param `platform_context` Android平台输入JNIEnv*；其他平台输入NULL
 * @param `license_string` license字符串
 * @param `secret_key` 传入license对应的secret_key，在申请的时候获得
 * @return 授权结果，0代表成功，错误码参考：[授权错误代码](#errorcode)
 */
YT_PUBLIC int ytliveness_auth_init_by_string(void* platform_context, const char* license_string, const char* secret_key);

/**
 * @brief 从url拉取授权文件，并缓存在本地，后面通过本地缓存来授权；如果本地授权过期，会重新到url拉取
 * @param `platform_context` Android平台输入JNIEnv*；其他平台输入NULL
 * @param `url`, 拉取授权的接口，一般为：https://license.youtu.qq.com/youtu/sdklicenseapi/license_generate
 * @param `cache_path`，缓存授权文件的外部路径，必须拥有写权限
 * @param `appid`, 拉取授权用的appid，用于认证，申请绑定设备授权时获得
 * @param `secret_key` 拉取授权用的secret_key，用于认证，申请绑定设备授权时获得
 * @return 授权结果，0代表成功，错误码参考：[授权错误代码](#errorcode)
*/
YT_PUBLIC int ytliveness_auth_init_online_with_cache(void* platform_context, const char* url, const char* cache_path, const char* appid, const char* secret_key);

/**
 * @brief 获取设备信息，用于绑定设备的授权
 * @param `platform_context` Android平台输入JNIEnv*；其他平台输入NULL
 * @param `out_device_id` 输出device_id，是每台设备的唯一编码
 * @param `inout_device_id_len` 如out_device_id为NULL，输出device_id的字符串长度；如out_device_id不为NULL，输入out_device_id的最大长度
 * @param `out_device_info` 输出device_info，是设备完整信息的加密字符串
 * @param `inout_device_info_len` 如out_device_info为NULL，输出device_info的字符串长度；如out_device_info不为NULL，输入out_device_info的最大长度
 * @return 获取设备信息结果，错误码参考：[授权错误代码](#errorcode)
 */
YT_PUBLIC int ytliveness_auth_get_device_info(void* platform_context, char* out_device_id, int* inout_device_id_len, char* out_device_info, int* inout_device_info_len);

/**
 * @brief 腾讯内部业务专用授权接口
 * @param `platform_context` Android平台输入JNIEnv*；其他平台输入NULL
 * @return 授权结果，0代表成功，错误码参考：[授权错误代码](#errorcode)
 */
YT_PUBLIC int ytliveness_auth_init_for_qq(void* platform_context);

/**
 * @brief 授权成功后，查询授权有效期
 * @return 授权到期时间的时间戳
 */
YT_PUBLIC long long ytliveness_auth_get_endtime();

/**
 * @brief 查询授权库的版本
 * @return 授权库的版本号
 */
YT_PUBLIC const char* ytliveness_auth_get_version();

/**
 * @brief 获取已授权的SDK列表
 * @param sdklist_buf 出参，返回sdklist，调用者自己分配一个int[]数组用于存储SDKlist
 * @param max_count 入参，传入的sdklist_buf的最大index
 * @return 实际返回的sdklist数量
 * @note 如果sdklist_buf传NULL，返回值代表SDK列表的总数
 */
YT_PUBLIC int ytliveness_auth_get_sdklist_ids(int* sdklist_buf, int max_count);

/**
 * @brief 获取sdk_id代表的SDK名称
 * @param sdk_id 
 * @return 该id代表的SDK名称
 */
YT_PUBLIC const char* ytliveness_auth_get_sdkname(int sdk_id);


/**
 * @brief 设置是否显示log，默认为显示
 * @param enable，1-显示   0-不显示
 * @return 
 */
YT_PUBLIC void ytliveness_auth_enable_log(int enable);

#endif
