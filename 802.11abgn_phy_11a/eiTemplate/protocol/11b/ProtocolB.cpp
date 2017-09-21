#include "stdafx.h"
#include <fstream>  
#include "ProtocolB.h"
#include<math.h> 
#include "configB.h"
//#include"complex.h"
using namespace std;

//using namespace complex;
//#include "stdafx.h"

//#include <MATH.H>
//
//#ifdef _DEBUG
//#define new DEBUG_NEW
//#undef THIS_FILE
//static char THIS_FILE[] = __FILE__;
//#endif



CProtocolB::CProtocolB()
{	
	//txvector 参数设置
    //CProtocolB txvector;

	////速率可选 _1Mbps,_2Mbps,_55Mbps,_11Mbps
	//data_rate = _11Mbps;

	////preamble类型可选  shortPreamble，longPreamble
	//preamble_type = longPreamble;

	////调制方式 DBPSK_1Mbps，DQPSK_2Mbps，CCK55_55Mbps，PBCC55_55Mbps，CCK11_11Mpbs，PBCC11_11Mbps
	//modulation_type =PBCC11_11Mbps; 

	////扰码 ON,OFF,Preamble_only
	//scrambler_state = ON;

	//数据字节数
	//PayloadData_size_bytes = 1024;
	PayloadData_size_bytes =11;

	//PSDU_size_bytes=PayloadData_size_bytes + FCS_size_bytes + MACHeader_size_bytes;
	//PSDU_size_bytes=PayloadData_size_bytes + FCS_size_bytes + MACHeader_size_bytes;//1024+4+30 = 1058

	PSDU_size_bytes = PayloadData_size_bytes;

	data_size = 8*PSDU_size_bytes;

	//data_size=PayloadData_size_bytes*8;

	//生成数据序列
	//数据的生成需要换成 PN9 PN15 全零等 这里涉及一个switch case，switch条件由界面选择，传入
	//或者写一个函数调用

	srand(time(NULL));
	for(int i=0;i<data_size;i++)
	{		
		//Data.push_back(rand()%2);	
		Data.resize(data_size,0);

	}

	S_preambpart=NULL;
	S_headerpart=NULL;
	S_datapart=NULL;
	S_datapart_f=NULL;
	S_PPDU=NULL;
	S_preamb_length=0;
	S_header_length=0;
	S_data_length=0;
	S_PPDU_length=0;

	S_FFTATUOpower=NULL;
	S_FFTspectrum=NULL;

    sync_size=0;
    length=0;
	bin_length[16]=NULL;
	msg.resize(32,0);
	header.resize(48,0);                                                                                                     
	CRC_bits.resize(16,0);	

	// void CProtocolB::Run(CProtocolB txvector);
}

CProtocolB::~CProtocolB()
{
}

void CProtocolB::dec2bin(int obj, int bin[], int m)
{
	int n = 0;
	for (int i = 0;i < m;i++)
	{
		if (obj != 0)
		{
			bin[i] = obj%2;
			obj = obj/2;
		}
		else
			bin[i] = 0;
	}
}

void CProtocolB:: ComplexNumberOutput(fushu c)//复数输出
{
	if(c.real==0.0&&c.img==0.0)
		cout<<0<<endl;
	if(c.real==0.0&&c.img!=0.0)
		cout<<c.img<<"j"<<endl;
	if(c.real!=0.0&&c.img==0.0)
		cout<<c.real<<endl;
	if(c.real!=0.0&&c.img!=0.0)
		cout<<c.real<<"+"<<c.img<<"j"<<endl;
};

void CProtocolB::length_calculate(int * LENGTH_extension,unsigned int * LENGTH_2,int PSDU_size_bytes,char service_b3,Data_Rate data_rate)
{	//int * LENGTH_extension 
	//int  P = service[3];
	int P = service_b3;
	double data_rate_double;
	if (data_rate == 55)
		 data_rate_double = 5.5;
	else
		data_rate_double = data_rate;
	double LENGTH_1 = ((PSDU_size_bytes+P)*8)/(double)data_rate_double;
	*LENGTH_2 = (int)ceil(LENGTH_1);
    double x=*LENGTH_2-LENGTH_1;
	double y=(double)8/11;
	if( (data_rate==11)  &&  ( x >= y ) )
	{*LENGTH_extension=1;}
	else
	{*LENGTH_extension=0;}
};


void CProtocolB::DBPSK(std::complex<double> complex_modDB[],vector<int>Data,double theta0)
{
	double Phase_Constellation_0 = 0;
	double Phase_Constellation_1 = PI;
	double theta;
	int yPhase = 0;
	if (theta0 ==0 )
	{
		yPhase = 0;
	}
	else if(theta0 == PI/2)
	{
		yPhase = 1;
	}


	 for (int k = 0; k<Data.size();k++)
		{
			if (Data[k]==0)
				theta = Phase_Constellation_0 ;
			else
			{
				theta = Phase_Constellation_1;
		    	yPhase++;
		    }

		//yPhase = yPhase + theta;
		//yPhase++;

			if (yPhase%2==0)
			//	complex_modDB[k].setValue(1.0,0.0);
			   { complex_modDB[k].real(1.0);
			complex_modDB[k].imag(0.0);}
			else
				//complex_modDB[k].setValue(-1.0,0.0);
			    {complex_modDB[k].real(-1.0);
			complex_modDB[k].imag(0.0);}

		//complex_modDB[k].setValue(cos(yPhase),sin(yPhase));
		//complex_modDB[k].display();
	} 
  //return complex_modDB;
}

void CProtocolB::DQPSK(std::complex<double> complex_modDQ[],vector<int>Data,double theta0)
{
    double Phase_Constellation_00 = 0;
	double Phase_Constellation_01 = PI/2;
	double Phase_Constellation_11 = PI;
	double Phase_Constellation_10 = PI*3/2;
	double theta;

	int yPhase;


	if (theta0 ==0 )
	{
		yPhase = 0;
	}
	else if(theta0 == PI/2)
	{
		yPhase = 1;
	}
	else if(theta0 == PI)
	{
		yPhase = 2;
	}
	else if(theta0 == PI*3/2)
	{
		yPhase = 3;
	}
	vector<int> I(Data.size()/2) ;
    vector<int> Q(Data.size()/2) ;
	for (int k=0;k<(Data.size()/2);k++)//串并变换
	{
		I[k]= Data[k*2];
	    Q[k]= Data[k*2+1];

		if (I[k] == 0 && Q[k] == 0)
         {
			 theta = Phase_Constellation_00 = 0;
			yPhase += 0;
		 }
		else if(I[k] == 0 && Q[k] == 1)
		{
			 theta = Phase_Constellation_01 = PI/2;
			 yPhase += 1;
		}
		else if(I[k] == 1 && Q[k] == 1)
		{
			 theta = Phase_Constellation_11 = PI;
			 yPhase += 2;
		}
		else 
		{ 
			theta = Phase_Constellation_10 = PI*3/2;
			 yPhase += 3;
		}

		if (yPhase%4==0)
			{//complex_modDQ[k].setValue(1.0,0.0);
		    complex_modDQ[k].real(1.0);
			complex_modDQ[k].imag(0.0);}
		else if (yPhase%4==1)
			{//complex_modDQ[k].setValue(0.0,1.0);
			complex_modDQ[k].real(0.0);
			complex_modDQ[k].imag(1.0);
		    }
		else if (yPhase%4==2)
			{//complex_modDQ[k].setValue(-1.0,0.0);
			complex_modDQ[k].real(-1.0);
			complex_modDQ[k].imag(0.0);
		    }
		else
			{//complex_modDQ[k].setValue(0.0,-1.0);
				complex_modDQ[k].real(0.0);
				complex_modDQ[k].imag(-1.0);
		    }

		//yPhase = yPhase + theta;
		//complex_modDQ[k].setValue(cos(yPhase),sin(yPhase));
	} 
}

void CProtocolB::CCK55(std::complex<double> complexOut[], vector<int> data_in,double theta)
{
	int inf_len;
	inf_len = data_in.size();

	int i,j,k;
	double P, P1, P2, P3, P4;
	//P = 0.0;
	P = 0.0;
	P1 = theta;
	P2 = 0.0;
	P3 = 0.0;
	P4 = 0.0;
	struct fushu C[8]={};
    int **input = (int**)malloc(sizeof(short*)*inf_len/4); 
    for(i = 0; i < inf_len / 4; i++)   
        input[i] = (int*)malloc(sizeof(int)*4);
	int m=0;
	int e = 0,f = 0;
	int sign = 0;//符号初始编号为0
	for(j = 0; j < inf_len/4; j++)
		for( k = 0; k < 4; k++)
			input[j][k] = data_in[m++];
	if(m > inf_len+1)
		cout<<"error";
	if(inf_len % 4 != 0)
		cout<<"input error!";
	else
	{
		for(j = 0; j < inf_len / 4; j++)
		{
			e = input[j][0];
			f = input[j][1];
			if(sign % 2 == 0)     
			{
				if(e == 0 && f == 0)
					P = 0.0;
				else if (e == 0 && f == 1)
					P = PI/2;
				else if (e == 1 && f == 1)
					P = PI;
				else if(e == 1 && f == 0)
					P = -PI/2;
			}
			else
			{
				if(e == 0 && f == 0)
					P = PI;
				else if (e == 0 && f == 1)
					P = -PI/2;
				else if (e == 1 && f == 1)
					P = 0.0;
				else if(e == 1 && f == 0)
					P = PI/2;
			}
			sign++;

                P1 = P1 + P;
			//P1 = P;
		    //P2,P3,P4 采用CCK编码	
			P2 = input[j][2]*PI+PI/2;
			P3 = 0.0;
			P4 = input[j][3]*PI;

			//CCK码字
			C[0].real = (int)cos(P1+P2+P3+P4);
			C[0].img = (int)sin(P1+P2+P3+P4);
			C[1].real = (int)cos(P1+P3+P4);
			C[1].img = (int)sin(P1+P3+P4);
			C[2].real = (int)cos(P1+P2+P4);
			C[2].img = (int)sin(P1+P2+P4);
			C[3].real = -(int)cos(P1+P4);
			C[3].img = -(int)sin(P1+P4);
			C[4].real = (int)cos(P1+P2+P3);
			C[4].img = (int)sin(P1+P2+P3);
			C[5].real = (int)cos(P1+P3);
			C[5].img = (int)sin(P1+P3);
			C[6].real = -(int)cos(P1+P2);
			C[6].img = -(int)sin(P1+P2);
			C[7].real = (int)cos(P1);
			C[7].img = (int)sin(P1);

			//编码输出
			for(i = 0; i < 8; i++)
			{
				//ComplexNumberOutput(C[i]);
				//complexOut[j*8 + i].setValue(C[i].real, C[i].img);
				complexOut[j*8 + i].real(C[i].real);
				complexOut[j*8 + i].imag(C[i].img);
			}
			//cout<<endl;
		}
	}
};

