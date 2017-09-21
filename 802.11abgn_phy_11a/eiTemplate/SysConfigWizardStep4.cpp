// SysConfigWizardStep1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "SysConfigWizardStep4.h"
#include "afxdialogex.h"
#include "SysConfigWizard.h"
#include "MainFrm.h"

// CSysConfigWizardStep4 �Ի���

IMPLEMENT_DYNAMIC(CSysConfigWizardStep4, CPropertyPage)

CSysConfigWizardStep4::CSysConfigWizardStep4()
	: CPropertyPage(CSysConfigWizardStep4::IDD)
{
	m_whiterush.CreateSolidBrush(RGB(255,255,255));
	m_font_title.CreateFont(19,0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
		DRAFT_QUALITY,FIXED_PITCH|FF_SWISS|FF_SCRIPT,"΢���ź�");
	m_font_content.CreatePointFont(90,"΢���ź�");
	m_reset_window = TRUE;
}

CSysConfigWizardStep4::~CSysConfigWizardStep4()
{
}

void CSysConfigWizardStep4::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TITLE_TEXT_STEP4, m_text_title);
	DDX_Control(pDX, IDC_CONTENT_TEXT_STEP4, m_text_content);
	DDX_Control(pDX, IDC_BTN_TEST_CONN, m_btn_test_conn);
	DDX_Control(pDX, IDC_SIGNAL_GEN_TEXT1, m_sg_text[0]);
	DDX_Control(pDX, IDC_SIGNAL_GEN_TEXT2, m_sg_text[1]);
	DDX_Control(pDX, IDC_SIGNAL_GEN_TEXT3, m_sg_text[2]);
	DDX_Control(pDX, IDC_SIGNAL_GEN_TEXT4, m_sg_text[3]);
	DDX_Control(pDX, IDC_SIGNAL_GEN_TEXT5, m_sg_text[4]);
	DDX_Control(pDX, IDC_SIGNAL_GEN_TEXT6, m_sg_text[5]);
	DDX_Control(pDX, IDC_SIGNAL_GEN_TEXT7, m_sg_text[6]);
	DDX_Control(pDX, IDC_SIGNAL_GEN_TEXT8, m_sg_text[7]);
	DDX_Control(pDX, IDC_COMBO_IO_TYPE1, m_comb_io_type[0]);
	DDX_Control(pDX, IDC_COMBO_IO_TYPE2, m_comb_io_type[1]);
	DDX_Control(pDX, IDC_COMBO_IO_TYPE3, m_comb_io_type[2]);
	DDX_Control(pDX, IDC_COMBO_IO_TYPE4, m_comb_io_type[3]);
	DDX_Control(pDX, IDC_COMBO_IO_TYPE5, m_comb_io_type[4]);
	DDX_Control(pDX, IDC_COMBO_IO_TYPE6, m_comb_io_type[5]);
	DDX_Control(pDX, IDC_COMBO_IO_TYPE7, m_comb_io_type[6]);
	DDX_Control(pDX, IDC_COMBO_IO_TYPE8, m_comb_io_type[7]);
	DDX_Control(pDX, IDC_COMBO_NUM_GENERATOR, m_num_generator);
	DDX_Control(pDX, IDC_GPIB_BOARD_INDEX1, m_gpib_board_index[0]);
	DDX_Control(pDX, IDC_GPIB_BOARD_INDEX2, m_gpib_board_index[1]);
	DDX_Control(pDX, IDC_GPIB_BOARD_INDEX3, m_gpib_board_index[2]);
	DDX_Control(pDX, IDC_GPIB_BOARD_INDEX4, m_gpib_board_index[3]);
	DDX_Control(pDX, IDC_GPIB_BOARD_INDEX5, m_gpib_board_index[4]);
	DDX_Control(pDX, IDC_GPIB_BOARD_INDEX6, m_gpib_board_index[5]);
	DDX_Control(pDX, IDC_GPIB_BOARD_INDEX7, m_gpib_board_index[6]);
	DDX_Control(pDX, IDC_GPIB_BOARD_INDEX8, m_gpib_board_index[7]);
	DDX_Control(pDX, IDC_GPIB_PRIMARY_INDEX1, m_gpib_primary_index[0]);
	DDX_Control(pDX, IDC_GPIB_PRIMARY_INDEX2, m_gpib_primary_index[1]);
	DDX_Control(pDX, IDC_GPIB_PRIMARY_INDEX3, m_gpib_primary_index[2]);
	DDX_Control(pDX, IDC_GPIB_PRIMARY_INDEX4, m_gpib_primary_index[3]);
	DDX_Control(pDX, IDC_GPIB_PRIMARY_INDEX5, m_gpib_primary_index[4]);
	DDX_Control(pDX, IDC_GPIB_PRIMARY_INDEX6, m_gpib_primary_index[5]);
	DDX_Control(pDX, IDC_GPIB_PRIMARY_INDEX7, m_gpib_primary_index[6]);
	DDX_Control(pDX, IDC_GPIB_PRIMARY_INDEX8, m_gpib_primary_index[7]);
	DDX_Control(pDX, IDC_GPIB_SECONDARY_INDEX1, m_gpib_secondary_index[0]);
	DDX_Control(pDX, IDC_GPIB_SECONDARY_INDEX2, m_gpib_secondary_index[1]);
	DDX_Control(pDX, IDC_GPIB_SECONDARY_INDEX3, m_gpib_secondary_index[2]);
	DDX_Control(pDX, IDC_GPIB_SECONDARY_INDEX4, m_gpib_secondary_index[3]);
	DDX_Control(pDX, IDC_GPIB_SECONDARY_INDEX5, m_gpib_secondary_index[4]);
	DDX_Control(pDX, IDC_GPIB_SECONDARY_INDEX6, m_gpib_secondary_index[5]);
	DDX_Control(pDX, IDC_GPIB_SECONDARY_INDEX7, m_gpib_secondary_index[6]);
	DDX_Control(pDX, IDC_GPIB_SECONDARY_INDEX8, m_gpib_secondary_index[7]);
	DDX_Control(pDX, IDC_IPADDRESS_INSTR1, m_ipaddr[0]);
	DDX_Control(pDX, IDC_IPADDRESS_INSTR2, m_ipaddr[1]);
	DDX_Control(pDX, IDC_IPADDRESS_INSTR3, m_ipaddr[2]);
	DDX_Control(pDX, IDC_IPADDRESS_INSTR4, m_ipaddr[3]);
	DDX_Control(pDX, IDC_IPADDRESS_INSTR5, m_ipaddr[4]);
	DDX_Control(pDX, IDC_IPADDRESS_INSTR6, m_ipaddr[5]);
	DDX_Control(pDX, IDC_IPADDRESS_INSTR7, m_ipaddr[6]);
	DDX_Control(pDX, IDC_IPADDRESS_INSTR8, m_ipaddr[7]);
	DDX_Control(pDX, IDC_INSTR_STATUS1, m_status_text[0]);
	DDX_Control(pDX, IDC_INSTR_STATUS2, m_status_text[1]);
	DDX_Control(pDX, IDC_INSTR_STATUS3, m_status_text[2]);
	DDX_Control(pDX, IDC_INSTR_STATUS4, m_status_text[3]);
	DDX_Control(pDX, IDC_INSTR_STATUS5, m_status_text[4]);
	DDX_Control(pDX, IDC_INSTR_STATUS6, m_status_text[5]);
	DDX_Control(pDX, IDC_INSTR_STATUS7, m_status_text[6]);
	DDX_Control(pDX, IDC_INSTR_STATUS8, m_status_text[7]);
}


