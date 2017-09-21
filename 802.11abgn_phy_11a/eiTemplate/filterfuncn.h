#ifndef _FILTERFUNCN_H_
#define _FILTERFUNCN_H_
#include <vector>
#include <complex>
using namespace std;
vector<double> Lowpass_filter(int length,double Wn)
{
	//win = 0.54-0.46*cos(2*(0:N-1)*pi/(N-1));
	vector<double> filter_coefs;
	vector<double> win;
	vector<double> hd;
	filter_coefs.resize(length);
	hd.resize(length);
	win.resize(length);
	win[0] =0.08;
	for(int i=1;i<length;i++)
		win[i]  =0.54-0.46*cos(2*i*PI/(double)(length-1));
	for(int i=1;i<=length;i++){
		if((i-(length-1)/2.0)!=0)
			hd[i-1]=sin((i-(length-1)/2.0)*Wn*PI)/((i-(length-1)/2.0)*PI);
		else
			hd[i-1] = Wn;
	}
	for(int i=0;i<length;i++){
		filter_coefs[i]=hd[i]*win[i];
	}
	return filter_coefs;
}
vector<double> Gauss_filter(int length,double BT)
{
	double Wn = BT;
	vector<double> filter_coefs;
	vector<double> filter_temp;
	vector<double> win;
	vector<double> hd;
	filter_coefs.resize(length);
	hd.resize(length);
	win.resize(length);
	double tao,alpha=3.0,win_max=0.0;
	tao =2.0/Wn;
	for(int i=0;i<length;i++)
		filter_temp.push_back(-2*tao+i*4*tao/(length-1));
	//¸ßË¹win=(1/(alpha*sqrt(pi)*tao)).*exp(-(x/(alpha*tao)).^2);
	for(int i=0;i<length;i++)
		win[i]  =(1/(alpha*sqrt(PI)*tao))*exp(-1*pow(filter_temp[i]/(alpha*tao),2.0));
	for(int i=0;i<length;i++)
		if(win[i]>win_max)
			win_max =win[i];
	for(int i=0;i<length;i++)
		win[i]/=win_max;
	//¼Ó´°
	for(int i=1;i<=length;i++){
		if((i-(length-1)/2.0)!=0)
			hd[i-1]=sin((i-(length-1)/2.0)*Wn*PI)/((i-(length-1)/2.0)*PI);
		else
			hd[i-1] = Wn;
	}
	for(int i=0;i<length;i++){
		filter_coefs[i]=hd[i]*win[i];
	}
	return filter_coefs;
}	
void My_conv( vector<complex<double>>  &Data_in,vector<double> &filter_coef,int Data_in_len){
	int len,len_1;
	vector<complex<double>> Data_out;
	vector<complex<double>> Data_out_1;
	complex<double> data_temp;
	double          filter_temp; 
	len =Data_in_len+filter_coef.size()-1;
	len_1 =Data_in_len;
	Data_out.resize(len);
	for (int n=0;n<filter_coef.size();n++)
	{
		for (int i=0;i<=n;i++)
		{
			data_temp =Data_in[n-i];
			filter_temp =filter_coef[i];
			Data_out[n] +=data_temp * filter_temp;
		}
	}

	for (int n=filter_coef.size();n<Data_in_len;n++)
	{
		for (int i=0;i<filter_coef.size();i++)
		{
			data_temp =Data_in[n-i];
			filter_temp =filter_coef[i];
			Data_out[n] +=data_temp * filter_temp;
		}
	}

	for (int n=Data_in_len;n<len+1;n++)
	{
		for (int i=n-Data_in_len+1;i<filter_coef.size();i++)
		{
			data_temp =Data_in[n-i];
			filter_temp =filter_coef[i];
			Data_out[n] +=data_temp * filter_temp;
		}
	}
	for(int i =0 ;i < len_1 ;i++)
	{
		Data_in[i] =Data_out[i];
	}
}
vector<double> Root_raised_cosine(double alpha,int ntaps)
{
	double gain =1.0;
	ntaps |= 1;	// ensure that ntaps is odd
	double spb = 4; // samples per bit/symbol
	vector<double> taps(ntaps);
	double scale = 0;
	for(int i=0;i<ntaps;i++)
	{
		double x1,x2,x3,num,den;
		double xindx = i - ntaps/2;
		x1 = PI * xindx/spb;
		x2 = 4 * alpha * xindx / spb;
		x3 = x2*x2 - 1;
		if( fabs(x3) >= 0.000001 )  // Avoid Rounding errors...
		{
			if( i != ntaps/2 )
				num = cos((1+alpha)*x1) + sin((1-alpha)*x1)/(4*alpha*xindx/spb);
			else
				num = cos((1+alpha)*x1) + (1-alpha) * PI / (4*alpha);
			den = x3 * PI;
		}
		else
		{
			if(alpha==1)
			{
				taps[i] = -1;
				continue;
			}
			x3 = (1-alpha)*x1;
			x2 = (1+alpha)*x1;
			num = (sin(x2)*(1+alpha)*PI
				- cos(x3)*((1-alpha)*PI*spb)/(4*alpha*xindx)
				+ sin(x3)*spb*spb/(4*alpha*xindx*xindx));
			den = -32 * PI * alpha * alpha * xindx/spb;
		}
		taps[i] = 4 * alpha * num / den;
		scale += taps[i];
	}

	for(int i=0;i<ntaps;i++)
		taps[i] = taps[i] * gain / scale;

	return taps;
}
#endif