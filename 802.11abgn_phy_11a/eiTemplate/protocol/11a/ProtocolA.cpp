// ProtocolEOOA.cpp : implementation file
//

#include "stdafx.h"
#include "ProtocolA.h"
#include <MATH.H>
#include "../../filterfunc.h"
//#include "vector.h"

#include <fstream>
#include <iostream>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProtocolA
//typedef std::complex<double> complex;

CProtocolA::CProtocolA()
{
	////测试信号段
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


	//Test_data[0] =0xff;Test_data[1]= 0xff;Test_data[2]= 0xff;Test_data[3]= 0xff;Test_data[4]= 0xff;
	//Test_data[5] =0xff;Test_data[6]= 0xff;Test_data[7]= 0xff;Test_data[8]= 0xff;Test_data[9]= 0xff;
	/*Test_data[0] = 0x80;
	Test_data[1] = 0x00;
	Test_data[2] = 0x00;
	Test_data[3] = 0x00;
	Test_data[4] = 0xff;
	Test_data[5] = 0xff;
	Test_data[6] = 0xff;
	Test_data[7] = 0xff;
	Test_data[8] = 0xff;
	Test_data[9] = 0xff;
	Test_data[10] = 0x64;
	Test_data[11] = 0x09;
	Test_data[12] = 0x80;
	Test_data[13] = 0x4d;
	Test_data[14] = 0x2b;
	Test_data[15] = 0xe0;
	Test_data[16] = 0x64;
	Test_data[17] = 0x09;
	Test_data[18] = 0x80;
	Test_data[19] = 0x4d;
	Test_data[20] = 0x2b;
	Test_data[21] = 0xe0;
	Test_data[22] = 0x80;
	Test_data[23] = 0x56;
	Test_data[24] = 0x51;
	Test_data[25] = 0x61;
	Test_data[26] = 0x56;
	Test_data[27] = 0x08;
	Test_data[28] = 0x00;
	Test_data[29] = 0x00;
	Test_data[30] = 0x00;
	Test_data[31] = 0x00;
	Test_data[32] = 0x64;
	Test_data[33] = 0x00;
	Test_data[34] = 0x11;
	Test_data[35] = 0x0c;
	Test_data[36] = 0x00;
	Test_data[37] = 0x06;
	Test_data[38] = 0x42;
	Test_data[39] = 0x55;
	Test_data[40] = 0x50;
	Test_data[41] = 0x54;
	Test_data[42] = 0x34;
	Test_data[43] = 0x31;
	Test_data[44] = 0x01;
	Test_data[45] = 0x08;
	Test_data[46] = 0x82;
	Test_data[47] = 0x84;
	Test_data[48] = 0x8b;
	Test_data[49] = 0x96;
	Test_data[50] = 0x12;
	Test_data[51] = 0x24;
	Test_data[52] = 0x48;
	Test_data[53] = 0x6c;
	Test_data[54] = 0x03;
	Test_data[55] = 0x01;
	Test_data[56] = 0x01;
	Test_data[57] = 0x32;
	Test_data[58] = 0x04;
	Test_data[59] = 0x0c;
	Test_data[60] = 0x18;
	Test_data[61] = 0x30;
	Test_data[62] = 0x60;
	Test_data[63] = 0x07;
	Test_data[64] = 0x06;
	Test_data[65] = 0x43;
	Test_data[66] = 0x4e;
	Test_data[67] = 0x20;
	Test_data[68] = 0x01;
	Test_data[69] = 0x0d;
	Test_data[70] = 0x14;
	Test_data[71] = 0x33;
	Test_data[72] = 0x08;
	Test_data[73] = 0x20;
	Test_data[74] = 0x01;
	Test_data[75] = 0x02;
	Test_data[76] = 0x03;
	Test_data[77] = 0x04;
	Test_data[78] = 0x05;
	Test_data[79] = 0x06;
	Test_data[80] = 0x07;
	Test_data[81] = 0x33;
	Test_data[82] = 0x08;
	Test_data[83] = 0x21;
	Test_data[84] = 0x05;
	Test_data[85] = 0x06;
	Test_data[86] = 0x07;
	Test_data[87] = 0x08;
	Test_data[88] = 0x09;
	Test_data[89] = 0x0a;
	Test_data[90] = 0x0b;
	Test_data[91] = 0x05;
	Test_data[92] = 0x04;
	Test_data[93] = 0x00;
	Test_data[94] = 0x01;
	Test_data[95] = 0x00;
	Test_data[96] = 0x00;
	Test_data[97] = 0xdd;
	Test_data[98] = 0x49;
	Test_data[99] = 0x00;
	Test_data[100] = 0x50;
	Test_data[101] = 0xf2;
	Test_data[102] = 0x04;
	Test_data[103] = 0x10;
	Test_data[104] = 0x4a;
	Test_data[105] = 0x00;
	Test_data[106] = 0x01;
	Test_data[107] = 0x10;
	Test_data[108] = 0x10;
	Test_data[109] = 0x44;
	Test_data[110] = 0x00;
	Test_data[111] = 0x01;
	Test_data[112] = 0x02;
	Test_data[113] = 0x10;
	Test_data[114] = 0x47;
	Test_data[115] = 0x00;
	Test_data[116] = 0x10;
	Test_data[117] = 0x28;
	Test_data[118] = 0x80;
	Test_data[119] = 0x28;
	Test_data[120] = 0x80;
	Test_data[121] = 0x28;
	Test_data[122] = 0x80;
	Test_data[123] = 0x18;
	Test_data[124] = 0x80;
	Test_data[125] = 0xa8;
	Test_data[126] = 0x80;
	Test_data[127] = 0x64;
	Test_data[128] = 0x09;
	Test_data[129] = 0x80;
	Test_data[130] = 0x4d;
	Test_data[131] = 0x2b;
	Test_data[132] = 0xe0;
	Test_data[133] = 0x10;
	Test_data[134] = 0x23;
	Test_data[135] = 0x00;
	Test_data[136] = 0x04;
	Test_data[137] = 0x52;
	Test_data[138] = 0x31;
	Test_data[139] = 0x43;
	Test_data[140] = 0x4d;
	Test_data[141] = 0x10;
	Test_data[142] = 0x11;
	Test_data[143] = 0x00;
	Test_data[144] = 0x0c;
	Test_data[145] = 0x58;
	Test_data[146] = 0x69;
	Test_data[147] = 0x61;
	Test_data[148] = 0x6f;
	Test_data[149] = 0x4d;
	Test_data[150] = 0x69;
	Test_data[151] = 0x52;
	Test_data[152] = 0x6f;
	Test_data[153] = 0x75;
	Test_data[154] = 0x74;
	Test_data[155] = 0x65;
	Test_data[156] = 0x72;
	Test_data[157] = 0x10;
	Test_data[158] = 0x3c;
	Test_data[159] = 0x00;
	Test_data[160] = 0x01;
	Test_data[161] = 0x01;
	Test_data[162] = 0x10;
	Test_data[163] = 0x49;
	Test_data[164] = 0x00;
	Test_data[165] = 0x06;
	Test_data[166] = 0x00;
	Test_data[167] = 0x37;
	Test_data[168] = 0x2a;
	Test_data[169] = 0x00;
	Test_data[170] = 0x01;
	Test_data[171] = 0x20;
	Test_data[172] = 0x2a;
	Test_data[173] = 0x01;
	Test_data[174] = 0x04;
	Test_data[175] = 0x2d;
	Test_data[176] = 0x1a;
	Test_data[177] = 0x6c;
	Test_data[178] = 0x00;
	Test_data[179] = 0x17;
	Test_data[180] = 0xff;
	Test_data[181] = 0xff;
	Test_data[182] = 0x00;
	Test_data[183] = 0x00;
	Test_data[184] = 0x00;
	Test_data[185] = 0x00;
	Test_data[186] = 0x00;
	Test_data[187] = 0x00;
	Test_data[188] = 0x00;
	Test_data[189] = 0x00;
	Test_data[190] = 0x00;
	Test_data[191] = 0x00;
	Test_data[192] = 0x00;
	Test_data[193] = 0x00;
	Test_data[194] = 0x00;
	Test_data[195] = 0x00;
	Test_data[196] = 0x00;
	Test_data[197] = 0x00;
	Test_data[198] = 0x00;
	Test_data[199] = 0x00;
	Test_data[200] = 0x00;
	Test_data[201] = 0x00;
	Test_data[202] = 0x00;
	Test_data[203] = 0x3d;
	Test_data[204] = 0x16;
	Test_data[205] = 0x01;
	Test_data[206] = 0x00;
	Test_data[207] = 0x04;
	Test_data[208] = 0x00;
	Test_data[209] = 0x00;
	Test_data[210] = 0x00;
	Test_data[211] = 0x00;
	Test_data[212] = 0x00;
	Test_data[213] = 0x00;
	Test_data[214] = 0x00;
	Test_data[215] = 0x00;
	Test_data[216] = 0x00;
	Test_data[217] = 0x00;
	Test_data[218] = 0x00;
	Test_data[219] = 0x00;
	Test_data[220] = 0x00;
	Test_data[221] = 0x00;
	Test_data[222] = 0x00;
	Test_data[223] = 0x00;
	Test_data[224] = 0x00;
	Test_data[225] = 0x00;
	Test_data[226] = 0x00;
	Test_data[227] = 0xdd;
	Test_data[228] = 0x1a;
	Test_data[229] = 0x00;
	Test_data[230] = 0x50;
	Test_data[231] = 0xf2;
	Test_data[232] = 0x01;
	Test_data[233] = 0x01;
	Test_data[234] = 0x00;
	Test_data[235] = 0x00;
	Test_data[236] = 0x50;
	Test_data[237] = 0xf2;
	Test_data[238] = 0x02;
	Test_data[239] = 0x02;
	Test_data[240] = 0x00;
	Test_data[241] = 0x00;
	Test_data[242] = 0x50;
	Test_data[243] = 0xf2;
	Test_data[244] = 0x02;
	Test_data[245] = 0x00;
	Test_data[246] = 0x50;
	Test_data[247] = 0xf2;
	Test_data[248] = 0x04;
	Test_data[249] = 0x01;
	Test_data[250] = 0x00;
	Test_data[251] = 0x00;
	Test_data[252] = 0x50;
	Test_data[253] = 0xf2;
	Test_data[254] = 0x02;
	Test_data[255] = 0x30;
	Test_data[256] = 0x18;
	Test_data[257] = 0x01;
	Test_data[258] = 0x00;
	Test_data[259] = 0x00;
	Test_data[260] = 0x0f;
	Test_data[261] = 0xac;
	Test_data[262] = 0x02;
	Test_data[263] = 0x02;
	Test_data[264] = 0x00;
	Test_data[265] = 0x00;
	Test_data[266] = 0x0f;
	Test_data[267] = 0xac;
	Test_data[268] = 0x02;
	Test_data[269] = 0x00;
	Test_data[270] = 0x0f;
	Test_data[271] = 0xac;
	Test_data[272] = 0x04;
	Test_data[273] = 0x01;
	Test_data[274] = 0x00;
	Test_data[275] = 0x00;
	Test_data[276] = 0x0f;
	Test_data[277] = 0xac;
	Test_data[278] = 0x02;
	Test_data[279] = 0x00;
	Test_data[280] = 0x00;
	Test_data[281] = 0xdd;
	Test_data[282] = 0x18;
	Test_data[283] = 0x00;
	Test_data[284] = 0x50;
	Test_data[285] = 0xf2;
	Test_data[286] = 0x02;
	Test_data[287] = 0x01;
	Test_data[288] = 0x01;
	Test_data[289] = 0x80;
	Test_data[290] = 0x00;
	Test_data[291] = 0x03;
	Test_data[292] = 0xa4;
	Test_data[293] = 0x00;
	Test_data[294] = 0x00;
	Test_data[295] = 0x27;
	Test_data[296] = 0xa4;
	Test_data[297] = 0x00;
	Test_data[298] = 0x00;
	Test_data[299] = 0x42;
	Test_data[300] = 0x43;
	Test_data[301] = 0x5e;
	Test_data[302] = 0x00;
	Test_data[303] = 0x62;
	Test_data[304] = 0x32;
	Test_data[305] = 0x2f;
	Test_data[306] = 0x00;
	Test_data[307] = 0x0b;
	Test_data[308] = 0x05;
	Test_data[309] = 0x01;
	Test_data[310] = 0x00;
	Test_data[311] = 0x65;
	Test_data[312] = 0x12;
	Test_data[313] = 0x7a;
	Test_data[314] = 0xdd;
	Test_data[315] = 0x07;
	Test_data[316] = 0x00;
	Test_data[317] = 0x0c;
	Test_data[318] = 0x43;
	Test_data[319] = 0x00;
	Test_data[320] = 0x00;
	Test_data[321] = 0x00;
	Test_data[322] = 0x00;
	Test_data[323] = 0x96;
	Test_data[324] = 0xf6;
	Test_data[325] = 0xf9;
	Test_data[326] = 0xf0;*/

Test_data[0] = 0x80;
Test_data[1] = 0x00;
Test_data[2] = 0x00;
Test_data[3] = 0x00;
Test_data[4] = 0xff;
Test_data[5] = 0xff;
Test_data[6] = 0xff;
Test_data[7] = 0xff;
Test_data[8] = 0xff;
Test_data[9] = 0xff;
Test_data[10] = 0xbc;
Test_data[11] = 0xd1;
Test_data[12] = 0x77;
Test_data[13] = 0x7d;
Test_data[14] = 0x40;
Test_data[15] = 0xf8;
Test_data[16] = 0xbc;
Test_data[17] = 0xd1;
Test_data[18] = 0x77;
Test_data[19] = 0x7d;
Test_data[20] = 0x40;
Test_data[21] = 0xf8;
Test_data[22] = 0x40;
Test_data[23] = 0x10;
Test_data[24] = 0xe7;
Test_data[25] = 0x80;
Test_data[26] = 0x11;
Test_data[27] = 0x01;
Test_data[28] = 0x00;
Test_data[29] = 0x00;
Test_data[30] = 0x00;
Test_data[31] = 0x00;
Test_data[32] = 0x64;
Test_data[33] = 0x00;
Test_data[34] = 0x21;
Test_data[35] = 0x05;
Test_data[36] = 0x00;
Test_data[37] = 0x06;
Test_data[38] = 0x43;
Test_data[39] = 0x45;
Test_data[40] = 0x54;
Test_data[41] = 0x43;
Test_data[42] = 0x34;
Test_data[43] = 0x31;
Test_data[44] = 0x01;
Test_data[45] = 0x08;
Test_data[46] = 0x82;
Test_data[47] = 0x84;
Test_data[48] = 0x8b;
Test_data[49] = 0x96;
Test_data[50] = 0x8c;
Test_data[51] = 0x12;
Test_data[52] = 0x98;
Test_data[53] = 0x24;
Test_data[54] = 0x03;
Test_data[55] = 0x01;
Test_data[56] = 0x01;
Test_data[57] = 0x05;
Test_data[58] = 0x04;
Test_data[59] = 0x00;
Test_data[60] = 0x01;
Test_data[61] = 0x00;
Test_data[62] = 0x00;
Test_data[63] = 0x20;
Test_data[64] = 0x01;
Test_data[65] = 0x00;
Test_data[66] = 0x2a;
Test_data[67] = 0x01;
Test_data[68] = 0x00;
Test_data[69] = 0x32;
Test_data[70] = 0x04;
Test_data[71] = 0xb0;
Test_data[72] = 0x48;
Test_data[73] = 0x60;
Test_data[74] = 0x6c;
Test_data[75] = 0xdd;
Test_data[76] = 0x18;
Test_data[77] = 0x00;
Test_data[78] = 0x50;
Test_data[79] = 0xf2;
Test_data[80] = 0x02;
Test_data[81] = 0x01;
Test_data[82] = 0x01;
Test_data[83] = 0x03;
Test_data[84] = 0x00;
Test_data[85] = 0x03;
Test_data[86] = 0xa4;
Test_data[87] = 0x00;
Test_data[88] = 0x00;
Test_data[89] = 0x27;
Test_data[90] = 0xa4;
Test_data[91] = 0x00;
Test_data[92] = 0x00;
Test_data[93] = 0x42;
Test_data[94] = 0x43;
Test_data[95] = 0x5e;
Test_data[96] = 0x00;
Test_data[97] = 0x62;
Test_data[98] = 0x32;
Test_data[99] = 0x2f;
Test_data[100] = 0x00;
Test_data[101] = 0xdd;
Test_data[102] = 0x09;
Test_data[103] = 0x00;
Test_data[104] = 0x03;
Test_data[105] = 0x7f;
Test_data[106] = 0x01;
Test_data[107] = 0x01;
Test_data[108] = 0x00;
Test_data[109] = 0x00;
Test_data[110] = 0xff;
Test_data[111] = 0x7f;
Test_data[112] = 0xdd;
Test_data[113] = 0x0e;
Test_data[114] = 0x00;
Test_data[115] = 0x50;
Test_data[116] = 0xf2;
Test_data[117] = 0x04;
Test_data[118] = 0x10;
Test_data[119] = 0x4a;
Test_data[120] = 0x00;
Test_data[121] = 0x01;
Test_data[122] = 0x10;
Test_data[123] = 0x10;
Test_data[124] = 0x44;
Test_data[125] = 0x00;
Test_data[126] = 0x01;
Test_data[127] = 0x01;
Test_data[128] = 0xc2;
Test_data[129] = 0x84;
Test_data[130] = 0xfa;
Test_data[131] = 0xe8;

    /*Test_data[0] = 0x80;
    Test_data[1] = 0x00;
    Test_data[2] = 0x00;
    Test_data[3] = 0x00;
    Test_data[4] = 0xff;
    Test_data[5] = 0xff;
    Test_data[6] = 0xff;
    Test_data[7] = 0xff;
    Test_data[8] = 0xff;
    Test_data[9] = 0xff;
    Test_data[10] = 0x9c;
    Test_data[11] = 0x1c;
    Test_data[12] = 0x12;
Test_data[13] = 0x51;
Test_data[14] = 0x8e;
Test_data[15] = 0xc0;
Test_data[16] = 0x9c;
Test_data[17] = 0x1c;
Test_data[18] = 0x12;
Test_data[19] = 0x51;
Test_data[20] = 0x8e;
Test_data[21] = 0xc0;
Test_data[22] = 0x80;
Test_data[23] = 0x50;
Test_data[24] = 0x80;
Test_data[25] = 0x61;
Test_data[26] = 0xec;
Test_data[27] = 0x23;
Test_data[28] = 0x3a;
Test_data[29] = 0x00;
Test_data[30] = 0x00;
Test_data[31] = 0x00;
Test_data[32] = 0x64;
Test_data[33] = 0x00;
Test_data[34] = 0x21;
Test_data[35] = 0x04;
Test_data[36] = 0x00;
Test_data[37] = 0x06;
Test_data[38] = 0x42;
Test_data[39] = 0x55;
Test_data[40] = 0x50;
Test_data[41] = 0x54;
Test_data[42] = 0x2d;
Test_data[43] = 0x31;
Test_data[44] = 0x01;
Test_data[45] = 0x07;
Test_data[46] = 0x92;
Test_data[47] = 0x98;
Test_data[48] = 0xa4;
Test_data[49] = 0x30;
Test_data[50] = 0x48;
Test_data[51] = 0x60;
Test_data[52] = 0x6c;
Test_data[53] = 0x03;
Test_data[54] = 0x01;
Test_data[55] = 0x01;
Test_data[56] = 0x05;
Test_data[57] = 0x04;
Test_data[58] = 0x00;
Test_data[59] = 0x01;
Test_data[60] = 0x00;
Test_data[61] = 0x00;
Test_data[62] = 0x2a;
Test_data[63] = 0x01;
Test_data[64] = 0x00;
Test_data[65] = 0x2d;
Test_data[66] = 0x1a;
Test_data[67] = 0xed;
Test_data[68] = 0x11;
Test_data[69] = 0x1b;
Test_data[70] = 0xff;
Test_data[71] = 0xff;
Test_data[72] = 0x00;
Test_data[73] = 0x00;
Test_data[74] = 0x00;
Test_data[75] = 0x00;
Test_data[76] = 0x00;
Test_data[77] = 0x00;
Test_data[78] = 0x00;
Test_data[79] = 0x00;
Test_data[80] = 0x00;
Test_data[81] = 0x00;
Test_data[82] = 0x00;
Test_data[83] = 0x00;
Test_data[84] = 0x00;
Test_data[85] = 0x00;
Test_data[86] = 0x00;
Test_data[87] = 0x00;
Test_data[88] = 0x00;
Test_data[89] = 0x00;
Test_data[90] = 0x00;
Test_data[91] = 0x00;
Test_data[92] = 0x00;
Test_data[93] = 0x3d;
Test_data[94] = 0x16;
Test_data[95] = 0x01;
Test_data[96] = 0x00;
Test_data[97] = 0x19;
Test_data[98] = 0x00;
Test_data[99] = 0x00;
Test_data[100] = 0x00;
Test_data[101] = 0x00;
Test_data[102] = 0x00;
Test_data[103] = 0x00;
Test_data[104] = 0x00;
Test_data[105] = 0x00;
Test_data[106] = 0x00;
Test_data[107] = 0x00;
Test_data[108] = 0x00;
Test_data[109] = 0x00;
Test_data[110] = 0x00;
Test_data[111] = 0x00;
Test_data[112] = 0x00;
Test_data[113] = 0x00;
Test_data[114] = 0x00;
Test_data[115] = 0x00;
Test_data[116] = 0x00;
Test_data[117] = 0x7f;
Test_data[118] = 0x08;
Test_data[119] = 0x00;
Test_data[120] = 0x00;
Test_data[121] = 0x08;
Test_data[122] = 0x00;
Test_data[123] = 0x00;
Test_data[124] = 0x00;
Test_data[125] = 0x00;
Test_data[126] = 0x00;
Test_data[127] = 0xdd;
Test_data[128] = 0x18;
Test_data[129] = 0x00;
Test_data[130] = 0x50;
Test_data[131] = 0xf2;
Test_data[132] = 0x02;
Test_data[133] = 0x01;
Test_data[134] = 0x01;
Test_data[135] = 0x80;
Test_data[136] = 0x00;
Test_data[137] = 0x03;
Test_data[138] = 0xa4;
Test_data[139] = 0x00;
Test_data[140] = 0x00;
Test_data[141] = 0x27;
Test_data[142] = 0xa4;
Test_data[143] = 0x00;
Test_data[144] = 0x00;
Test_data[145] = 0x42;
Test_data[146] = 0x43;
Test_data[147] = 0x5e;
Test_data[148] = 0x00;
Test_data[149] = 0x62;
Test_data[150] = 0x32;
Test_data[151] = 0x2f;
Test_data[152] = 0x00;
Test_data[153] = 0xdd;
Test_data[154] = 0x07;
Test_data[155] = 0x00;
Test_data[156] = 0x0b;
Test_data[157] = 0x86;
Test_data[158] = 0x01;
Test_data[159] = 0x04;
Test_data[160] = 0x08;
Test_data[161] = 0x12;
Test_data[162] = 0x1a;
Test_data[163] = 0x82;
Test_data[164] = 0x23;
Test_data[165] = 0x40;*/

/*
Test_data[0] = 0x00;
Test_data[1] = 0x00;
Test_data[2] = 0x00;
Test_data[3] = 0x00;
Test_data[4] = 0x00;
Test_data[5] = 0x00;
Test_data[6] = 0x00;
Test_data[7] = 0x00;
Test_data[8] = 0x00;
Test_data[9] = 0x00;
Test_data[10] = 0x00;
Test_data[11] = 0x00;
Test_data[12] = 0x00;
Test_data[13] = 0x00;
Test_data[14] = 0x00;
Test_data[15] = 0x00;
Test_data[16] = 0x00;
Test_data[17] = 0x00;
Test_data[18] = 0x00;
Test_data[19] = 0x00;
Test_data[20] = 0x00;
Test_data[21] = 0x00;
Test_data[22] = 0x00;
Test_data[23] = 0x00;
Test_data[24] = 0x00;
Test_data[25] = 0x00;
Test_data[26] = 0x00;
Test_data[27] = 0x00;
Test_data[28] = 0x00;
Test_data[29] = 0x00;
Test_data[30] = 0x00;
Test_data[31] = 0x00;
Test_data[32] = 0x00;
Test_data[33] = 0x00;
Test_data[34] = 0x00;
Test_data[35] = 0x00;
Test_data[36] = 0x00;
Test_data[37] = 0x00;
Test_data[38] = 0x00;
Test_data[39] = 0x00;
Test_data[40] = 0x00;
Test_data[41] = 0x00;
Test_data[42] = 0x00;
Test_data[43] = 0x00;
Test_data[44] = 0x00;
Test_data[45] = 0x00;
Test_data[46] = 0x00;
Test_data[47] = 0x00;
Test_data[48] = 0x00;
Test_data[49] = 0x00;
Test_data[50] = 0x00;
Test_data[51] = 0x00;
Test_data[52] = 0x00;
Test_data[53] = 0x00;
Test_data[54] = 0x00;
Test_data[55] = 0x00;
Test_data[56] = 0x00;
Test_data[57] = 0x00;
Test_data[58] = 0x00;
Test_data[59] = 0x00;
Test_data[60] = 0x00;
Test_data[61] = 0x00;
Test_data[62] = 0x00;
Test_data[63] = 0x00;
Test_data[64] = 0x00;
Test_data[65] = 0x00;
Test_data[66] = 0x00;
Test_data[67] = 0x00;
Test_data[68] = 0x00;
Test_data[69] = 0x00;
Test_data[70] = 0x00;
Test_data[71] = 0x00;
Test_data[72] = 0x00;
Test_data[73] = 0x00;
Test_data[74] = 0x00;
Test_data[75] = 0x00;
Test_data[76] = 0x00;
Test_data[77] = 0x00;
Test_data[78] = 0x00;
Test_data[79] = 0x00;
Test_data[80] = 0x00;
Test_data[81] = 0x00;
Test_data[82] = 0x00;
Test_data[83] = 0x00;
Test_data[84] = 0x00;
Test_data[85] = 0x00;
Test_data[86] = 0x00;
Test_data[87] = 0x00;
Test_data[88] = 0x00;
Test_data[89] = 0x00;
Test_data[90] = 0x00;
Test_data[91] = 0x00;
Test_data[92] = 0x00;
Test_data[93] = 0x00;
Test_data[94] = 0x00;
Test_data[95] = 0x00;
Test_data[96] = 0x00;
Test_data[97] = 0x00;
Test_data[98] = 0x00;
Test_data[99] = 0x00;
Test_data[100] = 0x00;
Test_data[101] = 0x00;
Test_data[102] = 0x00;
Test_data[103] = 0x00;
Test_data[104] = 0x00;
Test_data[105] = 0x00;
Test_data[106] = 0x00;
Test_data[107] = 0x00;
Test_data[108] = 0x00;
Test_data[109] = 0x00;
Test_data[110] = 0x00;
Test_data[111] = 0x00;
Test_data[112] = 0x00;
Test_data[113] = 0x00;
Test_data[114] = 0x00;
Test_data[115] = 0x00;
Test_data[116] = 0x00;
Test_data[117] = 0x00;
Test_data[118] = 0x00;
Test_data[119] = 0x00;
Test_data[120] = 0x00;
Test_data[121] = 0x00;
Test_data[122] = 0x00;
Test_data[123] = 0x00;
Test_data[124] = 0x00;
Test_data[125] = 0x00;
Test_data[126] = 0x00;
Test_data[127] = 0x00;
Test_data[128] = 0x00;
Test_data[129] = 0x00;
Test_data[130] = 0x00;
Test_data[131] = 0x00;
Test_data[132] = 0x00;
Test_data[133] = 0x00;
Test_data[134] = 0x00;
Test_data[135] = 0x00;
Test_data[136] = 0x00;
Test_data[137] = 0x00;
Test_data[138] = 0x00;
Test_data[139] = 0x00;
Test_data[140] = 0x00;
Test_data[141] = 0x00;
Test_data[142] = 0x00;
Test_data[143] = 0x00;
Test_data[144] = 0x00;
Test_data[145] = 0x00;
Test_data[146] = 0x00;
Test_data[147] = 0x00;
Test_data[148] = 0x00;
Test_data[149] = 0x00;
Test_data[150] = 0x00;
Test_data[151] = 0x00;
Test_data[152] = 0x00;
Test_data[153] = 0x00;
Test_data[154] = 0x00;
Test_data[155] = 0x00;
Test_data[156] = 0x00;
Test_data[157] = 0x00;
Test_data[158] = 0x00;
Test_data[159] = 0x00;
Test_data[160] = 0x00;
Test_data[161] = 0x00;
Test_data[162] = 0x00;
Test_data[163] = 0x00;
Test_data[164] = 0x00;
Test_data[165] = 0x00;
Test_data[166] = 0x00;
Test_data[167] = 0x00;
Test_data[168] = 0x00;
Test_data[169] = 0x00;
Test_data[170] = 0x00;
Test_data[171] = 0x00;
Test_data[172] = 0x00;
Test_data[173] = 0x00;
Test_data[174] = 0x00;
Test_data[175] = 0x00;
Test_data[176] = 0x00;
Test_data[177] = 0x00;
Test_data[178] = 0x00;
Test_data[179] = 0x00;
Test_data[180] = 0x00;
Test_data[181] = 0x00;
Test_data[182] = 0x00;
Test_data[183] = 0x00;
Test_data[184] = 0x00;
Test_data[185] = 0x00;
Test_data[186] = 0x00;
Test_data[187] = 0x00;
Test_data[188] = 0x00;
Test_data[189] = 0x00;
Test_data[190] = 0x00;
Test_data[191] = 0x00;
Test_data[192] = 0x00;
Test_data[193] = 0x00;
Test_data[194] = 0x00;
Test_data[195] = 0x00;
Test_data[196] = 0x00;
Test_data[197] = 0x00;
Test_data[198] = 0x00;
Test_data[199] = 0x00;
Test_data[200] = 0x00;
Test_data[201] = 0x00;
Test_data[202] = 0x00;
Test_data[203] = 0x00;
Test_data[204] = 0x00;
Test_data[205] = 0x00;
Test_data[206] = 0x00;
Test_data[207] = 0x00;
Test_data[208] = 0x00;
Test_data[209] = 0x00;
Test_data[210] = 0x00;
Test_data[211] = 0x00;
Test_data[212] = 0x00;
Test_data[213] = 0x00;
Test_data[214] = 0x00;
Test_data[215] = 0x00;
Test_data[216] = 0x00;
Test_data[217] = 0x00;
Test_data[218] = 0x00;
Test_data[219] = 0x00;
Test_data[220] = 0x00;
Test_data[221] = 0x00;
Test_data[222] = 0x00;
Test_data[223] = 0x00;
Test_data[224] = 0x00;
Test_data[225] = 0x00;
Test_data[226] = 0x00;
Test_data[227] = 0x00;
Test_data[228] = 0x00;
Test_data[229] = 0x00;
Test_data[230] = 0x00;
Test_data[231] = 0x00;
Test_data[232] = 0x00;
Test_data[233] = 0x00;
Test_data[234] = 0x00;
Test_data[235] = 0x00;
Test_data[236] = 0x00;
Test_data[237] = 0x00;
Test_data[238] = 0x00;
Test_data[239] = 0x00;
Test_data[240] = 0x00;
Test_data[241] = 0x00;
Test_data[242] = 0x00;
Test_data[243] = 0x00;
Test_data[244] = 0x00;
Test_data[245] = 0x00;
Test_data[246] = 0x00;
Test_data[247] = 0x00;
Test_data[248] = 0x00;
Test_data[249] = 0x00;
Test_data[250] = 0x00;
Test_data[251] = 0x00;
Test_data[252] = 0x00;
Test_data[253] = 0x00;
Test_data[254] = 0x00;
Test_data[255] = 0x00;
Test_data[256] = 0x00;
Test_data[257] = 0x00;
Test_data[258] = 0x00;
Test_data[259] = 0x00;
Test_data[260] = 0x00;
Test_data[261] = 0x00;
Test_data[262] = 0x00;
Test_data[263] = 0x00;
Test_data[264] = 0x00;
Test_data[265] = 0x00;
Test_data[266] = 0x00;
Test_data[267] = 0x00;
Test_data[268] = 0x00;
Test_data[269] = 0x00;
Test_data[270] = 0x00;
Test_data[271] = 0x00;
Test_data[272] = 0x00;
Test_data[273] = 0x00;
Test_data[274] = 0x00;
Test_data[275] = 0x00;
Test_data[276] = 0x00;
Test_data[277] = 0x00;
Test_data[278] = 0x00;
Test_data[279] = 0x00;
Test_data[280] = 0x00;
Test_data[281] = 0x00;
Test_data[282] = 0x00;
Test_data[283] = 0x00;
Test_data[284] = 0x00;
Test_data[285] = 0x00;
Test_data[286] = 0x00;
Test_data[287] = 0x00;
Test_data[288] = 0x00;
Test_data[289] = 0x00;
Test_data[290] = 0x00;
Test_data[291] = 0x00;
Test_data[292] = 0x00;
Test_data[293] = 0x00;
Test_data[294] = 0x00;
Test_data[295] = 0x00;
Test_data[296] = 0x00;
Test_data[297] = 0x00;
Test_data[298] = 0x00;
Test_data[299] = 0x00;
Test_data[300] = 0x00;
Test_data[301] = 0x00;
Test_data[302] = 0x00;
Test_data[303] = 0x00;
Test_data[304] = 0x00;
Test_data[305] = 0x00;
Test_data[306] = 0x00;
Test_data[307] = 0x00;
Test_data[308] = 0x00;
Test_data[309] = 0x00;
Test_data[310] = 0x00;
Test_data[311] = 0x00;
Test_data[312] = 0x00;
Test_data[313] = 0x00;
Test_data[314] = 0x00;
Test_data[315] = 0x00;
Test_data[316] = 0x00;
Test_data[317] = 0x00;
Test_data[318] = 0x00;
Test_data[319] = 0x00;
Test_data[320] = 0x00;
Test_data[321] = 0x00;
Test_data[322] = 0x00;
Test_data[323] = 0x00;
Test_data[324] = 0x00;*/

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
	/*Seq_p126[60]= std::complex<double>(-1.0, 0.0);*/  Seq_p126[60]= std::complex<double>(1.0, 0.0);
	Seq_p126[64]= std::complex<double>(-1.0, 0.0);  Seq_p126[62]= std::complex<double>(1.0, 0.0);   Seq_p126[63]= std::complex<double>(1.0, 0.0);

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
	S_datapart=NULL;
	S_PPDU=NULL;
	S_preamb_length=0;
	S_singal_length=0;
	S_data_length=0;
	S_PPDU_length=0;

	S_FFTATUOpower=NULL;
	S_FFTspectrum=NULL;
	n_bpsc = 1;
	n_cbps = 48;
	n_dbps = 24;
	n_rate=6;
	sample_rate=Sample_Rate;
	rate_field = 0x0D; // 0b00001101
	//基本参数
	Sample_Rate = 20;
	T_tr = 0.1;
	scramble_state=0x5d;
	index_q=0;
	//OFDM参数
	//信道参数
}

