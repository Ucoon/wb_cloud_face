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
    this.result = false,
    this.message = '',
  });

  bool result;
  String message;

  factory WbCloudFaceVerifyResult.fromJson(Map<String, dynamic> json) =>
      WbCloudFaceVerifyResult(
        result: json["result"],
        message: json["message"],
      );

  Map<String, dynamic> toJson() => {
        "result": result,
        "message": message,
      };
}
