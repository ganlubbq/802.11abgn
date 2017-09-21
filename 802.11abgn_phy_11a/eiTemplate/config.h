#ifndef CONFIG_H
#define CONFIG_H
#include "define_param.h"
class config
{

private:
protected:
public:


	//调制方式
	modulationType modulation_type;	
	//速率
	Data_Rate data_rate;
	//扰码器状态
	scramblerState scrambler_state;
	//preambleType 
	preambleType  preamble_type;

	//协议类型编号
	int      ProtocolModel;
	//调制方式
	Encoding EZOA_Encoding;
	config()
	{
		//默认选择调制方式为BPSK，码率为1/2
		EZOA_Encoding = BPSK_1_2;
		//默认选择协议11a
		ProtocolModel = OneA; //参数改动只对信号生成的默认程序选择有关，与默认界面无关
		preamble_type = OFDMPreamble;
		scrambler_state = ON;
	};
	~config(){};
};
#endif