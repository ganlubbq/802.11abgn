#ifndef __CONFIGA_H__
#define __CONFIGA_H__

#include "../../define_param.h"
#include "../../filter_para.h"

//配置类
class configA
{
private:
protected:
public:

	//11a协议基带信号计算模块
	//CProtocolA     protocolA;
	//协议类型编号
	int      DataRate;
	int      ProtocolModel;
	int      length;
	//调制方式
	Encoding EZOA_Encoding;
	//信源相关
	int      source_mode;
	int      datainmaxlen;
	int		 source_length;
	CString    filepath;
	//帧间间隔
	int      num_of_zeros;
	//帧数
	int      num_of_frame;
	//OFDM扰码器
	bool scrambler_state_OFDM;
	//OFDM扰码器初始值
	int scramble_state_initial;

	double IQ_gain;	//IQ增益
	double quan_angle_adjust;//正交角度调整
	float FrequencyOffset;//频率偏移
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
	configA()
	{
		DataRate = 6;
		add_channel =false;
		NumOfTaps = 4;
		MAX_Delay_Sample =16;//不能大于循环前缀
		InData_Complex =true;
		length = 2641;
		mobilespeed =30;
		carrierfreq =2.412e9;
		dt = 1 / 20e6 ;
		fd_max = mobilespeed /3.6 /(3e8) *carrierfreq ;
		EZOA_Encoding = BPSK_1_2;
		source_mode = 0;
		datainmaxlen = 4061;
		source_length =80;
		filepath ="";
		//默认选择协议11a
		ProtocolModel = OneA; //参数改动只对信号生成的默认程序选择有关，与默认界面无关
		oversample_ratio = 1;
		num_of_zeros=200;
		num_of_frame=20;
		scrambler_state_OFDM=true;
		scramble_state_initial=93;
		filter_para.filtertype = lpfilter;
		filter_para.lppara.wn = 0.24;
		filter_para.lppara.length = 30;
		filter_para.gausspara.length = 30;
		filter_para.gausspara.BT = 0.24;
		filter_para.cosinepara.length = 30;
		filter_para.cosinepara.alpha = 0.24;
		filter_para.filepath = "";
		IQ_gain=0;
		quan_angle_adjust=0;
		FrequencyOffset=0;
	};

	~configA(){};
};

#endif /*__CONFIG_H__*/