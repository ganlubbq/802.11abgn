#include "stdafx.h"
#include "preambleFunc.h"
using namespace std;

//preamble_l_stf
// 怎么校验
vv_c_dl preamble_l_stf(paramsFather params)
{
	int i,j,k;
	bool E_LONG_CP  = 0;
	int n_20  = params.N_20M;
	int NFFT = params.BSS_NFFT;
	double TSAMP = params.TSAMP;
	
	int Gamma_len = params.Gamma.size();
	vector<complex<double>> Gamma(Gamma_len);
	for(i=0;i<Gamma_len;i++)
		Gamma[i] = params.Gamma[i];
	
	int N_tx  = params.N_tx;
	int n_dsubc = 12*n_20;
	complex<double> *L_STF_20F=new complex<double> [64];
	for(i=0;i<64;i++)
	{
		L_STF_20F[i]=std::complex<double>(0.0,0.0);
	}
	L_STF_20F[8]=std::complex<double>(1/sqrt(2.0),1/sqrt(2.0));
	L_STF_20F[12]=std::complex<double>(-1/sqrt(2.0),-1/sqrt(2.0));
	L_STF_20F[16]=std::complex<double>(1/sqrt(2.0),1/sqrt(2.0));
	L_STF_20F[20]=std::complex<double>(-1/sqrt(2.0),-1/sqrt(2.0));
	L_STF_20F[24]=std::complex<double>(-1/sqrt(2.0),-1/sqrt(2.0));
	L_STF_20F[28]=std::complex<double>(1/sqrt(2.0),1/sqrt(2.0));
	L_STF_20F[36]=std::complex<double>(-1/sqrt(2.0),-1/sqrt(2.0));
	L_STF_20F[40]=std::complex<double>(-1/sqrt(2.0),-1/sqrt(2.0));
	L_STF_20F[44]=std::complex<double>(1/sqrt(2.0),1/sqrt(2.0));
	L_STF_20F[48]=std::complex<double>(1/sqrt(2.0),1/sqrt(2.0));
	L_STF_20F[52]=std::complex<double>(1/sqrt(2.0),1/sqrt(2.0));
	L_STF_20F[56]=std::complex<double>(1/sqrt(2.0),1/sqrt(2.0));
	complex<double> l_stf_f_bs[64];
	for (i=0;i<64;i++)
	{
		l_stf_f_bs[i]=L_STF_20F[i]/sqrt(double (N_tx * n_dsubc));
	}
	
	complex<double>*l_stf_f=new complex<double>[64*Gamma_len];
	
	for (k=0;k<Gamma_len;k++)
	{
		for(i=0;i<64;i++)
			l_stf_f[k*64+i]=(complex<double>)Gamma[k]*l_stf_f_bs[i];
	}

	complex<double> **l_stf_f_repmat=new complex<double>*[N_tx]; //映射到多个发端天线，将l_stf映射到多个天线上
	
	for(i=0;i<N_tx;i++)
	{
		l_stf_f_repmat[i]=new complex<double>[64*Gamma_len];
		for(j=0;j<64*Gamma_len;j++)
		{
			l_stf_f_repmat[i][j]=l_stf_f[j];
		}
	}
	
	//-- Convert to time domain --
    //1.6 us Cyclic prefix + 2 x 3.2 us symbols

    //first 4 us symbol
    //-- Insert cyclic delay --
	double *a=(double *)malloc(N_tx*sizeof(double));
	int *c=cshifts(N_tx,0);
	for(i=0;i<N_tx;i++)
	{
		a[i]=*c/TSAMP;
		c++;
	}
	
	complex<double> **fcds_tmp = fcycdel_g(l_stf_f_repmat,N_tx,64*Gamma_len,a,NFFT);

	double *idx_occ = (double *)malloc(params.NFFT_oc*sizeof(double));
	j=0;
	for(i=-params.NFFT_oc/2+1;i<=params.NFFT_oc/2;i++)
	{
		idx_occ[j]=params.BSS_NFFT/2 +i;
		j++;
	}
	int idx_ofset = params.BSS_NFFT/2 + (params.CH_Offset-1)*params.NFFT_oc/2 + 1;

	int *b=(int *)malloc(params.NFFT_oc*sizeof(int));
	for(i=0;i<params.NFFT_oc;i++)
	{
		b[i]=idx_ofset+i;
	}
	complex<double> ** l_stf_f_cds= new complex<double>*[N_tx];
	for( i=0;i<N_tx;i++)
	{
		l_stf_f_cds[i]= new complex<double>[params.BSS_NFFT];   //FFT size
		for( j=0;j<params.NFFT_oc;j++)
		{
			l_stf_f_cds[i][b[j]-1]=fcds_tmp[i][int(idx_occ[j]-1)];
		}
	}
	vv_c_dl l_stf_t1 = fd2td_g(l_stf_f_cds, 0, params);
	vv_c_dl l_stf_t(l_stf_t1.size()*2*params.N_bwseg,l_stf_t1[0].size());
	for(i=0;i<l_stf_t1.size();i++)
		for(j=0;j<l_stf_t1[0].size();j++)
		{
			l_stf_t[i][j] = l_stf_t1[i][j];
			l_stf_t[N_tx+i][j] = l_stf_t1[i][j];
		}

	if (params.BSS_BW==40)
		{
			for(i=0;i<4;i++)
		{
			for(j=0;j<160;j++)
				{
					if(j%2!=0)
					{
						l_stf_t[i][j]=(complex<double>)(-1)*l_stf_t[i][j];
				}
			}
		}
	}
	return l_stf_t;
}

