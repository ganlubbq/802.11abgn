#pragma once


// CframeConfig �Ի���

class CframeConfig : public CDialog
{
	DECLARE_DYNAMIC(CframeConfig)

public:
	CframeConfig(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CframeConfig();

// �Ի�������
	enum { IDD = IDD_FRAME_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	CStatic m_pic_framediag;
	HBITMAP m_pic_framediag1;
	HBITMAP m_pic_framediag2;
	HBITMAP m_pic_framediag3;
	CComboBox m_ComFramediag;//�����˵�ѡ��ؼ�
public:
	afx_msg void OnPaint();
	afx_msg void OnCbnSelchangeFrameSeclect();
	afx_msg void OnBnClickedConfig();
};
