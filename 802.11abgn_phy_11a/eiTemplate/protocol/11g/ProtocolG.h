
#pragma once
#ifndef _PROTOCOLG_H_
#define _PROTOCOLG_H_




#include <iostream>
#include <climits>
#include <string>

#include <iosfwd>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <vector>
#include <complex>

//#include "../../crc16.h"
//#include "complex.h"
//#include "E:\802.11abgn_phy_11b_new\eiTemplate\protocol\11g\configG.h"
#include "configG.h"
using namespace std;

//#define PI 3.141592653589793 
//#define BYTE_B 8
//#define LEN(array, len){len=sizeof(array)/sizeof(array[0]);}//计算数组长度
//typedef complex<double> complex;// 复数 实部虚部都是double型  
//#define N 64  
//#define FFT_N 64
//typedef struct fushu
//{
//	double real;
//	double img;
//}fushu;

//const int spread11[11]={1, -1, 1, 1, -1, 1, 1, 1, -1, -1, -1};			//11 digit Barker Code
//const int spreading_Rate = 11;
//const int sample_perchip = 8;
//const int SFD_size = 16;	
//const int signal_size = 8;
//const int service_size = 8;
//const int length_size = 16;
//const int CRC_size = 16;
////PSDU parameter size
//const int FCS_size_bytes = 4;//4
//const int MACHeader_size_bytes = 30;//4

//	enum dataRate
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
//
//enum preambleType 
//{
//	shortPreamble = 0,
//	longPreamble = 1,
//	OFDMPreamble = 2
//};
//
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
//    BPSK_1_2  = 8,  //6M
//	BPSK_3_4  = 9,  //9M
//	QPSK_1_2  = 10, //12M
//	QPSK_3_4  = 11, //18M
//	QAM16_1_2 = 12, //24M
//	QAM16_3_4 = 13, //36M
//	QAM64_2_3 = 14, //48M
//	QAM64_3_4 = 15  //54M
//};
//
// enum scramblerType
// {
//	DSSS_scrambler = 0,
//	OFDM_scrambler = 1 
// };
//
//  enum scramblerState
// {
//	ON = 0,
//	OFF = 1,
//	Preamble_only = 2
// };


class tx_11g_param
{
	//信道相关参数
public:
	bool   add_channel;
	double RndPhase[16][12];
	double Path_Delay[16];
	double Path_Average_Power[16];
	double Path_Average_Amp[16];
	double MAX_Delay_Sample;
	double fore_data_pr[50];
	double fore_data_pi[50];
	double RMS_Delay_Sample;
	int sizeof_Path_Delay;
	int sizeof_Path_Average_Power;
	//Jakes
	int NumOfFreq;
	bool InData_Complex;

	double fading_r[4];
	double fading_i[4];

	//
	int IntervalBetweenFrames;
	int LengthOfBurst;
public:
	configG  GprotocolConfig;
	std::complex<double> *S_preambpart;
	std::complex<double> *S_preambparta;
	std::complex<double> *S_singalpart;// 11a
	std::complex<double> *S_headerpart;
	std::complex<double> *S_datapart;
	std::complex<double> *S_datapart_f;
	std::complex<double> *preamble_last_symbol;
	std::complex<double> *header_last_symbol;
	std::complex<double> *header_last_chip;
	std::complex<double> *S_PPDU;
	int     S_preamb_length;
	int     S_singal_length;
	int     S_header_length;
	int     S_data_length;
	int     S_PPDU_length;

	//功率谱 
	std::complex<double> *S_FFTATUOpower;
	std::complex<double> *S_FFTspectrum;

	//tx_11g_param配置参数
	int PayloadData_size_bytes;//输入数据字节数 0~4061
	int PSDU_size_bytes;//PSDU 字节数 包含MAC头，payload，FCS，
	int PSDU_size;
	int data_size;
	Data_Rate data_rate;
	preambleType preamble_type;
	modulationType modulation_type;
	Encoding encoding;
	scramblerType scrambler_type;//DSSS OFDM
	scramblerState scrambler_state;//ON OFF PreambleOnly

	//11b系列参数
	int spread11[11];			//11 digit Barker Code
	int spreading_Rate;
	int sample_perchip;
	int sync_size; 
	int SFD_size;	
	int signal_size;
	int service_size;
	int length_size;
	int CRC_size;	
	int length;
	int bin_length[16];
	int FCS_size_bytes;//4
	int MACHeader_size_bytes;//30
	//     int PayloadData_size_bytes;