CProtocolA::~CProtocolA()
{
	//delete []data;
} 

void CProtocolA::ofdm_param(Encoding e)
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
		assert(false);
		break;
	}
}

void CProtocolA::tx_param(int psdu_length) 
{
	
	psdu_size = psdu_length;
	// number of symbols (17-11)
	n_sym = (int) ceil((16 + 8 * psdu_size + 6) / (double)n_dbps);
	// number of bits of the data field (17-12)
	n_data = n_sym * n_dbps;
	// number of padding bits (17-13)
	n_pad = n_data - (16 + 8 * psdu_size + 6);
	n_encoded_bits = n_sym * n_cbps;
}

void CProtocolA::ifft(std::complex<double> f[])
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



void CProtocolA:: bitrp (vector<complex<double>> &Data_In, int n)
{
	// 位反转置换 Bit-reversal Permutation
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

//void CProtocolA::  IFFT (vector<complex<double>> &Data_In, int n)
//{
//	int N=n,i,p;
//	complex<double> temp=(0.0,0.0);
//	if( N& (N-1) )
//	{
//		for (i = 1, p = 0; i < N; i *= 2)
//		{
//			p ++;
//		}
//		N=pow(2.0,p);
//	}	                                //不是2的幂
//	for(int len=0;len<N-n;len++)
//		Data_In.push_back(temp);
//	double* wreal=new double[N/2];
//	double* wimag=new double[N/2]; 
//	double treal, timag, ureal, uimag, arg;
//	int m, k, j, t, index1, index2;
//
//	bitrp (Data_In, N);
//
//	// 计算 1 的前 n / 2 个 n 次方根 Wj = wreal [j] + i * wimag [j] , j = 0, 1, ... , n / 2 - 1
//	arg = 2 * PI / N;
//	treal = cos (arg);
//	timag = sin (arg);
//	wreal [0] = 1.0;
//	wimag [0] = 0.0;
//	for (j = 1; j < N / 2; j ++)
//	{
//		wreal [j] = wreal [j - 1] * treal - wimag [j - 1] * timag;
//		wimag [j] = wreal [j - 1] * timag + wimag [j - 1] * treal;
//	}
//
//	for (m = 2; m <= N; m *= 2)
//	{
//		for (k = 0; k < N; k += m)
//		{
//			for (j = 0; j < m / 2; j ++)
//			{
//				index1 = k + j;
//				index2 = index1 + m / 2;
//				t = N * j / m;    // 旋转因子 w 的实部在 wreal [] 中的下标为 t
//				treal = wreal [t] * Data_In[index2].real() - wimag [t] * Data_In[index2].imag();
//				timag = wreal [t] * Data_In[index2].imag() + wimag [t] * Data_In[index2].real();
//				ureal = Data_In[index1].real();
//				uimag = Data_In[index1].imag();
//				Data_In[index1].real(ureal + treal);
//				Data_In[index1].imag(uimag + timag);
//				Data_In[index2].real(ureal - treal);
//				Data_In[index2].imag(uimag - timag);
//			}
//		}
//	}
//
//	for (j=0; j < N; j ++)
//	{
//		Data_In[j]/=N;
//	}
//	delete[] wreal;
//	delete[] wimag;
//}
//
//
//std::complex<double> CProtocolA::EE(std::complex<double> a,std::complex<double> b)
//{
//	std::complex<double> c;
//	c.real(a.real()*b.real()-a.imag()*b.imag());
//	c.imag(a.real()*b.imag()+a.imag()*b.real());
//	return(c);
//}
//
//void CProtocolA::FFT(std::complex<double> xin[])
//{
//	int f,m,nv2,nm1,i,k,l,j=0;
//	std::complex<double> u,w,t;
//	nv2=FFT_N/2;                  //变址运算，即把自然顺序变成倒位序，采用雷德算法
//	nm1=FFT_N-1;  
//	for(i=0;i<nm1;i++)        
//	{
//		if(i<j)                    //如果i<j,即进行变址
//		{
//			t=xin[j];           
//			xin[j]=xin[i];
//			xin[i]=t;
//		}
//		k=nv2;                    //求j的下一个倒位序
//		while(k<=j)               //如果k<=j,表示j的最高位为1   
//		{           
//			j=j-k;                 //把最高位变成0
//			k=k/2;                 //k/2，比较次高位，依次类推，逐个比较，直到某个位为0
//		}
//		j=j+k;                   //把0改为1
//	}
//	
//	{
//		int le,lei,ip;                            //FFT运算核，使用蝶形运算完成FFT运算
//		f=FFT_N;
//		for(l=1;(f=f/2)!=1;l++)                  //计算l的值，即计算蝶形级数
//			;
//		for(m=1;m<=l;m++)                         // 控制蝶形结级数
//		{                                        //m表示第m级蝶形，l为蝶形级总数l=log（2）N
//			le=2<<(m-1);                            //le蝶形结距离，即第m级蝶形的蝶形结相距le点
//			lei=le/2;                               //同一蝶形结中参加运算的两点的距离
//			u.real(1.0);                             //u为蝶形结运算系数，初始值为1
//			u.imag(0.0);
//			w.real(cos(pi/lei));                     //w为系数商，即当前系数与前一个系数的商
//			w.imag(-sin(pi/lei));
//			for(j=0;j<=lei-1;j++)                   //控制计算不同种蝶形结，即计算系数不同的蝶形结
//			{
//				for(i=j;i<=FFT_N-1;i=i+le)            //控制同一蝶形结运算，即计算系数相同蝶形结
//				{
//					ip=i+lei;                           //i，ip分别表示参加蝶形运算的两个节点
//
//					t=EE(xin[ip],u);                    //蝶形运算，详见公式
//					xin[ip].real((xin[i].real()-t.real()));
//					xin[ip].imag((xin[i].imag()-t.imag()));
//					xin[i].real((xin[i].real()+t.real()));
//					xin[i].imag((xin[i].imag()+t.imag()));
//				}
//				u=EE(u,w);                           //改变系数，进行下一个蝶形运算
//			}
//		}
//	}
//}

void CProtocolA::Produce_preamb(std::complex<double> complex_preamb[])
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

	std::complex<double> S_shorttext[64]={(0.0,0.0)};

	for(preamb_i=0;preamb_i<26;preamb_i++)
	{
		S_shorttext[preamb_i+1]=S_short[preamb_i+27];
		S_shorttext[preamb_i+38]=S_short[preamb_i];
	}

	ifft(S_shorttext);
	
	for (preamb_k=0;preamb_k<N_times;preamb_k++)
	{
		for(preamb_i=0;preamb_i<64;preamb_i++)
		{
			complex_preamb[preamb_k*64+preamb_i]=S_shorttext[preamb_i];
		}
	}
	for	(preamb_i=0;preamb_i<=N_mod;preamb_i++)//<=改为<,不给160个数字赋值
	{
		complex_preamb[N_times*64+preamb_i]=S_shorttext[preamb_i];
	}

	for (preamb_i=0;double(preamb_i)/(sample_rate) < T_tr/2;preamb_i++)
	{
		complex_preamb[preamb_i]=std::complex<double> (pow(sin(pi/2*(0.5+preamb_i/(T_tr*sample_rate))),2),0.0)*complex_preamb[preamb_i];//处理了preamble第一个数据
		complex_preamb[sample_rate*8-preamb_i]=std::complex<double> (pow(sin(pi/2*(0.5+preamb_i/(T_tr*sample_rate))),2),0.0)*complex_preamb[sample_rate*8-preamb_i];//处理了preamble[160]
	}
	//  160
	
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

	std::complex<double> S_longtext[64]={(0.0,0.0)};
	std::complex<double> S_addpoint=complex_preamb[sample_rate*8];

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

	complex_preamb[sample_rate*8*2]=S_longtext[N_mod];//给第320个数据复制


	for	(preamb_i=0;preamb_i<N_mod;preamb_i++)
	{
		complex_preamb[preamb_i+sample_rate*8]=S_longtext[preamb_i+64-N_mod];
	}


	//20160308注释
	for (preamb_i=0;double(preamb_i)/(sample_rate) < T_tr/2;preamb_i++)
	{
		complex_preamb[preamb_i+sample_rate*8]=std::complex<double> (pow(sin(pi/2*(0.5+preamb_i/(T_tr*sample_rate))),2),0.0)*complex_preamb[preamb_i+sample_rate*8];
		complex_preamb[sample_rate*8*2-preamb_i]=std::complex<double> (pow(sin(pi/2*(0.5+preamb_i/(T_tr*sample_rate))),2),0.0)*complex_preamb[sample_rate*8*2-preamb_i];
	}
	
	complex_preamb[sample_rate*8] +=S_addpoint;
	complex_preamb[sample_rate*8*2] = S_longtext[0]/std::complex<double>(2.0, 0.0);
	S_addpoint=complex_preamb[sample_rate*8*2];

}

