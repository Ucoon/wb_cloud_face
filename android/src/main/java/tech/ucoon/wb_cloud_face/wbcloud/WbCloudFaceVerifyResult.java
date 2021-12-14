package tech.ucoon.wb_cloud_face.wbcloud;

public class WbCloudFaceVerifyResult {
    private boolean result;
    private String message;

    public WbCloudFaceVerifyResult() {
    }

    public boolean isResult() {
        return result;
    }

    public void setResult(boolean result) {
        this.result = result;
    }

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }
}