void CProtocolB::CCK11(std::complex<double> complexOut[], vector<int> data_in,double theta)
{		
	int inf_len;
    //inf_len = sizeof(data_in)/sizeof(data_in[0]);
	inf_len = data_in.size();

	int i,j,k,l;
	double P;
	P=0.0;
	double fi[4]={};  
	fi[0]=theta;
                                                                                                                                                 ;
	struct fushu C[8]={};
    int **input = (int**)malloc(sizeof(short*)*inf_len/8); 
    for(i = 0; i < inf_len / 8; i++)   
        input[i] = (int*)malloc(sizeof(int)*8);
	int m=0;
	int e = 0,f = 0;
	int sign = 0;//符号初始编号为0
	for(j = 0; j < inf_len/8; j++)
		for( k = 0; k < 8; k++)
			input[j][k] = data_in[m++];
	if(m > inf_len+1)
		cout<<"error";
	if(inf_len % 8 != 0)
		cout<<"input error!";
	else
	{
		for(j = 0; j < inf_len / 8; j++)
		{
			e = input[j][0];
			f = input[j][1];
			//f = input[j][1];
			if(sign % 2 == 0)     
			{
				if(e == 0 && f == 0)
					P = 0.0;
				else if (e == 0 && f == 1)
					P = PI/2;
				else if (e == 1 && f == 1)
					P = PI;
				else if(e == 1 && f == 0)
					P = -PI/2;
			}
			else
			{
				if(e == 0 && f == 0)
					P = PI;
				else if (e == 0 && f == 1)
					P = -PI/2;
				else if (e == 1 && f == 1)
					P = 0.0;
				else if(e == 1 && f == 0)
					P = PI/2;
			}
			sign++;
                
               fi[0] = fi[0] + P;

		   //fi(2),fi(3),fi(4)采用QPSK编码
				for( l = 1; l < 4; l++)
				{
					if(input[j][2*l] == 0 && input[j][2*l+1] == 0)
						fi[l] = 0.0;
					else if(input[j][2*l] == 0 && input[j][2*l+1] == 1)
						fi[l] = PI/2;
					else if(input[j][2*l] == 1 && input[j][2*l+1] == 0)
						fi[l] = PI;
					else if(input[j][2*l] == 1 && input[j][2*l+1] == 1)
						fi[l] = -PI/2;
				}

				//CCK码字
			C[0].real = (int)cos(fi[0]+fi[1]+fi[2]+fi[3]);
			C[0].img = (int)sin(fi[0]+fi[1]+fi[2]+fi[3]);
			C[1].real = (int)cos(fi[0]+fi[2]+fi[3]);
			C[1].img = (int)sin(fi[0]+fi[2]+fi[3]);
			C[2].real = (int)cos(fi[0]+fi[1]+fi[3]);
			C[2].img = (int)sin(fi[0]+fi[1]+fi[3]);
			C[3].real = -(int)cos(fi[0]+fi[3]);
			C[3].img = -(int)sin(fi[0]+fi[3]);
			C[4].real = (int)cos(fi[0]+fi[1]+fi[2]);
			C[4].img = (int)sin(fi[0]+fi[1]+fi[2]);
			C[5].real = (int)cos(fi[0]+fi[2]);
			C[5].img = (int)sin(fi[0]+fi[2]);
			C[6].real = -(int)cos(fi[0]+fi[1]);
			C[6].img = -(int)sin(fi[0]+fi[1]);
			C[7].real = (int)cos(fi[0]);
			C[7].img = (int)sin(fi[0]);

			//编码输出
			for(i = 0; i < 8; i++)
			{
			//	ComplexNumberOutput(C[i]);
			//	complexOut[j*8 + i].setValue(C[i].real, C[i].img);
				complexOut[j*8 + i].real(C[i].real);
				complexOut[j*8 + i].imag(C[i].img);
				//cout<<endl;
			}
			
		}
			
	}
}

int CProtocolB::encoder(int gen[][7], int n, int L, int reg[], int m, vector<int> data_in, int inf_len, int output[])
//-------------------------------------------------------------------------------//
//  Function Discription: Convolutional Coding.
//-------------------------------------------------------------------------------//
//  History:
//    Created by Sun Weipeng    Date:2015-3-22    Version:1.0
//-------------------------------------------------------------------------------//
//  Fuction List
//-------------------------------------------------------------------------------//
//  Input Parameters:
//     gen		  is the generation sequence, which is a two-dimension array,and it is a two-dimension pointer,
//     n	      is the number of bits out the encoder at each clock cycle,
//     L	      is for the constraight length,
//     reg		  is for the shift registers,
//     m	      is for the number of registers,
//     data_in    is for the information sequence,
//     inf_len	  is for the inf length,
//     output     is for the output code.

//-------------------------------------------------------------------------------//
//  Output Parameters:
//-------------------------------------------------------------------------------//
//  Reference: scramble.m
//-------------------------------------------------------------------------------//
//  Note:
//    Null
//-------------------------------------------------------------------------------//
{
	int *inf_ex;
   //inf_ex = (int *) malloc((inf_len + m)* sizeof(int));
	inf_ex = (int *) malloc((inf_len + 8)* sizeof(int));
    int i,j;
   //for (i = 0;i < inf_len + m;i++)//尾比特
    for (i = 0;i < inf_len + 8;i++)//尾比特
    {
        if(i < inf_len)
            inf_ex[i] = data_in[i];
        else
            inf_ex[i] = 0;
    }
    //for (i = 0;i < inf_len + m;i++)
	for (i = 0;i < inf_len + 8;i++)
    {
        for (j = 0;j < n;j++)
        {
            int out_tem = 0;
			 if (gen[j][0] == 1)//判断第一位有没有接
                out_tem += inf_ex[i];
            int k;
            for (k = 0;k < m;k++)//遍历移位寄存器
            {
				 if (gen[j][k+1] == 1)
                    out_tem = out_tem + reg[k];
            }
            out_tem %= 2;//Mod 2
            output[i * n + j] = out_tem;
        }
        for (j = m - 1;j > 0;j--)//寄存器移位
        {
            reg[j] = reg[j - 1];
        }
        reg[0] = inf_ex[i];//寄存器输入数据
    }
    return 1;
}

void CProtocolB::repmat_PBCC_bits_55(vector<int> data_in, int Nfrm, int *convecdata,int tail_len,struct fushu *modout,double theta)
{
//-------------------------------------------------------------------------------//
//  Function Discription: Packet Binary Convolutional Coding.()5.5Mbits/s)
//-------------------------------------------------------------------------------//
//  History:
//    Created by Sun Weipeng    Date:2015-3-22    Version:1.0
//-------------------------------------------------------------------------------//
//  Fuction List
//-------------------------------------------------------------------------------//
//  Input Parameters:
//     data_in				is the pointer of information sequence,
//     Nfrm					is the number of Nfrm,
//     convecdata			is the pointer of convolutional encoder
//     tail_len				is the combination of info_len and tail_len,
//     modout               is the pointer of the phase info
//-------------------------------------------------------------------------------//
//  Output Parameters:
//-------------------------------------------------------------------------------//
//  Reference: scramble.m
//-------------------------------------------------------------------------------//
//  Note:
//    Null
//-------------------------------------------------------------------------------//
  int ia = 1;
  int ib = 0;
  int iacol = 1;
  int k,i,j;
  //int b = (sizeof(data_in) / sizeof(int)) / 256+1;//输入序列是否大于256位
  int b = data_in.size()/256+1;
  int *cover_bits;
  cover_bits = (int *) malloc(b * 256 * sizeof(int));//掩码序列
  int *PBCC_bits;
  PBCC_bits = (int *) malloc(tail_len * sizeof(int));
  int **rep_PBCC_cover_code   =   (int**)malloc(sizeof(short*)*16); 
  for(i=0;i<16;i++)   
     rep_PBCC_cover_code[i]   =   (int*)malloc(sizeof(int)*16);
  static const  int iv0[16] = {0,0,1,1,0,0,1,1,1,0,0,0,1,0,1,1};
  for(i = 0;i < 16; i++)
	  rep_PBCC_cover_code[0][i]=iv0[i];
  for(j = 1;j < 16; j++)//循环左移三位
  {
	//for(i = 3;i < 16; i++)
		/*rep_PBCC_cover_code[j][i-3]=rep_PBCC_cover_code[j-1][i];
	    rep_PBCC_cover_code[j][0]=rep_PBCC_cover_code[j-1][13];
	    rep_PBCC_cover_code[j][1]=rep_PBCC_cover_code[j-1][14];
        rep_PBCC_cover_code[j][2]=rep_PBCC_cover_code[j-1][15];*/
		for(i = 0;i < 13; i++)
		{
			rep_PBCC_cover_code[j][i]=rep_PBCC_cover_code[j-1][i+3];
		}   
		rep_PBCC_cover_code[j][13]=rep_PBCC_cover_code[j-1][0];
		rep_PBCC_cover_code[j][14]=rep_PBCC_cover_code[j-1][1];
		rep_PBCC_cover_code[j][15]=rep_PBCC_cover_code[j-1][2];
  }
  int m = 0;
  for(k = 0; k < b; k++)
	  for(i = 0; i < 16; i++)
		  for(j = 0;j < 16; j++)
			  cover_bits[m++]=rep_PBCC_cover_code[i][j]; //m可大于256位掩码 
  for (i = 0; i < tail_len; i++) 
  {
	 PBCC_bits[i] = cover_bits[i];//取L位掩码序列
  }
  for(i = 0;i < tail_len; i++)
  {
	if(PBCC_bits[i]==0)
	{
		if(convecdata[2*i]==0)
			{
			modout[2*i].real=sqrt(2.0)/2;
			modout[2*i].img=sqrt(2.0)/2;
			}
		else 
			{
			modout[2*i].real=-sqrt(2.0)/2;
			modout[2*i].img=-sqrt(2.0)/2;
			}
		if(convecdata[2*i+1]==0)
			{
			modout[2*i+1].real=sqrt(2.0)/2;
			modout[2*i+1].img=sqrt(2.0)/2;
			}
		else 
			{
			modout[2*i+1].real=-sqrt(2.0)/2;
			modout[2*i+1].img=-sqrt(2.0)/2;
			}
	}
	else if(PBCC_bits[i]==1)
	{
		if(convecdata[2*i]==0)
			{
			modout[2*i].real=-sqrt(2.0)/2;
			modout[2*i].img=sqrt(2.0)/2;
			}
		else 
			{
			modout[2*i].real=sqrt(2.0)/2;
			modout[2*i].img=-sqrt(2.0)/2;
			}
		if(convecdata[2*i+1]==0)
			{
			modout[2*i+1].real=-sqrt(2.0)/2;
			modout[2*i+1].img=sqrt(2.0)/2;
			}
		else 
			{
			modout[2*i+1].real=sqrt(2.0)/2;
			modout[2*i+1].img=-sqrt(2.0)/2;
			}
		}
	}
}