	vector<int> Data;
	vector<int> sync;
	vector<int> SFD;
	vector<int> preamble;
	// vector<int> signal;
	unsigned char signal;
	// vector<int> service;
	unsigned char service;
	// vector<int> crc;
	vector<int> header;                                                                                                     
	vector<int> msg;
	vector<int> CRC_bits;

	//length calculate for dsss mod 
	void length_calculate(int * LENGTH_extension_b7,int * LENGTH_extension_b6,int * LENGTH_extension_b5,int * LENGTH_2,int PSDU_size_bytes,char service_b3,Data_Rate data_rate);
	//length calculate for dsss-ofdm mod
	void length_calculate_DSSS_OFDM(int * LENGTH,int PSDU_size_bytes);
	//dsss 
	// vector<int> crc_calculate(vector<int> msg);

	std::vector<int> setVector(std::vector<int> vec, int temp[], int m);

	void dec2bin(int obj, int bin[], int m);

	void ComplexNumberOutput(fushu c);

	void scramble(int str[], int b_index, int Nfrm, int scramble_out[], int inf_len);	
	vector<int> tx_11g_param::scrambler(vector<int>PPDU_bit);

	void DBPSK(std::complex<double> complex_modDB[],vector<int>Data);
	void DBPSK(std::complex<double> complex_modDB[],vector<int>Data,double theta0);

	void DQPSK(std::complex<double> complex_modDQ[],vector<int>Data);
	void DQPSK(std::complex<double> complex_modDQ[],vector<int>Data,double theta0);

	void Barker_spread(std::complex<double> complex_barker[],std::complex<double> complex_mod[],int m) ;

	void CCK55(std::complex<double> complexOut[], vector<int> data_in);
	void CCK55(std::complex<double> complexOut[], vector<int> data_in,double theta);

	void CCK11(std::complex<double> complexOut[], vector<int> data_in);
	void CCK11(std::complex<double> complexOut[], vector<int> data_in,double theta);

	int encoder(int gen[][7], int n, int L, int reg[], int m, vector<int> data_in, int inf_len, int output[]);

	void repmat_PBCC_bits_55(vector<int> data_in, int Nfrm, int *convecdata,int tail_len,struct fushu *modout,double theta);

	void repmat_PBCC_bits_11(vector<int> data_in, int Nfrm, int *convecdata, int tail_len, struct fushu *modout,double theta);

	void PBCC55(std::complex<double> complexOut[], vector<int> data_in,double theta);

	void PBCC11(std::complex<double> complexOut[], vector<int> data_in,double theta);

	void PBCC22(std::complex<double> complexOut[], vector<int> data_in,double theta);

	void PBCC33(std::complex<double> complexOut[], vector<int> data_in,double theta);
	//DSSS
	vector<int> Produce_preamb_bit(int S_preamb_length);
	//void Produce_preamb_mod1(std::complex<double> complex_preamb[]);
	void Produce_preamb_mod1(std::complex<double> complex_preamb[],vector<int> PPDU_Scrambled,std::complex<double> preamble_last_symbol[]);

	vector<int> Produce_header_bit(int S_header_length);
	//void Produce_header_mod1(std::complex<double> complex_header[]);
	void Produce_header_mod1(std::complex<double> complex_header[],vector<int> PPDU_Scrambled,double theta0,std::complex<double> header_last_symbol[],std::complex<double> header_last_chip[]);
	
//	void Produce_PSDU_mod1(std::complex<double> complex_PSDU[]);
    void Produce_PSDU_mod1(std::complex<double> complex_PSDU[],vector<int> PPDU_Scrambled,double theta1,double theta2);

	void Produce_PPDU_mod1(std::complex<double> preambpart_in[],std::complex<double> headerpart_in[],std::complex<double> datapart_in[],std::complex<double> PPDU_out[],int preamb_length,int header_length,int data_length);


	//11a相关参数
public:

	//ofdm_param参数
	//	modulationType modulation_type;// data rate
	char     rate_field;// rate field of the SIGNAL header
	int      n_bpsc;// number of coded bits per sub carrier
	int      n_cbps;// number of coded bits per OFDM symbol
	int      n_dbps;// number of data bits per OFDM symbol
	int      n_rate;// transport rata
	int      sample_rate;// samples rata

