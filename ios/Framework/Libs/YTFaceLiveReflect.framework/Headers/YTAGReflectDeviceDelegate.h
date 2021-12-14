//
//  YTAGReflectDeviceDelegate.h
//  FaceVideoTest
//
//  Created by CosperYu on 2019/02/28.
//  Copyright © 2019 Tencent. All rights reserved.
//

#ifndef YTAGReflectDeviceDelegate_h
#define YTAGReflectDeviceDelegate_h

@protocol YTAGReflectDeviceDelegate <NSObject>
//设置camera的曝光时间和iso
- (void)setCameraSettings:(long)expTime1000thSec iso:(int)isoValue;
//用于获取iso等摄像头信息，该接口不会进行任何device设置，只会读取device信息;
- (AVCaptureDevice *_Nonnull)getCaptureDevice;
@end

#endif /* YTAGReflectDeviceDelegate_h */
