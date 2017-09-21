#pragma once
#include "define_param.h"

// CframeGeneralG 对话框

class CframeGeneralG : public CDialog
{
	DECLARE_DYNAMIC(CframeGeneralG)

public:
	CframeGeneralG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CframeGeneralG();

// 对话框数据
	enum { IDD = IDD_GENERAL_G };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMFCPropertyGridCtrl     m_MFCPropertyGrid_Mac_General;
	CMFCPropertyGridProperty* pGroup_General;
	CMFCPropertyGridProperty* pProp1;
	CMFCPropertyGridProperty* pProp2;
	CMFCPropertyGridProperty* pProp3;
	CMFCPropertyGridProperty* pProp4;
	CMFCPropertyGridProperty* pProp5;
	CMFCPropertyGridProperty* pProp6;
	CMFCPropertyGridProperty* pProp7;
	CMFCPropertyGridProperty* pProp8;
	CMFCPropertyGridProperty* pProp9;

	CMFCPropertyGridProperty* pGroup_RTS;
	CMFCPropertyGridProperty* pProp10;
	CMFCPropertyGridProperty* pProp11;
	CMFCPropertyGridProperty* pProp12;
	CMFCPropertyGridProperty* pProp13;

	CMFCPropertyGridProperty* pGroup_CTS;
	CMFCPropertyGridProperty* pProp14;
	CMFCPropertyGridProperty* pProp15;
	CMFCPropertyGridProperty* pProp16;
public:
	virtual BOOL OnInitDialog();
	FrameType frametype;
};
