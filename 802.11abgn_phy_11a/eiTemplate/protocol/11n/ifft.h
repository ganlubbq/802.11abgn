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
	/*----计算分解的级数M=log2(N)----*/  
	for(i=NN,M=1;(i=i/2)!=1;M++);       
	
	/*----IFFT算法----*/  
	for(m=1;m<=M;m++)  
	{   
		la=pow(double(2),M+1-m); //la=2^m代表第m级每个分组所含节点数     
		lb=la/2;    //lb代表第m级每个分组所含碟形单元数              
			   //同时它也表示每个碟形单元上下节点之间的距离    
	
	/*----碟形运算----*/   
		for(l=1;l<=lb;l++)   
		{    
			r=(l-1)*pow(double(2),m-1);     
			for(n=l-1;n<NN-1;n=n+la) //遍历每个分组，分组总数为N/la    
			{     
				lc=n+lb;  //n,lc分别代表一个碟形单元的上、下节点编号          
				t=f[lc]+f[n];     
				f[lc]=(f[n]-f[lc])*complex<double>(cos(2.0*pi_v*r/NN),sin(2.0*pi_v*r/NN));    
				f[n]=t;     
			}    
		}   
	}
	/*----按照倒位序重新排列变换后信号----*/
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

	/*----将信号乘以1/NN----*/   
	for(i=0;i<NN;i++) 
		f[i]=f[i]/complex<double>(NN,0.0);  
	
	return f;
}