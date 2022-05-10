import 'package:flutter/material.dart';

import 'KCheckBox.dart';

enum ColorMode {
  black,
  white,
  custom,
}

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
  const ColorChooseWidget({
    Key? key,
    this.colorMode,
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
        color: Color(0xFF1b1d1f),
        border: Border(
          top: BorderSide(color: Color(0xFF303133), width: 1.0),
          bottom: BorderSide(color: Color(0xFF303133), width: 1.0),
        ),
      ),
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: <Widget>[
          const Text(
            '选择皮肤',
            style: TextStyle(
              fontSize: 14,
              color: Colors.white54,
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
                  _colorModeChanged(ColorMode.black, value);
                },
              ),
              const SizedBox(
                width: 20,
              ),
              _buildChooseWidget(
                ColorMode.white,
                initValue: _currentColorMode == ColorMode.white,
                onChanged: (value) {
                  _colorModeChanged(ColorMode.white, value);
                },
              ),
              const SizedBox(
                width: 20,
              ),
              _buildChooseWidget(
                ColorMode.custom,
                initValue: _currentColorMode == ColorMode.custom,
                onChanged: (value) {
                  _colorModeChanged(ColorMode.custom, value);
                },
              ),
            ],
          ),
        ],
      ),
    );
  }

  void _colorModeChanged(ColorMode colorMode, bool check) {
    if (check) {
      if (_currentColorMode == colorMode) return;
      setState(() {
        _currentColorMode = colorMode;
      });
    }
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
            color: Colors.white54,
          ),
        ),
      ],
    );
  }
}
