#######################Demo里不能被混淆的########################################
-keep public class com.webank.cloudface.demo.SlipButton{
    public <methods>;
}
-keep public class com.webank.cloudface.demo.SlipButton$*{
    *;
}

-keep public class com.webank.cloudface.demo.SignUseCase{
    *;
}

-keep public class com.webank.cloudface.demo.SignUseCase$*{
    *;
}

-keep public class com.webank.cloudface.demo.GetFaceId{
    *;
}

-keep public class com.webank.cloudface.demo.GetFaceId$*{
    *;
}

-keep class tech.ucoon.wb_cloud_face.wbcloud.entity.*{
    *;
}

-keep class tech.ucoon.wb_cloud_face.wbcloud.WbCloudFaceVerifyResult{
    *;
}
#######################Demo里不能被混淆的########################################

#不混淆内部类
-keepattributes InnerClasses

#不混淆jni调用类
-keepclasseswithmembers class *{
    native <methods>;
}

###################### faceverify-BEGIN ###########################
-ignorewarnings
-keep public class com.tencent.ytcommon.**{*;}

-keep public class com.tencent.youtu.ytagreflectlivecheck.jni.**{*;}
-keep public class com.tencent.youtu.ytagreflectlivecheck.YTAGReflectLiveCheckInterface{
    public <methods>;
}
-keep public class com.tencent.youtu.ytposedetect.jni.**{*;}
-keep public class com.tencent.youtu.ytposedetect.data.**{*;}
-keep public class com.tencent.youtu.YTFaceTracker{*;}
-keep public class com.tencent.youtu.YTFaceTracker$*{*;}

-keep public class com.webank.facelight.net.*$*{
    *;
}
-keep public class com.webank.facelight.net.**{
    *;
}

#================数据上报混淆规则 start===========================
#实体类
-keep class com.webank.simple.wbanalytics.EventSender{
    *;
}
-keep class com.webank.simple.wbanalytics.EventSender$*{
    *;
}
-keep class com.webank.simple.wbanalytics.WBSAEvent{
     *;
}
#================数据上报混淆规则 end===========================

#不混淆内部类
-keepattributes InnerClasses
-keepattributes *Annotation*
-keepattributes Signature
-keepattributes Exceptions
-keep, allowobfuscation @interface com.webank.normal.xview.Inflater
-keep, allowobfuscation @interface com.webank.normal.xview.Find
-keep, allowobfuscation @interface com.webank.normal.xview.BindClick

-keep @com.webank.normal.xview.Inflater class *
-keepclassmembers class * {
    @com.webank.normal.xview.Find *;
    @com.webank.normal.xview.BindClick *;
}

-keep public class com.webank.normal.net.*$*{
    *;
}
-keep public class com.webank.normal.net.*{
    *;
}

#webank normal包含的第三方库bugly
-keep class com.tencent.bugly.webank.**{
    *;
}

#wehttp混淆规则
-dontwarn com.webank.mbank.okio.**
-keep class com.webank.mbank.okio.**{
    *;
}
-dontwarn com.webank.mbank.okhttp3.OkHttpClient$Builder


######################云产品依赖的第三方库 混淆规则-BEGIN###########################

## support:appcompat-v7
-keep public class android.support.v7.widget.** { *; }
-keep public class android.support.v7.internal.widget.** { *; }
-keep public class android.support.v7.internal.view.menu.** { *; }

-keep public class * extends android.support.v4.view.ActionProvider {
    public <init>(android.content.Context);
}

##########################云产品依赖的第三方库 混淆规则-END##############################