void CProtocolA::reshape_data(std::complex<double> complex_out[],std::complex<double> complex_in[],int index)
{
	int reshap_i=0;
	
	/*-----------------------------------------映射到64点数据上，再进行ifft运算之前进行数据重排。----------------*/
	
	for(reshap_i=0;reshap_i<5;reshap_i++)
	{
		complex_out[reshap_i+38]=complex_in[reshap_i];
		complex_out[reshap_i+22]=complex_in[reshap_i+43];
	}
	complex_out[21] = Seq_p126[index]*std::complex<double> (-1.0,0.0);				
	complex_out[43] = Seq_p126[index]*std::complex<double> (1.0,0.0);                
	
	for(reshap_i=0;reshap_i<13;reshap_i++)
	{
		complex_out[reshap_i+8] = complex_in[reshap_i+30];
		complex_out[reshap_i+44] = complex_in[reshap_i+5];
	}
	complex_out[7] = Seq_p126[index]*std::complex<double> (1.0,0.0);                
	complex_out[57] = Seq_p126[index]*std::complex<double> (1.0,0.0);				
	
	for(reshap_i=0;reshap_i<6;reshap_i++)
	{
		complex_out[reshap_i+58] = complex_in[reshap_i+18];
		complex_out[reshap_i+1] = complex_in[reshap_i+24];
	}
}