	//tx_param参数	
	int      psdu_size;// PSDU size in bytes
	int      n_sym;// number of OFDM symbols (17-11)
	int      n_data;// number of data bits in the DATA field, including service and padding (17-12)
	int      n_pad;// number of padding bits in the DATA field (17-13)
	int      n_encoded_bits;

public:
	void ofdm_param(Encoding e);
	void tx_param(int psdu_length);//基本参数实现函数

public:
	double  Sample_Rate;
	double  T_tr;  //过度时间：0.1us
	char    scramble_state;
	int     index_q;//q序列的导频索引

public:
	//char    Test_data[100];//测试信号段
	char    Test_data[10];//测试信号段
	std::complex<double> BPSK_D[2];
	std::complex<double> QPSK_D[4];
	std::complex<double> QAM16_D[16];
	std::complex<double> QAM64_D[64];
	std::complex<double> Seq_P53[53];
	std::complex<double> Seq_p126[127];

public:
	//ifft
	void ifft(std::complex<double> f[]);

	void reshape_data(std::complex<double> complex_out[],std::complex<double> complex_in[],int index); //进入48位数据，输出64位数据	

	void add_recycle(std::complex<double> complex_out[],std::complex<double> complex_in[],int sample_rate);//增加循环前缀

	void display(std::complex<double> comstr[],int leng_N);

	int  ones(int n);

	void Bit_to_bit(char Bitdata[],char bitdata[],int bit_length);

	void scramble_mod2(const char *in, char *out,int initial_state);//扰码11a模式

	void reset_tail_bits(char *scrambled_data);//尾比特

	void convolutional_encoding(const char *in, char *out,int data);//调制

	void puncturing(const char *in, char *out);//打孔
	//void puncturing(const char *in, char *out, tx_11g_param &tx, ofdm_param &ofdm) 
	void interleave(const char *in, char *out, bool reverse);//交织

	void symbol_mapping(const char map_in[], std::complex<double> map_out[]);//映射
	//OFDM mod
	void Produce_preamb_mod2(std::complex<double> complex_preamb[]);

	void Produce_singal_mod2(std::complex<double> complex_singal[],int * Q_pinter,int data_length);

	void Produce_data_mod2(char char_datain[],std::complex<double> complex_dataout[],int * Q_pinter,int data_length);

	void Produce_PPDU_mod2(std::complex<double> preambpart_in[],std::complex<double> singalpart_in[],std::complex<double> datapart_in[],std::complex<double> PPDU_out[],int preamb_length,int singal_length,int data_length);

	//DSSS-OFDM
	void Produce_preamb_mod3(std::complex<double> complex_preamb[]);

	void Produce_header_mod3(std::complex<double> complex_header[]);

	void Produce_training_sequence_mod3(std::complex<double> complex_preamb[]);

	void Produce_PSDU_mod3(char char_datain[],std::complex<double> complex_dataout[],int * Q_pinter,int data_length);

	void Produce_PPDU_mod3(std::complex<double> preambpart_in[],std::complex<double> singalpart_in[],std::complex<double> datapart_in[],std::complex<double> PPDU_out[],int preamb_length,int singal_length,int data_length);

	void AutoC(std::complex<double> *discrete_seq,std::complex<double> *auto_corr,unsigned int seq_length);//自相关函数
	void FFT(std::complex<double> *xin);
	std::complex<double> EE(std::complex<double> a,std::complex<double> b);
	void tx_param_gb(Encoding e);
	void channel_initialize_1(double RndPhase[][12], double *Path_Delay, double *Path_Average_Amp, double *fore_data_pr, double *fore_data_pi, \
		double* RMS_Delay_Sample, double MAX_Delay_Sample, int NumOfTaps, double *Path_Average_Power, \
		int sizeof_Path_Delay, int sizeof_Path_Average_Power);
	void Jakes_kernel(double Path_Ampli,int NumOfFreq,int UpdateInterval,double fd_max,double* Phase,\
		int UpdatesPerBurst,int LengthOfBurst,int t_tmp,\
		double dt,vector<double> &fading_re,vector<double> &fading_im);
	void multipath_channel(vector<double> &InData_pr,vector<double> &InData_pi,\
		double fd_max,long NumOfTaps,\
		int SamplesPerFrame,int ChangesPerFrame,\
		int* TimeIndex,double dt,\
		double Phase[][12],double *Path_Delay,double *Path_Average_Amp,\
		vector<double> &OutData_pr,vector<double> &OutData_pi,\
		double *out_fading_pr,double *out_fading_pi,\
		double *fore_data_pr,double *fore_data_pi,\
		double *fading_indx);
	vector<double> lowpass_filter(int length,double Wn);
	vector<double> gauss_filter(int length,double BT);
	vector<double> root_raised_cosine(double alpha,int ntaps);
	void my_conv( complex<double> * Data_in,vector<double> &filter_coef,int Data_in_len);
public:
	void Initialization();
	void Run(vector<int>src,int data_bytelen);
	void Clear();
public:
	tx_11g_param();
public:
	virtual ~tx_11g_param();


};



#endif 