//preamble_l_ltf
vv_c_dl preamble_l_ltf(paramsFather params)
{
	int i,j,k;
	bool E_LONG_CP  = 0;
	int n_20  = params.N_20M;
	int NFFT=params.BSS_NFFT;
	int NFFT_oc=params.NFFT_oc;
	double TSAMP = params.TSAMP;
	int Gamma_len = params.Gamma.size();
	vector<complex<double>> Gamma(Gamma_len);
	for(i=0;i<Gamma_len;i++)
		Gamma[i] = params.Gamma[i];
	int N_tx  = params.N_tx;
	//-- scale by sqrt(N_tx*N_tone) --
	int n_dsubc = 52*n_20;
	int consts_L_LTF_20[64] = {0,0,0,0,0,0,1, 1,-1,-1, 1, 1,-1, 1,-1, 1, 1, 
		1, 1, 1, 1,-1,-1, 1, 1,-1, 1,-1, 1, 1, 1, 1, 0,
		1,-1,-1, 1, 1,-1, 1,-1, 1,-1,-1,-1,-1,-1, 1, 1,
		-1,-1, 1,-1, 1,-1, 1, 1, 1, 1,0,0,0,0,0};
	double l_ltf_f_bs[64];
	for (i=0;i<64;i++)
	{
		l_ltf_f_bs[i]=consts_L_LTF_20[i]/sqrt(double (N_tx * n_dsubc));
	}

	//perform phase rotation according to each 20MHz component band
	complex<double> *l_ltf_f=new complex<double>[64*Gamma_len];
	
	for (j=0;j<Gamma_len;j++)
	{
		for(i=0;i<64;i++)
		{
			l_ltf_f[j*64+i]=Gamma[j]*l_ltf_f_bs[i];
		}
	}
	complex<double> **l_ltf_f_repmat=(complex<double> **)malloc(N_tx*sizeof(complex<double> *));
	for(i=0;i<N_tx;i++)
	{
		l_ltf_f_repmat[i]=(complex<double> *)malloc(Gamma_len*64*sizeof(complex<double>));
		for(j=0;j<Gamma_len*64;j++)
		{
			l_ltf_f_repmat[i][j]=l_ltf_f[j];
		}
	}
	//-- Convert to time domain --
    //1.6 us Cyclic prefix + 2 x 3.2 us symbols

    //first 4 us symbol
    //-- Insert cyclic delay --
	double *a=(double *)malloc(N_tx*sizeof(double));
	int *c=cshifts(N_tx,0);
	for(i=0;i<N_tx;i++)
	{
		a[i]=*c/TSAMP + NFFT/4;
		c++;
	}
	
	complex<double> **fcds_tmp = fcycdel_g(l_ltf_f_repmat,N_tx,Gamma_len*64,a,NFFT);

	int *idx_occ = (int *)malloc(NFFT_oc*sizeof(int));
	j=0;
	for(i=-NFFT_oc/2+1;i<=NFFT_oc/2;i++)
	{
		idx_occ[j]=params.BSS_NFFT/2 +i;
		j++;
	}
	double idx_ofset = params.BSS_NFFT/2 + (params.CH_Offset-1)*params.NFFT_oc/2+1;

	int *b=(int *)malloc(NFFT_oc*sizeof(int));
	for(i=0;i<params.NFFT_oc;i++)
	{
		b[i]=idx_ofset+i;
	}
	complex<double> ** l_ltf_f_cds= new complex<double>*[N_tx];
	for( i=0;i<N_tx;i++)
	{
		l_ltf_f_cds[i] = new complex<double>[params.BSS_NFFT];
		for( j=0;j<params.NFFT_oc;j++)
		{
			l_ltf_f_cds[i][b[j]-1]=fcds_tmp[i][int(idx_occ[j]-1)];
		}
	}
	//-- IFFT and windowing --
	vv_c_dl l_ltf_t1 = fd2td_g(l_ltf_f_cds, E_LONG_CP, params);

	//second 4 us symbol
	double *a_2=(double *)malloc(N_tx*sizeof(double));
	int *c_2=cshifts(N_tx,0);
	for(i=0;i<N_tx;i++)
	{
		a_2[i]=*c_2/TSAMP;
		c_2++;
	}
	complex<double> **fcds_tmp_2 = fcycdel_g(l_ltf_f_repmat,N_tx,Gamma_len*64,a_2,NFFT);

	complex<double> ** l_ltf_f_cds_2= new complex<double>*[N_tx];
	for( i=0;i<N_tx;i++)
	{
		l_ltf_f_cds_2[i] = new complex<double>[params.BSS_NFFT];
		for( j=0;j<NFFT_oc;j++)
		{
			l_ltf_f_cds_2[i][b[j]-1]=fcds_tmp_2[i][int(idx_occ[j]-1)];
		}
	}
	//-- IFFT and windowing --
	vv_c_dl l_ltf_t2 = fd2td_g(l_ltf_f_cds_2, E_LONG_CP, params);

	vv_c_dl l_ltf_t((l_ltf_t1.size()+l_ltf_t1.size())*params.N_bwseg,l_ltf_t1[0].size());
	for(i=0;i<N_tx;i++)
		for(j=0;j<l_ltf_t1[0].size();j++)
		{
			l_ltf_t[i][j] = l_ltf_t1[i][j];
			l_ltf_t[N_tx+i][j] = l_ltf_t2[i][j];
		}
	if (params.BSS_BW==40)
		{
			for(i=0;i<4;i++)
		{
			for(j=0;j<160;j++)
				{
					if(j%2!=0)
					{
						l_ltf_t[i][j]=(complex<double>)(-1)*l_ltf_t[i][j];
				}
			}
		}
	}
	return l_ltf_t;
}

