/*----------------------------------------------------
 Function Description: LDPC encoder wrapper
---------------------------------------------------
History:
Created by hxy   Date:2014-12-2    Version:1.0
----------------------------------------------------
Function List:
---------------------------------------------------
 Input Parameters:
         byte_in     : information byte input
		 Length      : Length of byte_in
         enc_str     : FEC structure
           .n_dbps   : number of total data bits
           .n_cbps   : number of total encoded bits
           .crate    : code rate
           .n_es     : number of codeblocks
         scram_seed  : scrambler seed
		 crc_sigb    : crc bits of sigb
----------------------------------------------------
Output Parameters:
           pktEncOut : coded bits
---------------------------------------------------*/
#include "stdafx.h"
#include "ldpc_encode.h"
#include "transform_bits_num.h"
#include "scramble.h"
#include "wlan_txparam.h"

applyLdpcEnc_out applyLdpcEnc_ac(int *bitIn,ldpcPara out_str,int cwIdx);

vector<int> ldpc_encoder(int *byte_in,int Length,MCSMode enc_str,ldpcPara ldpc_para,int scram_seed,int crc_sigb)
{
	int N = 8;
	int *bit_info;
	//bit_info = new int[Length*N];
	bit_info = new int[16+Length*N];
	//bit_info = num2bitsv(byte_in,Length,N);
	for(int i=0;i<Length*N+16;i++)
	{
		bit_info[i]=byte_in[i];
	}
	int *bitscr = NULL;
	int *crcsigb = &crc_sigb;
	if(enc_str.enc_type)
	{
		int *crcsigb_bit;
	    crcsigb_bit = new int[N];
	    crcsigb_bit = num2bitsv(crcsigb,1,N);
		long L = 8+N+Length*N+ldpc_para.n_pad;
		int *b_in;
		b_in = new int[L];
		for(int i=0;i<8;i++)
			b_in[i] = 0;
		for(int j=8;j<8+N;j++)
			b_in[j] = crcsigb_bit[j-8];
		for(int k=8+N;k<8+N+Length*N;k++)
			b_in[k] = bit_info[k-(8+N)];
		for(int r=8+N+Length*N;r<L;r++)
			b_in[r] = 0;
		

		bitscr = new int[L];
		/*bitscr = scram_t(scram_seed,b_in,L);*/
		delete [] b_in;
		delete [] crcsigb_bit;
	}
	else
	{
		int *b_in;
		long L = 16+Length*N;
		/*b_in = new int[L];
		for(int i=0;i<16;i++)
			b_in[i] = 0;
		for(int j=16;j<L;j++)
			b_in[j] = bit_info[j-16];*/
		/*for(int j=0;j<L;j++)
			b_in[j] = bit_info[j];*/
		bitscr = new int[L];
		for(int j=0;j<L;j++)
			bitscr[j] = bit_info[j];
		//bitscr = scram_t(scram_seed,b_in,L);
		//delete [] b_in;
	}
	applyLdpcEnc_out Sout;
	//applyLdpcEnc_out ldpc_encoder_out;

	Sout = applyLdpcEnc_ac(bitscr,ldpc_para,0);
	delete [] bitscr;
	delete [] bit_info;
	/*int *bit_o;
	bit_o = new int [Sout.n_sym * ldpc_para.Ncbps];
	bit_o = Sout.pktEncOut;

	ldpc_encoder_out.pktEncOut = bit_o;
	ldpc_encoder_out.n_sym = Sout.n_sym;*/
	return Sout.pktEncOut;
}