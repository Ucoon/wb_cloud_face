import 'package:flutter/material.dart';

class KCheckBox extends StatefulWidget {
  final bool initValue;
  final bool isRound;
  final double size;
  final Function(bool)? onChanged;
  const KCheckBox({
    Key? key,
    this.initValue = false,
    this.isRound = true,
    this.size = 16,
    this.onChanged,
  }) : super(key: key);

  @override
  _KCheckBoxState createState() => _KCheckBoxState();
}

class _KCheckBoxState extends State<KCheckBox> {
  late bool _initValue;
  @override
  void initState() {
    super.initState();
    _initValue = widget.initValue;
  }

  @override
  void didUpdateWidget(covariant KCheckBox oldWidget) {
    super.didUpdateWidget(oldWidget);
    if (widget.initValue != oldWidget.initValue) {
      _initValue = widget.initValue;
    }
  }

  @override
  Widget build(BuildContext context) {
    return SizedBox(
      width: widget.size,
      height: widget.size,
      child: Checkbox(
        value: _initValue,
        activeColor: Colors.lightBlueAccent,
        shape: widget.isRound ? const CircleBorder() : null,
        onChanged: (value) {
          setState(() {
            _initValue = !_initValue;
          });
          if (widget.onChanged == null) return;
          widget.onChanged!(_initValue);
        },
      ),
    );
  }
}
