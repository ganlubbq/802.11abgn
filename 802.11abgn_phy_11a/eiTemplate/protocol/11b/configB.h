#ifndef __CONFIGB_H__
#define __CONFIGB_H__

#include "../../define_param.h"
//�˲�������
#include "../../filter_para.h"

//������
class configB
{
private:
protected:
public:

	//11bЭ������źż���ģ��...
	//CProtocolB protocolB;

	//Э�����ͱ��
	int      ProtocolModel;
	//���Ʒ�ʽ
	modulationType modulation_type;	
	Encoding EZOB_Encoding;
	//����
	Data_Rate data_rate;
	//������״̬
	scramblerState scrambler_state;
    //preambleType 
	preambleType  preamble_type;
	int length;
	//֡��
	int num_of_frame;
	//֡����
	int num_of_zeros;
	double IQ_gain;	//IQ����
	double quan_angle_adjust;//�����Ƕȵ���
	float FrequencyOffset;//Ƶ��ƫ��
	//��Դ���
	int      source_mode;
	int      datainmaxlen;
	int		 source_length;
	CString    filepath;
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
	configB()
	{
		//Ĭ��ѡ��Э��11b
		ProtocolModel = OneB; //�����Ķ�ֻ���ź����ɵ�Ĭ�ϳ���ѡ���йأ���Ĭ�Ͻ����޹�
		//����Ĭ��Ϊ 1M DBPSK
		data_rate = _1Mbps;
		//Ĭ��ѡ����Ʒ�ʽΪDBPSK
		modulation_type = DBPSK_1Mbps;	//���ݲ��ֵ���
		EZOB_Encoding = DBPSK_1M;//���ݲ��ֵĵ��Ʒ�ʽӦ���޸�����
		length = 9152;
		//Ĭ��������״̬Ϊ��
		scrambler_state= ON;	
		//Ĭ��ǰ��Ϊ��ǰ��
		preamble_type = longPreamble;
		num_of_zeros=220;
		num_of_frame=20;
		//��Դ�ŵ�
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
		source_length =80;//length of PSDU����λ���ֽ�
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