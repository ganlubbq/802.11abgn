#ifndef __CONFIGA_H__
#define __CONFIGA_H__

#include "../../define_param.h"
#include "../../filter_para.h"

//������
class configA
{
private:
protected:
public:

	//11aЭ������źż���ģ��
	//CProtocolA     protocolA;
	//Э�����ͱ��
	int      DataRate;
	int      ProtocolModel;
	int      length;
	//���Ʒ�ʽ
	Encoding EZOA_Encoding;
	//��Դ���
	int      source_mode;
	int      datainmaxlen;
	int		 source_length;
	CString    filepath;
	//֡����
	int      num_of_zeros;
	//֡��
	int      num_of_frame;
	//OFDM������
	bool scrambler_state_OFDM;
	//OFDM��������ʼֵ
	int scramble_state_initial;

	double IQ_gain;	//IQ����
	double quan_angle_adjust;//�����Ƕȵ���
	float FrequencyOffset;//Ƶ��ƫ��
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
	//�˲�ϵ��
	std::vector<double> filter_user;
	int oversample_ratio;
	Filterpara filter_para;
	configA()
	{
		DataRate = 6;
		add_channel =false;
		NumOfTaps = 4;
		MAX_Delay_Sample =16;//���ܴ���ѭ��ǰ׺
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
		//Ĭ��ѡ��Э��11a
		ProtocolModel = OneA; //�����Ķ�ֻ���ź����ɵ�Ĭ�ϳ���ѡ���йأ���Ĭ�Ͻ����޹�
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