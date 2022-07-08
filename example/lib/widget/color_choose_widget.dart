import 'package:flutter/material.dart';
import 'package:wb_cloud_face/wb_cloud_face.dart';

import 'KCheckBox.dart';

extension ColorModeExtension on ColorMode {
  String get label {
    switch (this) {
      case ColorMode.black:
        return '黑色';
      case ColorMode.white:
        return '白色';
      case ColorMode.custom:
        return '客户定制';
      default:
        return '';
    }
  }
}

class ColorChooseWidget extends StatefulWidget {
  final ColorMode? colorMode;
  final Function? onColorModeChanged;
  const ColorChooseWidget({
    Key? key,
    this.colorMode,
    this.onColorModeChanged,
  }) : super(key: key);

  @override
  _ColorChooseWidgetState createState() => _ColorChooseWidgetState();
}

class _ColorChooseWidgetState extends State<ColorChooseWidget> {
  ColorMode? _currentColorMode;
  @override
  void initState() {
    super.initState();
    _currentColorMode = widget.colorMode;
  }

  @override
  void didUpdateWidget(covariant ColorChooseWidget oldWidget) {
    super.didUpdateWidget(oldWidget);
    if (_currentColorMode != widget.colorMode) {
      _currentColorMode = widget.colorMode;
    }
  }

  @override
  Widget build(BuildContext context) {
    return Container(
      padding: const EdgeInsets.all(10),
      decoration: const BoxDecoration(
        border: Border(
          top: BorderSide(color: Colors.blueGrey, width: 0.5),
          bottom: BorderSide(color: Colors.blueGrey, width: 0.5),
        ),
      ),
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: <Widget>[
          const Text(
            '选择皮肤',
            style: TextStyle(
              fontSize: 14,
            ),
          ),
          const SizedBox(
            height: 10,
          ),
          Row(
            children: <Widget>[
              _buildChooseWidget(
                ColorMode.black,
                initValue: _currentColorMode == ColorMode.black,
                onChanged: (value) {
                  _colorModeChanged(ColorMode.black);
                },
              ),
              const SizedBox(
                width: 20,
              ),
              _buildChooseWidget(
                ColorMode.white,
                initValue: _currentColorMode == ColorMode.white,
                onChanged: (value) {
                  _colorModeChanged(ColorMode.white);
                },
              ),
              const SizedBox(
                width: 20,
              ),
              _buildChooseWidget(
                ColorMode.custom,
                initValue: _currentColorMode == ColorMode.custom,
                onChanged: (value) {
                  _colorModeChanged(ColorMode.custom);
                },
              ),
            ],
          ),
        ],
      ),
    );
  }

  void _colorModeChanged(ColorMode colorMode) {
    if (_currentColorMode == colorMode) return;
    setState(() {
      _currentColorMode = colorMode;
      widget.onColorModeChanged?.call(_currentColorMode);
    });
  }

  Widget _buildChooseWidget(
    ColorMode colorMode, {
    bool initValue = false,
    Function(bool)? onChanged,
  }) {
    return Row(
      mainAxisSize: MainAxisSize.min,
      children: <Widget>[
        KCheckBox(
          initValue: initValue,
          onChanged: onChanged,
        ),
        const SizedBox(
          width: 4,
        ),
        Text(
          colorMode.label,
          style: const TextStyle(
            fontSize: 14,
          ),
        ),
      ],
    );
  }
}
