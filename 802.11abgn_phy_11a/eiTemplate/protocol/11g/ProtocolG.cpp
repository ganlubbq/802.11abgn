// CProtocolG.cpp : implementation file
//
#include "stdafx.h"
#include "ProtocolG.h"
#include <MATH.H>
//#include<complex>
//#include "stdafx.h"

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#undef THIS_FILE
//static char THIS_FILE[] = __FILE__;
//#endif


tx_11g_param::tx_11g_param()
{
	//测试信号段
	//Test_data[0] =0x04;Test_data[1]= 0x02;Test_data[2]= 0x00;Test_data[3]= 0x2e;Test_data[4]= 0x00;
	//Test_data[5] =0x60;Test_data[6]= 0x08;Test_data[7]= 0xcd;Test_data[8]= 0x37;Test_data[9]= 0xa6;
	//Test_data[10]=0x00;Test_data[11]=0x20;Test_data[12]=0xd6;Test_data[13]=0x01;Test_data[14]=0x3c;
	//Test_data[15]=0xf1;Test_data[16]=0x00;Test_data[17]=0x60;Test_data[18]=0x08;Test_data[19]=0xad;
	//Test_data[20]=0x3b;Test_data[21]=0xaf;Test_data[22]=0x00;Test_data[23]=0x00;Test_data[24]=0x4a;
	//Test_data[25]=0x6f;Test_data[26]=0x79;Test_data[27]=0x2c;Test_data[28]=0x20;Test_data[29]=0x62;
	//Test_data[30]=0x72;Test_data[31]=0x69;Test_data[32]=0x67;Test_data[33]=0x68;Test_data[34]=0x74;
	//Test_data[35]=0x20;Test_data[36]=0x73;Test_data[37]=0x70;Test_data[38]=0x61;Test_data[39]=0x72;
	//Test_data[40]=0x6b;Test_data[41]=0x20;Test_data[42]=0x6f;Test_data[43]=0x66;Test_data[44]=0x20;
	//Test_data[45]=0x64;Test_data[46]=0x69;Test_data[47]=0x76;Test_data[48]=0x69;Test_data[49]=0x6e;
	//Test_data[50]=0x69;Test_data[51]=0x74;Test_data[52]=0x79;Test_data[53]=0x2c;Test_data[54]=0x0a;
	//Test_data[55]=0x44;Test_data[56]=0x61;Test_data[57]=0x75;Test_data[58]=0x67;Test_data[59]=0x68;
	//Test_data[60]=0x74;Test_data[61]=0x65;Test_data[62]=0x72;Test_data[63]=0x20;Test_data[64]=0x6f;
	//Test_data[65]=0x66;Test_data[66]=0x20;Test_data[67]=0x45;Test_data[68]=0x6c;Test_data[69]=0x79;
	//Test_data[70]=0x73;Test_data[71]=0x69;Test_data[72]=0x75;Test_data[73]=0x6d;Test_data[74]=0x2c;
	//Test_data[75]=0x0a;Test_data[76]=0x46;Test_data[77]=0x69;Test_data[78]=0x72;Test_data[79]=0x65;
	//Test_data[80]=0x2d;Test_data[81]=0x69;Test_data[82]=0x6e;Test_data[83]=0x73;Test_data[84]=0x69;
	//Test_data[85]=0x72;Test_data[86]=0x65;Test_data[87]=0x64;Test_data[88]=0x20;Test_data[89]=0x77;
	//Test_data[90]=0x65;Test_data[91]=0x20;Test_data[92]=0x74;Test_data[93]=0x72;Test_data[94]=0x65;
	//Test_data[95]=0x61;Test_data[96]=0xda;Test_data[97]=0x57;Test_data[98]=0x99;Test_data[99]=0xed;

	Test_data[0] =0xff;Test_data[1]= 0xff;Test_data[2]= 0xff;Test_data[3]= 0xff;Test_data[4]= 0xff;
	Test_data[5] =0xff;Test_data[6]= 0xff;Test_data[7]= 0xff;Test_data[8]= 0xff;Test_data[9]= 0xff;

	//BPSK_D[2]
	BPSK_D[0]=std::complex<double>(-1.0, 0.0);         BPSK_D[1]=std::complex<double>(1.0, 0.0);
	//QPSK_D[4]
	QPSK_D[0]=std::complex<double>(-0.7071, -0.7071);  QPSK_D[1]=std::complex<double>(-0.7071, 0.7071);
	QPSK_D[2]=std::complex<double>(+0.7071, -0.7071);  QPSK_D[3]=std::complex<double>(+0.7071, 0.7071);
	//QAM16_D[16]
	QAM16_D[0]=std::complex<double>(-0.9487, -0.9487); QAM16_D[1]=std::complex<double>(-0.9487, -0.3162);
	QAM16_D[2]=std::complex<double>(-0.9487, 0.9487);  QAM16_D[3]=std::complex<double>(-0.9487, 0.3162);
	QAM16_D[4]=std::complex<double>(-0.3162, -0.9487); QAM16_D[5]=std::complex<double>(-0.3162, -0.3162);
	QAM16_D[6]=std::complex<double>(-0.3162, 0.9487);  QAM16_D[7]=std::complex<double>(-0.3162, 0.3162);
	QAM16_D[8]=std::complex<double>(0.9487, -0.9487);  QAM16_D[9]=std::complex<double>(0.9487, -0.3162);
	QAM16_D[10]=std::complex<double>(0.9487, 0.9487);  QAM16_D[11]=std::complex<double>(0.9487, 0.3162);
	QAM16_D[12]=std::complex<double>(0.3162, -0.9487); QAM16_D[13]=std::complex<double>(0.3162, -0.3162);
	QAM16_D[14]=std::complex<double>(0.3162, 0.9487);  QAM16_D[15]=std::complex<double>(0.3162, 0.3162);
	//QAM64_D[64]
	QAM64_D[0]=std::complex<double>(-1.0801, -1.0801); QAM64_D[1]=std::complex<double>(-1.0801, -0.7715);
	QAM64_D[2]=std::complex<double>(-1.0801, -0.1543); QAM64_D[3]=std::complex<double>(-1.0801, -0.4629);
	QAM64_D[4]=std::complex<double>(-1.0801, 1.0801);  QAM64_D[5]=std::complex<double>(-1.0801, 0.7715);
	QAM64_D[6]=std::complex<double>(-1.0801, 0.1543);  QAM64_D[7]=std::complex<double>(-1.0801, 0.4629);
	QAM64_D[8]=std::complex<double>(-0.7715, -1.0801); QAM64_D[9]=std::complex<double>(-0.7715, -0.7715);
	QAM64_D[10]=std::complex<double>(-0.7715, -0.1543);QAM64_D[11]=std::complex<double>(-0.7715, -0.4629);
	QAM64_D[12]=std::complex<double>(-0.7715, 1.0801); QAM64_D[13]=std::complex<double>(-0.7715, 0.7715);
	QAM64_D[14]=std::complex<double>(-0.7715, 0.1543); QAM64_D[15]=std::complex<double>(-0.7715, 0.4629);
	QAM64_D[16]=std::complex<double>(-0.1543, -1.0801);QAM64_D[17]=std::complex<double>(-0.1543, -0.7715);
	QAM64_D[18]=std::complex<double>(-0.1543, -0.1543);QAM64_D[19]=std::complex<double>(-0.1543, -0.4629);
	QAM64_D[20]=std::complex<double>(-0.1543, 1.0801); QAM64_D[21]=std::complex<double>(-0.1543, 0.7715);
	QAM64_D[22]=std::complex<double>(-0.1543, 0.1543); QAM64_D[23]=std::complex<double>(-0.1543, 0.4629);
	QAM64_D[24]=std::complex<double>(-0.4629, -1.0801);QAM64_D[25]=std::complex<double>(-0.4629, -0.7715);
	QAM64_D[26]=std::complex<double>(-0.4629, -0.1543);QAM64_D[27]=std::complex<double>(-0.4629, -0.4629);
	QAM64_D[28]=std::complex<double>(-0.4629, 1.0801); QAM64_D[29]=std::complex<double>(-0.4629, 0.7715);
	QAM64_D[30]=std::complex<double>(-0.4629, 0.1543); QAM64_D[31]=std::complex<double>(-0.4629, 0.4629);
	QAM64_D[32]=std::complex<double>(1.0801, -1.0801); QAM64_D[33]=std::complex<double>(1.0801, -0.7715);
	QAM64_D[34]=std::complex<double>(1.0801, -0.1543); QAM64_D[35]=std::complex<double>(1.0801, -0.4629);
	QAM64_D[36]=std::complex<double>(1.0801, 1.0801);  QAM64_D[37]=std::complex<double>(1.0801, 0.7715);
	QAM64_D[38]=std::complex<double>(1.0801, 0.1543);  QAM64_D[39]=std::complex<double>(1.0801, 0.4629);
	QAM64_D[40]=std::complex<double>(0.7715, -1.0801); QAM64_D[41]=std::complex<double>(0.7715, -0.7715);
	QAM64_D[42]=std::complex<double>(0.7715, -0.1543); QAM64_D[43]=std::complex<double>(0.7715, -0.4629);
	QAM64_D[44]=std::complex<double>(0.7715, 1.0801);  QAM64_D[45]=std::complex<double>(0.7715, 0.7715);
	QAM64_D[46]=std::complex<double>(0.7715, 0.1543);  QAM64_D[47]=std::complex<double>(0.7715, 0.4629);
	QAM64_D[48]=std::complex<double>(0.1543, -1.0801); QAM64_D[49]=std::complex<double>(0.1543, -0.7715);
	QAM64_D[50]=std::complex<double>(0.1543, -0.1543); QAM64_D[51]=std::complex<double>(0.1543, -0.4629);
	QAM64_D[52]=std::complex<double>(0.1543, 1.0801);  QAM64_D[53]=std::complex<double>(0.1543, 0.7715);
	QAM64_D[54]=std::complex<double>(0.1543, 0.1543);  QAM64_D[55]=std::complex<double>(0.1543, 0.4629);
	QAM64_D[56]=std::complex<double>(0.4629, -1.0801); QAM64_D[57]=std::complex<double>(0.4629, -0.7715);
	QAM64_D[58]=std::complex<double>(0.4629, -0.1543); QAM64_D[59]=std::complex<double>(0.4629, -0.4629);
	QAM64_D[60]=std::complex<double>(0.4629, 1.0801);  QAM64_D[61]=std::complex<double>(0.4629, 0.7715);
	QAM64_D[62]=std::complex<double>(0.4629, 0.1543);  QAM64_D[63]=std::complex<double>(0.4629, 0.4629);
	//短训练序列
	Seq_P53[0]= std::complex<double>(0.0, 0.0);  Seq_P53[1]= std::complex<double>(0.0, 0.0);  Seq_P53[2]= std::complex<double>(0.0, 0.0);
	Seq_P53[3]= std::complex<double>(0.0, 0.0);  Seq_P53[4]= std::complex<double>(0.0, 0.0);  Seq_P53[5]= std::complex<double>(1.0, 0.0);
	Seq_P53[6]= std::complex<double>(0.0, 0.0);  Seq_P53[7]= std::complex<double>(0.0, 0.0);  Seq_P53[8]= std::complex<double>(0.0, 0.0);
	Seq_P53[9]= std::complex<double>(0.0, 0.0);  Seq_P53[10]=std::complex<double>(0.0, 0.0);  Seq_P53[11]=std::complex<double>(0.0, 0.0);
	Seq_P53[12]=std::complex<double>(0.0, 0.0);  Seq_P53[13]=std::complex<double>(0.0, 0.0);  Seq_P53[14]=std::complex<double>(0.0, 0.0);
	Seq_P53[15]=std::complex<double>(0.0, 0.0);  Seq_P53[16]=std::complex<double>(0.0, 0.0);  Seq_P53[17]=std::complex<double>(0.0, 0.0);
	Seq_P53[18]=std::complex<double>(0.0, 0.0);  Seq_P53[19]=std::complex<double>(1.0, 0.0);  Seq_P53[20]=std::complex<double>(0.0, 0.0);
	Seq_P53[21]=std::complex<double>(0.0, 0.0);  Seq_P53[22]=std::complex<double>(0.0, 0.0);  Seq_P53[23]=std::complex<double>(0.0, 0.0);
	Seq_P53[24]=std::complex<double>(0.0, 0.0);  Seq_P53[25]=std::complex<double>(0.0, 0.0);  Seq_P53[26]=std::complex<double>(0.0, 0.0);
	Seq_P53[27]=std::complex<double>(0.0, 0.0);  Seq_P53[28]=std::complex<double>(0.0, 0.0);  Seq_P53[29]=std::complex<double>(0.0, 0.0);
	Seq_P53[30]=std::complex<double>(0.0, 0.0);  Seq_P53[31]=std::complex<double>(0.0, 0.0);  Seq_P53[32]=std::complex<double>(0.0, 0.0);
	Seq_P53[33]=std::complex<double>(1.0, 0.0);  Seq_P53[34]=std::complex<double>(0.0, 0.0);  Seq_P53[35]=std::complex<double>(0.0, 0.0);
	Seq_P53[36]=std::complex<double>(0.0, 0.0);  Seq_P53[37]=std::complex<double>(0.0, 0.0);  Seq_P53[38]=std::complex<double>(0.0, 0.0);
	Seq_P53[39]=std::complex<double>(0.0, 0.0);  Seq_P53[40]=std::complex<double>(0.0, 0.0);  Seq_P53[41]=std::complex<double>(0.0, 0.0);
	Seq_P53[42]=std::complex<double>(1.0, 0.0);  Seq_P53[43]=std::complex<double>(0.0, 0.0);  Seq_P53[44]=std::complex<double>(0.0, 0.0);
	Seq_P53[45]=std::complex<double>(0.0, 0.0);  Seq_P53[46]=std::complex<double>(0.0, 0.0);  Seq_P53[47]=std::complex<double>(-1.0, 0.0);
	Seq_P53[48]=std::complex<double>(0.0, 0.0);  Seq_P53[49]=std::complex<double>(0.0, 0.0);  Seq_P53[50]=std::complex<double>(0.0, 0.0);
	Seq_P53[51]=std::complex<double>(0.0, 0.0);  Seq_P53[52]=std::complex<double>(0.0, 0.0);  
	//长训练序列
	Seq_p126[0]=  std::complex<double>(1.0, 0.0);   Seq_p126[1]=  std::complex<double>(1.0, 0.0);   Seq_p126[2]=  std::complex<double>(1.0, 0.0);   Seq_p126[3]=  std::complex<double>(1.0, 0.0);
	Seq_p126[4]=  std::complex<double>(-1.0, 0.0);  Seq_p126[5]=  std::complex<double>(-1.0, 0.0);  Seq_p126[6]=  std::complex<double>(-1.0, 0.0);  Seq_p126[7]=  std::complex<double>(1.0, 0.0);
	Seq_p126[8]=  std::complex<double>(-1.0, 0.0);  Seq_p126[9]=  std::complex<double>(-1.0, 0.0);  Seq_p126[10]= std::complex<double>(-1.0, 0.0);  Seq_p126[11]= std::complex<double>(-1.0, 0.0);
	Seq_p126[12]= std::complex<double>(1.0, 0.0);   Seq_p126[13]= std::complex<double>(1.0, 0.0);   Seq_p126[14]= std::complex<double>(-1.0, 0.0);  Seq_p126[15]= std::complex<double>(1.0, 0.0);

	Seq_p126[16]= std::complex<double>(-1.0, 0.0);  Seq_p126[17]= std::complex<double>(-1.0, 0.0);  Seq_p126[18]= std::complex<double>(1.0, 0.0);   Seq_p126[19]= std::complex<double>(1.0, 0.0);
	Seq_p126[20]= std::complex<double>(-1.0, 0.0);  Seq_p126[21]= std::complex<double>(1.0, 0.0);   Seq_p126[22]= std::complex<double>(1.0, 0.0);   Seq_p126[23]= std::complex<double>(-1.0, 0.0);
	Seq_p126[24]= std::complex<double>(1.0, 0.0);   Seq_p126[25]= std::complex<double>(1.0, 0.0);   Seq_p126[26]= std::complex<double>(1.0, 0.0);   Seq_p126[27]= std::complex<double>(1.0, 0.0);
	Seq_p126[28]= std::complex<double>(1.0, 0.0);   Seq_p126[29]= std::complex<double>(1.0, 0.0);   Seq_p126[30]= std::complex<double>(-1.0, 0.0);  Seq_p126[31]= std::complex<double>(1.0, 0.0);

	Seq_p126[32]= std::complex<double>(1.0, 0.0);   Seq_p126[33]= std::complex<double>(1.0, 0.0);   Seq_p126[34]= std::complex<double>(-1.0, 0.0);  Seq_p126[35]= std::complex<double>(1.0, 0.0);
	Seq_p126[36]= std::complex<double>(1.0, 0.0);   Seq_p126[37]= std::complex<double>(-1.0, 0.0);  Seq_p126[38]= std::complex<double>(-1.0, 0.0);  Seq_p126[39]= std::complex<double>(1.0, 0.0);
	Seq_p126[40]= std::complex<double>(1.0, 0.0);   Seq_p126[41]= std::complex<double>(1.0, 0.0);   Seq_p126[42]= std::complex<double>(-1.0, 0.0);  Seq_p126[43]= std::complex<double>(1.0, 0.0);
	Seq_p126[44]= std::complex<double>(-1.0, 0.0);  Seq_p126[45]= std::complex<double>(-1.0, 0.0);  Seq_p126[46]= std::complex<double>(-1.0, 0.0);  Seq_p126[47]= std::complex<double>(1.0, 0.0);

	Seq_p126[48]= std::complex<double>(-1.0, 0.0);  Seq_p126[49]= std::complex<double>(1.0, 0.0);   Seq_p126[50]= std::complex<double>(-1.0, 0.0);  Seq_p126[51]= std::complex<double>(-1.0, 0.0);
	Seq_p126[52]= std::complex<double>(1.0, 0.0);   Seq_p126[53]= std::complex<double>(-1.0, 0.0);  Seq_p126[54]= std::complex<double>(-1.0, 0.0);  Seq_p126[55]= std::complex<double>(1.0, 0.0);
	Seq_p126[56]= std::complex<double>(1.0, 0.0);   Seq_p126[57]= std::complex<double>(1.0, 0.0);   Seq_p126[58]= std::complex<double>(1.0, 0.0);   Seq_p126[59]= std::complex<double>(1.0, 0.0);
	Seq_p126[60]= std::complex<double>(-1.0, 0.0);  Seq_p126[64]= std::complex<double>(-1.0, 0.0);  Seq_p126[62]= std::complex<double>(1.0, 0.0);   Seq_p126[63]= std::complex<double>(1.0, 0.0);

	Seq_p126[64]= std::complex<double>(-1.0, 0.0);  Seq_p126[65]= std::complex<double>(1.0, 0.0);   Seq_p126[66]= std::complex<double>(1.0, 0.0);   Seq_p126[67]= std::complex<double>(-1.0, 0.0);
	Seq_p126[68]= std::complex<double>(1.0, 0.0);   Seq_p126[69]= std::complex<double>(-1.0, 0.0);  Seq_p126[70]= std::complex<double>(1.0, 0.0);   Seq_p126[71]= std::complex<double>(1.0, 0.0);
	Seq_p126[72]= std::complex<double>(-1.0, 0.0);  Seq_p126[73]= std::complex<double>(-1.0, 0.0);  Seq_p126[74]= std::complex<double>(-1.0, 0.0);  Seq_p126[75]= std::complex<double>(1.0, 0.0);
	Seq_p126[76]= std::complex<double>(1.0, 0.0);   Seq_p126[77]= std::complex<double>(-1.0, 0.0);  Seq_p126[78]= std::complex<double>(-1.0, 0.0);  Seq_p126[79]= std::complex<double>(-1.0, 0.0);

	Seq_p126[80]= std::complex<double>(-1.0, 0.0);  Seq_p126[81]= std::complex<double>(1.0, 0.0);   Seq_p126[82]= std::complex<double>(-1.0, 0.0);  Seq_p126[83]= std::complex<double>(-1.0, 0.0);
	Seq_p126[84]= std::complex<double>(1.0, 0.0);   Seq_p126[85]= std::complex<double>(-1.0, 0.0);  Seq_p126[86]= std::complex<double>(1.0, 0.0);   Seq_p126[87]= std::complex<double>(1.0, 0.0);
	Seq_p126[88]= std::complex<double>(1.0, 0.0);   Seq_p126[89]= std::complex<double>(1.0, 0.0);   Seq_p126[90]= std::complex<double>(-1.0, 0.0);  Seq_p126[91]= std::complex<double>(1.0, 0.0);
	Seq_p126[92]= std::complex<double>(-1.0, 0.0);  Seq_p126[93]= std::complex<double>(1.0, 0.0);   Seq_p126[94]= std::complex<double>(-1.0, 0.0);  Seq_p126[95]= std::complex<double>(1.0, 0.0);

	Seq_p126[96]=  std::complex<double>(-1.0, 0.0); Seq_p126[97]= std::complex<double>(-1.0, 0.0);  Seq_p126[98]= std::complex<double>(-1.0, 0.0);  Seq_p126[99]= std::complex<double>(-1.0, 0.0);
	Seq_p126[100]= std::complex<double>(-1.0, 0.0); Seq_p126[101]= std::complex<double>(1.0, 0.0);  Seq_p126[102]= std::complex<double>(-1.0, 0.0); Seq_p126[103]= std::complex<double>(1.0, 0.0);
	Seq_p126[104]= std::complex<double>(1.0, 0.0);  Seq_p126[105]= std::complex<double>(-1.0, 0.0); Seq_p126[106]= std::complex<double>(1.0, 0.0);  Seq_p126[107]= std::complex<double>(-1.0, 0.0);
	Seq_p126[108]= std::complex<double>(1.0, 0.0);  Seq_p126[109]= std::complex<double>(1.0, 0.0);  Seq_p126[110]= std::complex<double>(1.0, 0.0);  Seq_p126[111]= std::complex<double>(-1.0, 0.0);

	Seq_p126[112]= std::complex<double>(-1.0, 0.0);   Seq_p126[113]= std::complex<double>(1.0, 0.0);   Seq_p126[114]= std::complex<double>(-1.0, 0.0); Seq_p126[115]= std::complex<double>(-1.0, 0.0);
	Seq_p126[116]= std::complex<double>(-1.0, 0.0);   Seq_p126[117]= std::complex<double>(1.0, 0.0);   Seq_p126[118]= std::complex<double>(1.0, 0.0);  Seq_p126[119]= std::complex<double>(1.0, 0.0);
	Seq_p126[120]= std::complex<double>(-1.0, 0.0);   Seq_p126[121]= std::complex<double>(-1.0, 0.0);  Seq_p126[122]= std::complex<double>(-1.0, 0.0);Seq_p126[123]= std::complex<double>(-1.0, 0.0);
	Seq_p126[124]= std::complex<double>(-1.0, 0.0);   Seq_p126[125]= std::complex<double>(-1.0, 0.0);  Seq_p126[126]= std::complex<double>(-1.0, 0.0);  


	S_preambpart=NULL;
	S_singalpart=NULL;
	S_headerpart=NULL;
	S_datapart=NULL;
	//S_datapart_f=NULL;
	S_PPDU=NULL;
	S_preamb_length=0;
	S_singal_length=0;
	S_header_length=0;
	S_data_length=0;
	S_PPDU_length=0;

	S_FFTATUOpower=NULL;
	S_FFTspectrum=NULL;

	//11a模式的参数
	//Encoding  e = BPSK_1_2;


	//基本参数
	Sample_Rate = 20;
	T_tr = 0.1;
	scramble_state=0x5d;
	index_q=0;	

	//ofdm 参数
	//BPSK_1_2
	n_bpsc = 1;
	n_cbps = 48;
	n_dbps = 24;
	n_rate=6;
	sample_rate=Sample_Rate;
	rate_field = 0x0D; // 0b00001101

	//11b模式参数
	spread11[0]=1;spread11[1]=-1;spread11[2]=1;spread11[3]=1;spread11[4]=-1;
	spread11[5]=1;spread11[6]=1;spread11[7]=1;spread11[8]=-1;spread11[9]=-1;spread11[10]=-1;
	spreading_Rate = 11;
	sample_perchip = 8;
	SFD_size = 16;	
	signal_size = 8;
	service_size = 8;
	length_size = 16;
	CRC_size = 16;
	//PSDU parameter size
	FCS_size_bytes = 4;
	MACHeader_size_bytes = 30;

//	11b mod parameter; 需要写到tx_param_gb里

	//速率可选 _1Mbps,_2Mbps,_55Mbps,_11Mbps, _6Mbps, _9Mbps,_12Mbps,_18Mbps,_24Mbps,_36Mbps,_48Mbps,_54Mbps,
	//data_rate =  _6Mbps;!!!!!!!!!

	//preamble类型可选  shortPreamble，longPreamble,OFDMPreamble
//	preamble_type = OFDMPreamble;
	
	//调制方式 DBPSK_1Mbps，DQPSK_2Mbps，CCK55_55Mbps，PBCC55_55Mbps，CCK11_11Mpbs，PBCC11_11Mbps,
	//BPSK_1_2  = 8,  //6M
	//BPSK_3_4  = 9,  //9M
	//	QPSK_1_2  = 10, //12M
	//	QPSK_3_4  = 11, //18M
	//	QAM16_1_2 = 12, //24M
	//	QAM16_3_4 = 13, //36M
	//	QAM64_2_3 = 14, //48M
	//	QAM64_3_4 = 15  //54M
	//modulation_type = BPSK_1_2_; !!!!!!!!!

	//扰码 ON,OFF,Preamble_only
	//scrambler_state = ON;!!!!!!!!

	//数据字节数
	PayloadData_size_bytes = 10;
	//PSDU_size_bytes=PayloadData_size_bytes + FCS_size_bytes + MACHeader_size_bytes;
	PSDU_size_bytes=PayloadData_size_bytes;
	data_size = 8*PSDU_size_bytes;

	//生成数据序列
	srand(time(NULL));
	for(int i=0;i<data_size;i++)
	{	
		Data.push_back(rand()%2);	
	}

	 length=0;
	 bin_length[16]=NULL;

	 /*if (preamble_type == longPreamble)
	 {
	 sync.resize(128,1);
	 sync_size=128;
	 preamble.resize(144,0);
	 }

	 else
	 {
	 sync.resize(56,0);
	 sync_size=56;
	 preamble.resize(72,0);
	 }*/

	SFD.resize(16,0);
	 //signal.resize(8,0);
	 signal = 0x00;
	// service.resize(8,0);	
	 service = 0x20;
	// crc.resize(16,0);
	 header.resize(48,0);                                                                                                     
	 msg.resize(32,0);
	 CRC_bits.resize(16,0);	
}

