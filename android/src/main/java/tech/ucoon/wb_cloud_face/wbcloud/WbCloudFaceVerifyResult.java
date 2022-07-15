package tech.ucoon.wb_cloud_face.wbcloud;

public class WbCloudFaceVerifyResult {
    /**
     * 核验结果
     */
    private boolean verifyResult;
    /**
     * 提示语
     */
    private String message;

    public WbCloudFaceVerifyResult() {
    }

    public boolean isVerifyResult() {
        return verifyResult;
    }

    public void setVerifyResult(boolean verifyResult) {
        this.verifyResult = verifyResult;
    }

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }
}
