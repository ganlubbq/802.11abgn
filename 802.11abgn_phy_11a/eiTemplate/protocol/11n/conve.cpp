#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <iostream>
//#include "matrix.h"
#include "primaryFunctionalFunc.h"
#include "stdafx.h"

static unsigned short state;
static short x, y;

void cenc(short bit_in);
//double *conve(double *bit_in,long BitLength,bool ts);

/*void main()
{
	double bit_in[4] = {1,1,0,1};
	long L = 4;
	double *out;
	out = (double (*))malloc(sizeof(double)*2*L);
	out = conve(bit_in,L,1);
	for (int i=0;i<2*L;i++)
		std::cout << out[i] << " ";
	while(1);
	free(out);
}*/

static void cenc(short bit_in){
	x = (bit_in & 1) ^ 
		((state & (1 << 0)) ? 1 : 0) ^
		((state & (1 << 1)) ? 1 : 0) ^
		((state & (1 << 3)) ? 1 : 0) ^
		((state & (1 << 4)) ? 1 : 0)
		;
	y = (bit_in & 1) ^ 
		((state & (1 << 0)) ? 1 : 0) ^
		((state & (1 << 3)) ? 1 : 0) ^
		((state & (1 << 4)) ? 1 : 0) ^
		((state & (1 << 5)) ? 1 : 0)
		;
	state = (state >> 1) | ((bit_in & 1) << 5);
}

int* conve(int *bit_in,long BitLength,bool ts)
{

	int startNum=0;
	int nout=0;

	int *pin = NULL,*plhs = NULL;
	
	plhs = (int (*))malloc(sizeof(int)*2*BitLength);
	while(startNum<=BitLength)
	{
		plhs[startNum] = 0;
		startNum++; 
	}

	pin = (int *)  bit_in;

	if(ts) 
		state = 0;
	for(int j = 0; j < BitLength; j++) 
	{
		if(j < BitLength) 
			cenc((short) pin[j]);
		else
			cenc((short) 0);

		plhs[2*j] = (int) x;
		plhs[2*j+1] = (int) y;
	}

	return plhs;
}