# wb_cloud_face

腾讯云基础版人脸核身Flutter插件

[**官方接入文档**](https://cloud.tencent.com/document/product/1007/56811)

安装：

```yaml
dependencies:
  flutter:
    sdk: flutter
  wb_cloud_face:
    git:
      url: https://github.com/Ucoon/wb_cloud_face.git
      ref: master
```

导入：

```dart
import 'package:wb_cloud_face/wb_cloud_face.dart';
```

使用：

```dart
  void _openCloudFaceService() async {
    ///这些都是 WbCloudFaceVerifySdk.InputData 对象里的字段，是需要传入的数据信息
    WbCloudFaceParams params = WbCloudFaceParams(
      nonce: '', //32位随机字符串
      userId: '', //user id
      keyLicence: '', //在人脸核身控制台内申请
      appId: '', //APP_ID
      order: '', //订单号
      sign: '', //签名信息
      faceId: '', //此次刷脸用户标识，合作方需要向人脸识别后台拉取获得，详见获取 faceId 接口
    );
    WbCloudFaceVerifyConfig config = WbCloudFaceVerifyConfig(
      showSuccessPage:
          StorageUtil().getBool('showSuccessPage', defValue: false),
      showFailPage: StorageUtil().getBool('showFailPage', defValue: false),
      colorMode: ColorMode.values.firstWhere((element) =>
          element.name ==
          StorageUtil().getString('colorMode', defValue: ColorMode.black.name)),
      videoUpload: StorageUtil().getBool('videoUpload', defValue: true),
      isIpv6: StorageUtil().getBool('isIpv6', defValue: false),
      enableCloseEyes:
          StorageUtil().getBool('enableCloseEyes', defValue: false),
      playVoice: StorageUtil().getBool('playVoice', defValue: true),
      compareType: CompareType.values.firstWhere((element) =>
          element.name ==
          StorageUtil()
              .getString('compareType', defValue: CompareType.idCard.name)),
    );
    WbCloudFaceVerifyResult res =
        await WbCloudFace.openCloudFaceService(params, config: config);
    Fluttertoast.showToast(msg: '认证${res.result ? '成功' : '失败'}');
  }
```

注意事项：

1. iOSSDK 依赖以下系统框架，需要在**BuildPhases**>**Link Binary With Libraries**中添加，可以参考 example，具体依赖的系统库如下：

   ```dart
   libz.tbd
   libc++.tbd
   UIKit.framewrok
   WebKit.framewrok
   ImageIO.framework
   Security.framework
   CoreVideo.framework
   CoreMedia.framework
   Accelerate.framework
   AVFoundation.framework
   CoreTelephony.framework 
   SystemConfiguration.framework
   ```

   
