#include "scramble.h"
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using namespace std;
int scr_init[133]={0,0,0,0,1,3,7,14,29,59,119,111,94,60,121,114,101,75,22,44,89,50,100,73,18,36,72,16,32,64,1,2,4,8,17,34,68,9,19,38,76,24,49,98,69,11,23,46,93,58,117,107,86,45,91,54,108,88,48,96,65,3,6,12,25,51,102,77,26,53,106,84,41,83,39,78,28,57,115,103,79,30,61,123,118,109,90,52,104,80,33,66,5,10,21,42,85,43,87,47,95,62,125,122,116,105,82,37,74,20,40,81,35,70,13,27,55,110,92,56,113,99,71,15,31,63,127,126,124,120,112,97,67}; 
int src_seq[127] = {0,0,0,0,1,1,1,0,1,1,1,1,0,0,1,0,1,1,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,0,1,0,0,1,1,0,0,0,1,0,1,1,1,0,1,0,1,1,0,1,1,0,0,0,0,0,1,1,0,0,1,1,0,1,0,1,0,0,1,1,1,0,0,1,1,1,1,0,1,1,0,1,0,0,0,0,1,0,1,0,1,0,1,1,1,1,1,0,1,0,0,1,0,1,0,0,0,1,1,0,1,1,1,0,0,0,1,1,1,1,1,1,1};

void scrambler(int start,int size,vector<int> &Data_in){

	vector<int> scr_init_seq(scr_init+6,scr_init+sizeof(scr_init)/sizeof(scr_init[0]));
	vector<int>::iterator iter=find(scr_init_seq.begin(),scr_init_seq.end(),start);  
	int init_loc= iter - scr_init_seq.cbegin()+7;
	//scr_bits = scr_seq(1+mod(init_loc+(0:size-1),127))
	int pos;
	for(int i = 0;i < size;i++){
		pos = (init_loc + i) % 127;
		Data_in[i] = src_seq[pos] ^ Data_in[i];
	}
}