//preamble_l_sig
vv_c_dl preamble_l_sig(int txvector_MCS,paramsFather params,wlan_consts consts)
{
	int N_tx=params.N_tx; 
	int len;
	bool E_LONG_CP=0;
	int ratebits[4];
	int Gamma_len = params.Gamma.size();
	vector<complex<double>> Gamma(Gamma_len);
	for(int i=0;i<Gamma_len;i++)
		Gamma[i] = params.Gamma[i];

	if(params.Tx_Format==0)//E_LEG20M=1
	{
		for(int i=0;i<4;i++)
			ratebits[i]=consts.rate_table[txvector_MCS][i];
		len=params.PDU_LEN;
	}
	else
	{
		ratebits[0]=ratebits[1]=ratebits[3]=1;
		ratebits[2]=0;
        len=(int)(ceil((double)((params.Tx_Time-20)/4))*3-3);
		if(len>4095)
			puts("Tx time is too long");
	}

	double TSAMP=params.TSAMP;
	int *lenbitss;
	int lenbits[12];
	
	lenbitss=num2bitsv(&len,1,12);
	for(int i=0;i<12;i++)
		lenbits[i]=lenbitss[11-i];

	int sigbits[24]={0};
	for(int i=0;i<4;i++)
		sigbits[i]=ratebits[i];
	sigbits[4]=0;
	for(int i=0;i<12;i++)
		sigbits[i+5]=lenbits[i];
	int sum=0;
	for(int i=0;i<16;i++)
		sum=sum+sigbits[i];
	int parity=sum%2;
	sigbits[17]=parity;

	int *l_sig_conve_out=conve(sigbits,24,1);
	int *sig_ilv;
	sig_ilv=interleave_n(l_sig_conve_out,1, Legacy, 0, 0, 0, 1);//48
	
	complex<double> *sig_map=qam_map(sig_ilv,1,48,1);
	vector<int> n(1,0);
	vector<vector<int> >l_sig_pilots=pilot_map(n,0,1,1,0);
	
	complex<double> sig_map_20[64];
	for(int i=0;i<64;i++)
		sig_map_20[i]=sig_map[i]+(complex<double>)l_sig_pilots[i][0];
	
	int n_20 = params.N_20M;
	int n_dsubc=52*n_20;
	complex<double> l_sig_ff[64];
	
	for(int i=0;i<64;i++)
		l_sig_ff[i]= sig_map_20[i]/sqrt(double(N_tx * n_dsubc));

	complex<double> *l_sig_f = new complex<double>[Gamma_len*64];
	for(int i=0;i<Gamma_len;i++)
		for(int j=0;j<64;j++)
			l_sig_f[i*64+j]=Gamma[i]*l_sig_ff[j];
	
	complex<double> **l_sig_f_tx= new complex<double>*[N_tx];
	for(int i=0;i<N_tx;i++)
		l_sig_f_tx[i] = new complex<double> [Gamma_len*64];
	for(int i=0;i<N_tx;i++)
		for(int j=0;j<Gamma_len*64;j++)
			l_sig_f_tx[i][j]=l_sig_f[j];
	
	int htpart=0;
	int *c=cshifts(N_tx,htpart);
	double *cs=(double *)malloc(N_tx*sizeof(double));
	for(int i=0;i<N_tx;i++)
		cs[i]=c[i]/TSAMP;
	complex<double> **fcds_tmp=fcycdel_g(l_sig_f_tx, N_tx,Gamma_len*64,cs,params.BSS_NFFT);
	
	complex<double> ** l_sig_f_cds= new complex<double>*[N_tx];
	for(int i=0;i<N_tx;i++)
		l_sig_f_cds[i] = new complex<double> [params.BSS_NFFT];
	for(int i=0;i<N_tx;i++)
		for(int j=0;j<params.BSS_NFFT;j++)
			l_sig_f_cds[i][j]=0;
	int *idx_occ=(int *)malloc(params.NFFT_oc*sizeof(int));
	for(int i=0;i<params.NFFT_oc;i++)
		idx_occ[i]=params.BSS_NFFT/2-params.NFFT_oc/2+1+i;
	int idx_ofset=params.BSS_NFFT/2 + (params.CH_Offset-1)*params.NFFT_oc/2+1;
	
	for(int i=0;i<N_tx;i++)
	{
		int temp=0;
		for(int j=idx_ofset-1;j<idx_ofset+params.NFFT_oc-1;j++)
			l_sig_f_cds[i][j]=fcds_tmp[i][idx_occ[temp++]-1];
	}
	// -- IFFT and windowing --
	vv_c_dl l_sig_t = fd2td_g(l_sig_f_cds,E_LONG_CP,params);
	if (params.N_bwseg==2)
	{
		l_sig_t.resize(N_tx*2);
		for(int i=0;i<N_tx;i++)
		{
			l_sig_t[i+N_tx].resize(l_sig_t[0].size());
			for(int j=0;j<l_sig_t[0].size();j++)
				l_sig_t[i+N_tx][j]=l_sig_t[i][j];
		}
	}
	if (params.BSS_BW==40)
		{
			for(int i=0;i<2;i++)
		{
			for(int j=0;j<160;j++)
				{
					if(j%2!=0)
					{
						l_sig_t[i][j]=(complex<double>)(-1)*l_sig_t[i][j];
				}
			}
		}
	}
	return l_sig_t;
}