BEGIN_MESSAGE_MAP(CSysConfigWizardStep4, CPropertyPage)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_COMBO_IO_TYPE1, &CSysConfigWizardStep4::OnSelchangeComboIoType1)
	ON_CBN_SELCHANGE(IDC_COMBO_IO_TYPE2, &CSysConfigWizardStep4::OnSelchangeComboIoType2)
	ON_CBN_SELCHANGE(IDC_COMBO_IO_TYPE3, &CSysConfigWizardStep4::OnSelchangeComboIoType3)
	ON_CBN_SELCHANGE(IDC_COMBO_IO_TYPE4, &CSysConfigWizardStep4::OnSelchangeComboIoType4)
	ON_CBN_SELCHANGE(IDC_COMBO_IO_TYPE5, &CSysConfigWizardStep4::OnSelchangeComboIoType5)
	ON_CBN_SELCHANGE(IDC_COMBO_IO_TYPE6, &CSysConfigWizardStep4::OnSelchangeComboIoType6)
	ON_CBN_SELCHANGE(IDC_COMBO_IO_TYPE7, &CSysConfigWizardStep4::OnSelchangeComboIoType7)
	ON_CBN_SELCHANGE(IDC_COMBO_IO_TYPE8, &CSysConfigWizardStep4::OnSelchangeComboIoType8)
	ON_BN_CLICKED(IDC_BTN_TEST_CONN, &CSysConfigWizardStep4::OnBnClickedBtnTestConn)
	ON_STN_CLICKED(IDC_TEXT_NUM_GENERATOR, &CSysConfigWizardStep4::OnStnClickedTextNumGenerator)
