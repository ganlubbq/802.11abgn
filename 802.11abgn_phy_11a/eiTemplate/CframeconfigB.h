#pragma once


// CframeconfigB �Ի���

class CframeconfigB : public CDialog
{
	DECLARE_DYNAMIC(CframeconfigB)

public:
	CframeconfigB(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CframeconfigB();

// �Ի�������
	enum { IDD = IDD_FRAME_CONFIG_B };

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
	afx_msg void OnCbnSelchangeConfigSelectB();
	afx_msg void OnBnClickedButtonConfig();
};