void tx_11g_param::ofdm_param(Encoding e)
{
	encoding = e;
	switch(e) 
	{
	case BPSK_1_2:
		n_bpsc = 1;
		n_cbps = 48;
		n_dbps = 24;
		n_rate=6;
		sample_rate=Sample_Rate;
		rate_field = 0x0D; // 0b00001101
		break;
		
	case BPSK_3_4:
		n_bpsc = 1;
		n_cbps = 48;
		n_dbps = 36;
		n_rate=9;
		sample_rate=Sample_Rate;
		rate_field = 0x0F; // 0b00001111
		break;
		
	case QPSK_1_2:
		n_bpsc = 2;
		n_cbps = 96;
		n_dbps = 48;
		n_rate=12;
		sample_rate=Sample_Rate;
		rate_field = 0x05; // 0b00000101
		break;
		
	case QPSK_3_4:
		n_bpsc = 2;
		n_cbps = 96;
		n_dbps = 72;
		n_rate=18;
		sample_rate=Sample_Rate;
		rate_field = 0x07; // 0b00000111
		break;
		
	case QAM16_1_2:
		n_bpsc = 4;
		n_cbps = 192;
		n_dbps = 96;
		n_rate=24;
		sample_rate=Sample_Rate;
		rate_field = 0x09; // 0b00001001
		break;
		
	case QAM16_3_4:
		n_bpsc = 4;
		n_cbps = 192;
		n_dbps = 144;
		n_rate=36;
		sample_rate=Sample_Rate;
		rate_field = 0x0B; // 0b00001011
		break;
		
	case QAM64_2_3:
		n_bpsc = 6;
		n_cbps = 288;
		n_dbps = 192;
		n_rate=48;
		sample_rate=Sample_Rate;
		rate_field = 0x01; // 0b00000001
		break;
		
	case QAM64_3_4:
		n_bpsc = 6;
		n_cbps = 288;
		n_dbps = 216;
		n_rate=54;
		sample_rate=Sample_Rate;
		rate_field = 0x03; // 0b00000011
		break;
		
	default:
		//assert(false);
		break;
	}
}

tx_11g_param::~tx_11g_param()
{
	//delete []data;
}

void tx_11g_param::tx_param(int psdu_length) 
{
	
	psdu_size = psdu_length;//PSDU字节数
	// number of symbols (17-11)
	n_sym = (int) ceil((16 + 8 * psdu_size + 6) / (double)n_dbps);//ofdm 数据 符号数 也即是调制之前的数据分组数 为了凑成ofdm数据符号的整数倍，向上取整
	// number of bits of the data field (17-12)
	n_data = n_sym * n_dbps;  // 根据向上取整的符号数，算出正真的数据比特数，可能需要填充比特
	// number of padding bits (17-13)
	n_pad = n_data - (16 + 8 * psdu_size + 6); //算出填充比特的数量
	n_encoded_bits = n_sym * n_cbps;  //编码后的总比特数，ofdm符号数*每个编码后ofdm符号所含比特数
}

void tx_11g_param::ifft(std::complex<double> f[])
{
	int i,j,k,m,n,l,r,M;  
	int la,lb,lc;  
	std::complex<double> t;   

	/*----计算分解的级数M=log2(N)----*/  
	for(i=FFT_N,M=1;(i=i/2)!=1;M++);       

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
			for(n=l-1;n<FFT_N-1;n=n+la) //遍历每个分组，分组总数为N/la    
			{     
				lc=n+lb;  //n,lc分别代表一个碟形单元的上、下节点编号          
				t=f[lc]+f[n];     
				f[lc]=(f[n]-f[lc])*std::complex<double>(cos(2.0*pi*r/FFT_N),sin(2.0*pi*r/FFT_N));    
				f[n]=t;     
			}    
		}   
	}
	/*----按照倒位序重新排列变换后信号----*/
	for (i=1,j=FFT_N/2;i<=FFT_N-2;i++)
	{
		if (i<j)
		{
			t=f[j];
			f[j]=f[i];
			f[i]=t;
		}
		k=FFT_N/2;

		while (k<=j)
		{
			j=j-k;
			k=k/2;
		}
		j=j+k;
	}

	/*----将信号乘以1/N----*/   
	for(i=0;i<FFT_N;i++) f[i]=f[i]/std::complex<double>(FFT_N,0.0);  
}


