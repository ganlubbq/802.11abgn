#pragma once


// CSysConfigWizardStep1 �Ի���

class CSysConfigWizardStep1 : public CPropertyPage//����ҳ
{
	DECLARE_DYNAMIC(CSysConfigWizardStep1)

public:
	CSysConfigWizardStep1();
	virtual ~CSysConfigWizardStep1();

// �Ի�������
	enum { IDD = IDD_SYSCONFIGWIZARD_STEP_1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CBrush m_whiterush;
	CFont m_font_title;
	CFont m_font_content;
	CStatic m_text_title;//��������ҳ����
	CStatic m_text_content;//����ҳ��ʾ
	CListBox m_list_function;//����ҳѡ��
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
};
