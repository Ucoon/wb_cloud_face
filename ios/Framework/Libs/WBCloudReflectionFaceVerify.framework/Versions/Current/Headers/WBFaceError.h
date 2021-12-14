//
//  WBFaceError.h
//  Pods
//
//  Created by pp on 2017/8/15.
//
//

#import <UIKit/UIKit.h>
/*
 Domain(错误出现的地方)                    Code        Desc(描述)                                  Reason(详细实际原因)
 WBFaceErrorDomainInputParams           12000     传入参数为空                               传入的xx为空
                                        12001     传入的keyLicence不可用                     传入的keyLicence不可用
                                        12002     身份证格式不正确                            身份证格式不正确
                                        12003     使用自带对比源,传入参数错误,非base64          传入的srcPhotoString不是base64
                                        12004     使用自带对比源,传入参数错误,超过3M            传入的srcPhotoString超过3M
                                        12005     sdk资源引入版本不匹配                       没有引入资源包或者引入的资源包版本与当前SDK版本不匹配
                                        12006     订单号不能为0或者超过32位
                                        12007     nonce字符串位数不为32
                                        12008     faceid不合法，需要保证faceid与接口对应

 WBFaceErrorDomainLoginNetwork          22100     网络异常                                   登陆时网络异常（请求未到达后台）
                                        22200     网络异常                                   登陆时后台返回参数有误（请求到达后台）

 WBFaceErrorDomainLoginServer           其他       透传后台错误码(请参考后台错误)                例如签名问题等等


 WBFaceErrorDomainGetInfo               32100      网络异常                                   获取数字/活体类型/光线阈值，网络异常(请求未到达后台)
                                        32200      网络异常                                   获取数字/活体类型/光线阈值，后台返回参数有误(请求到达后台)


 WBFaceErrorDomainNativeProcess         42000     用户取消                                    回到后台/点击home/左上角/上传时左上角 取消
                                        42001     网络环境不满足认证需求                        无网络/2g网络
                                        42002     权限异常，未获取权限                           相机/麦克风/read phone/external storage
                                        42003     相机运行中出错
                                        42004     视频录制中出错                                不能存/启动失败/结束失败
                                        42005     请勿晃动人脸,保持姿势                          未获取到最佳图片
                                        42006     视频大小不满足要求                             视频大小不满足要求
                                        42007     超时                                         预检测/动作活体
                                        42008     检测中人脸移出框外                             活体/数字/反光
                                        42009     光线活体本地错误
                                        42010     风险控制超出次数                               用户重试太多次
                                        42011     没有检测到读数声音                             数字活体过程中没有发声
                                        42012     模型初始化失败
                                        42015     报文解密失败
 WBFaceErrorDomainCompareNetwork        52100    网络异常                                    对比时，网络异常（请求未到达后台）
                                        52200    网络异常                                    对比时，后台返回参数有误（请求到达后台）

 WBFaceErrorDomainCompareServer         其他      透传后台错误码
*/
NS_ASSUME_NONNULL_BEGIN

/*
 错误domain划分成两类:

 1. 出现在登录时, 通过调用startXXXX 方法的failure block进行回调返回:
 WBFaceErrorDomainInputParams, WBFaceErrorDomainLoginNetwork, WBFaceErrorDomainLoginServer


 2. 人脸服务结果返回(封装在WBFaceVerifyResult中):
 WBFaceErrorDomainGetInfo, WBFaceErrorDomainNativeProcess, WBFaceErrorDomainCompareNetwork, WBFaceErrorDomainCompareServer
 */

/* 登录时传入参数有误 */
UIKIT_EXTERN NSString *const WBFaceErrorDomainInputParams;
/* 登录时网络请求错误 */
UIKIT_EXTERN NSString *const WBFaceErrorDomainLoginNetwork;
/* 登录时后台拒绝登录, 具体参考后台word版本错误码, 这里直接透传 */
UIKIT_EXTERN NSString *const WBFaceErrorDomainLoginServer;
/* 拉取有效信息时候网络错误 */
UIKIT_EXTERN NSString *const WBFaceErrorDomainGetInfo;
/* native本地在活体检测中, 某些原因导致错误 */
UIKIT_EXTERN NSString *const WBFaceErrorDomainNativeProcess;
/* 上送后台比对时,网络错误 */
UIKIT_EXTERN NSString *const WBFaceErrorDomainCompareNetwork;
/* 后台比对完成,返回比对结果的错误原因*/
UIKIT_EXTERN NSString *const WBFaceErrorDomainCompareServer;

@interface WBFaceError: NSObject
/**
 错误发生的地方, 具体的发生地方由上面定义的 WBFaceErrorDomainXXXX 指定
 */
@property (nonatomic, readonly, copy) NSString *domain;
/**
 每个domain中有相应的错误代码, 具体的错误代码见
 */
@property (nonatomic, readonly, assign) NSInteger code; //错误代码
@property (nonatomic, readonly, copy) NSString *desc; //获取本地化描述
@property (nonatomic, readonly, copy) NSString *reason; // 错误出现的真实原因原因
@property (nonatomic, readonly, copy) NSDictionary * _Nullable otherInfo;// 预留接口


+ (instancetype)errorWithDomain:(NSString *)domain code:(NSInteger)code desc:(NSString *)desc;
+ (instancetype)errorWithDomain:(NSString *)domain code:(NSInteger)code desc:(NSString *)desc reason:(NSString *)reason;
+ (instancetype)errorWithDomain:(NSString *)domain code:(NSInteger)code desc:(NSString *)desc reason:(NSString *)reason otherInfo:(nullable NSDictionary *)otherInfo;

@end

NS_ASSUME_NONNULL_END
