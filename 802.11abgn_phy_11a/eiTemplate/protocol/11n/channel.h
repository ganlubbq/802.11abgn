#ifndef CHANNELL_H
#define CHANNELL_H

// created by zhou en,  2003-10-20
// modified by zhou en, 2003-10-28 
// modified by zhou en, 2003-12-25 version2
// lhrzrzlh, 2005-11-10 version 5
// Weipeng Sun 2016-07-11 version 6
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <assert.h>
#include<stdio.h> 
#include<time.h>

using namespace std;
static bool InData_Complex;
#define PI 3.1415926
double round(double r)
{
	return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
};

void JakesIV(double Path_Ampli,vector<double> &An,vector<double> &Bn,
	vector<double> &Wn,vector<double> &Phase,int NumOfFreq,int UpdateInterval,
		int UpdatesPerBurst,int LengthOfBurst,int t_tmp,
		double dt,vector<double> &fading_re,vector<double> &fading_im)
{  
   int i,j,k,n,M_tones,M_magic;
   double cosine, scale,ival,qval;   
   M_tones=NumOfFreq+1;
   M_magic=NumOfFreq*4+2;//N//
   i=0;
   scale=1.414*Path_Ampli/sqrt((double)M_magic);   
   for(k=0;k<=UpdatesPerBurst;k++)
   {
      //Reset sum 
      ival = 0;
      qval = 0;
      for(n=0;n<M_tones;n++)
      {
		cosine = cos(Wn[n]*t_tmp*dt+Phase[n]);
        ival = ival+An[n] * cosine;
        qval = qval+Bn[n] * cosine;
      }
      //UpdateInterval = 4;
      for(j=i;j<i+UpdateInterval;j++)
      {
      	  if(j<LengthOfBurst)
      	  {
             fading_re[j]= ival * scale;
             fading_im[j]= qval * scale;
          }        
      }
      i=i+UpdateInterval;
      t_tmp=t_tmp+UpdateInterval;    
   } 
};

//每一径的收端（发端）的互相关系数
void mimocorr_cx(double anglespread,double angle,double d,int M,int distype,
	vector<double> &correlation2_r,vector<double> &correlation2_i,int BS)
{
	// d 天线之间的距离
	// M 天线的个数
	int L=1000;
    double anglespread1=180;
	double anglerange=180;
    double c=0;
	int ii,m,n,jj;
	vector<double> p(L,0);//
	vector<double> fai1(L,0);//
	vector<double> FAI(L,0);//
	vector<double> matrix_r(M,0);
	vector<double> matrix_i(M,0);
	if(anglespread==0)
	{
		anglespread=0.00000001;
	}
	for(ii=0;ii<L;ii++)
	{
		if(distype==1)//uniform distribution		//均匀分布
		{
			fai1[ii]=angle-anglerange+2*anglerange*(ii+1)/L;//所有的径的到达角以一定的概率分布在AOD+[-AS_max,AS_max]之间
     		FAI[ii]=d*sin(2*PI*fai1[ii]/360);
    		p[ii]=1.0/L;
	    	//c=c+p[ii];
		}
		else if(distype==2)//Laplace distribution   //拉普拉斯分布
		{
			fai1[ii]=angle-anglespread1+2*anglespread1*(ii+1)/L;
			FAI[ii]=d*sin(2*PI*fai1[ii]/360);
			p[ii]=sqrt(2.0)*anglespread1*exp(-sqrt(2.0)*fabs(fai1[ii]-angle)/anglespread)/(anglespread*L);//Laplace?
			//c=c+p[ii];
		}
		else//normal distribution
		{
			fai1[ii]=angle-anglespread1+2*anglespread1*(ii+1)/L;
			FAI[ii]=d*sin(2*PI*fai1[ii]/360);
			p[ii]=exp(-(fai1[ii]-angle)*(fai1[ii]-angle)/(2*anglespread*anglespread))/(anglespread*L);
			//c=c+p[ii];
		}
		if (BS==1)
		{
			if(fai1[ii]>180)
			{
	    		fai1[ii]=fai1[ii]-360;
			}
	    	if(fai1[ii]<-180)
			{
    			fai1[ii]=fai1[ii]+360;
			}
    		if(fabs(fai1[ii])>90)
			{
	    		p[ii]=p[ii]/pow(10.0,20/20);
			}
	    	else
			{
	    		p[ii]=p[ii]/pow(10.0,fai1[ii]*fai1[ii]/4900*0.6);
			}
		}
		c=c+p[ii];//验证概率和是否为1
	}
	for(ii=0;ii<M*M;ii++)
	{
		correlation2_r[ii]=0;
		correlation2_i[ii]=0;
	}
	for(m=0;m<L;m++)//作积分运算
	{
		for(n=0;n<M;n++)
		{
			matrix_r[n]=cos(FAI[m]*2*PI*n);
			matrix_i[n]=-sin(FAI[m]*2*PI*n);
		}
		for(ii=0;ii<M;ii++)
		{
			for(jj=0;jj<M;jj++)
			{
				correlation2_r[ii*M+jj]+=(matrix_r[ii]*matrix_r[jj] + matrix_i[ii]*matrix_i[jj]) * p[m]/c;
				correlation2_i[ii*M+jj]+=( - matrix_r[ii]*matrix_i[jj] + matrix_i[ii]*matrix_r[jj]) * p[m]/c;
			}
		}
	}
	p.clear();
	fai1.clear();
	FAI.clear();
	matrix_i.clear();
	matrix_r.clear();
};

