#ifndef __DEFINE_PARAM_H__
#define __DEFINE_PARAM_H__

#include "crc16.h"
#include <string>
//宏定义//11abgn协议的编号
#define OneA 0
#define OneB 1
#define OneG 2
#define OneN 3
#define OneNL 4


//常用参数
#define pi 3.141592653589793
#define PI 3.141592653589793 
#define FFT_N 64
#define BYTE_B 8
#define LEN(array, len){len=sizeof(array)/sizeof(array[0]);}//计算数组长度
//#define N 64
typedef struct fushu
{
	double real;
	double img;
}fushu;

enum FrameType{
	General = 0,
	RTS = 1,
	CTS = 2
};
//枚举前导类型：长、短
enum preambleType 
{
	shortPreamble = 0,
	longPreamble = 1,
	OFDMPreamble = 2
};

enum scramblerState
{
	ON = 0,
	OFF = 1,
	Preamble_only = 2
};

//多种调制方式和码率
enum  Encoding
{
	BPSK_1_2  = 0,
	BPSK_3_4  = 1,
	QPSK_1_2  = 2,
	QPSK_3_4  = 3,
	QAM16_1_2 = 4,
	QAM16_3_4 = 5,
	QAM64_2_3 = 6,
	QAM64_3_4 = 7,
	DBPSK_1M = 8,      
	DQPSK_2M = 9,
	CCK_5_5M = 10,
	CCK_11M =11,
	PBCC_5_5M = 12,
	PBCC_11M = 13,
	PBCC_22M =14,
	PBCC_33M =15

};
enum Data_Rate
{
	_1Mbps = 1,
	_2Mbps = 2,
	_3Mbps = 3,
	_55Mbps = 55,
	_11Mbps = 11,
	_22Mbps = 22,
	_33Mbps = 33,
	_6Mbps = 6,
	_9Mbps = 9,
	_12Mbps = 12,
	_18Mbps = 18,
	_24Mbps = 24,
	_36Mbps = 36,
	_48Mbps = 48,
	_54Mbps = 54
};


enum modulationType
{
	DBPSK_1Mbps = 0,
	DQPSK_2Mbps = 1,
	CCK55_55Mbps = 2,
	PBCC55_55Mbps = 3,
	CCK11_11Mpbs = 4,
	PBCC11_11Mbps = 5 ,
	PBCC22_22Mbps = 6 ,
	PBCC33_33Mbps = 7 ,
	BPSK_1_2_  = 8,  //6M
	BPSK_3_4_  = 9,  //9M
	QPSK_1_2_  = 10, //12M
	QPSK_3_4_  = 11, //18M
	QAM16_1_2_ = 12, //24M
	QAM16_3_4_ = 13, //36M
	QAM64_2_3_ = 14, //48M
	QAM64_3_4_ = 15  //54M
};

//enum MCS
//{
//
//
//
//}

#endif