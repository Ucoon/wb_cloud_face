import 'dart:convert';
import 'package:flutter/services.dart';
import 'model/wb_cloud_face_verify_config.dart';
import 'model/wb_cloud_face_params.dart';
import 'model/wb_cloud_face_verify_result.dart';

class WbCloudFace {
  static const MethodChannel _channel = MethodChannel('wb_cloud_face');

  static Future<WbCloudFaceVerifyResult> openCloudFaceService(
    WbCloudFaceParams params, {
    WbCloudFaceVerifyConfig? config,
  }) async {
    final res = await _channel.invokeMethod(
      'openCloudFaceService',
      {
        'params': params.toJson(),
        'config': config?.toJson() ?? WbCloudFaceVerifyConfig().toJson(),
      },
    );
    return wbCloudFaceVerifyResultFromJson(json.encode(res));
  }
}
