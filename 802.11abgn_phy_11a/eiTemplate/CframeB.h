#pragma once


// CframeB �Ի���

class CframeB : public CDialog
{
	DECLARE_DYNAMIC(CframeB)

public:
	CframeB(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CframeB();

// �Ի�������
	enum { IDD = IDD_FRAME_B };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_pic_framediag;
	HBITMAP m_pic_framediag1;
	HBITMAP m_pic_framediag2;
	HBITMAP m_pic_framediag3;
	CComboBox m_ComFramediag;//�����˵�ѡ��ؼ�
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeFrameSelectB();
	afx_msg void OnPaint();
};
