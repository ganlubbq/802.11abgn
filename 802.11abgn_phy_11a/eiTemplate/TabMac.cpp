// TabMac.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "TabMac.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "TabProtocolConfig.h"
#include "TabCarrier.h"
#include "config.h"
#include "TabParent.h"
// CTabMac �Ի���

IMPLEMENT_DYNAMIC(CTabMac, CDialog)

CTabMac::CTabMac(CWnd* pParent /*=NULL*/)
	: CDialog(CTabMac::IDD, pParent)
{  
	m_font.CreatePointFont(100,"΢���ź�");
	m_finished_ini=FALSE;
}

CTabMac::~CTabMac()
{
}

void CTabMac::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONFIGLIST, m_configlist);
}


BEGIN_MESSAGE_MAP(CTabMac, CDialog)
	ON_WM_SIZE()
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED,OnPropertyChanged)
	ON_NOTIFY(NM_CLICK, IDC_CONFIGLIST, &CTabMac::OnClickListprotocol)
	ON_NOTIFY(NM_DBLCLK, IDC_CONFIGLIST, &CTabMac::OnDblclkListprotocol)
END_MESSAGE_MAP()

void CTabMac::Point(){
	CTabParent* p_tabParent = (CTabParent*)(((CMainFrame*)(AfxGetMainWnd()))->m_mainSplitter.GetPane(0,0));
	p_tabParent->m_tabMac.m_configIndex =((CMainFrame*)AfxGetMainWnd())->m_configIndex;
	p_tabParent->m_tabCarrier.m_configIndex =((CMainFrame*)AfxGetMainWnd())->m_configIndex;
	p_tabParent->m_tabProtocolConfig.m_configIndex =((CMainFrame*)AfxGetMainWnd())->m_configIndex;

}
// CTabMac ��Ϣ�������
void CTabMac::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	// CDialog::OnOK();
}
BOOL CTabMac::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//����Э����Ϣ�б���������
	m_configlist.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);
	m_configlist.DeleteAllItems();
	m_configlist.InsertColumn(0,_T("����"),LVCFMT_LEFT,250);
	m_configlist.InsertColumn(1,_T("��Ϣ"),LVCFMT_LEFT,266);
	m_configlist.InsertItem(0,_T("IEEE 802.11 a"));
	m_configlist.SetItemText(0,1,_T("IEEE 802.11a (ei41)"));//�����
	m_configlist.InsertItem(1,_T("IEEE 802.11 b"));
	m_configlist.SetItemText(1,1,_T("IEEE 802.11b (ei41)"));//�����
	m_configlist.InsertItem(2,_T("IEEE 802.11 g"));
	m_configlist.SetItemText(2,1,_T("IEEE 802.11g (ei41)"));//�����
	m_configlist.InsertItem(3,_T("IEEE 802.11n M��N (1 SG)"));
	m_configlist.SetItemText(3,1,_T("IEEE 802.11n M��N (1 SG)"));//�����
	m_configlist.InsertItem(4,_T("IEEE 802.11n M��2 (2 SG,1 Arb)"));
	m_configlist.SetItemText(4,1,_T("IEEE 802.11n M��2 MIMO (2 SG, 1ARB)"));//�����
	m_configlist.InsertItem(5,_T("IEEE 802.11n M��2"));
	m_configlist.SetItemText(5,1,_T("IEEE 802.11n M��2 MIMO (ei41)"));//�����
	m_configlist.InsertItem(6,_T("IEEE 802.11n M��3"));
	m_configlist.SetItemText(6,1,_T("IEEE 802.11n M��3 MIMO (ei41)"));//�����
	m_configlist.InsertItem(7,_T("IEEE 802.11n M��4"));
	m_configlist.SetItemText(7,1,_T("IEEE 802.11n M��4 MIMO (ei41)"));//�����
	m_configlist.InsertItem(8,_T("IEEE 802.11n 1��1 (for ei)"));
	m_configlist.SetItemText(8,1,_T("IEEE 802.11n M��N MIMO (1 SG)"));//�����
	m_configlist.InsertItem(9,_T("IEEE 802.11n 2��2 (for ei)"));
	m_configlist.SetItemText(9,1,_T("IEEE 802.11n M��2 MIMO (ei41)"));//�����
	m_configlist.InsertItem(10,_T("IEEE 802.11n 4��4 (for ei)"));
	m_configlist.SetItemText(10,1,_T("IEEE 802.11n M��4 MIMO (ei41)"));//�����
	m_configlist.ShowWindow(TRUE);

	//�ı���ʾ��Ϣ
	//protocol ������Ϣ�б�
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	CRect rc;
	GetClientRect(&rc);
	
	rc.left += 10;
	rc.top += 10;
	m_MFCPropertyGridOne.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,rc,this,2000);
	m_MFCPropertyGridOne.EnableHeaderCtrl(FALSE,_T("����"),_T("ֵ"));
	m_MFCPropertyGridOne.EnableDescriptionArea();
	m_MFCPropertyGridOne.SetDescriptionRows(3);
	m_MFCPropertyGridOne.SetVSDotNetLook();
	m_MFCPropertyGridOne.MarkModifiedProperties();
	m_MFCPropertyGridOne.SetAlphabeticMode(false); 
	m_MFCPropertyGridOne.SetShowDragContext();

	pGroup01 = new CMFCPropertyGridProperty(_T("Э�����"));
	pGroup02 = new CMFCPropertyGridProperty(_T("����˵��"));


	CMFCPropertyGridProperty *pPropF1 = new CMFCPropertyGridProperty(_T("Э����"),_T("802.11a"),_T("ѡ����Э������"));
	pPropF1->Enable(FALSE);
	pGroup01->AddSubItem(pPropF1);
	CMFCPropertyGridProperty *pPropF2 = new CMFCPropertyGridProperty(_T("����"),_T("5/10/20 MHz"),_T("����Χ"));
	pPropF2->Enable(FALSE);
	pGroup01->AddSubItem(pPropF2);
	CMFCPropertyGridProperty *pPropF3 = new CMFCPropertyGridProperty(_T("��Ƶ"),_T("5.2-5.8 GHz"),_T("�ز�Ƶ�����ڷ�Χ��С"));
	pPropF3->Enable(FALSE);
	pGroup01->AddSubItem(pPropF3);
	CMFCPropertyGridProperty *pPropF4 = new CMFCPropertyGridProperty(_T("���似��"),_T("OFDM"),_T("OFDM������Ƶ�ָ��ã�"));
	pPropF4->Enable(FALSE);
	pGroup01->AddSubItem(pPropF4);
	CMFCPropertyGridProperty *pPropF5 = new CMFCPropertyGridProperty(_T("��ֵ����"),_T("54 Mbps"),_T("�����ϵķ�ֵ����"));
	pPropF5->Enable(FALSE);
	pGroup01->AddSubItem(pPropF5);
	CMFCPropertyGridProperty *pPropF6 = new CMFCPropertyGridProperty(_T("�ŵ�����"),_T("�����"),_T("�����"));
	pPropF6->Enable(FALSE);
	pGroup01->AddSubItem(pPropF6);
	CMFCPropertyGridProperty *pPropF7 = new CMFCPropertyGridProperty(_T("����"),_T("CC: R=1/2,2/3,3/4"),_T("��ͬ�ı�������"));
	pPropF7->Enable(FALSE);
	pGroup01->AddSubItem(pPropF7);
	CMFCPropertyGridProperty *pPropF8 = new CMFCPropertyGridProperty(_T("���Ʒ�ʽ"),_T("BPSK/QPSK/16QAM/64QAM"),_T("���Ʒ�ʽ֮һ"));
	pPropF8->Enable(FALSE);
	pGroup01->AddSubItem(pPropF8);
	CMFCPropertyGridProperty *pPropF9 = new CMFCPropertyGridProperty(_T("FFT����"),_T("64(52/4), 4us(800ns)"),_T("FFT:���ٸ���Ҷ�任������Ϊ64"));
	pPropF9->Enable(FALSE);
	pGroup01->AddSubItem(pPropF9);
	CMFCPropertyGridProperty *pPropF10 = new CMFCPropertyGridProperty(_T("��������"),_T("1��1"),_T("û��MIMOģʽ"));
	pPropF10->Enable(FALSE);
	pGroup01->AddSubItem(pPropF10);
	CMFCPropertyGridProperty *pPropF11 = new CMFCPropertyGridProperty(_T("MCS����"),_T("0~7"),_T("��ͬ��MCSѡ��"));
	pPropF11->Enable(FALSE);
	pGroup01->AddSubItem(pPropF11);
	CMFCPropertyGridProperty *pPropF12 = new CMFCPropertyGridProperty(_T("�ŵ�ģ��"),_T("��"),_T("AWGN��"));
	pPropF12->Enable(FALSE);
	pGroup02->AddSubItem(pPropF12);

	m_MFCPropertyGridOne.AddProperty(pGroup01);
	m_MFCPropertyGridOne.AddProperty(pGroup02);

	m_MFCPropertyGridOne.ExpandAll(TRUE);
	m_MFCPropertyGridOne.EnableDescriptionArea(TRUE);

	m_MFCPropertyGridOne.SetCustomColors(RGB(250,250,250),RGB(0,0,0),RGB(230,230,230),RGB(100,100,100),RGB(230,230,230),RGB(0,0,0),RGB(220,220,220));
	m_MFCPropertyGridOne.ShowWindow(SW_SHOW);

	//11b �г��Ĳ�������ʵ������޸�
	CRect rcB;
	GetClientRect(&rcB);

	rcB.left += 10;
	rcB.top += 10;

	m_MFCPropertyGridB.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,rcB,this,20001);
	m_MFCPropertyGridB.EnableHeaderCtrl(FALSE,_T("����"),_T("ֵ"));
	m_MFCPropertyGridB.EnableDescriptionArea();
	m_MFCPropertyGridB.SetDescriptionRows(3);
	m_MFCPropertyGridB.SetVSDotNetLook();
	m_MFCPropertyGridB.MarkModifiedProperties();
	m_MFCPropertyGridB.SetAlphabeticMode(false); 
	m_MFCPropertyGridB.SetShowDragContext();

	pGroupB01 = new CMFCPropertyGridProperty(_T("Э�����"));
	pGroupB02 = new CMFCPropertyGridProperty(_T("����˵��"));

	CMFCPropertyGridProperty *pPropFB1 = new CMFCPropertyGridProperty(_T("Э����"),_T("802.11b"),_T("ѡ����Э������"));
	pPropFB1->Enable(FALSE);
	pGroupB01->AddSubItem(pPropFB1);
	CMFCPropertyGridProperty *pPropFB2 = new CMFCPropertyGridProperty(_T("����"),_T("20 MHz"),_T("����Χ"));
	pPropFB2->Enable(FALSE);
	pGroupB01->AddSubItem(pPropFB2);
	CMFCPropertyGridProperty *pPropFB3 = new CMFCPropertyGridProperty(_T("��Ƶ"),_T("2.4 GHz"),_T("�ز�Ƶ�����ڷ�Χ��С"));
	pPropFB3->Enable(FALSE);
	pGroupB01->AddSubItem(pPropFB3);
	CMFCPropertyGridProperty *pPropFB4 = new CMFCPropertyGridProperty(_T("���似��"),_T("DSSS"),_T("DSSS��ֱ������չƵ��"));
	pPropFB4->Enable(FALSE);
	pGroupB01->AddSubItem(pPropFB4);
	CMFCPropertyGridProperty *pPropFB5 = new CMFCPropertyGridProperty(_T("��ֵ����"),_T("11 Mbps"),_T("�����ϵķ�ֵ����"));
	pPropFB5->Enable(FALSE);
	pGroupB01->AddSubItem(pPropFB5);
	CMFCPropertyGridProperty *pPropFB8 = new CMFCPropertyGridProperty(_T("���Ʒ�ʽ"),_T("DBPSK/DQPSK/CCK/PBCC"),_T("���Ʒ�ʽ֮һ"));
	pPropFB8->Enable(FALSE);
	pGroupB01->AddSubItem(pPropFB8);
	CMFCPropertyGridProperty *pPropFB11 = new CMFCPropertyGridProperty(_T("MCS����"),_T("0~8"),_T("��ͬ��MCSѡ��"));
	pPropFB11->Enable(FALSE);
	pGroupB01->AddSubItem(pPropFB11);
	CMFCPropertyGridProperty *pPropFB12 = new CMFCPropertyGridProperty(_T("�ŵ�ģ��"),_T("��"),_T("AWGN��"));
	pPropFB12->Enable(FALSE);
	pGroupB02->AddSubItem(pPropFB12);


	m_MFCPropertyGridB.AddProperty(pGroupB01);
	m_MFCPropertyGridB.AddProperty(pGroupB02);

	m_MFCPropertyGridB.ExpandAll(TRUE);
	m_MFCPropertyGridB.EnableDescriptionArea(TRUE);

	m_MFCPropertyGridB.SetCustomColors(RGB(250,250,250),RGB(0,0,0),RGB(230,230,230),RGB(100,100,100),RGB(230,230,230),RGB(0,0,0),RGB(220,220,220));
	m_MFCPropertyGridB.ShowWindow(SW_HIDE);

	
	//11g �г��Ĳ�������ʵ������޸�
	CRect rcG;
	GetClientRect(&rcG);
	
	rcG.left += 10;
	rcG.top += 10;

	m_MFCPropertyGridG.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,rcB,this,20001);
	m_MFCPropertyGridG.EnableHeaderCtrl(FALSE,_T("����"),_T("ֵ"));
	m_MFCPropertyGridG.EnableDescriptionArea();
	m_MFCPropertyGridG.SetDescriptionRows(3);
	m_MFCPropertyGridG.SetVSDotNetLook();
	m_MFCPropertyGridG.MarkModifiedProperties();
	m_MFCPropertyGridG.SetAlphabeticMode(false); 
	m_MFCPropertyGridG.SetShowDragContext();

	pGroupG01 = new CMFCPropertyGridProperty(_T("Э�����"));
	pGroupG02 = new CMFCPropertyGridProperty(_T("����˵��"));

	CMFCPropertyGridProperty *pPropFG1 = new CMFCPropertyGridProperty(_T("Э����"),_T("802.11g"),_T("ѡ����Э������"));
	pPropFG1->Enable(FALSE);
	pGroupG01->AddSubItem(pPropFG1);

	CMFCPropertyGridProperty *pPropFG2 = new CMFCPropertyGridProperty(_T("����"),_T("5/10/20 MHz"),_T("����Χ"));
	pPropFG2->Enable(FALSE);
	pGroupG01->AddSubItem(pPropFG2);
	CMFCPropertyGridProperty *pPropFG3 = new CMFCPropertyGridProperty(_T("��Ƶ"),_T("2.4-2.5 GHz"),_T("�ز�Ƶ�����ڷ�Χ��С"));
	pPropFG3->Enable(FALSE);
	pGroupG01->AddSubItem(pPropFG3);
	CMFCPropertyGridProperty *pPropFG4 = new CMFCPropertyGridProperty(_T("���似��"),_T("OFDM/DSSS/PBCC"),_T("OFDM������Ƶ�ָ��ã�"));
	pPropFG4->Enable(FALSE);
	pGroupG01->AddSubItem(pPropFG4);
	CMFCPropertyGridProperty *pPropFG5 = new CMFCPropertyGridProperty(_T("��ֵ����"),_T("54 Mbps"),_T("�����ϵķ�ֵ����"));
	pPropFG5->Enable(FALSE);
	pGroupG01->AddSubItem(pPropFG5);
	CMFCPropertyGridProperty *pPropFG6 = new CMFCPropertyGridProperty(_T("�ŵ�����"),_T("�����"),_T("�����"));
	pPropFG6->Enable(FALSE);
	pGroupG01->AddSubItem(pPropFG6);
	CMFCPropertyGridProperty *pPropFG7 = new CMFCPropertyGridProperty(_T("����"),_T("CC: R=1/2,2/3,3/4"),_T("��ͬ�ı�������"));
	pPropFG7->Enable(FALSE);
	pGroupG01->AddSubItem(pPropFG7);
	CMFCPropertyGridProperty *pPropFG8 = new CMFCPropertyGridProperty(_T("���Ʒ�ʽ"),_T("BPSK/QPSK/16QAM/64QAM"),_T("���Ʒ�ʽ֮һ"));
	pPropFG8->Enable(FALSE);
	pGroupG01->AddSubItem(pPropFG8);
	CMFCPropertyGridProperty *pPropFG9 = new CMFCPropertyGridProperty(_T("FFT����"),_T("64(52/4), 4us(800ns)"),_T("FFT:���ٸ���Ҷ�任������Ϊ64"));
	pPropFG9->Enable(FALSE);
	pGroupG01->AddSubItem(pPropFG9);
	CMFCPropertyGridProperty *pPropFG10 = new CMFCPropertyGridProperty(_T("��������"),_T("1��1"),_T("û��MIMOģʽ"));
	pPropFG10->Enable(FALSE);
	pGroupG01->AddSubItem(pPropFG10);
	CMFCPropertyGridProperty *pPropFG11 = new CMFCPropertyGridProperty(_T("MCS����"),_T("0~7"),_T("��ͬ��MCSѡ��"));
	pPropFG11->Enable(FALSE);
	pGroupG01->AddSubItem(pPropFG11);
	CMFCPropertyGridProperty *pPropFG12 = new CMFCPropertyGridProperty(_T("�ŵ�ģ��"),_T("��"),_T("AWGN��"));
	pPropFG12->Enable(FALSE);
	pGroupG02->AddSubItem(pPropFG12);


	m_MFCPropertyGridG.AddProperty(pGroupG01);
	m_MFCPropertyGridG.AddProperty(pGroupG02);

	m_MFCPropertyGridG.ExpandAll(TRUE);
	m_MFCPropertyGridG.EnableDescriptionArea(TRUE);

	m_MFCPropertyGridG.SetCustomColors(RGB(250,250,250),RGB(0,0,0),RGB(230,230,230),RGB(100,100,100),RGB(230,230,230),RGB(0,0,0),RGB(220,220,220));
	m_MFCPropertyGridG.ShowWindow(SW_HIDE);


	
	//11n  �г��Ĳ�������ʵ������޸�
	CRect rcN;
	GetClientRect(&rcN);
	//rc.bottom += 20;
	rcN.left += 10;
	//rc.right += 10;
	rcN.top += 10;

	m_MFCPropertyGridN.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,rcB,this,20001);
	m_MFCPropertyGridN.EnableHeaderCtrl(FALSE,_T("����"),_T("ֵ"));
	m_MFCPropertyGridN.EnableDescriptionArea();
	m_MFCPropertyGridN.SetDescriptionRows(3);
	m_MFCPropertyGridN.SetVSDotNetLook();
	m_MFCPropertyGridN.MarkModifiedProperties();
	m_MFCPropertyGridN.SetAlphabeticMode(false); 
	m_MFCPropertyGridN.SetShowDragContext();

	pGroupN01 = new CMFCPropertyGridProperty(_T("Э�����"));
	pGroupN02 = new CMFCPropertyGridProperty(_T("����˵��"));

	CMFCPropertyGridProperty *pPropFN1 = new CMFCPropertyGridProperty(_T("Э����"),_T("802.11n"),_T("ѡ����Э������"));
	pPropFN1->Enable(FALSE);
	pGroupN01->AddSubItem(pPropFN1);

	CMFCPropertyGridProperty *pPropFN2 = new CMFCPropertyGridProperty(_T("����"),_T("20/40 MHz"),_T("����Χ"));
	pPropFN2->Enable(FALSE);
	pGroupN01->AddSubItem(pPropFN2);
	CMFCPropertyGridProperty *pPropFN3 = new CMFCPropertyGridProperty(_T("��Ƶ"),_T("2.4GHz/5.2-5.8 GHz"),_T("�ز�Ƶ�����ڷ�Χ��С"));
	pPropFN3->Enable(FALSE);
	pGroupN01->AddSubItem(pPropFN3);
	CMFCPropertyGridProperty *pPropFN4 = new CMFCPropertyGridProperty(_T("���似��"),_T("OFDM"),_T("OFDM������Ƶ�ָ��ã�"));
	pPropFN4->Enable(FALSE);
	pGroupN01->AddSubItem(pPropFN4);
	CMFCPropertyGridProperty *pPropFN5 = new CMFCPropertyGridProperty(_T("��ֵ����"),_T("54 Mbps"),_T("�����ϵķ�ֵ����"));
	pPropFN5->Enable(FALSE);
	pGroupN01->AddSubItem(pPropFN5);
	CMFCPropertyGridProperty *pPropFN6 = new CMFCPropertyGridProperty(_T("�ŵ�����"),_T("�����/LDPC"),_T("�����"));
	pPropFN6->Enable(FALSE);
	pGroupN01->AddSubItem(pPropFN6);
	CMFCPropertyGridProperty *pPropFN7 = new CMFCPropertyGridProperty(_T("����"),_T("CC: R=1/2,2/3,3/4,5/6;LDPC: R=1/2,2/3,3/4,5/6"),_T("��ͬ�ı�������"));
	pPropFN7->Enable(FALSE);
	pGroupN01->AddSubItem(pPropFN7);
	CMFCPropertyGridProperty *pPropFN8 = new CMFCPropertyGridProperty(_T("���Ʒ�ʽ"),_T("BPSK/QPSK/16QAM/64QAM"),_T("���Ʒ�ʽ֮һ"));
	pPropFN8->Enable(FALSE);
	pGroupN01->AddSubItem(pPropFN8);
	CMFCPropertyGridProperty *pPropFN9 = new CMFCPropertyGridProperty(_T("FFT����"),_T("128(108/6)"),_T("FFT:���ٸ���Ҷ�任������Ϊ128"));
	pPropFN9->Enable(FALSE);
	pGroupN01->AddSubItem(pPropFN9);
	CMFCPropertyGridProperty *pPropFN10 = new CMFCPropertyGridProperty(_T("��������"),_T("1��4"),_T("SU-MIMOģʽ"));
	pPropFN10->Enable(FALSE);
	pGroupN01->AddSubItem(pPropFN10);
	CMFCPropertyGridProperty *pPropFN11 = new CMFCPropertyGridProperty(_T("MCS����"),_T("0~76"),_T("��ͬ��MCSѡ��"));
	pPropFN11->Enable(FALSE);
	pGroupN01->AddSubItem(pPropFN11);
	CMFCPropertyGridProperty *pPropFN12 = new CMFCPropertyGridProperty(_T("�ŵ�ģ��"),_T("��"),_T("AWGN��"));
	pPropFN12->Enable(FALSE);
	pGroupN02->AddSubItem(pPropFN12);


	m_MFCPropertyGridN.AddProperty(pGroupN01);
	m_MFCPropertyGridN.AddProperty(pGroupN02);

	m_MFCPropertyGridN.ExpandAll(TRUE);
	m_MFCPropertyGridN.EnableDescriptionArea(TRUE);

	m_MFCPropertyGridN.SetCustomColors(RGB(250,250,250),RGB(0,0,0),RGB(230,230,230),RGB(100,100,100),RGB(230,230,230),RGB(0,0,0),RGB(220,220,220));
	m_MFCPropertyGridN.ShowWindow(SW_HIDE);
	
	CWnd *pWnd = GetTopWindow();  
	while (NULL != pWnd)  
	{  
		pWnd->SetFont(&m_font);  
		pWnd = pWnd->GetNextWindow();  
	}  
	m_finished_ini = TRUE;
	Point();       //������ҳm_configIndexָ��MainFrame�е�config����
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CTabMac::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (IsWindowVisible() || m_finished_ini)
	{
		m_MFCPropertyGridOne.MoveWindow(10,300,cx-32,cy-325);
		m_MFCPropertyGridB.MoveWindow(10,300,cx-32,cy-325);
		m_MFCPropertyGridG.MoveWindow(10,300,cx-32,cy-325);
		m_MFCPropertyGridN.MoveWindow(10,300,cx-32,cy-325);
		//LIST �ռ�
		m_configlist.MoveWindow(10,10,cx-30,cy-325);
	}
}
LRESULT CTabMac::OnPropertyChanged(__in WPARAM wparam,__in LPARAM lparam)
{
	return 0;
}

