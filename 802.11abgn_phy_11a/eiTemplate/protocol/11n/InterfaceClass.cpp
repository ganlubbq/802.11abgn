#include "stdafx.h"
#include "InterfaceClass.h"

Vec_compA_3D DataConnect(wlan_txparam txvector);

void InterfaceClass::DataGenerate(int DataLen ,vector<int> src)
{
	txvector.Data.resize(DataLen);
	copy(src.cbegin(),src.cend(),txvector.Data.begin());
	txvector.handlingFunction();//
	txSignal = DataConnect(txvector);
}

Vec_compA_3D DataConnect(wlan_txparam txvector)
{
	wlan_consts consts1;
	wlan_consts consts=wlan_constsValue(consts1);
	int N_tx = txvector.N_TX;
		
	Vec_compA_3D preamble_sym;
	Vec_compA_3D data_sym;

	//preamble 符号生成
	int row_count=0;
	//************************** L-Preamble  ***********************
	if(txvector.format!=HT_GF)
	{
		//preamble_l_stf
		vv_c_dl l_stf_t = preamble_l_stf(txvector.params);
		preamble_sym.resize(2,vector<vector<complex<double>>>
			(N_tx,vector<complex<double>>(l_stf_t[0].size())));
		for(int i=0;i<2;i++)
			for(int j=0;j<N_tx;j++)
				for(int k=0;k<(int)l_stf_t[0].size();k++)
					preamble_sym[i][j][k] = l_stf_t[i*N_tx+j][k];
		row_count+=2;
		//preamble_l_ltf
		vv_c_dl l_ltf_t=preamble_l_ltf(txvector.params);
		preamble_sym.resize(row_count+2,vector<vector<complex<double>>>
			(N_tx,vector<complex<double>>(l_ltf_t[0].size())));
		for(int i=0;i<2;i++)
			for(int j=0;j<N_tx;j++)
				for(int k=0;k<(int)l_ltf_t[0].size();k++)
					preamble_sym[row_count+i][j][k] = l_ltf_t[i*N_tx+j][k];
		row_count+=2;
		//preamble_l_sig
		vv_c_dl l_sig_t=preamble_l_sig(txvector.MCS,txvector.params,consts);
		
		preamble_sym.resize(row_count+1,vector<vector<complex<double>>>
			(N_tx,vector<complex<double>>(l_sig_t[0].size())));
		
		for(int j=0;j<N_tx;j++)
			for(int k=0;k<(int)l_sig_t[0].size();k++)
				preamble_sym[row_count][j][k] = l_sig_t[j][k];
		row_count+=1;
	}

	switch(txvector.format)
	{
	case 1://E_HT_MF
		{
			//************************** HT-MF-Preamble  ***********************
			//preamble_ht_sig
			vv_c_dl ht_sig_t=preamble_ht_sig(txvector,txvector.params);
			preamble_sym.resize(row_count+2,vector<vector<complex<double>>>
			(N_tx,vector<complex<double>>(ht_sig_t[0].size())));
			for(int i=0;i<2;i++)
				for(int j=0;j<N_tx;j++)
					for(int k=0;k<(int)ht_sig_t[0].size();k++)
						preamble_sym[row_count+i][j][k] = ht_sig_t[i*N_tx+j][k];
			row_count+=2;
			//preamble_ht_stf
			vv_c_dl ht_stf_t=preamble_ht_stf(txvector,txvector.params);
			preamble_sym.resize(row_count+1,vector<vector<complex<double>>>
			(N_tx,vector<complex<double>>(ht_stf_t[0].size())));
			for(int j=0;j<N_tx;j++)
				for(int k=0;k<(int)ht_stf_t[0].size();k++)
					preamble_sym[row_count][j][k] = ht_stf_t[j][k];
			row_count+=1;
			//preamble_ht_ltf
			vv_c_dl ht_ltfn;
			preamble_sym.resize(row_count+txvector.params.N_dltf+txvector.params.N_eltf,vector<vector<complex<double>>>
			(N_tx,vector<complex<double>>(ht_sig_t[0].size())));
			for(int n=0;n<txvector.params.N_dltf;n++)
			{
				ht_ltfn = preamble_ht_ltf(txvector,txvector.params,n+1);
				for(int j=0;j<N_tx;j++)
					for(int k=0;k<(int)ht_ltfn[0].size();k++)
						preamble_sym[row_count][j][k] = ht_ltfn[j][k];
				row_count+=1;
			}
			for(int n=0;n<txvector.params.N_eltf;n++)
			{
				ht_ltfn = preamble_ht_ltf(txvector,txvector.params,n+txvector.params.N_dltf+1);
				for(int j=0;j<N_tx;j++)
					for(int k=0;k<(int)ht_ltfn[0].size();k++)
						preamble_sym[row_count][j][k] = ht_ltfn[j][k];
				row_count+=1;
			}
		}
		break;
	case 2://E_HT_GF
		{
			//************************** HT-GF-Preamble  ***********************
			//preamble_ht_stf[sym][tx][80]
			// ht_stf_t[tx][80]
			vv_c_dl ht_stf_t=preamble_ht_stf(txvector,txvector.params);
			preamble_sym.resize(row_count+2,vector<vector<complex<double>>>
			(N_tx,vector<complex<double>>(ht_stf_t[0].size())));
			if(txvector.BSS_BW==40){
				for(int j=0;j<N_tx;j++)
					for(int k=0;k<(int)ht_stf_t[0].size();k++)
					         ht_stf_t[j][k]*= k % 2 == 1 ? -1:1;
			}
			for(int j=0;j<N_tx;j++)
				for(int k=0;k<(int)ht_stf_t[0].size();k++)
				{
					preamble_sym[row_count][j][k] = ht_stf_t[j][k];
					preamble_sym[row_count+1][j][k] = ht_stf_t[j][k];
				}
			row_count+=2;
			//preamble_ht_ltf-1
			vv_c_dl ht_ltfn;
			ht_ltfn = preamble_ht_ltf(txvector,txvector.params,1);
			preamble_sym.resize(row_count+2,vector<vector<complex<double>>>
			(N_tx,vector<complex<double>>(ht_ltfn[0].size())));
			for(int i=0;i<2;i++)
				for(int j=0;j<N_tx;j++)
					for(int k=0;k<(int)ht_ltfn[0].size();k++)
						preamble_sym[row_count+i][j][k] = ht_ltfn[i*N_tx+j][k];
			row_count+=2;

			//preamble_ht_sig
			vv_c_dl ht_sig_t=preamble_ht_sig(txvector,txvector.params);
			preamble_sym.resize(row_count+2,vector<vector<complex<double>>>
			(N_tx,vector<complex<double>>(ht_sig_t[0].size())));

			for(int i=0;i<2;i++)
				for(int j=0;j<N_tx;j++)
					for(int k=0;k<(int)ht_sig_t[0].size();k++)
						preamble_sym[row_count+i][j][k] = ht_sig_t[i*N_tx+j][k];
			
			row_count+=2;
			//preamble_ht_ltf
			for(int n=1;n<txvector.params.N_dltf;n++)
			{
				ht_ltfn = preamble_ht_ltf(txvector,txvector.params,n+1);
				preamble_sym.resize(row_count+1+txvector.params.N_eltf,vector<vector<complex<double>>>
					(N_tx,vector<complex<double>>(ht_sig_t[0].size())));
				for(int j=0;j<N_tx;j++)
					for(int k=0;k<(int)ht_ltfn[0].size();k++)
						preamble_sym[row_count][j][k] = ht_ltfn[j][k];
				row_count+=1;
			}
			for(int n=0;n<txvector.params.N_eltf;n++)
			{
				ht_ltfn = preamble_ht_ltf(txvector,txvector.params,n+txvector.params.N_dltf+1);
				for(int j=0;j<N_tx;j++)
					for(int k=0;k<(int)ht_ltfn[0].size();k++)
						preamble_sym[row_count][j][k] = ht_ltfn[j][k];
				row_count+=1;
			}
		}
		break;
	case 0://E_NON_HT, 
	case 10://E_NON_HT_DUP
		break;
	}

	//数据符号生成
	data_sym=DataSym_11n(txvector,txvector.params,consts);

	Vec_compA_3D txSignal;
	txSignal = txSymbolAssembly(preamble_sym,data_sym,txvector);

	return txSignal;
}
	