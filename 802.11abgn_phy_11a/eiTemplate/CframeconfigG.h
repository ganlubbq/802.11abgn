#pragma once


// CframeconfigG �Ի���

class CframeconfigG : public CDialogEx
{
	DECLARE_DYNAMIC(CframeconfigG)

public:
	CframeconfigG(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CframeconfigG();

// �Ի�������
	enum { IDD = IDD_FRAME_CONFIG_G };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_pic_framediag;
	HBITMAP m_pic_framediag1;
	HBITMAP m_pic_framediag2;
	HBITMAP m_pic_framediag3;
	CComboBox m_ComFramediag;//�����˵�ѡ��ؼ�
public:
	afx_msg void OnBnClickedConfigButtonG();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeConfigSelectG();
};
