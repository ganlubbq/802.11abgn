#pragma once


// CSysConfigWizardStep1 对话框

class CSysConfigWizardStep1 : public CPropertyPage//属性页
{
	DECLARE_DYNAMIC(CSysConfigWizardStep1)

public:
	CSysConfigWizardStep1();
	virtual ~CSysConfigWizardStep1();

// 对话框数据
	enum { IDD = IDD_SYSCONFIGWIZARD_STEP_1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CBrush m_whiterush;
	CFont m_font_title;
	CFont m_font_content;
	CStatic m_text_title;//设置配置页标题
	CStatic m_text_content;//配置页提示
	CListBox m_list_function;//配置页选项
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
};
