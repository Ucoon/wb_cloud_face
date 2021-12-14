//
//  YTFaceCheckLivePose.hpp
//  YTPoseDetector
//
//  Created by Cheng Pan on 3/27/18.
//  Copyright © 2018 PanCheng. All rights reserved.
//

#ifndef YTFaceCheckLivePose_hpp
#define YTFaceCheckLivePose_hpp

#include <stdint.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <math.h>
#include <sstream>

#ifdef YTFACETRACK_NAMESPACE
using namespace YTFACETRACK_NAMESPACE;
#endif
#define FACEDETECT_EXPORT __attribute__((visibility("default")))
#define YT_FACEPOSE_VERSION "3.7.0"
namespace youtu {
typedef int (*YtFacePoseSDKLogCallback)(void *caller, int level, std::string message);
class YTPoseLiveDetector;

/// 动作类型
typedef enum :int{
    /// 眨眨眼动作
    POSETYPE_BLINK_EYE = 1,
    /// 张张嘴动作
    POSETYPE_OPEN_MOUSE = 2,
    
    //不建议使用的动作检测方式，安全性不如眨眼和张嘴高
    /// 点点头动作
    POSETYPE_NOD_HEAD = 3,
    /// 摇摇头
    POSETYPE_SHAKE_HEAD = 4,
    /// 静默动作
    POSETYPE_SILENCE = 5,
    //缓慢向左转头
    POSETYPE_TURN_LEFT = 6,
    //缓慢向右转头
    POSETYPE_TURN_RIGHT = 7,
    //由近及远
    POSETYPE_CLOSER_FAR = 8,
    //由远及近
    POSETYPE_FAR_CLOSER = 9,
    POSETYPE_COUNT = POSETYPE_SILENCE+1
}POSETYPE;

/// 动作检测返回码
typedef enum :int{
    /// 动作检测通过
    POSE_RET_POSE_COMMIT = 1,
    /// 动作检测中
    POSE_RET_POSE_DETECTING = 0,
    /// 姿态不正确
    POSE_RET_POSE_NOT_RIGHT = -1,
    /// 无人脸
    POSE_RET_NO_FACE = -2,
    /// 半边人脸
    POSE_RET_HALF_FACE = -3,
    /// 光线不合适
    POSE_RET_LIGHT_NOT_RIGHT = -4,
    /// 晃动
    POSE_RET_SHAKING = -5,
    ///点位信息不对
    POSE_SHAPE_ERROR = -6,
    /// 授权不通过
    POSE_RET_AUTH_FAILED = -1024
}YT_POSE_RET_TYPE;

/// 最佳照片检测时的返回码
typedef enum :int{
    /// 当前帧光照质量较差
    LIGHT_ERROR               = -2,
    /// 当前帧的人脸所占屏幕区域较小
    FACE_TOO_SMALL            = -3,
    /// 当前帧的人脸姿态角度过大
    POSE_ANGLE_ERROR          = -4,
    /// 当前帧的人脸嘴部姿态异常
    POSE_MOUTH_ERROR          = -5,
    /// 当前帧其他异常情况
    OHTER_ERROR               =  0,
    /// 检测正常
    SUCCESS                   =  1
}BestImgCode;

/// 动作算法类型
typedef enum :int {
    /// 推荐安全类型，光流算法
    YTPOSE_SAFETY_RECOMMAND    = 0,
    /// (点位计算)灵敏度高，但是对遮挡攻击的效果不够理想
    YTPOSE_SAFETY_LOW          = 1,
    /// (光流算法)相对安全，但是灵敏度会略微下降，让面部距离屏幕更近，可以有效提高通过率
    YTPOSE_SAFETY_HIGH         = 2,
    /// 动作类型算法数量
    YTPOSE_SAFETY_COUNT        = 3
}YTPOSE_SAFETY_LEVEL;

// typedef enum :int{
//     CV8_U1 = 0,
//     CV8_U3 = 1,
// }YTPoseMat_TYPE;

class YTPoseMat
{
public:
    int cols;
    int rows;
    int type;
    // std::vector<unsigned char> data;
    unsigned char* data = nullptr;
    int size;