void CProtocolA::add_recycle(std::complex<double> complex_out[],std::complex<double> complex_in[],int sample_rate)
{
	int recycle_i = 0;
	int index_out=80;
    int recycle_mod = index_out % 64;
	
	
	for(recycle_i=0;recycle_i < 64;recycle_i++)
	{
		complex_out[recycle_i+recycle_mod]=complex_in[recycle_i];//begin from N_mod
	}
	
	complex_out[index_out]=complex_in[0];//多加的一位
	
	
	for	(recycle_i=0;recycle_i<recycle_mod;recycle_i++)
	{
		complex_out[recycle_i]=complex_in[recycle_i+64-recycle_mod];
	}
	
	for (recycle_i=0; double(recycle_i)/(sample_rate) < T_tr/2;recycle_i++)
	{
		complex_out[recycle_i]=std::complex<double> (pow(sin(pi/2*(0.5+recycle_i/(T_tr*sample_rate))),2),0.0)*complex_out[recycle_i];
		complex_out[index_out-recycle_i]=std::complex<double> (pow(sin(pi/2*(0.5+recycle_i/(T_tr*sample_rate))),2),0.0)*complex_out[index_out-recycle_i];
	}

}

int CProtocolA::ones(int n)
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

void CProtocolA::Produce_singal(std::complex<double> complex_singal[],int *Q_pinter,int data_length)
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

	////std::complex<double> Q[24]={0};//用于存储Q路数据
	//int Q[24]={0};
	//ofstream of("11a_mcs7_sig.txt");
	//for (int i = 0;i<24;i++)
	//{
	//	Q[i] = SINGAL[i];
	//	of<<Q[i]<<endl;
	//}
	//of.close();


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

	std::complex<double> SINGAL_map[48]={(0.0,0.0)};

	for (int i=0;i<48;i++)
	{
		SINGAL_map[i]=BPSK_D[SINGAL_inter[i]];
	}

	std::complex<double> S_singal[64]={(0.0,0.0)};
	reshape_data(S_singal,SINGAL_map,index_q);

	ifft(S_singal);

	add_recycle(complex_singal,S_singal,sample_rate);

	(* Q_pinter)++;

}

