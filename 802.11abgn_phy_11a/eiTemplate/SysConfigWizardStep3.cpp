// SysConfigWizardStep1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "SysConfigWizardStep3.h"
#include "SysConfigWizardStep3ViewDetail.h"
#include "afxdialogex.h"
#include "SysConfigWizard.h"

using namespace rapidxml;

// CSysConfigWizardStep3 �Ի���

IMPLEMENT_DYNAMIC(CSysConfigWizardStep3, CPropertyPage)

CSysConfigWizardStep3::CSysConfigWizardStep3()
	: CPropertyPage(CSysConfigWizardStep3::IDD)
{
	m_whiterush.CreateSolidBrush(RGB(255,255,255));
	m_font_title.CreateFont(19,0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
		DRAFT_QUALITY,FIXED_PITCH|FF_SWISS|FF_SCRIPT,"΢���ź�");
	m_font_content.CreatePointFont(90,"΢���ź�");
}

CSysConfigWizardStep3::~CSysConfigWizardStep3()
{
}

void CSysConfigWizardStep3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TITLE_TEXT_STEP3, m_text_title);
	DDX_Control(pDX, IDC_CONTENT_TEXT_STEP3, m_text_content);
	DDX_Control(pDX, IDC_WIZ_LIST_STEP3, m_list);
	DDX_Control(pDX, IDC_BUTTON_VIEWDETAIL, m_btn_viewdetial);
	DDX_Control(pDX, IDC_BUTTON_DELETEITEM, m_btn_deleteitem);
}


BEGIN_MESSAGE_MAP(CSysConfigWizardStep3, CPropertyPage)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_LBN_SELCHANGE(IDC_WIZ_LIST_STEP3, &CSysConfigWizardStep3::OnSelchangeWizListStep3)
	ON_BN_CLICKED(IDC_BUTTON_VIEWDETAIL, &CSysConfigWizardStep3::OnBnClickedButtonViewdetail)
	ON_BN_CLICKED(IDC_BUTTON_DELETEITEM, &CSysConfigWizardStep3::OnBnClickedButtonDeleteitem)
END_MESSAGE_MAP()


// CSysConfigWizardStep3 ��Ϣ�������


BOOL CSysConfigWizardStep3::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_text_title.MoveWindow(25,2,300,50);
	m_text_title.SetFont(&m_font_title);
	m_text_title.SetWindowText("��������");
	m_text_content.MoveWindow(45,25,400,40);
	m_text_content.SetFont(&m_font_content);
	m_text_content.SetWindowText("����±��б����Ѿ�����������Ϣ������ֱ��ѡ������֮һ\r\n��Ҳ����ͨ��<�½�>ȥ�����µ�������Ϣ");

	m_btn_deleteitem.SetFont(&m_font_content);
	m_btn_viewdetial.SetFont(&m_font_content);

	m_list.SetFont(&m_font_content);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CSysConfigWizardStep3::OnPaint()
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
	/* ���ݵ�һ����ѡ�������ѡ���ȡ��Ӧ���ļ������б�ĳ�ʼ��             */
	/************************************************************************/
	CSysConfigWizard* p_wiz = (CSysConfigWizard*)GetParent();
	/************************************************************************/
	/* ������Ӧ��xml�ļ��������ļ���������д�˴���listӦ����ʾ��������      */
	/************************************************************************/
	file<> fdoc(p_wiz->m_config_list_dir.GetBuffer());//����һ����д�Ļ�����ָ��
	xml_document<> doc;
	doc.parse<0>(fdoc.data());
	// ��ȡ���ڵ�  
	xml_node<>* p_WizardList = doc.first_node();
	//����б�
	while(m_list.GetCount())
	{
		m_list.DeleteString(0);
	}
	//��ȡ��������ѡ��
	int i = 0;
	for (xml_node<>* p_ConfigOption = p_WizardList->first_node();p_ConfigOption;p_ConfigOption=p_ConfigOption->next_sibling(),i++)
	{
		m_list.InsertString(i,p_ConfigOption->value());
	}
	m_list.SetCurSel(0);
	m_btn_deleteitem.EnableWindow(FALSE);
	m_btn_viewdetial.EnableWindow(FALSE);

	// ��Ϊ��ͼ��Ϣ���� CPropertyPage::OnPaint()
}


HBRUSH CSysConfigWizardStep3::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


BOOL CSysConfigWizardStep3::OnSetActive()
{
	// TODO: �ڴ����ר�ô����/����û���
	CPropertySheet* psheet = (CPropertySheet*) GetParent();
	psheet->SetWizardButtons(PSWIZB_NEXT|PSWIZB_BACK);
	return CPropertyPage::OnSetActive();
}


void CSysConfigWizardStep3::OnSelchangeWizListStep3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	switch(m_list.GetCurSel())
	{
	case 0:
		m_btn_viewdetial.EnableWindow(FALSE);
		m_btn_deleteitem.EnableWindow(FALSE);
		break;
	default:
		m_btn_viewdetial.EnableWindow(TRUE);
		m_btn_deleteitem.EnableWindow(TRUE);
		break;
	}
}


void CSysConfigWizardStep3::OnBnClickedButtonViewdetail()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CSysConfigWizardStep3ViewDetail�̳���CDiag��
	CSysConfigWizardStep3ViewDetail d_view_detail;
	CSysConfigWizard* p_wiz = (CSysConfigWizard*)GetParent();
	CString str_temp = "";
	m_list.GetText(m_list.GetCurSel(),str_temp);
	d_view_detail.m_file_name = str_temp;//���������ļ���
	d_view_detail.m_file_dir = p_wiz->m_option_dir;
	d_view_detail.DoModal();
}


void CSysConfigWizardStep3::OnBnClickedButtonDeleteitem()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if (IDOK == MessageBox("ȷ��ɾ��������ѡ�","ȷ��ɾ��",MB_ICONWARNING|MB_OKCANCEL) && m_list.GetCurSel()!=0)
	{
		
		CString current_name = "";//����Ҫɾ��ѡ�������
		m_list.GetText(m_list.GetCurSel(),current_name);
		m_list.DeleteString(m_list.GetCurSel());
		m_list.SetCurSel(0);
		m_btn_viewdetial.EnableWindow(FALSE);
		m_btn_deleteitem.EnableWindow(FALSE);
	}
}


LRESULT CSysConfigWizardStep3::OnWizardNext()
{
	// TODO: �ڴ����ר�ô����/����û���
	CSysConfigWizard* p_wiz = (CSysConfigWizard*)GetParent();
	CString option_name = "";

	if (m_list.GetCurSel()==0)
	{
		p_wiz->m_option_name = "";
	}else{
		m_list.GetText(m_list.GetCurSel(),option_name);
		p_wiz->m_option_name = option_name;
	}
	
	return CPropertyPage::OnWizardNext();
}