//Э��������õ�����ʾЭ����Ϣ
	void CTabMac::OnClickListprotocol(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION pos=m_configlist.GetFirstSelectedItemPosition();
	if (pos==NULL)
		return;
	else
	{
		//while(pos)
		//{
		int nItem = m_configlist.GetNextSelectedItem(pos);
		switch(nItem)
		{
		case 0:
			m_MFCPropertyGridOne.ShowWindow(SW_SHOW);//IEEE 802.11aЭ�����Ϣչ����ʾ
			m_MFCPropertyGridB.ShowWindow(SW_HIDE);//11b
			m_MFCPropertyGridG.ShowWindow(SW_HIDE);//11g
			m_MFCPropertyGridN.ShowWindow(SW_HIDE);//11n
			break;
		case 1:
			m_MFCPropertyGridOne.ShowWindow(SW_HIDE);//11a
			m_MFCPropertyGridB.ShowWindow(SW_SHOW);//11b show
			m_MFCPropertyGridG.ShowWindow(SW_HIDE);//11g
			m_MFCPropertyGridN.ShowWindow(SW_HIDE);//11n
			break;
		case 2:
			//m_MFCPropertyGridOne.ExpandAll(TRUE);//IEEE 802.11gЭ�����Ϣչ����ʾ
			m_MFCPropertyGridOne.ShowWindow(SW_HIDE);//11a
			m_MFCPropertyGridB.ShowWindow(SW_HIDE);//11b
			m_MFCPropertyGridG.ShowWindow(SW_SHOW);//11g show
			m_MFCPropertyGridN.ShowWindow(SW_HIDE);//11n
			break;
		case 3:
			//m_MFCPropertyGridOne.ExpandAll(TRUE);//IEEE 802.11n M��N (1 SG)Э�����Ϣչ����ʾ
			m_MFCPropertyGridOne.ShowWindow(SW_HIDE);//11a
			m_MFCPropertyGridB.ShowWindow(SW_HIDE);//11b
			m_MFCPropertyGridG.ShowWindow(SW_HIDE);//11g
			m_MFCPropertyGridN.ShowWindow(SW_SHOW);//11n show

			break;
		case 4:
			//m_MFCPropertyGridOne.ExpandAll(TRUE);//IEEE 802.11n M��2 (2 SG,1 Arb)
			m_MFCPropertyGridOne.ShowWindow(SW_HIDE);//11a
			m_MFCPropertyGridB.ShowWindow(SW_HIDE);//11b
			m_MFCPropertyGridG.ShowWindow(SW_HIDE);//11g
			m_MFCPropertyGridN.ShowWindow(SW_SHOW);//11n
			break;
		case 5:
			//m_MFCPropertyGridOne.ExpandAll(TRUE);//IEEE 802.11n M��2 MIMO
			m_MFCPropertyGridOne.ShowWindow(SW_HIDE);//11a
			m_MFCPropertyGridB.ShowWindow(SW_HIDE);//11b
			m_MFCPropertyGridG.ShowWindow(SW_HIDE);//11g
			m_MFCPropertyGridN.ShowWindow(SW_SHOW);//11n
			break;
		case 6:
			//m_MFCPropertyGridOne.ExpandAll(TRUE);//IEEE 802.11n M��3 MIMO
			m_MFCPropertyGridOne.ShowWindow(SW_HIDE);//11a
			m_MFCPropertyGridB.ShowWindow(SW_HIDE);//11b
			m_MFCPropertyGridG.ShowWindow(SW_HIDE);//11g
			m_MFCPropertyGridN.ShowWindow(SW_SHOW);//11n
			break;
		case 7:
			//m_MFCPropertyGridOne.ExpandAll(TRUE);//IEEE 802.11n M��4 MIMO
			m_MFCPropertyGridOne.ShowWindow(SW_HIDE);//11a
			m_MFCPropertyGridB.ShowWindow(SW_HIDE);//11b
			m_MFCPropertyGridG.ShowWindow(SW_HIDE);//11g
			m_MFCPropertyGridN.ShowWindow(SW_SHOW);//11n show
			break;
		case 8:
			//m_MFCPropertyGridOne.ExpandAll(TRUE);//IEEE 802.11n 1��1 
			m_MFCPropertyGridOne.ShowWindow(SW_HIDE);//11a
			m_MFCPropertyGridB.ShowWindow(SW_HIDE);//11b
			m_MFCPropertyGridG.ShowWindow(SW_HIDE);//11g
			m_MFCPropertyGridN.ShowWindow(SW_SHOW);//11n show
			break;
		case 9:
			//m_MFCPropertyGridOne.ExpandAll(TRUE);//IEEE 802.11n 2��2
			m_MFCPropertyGridOne.ShowWindow(SW_HIDE);//11a
			m_MFCPropertyGridB.ShowWindow(SW_HIDE);//11b
			m_MFCPropertyGridG.ShowWindow(SW_HIDE);//11g
			m_MFCPropertyGridN.ShowWindow(SW_SHOW);//11n show
			break;
		case 10:
			//m_MFCPropertyGridOne.ExpandAll(TRUE);//IEEE 802.11n 4��4
			m_MFCPropertyGridOne.ShowWindow(SW_HIDE);//11a
			m_MFCPropertyGridB.ShowWindow(SW_HIDE);//11b
			m_MFCPropertyGridG.ShowWindow(SW_HIDE);//11g
			m_MFCPropertyGridN.ShowWindow(SW_SHOW);//11n show
			break;
		default:
			break;
		}
		//}
	}
	*pResult = 0;
}
	void CTabMac::OnDblclkListprotocol(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMainFrame*	m_mainframe = (CMainFrame*)(AfxGetMainWnd());
	CTabParent* p_tabParent = (CTabParent*)(m_mainframe->m_mainSplitter.GetPane(0,0));
	CTabCtrl* m_tabIndex = &(p_tabParent->m_mainTab);
	POSITION pos=m_configlist.GetFirstSelectedItemPosition();
	if (pos==NULL)
		return;
	else
	{
		while(pos)
		{
			int nItem = m_configlist.GetNextSelectedItem(pos);
			if (IDYES == AfxMessageBox(_T("ѡ����Э�飬�����������ã�"),MB_YESNO |MB_ICONINFORMATION ))
			{

				m_tabIndex->SetCurSel(1);// 0-config  1-carrier 2-params 3-instrument
				this->ShowWindow(SW_HIDE);//configҳ����
				p_tabParent->m_tabCarrier.ShowWindow(SW_SHOW);//ָ����Ҫ��ʾ��ҳ��
				//CListCtrl* p_CarrierInfoList = &(p_tabParent->m_tabCarrier.m_CarrierInfoList);//configҳ��p_CarrierInfoList ָ�� carrierҳ�� m_CarrierInfoList

				//p_tabParent->m_tabCarrier.nCarrier =0;
				switch(nItem)
				{
				case 0://11a
					{
                    m_mainframe->m_configIndex->ProtocolModel=OneA;
					//waveͼ�����޸�
					CGraphWAVE* m_wave =(CGraphWAVE*)((CMainFrame*)AfxGetMainWnd())->m_rightSplitter.GetPane(1,0);
					m_wave->m_wave[0].m_IQ_range=0.4;
					p_tabParent->m_protocol.SetWindowTextA("WLAN 802.11a");
					break;
					}
					
				case 1://11b
					{
						m_mainframe->m_configIndex->ProtocolModel =OneB;
						m_mainframe->m_configIndex->EZOA_Encoding = DBPSK_1M;
						CGraphWAVE* m_wave =(CGraphWAVE*)((CMainFrame*)AfxGetMainWnd())->m_rightSplitter.GetPane(1,0);
						m_wave->m_wave[0].m_IQ_range=1;
						p_tabParent->m_protocol.SetWindowTextA("WLAN 802.11b");
						break;
					}
					
				case 2://11g
					{
					 m_mainframe->m_configIndex->ProtocolModel = OneG;
					 m_mainframe->m_configIndex->data_rate = _6Mbps;
					 CGraphWAVE* m_wave =(CGraphWAVE*)((CMainFrame*)AfxGetMainWnd())->m_rightSplitter.GetPane(1,0);
					 m_wave->m_wave[0].m_IQ_range=1.0;
					 p_tabParent->m_protocol.SetWindowTextA("WLAN 802.11g");
					 break;
					}
				case 3:
					{
						m_mainframe->m_configIndex->ProtocolModel = OneN;
						for(int i=0;i<4;i++)
						{
							CGraphWAVE* m_wave =(CGraphWAVE*)((CMainFrame*)AfxGetMainWnd())->m_rightSplitter.GetPane(1,0);
							m_wave->m_wave[i].m_IQ_range=1.0;
						}
						p_tabParent->m_protocol.SetWindowTextA("WLAN 802.11n");
						break;
					}
					
				case 4:
					m_mainframe->m_configIndex->ProtocolModel = OneN;
					p_tabParent->m_protocol.SetWindowTextA("WLAN 802.11n");
					break;
				case 5:
					m_mainframe->m_configIndex->ProtocolModel = OneN;
					p_tabParent->m_protocol.SetWindowTextA("WLAN 802.11n");
					break;
				case 6:
					m_mainframe->m_configIndex->ProtocolModel = OneN;
					p_tabParent->m_protocol.SetWindowTextA("WLAN 802.11n");
					break;
				case 7:
					m_mainframe->m_configIndex->ProtocolModel = OneN;
					p_tabParent->m_protocol.SetWindowTextA("WLAN 802.11n");
					break;
				case 8:
					m_mainframe->m_configIndex->ProtocolModel = OneN;
					p_tabParent->m_protocol.SetWindowTextA("WLAN 802.11n");
					break;
				case 9:
					m_mainframe->m_configIndex->ProtocolModel = OneN;
					p_tabParent->m_protocol.SetWindowTextA("WLAN 802.11n");
					break;
				case 10:
					m_mainframe->m_configIndex->ProtocolModel = OneN;
					p_tabParent->m_protocol.SetWindowTextA("WLAN 802.11n");
					break;
				default:
					
					break;

				}
			    p_tabParent->m_tabCarrier.update();
			    p_tabParent->m_tabProtocolConfig.update();
			}
		}
	}
	*pResult = 0;
}
