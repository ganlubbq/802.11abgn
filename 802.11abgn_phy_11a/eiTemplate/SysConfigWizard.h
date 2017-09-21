#pragma once

#include "SysConfigWizardStep1.h"
#include "SysConfigWizardStep2.h"
#include "SysConfigWizardStep3.h"
#include "SysConfigWizardStep4.h"
#include "SysConfigWizardStep5.h"
#include "SysConfigWizardStep6.h"
// CSysConfigWizard

class CSysConfigWizard : public CPropertySheet//��ʾ���Ա�Ҳ��Ϊ"ѡ��"�Ի���
{
	DECLARE_DYNAMIC(CSysConfigWizard)

public:
	CSysConfigWizard(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CSysConfigWizard(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CSysConfigWizard();
private:
	CFont m_font;//Ϊͳһҳ���������÷������������wizard�İ�ť����
	/************************************************************************/
	/* 6�����ò����ָ������                                                */
	/************************************************************************/
	CSysConfigWizardStep1 *m_step1;
	CSysConfigWizardStep2 *m_step2;
	CSysConfigWizardStep3 *m_step3;
	CSysConfigWizardStep4 *m_step4;
	CSysConfigWizardStep5 *m_step5;
	CSysConfigWizardStep6 *m_step6;
protected:
	DECLARE_MESSAGE_MAP()
public:
	/************************************************************************/
	/* ����������صı�������Щ����Ҳ�Ǳ���Ҫ���õ���Ҫ����               */
	/************************************************************************/
	ViSession defaultRM;
	ViSession vi[8];//ָ���뱻��������ص�ViSession����
	ViStatus vi_error_info[8];//ViStatus ����״ֵ̬����
	CString str_conn[8];//���������ĳ̿�����
	BOOL b_instr_connected;
	int m_function_choice;//��ǰѡ���������
	int m_num_instruments;//��ǰ���õ���������

	CString m_option_dir;//��ǰ����ѡ�����ڵ��ļ���
	CString m_option_name;//��ǰ����ѡ����ļ���
	CString m_config_list_dir;//��ǰ���ð�����ѡ����ļ�·�������ļ�����ȷ������������ʾ�û��ѱ��������ѡ��

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};