void CProtocolB::repmat_PBCC_bits_11(vector<int> data_in, int Nfrm, int *convecdata, int tail_len, struct fushu *modout,double theta)
{

//-------------------------------------------------------------------------------//
//  Function Discription: Packet Binary Convolutional Coding.(11Mbits/s)
//-------------------------------------------------------------------------------//
//  History:
//    Created by Sun Weipeng    Date:2015-3-22    Version:1.0
//-------------------------------------------------------------------------------//
//  Fuction List
//-------------------------------------------------------------------------------//
//  Input Parameters:
//     data_in				is the pointer of information sequence,
//     Nfrm					is the number of Nfrm,
//     convecdata			is the pointer of convolutional encoder
//     tail_len				is the combination of info_len and tail_len,
//     modout               is the pointer of the phase info
//-------------------------------------------------------------------------------//
//  Output Parameters:
//-------------------------------------------------------------------------------//
//  Reference: scramble.m
//-------------------------------------------------------------------------------//
//  Note:
//    Null
//-------------------------------------------------------------------------------//
  int ia = 1;
  int ib = 0;
  int iacol = 1;
  int k,i,j;
  //int b = (sizeof(data_in) / sizeof(int)) / 256+1;//输入序列是否大于256位
  int b = data_in.size()/256+1;
  int *cover_bits;
  cover_bits = (int *) malloc(b * 256 * sizeof(int));//掩码序列
  int *PBCC_bits;
  PBCC_bits = (int *) malloc(tail_len * sizeof(int));
  int f[2] = {};
  int dd;
  int **rep_PBCC_cover_code   =   (int**)malloc(sizeof(short*)*16); 
  for(i=0;i<16;i++)   
     rep_PBCC_cover_code[i]   =   (int*)malloc(sizeof(int)*16);
  // int *p=*rep_PBCC_cover_code;
  static const int iv0[16] = {0,0,1,1,0,0,1,1,1,0,0,0,1,0,1,1};
  for(i = 0;i < 16; i++)
	  rep_PBCC_cover_code[0][i]=iv0[i];
  for(j = 1;j < 16; j++)//循环左移三位
  {
	for(i = 0;i < 13; i++)
	{
		rep_PBCC_cover_code[j][i]=rep_PBCC_cover_code[j-1][i+3];
	 }   
		rep_PBCC_cover_code[j][13]=rep_PBCC_cover_code[j-1][0];
	    rep_PBCC_cover_code[j][14]=rep_PBCC_cover_code[j-1][1];
        rep_PBCC_cover_code[j][15]=rep_PBCC_cover_code[j-1][2];
	
  }
  int m = 0;
  for(k = 0; k < b; k++)
	  for(i = 0; i < 16; i++)
		  for(j = 0;j < 16; j++)
			  cover_bits[m++]=rep_PBCC_cover_code[i][j];  //m可大于256位掩码 
  for (i = 0; i < tail_len; i++) 
  {
	 PBCC_bits[i] = cover_bits[i];//取L位掩码序列
  }
  for(i = 0;i < tail_len; i++)
  {
	f[0] = convecdata[2 * i];//y0
	f[1] = convecdata[2 * i + 1];//y1
	k = 2 * f[0] + f[1];
	switch(k)
	{	 case 0: dd = 0;	
		        break;
		 case 1: dd = 1;
		 		break;
         case 2: dd = 3;
				break;
         case 3: dd = 2;
				break;
		 default:break;
	}	
	if(PBCC_bits[i]==0)
		{
		switch(dd)
			{
				case 0:{
						modout[i].real=sqrt(2.0)/2;
					    modout[i].img=sqrt(2.0)/2;
					   }
						break;
				case 1:{
					    modout[i].real=sqrt(2.0)/2;
					    modout[i].img=-sqrt(2.0)/2;
					   }
						break;						
				case 2:{
					    modout[i].real=-sqrt(2.0)/2;
					    modout[i].img=-sqrt(2.0)/2;
					   }
						break;		
				case 3:{
						modout[i].real=-sqrt(2.0)/2;
					    modout[i].img=sqrt(2.0)/2;
					   }
						break;
				default:break;
			}
		}
	else
		{
		switch(dd)
			{
				case 0:{
						modout[i].real=-sqrt(2.0)/2;
					    modout[i].img=sqrt(2.0)/2;
					   }
						break;
				case 1:{
					    modout[i].real=sqrt(2.0)/2;
					    modout[i].img=sqrt(2.0)/2;
					   }
						break;						
				case 2:{
					    modout[i].real=sqrt(2.0)/2;
					    modout[i].img=-sqrt(2.0)/2;
					   }
						break;		
				case 3:{
						modout[i].real=-sqrt(2.0)/2;
					    modout[i].img=-sqrt(2.0)/2;
					   }
						break;
				default:break;					
			}
		}
  }
  if (convecdata[0]==0 && convecdata[1]==0)
  {
	 if (theta==0)
	 {
		 modout[0].real=sqrt(2.0)/2;
		 modout[0].img=sqrt(2.0)/2;
	 } 
	 else if (theta==PI/2)
	 {
		 modout[0].real=-sqrt(2.0)/2;
		 modout[0].img=sqrt(2.0)/2;
	 }
	 else if (theta==PI)
	 {
		 modout[0].real=-sqrt(2.0)/2;
		 modout[0].img=-sqrt(2.0)/2;
	 } 
	 else
	 {
		 modout[0].real=sqrt(2.0)/2;
		 modout[0].img=-sqrt(2.0)/2;
	 }
  }

}

void CProtocolB::PBCC55(std::complex<double> complexOut[], vector<int> data_in,double theta)
{
   // LEN(data_in,int  inf_len);
	int inf_len;
    //inf_len = sizeof(data_in)/sizeof(data_in[0]);
	inf_len=data_in.size();//可能是取输入数据的长度
	int Nfrm = 1;
	int tail_len = inf_len + 8;
	struct fushu * modout=NULL;
	modout=(struct fushu *)malloc(sizeof(struct fushu)*tail_len*2);
	int i;
    int gen[2][7] = {{1, 1, 0, 1, 1, 0, 1}, {1, 0, 1, 1, 1, 1, 1}};//生成多项式
    int n;
    int L;//约束长度
    LEN(gen, n);
    LEN(gen[0], L);
    int m = L - 1;//移位寄存器个数
    int init_s[] = {0, 0, 0, 0, 0, 0}; //移位寄存器初始状态
	int *reg;
	reg = (int *) malloc(m * sizeof(int));
    for (i = 0;i < m;i++)
    {
        reg[i] = init_s[i];
    }
    //int output_len = (inf_len + m)*n;
    int output_len = (inf_len + 8)*n;
	int *output;
	output = (int *) malloc(output_len * sizeof(int));
    encoder(gen, n, L, reg, m, data_in, inf_len, output);//卷积编码
	//cout<<output<<endl;

	//for (i=0;i < output_len;i++)//输出卷积编码结果
	//{
	//	printf("%d",output[i]);
	//}
	//cout<<endl;

	repmat_PBCC_bits_55(data_in, Nfrm, output,tail_len,modout, theta);//根据卷积码得到相位信息
	for(i=0;i<tail_len*2;i++)//输出相位信息
	{
		//ComplexNumberOutput(modout[i]);
		//complexOut[i].setValue(modout[i].real, modout[i].img);
		complexOut[i].real(modout[i].real);
		complexOut[i].imag(modout[i].img);
	}
	//cout<<tail_len;
	//system("pause");
};    

