//
//  TuringCamRiskTask.h
//  TuringShieldCamRisk
//
//  Created by 徐森圣 on 2020/12/2.
//  Copyright © 2020 Tencent Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>


/// 摄像头检测任务
/// @example
/// ```
/// [task queryPostDataWithCompletionHandler:^(NSData * _Nullable data, NSError * _Nullable error) {
///     // error为空时可以用于发送到图灵盾服务器
/// }];
/// ```
@interface TuringCamRiskTask : NSObject

/// 禁止直接创建摄像头检测任务
- (nonnull instancetype)init NS_UNAVAILABLE;

/// 为任务指定要监控的摄像头设备及其相关信息，需要调用`-postWithCompletionHandler:`或者
/// `-queryPostDataWithCompletionHandler`之前调用。
/// @param cameraDevice 受监控的摄像头设备
/// @param session 受监控的摄像会话
/// @param previewLayer 受监控的预览图层
/// @discussion 调用该方法是可选的，但会提升检测的准确性
- (void)monitorCameraWithDevice:(nullable AVCaptureDevice *)cameraDevice session:(nullable AVCaptureSession *)session previewView:(nullable AVCaptureVideoPreviewLayer *)previewLayer;

/// 为任务指定要监控的用户界面，通常是一个用户可操作的视图，例如viewController.view，或者一个按钮
/// @param view 受监控的用户界面
/// @discussion 调用该方法是可选的，但会提升检测的准确性
- (void)monitorView:(nonnull UIView *)view;

/// 请求检测
/// @param completionHandler 请求完成的回调函数。如果正确返回，则result非空，否则error非空
/// @discussion 数据将会直接发送到图灵盾服务器，只是为了便于测试连通性而提供该接口。
- (void)postWithCompletionHandler:(nullable void(^)(NSDictionary<NSString *, id> *_Nullable result, NSError *_Nullable error))completionHandler;

/// 生成用于请求的数据包
/// @param completionHandler 请求完成的回调函数。如果正确返回，则data非空，否则error非空
- (void)queryPostDataWithCompletionHandler:(nonnull void(^)(NSData *_Nullable data, NSError *_Nullable error))completionHandler;

/// 任务的场景ID
@property (nonatomic, copy, readonly, nonnull) NSString *scene;

@end

