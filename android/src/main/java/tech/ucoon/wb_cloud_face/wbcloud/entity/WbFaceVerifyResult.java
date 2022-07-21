package tech.ucoon.wb_cloud_face.wbcloud.entity;

public class WbFaceVerifyResult {
    private boolean success;
    private String sign;
    private String liveRate;
    private String similarity;
    private String userImageString;
    private String orderNo;

    public boolean isSuccess() {
        return success;
    }

    public void setSuccess(boolean success) {
        this.success = success;
    }

    public String getSign() {
        return sign;
    }

    public void setSign(String sign) {
        this.sign = sign;
    }

    public String getLiveRate() {
        return liveRate;
    }

    public void setLiveRate(String liveRate) {
        this.liveRate = liveRate;
    }

    public String getSimilarity() {
        return similarity;
    }

    public void setSimilarity(String similarity) {
        this.similarity = similarity;
    }

    public String getUserImageString() {
        return userImageString;
    }

    public void setUserImageString(String userImageString) {
        this.userImageString = userImageString;
    }

    public String getOrderNo() {
        return orderNo;
    }

    public void setOrderNo(String orderNo) {
        this.orderNo = orderNo;
    }

    public static WbFaceVerifyResult setWbFaceVerifyResult(com.webank.facelight.api.result.WbFaceVerifyResult result) {
        if (result == null) return null;
        WbFaceVerifyResult wbFaceVerifyResult = new WbFaceVerifyResult();
        wbFaceVerifyResult.setSuccess(result.isSuccess());
        wbFaceVerifyResult.setSign(result.getSign());
        wbFaceVerifyResult.setLiveRate(result.getLiveRate());
        wbFaceVerifyResult.setSimilarity(result.getSimilarity());
        wbFaceVerifyResult.setUserImageString(result.getUserImageString());
        wbFaceVerifyResult.setOrderNo(result.getOrderNo());
        return wbFaceVerifyResult;
    }
}
