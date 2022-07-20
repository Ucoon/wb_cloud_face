package tech.ucoon.wb_cloud_face.wbcloud;

import java.util.Map;

public class WbCloudFaceVerifyResult {
    public static final int SUCCEED = 200;
    /**
     * 错误码：code == 200代表成功
     */
    private int code = -1;
    /**
     * 说明
     */
    private String description = "";
    /**
     * 错误原因
     */
    private String errorReason = "";
    /**
     * 核验结果
     */
    private Map<String, Object> verifyResult;

    public int getCode() {
        return code;
    }

    public void setCode(int code) {
        this.code = code;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public String getErrorReason() {
        return errorReason;
    }

    public void setErrorReason(String errorReason) {
        this.errorReason = errorReason;
    }

    public Map<String, Object> getVerifyResult() {
        return verifyResult;
    }

    public void setVerifyResult(Map<String, Object> verifyResult) {
        this.verifyResult = verifyResult;
    }
}
