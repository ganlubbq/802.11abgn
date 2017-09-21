//#if !defined(AFX_PROTOCOLEOOA_H__7B2DEEBE_D5C5_4FA7_867E_AF446BDE1536__INCLUDED_)
//#define AFX_PROTOCOLEOOA_H__7B2DEEBE_D5C5_4FA7_867E_AF446BDE1536__INCLUDED_
//
//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000


// ProtocolEOOA.h : header file
//

#ifndef _PROTOCOLB_H_
#define _PROTOCOLB_H_

#include <iostream>
//#include <climits>
#include <string>
#include <complex>
//#include "complex.h"
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include<malloc.h>
#include <vector>
//#include "../../crc16.h"这个头文件包含的问题，有待解决！
#include "configB.h"
using namespace std;

//#define PI 3.141592653589793 
//#define pi 3.141592653589793 
//#define BYTE_B 8
//#define LEN(array, len){len=sizeof(array)/sizeof(array[0]);}//计算数组长度
//#define FFT_N 64

//typedef struct fushu
//{
//	double real;
//	double img;
//}fushu;

const int spread11[11]={1, -1, 1, 1, -1, 1, 1, 1, -1, -1, -1};			//11 digit Barker Code
const int spreading_Rate = 11;
const int sample_perchip = 8;
const int SFD_size = 16;	
const int signal_size = 8;
const int service_size = 8;
const int length_size = 16;
const int CRC_size = 16;



//PSDU parameter size
const int FCS_size_bytes = 4;//4
const int MACHeader_size_bytes = 30;//4

////枚举扰码器状态：开、关和只前导扰码
// enum scramblerState
// {
//	ON = 0,
//	OFF = 1,
//	Preamble_only = 2
// };
//
////枚举前导类型：长、短
//enum preambleType 
//{
//	shortPreamble = 0,
//	longPreamble = 1
//};
//
////枚举调制类型
//enum modulatiomType
//{
//	DBPSK_1Mbps = 0,
//	DQPSK_2Mbps = 1,
//	CCK55_55Mbps = 2,
//	PBCC55_55Mbps = 3,
//	CCK11_11Mpbs = 4,
//	PBCC11_11Mbps = 5 ,
//};
//
////枚举数据速率
//enum Data_Rate
//{
//	_1Mbps = 1,
//	_2Mbps = 2,
//	_55Mbps = 55,
//	_11Mbps = 11,
//};

/////////////////////////////////////////////////////////////////////////////
// CProtocolB window


//定义11b发送端参数类
class CProtocolB 
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
	//
	int IntervalBetweenFrames;
	int LengthOfBurst;
