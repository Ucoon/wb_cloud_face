# wb_cloud_face

腾讯云基础版人脸核身Flutter插件

[**官方接入文档**](https://cloud.tencent.com/document/product/1007/56811)

安装：

```yaml
dependencies:
  flutter:
    sdk: flutter
  wb_cloud_face: ^x.x.x
```

导入：

```dart
import 'package:wb_cloud_face/model/wb_cloud_face_params.dart';
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
    WbCloudFaceVerifyResult res =
        await WbCloudFace.openCloudFaceService(params: params);
    Fluttertoast.showToast(msg: '认证${res.result ? '成功' : '失败'}');
  }
```

