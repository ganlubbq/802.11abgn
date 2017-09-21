#include "stdafx.h"
#include "wlan_txparam.h"
#include "wlan_const_set.h"
#include "transform_bits_num.h"
#include "E_HT_MCStable.h"
#include "ldpc_encode.h"
#include "Qmatrix_gen.h"
#include "primaryFunctionalFunc.h"
#include "constants_def.h"
#include <stdexcept>
#include <numeric>
#include <algorithm>

using namespace std;

void wlan_txparam::handlingFunction()
{
	wlan_consts consts1;

	//常量数组赋值
	wlan_consts consts=wlan_constsValue(consts1);

	//LENGTH derived from data
	params.PDU_LEN = PSDU_LENGTH = Data.size()/8;//数据源长度，字节为单位
	source_bit = Data.size()+16;
	////LSB first
	//if (lsbFirst != 0)
	//{
	//	int Len = PSDU_LENGTH;
	//	int *in = new int[Len];
	//	int *out = new int[Len];
	//	copy(Data.cbegin(),Data.cend(),in);
	//	bitrev(in,Len,8,out);
	//	copy(out,out+Len,Data.begin());
	//	delete [] in;
	//	delete [] out;
	//}

	//增加CRC校验，MAC配置会用到
	if (ADD_CRC == 1)
	{
		int Len = PSDU_LENGTH*8;
		int *in = new int[Len];
		int *out = new int[Len];
		copy(Data.cbegin(),Data.cend(),in);
		out = crc32(in,Len);
		copy(out,out+Len,Data.begin());
		delete [] in;
		delete [] out;
	}

	//天线数 >= 空间流,调整天线数
	if(N_TX<N_ss)
		N_TX=N_ss;

	if (sounding == 1)
		ieeeQ = 0;// unitary spatial mapping

	// scram seed table
	/*int b_in[7]={0};
	int seed_table[127]={0};
	int *scram_out;
	int *b2n;
	for (int seedI = 1;seedI <= 127;seedI++)
	{
	scram_out = scram_t(seedI,b_in,7);
	b2n = bits2numv(scram_out,7,7);
	seed_table[*b2n-1] = seedI;
	}
	delete [] scram_out;*/
	
	int idx_intlvtbl = 0;//交织相关参数
	int tx_bw = 0;       //带宽速率配置
	int bss_bw = 0;
	int output_rate = 0;
	int ch_bw = 0;
	
	switch(format)
	{
	case 0://NON_HT:
		FRMT_str = _T("Legacy");
		params.Tx_Format = E_LEG20M;
		idx_intlvtbl = 1;

		if (BW_str == _T("20")) //没有区分up lower
		{
			BW = NON_HT_CBW20;
			tx_bw = 20;
		}
		else if (BW_str == _T("40")) //Duplicate
		{
			BW = NON_HT_CBW40;
			tx_bw = 40;
		}
		
		if(bss_bw)
			params.BSS_BW = bss_bw;
		else
			params.BSS_BW = tx_bw;

		output_rate = params.BSS_BW;
		params.NFFT_oc = 64*tx_bw/20;

		int *bit_f7bit;

		/************************************************************************/
		if (IND_CH_BW == 1)  //IND_CH_BW代表什么
		{
			bit_f7bit = num2bitsv(&scramSeed,1,7);
			
			if (IND_DYN_BW == 2)
				bit_f7bit[4] = 1;
			if (IND_DYN_BW == 1)
				bit_f7bit[4] = 0;
		
			bit_f7bit[5] = 0;
			bit_f7bit[6] = 0;
			int *num_f7bit  = bits2numv(bit_f7bit,7, 7);//两个函数类型不一致，一个int，一个double，而且都是指针！
			//scramSeed = seed_table[*num_f7bit-1];//有问题！
			scram_f7bit = *num_f7bit;
		}
		/************************************************************************/
		break;
	//case 10://E_NON_HT_DUP:
	//	{
	//	FRMT_str = _T("non_HT_DUP");
	//	params.Tx_Format = E_LEG20M;
	//	idx_intlvtbl = 1;
	//	int *bitrev_in = new int [1];
	//	if (BW_str == _T("20"))
	//	{
	//		BW = NON_HT_CBW20;
	//		tx_bw = 20;
	//		*bitrev_in = 1;
	//	}

	//	else if (BW_str == _T("40"))
	//	{
	//		BW = NON_HT_CBW40;
	//		tx_bw = 40;
	//		*bitrev_in = 2;
	//	}

	//	if(bss_bw)
	//		params.BSS_BW = bss_bw;
	//	else
	//		params.BSS_BW = tx_bw;

	//	output_rate = params.BSS_BW;
	//	params.NFFT_oc = 64*tx_bw/20;

	//	if (IND_CH_BW == 1)
	//	{
	//		bit_f7bit = num2bitsv(&scramSeed,1,7);
	//		if (IND_DYN_BW == 2)
	//			bit_f7bit[4] = 1;
	//		if (IND_DYN_BW == 1)
	//			bit_f7bit[4] = 0;
	//		int *out;
	//		bitrev(bitrev_in,1,2,out);
	//		int *bit_f7bitIndex = num2bitsv(out,1,2);
	//		bit_f7bit[5] = bit_f7bitIndex[0];
	//		bit_f7bit[6] = bit_f7bitIndex[1];
	//		int *num_f7bit  = bits2numv(bit_f7bit,7, 7);//两个函数类型不一致，一个int，一个double，而且都是指针！
	//		scramSeed = seed_table[*num_f7bit-1];//有问题！
	//		scram_f7bit = *num_f7bit;
	//	}
	//	}
	//	break;

	case 1://E_HT_MF:
	case 2://E_HT_GF:
		if (format == HT_MM)
			FRMT_str = _T("HT_MM");
		else
			FRMT_str = _T("HT_GF");
		if (BW_str == _T("20"))
		{
			params.Tx_Format = E_HT20M;
			BW = HT_CBW20;
			tx_bw = 20;
			idx_intlvtbl = 2;
		}
		else if (BW_str = _T("40"))
		{
			params.Tx_Format = E_HT40M;
			BW = HT_CBW40;
			tx_bw = 40;
			idx_intlvtbl = 3;
		}

		if(bss_bw)
			params.BSS_BW = bss_bw;
		else
			params.BSS_BW = tx_bw;

		if (MCS == 32)
			idx_intlvtbl = 1;

		output_rate = params.BSS_BW;
		ch_bw = consts.BW_per_bw_seg[params.Tx_Format];
		params.NFFT_oc = 64*ch_bw/20;
		break;

	default:
		break;
    }

    params.idx_intlvtbl = idx_intlvtbl;

	if (Ch_offset == 0)
		Ch_offset = 0;
	else if (Ch_offset > 0)
		Ch_offset = Ch_offset*2 - 1;
	else
		Ch_offset = Ch_offset*2 + 1;

	//FEC, OFDM modulation parameters

	switch(format)
	{
	case 0://calculate FEC (BCC) parameters
		{
			if(!(MCS<8 && MCS>=0))
				throw invalid_argument("MCS must be in[0,7]");
			int i_mcs = MCS;
			int mcs_typ_row = 8;
			int *p_mcs_typ_row = &mcs_typ_row;
			
			//mcs二维信息表 8*8
			int **mcs_tbl = new int *[mcs_typ_row];
			for(int i = 0; i < mcs_typ_row; i++)
				mcs_tbl[i] = new int[8];

			N_ss = 1;
			N_sts = 1;
			mcs_tbl_ac(params.Tx_Format,N_ss,p_mcs_typ_row,mcs_tbl);
			
			params.MCSmodeSU.mcs = MCS;
			params.MCSmodeSU.mods.push_back(mcs_tbl[i_mcs][0]);
			params.MCSmodeSU.raten = (double)mcs_tbl[i_mcs][3]/(double)mcs_tbl[i_mcs][2];
			params.MCSmodeSU.nes_a = mcs_tbl[i_mcs][4];
			params.MCSmodeSU.ndbps = mcs_tbl[i_mcs][3];
			params.MCSmodeSU.ncbps = mcs_tbl[i_mcs][2];

			params.MCSmodeSU.idx_intlvtble = idx_intlvtbl;
			params.MCSmodeSU.intlv_ncol = consts.intlv_param[0][idx_intlvtbl-1];
			params.MCSmodeSU.intlv_nrow = params.MCSmodeSU.ncbps /16;
			params.MCSmodeSU.intlv_nrot = consts.intlv_param[2][idx_intlvtbl-1];
			params.MCSmodeSU.enc_type = 0;
		}
		break;

	case 1://E_HT_MF:
	case 2://E_HT_GF:
		{
		vector<MCSpara> mcs20;
	    vector<MCSpara> mcs40;
		HT_MCSvalue(mcs20,mcs40);  //mcs table constructed

		if (BW == HT_CBW20)
		{
			params.MCSmodeSU.mcs = MCS;
			int count = 0;
			for(int i=0;i<4;i++)
			{
				if(mcs20[0].mods[MCS][i])
				{
					params.MCSmodeSU.mods.push_back(mcs20[0].mods[MCS][i]);
					count++;
				}
			}

			N_ss = count;     //不同mcs的空间流数获取，根据mcs的mods确定

			params.MCSmodeSU.raten = mcs20[0].raten[MCS];
			params.MCSmodeSU.nes_a = mcs20[0].nes[MCS][Short_GI];
			params.MCSmodeSU.ndbps = mcs20[0].ndbps[MCS];
		}
		else if(BW == HT_CBW40)
		{
			params.MCSmodeSU.mcs = MCS;
			int count = 0;
			for(int i=0;i<4;i++)
			{
				if(mcs40[0].mods[MCS][i])
				{
					params.MCSmodeSU.mods.push_back(mcs40[0].mods[MCS][i]);
					count++;
				}
			}

			N_ss = count;

			params.MCSmodeSU.raten = mcs40[0].raten[MCS];
			params.MCSmodeSU.nes_a = mcs40[0].nes[MCS][Short_GI];
			params.MCSmodeSU.ndbps = mcs40[0].ndbps[MCS];
		}

		params.MCSmodeSU.ncbps = params.MCSmodeSU.ndbps/params.MCSmodeSU.raten;
		params.MCSmodeSU.idx_intlvtble = idx_intlvtbl;
		params.MCSmodeSU.intlv_ncol = consts.intlv_param[0][idx_intlvtbl-1];
		params.MCSmodeSU.intlv_nrow = consts.intlv_param[1][idx_intlvtbl-1];
		params.MCSmodeSU.intlv_nrot = consts.intlv_param[2][idx_intlvtbl-1];
		params.MCSmodeSU.enc_type = 0;

		N_sts = STBC + N_ss;  //？？ 空时流个数
		}
		break;
	}

	int N_osubc = consts.N_tones_per_modtype[params.Tx_Format];//还是结构体/类对象consts
	int N_sd;
	if(format==1||format==2)
	{
		if (MCS == 32)
			N_sd = 48;
		else
			N_sd = consts.N_sd_per_modtype[params.Tx_Format];
	}
	else
		N_sd = consts.N_sd_per_modtype[params.Tx_Format];

	int N_ess = numExtenSS;  //扩展空间流
	int N_dltf = (N_sts == 3)*4 + (N_sts != 3)*N_sts;
	int N_eltf = (N_ess == 3)*4 + (N_ess != 3)*N_ess;

	int ldpc_nsym_init_lt_nsymindex = 0;
	int m_stbc = 0;
	int Nsym_init = 0;
	switch(format)
	{
	case 0://E_NON_HT:
	case 10://E_NON_HT_DUP:
		{
			LENGTH = PSDU_LENGTH;
			
			N_sym = ceil((double)(8*PSDU_LENGTH+16+6)/params.MCSmodeSU.ndbps);

			Nsym_init = N_sym;
			params.N_sym_init = Nsym_init;
			//[service source pad_and_tail]
			// 16 位 Service 比特
			Data.insert(Data.begin(),16,0);
			//pad_and_tail
			for(int i= 0;i<N_sym*params.MCSmodeSU.ndbps-8*LENGTH-16;i++)
				Data.push_back(0);

		}
		break;
	case 1://E_HT_MF:
	case 2://E_HT_GF://PDU_LENGTH<65535  和MATLAB源码可以对上
		if (NDP == 1)
			LENGTH = 0;
		else
			LENGTH = PSDU_LENGTH;
		if (STBC != 0)
			m_stbc = 2;
		else
			m_stbc = 1;

		//计算ofdm符号个数
		if (LDPC_Coding == 0)
		{
			N_sym = m_stbc*ceil((double)(8*LENGTH+16+6*params.MCSmodeSU.nes_a)/m_stbc/params.MCSmodeSU.ndbps);
			Nsym_init = N_sym;
			params.N_sym_init = Nsym_init;
			//[service source pad_and_tail]
			// 16 位 Service 比特
			Data.insert(Data.begin(),16,0);
			//pad_and_tail
			for(int i= 0;i<N_sym*params.MCSmodeSU.ndbps-8*LENGTH-16;i++)
				Data.push_back(0);
		}
		else
		{
			Nsym_init = m_stbc*ceil((double)(8*LENGTH+16)/m_stbc/params.MCSmodeSU.ndbps);
			params.N_sym_init = Nsym_init;
			
			params.ldpcParaSU = ldpc_encpara_g(8*LENGTH, params. MCSmodeSU, m_stbc);
			params.ldpcParaSU.n_pad = Nsym_init*params.MCSmodeSU.ndbps - PSDU_LENGTH*8 - 16;
				
			N_sym =params.ldpcParaSU.Nsym;
		}
		break;
	}

	//*************** Windowing Parameters ***************
	double T_TR;
	double T;

	vector<double> n_pre;
	vector<double> n_mid;
	vector<double> n_pos;
	vector<double> t;
	vector<double> w_pre;
	vector<double> w_mid;
	vector<double> w_pos;

	int Num = 0;

	switch(applyWindow)
	{
	case 0:
	case 1:
		params.WINDOWF[0]=params.WINDOWF[1] = 0.5;
		break;
	case 2:
		T_TR = windowTTR*0.0000000001;
		if (Short_GI)
			T = 0.0000032;
		else
			T = 0.000004;

		n_pre.resize(T_TR/2 * output_rate*1000000-1,0);
		t.resize(T_TR/2 * output_rate*1000000-1,0);
		w_pre.resize(T_TR/2 * output_rate*1000000-1,0);

		n_mid.resize((T - T_TR/2) * output_rate*1000000 - 1 - T_TR/2 * output_rate*1000000,0);

		n_pos.resize((T + T_TR/2) * output_rate*1000000 - 1 - (T - T_TR/2) * output_rate*1000000,0);
		w_mid.resize((T + T_TR/2) * output_rate*1000000 - 1 - (T - T_TR/2) * output_rate*1000000,1);
		w_pos.resize((T + T_TR/2) * output_rate*1000000 - 1 - (T - T_TR/2) * output_rate*1000000,0);

		Num = T_TR/2 * output_rate*1000000-1+(T - T_TR/2) * output_rate*1000000 - 1 - T_TR/2 * output_rate*1000000+(T + T_TR/2) * output_rate*1000000 - 1 - (T - T_TR/2) * output_rate*1000000;
		params.WTINDEX.resize(Num,0);
		params.WINDOW.resize(Num,0);

		for (int i=1;i != T_TR/2 * output_rate*1000000-1;i++)
		{
			n_pre[i-1] = -T_TR/2 * output_rate*1000000 + i;
			t[i-1] = n_pre[i-1]/(output_rate*1000000);
			w_pre[i-1] = pow(sin(pi_/2 * (0.5 + t[i-1]/T_TR)),2);

			params.WTINDEX[i-1] = n_pre[i-1];
			params.WINDOW[i-1] = w_pre[i-1];
		}

		for (int i = T_TR/2 * output_rate*1000000;i != (T - T_TR/2) * output_rate*1000000 - 1;i++)
		{
			n_mid[i-T_TR/2 * output_rate*1000000] = i;
			params.WTINDEX[T_TR/2 * output_rate*1000000-1+i-T_TR/2 * output_rate*1000000] = n_mid[i-T_TR/2 * output_rate*1000000];
			params.WINDOW[T_TR/2 * output_rate*1000000-1+i-T_TR/2 * output_rate*1000000] = 1;
		}

		for (int i = (T - T_TR/2) * output_rate*1000000;i != (T + T_TR/2) * output_rate*1000000 - 1;i++)
		{
			n_pos[i-(T - T_TR/2) * output_rate*1000000] = i;
			w_pos[i-(T - T_TR/2) * output_rate*1000000] = pow(sin(pi_/2 * (0.5-(n_pos[i-(T - T_TR/2) * output_rate*1000000]/(output_rate*1e6)-T)/T_TR)),2);
		
			params.WTINDEX[T_TR/2 * output_rate*1000000-1+(T + T_TR/2) * output_rate*1000000 - 1 - (T - T_TR/2) * output_rate*1000000+i-(T - T_TR/2) * output_rate*1000000] = n_pos[i-(T - T_TR/2) * output_rate*1000000];
			params.WINDOW[T_TR/2 * output_rate*1000000-1+(T + T_TR/2) * output_rate*1000000 - 1 - (T - T_TR/2) * output_rate*1000000+i-(T - T_TR/2) * output_rate*1000000] = w_pos[i-(T - T_TR/2) * output_rate*1000000];
		}
		
		break;
	}


	// *************** TXVECTOR ***************
	//check_txvector
	int num_seg = consts.Num_BW_seg[params.Tx_Format];
	int bw_seg  = consts.BW_per_bw_seg[params.Tx_Format];

	params.N_20M  = params.NFFT_oc/64;
	params.BW_seg = bw_seg;
	params.N_bwseg = num_seg;

	double TSAMP = 1000/output_rate;//sampling interval，ns
	int NFFT = bw_seg/20*64; //FFT length

	params.N_tx = N_TX;
	params.N_sd = N_sd;
	params.N_osubc = N_osubc;

	params.N_ss = N_ss;
	params.N_sts = N_sts;
	params.N_ess = N_ess;
	params.N_dltf = N_dltf;
	params.N_eltf = N_eltf;

	params.TSAMP = TSAMP;
	params.NFFT = NFFT;
	params.BSS_NFFT = 64*params.BSS_BW/20;

	int idx_ofset = params.BSS_NFFT/2 + (Ch_offset-1)*params.NFFT_oc/2 + 1;
	if (!(idx_ofset>0)&&(idx_ofset<=params.BSS_NFFT))
		puts("Invalid Offset");
	//这两句属于判断异常语句，可不写。
	params.N_sym = N_sym;//以下需分单用户/多用户情况
	params.CH_Offset = Ch_offset;
	params.scram_seed = scramSeed;
	params.output_rate = output_rate;

	int PSLEN = params.BSS_NFFT*(1+0.25);
	int DSLEN = 0;
	if (Short_GI)
		DSLEN = params.BSS_NFFT*(1+0.125);
	else
		DSLEN = params.BSS_NFFT*(1+0.25);
	
	params.PS_len = PSLEN;
	params.DS_len = DSLEN;

	complex<double> L_STF_20[53];
	params.L_STF_20.resize(53,0);   //L-STF
	params.L_LTF_20.resize(64,0);   //L-LTF
	params.Indx_dsubc_lsig.resize(48,0);//L-SIG
	for (int i=0;i<53;i++)
		params.L_STF_20[i]=L_STF_20[i] = consts.L_STF_20[i];
	for (int i=0;i<6;i++)
		params.L_LTF_20[i] = 0;
	for (int i=0;i<53;i++)
		params.L_LTF_20[i+6] = consts.L_LTF_20[i];
	for (int i=0;i<5;i++)
		params.L_LTF_20[i+59] = 0;

	for (int i=0;i<48;i++)
		params.Indx_dsubc_lsig[i] = consts.idx_dsubc_20leg[i];

	vector<complex<double>> L_STF_40;

	switch(params.Tx_Format)
	{
	case 0://E_LEG20M:
		params.Indx_pilot.resize(4,0);
		params.Indx_dsubc.resize(48,0);
		params.N_stfsubc = 12;
		for (int i=0;i<4;i++)
			params.Indx_pilot[i] = consts.Idx_pilot_20[i];

		for (int i=0;i<48;i++)
			params.Indx_dsubc[i] = consts.idx_dsubc_20leg[i];

		break;
	case 1://E_HT20M:
		params.Indx_pilot.resize(4,0);
		params.Indx_dsubc.resize(52,0);
		for (int i=0;i<4;i++)
			params.Indx_pilot[i] = consts.Idx_pilot_20[i];
		for (int i=0;i<52;i++)
			params.Indx_dsubc[i] = consts.idx_dsubc_20[i];
		break;
	case 2://E_HT40M:
		if (MCS == 32)
		{
			params.Indx_pilot.resize(4,0);
			params.Indx_dsubc.resize(48,0);
			for (int i=0;i<4;i++)
				params.Indx_pilot[i] = consts.Idx_pilot_20[i];

			for (int i=0;i<48;i++)
				params.Indx_dsubc[i] = consts.idx_dsubc_20leg[i];
		}
		else
		{
			params.Indx_pilot.resize(6,0);
			params.Indx_dsubc.resize(108,0);
			for (int i=0;i<6;i++)
				params.Indx_pilot[i] = consts.Idx_pilot_40[i];

			for (int i=0;i<108;i++)
				params.Indx_dsubc[i] = consts.idx_dsubc_40[i]+1;

		}
		break;
	}

	/********************************Gamma用于Legacy 复用模式 40M *****************************************************/
	switch(params.N_20M)
	{
	case 1:
		params.Gamma.resize(1);                  //20M无相位旋转 
		params.Gamma[0] = consts.Gamma_20;// =1
		break;
	case 2:                                     //40M Legacy
		params.Gamma.resize(2);
		for (int i=0;i<2;i++)
			params.Gamma[i] = consts.Gamma_40[i][0];
		break;
	/***********************ac*****************************/
	case 4:
		params.Gamma.resize(4);
		for (int i=0;i<4;i++)
			params.Gamma[i] = consts.Gamma_80[i][0];
		break;
	case 8:
		params.Gamma.resize(8);
		for (int i=0;i<8;i++)
			params.Gamma[i] = consts.Gamma_160[i][0];
		break;
	}

	if (UseBF==1)
		ieeeQ = 2;
	if(ieeeQ!=2)
	{
		int TxBf1=(int)TxBf.size();
		int TxBf2=(int)TxBf[0].size();
		for(int i=0;i<(int)TxBf.size();i++)
		{
			if((params.N_ess+params.N_sts)==0)
				TxBf[i].resize(1, vector<complex<double> >(params.NFFT));
			else
			    TxBf[i].resize(params.N_ess+params.N_sts, vector<complex<double> >(params.NFFT));
			for(int j=0;j<TxBf2;j++)
				TxBf[i][j].resize(params.NFFT);
		}
		TxBf.resize(params.N_tx, vector<vector<complex<double>  > >
			(params.N_ess+params.N_sts, vector<complex<double> >(params.NFFT)));
	}
	if (params.Tx_Format != 0)//E_LEG20M;
	{
		Txvector_Q txvector_Q; 
		Params_Q params_Q;
		txvector_Q.FORMAT = format;
		txvector_Q.ieee_Q = ieeeQ;
		
		params_Q.NFFT = params.NFFT;
		params_Q.N_ess = params.N_ess;
		params_Q.N_sts = params.N_sts;
		params_Q.N_tx = params.N_tx;
		txvector_Q.TxBf.resize(params_Q.N_tx, vector<vector<complex<double>  > >
			(params_Q.N_ess+params_Q.N_sts, vector<complex<double> >(params_Q.NFFT)));
		for(int i=0;i<params_Q.N_tx;i++)
			for(int j=0;j<params_Q.N_ess+params_Q.N_sts;j++)
				for(int k=0;k<params_Q.NFFT;k++)
					txvector_Q.TxBf[i][j][k] = TxBf[i][j][k];
		EXPANSION_MAT.resize(params_Q.N_tx, vector<vector<complex<double>  > >
			(params_Q.N_ess+params_Q.N_sts, vector<complex<double> >(params_Q.NFFT)));
		Qmatrix_gen (txvector_Q, params_Q, EXPANSION_MAT);
	}
		
	int N_ltf = 0;
	int Tx_Time = 0;
	int tx_preamble = 0;
	int tx_dat = 0;
	switch(params.Tx_Format)
	{
	case 1://E_HT20M:
	case 2://E_HT40M:
		if (format == HT_MM)
			tx_preamble = 16 + 4 + 8 + 4 + N_dltf*4 + N_eltf*4;
		else
			tx_preamble = 8*3 + N_dltf*4 + N_eltf*4;

		if (Short_GI != 0)
			tx_dat = 4*ceil(Nsym_init*3.6/4);
		else 
			tx_dat = 4*Nsym_init;

		Tx_Time = tx_preamble + tx_dat;
		params.Nsym_pre = tx_preamble/4;
		break;
	case 0://E_LEG20M:
		if (Short_GI != 0)
			Tx_Time = 16 + 4 + 4*ceil(N_sym*3.6/4);
		else
			Tx_Time = 16 + 4 + N_sym*4;
		params.Nsym_pre = 5;
		break;
	}
	params.Tx_Time = Tx_Time;
	params.App_Win = applyWindow;
	params.FFTSat = FFTSat;
	params.crc_sigb = 0;

	BSS_BW  = params.BSS_BW;
	//txvector.Gamma   = params.Gamma;

	IPNBw_3dB  = 20e3;
	IPNBw_samp = BSS_BW;
	//需再议
}