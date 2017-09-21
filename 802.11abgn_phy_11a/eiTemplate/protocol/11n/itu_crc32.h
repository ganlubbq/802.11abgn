#ifndef ITU_CRC32_H_
#define ITU_CRC32_H_

#include <math.h>
#include <stdio.h>

/*----------------------------------------------------
 Function Description: ITU标准32位CRC
---------------------------------------------------
History:
Created by hxy   Date:2014-11-19    Version:1.0
----------------------------------------------------
Function List:
---------------------------------------------------
 Input Parameters:
           crc_in: 输入比特流
		   length：输入长度
		   n：移位序列
----------------------------------------------------
Output Parameters:
           ou: 输出比特流
---------------------------------------------------
 Reference:
 ----------------------------------------------------*/
// Note:
unsigned itu_crc32(int *crc_in,int length,const unsigned n)
{
	unsigned int CRC,bitIn;
	int *pin;
	unsigned m = 0x0ffffffff;

	unsigned b,temA;
	unsigned prodLow;
	const unsigned long POLY = 0x04C11DB7;
	int i;

	pin = crc_in;
	for( i=0; i<length; i++)
	{
		bitIn = (unsigned)(*(pin++));
		b = (m >> 31) ^ bitIn;
		temA = m << 1;
		prodLow = b * POLY;			
		m = prodLow ^ temA;
	}
	CRC = m ^ n;

	return CRC;
}

#endif