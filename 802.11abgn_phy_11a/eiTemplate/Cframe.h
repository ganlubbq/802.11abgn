#pragma once
#include "afxwin.h"


// Cframe �Ի���

class Cframe : public CDialog
{
	DECLARE_DYNAMIC(Cframe)

public:
	Cframe(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Cframe();

// �Ի�������
	enum { IDD = IDD_FRAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CStatic m_pic_framediag;
	HBITMAP m_pic_framediag1;
	HBITMAP m_pic_framediag2;
	HBITMAP m_pic_framediag3;
	CComboBox m_ComFramediag;//�����˵�ѡ��ؼ�
	afx_msg void OnCbnSelchangeFrameSeclect();
	afx_msg void OnPaint();
};
