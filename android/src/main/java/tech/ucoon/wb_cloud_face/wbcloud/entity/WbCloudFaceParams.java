package tech.ucoon.wb_cloud_face.wbcloud.entity;

public class WbCloudFaceParams {
    /**
     * 32位随机字符串
     */
    private String nonce;
    /**
     * user id
     */
    private String userId;
    /**
     * 在人脸核身控制台内申请
     */
    private String keyLicence;

    private String appId;
    /**
     * 订单号
     */
    private String order;
    /**
     * 签名信息
     */
    private String sign;
    /**
     * 此次刷脸用户标识，合作方需要向人脸识别后台拉取获得，详见获取 faceId 接口
     */
    private String faceId;

    public String getNonce() {
        return nonce;
    }

    public void setNonce(String nonce) {
        this.nonce = nonce;
    }

    public String getUserId() {
        return userId;
    }

    public void setUserId(String userId) {
        this.userId = userId;
    }

    public String getKeyLicence() {
        return keyLicence;
    }

    public void setKeyLicence(String keyLicence) {
        this.keyLicence = keyLicence;
    }

    public String getAppId() {
        return appId;
    }

    public void setAppId(String appId) {
        this.appId = appId;
    }

    public String getOrder() {
        return order;
    }

    public void setOrder(String order) {
        this.order = order;
    }

    public String getSign() {
        return sign;
    }

    public void setSign(String sign) {
        this.sign = sign;
    }

    public String getFaceId() {
        return faceId;
    }

    public void setFaceId(String faceId) {
        this.faceId = faceId;
    }
}