END_MESSAGE_MAP()


// CSysConfigWizardStep4 ��Ϣ�������


BOOL CSysConfigWizardStep4::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_text_title.MoveWindow(25,2,300,50);
	m_text_title.SetFont(&m_font_title);
	m_text_title.SetWindowText("���Ĳ���");
	m_text_content.MoveWindow(45,25,300,40);
	m_text_content.SetFont(&m_font_content);
	m_text_content.SetWindowText("ѡ���������������ӷ�ʽ��IP��ַ���˿ںŵȣ�");

	((CStatic*)GetDlgItem(IDC_TEXT_NUM_GENERATOR))->SetFont(&m_font_content);

	m_num_generator.SetFont(&m_font_content);
	m_num_generator.SetCurSel(0);
	m_num_generator.EnableWindow(FALSE);
	m_btn_test_conn.SetFont(&m_font_content);
	
	for (int i=0;i<8;i++)
	{
		m_sg_text[i].SetFont(&m_font_content);
		m_comb_io_type[i].SetFont(&m_font_content);
		m_comb_io_type[i].SetCurSel(0);
		m_gpib_board_index[i].SetFont(&m_font_content);
		m_gpib_board_index[i].SetCurSel(0);
		m_gpib_primary_index[i].SetFont(&m_font_content);
		m_gpib_primary_index[i].SetCurSel(19);
		m_gpib_secondary_index[i].SetFont(&m_font_content);
		m_gpib_secondary_index[i].SetCurSel(0);
		m_gpib_secondary_index[i].EnableWindow(FALSE);
		m_ipaddr[i].SetFont(&m_font_content);
		m_status_text[i].SetFont(&m_font_content);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CSysConfigWizardStep4::OnPaint()
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
	CSysConfigWizard* p_wzd = (CSysConfigWizard*)GetParent();
	int num_instr = p_wzd->m_num_instruments;
	if (m_reset_window)
	{
		m_reset_window = FALSE;
		m_num_generator.SetCurSel(num_instr-1);
		//������������������ʾ����
		for (int i=0;i<num_instr;i++)
		{
			m_sg_text[i].ShowWindow(SW_SHOW);
			m_comb_io_type[i].ShowWindow(SW_SHOW);
			m_comb_io_type[i].SetCurSel(0);
			
			//����GPIB��ַ������
			m_gpib_board_index[i].ShowWindow(SW_HIDE);
			m_gpib_board_index[i].SetCurSel(0);
			m_gpib_primary_index[i].ShowWindow((SW_HIDE));
			m_gpib_primary_index[i].SetCurSel(19);
			m_gpib_secondary_index[i].ShowWindow(SW_HIDE);
			m_gpib_secondary_index[i].SetCurSel(0);

			//��ʾip��ַ��
			m_ipaddr[i].ShowWindow(SW_SHOW);
			m_ipaddr[i].ClearAddress();
			m_status_text[i].ShowWindow(SW_SHOW);
		}
		for (int i=num_instr;i<8;i++)
		{
			m_sg_text[i].ShowWindow(SW_HIDE);
			m_comb_io_type[i].ShowWindow(SW_HIDE);
			m_gpib_board_index[i].ShowWindow(SW_HIDE);
			m_gpib_primary_index[i].ShowWindow((SW_HIDE));
			m_gpib_secondary_index[i].ShowWindow(SW_HIDE);
			m_ipaddr[i].ShowWindow(SW_HIDE);
			m_status_text[i].ShowWindow(SW_HIDE);
		}
	}

	// ��Ϊ��ͼ��Ϣ���� CPropertyPage::OnPaint()
}