std::complex<double> tx_11g_param::EE(std::complex<double> a,std::complex<double> b)
{
	std::complex<double> c;
	c.real(a.real()*b.real()-a.imag()*b.imag());
	c.imag(a.real()*b.imag()+a.imag()*b.real());
	return(c);
}

void tx_11g_param::FFT(std::complex<double> xin[])
{
	int f,m,nv2,nm1,i,k,l,j=0;
	std::complex<double> u,w,t;
	nv2=FFT_N/2;                  //变址运算，即把自然顺序变成倒位序，采用雷德算法
	nm1=FFT_N-1;  
	for(i=0;i<nm1;i++)        
	{
		if(i<j)                    //如果i<j,即进行变址
		{
			t=xin[j];           
			xin[j]=xin[i];
			xin[i]=t;
		}
		k=nv2;                    //求j的下一个倒位序
		while(k<=j)               //如果k<=j,表示j的最高位为1   
		{           
			j=j-k;                 //把最高位变成0
			k=k/2;                 //k/2，比较次高位，依次类推，逐个比较，直到某个位为0
		}
		j=j+k;                   //把0改为1
	}

	{
		int le,lei,ip;                            //FFT运算核，使用蝶形运算完成FFT运算
		f=FFT_N;
		for(l=1;(f=f/2)!=1;l++)                  //计算l的值，即计算蝶形级数
			;
		for(m=1;m<=l;m++)                         // 控制蝶形结级数
		{                                        //m表示第m级蝶形，l为蝶形级总数l=log（2）N
			le=2<<(m-1);                            //le蝶形结距离，即第m级蝶形的蝶形结相距le点
			lei=le/2;                               //同一蝶形结中参加运算的两点的距离
			u.real(1.0);                             //u为蝶形结运算系数，初始值为1
			u.imag(0.0);
			w.real(cos(pi/lei));                     //w为系数商，即当前系数与前一个系数的商
			w.imag(-sin(pi/lei));
			for(j=0;j<=lei-1;j++)                   //控制计算不同种蝶形结，即计算系数不同的蝶形结
			{
				for(i=j;i<=FFT_N-1;i=i+le)            //控制同一蝶形结运算，即计算系数相同蝶形结
				{
					ip=i+lei;                           //i，ip分别表示参加蝶形运算的两个节点

					t=EE(xin[ip],u);                    //蝶形运算，详见公式
					xin[ip].real((xin[i].real()-t.real()));
					xin[ip].imag((xin[i].imag()-t.imag()));
					xin[i].real((xin[i].real()+t.real()));
					xin[i].imag((xin[i].imag()+t.imag()));
				}
				u=EE(u,w);                           //改变系数，进行下一个蝶形运算
			}
		}
	}
}

void tx_11g_param::Produce_preamb_mod2(std::complex<double>  complex_preamb[])
{
	int preamb_i,preamb_k;

	int N_times=sample_rate*8/64;
	int N_mod = sample_rate*8 % 64;

	std::complex<double> S_short[53] = 
	{
		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),
		std::complex<double>(1.0, 1.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),
		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),
		std::complex<double>(-1.0, -1.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),
		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),
		std::complex<double>(1.0, 1.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),
		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),
		std::complex<double>(-1.0, -1.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),
		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),
		std::complex<double>(-1.0, -1.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),
		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),
		std::complex<double>(1.0, 1.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),
		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),
		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),
		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),
		std::complex<double>(-1.0, -1.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),
		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),
		std::complex<double>(-1.0, -1.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),
		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),
		std::complex<double>(1.0, 1.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),
		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),
		std::complex<double>(1.0, 1.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),
		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),
		std::complex<double>(1.0, 1.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),
		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),
		std::complex<double>(1.0, 1.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0),
		std::complex<double>(0.0, 0.0)*std::complex<double> (sqrt(float (13.0/6)),0.0)
	};//注意这里必须要变成（13.0/6）=2.1667,而不能是（13/6）=2：
	std::complex<double>  S_shorttext[64];
	memset(S_shorttext, (0.0,0.0),64);

	for(preamb_i=0;preamb_i<26;preamb_i++)  //IFFT算法基于64点 把53个子载波分别映射到相应的子载波上  27-52 -》1-26  0-25->38-63 26是直流子载波，不传送符号，为空符号0
	{
		S_shorttext[preamb_i+1]=S_short[preamb_i+27];
		S_shorttext[preamb_i+38]=S_short[preamb_i];
	}

	ifft(S_shorttext);// IFFT运算
	
	for (preamb_k=0;preamb_k<N_times;preamb_k++)
	{
		for(preamb_i=0;preamb_i<64;preamb_i++)
		{
			complex_preamb[preamb_k*64+preamb_i]=S_shorttext[preamb_i];
		}
	}
	for	(preamb_i=0;preamb_i<=N_mod;preamb_i++)
	{
		complex_preamb[N_times*64+preamb_i]=S_shorttext[preamb_i];
	}
	
	for (preamb_i=0;double(preamb_i)/(sample_rate) < T_tr/2;preamb_i++)
	{
		complex_preamb[preamb_i]=std::complex<double>  (pow(sin(PI/2*(0.5+preamb_i/(T_tr*sample_rate))),2),0.0)*complex_preamb[preamb_i];
		complex_preamb[sample_rate*8-preamb_i]=std::complex<double>  (pow(sin(PI/2*(0.5+preamb_i/(T_tr*sample_rate))),2),0.0)*complex_preamb[sample_rate*8-preamb_i];
	}

	
	std::complex<double> S_long[53] = 
	{
		std::complex<double>(1.0, 0.0),		std::complex<double>(1.0, 0.0),
		std::complex<double>(-1.0, 0.0),		std::complex<double>(-1.0, 0.0),
		std::complex<double>(1.0, 0.0),		std::complex<double>(1.0, 0.0),
		std::complex<double>(-1.0, 0.0),		std::complex<double>(1.0, 0.0),

		std::complex<double>(-1.0, 0.0),		std::complex<double>(1.0, 0.0),
		std::complex<double>(1.0, 0.0),		std::complex<double>(1.0, 0.0),
		std::complex<double>(1.0, 0.0),		std::complex<double>(1.0, 0.0),
		std::complex<double>(1.0, 0.0),		std::complex<double>(-1.0, 0.0),

		std::complex<double>(-1.0, 0.0),		std::complex<double>(1.0, 0.0),
		std::complex<double>(1.0, 0.0),		std::complex<double>(-1.0, 0.0),
		std::complex<double>(1.0, 0.0),		std::complex<double>(-1.0, 0.0),
		std::complex<double>(1.0, 0.0),		std::complex<double>(1.0, 0.0),

		std::complex<double>(1.0, 0.0),		std::complex<double>(1.0, 0.0),
		std::complex<double>(0.0, 0.0),		std::complex<double>(1.0, 0.0),
		std::complex<double>(-1.0, 0.0),		std::complex<double>(-1.0, 0.0),
		std::complex<double>(1.0, 0.0),		std::complex<double>(1.0, 0.0),

		std::complex<double>(-1.0, 0.0),		std::complex<double>(1.0, 0.0),
		std::complex<double>(-1.0, 0.0),		std::complex<double>(1.0, 0.0),
		std::complex<double>(-1.0, 0.0),		std::complex<double>(-1.0, 0.0),
		std::complex<double>(-1.0, 0.0),		std::complex<double>(-1.0, 0.0),

		std::complex<double>(-1.0, 0.0),		std::complex<double>(1.0, 0.0),
		std::complex<double>(1.0, 0.0),		    std::complex<double>(-1.0, 0.0),
		std::complex<double>(-1.0, 0.0),		std::complex<double>(1.0, 0.0),
		std::complex<double>(-1.0, 0.0),		std::complex<double>(1.0, 0.0),

		std::complex<double>(-1.0, 0.0),		std::complex<double>(1.0, 0.0),
		std::complex<double>(1.0, 0.0),		    std::complex<double>(1.0, 0.0),
		std::complex<double>(1.0, 0.0)
	};


	std::complex<double>  S_longtext[64];//={(0.0,0.0)};
	memset(S_longtext, (0.0,0.0),64);

	std::complex<double>  S_addpoint=complex_preamb[sample_rate*8];

	for(preamb_i=0;preamb_i<26;preamb_i++)
	{     
		S_longtext[preamb_i+1]=S_long[preamb_i+27];
		S_longtext[preamb_i+38]=S_long[preamb_i];
	}
	
	ifft(S_longtext);

	for (preamb_k=0;preamb_k<N_times;preamb_k++)
	{
		for(preamb_i=0;preamb_i<64;preamb_i++)
		{
			complex_preamb[preamb_k*64+preamb_i+sample_rate*8+N_mod]=S_longtext[preamb_i];//begin from N_mod
		}
	}

	complex_preamb[sample_rate*8*2]=S_longtext[N_mod];


	for	(preamb_i=0;preamb_i<N_mod;preamb_i++)
	{
		complex_preamb[preamb_i+sample_rate*8]=S_longtext[preamb_i+64-N_mod];
	}


	
	for (preamb_i=0;double(preamb_i)/(sample_rate) < T_tr/2;preamb_i++)
	{
		complex_preamb[preamb_i+sample_rate*8]=std::complex<double>  (pow(sin(PI/2*(0.5+preamb_i/(T_tr*sample_rate))),2),0.0)*complex_preamb[preamb_i+sample_rate*8];
		complex_preamb[sample_rate*8*2-preamb_i]=std::complex<double>  (pow(sin(PI/2*(0.5+preamb_i/(T_tr*sample_rate))),2),0.0)*complex_preamb[sample_rate*8*2-preamb_i];
	}
	
	complex_preamb[sample_rate*8] = complex_preamb[sample_rate*8] +S_addpoint;
	//这里有改动！！！！！！！
	complex_preamb[sample_rate*8*2] = S_longtext[0]/std::complex<double>(2.0, 0.0);
	S_addpoint=complex_preamb[sample_rate*8*2];
}

void tx_11g_param::reshape_data(std::complex<double>  complex_out[],std::complex<double>  complex_in[],int index)
{
	int reshap_i=0;
	
	/*-----------------------------------------映射到64点数据上，再进行ifft运算之前进行数据重排。----------------*/
	
	for(reshap_i=0;reshap_i<5;reshap_i++)
	{
		complex_out[reshap_i+38]=complex_in[reshap_i];
		complex_out[reshap_i+22]=complex_in[reshap_i+43];
	}
	complex_out[21] = Seq_p126[index]*std::complex<double>  (-1.0,0.0);				
	complex_out[43] = Seq_p126[index]*std::complex<double>  (1.0,0.0);                
	
	for(reshap_i=0;reshap_i<13;reshap_i++)
	{
		complex_out[reshap_i+8] = complex_in[reshap_i+30];
		complex_out[reshap_i+44] = complex_in[reshap_i+5];
	}
	complex_out[7] = Seq_p126[index]*std::complex<double>  (1.0,0.0);                
	complex_out[57] = Seq_p126[index]*std::complex<double>  (1.0,0.0);				
	
	for(reshap_i=0;reshap_i<6;reshap_i++)
	{
		complex_out[reshap_i+58] = complex_in[reshap_i+18];
		complex_out[reshap_i+1] = complex_in[reshap_i+24];
	}
}

void tx_11g_param::add_recycle(std::complex<double>  complex_out[],std::complex<double>  complex_in[],int sample_rate)
{
	int recycle_i = 0;
	int index_out=80;
    int recycle_mod = index_out % 64;
	
	
	for(recycle_i=0;recycle_i < 64;recycle_i++)
	{
		complex_out[recycle_i+recycle_mod]=complex_in[recycle_i];//begin from N_mod
	}
	
//	complex_out[index_out]=complex_in[0];
	
	
	for	(recycle_i=0;recycle_i<recycle_mod;recycle_i++)
	{
		complex_out[recycle_i]=complex_in[recycle_i+64-recycle_mod];
	}
	
	//for (recycle_i=0; double(recycle_i)/(sample_rate) < T_tr/2;recycle_i++)
//	{
//		complex_out[recycle_i]=std::complex<double>  (pow(sin(PI/2*(0.5+recycle_i/(T_tr*sample_rate))),2),0.0)*complex_out[recycle_i];
//		complex_out[index_out-recycle_i]=std::complex<double>  (pow(sin(PI/2*(0.5+recycle_i/(T_tr*sample_rate))),2),0.0)*complex_out[index_out-recycle_i];
//	}

}

int tx_11g_param::ones(int n)
{
	int sum = 0;
	for(int i = 0; i < 8; i++) 
	{
		if(n & (1 << i)) 
		{
			sum++;
		}
	}
	return sum;
}

void tx_11g_param::Produce_singal_mod2(std::complex<double>  complex_singal[],int *Q_pinter,int data_length)
{
//	int ones(int);

	int singal_i=0;
	int length_N=0;
	char SINGAL[24] = {0};
	
/*---------------------------------------------------设置SINGAL域的各个参数位-------------------------------------------------------*/
	
	switch(encoding) 
	{
		case BPSK_1_2:
			SINGAL[0] = 1;
			SINGAL[1] = 1;
			SINGAL[2] = 0;
			SINGAL[3] = 1; // 0b00001101
			break;

		case BPSK_3_4:
			SINGAL[0] = 1;
			SINGAL[1] = 1;
			SINGAL[2] = 1;
			SINGAL[3] = 1; // 0b00001111
			break;

		case QPSK_1_2:
			SINGAL[0] = 0;
			SINGAL[1] = 1;
			SINGAL[2] = 0;
			SINGAL[3] = 1; // 0b00000101
			break;

		case QPSK_3_4:
			SINGAL[0] = 0;
			SINGAL[1] = 1;
			SINGAL[2] = 1;
			SINGAL[3] = 1; // 0b00000111
			break;

		case QAM16_1_2:
			SINGAL[0] = 1;
			SINGAL[1] = 0;
			SINGAL[2] = 0;
			SINGAL[3] = 1; // 0b00001001
			break;
			break;

		case QAM16_3_4:
			SINGAL[0] = 1;
			SINGAL[1] = 0;
			SINGAL[2] = 1;
			SINGAL[3] = 1; // 0b00001011
			break;

		case QAM64_2_3:
			SINGAL[0] = 0;
			SINGAL[1] = 0;
			SINGAL[2] = 0;
			SINGAL[3] = 1; // 0b00000001
			break;

		case QAM64_3_4:
			SINGAL[0] = 0;
			SINGAL[1] = 0;
			SINGAL[2] = 1;
			SINGAL[3] = 1; // 0b00000011
			break;
		
		default:
			assert(false);
			break;
	}

	for (singal_i=0;singal_i<12;singal_i++)
	{
		SINGAL[singal_i+5]=(data_length >> singal_i) & 0x01;
	}

	//偶校验
	int P=0;
	for(int i = 0;i<17;i++)
	{
		if (SINGAL[i]==1)
		{
			P++;
		}
	}
	int n;
	n = P%2;
	if (n==1)
	{
		SINGAL[17]=1;
	}
	else
	{
		SINGAL[17]=0;
	}



/*------------------------------------------------SINGAL域信号生成-------------------------------------------------------------*/
	char SINGAL_pointer[48] = {0} ;

// convolutional encoding (scrambling is not needed)
	convolutional_encoding(SINGAL, SINGAL_pointer,24);//卷积编码

	char SINGAL_inter[1000]={0};
	int first_num [48] = {0} ;       //
	int second_num [48] = {0} ;

//	int s = max(1 / 2, 1);
	int s=1;

	for(int n = 0; n < 48; n++) 
	{
		first_num[n] = 3*( n % 16 ) + int(floor(double (n/16)));
	}
	for(int j = 0; j < 48; j++) 
	{
		second_num[j] = s * int (floor(double (j / s))) +  ((j + int(floor(16.0 * j / 48))) % s);
	}
	for(int k = 0; k < 48; k++) 
	{
		SINGAL_inter[second_num[first_num[k]]] = SINGAL_pointer[k];
	}

	std::complex<double>  SINGAL_map[48];//={(0.0,0.0)};
	memset(SINGAL_map, (0.0,0.0),48);

	for (int i=0;i<48;i++)
	{
		SINGAL_map[i]=BPSK_D[SINGAL_inter[i]];
	}

	std::complex<double>  S_singal[64];//={(0.0,0.0)};
	memset(S_singal,(0.0,0.0),64);

	reshape_data(S_singal,SINGAL_map,index_q);

	ifft(S_singal);

	add_recycle(complex_singal,S_singal,sample_rate);

	(* Q_pinter)++;

}

