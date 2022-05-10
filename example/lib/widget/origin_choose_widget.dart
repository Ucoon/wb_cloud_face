import 'package:flutter/material.dart';

import 'KCheckBox.dart';

enum OriginMode {
  idCard,
  face,
}

extension OriginModeExtension on OriginMode {
  String get label {
    switch (this) {
      case OriginMode.idCard:
        return '身份证对比';
      case OriginMode.face:
        return '仅活体检测';
      default:
        return '';
    }
  }
}

class OriginChooseWidget extends StatefulWidget {
  final OriginMode? originMode;
  const OriginChooseWidget({
    Key? key,
    this.originMode,
  }) : super(key: key);

  @override
  _OriginChooseWidgetState createState() => _OriginChooseWidgetState();
}

class _OriginChooseWidgetState extends State<OriginChooseWidget> {
  OriginMode? _currentOriginMode;
  @override
  void initState() {
    super.initState();
    _currentOriginMode = widget.originMode;
  }

  @override
  void didUpdateWidget(covariant OriginChooseWidget oldWidget) {
    super.didUpdateWidget(oldWidget);
    if (_currentOriginMode != widget.originMode) {
      _currentOriginMode = widget.originMode;
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
            '选择对比源',
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
                OriginMode.idCard,
                initValue: _currentOriginMode == OriginMode.idCard,
                onChanged: (value) {
                  _originModeChanged(OriginMode.idCard, value);
                },
              ),
              const SizedBox(
                width: 20,
              ),
              _buildChooseWidget(
                OriginMode.face,
                initValue: _currentOriginMode == OriginMode.face,
                onChanged: (value) {
                  _originModeChanged(OriginMode.face, value);
                },
              ),
            ],
          ),
        ],
      ),
    );
  }

  void _originModeChanged(OriginMode originMode, bool check) {
    if (check) {
      if (_currentOriginMode == originMode) return;
      setState(() {
        _currentOriginMode = originMode;
      });
    }
  }

  Widget _buildChooseWidget(
    OriginMode originMode, {
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
          originMode.label,
          style: const TextStyle(
            fontSize: 14,
            color: Colors.white54,
          ),
        ),
      ],
    );
  }
}
