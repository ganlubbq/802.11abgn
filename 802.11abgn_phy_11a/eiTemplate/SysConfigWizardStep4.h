#pragma once


// CSysConfigWizardStep4 �Ի���

class CSysConfigWizardStep4 : public CPropertyPage
{
	DECLARE_DYNAMIC(CSysConfigWizardStep4)

public:
	CSysConfigWizardStep4();
	virtual ~CSysConfigWizardStep4();

// �Ի�������
	enum { IDD = IDD_SYSCONFIGWIZARD_STEP_4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CBrush m_whiterush;
	CFont m_font_title;
	CFont m_font_content;
	CStatic m_text_title;
	CStatic m_text_content;
	CButton m_btn_test_conn;//��������
	CComboBox m_num_generator;//�źŷ�����������

	CStatic m_sg_text[8];//��ʶ�źŷ�����
	CComboBox m_comb_io_type[8];//I/O����
	//GPIB��ص�ַ
	CComboBox m_gpib_board_index[8];
	CComboBox m_gpib_primary_index[8];
	CComboBox m_gpib_secondary_index[8];
	CIPAddressCtrl m_ipaddr[8];
	CStatic m_status_text[8];

	BOOL m_reset_window;//����һ����ǣ�����ָʾ�ػ�ʱ�Ƿ���Ҫ�������ҳ��
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSelchangeComboIoType1();
	afx_msg void OnSelchangeComboIoType2();
	afx_msg void OnSelchangeComboIoType3();
	afx_msg void OnSelchangeComboIoType4();
	afx_msg void OnSelchangeComboIoType5();
	afx_msg void OnSelchangeComboIoType6();
	afx_msg void OnSelchangeComboIoType7();
	afx_msg void OnSelchangeComboIoType8();
	virtual LRESULT OnWizardNext();
	virtual LRESULT OnWizardBack();
	afx_msg void OnBnClickedBtnTestConn();
	afx_msg void OnStnClickedTextNumGenerator();
};
