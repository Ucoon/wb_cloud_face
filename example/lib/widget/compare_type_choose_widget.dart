import 'package:flutter/material.dart';
import 'package:wb_cloud_face/wb_cloud_face.dart';
import 'KCheckBox.dart';

extension CompareTypeExtension on CompareType {
  String get label {
    switch (this) {
      case CompareType.idCard:
        return '身份证对比';
      case CompareType.none:
        return '仅活体检测';
      default:
        return '';
    }
  }
}

class CompareTypeChooseWidget extends StatefulWidget {
  final CompareType? compareType;
  final Function? onCompareTypeChanged;
  const CompareTypeChooseWidget({
    Key? key,
    this.compareType,
    this.onCompareTypeChanged,
  }) : super(key: key);

  @override
  _CompareTypeChooseWidgetState createState() => _CompareTypeChooseWidgetState();
}

class _CompareTypeChooseWidgetState extends State<CompareTypeChooseWidget> {
  CompareType? _currentCompareType;
  @override
  void initState() {
    super.initState();
    _currentCompareType = widget.compareType;
  }

  @override
  void didUpdateWidget(covariant CompareTypeChooseWidget oldWidget) {
    super.didUpdateWidget(oldWidget);
    if (_currentCompareType != widget.compareType) {
      _currentCompareType = widget.compareType;
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
            '选择对比源',
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
                CompareType.idCard,
                initValue: _currentCompareType == CompareType.idCard,
                onChanged: (value) {
                  _originModeChanged(CompareType.idCard, value);
                },
              ),
              const SizedBox(
                width: 20,
              ),
              _buildChooseWidget(
                CompareType.none,
                initValue: _currentCompareType == CompareType.none,
                onChanged: (value) {
                  _originModeChanged(CompareType.none, value);
                },
              ),
            ],
          ),
        ],
      ),
    );
  }

  void _originModeChanged(CompareType originMode, bool check) {
    if (check) {
      if (_currentCompareType == originMode) return;
      setState(() {
        _currentCompareType = originMode;
        widget.onCompareTypeChanged?.call(_currentCompareType);
      });
    }
  }

  Widget _buildChooseWidget(
    CompareType originMode, {
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
          ),
        ),
      ],
    );
  }
}
