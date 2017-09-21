// SysConfigWizardStep1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "SysConfigWizardStep5.h"
#include "afxdialogex.h"
#include "SysConfigWizard.h"

// CSysConfigWizardStep5 �Ի���

IMPLEMENT_DYNAMIC(CSysConfigWizardStep5, CPropertyPage)

CSysConfigWizardStep5::CSysConfigWizardStep5()
	: CPropertyPage(CSysConfigWizardStep5::IDD)
{
	m_whiterush.CreateSolidBrush(RGB(255,255,255));
	m_font_title.CreateFont(19,0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
		DRAFT_QUALITY,FIXED_PITCH|FF_SWISS|FF_SCRIPT,"΢���ź�");
	m_font_content.CreatePointFont(90,"΢���ź�");
	b_send_conn = TRUE;
}

CSysConfigWizardStep5::~CSysConfigWizardStep5()
{
}

void CSysConfigWizardStep5::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TITLE_TEXT_STEP5, m_text_title);
	DDX_Control(pDX, IDC_CONTENT_TEXT_STEP5, m_text_content);
	DDX_Control(pDX, IDC_WZD_CONNECTION_INFO, m_connection_info);
}


BEGIN_MESSAGE_MAP(CSysConfigWizardStep5, CPropertyPage)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSysConfigWizardStep5 ��Ϣ�������


BOOL CSysConfigWizardStep5::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_text_title.MoveWindow(25,2,300,50);
	m_text_title.SetFont(&m_font_title);
	m_text_title.SetWindowText("���岽��");
	m_text_content.MoveWindow(45,25,300,40);
	m_text_content.SetFont(&m_font_content);
	m_text_content.SetWindowText("�����źŷ������� I/O �ӿ�����״̬");

	m_connection_info.SetFont(&m_font_content);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CSysConfigWizardStep5::OnPaint()
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
	/* ����������Ӧ��Ӧ��һ�����õ��������                                 */
	/************************************************************************/
	if (b_send_conn)
	{
		b_send_conn = FALSE;
		CSysConfigWizard* p_wiz = (CSysConfigWizard*)GetParent();
		int num_instr = p_wiz->m_num_instruments;
		ViStatus stat = 0;
		stat = viOpenDefaultRM(&(p_wiz->defaultRM));//���ڳ�ʼ������λVISAϵͳ,defaultRM---VISA��Դ������
		Sleep(10);
		//�����������������ͳ̿������������״̬��
		for (int i = 0;i<num_instr;i++)
		{
			//viOpen ���ڽ��������������֮����ϵ�ĻỰ
			//vi[i]���صĶԻ�ͨ����ʶ���������
			p_wiz->vi_error_info[i] = viOpen(p_wiz->defaultRM,p_wiz->str_conn[i].GetBuffer(),VI_NULL,VI_NULL,&(p_wiz->vi[i]));
			Sleep(10);
			if (p_wiz->vi_error_info[i]>=0)
			{
				//���ûỰ����
				viSetAttribute(p_wiz->vi[i],VI_ATTR_TMO_VALUE,2000);//������С�ĳ�ʱֵ�����룩
				Sleep(10);
				viSetAttribute(p_wiz->vi[i],VI_ATTR_TERMCHAR_EN,VI_TRUE);//�յ��ж��ַ��жϵ�ǰ������
				Sleep(10);
				viSetAttribute(p_wiz->vi[i],VI_ATTR_TERMCHAR,'\n');//���ûس�Ϊ�ж��ַ�
				Sleep(10);
			}
		}

		//�ж����������Ƿ�ɹ�(�����������ӳɹ�����TRUE,���򷵻�FALSE)
		BOOL temp_connected = TRUE;
		for (int i = 0;i<num_instr;i++)
		{
			temp_connected &= (p_wiz->vi_error_info[i] >= 0);
		}
		p_wiz->b_instr_connected = temp_connected;

		if (temp_connected == FALSE) {
			MessageBox( "�豸���Ӵ���", "Init Error!", MB_OK | MB_ICONERROR );
			OnWizardBack();
			CSysConfigWizard* p_wiz = (CSysConfigWizard*)GetParent();
			p_wiz->SetActivePage(3);
		}
	}

	
	// ��Ϊ��ͼ��Ϣ���� CPropertyPage::OnPaint()
}


HBRUSH CSysConfigWizardStep5::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


BOOL CSysConfigWizardStep5::OnSetActive()
{
	// TODO: �ڴ����ר�ô����/����û���
	CPropertySheet* psheet = (CPropertySheet*) GetParent();
	psheet->SetWizardButtons(PSWIZB_NEXT|PSWIZB_BACK);
	return CPropertyPage::OnSetActive();
}


LRESULT CSysConfigWizardStep5::OnWizardBack()
{
	// TODO: �ڴ����ר�ô����/����û���
	/************************************************************************/
	/* �������һҳ�����˷��ذ�ť��˵���û�Ҫ���¶���������Ϣ��������Ҫ�Ͽ� */
	/* ���гɹ������ӣ�׼����һ�γ̿�����ķ���                             */
	/************************************************************************/
	b_send_conn = TRUE;
	CSysConfigWizard* p_wiz = (CSysConfigWizard*)GetParent();
	int num_instr = p_wiz->m_num_instruments;
	ViStatus stat = 0;
	for (int i = 0;i<num_instr;i++)
	{
		if (p_wiz->vi_error_info >= 0)
		{
			//�Ͽ����ӳɹ�������
			stat = viClear(p_wiz->vi[i]);//send Clear command 
			stat = viClose(p_wiz->vi[i]);//�ͷŻỰ���Ự�е�����
		}
	}
	stat = viClose(p_wiz->defaultRM);
	return CPropertyPage::OnWizardBack();
}
