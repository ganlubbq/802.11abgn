#ifndef __CONFIGB_H__
#define __CONFIGB_H__

#include "../../define_param.h"
//滤波器参数
#include "../../filter_para.h"

//配置类
class configB
{
private:
protected:
public:

	//11b协议基带信号计算模块...
	//CProtocolB protocolB;

	//协议类型编号
	int      ProtocolModel;
	//调制方式
	modulationType modulation_type;	
	Encoding EZOB_Encoding;
	//速率
	Data_Rate data_rate;
	//扰码器状态
	scramblerState scrambler_state;
    //preambleType 
	preambleType  preamble_type;
	int length;
	//帧数
	int num_of_frame;
	//帧间间隔
	int num_of_zeros;
	double IQ_gain;	//IQ增益
	double quan_angle_adjust;//正交角度调整
	float FrequencyOffset;//频率偏移
	//信源相关
	int      source_mode;
	int      datainmaxlen;
	int		 source_length;
	CString    filepath;
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
	//滤波系数
	std::vector<double> filter_user;
	int oversample_ratio;
	Filterpara filter_para;
	configB()
	{
		//默认选择协议11b
		ProtocolModel = OneB; //参数改动只对信号生成的默认程序选择有关，与默认界面无关
		//速率默认为 1M DBPSK
		data_rate = _1Mbps;
		//默认选择调制方式为DBPSK
		modulation_type = DBPSK_1Mbps;	//数据部分调制
		EZOB_Encoding = DBPSK_1M;//数据部分的调制方式应该修改这里
		length = 9152;
		//默认扰码器状态为开
		scrambler_state= ON;	
		//默认前导为长前导
		preamble_type = longPreamble;
		num_of_zeros=220;
		num_of_frame=20;
		//信源信道
		add_channel =false;
		NumOfTaps = 1;
		MAX_Delay_Sample =16;
		InData_Complex =true;
		mobilespeed =30;
		carrierfreq =2.412e9;
		dt = 1 / 11e6 ;
		fd_max = mobilespeed /3.6 /(3e8) *carrierfreq ;
		source_mode = 0;
		datainmaxlen = 4061;
		source_length =80;//length of PSDU，单位：字节
		filepath ="";
		oversample_ratio = 1;
		filter_para.filtertype = lpfilter;
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

	~configB(){};
};

#endif /*__CONFIGB_H__*/