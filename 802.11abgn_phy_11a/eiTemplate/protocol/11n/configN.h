#ifndef __CONFIGA_N__
#define __CONFIGA_N__

#include "../../define_param.h"
#include"constants_def.h"
#include "../../filter_para.h"
#include "../../MpduPara.h"
using namespace std;

////宏定义//11abgn协议的编号
//#define OneA 0
//#define OneB 1
//#define OneG 2
//#define OneN 3
//#define OneNL 4
//
////常用参数
//#define pi 3.141592653589793
//#define PI 3.141592653589793 
//#define FFT_N 64
//
////多种调制方式和码率
//enum  Encoding
//{
//	BPSK_1_2  = 0,
//	BPSK_3_4  = 1,
//	QPSK_1_2  = 2,
//	QPSK_3_4  = 3,
//	QAM16_1_2 = 4,
//	QAM16_3_4 = 5,
//	QAM64_2_3 = 6,
//	QAM64_3_4 = 7,		
//};

//配置类
class configN
{
private:
protected:
public:

	//11a协议基带信号计算模块
	//CProtocolA     protocolA;
	//协议类型编号
	int      ProtocolModel;
	//波形产生模式（FORMAT）
	int      txvector_format;
	//带宽
	CString  BandWidth;
	int      datalength;//负载长度
	int      length;//采样点数
	//天线数目
	int      num_of_antenna;
	int      num_of_sts;
	int      Nss;
	int      STBC;
	int      Ness;
	//帧数
	int      num_of_frame;
	//帧间间隔
	int      num_of_zeros;
	//调制方式
	int      mcs;
	//保护间隔
	int     Short_GI;
	//波束成型
	int     UseBF;
	int     win;
	//空间映射机制
	int     ieeeQ ;
	//扰码初始值
	int     scramSeed;
	int     LDPC_Coding;
	bool    interleave_state;
	bool    scrambler;
	double IQ_gain;	//IQ增益
	double quan_angle_adjust;//正交角度调整
	float FrequencyOffset;//频率偏移
	//载荷配置
	int     aggregation;
	int     smoothing;
	int     sounding;
	//信源相关
	int      source_mode;
	int      datainmaxlen;
	int		 source_length;
	CString    filepath;
	//信道相关参数
	bool    add_channel;
	int     Nr;
	int     Nt;
	double  mobilespeed;
	double  carrierfreq;
	char    channel_type;
	//滤波器
	std::vector<double> filter_user;
	int oversample_ratio;
	Filterpara filter_para;
	vector<MpduPara> mpdus;
	int    num_of_mpdus;
	configN()
	{
		 add_channel =false;
		 Nr = 1;
		 Nt = 2;
		 Nss = 2;
		 Ness = 0;
		 STBC = 0;
		 length=1280;
		 mobilespeed = 30;
		 carrierfreq = 2.412;
		 channel_type = 'B';
		 txvector_format=HT_MM;
		 BandWidth="20";
		 datalength =20;
		 num_of_sts =2;
		 num_of_antenna=2;
		 mcs =10;
		 Short_GI=0;
		 UseBF=0;
		 win =0;
		 ieeeQ =0;
		 scramSeed=93;
		 LDPC_Coding=0;
		 scrambler=true;
		 interleave_state=true;
		 aggregation=0;
		 smoothing=0;
		 sounding=0;
		 ProtocolModel = OneN; //参数改动只对信号生成的默认程序选择有关，与默认界面无关
		 source_mode = 1;
		 datainmaxlen = 4061;
		 source_length =100;
		 filepath ="";
		 oversample_ratio = 1;
		 num_of_zeros=200;
		 num_of_frame=20;
		 filter_para.filtertype = lpfilter;
		 filter_para.lppara.wn = 0.24;
		 filter_para.lppara.length = 30;
		 filter_para.gausspara.length = 30;
		 filter_para.gausspara.BT = 0.24;
		 filter_para.cosinepara.length = 30;
		 filter_para.cosinepara.alpha = 0.24;
		 mpdus.resize(1);
		 IQ_gain=0;
		 quan_angle_adjust=0;
		 FrequencyOffset=0;
		 num_of_mpdus=0;
	};

	~configN(){};
};

#endif /*__CONFIG_H__*/