int cx_chol(vector<double> &a_r,vector<double> &a_i,int n)
{
	int i,j,k,u,l;
    if ((a_r[0]+1.0==1.0)||(a_r[0]<0.0))
    {
		return(-2);
	}
    a_r[0]=sqrt(a_r[0]);
    for (i=1; i<=n-1; i++)
    {
		u=i*n; 
		a_r[u]=a_r[u]/a_r[0];
		a_i[u]=a_i[u]/a_r[0];
	}
    for (j=1; j<=n-1; j++)
    {
		l=j*n+j;
        for (k=0; k<=j-1; k++)
        { 
			u=j*n+k; 
			//a_r[l]=a_r[l]-a_r[u]*a_r[u];
			a_r[l]=a_r[l]-a_r[u]*a_r[u]-a_i[u]*a_i[u];//(1)
		}
        if ((a_r[l]+1.0==1.0)||(a_r[l]<0.0))
        {
			return(-2);
		}
        a_r[l]=sqrt(a_r[l]);
        //d=d*a[l];
        for (i=j+1; i<=n-1; i++)
        {
			u=i*n+j;
            for (k=0; k<=j-1; k++)
			{
				//a_r[u]=a_r[u]-a_r[i*n+k]*a_r[j*n+k];
				a_r[u]=a_r[u]-a_r[i*n+k]*a_r[j*n+k]-a_i[i*n+k]*a_i[j*n+k];
				a_i[u]=a_i[u]+a_r[i*n+k]*a_i[j*n+k]-a_i[i*n+k]*a_r[j*n+k];
			}
            a_r[u]=a_r[u]/a_r[l];
			a_i[u]=a_i[u]/a_r[l];//(2)
        }
    }
    for (i=0; i<=n-2; i++)
	{
		for (j=i+1; j<=n-1; j++)
		{
           a_r[i*n+j]=0.0;
		   a_i[i*n+j]=0.0;
		}
	}
    return(2);
};
//通过归一化的角度功率谱，计算每一条径的复相关系数，分别求出发送端和接收端的相关矩阵。
//最后，通过对其做Kronecker乘积，得到MIMO信道整体空间相关矩阵
void mimochannel_cx(int Nr,int Nt,double aglsprR,double aglR,double aglsprT,
	double aglT,double dR,double dT,int distypeR,int distypeT,
	vector<double> &hr_r,vector<double> &hr_i,int uplink)
{
	vector<double> corrR_r(Nr*Nr);
	vector<double> corrR_i(Nr*Nr);
	vector<double> corrT_r(Nt*Nt);
	vector<double> corrT_i(Nt*Nt);	
	int ri,rj;
	int ti,tj;	
	if (uplink==1)
	{
		mimocorr_cx(aglsprR,aglR,dR,Nr,distypeR,corrR_r,corrR_i,1);
		mimocorr_cx(aglsprT,aglT,dT,Nt,distypeT,corrT_r,corrT_i,0);
	}
	else //downlink
	{
		mimocorr_cx(aglsprR,aglR,dR,Nr,distypeR,corrR_r,corrR_i,0);
		mimocorr_cx(aglsprT,aglT,dT,Nt,distypeT,corrT_r,corrT_i,1);
	}
    //收发相关矩阵的Kronecker内积
	for(ri=0;ri<Nr;ri++)
	{
		for(rj=0;rj<Nr;rj++)
		{
			for(ti=0;ti<Nt;ti++)
			{
				for(tj=0;tj<Nt;tj++)
				{
					hr_r[(ri*Nt+ti)*Nr*Nt+(rj*Nt+tj)]=corrR_r[ri*Nr+rj]*corrT_r[ti*Nt+tj]-corrR_i[ri*Nr+rj]*corrT_i[ti*Nt+tj];
					hr_i[(ri*Nt+ti)*Nr*Nt+(rj*Nt+tj)]=corrR_r[ri*Nr+rj]*corrT_i[ti*Nt+tj]+corrR_i[ri*Nr+rj]*corrT_r[ti*Nt+tj];
				}
			}
		}
	}
	cx_chol(hr_r,hr_i,Nr*Nt);  //对矩阵进行Cholesky分解，则产生一个上三角阵R，使R'R=X。若X为非对称正定，则输出一个出错信息。
	corrR_r.clear();
	corrR_i.clear();
	corrT_i.clear();
	corrT_r.clear();
};


void mul_cx(vector<double> &hr_r,vector<double> &hr_i,vector<double> &b_r,
	vector<double> &b_i,int m,int n,int k,vector<double> &c_r,
	vector<double> &c_i)
//hr stored in row,b stored in column,c stored in column
{
	int i,j,l,u;
    for (i=0; i<=m-1; i++)
	{
		for (j=0; j<=k-1; j++)
		{
			u=i+j*m; 
			c_r[u]=0.0;
			c_i[u]=0.0;
			for (l=0; l<=n-1; l++)
			{
				c_r[u]=c_r[u]+hr_r[i*n+l]*b_r[l+j*n]-hr_i[i*n+l]*b_i[l+j*n];
				c_i[u]=c_i[u]+hr_r[i*n+l]*b_i[l+j*n]+hr_i[i*n+l]*b_r[l+j*n];
			}
		}
	}
};
//==========================================================================

