#include "transform_bits_num.h"
#include "stdafx.h"
#include <MATH.H>
//----------------------------------------------------//
// Function Description: converts a bit stream,MSB first, to the corresponding numbers 
//----------------------------------------------------//
// History:
// Created by Liyuli   Date:2014-10-28    Version:1.0
//
//----------------------------------------------------//
// Function List:
//----------------------------------------------------//
// Input Parameters:
//           b_in:输入0,1比特序列
//           b_n1:
//           N_bpsc:
//----------------------------------------------------//
// Output Parameters:
//           ou:
//----------------------------------------------------//
// Reference:
//----------------------------------------------------//
// Note:
int *bits2numv(int *b_in, int b_n1, int N_bpsc)
{
	int* res = (int *)malloc(sizeof(int) * (b_n1/N_bpsc));
	if(b_n1 == 0) return NULL;
	else
	{
		int i, j;
		int templen;
		long sum;
		templen = b_n1;
		for(i = 0;i < (b_n1/N_bpsc);i++)//去掉+1
		{
			sum=0;
				for(j =i*N_bpsc;j < i*N_bpsc + N_bpsc;j++)
				{
					sum += b_in[j] * pow(2.0,i*N_bpsc + N_bpsc - 1 - j);//
				}
				res[i] = sum;
		}
			templen -= N_bpsc;
	}
	return res;
}

/*----------------------------------------------------
 Function Description: convert a sequence of numbers to a vector
 with their bits, MSB first. 
---------------------------------------------------
History:
Created by hxy   Date:2014-11-13    Version:1.0
----------------------------------------------------
Function List:
---------------------------------------------------
 Input Parameters:
           b_in:输入十进制数组
		   L:输入的十进制数组长度
           N:每个十进制数转化成的比特数
----------------------------------------------------
Output Parameters:
           ou:输出比特流
---------------------------------------------------
 Reference:
 ----------------------------------------------------*/
// Note:
int* num2bitsv(int *b_in, int L, int N)
{
	int i,j,k;
	int ninp;

	int *pout = NULL;
	pout = new int[L*N];
	if (L > 262144-1)
	{
		printf("Input vector is too large");
		exit(0);
	}
	else
	{
		if (N > 32) N = 32;
		if (N < 1) N = 1;

		k = 0;
        for(j = 0; j < L; j++)
		{
           ninp = b_in[j];
           for(i = 0; i < N; i++) 
		   {
			   pout[k++] = (ninp & (1 << (N - 1))) ? 1 : 0; 
			   ninp <<= 1;
		   }
        }
	}
	return pout;
}