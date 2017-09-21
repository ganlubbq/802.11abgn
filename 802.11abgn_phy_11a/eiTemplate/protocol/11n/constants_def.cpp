#include "stdafx.h"
#include<iostream>
#include"constants_def.h"
//-------------------------------------------------------------------------------//
//  Function Discription: WLAN transmitter constants and enumerates definition
//-------------------------------------------------------------------------------//
//  History:
//    Created by Li Yinan    Date:2014-11-10    Version:1.0
//-------------------------------------------------------------------------------//
//  Fuction List
//-------------------------------------------------------------------------------//
//  Input Parameters:
//    Null
//-------------------------------------------------------------------------------//
//  Output Parameters:
//    Null
//-------------------------------------------------------------------------------//
//  Reference: constants_def.m
//-------------------------------------------------------------------------------//
//  Note:
//    Null
//-------------------------------------------------------------------------------//
//CP LENGTH ENUMERATOR
const int E_LONG_CP  = 0;
const int E_SHORT_CP = 1;
/*
//MIMO mode
const int SU = 0;
const int MU = 1;
*/
//PPDU FORMAT ENUMERATES
const int Legacy     = 0; //Legacy 
const int non_HT_DUP = 10; 
const int HT_MM      = 1; 
const int HT_GF      = 2; 
//const int E_VHT        = 3; //VHT
const int UNDET      = 4; //undetermined

//TX FORMAT ENUMERATOR
//used to index the configuration depandent parameter table
const int E_LEG20M    = 0;
const int E_HT20M     = 1;
const int E_HT40M     = 2; 
/*const int E_VHT20M    = 3;
const int E_VHT40M    = 4; 
const int E_VHT80M    = 5;
const int E_VHT160M   = 6;
const int E_VHT80P80M = 7;
*/
//CHANNEL BANDWIDTH
const int HT_CBW20    = 0;
const int HT_CBW40    = 1;
/*const int HT_CBW80    = 3;
const int HT_CBW80P80 = 4;
const int HT_CBW160   = 5;*/

const int NON_HT_CBW20  = 10;  //all other non-HT formats
const int NON_HT_CBW40  = 11;  //40M duplicate
const int NON_HT_CBW80  = 13;  //80M duplicate
const int NON_HT_CBW160 = 15;  //160M duplicate

//RX vectors update stages
const int E_SYNC = 0;
const int E_LSIG = 1;
const int E_FRMT = 2;
const int E_VSIGA= 3;
const int E_VSIGB= 4;
const int E_HTSIG= 5;

//OFDM symbol type enumerates
const int E_LLTF_TYP  = 1;
const int E_LTF1_TYP  = 2;
const int E_LSIG_TYP  = 3;
const int E_HTSIG_TYP = 4;
const int E_VSIGA_TYP = 5;
const int E_VSTF_TYP  = 6;
const int E_VLTF_TYP  = 7;
const int E_VSIGB_TYP = 8;
const int E_LDATA_TYP = 9;
const int E_VDATA_TYP = 10;
const int E_UNDET_TYP = 11;

//RX processing state
const int E_LLTF_ST  = 1;
const int E_LTF1_ST  = 2;
const int E_LSIG_ST  = 3;
const int E_HTSIG_ST = 4;
const int E_VSIGA_ST = 5;
const int E_VSIGB_ST = 6;

//ERROR code enumerates
const int ERR_SYNC_FAILURE          = 1;
const int ERR_SAMP_INDEX_OUTOFRANGE = 2;
const int ERR_UNDEF_OFDMSYMTYPE     = 3;
const int ERR_MCS_INDEX_OUTOFRANGE  = 4;
const int ERR_UNDEF_DATA_RATE       = 5;
const int ERR_LENGTH_OUTOFRANGE     = 6;
const int ERR_NUMOFSYMB_OUTOFRANGE  = 7;
const int ERR_FRMTDET_LSIG_MISMATCH = 8; //Format Detection output contradicting with L-SIG decode
const int ERR_INVALID_NSS           = 9;
const int ERR_INVALID_SHORTGI       = 10;
const int ERR_INVALID_MCS_INDEX     = 11;
const int ERR_INVALID_NUMOFSYMB     = 12;
const int ERR_LSIG_PARITY_FAIL      = 13;
const int ERR_VSIGA_CRC_FAIL        = 14;
const int ERR_SIGA_CRC_FAIL         = 15;
const int ERR_SIGB_CRC_FAIL         = 16;
const int ERR_DATA_CRC_FAIL         = 17;
const int ERR_NO_DATA_CRC           = 18;
const int ERR_INVALID_PDU_LENGTH    = 19;
const int ERR_ZERO_SCRMBSEED        = 20;
const int ERR_NO_ERR                = 100;


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
