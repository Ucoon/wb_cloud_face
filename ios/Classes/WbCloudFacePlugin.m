#import "WbCloudFacePlugin.h"
#include <mach/mach_time.h>
#import <objc/runtime.h>
#import <AssetsLibrary/AssetsLibrary.h>
#import <CommonCrypto/CommonCryptor.h>
#import <WBCloudReflectionFaceVerify/WBFaceVerifyCustomerService.h>

@implementation WbCloudFacePlugin
FlutterResult resultFunc;
+ (void)registerWithRegistrar:(NSObject<FlutterPluginRegistrar>*)registrar {
    FlutterMethodChannel* channel = [FlutterMethodChannel
                                     methodChannelWithName:@"wb_cloud_face"
                                     binaryMessenger:[registrar messenger]];
    WbCloudFacePlugin* instance = [[WbCloudFacePlugin alloc] init];
    [registrar addMethodCallDelegate:instance channel:channel];
}

- (void)handleMethodCall:(FlutterMethodCall*)call result:(FlutterResult)result {
    resultFunc = result;
    if ([@"openCloudFaceService" isEqualToString:call.method]) {
        [self setWBVerifyCallBack];
        [self openCloudFaceService:call.arguments[@"params"] config:call.arguments[@"config"]];
    } else {
        result(FlutterMethodNotImplemented);
    }
}

- (void)setWBVerifyCallBack {
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(wbSDKServiceDidFinishedNotification:) name:WBFaceVerifyCustomerServiceDidFinishedNotification object:nil];
}

-(WBFaceVerifySDKConfig *)getSDKSettings:(NSDictionary<NSString*, NSString*>*)_config{
    WBFaceVerifySDKConfig *config = [WBFaceVerifySDKConfig sdkConfig];
    config.showSuccessPage = [_config[@"showSuccessPage"] isEqual: @"1"];
    config.showFailurePage = [_config[@"showFailPage"] isEqual: @"1"];
    config.theme = [_config[@"colorMode"] isEqualToString: @"black"]? WBFaceVerifyThemeDarkness: WBFaceVerifyThemeLightness;
    config.recordVideo = [_config[@"videoUpload"] isEqual: @"1"];
    config.isIpv6 = [_config[@"isIpv6"] isEqual: @"1"];
    config.mute = [_config[@"playVoice"] isEqual: @"1"];
    config.useSimpleMode = NO;
    config.useAdvanceCompare = [_config[@"compareType"] isEqualToString: @"idCard"]? YES : NO ;
    return config;
}

-(void)openCloudFaceService:(NSDictionary<NSString*, NSString*>*)_inputData
                     config:(NSDictionary<NSString*, NSString*>*)_config{
    WBFaceVerifySDKConfig *config = [self getSDKSettings:_config];
    dispatch_async(dispatch_get_main_queue(), ^{
        NSLog(@"wb cloud face %@",@"start verify");
        [[WBFaceVerifyCustomerService sharedInstance]  initSDKWithUserId:_inputData[@"userId"] nonce:_inputData[@"nonce"]  sign:_inputData[@"sign"] appid:_inputData[@"appId"] orderNo:_inputData[@"order"] apiVersion:@"1.0.0" licence:_inputData[@"keyLicence"] faceId:_inputData[@"faceId"] sdkConfig:config success:^{
            [[WBFaceVerifyCustomerService sharedInstance] startWbFaceVeirifySdk];
        } failure:^(WBFaceError * _Nonnull error) {
            NSString *message = [NSString stringWithFormat:@"code: %ld, message %@", error.code, error.desc];
            NSLog(@"wb cloud face error: %@", message);
            NSDictionary *result = @{@"code": @(error.code), @"description": error.desc, @"errorReason":error.reason};
            resultFunc(result);
        }];
    });
}


#pragma mark - WBFaceVerifyCustomerServiceDelegate
-(void)wbSDKServiceDidFinishedNotification:(NSNotification *)noti {
    WBFaceVerifyResult *faceVerifyResult = (WBFaceVerifyResult *)[noti.userInfo objectForKey:@"faceVerifyResult"];
    NSDictionary *verifyResult = [NSDictionary dictionaryWithObjectsAndKeys:@(faceVerifyResult.isSuccess),@"success",faceVerifyResult.sign,@"sign", faceVerifyResult.liveRate, @"liveRate", faceVerifyResult.similarity,@"similarity", faceVerifyResult.userImageString, @"userImageString",faceVerifyResult.orderNo, @"orderNo", nil];
    NSDictionary *result;
    if (faceVerifyResult.isSuccess) {
        result = [NSDictionary dictionaryWithObjectsAndKeys:@200,@"code",@"",@"description",verifyResult,@"verifyResult", nil];
    }else {
        result = [NSDictionary dictionaryWithObjectsAndKeys:@(faceVerifyResult.error.code),@"code",faceVerifyResult.error.desc,@"description",faceVerifyResult.error.reason,@"errorReason", verifyResult, @"verifyResult",nil];
    }
    NSLog(@"wb cloud face result: %@",result);
    resultFunc(result);
}
@end