void CProtocolA::Bit_to_bit(char Bitdata[],char bitdata[],int bit_length)
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

void CProtocolA::scramble(const char *in, char *out,int initial_state)
{
  if (AprotocolConfig.scrambler_state_OFDM)
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

void CProtocolA::reset_tail_bits(char *scrambled_data)
{
	memset(scrambled_data + n_data - n_pad - 6, 0, 6 * sizeof(char));
}

void CProtocolA::convolutional_encoding(const char *in, char *out,int data)
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

void CProtocolA::puncturing(const char *in, char *out)
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

void CProtocolA::interleave(const char *in, char *out, bool reverse)
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

void CProtocolA::symbol_mapping(const char map_in[], std::complex<double> map_out[])
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

void CProtocolA::Produce_data(char char_datain[],std::complex<double> complex_dataout[],int * Q_pinter,int data_length)
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
	int scramble_state=AprotocolConfig.scramble_state_initial;
	scramble(data_scramble, data_scrambleout,scramble_state);//
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
    
	std::complex<double> *symbol_mapp = new std::complex<double> [n_encoded_bits/n_bpsc];
	memset(symbol_mapp, (0.0,0.0), n_encoded_bits/n_bpsc);
	symbol_mapping(data_interleave, symbol_mapp);
	delete []data_interleave;
	std::complex<double> ofdm_side=(0.0,0.0) ;   
	
	for (int data_i=0;data_i<n_sym;data_i++)
	{	
		std::complex<double> data_part64[64]={(0.0,0.0)}; 
		std::complex<double> data_part48[48]={(0.0,0.0)}; 
		std::complex<double> data_part81[81]={(0.0,0.0)};
		
		for(int data_k=0;data_k<48;data_k++)
		{
			data_part48[data_k]=symbol_mapp[48*data_i+data_k];
		}
		
		reshape_data(data_part64,data_part48,* Q_pinter);
		
		ifft(data_part64);
		
		add_recycle(data_part81,data_part64,sample_rate);
		
		data_part81[0]=data_part81[0]+ofdm_side;//删掉这两句
		if((data_i+1)*80==80*n_sym) complex_dataout[80*n_sym] = data_part64[0]/std::complex<double>(2.0,0.0);//删掉这两句
		ofdm_side=data_part81[80];
		
		for(int data_m=0;data_m<80;data_m++)
		{
			complex_dataout[80*data_i+data_m]=data_part81[data_m];
		}
		
		(*Q_pinter)++;
	}
	
	delete [] symbol_mapp;
}

