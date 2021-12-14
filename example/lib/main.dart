import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:fluttertoast/fluttertoast.dart';
import 'package:permission_handler/permission_handler.dart';
import 'package:wb_cloud_face/model/wb_cloud_face_params.dart';
import 'package:wb_cloud_face/model/wb_cloud_face_verify_result.dart';
import 'package:wb_cloud_face/wb_cloud_face.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({Key? key}) : super(key: key);

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  final TextEditingController _idNoController = TextEditingController();
  final TextEditingController _nameController = TextEditingController();

  @override
  void initState() {
    super.initState();
    WidgetsBinding.instance?.addPostFrameCallback((timeStamp) {
      _requireCamera();
    });
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('腾讯云人脸核身'),
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
      ),
    );
  }

  void _requireCamera() async {
    final isGranted = await Permission.camera.isGranted;
    if (!isGranted) await Permission.camera.request();
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
    WbCloudFaceParams params = WbCloudFaceParams(
      nonce: 'b112f0a7cb274035b5ca9bdde46b5960',
      userId: '003ecaf667a54774b7a0f995c539c068',
      keyLicence:
          'evncw5yt9V4g5Yqw0+0B+EzKEHNKgKkgJzUS4JLSYpFim/yVh1y0ZMkS4iMPc7FVYGHmbhHRJezeZj1DQJ0CHIssX5IMqeE+nxm+zyjZfaAxFG55E4W0oLT7W9U1b5hCo8Q10a4iayVzT4S9ilRXLyFRHRUjU5cRGHecVf93UNeAJYvwXMzFdsuoV4rb6u94SZzjAYN3DFSlYzY2sK6l5pImuevYwhBmfhdLiMA0QVOXzcmGLl5b+GYHBf90J9tCHroQST1zGf1PIKNy08vqNA9XzxJWJZf2uyfPKsLHUKz1y17Z8me5m3bsxhTP+rqpVFyOsSLQG8TRjxvRj+60EQ==',
      appId: 'TIDAAQ7A',
      order: 'bb2a036047d7411ca8ce716cd609ac06',
      sign: '503A4FC117D419A665BFC7937FCA281C8A6D088F',
      faceId: 'wb0b340f1f034b2aa276ae1eee6eeb00',
    );
    WbCloudFaceVerifyResult res =
        await WbCloudFace.openCloudFaceService(params: params);
    Fluttertoast.showToast(msg: '认证${res.result ? '成功' : '失败'}');
  }
}
