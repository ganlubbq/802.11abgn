// SysConfigWizardStep1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "SysConfigWizardStep6.h"
#include "afxdialogex.h"


// CSysConfigWizardStep6 �Ի���

IMPLEMENT_DYNAMIC(CSysConfigWizardStep6, CPropertyPage)

CSysConfigWizardStep6::CSysConfigWizardStep6()
	: CPropertyPage(CSysConfigWizardStep6::IDD)
{
	m_whiterush.CreateSolidBrush(RGB(255,255,255));
	m_font_title.CreateFont(19,0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
		DRAFT_QUALITY,FIXED_PITCH|FF_SWISS|FF_SCRIPT,"΢���ź�");
	m_font_content.CreatePointFont(90,"΢���ź�");
}

CSysConfigWizardStep6::~CSysConfigWizardStep6()
{
}

void CSysConfigWizardStep6::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TITLE_TEXT_STEP6, m_text_title);
	DDX_Control(pDX, IDC_CONTENT_TEXT_STEP6, m_text_content);
	DDX_Control(pDX, IDC_WIZ_NAME, m_edit_name);
	DDX_Control(pDX, IDC_WIZ_SUMMARY, m_edit_summary);
}


BEGIN_MESSAGE_MAP(CSysConfigWizardStep6, CPropertyPage)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSysConfigWizardStep6 ��Ϣ�������


BOOL CSysConfigWizardStep6::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_text_title.MoveWindow(25,2,300,50);
	m_text_title.SetFont(&m_font_title);
	m_text_title.SetWindowText("��������");
	m_text_content.MoveWindow(45,25,300,40);
	m_text_content.SetFont(&m_font_content);
	m_text_content.SetWindowText("���������õ��������Ʋ���ʼʹ��Ӳ��ϵͳ");
	((CStatic*)GetDlgItem(IDC_SUMMARY_SYS_STEP6))->SetFont(&m_font_content);
	((CStatic*)GetDlgItem(IDC_NAME_SYS_STEP6))->SetFont(&m_font_content);

	m_edit_name.SetFont(&m_font_content);
	m_edit_name.SetWindowText("Untitled");

	m_edit_summary.SetFont(&m_font_content);
	m_edit_summary.SetWindowText("��ʾ��ϸ��Ϣ");


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CSysConfigWizardStep6::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	/************************************************************************/
	/* �����Ϸ��İ�ɫ����                                                   */
	/************************************************************************/
	CBrush brush(RGB(255,255,255));
	dc.FillRect(CRect(0,0,620,66),&brush);
	/************************************************************************/
	/* �����Ϸ��ķָ���                                                     */
	/************************************************************************/
	CPen pen_top,pen_bottom;
	pen_top.CreatePen(PS_SOLID,1,RGB(160,160,160));
	dc.SelectObject(pen_top);
	dc.MoveTo(0,67);
	dc.LineTo(620,67);
	pen_bottom.CreatePen(PS_SOLID,1,RGB(255,255,255));
	dc.SelectObject(pen_bottom);
	dc.MoveTo(0,68);
	dc.LineTo(620,68);
	/************************************************************************/
	/* ͨ������Ĵ��룬���CSysConfigWizard�е�ȫ�ֱ���������ʵ�ֽ����ڲ�ͬ */
	/* ��������ʵ���ض�����ʾЧ��											*/
	/************************************************************************/


	// ��Ϊ��ͼ��Ϣ���� CPropertyPage::OnPaint()
}


HBRUSH CSysConfigWizardStep6::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (m_text_title.m_hWnd == pWnd->m_hWnd || m_text_content.m_hWnd == pWnd->m_hWnd)
	{
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkColor(RGB(255, 255, 255));
		return m_whiterush;
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


BOOL CSysConfigWizardStep6::OnSetActive()
{
	// TODO: �ڴ����ר�ô����/����û���
	CPropertySheet* psheet = (CPropertySheet*) GetParent();
	psheet->SetWizardButtons(PSWIZB_BACK|PSWIZB_FINISH);
	return CPropertyPage::OnSetActive();
}