public:
	 configB  BprotocolConfig;//??????
	//指向各部分的指针及各段长度
	 std::complex<double>        *S_preambpart;
	 std::complex<double>        *S_headerpart;
	 std::complex<double>        *S_datapart;
	 std::complex<double>        *S_datapart_f;
	 std::complex<double>        *S_PPDU;
	 std::complex<double>		 *preamble_last_symbol;
	 std::complex<double>		 *header_last_symbol;
	 std::complex<double>		 *header_last_chip;
	 int             S_preamb_length;
	 int             S_header_length;
	 int             S_data_length;
	 int             S_PPDU_length;

	 std::complex<double> *S_FFTATUOpower;
	 std::complex<double> *S_FFTspectrum;

	//CProtocolB配置参数
	 int             PayloadData_size_bytes;//输入数据字节数 0~4061
	 int             PSDU_size_bytes;//PSDU 字节数 包含MAC头，payload，FCS，
	 int             data_size;
	 Data_Rate       data_rate;
	 modulationType  modulation_type;
	 preambleType    preamble_type;
	 scramblerState  scrambler_state;
	
	 //中间变量
	 int             sync_size;
	unsigned int             length;
	 int             bin_length[16];
	 vector<int>     Data;	 
	 vector<int>     sync;
	 vector<int>     SFD;
	 vector<int>     preamble;
	// vector<int>     signal;
	 unsigned char signal;
	// vector<int>     service;
	 unsigned char service;
	 vector<int>     crc;
	 vector<int>     header;                                                                                                     
	 vector<int>     msg;
	 vector<int>     CRC_bits;	
     
	 //成员函数

	 //参数配置
	 void tx_param(Encoding e);//基本参数实现函数
	  
	 //十进制转为二进制
	 void dec2bin(int obj, int bin[], int m);
	 //复数输出
	 void ComplexNumberOutput(fushu c);
	 //计算length字段
	 void length_calculate(int * LENGTH_extension,unsigned int * LENGTH_2,int PSDU_size_bytes,char service_b3,Data_Rate data_rate);
	 //计算crc字段
	 vector<int> crc_calculate(vector<int> msg);
	 //调制方式系列函数
	 void DBPSK(std::complex<double> complex_modDB[],vector<int>Data,double theta0);
	 void DQPSK(std::complex<double>complex_modDQ[],vector<int>Data,double theta0);
	 void CCK55(std::complex<double> complexOut[], vector<int> data_in,double theta);
	 void CCK11(std::complex<double> complexOut[], vector<int> data_in,double theta);
	 void PBCC55(std::complex<double> complexOut[], vector<int> data_in,double theta);
	 void PBCC11(std::complex<double> complexOut[], vector<int> data_in,double theta);
	 void repmat_PBCC_bits_55(vector<int> data_in, int Nfrm, int *convecdata,int tail_len,struct fushu *modout,double theta);
	 void repmat_PBCC_bits_11(vector<int> data_in, int Nfrm, int *convecdata,int tail_len,struct fushu *modout,double theta);
	 //卷积编码
	 int encoder(int gen[][7], int n, int L, int reg[], int m, vector<int> data_in, int inf_len, int output[]);
	 //扰码
	 void scramble(int str[], int b_index, int Nfrm, int scramble_out[], int inf_len);

	 vector<int> scrambler(vector<int>PPDU_bit);
	 // Barker扩频
	 void Barker_spread(std::complex<double> complex_barker[],std::complex<double> complex_mod[],int m) ;
	 //将数组的值赋给vector容器
	 std::vector<int> setVector(std::vector<int> vec, int temp[], int m);
	 //生成各字段数据
	 vector<int> Produce_preamb_bit(int S_preamb_length);
	 void Produce_preamb(std::complex<double> complex_preamb[],vector<int> PPDU_scrambled,std::complex<double> preamble_last_symbol[]);
	 vector<int> Produce_header_bit(int S_header_length,int bytes);
	 void Produce_header(std::complex<double> complex_header[],vector<int> PPDU_Scrambled,double theta0,std::complex<double> header_last_symbol[],std::complex<double> header_last_chip[]);
	 void Produce_PSDU(std::complex<double> complex_PSDU[],vector<int> PPDU_scrambled,double theta1,double theta2);
	 void Produce_PPDU(std::complex<double> preambpart_in[],std::complex<double> headerpart_in[],std::complex<double> datapart_in[],std::complex<double> PPDU_out[],int preamb_length,int header_length,int data_length);
	 
	 void AutoC(std::complex<double>  *discrete_seq,std::complex<double> *auto_corr,unsigned int seq_length);//自相关函数
	 void FFT(std::complex<double> *xin);
	 std::complex<double> EE(std::complex<double> a,std::complex<double> b);
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
	 //初始化函数
	 void Initialization();
	 //界面调用接口
	 void Run(vector<int>src,int data_bytelen);
	 //清除动态申请的数组等
 	 void Clear();
	 //构造
     CProtocolB();
	 //析构
	 virtual ~CProtocolB();
//protected:
//	DECLARE_MESSAGE_MAP();

};

/////////////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_PROTOCOLEOOA_H__7B2DEEBE_D5C5_4FA7_867E_AF446BDE1536__INCLUDED_)