HBRUSH CSysConfigWizardStep4::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CSysConfigWizardStep4::OnSelchangeComboIoType1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_comb_io_type[0].GetCurSel()==1)
	{
		m_gpib_board_index[0].ShowWindow(SW_SHOW);
		m_gpib_primary_index[0].ShowWindow(SW_SHOW);
		m_gpib_secondary_index[0].ShowWindow(SW_SHOW);
		m_ipaddr[0].ShowWindow(SW_HIDE);
	}else{
		m_gpib_board_index[0].ShowWindow(SW_HIDE);
		m_gpib_primary_index[0].ShowWindow(SW_HIDE);
		m_gpib_secondary_index[0].ShowWindow(SW_HIDE);
		m_ipaddr[0].ShowWindow(SW_SHOW);
	}
}


void CSysConfigWizardStep4::OnSelchangeComboIoType2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_comb_io_type[1].GetCurSel()==1)
	{
		m_gpib_board_index[1].ShowWindow(SW_SHOW);
		m_gpib_primary_index[1].ShowWindow(SW_SHOW);
		m_gpib_secondary_index[1].ShowWindow(SW_SHOW);
		m_ipaddr[1].ShowWindow(SW_HIDE);
	}else{
		m_gpib_board_index[1].ShowWindow(SW_HIDE);
		m_gpib_primary_index[1].ShowWindow(SW_HIDE);
		m_gpib_secondary_index[1].ShowWindow(SW_HIDE);
		m_ipaddr[1].ShowWindow(SW_SHOW);
	}
}


void CSysConfigWizardStep4::OnSelchangeComboIoType3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_comb_io_type[2].GetCurSel()==1)
	{
		m_gpib_board_index[2].ShowWindow(SW_SHOW);
		m_gpib_primary_index[2].ShowWindow(SW_SHOW);
		m_gpib_secondary_index[2].ShowWindow(SW_SHOW);
		m_ipaddr[2].ShowWindow(SW_HIDE);
	}else{
		m_gpib_board_index[2].ShowWindow(SW_HIDE);
		m_gpib_primary_index[2].ShowWindow(SW_HIDE);
		m_gpib_secondary_index[2].ShowWindow(SW_HIDE);
		m_ipaddr[2].ShowWindow(SW_SHOW);
	}
}


void CSysConfigWizardStep4::OnSelchangeComboIoType4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_comb_io_type[3].GetCurSel()==1)
	{
		m_gpib_board_index[3].ShowWindow(SW_SHOW);
		m_gpib_primary_index[3].ShowWindow(SW_SHOW);
		m_gpib_secondary_index[3].ShowWindow(SW_SHOW);
		m_ipaddr[3].ShowWindow(SW_HIDE);
	}else{
		m_gpib_board_index[3].ShowWindow(SW_HIDE);
		m_gpib_primary_index[3].ShowWindow(SW_HIDE);
		m_gpib_secondary_index[3].ShowWindow(SW_HIDE);
		m_ipaddr[3].ShowWindow(SW_SHOW);
	}
}


void CSysConfigWizardStep4::OnSelchangeComboIoType5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_comb_io_type[4].GetCurSel()==1)
	{
		m_gpib_board_index[4].ShowWindow(SW_SHOW);
		m_gpib_primary_index[4].ShowWindow(SW_SHOW);
		m_gpib_secondary_index[4].ShowWindow(SW_SHOW);
		m_ipaddr[4].ShowWindow(SW_HIDE);
	}else{
		m_gpib_board_index[4].ShowWindow(SW_HIDE);
		m_gpib_primary_index[4].ShowWindow(SW_HIDE);
		m_gpib_secondary_index[4].ShowWindow(SW_HIDE);
		m_ipaddr[4].ShowWindow(SW_SHOW);
	}
}


