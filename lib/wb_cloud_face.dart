import 'dart:convert';
import 'package:flutter/services.dart';
import 'model/wb_cloud_face_params.dart';
import 'model/wb_cloud_face_verify_result.dart';

class WbCloudFace {
  static const MethodChannel _channel = MethodChannel('wb_cloud_face');

  static Future<WbCloudFaceVerifyResult> openCloudFaceService({
    required WbCloudFaceParams params,
  }) async {
    final res = await _channel.invokeMethod(
        'openCloudFaceService', params.toJson());
    return WbCloudFaceVerifyResult.fromJson(json.decode(res));
  }
}
