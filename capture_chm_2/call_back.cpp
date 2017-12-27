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


#define USECOLOR 1


using namespace std;
using namespace cv;


 extern LONG lPort;   //全局的播放库port号


 void yv12toYUV(char *outYuv, char *inYv12, int width, int height,int widthStep)
 {
     qDebug() << "fault8";
     int col,row;
     unsigned int Y,U,V;
     int tmp;
     int idx;

     //printf("widthStep=%d.\n",widthStep);

     for (row=0; row<height; row++)
     {
         idx=row * widthStep;
         int rowptr=row*width;

         for (col=0; col<width; col++)
         {
             //int colhalf=col>>1;
             tmp = (row/2)*(width/2)+(col/2);
             //         if((row==1)&&( col>=1400 &&col<=1600))
             //         {
             //          printf("col=%d,row=%d,width=%d,tmp=%d.\n",col,row,width,tmp);
             //          printf("row*width+col=%d,width*height+width*height/4+tmp=%d,width*height+tmp=%d.\n",row*width+col,width*height+width*height/4+tmp,width*height+tmp);
             //         }
             Y=(unsigned int) inYv12[row*width+col];
             U=(unsigned int) inYv12[width*height+width*height/4+tmp];
             V=(unsigned int) inYv12[width*height+tmp];
             //         if ((col==200))
             //         {
             //         printf("col=%d,row=%d,width=%d,tmp=%d.\n",col,row,width,tmp);
             //         printf("width*height+width*height/4+tmp=%d.\n",width*height+width*height/4+tmp);
             //         return ;
             //         }
             if((idx+col*3+2)> (1200 * widthStep))
             {
                 //printf("row * widthStep=%d,idx+col*3+2=%d.\n",1200 * widthStep,idx+col*3+2);
             }
             outYuv[idx+col*3]   = Y;
             outYuv[idx+col*3+1] = U;
             outYuv[idx+col*3+2] = V;
         }
     }
     //printf("col=%d,row=%d.\n",col,row);
 }

//解码回调 视频为YUV数据(YV12)，音频为PCM数据
void CALLBACK DecCBFun(int nPort,char * pBuf,int nSize,FRAME_INFO * pFrameInfo, void* nReserved1,int nReserved2)
{

    int i = 0;
    int num = 0;//统计帧数
    cv::Mat img;
    string img_name;
    char image_name[50];

    qDebug() << "fault9";

    long lFrameType = pFrameInfo->nType;

    if(lFrameType ==T_YV12)
    {
#if USECOLOR
    //int start = clock();
    IplImage* pImgYCrCb = cvCreateImage(cvSize(pFrameInfo->nWidth,pFrameInfo->nHeight), 8, 3);//得到图像的Y分量
    yv12toYUV(pImgYCrCb->imageData, pBuf, pFrameInfo->nWidth,pFrameInfo->nHeight,pImgYCrCb->widthStep);//得到全部RGB图像
    IplImage* pImg = cvCreateImage(cvSize(pFrameInfo->nWidth,pFrameInfo->nHeight), 8, 3);
    cvCvtColor(pImgYCrCb,pImg,CV_YCrCb2RGB);//cvCvtColor(...),是Opencv里的颜色空间转换函数，可以实现rgb颜色向HSV,HSI等颜色空间的转换，也可以转换为灰度图像。

//    sprintf(image_name, "%d.jpg", i);//保存图片
//    cvSaveImage(image_name, pImg);

    //int end = clock();
#else
    IplImage* pImg = cvCreateImage(cvSize(pFrameInfo->nWidth,pFrameInfo->nHeight), 8, 1);
    memcpy(pImg->imageData,pBuf,pFrameInfo->nWidth*pFrameInfo->nHeight);
//    sprintf(image_name, "%s%d%s", "image", ++num, ".jpg");//保存的图片名
//    img_name = image_name;
//    imwrite(img_name, frame);//保存保存一帧图片
#endif
    //printf("%d\n",end-start);
//    namedWindow( "Image_1", WINDOW_AUTOSIZE );//创建窗口
//    cvShowImage("Image_1",pImg);
//    waitKey(1);

//        sprintf(image_name, "%s%d%s", "image", ++num, ".jpg");//保存的图片名
//        cvSaveImage(image_name, pImg);
//        if( !cvSaveImage(image_name,pImg))
//        {
//            qDebug()<<cvSaveImage(image_name,pImg);
//        }
        //if(num==25)break;
        sprintf(image_name,"%s%d%s","k",i++,".jpg");
        if( !cvSaveImage(image_name,pImg))
        {
            qDebug()<<cvSaveImage(image_name,pImg);
        }

#if USECOLOR
    cvReleaseImage(&pImgYCrCb);
    cvReleaseImage(&pImg);
#else
    cvReleaseImage(&pImg);
#endif



  }

}

void CALLBACK g_RealDataCallBack_V30(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize,DWORD dwUser)
{
//    qDebug() << "fault2";
    HWND hWnd = NULL;

    DWORD dRet;
    switch (dwDataType)
    {
    case NET_DVR_SYSHEAD:    //系统头
       if (!PlayM4_GetPort(&lPort)) //获取播放库未使用的通道号
       {
           break;
       }
       if(dwBufSize > 0)
       {
           if (!PlayM4_OpenStream(lPort,pBuffer,dwBufSize,1024*1024))
           {
               dRet=PlayM4_GetLastError(lPort);
               break;
           }
           //设置解码回调函数 只解码不显示
           if (!PlayM4_SetDecCallBack(lPort,DecCBFun))
           {
               dRet=PlayM4_GetLastError(lPort);
               break;
           }

           //设置解码回调函数 解码且显示
           //if (!PlayM4_SetDecCallBackEx(nPort,DecCBFun,NULL,NULL))
           //{
           //  dRet=PlayM4_GetLastError(nPort);
           //  break;
           //}

           //打开视频解码
           if (!PlayM4_Play(lPort,hWnd))
           {
               dRet=PlayM4_GetLastError(lPort);
               break;
           }

           //打开音频解码, 需要码流是复合流
           if (!PlayM4_PlaySound(lPort))
           {
               dRet=PlayM4_GetLastError(lPort);
               break;
           }
       }
       break;
    case NET_DVR_STREAMDATA:   //码流数据
            if (dwBufSize > 0 && lPort != -1)
            {
                BOOL inData=PlayM4_InputData(lPort,pBuffer,dwBufSize);
                while (!inData)
                {
                    sleep(10);
                    inData=PlayM4_InputData(lPort,pBuffer,dwBufSize);

                }
            }
            break;
    }

}
void CALLBACK g_ExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser)
{
    char tempbuf[256] = {0};
    switch(dwType)
    {
    case EXCEPTION_RECONNECT:    //预览时重连
    printf("----------reconnect--------%d\n", time(NULL));
    break;
    default:
    break;
    }
}
