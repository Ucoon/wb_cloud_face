package tech.ucoon.wb_cloud_face.wbcloud.entity;

import com.webank.facelight.api.WbCloudFaceContant;

import org.jetbrains.annotations.NotNull;

/**
 * 人脸核身配置参数类
 */
public class WbCloudFaceVerifyConfig {
    /**
     * 是否展示刷脸成功页面，默认不展示
     */
    private boolean showSuccessPage;

    /**
     * 是否展示刷脸失败页面，默认不展示
     */
    private boolean showFailPage;

    /**
     * 颜色设置，默认黑色
     */
    private String colorMode = WbCloudFaceContant.BLACK;

    /**
     * 是否需要录制上传视频，默认需要
     */
    private boolean videoUpload = true;

    /**
     * 是否使用ipv6网络，默认不使用
     */
    private boolean isIpv6;

    /**
     * 是否开启闭眼检测，默认不开启
     */
    private boolean enableCloseEyes;

    /**
     * 是否播放提示音，默认播放
     */
    private boolean playVoice = true;

    /**
     * 比对类型，默认为公安网纹图片对比
     */
    private String compareType = WbCloudFaceContant.ID_CARD;

    public boolean isShowSuccessPage() {
        return showSuccessPage;
    }

    public void setShowSuccessPage(boolean showSuccessPage) {
        this.showSuccessPage = showSuccessPage;
    }

    public boolean isShowFailPage() {
        return showFailPage;
    }

    public void setShowFailPage(boolean showFailPage) {
        this.showFailPage = showFailPage;
    }

    public String getColorMode() {
        return colorMode;
    }

    public void setColorMode(String colorMode) {
        this.colorMode = colorMode;
    }

    public boolean isVideoUpload() {
        return videoUpload;
    }

    public void setVideoUpload(boolean videoUpload) {
        this.videoUpload = videoUpload;
    }

    public boolean isIpv6() {
        return isIpv6;
    }

    public void setIpv6(boolean ipv6) {
        isIpv6 = ipv6;
    }

    public boolean isEnableCloseEyes() {
        return enableCloseEyes;
    }

    public void setEnableCloseEyes(boolean enableCloseEyes) {
        this.enableCloseEyes = enableCloseEyes;
    }

    public boolean isPlayVoice() {
        return playVoice;
    }

    public void setPlayVoice(boolean playVoice) {
        this.playVoice = playVoice;
    }

    public String getCompareType() {
        return compareType;
    }

    public void setCompareType(String compareType) {
        this.compareType = compareType;
    }

    @NotNull
    @Override
    public String toString() {
        return "WbCloudFaceVerifyConfig{" +
                "showSuccessPage=" + showSuccessPage +
                ", showFailPage=" + showFailPage +
                ", colorMode='" + colorMode + '\'' +
                ", videoUpload=" + videoUpload +
                ", isIpv6=" + isIpv6 +
                ", enableCloseEyes=" + enableCloseEyes +
                ", playVoice=" + playVoice +
                ", compareType='" + compareType + '\'' +
                '}';
    }
}
