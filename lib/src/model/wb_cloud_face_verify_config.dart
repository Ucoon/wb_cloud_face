import 'dart:convert';
import 'package:wb_cloud_face/src/model/enum.dart';

WbCloudFaceVerifyConfig wbCloudFaceVerifyConfigFromJson(String str) =>
    WbCloudFaceVerifyConfig.fromJson(json.decode(str));

String wbCloudFaceVerifyConfigToJson(WbCloudFaceVerifyConfig data) =>
    json.encode(data.toJson());

class WbCloudFaceVerifyConfig {
  WbCloudFaceVerifyConfig({
    this.showSuccessPage = false,
    this.showFailPage = false,
    this.colorMode = ColorMode.black,
    this.videoUpload = true,
    this.isIpv6 = false,
    this.enableCloseEyes = false,
    this.playVoice = true,
    this.compareType = CompareType.idCard,
  });

  bool showSuccessPage; //是否展示刷脸成功页面，默认不展示
  bool showFailPage; //是否展示刷脸失败页面，默认不展示
  ColorMode colorMode; //颜色设置，默认黑色
  bool videoUpload; //是否需要录制上传视频，默认需要
  bool isIpv6; //是否使用ipv6网络，默认不使用
  bool enableCloseEyes; //是否开启闭眼检测，默认不开启
  bool playVoice; //是否播放提示音，默认播放
  CompareType compareType; //比对类型，默认为公安网纹图片对比

  factory WbCloudFaceVerifyConfig.fromJson(Map<String, dynamic> json) =>
      WbCloudFaceVerifyConfig(
        showSuccessPage: json["showSuccessPage"],
        showFailPage: json["showFailPage"],
        colorMode: ColorMode.values
            .firstWhere((element) => element.name == json["colorMode"]),
        videoUpload: json["videoUpload"],
        isIpv6: json["isIpv6"],
        enableCloseEyes: json["enableCloseEyes"],
        playVoice: json["playVoice"],
        compareType: CompareType.values
            .firstWhere((element) => element.name == json["compareType"]),
      );

  Map<String, dynamic> toJson() => {
        "showSuccessPage": showSuccessPage,
        "showFailPage": showFailPage,
        "colorMode": colorMode.name,
        "videoUpload": videoUpload,
        "isIpv6": isIpv6,
        "enableCloseEyes": enableCloseEyes,
        "playVoice": playVoice,
        "compareType": compareType.name,
      };
}