void tx_11g_param::Bit_to_bit(char Bitdata[],char bitdata[],int bit_length)
{
	int B2b_i,B2b_k;
	
	for (B2b_k=0; B2b_k<bit_length; B2b_k++)
	{
		for (B2b_i=0;B2b_i<8;B2b_i++)
		{
			bitdata[8*B2b_k+B2b_i]=(Bitdata[B2b_k] >> B2b_i) & 0x01;
		}
	}
}

//void tx_11g_param::scramble_mod2(const char *in, char *out,char initial_state)
	void tx_11g_param::scramble_mod2(const char *in, char *out,int initial_state)
{

  if (GprotocolConfig.scrambler_state_OFDM)
  {

	
	int state = initial_state;
    int feedback;
	
    for (int i = 0; i < n_data; i++) 
	{
		feedback = (!!(state & 64)) ^ (!!(state & 8));
		out[i] = feedback ^ in[i];
		state = ((state << 1) & 0x7e) | feedback;
    }
  } 
  else
  {
	  for (int i = 0; i < n_data; i++) 
	  {
		  out[i] = in[i];
	  }
  }
}

void tx_11g_param::reset_tail_bits(char *scrambled_data)
{
	memset(scrambled_data + n_data - n_pad - 6, 0, 6 * sizeof(char));
}

void tx_11g_param::convolutional_encoding(const char *in, char *out,int data)
{
	int state = 0;
	
	for(int i = 0; i < data; i++) 
	{
		assert(in[i] == 0 || in[i] == 1);  //assert宏的原型定义在<assert.h>中，其作用是如果它的条件返回错误，则终止程序执行.
		state = ((state << 1) & 0x7e) | in[i];
		out[i * 2]     = ones(state & 0155) % 2;
		out[i * 2 + 1] = ones(state & 0117) % 2;
	}
}

void tx_11g_param::puncturing(const char *in, char *out)
{
	int mod;
	
	for (int i = 0; i < n_data * 2; i++) 
	{
		switch(encoding) 
		{
		case BPSK_1_2:
		case QPSK_1_2:
		case QAM16_1_2:
			*out = in[i];
			out++;
			break;
			
		case QAM64_2_3:
			if (i % 4 != 3) 
			{
				*out = in[i];
				out++;
			}
			break;
			
		case BPSK_3_4:
		case QPSK_3_4:
		case QAM16_3_4:
		case QAM64_3_4:
			mod = i % 6;
			if (!(mod == 3 || mod == 4)) 
			{
				*out = in[i];
				out++;
			}
			break;
			
		default:
			assert(false);
			break;
		}
	}
}

void tx_11g_param::interleave(const char *in, char *out, bool reverse)
{
	int *first = new int [n_cbps];       
	int *second =new int [n_cbps];
	int s = max(n_bpsc / 2, 1);
	
	for(int j = 0; j < n_cbps; j++) 
	{
		*(first+j) = s * (j / s) + ((j + int(floor(16.0 * j / n_cbps))) % s);
	}
	
	for(int m = 0; m < n_cbps; m++) 
	{
		*(second+m) = 16 * m - (n_cbps - 1) * int(floor(16.0 * m / n_cbps));
	}
	
	for(int i = 0; i < n_sym; i++) 
	{
		for(int k = 0; k < n_cbps; k++) 
		{
			if(reverse) {
				out[i * n_cbps + *(second+*(first+k))] = in[i * n_cbps + k];
			} 
			else 
			{
				out[i * n_cbps + k] = in[i * n_cbps + *(second+*(first+k))];
			}
		}
	}
	
	delete first;
	delete second;
}

void tx_11g_param::symbol_mapping(const char map_in[], std::complex<double>  map_out[])
{
	int map_i;
	
	switch(encoding) 
	{
	case BPSK_1_2:
	case BPSK_3_4:
		for(map_i=0;map_i<n_encoded_bits/n_bpsc;map_i++)
		{
			map_out[map_i]=BPSK_D[map_in[map_i*n_bpsc]];
		}
		break;
		
	case QPSK_1_2:
	case QPSK_3_4:
		for(map_i=0;map_i<n_encoded_bits/n_bpsc;map_i++)
		{
			map_out[map_i]=QPSK_D[map_in[map_i*n_bpsc]*2+map_in[map_i*n_bpsc+1]];
		}
		break;
		
	case QAM16_1_2:
	case QAM16_3_4:
		for(map_i=0;map_i<n_encoded_bits/n_bpsc;map_i++)
		{
			map_out[map_i]=QAM16_D[map_in[map_i*n_bpsc]*8+map_in[map_i*n_bpsc+1]*4+map_in[map_i*n_bpsc+2]*2+map_in[map_i*n_bpsc+3]];
		}
		break;
		
	case QAM64_2_3:
	case QAM64_3_4:
		for(map_i=0;map_i<n_encoded_bits/n_bpsc;map_i++)
		{
			map_out[map_i]=QAM64_D[map_in[map_i*n_bpsc]*32+map_in[map_i*n_bpsc+1]*16+map_in[map_i*n_bpsc+2]*8+map_in[map_i*n_bpsc+3]*4+map_in[map_i*n_bpsc+4]*2+map_in[map_i*n_bpsc+5]];
		}
		break;
		
				default:
					assert(false);
					break;
		}
}

void tx_11g_param::Produce_data_mod2(char char_datain[],std::complex<double>  complex_dataout[],int * Q_pinter,int data_length)
{
	char *b_data = new char [data_length*8];
	memset(b_data, 0, data_length*8);
	Bit_to_bit(char_datain,b_data,data_length);
	
	char *data_scramble = new char [n_data];
	memset(data_scramble, 0, n_data);
	for(int i=16;i<16+data_length*8;i++) data_scramble[i]=b_data[i-16];
	delete []b_data;
	
	char *data_scrambleout = new char [n_data];
	memset(data_scrambleout, 0, n_data);
	int scramble_state=GprotocolConfig.scramble_state_initial;
	scramble_mod2(data_scramble, data_scrambleout,scramble_state);//
	delete []data_scramble;
	
	reset_tail_bits(data_scrambleout) ;//将加扰后的尾比特置0.
	
	char *data_convolution =new char [n_data*2];
	memset(data_convolution, 0, n_data*2);
	convolutional_encoding(data_scrambleout, data_convolution,n_data);
	delete data_scrambleout;
	
	char *data_punctur =new char [n_encoded_bits];
	memset(data_punctur, 0, n_encoded_bits);
	puncturing(data_convolution, data_punctur);
	delete []data_convolution;
	
	char *data_interleave = new char [n_encoded_bits];
	memset(data_interleave, 0, n_encoded_bits);
	interleave(data_punctur, data_interleave,false);
	delete []data_punctur;
    
	std::complex<double>  *symbol_mapp = new std::complex<double>  [n_encoded_bits/n_bpsc];
	memset(symbol_mapp, (0.0,0.0), n_encoded_bits/n_bpsc);
	symbol_mapping(data_interleave, symbol_mapp);
	delete []data_interleave;
	//complex ofdm_side=(0.0,0.0) ;
//	std::complex<double>  ofdm_side;
	//ofdm_side.setValue(0.0,0.0);
	//ofdm_side.real(0.0);
	//ofdm_side.imag(0.0);
	
	
	for (int data_i=0;data_i<n_sym;data_i++)
	{	
		std::complex<double>  data_part64[64];//={(0.0,0.0)}; 
		std::complex<double>  data_part48[48];//={(0.0,0.0)}; 
		std::complex<double>  data_part81[81];//={(0.0,0.0)};

		memset(data_part64, (0.0,0.0),64);
		memset(data_part48, (0.0,0.0),48);
		memset(data_part81, (0.0,0.0),81);
		
		for(int data_k=0;data_k<48;data_k++)
		{
			data_part48[data_k]=symbol_mapp[48*data_i+data_k];
		}
		
		reshape_data(data_part64,data_part48,* Q_pinter);
		
		ifft(data_part64);
		
		add_recycle(data_part81,data_part64,sample_rate);
		
	//	data_part81[0]=data_part81[0]+ofdm_side;
	//	if((data_i+1)*80==80*n_sym) complex_dataout[80*n_sym] = data_part64[0]/std::complex<double> (2.0,0.0);
	//	ofdm_side=data_part81[80];
		
		for(int data_m=0;data_m<80;data_m++)
		{
			complex_dataout[80*data_i+data_m]=data_part81[data_m];
		}
		
		(*Q_pinter)++;
	}
	
	delete [] symbol_mapp;
}

void tx_11g_param::Produce_PPDU_mod2(std::complex<double>  preambpart_in[],std::complex<double>  singalpart_in[],std::complex<double>  datapart_in[],std::complex<double>  PPDU_out[],int preamb_length,int singal_length,int data_length)
{
	/*int PPDU_i=0;
	
	for(PPDU_i=0;PPDU_i<preamb_length;PPDU_i++) PPDU_out[PPDU_i]=preambpart_in[PPDU_i];
	
	PPDU_out[preamb_length-1]=preambpart_in[preamb_length-1]+singalpart_in[0];
	
	for(PPDU_i=0;PPDU_i<singal_length;PPDU_i++) PPDU_out[PPDU_i+preamb_length]=singalpart_in[PPDU_i];
	
	PPDU_out[preamb_length+singal_length-2]=singalpart_in[singal_length-1]+datapart_in[0];
	
	for(PPDU_i=0;PPDU_i<data_length;PPDU_i++) PPDU_out[PPDU_i+preamb_length+singal_length]=datapart_in[PPDU_i];//*/

	int PPDU_i=0;
	
	for(PPDU_i=0;PPDU_i<preamb_length-1;PPDU_i++) PPDU_out[PPDU_i]=preambpart_in[PPDU_i];
	
	PPDU_out[preamb_length-1]=preambpart_in[preamb_length-1]+singalpart_in[0];
	
	for(PPDU_i=1;PPDU_i<singal_length-1;PPDU_i++) PPDU_out[PPDU_i+preamb_length-1]=singalpart_in[PPDU_i];
	
	PPDU_out[preamb_length+singal_length-2]=singalpart_in[singal_length-1]+datapart_in[0];
	
	for(PPDU_i=1;PPDU_i<data_length;PPDU_i++) PPDU_out[PPDU_i+preamb_length+singal_length-2]=datapart_in[PPDU_i];
}

void tx_11g_param::AutoC(std::complex<double>  *discrete_seq,std::complex<double>  *auto_corr,unsigned int seq_length)//自相关函数
{
	for (unsigned int m=0;m<seq_length;m++)
	{
		std::complex<double>  temp;
	//	temp.setValue(0.0,0.0);
		temp.real(0.0);
		temp.imag(0.0);
		for(unsigned int n=0;n<=seq_length-1 - m;n++)
		{
			temp +=discrete_seq [n + m] *conj( discrete_seq[n]);//求复数的共轭
		}
		if (0 == m)
		{
			auto_corr[seq_length - 1] = temp;
		}
		else
		{
			auto_corr[seq_length-1 + m] = conj(temp);
			auto_corr[seq_length-1 - m] = (temp);

		}
	}
}

void tx_11g_param::length_calculate(int * LENGTH_extension_b7,int * LENGTH_extension_b6,int * LENGTH_extension_b5,int * LENGTH_2,int PSDU_size_bytes,char service_b3,Data_Rate data_rate)
{	//int * LENGTH_extension 
	//int  P = service[3];
	int P = service_b3;
	double data_rate_double;
	if (data_rate == 55)
		 data_rate_double =5.5;
	else
		data_rate_double = data_rate;

	double LENGTH_1 = ((PSDU_size_bytes+P)*8)/(double)data_rate_double;
	*LENGTH_2 = (int)ceil(LENGTH_1);
	
	if( (data_rate==11)&&((*LENGTH_2-LENGTH_1)>= (double)8/11))
		 *LENGTH_extension_b7=1;
	else
		*LENGTH_extension_b7=0;

	if( (data_rate==22)&&((*LENGTH_2-LENGTH_1)< (double)4/11))
		{
			*LENGTH_extension_b7=0;
			*LENGTH_extension_b6=0;
		}
	else if( (data_rate==22)&&((*LENGTH_2-LENGTH_1)< (double)8/11)&&((*LENGTH_2-LENGTH_1)>= (double)4/11))
		{  
			*LENGTH_extension_b7=1;
			*LENGTH_extension_b6=0;
		}
	else if( (data_rate==22)&&((*LENGTH_2-LENGTH_1)>= (double)8/11))
		{  
			*LENGTH_extension_b7=0;
			*LENGTH_extension_b6=1;
		}

	if( (data_rate==33)&&((*LENGTH_2-LENGTH_1)< (double)8/33))
		{
			*LENGTH_extension_b7=0;
			*LENGTH_extension_b6=0;
			*LENGTH_extension_b5=0;
		}
	else if( (data_rate==33)&&((*LENGTH_2-LENGTH_1)< (double)16/33)&&((*LENGTH_2-LENGTH_1)>= (double)8/33))
		{  
			*LENGTH_extension_b7=1;
			*LENGTH_extension_b6=0;
			*LENGTH_extension_b5=0;
		}
	else if( (data_rate==33)&&((*LENGTH_2-LENGTH_1)< (double)24/33)&&((*LENGTH_2-LENGTH_1)>= (double)16/33))
		{  
			*LENGTH_extension_b7=0;
			*LENGTH_extension_b6=1;
			*LENGTH_extension_b5=0;
		}
	else if( (data_rate==33)&&((*LENGTH_2-LENGTH_1)< (double)32/33)&&((*LENGTH_2-LENGTH_1)>= (double)24/33))
		{  
			*LENGTH_extension_b7=1;
			*LENGTH_extension_b6=1;
			*LENGTH_extension_b5=0;
		}
	else if( (data_rate==33)&&((*LENGTH_2-LENGTH_1)>= (double)32/33))
		{  
			*LENGTH_extension_b7=0;
			*LENGTH_extension_b6=0;
			*LENGTH_extension_b5=1;
		}
};

