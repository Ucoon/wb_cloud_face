//
//  WBFaceVerifySDKConfig.h
//  Pods
//
//  Created by pp on 2017/8/2.
//
//

#import <Foundation/Foundation.h>
#import "WBFaceVerifyConst.h"
NS_ASSUME_NONNULL_BEGIN

/**
 人脸识别SDK 基础配置类
 */
@interface WBFaceVerifySDKConfig : NSObject

/*
 是否使用非标模式（具体含义请咨询技术支持）
 ！！！使用原WBCloudFaceVerifySimpleSDK切过来的，务必打开此项
 默认为NO
 */
@property (nonatomic, assign) BOOL useSimpleMode;

#pragma mark - common
/**
 sdk中拉起人脸活体识别界面中使用UIWindow时的windowLevel配置,默认配置是1 + UIWindowLevelNormal

 如果接入放app中有其他自定义UIWindow, 为了防止界面覆盖,可以酌情设置该参数
 */
@property (nonatomic, assign) NSUInteger windowLevel;

/**
 人脸识别服务结果页是否展示配置项 - 是否展示人脸对比成功界面 -> 建议关闭

 default: NO
 */
@property (nonatomic, assign) BOOL showSuccessPage;

/**
 人脸识别服务结果页是否展示配置项 - 是否展示人脸对比失败界面 -> 建议关闭

 default: NO
 */
@property (nonatomic, assign) BOOL showFailurePage;

/**
 人脸识别服务是否进行通过录像, 从而进行视频存证

 default: NO
 */
@property (nonatomic, assign) BOOL recordVideo;

/**
 是否由SDK内部处理sdk网络请求的cookie

 默认值: YES
 */
@property (nonatomic, assign) BOOL manualCookie;

/**
 人脸识别页面中的主题风格, 需要配合不同资源包使用:
 WBFaceVerifyThemeDarkness - 暗灰主题
 WBFaceVerifyThemeLightness - 明亮主题
 */
@property (nonatomic, assign) WBFaceVerifyTheme theme;

/**
 是否静音
 默认值：YES
 */
@property (nonatomic, assign) BOOL mute;

/**
 刷脸服务走iPv6协议栈
 默认：YES
 */
@property (nonatomic, assign) BOOL isIpv6;

/*
 送入自定义提示文案的位置
 默认：WBFaceCustomTipsLoc_Bottom
 */
@property (nonatomic, assign) WBFaceCustomTipsLoc tipsLoc;

/*
 检测过程中展示的文案
 默认为空
 */
@property (nonatomic, copy) NSString *customTipsInDetect;

/*
 上传过程中展示的文案
 默认为空
 */
@property (nonatomic, copy) NSString *customTipsInUpload;

/*
 底部提示文案，长度不超过70字
 */
@property (nonatomic, copy) NSString *bottomCustomTips;

/*
 退出二次确认UI配置
 */
@property (nonatomic, copy) NSString *exitAlertTitle; //标题
@property (nonatomic, copy) NSString *exitAlertMessage; //内容
@property (nonatomic, copy) NSString *exitAlertRight; //右边按钮
@property (nonatomic, copy) NSString *exitAlertLeft; //左边按钮

/*
 如果有使用苹果分屏模式（UIWindowScene），打开此开关
 Xcode11新建工程有使用Scene，可以参考资料自行调整
 默认为NO
 */
@property (nonatomic, assign) BOOL useWindowSecene;

/**
 资源路径，不包含bundle本身（仅当需要自己下发资源时配置，本地资源无需配置）
 ！！！重要：此目录下必须包含face-tracker-v001.bundle和WBCloudReflectionFaceVerify.bundle两个文件，否则无法拉起SDK
 */
@property (nonatomic, copy) NSString *bundlePath;

/**
 是否采用增强比对服务，仅增强接口生效，仅活体服务设置为NO
 默认为 NO
 */
@property (nonatomic, assign) BOOL useAdvanceCompare;

#pragma mark - simple //非标特有字段，标准模式无需设置
/**
 是否返回录制的视频
 
 default: NO
 */
@property (nonatomic, assign) BOOL returnVideo;

/**
 返回视频加密的公钥，如果不配置则不加密
 
 需要recordVideo returnVideo同时为YES，才返回加密的视频内容
 */
@property (nonatomic, copy) NSString *publicKey;

/**
 AES加密需要用到的IV
 */
@property (nonatomic, copy) NSString *aesIV;

#pragma mark -
/**
 默认sdk配置
 */
+(instancetype)sdkConfig;

@end
NS_ASSUME_NONNULL_END
