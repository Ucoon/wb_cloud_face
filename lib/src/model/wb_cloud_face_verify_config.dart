// To parse this JSON data, do
//
//     final wbCloudFaceVerifyConfig = wbCloudFaceVerifyConfigFromJson(jsonString);

import 'dart:convert';

WbCloudFaceVerifyConfig wbCloudFaceVerifyConfigFromJson(String str) =>
    WbCloudFaceVerifyConfig.fromJson(json.decode(str));

String wbCloudFaceVerifyConfigToJson(WbCloudFaceVerifyConfig data) =>
    json.encode(data.toJson());

class WbCloudFaceVerifyConfig {
  WbCloudFaceVerifyConfig({
    this.showSuccessPage = false,
    this.showFailPage = false,
    this.colorMode = 'black',
    this.videoUpload = true,
    this.isIpv6 = false,
    this.enableCloseEyes = false,
    this.playVoice = true,
    this.compareType = 'idCard',
  });

  bool showSuccessPage;
  bool showFailPage;
  String colorMode;
  bool videoUpload;
  bool isIpv6;
  bool enableCloseEyes;
  bool playVoice;
  String compareType;

  factory WbCloudFaceVerifyConfig.fromJson(Map<String, dynamic> json) =>
      WbCloudFaceVerifyConfig(
        showSuccessPage: json["showSuccessPage"],
        showFailPage: json["showFailPage"],
        colorMode: json["colorMode"],
        videoUpload: json["videoUpload"],
        isIpv6: json["isIpv6"],
        enableCloseEyes: json["enableCloseEyes"],
        playVoice: json["playVoice"],
        compareType: json["compareType"],
      );

  Map<String, dynamic> toJson() => {
        "showSuccessPage": showSuccessPage,
        "showFailPage": showFailPage,
        "colorMode": colorMode,
        "videoUpload": videoUpload,
        "isIpv6": isIpv6,
        "enableCloseEyes": enableCloseEyes,
        "playVoice": playVoice,
        "compareType": compareType,
      };
}
