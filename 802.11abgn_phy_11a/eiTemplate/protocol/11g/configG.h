
#pragma once
#ifndef __CONFIGG_H__
#define __CONFIGG_H__

#include "C:\Users\dell\Desktop\802.11abgn_phy_11a\eiTemplate\define_param.h"
#include "C:\Users\dell\Desktop\802.11abgn_phy_11a\eiTemplate\filter_para.h"
//#include "../../define_param.h"
//滤波器参数
//#include "../../filter_para.h"
//枚举扰码器状态：开、关和只前导扰码

enum scramblerType
{
	DSSS_scrambler = 0,
	OFDM_scrambler = 1 
};

//enum scramblerState
//{
//	ON = 0,
//	OFF = 1,
//	Preamble_only = 2
//};

////枚举前导类型：长、短
//enum preambleType 
//{
//	shortPreamble = 0,
//	longPreamble = 1,
//	OFDMPreamble = 2
//};

//枚举调制类型
//enum modulationType
//{
//	DBPSK_1Mbps = 0,
//	DQPSK_2Mbps = 1,
//	CCK55_55Mbps = 2,
//	PBCC55_55Mbps = 3,
//	CCK11_11Mpbs = 4,
//	PBCC11_11Mbps = 5 ,
//	PBCC22_22Mbps = 6 ,
//	PBCC33_33Mbps = 7 ,
//	BPSK_1_2_  = 8,  //6M
//	BPSK_3_4_  = 9,  //9M
//	QPSK_1_2_  = 10, //12M
//	QPSK_3_4_  = 11, //18M
//	QAM16_1_2_ = 12, //24M
//	QAM16_3_4_ = 13, //36M
//	QAM64_2_3_ = 14, //48M
//	QAM64_3_4_ = 15  //54M
//};

//枚举数据速率
//enum Data_Rate
//{
//	_1Mbps = 1,
//	_2Mbps = 2,
//	_55Mbps = 55,
//	_11Mbps = 11,
//};

//enum dataRate
//{
//	_1Mbps = 1,
//	_2Mbps = 2,
//	_55Mbps = 55,
//	_11Mbps = 11,
//	_22Mbps = 22,
//	_33Mbps = 33,
//	_6Mbps = 6,
//	_9Mbps = 9,
//	_12Mbps = 12,
//	_18Mbps = 18,
//	_24Mbps = 24,
//	_36Mbps = 36,
//	_48Mbps = 48,
//	_54Mbps = 54
//
//};

//配置类
class configG
{
private:
protected:
public:

	//协议类型编号
	int      ProtocolModel;
	//调制方式
	modulationType modulation_type;	
	Encoding EZOG_Encoding;
	//速率
	Data_Rate data_rate;
	int length;
	//扰码器状态
	scramblerState scrambler_state;
	bool scrambler_state_OFDM;
	//OFDM扰码器初始值
	int scramble_state_initial;
	//preambleType 
	preambleType  preamble_type;
	double IQ_gain;	//IQ增益
	double quan_angle_adjust;//正交角度调整
	float FrequencyOffset;//频率偏移
	//信源相关
	int      source_mode;
	int      datainmaxlen;
	int		 source_length;
	CString    filepath;
	//帧间间隔
	int      num_of_zeros;
	//帧数
	int      num_of_frame;
	//信道相关
	bool     add_channel;
	double   NumOfTaps;
	double	 MAX_Delay_Sample;
	bool     InData_Complex;
	double   mobilespeed;
	double   carrierfreq;
	//fd_max = mobilespeed / 3.6 / (3*1e8) *carrierfreq ; 
	double   fd_max;
	double   dt;//带宽的倒数
	//滤波器
	std::vector<double> filter_user;
	int oversample_ratio;
	Filterpara filter_para;
	configG()
	{
		//默认选择协议11b
		ProtocolModel = OneG; //参数改动只对信号生成的默认程序选择有关，与默认界面无关
		//速率默认为 1M DBPSK
		data_rate = _6Mbps;
		//默认选择调制方式为DBPSK
		modulation_type = BPSK_1_2_;	
		EZOG_Encoding = BPSK_1_2;//数据部分调制方式修改这里
		length = 2641;
		//默认扰码器状态为开
		scrambler_state= ON;
		scrambler_state_OFDM=true;
		scramble_state_initial=93;
		//默认前导为长前导
		preamble_type = OFDMPreamble;
		num_of_zeros=200;
		num_of_frame=20;
		//信源信道
		add_channel =false;
		NumOfTaps = 4;
		MAX_Delay_Sample =16;//不能大于循环前缀
		InData_Complex =true;
		mobilespeed =30;
		carrierfreq =2.412e9;
		dt = 1 / 20e6 ;
		fd_max = mobilespeed /3.6 /(3e8) *carrierfreq ;
		source_mode = 0;
		datainmaxlen = 4061;
		source_length =80;
		filepath ="";
		oversample_ratio = 1;
		filter_para.filtertype = cosfilter;
		filter_para.lppara.wn = 0.24;
		filter_para.lppara.length = 30;
		filter_para.gausspara.length = 30;
		filter_para.gausspara.BT = 0.24;
		filter_para.cosinepara.length = 30;
		filter_para.cosinepara.alpha = 0.24;
		IQ_gain=0;
		quan_angle_adjust=0;
		FrequencyOffset=0;
	};

	~configG(){};
};

#endif /*__CONFIGB_H__*/