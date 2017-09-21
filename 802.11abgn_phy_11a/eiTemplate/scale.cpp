#include "stdafx.h"
#include<stdlib.h>
#include<math.h>
#include "protocol/11n/primaryFunctionalFunc.h"

double scale(int format,wlan_txparam txvector,int n_20){

	int index=0;
	if(txvector.format==0 || txvector.MCS==32)
		index=1;
	double a[2][2]={{56.0,114.0},{52.0,104.0}};
	return 1/sqrt(a[index][n_20-1]);
}