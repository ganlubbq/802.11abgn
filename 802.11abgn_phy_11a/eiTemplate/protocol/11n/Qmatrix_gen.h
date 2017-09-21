//---------------------------------------------------------------------------------------------------------//
	//	Function Description: bit reverse
	//---------------------------------------------------------------------------------------------------------//
	//	History:
	//		Created by LiuHang			Date: 2014-11-8			Version: 1.0
	//
	//---------------------------------------------------------------------------------------------------------//
	//	Function List:
	//				unitary_expansion
	//				ieee_expansion
	//				dft_precoding
	//---------------------------------------------------------------------------------------------------------//
	//	Input Parameters:
	//			txvector : 
	//			params : 
	//---------------------------------------------------------------------------------------------------------//
	//	Output Parameters:
	//			wk :
	//---------------------------------------------------------------------------------------------------------//
	// Reference:
	//		Qmatrix_gen.m
	//---------------------------------------------------------------------------------------------------------//
	
#include <iostream>
#include <cmath>
#include <vector>
#include <complex>
#include "constants_def.h"

using namespace std;

#define PI 3.1415926

struct Txvector_Q
{
	int ieee_Q;
	int FORMAT;
	vector<vector<vector<complex<double> > > >  TxBf;
};
struct Params_Q
{
	unsigned int NFFT;
	int N_tx;
	int N_ess;
	int N_sts;
};

void unitary_expansion(vector<int> &sc_freqs, int N_tx, int N_sts, int htMode,
										int N_fft, vector<vector<vector<complex<double> > > > &wk)
{
	//if (htMode != 0)
	//{
	//	switch (N_tx)
	//	{
	//		case 1:
	//			{
	//				double W = 1;
	//				for (int i = 0; i < N_fft; i++)
	//				{
	//					wk[0][0][i] = W;
	//				}
	//			}
	//			break;
	//		case 2:
	//			{
	//				double W_tmp[2][2] ={	{1/sqrt(2.0), -1/sqrt(2.0)},
	//														{1/sqrt(2.0),  1/sqrt(2.0)}  } ;
	//				vector<vector<double> > W(2, vector<double>(N_sts));
	//				for (int i = 0; i < N_sts; i++)
	//				{
	//					W[0][i] = W_tmp[0][i];
	//					W[1][i] = W_tmp[1][i];
	//				}
	//				for(int i = 0; i < 2; i++)
	//				{
	//					for (int j = 0; j < N_sts; j++)
	//					{
	//						for (int m = 0; m < N_fft; m++)
	//						{
	//							wk[i][j][m] = W[i][j];
	//						}
	//					}
	//				} //给wk赋值
	//			}
	//			break;
	//		case 3:
	//			{
	//				complex<double> cplx(0, (-2 )* PI / 3);

	//				complex<double> W_tmp[3][3] = {  {1/sqrt(3.0), 1/sqrt(3.0), 1/sqrt(3.0) },
	//										         {1/sqrt(3.0), exp(cplx)/sqrt(3.0), exp(cplx * 2.0)/sqrt(3.0) },
	//												 {1/sqrt(3.0), exp(cplx * 2.0)/sqrt(3.0),exp(cplx)/sqrt(3.0) }
	//				                               };
	//				vector<vector<complex<double> > > W(3, vector<complex<double> >(N_sts));
	//				for (int i = 0; i < N_sts; i++)
	//				{
	//					W[0][i] = W_tmp[0][i];
	//					W[1][i] = W_tmp[1][i];
	//					W[2][i] = W_tmp[2][i];
	//				} //给W赋值
	//				for(int i = 0; i < 3; i++)
	//				{
	//					for (int j = 0; j < N_sts; j++)
	//					{
	//						for (int m = 0; m < N_fft; m++)
	//						{
	//							wk[i][j][m] = W[i][j];
	//						}
	//					}
	//				} //给wk赋值
	//			}
	//			break;
	//		case 4:
	//			{
	//				double W_tmp[4][4] = { {1/sqrt(4.0), -1/sqrt(4.0), 1/sqrt(4.0), 1/sqrt(4.0)},
	//														{1/sqrt(4.0), 1/sqrt(4.0), -1/sqrt(4.0), 1/sqrt(4.0)},
	//														{1/sqrt(4.0), 1/sqrt(4.0), 1/sqrt(4.0), -1/sqrt(4.0)},
	//														{-1/sqrt(4.0), 1/sqrt(4.0), 1/sqrt(4.0), 1/sqrt(4.0)} };
	//				vector<vector<double> > W(4, vector<double>(N_sts));
	//				for (int i = 0; i < N_sts; i++)
	//				{
	//					W[0][i] = W_tmp[0][i];
	//					W[1][i] = W_tmp[1][i];
	//					W[2][i] = W_tmp[2][i];
	//					W[3][i] = W_tmp[3][i];

	//				} //给W赋值
	//				for(int i = 0; i < 4; i++)
	//				{
	//					for (int j = 0; j < N_sts; j++)
	//					{
	//						for (int m = 0; m < N_fft; m++)
	//						{
	//							wk[i][j][m] = W[i][j];
	//						}
	//					}
	//				} //给wk赋值
	//			}
	//			break;
	//	}//switch N_tx
	//}//htMode != 0 的情况
	//else
	//{
		for (int i = 0; i < N_tx; i++)
		{
			for (int j = 0; j < N_fft; j++)
			{
				//wk[i][i][j] = 1/sqrt((double)N_tx);  //单位映射矩阵
				wk[i][i][j] = 1.0;
			}
		} //给wk赋值
	//}//htMode == 0的情况
}