//preamble_ht_stf
vv_c_dl preamble_ht_stf(wlan_txparam txv,paramsFather params)
{
    int i,j,k;
	double TSAMP = params.TSAMP; 
	int NFFT  = params.BSS_NFFT; 
	int N_tx  = params.N_tx;
	int N_sts = params.N_sts;
	int Gamma_len = params.Gamma.size();
	vector<complex<double>> Gamma(Gamma_len);
	for(i=0;i<Gamma_len;i++)
		Gamma[i] = params.Gamma[i];
	
	int E_HT_GF  = 2;
	bool E_LONG_CP=0;
	int P_htltf[4][4] = {{1 ,-1 ,1, 1},{1 ,1 ,-1 ,1}, {1 ,1 ,1 ,-1},{-1, 1, 1, 1}};
	vector<complex<double>> L_STF_20F(64);
	L_STF_20F[8]=std::complex<double>(1/sqrt(2.0),1/sqrt(2.0));
	L_STF_20F[12]=std::complex<double>(-1/sqrt(2.0),-1/sqrt(2.0));
	L_STF_20F[16]=std::complex<double>(1/sqrt(2.0),1/sqrt(2.0));
	L_STF_20F[20]=std::complex<double>(-1/sqrt(2.0),-1/sqrt(2.0));
	L_STF_20F[24]=std::complex<double>(-1/sqrt(2.0),-1/sqrt(2.0));
	L_STF_20F[28]=std::complex<double>(1/sqrt(2.0),1/sqrt(2.0));
	L_STF_20F[36]=std::complex<double>(-1/sqrt(2.0),-1/sqrt(2.0));
	L_STF_20F[40]=std::complex<double>(-1/sqrt(2.0),-1/sqrt(2.0));
	L_STF_20F[44]=std::complex<double>(1/sqrt(2.0),1/sqrt(2.0));
	L_STF_20F[48]=std::complex<double>(1/sqrt(2.0),1/sqrt(2.0));
	L_STF_20F[52]=std::complex<double>(1/sqrt(2.0),1/sqrt(2.0));
	L_STF_20F[56]=std::complex<double>(1/sqrt(2.0),1/sqrt(2.0));

	//-- scale by sqrt(N_tx*N_tone) --
	complex<double>*L_STF_F=new complex<double>[64*Gamma_len];

	double m=sqrt(double((N_sts * 12 * params.N_20M)));
	for (k=0;k<Gamma_len;k++)
	{
		for(i=0;i<64;i++)
			L_STF_F[k*64+i]=(complex<double>)Gamma[k]*L_STF_20F[i]/m;
	}

	complex<double>**HT_STF_STS=new complex<double>*[N_sts];
	if(txv.format == HT_GF)
	{
		for(i=0;i<N_sts;i++)
		{
			HT_STF_STS[i]=new complex<double>[64*Gamma_len];
			for(j=0;j<64*Gamma_len;j++)
			{
				HT_STF_STS[i][j]=std::complex<double>(P_htltf[i][0])*L_STF_F[j];	
			}
		}
	}
	else
	{
		for(i=0;i<N_sts;i++)
		{
			HT_STF_STS[i]=new complex<double>[64*Gamma_len];
			for(j=0;j<64*Gamma_len;j++)
			{
				HT_STF_STS[i][j]=std::complex<double>(L_STF_F[j]);
			}
		}
	}
	int *idx_occ = (int *)malloc(params.NFFT_oc*sizeof(int));
	j=0;
	for(i=-params.NFFT_oc/2+1;i<=params.NFFT_oc/2;i++)
	{
		idx_occ[j]=params.BSS_NFFT/2 +i;
		j++;
	}
	int idx_ofset = params.BSS_NFFT/2 + (params.CH_Offset-1)*params.NFFT_oc/2;

	complex<double> **HT_LTF_FTX= new complex<double>*[N_tx];
	for(i=0;i<N_tx;i++)
	{
		HT_LTF_FTX[i]=new complex<double> [params.BSS_NFFT];
		for(j=0;j<params.BSS_NFFT;j++)
		{
			HT_LTF_FTX[i][j]=0;
		}
	}

	double *a=(double *)malloc(N_sts*sizeof(double));
	int *c=cshifts(N_sts,1);
	for(i=0;i<N_sts;i++)
	{
		a[i]=*c/TSAMP;
		c++;
	}

	complex<double> **HT_STF_CDS = fcycdel_g(HT_STF_STS,N_sts,64*Gamma_len,a,NFFT);

   for(int indx=0;indx<params.NFFT_oc;indx++)
   {
	   int i_subc=idx_occ[indx];
	   for(i=0;i<N_tx;i++)
		   for(j=0;j<N_sts;j++)
			   HT_LTF_FTX[i][idx_ofset+indx]+=txv.EXPANSION_MAT[i][j][indx]*HT_STF_CDS[j][i_subc-1];
   }
  // -- IFFT and windowing --
	vv_c_dl HT_STF_T=fd2td_g(HT_LTF_FTX, E_LONG_CP, params);
	if (params.BSS_BW==40)
		{
			for(i=0;i<2;i++)
		{
			for(j=0;j<160;j++)
				{
					if(j%2!=0)
					{
						HT_STF_T[i][j]=(complex<double>)(-1)*HT_STF_T[i][j];
				}
			}
		}
	}
	return HT_STF_T;
}