void tx_11g_param::length_calculate_DSSS_OFDM(int * LENGTH,int PSDU_size_bytes)
{	//int * LENGTH_extension 
	
	int PSDUsyncOFDM = 8;
	int PSDUSignalOFDM = 4;
	int PLCPServiceBits = 8;
	int NumberOfOctets;	
	NumberOfOctets= PSDU_size_bytes;
	int PadBits = 6;
	int N_DBPS;//如何初始化？？？
	int SignalExtension = 6;
	int LENGTH_2;

	double LENGTH_1;
	N_DBPS = n_dbps;
	LENGTH_1 = (PLCPServiceBits+8*(NumberOfOctets)+PadBits)/(double)N_DBPS;
	LENGTH_2 = (int) ceil(LENGTH_1);
	*LENGTH = PSDUsyncOFDM + PSDUSignalOFDM + 4*LENGTH_2 + SignalExtension;	
};

 std::vector<int>  tx_11g_param::setVector(std::vector<int> vec, int temp[], int m)
{
	for (int i = 0;i < m;i++)
		vec.push_back(temp[i]);
	return vec;
}

 void  tx_11g_param::dec2bin(int obj, int bin[], int m)
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

 vector<int> tx_11g_param::scrambler(vector<int>PPDU_bit)
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

 void  tx_11g_param::scramble(int str[], int b_index, int Nfrm, int scramble_out[], int inf_len)
{
  int s[7];
  int i0;
  
  static const int iv0[7] = { 1, 1, 0, 1, 1, 0, 0 };//初始值，固定的
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
  } else 
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
    } else 
    {
      i0 = (y + 1);
      i1 = d0;
    }
    i2 = (inf_len / Nfrm);
    for (ss = 0; ss <= i2 - 1; ss++) 
	{
      tmp_size_idx_0 = (i1 - i0) + 1;
      loop_ub = i1 - i0;
      for (i3 = 0; i3 <= loop_ub; i3++) {
        tmp_data[i3] = i0 + i3;
      }
      loop_ub = tmp_size_idx_0 - 1;
      for (i3 = 0; i3 <= loop_ub; i3++) {
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

 void tx_11g_param::DBPSK(std::complex<double> complex_modDB[],vector<int>Data,double theta0)
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


		 if (yPhase%2==0)
		 { 
			 complex_modDB[k].real(1.0);
			complex_modDB[k].imag(0.0);
		 }
		 else
		 {
			 complex_modDB[k].real(-1.0);
			complex_modDB[k].imag(0.0);
		 }
	 } 
 }

 void tx_11g_param::DBPSK(std::complex<double>  complex_modDB[],vector<int>Data)
{
	double Phase_Constellation_0 = 0;
	double Phase_Constellation_1 = PI;
	double theta;
	int yPhase = 0;

  for (int k = 0; k<Data.size();k++)
	{
		if (Data[k]==0)
			theta = Phase_Constellation_0 ;
		else
			{
				theta = Phase_Constellation_1;
		    	yPhase++;
		    }

		if (yPhase%2==0)			
		{	
			complex_modDB[k].real(1.0);
			complex_modDB[k].imag(0.0);
		}
		else
		{
			complex_modDB[k].real(-1.0);
			complex_modDB[k].imag(0.0);
		} 
  //return complex_modDB;
	}
 }

 void tx_11g_param::DQPSK(std::complex<double> complex_modDQ[],vector<int>Data,double theta0)
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

 void tx_11g_param::DQPSK(std::complex<double>  complex_modDQ[],vector<int>Data)
{
    double Phase_Constellation_00 = 0;
	double Phase_Constellation_01 = PI/2;
	double Phase_Constellation_11 = PI;
	double Phase_Constellation_10 = PI*3/2;
	double theta;
	int yPhase = 0;

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
		{
			complex_modDQ[k].real(1.0);
			complex_modDQ[k].imag(0.0);
		}
		else if (yPhase%4==1)
		{
			complex_modDQ[k].real(0.0);
			complex_modDQ[k].imag(1.0);
		}
		else if (yPhase%4==2)
		{
			complex_modDQ[k].real(-1.0);
			complex_modDQ[k].imag(1.0);
		}
		else
		{
			complex_modDQ[k].real(0.0);
			complex_modDQ[k].imag(-1.0);
		}


		//yPhase = yPhase + theta;

		//complex_modDQ[k].setValue(cos(yPhase),sin(yPhase));
	} 
}

 void tx_11g_param::Barker_spread(std::complex<double>  complex_barker[],std::complex<double>  complex_mod[],int m) 
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
			complex_barker[j*Ns+i].real(complex_mod[j].real()*spread11[i]);
			complex_barker[j*Ns+i].imag(complex_mod[j].imag()*spread11[i]);
		}
	//return complex_barker;
}
};

 void tx_11g_param::CCK55(std::complex<double> complexOut[], vector<int> data_in,double theta)//mod1
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
 void tx_11g_param::CCK55(std::complex<double>  complexOut[], vector<int> data_in)
{
	int inf_len;
    //inf_len = sizeof(data_in)/sizeof(data_in[0]);
	inf_len = data_in.size();

	int i,j,k;
	double P, P1, P2, P3, P4;
	P = 0.0;
	P1 = 0.0;
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
				//complexOut[j*8 + i].setValue(C[i].real, C[i].img);
				complexOut[j*8 + i].real(C[i].real);
				complexOut[j*8 + i].imag(C[i].img);
			}
			
		}
	}
};

 void tx_11g_param::CCK11(std::complex<double> complexOut[], vector<int> data_in,double theta)
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
 void  tx_11g_param::CCK11(std::complex<double>  complexOut[], vector<int> data_in)
{
		
	int inf_len;
  //  inf_len = sizeof(data_in)/sizeof(data_in[0]);
	inf_len = data_in.size();

	int i,j,k,l;
	double P;
	P=0.0;
	double fi[4]={};                                                                                                                                                   ;
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
				//complexOut[j*8 + i].setValue(C[i].real, C[i].img);	
				complexOut[j*8 + i].real(C[i].real);
				complexOut[j*8 + i].imag(C[i].img);
			}
			
		}
			
	}
}

 int  tx_11g_param::encoder(int gen[][7], int n, int L, int reg[], int m, vector<int> data_in, int inf_len, int output[])

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

 void  tx_11g_param::repmat_PBCC_bits_55(vector<int> data_in, int Nfrm, int *convecdata,int tail_len,struct fushu *modout,double theta)
{
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
	/*for(i = 3;i < 16; i++)
	{
		rep_PBCC_cover_code[j][i-3]=rep_PBCC_cover_code[j-1][i];
		rep_PBCC_cover_code[j][13]=rep_PBCC_cover_code[j-1][0];//对换顺序
		rep_PBCC_cover_code[j][14]=rep_PBCC_cover_code[j-1][1];
		rep_PBCC_cover_code[j][15]=rep_PBCC_cover_code[j-1][2];
	}*/
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

 void  tx_11g_param::repmat_PBCC_bits_11(vector<int> data_in, int Nfrm, int *convecdata, int tail_len, struct fushu *modout,double theta)
{
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
	/*for(i = 3;i < 16; i++)
		{
			rep_PBCC_cover_code[j][i-3]=rep_PBCC_cover_code[j-1][i];
			rep_PBCC_cover_code[j][13]=rep_PBCC_cover_code[j-1][0];
			rep_PBCC_cover_code[j][14]=rep_PBCC_cover_code[j-1][1];
			rep_PBCC_cover_code[j][15]=rep_PBCC_cover_code[j-1][2];
		}*/
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
	//f[0] = convecdata[2 * i];
	//f[1] = convecdata[2 * i + 1];
	f[0] = convecdata[2 * i + 1]; //y1在前
	f[1] = convecdata[2 * i ];//y0在后
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
					    modout[i].real=-sqrt(2.0)/2;
					    modout[i].img=sqrt(2.0)/2;
					   }
						break;						
				case 2:{
					    modout[i].real=-sqrt(2.0)/2;
					    modout[i].img=-sqrt(2.0)/2;
					   }
						break;		
				case 3:{
						modout[i].real=sqrt(2.0)/2;
					    modout[i].img=-sqrt(2.0)/2;
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
					    modout[i].real=-sqrt(2.0)/2;
					    modout[i].img=-sqrt(2.0)/2;
					   }
						break;						
				case 2:{
					    modout[i].real=sqrt(2.0)/2;
					    modout[i].img=-sqrt(2.0)/2;
					   }
						break;		
				case 3:{
						modout[i].real=sqrt(2.0)/2;
					    modout[i].img=sqrt(2.0)/2;
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

 void  tx_11g_param::PBCC55(std::complex<double>  complexOut[], vector<int> data_in,double theta)
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
	
	repmat_PBCC_bits_55(data_in, Nfrm, output,tail_len,modout, theta);//根据卷积码得到相位信息
	for(i=0;i<tail_len*2;i++)//输出相位信息
	{
		//complexOut[i].setValue(modout[i].real, modout[i].img);
		complexOut[i].real(modout[i].real);
		complexOut[i].imag(modout[i].img);
	}
};    

 void  tx_11g_param::PBCC11(std::complex<double>  complexOut[], vector<int> data_in,double theta)
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

 void  tx_11g_param::PBCC22(std::complex<double>  complexOut[], vector<int> data_in,double theta)
{
	//卷积编码
	//encoder_PBCC22();
	//LEN(data_in, int inf_len);
	int inf_len;
	//inf_len = sizeof(data_in)/sizeof(data_in[0]);
	inf_len=data_in.size();//可能是取输入数据的长度
	int Nfrm = 1;
	int tail_len = inf_len + 8;
	struct fushu *modout=NULL;
	modout=(struct fushu *)malloc(sizeof(struct fushu)*tail_len/2);
	vector<int> data_encode0;//卷积器输入第一路
	vector<int> data_encode1;//卷积器输入第二路
	for (int i=inf_len;i<inf_len+8;i++)
	{
		data_in.push_back(0);
	}
	for (int j=0;j<tail_len/2;j++)
	{
		data_encode0.push_back(data_in[2*j]);
		data_encode1.push_back(data_in[2*j+1]);
	}

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
	/*for(i = 3;i < 16; i++)
	{
		rep_PBCC_cover_code[j][i-3]=rep_PBCC_cover_code[j-1][i];
		rep_PBCC_cover_code[j][13]=rep_PBCC_cover_code[j-1][0];//对换顺序
		rep_PBCC_cover_code[j][14]=rep_PBCC_cover_code[j-1][1];
		rep_PBCC_cover_code[j][15]=rep_PBCC_cover_code[j-1][2];
	}*/
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
    for (i = 0; i < tail_len/2; i++) 
    {
	   PBCC_bits[i] = cover_bits[i];//取L位掩码序列
    }


	int state0 = 0;
	int state1 = 0;

	for(int i = 0; i < tail_len/2; i++) 
	{
		int y0,y1,y2,dd,p;
		//assert(in[i] == 0 || in[i] == 1);  //assert宏的原型定义在<assert.h>中，其作用是如果它的条件返回错误，则终止程序执行.
		state0 = ((state0 << 1) & 0x1e) | data_encode0[i];
		state1 = ((state1 << 1) & 0x1e) | data_encode1[i];
		y0     = (ones(state0 & 0x11)+ones(state1 & 0x08)) % 2;
		y1     = (ones(state0 & 0x02)+ones(state1 & 0x15)) % 2;
		y2     = (ones(state0 & 0x0a)+ones(state1 & 0x0a)) % 2;

		p = 4 * y2 + 2 * y1 + y0;
		switch(p)
		{	 
		case 0: dd = 0;	
		    break;
		case 1: dd = 2;
			break;
		case 2: dd = 4;
			break;
		case 3: dd = 6;
			break;
		case 4: dd = 1;
			break;
		case 5: dd = 3;
			break;
		case 6: dd = 5;
			break;
		case 7: dd = 7;
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
				modout[i].real=0;
				modout[i].img=1;
				   }
				   break;						
			case 2:{
				modout[i].real=-sqrt(2.0)/2;
				modout[i].img=sqrt(2.0)/2;
				   }
				   break;		
			case 3:{
				modout[i].real=-1;
				modout[i].img=0;
				   }
				   break;
			case 4:{
				modout[i].real=-sqrt(2.0)/2;
				modout[i].img=-sqrt(2.0)/2;
				   }
				   break;	
			case 5:{
				modout[i].real=0;
				modout[i].img=-1;
				   }
				   break;	
			case 6:{
				modout[i].real=sqrt(2.0)/2;
				modout[i].img=-sqrt(2.0)/2;
				   }
				   break;	
			case 7:{
				modout[i].real=1;
				modout[i].img=0;
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
				modout[i].real=-1;
				modout[i].img=0;
				   }
				   break;						
			case 2:{
				modout[i].real=-sqrt(2.0)/2;
				modout[i].img=-sqrt(2.0)/2;
				   }
				   break;		
			case 3:{
				modout[i].real=0;
				modout[i].img=-1;
				   }
				   break;
			case 4:{
				modout[i].real=sqrt(2.0)/2;
				modout[i].img=-sqrt(2.0)/2;
				   }
				   break;	
			case 5:{
				modout[i].real=1;
				modout[i].img=0;
				   }
				   break;	
			case 6:{
				modout[i].real=sqrt(2.0)/2;
				modout[i].img=sqrt(2.0)/2;
				   }
				   break;	
			case 7:{
				modout[i].real=0;
				modout[i].img=1;
				   }
				   break;	
			default:break;					
			}
		}

	}
	/*int i;
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
	encoder(gen, n, L, reg, m, data_in, inf_len, output);//卷积编码*/

	//repmat_PBCC_bits_11(data_in, Nfrm, output,tail_len,modout,theta);////根据卷积码得到相位信息
	for(i=0;i<tail_len/2;i++)
	{
		//ComplexNumberOutput(modout[i]);
		//complexOut[i].setValue(modout[i].real, modout[i].img);
		complexOut[i].real(modout[i].real);
		complexOut[i].imag(modout[i].img);
	}


}

 void  tx_11g_param::PBCC33(std::complex<double>  complexOut[], vector<int> data_in,double theta)
{
	//encoder_PBCC33();



}

