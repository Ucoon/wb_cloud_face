import 'package:flutter/material.dart';
import 'package:wb_cloud_face_example/widget/color_choose_widget.dart';
import 'package:wb_cloud_face_example/widget/origin_choose_widget.dart';
import 'widget/KCupertinoSwitch.dart';

class SettingPage extends StatelessWidget {
  const SettingPage({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: const Color(0xFF181a1c),
      appBar: AppBar(
        centerTitle: true,
        backgroundColor: const Color(0xFF181a1c),
        title: const Text(
          '设置',
          style: TextStyle(
            fontSize: 16,
            fontWeight: FontWeight.w400,
            color: Colors.white,
          ),
        ),
        leading: IconButton(
          onPressed: () {},
          icon: const Icon(
            Icons.arrow_back_ios,
            color: Colors.white,
          ),
        ),
      ),
      body: SingleChildScrollView(
        child: Column(
          children: <Widget>[
            _buildItemSettingWidget('验证成功展示结果页'),
            _buildItemSettingWidget('验证失败展示结果页'),
            _buildItemSettingWidget('是否录制视频'),
            _buildItemSettingWidget('是否播放提示语'),
            const ColorChooseWidget(),
            const OriginChooseWidget(),
          ],
        ),
      ),
    );
  }

  Widget _buildItemSettingWidget(
    String label, {
    ValueChanged<bool>? onChanged,
  }) {
    return Container(
      padding: const EdgeInsets.all(10),
      decoration: const BoxDecoration(
        color: Color(0xFF1b1d1f),
        border: Border(
          top: BorderSide(color: Color(0xFF303133), width: 1.0),
          bottom: BorderSide(color: Color(0xFF303133), width: 1.0),
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
              color: Colors.white54,
            ),
          ),
          KCupertinoSwitch(
            initValue: false,
            onChanged: onChanged,
          ),
        ],
      ),
    );
  }
}