void CProtocolB::PBCC11(std::complex<double> complexOut[], vector<int> data_in,double theta)
{
	//LEN(data_in, int inf_len);
	int inf_len;
    //inf_len = sizeof(data_in)/sizeof(data_in[0]);
	inf_len=data_in.size();//可能是取输入数据的长度

	int Nfrm = 1;
	int tail_len = inf_len + 8;
	struct fushu *modout=NULL;
	modout=(struct fushu *)malloc(sizeof(struct fushu)*tail_len);
	int i;
    int gen[2][7] = {{1, 1, 0, 1, 1, 0, 1}, {1, 0, 1, 1, 1, 1, 1}};//生成多项式序列
    int n;
    int L;//约束长度
    LEN(gen, n);
    LEN(gen[0], L);
    int m = L - 1;//移位寄存器个数
    int init_s[] = {0, 0, 0, 0, 0, 0}; //初始化移位寄存器状态
	int *reg;
	reg = (int *) malloc(m * sizeof(int));//移位寄存器状态
    for (i = 0;i < m;i++)
    {
        reg[i] = init_s[i];
    }
    //int output_len = (inf_len + m)*n;//输出长度
	int output_len = (inf_len + 8)*n;//输出长度
	int *output;
	output = (int *) malloc(output_len * sizeof(int));
    encoder(gen, n, L, reg, m, data_in, inf_len, output);//卷积编码
	
	//for (i=0;i < output_len;i++)//输出卷积编码结果
	//{
	//	printf("%d",output[i]);
	//}
	//cout<<endl;
	//cout<<endl;
	repmat_PBCC_bits_11(data_in, Nfrm, output,tail_len,modout,theta);////根据卷积码得到相位信息
	for(i=0;i<tail_len;i++)
	{
		//ComplexNumberOutput(modout[i]);
		//complexOut[i].setValue(modout[i].real, modout[i].img);
			complexOut[i].real(modout[i].real);
			complexOut[i].imag(modout[i].img);
	}
	
    //system("pause");
};

void CProtocolB::scramble(int str[], int b_index, int Nfrm, int scramble_out[], int inf_len)
{
//-------------------------------------------------------------------------------//
//  Function Discription: Scrambling code
//-------------------------------------------------------------------------------//
//  History:
//    Created by Sun Weipeng    Date:2015-3-22    Version:1.0
//-------------------------------------------------------------------------------//
//  Fuction List
//-------------------------------------------------------------------------------//
//  Input Parameters:
//    str           is for Information sequence                                                   
//    b_index       is for index
//    Nfrm          is for Nfrm
//    scramble_out  is for output sequence
//    inf_len       is for the length of information sequence 
//-------------------------------------------------------------------------------//
//  Output Parameters:
//-------------------------------------------------------------------------------//
//  Reference: PBCC11_MOD.m
//-------------------------------------------------------------------------------//
//  Note:
//    Null
//-------------------------------------------------------------------------------//
  int s[7];
  int i0;
  
  static const int iv0[7] = { 1, 1, 0, 1, 1, 0, 0 };
  static const int iv1[7] = { 0, 0, 1, 1, 0, 1, 1 };

  int kk;
  int y;
  int d0;
  int i1;
  int i2;
  int ss;
  int *tmp_data;
  tmp_data = (int *) malloc(inf_len * sizeof(int));
  int tmp_size_idx_0;
  int loop_ub;
  int i3;
  int *b_tmp_data;
  b_tmp_data = (int *) malloc(inf_len * sizeof(int));
  int b_s[6];
  if (b_index == 1)
  {
	  for (i0 = 0; i0 < 7; i0++) 
		 s[i0] = iv0[i0];
  }
  else 
  {
     for (i0 = 0; i0 < 7; i0++) 
		s[i0] = iv1[i0];
  }

  for (i0 = 0; i0 < 7; i0++) 
	 scramble_out[i0] = 0;  

  for (kk = 0; kk < Nfrm; kk++) 
  {
	 y = kk * inf_len / Nfrm;
	 d0 = (kk+1)* inf_len / Nfrm;
    if (y + 1 > d0) 
	{
		i0 = 1;
		i1 = 0;
    } 
	else 
    {
       i0 = (y + 1);
       i1 = d0;
    }
    i2 = (inf_len / Nfrm);
    for (ss = 0; ss <= i2 - 1; ss++) 
	{
      tmp_size_idx_0 = (i1 - i0) + 1;
      loop_ub = i1 - i0;
      for (i3 = 0; i3 <= loop_ub; i3++) 
	  {
         tmp_data[i3] = i0 + i3;
      }

      loop_ub = tmp_size_idx_0 - 1;

      for (i3 = 0; i3 <= loop_ub; i3++) 
	  {
         b_tmp_data[i3] = tmp_data[i3];
      }
	  y = (str[b_tmp_data[ss] - 1] + s[3]) + s[6];

      scramble_out[ss] = y % 2;

      for (i3 = 0; i3 < 6; i3++) 
	  {
         b_s[i3] = s[i3];
      }

      for (i3 = 0; i3 < 6; i3++) 
	  {
         s[1 + i3] = b_s[i3];
      }
      s[0] = scramble_out[ss];
    }
  }
}

void CProtocolB:: Barker_spread(std::complex<double> complex_barker[],std::complex<double> complex_mod[],int m) 
 {
	int inf_len;
//	inf_len=sizeof(complex_mod)/sizeof(complex_mod[0]);//sizeof(pointer)=4,not the length of array!!!!)
	inf_len = m;
	int Ns = 11;

 for(int j=0;j<inf_len;j++)											//Spread Spectrum
{
	for(int i=0; i<11; i++)
		{
			//complex_barker[j*Ns+i] = complex_mod[j]*spread11[i];
			//complex_barker[j*Ns+i] = complex_mod[j]*spread11[i];

			complex_barker[j*Ns+i].real(complex_mod[j].real()*spread11[i]);
			complex_barker[j*Ns+i].imag(complex_mod[j].imag()*spread11[i]);

		}
	//return complex_barker;
	}
};

std::vector<int> CProtocolB:: setVector(std::vector<int> vec, int temp[], int m)
{
	for (int i = 0;i < m;i++)
		vec.push_back(temp[i]);
	return vec;
}

vector<int> CProtocolB:: Produce_preamb_bit(int S_preamb_length)
{
	vector<int> preamble_bit;
	preamble_bit.resize(S_preamb_length,0);

	if (preamble_type ==shortPreamble)
	{  
		sync_size = 56;
		for (int i=0;i<sync_size;i++)
		{ 
			sync.push_back(0);
		};//56个0比特	

		//SFD=0x05CF;发送时从右边开始发送
		int temp[16] = {1,1,1,1,0,0,1,1,1,0,1,0,0,0,0,0};
		SFD = setVector(SFD, temp, 16);
		//preamble
		for (int j=0;j<sync_size;j++)
		{ 
			preamble_bit[j]=sync[j];
			//preamble.push_back(sync[j]);
		}

		for (int j=0;j<SFD_size;j++)
		{ 
			preamble_bit[j+56]=SFD[j];
			//preamble.push_back(SFD[j]);
		}
	}	
	else
	{
		sync_size =128;
		for (int i=0;i<sync_size;i++)
		{ 
			sync.push_back(1); 
		}//128个1比特

		//SFD=0xF3A0; 发送时从右边开始发送
		int temp[16] = {0,0,0,0,0,1,0,1,1,1,0,0,1,1,1,1};
		SFD = setVector(SFD, temp, 16);
		for (int j=0;j<sync_size;j++)
		{
			preamble_bit[j]=sync[j];
			//preamble.push_back(sync[j]);
		}
		for (int j=0;j<SFD_size;j++)
		{
			preamble_bit[j+128]=SFD[j];
			//preamble.push_back(SFD[j]);
		}
	}

	return preamble_bit;
	
}

void CProtocolB:: Produce_preamb(std::complex<double> complex_preamb[],vector<int> PPDU_Scrambled,std::complex<double> preamble_last_symbol[])
 {

	 double theta0 = 0;
	 if (preamble_type ==shortPreamble)
		{   
			int m = 72;
			vector<int> scrambleOut;
			scrambleOut.resize(m,0);
		 	std::complex<double> complex_modDB[72];
			
			for (int i=0;i<m;i++)
			{
				scrambleOut[i]=PPDU_Scrambled[i];
			}

			DBPSK(complex_modDB,scrambleOut,theta0);	
			preamble_last_symbol[0] = complex_modDB[71];
			Barker_spread(complex_preamb, complex_modDB,m);
		}		 
	else
		{	
			int m = 144;		  	
			vector<int> scrambleOut;
			scrambleOut.resize(m,0);
			std::complex<double> complex_modDB[144];

			for (int i=0;i<m;i++)
			{
				scrambleOut[i]=PPDU_Scrambled[i];
			}
		
		  DBPSK(complex_modDB, scrambleOut,theta0);	
		  preamble_last_symbol[0] = complex_modDB[143];
		  Barker_spread(complex_preamb, complex_modDB,m);
	 }      
	
 }

