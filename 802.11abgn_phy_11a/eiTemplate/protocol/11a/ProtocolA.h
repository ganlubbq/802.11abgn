#if !defined(AFX_PROTOCOLEOOA_H__7B2DEEBE_D5C5_4FA7_867E_AF446BDE1536__INCLUDED_)
#define AFX_PROTOCOLEOOA_H__7B2DEEBE_D5C5_4FA7_867E_AF446BDE1536__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProtocolEOOA.h : header file
//
#include <iostream>
#include <climits>
#include <string>
#include <complex>
#include <iosfwd>
#include <assert.h>
#include "configA.h"
#include <vector>
using namespace std;
/////////////////////////////////////////////////////////////////////////////
// CProtocolA window
//typedef std::complex<double> complex;

class CProtocolA : public CStatic
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
	configA AprotocolConfig;
	std::complex<double> *S_preambpart;
	std::complex<double> *S_singalpart;
	std::complex<double> *S_datapart;
	std::complex<double> *S_PPDU;
	int     S_preamb_length;
	int     S_singal_length;
	int     S_data_length;
	int     S_PPDU_length;

	std::complex<double> *S_FFTATUOpower;
	std::complex<double> *S_FFTspectrum;
public:
	//ofdm_param参数
	Encoding encoding;// data rate
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
	char    Test_data[132];//测试信号段
	//char    Test_data[10];
	std::complex<double> BPSK_D[2];
	std::complex<double> QPSK_D[4];
	std::complex<double> QAM16_D[16];
	std::complex<double> QAM64_D[64];
	std::complex<double> Seq_P53[53];
	std::complex<double> Seq_p126[127];

public:
	//ifft
	void ifft(std::complex<double> f[]);
	void bitrp (vector<complex<double>>  &Data_In, int n);
	void  IFFT (vector<complex<double>> &Data_in, int n);
	
	void Produce_preamb(std::complex<double> complex_preamb[]);//报头
	void reshape_data(std::complex<double> complex_out[],std::complex<double> complex_in[],int index); //进入48位数据，输出64位数据
	void add_recycle(std::complex<double> complex_out[],std::complex<double> complex_in[],int sample_rate);//增加循环前缀
	
	void Produce_singal(std::complex<double> complex_singal[],int * Q_pinter,int data_length);//Signal部分
	int  ones(int n);
	void Bit_to_bit(char Bitdata[],char bitdata[],int bit_length);
	void scramble(const char *in, char *out,int initial_state);//扰码
	void reset_tail_bits(char *scrambled_data);//尾比特
	void convolutional_encoding(const char *in, char *out,int data);//调制
	void puncturing(const char *in, char *out);//打孔
	void interleave(const char *in, char *out, bool reverse);//交织
	void symbol_mapping(const char map_in[], std::complex<double> map_out[]);//映射
	//data域数据
	void Produce_data(char char_datain[],std::complex<double> complex_dataout[],int * Q_pinter,int data_length);
	//PPDU数据
	void Produce_PPDU(std::complex<double> preambpart_in[],std::complex<double> singalpart_in[],std::complex<double> datapart_in[],std::complex<double> PPDU_out[],int preamb_length,int singal_length,int data_length);
	void AutoC(std::complex<double> *discrete_seq,std::complex<double> *auto_corr,unsigned int seq_length);//自相关函数
	void FFT(std::complex<double> *xin);
	std::complex<double> EE(std::complex<double> a,std::complex<double> b);
	void channel_initialize_1(double RndPhase[][12], double *Path_Delay, double *Path_Average_Amp, double *fore_data_pr, double *fore_data_pi, \
		double* RMS_Delay_Sample, double MAX_Delay_Sample, int NumOfTaps, double *Path_Average_Power, \
		int sizeof_Path_Delay, int sizeof_Path_Average_Power);
	void Jakes_kernel(double Path_Ampli,int NumOfFreq,int UpdateInterval,double fd_max,double* Phase,\
		int UpdatesPerBurst,int LengthOfBurst,int t_tmp,\
		double dt,vector<double> &fading_re,vector<double> &fading_im);
	void multipath_channel(double *InData_pr,double *InData_pi,\
		double fd_max,long NumOfTaps,\
		int SamplesPerFrame,int ChangesPerFrame,\
		int* TimeIndex,double dt,\
		double Phase[][12],double *Path_Delay,double *Path_Average_Amp,\
		vector<double> &OutData_pr,vector<double> &OutData_pi,\
		double *out_fading_pr,double *out_fading_pi,\
		double *fore_data_pr,double *fore_data_pi,\
		double *fading_indx);
public:
	void Initialization();
	void Run(vector<int> src,int data_bytelen);
	void Clear();
public:
	CProtocolA();
public:
	virtual ~CProtocolA();
protected:
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_PROTOCOLEOOA_H__7B2DEEBE_D5C5_4FA7_867E_AF446BDE1536__INCLUDED_)
