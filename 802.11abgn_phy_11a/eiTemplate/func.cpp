#include "stdafx.h"
#include "func.h"
double maxCCDFData(double *s,int sizeN)
{
	double num;
	num = s[0];
	for (int i=0;i<sizeN;i++)
	{
		if(num<s[i])
			num = s[i];
	}
	return num;
}
//����CCDF���е㺯��
double sumCCDF(double *acceptPointArray,double *pPointArrayCCDF,int m_RealValuenSize,int ScaleXend,int num_of_space)
{
	//CCDF�Ĺ��̲���
	double* NUm=new double[num_of_space+1];//����0�ļ����С��0�Ĳ���
	double DataMax;
	//double DataMin;
	double max_ccdf;
	double DataInter;
	double AvgSum=0;
	BOOL   m_first=TRUE;
	//����ƽ������
	for (int avgFlg=0;avgFlg<m_RealValuenSize;avgFlg++)
	{
		AvgSum = AvgSum+pPointArrayCCDF[avgFlg];
	}
	AvgSum = AvgSum/m_RealValuenSize;
	//Power/avg.power
	for (int avgFlgE=0;avgFlgE<m_RealValuenSize;avgFlgE++)
	{
		pPointArrayCCDF[avgFlgE]=10*log10(pPointArrayCCDF[avgFlgE]/AvgSum);
		if(pPointArrayCCDF[avgFlgE]>10)
			pPointArrayCCDF[avgFlgE]=pPointArrayCCDF[avgFlgE-1];
	}
	max_ccdf = maxCCDFData(pPointArrayCCDF,m_RealValuenSize);//���ֵ
	DataInter = (ScaleXend)/(double)num_of_space;           //����ֱ��ͼ���䳤��,��Ϊ500������

	for (int NM=0;NM<=num_of_space;NM++)
		NUm[NM]=0;//m_ALLNim������������������ֵ
	for (int SM=0;SM<=num_of_space;SM++)
		acceptPointArray[SM]=0;           //��ʼ���ۻ���������

	for (int i=0;i<m_RealValuenSize;i++)
	{
		if((long)(pPointArrayCCDF[i])*1000000<0)
		{
			NUm[0]++;
		}
		for (int j=1;j<=num_of_space;j++)
		{
			if ((long)(pPointArrayCCDF[i])>= (long)((DataInter*(double)(j-1))) && (long)(pPointArrayCCDF[i])< (long)((DataInter*(double)j)))
			{
				// cdf�����ֵ��ʾ
				NUm[j]++;          //ͳ������ÿ���������Ŀ
				break;
			}
		}
	}

	acceptPointArray[0]=NUm[0]/m_RealValuenSize;         //С��0�ĸ���
	for (int m=1;m<=num_of_space;m++)
	{
		NUm[m]=NUm[m]/m_RealValuenSize;        //�����
		acceptPointArray[m]=acceptPointArray[m-1]+NUm[m];//�ۼƸ���
	}

	for (int n=0;n<=num_of_space;n++)
	{
		if(acceptPointArray[n]>0.9)
		{	
			acceptPointArray[n]=1;
			if(m_first)
			{ 
				max_ccdf = DataInter*n;
			    m_first=FALSE;
			}
		}
		acceptPointArray[n]=1-acceptPointArray[n];// cdf->ccdf
	}
	return max_ccdf;   //max_ccdf
}

//���ط�ת
void bitrp (vector<complex<double>> &Data_In, int n)
{
	// λ��ת�û� Bit-reversal Permutation
	int i, j, a, b, p;
	complex<double> temp;
	for (i = 1, p = 0; i < n; i *= 2)
	{
		p ++;
	}
	for (i = 0; i < n; i ++)
	{
		a = i;
		b = 0;
		for (j = 0; j < p; j ++)
		{
			b = (b << 1) + (a & 1);    // b = b * 2 + a % 2;
			a >>= 1;        // a = a / 2;
		}
		if ( b > i)
		{
			temp=Data_In[b];
			Data_In[b]=Data_In[i];
			Data_In[i]=temp;
		}
	}
}

//FFT
int FFT(vector<complex<double>> &Data_in, int n)
{
	int N=n,i,p;
	complex<double> temp=(0.0,0.0);
	if( N& (N-1) )
	{
		for (i = 1, p = 0; i < N; i *= 2)
		{
			p ++;
		}
		N=pow(2.0,p);
	}	                                //����2����
	for(int len=0;len<N-n;len++)
		Data_in.push_back(temp);
	double* wreal=new double[N/2];
	double* wimag=new double[N/2]; 
	double treal, timag, ureal, uimag, arg;
	int m, k, j, t, index1, index2;

	bitrp (Data_in, N);

	// ���� 1 ��ǰ n / 2 �� n �η����Ĺ���� W'j = wreal [j] + i * wimag [j] , j = 0, 1, ... , n / 2 - 1
	arg = - 2 * 3.14159 / N;
	treal = cos (arg);
	timag = sin (arg);
	wreal [0] = 1.0;
	wimag [0] = 0.0;
	for (j = 1; j < N / 2; j ++)
	{
		wreal [j] = wreal [j - 1] * treal - wimag [j - 1] * timag;
		wimag [j] = wreal [j - 1] * timag + wimag [j - 1] * treal;
	}

	for (m = 2; m <= N; m *= 2)
	{
		for (k = 0; k < N; k += m)
		{
			for (j = 0; j < m / 2; j ++)
			{
				index1 = k + j;
				index2 = index1 + m / 2;
				t = N * j / m;    // ��ת���� w ��ʵ���� wreal [] �е��±�Ϊ t
				treal = wreal [t] * Data_in[index2].real() - wimag [t] * Data_in[index2].imag();
				timag = wreal [t] * Data_in[index2].imag() + wimag [t] * Data_in[index2].real();
				ureal = Data_in[index1].real();
				uimag = Data_in[index1].imag();
				Data_in[index1].real(ureal + treal);
				Data_in[index1].imag(uimag + timag);
				Data_in[index2].real(ureal - treal);
				Data_in[index2].imag(uimag - timag);
			}
		}
	}
	delete[] wreal;
	delete[] wimag;
	return N;
}

void FFTShift(vector<complex<double>> &Data_in)
{
	int len=Data_in.size();
	complex<double> temp;
	for(int i=0;i<len/2;i++)
	{
		temp=Data_in[i];
		Data_in[i]=Data_in[i+len/2];
		Data_in[i+len/2]=temp;
	}
}