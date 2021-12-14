// To parse this JSON data, do
//
//     final wbCloudFaceParams = wbCloudFaceParamsFromJson(jsonString);

import 'dart:convert';

WbCloudFaceParams wbCloudFaceParamsFromJson(String str) =>
    WbCloudFaceParams.fromJson(json.decode(str));

String wbCloudFaceParamsToJson(WbCloudFaceParams data) =>
    json.encode(data.toJson());

class WbCloudFaceParams {
  WbCloudFaceParams({
    this.nonce = '',
    this.userId = '',
    this.keyLicence = '',
    this.appId = '',
    this.order = '',
    this.sign = '',
    this.faceId = '',
  });

  String nonce;
  String userId;
  String keyLicence;
  String appId;
  String order;
  String sign;
  String faceId;

  factory WbCloudFaceParams.fromJson(Map<String, dynamic> json) =>
      WbCloudFaceParams(
        nonce: json["nonce"],
        userId: json["userId"],
        keyLicence: json["keyLicence"],
        appId: json["appId"],
        order: json["order"],
        sign: json["sign"],
        faceId: json["faceId"],
      );

  Map<String, dynamic> toJson() => {
        "nonce": nonce,
        "userId": userId,
        "keyLicence": keyLicence,
        "appId": appId,
        "order": order,
        "sign": sign,
        "faceId": faceId,
      };
}
