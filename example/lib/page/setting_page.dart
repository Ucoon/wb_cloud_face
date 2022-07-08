import 'package:flutter/material.dart';
import 'package:wb_cloud_face/wb_cloud_face.dart';
import 'package:wb_cloud_face_example/widget/color_choose_widget.dart';
import 'package:wb_cloud_face_example/widget/origin_choose_widget.dart';
import '../util/storage.dart';
import '../widget/KCupertinoSwitch.dart';

class SettingPage extends StatelessWidget {
  const SettingPage({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('设置'),
        centerTitle: true,
        leading: IconButton(
          onPressed: () {
            Navigator.of(context).pop();
          },
          icon: const Icon(
            Icons.arrow_back_ios,
            color: Colors.white,
          ),
        ),
      ),
      body: SingleChildScrollView(
        child: Column(
          children: <Widget>[
            _buildItemSettingWidget(
              '验证成功展示结果页',
              StorageUtil().getBool('showSuccessPage', defValue: false),
              onChanged: (value) {
                StorageUtil().putBool('showSuccessPage', value);
              },
            ),
            _buildItemSettingWidget(
              '验证失败展示结果页',
              StorageUtil().getBool('showFailPage', defValue: false),
              onChanged: (value) {
                StorageUtil().putBool('showFailPage', value);
              },
            ),
            _buildItemSettingWidget(
              '是否录制视频',
              StorageUtil().getBool('videoUpload', defValue: true),
              onChanged: (value) {
                StorageUtil().putBool('videoUpload', value);
              },
            ),
            _buildItemSettingWidget(
              '是否使用ipv6网络',
              StorageUtil().getBool('isIpv6', defValue: false),
              onChanged: (value) {
                StorageUtil().putBool('isIpv6', value);
              },
            ),
            _buildItemSettingWidget(
              '是否开启闭眼检测',
              StorageUtil().getBool('enableCloseEyes', defValue: false),
              onChanged: (value) {
                StorageUtil().putBool('enableCloseEyes', value);
              },
            ),
            _buildItemSettingWidget(
              '是否播放提示语',
              StorageUtil().getBool('playVoice', defValue: true),
              onChanged: (value) {
                StorageUtil().putBool('playVoice', value);
              },
            ),
            ColorChooseWidget(
              colorMode: ColorMode.values.firstWhere((element) =>
                  element.name ==
                  StorageUtil()
                      .getString('colorMode', defValue: ColorMode.black.name)),
              onColorModeChanged: (ColorMode colorMode) {
                StorageUtil().putString('colorMode', colorMode.name);
              },
            ),
            CompareTypeChooseWidget(
              compareType: CompareType.values.firstWhere((element) =>
                  element.name ==
                  StorageUtil().getString('compareType',
                      defValue: CompareType.idCard.name)),
              onCompareTypeChanged: (CompareType compareType) {
                StorageUtil().putString('compareType', compareType.name);
              },
            ),
          ],
        ),
      ),
    );
  }

  Widget _buildItemSettingWidget(
    String label,
    bool initValue, {
    ValueChanged<bool>? onChanged,
  }) {
    return Container(
      padding: const EdgeInsets.all(10),
      decoration: const BoxDecoration(
        border: Border(
          top: BorderSide(color: Colors.blueGrey, width: 0.5),
          bottom: BorderSide(color: Colors.blueGrey, width: 0.5),
        ),
      ),
      child: Row(
        mainAxisSize: MainAxisSize.max,
        mainAxisAlignment: MainAxisAlignment.spaceBetween,
        children: <Widget>[
          Text(
            label,
            style: const TextStyle(
              fontSize: 14,
            ),
          ),
          KCupertinoSwitch(
            initValue: initValue,
            onChanged: onChanged,
          ),
        ],
      ),
    );
  }
}