//preamble_ht_ltf
vv_c_dl preamble_ht_ltf(wlan_txparam txv,paramsFather params,int n)
{
	int i,j,indx;
	double TSAMP = params.TSAMP; 
	int NFFT  = params.BSS_NFFT; 
	int N_tx  = params.N_tx;
	int N_sts = params.N_sts;
	int N_ess = params.N_ess;
	int N_dltf = params.N_dltf;
	int n_20 = params.N_20M;
	bool E_LONG_CP=0;
	int Gamma_len = params.Gamma.size();
	vector<complex<double>> Gamma(Gamma_len);
	for(i=0;i<Gamma_len;i++)
		Gamma[i] = params.Gamma[i];
	
	int P_htltf[4][4] = {{1 ,-1 ,1, 1},{1 ,1 ,-1 ,1}, {1 ,1 ,1 ,-1},{-1, 1, 1, 1}};
	double HT_LTF_20[64] ={0,0,0,0,1,1,1, 1,-1,-1, 1, 1,-1, 1,-1, 1, 1, 1, 1, 1, 1,-1,-1, 1, 1,-1, 1,-1, 1, 1, 1, 1, 0,
		1,-1,-1, 1, 1,-1, 1,-1, 1,-1,-1,-1,-1,-1, 1, 1,-1,-1, 1,-1, 1,-1, 1, 1, 1, 1,-1,-1,0,0,0};
	/*double HT_LTF_40[128] ={0,0,0,0,0,0,1, 1,-1,-1, 1, 1,-1, 1,-1, 1, 1, 1, 1, 1, 1,-1,-1, 1, 1,-1, 1,-1, 1, 1, 1, 1, 1,
		1,-1,-1, 1, 1,-1, 1,-1, 1,-1,-1,-1,-1,-1, 1, 1,-1,-1, 1,-1, 1,-1, 1, 1, 1, 1,-1,-1,-1,1,0,
		0,0,-1,1,1,-1,1, 1,-1,-1, 1, 1,-1, 1,-1, 1, 1, 1, 1, 1, 1,-1,-1, 1, 1,-1, 1,-1, 1, 1, 1, 1, 1,
		1,-1,-1, 1, 1,-1, 1,-1, 1,-1,-1,-1,-1,-1, 1, 1,-1,-1, 1,-1, 1,-1, 1, 1, 1, 1,0,0,0,0,0};*/
	double HT_LTF_40[128] ={0,0,-1,1,1,-1,1,1,-1,-1,1,1,-1,1,-1,1,1,1,1,1,1,-1,-1,1,1,-1,1,-1,1,1,1,1,1,1,-1,-1,1,1,-1,1,-1,1,-1,-1,-1,-1,-1,1,1,-1,-1,1,-1,1,-1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,-1,-1,1,1,-1,1,-1,1,1,1,1,1,1,-1,-1,1,1,-1,1,-1,1,1,1,1,1,1,-1,-1,1,1,-1,1,-1,1,-1,-1,-1,-1,-1,1,1,-1,-1,1,-1,1,-1,1,1,1,1,-1,-1,-1,1,0};
	//double HT_LTF_40[128] ={0,0;-1;1;1;-1;1;1;-1;-1;1;1;-1;1;-1;1;1;1;1;1;1;-1;-1;1;1;-1;1;-1;1;1;1;1;1;1;-1;-1;1;1;-1;1;-1;1;-1;-1;-1;-1;-1;1;1;-1;-1;1;-1;1;-1;1;1;1;1;0;0;0;0;0;0;0;0;0;0;0;1;1;-1;-1;1;1;-1;1;-1;1;1;1;1;1;1;-1;-1;1;1;-1;1;-1;1;1;1;1;1;1;-1;-1;1;1;-1;1;-1;1;-1;-1;-1;-1;-1;1;1;-1;-1;1;-1;1;-1;1;1;1;1;-1;-1;-1;1;0}；
	if(N_ess + N_sts > N_tx)
		printf("too many E-LTF''s\n");

	//-- scale by sqrt(N_tx*N_tone) --
	vector<double> HT_LTF_F;
	switch (params.Tx_Format)
	{
		case 1://E_HT20M
			{
				HT_LTF_F.resize(64);
				for(i=0;i<64;i++)
					 HT_LTF_F[i] = HT_LTF_20[i] / sqrt(double(56));
			}
			break;
		case 2://E_HT40M
			{
				HT_LTF_F.resize(128);
				for(i=0;i<128;i++)
				{
					 HT_LTF_F[i] = HT_LTF_40[i] / sqrt(double(114));
				}
			}
			break;
		default:{}
	}

	int line = HT_LTF_F.size()/n_20;
	/*vv_c_dl h_ltf_ftmp(line,n_20);
	for(j=0;j<n_20;j++)
		for(i=0;i<line;i++)
			h_ltf_ftmp[i][j] = HT_LTF_F[j*line+i];
	vv_c_dl h_ltf_frot(line,n_20);
	for(i=0;i<line;i++)
		for(j=0;j<n_20;j++)
			for(int k=0;k<n_20;k++)
				h_ltf_frot[i][j]=h_ltf_ftmp[i][k]*Gamma[j];*/
	int k=0;
	vector<complex<double>> h_ltf_ftmp(HT_LTF_F.size());
	while(k<n_20)
	{
		for(int j=0;j<line;j++)
			h_ltf_ftmp[k*line+j] = HT_LTF_F[k*line+j] * Gamma[k];
		k++;
	}

	vector<vector<complex<double>>> HT_LTF_F0(N_sts,vector<complex<double>> (HT_LTF_F.size()));
	for(k=0;k<N_sts;k++)
		for(j=0;j<HT_LTF_F.size();j++)
				HT_LTF_F0[k][j]= h_ltf_ftmp[j];

	//-- Apply spatial mapping matrix --
	complex<double> **HT_LTF_STS;
	int row;
	if (n<=N_dltf)
	{
		HT_LTF_STS=new complex<double>*[N_sts];
		row=N_sts;
		for(i=0;i<N_sts;i++)
		{
			HT_LTF_STS[i]=new complex<double>[HT_LTF_F0[0].size()];
			for(j=0;j<HT_LTF_F0[0].size();j++)
			{
				HT_LTF_STS[i][j]=complex<double>(P_htltf[i][n-1])*HT_LTF_F0[i][j];
			}
		}
	}
	else
    {
		HT_LTF_STS=new complex<double>*[N_ess];
		row=N_ess;
		for(i=0;i<N_ess;i++)
		{
			HT_LTF_STS[i]=new complex<double>[HT_LTF_F0[0].size()];
			for(j=0;j<HT_LTF_F0[0].size();j++)
			{
				HT_LTF_STS[i][j]=complex<double>(P_htltf[i][n-N_dltf-1])*HT_LTF_F0[i][j];
			}
		}
	}

	complex<double> **HT_LTF_FTX1= new complex<double>*[N_tx];
	for(i=0;i<N_tx;i++)
	{
		HT_LTF_FTX1[i]=new complex<double> [params.BSS_NFFT];
		for(j=0;j<params.BSS_NFFT;j++)
		{
			HT_LTF_FTX1[i][j]=0;
		}
	}
	
	int *idx_occ = (int *)malloc(params.NFFT_oc*sizeof(int));
	j=0;
	for(i=-params.NFFT_oc/2+1;i<=params.NFFT_oc/2;i++)
	{
		
		idx_occ[j]=params.BSS_NFFT/2 +i;
		j++;
	}
	int idx_ofset = params.BSS_NFFT/2 + (params.CH_Offset-1)*params.NFFT_oc/2 + 1;

	double *a_1=(double *)malloc(N_sts*sizeof(double));
	int *c_1=cshifts(N_sts,1);
	for(i=0;i<N_tx;i++)
	{
		a_1[i]=*c_1/TSAMP+NFFT/4;
		c_1++;
	}
	vv_c_dl HT_LTF_T1;
	if ((n == 1) && (txv.format == 2))//E_HT_GF
	{
		complex<double> **HT_LTF_F1 = fcycdel_g(HT_LTF_STS,N_sts,HT_LTF_F0[0].size(),a_1,params.BSS_NFFT);
		for(int indx=0;indx<params.NFFT_oc;indx++)
		{
			int i_subc=int(idx_occ[indx]);
			for(i=0;i<N_tx;i++)
				for(j=0;j<N_sts;j++)
					HT_LTF_FTX1[i][int(idx_ofset)+indx-1]+=txv.EXPANSION_MAT[i][j][indx]*HT_LTF_F1[j][i_subc-1];
		}
		for(i=0;i<N_tx;i++)
			for(j=0;j<params.BSS_NFFT;j++)
				HT_LTF_FTX1[i][j]=HT_LTF_FTX1[i][j]/sqrt(double(N_sts));
		HT_LTF_T1=fd2td_g(HT_LTF_FTX1,E_LONG_CP,params);
	}
	else{}

	complex<double> **HT_LTF_FTX2= new complex<double>*[N_tx];
	for(i=0;i<N_tx;i++)
	{
		HT_LTF_FTX2[i]=new complex<double> [params.BSS_NFFT];
		for(j=0;j<params.BSS_NFFT;j++)
		{
			HT_LTF_FTX2[i][j]=0;
		}
	}
	vv_c_dl HT_LTF_T2;
	double *a;
	if(n<=N_dltf)
	{	
		a=new double[N_sts];
		int *c=cshifts(N_sts,1);
		for(i=0;i<N_sts;i++)
		{
			a[i]=*c/TSAMP;
			c++;
		}		
	}
	else
	{	
		a=new double[N_ess];
		int *c=cshifts(N_ess,1);
		for(i=0;i<N_ess;i++)
		{
			a[i]=*c/TSAMP;
			c++;
		}		
	}
//  complex<double> **HT_LTF_F1 = fcycdel_g(HT_LTF_STS,N_sts,HT_LTF_F0[0].size(),a_1,params.BSS_NFFT);
	complex<double> **HT_LTF_F2 = fcycdel_g(HT_LTF_STS,row,HT_LTF_F0[0].size(),a,params.BSS_NFFT);
	if(n<=N_dltf)
	{
		for(indx=0;indx<params.NFFT_oc;indx++)
		{
			int i_subc=int(idx_occ[indx]);
			for(i=0;i<N_tx;i++)
				for(j=0;j<N_sts;j++)
					HT_LTF_FTX2[i][int(idx_ofset)+indx-1]+=txv.EXPANSION_MAT[i][j][indx]*HT_LTF_F2[j][i_subc-1];
		}
		for(i=0;i<N_tx;i++)
			for(j=0;j<params.BSS_NFFT;j++)
				HT_LTF_FTX2[i][j]=HT_LTF_FTX2[i][j]/sqrt(double(N_sts));
	}
	else
	{
		//int indx;
		for(indx=0;indx<params.NFFT_oc;indx++)
		{
			int i_subc=int(idx_occ[indx]);
			for(i=0;i<N_tx;i++)
				for(j=N_sts;j<N_sts+N_ess;j++)
					HT_LTF_FTX2[i][int(idx_ofset)+indx-1]+=txv.EXPANSION_MAT[i][j][indx]*HT_LTF_F2[j-N_sts][i_subc-1];
		}
		for(i=0;i<N_tx;i++)
			for(j=0;j<params.BSS_NFFT;j++)
				HT_LTF_FTX2[i][j]=HT_LTF_FTX2[i][j]/sqrt(double(N_ess));
	}
	HT_LTF_T2=fd2td_g(HT_LTF_FTX2,E_LONG_CP,params);
	vv_c_dl HT_LTF_T;
	if((n == 1) && (txv.format == 2))//E_HT_GF
	{
		HT_LTF_T.resize(N_tx*2);
		for(i=0;i<N_tx;i++)
		{
			HT_LTF_T[i].resize(HT_LTF_T2[0].size());
			HT_LTF_T[i+N_tx].resize(HT_LTF_T2[0].size());
			for(j=0;j<HT_LTF_T2[0].size();j++)
			{
				HT_LTF_T[i][j]=HT_LTF_T1[i][j];
				HT_LTF_T[i+N_tx][j]=HT_LTF_T2[i][j];
			}
		}
	}
	else
	{
		HT_LTF_T.resize(N_tx);
		for(i=0;i<N_tx;i++)
		{
			HT_LTF_T[i].resize(HT_LTF_T2[0].size());
			for(j=0;j<HT_LTF_T2[0].size();j++)
			{
				HT_LTF_T[i][j]=HT_LTF_T2[i][j];
			}
		}
	}
	if (params.BSS_BW==40){
	if (n == 1)
		{
			if(txv.format == 2)
			{
			//int size=sizeof(HT_LTF_T)/sizeof(HT_LTF_T[0]);
			for(i=0;i<N_tx*2;i++)
		{
			for(j=0;j<160;j++)
				{
					if(j%2!=0)
					{
						HT_LTF_T[i][j]=(complex<double>)(-1)*HT_LTF_T[i][j];
				}
			}
		}
			}else{
			for(i=0;i<N_tx;i++)
		{
			for(j=0;j<160;j++)
				{
					if(j%2!=0)
					{
						HT_LTF_T[i][j]=(complex<double>)(-1)*HT_LTF_T[i][j];
				}
			}
		}
		}
	}else{
		for(i=0;i<N_tx;i++)
		{
			for(j=0;j<160;j++)
				{
					if(j%2!=0)
					{
						HT_LTF_T[i][j]=(complex<double>)(-1)*HT_LTF_T[i][j];
				}
			}
		}
	}
	}
	return HT_LTF_T;
	AfxMessageBox("函数运行结束");
}

