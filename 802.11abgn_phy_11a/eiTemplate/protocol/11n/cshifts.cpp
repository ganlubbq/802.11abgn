//-------------------------------------------------------------------------------//
//  Function Discription: 802.11n transmit simulation
//-------------------------------------------------------------------------------//
//  History:
//    Created by Li Yinan    Date:2014-11-10    Version:1.0
//    Modefied by hxy        Date:2014-12-15    Version:2.0
//-------------------------------------------------------------------------------//
//  Fuction List
//-------------------------------------------------------------------------------//
//  Input Parameters:
//    N      : select the value of cshift
//    htpart : For non-HT part, htpart=0.For HT part, htpart=1
//-------------------------------------------------------------------------------//
//  Output Parameters:
//    cshift: row vector of cyclic shifts in ns
//-------------------------------------------------------------------------------//
//  Reference: cshifts.m
//-------------------------------------------------------------------------------//
//  Note:
//    Null
//-------------------------------------------------------------------------------//
#include<iostream>
#include<stdlib.h>
#include"primaryFunctionalFunc.h"
#include "stdafx.h"

int *cshifts(int N,int htpart)
{
	int *cs;
	cs = new int[N];
	if(htpart)
	{
	//Per space-time stream cyclic shift in HT part
		switch(N)
		{
		case 1:
			{
				int cshift[1] = {0};
				for(int i=0;i<1;i++)
					cs[i] = cshift[i];
				break;
			}
		case 2:
			{
				int cshift[] = {0,-400};
				for(int i=0;i<2;i++)
					cs[i] = cshift[i];
				//return cshift;
				break;
			}
		case 3:
			{
				int cshift[] = {0,-400,-200};
				for(int i=0;i<3;i++)
					cs[i] = cshift[i];
				break;
			}
		case 4:
			{
				int cshift[] = {0,-400,-200,-600};
				for(int i=0;i<4;i++)
					cs[i] = cshift[i];
				//cs = cshift;
				break;
			}
			/*case 5:
			{
			int cshift[] = {0,-400,-200,-600,-350};
			for(int i=0;i<5;i++)
			cs[i] = cshift[i];
			break;
			}
			case 6:
			{
			int cshift[] = {0,-400,-200,-600,-350,-650};
			for(int i=0;i<6;i++)
			cs[i] = cshift[i];
			break;
			}
			case 7:
			{
			int cshift[] = {0,-400,-200,-600,-350,-650,-100};
			for(int i=0;i<7;i++)
			cs[i] = cshift[i];
			break;
			}
			case 8:
			{
			int cshift[] = {0,-400,-200,-600,-350,-650,-100,-750};
			for(int i=0;i<8;i++)
			cs[i] = cshift[i];
			break;
			}
			default: printf("too many tx chains");*/
			}
	}
	else
	{
	//Per Tx cyclic shift
		switch(N)
		{
		case 1:
			{
				int cshift[] = {0};
				for(int i=0;i<1;i++)
					cs[i] = cshift[i];
				break;
			}
		case 2:
			{
				int cshift[] = {0,-200};
				for(int i=0;i<2;i++)
					cs[i] = cshift[i];
				break;
			}
		case 3:
			{
				int cshift[] = {0,-100,-200};
				for(int i=0;i<3;i++)
					cs[i] = cshift[i];
				break;
			}
		case 4:
			{
				int cshift[] = {0,-50,-100,-150};
				for(int i=0;i<4;i++)
					cs[i] = cshift[i];
				break;
			}
			/*case 5:
			{
			int cshift[] = {0,-175,-25,-50,-75};
			for(int i=0;i<5;i++)
			cs[i] = cshift[i];
			break;
			}
			case 6:
			{
			int cshift[]={0,-200,-25,-150,-175,-125};
			for(int i=0;i<6;i++)
			cs[i] = cshift[i];
			break;
			}
			case 7:
			{
			int cshift[] = {0,-200,-150,-25,-175,-75,-50};
			for(int i=0;i<7;i++)
			cs[i] = cshift[i];
			break;
			}
			case 8:
			{
			int cshift[] = {0,-175,-150,-125,-25,-100,-50,-200};
			for(int i=0;i<8;i++)
			cs[i] = cshift[i];
			break;
			}
			default:printf("too many tx chains");*/
			}
	}
	return cs;
}

//------------DISCLAIMER--------------
//  By opening the prototype 802.11ac signal model (Signal Model) the recipient
//  accepts that they are supplied by Cambridge Silicon Radio Limited (CSR),
//  for recipient's use only as a reference model for IEEE, on a non-transferrable basis,
//  entirely at recipient's sole risk, without any warranties of any kind.  
//  CSR does not warrant, without limitation, that the Signal Model is fit for
//  recipient's purpose or do not infringe a third party's intellectual property rights.
//  To the fullest extent permitted by law, CSR shall not be liable for any direct,
//  indirect, special, incidental, consequential or punitive damages of any kind
//  arising out of the use of the Signal Model.