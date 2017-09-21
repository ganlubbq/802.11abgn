#include<iostream>
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
extern const int E_LONG_CP    ;
extern const int E_SHORT_CP   ;
/*
//MIMO mode
extern const int SU   ;
extern const int MU   ;*/

//PPDU FORMAT ENUMERATES
extern const int Legacy       ; //Legacy 
extern const int non_HT_DUP   ; 
extern const int HT_MM        ; 
extern const int HT_GF        ; 
//extern const int E_VHT          ; //VHT
extern const int UNDET        ; //undetermined

//TX FORMAT ENUMERATOR
//used to index the configuration dependent parameter table
extern const int E_LEG20M      ;
extern const int E_HT20M       ;
extern const int E_HT40M       ; 
/*extern const int E_VHT20M      ;
extern const int E_VHT40M      ; 
extern const int E_VHT80M      ;
extern const int E_VHT160M     ;
extern const int E_VHT80P80M   ;*/

//CHANNEL BANDWIDTH
extern const int HT_CBW20      ;
extern const int HT_CBW40      ;
extern const int HT_CBW80      ;
extern const int HT_CBW80P80   ;
extern const int HT_CBW160     ;

extern const int NON_HT_CBW20    ;  //all other non-HT formats
extern const int NON_HT_CBW40    ;  //40M duplicate
extern const int NON_HT_CBW80    ;  //80M duplicate
extern const int NON_HT_CBW160   ;  //160M duplicate

//RX vectors update stages
extern const int E_SYNC   ;
extern const int E_LSIG   ;
extern const int E_FRMT   ;
extern const int E_VSIGA  ;
extern const int E_VSIGB  ;
extern const int E_HTSIG  ;

//OFDM symbol type enumerates
extern const int E_LLTF_TYP    ;
extern const int E_LTF1_TYP    ;
extern const int E_LSIG_TYP    ;
extern const int E_HTSIG_TYP   ;
extern const int E_VSIGA_TYP   ;
extern const int E_VSTF_TYP    ;
extern const int E_VLTF_TYP    ;
extern const int E_VSIGB_TYP   ;
extern const int E_LDATA_TYP   ;
extern const int E_VDATA_TYP   ;
extern const int E_UNDET_TYP   ;

//RX processing state
extern const int E_LLTF_ST    ;
extern const int E_LTF1_ST    ;
extern const int E_LSIG_ST    ;
extern const int E_HTSIG_ST   ;
extern const int E_VSIGA_ST   ;
extern const int E_VSIGB_ST   ;

//ERROR code enumerates
extern const int ERR_SYNC_FAILURE            ;
extern const int ERR_SAMP_INDEX_OUTOFRANGE   ;
extern const int ERR_UNDEF_OFDMSYMTYPE       ;
extern const int ERR_MCS_INDEX_OUTOFRANGE    ;
extern const int ERR_UNDEF_DATA_RATE         ;
extern const int ERR_LENGTH_OUTOFRANGE       ;
extern const int ERR_NUMOFSYMB_OUTOFRANGE    ;
extern const int ERR_FRMTDET_LSIG_MISMATCH   ; //Format Detection output contradicting with L-SIG decode
extern const int ERR_INVALID_NSS             ;
extern const int ERR_INVALID_SHORTGI         ;
extern const int ERR_INVALID_MCS_INDEX       ;
extern const int ERR_INVALID_NUMOFSYMB       ;
extern const int ERR_LSIG_PARITY_FAIL        ;
extern const int ERR_VSIGA_CRC_FAIL          ;
extern const int ERR_SIGA_CRC_FAIL           ;
extern const int ERR_SIGB_CRC_FAIL           ;
extern const int ERR_DATA_CRC_FAIL           ;
extern const int ERR_NO_DATA_CRC             ;
extern const int ERR_INVALID_PDU_LENGTH      ;
extern const int ERR_ZERO_SCRMBSEED          ;
extern const int ERR_NO_ERR                  ;

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
