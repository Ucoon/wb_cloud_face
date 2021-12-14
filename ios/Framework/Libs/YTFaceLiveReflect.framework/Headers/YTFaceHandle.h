//
//  YTFaceHandle.h
//  FaceVideoTest
//
//  Created by CosperYu on 2019/02/28.
//  Copyright © 2019 Tencent. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DataDef.h"

#import <AVFoundation/AVFoundation.h>

#import <sys/utsname.h>

#import "YTAGReflectDeviceDelegate.h"

#import <CommonCrypto/CommonCrypto.h>


#ifndef YTFaceHandle_h
#define YTFaceHandle_h

//#define YT_ENCODE_REFLECT_DATA

using namespace std;

// Comment this version define avoid redefined and use interfaces instead.
#define YT_FACE_REFLECT_VERSION @"3.7.3"

//活体类型
enum YTLIVETYPE {
    LIVETYPE_REFLECT = 1,   //反光
    LIVETYPE_POSE = 2,      //动作
};

//服务器回调验证
enum YTSERVERCHECK_TYPE {
    YTSERVERCHECK_INPUTPARAM_NULL = -1,     //入参为空
    YTSERVERCHECK_CHECKPASS = 0,            //检测通过
    
    //反光验证使用
    YTSERVERCHECK_REFLECT_FAILED = 1,       //反光验证失败
    YTSERVERCHECK_PICTURE_FAILED = 2,       //防翻拍验证失败
    YTSERVERCHECK_COMPARE_FAILED = 3,       //对比失败
};

enum YTREFLECT_SAFETY_LEVEL {
    YTREFLECT_SAFETY_RECOMMAND    = 0,    //推荐大小，反光上传数据大概500K
    YTREFLECT_SAFETY_LOW          = 1,    //低安全性，上传包体大概300K。若网络环境或者破解要求没那么高的场景使用
    YTREFLECT_SAFETY_HIGH         = 2,    //高安全性，上传包体可能会到2M。微信在用
    
    YTREFLECT_SAFETY_COUNT        = 3
};

/*
 @brief 反光结束时的回调
 @param ret: 反光序列字符串
             0 成功
             -1    调用了clearAG终止反光
             -1491    反光图片序列检验的时候检查不到人脸
             -1493    时间戳数量跟图片数量对不上，通常是sdk内部错误
             -1494    iso变光点时序不正确，通常是sdk内部错误造成
 @param fullPack: 反光结果图
 @param bestImg: 反光过程中的最优图
 */
typedef void (^onFinish)(int ret, YTFullPack fullPack, void* _Nullable bestImgMat);
typedef void (^onDalayCalc)();


/*
 @brief 解析rgb请求
 @param rgbconfig: 解析后的rgb序列
 @param error: 解析产生错误或者服务器回调错误。如果无错误，则为nil
 */
typedef void (^YTRgbconfigParseResult)(NSString* _Nullable rgbconfig, NSError *_Nullable error);
/**
 @brief 反光事件回调接口
 @param rgb 屏幕颜色
 @param light 屏幕亮度
 */
typedef void (^YTReflectEventCallback)(uint argb ,CGFloat light);

/**
@brief 反光SDK日志注册回调
@param level 日志等级 （0 - error， 1 - warn， 2 - info， 3 - error)
@param message 日志信息
 */
typedef void (^OnYTFaceReflectSDKLoggerEventBlock)(int level, NSString * _Nonnull message);

@interface YTFaceHandle : NSObject
#pragma mark - Global Interface
/**
 @brief 日志注册接口
 @param level 日志等级 （0 - error， 1 - warn， 2 - info， 3 - error)
 @param listener 日志回调
 */
+ (void)registerSDKLogger:(int) level withListener:(OnYTFaceReflectSDKLoggerEventBlock _Nullable)listener;
#pragma mark - Life Circle

/**
 @brief 初始化反光实例
 @param appId: 应用的appid，需要在优图后台申请
 */
- (id _Nullable )initWithAppId:(NSString*_Nonnull)appId;
/**
 @brief 反光事件回调注册函数
 @param callback 反光事件回调
 */
- (void)setReflectEvent:(YTReflectEventCallback _Nonnull)callback;
/**
 @brief 获取sdk版本
 @return 返回版本信息
 */
- (const NSString * _Nonnull)getVersion;

/**
 @brief 初始化并且开始反光过程
 @param rgbConfig: 反光序列字符串
 @param device:遵循YTAGReflectDeviceDelegate协议的对象
 @param shapeView: 用于控制屏幕颜色变化的view
 @param onDalayCalc: 开始延迟计算过程
 @param onFinish: 前段反光过程完成，具体返回内容含义参照onFinish定义。回调发生在主线程
 @return error code:
            0 成功
            -1 CP_string格式组成不正确
            -2 device为空
            -3 shapeView为空
            -4 onDalayCalc为空
            -5 onFinish为空
            -1024 授权验证失败
 @warning 1、请在主线程调用
          2、反光活体暂不支持多线程同时使用
 */
- (NSInteger)initAG:(NSString *_Nonnull)rgbConfig
             device:(id<YTAGReflectDeviceDelegate> _Nonnull)device
          shapeView:(UIView* _Nullable)shapeView
        onDalayCalc:(onDalayCalc _Nonnull)onDalayCalc
           onFinish:(onFinish _Nonnull)onFinish
   outputDurationMS:(long &)durationMS;
/**
 @brief 自动生成反光序列
 @return 返回反光序列
 */
- (NSString * _Nonnull)AutoGenRgb:(int)rgbNum mode:(NSString * _Nonnull)mode;
/**
 @brief 反光过程压帧接口
 @param faceImageCrop: 反光开始后的每帧数据
 @param faceAlign: 当前帧的配准结果
 @param timeStamp: 当前帧时间戳
 */
- (void)PushImgSequence:(void*_Nonnull)faceRgbMat faceAlign:(NSMutableArray* _Nonnull)faceAlign timeStamp:(uint64_t)timeStamp;

//终止反光并清理反光数据，调用后如需再次反光，需要重新调用initAG
//可以在反光过程的任意阶段调用，如用户反光过程来电或者其他原因希望结束反光验证时
//正常流程下依然建议使用demo的方式，反光过程进行界面锁定避免用户不必要的操作
- (void)clearAG;

#pragma mark - Settings
//安全性设置，参照 YTSAFETYLEVEL
- (void)setSafety:(YTREFLECT_SAFETY_LEVEL) value;
- (int)getSafety;


#pragma mark - Utility

//检测是否睁眼
//反光开始前需要用户睁眼，以避免沉睡状态下通过了反光验证
- (float) precheckCloseEye:(const NSMutableArray* _Nonnull) att;

////临时存储图的路径（测试用）
//-(void)setSavePath:(NSString* _Nonnull)savePath;

@end

#endif /* YTFaceHandle_h */