    ~YTPoseMat()
    {
        if (data != nullptr)
        {
            delete[] data;
            data = nullptr;
        }
    }

    YTPoseMat() :cols(0), rows(0), type(3){
        data = nullptr;
        size = 0;
    }
    YTPoseMat(int cols_, int rows_, int type_) : cols(cols_), rows(rows_), type(type_)
    {
        if (type == 1)
        {
            size = cols * rows;
            data = new unsigned char[size];
        }
        else if (type == 3)
        {
            size = cols * rows * 3;
            data = new unsigned char[size];
        }
    }
    YTPoseMat(int cols_, int rows_, int type_, void* data_) :cols(cols_), rows(rows_), type(type_)
    {
        // unsigned char *indata = (unsigned char*) data_;
        if (type == 1)
        {
            size = cols * rows;
            data = new unsigned char[cols * rows];
            memcpy(data, data_, size);
        }
        else if (type == 3)
        {
            size = cols * rows * 3;
            data = new unsigned char[cols * rows * 3];
            memcpy(data, data_, size);
        }
    }

    YTPoseMat(const YTPoseMat &mat) {
        cols = mat.cols;
        rows = mat.rows;
        size = mat.size;
        type = mat.type;
        if (data != mat.data) {            
            data = new unsigned char[size];       
            memcpy(data, mat.data, size);
        } 
    }

    YTPoseMat& operator =(const YTPoseMat& mat)
    {
        cols = mat.cols;
        rows = mat.rows;
        size = mat.size;
        type = mat.type;
        if (data != mat.data) {
            if (data != nullptr) delete [] data;
            data = new unsigned char[size];       
            memcpy(data, mat.data, size);
        }
        return *this;
    }

    YTPoseMat(YTPoseMat&& mat) {
        cols = mat.cols;
        rows = mat.rows;
        size = mat.size;
        type = mat.type;
        if (nullptr != mat.data) {
            data = mat.data;
            mat.data = nullptr;
        }
    }

    YTPoseMat& operator=(YTPoseMat&& mat) {
        cols = mat.cols;
        rows = mat.rows;
        size = mat.size;
        type = mat.type;
        if (this != &mat) {
            if (data != nullptr) delete [] data;
            data = mat.data;
            mat.data = nullptr;
        }
        return *this;
    }
};

struct YTPoseRect
{
    int x;
    int y;
    int width;
    int height;

    YTPoseRect() :x(0), y(0), width(0), height(0){}
    YTPoseRect(int x_, int y_, int width_, int height_) :x(x_), y(y_), width(width_), height(height_){}
};

struct YTSize
{
    int width;
    int height;

    YTSize() :width(0), height(0){}
    YTSize(int width_, int height_) :width(width_), height(height_){}
};


struct YTPosePoint2f
{
    float x;
    float y;
    YTPosePoint2f() :x(0), y(0){}
    YTPosePoint2f(int x_, int y_) :x(x_), y(y_){}

    YTPosePoint2f operator -(const YTPosePoint2f& rp){
        return YTPosePoint2f(x - rp.x, y - rp.y);
    }
};

static float Norm(YTPosePoint2f p)
{
    double x = p.x;
    double y = p.y;
    return sqrt(x * x + y * y);
}

/// 动作检测对象类
class FACEDETECT_EXPORT FaceCheckLivePose
{
public:
    /// 动作检测构造接口
    /// @param _frameNum 缓存视频帧数（推荐20帧）
    FaceCheckLivePose(int _frameNum=20);
    /// 动作检测析构接口
    ~FaceCheckLivePose();
    /// 获取版本信息
    /// @note 返回当前版本信息
    static std::string getVersion();
    /// 重置接口
    ///@note 每次开始检测动作的时候请调用reset；检测不到人脸的时候也应该调用reset，以保障动作过程中没有发生人脸切换
    /// 获取完最优图和视频帧数据后也请调用reset接口
    void reset();
    
