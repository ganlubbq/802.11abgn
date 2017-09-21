#include "stdafx.h"
#include "primaryFunctionalFunc.h"

Vec_compA_3D txSymbolAssembly(Vec_compA_3D preamble,Vec_compA_3D data,wlan_txparam txvector)
{
	int OFF,blen;
	int N_tx=txvector.N_TX;
	int PSLEN=txvector.params.PS_len;
	int constsNLTF_tble[8]   = {1, 2, 4, 4, 6, 6, 8, 8};
	int sym_num=preamble.size()+data.size();
	switch(txvector.params.App_Win)
	{
	case 2:
		OFF = abs(txvector.params.WTINDEX[0]);
		blen = txvector.params.Nsym_pre * txvector.params.PS_len + (sym_num
			-txvector.params.Nsym_pre) * txvector.params.DS_len + OFF + 10;
		break;
	case 1:
		OFF = 1;
		blen = txvector.params.Nsym_pre * txvector.params.PS_len + (sym_num
			-txvector.params.Nsym_pre) * txvector.params.DS_len + OFF;
		break;
	case 0:
		OFF = 1;
		blen = txvector.params.Nsym_pre * txvector.params.PS_len + (sym_num
			-txvector.params.Nsym_pre) * txvector.params.DS_len;
		break;
	default:break;
	}
	int sptr;
 	if (txvector.applyWindow>1)
		sptr = txvector.params.WTINDEX[0]; 
	else
		sptr = 0;

	Vec_compA_3D sym_assy_out(txvector.params.N_bwseg,vector<vector<complex<double>>>
		(txvector.N_TX,vector<complex<double> >(blen)));

	if(txvector.params.N_bwseg==2)
	{
		for(int i_seg=0;i_seg<2;i_seg++)
		{
			vv_c_dl b(N_tx,vector<complex<double> >(blen));
			int sym_count=0+i_seg*2;
			int i_seg_symcount=0;
			//L_STF 2¸öOFDM·ûºÅ
			for(int k=0;k<2;k++)
				for(int i=0;i<N_tx;i++)
					for(int j=0;j<(int)preamble[0][0].size();j++)
						b[i][OFF-1+sptr+i_seg_symcount+k*PSLEN+j] += preamble[sym_count+k][i][j];
			sym_count+=4;
			i_seg_symcount+=2;
			//L_LTF 2¸öOFDM·ûºÅ
			for(int k=0;k<2;k++)
				for(int i=0;i<N_tx;i++)
					for(int j=0;j<(int)preamble[0][0].size();j++)
						b[i][OFF-1+sptr+i_seg_symcount*PSLEN+k*PSLEN+j] += preamble[sym_count+k][i][j];
			sym_count+=4-i_seg;
			i_seg_symcount+=2;
			//L_SIG 1¸öOFDM·ûºÅ
			for(int i=0;i<N_tx;i++)
				for(int j=0;j<(int)preamble[0][0].size();j++)
					b[i][OFF-1+sptr+i_seg_symcount*PSLEN+j] += preamble[sym_count][i][j];
			sym_count+=2+i_seg;
			i_seg_symcount+=1;
			//VHT_SIGA 2¸öOFDM·ûºÅ
			for(int k=0;k<2;k++)
				for(int i=0;i<N_tx;i++)
					for(int j=0;j<(int)preamble[0][0].size();j++)
						b[i][OFF-1+sptr+i_seg_symcount*PSLEN+k*PSLEN+j] += preamble[sym_count+k][i][j];
			sym_count+=4-i_seg;
			i_seg_symcount+=2;
			//VHT_STF 1¸öOFDM·ûºÅ
			for(int i=0;i<N_tx;i++)
				for(int j=0;j<(int)preamble[0][0].size();j++)
					b[i][OFF-1+sptr+i_seg_symcount*PSLEN+j] += preamble[sym_count][i][j];
			sym_count+=2+i_seg;
			i_seg_symcount+=1;
			//VHT_LTF N_ltf¸öOFDM·ûºÅ
			int N_ltf=constsNLTF_tble[txvector.params.N_sts-1];
			for(int k=0;k<N_ltf;k++)
				for(int i=0;i<N_tx;i++)
					for(int j=0;j<(int)preamble[0][0].size();j++)
						b[i][OFF-1+sptr+i_seg_symcount*PSLEN+k*PSLEN+j] += preamble[sym_count+k][i][j];
			int symadd=(i_seg==0)?N_ltf:1;
			sym_count+=N_ltf+symadd;
			i_seg_symcount+=N_ltf;
			//VHT_SIGB 1¸öOFDM·ûºÅ
			for(int i=0;i<N_tx;i++)
				for(int j=0;j<(int)preamble[0][0].size();j++)
					b[i][OFF-1+sptr+i_seg_symcount*PSLEN+j] += preamble[sym_count][i][j];
			i_seg_symcount+=1;
			//DATA data.size()¸öOFDM·ûºÅ
			for(int k=0;k<(int)data.size()/2;k++)
				for(int i=0;i<N_tx;i++)
					for(int j=0;j<(int)data[0][0].size();j++)
						b[i][OFF-1+sptr+i_seg_symcount*PSLEN+k*PSLEN+j] +=data[i_seg*data.size()/2+k][i][j];
			for(int i=0;i<N_tx;i++)
				for(int j=0;j<blen;j++)
					sym_assy_out[i_seg][i][j]=b[i][j];
		}
	}
	else
	{
		vv_c_dl b(N_tx,vector<complex<double>>(blen));
		for(int i=0;i<(int)preamble.size();i++)
			for(int j=0;j<N_tx;j++)
				for(int k=0;k<(int)preamble[0][0].size();k++)
					b[j][OFF-1+sptr+i*PSLEN+k]+=preamble[i][j][k];
		for(int i=0;i<(int)data.size();i++)
			for(int j=0;j<N_tx;j++)
				for(int k=0;k<(int)data[0][0].size();k++)
					b[j][OFF-1+sptr+preamble.size()*PSLEN+i*data[0][0].size()+k]+=data[i][j][k];
		for(int i=0;i<N_tx;i++)
			for(int j=0;j<blen;j++)
				sym_assy_out[0][i][j]=b[i][j];
	}
	return sym_assy_out;
}