void ieee_expansion (int N_fft, int N_tx, int N_sts, vector<vector<vector<complex<double> > > > &wk)
{
	vector<vector<int> > I_mat(N_sts, vector<int>(N_sts));
	for (int i = 0; i < N_sts; i++)
	{
		for (int j = 0; j < N_sts; j++)
		{
			I_mat[i][j] = 0;
			I_mat[j][j] = 1;
		}
	}

	vector<vector<double> > Q(N_tx, vector<double>(N_sts));

	for (int i = 0; i < N_tx; i++)
	{
		for (int j = 0; j < N_sts; j++)
		{
			Q[i][j] = I_mat[i % N_sts][j] * sqrt((double)N_sts/(double)N_tx);
		}
	}

	for(int i = 0; i < N_tx; i++)
	{
		for (int j = 0; j < N_sts; j++)
		{
			for (int m = 0; m < N_fft; m++)
			{
				wk[i][j][m] = Q[i][j];
			}
		}
	}

}

void space_expansion(int N_fft, int N_tx, int N_sts, vector<vector<vector<complex<double> > > > &wk){
	if(N_sts==1)
	{
		if(N_tx==2)
		{
			for(int i=0;i<N_fft;i++)
			{
				wk[0][0][i]=1/sqrt(2.0);wk[1][0][i]=1/sqrt(2.0);  // 2*1
			}
		}
		if(N_tx==3)
		{
			for(int i=0;i<N_fft;i++)
			{
				wk[0][0][i]=1/sqrt(3.0);wk[1][0][i]=1/sqrt(3.0);wk[2][0][i]=1/sqrt(3.0);//3*1
			}
		}
		if(N_tx==4)
		{
			for(int i=0;i<N_fft;i++)
			{
				wk[0][0][i]=1/sqrt(4.0);wk[1][0][i]=1/sqrt(4.0);wk[2][0][i]=1/sqrt(4.0);wk[3][0][i]=1/sqrt(4.0);//4*1
			}
		}
	}
	if(N_sts==2)
	{
		if(N_tx==3){
			for(int i=0;i<N_fft;i++)   //3*2
			{
				wk[0][0][i]=sqrt(2/3.0);wk[1][0][i]=0.0;wk[2][0][i]=sqrt(2/3.0);
				wk[0][1][i]=0.0;wk[1][1][i]=sqrt(2/3.0);wk[2][1][i]=0.0;
			}
		}
		if(N_tx==4){                  //4*2
			for(int i=0;i<N_fft;i++)
			{
				wk[0][0][i]=1/sqrt(2.0/4);wk[1][0][i]=0.0;wk[2][0][i]=1/sqrt(2.0/4);wk[3][0][i]=0.0;
				wk[0][1][i]=0.0;wk[1][1][i]=1/sqrt(2.0/4);wk[2][1][i]=0.0;wk[3][1][i]=1/sqrt(2.0/4);
			}
		}
	}
	if(N_sts==3){
		for(int i=0;i<N_fft;i++)   //4*3
		{
			wk[0][0][i]=sqrt(3.0)/2.0;wk[1][0][i]=0.0;wk[2][0][i]=0.0;wk[3][0][i]=sqrt(3.0)/2.0;
			wk[0][1][i]=0.0;wk[1][1][i]=sqrt(3.0)/2.0;wk[2][1][i]=0.0;wk[3][1][i]=0.0;
			wk[0][2][i]=0.0;wk[1][2][i]=0.0;wk[2][2][i]=sqrt(3.0)/2.0;wk[3][2][i]=0.0;
		}
	}
	if(N_sts==4){
		for(int j=0;j<4;j++){
		   for(int i=0;i<N_fft;i++)
			wk[j][j][i]=1.0;
	    }
	}
	
}
void dft_precoding (int N_tx, int N_sts, int N_fft, vector<vector<vector<complex<double> > > > &wk)
{
	vector<vector<double> > x (N_tx, vector<double>(N_tx));
	vector<vector<double> > y (N_tx, vector<double>(N_tx));
	for (int i = 0; i < N_tx; i++)
	{
		for (int j = 0; j < N_tx; j++)
		{
			x[i][j] = j;
			y[i][j] = i;
		}
	}
	vector<vector<complex<double> > > W (N_tx, vector<complex<double> >(N_tx));
	complex<double> cplx(0, (-2)*PI);
	for (int i = 0; i < N_tx; i++)
	{
		for (int j = 0; j < N_tx; j++)
		{
			W[i][j] = sqrt(1/(double)N_tx) * exp(cplx * x[i][j] * y[i][j] / (double)N_tx);
		}
	}
	for (int i = 0; i < N_tx; i++)
	{
		for (int j = 0; j < N_sts; j++)
		{
			for (int m = 0; m < N_fft; m++)
			{
				wk[i][j][m] = W[i][j];
			}
		}
	}
}

