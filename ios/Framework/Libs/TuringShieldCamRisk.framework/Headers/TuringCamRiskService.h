//
//  TuringCamRiskService.h
//  TuringShieldCamRisk
//
//  Created by 徐森圣 on 2020/12/2.
//  Copyright © 2020 Tencent Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <TuringShieldCamRisk/TuringCamRiskTask.h>






/// 这些常量值用于设置或获取context中的字典数据中的key。
typedef NSString * TuringCamRiskContextKey NS_EXTENSIBLE_STRING_ENUM;

/// 用于设置请求序列编号的key，参见 `TuringCamRiskContextKey`。该key对应的值应为 NSString *。
extern TuringCamRiskContextKey const _Nonnull TuringCamRiskContextRequestSequenceKey;

/// 用于设置meta data的key，参见 `TuringCamRiskContextKey`。该key对应的值应为 NSString *。
extern TuringCamRiskContextKey const _Nonnull TuringCamRiskContextMetaDataKey;

/// 用于设置接入渠道号的key，参见 `TuringCamRiskContextKey`。该key对应的值应为 NSString *。
extern TuringCamRiskContextKey const _Nonnull TuringCamRiskContextChannelKey;

/// 用于设置接入构建号的key，参见 `TuringCamRiskContextKey`。该key对应的值应为 NSNumber *。
extern TuringCamRiskContextKey const _Nonnull TuringCamRiskContextBuildNoKey;

/// 用于设置接入版本号的key，参见 `TuringCamRiskContextKey`。该key对应的值应为 NSString *。
extern TuringCamRiskContextKey const _Nonnull TuringCamRiskContextVersionKey;

/// 用于设置接入版本LC的key，参见 `TuringCamRiskContextKey`。该key对应的值应为 NSString *。
extern TuringCamRiskContextKey const _Nonnull TuringCamRiskContextLCKey;

/// 用于设置其它额外信息的key，参见 `TuringCamRiskContextKey`。该key对应的值应为 NSString *。
extern TuringCamRiskContextKey const _Nonnull TuringCamRiskContextExtraInfoKey;

/// 用于设置接入App ID的key，参见 `TuringCamRiskContextKey`。该key对应的值应为 NSString *。
extern TuringCamRiskContextKey const _Nonnull TuringCamRiskContextAppIDKey;


@interface TuringCamRiskService : NSObject

/// 禁止直接生成实例
- (nonnull instancetype)init NS_UNAVAILABLE;

/// 所有服务均以此单例提供
+ (nonnull instancetype)sharedService;

/// 设置调用相关的上下文。字典中用到的key，请参考`TuringCamRiskContextKey`及其常量定义
- (void)setupContext:(nonnull NSDictionary<TuringCamRiskContextKey, id> *)context;

/// 生成一个摄像头检测任务并接受TuringCamRiskService的管理。如果相同sceneIDID的任务已经生成，则会
/// 返回同一个任务实例，直到该实例被`- detatchTask:`释放。
/// @param sceneID 摄像头检测任务的场景ID
/// @discussion 如果sceneID为空，则该任务不会被TuringCamRiskService管理，也不需要调用
/// `- detatchTask:`释放
- (nonnull TuringCamRiskTask *)taskForSceneID:(nullable NSString *)sceneID;

/// 释放一个摄像头检测任务
/// @param task 要释放的任务实例
- (void)detatchTask:(nonnull TuringCamRiskTask *)task;

+ (nonnull NSDictionary *)SDKInfo;

@end

@interface TuringCamRiskService (Debugging)

/// 设置是否使用测试服务器
/// @discussion 注意只能在未使用任何 TuringCamRiskService 的服务之前设置，否则某些正在进行中的
/// 服务可能会出现错误
@property (class, nonatomic) BOOL usesDebugServer;

@end
