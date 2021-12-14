//
//  YTBrightnessManager.h
//  YTFaceLiveReflect
//
//  Created by CosperYu on 2019/01/03.
//  Copyright © 2019年 Patrick Yang. All rights reserved.
//

#import <Foundation/Foundation.h>

#include <vector>

NS_ASSUME_NONNULL_BEGIN

@protocol YTOnGetBrightness <NSObject>
-(void)onGetBrightness:(float)brightness;   //获取到光线强度
-(void)getBrightnessOverTime;   //获取超时
@end

@class BrightnessDevice;

@interface YTBrightnessManager : NSObject {
    std::vector<float> vec;
}

@property (nonatomic, weak) id<YTOnGetBrightness> onGetBrightnessDelegate;
@property (nonatomic, strong, nullable) BrightnessDevice *brightnessDevice;
@property (nonatomic, strong, nullable) NSTimer *timer;
//@property (nonatomic, assign) std::vector<float> vec;
@property (nonatomic, assign) int recordCount;


+ (NSDictionary*)getUploadDic:(float)brightnessValue;

//overTime 超时时间（单位:ms），超时后回调getBrightnessOverTime。
//启动后会调用前置摄像头传感设备获取信息，如果当前正在使用前置摄像头可能会造成短时间（7plus上1秒内）的显示卡顿
- (int)getBrightness:(id<YTOnGetBrightness>)onGetBrightness overTime:(NSTimeInterval)overTime;

@end

NS_ASSUME_NONNULL_END