//preamble_ht_sig
vv_c_dl preamble_ht_sig(wlan_txparam txv,paramsFather params)
{
	int P_htltf[4][4]={{1,-1,1,1},{1,1,-1,1},{1,1,1,-1},{-1,1,1,1}};
	double TSAMP=1000.0/params.output_rate;//sampling interval, ns
	int N_tx=params.N_tx;
	int N_ss=params.MCSmodeSU.mods.size();
	int N_sts=N_ss+txv.STBC;
	bool E_LONG_CP=0;

	vector<int> crc_bits(34);
	int *mcsbitss=num2bitsv(&txv.MCS, 1,7);//翻转前
	int mcsbits[7];
	for(int i=0;i<7;i++)
	{
		mcsbits[i]=mcsbitss[6-i];
		crc_bits[i]=mcsbits[i];
	}
	int bwbits=(params.Tx_Format==2);//E_HT_40M
	crc_bits[7]=bwbits;
	int *htlen_bitss;
	int htlen_bits[16];
	if (txv.NDP)
	{
		for(int i=0;i<16;i++)
		{
			htlen_bits[i]=0;
			crc_bits[i+8]=htlen_bits[i];
		}
	}
	else
	{
		htlen_bitss=num2bitsv(&params.PDU_LEN,1,16);
		for(int i=0;i<16;i++)
		{
			htlen_bits[i]=htlen_bitss[15-i];
			crc_bits[i+8]=htlen_bits[i];
		}
	}
    int smoothing_bits = txv.smoothing;
	crc_bits[24]=smoothing_bits;
    int nsounding_bits = !(txv.sounding);
	crc_bits[25]=nsounding_bits;
	crc_bits[26]=1;
	int aggr_bits=txv.aggregation;
	crc_bits[27]=aggr_bits;
	int STBC[1]={txv.STBC};
	int *stbc_bitss=num2bitsv(STBC,1,2);
	int stbc_bits[2];
	for(int i=0;i<2;i++)
	{
		stbc_bits[i]=stbc_bitss[1-i];
		crc_bits[28+i]=stbc_bits[i];
	}
	int advcoding_bits=txv.LDPC_Coding;
	int shortgi_bits=txv.Short_GI;
	crc_bits[30]=advcoding_bits;
	crc_bits[31]=shortgi_bits;
	int SS[1]={txv.numExtenSS};
	int * nextltf_bitss=num2bitsv(SS,1,2);
	int nextltf_bits[2];
	for(int i=0;i<2;i++)
	{
		nextltf_bits[i]=nextltf_bitss[1-i];
		crc_bits[32+i]=nextltf_bits[i];
	}
	int crc=crc8(crc_bits);
	int ht_bits[48];
	for(int i=0;i<34;i++)
		ht_bits[i]=crc_bits[i];
	int c[1]={crc};
	int *crc_b=num2bitsv(c,1,8);//crc转换
	for(int i=0;i<8;i++)
		ht_bits[i+34]=crc_b[i];
	for(int i=0;i<6;i++)
		ht_bits[i+42]=0;
	/*for(int i=0;i<48;i++)
		cout<<i+1<<" "<<ht_bits[i]<<endl;*/
	//编码
	int *ht_bits_enc_q=conve(ht_bits,48,1);
	int *ht_bits_enc1=(int *)malloc(48*sizeof(int));
	int *ht_bits_enc2=(int *)malloc(48*sizeof(int));
	for(int i=0;i<48;i++)
	{
		ht_bits_enc1[i]=ht_bits_enc_q[i];
		ht_bits_enc2[i]=ht_bits_enc_q[48+i];
	}

	int scale;
	switch(txv.format)
	{
	case 2://E_HT_GF
		{
			if(params.NFFT==64)
				scale=56*N_sts;
			else
				scale = 114*N_sts;
			break;
		}
	case 1://E_HT_MF
		{
			scale = 52*params.N_20M*N_tx;
			break;
		}
	default:
		puts("Error tx format");
	}

	int Gamma_len = params.Gamma.size();
	vector<complex<double>> Gamma(Gamma_len);
	for(int i=0;i<Gamma_len;i++)
		Gamma[i] = params.Gamma[i];

	int *idx_occ=(int *)malloc(params.NFFT_oc*sizeof(int));
	for(int i=0;i<params.NFFT_oc;i++)
		idx_occ[i]=params.BSS_NFFT/2-params.NFFT_oc/2+1+i;
	int idx_ofset=params.BSS_NFFT/2 + (params.CH_Offset-1)*params.NFFT_oc/2+1;

    int *s_ilv1 = interleave_n(ht_bits_enc1,1, Legacy, 0, 0, 0, 1);
	int *s_ilv2 = interleave_n(ht_bits_enc2,1, Legacy, 0, 0, 0, 1);
	
	complex<double> *s_map1=qam_map(s_ilv1,1,48,1);
	complex<double> *s_map2=qam_map(s_ilv2,1,48,1);
	
	vector<int>n1(1,1);
	vector<int>n2(1,2);
	vector<vector<int> > pilots1=pilot_map(n1,0+(txv.format!= 2), 1, 1, 0);
	vector<vector<int> > pilots2=pilot_map(n2,0+(txv.format!= 2), 1, 1, 0);

	complex<double> *s_20_1 = new complex<double>[64];
	complex<double> *s_20_2 = new complex<double>[64];
	for(int i=0;i<64;i++)
	{
		s_20_1[i] = complex<double>(0,1)*s_map1[i]+complex<double>(pilots1[i][0],0);
		s_20_2[i] = complex<double>(0,1)*s_map2[i]+complex<double>(pilots2[i][0],0);
	}
	
	//-- scale by sqrt(N_tx*N_tone) --  
	complex<double> *s_fd1 = new complex<double> [Gamma_len*64];
	complex<double> *s_fd2 = new complex<double> [Gamma_len*64];
	for(int i=0;i<Gamma_len;i++)
	{
		for(int j=0;j<64;j++)
		{
			s_fd1[i*64+j]=Gamma[i]*s_20_1[j]/sqrt((double)scale);
			s_fd2[i*64+j]=Gamma[i]*s_20_2[j]/sqrt((double)scale);
		}
	}
	
	complex<double> ** s_fd_sh1=new complex<double>*[N_tx];
	for(int i=0;i<N_tx;i++)
		s_fd_sh1[i] = new complex<double> [params.BSS_NFFT];
	complex<double> ** s_fd_sh2=new complex<double>*[N_tx];
	for(int i=0;i<N_tx;i++)
		s_fd_sh2[i] = new complex<double> [params.BSS_NFFT];//s_fd_sh
	switch(txv.format)
	{
	case 1://E_HT_MF
		{
			complex<double> ** s_f1=new complex<double>*[N_tx];
	        for(int i=0;i<N_tx;i++)
				s_f1[i] = new complex<double> [Gamma_len*64];
			complex<double> ** s_f2=new complex<double>*[N_tx];
	        for(int i=0;i<N_tx;i++)
				s_f2[i] = new complex<double> [Gamma_len*64];//s_f
			for(int i=0;i<N_tx;i++)
			{
				for(int j=0;j<Gamma_len*64;j++)
				{
					s_f1[i][j] = s_fd1[j];
					s_f2[i][j] = s_fd2[j];
				}
			}
			//-- Insert cyclic delay --
			double *a = new double[N_tx];
			int *c=cshifts(N_tx,0);
			for(int i=0;i<N_tx;i++)
				a[i]=c[i]/TSAMP;
			complex<double> **s_ff1=fcycdel_g(s_f1,N_tx,Gamma_len*64,a,params.BSS_NFFT);
			complex<double> **s_ff2=fcycdel_g(s_f2,N_tx,Gamma_len*64,a,params.BSS_NFFT);
			
			for(int j=0;j<N_tx;j++)
			{
				for(int i=idx_ofset-1;i<idx_ofset+params.NFFT_oc-1;i++)
				{
					s_fd_sh1[j][i]=s_ff1[j][idx_occ[i]-1];
					s_fd_sh2[j][i]=s_ff2[j][idx_occ[i]-1];
				}
			}
			break;
		}
	case 2://E_HT_GF
		{
			// -- Apply spatial mapping matrix --
			complex<double> ** s_fd_sts1=new complex<double>*[N_sts];
			complex<double> ** s_fd_sts2=new complex<double>*[N_sts];
			for(int i=0;i<N_sts;i++)
			{
				s_fd_sts1[i]=new complex<double>[Gamma_len*64];
				s_fd_sts2[i]=new complex<double>[Gamma_len*64];
				for(int j=0;j<Gamma_len*64;j++)
				{
					s_fd_sts1[i][j]=s_fd1[j];
					s_fd_sts2[i][j]=s_fd2[j];
				}
			}

			complex<double> ** s_fd_cyc1=new complex<double>*[N_sts];
			complex<double> ** s_fd_cyc2=new complex<double>*[N_sts];
			for(int i=0;i<N_sts;i++)
			{
				s_fd_cyc1[i]=new complex<double>[Gamma_len*64];
				s_fd_cyc2[i]=new complex<double>[Gamma_len*64];
				for(int j=0;j<Gamma_len*64;j++)
				{
					s_fd_cyc1[i][j]=(complex<double>)P_htltf[i][0]*s_fd_sts1[i][j];
					s_fd_cyc2[i][j]=(complex<double>)P_htltf[i][0]*s_fd_sts2[i][j];
				}
			}
			/*for(int j=0;j<Gamma_len*64;j++)
				cout<<j+1<<" "<<s_fd_cyc2[0][j]<<endl;
			for(int j=0;j<Gamma_len*64;j++)
				cout<<j+1<<" "<<s_fd_cyc2[1][j]<<endl;*/
			double *a = new double[N_sts];
			int *c=cshifts(N_sts,1);
			for(int i=0;i<N_sts;i++)
				a[i]=c[i]/TSAMP;
			
			complex<double> **s_ff1=fcycdel_g(s_fd_cyc1,N_sts,Gamma_len*64,a,params.BSS_NFFT);
			complex<double> **s_ff2=fcycdel_g(s_fd_cyc2,N_sts,Gamma_len*64,a,params.BSS_NFFT);
			/*for(int j=0;j<Gamma_len*64;j++)
				cout<<j+1<<" "<<s_ff2[1][j]<<endl;*/
			int *idx_occ = (int *)malloc(params.NFFT_oc*sizeof(int));
			int j=0;
			for(int i=-params.NFFT_oc/2+1;i<=params.NFFT_oc/2;i++)
			{
				idx_occ[j]=params.BSS_NFFT/2 +i;
				j++;
			}
			
			Vec_compA_3D Q(N_tx,vector<vector<complex<double>>>(N_sts,params.NFFT));
			complex<double> **s_fdq1=new complex<double> *[N_tx];
			complex<double> **s_fdq2=new complex<double> *[N_tx];
			for(int i=0;i<N_tx;i++)
			{
				s_fdq1[i]=new complex<double> [params.NFFT];
				s_fdq2[i]=new complex<double> [params.NFFT];
				for(int j=0;j<params.NFFT;j++)
				{
					s_fdq1[i][j]=0;
					s_fdq2[i][j]=0;
				}
			}
			for(int indx=0;indx<params.NFFT;indx++)
			{
				int i_subc=idx_occ[indx];
				for(int i=0;i<N_tx;i++)
					for(int j=0;j<N_sts;j++)
					{
						Q[i][j][indx] = txv.EXPANSION_MAT[i][j][indx];
						s_fdq1[i][idx_ofset+indx-1]+=Q[i][j][indx]*s_ff1[j][i_subc-1];
						s_fdq2[i][idx_ofset+indx-1]+=Q[i][j][indx]*s_ff2[j][i_subc-1];
					}
			}
			/*for(int j=0;j<Gamma_len*64;j++)
				cout<<j+1<<" "<<s_fdq1[0][j]<<endl;*/
			for(int j=0;j<N_tx;j++)
			{
				for(int i=idx_ofset-1;i<idx_ofset+params.NFFT_oc-1;i++)
				{
					s_fd_sh1[j][i]=s_fdq1[j][idx_occ[i]-1];
					s_fd_sh2[j][i]=s_fdq2[j][idx_occ[i]-1];
				}
			}
			break;
		}
	default:
		puts("Error tx format");
	}
	//-- IFFT and windowing --
	vv_c_dl s_td1 = fd2td_g(s_fd_sh1,E_LONG_CP,params);
	vv_c_dl s_td2 = fd2td_g(s_fd_sh2,E_LONG_CP,params);
	vv_c_dl ht_sig_t(N_tx*2,vector<complex<double>>(s_td1[0].size()));
	for(int i=0;i<N_tx;i++)
	{
		for(int j=0;j<(int)s_td1[0].size();j++)
		{
			ht_sig_t[i][j] = s_td1[i][j];
			ht_sig_t[i+N_tx][j] = s_td2[i][j];
		}
	}
	if (params.BSS_BW==40)
		{
			for(int i=0;i<4;i++)
		{
			for(int j=0;j<160;j++)
				{
					if(j%2!=0)
					{
						ht_sig_t[i][j]=(complex<double>)(-1)*ht_sig_t[i][j];
				}
			}
		}
	}
	return ht_sig_t;
}
