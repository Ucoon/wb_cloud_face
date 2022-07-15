import 'package:flutter/material.dart';
import 'package:fluttertoast/fluttertoast.dart';
import 'package:wb_cloud_face/wb_cloud_face.dart';
import 'package:wb_cloud_face_example/util/storage.dart';
import 'setting_page.dart';

class HomePage extends StatelessWidget {
  final TextEditingController _idNoController = TextEditingController();
  final TextEditingController _nameController = TextEditingController();

  HomePage({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('腾讯云人脸核身'),
        centerTitle: true,
        actions: <Widget>[
          IconButton(
            icon: const Icon(
              Icons.settings,
              size: 24,
              color: Colors.white,
            ),
            onPressed: () {
              Navigator.of(context).push(MaterialPageRoute(
                builder: (context) => const SettingPage(),
              ));
            },
          ),
        ],
      ),
      body: Stack(
        children: <Widget>[
          Container(
            padding: const EdgeInsets.fromLTRB(16, 16, 16, 0),
            child: Column(
              children: <Widget>[
                _buildDataInputWidget('姓名', '请输入姓名', _nameController),
                const SizedBox(
                  height: 20,
                ),
                _buildDataInputWidget('身份证号', '请输入身份证号码', _idNoController)
              ],
            ),
          ),
          Positioned(
            bottom: 10,
            child: _buildFaceVerifyButton(),
          ),
        ],
      ),
    );
  }

  Widget _buildFaceVerifyButton() {
    return Container(
      color: Colors.white,
      width: 375,
      height: 64,
      padding: const EdgeInsets.symmetric(horizontal: 24, vertical: 10),
      child: MaterialButton(
        child: const Text(
          '进行人脸核验',
          style: TextStyle(
            fontSize: 16,
            color: Colors.lightBlue,
          ),
        ),
        onPressed: () {
          _openCloudFaceService();
        },
      ),
    );
  }

  Widget _buildDataInputWidget(
      String label, String hintText, TextEditingController controller) {
    return Row(
      children: <Widget>[
        SizedBox(
          width: 80,
          child: Text(
            label,
            style: const TextStyle(
              fontSize: 14,
              color: Colors.grey,
            ),
          ),
        ),
        Expanded(
          child: TextFormField(
            keyboardType: TextInputType.text,
            controller: controller,
            style: const TextStyle(
              fontSize: 16,
              color: Colors.black54,
            ),
            decoration: InputDecoration(
              border: InputBorder.none,
              contentPadding: const EdgeInsets.fromLTRB(0, 16, 0, 14),
              hintText: hintText,
              hintStyle: const TextStyle(
                color: Colors.grey,
                fontSize: 14,
              ),
            ),
          ),
        ),
      ],
    );
  }

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
    WbCloudFaceVerifyConfig config = WbCloudFaceVerifyConfig(
      showSuccessPage:
          StorageUtil().getBool('showSuccessPage', defValue: false),
      showFailPage: StorageUtil().getBool('showFailPage', defValue: false),
      colorMode: ColorMode.values.firstWhere((element) =>
          element.name ==
          StorageUtil().getString('colorMode', defValue: ColorMode.black.name)),
      videoUpload: StorageUtil().getBool('videoUpload', defValue: true),
      isIpv6: StorageUtil().getBool('isIpv6', defValue: false),
      enableCloseEyes:
          StorageUtil().getBool('enableCloseEyes', defValue: false),
      playVoice: StorageUtil().getBool('playVoice', defValue: true),
      compareType: CompareType.values.firstWhere((element) =>
          element.name ==
          StorageUtil()
              .getString('compareType', defValue: CompareType.idCard.name)),
    );
    WbCloudFaceVerifyResult res =
        await WbCloudFace.openCloudFaceService(params: params, config: config);
    Fluttertoast.showToast(msg: '认证${res.result ? '成功' : '失败'}');
  }
}
