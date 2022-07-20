// To parse this JSON data, do
//
//     final wbCloudFaceVerifyResult = wbCloudFaceVerifyResultFromJson(jsonString);

import 'dart:convert';

WbCloudFaceVerifyResult wbCloudFaceVerifyResultFromJson(String str) =>
    WbCloudFaceVerifyResult.fromJson(json.decode(str));

String wbCloudFaceVerifyResultToJson(WbCloudFaceVerifyResult data) =>
    json.encode(data.toJson());

class WbCloudFaceVerifyResult {
  WbCloudFaceVerifyResult({
    this.code = -1,
    this.description = '',
    this.errorReason = '',
    this.verifyResult,
  });

  int code; //错误码：code == 200代表成功
  String description; //说明
  String errorReason; //错误原因
  Map<String, dynamic>? verifyResult; //核验结果

  bool get succeed => code == 200;

  factory WbCloudFaceVerifyResult.fromJson(Map<String, dynamic> json) =>
      WbCloudFaceVerifyResult(
        code: json["code"],
        description: json["description"],
        errorReason: json["errorReason"],
        verifyResult: json["verifyResult"],
      );

  Map<String, dynamic> toJson() => {
        "result": code,
        "description": description,
        "errorReason": errorReason,
        "verifyResult": verifyResult,
      };
}