void corrj_channel(	double *InData_pr, double *InData_pi, 
	vector<double> &An, vector<double> &Bn, vector<double> &Wn, 
	vector<double> &RndPhase, int NumOfFreq, int UpdateInterval, int UpdatesPerBurst, 
	int LengthOfBurst, int SampleIndex, double dt, int NumOfTaps, 
	vector<double> &Path_Delay, vector<double> &Path_Average_Amp,  
	vector<double> &fore_data_pr,vector<double> &fore_data_pi, 
	vector<double> &OutData_pr, vector<double> &OutData_pi, 
	vector<double> &out_fading_pr, vector<double> &out_fading_pi,
	int Nr,int Nt,vector<double> &aglsprR,vector<double> &aglR,
	vector<double> &aglsprT,vector<double> &aglT,double dR,double dT,
	vector<double> &distypeR,vector<double> &distypeT,
	int corrmodel,double alf,double fd,int loson,int uplink)
{ 
    int M_tones = NumOfFreq + 1; 
    long i,tap,Delay_Length;
    double Path_Ampli; 
	vector<double> fading_pr;
	vector<double> fading_pi;
	vector<double> inner_sub_fading_pr;
	vector<double> inner_sub_fading_pi;//
	vector<double> out_sub_fading_pr;
	vector<double> out_sub_fading_pi;//
    int max_delay= Path_Delay[NumOfTaps-1];
    int n;
	int nt,nr;
	double u;
	double pow1,pow2;
	vector<double> hr_r;//
	vector<double> hr_i;
	vector<double> Output_Each_Channel_pr;
	vector<double> Output_Each_Channel_pi;
	vector<double> Output_Sub_path_pr;
	vector<double> Output_Sub_path_pi;
	vector<double> Phase_per_Tap_channel;
	vector<double> matrix_r;
	vector<double> matrix_i;
	vector<double> Hlos_r; //Nr*Nt,Rice H
	vector<double> Hlos_i;	
    if(corrmodel!=0)
    {
		fading_pr.resize(LengthOfBurst,0);
		fading_pi.resize(LengthOfBurst,0);
		inner_sub_fading_pr.resize(Nr*Nt*LengthOfBurst,0);
		inner_sub_fading_pi.resize(Nr*Nt*LengthOfBurst,0);
		out_sub_fading_pr.resize(Nr*Nt*LengthOfBurst,0);
		out_sub_fading_pi.resize(Nr*Nt*LengthOfBurst,0);
		hr_r.resize(Nr*Nt*Nr*Nt,0);
		hr_i.resize(Nr*Nt*Nr*Nt,0);
    }
    else
    {
		fading_pr.resize(LengthOfBurst,0);
		fading_pi.resize(LengthOfBurst,0);
		inner_sub_fading_pr.resize(Nr*Nt*LengthOfBurst,0);
		inner_sub_fading_pi.resize(Nr*Nt*LengthOfBurst,0);
		out_sub_fading_pr=inner_sub_fading_pr;
		out_sub_fading_pi=inner_sub_fading_pi;		
    }
	if (loson==1)
	{
		matrix_r.resize(Nr,0);
		matrix_i.resize(Nr,0);
		Hlos_r.resize(Nr*Nt,0);
		Hlos_i.resize(Nr*Nt,0);
	}        
	Output_Each_Channel_pr.resize(Nr*LengthOfBurst,0);
	Output_Each_Channel_pi.resize(Nr*LengthOfBurst,0);
	Output_Sub_path_pr.resize(Nr*LengthOfBurst,0);//
	Output_Sub_path_pi.resize(Nr*LengthOfBurst,0);
    Phase_per_Tap_channel.resize(M_tones,0);

	for(i=0;i<max_delay;i++)
	{
		//for(nt=0;nt<Nt;nt++)
	    //{
	    	for(nr=0;nr<Nr;nr++)
	    	{	     		
				Output_Each_Channel_pr[nr+i*Nr] = fore_data_pr[nr+i*Nr];
				Output_Each_Channel_pi[nr+i*Nr] = fore_data_pi[nr+i*Nr];
	        }
	  	//}
   	}	

	for(i=0;i<Nr*max_delay;i++)
	{
		fore_data_pr[i] = 0.0;
		fore_data_pi[i] = 0.0;
	}

	for(tap=0;tap<NumOfTaps;tap++)
    {
		for(i=0;i<Nr*LengthOfBurst;i++)
		{
		Output_Sub_path_pr[i] =0;
		Output_Sub_path_pi[i] =0;
		}
		if (loson==1&&tap==0)
		{
			Path_Ampli=Path_Average_Amp[tap];	
			u=2*PI*dT*sin(2*PI*aglT[tap]/360);
     		for(nr=0;nr<Nr;nr++)
    		{
     			matrix_r[nr]=cos(u*nr);
	    		matrix_i[nr]=-sin(u*nr);//
    		}
     		u=2*PI*fd*SampleIndex*dt*cos(alf*2*PI/360);
     		for (nr=0;nr<Nr;nr++)
    		{
	    		for (nt=0;nt<Nt;nt++)
	    		{
	    			if (nt==0)
	    			{
	    				Hlos_r[nr*Nt+nt]=(cos(u)*matrix_r[nr]-sin(u)*matrix_i[nr])*Path_Ampli;
			    		Hlos_i[nr*Nt+nt]=(sin(u)*matrix_r[nr]+cos(u)*matrix_i[nr])*Path_Ampli;
	    			}
		    		else
		    		{
		    			Hlos_r[nr*Nt+nt]=Hlos_r[nr*Nt];
		    			Hlos_i[nr*Nt+nt]=Hlos_i[nr*Nt];
		    		}
  	     		}
	    	}
			for (nr=0;nr<Nr;nr++)
    		{
	    		for (nt=0;nt<Nt;nt++)
	    		{
					for(n=0;n<LengthOfBurst;n++)
	            	{
						out_sub_fading_pr[(nr*Nt+nt)+n*(Nr*Nt)]=Hlos_r[nr*Nt+nt];
						out_sub_fading_pi[(nr*Nt+nt)+n*(Nr*Nt)]=Hlos_i[nr*Nt+nt];
					}
				}
			}
		}
		else
		{
     		for(nr=0;nr<Nr;nr++)
         	{
    	    	for(nt=0;nt<Nt;nt++)
	         	{			    		
	    			Path_Ampli=Path_Average_Amp[tap];	
             	    Delay_Length = (long) Path_Delay[tap];         		        			
             		// get Phase Rotation
        	    	for(i=0;i<M_tones;i++)
	             	{
	            		//Phase_per_Tap_channel[i] = RndPhase[((nr*Nr+nt)*NumOfTaps+tap) +i*NumOfTaps*Nr*Nt];
						Phase_per_Tap_channel[i] = RndPhase[((nr*Nt+nt)*NumOfTaps+tap) +i*NumOfTaps*Nr*Nt];
	             	}                         
             		//Generate inner Fading weight
             		JakesIV(Path_Ampli, An, Bn, Wn, Phase_per_Tap_channel, NumOfFreq, 
             			UpdateInterval,UpdatesPerBurst,LengthOfBurst, 
             			(long)SampleIndex, dt, fading_pr, fading_pi);		
    	    	
	             	for(n=0;n<LengthOfBurst;n++)
	            	{	
						inner_sub_fading_pr[(nr*Nt+nt)+n*(Nr*Nt)]=fading_pr[n];
		    			inner_sub_fading_pi[(nr*Nt+nt)+n*(Nr*Nt)]=fading_pi[n];
		    		}			         												
	    		}
	    	}
		}		
		if(corrmodel!=0)//
		{
			if (loson==1&&tap==0)
			{
			}
			else
			{
				mimochannel_cx(Nr,Nt,aglsprR[tap],aglR[tap],aglsprT[tap],aglT[tap],dR,dT,(int)distypeR[tap],(int)distypeT[tap],hr_r,hr_i,uplink);
	     		mul_cx(hr_r,hr_i,inner_sub_fading_pr,inner_sub_fading_pi,Nr*Nt,Nr*Nt,LengthOfBurst,out_sub_fading_pr,out_sub_fading_pi);
			}
		}       
        //generate the output fading
		out_fading_pr.clear();
		out_fading_pi.clear();
		for(nr=0;nr<Nr;nr++)
     	{
	    	for(nt=0;nt<Nt;nt++)
	     	{
				for(i=0; i<LengthOfBurst; i++)
	            {
					//out_fading_pr[((nr*Nr+nt)*NumOfTaps+tap)+i*NumOfTaps*Nr*Nt]=out_sub_fading_pr[(nr*Nr+nt)+i*Nr*Nt];
					//out_fading_pi[((nr*Nr+nt)*NumOfTaps+tap)+i*NumOfTaps*Nr*Nt]=out_sub_fading_pi[(nr*Nr+nt)+i*Nr*Nt];
					out_fading_pr.push_back( out_sub_fading_pr[(nr*Nt+nt)+i*Nr*Nt]);
					out_fading_pi.push_back( out_sub_fading_pi[(nr*Nt+nt)+i*Nr*Nt]);
				}
			}
		}		
		// get the output data of each independent sub-channel
		InData_Complex = true;
        if(InData_Complex)
    	{
			for(i=0; i<LengthOfBurst; i++)
			{
     			for(nr=0;nr<Nr;nr++)
     			{
     				for(nt=0;nt<Nt;nt++)
     				{
						Output_Sub_path_pr[nr + i*Nr] += 
							InData_pr[nt+i*Nt] * out_sub_fading_pr[(nr*Nt+nt)+i*Nr*Nt] 
							- InData_pi[nt+i*Nt] * out_sub_fading_pi[(nr*Nt+nt)+i*Nr*Nt]; 
    	            	Output_Sub_path_pi[nr + i*Nr] += 
							InData_pr[nt+i*Nt] * out_sub_fading_pi[(nr*Nt+nt)+i*Nr*Nt] 
							+ InData_pi[nt+i*Nt] * out_sub_fading_pr[(nr*Nt+nt)+i*Nr*Nt];
	                }
     			}
    		}
     	}
        else
     	{
    		for(i=0; i<LengthOfBurst; i++)
    		{
    			for(nr=0;nr<Nr;nr++)
    			{
     				for(nt=0;nt<Nt;nt++)
     				{
    					//Output_Sub_path_pr[nr + i*Nr] += InData_pr[nt+i*Nt] * out_sub_fading_pr[(nr*Nr+nt)+i*Nr*Nt]; 
    	            	//Output_Sub_path_pi[nr + i*Nr] += InData_pr[nt+i*Nt] * out_sub_fading_pi[(nr*Nr+nt)+i*Nr*Nt]; 
						Output_Sub_path_pr[nr + i*Nr] += InData_pr[nt+i*Nt] * out_sub_fading_pr[(nr*Nt+nt)+i*Nr*Nt]; 
    	            	//Output_Sub_path_pi[nr + i*Nr] += InData_pr[nt+i*Nt] * out_sub_fading_pi[(nr*Nt+nt)+i*Nr*Nt]; 
						Output_Sub_path_pi[nr + i*Nr] += InData_pi[nt+i*Nt] * out_sub_fading_pi[(nr*Nt+nt)+i*Nr*Nt]; 
	                }
		    	}
	    	}
	    }
		
    	for(nr=0;nr<Nr;nr++)
    	{
     		for(i=Delay_Length; i<LengthOfBurst; i++)
            {
     			// adding each sub path to generate outdata
     			Output_Each_Channel_pr[nr + i*Nr] += Output_Sub_path_pr[nr+(i-Delay_Length)*Nr];
    		    Output_Each_Channel_pi[nr + i*Nr] += Output_Sub_path_pi[nr+(i-Delay_Length)*Nr];
    		}
    	}
        
        //conceive the fore frame data
     	fore_data_pr.clear();
		fore_data_pr.resize(Nr * Delay_Length,0);
		fore_data_pi.clear();
		fore_data_pi.resize(Nr * Delay_Length,0);
    	for(nr=0;nr<Nr;nr++)
    	{
    		for(i=0;i<Delay_Length;i++)
    	    {
				fore_data_pr[nr+i*Nr] += Output_Sub_path_pr[nr+(LengthOfBurst-Delay_Length+i)*Nr];
				fore_data_pi[nr+i*Nr] += Output_Sub_path_pi[nr+(LengthOfBurst-Delay_Length+i)*Nr];
    		}
    	}
					
	}//tap

    OutData_pr.clear();
	OutData_pr.resize(Nr * LengthOfBurst);
	OutData_pi.clear();
	OutData_pi.resize(Nr * LengthOfBurst);
	for(nr=0;nr<Nr;nr++)
    {
		for(i=0; i<LengthOfBurst; i++)
    	{
			OutData_pr[nr + i*Nr] = Output_Each_Channel_pr[nr + i*Nr];
			OutData_pi[nr + i*Nr] = Output_Each_Channel_pi[nr + i*Nr];
	    }
    }
};

