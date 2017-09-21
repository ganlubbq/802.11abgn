#pragma once
#include "define_param.h"

// CframeGeneralG �Ի���

class CframeGeneralG : public CDialog
{
	DECLARE_DYNAMIC(CframeGeneralG)

public:
	CframeGeneralG(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CframeGeneralG();

// �Ի�������
	enum { IDD = IDD_GENERAL_G };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
