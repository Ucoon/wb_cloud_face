import 'package:flutter/material.dart';
import 'package:permission_handler/permission_handler.dart';
import 'package:wb_cloud_face_example/page/home_page.dart';

import 'util/storage.dart';

Future<void> main() async {
  //初始化WidgetsBinding.instance单例
  WidgetsFlutterBinding.ensureInitialized();
  // 本地存储初始化
  await StorageUtil().init();
  runApp(const MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({Key? key}) : super(key: key);

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  @override
  void initState() {
    super.initState();
    WidgetsBinding.instance.addPostFrameCallback((timeStamp) {
      _requireCamera();
    });
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: HomePage(),
    );
  }

  void _requireCamera() async {
    final isGranted = await Permission.camera.isGranted;
    if (!isGranted) await Permission.camera.request();
  }
}