void Multipath_Channel_Init_80211n(vector<double > &An,vector<double > &Bn,
	vector<double > &Wn,double &NumOfTaps,vector<double> &RndPhase,
	double &UpdateInterval,double &UpdatesPerBurst,double &dt,
	vector<double > &Path_Delay,vector<double > &Path_Power,
	vector<double > &Path_Average_Amp,vector<double > &aglsprR,
	vector<double > &aglR,vector<double > &aglsprT,vector<double > &aglT,
	double &dR,double &dT,vector<double > &distypeR,
	vector<double > &distypeT,double &corrmodel,double &alf,double &fd,
	double &loson,int LengthOfBurst,double IntervalBetweenFrames,
	double MobileSpeed,double CarrierFrequency,int NumOfFreq,int NumOfChannels,char Channel_Type,
	int uplink)
	//-----------------------------------------------------------------------//
	//  Function Description:  802.11n 信道初始化c程序
	// ----------------------------------------------------------------------//
	//  History:                   
	//     Created by  Wangjun      Data: 2014-11-06   Version: 1.0
	//             
	// ----------------------------------------------------------------------//
	//  Functions List:  
	// ----------------------------------------------------------------------//
	//	Input Parameters:    
	//-------------------------------------------------------------------------
	//		LengthOfBurst: length of frame     (sample)
	//		IntervalBetweenFrames: one frame duration (s)
	//		MobileSpeed:  mobile speed (km/h) 3,30,120
	//		NumOfFreq: number of different frequecies used to generate fading
	//		NumOfChannel: Number of channels
	//		Channel_Type: Type of the channel
	//		LOS,1.2 for Modified Pedestrian A without LOS,2 for Vehicular A,3 for
	//		uplink:flag of uplink (1) or downlink (others)
	// ----------------------------------------------------------------------//
	//  Output Parameters:
	//      *An,*Bn,*Wn:  parameters used to generate fading
	//		*dt:  the basic time interval
	//		*NumOfTaps: number of taps
	//		*Path_Delay: the path delay of each tap
	//		*Path_Average_Amp: the average amplitude of each tap
	//		*aglsprR: angle spread at Receiver
	//		*aglR: angle of arrival for each path
	//		*aglsprT: angle spread at Transmitter
	//		*aglT: angle of departure for each path
	//		*dR: distance between antennae at Receiver divide wavelength
	//		*dT: distance between antennae at Transmitter divide wavelength
	//		*distypeR: distribution type of angle at Receiver for each path
	//		*distypeT: distribution type of angle at Transmitter for each path
	//		*corrmodel: flag of correlation (1 if necessary)
	//		*alf: angle between MS velocity and transmission wave
	//		*fd: Doppler Frequency
	//		*loson: flag of LOS (1 for on and others for off)
	// ----------------------------------------------------------------------//
	//  Reference:    
	// ----------------------------------------------------------------------//
	//  Note:


