package tech.ucoon.wb_cloud_face.wbcloud;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.widget.Toast;

import com.webank.facelight.api.FaceVerifyConfig;
import com.webank.facelight.api.WbCloudFaceContant;
import com.webank.facelight.api.WbCloudFaceVerifySdk;
import com.webank.facelight.api.listeners.WbCloudFaceVerifyLoginListener;
import com.webank.facelight.api.result.WbFaceError;
import com.webank.facelight.process.FaceVerifyStatus;

import java.util.HashMap;

/**
 * 腾讯活体检测工具类
 */
public class WbCloudFaceVerifyKit {
    private static final String TAG = WbCloudFaceVerifyKit.class.getSimpleName();

    /**
     * 初始化刷脸SDK输入参数
     *
     * @return
     */
    public static WbCloudFaceVerifySdk.InputData initWbCloudFaceInputData(HashMap<String, String> params) {
        WbCloudFaceVerifySdk.InputData inputData = new WbCloudFaceVerifySdk.InputData(
                params.get("faceId"),
                params.get("order"),
                params.get("appId"),
                "1.0.0",
                params.get("nonce"),
                params.get("userId"),
                params.get("sign"),
                FaceVerifyStatus.Mode.GRADE,
                params.get("keyLicence"));
        return inputData;
    }

    /**
     * 调用腾讯云活体检测SDK, 比对类型 默认为公安网纹图片对比
     *
     * @param activity
     * @param inputData
     */
    public static void openCloudFaceService(Activity activity, WbCloudFaceVerifySdk.InputData inputData, WbCloudFaceVerifyResultListener listener) {
        Log.d(TAG, "openCloudFaceService");
        Bundle data = new Bundle();
        WbCloudFaceVerifyResult wbCloudFaceVerifyResult = new WbCloudFaceVerifyResult();
        data.putSerializable(WbCloudFaceContant.INPUT_DATA, inputData);
        //是否展示刷脸成功页面，默认不展示
        data.putBoolean(WbCloudFaceContant.SHOW_SUCCESS_PAGE, false);
        //是否展示刷脸失败页面，默认不展示
        data.putBoolean(WbCloudFaceContant.SHOW_FAIL_PAGE, false);
        //颜色设置,sdk内置黑色和白色两种模式，默认黑色
        //如果客户想定制自己的皮肤，可以传入WbCloudFaceContant.CUSTOM模式,此时可以配置ui里各种元素的色值
        //定制详情参考app/res/colors.xml文件里各个参数
        data.putString(WbCloudFaceContant.COLOR_MODE, WbCloudFaceContant.WHITE);
        //是否需要录制上传视频 默认需要
        data.putBoolean(WbCloudFaceContant.VIDEO_UPLOAD, true);
        //是否使用ipv6网络
        data.putBoolean(WbCloudFaceContant.IS_IPV6, false);
        //是否开启闭眼检测，默认不开启
        data.putBoolean(WbCloudFaceContant.ENABLE_CLOSE_EYES, false);
        //是否播放提示音，默认播放
        data.putBoolean(WbCloudFaceContant.PLAY_VOICE, true);
        //设置选择的比对类型  默认为公安网纹图片对比
        data.putString(WbCloudFaceContant.COMPARE_TYPE, WbCloudFaceContant.ID_CARD);
        //打开美颜功能
        FaceVerifyConfig.getInstance().enableFaceBeauty(false);

        data.putBoolean(WbCloudFaceContant.IS_ENABLE_LOG, true);

        Log.d(TAG, "WbCloudFaceVerifySdk initSdk");
        WbCloudFaceVerifySdk.getInstance().initSdk(activity, data, new WbCloudFaceVerifyLoginListener() {
            @Override
            public void onLoginSuccess() {
                //登录sdk成功
                Log.i(TAG, "onLoginSuccess");
                //拉起刷脸页面
                WbCloudFaceVerifySdk.getInstance().startWbFaceVerifySdk(activity, result -> {
                    String message = "";
                    //得到刷脸结果
                    if (result != null) {
                        if (result.isSuccess()) {
                            Log.d(TAG, "刷脸成功! Sign=" + result.getSign() + "; liveRate=" + result.getLiveRate() +
                                    "; similarity=" + result.getSimilarity() + "userImageString=" + result.getUserImageString());
                        } else {
                            WbFaceError error = result.getError();
                            if (error != null) {
                                Log.d(TAG, "刷脸失败！domain=" + error.getDomain() + " ;code= " + error.getCode()
                                        + " ;desc=" + error.getDesc() + ";reason=" + error.getReason());
                                if (error.getDomain().equals(WbFaceError.WBFaceErrorDomainCompareServer)) {
                                    Log.d(TAG, "对比失败，liveRate=" + result.getLiveRate() +
                                            "; similarity=" + result.getSimilarity());
                                }
                                message = error.getDesc();
                            } else {
                                Log.e(TAG, "sdk返回error为空！");
                            }
                        }
                    } else {
                        Log.e(TAG, "sdk返回结果为空！");
                    }
                    wbCloudFaceVerifyResult.setResult(result != null && result.isSuccess());
                    wbCloudFaceVerifyResult.setMessage(message);
                    listener.onVerifyResultListener(wbCloudFaceVerifyResult);
                });
            }

            @Override
            public void onLoginFailed(WbFaceError error) {
                //登录失败
                Log.i(TAG, "onLoginFailed!");
                if (error != null) {
                    Log.d(TAG, "登录失败！domain=" + error.getDomain() + " ;code= " + error.getCode()
                            + " ;desc=" + error.getDesc() + ";reason=" + error.getReason());
                    if (error.getDomain().equals(WbFaceError.WBFaceErrorDomainParams)) {
                        Toast.makeText(activity, "传入参数有误！" + error.getDesc(), Toast.LENGTH_SHORT).show();
                    } else {
                        Toast.makeText(activity, "登录刷脸sdk失败！" + error.getDesc(), Toast.LENGTH_SHORT).show();
                    }
                } else {
                    Log.e(TAG, "sdk返回error为空！");
                }
                wbCloudFaceVerifyResult.setResult(false);
                wbCloudFaceVerifyResult.setMessage("");
                listener.onVerifyResultListener(wbCloudFaceVerifyResult);
            }
        });
    }
}
