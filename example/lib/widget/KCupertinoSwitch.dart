import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

class KCupertinoSwitch extends StatefulWidget {
  final bool initValue;
  final Function(bool)? onChanged;
  const KCupertinoSwitch({
    Key? key,
    this.initValue = false,
    this.onChanged,
  }) : super(key: key);

  @override
  _KCupertinoSwitchState createState() => _KCupertinoSwitchState();
}

class _KCupertinoSwitchState extends State<KCupertinoSwitch> {
  late bool _initValue;
  @override
  void initState() {
    super.initState();
    _initValue = widget.initValue;
  }

  @override
  void didUpdateWidget(covariant KCupertinoSwitch oldWidget) {
    super.didUpdateWidget(oldWidget);
    if (widget.initValue != oldWidget.initValue) {
      _initValue = widget.initValue;
    }
  }

  @override
  Widget build(BuildContext context) {
    return CupertinoSwitch(
      value: _initValue,
      activeColor: Colors.lightBlueAccent,
      onChanged: (value) {
        setState(() {
          _initValue = !_initValue;
        });
        if (widget.onChanged == null) return;
        widget.onChanged!(_initValue);
      },
    );
  }
}