{  
	//double CarrierFrequency=5.25*pow(10.0, 9);										// 5.25 G[Hz]
	double SpeedOfLight=3*pow(10.0, 8);												// [m/s]
	double fd_max = MobileSpeed / 3.6/ SpeedOfLight * CarrierFrequency;

	int MaxPhaseChange=5;												//MaxPhaseChange in degree  
	int n;
	int ant;
	int tap;
	int Numtap;
	int output_i;

	int M_OSCIL=NumOfFreq;
	int M_TONES=M_OSCIL+1;
	int N_MAGIC=M_OSCIL*4+2;

	dt=IntervalBetweenFrames / LengthOfBurst;                    // Basic Time 

	if(Channel_Type=='A')
	{
		// typical office environment no Los  50ns RMS optional
		// single path
		// with speed 3km/h

		double Path_Power_dB=0;
		NumOfTaps=1;
		Path_Delay.push_back(0.0);

		Path_Power.push_back(pow(10.0, (Path_Power_dB/10)));
		Path_Average_Amp.push_back(1.0);
		corrmodel=1;
		alf=0;
		loson=0;

		if(uplink==1)
		{
			aglT.push_back(45);
			aglsprT.push_back(40);
			distypeT.push_back(2);        
			dT=0.5;
			aglR.push_back(45);   
			aglsprR.push_back(40); 
			distypeR.push_back(2);   
			dR=0.5;
		}
		else
		{
			//downlink    
			aglT.push_back(45);         
			aglsprT.push_back(40);            
			distypeT.push_back(2);  
			dT=0.5;
			aglR.push_back(45);
			aglsprR.push_back(40); 
			distypeR.push_back(2);   
			dR=0.5;
		}
	}else if(Channel_Type=='B')
	{
		// A Typical large open space and office environment no los 2 cluster
		// Model B with 15 ns rms delay spread.
		// with speed 3km/h  
		double Path_Data[]={0,10,20,30,40,20,30,40,50,60,70,80};
		double Path_Power_dB[]={0.0,-5.4,-10.8,-16.2,-21.7,-3.2,-6.3,-9.4,-12.5,-15.6,-18.7,-21.8};
		double Power_sum=0;
		int path_i;
		int path_pow;

		NumOfTaps=12;
		Numtap=12;
		Path_Delay.clear();
		for(path_i=0; path_i<Numtap; path_i++)	
			Path_Delay.push_back(round((Path_Data[path_i]*pow(10.0, -9)/(dt))));

		Path_Power.clear();
		for(path_pow=0;path_pow<Numtap;path_pow++) 
		{
			Path_Power.push_back(pow(10.0, (Path_Power_dB[path_pow]/10)));
			Power_sum=Power_sum+Path_Power[path_pow];
		}
		Path_Average_Amp.clear();
		for (path_pow=0;path_pow<Numtap;path_pow++) 
		{
			Path_Average_Amp.push_back(sqrt(Path_Power[path_pow]/Power_sum));
		}
		corrmodel=1;
		alf=22.5;
		loson=0;
		if(uplink==1)
		{
			double aglT_data[]={225.1,225.1,225.1,225.1,225.1,106.5,106.5,106.5,106.5,106.5,106.5,106.5};
			double aglsprT_data[]={14.4,14.4,14.4,14.4,14.4,25.4,25.4,25.4,25.4,25.4,25.4,25.4};
			double distypeT_data[]={2,2,2,2,2,2,2,2,2,2,2,2};
			double aglR_data[]={4.3,4.3,4.3,4.3,4.3,118.4,118.4,118.4,118.4,118.4,118.4,118.4};
			double aglsprR_data[]={14.4,14.4,14.4,14.4,14.4,25.2,25.2,25.2,25.2,25.2,25.2,25.2};
			double distypeR_data[]={2,2,2,2,2,2,2,2,2,2,2,2};
			aglT.clear();aglsprR.clear();distypeT.clear();distypeR.clear();aglR.clear();aglsprT.clear();
			for(int agl_i=0;agl_i<Numtap;agl_i++)
			{
				aglT.push_back(aglT_data[agl_i]);
				aglsprT.push_back(aglsprT_data[agl_i]);
				distypeT.push_back(distypeT_data[agl_i]);
				aglR.push_back(aglR_data[agl_i]);
				aglsprR.push_back(aglsprR_data[agl_i]);
				distypeR.push_back(distypeR_data[agl_i]);
			}
			dT=0.5;
			dR=0.5; //0.5 or 10
		}
		else
		{
			double aglT_data[]={225.1,225.1,225.1,225.1,225.1,106.5,106.5,106.5,106.5,106.5,106.5,106.5};
			double aglsprT_data[]={14.4,14.4,14.4,14.4,14.4,25.2,25.2,25.2,25.2,25.2,25.2,25.2};
			double distypeT_data[]={2,2,2,2,2,2,2,2,2,2,2,2};
			double aglR_data[]={4.3,4.3,4.3,4.3,4.3,118.4,118.4,118.4,118.4,118.4,118.4,118.4};
			double aglsprR_data[]={14.4,14.4,14.4,14.4,14.4,25.4,25.4,25.4,25.4,25.4,25.4,25.4};
			double distypeR_data[]={2,2,2,2,2,2,2,2,2,2,2,2};
	
			for(int agl_i=0;agl_i<Numtap;agl_i++)
			{
				aglT.push_back(aglT_data[agl_i]);
				aglsprT.push_back( aglsprT_data[agl_i]);
				distypeT.push_back( distypeT_data[agl_i]);
				aglR.push_back( aglR_data[agl_i]);
				aglsprR.push_back( aglsprR_data[agl_i]);
				distypeR.push_back( distypeR_data[agl_i]);
			}
			dT=0.5;
			dR=0.5; //0.5 or 10
		} 
	}else if(Channel_Type=='C')
	{
		//  a large open space(indoor and outdoor),NLOS ,150ns 
		// Model C with 30 ns rms delay spread.
		double Path_Data[]={0,10,20,30,40,50,60,70,80,90,60,70,80,90,110,140,170,200};
		double Path_Power_dB[]={0.0,-2.1,-4.3,-6.5,-8.6,-10.8,-13.0,-15.2,-17.3,-19.5,-5.0,-7.2,-9.3,-11.5,-13.7,-15.8,-18.0,-20.2 };
		int path_i;
		double Power_sum=0;
		int path_pow;
		NumOfTaps=18;
		Numtap=18;
		Path_Delay.clear();
		for (path_i=0; path_i<Numtap; path_i++)	
			Path_Delay.push_back( round((Path_Data[path_i]*pow(10.0, -9)/(dt))));
	    Path_Power.clear();
		for (path_pow=0;path_pow<Numtap;path_pow++) 
		{
			Path_Power.push_back( pow(10.0, (Path_Power_dB[path_pow]/10)));
			Power_sum=Power_sum+Path_Power[path_pow];
		}
		Path_Average_Amp.clear();
		for (path_pow=0;path_pow<Numtap;path_pow++) 
		{
			Path_Average_Amp.push_back( sqrt(Path_Power[path_pow]/Power_sum));
		}
		corrmodel=1;
		alf=22.5;
		loson=0;
		if(uplink==1)
		{
			double aglT_data[]={13.5,13.5,13.5,13.5,13.5,13.5,13.5,13.5,13.5,13.5,56.4,56.4,56.4,56.4,56.4,56.4,56.4,56.4};
			double aglsprT_data[]={24.7,24.7,24.7,24.7,24.7,24.7,24.7,24.7,24.7,24.7,22.5,22.5,22.5,22.5,22.5,22.5,22.5,22.5};
			double distypeT_data[]={2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
			double aglR_data[]={290.3,290.3,290.3,290.3,290.3,290.3,290.3,290.3,290.3,290.3,332.3,332.3,332.3,332.3,332.3,332.3,332.3,332.3};
			double aglsprR_data[]={24.6,24.6,24.6,24.6,24.6,24.6,24.6,24.6,24.6,24.6,22.4,22.4,22.4,22.4,22.4,22.4,22.4,22.4};
			double distypeR_data[]={2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
			
			for(int agl_i=0;agl_i<Numtap;agl_i++)
			{
				aglT.push_back( aglT_data[agl_i]);
				aglsprT.push_back( aglsprT_data[agl_i]);
				distypeT.push_back( distypeT_data[agl_i]);
				aglR.push_back( aglR_data[agl_i]);
				aglsprR.push_back( aglsprR_data[agl_i]);
				distypeR.push_back( distypeR_data[agl_i]);
			}
			dT=0.5;
			dR=0.5; //0.5 or 10
		}
		else 
		{
			double aglT_data[]={13.5,13.5,13.5,13.5,13.5,13.5,13.5,13.5,13.5,13.5,56.4,56.4,56.4,56.4,56.4,56.4,56.4,56.4};
			double aglsprT_data[]={24.7,24.7,24.7,24.7,24.7,24.7,24.7,24.7,24.7,24.7,22.5,22.5,22.5,22.5,22.5,22.5,22.5,22.5};
			double distypeT_data[]={2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
			double aglR_data[]={290.3,290.3,290.3,290.3,290.3,290.3,290.3,290.3,290.3,290.3,332.3,332.3,332.3,332.3,332.3,332.3,332.3,332.3};
			double aglsprR_data[]={24.6,24.6,24.6,24.6,24.6,24.6,24.6,24.6,24.6,24.6,22.4,22.4,22.4,22.4,22.4,22.4,22.4,22.4};
			double distypeR_data[]={2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
			for(int agl_i=0;agl_i<Numtap;agl_i++)
			{
				aglT.push_back( aglT_data[agl_i]);
				aglsprT.push_back( aglsprT_data[agl_i]);
				distypeT.push_back( distypeT_data[agl_i]);
				aglR.push_back( aglR_data[agl_i]);
				aglsprR.push_back( aglsprR_data[agl_i]);
				distypeR.push_back( distypeR_data[agl_i]);
			}
			dT=0.5;
			dR=0.5; //0.5 or 10
		}
	}else if(Channel_Type=='D')
	{
		// Model D with 50 ns rms delay spread.
		double Path_Data[]={0,10,20,30,40,50,60,70,80,90,110,140,170,200,240,290,110,140,170,200,240,290,340,240,290,340,300};
		double Path_Power_dB[]={0,-0.9,-1.7,-2.6,-3.5,-4.3,-5.2,-6.1,-6.9,-7.8,-9.0,-11.1,-13.7,-16.3,-19.3,-23.2,-6.6,-9.5,-12.1,-14.7,-17.4,-21.9,-25.5,-18.8,-23.2,-25.2,-26.7};
		double Power_sum=0;

		int path_i;
		int path_pow;

		NumOfTaps=27;
		Numtap=27;
		Path_Delay.clear();
		for (path_i=0; path_i<Numtap; path_i++)	
			Path_Delay.push_back( round((Path_Data[path_i]*pow(10.0, -9)/(dt))));
		Path_Power.clear();
		for (path_pow=0;path_pow<Numtap;path_pow++) 
		{
			Path_Power.push_back( pow(10.0, (Path_Power_dB[path_pow]/10)));
			Power_sum=Power_sum+Path_Power[path_pow];
		}
		Path_Average_Amp.clear();
		for (path_pow=0;path_pow<Numtap;path_pow++) 
		{
			Path_Average_Amp.push_back( sqrt(Path_Power[path_pow]/Power_sum));
		}
		corrmodel=1;
		alf=22.5;
		loson=0;

		if(uplink==1)
		{
			double aglT_data[]={332.1,332.1,332.1,332.1,332.1,332.1,332.1,332.1,332.1,332.1,332.1,332.1,332.1,332.1,332.1,332.1,49.3,49.3,49.3,49.3,49.3,49.3,49.3,275.9,275.9,275.9,275.9};
			double aglsprT_data[]={27.4,27.4,27.4,27.4,27.4,27.4,27.4,27.4,27.4,27.4,27.4,27.4,27.4,27.4,27.4,27.4,320.2,320.2,320.2,320.2,320.2,320.2,320.2,36.8,36.8,36.8,36.8};
			double distypeT_data[]={2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
			double aglR_data[]={158.9,158.9,158.9,158.9,158.9,158.9,158.9,158.9,158.9,158.9,158.9,158.9,158.9,158.9,158.9,158.9,320.2,320.2,320.2,320.2,320.2,320.2,320.2,276.1,276.1,276.1,276.1};
			double aglsprR_data[]={27.7,27.7,27.7,27.7,27.7,27.7,27.7,27.7,27.7,27.7,27.7,27.7,27.7,27.7,27.7,27.7,31.4,31.4,31.4,31.4,31.4,31.4,31.4,37.4,37.4,37.4,37.4};
			double distypeR_data[]={2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
		
			for(int agl_i=0;agl_i<Numtap;agl_i++)
			{
				aglT.push_back(aglT_data[agl_i]);
				aglsprT.push_back(aglsprT_data[agl_i]);
				distypeT.push_back(distypeT_data[agl_i]);
				aglR.push_back(aglR_data[agl_i]);
				aglsprR.push_back(aglsprR_data[agl_i]);
				distypeR.push_back(distypeR_data[agl_i]);
			}
			dT=0.5;
			dR=0.5; //0.5 or 10
		}
		else
		{
			double aglT_data[]={332.1,332.1,332.1,332.1,332.1,332.1,332.1,332.1,332.1,332.1,332.1,332.1,332.1,332.1,332.1,332.1,49.3,49.3,49.3,49.3,49.3,49.3,49.3,275.9,275.9,275.9,275.9};
			double aglsprT_data[]={27.4,27.4,27.4,27.4,27.4,27.4,27.4,27.4,27.4,27.4,27.4,27.4,27.4,27.4,27.4,27.4,32.1,32.1,32.1,32.1,32.1,32.1,32.1,36.8,36.8,36.8,36.8};
			double distypeT_data[]={2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
			double aglR_data[]={158.9,158.9,158.9,158.9,158.9,158.9,158.9,158.9,158.9,158.9,158.9,158.9,158.9,158.9,158.9,158.9,320.2,320.2,320.2,320.2,320.2,320.2,320.2,276.1,276.1,276.1,276.1};
			double aglsprR_data[]={27.7,27.7,27.7,27.7,27.7,27.7,27.7,27.7,27.7,27.7,27.7,27.7,27.7,27.7,27.7,27.7,31.4,31.4,31.4,31.4,31.4,31.4,31.4,37.4,37.4,37.4,37.4};
			double distypeR_data[]={2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
			
			for(int agl_i=0;agl_i<Numtap;agl_i++)
			{
				aglT.push_back( aglT_data[agl_i]);
				aglsprT.push_back( aglsprT_data[agl_i]);
				distypeT.push_back( distypeT_data[agl_i]);
				aglR.push_back( aglR_data[agl_i]);
				aglsprR.push_back( aglsprR_data[agl_i]);
				distypeR.push_back( distypeR_data[agl_i]);;
			}
			dT=0.5;
			dR=0.5; //0.5 or 10
		} 
	}else if(Channel_Type=='E')
		{
			// a typical large open space(indoor and outdoor)  no los  100na rms
			// Model E with 100 ns rms delay spread.

			double Path_Data[]={0,10,20,30,50,80,110,140,180,230,280,330,380,430,490,50,80,110,140,180,230,280,330,380,430,490,560,180,230,280,330,380,430,490,490,560,640,730};
			double Path_Power_dB[]={-2.6,-3.0,-3.5,-3.9,-4.5,-5.6,-6.9,-8.2,-9.8,-11.7,-13.9,-16.1,-18.3,-20.5,-22.9,-1.8,-3.2,-4.5,-5.8,-7.1,-9.9,-10.3,-14.3,-14.7,-18.7,-19.9,-22.4,-7.9,-9.6,-14.2,-13.8,-18.6,-18.1,-22.8,-20.6,-20.5,-20.7,-24.6};
			double Power_sum=0;
			int path_i;
			int path_pow;

			NumOfTaps=38;

			Numtap=38;
			Path_Delay.clear();
			for (path_i=0; path_i<Numtap; path_i++)	
				Path_Delay.push_back( round((Path_Data[path_i]*pow(10.0, -9)/(dt))));
			Path_Power.clear();
			for (path_pow=0;path_pow<Numtap;path_pow++) 
			{
				Path_Power.push_back( pow(10.0, (Path_Power_dB[path_pow]/10)));
				Power_sum=Power_sum+Path_Power[path_pow];
			}
			Path_Average_Amp.clear();
			for (path_pow=0;path_pow<Numtap;path_pow++) 
			{
				Path_Average_Amp.push_back( sqrt(Path_Power[path_pow]/Power_sum));
			}
			corrmodel=1;
			alf=22.5;
			loson=0;
			if(uplink==1)
			{
				double aglT_data[]={105.6,105.6,105.6,105.6,105.6,105.6,105.6,105.6,105.6,105.6,105.6,105.6,105.6,105.6,105.6,293.1,293.1,293.1,293.1,293.1,293.1,293.1,293.1,293.1,293.1,293.1,293.1,61.9,61.9,61.9,61.9,61.9,61.9,61.9,275.7,275.7,275.7,275.7};
				double aglsprT_data[]={36.1,36.1,36.1,36.1,36.1,36.1,36.1,36.1,36.1,36.1,36.1,36.1,36.1,36.1,36.1,42.5,42.5,42.5,42.5,42.5,42.5,42.5,42.5,42.5,42.5,42.5,42.5,38.0,38.0,38.0,38.0,38.0,38.0,38.0,38.7,38.7,38.7,38.7};
				double distypeT_data[]={2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
				double aglR_data[]={163.7,163.7,163.7,163.7,163.7,163.7,163.7,163.7,163.7,163.7,163.7,163.7,163.7,163.7,163.7,251.8,251.8,251.8,251.8,251.8,251.8,251.8,251.8,251.8,251.8,251.8,251.8,80.0,80.0,80.0,80.0,80.0,80.0,80.0,182.0,182.0,182.0,182.0};
				double aglsprR_data[]={35.8,35.8,35.8,35.8,35.8,35.8,35.8,35.8,35.8,35.8,35.8,35.8,35.8,35.8,35.8,41.6,41.6,41.6,41.6,41.6,41.6,41.6,41.6,41.6,41.6,41.6,41.6,37.4,37.4,37.4,37.4,37.4,37.4,37.4,40.3,40.3,40.3,40.3};
				double distypeR_data[]={2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
				for(int agl_i=0;agl_i<Numtap;agl_i++)
				{
					aglT.push_back( aglT_data[agl_i]);
					aglsprT.push_back( aglsprT_data[agl_i]);
					distypeT.push_back( distypeT_data[agl_i]);
					aglR.push_back( aglR_data[agl_i]);
					aglsprR.push_back( aglsprR_data[agl_i]);
					distypeR.push_back( distypeR_data[agl_i]);
				}
				dT=0.5;
				dR=0.5; //0.5 or 10
			}
			else
			{	
				double aglT_data[]={105.6,105.6,105.6,105.6,105.6,105.6,105.6,105.6,105.6,105.6,105.6,105.6,105.6,105.6,105.6,293.1,293.1,293.1,293.1,293.1,293.1,293.1,293.1,293.1,293.1,293.1,293.1,61.9,61.9,61.9,61.9,61.9,61.9,61.9,275.7,275.7,275.7,275.7};
				double aglsprT_data[]={36.1,36.1,36.1,36.1,36.1,36.1,36.1,36.1,36.1,36.1,36.1,36.1,36.1,36.1,36.1,42.5,42.5,42.5,42.5,42.5,42.5,42.5,42.5,42.5,42.5,42.5,42.5,38.0,38.0,38.0,38.0,38.0,38.0,38.0,38.7,38.7,38.7,38.7};
				double distypeT_data[]={2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
				double aglR_data[]={163.7,163.7,163.7,163.7,163.7,163.7,163.7,163.7,163.7,163.7,163.7,163.7,163.7,163.7,163.7,251.8,251.8,251.8,251.8,251.8,251.8,251.8,251.8,251.8,251.8,251.8,251.8,80.0,80.0,80.0,80.0,80.0,80.0,80.0,182.0,182.0,182.0,182.0};
				double aglsprR_data[]={35.8,35.8,35.8,35.8,35.8,35.8,35.8,35.8,35.8,35.8,35.8,35.8,35.8,35.8,35.8,41.6,41.6,41.6,41.6,41.6,41.6,41.6,41.6,41.6,41.6,41.6,41.6,37.4,37.4,37.4,37.4,37.4,37.4,37.4,40.3,40.3,40.3,40.3};
				double distypeR_data[]={2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};

				int agl_i;

		
				for(agl_i=0;agl_i<Numtap;agl_i++)
				{
					aglT.push_back( aglT_data[agl_i]);
					aglsprT.push_back( aglsprT_data[agl_i]);
					distypeT.push_back( distypeT_data[agl_i]);
					aglR.push_back( aglR_data[agl_i]);
					aglsprR.push_back( aglsprR_data[agl_i]);
					distypeR.push_back( distypeR_data[agl_i]);
				}

				dT=0.5;
				dR=0.5; //0.5 or 10
			}
		}else if(Channel_Type=='F')
		{
			// Model F with 150 ns rms delay spread.

			double Path_Data[]={0,10,20,30,50,80,110,140,180,230,280,330,400,490,600,50,80,110,140,180,230,280,330,400,490,600,730,180,230,280,330,400,490,600,400,490,600,600,730,880,1050};
			double Path_Power_dB[]={-3.3,-3.6,-3.9,-4.2,-4.6,-5.3,-6.2,-7.1,-8.2,-9.5,-11.0,-12.5,-14.3,-16.7,-19.9,-1.8,-2.8,-3.5,-4.4,-5.3,-7.4,-7.0,-10.3,-10.4,-13.8,-15.7,-19.9,-5.7,-6.7,-10.4,-9.6,-14.1,-12.7,-18.5,-8.8,-13.3,-18.7,-12.9,-14.2,-16.3,-21.2};
			double Power_sum=0;

			int path_i;
			int path_pow;

			NumOfTaps=41;
			Numtap=41;
			Path_Delay.clear();
			for (path_i=0; path_i<Numtap; path_i++)	
				Path_Delay.push_back( round((Path_Data[path_i]*pow(10.0, -9)/(dt))));
			Path_Power.clear();
			for (path_pow=0;path_pow<Numtap;path_pow++) 
			{
				Path_Power.push_back( pow(10.0, (Path_Power_dB[path_pow]/10)));
				Power_sum=Power_sum+Path_Power[path_pow];
			}
			Path_Average_Amp.clear();
			for (path_pow=0;path_pow<Numtap;path_pow++) 
			{
				Path_Average_Amp.push_back( sqrt(Path_Power[path_pow]/Power_sum));
			}

			corrmodel=1;
			alf=22.5;
			loson=0;

			if(uplink==1)
			{
				double aglT_data[]={56.2,56.2,56.2,56.2,56.2,56.2,56.2,56.2,56.2,56.2,56.2,56.2,56.2,56.2,56.2,183.7,183.7,183.7,183.7,183.7,183.7,183.7,183.7,183.7,183.7,183.7,183.7,153.0,153.0,153.0,153.0,153.0,153.0,153.0,112.5,112.5,112.5,291.0,291.0,62.3,62.3};
				double aglsprT_data[]={41.6,41.6,41.6,41.6,41.6,41.6,41.6,41.6,41.6,41.6,41.6,41.6,41.6,41.6,41.6,55.2,55.2,55.2,55.2,55.2,55.2,55.2,55.2,55.2,55.2,55.2,55.2,47.4,47.4,47.4,47.4,47.4,47.4,47.4,27.2,27.2,27.2,33.0,33.0,38.0,38.0};
				double distypeT_data[]={2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
				double aglR_data[]={315.1,315.1,315.1,315.1,315.1,315.1,315.1,315.1,315.1,315.1,315.1,315.1,315.1,315.1,315.1,180.4,180.4,180.4,180.4,180.4,180.4,180.4,180.4,180.4,180.4,180.4,180.4,74.7,74.7,74.7,74.7,74.7,74.7,74.7,251.5,251.5,251.5,68.5,68.5,24.6,24.6};
				double aglsprR_data[]={48.0,48.0,48.0,48.0,48.0,48.0,48.0,48.0,48.0,48.0,48.0,48.0,48.0,48.0,48.0,55.0,55.0,55.0,55.0,55.0,55.0,55.0,55.0,55.0,55.0,55.0,55.0,42.0,42.0,42.0,42.0,42.0,42.0,42.0,28.6,28.6,28.6,30.7,30.7,38.2,38.2};
				double distypeR_data[]={2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
				for(int agl_i=0;agl_i<Numtap;agl_i++)
				{
					aglT.push_back( aglT_data[agl_i]);
					aglsprT.push_back( aglsprT_data[agl_i]);
					distypeT.push_back( distypeT_data[agl_i]);
					aglR.push_back( aglR_data[agl_i]);
					aglsprR.push_back( aglsprR_data[agl_i]);
					distypeR.push_back( distypeR_data[agl_i]);
				}
				dT=0.5;
				dR=0.5; //0.5 or 10
			}
			else
			{
				double aglT_data[]={56.2,56.2,56.2,56.2,56.2,56.2,56.2,56.2,56.2,56.2,56.2,56.2,56.2,56.2,56.2,183.7,183.7,183.7,183.7,183.7,183.7,183.7,183.7,183.7,183.7,183.7,183.7,153.0,153.0,153.0,153.0,153.0,153.0,153.0,112.5,112.5,112.5,291.0,291.0,62.3,62.3};
				double aglsprT_data[]={41.6,41.6,41.6,41.6,41.6,41.6,41.6,41.6,41.6,41.6,41.6,41.6,41.6,41.6,41.6,55.2,55.2,55.2,55.2,55.2,55.2,55.2,55.2,55.2,55.2,55.2,55.2,47.4,47.4,47.4,47.4,47.4,47.4,47.4,27.2,27.2,27.2,33.0,33.0,38.0,38.0};
				double distypeT_data[]={2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
				double aglR_data[]={315.1,315.1,315.1,315.1,315.1,315.1,315.1,315.1,315.1,315.1,315.1,315.1,315.1,315.1,315.1,180.4,180.4,180.4,180.4,180.4,180.4,180.4,180.4,180.4,180.4,180.4,180.4,74.7,74.7,74.7,74.7,74.7,74.7,74.7,251.5,251.5,251.5,68.5,68.5,24.6,24.6};
				double aglsprR_data[]={48.0,48.0,48.0,48.0,48.0,48.0,48.0,48.0,48.0,48.0,48.0,48.0,48.0,48.0,48.0,55.0,55.0,55.0,55.0,55.0,55.0,55.0,55.0,55.0,55.0,55.0,55.0,42.0,42.0,42.0,42.0,42.0,42.0,42.0,28.6,28.6,28.6,30.7,30.7,38.2,38.2};
				double distypeR_data[]={2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
				for(int agl_i=0;agl_i<Numtap;agl_i++)
				{
					aglT.push_back( aglT_data[agl_i]);
					aglsprT.push_back( aglsprT_data[agl_i]);
					distypeT.push_back( distypeT_data[agl_i]);
					aglR.push_back( aglR_data[agl_i]);
					aglsprR.push_back( aglsprR_data[agl_i]);
					distypeR.push_back( distypeR_data[agl_i]);
				}
				dT=0.5;
				dR=0.5; //0.5 or 10
			}

		}//else mexErrMsgTxt("Input wrong channel type .");
	double  LastUpdateInterval;
	if(MobileSpeed != 0.0)
	{	
	fd_max = MobileSpeed / 3.6 / SpeedOfLight * CarrierFrequency*cos((alf)*2*PI/360);
	// maximum doppler frequency (in [Hz])

	UpdateInterval = round((MaxPhaseChange / 360.0) / fd_max / (dt)/1000);//?//

	// in samples 

	// restrict "UpdateInterval" to the interval [1; lburst]  
	if(UpdateInterval<1) UpdateInterval=1;
	if(UpdateInterval>LengthOfBurst) UpdateInterval=LengthOfBurst;			//更新间隔%

	UpdatesPerBurst = round((LengthOfBurst-1) / UpdateInterval);  //更新次数%
	LastUpdateInterval = LengthOfBurst - UpdatesPerBurst *UpdateInterval;
	}
	else
	{
		UpdatesPerBurst = 0;
		UpdateInterval = 0;
		LastUpdateInterval = LengthOfBurst;
	}
	//-----------------------------------------------------------------------
	// Parameters for fading generating
	//-----------------------------------------------------------------------

	//-----------------------------------------------------------------------
	// Initialise the coefficients for fading generating
	//-----------------------------------------------------------------------

	double belta[100]={0};
	An.clear();
	Bn.clear();
	Wn.clear();
	for(n=0;n<M_OSCIL;n++)
	{
		belta[n] = PI*n/M_OSCIL;
		An.push_back( 2*cos(belta[n]));
		Bn.push_back(2*sin(belta[n]));
	}
	An.push_back( 1.0);
	Bn.push_back( 1.0);
	//-----------------------------------------------------------------------
	// Initialise the tone frequencies 
	//-----------------------------------------------------------------------
	for(n=0;n<M_OSCIL;n++)
	{
		Wn.push_back( 2.0 * PI * fd_max * cos(2*PI*n/N_MAGIC));
	}
	Wn.push_back( 2.0 * PI * fd_max);
	Numtap = NumOfTaps;
	srand(time(0)); //种子必须放在循环外面，否则数一样。
	RndPhase.resize(NumOfChannels * Numtap * M_TONES);
	for(ant=1;ant<=NumOfChannels;ant++)//信道数
	{
		for(tap=0;tap<Numtap;tap++)//每个信道的多径数
		{
			int tone;
			for(tone=0;tone<M_TONES;tone++)
			{
				double Rnd[100]={0};
				Rnd[tone]=(int)(rand()/(RAND_MAX+1.0));
				RndPhase[tone*(Numtap*(ant-1))+tone]=PI*(1-2*Rnd[tone]);
			}
			
		}
	}
	fd=fd_max;	
};

#endif