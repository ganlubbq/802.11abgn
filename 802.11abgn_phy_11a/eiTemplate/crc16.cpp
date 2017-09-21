#include "stdafx.h"
#include "crc16.h"
INT16U crc16(unsigned char *buf,int length)
{
	INT16U shift,data,val;
	int i;
	shift = CRC_SEED;
	for(i=0;i<length;i++) {
		if((i % 8) == 0)
			data = (*buf++)<<8;
		val = shift ^ data;
		shift = shift<<1;
		data = data <<1;
		if(val&0x8000)
			shift = shift ^ POLY16;
	}
	return ~shift;
} 