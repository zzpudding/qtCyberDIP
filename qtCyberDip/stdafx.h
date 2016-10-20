
//*************************************************************//
//                                                             //
//                   CyberDip ��������v0.98                     //
//                                                             //
//             ���� Qt5.7 OpenCV2.4.9  VS2013 �ȸ��߰汾        //
//             ���� FFmpeg 2.2.2                               //
//             ���� bbqScreenClient ��Դ����			     	   // 
//			   ���� grbl v0.8c (Baud 9600)			    	   //
//			   ���� grbl v0.9j (Baud 115200)			    	   //
//                                                             //
//                       CVPRʵ���� ��Ʒ                       //
//                   �ص㣺����Ⱥ¥ 2 - 302B                    //
//                                                             //
//*************************************************************//
//����ı߿��ܱ����������������ǶԲ���ģ�ǿ��֢�Ƿ�����..

//STEP0:���Ϸ�QT�˵�������QT�汾
//STEP0:Set QT version

//STEP1: ע����#define VIA_OPENCV��������OpenCVǰ���Ա��뱾���� ����ͨ����������OpenCV����
//STEP1: Comment #define VIA_OPENCV and build -> Test your QT and FFmpeg settings.
//#define VIA_OPENCV

//STEP2: ������������豸�ĳ����Լ����ڵ��ϱ�Ե
//RANGE  ��ʾ�豸��Ļ��CyberDIP�еĳߴ�
//UP_CUT ��ʾCaptureʱ��ȥ����ͷ���ı����Ĵ�С������ʹ��AirPlayerʱʹ�ã�ʹ��bbq��ʱ��Ӧ����Ϊ0.
//STEP2: Measure the range of your device in CyberDIP.
//RANGE  means the screen size of device in CyberDIP coordinates.
//UP_CUT is used to chop the title of video window.
#define RANGE_X 61
#define RANGE_Y 47
#define UP_CUT 35.0

//STEP3: ��qtCyberDIP.cpp���޸���Ӧ��ͼ�������
//STEP3: Modify codes in qtCyberDIP.cpp for image processing.

//���²��ظ���
#include <QtWidgets/QtWidgets>

#ifdef VIA_OPENCV
#include <opencv2\opencv.hpp>
#include <opencv\cv.h>
#include <opencv\highgui.h>
#endif
