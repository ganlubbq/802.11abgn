// SysConfigWizardStep1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "SysConfigWizardStep1.h"
#include "afxdialogex.h"
#include "SysConfigWizard.h"


// CSysConfigWizardStep1 �Ի���

IMPLEMENT_DYNAMIC(CSysConfigWizardStep1, CPropertyPage)

CSysConfigWizardStep1::CSysConfigWizardStep1()
	: CPropertyPage(CSysConfigWizardStep1::IDD)
{
	m_whiterush.CreateSolidBrush(RGB(255,255,255));
	m_font_title.CreateFont(19,0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
		DRAFT_QUALITY,FIXED_PITCH|FF_SWISS|FF_SCRIPT,"΢���ź�");
	m_font_content.CreatePointFont(90,"΢���ź�");//9-point font
}

CSysConfigWizardStep1::~CSysConfigWizardStep1()
{
}

void CSysConfigWizardStep1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TITLE_TEXT_STEP1, m_text_title);
	DDX_Control(pDX, IDC_CONTENT_TEXT_STEP1, m_text_content);
	DDX_Control(pDX, IDC_WIZ_LIST_STEP1, m_list_function);
}


BEGIN_MESSAGE_MAP(CSysConfigWizardStep1, CPropertyPage)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSysConfigWizardStep1 ��Ϣ�������


BOOL CSysConfigWizardStep1::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	/************************************************************************/
	/* ���ø����ؼ�����ʾ������ı�                                         */
	/************************************************************************/
	m_text_title.MoveWindow(25,2,300,50);
	m_text_title.SetFont(&m_font_title);
	m_text_title.SetWindowText("��һ����");

	m_text_content.MoveWindow(45,25,360,40);
	m_text_content.SetFont(&m_font_content);
	m_text_content.SetWindowText("ѡ���������������б����ѡ��һ��������������");

	m_list_function.SetFont(&m_font_content);
	m_list_function.InsertString(0,"������");
	m_list_function.InsertString(1,"������");
	m_list_function.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CSysConfigWizardStep1::OnPaint()
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
	dc.SelectObject(pen_top);//ѡ�񻭱�
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

//calls this member function when a child control is about to be drawn
HBRUSH CSysConfigWizardStep1::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//the brush that is to be used for painting the control background
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (m_text_title.m_hWnd == pWnd->m_hWnd || m_text_content.m_hWnd == pWnd->m_hWnd)
	{
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkColor(RGB(255, 255, 255));//��̬�ı��򱳾�ɫ
		return m_whiterush;
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


BOOL CSysConfigWizardStep1::OnSetActive()
{
	// TODO: �ڴ����ר�ô����/����û���
	CPropertySheet* psheet = (CPropertySheet*) GetParent();
	//��һҳ
	//�������Ա�ֻ�С���һ������ť
	psheet->SetWizardButtons(PSWIZB_NEXT);
	return CPropertyPage::OnSetActive();
}


LRESULT CSysConfigWizardStep1::OnWizardNext()
{
	// TODO: �ڴ����ר�ô����/����û���
	/************************************************************************/
	/* ��һ����������Ҫ��Ϊ��ȷ��ʹ�õ���������                             */
	/************************************************************************/
	CSysConfigWizard* p_wiz = (CSysConfigWizard*)GetParent();
	int cur_sel = m_list_function.GetCurSel();
	if(!cur_sel)
	{
		p_wiz->m_function_choice = cur_sel;
		p_wiz->m_num_instruments = 1;
	}
	else{
	      p_wiz->m_function_choice = cur_sel;
	      p_wiz->m_num_instruments = 2;
	}
	CString str = "";
	str.Format("./user/config_list/Instr_Sel_%d.conf",cur_sel);
	p_wiz->m_config_list_dir = str;
	str.Format("./user/Instr_Sel_%d/",cur_sel);
	p_wiz->m_option_dir = str;
	
	return CPropertyPage::OnWizardNext();
}
