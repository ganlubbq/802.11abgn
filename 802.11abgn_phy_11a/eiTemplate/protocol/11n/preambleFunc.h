#ifndef PREAMBLEFUNC_H_
#define PREAMBLEFUNC_H_

//preamble 函数声明文件
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
//#include <mat.h> 
#include <stdlib.h>
#include <stdio.h>
#include "wlan_const_set.h"
#include "primaryFunctionalFunc.h"

using namespace std;

vv_c_dl preamble_l_stf(paramsFather params);
vv_c_dl preamble_l_ltf(paramsFather params);
vv_c_dl preamble_l_sig(int txvector_MCS,paramsFather params,wlan_consts consts);

vv_c_dl preamble_ht_ltf(wlan_txparam txv,paramsFather params,int n);
vv_c_dl preamble_ht_stf(wlan_txparam txv,paramsFather params);
vv_c_dl preamble_ht_sig(wlan_txparam txv,paramsFather params);

#endif