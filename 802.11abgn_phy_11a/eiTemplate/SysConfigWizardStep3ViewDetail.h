#pragma once


// CSysConfigWizardStep3ViewDetail �Ի���

class CSysConfigWizardStep3ViewDetail : public CDialog
{
	DECLARE_DYNAMIC(CSysConfigWizardStep3ViewDetail)

public:
	CSysConfigWizardStep3ViewDetail(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSysConfigWizardStep3ViewDetail();

// �Ի�������
	enum { IDD = IDD_SYSCONFIGWIZARD_STEP_3_VIEW_DETAIL };
private:
	CFont m_font_content;
	CMFCPropertyGridCtrl m_content_instr_config;//��ʾ��������Ŀؼ�
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_file_dir;//�����ļ�Ŀ¼
	CString m_file_name;//�����ļ���
	virtual BOOL OnInitDialog();
};
