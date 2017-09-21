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
//#include "../../crc16.h"���ͷ�ļ����������⣬�д������
#include "configB.h"
using namespace std;

//#define PI 3.141592653589793 
//#define pi 3.141592653589793 
//#define BYTE_B 8
//#define LEN(array, len){len=sizeof(array)/sizeof(array[0]);}//�������鳤��
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

////ö��������״̬�������غ�ֻǰ������
// enum scramblerState
// {
//	ON = 0,
//	OFF = 1,
//	Preamble_only = 2
// };
//
////ö��ǰ�����ͣ�������
//enum preambleType 
//{
//	shortPreamble = 0,
//	longPreamble = 1
//};
//
////ö�ٵ�������
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
////ö����������
//enum Data_Rate
//{
//	_1Mbps = 1,
//	_2Mbps = 2,
//	_55Mbps = 55,
//	_11Mbps = 11,
//};

/////////////////////////////////////////////////////////////////////////////
// CProtocolB window


//����11b���Ͷ˲�����
class CProtocolB 
{
	//�ŵ���ز���
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
	//ָ������ֵ�ָ�뼰���γ���
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

	//CProtocolB���ò���
	 int             PayloadData_size_bytes;//���������ֽ��� 0~4061
	 int             PSDU_size_bytes;//PSDU �ֽ��� ����MACͷ��payload��FCS��
	 int             data_size;
	 Data_Rate       data_rate;
	 modulationType  modulation_type;
	 preambleType    preamble_type;
	 scramblerState  scrambler_state;
	
	 //�м����
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
     
	 //��Ա����

	 //��������
	 void tx_param(Encoding e);//��������ʵ�ֺ���
	  
	 //ʮ����תΪ������
	 void dec2bin(int obj, int bin[], int m);
	 //�������
	 void ComplexNumberOutput(fushu c);
	 //����length�ֶ�
	 void length_calculate(int * LENGTH_extension,unsigned int * LENGTH_2,int PSDU_size_bytes,char service_b3,Data_Rate data_rate);
	 //����crc�ֶ�
	 vector<int> crc_calculate(vector<int> msg);
	 //���Ʒ�ʽϵ�к���
	 void DBPSK(std::complex<double> complex_modDB[],vector<int>Data,double theta0);
	 void DQPSK(std::complex<double>complex_modDQ[],vector<int>Data,double theta0);
	 void CCK55(std::complex<double> complexOut[], vector<int> data_in,double theta);
	 void CCK11(std::complex<double> complexOut[], vector<int> data_in,double theta);
	 void PBCC55(std::complex<double> complexOut[], vector<int> data_in,double theta);
	 void PBCC11(std::complex<double> complexOut[], vector<int> data_in,double theta);
	 void repmat_PBCC_bits_55(vector<int> data_in, int Nfrm, int *convecdata,int tail_len,struct fushu *modout,double theta);
	 void repmat_PBCC_bits_11(vector<int> data_in, int Nfrm, int *convecdata,int tail_len,struct fushu *modout,double theta);
	 //�������
	 int encoder(int gen[][7], int n, int L, int reg[], int m, vector<int> data_in, int inf_len, int output[]);
	 //����
	 void scramble(int str[], int b_index, int Nfrm, int scramble_out[], int inf_len);

	 vector<int> scrambler(vector<int>PPDU_bit);
	 // Barker��Ƶ
	 void Barker_spread(std::complex<double> complex_barker[],std::complex<double> complex_mod[],int m) ;
	 //�������ֵ����vector����
	 std::vector<int> setVector(std::vector<int> vec, int temp[], int m);
	 //���ɸ��ֶ�����
	 vector<int> Produce_preamb_bit(int S_preamb_length);
	 void Produce_preamb(std::complex<double> complex_preamb[],vector<int> PPDU_scrambled,std::complex<double> preamble_last_symbol[]);
	 vector<int> Produce_header_bit(int S_header_length,int bytes);
	 void Produce_header(std::complex<double> complex_header[],vector<int> PPDU_Scrambled,double theta0,std::complex<double> header_last_symbol[],std::complex<double> header_last_chip[]);
	 void Produce_PSDU(std::complex<double> complex_PSDU[],vector<int> PPDU_scrambled,double theta1,double theta2);
	 void Produce_PPDU(std::complex<double> preambpart_in[],std::complex<double> headerpart_in[],std::complex<double> datapart_in[],std::complex<double> PPDU_out[],int preamb_length,int header_length,int data_length);
	 
	 void AutoC(std::complex<double>  *discrete_seq,std::complex<double> *auto_corr,unsigned int seq_length);//����غ���
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
	 //��ʼ������
	 void Initialization();
	 //������ýӿ�
	 void Run(vector<int>src,int data_bytelen);
	 //�����̬����������
 	 void Clear();
	 //����
     CProtocolB();
	 //����
	 virtual ~CProtocolB();
//protected:
//	DECLARE_MESSAGE_MAP();

};

/////////////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_PROTOCOLEOOA_H__7B2DEEBE_D5C5_4FA7_867E_AF446BDE1536__INCLUDED_)