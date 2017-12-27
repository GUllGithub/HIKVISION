#include <stdio.h>
#include <string>
#include <iostream>
#include <time.h>

#include "PlayM4.h"
#include "HCNetSDK.h"
#include <QDebug>

#include <highgui.hpp>
#include <imgproc.hpp>
#include "cv.h"
#include <QApplication>
#include"highgui.h"   
#include "cxcore.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <unistd.h>
#include <call_back.h>

#define USECOLOR 1

using namespace std;
using namespace cv;

 LONG lPort=-1;   //全局的播放库port号

int main() {
  // 初始化
  NET_DVR_Init();
  NET_DVR_SetConnectTime(2000, 1);
  NET_DVR_SetReconnect(10000, true);


  //  LPNET_DVR_JPEGPARA lpJpegPara = new NET_DVR_JPEGPARA;
  //        lpJpegPara->wPicQuality = 0; //图像质量 Image quality
  //           lpJpegPara->wPicSize = 0xff; //抓图分辨率 Picture size: 2- 4CIF，0xff- Auto(使用当前码
  //---------------------------------------
  // 注册设备
  LONG lUserID;
  NET_DVR_DEVICEINFO_V30 struDeviceInfo;
  lUserID = NET_DVR_Login_V30("49.91.240.70", 8000, "admin", "ad53937301", &struDeviceInfo);
  if (lUserID < 0)
  {
       printf("Login error, %d\n", NET_DVR_GetLastError());
       NET_DVR_Cleanup();
       return -1;
  }

  //---------------------------------------
  //设置异常消息回调函数
  NET_DVR_SetExceptionCallBack_V30(0, NULL,g_ExceptionCallBack, NULL);

  //---------------------------------------
  //启动预览并设置回调数据流
  LONG lRealPlayHandle;
  NET_DVR_CLIENTINFO ClientInfo = {0};
  ClientInfo.hPlayWnd = NULL;         //需要SDK解码时句柄设为有效值，仅取流不解码时可设为空
  ClientInfo.lChannel     = 1;       //预览通道号
  ClientInfo.lLinkMode    = 0;       //最高位(31)为0表示主码流，为1表示子码流0～30位表示连接方式：0－TCP方式；1－UDP方式；2－多播方式；3－RTP方式;
  ClientInfo.sMultiCastIP = NULL;   //多播地址，需要多播预览时配置

  BOOL bPreviewBlock = false;       //请求码流过程是否阻塞，0：否，1：是
  lRealPlayHandle = NET_DVR_RealPlay_V30(lUserID, &ClientInfo, NULL, NULL, 0);

  if (lRealPlayHandle < 0)
  {
      printf("NET_DVR_RealPlay_V30 error\n");
      NET_DVR_Logout(lUserID);
      NET_DVR_Cleanup();
      return -1;
  }

  if (!NET_DVR_SetRealDataCallBack(lRealPlayHandle, g_RealDataCallBack_V30, 0))//注册回调函数,捕获实时码流数据
  {
      printf("NET_DVR_SetRealDataCallBack error\n");
  }

  //  NET_DVR_SetCapturePictureMode(1);//设置抓图模式
  //  NET_DVR_CaptureJPEGPicture(lUserID, 1, lpJpegPara, "JPEG_test.jpg");//单帧数据捕获并保存成 JPEG 图片
  //  NET_DVR_CapturePicture(lRealPlayHandle,"test.jpg");//预览时,单帧数据捕获并保存成图片
  //NET_DVR_SaveRealData(lRealPlayHandle,"1_.mp4");//捕获数据并保存到指定的文件中
  //NET_DVR_STDControl(lUserID, 3714, LPNET_DVR_STD_CONTROL  lpControlParam)//强制刷新帧(Smart264)
    qDebug() << "fault10";
  //   while(1);
  sleep(-1);                //sleep 无限时间
  //---------------------------------------
  //关闭预览
  NET_DVR_StopRealPlay(lRealPlayHandle);
  //注销用户
  NET_DVR_Logout_V30(lUserID);
  NET_DVR_Cleanup();

  return -1;
}
