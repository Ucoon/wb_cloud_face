//
//  CamRisk.h
//  CamRisk
//
//  Created by 徐森圣 on 2020/12/1.
//  Copyright © 2020 Tencent Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <TuringShieldCamRisk/TuringCamRiskTask.h>
#import <TuringShieldCamRisk/TuringCamRiskService.h>



/**
!!!: 一、服务概览
    本服务旨在对摄像头风险进行识别。由于识别引擎和预测模型均在云端，因此大多数服务均为异步接口。
 
!!!: 二、主要接口介绍
        
      TuringCamRiskService
             |
             |  创建检测任务
             |
             v
      TuringCamRiskTask
             |
             | 产生请求数据
             v
          NSData
 
    更多的信息请参阅 TuringCamRiskService.h 和 TuringCamRiskTask.h中的注释
 
 !!!: 三、一般使用范例
    ```objective-c
     // 为服务配置上下文（可用的key有多个，这里只简单例举一个，参见TuringCamRiskContextKey中的枚举字符串）
     [[TuringCamRiskService sharedService] setupContext:@{ TuringCamRiskContextAppIDKey: @"F.R.D." }];

     // 创建一个检测任务
     TuringCamRiskTask *task = [[TuringCamRiskService sharedService] taskForSceneID:nil];
     // 为任务指定监控的视图，检测群控风险（此动作可选）
     [task monitorView:[UIApplication sharedApplication].keyWindow];
     // 为任务指定监控的摄像头设备，检测劫持风险（注意请提供正在使用的设备；此动作可选）
     [task monitorCameraWithDevice:cameraDevice session:captureSession previewView:previewLayer];
     // 获取用于请求的数据
     [task queryPostDataWithCompletionHandler:^(NSData * _Nullable data, NSError * _Nullable error) {
         // 如果成功，data非空，error为空；如果失败，data为空，error非空
         // data可用于http post直接请求图灵盾服务
         NSLog(@"data = %@, error = %@", error);
     }];
    ```
 */
