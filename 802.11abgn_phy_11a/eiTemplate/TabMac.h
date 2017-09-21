#pragma once
#include "config.h"

// CTabMac �Ի���

class CTabMac : public CDialog
{
	DECLARE_DYNAMIC(CTabMac)

public:
	CTabMac(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabMac();

// �Ի�������
	enum { IDD = IDD_TAB_MAC_INFO };
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnOK();
	BOOL m_finished_ini;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnPropertyChanged(__in WPARAM wparam,__in LPARAM lparam);
	void Point();
public:
	config		 *m_configIndex;
	CListCtrl	 m_configlist;
	CFont        m_font;
	//add pGroup
	CMFCPropertyGridCtrl     m_MFCPropertyGridOne; //m_MFCPropertyGridA
	CMFCPropertyGridCtrl     m_MFCPropertyGridB;   //a/b/gЭ������б�
	CMFCPropertyGridCtrl     m_MFCPropertyGridG;
	CMFCPropertyGridCtrl     m_MFCPropertyGridN;

	CMFCPropertyGridProperty *pGroup01;
	CMFCPropertyGridProperty *pGroup02;

	CMFCPropertyGridProperty *pGroupB01;
	CMFCPropertyGridProperty *pGroupB02;

	CMFCPropertyGridProperty *pGroupG01;
	CMFCPropertyGridProperty *pGroupG02;

	CMFCPropertyGridProperty *pGroupN01;
	CMFCPropertyGridProperty *pGroupN02;

	afx_msg void OnDblclkListprotocol(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickListprotocol(NMHDR *pNMHDR, LRESULT *pResult);
};
