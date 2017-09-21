#ifndef CONFIG_H
#define CONFIG_H
#include "define_param.h"
class config
{

private:
protected:
public:


	//���Ʒ�ʽ
	modulationType modulation_type;	
	//����
	Data_Rate data_rate;
	//������״̬
	scramblerState scrambler_state;
	//preambleType 
	preambleType  preamble_type;

	//Э�����ͱ��
	int      ProtocolModel;
	//���Ʒ�ʽ
	Encoding EZOA_Encoding;
	config()
	{
		//Ĭ��ѡ����Ʒ�ʽΪBPSK������Ϊ1/2
		EZOA_Encoding = BPSK_1_2;
		//Ĭ��ѡ��Э��11a
		ProtocolModel = OneA; //�����Ķ�ֻ���ź����ɵ�Ĭ�ϳ���ѡ���йأ���Ĭ�Ͻ����޹�
		preamble_type = OFDMPreamble;
		scrambler_state = ON;
	};
	~config(){};
};
#endif