    /// 动作安全等级设置接口
    /// @param level 参考YTPOSE_SAFETY_LEVEL 目标安全等级
    void setSafetyLevel(YTPOSE_SAFETY_LEVEL level);
    /// 动作安全等级获取接口
    /// @return 返回当前动作安全等级
    YTPOSE_SAFETY_LEVEL getSafetyLevel();
    
    /// 动作检测接口
    /// @param shapeInput 输入人脸框
    /// @param visVec 输入关键点置信度
    /// @param poseType 输入目标动作
    /// @param rgb 输入帧信息rgb
    /// @param yuv 输入帧信息yuv（仅android使用，其他情况请填充空mat）
    /// @param pitch 输入人脸俯仰角度
    /// @param yaw 输入人脸左右角度
    /// @param roll 输入人脸旋转角度
    /// @return 返回YT_POSE_RET_TYPE 对应的错误码信息
    /**
    return -1 姿态不正确
    -2 当前没有人脸
    -3 当前只有半张脸
    -4 光线不合适
    -5 当前晃动较大
    -1024 授权检测不过
    **/
    int detect_liveness(const std::vector<float> &shapeVec, const std::vector<float> visVec, POSETYPE poseType ,void* rgb ,void* yuv, float pitch, float yaw, float roll);
    void registerSDKLogger(int level, YtFacePoseSDKLogCallback listener);
    //最优图相关接口    
    /// 获取最优图
    /// @param Type  返回图片类型 0 - rgb 1 - yuv
    /// @return 返回对应最优图
    YTPoseMat get_BestImgMat(int type=0);
    /// 获取最优图
    /// @param shape 人脸信息
    /// @param type 返回mat类型（0 - rgb，1 - yuv）
    /// @return 返回对应最优图
    YTPoseMat get_BestImgMat(std::vector<float> & shape, int type=0);
    /// 检测记录完成通知
    /// @return 返回是否可以获取序列帧视频和最优图
    bool get_RecordingDone();

    /// 获取当前已经存储的视频流
    /// @return 返回序列帧 rgb格式
    std::vector<YTPoseMat> get_frameList();
    /// 获取当前已经存储的视频流
    /// @return 返回序列帧 yuv格式
    std::vector<YTPoseMat> get_yuvFrameList();
    // 动作+反光合并协议相关接口
    /// 获取动作幅度最大图
    /// @param bestImg 输出动作最大的图
    /// @param bestShape 输出动作最大的点位信息
    /// @param eyeImg 输出动作最大的eye部图
    /// @param eyeShape 输出动作最大的eye部点位信息
    /// @param mouthImg 输出动作最大的mouth部图
    /// @param mouthImg 输出动作最大的mouth部点位信息
    void get_PoseImgMat(YTPoseMat &bestImg, std::vector<float> &bestShape,
                        YTPoseMat &eyeImg, std::vector<float> &eyeShape,
                        YTPoseMat &mouthImg, std::vector<float> &mouthShape
                                      );
    //主要动作执行完成，可以启动下一个步骤（目前主要用于动作+反光方案）
    /// 检测是否可以进入反光
    /// @return 返回是否可以进入反光状态
    bool get_CanReflect();
    /// 更新内部检测参数
    /// @param key 参数key
    /// @param value 参数值
    int updateParam(const std::string &key, const std::string &value);
    static std::string checksum(const std::string data);
private:
    YTPoseLiveDetector* livenessdetector;
    std::string anchorWidths;
};
/// 推荐对外使用类型
class FACEDETECT_EXPORT YTFaceCheckLivePose:public FaceCheckLivePose{};

}

#endif /* YTFaceCheckLivePose_hpp */
