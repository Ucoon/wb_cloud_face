//
//  DataDef.h
//  FaceVideoTest
//
//  Created by starimeliu on 2017/4/13.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#ifndef DataDef_h
#define DataDef_h
#include <vector>
#include <string>
// ===== Observation Pack ======

struct YTRawImgData // === N pairs of images along with their landmarks ===
{
    std::vector<unsigned char> frame_buffer;            // Frame data in buffer
    std::string frame_buffer_string;            //frame_buffer的std::string类型值
    std::string checksum;
    long long CaptureTime;
    int x;
    int y;
};

struct RawYuvData
{
    std::vector<unsigned char> yuvData;
    int width;
    int height;
};

struct YTDataPack
{
    std::vector<YTRawImgData> VideoData;		// Length = 2*N
    long long BeginTime;
    long long ChangePointTime;
    std::vector<long long> ChangePointTimeList;
    float OffsetSys;
    int config_begin;
    int frameNum;							// Number of frames = 2*N
    int LandMarkNum;						// Length of landmark points = 90 here
    int width;
    int height;
    const char *log;							// text log info
    const char *SeqID;
    const char *version;

    std::vector<RawYuvData> yuvDatas;
    
};


// ===== CAPTCHA Pack ======

struct YTCAPTCHA{
    int fixedInterval;
    int unit;
    int rand_shift;
    int rand_inv;
    std::vector<int> intervals;
    
    const char *SeqID;
};

// ===== Full Pack ======
struct YTFullPack{
    YTDataPack AGin;
    YTCAPTCHA CP;
    std::vector<unsigned char> SingleImg_buffer;
};

#endif /* DataDef_h */
