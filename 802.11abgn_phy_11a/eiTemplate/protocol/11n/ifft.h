#include <iostream>
#include <climits>
#include <string>
#include <complex>
#include <iosfwd>
#include <assert.h>
#include <vector>

using namespace std;

#define pi_v 3.1415926535898

//typedef std::complex<double> complex;

vector<complex<double> >  ifft(vector<complex<double> > f) 
{  
	int i,j,k,m,n,l,r,M;  
	int la,lb,lc;  
	complex<double> t;   
	int NN=f.size();
	/*----����ֽ�ļ���M=log2(N)----*/  
	for(i=NN,M=1;(i=i/2)!=1;M++);       
	
	/*----IFFT�㷨----*/  
	for(m=1;m<=M;m++)  
	{   
		la=pow(double(2),M+1-m); //la=2^m�����m��ÿ�����������ڵ���     
		lb=la/2;    //lb�����m��ÿ�������������ε�Ԫ��              
			   //ͬʱ��Ҳ��ʾÿ�����ε�Ԫ���½ڵ�֮��ľ���    
	
	/*----��������----*/   
		for(l=1;l<=lb;l++)   
		{    
			r=(l-1)*pow(double(2),m-1);     
			for(n=l-1;n<NN-1;n=n+la) //����ÿ�����飬��������ΪN/la    
			{     
				lc=n+lb;  //n,lc�ֱ����һ�����ε�Ԫ���ϡ��½ڵ���          
				t=f[lc]+f[n];     
				f[lc]=(f[n]-f[lc])*complex<double>(cos(2.0*pi_v*r/NN),sin(2.0*pi_v*r/NN));    
				f[n]=t;     
			}    
		}   
	}
	/*----���յ�λ���������б任���ź�----*/
	for (i=1,j=NN/2;i<=NN-2;i++)
	{
		if (i<j)
		{
			t=f[j];
			f[j]=f[i];
			f[i]=t;
		}
		k=NN/2;

		while (k<=j)
		{
			j=j-k;
			k=k/2;
		}
		j=j+k;
	}

	/*----���źų���1/NN----*/   
	for(i=0;i<NN;i++) 
		f[i]=f[i]/complex<double>(NN,0.0);  
	
	return f;
}