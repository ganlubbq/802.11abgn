#ifndef _MPDUPARA_H_
#define _MPDUPARA_H_

enum sourcemode{
	DPN9 = 0,
	DPN15 = 1,
	DALL0 = 2,
	DUserFile = 3,
};
typedef struct MPDU {
	sourcemode s_mode;
	int DataSource_len;
	int mac_Header;
	int mac_FCS;
	int MPDU_len;
	int A_Subframe_len;
	int numOFmpdus;
	MPDU(){
		s_mode = DPN9;
		DataSource_len = 1024;
		mac_Header = 1;
		mac_FCS = 1;
		MPDU_len = 1058;
		A_Subframe_len = 1062;
		numOFmpdus = 0;
	}
}MpduPara;
#endif