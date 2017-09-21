// TabParent.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "TabParent.h"

// CTabParent

IMPLEMENT_DYNCREATE(CTabParent, CFormView)

CTabParent::CTabParent()
	: CFormView(CTabParent::IDD)
{
}

CTabParent::~CTabParent()
{
}

void CTabParent::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MAIN, m_mainTab);
	DDX_Control(pDX, IDC_PROTOCOL,m_protocol);
}

BEGIN_MESSAGE_MAP(CTabParent, CFormView)
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CTabParent::OnSelchangeTabMain)
END_MESSAGE_MAP()


// CTabParent ���

#ifdef _DEBUG
void CTabParent::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTabParent::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTabParent ��Ϣ�������


void CTabParent::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	CRect rc;

	m_mainTab.InsertItem(0,"��������");
	m_mainTab.InsertItem(1,"�ز���Ϣ");
	m_mainTab.InsertItem(2,"Э�����");
	m_mainTab.InsertItem(3,"��������");

	//ͨ��Dialog��Դ������ģ̬�Ի���
	m_tabMac.Create(IDD_TAB_MAC_INFO,&m_mainTab);
	m_tabInstrument.Create(IDD_TAB_INSTRUMENT,&m_mainTab);
	m_tabProtocolConfig.Create(IDD_TAB_PROTOCOL_CONFIG,&m_mainTab);
	m_tabCarrier.Create(IDD_TAB_CARRIER_INFO,&m_mainTab);

	m_mainTab.GetClientRect(&rc);

	m_protocol.MoveWindow(10,27,100,25);
	m_protocol.SetWindowText("WLAN 802.11a");
	
	m_tabMac.ShowWindow(SW_SHOW);
	m_tabCarrier.ShowWindow(SW_HIDE);
	m_tabInstrument.ShowWindow(SW_HIDE);
	m_tabProtocolConfig.ShowWindow(SW_HIDE);
	m_font.CreatePointFont(100,"΢���ź�");
	CWnd *pWnd = GetTopWindow();  
	while (NULL != pWnd)  
	{  
		pWnd->SetFont(&m_font);  
		pWnd = pWnd->GetNextWindow();  
	}  
}


void CTabParent::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	SetScrollSizes(MM_TEXT,CSize(0,0));
	//MessageBox("change");
	// TODO: �ڴ˴������Ϣ����������
	if (IsWindowVisible())       //���ڿɼ�
	{
		CRect rc;
		GetClientRect(&rc);
		m_mainTab.MoveWindow(0,0,rc.Width()+1,rc.Height()+1);
		m_mainTab.GetClientRect(&rc);

		m_tabMac.MoveWindow(0,45,rc.Width()+20,rc.Height());
		m_tabCarrier.MoveWindow(0,45,rc.Width()+20,rc.Height());
		m_tabProtocolConfig.MoveWindow(0,45,rc.Width()+20,rc.Height());
		m_tabInstrument.MoveWindow(0,45,rc.Width()+20,rc.Height());
	}
	CFormView::ShowScrollBar(SB_BOTH, false);//�����ù�����
}


void CTabParent::OnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int cursel = m_mainTab.GetCurSel();
	switch(cursel)
	{
	case 0:
		m_tabMac.ShowWindow(SW_SHOW);
	    m_tabCarrier.ShowWindow(SW_HIDE);
	    m_tabProtocolConfig.ShowWindow(SW_HIDE);
	    m_tabInstrument.ShowWindow(SW_HIDE);
	    break;
	case 1:
		m_tabMac.ShowWindow(SW_HIDE);
		m_tabCarrier.ShowWindow(SW_SHOW);
		m_tabProtocolConfig.ShowWindow(SW_HIDE);
		m_tabInstrument.ShowWindow(SW_HIDE);
		break;
	case 2:
		m_tabMac.ShowWindow(SW_HIDE);
		m_tabCarrier.ShowWindow(SW_HIDE);
		m_tabProtocolConfig.ShowWindow(SW_SHOW);
		m_tabInstrument.ShowWindow(SW_HIDE);
		break;
	case 3:
		m_tabMac.ShowWindow(SW_HIDE);
		m_tabCarrier.ShowWindow(SW_HIDE);
		m_tabProtocolConfig.ShowWindow(SW_HIDE);
		m_tabInstrument.ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}
	*pResult = 0;
}
