#pragma once


// CSysConfigWizardStep3 �Ի���

class CSysConfigWizardStep3 : public CPropertyPage
{
	DECLARE_DYNAMIC(CSysConfigWizardStep3)

public:
	CSysConfigWizardStep3();
	virtual ~CSysConfigWizardStep3();

// �Ի�������
	enum { IDD = IDD_SYSCONFIGWIZARD_STEP_3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CBrush m_whiterush;
	CFont m_font_title;
	CFont m_font_content;
	CStatic m_text_title;
	CStatic m_text_content;
	CButton m_btn_viewdetial;//�鿴
	CButton m_btn_deleteitem;//ɾ��
	CListBox m_list;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnSetActive();
	afx_msg void OnSelchangeWizListStep3();
	afx_msg void OnBnClickedButtonViewdetail();
	afx_msg void OnBnClickedButtonDeleteitem();
	virtual LRESULT OnWizardNext();
};
