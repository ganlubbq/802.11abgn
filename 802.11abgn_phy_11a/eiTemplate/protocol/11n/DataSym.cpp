/*----------------------------------------------------
 Function Description: 11n transmitter wrapper
---------------------------------------------------
History:
Created by hxy   Date:2014-12-4    Version:1.0
----------------------------------------------------
Function List:
---------------------------------------------------
 Input Parameters:
      txvector, params, consts  
----------------------------------------------------
Output Parameters:
      osym_t : n_seg x n_sym cells
	   each cell contains n_tx x n_sample time domain waveform
---------------------------------------------------*/
//把LDPC参数单独定义一个结构体？？？
//编码函数输出的数据长度定义成全局变量，用在stream_parser()函数中
#include "stdafx.h"
#include "DataSym.h"
#include "scramble.h"
vector<vector<int>> bcc_encoder(int *byte_in,int L, int length,MCSMode enc_str, int scram_seed, int &N_sym, int crc_sigb,int source_len);
vector<int> ldpc_encoder(int *byte_in,int Length,MCSMode enc_str,ldpcPara ldpc_para,int scram_seed,int crc_sigb);
int **stream_parser(vector<vector<int>> bitenc_penc,vector<int> n_bpscs,int n_ss,int n_es);

Vec_compA_3D DataSym_11n(wlan_txparam txvector,paramsFather params,wlan_consts consts)
{
	int n_tx = params.N_tx;
    int NFFT  = params.NFFT;
    int n_20  = params.N_20M;
    double TSAMP = params.TSAMP;
    int n_sd  = params.N_sd;
	int N_sym = params.N_sym;
	//valarray<int> myvalarray (params.N_ss,N_UE);
	int N_es;
	int n_sts = params.N_sts;
	int n_ss = txvector.N_ss;
	int Gamma_len = params.Gamma.size();
	vector<complex<double>> Gamma(Gamma_len);
    for(int i = 0;i<(int)Gamma_len;i ++ )
		Gamma[i] = params.Gamma[i];
	
	//data ofdm symbol generation
	
	int idx_ss = 0;
	vector<vector<int> > bit_enc;
	int **bitss_out;
	int **bitilv_out;

	int mods_len = params.MCSmodeSU.mods.size();
	vector<int> n_bpscs(mods_len);
	for(int i = 0;i<(int)mods_len;i ++ )
		n_bpscs[i] = params.MCSmodeSU.mods[i];

	//扰码
	//int *data = new int[txvector.Data.size()];
	//int *datatmp = new int[txvector.Data.size()+16];
	
	//int *data;

	
        int *dataldpc = new int[txvector.Data.size()+16];
	
        int *data = new int[txvector.Data.size()];
	

	if(txvector.LDPC_Coding == 1)
	{
		
		vector<int> datatmp;
		datatmp.resize(txvector.Data.size()+16);
	    for(int m=0;m<16;m++)
	    {
		    datatmp[m]=0;
	    }
	    for(int m=16;m<txvector.Data.size()+16;m++)
	    {
		    datatmp[m]=txvector.Data[m-16];
	    }
	    scrambler(txvector.scramSeed,datatmp.size(),datatmp);
	    for(size_t i=0;i<datatmp.size();i++)
		    dataldpc[i] = datatmp[i];
	    }
	else
	{
		
	    scrambler(txvector.scramSeed,txvector.Data.size(),txvector.Data);
        for(size_t i=0;i<txvector.Data.size();i++)
		    data[i] = txvector.Data[i];
	}
	
	
	//FEC coding
	//已校验
  	if(txvector.LDPC_Coding == 0)
	{
		bit_enc = bcc_encoder(data,txvector.Data.size(),txvector.PSDU_LENGTH,params.MCSmodeSU,
			params.scram_seed,N_sym,params.crc_sigb,txvector.source_bit);
		N_es = params.MCSmodeSU.nes_a;
	}
	else
	{
		bit_enc.resize(1);
		bit_enc[0] = ldpc_encoder(dataldpc,txvector.PSDU_LENGTH,params.MCSmodeSU,
			params.ldpcParaSU,params.scram_seed,params.crc_sigb);
		N_es = 1;
	}
		
	//stream parser
	bitss_out = stream_parser(bit_enc,n_bpscs,n_ss,N_es);

	// interleaver
	int **bitblock;
	complex<double> **qam_out = new complex<double> *[n_ss];
		
	int row,colum;
	for(int i_ss=0;i_ss<n_ss;++i_ss)
	{
		colum = params.N_sd*n_bpscs[i_ss];
		row = N_sym;
		bitblock = new int*[row];
		for(int i=0;i<row;i++)
			bitblock[i] = new int [colum];
		for(int i=0;i<row;i++)
			for(int j=0;j<colum;j++)
				bitblock[i][j] = bitss_out[i_ss][params.N_sd*n_bpscs[i_ss]*i+j];

		if (txvector.LDPC_Coding == 0)
		{
			bitilv_out = new int*[row];
			for(int i=0;i<row;i++)
			{
				bitilv_out[i] = new int [colum];
				//int modType, int format, int MCS, int BW, int iss, int Nbpscs
				bitilv_out[i] = interleave_n(bitblock[i],params.MCSmodeSU.idx_intlvtble,
					txvector.format,txvector.MCS,txvector.BW,i_ss,n_bpscs[i_ss]);
			}
		}

		else
		{
			bitilv_out = new int*[row];
			for(int i=0;i<row;i++)
				bitilv_out[i] = new int [colum];
			bitilv_out = bitblock;
		}

		int *qam_in;
		qam_in = new int[row*colum];
		for(int i=0;i<row;i++)
			for(int j=0;j<colum;j++)
				qam_in[i*colum+j] = bitilv_out[i][j];
		qam_out[i_ss] = qam_map256(qam_in,n_bpscs[i_ss],row*colum);
	}
		
	//tone mapping
	//qam_tmp [流数][数据子载波][符号数]
	complex<double> ***qam_tmp;
	qam_tmp = new complex<double>**[n_ss] ;	
	for(int i = 0;i<n_ss;i ++ )
		qam_tmp[i] = new complex<double>*[params.N_sd] ;
	for(int i = 0 ; i < n_ss ; i ++ )
		for(int j = 0 ; j < params.N_sd ; j ++ )
			qam_tmp[i][j] = new complex<double>[params.N_sym];
	for(int i = 0 ; i < n_ss ; i ++ )
		for(int j = 0 ; j < params.N_sd ; j ++ )
			for(int k = 0 ; k < params.N_sym ; k ++ )
				qam_tmp[i][j][k] = qam_out[i][k*params.N_sd+j];

	/*for(int j=0;j<52;j++)
	{
		cout<<j+1<<" "<<qam_pss[0][j][0];
		cout<<endl;
	}*/

	Vec_compA_3D qam_psts(n_sts,vector<vector<complex<double>>>(n_sd,vector<complex<double>>(N_sym)));

	if(txvector.STBC!=0)
	{
		for(int i_ss=0;i_ss<txvector.STBC;i_ss++)
		{
			for(int j=0;j<n_sd;j++)
			{
				for(int k=0;k<N_sym;k++)
					qam_psts[2*i_ss][j][k] = qam_tmp[i_ss][j][k];
			}
			for(int j=0;j<n_sd/2;j++)
			{
				for(int k=0;k<N_sym;k++)
				{
					qam_psts[2*i_ss+1][2*j][k] = -conj(qam_tmp[i_ss][2*j+1][k]);
					qam_psts[2*i_ss+1][2*j+1][k] = conj(qam_tmp[i_ss][2*j][k]);
				}
			}
		}
		//following only applicable for two HT modes
		for(int i_ss=2*txvector.STBC;i_ss<n_sts;i_ss++)
			for(int j=0;j<n_sd;j++)
				for(int k=0;k<N_sym;k++)
					qam_psts[i_ss][j][k] = qam_tmp[i_ss-txvector.STBC][j][k];
	}
	else
	{
		for(int i_ss=0;i_ss<n_sts;i_ss++)
			for(int j=0;j<n_sd;j++)
				for(int k=0;k<N_sym;k++)
					qam_psts[i_ss][j][k] = qam_tmp[i_ss][j][k];
	}
	
	//for oversampling and channel offset
	int idx_ofset = params.BSS_NFFT/2 + (params.CH_Offset-1)*params.NFFT_oc/2 + 1;
	int Nsd = params.N_sd;
	int sym_ofset;
	switch(txvector.format)
	{
	case 0://E_NON_HT:
	case 10://E_NON_HT_DUP:
		sym_ofset = 1;
		break;
	case 1://E_HT_MF:
		sym_ofset = 3;
		break;
	case 2://E_HT_GF:
		sym_ofset = 2;
		break;
	default: cout<<"Unknown transmit format!!";
	}

	Vec_compA_3D osym_t(params.N_bwseg*N_sym,vector<vector<complex<double>>>(n_tx));
	
	// o_map[n_sts][NFFT][N_sym]
	complex<double> ***o_map;
	o_map = new complex<double> **[n_sts];
	if(txvector.format==non_HT_DUP)//txvector.FORMAT==E_NON_HT_DUP
	{
		for(int i = 0;i<n_sts;i ++ )
			o_map[i] = new complex<double>*[n_20*params.NFFT] ;
		for(int i = 0 ; i < n_sts ; i ++ )
			for(int j = 0; j < n_20*params.NFFT; j ++ )
				o_map[i][j] = new complex<double>[N_sym];
		for(int i=0;i<n_sts;i++)
			for(int j=0;j<n_20*params.NFFT;j++)
				for(int k=0;k<N_sym;k++)
					o_map[i][j][k]=0;
	}
	else
	{
		for(int i = 0;i<n_sts;i ++ )
			o_map[i] = new complex<double>*[params.NFFT];
		for(int i = 0 ; i < n_sts ; i ++ )
			for(int j = 0 ; j < params.NFFT ; j ++ )
				o_map[i][j] = new complex<double>[N_sym];

		//构造三维数组并初始化
		for(int i=0;i<n_sts;i++)
			for(int j=0;j<params.NFFT;j++)
				for(int k=0;k<N_sym;k++)
					o_map[i][j][k]=0;
	}
	for(int i=0;i<n_sts;i++)
		for(int idx=0;idx<Nsd;idx++)
			for(int k=0;k<N_sym;k++)
				o_map[i][params.Indx_dsubc[idx]-1][k] = qam_psts[i][idx][k];
	

	// 插入导频
	int **s_pilot;
	for(int i_sym=0;i_sym<params.N_sym;i_sym++)
	{
		switch (txvector.format)
		{
		case 0://E_NON_HT:
			{
				s_pilot = pilot_seq(i_sym,sym_ofset,0,n_sts,params,consts);
				for(int i=0;i<n_sts;i++)
				{
					for(int j=0;j<4;j++)
						o_map[i][params.Indx_pilot[j]-1][i_sym] = s_pilot[0][j];
				}
				break;
			}
		case 10://E_NON_HT_DUP:
			{
				s_pilot = pilot_seq(i_sym,sym_ofset,10,n_sts,params,consts);
				for(int i=0;i<n_sts;i++)
				{
					for(int j=0;j<4;j++)
						o_map[i][params.Indx_pilot[j]-1][i_sym] = s_pilot[0][j];
				}
				for(int i=0;i<n_sts;i++)
					for(int n20=0;n20<n_20;n20++)
						for(int j=0;j<params.NFFT;j++)
							o_map[i][n20*params.NFFT+j][i_sym]=o_map[i][j][i_sym];
				break;
			}
		case 1://E_HT_MF:
		case 2://E_HT_GF:
			{
				if(txvector.MCS==32)
				{
					s_pilot = pilot_seq(i_sym,sym_ofset,0,1,params,consts);
					for(int i=0;i<n_sts;i++)
						for(int j=0;j<4;j++)
							o_map[i][params.Indx_pilot[j]-1][i_sym] = s_pilot[0][j];
					for(int i=0;i<n_sts;i++)
						for(int j=0;j<params.NFFT/2;j++)
							o_map[i][params.NFFT/2+j][i_sym]=o_map[i][j][i_sym];
				}
				else
				{
					s_pilot = pilot_seq(i_sym,sym_ofset,txvector.format,n_sts,params,consts);
					int n_pilot;
					switch (params.N_20M)
					{
					case 1:n_pilot=4;
						break;
					case 2:n_pilot=6;
						break;
					}
					for(int i=0;i<n_sts;i++)
						for(int j=0;j<n_pilot;j++)
							o_map[i][params.Indx_pilot[j]-1][i_sym] = s_pilot[i][j];
				}
				break;
			}
		}
	}

	
	int N_osubc = params.N_osubc;
	//for duplicate modes
	//the number of subcarrier from F-T mapping is only one replic
	if(txvector.format==non_HT_DUP)
		N_osubc = N_osubc*n_20;
	else if(txvector.MCS == 32)
		N_osubc = (params.N_sd+4)*2;
	
	//scale
	int o_map_line;
	if(txvector.format==non_HT_DUP)
		o_map_line = n_20*params.NFFT;
	else
		o_map_line = params.NFFT;

	/*for(int i=0;i<n_sts;i++)
	for(int j=0;j<o_map_line;j++)
	for(int k=0;k<N_sym;k++)
	o_map[i][j][k]=o_map[i][j][k]/sqrt((double)N_osubc*n_sts);*/

	
	//s_fd[n_sts][fft]
	complex<double> **s_fd;
	s_fd = new complex<double>*[n_sts];
	for(int i = 0;i<n_sts;i ++ )
		s_fd[i] = new complex<double>[o_map_line];
	//s_fdtx[n_tx][fft]
	complex<double> **s_fdtx;
	s_fdtx = new complex<double>*[n_tx];
	for(int i = 0;i<n_tx;i ++ )
		s_fdtx[i] = new complex<double>[params.BSS_NFFT];
		
	for(int i_sym=0;i_sym<N_sym;i_sym++)
	{
		for(int i = 0;i<n_tx;i ++ )
			for(int j=0;j<NFFT;j++)
				s_fdtx[i][j]=0;

		if(n_20==1){
			for(int i = 0; i < n_sts; i ++ )
				for(int j = 0; j < o_map_line; j ++ )
					s_fd[i][j] = o_map[i][j][i_sym];
		}
		else{
			for(int i = 0; i < n_sts; i ++ )
				for(int j = 0; j < o_map_line; j ++ )
					s_fd[i][(j+64)%128] = o_map[i][j][i_sym];  //FFTshift

		}
		

		for(int i = 0; i < n_sts; i ++ )
		{
			int k=0;
			while(k<n_20)
			{
				for(int j=0;j<o_map_line/n_20;j++)
					s_fd[i][k*o_map_line/n_20+j] *= Gamma[k];
				k++;
			}
		}

		if(n_20==2){
			for(int i = 0; i < n_sts; i ++ )
				for(int j = 0; j < o_map_line/n_20; j ++ ){
					complex<double> temp;
					temp = s_fd[i][(j+64)%128];
					s_fd[i][(j+64)%128] = s_fd[i][j];
					s_fd[i][j]=temp;
				}
		}
		
				
		switch (params.Tx_Format)
		{
		case 0://E_LEG20M:
			{
				complex<double> **s_fd_rot2;
				s_fd_rot2 = new complex<double>*[n_tx];
				for(int i = 0;i<n_tx;i ++ )
				{
					s_fd_rot2[i] = new complex<double>[n_sts*o_map_line];
					s_fd_rot2[i] = s_fd[0];
				}

				double *a = new double[n_tx];
				int* cshift = cshifts(n_tx,0);
				for(int i=0;i<n_tx;i++)
					a[i]=cshift[i]/TSAMP;
				complex<double> **s_fdtxcds;
				s_fdtxcds = fcycdel_g(s_fd_rot2,n_tx,n_sts*o_map_line,a,params.BSS_NFFT);
				int tem1=params.BSS_NFFT/2-params.NFFT_oc/2;
				int tem2=params.BSS_NFFT/2+params.NFFT_oc/2;
				for(int i=0;i<n_tx;i++)
				{
					int temp=0;
					for(int j=tem1;j<tem2;j++)
						s_fdtx[i][temp++]=s_fdtxcds[i][j];
				}
				
				break;
			}
		case 1://E_HT20M:
		case 2://E_HT40M:
			{
				double *a = new double[n_sts];
				int *cshift = cshifts(n_sts,1);
				for(int i=0;i<n_sts;i++)
					a[i]=cshift[i]/TSAMP;
				complex<double> **s_fdtxcds;
				s_fdtxcds = fcycdel_g(s_fd,n_sts,o_map_line,a,params.BSS_NFFT);
				
				int tem1=params.BSS_NFFT/2-params.NFFT_oc/2;
				int tem2=params.BSS_NFFT/2+params.NFFT_oc/2;
				
				//Spatial mapping
				int *idx_occ = new int[NFFT];
				for(int i=0;i<NFFT;i++)
					idx_occ[i]=tem1+i;
				for(int k=0;k<NFFT;k++)
					for(int i=0;i<n_tx;i++)//i天线数
						for(int j=0;j<n_sts;j++)//j空时流数
							s_fdtx[i][k]+=txvector.EXPANSION_MAT[i][j][k]*s_fdtxcds[j][idx_occ[k]];
				
				delete [] s_fdtxcds;
				delete [] cshift;

				break;
			}
		}
		
		// -- Channel offset --
		complex<double> **s_fdtx_ovs;
		s_fdtx_ovs = new complex<double>*[n_tx];
		for(int i = 0;i<n_tx;i ++ )
			s_fdtx_ovs[i] = new complex<double>[params.BSS_NFFT];
		for(int i = 0;i<n_tx;i ++ )
			for(int j=0;j<params.BSS_NFFT;j++)
				s_fdtx_ovs[i][j]=0;
		for(int i = 0;i<n_tx;i ++ )
			for(int j=idx_ofset-1;j<idx_ofset+params.NFFT_oc-1;j++)
				s_fdtx_ovs[i][j]=s_fdtx[i][j-idx_ofset+1];
		
		vv_c_dl fd_out;
		fd_out = fd2td_g(s_fdtx_ovs,txvector.Short_GI,params);
		double factor;
		factor = scale(params.Tx_Format,txvector,n_20)/sqrt(n_sts*1.0);
		for(int i = 0;i<n_tx;i ++ )
		{
			osym_t[i_sym][i].resize(fd_out[0].size());
			for(int j=0;j<fd_out[0].size();j++)
				osym_t[i_sym][i][j]=fd_out[i][j]*factor;
		}

	}
	return osym_t;
}