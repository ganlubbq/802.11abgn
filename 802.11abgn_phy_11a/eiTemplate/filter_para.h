#ifndef _FILTER_PARAM_H_
#define _FILTER_PARAM_H_
//ÂË²¨Æ÷²ÎÊı
typedef struct lowpass{
	int length;
	double wn;
}LPpara;

typedef struct gauss{
	int length;
	double BT;
}Gausspara;
typedef struct cosine{
	int length;
	double alpha;
}Cosinepara;

enum Filtertype{
	lpfilter = 0,
	gaussfilter = 1,
	cosfilter = 2,
	userdefined = 3,
};
typedef struct filterpara{
	Filtertype filtertype;
	Gausspara  gausspara;
	Cosinepara cosinepara;
	LPpara     lppara;
    CString    filepath;
}Filterpara;

#endif