vector<int> CProtocolB::Produce_header_bit(int S_header_length,int bytes)
 {
	 int * LENGTH_extension = new int;
	 * LENGTH_extension = 0;
	 switch(data_rate)
	 {
	 case  _1Mbps:
		 {
			 signal = 0x50;;
			 service = 0x00;
			 char service_b3 = 0;
			 length_calculate(LENGTH_extension,&length,PSDU_size_bytes,service_b3,_1Mbps);		
			 break;
		 }
	 case _2Mbps:		
		 {

			 //signal = 0x14;
			 signal = 0x28;
			 service = 0x00;
			 char service_b3 = 0;
			 length_calculate(LENGTH_extension,&length,PSDU_size_bytes,service_b3,_2Mbps);
			 break;
		 }
	 case _55Mbps:
		 {
			 //signal = 0x37;
			 signal = 0xec;
			 service = 0x00;
			 int service_b3 = 0; 
			 if (modulation_type != CCK55_55Mbps)		 
			 { service_b3 = 1;
			 service = 0x10;}
			 length_calculate(LENGTH_extension,&length,PSDU_size_bytes,service_b3,_55Mbps);
			 if (modulation_type != CCK55_55Mbps)		 
			 {}
			 break;
		 }
	 case _11Mbps:
		 {
			 //signal = 0x6E;
			 signal = 0x76;
			 service = 0x00;
			 char service_b3 = 0; 
			 if (modulation_type != CCK11_11Mpbs)	 
			 { 
				 service_b3 = 1;
				 service = 0x10;
			 }		 
			 length_calculate(LENGTH_extension,&length,PSDU_size_bytes,service_b3,_11Mbps);		
			
			 if ( *LENGTH_extension == 1)
			 { 
				 service = service ^ 0x01;
			 }
			/* int x=(int) bytes*8/11;
			 double y=bytes*8/11;
			 double delt=y-x;
			 if(delt>8/11)
			 {
			 service = service ^ 0x01;
			 }*/
			 break;
		 }
	 default:
		 {
			 assert(false);
			 break;
		 }
	 }

	 for (int i=0;i< signal_size;i++)
	 {		
		 msg[signal_size-1-i] = (signal>>i)&0x01; //低有效位先发送
	 }

	 for (int i=0;i<service_size;i++)
	 {
		 msg[signal_size+service_size-1-i] = (service>>i) & 0x01;//b0开始发送，这里需要确认一下，目前是高有效位在前！！！！！！改成b0先发送
	 }

	 for (int i=0;i<length_size;i++)
	 {	
		 msg[i+signal_size+service_size] = (length>>i) & 0x01;//低有效位先发送
	 }


	 // bit reverse
	 unsigned int r = length; // r will be reversed bits of v; first get LSB of v
	 int s = sizeof(length) * CHAR_BIT - 1; // extra shift needed at end

	 for (length >>= 1; length; length >>= 1)
	 {   
		 r <<= 1;
		 r |= length & 1;
		 s--;
	 }
	 r <<= s; // shift when v's highest bits are zero

	 unsigned char length1,length2;
	 length2=(unsigned char)(r>>16);
	 length1=(unsigned char)(r>>24);

	 unsigned short msg_size = 32;
	 unsigned char buf[4] = {signal,service,length1,length2};//把三个字段传入crc  传入的应该是四个字节，length拆成两个字节
	 int crc_16[16]={0};
	 unsigned short crc; 

	 crc = crc16(buf,msg_size);
	 dec2bin( crc,crc_16,16);

	 msg_size = 32;
	 for (int i=0;i<msg_size;i++)
		 header[i] = msg[i];

	 for (int i = 0;i<CRC_size;i++)
		 header[i+msg_size] = crc_16[CRC_size-1-i];

	 return header;
	 delete [] LENGTH_extension;

 }

void CProtocolB::Produce_header(std::complex<double> complex_header[],vector<int> PPDU_Scrambled,double theta0,std::complex<double> header_last_symbol[],std::complex<double> header_last_chip[])
  {
	
    if (preamble_type == longPreamble)
	{
		int m = 6*BYTE_B;
		vector<int> scrambleOut;
		scrambleOut.resize(m,0);
		std::complex<double> complex_modDB[6*BYTE_B];
		for (int i=0;i<m;i++)
		{
			scrambleOut[i]=PPDU_Scrambled[i+144];
		}
		DBPSK(complex_modDB,scrambleOut,theta0);
		 header_last_symbol[0] = complex_modDB[47];
        Barker_spread(complex_header,complex_modDB,m);  
		header_last_chip[0]=complex_header[527];
	}
	else
	{
		int m = 24;
		vector<int> scrambleOut; 
		scrambleOut.resize(48,0);
		std::complex<double> complex_modDQ[24];
		for (int i=0;i<48;i++)
		{
			scrambleOut[i]=PPDU_Scrambled[i+72];
		}
		DQPSK(complex_modDQ,scrambleOut,theta0);
		 header_last_symbol[0] = complex_modDQ[23];
        Barker_spread(complex_header,complex_modDQ,m);
		header_last_chip[0] =complex_header[263];
	}
  }

void CProtocolB::Produce_PSDU(std::complex<double> complex_PSDU[],vector<int> PPDU_Scrambled,double theta1,double theta2)
 {
     //加扰
	 int len = data_size;
	 vector<int> scrambleOut;
	 scrambleOut.resize(len,0);
	 if (preamble_type == longPreamble)
	 {
		 for (int i=0;i<len;i++)
		 {
			 scrambleOut[i]=PPDU_Scrambled[i+192];
		 }
	 }
	 else
	{ 
		for (int i=0;i<len;i++)
		{
			scrambleOut[i]=PPDU_Scrambled[i+120];
		}
	 }

	  //int data_size = Data.size();
     //	complex * complex_modDB = new complex [data_size];
	if (modulation_type == 0)   //DBPSK
	{  
		std::complex<double> * complex_modDB = new std::complex<double> [data_size];
		DBPSK(complex_modDB,scrambleOut,theta1);
		//int m = data_size;
	    Barker_spread(complex_PSDU,complex_modDB,data_size);
		delete [] complex_modDB;
	}
	else if(modulation_type == 1)  //DQPSK
	{   
		int m = data_size/2;
		std::complex<double> * complex_modDQ = new std::complex<double> [m];
	    DQPSK(complex_modDQ,scrambleOut,theta1);
	//	int m = data_size;
	    Barker_spread(complex_PSDU, complex_modDQ,m);
		delete [] complex_modDQ;
	}
	else if(modulation_type == 2)  //CCK5.5
	{
		
		CCK55(complex_PSDU, scrambleOut,theta1);

	}
		
	else if(modulation_type == 3)  //PBCC5.5
	{

         PBCC55(complex_PSDU, scrambleOut,theta2);
	}

	else if(modulation_type == 4)  //CCK11
	{
	     CCK11(complex_PSDU,scrambleOut,theta1);
	}

	else if(modulation_type == 5)  //PBCC11
	{
		 PBCC11(complex_PSDU,scrambleOut,theta2);
	}
	else 
		cout<<"Error modulation!\n";
 // delete [] complex_modDB;
  
  }

void CProtocolB::Produce_PPDU(std::complex<double> preambpart_in[],std::complex<double> headerpart_in[],std::complex<double> datapart_in[],std::complex<double> PPDU_out[],int preamb_length,int header_length,int data_length)
  {

    int PPDU_i=0;
	
	for(PPDU_i=0;PPDU_i<preamb_length;PPDU_i++) PPDU_out[PPDU_i]=preambpart_in[PPDU_i];

	for(PPDU_i=0;PPDU_i<header_length;PPDU_i++) PPDU_out[PPDU_i+preamb_length]=headerpart_in[PPDU_i];

	for(PPDU_i=0;PPDU_i<data_length;PPDU_i++) PPDU_out[PPDU_i+preamb_length+header_length]=datapart_in[PPDU_i];

  } 