//DSSS
 vector<int> tx_11g_param:: Produce_preamb_bit(int S_preamb_length)
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
		int temp[16] = {1,1,1,1,0,0,1,1,1,0,1,0,0,0,0,0};
		//SFD = setVector(SFD, temp, 16);
		for(int i = 0;i<16;i++)
		{
		SFD[i]=temp[i];
		}
		//preamble
		for (int j=0;j<sync_size;j++)
		{ 
			preamble_bit[j]=sync[j];
		}

		for (int j=0;j<SFD_size;j++)
		{ 
			preamble_bit[j+56]=SFD[j];
		}
	}	
	else
	{
		sync_size =128;
		for (int i=0;i<sync_size;i++)
		{ 
			sync.push_back(1); 
		}//128个1比特
		int temp[16] = {0,0,0,0,0,1,0,1,1,1,0,0,1,1,1,1};
		//SFD = setVector(SFD, temp, 16);

		for(int i = 0;i<16;i++)
		{
		SFD[i]=temp[i];
		}
		for (int j=0;j<sync_size;j++)
		{
			preamble_bit[j]=sync[j];
		}
		for (int j=0;j<SFD_size;j++)
		{
			preamble_bit[j+128]=SFD[j];
		}
	}

	return preamble_bit;

}

 void tx_11g_param:: Produce_preamb_mod1(std::complex<double> complex_preamb[],vector<int> PPDU_Scrambled,std::complex<double> preamble_last_symbol[])
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

 

 vector<int> tx_11g_param::Produce_header_bit(int S_header_length)
 {

	 int * LENGTH_extension_b7 = new int;	  
	 int * LENGTH_extension_b6 = new int;
	 int * LENGTH_extension_b5 = new int;

	 * LENGTH_extension_b7 = 0;
	 * LENGTH_extension_b6 = 0;
	 * LENGTH_extension_b5 = 0;

	 switch(data_rate)
	 {
	 case  _1Mbps:
		 {
			 signal = 0x50;;
			 service = 0x00;
			 char service_b3 = 0;
			 length_calculate(LENGTH_extension_b7,LENGTH_extension_b6,LENGTH_extension_b5,&length,PSDU_size_bytes,service_b3,_1Mbps);
			 break;
		 }
	 case _2Mbps:		
		 {

			 //signal = 0x14;
			 signal = 0x28;
			 service = 0x00;
			 char service_b3 = 0;
			 length_calculate(LENGTH_extension_b7,LENGTH_extension_b6,LENGTH_extension_b5,&length,PSDU_size_bytes,service_b3,_2Mbps);
			 break;
		 }
	 case _3Mbps:
		 {
			 int NDBPS;
			 switch(GprotocolConfig.EZOG_Encoding)
			 {
			 case BPSK_1_2:
				 NDBPS=24;
				 break;
			 case BPSK_3_4:
				 NDBPS=36;
				 break;
	         case QPSK_1_2:
				 NDBPS=48;
				 break;
			 case QPSK_3_4:
				 NDBPS=72;
				 break;
             case QAM16_1_2:
				 NDBPS=96;
				 break;
			 case QAM16_3_4:
				 NDBPS=144;
				 break;
			 case QAM64_2_3:
				 NDBPS=192;
				 break;
			 case QAM64_3_4:
				 NDBPS=216;
				 break;
			 default:
		     {
			 assert(false);
			 break;
		     }
			 }
			 signal = 0x78;
			 service = 0x00;
             int x=(int)ceil((double)(8+PSDU_size_bytes*8+6)/NDBPS);
			 length=12+4*x+6;
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
			 length_calculate(LENGTH_extension_b7,LENGTH_extension_b6,LENGTH_extension_b5,&length,PSDU_size_bytes,service_b3,_55Mbps);

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
			 length_calculate(LENGTH_extension_b7,LENGTH_extension_b6,LENGTH_extension_b5,&length,PSDU_size_bytes,service_b3,_11Mbps);

			 if ( *LENGTH_extension_b7 == 1)
			 { 
				 service = service ^ 0x01;
			 }

			 break;
		 }
	 case _22Mbps:
		 {
			 signal = 0x3b;
			 service = 0x10;
			 int service_b3 = 1; 
			 length_calculate(LENGTH_extension_b7,LENGTH_extension_b6,LENGTH_extension_b5,&length,PSDU_size_bytes,service_b3,_22Mbps);		
			 service = service & (*LENGTH_extension_b7);
			 service = service & ((*LENGTH_extension_b6)<<1);			 
			 break;
		 }
	 case _33Mbps:
		 {

			 signal = 0x84;
			 service = 0x10;
			 int service_b3 = 1; 
			 length_calculate(LENGTH_extension_b7,LENGTH_extension_b6,LENGTH_extension_b5,&length,PSDU_size_bytes,service_b3,_33Mbps);		

			 service = service & (*LENGTH_extension_b7);
			 service = service & ((*LENGTH_extension_b6)<<1);
			 service = service & ((*LENGTH_extension_b5)<<2);


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

	 delete [] LENGTH_extension_b7;
	 delete [] LENGTH_extension_b6;
	 delete [] LENGTH_extension_b5;

 }

 void tx_11g_param::Produce_header_mod1(std::complex<double> complex_header[],vector<int> PPDU_Scrambled,double theta0,std::complex<double> header_last_symbol[],std::complex<double> header_last_chip[])
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


 void tx_11g_param::Produce_PSDU_mod1(std::complex<double> complex_PSDU[],vector<int> PPDU_Scrambled,double theta1,double theta2)
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
	  else if(modulation_type == 6)  //PBCC22
	  {
		  PBCC22(complex_PSDU,scrambleOut,theta2);
	  }
	  else if(modulation_type == 7)  //PBCC33
	  {
		  PBCC33(complex_PSDU,scrambleOut,theta2);
	  }
	  else 
		  cout<<"Error modulation!\n";
	  // delete [] complex_modDB;
  }



 void tx_11g_param::Produce_PPDU_mod1(std::complex<double>  preambpart_in[],std::complex<double>  headerpart_in[],std::complex<double>  datapart_in[],std::complex<double>  PPDU_out[],int preamb_length,int header_length,int data_length)
  {

    int PPDU_i=0;
	
	for(PPDU_i=0;PPDU_i<preamb_length;PPDU_i++) PPDU_out[PPDU_i]=preambpart_in[PPDU_i];

	for(PPDU_i=0;PPDU_i<header_length;PPDU_i++) PPDU_out[PPDU_i+preamb_length]=headerpart_in[PPDU_i];

	for(PPDU_i=0;PPDU_i<data_length;PPDU_i++) PPDU_out[PPDU_i+preamb_length+header_length]=datapart_in[PPDU_i];

  } 

/*----显示信号数据----*/ 
void  tx_11g_param::display(std::complex<double>  comstr[],int leng_N) 
{  
	int i; 
	
	for(i=0;i<leng_N;i++)  
	{   
		cout.width(9);      
		cout.precision(3);
		cout<<comstr[i].real();	
		//if (abs(comstr[i].real())<10e-10) cout<<"0.0";//由于计算机数据位长的误差产生的特别小是数不予以显示。
		//else cout<<comstr[i].real();
		cout.width(2);      
		cout<<'+';

		cout.width(9);    
		cout.precision(3); 
		cout<<comstr[i].imag()<<'i'<<'\t'; 	
		//if (abs(comstr[i].imag())<10e-10) cout<<"0.0"<<'i'<<'\t';//由于计算机数据位长的误差产生的特别小是数不予以显示。
		//else cout<<comstr[i].imag()<<'i'<<'\t';   
		if((i+1)%3==0) cout<<endl;    
		//if((i+1)%80==0) cout<<"data域信号："<<std::endl<<endl; 
	}
}

//DSSS-OFDM
 void  tx_11g_param::Produce_preamb_mod3(std::complex<double>  complex_preamb[])
 {
	 if (preamble_type ==shortPreamble)
		{  		  		  
			  //SFD=0x05CF;发送时从右边开始发送
			  int temp[16] = {0,0,0,0,0,1,0,1,1,1,0,0,1,1,1,1};
			   for (int i=0; i<SFD_size;i++)
		         {SFD[i] = temp[i];}

			   //preamble
			  for (int j=0;j<sync_size;j++)
			   { preamble[j] = sync[j] ;}
			  for (int j=SFD_size-1;j>=0;j--)
			   { preamble[j+sync_size]=temp[SFD_size-1-j];}

			    vector<int> scrambleOut(72,0);
			  if((scrambler_state == ON)||(scrambler_state == Preamble_only))
			  {
				  int b_index = 0; //short preamble initial 0 0 1 1 0 1 1
				  int Nfrm = 1;
				  int inf_len= preamble.size();
				  int *scramble_out;
				  scramble_out = (int *) malloc(inf_len* sizeof(int));
				 int str[72];
				 for (int i=0;i<72;i++)
					 str[i]=preamble[i];

				  scramble(str, b_index, Nfrm, scramble_out, inf_len);		  

			   for (int i=0;i<72;i++)
				 {
					 scrambleOut[i]=scramble_out[i];
					}
				}
	 
			   else
			   {
				   scrambleOut = preamble;		   
			   }

			  std::complex<double>  complex_modDB[72];
			  DBPSK(complex_modDB, scrambleOut);
			  int m = 72;
			  Barker_spread(complex_preamb, complex_modDB,m);
		  }
		 
		  else
		  {
			 // sync_size =128;	  
			   //SFD=0xF3A0; 发送时从右边开始发送
			  int temp[16] = {1,1,1,1,0,0,1,1,1,0,1,0,0,0,0,0};
			  
			  for (int i=0; i<SFD_size;i++)
				{SFD[i] = temp[i];}

		 for (int j=0;j<sync_size;j++)
				 { preamble[j] = sync[j] ;}
			  for (int j=0;j<SFD_size;j++)
				 { preamble[j+sync_size]=temp[SFD_size-1-j];}

			    vector<int> scrambleOut(144,0);

			   if((scrambler_state == ON)||(scrambler_state == Preamble_only))
			  {   
				  int b_index = 1; //long preamble initial [1 1 0  1 1 0 0]
				  int Nfrm = 1;
				  int inf_len= preamble.size();
				  int *scramble_out;
				  scramble_out = (int *) malloc(inf_len* sizeof(int));
				 int str[144];
				 for (int i=0;i<144;i++)
					 str[i]=preamble[i];
				  scramble(str, b_index, Nfrm, scramble_out, inf_len);	

				 for (int i=0;i<144;i++)
				 {
					 scrambleOut[i] = scramble_out[i];
				  }
			   }
			   else
			   {
				   scrambleOut = preamble;		   
			   }
			
			  std::complex<double>  complex_modDB[144];
			  DBPSK(complex_modDB, scrambleOut);
			
			  int m = 144;
			  Barker_spread(complex_preamb, complex_modDB,m);
		  }      
 }

void  tx_11g_param::Produce_header_mod3(std::complex<double>  complex_header[])
  {		
	 //所有速率 signal都置为3Mbit/s
	signal = 0x1E;
	service = 0x20;

	length_calculate_DSSS_OFDM(&length,PSDU_size_bytes);	
	
	for (int i=0;i< signal_size;i++)
		{		
			msg[i] = (signal>>i)&0x01;
		}

	for (int i=0;i<service_size;i++)
		{
			msg[i+signal_size] = (service>>i) & 0x01;
		}

	for (int i=0;i<length_size;i++)
		{	
			msg[i+signal_size+service_size] = (length>>i) & 0x01;
		}

	unsigned short msg_size = 32;
	unsigned char buf[3] = {signal,service,length};
	int crc_16[16]={0};
	unsigned short crc; 

	crc = crc16(buf,msg_size);
	dec2bin( crc,crc_16, 2*BYTE_B);
	  
	for (int i=0;i<msg_size;i++)
		header[i] = msg[i];

	for (int i = 0;i<CRC_size;i++)
		header[i+msg_size] = crc_16[i];

	if (preamble_type == longPreamble)
	{
		  vector<int> scrambleOut(48,0);
		  if(scrambler_state == ON)
		  {   
			  int b_index = 1; //long preamble initial [1 1 0  1 1 0 0] -> b_index = 1
			  int Nfrm = 1;
			  int inf_len= header.size();
			  int *scramble_out;
	          scramble_out = (int *) malloc(inf_len* sizeof(int));
			  int str[48];
			  for (int i=0;i<48;i++)
				  str[i]=header[i];
			  
			  scramble(str, b_index, Nfrm, scramble_out, inf_len);	

			 for (int i=0;i<48;i++)
			 {
				 scrambleOut[i]=scramble_out[i];
			  }
		   }
		   else
		   {
			   scrambleOut = header;		   
		   }
		std::complex<double>  complex_modDB[6*BYTE_B];
		DBPSK(complex_modDB,scrambleOut);
		int m = 6*BYTE_B;
        Barker_spread(complex_header,complex_modDB,m);  
	}
	else
	{
		  vector<int> scrambleOut(48,0);
		   if(scrambler_state == ON)
		  {   
			  int b_index = 0; //short preamble initial 0 0 1 1 0 1 1
			  int Nfrm = 1;
			  int inf_len= header.size();
			  int *scramble_out;
	          scramble_out = (int *) malloc(inf_len* sizeof(int));
			 int str[48];
			 for (int i=0;i<48;i++)
				 str[i]=header[i];
			  scramble(str, b_index, Nfrm, scramble_out, inf_len);	

			 for (int i=0;i<48;i++)
			 {
				 scrambleOut[i]=scramble_out[i];
			  }
		   }
		   else
		   {
			   scrambleOut = header;		   
		   }
		std::complex<double>  complex_modDQ[6*BYTE_B];
		DQPSK(complex_modDQ,scrambleOut);
		int m = 3*BYTE_B; //DQPSK
        Barker_spread(complex_header,complex_modDQ,m);
	}
  }


//只包含两个长训练序列和保护间隔 由preamble修改成如下函数 
void  tx_11g_param::Produce_training_sequence_mod3(std::complex<double>  complex_preamb[])
{   
	void display(std::complex<double>  comstr[],int leng_N);
	int preamb_i,preamb_k;

	int N_times=sample_rate*8/64;
	int N_mod = sample_rate*8 % 64;
	
	std::complex<double>  S_long[53] = 
	{
		std::complex<double> (1.0, 0.0),		std::complex<double> (1.0, 0.0),
		std::complex<double> (-1.0, 0.0),		std::complex<double> (-1.0, 0.0),
		std::complex<double> (1.0, 0.0),		std::complex<double> (1.0, 0.0),
		std::complex<double> (-1.0, 0.0),		std::complex<double> (1.0, 0.0),

		std::complex<double> (-1.0, 0.0),		std::complex<double> (1.0, 0.0),
		std::complex<double> (1.0, 0.0),		std::complex<double> (1.0, 0.0),
		std::complex<double> (1.0, 0.0),		std::complex<double> (1.0, 0.0),
		std::complex<double> (1.0, 0.0),		std::complex<double> (-1.0, 0.0),

		std::complex<double> (-1.0, 0.0),		std::complex<double> (1.0, 0.0),
		std::complex<double> (1.0, 0.0),		std::complex<double> (-1.0, 0.0),
		std::complex<double> (1.0, 0.0),		std::complex<double> (-1.0, 0.0),
		std::complex<double> (1.0, 0.0),		std::complex<double> (1.0, 0.0),

		std::complex<double> (1.0, 0.0),		std::complex<double> (1.0, 0.0),
		std::complex<double> (0.0, 0.0),		std::complex<double> (1.0, 0.0),
		std::complex<double> (-1.0, 0.0),		std::complex<double> (-1.0, 0.0),
		std::complex<double> (1.0, 0.0),		std::complex<double> (1.0, 0.0),

		std::complex<double> (-1.0, 0.0),		std::complex<double> (1.0, 0.0),
		std::complex<double> (-1.0, 0.0),		std::complex<double> (1.0, 0.0),
		std::complex<double> (-1.0, 0.0),		std::complex<double> (-1.0, 0.0),
		std::complex<double> (-1.0, 0.0),		std::complex<double> (-1.0, 0.0),

		std::complex<double> (-1.0, 0.0),		std::complex<double> (1.0, 0.0),
		std::complex<double> (1.0, 0.0),		std::complex<double> (-1.0, 0.0),
		std::complex<double> (-1.0, 0.0),		std::complex<double> (1.0, 0.0),
		std::complex<double> (-1.0, 0.0),		std::complex<double> (1.0, 0.0),

		std::complex<double> (-1.0, 0.0),		std::complex<double> (1.0, 0.0),
		std::complex<double> (1.0, 0.0),		std::complex<double> (1.0, 0.0),
		std::complex<double> (1.0, 0.0)
	};

	std::complex<double>  S_longtext[64];
	memset(S_longtext,(0.0,0.0),64);

	//complex S_addpoint=complex_preamb[sample_rate*8];//为什么要设置 S_addpoint
	//complex S_addpoint=complex_preamb[0];

	for(preamb_i=0;preamb_i<26;preamb_i++)
	{
		S_longtext[preamb_i+1]=S_long[preamb_i+27];
		S_longtext[preamb_i+38]=S_long[preamb_i];
	}
	
	ifft(S_longtext);

	for (preamb_k=0;preamb_k<N_times;preamb_k++)
	{
		for(preamb_i=0;preamb_i<64;preamb_i++)
		{
			//complex_preamb[preamb_k*64+preamb_i+sample_rate*8+N_mod]=S_longtext[preamb_i];//begin from N_mod
			complex_preamb[preamb_k*64+preamb_i+N_mod]=S_longtext[preamb_i];//begin from N_mod
		}
	}

	//complex_preamb[sample_rate*8*2]=S_longtext[N_mod];
	complex_preamb[sample_rate*8]=S_longtext[N_mod];

	for	(preamb_i=0;preamb_i<N_mod;preamb_i++)
	{
		/*complex_preamb[preamb_i+sample_rate*8]=S_longtext[preamb_i+64-N_mod];*/
		complex_preamb[preamb_i]=S_longtext[preamb_i+64-N_mod];// GI2
	}
	
	for (preamb_i=0;double(preamb_i)/(sample_rate) < T_tr/2;preamb_i++)
	{
		//complex_preamb[preamb_i+sample_rate*8]=complex (pow(sin(PI/2*(0.5+preamb_i/(T_tr*sample_rate))),2),0.0)*complex_preamb[preamb_i+sample_rate*8];
		//complex_preamb[sample_rate*8*2-preamb_i]=complex (pow(sin(PI/2*(0.5+preamb_i/(T_tr*sample_rate))),2),0.0)*complex_preamb[sample_rate*8*2-preamb_i]; ////序号都要改，去掉短训练序列
		complex_preamb[preamb_i]=std::complex<double>  (pow(sin(PI/2*(0.5+preamb_i/(T_tr*sample_rate))),2),0.0)*complex_preamb[preamb_i];
		complex_preamb[sample_rate*8-preamb_i]=std::complex<double>  (pow(sin(PI/2*(0.5+preamb_i/(T_tr*sample_rate))),2),0.0)*complex_preamb[sample_rate*8-preamb_i]; ////序号都要改，去掉短训练序列
	
	}
	
	//complex_preamb[sample_rate*8] =complex_preamb[sample_rate*8]+ S_addpoint;//干什么用的啊？？ 如果没有短训练序列，那么S_addpoint是否可以不要
	//S_addpoint=complex_preamb[sample_rate*8*2];	
	//S_addpoint=complex_preamb[sample_rate*8];	
}

void  tx_11g_param::Produce_PSDU_mod3(char char_datain[],std::complex<double>  complex_dataout[],int * Q_pinter,int data_length)
{	
	int Test_data_length=sizeof(Test_data)/sizeof(Test_data[0]);//字节长度

	  //  ofdm_param();//输入需要传输的方式
	  //  tx_param(Test_data_length);


		//preamble部分，只有长训练序列和保护间隔，没有短训练序列，长度要改！！！
		//int S_preamb_length=Sample_Rate*16+1;  // pream part 长度
		int S_preamb_length=Sample_Rate*16/2+1;  // pream part 长度
		//if(S_preambpart == NULL)
		S_preambparta=new std::complex<double>  [S_preamb_length];//preamb  定义complex型 数组
		memset(S_preambparta, (0.0,0.0),S_preamb_length); //将S_preambpart全部初始化为（0.0，0.0）
		Produce_training_sequence_mod3(S_preambparta);

		int S_singal_length=81;//为什么都要加1 呢
		if(S_singalpart == NULL)
		S_singalpart = new std::complex<double>  [S_singal_length];//SINGAL
		memset(S_singalpart, (0.0,0.0),S_singal_length);
		Produce_singal_mod2(S_singalpart,&index_q,Test_data_length);// 输入的Test_data_length 不包括6us的信号拓展长度。也即120个比特
		
		int S_data_length=80*n_sym+1;//为什么都要加1 呢
		if(S_datapart == NULL)
		S_datapart = new std::complex<double>  [S_data_length] ;
		memset(S_datapart, (0.0,0.0),S_data_length);
		Produce_data_mod2(Test_data,S_datapart,&index_q,Test_data_length);
		
		int S_PPDU_length=S_data_length+S_singal_length+S_preamb_length-2+120;//减2是为了什么呢
		if(S_PPDU == NULL)
		S_PPDU= new std::complex<double>  [S_PPDU_length];
		Produce_PPDU_mod2(S_preambparta,S_singalpart,S_datapart,S_PPDU,S_preamb_length,S_singal_length,S_data_length);
		//6us 对应是 120bit长度bits signal extension
		for (int i= S_PPDU_length-1;i>S_PPDU_length-121;i--)
		{
			//S_PPDU[i].setValue(0.0,0.0);
			S_PPDU[i].real(0.0);
			S_PPDU[i].imag(0.0);
		}
		
		complex_dataout=S_PPDU;

		delete [] S_preambparta;
		delete [] S_singalpart;
		//delete [] S_datapart;
		delete [] S_PPDU;
}

void  tx_11g_param::Produce_PPDU_mod3(std::complex<double>  preambpart_in[],std::complex<double>  singalpart_in[],std::complex<double>  datapart_in[],std::complex<double>  PPDU_out[],int preamb_length,int singal_length,int data_length)
{
	int PPDU_i=0;

	for(PPDU_i=0;PPDU_i<preamb_length-1;PPDU_i++) PPDU_out[PPDU_i]=preambpart_in[PPDU_i];

	PPDU_out[preamb_length-1]=preambpart_in[preamb_length-1]+singalpart_in[0];

	for(PPDU_i=1;PPDU_i<singal_length-1;PPDU_i++) PPDU_out[PPDU_i+preamb_length-1]=singalpart_in[PPDU_i];

	PPDU_out[preamb_length+singal_length-2]=singalpart_in[singal_length-1]+datapart_in[0];

	for(PPDU_i=1;PPDU_i<data_length;PPDU_i++) PPDU_out[PPDU_i+preamb_length+singal_length-2]=datapart_in[PPDU_i];
}


void tx_11g_param::tx_param_gb(Encoding e)
{
	switch(e)
	{
	case DBPSK_1M:
		//速率可选 _1Mbps,_2Mbps,_55Mbps,_11Mbps
		data_rate = _1Mbps;
		//preamble类型可选  shortPreamble，longPreamble
		//preamble_type = longPreamble;
		//调制方式 DBPSK_1Mbps，DQPSK_2Mbps，CCK55_55Mbps，PBCC55_55Mbps，CCK11_11Mpbs，PBCC11_11Mbps
		modulation_type = DBPSK_1Mbps; 
		//扰码 ON,OFF,Preamble_only
		//scrambler_state = ON;
		break;
	case  DQPSK_2M:
		//速率可选 _1Mbps,_2Mbps,_55Mbps,_11Mbps
		data_rate = _2Mbps;
		//preamble类型可选  shortPreamble，longPreamble
		//preamble_type = longPreamble;
		//调制方式 DBPSK_1Mbps，DQPSK_2Mbps，CCK55_55Mbps，PBCC55_55Mbps，CCK11_11Mpbs，PBCC11_11Mbps
		modulation_type = DQPSK_2Mbps; 
		//扰码 ON,OFF,Preamble_only
		//scrambler_state = ON;

		break;
	case   CCK_5_5M:
		//速率可选 _1Mbps,_2Mbps,_55Mbps,_11Mbps
		data_rate = _55Mbps;
		//preamble类型可选  shortPreamble，longPreamble
		//preamble_type = longPreamble;
		//调制方式 DBPSK_1Mbps，DQPSK_2Mbps，CCK55_55Mbps，PBCC55_55Mbps，CCK11_11Mpbs，PBCC11_11Mbps
		modulation_type = CCK55_55Mbps; 
		//扰码 ON,OFF,Preamble_only
		//scrambler_state = ON;

		break;
	case CCK_11M:
		//速率可选 _1Mbps,_2Mbps,_55Mbps,_11Mbps
		data_rate = _11Mbps;
		//preamble类型可选  shortPreamble，longPreamble
		//preamble_type = longPreamble;
		//调制方式 DBPSK_1Mbps，DQPSK_2Mbps，CCK55_55Mbps，PBCC55_55Mbps，CCK11_11Mpbs，PBCC11_11Mbps
		modulation_type = CCK11_11Mpbs; 
		//扰码 ON,OFF,Preamble_only
		//scrambler_state = ON;

		break;
	case   PBCC_5_5M:
		//速率可选 _1Mbps,_2Mbps,_55Mbps,_11Mbps
		data_rate = _55Mbps;
		//preamble类型可选  shortPreamble，longPreamble
		//preamble_type = longPreamble;
		//调制方式 DBPSK_1Mbps，DQPSK_2Mbps，CCK55_55Mbps，PBCC55_55Mbps，CCK11_11Mpbs，PBCC11_11Mbps
		modulation_type =PBCC55_55Mbps; 
		//扰码 ON,OFF,Preamble_only
		//scrambler_state = ON;

		break;
	case  PBCC_11M:
		//速率可选 _1Mbps,_2Mbps,_55Mbps,_11Mbps
		data_rate = _11Mbps;
		//preamble类型可选  shortPreamble，longPreamble
		//preamble_type = longPreamble;
		//调制方式 DBPSK_1Mbps，DQPSK_2Mbps，CCK55_55Mbps，PBCC55_55Mbps，CCK11_11Mpbs，PBCC11_11Mbps
		modulation_type =PBCC11_11Mbps; 
		//扰码 ON,OFF,Preamble_only
		//scrambler_state = ON;

		break;
	case PBCC_22M:
		//速率可选 _1Mbps,_2Mbps,_55Mbps,_11Mbps
		data_rate = _22Mbps;
		//preamble类型可选  shortPreamble，longPreamble
		//preamble_type = longPreamble;
		//调制方式 DBPSK_1Mbps，DQPSK_2Mbps，CCK55_55Mbps，PBCC55_55Mbps，CCK11_11Mpbs，PBCC11_11Mbps
		modulation_type =PBCC22_22Mbps; 
		//扰码 ON,OFF,Preamble_only
		//scrambler_state = ON;
		break;
	case PBCC_33M:
		//速率可选 _1Mbps,_2Mbps,_55Mbps,_11Mbps
		data_rate = _33Mbps;
		//preamble类型可选  shortPreamble，longPreamble
		//preamble_type = longPreamble;
		//调制方式 DBPSK_1Mbps，DQPSK_2Mbps，CCK55_55Mbps，PBCC55_55Mbps，CCK11_11Mpbs，PBCC11_11Mbps
		modulation_type =PBCC33_33Mbps; 
		//扰码 ON,OFF,Preamble_only
		//scrambler_state = ON;
		break;
	default:
		//assert(false);
		break;
	}


}



void  tx_11g_param::Run(vector<int>src,int data_bytelen)
{	
	//OFDM/OFDM-DSSS模式,信源数据转为char型
	char *src_g = new char[data_bytelen];
	for (int k=0;k<data_bytelen;k++)
	{
		src_g[k] = 0x00;
	}
	int data_inlen = data_bytelen*8;
	int g_BinArr[8] = {128,64,32,16,8,4,2,1}; //2的次幂  
	//vector<int> src 转存成char *src_a
	int iByteNo = 0;   //字节序号  
	int iBitInByte = 0;  //字节里的比特序号(0-7) 
	for (int i = 0; i < data_inlen; i++)
	{
		iByteNo = i/8;    
		iBitInByte = i%8;  
		src_g[iByteNo] += src[i]*g_BinArr[iBitInByte];
	}

	int Test_data_length =data_bytelen;

	//对DSSS模式，信源数据不需要转换类型
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
	preamble_type = GprotocolConfig.preamble_type;
	data_rate = GprotocolConfig.data_rate;
	modulation_type =GprotocolConfig.modulation_type;
	scrambler_state = GprotocolConfig.scrambler_state;

	tx_param_gb(GprotocolConfig.EZOG_Encoding);
	ofdm_param(GprotocolConfig.EZOG_Encoding);//输入需要传输的方式	
	tx_param(Test_data_length);


	//txvector 参数设置  放到构造函数中
	/*tx_11g_param txvector;
	txvector.data_rate = _1Mbps;
	txvector.modulation_type = DBPSK_1Mbps; 
	txvector.preamble_type = longPreamble;
	txvector.scrambler_type = DSSS_scrambler;
	txvector.scrambler_state = OFF;
	txvector.PayloadData_size_bytes = 1;*/
	//int data_size = 8*(txvector.PayloadData_size_bytes + FCS_size_bytes + MACHeader_size_bytes);
	////生成数据序列
	//srand(time(NULL));
	//for(int i=0;i<data_size;i++)
	//{		
	//	txvector.Data.push_back(rand()%2);			
	//}




	 //***********************************************************************************************************
	 
	// DSSS modulaiton
	 if ((data_rate == _1Mbps)||(data_rate == _2Mbps)||(data_rate == _55Mbps)
		 ||(data_rate == _11Mbps)||(data_rate == _22Mbps)||(data_rate==_33Mbps))
	 {		
		 //tx_param_gb(GprotocolConfig.EZOG_Encoding);
		// FCS_size_bytes = 4;
		// int data_size = 8*(PayloadData_size_bytes + FCS_size_bytes + MACHeader_size_bytes);//FCS_size_bytes为何变为零了

		 //PayloadData_size_bytes=10;
		 //data_size = 8*PayloadData_size_bytes;
	
		GprotocolConfig.dt=1 / 11e6 ;
		 //preamble bit
		if (preamble_type == 0)
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
		header_bit=Produce_header_bit(S_header_length);

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
		//std::complex<double>  *S_preambpart=new std::complex<double>  [S_preamb_length];
		S_preambpart=new std::complex<double> [S_preamb_length];
		preamble_last_symbol = new std::complex<double> [1];
		memset(S_preambpart, (0.0,0.0),S_preamb_length);//有问题！！！边界 or 赋值问题
		//Produce_preamb_mod1(S_preambpart);
		Produce_preamb_mod1(S_preambpart,PPDU_scrambled,preamble_last_symbol);

		//header symbol		
		if (preamble_type == 1)
			S_header_length = S_header_length*11;
		else
			S_header_length = S_header_length*11/2;
		if(S_headerpart == NULL)
		S_headerpart = new std::complex<double>  [S_header_length];
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
		//Produce_header_mod1(S_headerpart);
		Produce_header_mod1(S_headerpart,PPDU_scrambled,theta0,header_last_symbol,header_last_chip);//传入S_preambpart判断最后一个符号的相位		

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
		S_data_length = 11*data_size;//按照最长内存空间，预留内存 DBPSK+barker
		//if (modulation_type == 0)   //DBPSK 
		//	S_data_length = 11*data_size; 
	
		//else if(modulation_type == 1)  //DQPSK 
		//	S_data_length = 11*data_size/2; 

		//else if(modulation_type == 2)  //CCK5.5
		//	S_data_length = 2*data_size; 
		//
		//else if(modulation_type == 3)  //PBCC5.5	
		//  S_data_length = 2*(data_size+8); 
	
		//else if(modulation_type == 4)  //CCK11	
		//	S_data_length = data_size; 
	
		//else if(modulation_type == 5)  //PBCC11
		//	 S_data_length = (data_size+8); 

		//else if(modulation_type == 6)  //PBCC22	
		//	S_data_length = (data_size+8); //需要修改具体正确的值
	
		//else if(modulation_type == 7)  //PBCC33
		//	 S_data_length = (data_size+8); //需要修改正确的值

		//else 
		//	cout<<"Error modulation!\n";

		if(S_datapart == NULL)
		S_datapart = new std::complex<double>  [S_data_length] ;
		memset(S_datapart, (0.0,0.0),S_data_length);
		Produce_PSDU_mod1(S_datapart,PPDU_scrambled,theta1,theta2);
		//判断有多少个没有意义的symbol
		int temp_len = 0;
		for (int i = 0;i < S_data_length;i++)
		{
			if ((S_datapart[i].real() == 0) && (S_datapart[i].imag() == 0))		
			{
				temp_len = i;
				break;
			}	
		}

		//PPDU
		if (temp_len==0)
		//if(1)
		{
			S_PPDU_length=S_data_length+S_header_length+S_preamb_length;//1Mbps
			S_datapart_f = new std::complex<double>[S_data_length];
			memset(S_datapart_f, (0.0,0.0),S_data_length);
			for (int i = 0;i < S_data_length; i++)
			{
				S_datapart_f[i].real(S_datapart[i].real());
				S_datapart_f[i].imag(S_datapart[i].imag());
			}
			if(S_PPDU == NULL)
				S_PPDU= new std::complex<double> [S_PPDU_length];  
			Produce_PPDU_mod1(S_preambpart,S_headerpart,S_datapart_f,S_PPDU,S_preamb_length,S_header_length,S_data_length);

			complex<double> temp(+0.7071,+0.7071);
			//complex<double> temp(+0.5,+0.866);
			for(int i=0;i<S_PPDU_length;i++){
				S_PPDU[i] = S_PPDU[i]*temp;
			}
		}
		else
		{
			S_PPDU_length=temp_len+S_header_length+S_preamb_length;
			S_datapart_f = new std::complex<double>[temp_len];
			memset(S_datapart_f, (0.0,0.0),temp_len);
			for (int i = 0;i < temp_len; i++)
			{
				S_datapart_f[i].real(S_datapart[i].real());
				S_datapart_f[i].imag(S_datapart[i].imag());
			}
			if(S_PPDU == NULL)
				S_PPDU= new std::complex<double> [S_PPDU_length];  
			Produce_PPDU_mod1(S_preambpart,S_headerpart,S_datapart_f,S_PPDU,S_preamb_length,S_header_length,temp_len);
			if(GprotocolConfig.EZOG_Encoding!=PBCC_11M && GprotocolConfig.EZOG_Encoding!=PBCC_5_5M && GprotocolConfig.EZOG_Encoding!=PBCC_22M && GprotocolConfig.EZOG_Encoding!=PBCC_33M){
			    complex<double> temp(+0.7071,+0.7071);
			    //complex<double> temp(+0.5,+0.866);
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

		delete [] S_preambpart;
		delete [] S_headerpart;
		delete [] S_datapart;
		delete []S_datapart_f;
	 }
//***********************************************************************************************************
	 
	 // OFDM modulation
	 else if (((data_rate == _6Mbps)||(data_rate == _9Mbps)||(data_rate == _12Mbps)
		 ||(data_rate == _18Mbps)||(data_rate == _24Mbps)||(data_rate==_36Mbps)
		 ||(data_rate == _48Mbps)||(data_rate == _54Mbps))&&(preamble_type == OFDMPreamble ))
	 {		 
		 //int Test_data_length=sizeof(Test_data)/sizeof(Test_data[0]);
		 //ofdm_param(GprotocolConfig.EZOG_Encoding);//输入需要传输的方式	
		 //tx_param(Test_data_length);
		GprotocolConfig.dt = 1 / 20e6 ;
		S_preamb_length=Sample_Rate*16+1;  // pream part 长度
		S_preambpart=new std::complex<double>  [S_preamb_length];//preamb  定义std::complex<double> 型 数组
		memset(S_preambpart, (0.0,0.0),S_preamb_length); //将S_preambpart全部初始化为（0.0，0.0）
		Produce_preamb_mod2(S_preambpart);

		S_singal_length=81;
		S_singalpart = new std::complex<double>  [S_singal_length];//SINGAL
		memset(S_singalpart, (0.0,0.0),S_singal_length);
		Produce_singal_mod2(S_singalpart,&index_q,Test_data_length);

		S_data_length=80*n_sym+1;
		S_datapart = new std::complex<double>  [S_data_length] ;
		memset(S_datapart, (0.0,0.0),S_data_length);
		Produce_data_mod2(Test_data,S_datapart,&index_q,Test_data_length);

		S_PPDU_length=S_data_length+S_singal_length+S_preamb_length-2+120;
		S_PPDU= new std::complex<double>  [S_PPDU_length];
		Produce_PPDU_mod2(S_preambpart,S_singalpart,S_datapart,S_PPDU,S_preamb_length,S_singal_length,S_data_length);
		//6 bits signal extension
		for (int i= S_PPDU_length-1;i>S_PPDU_length-121;i--)
		{
			S_PPDU[i].real(0.0);
			S_PPDU[i].imag(0.0);
		}
		S_PPDU_length = S_PPDU_length-120;
		
		delete [] S_preambpart;
		delete [] S_singalpart;
		delete [] S_datapart;
	//	delete [] S_PPDU;
	 }
 //***********************************************************************************************************

     // DSSS-OFDM modulation
	 else if(((data_rate == _6Mbps)||(data_rate == _9Mbps)||(data_rate == _12Mbps)
		 ||(data_rate == _18Mbps)||(data_rate == _24Mbps)||(data_rate==_36Mbps)
		 ||(data_rate == _48Mbps)||(data_rate == _54Mbps)||(data_rate == _3Mbps))&&(preamble_type != OFDMPreamble ))
	 {

		// PPDU_produce_mod3(S_PPDU_3,txvector) 

		// FCS_size_bytes = 4;
		//int data_size = 8*(PayloadData_size_bytes + FCS_size_bytes + MACHeader_size_bytes);	

		//int Test_data_length = data_size;
		//int Test_data_length = sizeof(Test_data)/sizeof(Test_data[0]);
		//ofdm_param(GprotocolConfig.EZOG_Encoding);//输入需要传输的方式
	 //   tx_param(Test_data_length);
		
		//PayloadData_size_bytes=10;
		//data_size = 8*PayloadData_size_bytes;
		GprotocolConfig.dt = 1 / 20e6 ;//存疑
		//preamble bit
		if (preamble_type == 0)
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
		data_rate=_3Mbps;//参见协议
		header_bit=Produce_header_bit(S_header_length);

		//PPDU before scrambler
		int Preamble_header_length = S_preamb_length+S_header_length;
		vector<int> Preamble_header_bit;
		Preamble_header_bit.resize(Preamble_header_length,0);

		vector<int> Preamble_header_scrambled;
		Preamble_header_scrambled.resize(Preamble_header_length,0);

		for(int i=0;i<S_preamb_length;i++)
		{
			Preamble_header_bit[i]=preamble_bit[i];
		}

		for (int i=0;i<S_header_length;i++)
		{
			Preamble_header_bit[i+S_preamb_length]=header_bit[i];
		};

		Preamble_header_scrambled = scrambler(Preamble_header_bit);

		//preamble symbol
		S_preamb_length *= 11;
		S_preambpart=new std::complex<double> [S_preamb_length];
		preamble_last_symbol = new std::complex<double> [1];
		memset(S_preambpart, (0.0,0.0),S_preamb_length);//有问题！！！边界 or 赋值问题
		Produce_preamb_mod1(S_preambpart,Preamble_header_scrambled,preamble_last_symbol);

		//header symbol		
		if (preamble_type == 1)
			S_header_length = S_header_length*11;
		else
			S_header_length = S_header_length*11/2;
		if(S_headerpart == NULL)
			S_headerpart = new std::complex<double>  [S_header_length];
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
		//Produce_header_mod1(S_headerpart);
		Produce_header_mod1(S_headerpart,Preamble_header_scrambled,theta0,header_last_symbol,header_last_chip);//传入S_preambpart判断最后一个符号的相位		

		////preamb, the same with DSSS
		//int S_preamb_length;
		//if (preamble_type == 0)
		//	S_preamb_length= 72;
		//else
		//	S_preamb_length= 144;
		//S_preamb_length *= 11;
		//std::complex<double>  *S_preambpart=new std::complex<double>  [S_preamb_length];
		//memset(S_preambpart, (0.0,0.0),S_preamb_length);
		//Produce_preamb_mod1(S_preambpart);
		//Produce_preamb_mod1(S_preambpart,PPDU_scrambled,preamble_last_symbol); 

		////header, similar to mod1
		//int S_header_length = 48;
		//if (preamble_type == 1)
		//	S_header_length = S_header_length*11;
		//else
		//	S_header_length = S_header_length*11/2;
		//std::complex<double>  *S_headerpart = new std::complex<double>  [S_header_length];
		//memset(S_headerpart, (0.0,0.0),S_header_length);
		//Produce_header_mod3(S_headerpart);


		//OFDM 部分  改写11a得到
		int S_data_length=80*(n_sym+2+1)+1+120;// 这里的OFDM符号 包括 2长训练序列 ofdm+1个signal ofdm +data部分的n_sym 个 ofdm  这里的数据和第二个模式的数据一致
		std::complex<double>  *S_datapart = new std::complex<double>  [S_data_length] ;
		memset(S_datapart, (0.0,0.0),S_data_length);
		Produce_PSDU_mod3(Test_data,S_datapart,&index_q,Test_data_length);
		display(S_datapart,S_data_length);

		S_PPDU_length=S_data_length+S_header_length+S_preamb_length-2;
		S_PPDU= new std::complex<double>  [S_PPDU_length];
		Produce_PPDU_mod3(S_preambpart,S_headerpart,S_datapart,S_PPDU,S_preamb_length,S_header_length,S_data_length);
		//for (int i = 0;i < S_PPDU_length;i++)
		//	cout<<S_PPDU[i];
		
		//display(S_PPDU,S_PPDU_length);

	delete [] S_preambpart;
	delete [] S_headerpart;
	delete [] S_datapart;
	//delete [] S_PPDU;
 }

 vector<double> t;
 double Data_temp_real,Data_temp_imag;
 int i;
 for (i=0; i<S_PPDU_length; i++ )
 {
	 t.push_back(i*GprotocolConfig.dt);
 }  

 for (i=0; i<S_PPDU_length; i++ )
 {
	 Data_temp_real = cos(2*pi*GprotocolConfig.FrequencyOffset*t[i]);
	 Data_temp_imag = sin(2*pi*GprotocolConfig.FrequencyOffset*t[i]);
	 S_PPDU[i].real(S_PPDU[i].real()*Data_temp_real - S_PPDU[i].imag()*Data_temp_imag);
	 S_PPDU[i].imag(S_PPDU[i].real()*Data_temp_imag + S_PPDU[i].imag()*Data_temp_real);
 }  
 GprotocolConfig.length=S_PPDU_length;
 //信道
 if(GprotocolConfig.add_channel)
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
		 &RMS_Delay_Sample,GprotocolConfig.MAX_Delay_Sample,GprotocolConfig.NumOfTaps,Path_Average_Power,\
		 sizeof_Path_Delay,sizeof_Path_Average_Power);
	 double fd_max = GprotocolConfig.mobilespeed / 3.6 / (3e8) * GprotocolConfig.carrierfreq;
	 multipath_channel(data_r,data_i,fd_max,GprotocolConfig.NumOfTaps,SamplesPerFrame,\
		 ChangesPerFrame,TimeIndex,GprotocolConfig.dt,RndPhase,Path_Delay,\
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
 //过采滤波
 int over_ratio = GprotocolConfig.oversample_ratio;
 //int over_ratio = DataAndGraph->m_configGIndex->oversample_ratio;
 if(over_ratio >1)
 {
	 complex<double>* after_oversample = new complex<double>[S_PPDU_length*over_ratio];
	 complex<double> zero(0.0,0.0);
	 //complex<double>* after_oversample = new complex<double>[S_PPDU_length*over_ratio];
	 //complex<double> zero(0.0,0.0);
	 for(int i = 0; i < S_PPDU_length * over_ratio ; i++)
	 {
		 if( (i % over_ratio) == 0)
			 //after_oversample[i] = S_PPDU[ i/4 ];
		 {after_oversample[i] = S_PPDU[ i/over_ratio ];}
		 else
		 {after_oversample[i] = zero ;}
	 }
	 switch(GprotocolConfig.filter_para.filtertype)
	 {
	 case lpfilter:
		 {
			 vector<double> filter_coef = lowpass_filter(GprotocolConfig.filter_para.lppara.length,GprotocolConfig.filter_para.lppara.wn);
			 my_conv(after_oversample,filter_coef,S_PPDU_length * over_ratio);
			 S_PPDU = after_oversample;
			 break;
		 }
	 case gaussfilter:
		 {
			 vector<double> filter_coef = gauss_filter(GprotocolConfig.filter_para.gausspara.length,GprotocolConfig.filter_para.gausspara.BT);
			 my_conv(after_oversample,filter_coef,S_PPDU_length * over_ratio);
			 S_PPDU = after_oversample;
			 break;
		 }
	 case cosfilter:
		 {
			 vector<double> filter_coef = root_raised_cosine(GprotocolConfig.filter_para.cosinepara.alpha,GprotocolConfig.filter_para.cosinepara.length);
			 my_conv(after_oversample,filter_coef,S_PPDU_length * over_ratio);
			 S_PPDU = after_oversample;
			 break;
		 }
	 case userdefined:
		 {
			 my_conv(after_oversample,GprotocolConfig.filter_user,S_PPDU_length * over_ratio);
			 S_PPDU = after_oversample;
			 break;
		 }
	 }

 }
 int sig_len = S_PPDU_length * over_ratio;
 int sig_len_idle = sig_len;


 //加正交角度调整，IQ平衡增益
 double I_Q_max=0.0,I_data,Q_data=0.0;
 //double *I_gfsk=new double[sig_len];
 //double *Q_gfsk=new double[sig_len];
 double real_temp = 0;
 double imag_temp = 0;
 double IQ_gain = GprotocolConfig.IQ_gain;//注意与自己的对应
 double qAngleAD = GprotocolConfig.quan_angle_adjust;
 if(GprotocolConfig.add_channel == false)//不加信道的时候如果改正交角度调整或IQ平衡增益就会做如下公式
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
 void tx_11g_param::channel_initialize_1(double RndPhase[][12], double *Path_Delay, double *Path_Average_Amp, double *fore_data_pr, double *fore_data_pi, \
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
 void tx_11g_param::Jakes_kernel(double Path_Ampli,int NumOfFreq,int UpdateInterval,double fd_max,double* Phase,\
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
 void tx_11g_param::multipath_channel(vector<double> &InData_pr,vector<double> &InData_pi,\
	double fd_max,long NumOfTaps,\
	int SamplesPerFrame,int ChangesPerFrame,\
	int* TimeIndex,double dt,\
	double Phase[][12],double *Path_Delay,double *Path_Average_Amp,\
	vector<double> &OutData_pr,vector<double> &OutData_pi,\
	double *out_fading_pr,double *out_fading_pi,\
	double *fore_data_pr,double *fore_data_pi,\
	double *fading_indx)
{   
	dt=dt/GprotocolConfig.oversample_ratio;
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

		fading_r[tap]=fading_pr[0];
		fading_i[tap]=fading_pi[0];


		//// added in version 3
		//if(NumOfTaps>1)
		//{
		//	for(n=0;n<SamplesPerFrame;n++)
		//	{
		//		out_fading_pr[n*NumOfTaps+tap]=fading_pr[n];
		//		out_fading_pi[n*NumOfTaps+tap]=fading_pi[n];				
		//	}			
		//}

		//InData_Complex=false;
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
				//Output_Sub_path_pr[i]=InData_pr[i] * fading_pr[i]; 
				//Output_Sub_path_pi[i]=InData_pr[i] * fading_pi[i];
				Output_Sub_path_pr[i]=OutData_tmp_r[i] * fading_pr[i]; 
				Output_Sub_path_pi[i]=OutData_tmp_i[i] * fading_pi[i];
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
vector<double> tx_11g_param::lowpass_filter(int length,double Wn)
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
vector<double> tx_11g_param::gauss_filter(int length,double BT)
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
void tx_11g_param::my_conv( complex<double> * Data_in,vector<double> &filter_coef,int Data_in_len){
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
vector<double> tx_11g_param::root_raised_cosine(double alpha,int ntaps)
{
	double gain =1.0;
	ntaps |= 1;	// ensure that ntaps is odd
	double spb =  GprotocolConfig.oversample_ratio; // samples per bit/symbol这里是过采样率
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
void tx_11g_param::Clear()
{	
	delete []S_preambpart;
	delete []S_headerpart;
	delete []S_datapart;
	delete []S_PPDU;//清除内存
	delete []S_FFTATUOpower;
	delete []S_FFTspectrum;

}