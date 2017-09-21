
#pragma once
#ifndef __CONFIGG_H__
#define __CONFIGG_H__

#include "C:\Users\dell\Desktop\802.11abgn_phy_11a\eiTemplate\define_param.h"
#include "C:\Users\dell\Desktop\802.11abgn_phy_11a\eiTemplate\filter_para.h"
//#include "../../define_param.h"
//�˲�������
//#include "../../filter_para.h"
//ö��������״̬�������غ�ֻǰ������

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

////ö��ǰ�����ͣ�������
//enum preambleType 
//{
//	shortPreamble = 0,
//	longPreamble = 1,
//	OFDMPreamble = 2
//};

//ö�ٵ�������
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

//ö����������
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

//������
class configG
{
private:
protected:
public:

	//Э�����ͱ��
	int      ProtocolModel;
	//���Ʒ�ʽ
	modulationType modulation_type;	
	Encoding EZOG_Encoding;
	//����
	Data_Rate data_rate;
	int length;
	//������״̬
	scramblerState scrambler_state;
	bool scrambler_state_OFDM;
	//OFDM��������ʼֵ
	int scramble_state_initial;
	//preambleType 
	preambleType  preamble_type;
	double IQ_gain;	//IQ����
	double quan_angle_adjust;//�����Ƕȵ���
	float FrequencyOffset;//Ƶ��ƫ��
	//��Դ���
	int      source_mode;
	int      datainmaxlen;
	int		 source_length;
	CString    filepath;
	//֡����
	int      num_of_zeros;
	//֡��
	int      num_of_frame;
	//�ŵ����
	bool     add_channel;
	double   NumOfTaps;
	double	 MAX_Delay_Sample;
	bool     InData_Complex;
	double   mobilespeed;
	double   carrierfreq;
	//fd_max = mobilespeed / 3.6 / (3*1e8) *carrierfreq ; 
	double   fd_max;
	double   dt;//����ĵ���
	//�˲���
	std::vector<double> filter_user;
	int oversample_ratio;
	Filterpara filter_para;
	configG()
	{
		//Ĭ��ѡ��Э��11b
		ProtocolModel = OneG; //�����Ķ�ֻ���ź����ɵ�Ĭ�ϳ���ѡ���йأ���Ĭ�Ͻ����޹�
		//����Ĭ��Ϊ 1M DBPSK
		data_rate = _6Mbps;
		//Ĭ��ѡ����Ʒ�ʽΪDBPSK
		modulation_type = BPSK_1_2_;	
		EZOG_Encoding = BPSK_1_2;//���ݲ��ֵ��Ʒ�ʽ�޸�����
		length = 2641;
		//Ĭ��������״̬Ϊ��
		scrambler_state= ON;
		scrambler_state_OFDM=true;
		scramble_state_initial=93;
		//Ĭ��ǰ��Ϊ��ǰ��
		preamble_type = OFDMPreamble;
		num_of_zeros=200;
		num_of_frame=20;
		//��Դ�ŵ�
		add_channel =false;
		NumOfTaps = 4;
		MAX_Delay_Sample =16;//���ܴ���ѭ��ǰ׺
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