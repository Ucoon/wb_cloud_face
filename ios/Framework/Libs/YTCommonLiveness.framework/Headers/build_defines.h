#define ANDROID_CUSTOM_NONE     (1)
#define ANDROID_CUSTOM_FOR_IOT  (0)
#define ANDROID_CUSTOM_FOR_UNIONPAY    (0)
#define ANDROID_CUSTOM_SUPPORT_VTS  (0)
//vts && vndk: https://source.android.com/devices/architecture/images/VNDK.pdf

#define CUSTOM_FOR_QQ (0)

#define ALLOW_EMPTY_SECRET_KEY  (1)


// change namespace for different business
#define YTLICENSE_NAMESPACE ytliveness
#define CLASS_WITH_PREFIX(__class) YTLiveness##__class
#define FUNCTION_WITH_PREFIX(__func) ytliveness_##__func
#define INNER_INTERFACE_USE_NAMESPACE (1)
