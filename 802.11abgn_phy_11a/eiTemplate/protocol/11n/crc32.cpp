/*----------------------------------------------------
 Function Description: CRC32 insertion
---------------------------------------------------
History:
Created by hxy   Date:2014-11-19    Version:1.0
----------------------------------------------------
 Input Parameters:
           in: a vector of N bytes 十进制数序列
----------------------------------------------------
Output Parameters:
           ou: the input vector, with the last four values replaced by CRC32 bytes
---------------------------------------------------
 Reference:
 ----------------------------------------------------*/
#include "stdafx.h"
#include "itu_crc32.h"
//#include <math.h>
#include <iostream>
#include "transform_bits_num.h"
#include"primaryFunctionalFunc.h"

int* crc32(int *in,int L)
{
	int *ou = NULL;
	ou = new int[L];
	
	int i;
	int N =8;

	int *a;
	a = new int[(L-4)*N];
	unsigned m;
	double num1,num2,num3;
	const unsigned n = 0x0ffffffff;

	for (i=0;i<L-4;i++)
		ou[i] = in[i];
	a = num2bitsv(ou,L-4,N);
	m = itu_crc32(a,(L-4)*N,n);

	num1 = m/pow(2.0,24.0);
	num2 = m/pow(2.0,16.0);
	num3 = m/256;

	ou[L-4] = unsigned (num1);
	ou[L-3] = (unsigned(num2)) & 255;
	ou[L-2] = (unsigned(num3)) & 255;
	ou[L-1] = m & 255;

	return ou;
}