void Qmatrix_gen (Txvector_Q txvector, Params_Q params, vector<vector<vector<complex<double> > > > &wk)
{	
	int ieee_Q = txvector.ieee_Q;
	if (txvector.FORMAT == Legacy)
	{
		ieee_Q = 0;
	}
	
	int N_fft = params.NFFT;
	int Nfft_h = N_fft / 2;
	vector<int> Idx_subc(Nfft_h * 2);
	int k = -Nfft_h;

	for (int i = 0; i < Nfft_h * 2; i++)
	{
		Idx_subc[i] = k / N_fft;
		k++;
	}

	int N_tx = params.N_tx; //发射天线数
	//int N_sts = params.N_sts + params.N_ess;  //总的空时流(有问题，先注释掉)
	int N_sts = params.N_sts ; 
	int htMode = 1;

	switch (ieee_Q)
	{
		case 0: // 单位映射
			unitary_expansion(Idx_subc, params.N_tx, params.N_sts, 1, N_fft, wk);
			break;
		case 1: // ieee
			ieee_expansion(N_fft, N_tx, N_sts, wk);
			break;
		case 2:
			for(int i=0;i<N_tx;i++)
				for(int j=0;j<N_sts;j++)
					for(int k=0;k<N_fft;k++)
						wk[i][j][k] = txvector.TxBf[i][j][k];
			break;
		case 4:
			//dft_precoding(N_tx, N_sts, N_fft, wk);
			space_expansion(N_fft,N_tx,N_sts,wk);
			break;
		case 5:
			{
				for (int i = 0; i < N_tx; i++)
				{
					for (int j = 0; j < N_sts; j++)
					{
						for (int m = 0; m < N_fft; m++)
						{
							wk[i][j][m] = 0;
						}
					}
				} 
				
				for (int j = 0; j < N_sts; j++)
				{

					for (int m = 0; m < N_fft; m++)
					{
						wk[j][j][m] = 1;
					}
				}
			}
			break;
	}

}

