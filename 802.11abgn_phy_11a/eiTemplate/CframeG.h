#pragma once


// CframeG �Ի���

class CframeG : public CDialog
{
	DECLARE_DYNAMIC(CframeG)

public:
	CframeG(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CframeG();

// �Ի�������
	enum { IDD = IDD_FRAME_G };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_pic_framediag;
	HBITMAP m_pic_framediag1;
	HBITMAP m_pic_framediag2;
	HBITMAP m_pic_framediag3;
	CComboBox m_ComFramediag;//�����˵�ѡ��ؼ�
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeFrameSelectG();
};