void CProtocolB::tx_param(Encoding e)
{
	//以下配置项需要和界面传递参数，目前只传递了MCS选项！
	switch(e)
	{
	case DBPSK_1M:
		//速率可选 _1Mbps,_2Mbps,_55Mbps,_11Mbps
		data_rate = _1Mbps;
		//preamble类型可选  shortPreamble，longPreamble
		preamble_type = longPreamble;
		//调制方式 DBPSK_1Mbps，DQPSK_2Mbps，CCK55_55Mbps，PBCC55_55Mbps，CCK11_11Mpbs，PBCC11_11Mbps
		modulation_type = DBPSK_1Mbps; 
		//扰码 ON,OFF,Preamble_only
		scrambler_state = BprotocolConfig.scrambler_state;
		break;
	case  DQPSK_2M:
		//速率可选 _1Mbps,_2Mbps,_55Mbps,_11Mbps
		data_rate = _2Mbps;
		//preamble类型可选  shortPreamble，longPreamble
		preamble_type = BprotocolConfig.preamble_type;
		//调制方式 DBPSK_1Mbps，DQPSK_2Mbps，CCK55_55Mbps，PBCC55_55Mbps，CCK11_11Mpbs，PBCC11_11Mbps
		modulation_type = DQPSK_2Mbps; 
		//扰码 ON,OFF,Preamble_only
		scrambler_state = BprotocolConfig.scrambler_state;
		
		break;
	case   CCK_5_5M:
		//速率可选 _1Mbps,_2Mbps,_55Mbps,_11Mbps
		data_rate = _55Mbps;
		//preamble类型可选  shortPreamble，longPreamble
		preamble_type = BprotocolConfig.preamble_type;
		//调制方式 DBPSK_1Mbps，DQPSK_2Mbps，CCK55_55Mbps，PBCC55_55Mbps，CCK11_11Mpbs，PBCC11_11Mbps
		modulation_type = CCK55_55Mbps; 
		//扰码 ON,OFF,Preamble_only
		scrambler_state = BprotocolConfig.scrambler_state;

		break;
	case CCK_11M:
		//速率可选 _1Mbps,_2Mbps,_55Mbps,_11Mbps
		data_rate = _11Mbps;
		//preamble类型可选  shortPreamble，longPreamble
		preamble_type = BprotocolConfig.preamble_type;
		//调制方式 DBPSK_1Mbps，DQPSK_2Mbps，CCK55_55Mbps，PBCC55_55Mbps，CCK11_11Mpbs，PBCC11_11Mbps
		modulation_type = CCK11_11Mpbs; 
		//扰码 ON,OFF,Preamble_only
		scrambler_state = BprotocolConfig.scrambler_state;

		break;
	case   PBCC_5_5M:
		//速率可选 _1Mbps,_2Mbps,_55Mbps,_11Mbps
		data_rate = _55Mbps;
		//preamble类型可选  shortPreamble，longPreamble
		preamble_type = BprotocolConfig.preamble_type;
		//调制方式 DBPSK_1Mbps，DQPSK_2Mbps，CCK55_55Mbps，PBCC55_55Mbps，CCK11_11Mpbs，PBCC11_11Mbps
		modulation_type =PBCC55_55Mbps; 
		//扰码 ON,OFF,Preamble_only
		scrambler_state = BprotocolConfig.scrambler_state;

		break;
	case  PBCC_11M:
		//速率可选 _1Mbps,_2Mbps,_55Mbps,_11Mbps
		data_rate = _11Mbps;
		//preamble类型可选  shortPreamble，longPreamble
		preamble_type = BprotocolConfig.preamble_type;
		//调制方式 DBPSK_1Mbps，DQPSK_2Mbps，CCK55_55Mbps，PBCC55_55Mbps，CCK11_11Mpbs，PBCC11_11Mbps
		modulation_type =PBCC11_11Mbps; 
		//扰码 ON,OFF,Preamble_only
		scrambler_state = BprotocolConfig.scrambler_state;

		break;

	default:	
		//assert(false);
		break;
	}
}


 vector<int> CProtocolB::scrambler(vector<int>PPDU_bit)
 {

	 int length_PPDU = PPDU_bit.size();
	 vector<int>PPDU_scrambled;
	 PPDU_scrambled.resize(length_PPDU,0);

	 if (preamble_type ==shortPreamble)
	 {  
		// vector<int> scrambleOut;
		 if((scrambler_state == ON)||(scrambler_state == Preamble_only))
		 {
			 int b_index = 0; //short preamble initial 0 0 1 1 0 1 1
			 int Nfrm = 1;
			 int inf_len= PPDU_bit.size();
		//	 int inf_len_1=120;
			 int *scramble_out;
			 scramble_out = (int *) malloc(inf_len* sizeof(int));			 
			int *str = new int[inf_len];
			// int str_1[120];
			 for (int i=0;i<inf_len;i++)
			 {
				 str[i]=PPDU_bit[i];
			 }
			 scramble(str, b_index, Nfrm, scramble_out, inf_len);		  
			 for (int i=0;i<inf_len;i++)
			 {
				 PPDU_scrambled[i]=scramble_out[i];
			 }

			 //b_index = 1; //long preamble initial [1 1 0  1 1 0 0]
			 //int inf_len_2= PPDU_bit.size()-120;
			 //int *scramble_out_2;
			 //scramble_out_2 = (int *) malloc(inf_len_2* sizeof(int));
			 //int *str_2 = new int[inf_len_2];
			 //for (int i=0;i<inf_len_2;i++)
				// str_2[i]=Data[i];

			 //scramble(str_2, b_index, Nfrm, scramble_out_2, inf_len_2);	

			 //delete [] str_2;
			 //for (int i=0;i<inf_len_2;i++)
			 //{
				// PPDU_scrambled[i+120]=scramble_out_2[i];
			 //}

		 }
		 else
		 {
			 PPDU_scrambled = PPDU_bit;		   
		 }
	 }		 

	 else
	 {
		 if((scrambler_state == ON)||(scrambler_state == Preamble_only))
		 {   
			 int b_index = 1; //long preamble initial [1 1 0  1 1 0 0]
			 int Nfrm = 1;
			 int inf_len= PPDU_bit.size();
			 int *scramble_out;
			 scramble_out = (int *) malloc(inf_len* sizeof(int));
			 int *str = new int[inf_len];
			 for (int i=0;i<inf_len;i++)
				 str[i]=PPDU_bit[i];
			 scramble(str, b_index, Nfrm, scramble_out, inf_len);	
			 delete [] str;
			 for (int i=0;i<inf_len;i++)
			 {
				 PPDU_scrambled[i]=scramble_out[i];
			 }
		 }
		 else
		 {
			 PPDU_scrambled = PPDU_bit;		   
		 }
	 } 
	 return PPDU_scrambled;
 }
 void CProtocolB::channel_initialize_1(double RndPhase[][12], double *Path_Delay, double *Path_Average_Amp, double *fore_data_pr, double *fore_data_pi, \
	 double* RMS_Delay_Sample, double MAX_Delay_Sample, int NumOfTaps, double *Path_Average_Power, \
	 int sizeof_Path_Delay, int sizeof_Path_Average_Power){
		 int tap;
		 int TONES;
		 int Sample;

		 int NumOfFreq = 8;
		 int M_OSCIL = NumOfFreq;
		 int M_TONES = M_OSCIL + 1;
		 //随机相位生成

		 for(int i=0;i<NumOfTaps;i++)
			 for(int j=0;j<M_TONES;j++)
				 RndPhase[i][j]=PI * (1-2*rand()/(RAND_MAX +1.0));
		 //多径时延生成
		 double Dexp_sample = floor(MAX_Delay_Sample/(NumOfTaps-1));

		 Path_Delay[0] = 0;
		 for( int i=1 ;i <= NumOfTaps -1 ;i++)
			 Path_Delay[i] = Dexp_sample * i ;
		 //多径功率生成
		 Path_Average_Power[0] = 1;
		 double bili =pow(10.0,(1.2 / (double)NumOfTaps));
		 for( int i=1 ;i <= NumOfTaps -1 ;i++)
			 Path_Average_Power[i] = Path_Average_Power[i-1] / bili;

		 double tao_avg = 0;
		 double tao2_avg = 0;

		 double TotalPower = 0;
		 double Scaled_Path_Average_Power = 0;



		 for (tap = 0; tap<NumOfTaps; tap++)
		 {
			 TotalPower = TotalPower + Path_Average_Power[tap];  //unify the power
		 }

		 //              calculate the RMS delay 
		 //---------------------------------------------------------------



		 for (tap = 0; tap<NumOfTaps; tap++)
		 {
			 tao_avg = tao_avg + ((Path_Average_Power[tap] * Path_Delay[tap]) / TotalPower);
			 tao2_avg = tao2_avg + ((Path_Average_Power[tap] * (Path_Delay[tap] * Path_Delay[tap])) / TotalPower);
		 }
		 *RMS_Delay_Sample = sqrt(tao2_avg - tao_avg*tao_avg);


		 //Scale tap powers to total power 1.0 and convert to amplitudes
		 //----------------------------------------------------------------                         
		 for (tap = 0; tap<NumOfTaps; tap++)
		 {
			 Scaled_Path_Average_Power = Path_Average_Power[tap] / TotalPower;
			 Path_Average_Amp[tap] = sqrt(Scaled_Path_Average_Power);              //the amplitude of each tap
		 }


		 //Build the fore_data
		 //---------------------------------------------------------------- 
		 for (Sample = 0; Sample<MAX_Delay_Sample; Sample++)
		 {
			 fore_data_pr[Sample] = rand() / double(RAND_MAX);     //必须用复数向量进行初始化，该变量空间用于保存信道前一帧对后一帧的时延影响
			 fore_data_pi[Sample] = rand() / double(RAND_MAX);
		 }
 }
 void CProtocolB::Jakes_kernel(double Path_Ampli,int NumOfFreq,int UpdateInterval,double fd_max,double* Phase,\
	 int UpdatesPerBurst,int LengthOfBurst,int t_tmp,\
	 double dt,vector<double> &fading_re,vector<double> &fading_im)
 {  
	 int i,j,k,n,M_tones,M_magic;
	 double cosine, scale,ival,qval;


	 M_tones=NumOfFreq+1;
	 M_magic=NumOfFreq*4+2;//N//

	 i=0;
	 scale=1.414*Path_Ampli/sqrt(float(M_magic));
	 double An[9];
	 double Bn[9];
	 double Wn[9];
	 for (int i=0;i <M_tones-1;i++)
	 {
		 An[i] = 2 *cos(PI *(i+1) /(M_tones-1));
		 Bn[i] = 2 *sin(PI *(i+1) /(M_tones-1));
		 Wn[i] = 2 * PI * fd_max * cos(2*PI*(i+1)/M_magic);
	 }
	 An[M_tones-1] = 1.0;
	 Bn[M_tones-1] =1.0;
	 Wn[M_tones-1] =2 * PI * fd_max;
	 int ii=0;
	 for(k=0;k<UpdatesPerBurst;k++)   //一帧中更新UpdatesPerBurst
	 {
		 //Reset sum 
		 ival = 0;
		 qval = 0;
		 for(n=0;n<M_tones;n++)
		 {
			 cosine = cos(Wn[n]*t_tmp*dt+Phase[n]);

			 ival = ival+An[n] * cosine;
			 qval = qval+Bn[n] * cosine;  //参见Jakes模型公式
		 }

		 for(j=ii;j<ii+UpdateInterval;j++)   //一帧中信道衰落系数，一个更新间隔内不改变 
		 {

			 fading_re[j]= ival * scale;
			 fading_im[j]= qval * scale;

		 }
		 ii=ii+UpdateInterval;
		 t_tmp=t_tmp+UpdateInterval;    
	 } 
 }
 void CProtocolB::multipath_channel(vector<double> &InData_pr,vector<double> &InData_pi,\
	double fd_max,long NumOfTaps,\
	int SamplesPerFrame,int ChangesPerFrame,\
	int* TimeIndex,double dt,\
	double Phase[][12],double *Path_Delay,double *Path_Average_Amp,\
	vector<double> &OutData_pr,vector<double> &OutData_pi,\
	double *out_fading_pr,double *out_fading_pi,\
	double *fore_data_pr,double *fore_data_pi,\
	double *fading_indx)
{   
	dt=dt/BprotocolConfig.oversample_ratio;
	long SamplesUnchanged;
	long i,tap,Delay_Length;
	double Path_Ampli; 
	vector<double> fading_pr,fading_pi;
	long max_delay= (long) Path_Delay[NumOfTaps-1];
	int n;
	int NumOfFreq = 8;
	SamplesUnchanged = (long) ceil((float)(SamplesPerFrame/ChangesPerFrame));
	vector<double> OutData_tmp_r,OutData_tmp_i;
	OutData_tmp_i.resize(SamplesPerFrame);OutData_tmp_r.resize(SamplesPerFrame);
	// added in version 2
	if(NumOfTaps>=1)
	{
		fading_pr.resize(SamplesPerFrame);
		fading_pi.resize(SamplesPerFrame);
	}

	//用于暂存数据
	vector<double> Output_Sub_path_pr,Output_Sub_path_pi;
	Output_Sub_path_pi.resize(SamplesPerFrame);
	Output_Sub_path_pr.resize(SamplesPerFrame);

	////clear the fore data
	//for(i=0;i<max_delay;i++)
	//{
	//	fore_data_pr[i] = 0.0;
	//	fore_data_pi[i] = 0.0;
	//}


	//main function
	for(tap=0;tap<NumOfTaps;tap++)
	{
		// get fading weight
		Path_Ampli=Path_Average_Amp[tap];		
		Delay_Length = (long) Path_Delay[tap];

		//初始化输出数据
		int index =0;
		for(i=0;i<Delay_Length;i++)
		{
			/*OutData_pr[i] = fore_data_pr[i];
			OutData_pi[i] = fore_data_pi[i];*/
			OutData_tmp_r[i] = 0.0;
			OutData_tmp_i[i] = 0.0;
		}
		for(i=Delay_Length;i<SamplesPerFrame;i++)
		{
			OutData_tmp_r[i] = InData_pr[index];
			OutData_tmp_i[i] = InData_pi[index++];
		}


		//Generate Fading weight
		Jakes_kernel(Path_Ampli,NumOfFreq,SamplesUnchanged,fd_max,Phase[tap],\
			ChangesPerFrame,SamplesPerFrame,TimeIndex[tap],\
			dt,fading_pr,fading_pi);		

		//// added in version 3
		//if(NumOfTaps>1)
		//{
		//	for(n=0;n<SamplesPerFrame;n++)
		//	{
		//		out_fading_pr[n*NumOfTaps+tap]=fading_pr[n];
		//		out_fading_pi[n*NumOfTaps+tap]=fading_pi[n];				
		//	}			
		//}


		// get the output data of each independent sub-channel
		if(InData_Complex)
			for(i=0;i<SamplesPerFrame;i++)
			{
				Output_Sub_path_pr[i]=OutData_tmp_r[i] * fading_pr[i] \
					-OutData_tmp_i[i] * fading_pi[i]; 
				Output_Sub_path_pi[i]=OutData_tmp_r[i] * fading_pi[i] \
					+OutData_tmp_i[i] * fading_pr[i];
			}
		else
			for(i=0;i<SamplesPerFrame;i++)
			{
				Output_Sub_path_pr[i]=InData_pr[i] * fading_pr[i]; 
				Output_Sub_path_pi[i]=InData_pr[i] * fading_pi[i];
			}



			//generate the output fading data
			//for(i=0;i<SamplesPerFrame-Delay_Length;i++)
			for(i=0;i<SamplesPerFrame;i++)
			{
				// adding each sub path to generate outdata
				//OutData_pr[i+Delay_Length] += Output_Sub_path_pr[i];
				//OutData_pi[i+Delay_Length] += Output_Sub_path_pi[i];
				OutData_pr[i] += Output_Sub_path_pr[i];
				OutData_pi[i] += Output_Sub_path_pi[i];
			}

			////conceive the fore frame data
			////对数据进行反写，保存当前帧数据对下一帧数据的多径延时混叠影响
			//for(i=0;i<Delay_Length;i++)
			//{
			//	fore_data_pr[i] += Output_Sub_path_pr[SamplesPerFrame-Delay_Length+i];
			//	fore_data_pi[i] += Output_Sub_path_pi[SamplesPerFrame-Delay_Length+i];
			//}

	}

}
void CProtocolB::Run(vector<int>src,int data_bytelen)
{
	//参数传递的函数
	//test
	//data_bytelen=500;
	tx_param(BprotocolConfig.EZOB_Encoding);
	PayloadData_size_bytes = data_bytelen;
	//PSDU_size_bytes=PayloadData_size_bytes + FCS_size_bytes + MACHeader_size_bytes;
	PSDU_size_bytes = PayloadData_size_bytes;//暂时没加MAC层
	data_size = 8*PSDU_size_bytes;
	vector<int> Data(data_size,0);
	for(int i=0;i<data_size;i++)
	{		
		Data[i]=src[i];
		//Data[i]=0;
	}
	//preamble bit
	if (preamble_type == shortPreamble)
		S_preamb_length= 72;
	else
		S_preamb_length= 144;
	vector<int> preamble_bit;
	preamble_bit.resize(S_preamb_length,0);
    preamble_bit=Produce_preamb_bit(S_preamb_length);

    //header bit
	int S_header_length = 48;
	vector<int> header_bit;
	header_bit.resize(S_header_length,0);
	header_bit=Produce_header_bit(S_header_length,PSDU_size_bytes);

	//PPDU before scrambler
	int PPDU_length = S_preamb_length+S_header_length+data_size;
	vector<int> PPDU_bit;
	PPDU_bit.resize(PPDU_length,0);

	vector<int> PPDU_scrambled;
	PPDU_scrambled.resize(PPDU_length,0);

	for(int i=0;i<S_preamb_length;i++)
	{
		PPDU_bit[i]=preamble_bit[i];
	}

	for (int i=0;i<S_header_length;i++)
	{
		PPDU_bit[i+S_preamb_length]=header_bit[i];
	};

	for (int i=0;i<data_size;i++)
	{
		PPDU_bit[i+S_preamb_length+S_header_length]= Data[i];
	}

	PPDU_scrambled = scrambler(PPDU_bit);

	//preamble symbol
	S_preamb_length *= 11;
	S_preambpart=new std::complex<double> [S_preamb_length];
	memset(S_preambpart, (0.0,0.0),S_preamb_length);
	preamble_last_symbol = new std::complex<double> [1];
	memset(preamble_last_symbol,(0.0,0.0),1);
	//preamble_last_symbol.real(0.0);
//	preamble_last_symbol.imag(0.0);
	Produce_preamb(S_preambpart,PPDU_scrambled,preamble_last_symbol);


	//header symbol
	if (preamble_type == longPreamble)
		S_header_length = S_header_length*11;
	else
		S_header_length = S_header_length*11/2;
	S_headerpart = new std::complex<double> [S_header_length];
	memset(S_headerpart, (0.0,0.0),S_header_length);

	double theta0;

	if ((preamble_last_symbol->real()==1.0)&&(preamble_last_symbol->imag()==0.0))
	{
		theta0 = 0;
	} 
	else
	{
		theta0=PI;
	}
	 header_last_symbol = new std::complex<double>[1];
	 memset(header_last_symbol,(0.0,0.0),1);
	 header_last_chip = new std::complex<double>[1];
	 memset(header_last_chip,(0.0,0.0),1);
    Produce_header(S_headerpart,PPDU_scrambled,theta0,header_last_symbol,header_last_chip);//传入S_preambpart判断最后一个符号的相位


	//std::complex<double> Q[20000]={0};//用于存储Q路数据
	//ofstream of("data_11b_2m_header.txt");
	//for (int i = 0;i<S_header_length;i++)
	//{
	//	Q[i] = S_headerpart[i];
	//	of<<Q[i]<<endl;
	//}
	//of.close();


	

	double theta1,theta2;
	if ((header_last_symbol->real()==1.0)&&(header_last_symbol->imag()==0.0))
	{
		theta1 = 0;
	} 
	else if((header_last_symbol->real()==0.0)&&(header_last_symbol->imag()==1.0))
	{
		theta1=PI/2;
	}
	else if((header_last_symbol->real()==-1.0)&&(header_last_symbol->imag()==0.0))
	{
		theta1=PI;
	}
	else if((header_last_symbol->real()==0.0)&&(header_last_symbol->imag()==-1.0))
	{
		theta1=PI*3/2;
	}

	if ((header_last_chip->real()==1.0)&&(header_last_chip->imag()==0.0))
	{
		theta2 = 0;
	} 
	else if((header_last_chip->real()==0.0)&&(header_last_chip->imag()==1.0))
	{
		theta2=PI/2;
	}
	else if((header_last_chip->real()==-1.0)&&(header_last_chip->imag()==0.0))
	{
		theta2=PI;
	}
	else if((header_last_chip->real()==0.0)&&(header_last_chip->imag()==-1.0))
	{
		theta2=PI*3/2;
	}


     // PSDU
	//int S_data_length = 2*(data_size+8) ;
	S_data_length = 11*data_size;
	if(S_datapart == NULL)
	S_datapart = new std::complex<double> [S_data_length] ;
	memset(S_datapart, (0.0,0.0),S_data_length);
    Produce_PSDU(S_datapart,PPDU_scrambled,theta1,theta2);


	//std::complex<double> Q[20000]={0};//用于存储Q路数据
	//ofstream of("data_11b_2m_data.txt");
	//for (int i = 0;i<S_data_length;i++)
	//{
	//	Q[i] = S_datapart[i];
	//	of<<Q[i]<<endl;
	//}
	//of.close();

	//判断有多少个没有意义的symbol
	int temp_len = 0;
	for (int i = 0;i < S_data_length;i++)
	{
		if ((S_datapart[i].real() == 0) && (S_datapart[i].imag() == 0))		
		{
			temp_len = i;
			break;
		}	  
		//break;
	}
	
    //PPDU
	if (temp_len==0)
	//if(1>0)
	{
		S_PPDU_length=S_data_length+S_header_length+S_preamb_length;//1Mbps
		S_datapart_f = new std::complex<double>[S_data_length];
		memset(S_datapart_f, (0.0,0.0),S_data_length);
		for (int i = 0;i < S_data_length; i++)
		{
			//S_datapart_f[i].setValue(S_datapart[i].getReal(), S_datapart[i].getImag());
			S_datapart_f[i].real(S_datapart[i].real());
			S_datapart_f[i].imag(S_datapart[i].imag());
		}
		if(S_PPDU == NULL)
			S_PPDU= new std::complex<double> [S_PPDU_length];  
		Produce_PPDU(S_preambpart,S_headerpart,S_datapart_f,S_PPDU,S_preamb_length,S_header_length,S_data_length);
		//if(BprotocolConfig.EZOB_Encoding==DBPSK_1M || BprotocolConfig.EZOB_Encoding==CCK_5_5M || BprotocolConfig.EZOB_Encoding==CCK_11M){
		if(1){
			complex<double> temp(+0.7071,+0.7071);
			//complex<double> temp(+0.5,+0.866);
			for(int i=0;i<S_PPDU_length;i++){
				S_PPDU[i] = S_PPDU[i]*temp;
			}
		}
	}
	else
	{
		S_PPDU_length=temp_len+S_header_length+S_preamb_length;
		S_datapart_f = new std::complex<double>[temp_len];
		memset(S_datapart_f, (0.0,0.0),temp_len);
		for (int i = 0;i < temp_len; i++)
		{
			//S_datapart_f[i].setValue(S_datapart[i].getReal(), S_datapart[i].getImag());
			S_datapart_f[i].real(S_datapart[i].real());
			S_datapart_f[i].imag(S_datapart[i].imag());
		}
		if(S_PPDU == NULL)
			S_PPDU= new std::complex<double> [S_PPDU_length];  
		Produce_PPDU(S_preambpart,S_headerpart,S_datapart_f,S_PPDU,S_preamb_length,S_header_length,temp_len);
		//if(BprotocolConfig.EZOB_Encoding==DBPSK_1M){
		//if(1){
		if(BprotocolConfig.EZOB_Encoding!=PBCC_11M && BprotocolConfig.EZOB_Encoding!=PBCC_5_5M){
			complex<double> temp(+0.7071,+0.7071);
			for(int i=0;i<S_PPDU_length;i++){
				S_PPDU[i] = S_PPDU[i]*temp;
			}
		}else
		{
			complex<double> temp(+0.7071,+0.7071);
			for(int i=0;i<S_header_length+S_preamb_length;i++){
				S_PPDU[i] = S_PPDU[i]*temp;
			}
		}
	}

	vector<double> t;
	double Data_temp_real,Data_temp_imag;
	int i;
	for (i=0; i<S_PPDU_length; i++ )
	{
		t.push_back(i*BprotocolConfig.dt);
	}  

	for (i=0; i<S_PPDU_length; i++ )
	{
		Data_temp_real = cos(2*pi*BprotocolConfig.FrequencyOffset*t[i]);
		Data_temp_imag = sin(2*pi*BprotocolConfig.FrequencyOffset*t[i]);
		S_PPDU[i].real(S_PPDU[i].real()*Data_temp_real - S_PPDU[i].imag()*Data_temp_imag);
		S_PPDU[i].imag(S_PPDU[i].real()*Data_temp_imag + S_PPDU[i].imag()*Data_temp_real);
	}  
	BprotocolConfig.length=S_PPDU_length;
	//信道
	if(BprotocolConfig.add_channel)
	{
		sizeof_Path_Delay = sizeof(Path_Delay) / sizeof(Path_Delay[0]);
		sizeof_Path_Average_Power = sizeof(Path_Average_Power) / sizeof(Path_Average_Power[0]);
		int SamplesPerFrame = S_PPDU_length;
		int ChangesPerFrame = SamplesPerFrame;
		vector<double>  OutData_pr,OutData_pi;
		OutData_pr.resize(S_PPDU_length);OutData_pi.resize(S_PPDU_length);
		double * out_fading_pr =new double[S_PPDU_length];
		double * out_fading_pi =new double[S_PPDU_length];
		double  fading_indx=0.0;
		vector<double>  data_r;
		data_r.resize(S_PPDU_length,0);
		vector<double>  data_i;
		data_i.resize(S_PPDU_length,0);
		int TimeIndex[16] ={0};
		for(int i=0;i<16;i++)
			TimeIndex[i] = i*10;
		for(int i=0;i< S_PPDU_length;i++)
		{
			data_r[i] =S_PPDU[i].real();
			data_i[i] =S_PPDU[i].imag();
		}
		//初始化
		for(int i=0;i<16;i++)
			for(int j=0;j<12;j++)
				RndPhase[i][j] =0.0;
		for(int i=0;i<16;i++)
			Path_Delay[i] =Path_Average_Amp[i] =Path_Average_Power[i] =0;

		channel_initialize_1(RndPhase,Path_Delay,Path_Average_Amp,fore_data_pr,fore_data_pi,\
			&RMS_Delay_Sample,BprotocolConfig.MAX_Delay_Sample,BprotocolConfig.NumOfTaps,Path_Average_Power,\
			sizeof_Path_Delay,sizeof_Path_Average_Power);
		double fd_max = BprotocolConfig.mobilespeed / 3.6 / (3e8) * BprotocolConfig.carrierfreq;
		multipath_channel(data_r,data_i,fd_max,BprotocolConfig.NumOfTaps,SamplesPerFrame,\
			ChangesPerFrame,TimeIndex,BprotocolConfig.dt,RndPhase,Path_Delay,\
			Path_Average_Amp,OutData_pr,OutData_pi,\
			out_fading_pr,out_fading_pi,\
			fore_data_pr,fore_data_pi,&fading_indx);
		for(int i=0;i<S_PPDU_length;i++)
		{
			complex<double> outdata;
			outdata.real(abs(OutData_pr[i])> 10 ? S_PPDU[i].real():OutData_pr[i]);
			outdata.imag(abs(OutData_pi[i])> 10 ?  S_PPDU[i].imag():OutData_pi[i]);
			S_PPDU[i] = outdata;
		}
	}
	
	int over_ratio = BprotocolConfig.oversample_ratio;
	if(over_ratio >1)
	{
		complex<double>* after_oversample = new complex<double>[S_PPDU_length*over_ratio];
		complex<double> zero(0.0,0.0);
		for(int i = 0; i < S_PPDU_length * over_ratio ; i++)
		{
			if( (i % over_ratio) == 0)
				//after_oversample[i] = S_PPDU[ i/4 ];//应该改成i/over_ratio
			    after_oversample[i] = S_PPDU[ i/over_ratio ];
			else
				after_oversample[i] = zero ;
		}
		switch(BprotocolConfig.filter_para.filtertype)
		{
		case lpfilter:
			{
				vector<double> filter_coef = lowpass_filter(BprotocolConfig.filter_para.lppara.length,BprotocolConfig.filter_para.lppara.wn);
				my_conv(after_oversample,filter_coef,S_PPDU_length * over_ratio);
				S_PPDU = after_oversample;
				break;
			}
		case gaussfilter:
			{
				vector<double> filter_coef = gauss_filter(BprotocolConfig.filter_para.gausspara.length,BprotocolConfig.filter_para.gausspara.BT);
				my_conv(after_oversample,filter_coef,S_PPDU_length * over_ratio);
				S_PPDU = after_oversample;
				break;
			}
		case cosfilter:
			{
				vector<double> filter_coef = root_raised_cosine(BprotocolConfig.filter_para.cosinepara.alpha,BprotocolConfig.filter_para.cosinepara.length);
				my_conv(after_oversample,filter_coef,S_PPDU_length * over_ratio);
				S_PPDU = after_oversample;
				break;
			}
		case userdefined:
			{
				my_conv(after_oversample,BprotocolConfig.filter_user,S_PPDU_length * over_ratio);
				S_PPDU = after_oversample;
				break;
			}
		}

	}
	//std::complex<double> Q[20000]={0};//用于存储Q路数据
	//ofstream of("data_11b_2m_ppdu.txt");
	//for (int i = 0;i<S_PPDU_length;i++)
	//{
	//	Q[i] = S_PPDU[i];
	//	of<<Q[i]<<endl;
	//}
	//of.close();
	//Clear();
	int sig_len = S_PPDU_length * over_ratio;
	int sig_len_idle = sig_len;

	
	//加正交角度调整，IQ平衡增益
	double I_Q_max=0.0,I_data,Q_data=0.0;
	//double *I_gfsk=new double[sig_len];
	//double *Q_gfsk=new double[sig_len];
	double real_temp = 0;
	double imag_temp = 0;
	double IQ_gain = BprotocolConfig.IQ_gain;//注意与自己的对应
	double qAngleAD = BprotocolConfig.quan_angle_adjust;
	if(BprotocolConfig.add_channel == false)//不加信道的时候如果改正交角度调整或IQ平衡增益就会做如下公式
	{
		for (int i = 0; i < sig_len_idle; ++i)
		{
			real_temp = S_PPDU[i].real() - pow(10,(IQ_gain/10))*sin(qAngleAD)*S_PPDU[i].imag();
			imag_temp = pow(10,(IQ_gain/10))*cos(qAngleAD)*S_PPDU[i].imag();
			S_PPDU[i].real(real_temp);
			S_PPDU[i].imag(imag_temp);
		}
	}
	
}
vector<double> CProtocolB::lowpass_filter(int length,double Wn)
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
vector<double> CProtocolB::gauss_filter(int length,double BT)
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
	//高斯win=(1/(alpha*sqrt(pi)*tao)).*exp(-(x/(alpha*tao)).^2);
	for(int i=0;i<length;i++)
		win[i]  =(1/(alpha*sqrt(PI)*tao))*exp(-1*pow(filter_temp[i]/(alpha*tao),2.0));
	for(int i=0;i<length;i++)
		if(win[i]>win_max)
			win_max =win[i];
	for(int i=0;i<length;i++)
		win[i]/=win_max;
	//加窗
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
void CProtocolB::my_conv( complex<double> * Data_in,vector<double> &filter_coef,int Data_in_len){
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
vector<double> CProtocolB::root_raised_cosine(double alpha,int ntaps)
{
	double gain =1.0;
	ntaps |= 1;	// ensure that ntaps is odd
	double spb = BprotocolConfig.oversample_ratio; // samples per bit/symbol过采样率几倍就是几
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
void CProtocolB::Clear()
{	
	delete []S_preambpart;
	delete []S_headerpart;
	delete []S_datapart;
	delete []S_datapart_f;
	//delete []S_PPDU;//清除内存
//	delete []S_FFTATUOpower;
//	delete []S_FFTspectrum;

}


//
//BEGIN_MESSAGE_MAP(CProtocolB, CStatic)
//	//{{AFX_MSG_MAP(CProtocolA)
//	//}}AFX_MSG_MAP
//END_MESSAGE_MAP()