void CSysConfigWizardStep4::OnSelchangeComboIoType6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_comb_io_type[5].GetCurSel()==1)
	{
		m_gpib_board_index[5].ShowWindow(SW_SHOW);
		m_gpib_primary_index[5].ShowWindow(SW_SHOW);
		m_gpib_secondary_index[5].ShowWindow(SW_SHOW);
		m_ipaddr[5].ShowWindow(SW_HIDE);
	}else{
		m_gpib_board_index[5].ShowWindow(SW_HIDE);
		m_gpib_primary_index[5].ShowWindow(SW_HIDE);
		m_gpib_secondary_index[5].ShowWindow(SW_HIDE);
		m_ipaddr[5].ShowWindow(SW_SHOW);
	}
}


void CSysConfigWizardStep4::OnSelchangeComboIoType7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_comb_io_type[6].GetCurSel()==1)
	{
		m_gpib_board_index[6].ShowWindow(SW_SHOW);
		m_gpib_primary_index[6].ShowWindow(SW_SHOW);
		m_gpib_secondary_index[6].ShowWindow(SW_SHOW);
		m_ipaddr[6].ShowWindow(SW_HIDE);
	}else{
		m_gpib_board_index[6].ShowWindow(SW_HIDE);
		m_gpib_primary_index[6].ShowWindow(SW_HIDE);
		m_gpib_secondary_index[6].ShowWindow(SW_HIDE);
		m_ipaddr[6].ShowWindow(SW_SHOW);
	}
}


void CSysConfigWizardStep4::OnSelchangeComboIoType8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_comb_io_type[7].GetCurSel()==1)
	{
		m_gpib_board_index[7].ShowWindow(SW_SHOW);
		m_gpib_primary_index[7].ShowWindow(SW_SHOW);
		m_gpib_secondary_index[7].ShowWindow(SW_SHOW);
		m_ipaddr[7].ShowWindow(SW_HIDE);
	}else{
		m_gpib_board_index[7].ShowWindow(SW_HIDE);
		m_gpib_primary_index[7].ShowWindow(SW_HIDE);
		m_gpib_secondary_index[7].ShowWindow(SW_HIDE);
		m_ipaddr[7].ShowWindow(SW_SHOW);
	}
}


LRESULT CSysConfigWizardStep4::OnWizardNext()
{
	// TODO: �ڴ����ר�ô����/����û���
	/************************************************************************/
	/* ����ÿ̨������Ӧ��visa���ӳ̿�������� LAN ���Ӻ� GPIB ���ӽ�������*/
	/************************************************************************/
	CSysConfigWizard* p_wiz = (CSysConfigWizard*)GetParent();
	int num_instr = p_wiz->m_num_instruments;

	BYTE add0,add1,add2,add3;
	for (int i = 0; i<num_instr;i++)
	{
		if (m_ipaddr[i].IsWindowVisible())
		{
			m_ipaddr[i].GetAddress(add0,add1,add2,add3);
			p_wiz->str_conn[i].Format("TCPIP0::%d.%d.%d.%d::5001::SOCKET",add0,add1,add2,add3);
		}
		else
		{
			p_wiz->str_conn[i].Format("GPIB%d::%d::INSTR",m_gpib_board_index[i].GetCurSel(),m_gpib_primary_index[i].GetCurSel());
		}
	}

	/************************************************************************/
	/* �ڱ�ҳ�޸������ã�����Ҫ�ر����е����ӣ������µ�����                 */
	/************************************************************************/
	CMainFrame* p_mainframe = (CMainFrame*)GetParent();
	int old_num_instr = p_mainframe->m_num_instr;
	
	for (int i = 0;i<old_num_instr;i++)
	{
		viClear(p_mainframe->vi[i]);
		viClose(p_mainframe->vi[i]);
		
	}
	if (old_num_instr)
	{
		viClose(p_mainframe->defaultRM);
	}

	return CPropertyPage::OnWizardNext();
}


LRESULT CSysConfigWizardStep4::OnWizardBack()
{
	// TODO: �ڴ����ר�ô����/����û���
	m_reset_window = TRUE;
	return CPropertyPage::OnWizardBack();
}


void CSysConfigWizardStep4::OnBnClickedBtnTestConn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox("�˴���Ӳ������ӵĴ���");
}


void CSysConfigWizardStep4::OnStnClickedTextNumGenerator()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