void CProtocolA::Produce_PPDU(std::complex<double> preambpart_in[],std::complex<double> singalpart_in[],std::complex<double> datapart_in[],std::complex<double> PPDU_out[],int preamb_length,int singal_length,int data_length)
{
	int PPDU_i=0;
	
	for(PPDU_i=0;PPDU_i<preamb_length-1;PPDU_i++) PPDU_out[PPDU_i]=preambpart_in[PPDU_i];
	
	PPDU_out[preamb_length-1]=preambpart_in[preamb_length-1]+singalpart_in[0];
	
	for(PPDU_i=1;PPDU_i<singal_length-1;PPDU_i++) PPDU_out[PPDU_i+preamb_length-1]=singalpart_in[PPDU_i];
	
	PPDU_out[preamb_length+singal_length-2]=singalpart_in[singal_length-1]+datapart_in[0];
	
	for(PPDU_i=1;PPDU_i<data_length;PPDU_i++) PPDU_out[PPDU_i+preamb_length+singal_length-2]=datapart_in[PPDU_i];
}

void CProtocolA::channel_initialize_1(double RndPhase[][12], double *Path_Delay, double *Path_Average_Amp, double *fore_data_pr, double *fore_data_pi, \
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
void CProtocolA::Jakes_kernel(double Path_Ampli,int NumOfFreq,int UpdateInterval,double fd_max,double* Phase,\
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
			//cosine = cos(Wn[n]*t_tmp*dt);

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
void CProtocolA::multipath_channel(double *InData_pr,double *InData_pi,\
	double fd_max,long NumOfTaps,\
	int SamplesPerFrame,int ChangesPerFrame,\
	int* TimeIndex,double dt,\
	double Phase[][12],double *Path_Delay,double *Path_Average_Amp,\
	vector<double> &OutData_pr,vector<double> &OutData_pi,\
	double *out_fading_pr,double *out_fading_pi,\
	double *fore_data_pr,double *fore_data_pi,\
	double *fading_indx)
{   
	dt=dt/AprotocolConfig.oversample_ratio;
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

void CProtocolA::Run(vector<int> src,int data_bytelen)
{
	//将数据类型从int转换为char 
	char *src_a = new char[data_bytelen];//一个char型占1个字节，8个比特位
	for (int k=0;k<data_bytelen;k++)
	{
		src_a[k] = 0x00;
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
		src_a[iByteNo] += src[i]*g_BinArr[iBitInByte];
	}
	int Test_data_length=data_bytelen;
	
	ofdm_param(AprotocolConfig.EZOA_Encoding);//输入需要传输的方式
	tx_param(Test_data_length);
	
	S_preamb_length=Sample_Rate*16+1;
	if(S_preambpart == NULL)
	S_preambpart=new std::complex<double> [S_preamb_length];//preamb
	memset(S_preambpart, (0.0,0.0),S_preamb_length);
	Produce_preamb(S_preambpart);
	
	S_singal_length=81;
	if(S_singalpart == NULL)
	S_singalpart = new std::complex<double> [S_singal_length];//SINGAL
	memset(S_singalpart, (0.0,0.0),S_singal_length);
	Produce_singal(S_singalpart,&index_q,Test_data_length);
	
	S_data_length=80*n_sym+1;
	if(S_datapart == NULL)
	S_datapart = new std::complex<double> [S_data_length] ;
	memset(S_datapart, (0.0,0.0),S_data_length);
	Produce_data(src_a,S_datapart,&index_q,Test_data_length);

	S_PPDU_length=S_data_length+S_singal_length+S_preamb_length-2;
	if(S_PPDU == NULL)
	S_PPDU= new std::complex<double> [S_PPDU_length];
	Produce_PPDU(S_preambpart,S_singalpart,S_datapart,S_PPDU,S_preamb_length,S_singal_length,S_data_length);
	 
	vector<double> t;
	double Data_temp_real,Data_temp_imag;
	int i;
	for (i=0; i<S_PPDU_length; i++ )
	{
		t.push_back(i*AprotocolConfig.dt);
	}  

	for (i=0; i<S_PPDU_length; i++ )
	{
		Data_temp_real = cos(2*pi*AprotocolConfig.FrequencyOffset*t[i]);
		Data_temp_imag = sin(2*pi*AprotocolConfig.FrequencyOffset*t[i]);
		S_PPDU[i].real(S_PPDU[i].real()*Data_temp_real - S_PPDU[i].imag()*Data_temp_imag);
		S_PPDU[i].imag(S_PPDU[i].real()*Data_temp_imag + S_PPDU[i].imag()*Data_temp_real);
	}  
	AprotocolConfig.length=S_PPDU_length;
	//信道部分
	
	if(AprotocolConfig.add_channel)
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
		double * data_r = new double[S_PPDU_length];
		double * data_i = new double[S_PPDU_length];
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
			&RMS_Delay_Sample,AprotocolConfig.MAX_Delay_Sample,AprotocolConfig.NumOfTaps,Path_Average_Power,\
			sizeof_Path_Delay,sizeof_Path_Average_Power);
		double fd_max = AprotocolConfig.mobilespeed / 3.6 / (3e8) * AprotocolConfig.carrierfreq;
		multipath_channel(data_r,data_i,fd_max,AprotocolConfig.NumOfTaps,SamplesPerFrame,\
			ChangesPerFrame,TimeIndex,AprotocolConfig.dt,RndPhase,Path_Delay,\
			Path_Average_Amp,OutData_pr,OutData_pi,\
			out_fading_pr,out_fading_pi,\
			fore_data_pr,fore_data_pi,&fading_indx);
		for(int i=0;i<S_PPDU_length;i++)
		{
			complex<double> outdata;
			//outdata.real(abs(OutData_pr[i])>0.4 ? S_PPDU[i].real():OutData_pr[i]);
			//outdata.imag(abs(OutData_pi[i])> 0.4 ?  S_PPDU[i].imag():OutData_pi[i]);

			outdata.real(abs(OutData_pr[i])>1000 ? S_PPDU[i].real():OutData_pr[i]);
			outdata.imag(abs(OutData_pi[i])>1000 ? S_PPDU[i].imag():OutData_pi[i]);

			S_PPDU[i] = outdata;
		}
	}
	//过采滤波
	int over_ratio = AprotocolConfig.oversample_ratio;
	if(over_ratio >1)
	{
		complex<double>* after_oversample = new complex<double>[S_PPDU_length*over_ratio];
		complex<double> zero(0.0,0.0);
		for(int i = 0; i < S_PPDU_length * over_ratio ; i++)
		{
			if( (i % over_ratio) == 0)
				after_oversample[i] = S_PPDU[ i/over_ratio ];
			else
				after_oversample[i] = zero ;
		}
		switch(AprotocolConfig.filter_para.filtertype)
		{
		case lpfilter:
			   
			{
				vector<double> filter_coef = lowpass_filter(AprotocolConfig.filter_para.lppara.length,AprotocolConfig.filter_para.lppara.wn);
				my_conv(after_oversample,filter_coef,S_PPDU_length * over_ratio);
				S_PPDU = after_oversample;
				break;
			}
		case gaussfilter:
			{
				vector<double> filter_coef = gauss_filter(AprotocolConfig.filter_para.gausspara.length,AprotocolConfig.filter_para.gausspara.BT);
				my_conv(after_oversample,filter_coef,S_PPDU_length * over_ratio);
				S_PPDU = after_oversample;
				break;
			}
		case cosfilter:
			{
				vector<double> filter_coef = root_raised_cosine(AprotocolConfig.filter_para.cosinepara.alpha,AprotocolConfig.filter_para.cosinepara.length,AprotocolConfig.oversample_ratio);
				my_conv(after_oversample,filter_coef,S_PPDU_length * over_ratio);
				S_PPDU = after_oversample;
				break;
			}
		case userdefined:
			{
				my_conv(after_oversample,AprotocolConfig.filter_user,S_PPDU_length * over_ratio);
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
	double IQ_gain = AprotocolConfig.IQ_gain;//注意与自己的对应
	double qAngleAD = AprotocolConfig.quan_angle_adjust;
	if(AprotocolConfig.add_channel == false)//不加信道的时候如果改正交角度调整或IQ平衡增益就会做如下公式
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

void CProtocolA::Clear()
{
	delete []S_PPDU;//清除内存
	delete []S_preambpart;
	delete []S_singalpart;
	delete []S_datapart;
	delete []S_FFTATUOpower;
	delete []S_FFTspectrum;
}
BEGIN_MESSAGE_MAP(CProtocolA, CStatic)
	//{{AFX_MSG_MAP(CProtocolA)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProtocolA message handlers

