//
//  WBFaceVerifyResult.h
//  Pods
//
//  Created by pp on 2017/8/22.
//
//

#import <UIKit/UIKit.h>
#import "WBFaceError.h"
#import "WBFaceVerifyConst.h"

@interface WBFaceSimpleModeResult : NSObject

/**
 结果对应的订单号
 */
@property (nonatomic, copy, readonly) NSString *orderNo;

/**
 接下来用于人脸对比的安全性参数
 */
@property (nonatomic, copy, readonly) NSString *encryptAESKey;

/**
 视频编码
 */
@property (nonatomic, copy, readonly) NSString *userVideoString;

/**
 使用传入publickey加密过的AES
 */
@property (nonatomic, copy, readonly) NSString *videoEncryptAESKey;
/**
 用于后面进行人脸比对的数据参数
 */
@property (nonatomic, copy, readonly) NSString *identifyStr;

@end

/*
 增强级结果，具体参数含义参考后台返回字段，结果为透传
 */
@interface WBFaceRiskInfo : NSObject
@property (nonatomic, copy, readonly) NSString *deviceInfoLevel;
@property (nonatomic, copy, readonly) NSString *deviceInfoTag;
@property (nonatomic, copy, readonly) NSString *riskInfoLevel;
@property (nonatomic, copy, readonly) NSString *riskInfoTag;
@end
/**
 人脸服务返回结果对象
 */
@interface WBFaceVerifyResult : NSObject
/**
 人脸比对结果是否通过:

 YES: 表示人脸服务通过
 NO:  表示人脸服务不通过lo
 */
@property (nonatomic, assign, readonly) BOOL isSuccess;

/**
 结果对应的订单号
 */
@property (nonatomic, copy, readonly) NSString *orderNo;

/**
 isSuccess == YES 时, sign有值, 通过该sign可以去后台拉取本次人脸服务的照片,视频存证
 isSuccess == NO  时, sign 无意义
 */
@property (nonatomic, copy, readonly) NSString * sign;

/**
 活体检测服务得分

 isSuccess == YES 时, liveRate 有值:
        1. liveRate 可能是 @"分数为空", 这种情况具体咨询合作方
        2. float类型的字符串, 请调用 [liveRate floatValue] 获取具体分数
 isSuccess == NO  时, liveRate 无意义
 */
@property (nonatomic, copy, readonly) NSString * liveRate;

/**
 人脸比对服务得分

 isSuccess == YES 时, similarity 有值:
         1. similarity 可能是 @"分数为空", 这种情况具体咨询合作方
         2. float类型的字符串, 请调用 [similarity floatValue] 获取具体分数
 isSuccess == NO  时, similarity 无意义
 */
@property (nonatomic, copy, readonly) NSString * similarity;

/**
 人脸比对图片之一

 isSuccess == YES 时, 该属性是上送比对图片之一UIImage的base64编码字符串(图片格式是jpg)

 isSuccess == NO  时, 该属性为nil
 */
@property (nonatomic, copy, readonly) NSString * userImageString;

/**
 isSuccess == YES 时候, error 无意义
 isSuccess == NO  时, error中存储的具体错误信息,参考 WBFaceError.h
 */
@property (nonatomic, strong, readonly) WBFaceError * error;

#pragma mark - 非标专用返回参数

@property (nonatomic, strong, readonly) WBFaceSimpleModeResult *simpleModeResult;

#pragma mark - 增强SDK专用参数
@property (nonatomic, strong, readonly) WBFaceRiskInfo *riskInfo;

#pragma mark -

-(NSString *)description;
@end
