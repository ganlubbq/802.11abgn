#ifndef WLAN_TXPARAM_H_
#define WLAN_TXPARAM_H_

#include "stdio.h"
//#include <string> 在MFC工程中使用
#include "atlstr.h"//在非MFC工程中使用
#include <iostream>
#include <vector>
#include <math.h>
#include <complex>
#include "constants_def.h"

using namespace std;

struct MCSMode//MCS信息结构体
{
	int mcs;
	vector<int> mods;  //调制方式 ，在mcs>32时，不同的流调制方式不同
	double raten;  //码率
	int nes_a;
	int ndbps;  //每个符号未编码比特数
	int ncbps;  //每个符号编码比特数
	int enc_type;
	int idx_intlvtble;
	int intlv_ncol;
	int intlv_nrow;
	int intlv_nrot;
};

struct ldpcPara
{
	int Lldpc;
	int Ncw;
	int Ncbps;
    int Navbits;    
	int K0;
	int Nsym;
    double rate;
    int Nshrt;        
	int Npunc;
    int Nrep;
	int idxCwLen;
	int idxRate;
	int n_pad;
	// the following vectors are 1-by-Ncw
	int *vNshrt;
	int *vNpunc;
	int *vNrepInt;
	int *vNrepRem;
	int *vCwLen;
};

struct paramsFather
{
	int Tx_Format;
    int idx_intlvtbl;
	int D_tm;
	int BSS_BW;
	int NFFT_oc;
	int N_20M;
	int CH_Offset;

	MCSMode MCSmodeSU;
	ldpcPara ldpcParaSU;
	
	int PDU_LEN;
	int N_sym_init;

	double WINDOWF[2];
	vector<double> WTINDEX;
	vector<double> WINDOW;

	int N_tx;
	int N_sd;
	int N_osubc;

	int N_ss;
	int N_sts;
	int N_ess;
	int N_dltf;
	int N_eltf;
	double TSAMP;
	int NFFT;
	int BSS_NFFT;
	int N_sym;
	
	int scram_seed;
	//int scram_seedOneValue;

	int BW_seg;
	int N_bwseg;
	int PS_len;
	int DS_len;
	int output_rate;

	vector<complex<double>> L_STF_20;
	vector<complex<double>> L_LTF_20;
	vector<int> Indx_dsubc_lsig;
	//vector<int> V_LTF;

	int N_ltfsubc;
	//vector<complex<double>> V_STF;

	int N_stfsubc;
	vector<int> Indx_pilot;
	vector<int> Indx_dsubc;

	vector<complex<double>> Gamma;

	int Nsym_pre;
	int Tx_Time;
	int App_Win;
	int FFTSat;
	int crc_sigb;

	vector<int> idx_segp;
};
//定义配置参数结构体
class wlan_txparam 
{
public:
	paramsFather params;//结构体
	int format;
	int NDP;//1 = Null Data packet;0 is opposite
	int BW;
	CString BW_str;
	int Ch_offset;
	int BSS_BW;
	//Equal MCS for VHT
	int MCS;
	int N_ss;
	//int N_ss_lentgh;
	int source_bit;
	int Short_GI;
	int sounding;
	int STBC;
	//int LDPC_CodingFirstValue;//1 is LDPC
	bool interleave_state;
	bool scrambler;
	int LDPC_Coding;
	int numExtenSS;
	int smoothing;
	int aggregation;
	int LSIG_PROT;
	int ANTENNA_SET;
	//int ANTENNA_SET_LENGTH;
	int N_TX;
	int ADD_CRC;//add CRC to the end of input bytes
	int applyWindow;//Option to apply time-domain window
	int windowTTR;//Window overlap time in ns

	//int MIMOmode;//MIMO 模式
	//int NUE;
	
	int Pos_UE;
	int UseBF;//0 is not beamforming

	int PAID;//a random number for the time being 0-511?

	int IND_CH_BW;// 0: not present, 1: present CH_BANDWIDTH_IN_NON_HT
	int IND_DYN_BW;//0: not present, 1: static  2: dynamic

	int ieeeQ;
	
	int TX_OP;

	int fileOutput;//produce output files at various stages of processing
	//int lsbFirst;

	int IPN;//integrated phase noise figure in degree

	int FFTSat;

	//数据源bit
	vector<int> Data;
	

	int scramSeed;

	CString FRMT_str;
	int bss_bw;
	BOOL bss_bw_flg;

	int scram_f7bit;//得到的是什么？

	int LENGTH;
	int PSDU_LENGTH;


	int ldpc_nsym_init_lt_nsym;

	int N_sts;
	
	int N_sym;
	unsigned IPNBw_3dB;
	int IPNBw_samp;
	vector<vector<vector<complex<double> > > > EXPANSION_MAT;
	vector<vector<vector<complex<double> > > >  TxBf;
	
	wlan_txparam()//构造函数
	{
		format = Legacy;//Legacy HT_MM HT_GF
		NDP    = 0;
		BW     = HT_CBW20;
		BW_str = _T("20");

		Ch_offset   = 0;
		 
		N_TX        = 3;
		MCS         = 10;
		N_ss        = 2;
		
		Short_GI    = 0;
		sounding    = 0;
		STBC        = 0;
		LDPC_Coding = 0;

		interleave_state=true;
		scrambler   = true;

		numExtenSS  = 0;
		smoothing   = 0;
		aggregation = 0;
		LSIG_PROT   = 0;
		ANTENNA_SET = 1;
		ADD_CRC     = 0;
		applyWindow = 1;
		windowTTR   = 100;
		
		PAID        = 1373;
		IND_CH_BW   = 0;
		IND_DYN_BW  = 0;

		ieeeQ       = 5;
		UseBF       = 0;
		TxBf.resize(1,vector<vector<complex<double>>> (1,vector<complex<double>> (64)));
		for(int i=0;i<64;i++)
			TxBf[0][0][i] = 1;
		TX_OP       = 0;
		
		fileOutput  = 0;
		//lsbFirst    = 0;

		IPN         = 0;

		FFTSat      = 0;
		

		scramSeed   = 0x59;//matlab中有函数hex2dec(59),将16进制转化成10进制值

		ldpc_nsym_init_lt_nsym = 0;

		N_sts = 2;
	};
	~wlan_txparam()//析构函数
	{

	}
	void handlingFunction();

};

#endif