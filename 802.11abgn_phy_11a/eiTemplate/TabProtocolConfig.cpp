// TabProtocolConfig.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "TabProtocolConfig.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "TabParent.h"
#include "MpduPara.h"
#include "MPDUGeneral.h"

IMPLEMENT_DYNAMIC(CTabProtocolConfig, CDialog)

CTabProtocolConfig::CTabProtocolConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CTabProtocolConfig::IDD, pParent)
{
	NumOfMPDU = 0;
	m_font.CreatePointFont(100,"΢���ź�");
	m_finished_ini = FALSE;
}

CTabProtocolConfig::~CTabProtocolConfig()
{
}

void CTabProtocolConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MPDU, m_MpduInfoList);
	DDX_Control(pDX, IDC_MPDUADD, m_MPDUAdd);
	DDX_Control(pDX, IDC_MPDUDELETE, m_MPDUDelete);
	
}


BEGIN_MESSAGE_MAP(CTabProtocolConfig, CDialog)
	ON_WM_SIZE()
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED,OnPropertyChanged)
	ON_BN_CLICKED(IDC_MPDUDELETE, &CTabProtocolConfig::OnBnClickedMpdudelete)
	ON_BN_CLICKED(IDC_MPDUADD, &CTabProtocolConfig::OnBnClickedMpduadd)
	ON_NOTIFY(NM_DBLCLK, IDC_MPDU, &CTabProtocolConfig::OnDblclkListMpdu)
END_MESSAGE_MAP()


// CTabProtocolConfig ��Ϣ�������


void CTabProtocolConfig::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialog::OnOK();
}


BOOL CTabProtocolConfig::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//�й�Э�����õ�ָ�봫�ݵ�����Э����
	//p_bluetoothparams = ((CMainFrame*)AfxGetMainWnd())->m_pass_to_thread.p_protocol_params;

	CRect rc;
	GetClientRect(&rc);
	//rc.bottom += 20;
	rc.left += 10;
	//rc.right += 10;
	rc.top += 10;

	//11aЭ��
	m_MFCPropertyGridThree.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP| WS_BORDER,rc,this,2003);
	m_MFCPropertyGridThree.EnableHeaderCtrl(FALSE,_T("����"),_T("ֵ"));
	m_MFCPropertyGridThree.EnableDescriptionArea();
	m_MFCPropertyGridThree.SetDescriptionRows(5);
	m_MFCPropertyGridThree.SetVSDotNetLook();
	m_MFCPropertyGridThree.MarkModifiedProperties();
	m_MFCPropertyGridThree.SetAlphabeticMode(false); 
	m_MFCPropertyGridThree.SetShowDragContext();

	pGroup31 = new CMFCPropertyGridProperty(_T("�ز���Ϣ"),MFCPROPERTYTO);
	pGroup32 = new CMFCPropertyGridProperty(_T("���Ʊ���"),MFCPROPERTYTO);
	pGroup33 = new CMFCPropertyGridProperty(_T("�غ�����"),MFCPROPERTYTO);
	pGroup34 = new CMFCPropertyGridProperty(_T("Ƶ�׿���"),MFCPROPERTYTO);
	pGroup35 = new CMFCPropertyGridProperty(_T("�ŵ�"));

	/*CMFCPropertyGridProperty **/pPropT1 = new CMFCPropertyGridProperty(_T("Э��"),_T("IEEE 802.11a"),_T("IEEE 802.11ϵ��֮һ��11a/b/g/n"),MFCPROPERTYTOO);
	pPropT1->Enable(FALSE);
	pGroup31->AddSubItem(pPropT1);
	/*CMFCPropertyGridProperty **/pPropT2 = new CMFCPropertyGridProperty(_T("֡��"),_T("20"),_T("��������֡����Ŀ"),MFCPROPERTYTOS);
	//pPropT2->Enable(FALSE);
	pGroup31->AddSubItem(pPropT2);
	/*CMFCPropertyGridProperty **/pPropT3 = new CMFCPropertyGridProperty(_T("Ƶ��ƫ��"),_T("+0.000000 Hz"),_T("����Ƶ��ƫ��"),MFCPROPERTYTOFR);
	//pPropT3->Enable(FALSE);
	pGroup31->AddSubItem(pPropT3);
	pPropT3a=new CMFCPropertyGridProperty(_T("����ʱ����"),_T("10.0"),_T("���ÿ���ʱ��������λ��s"),MFCPROPERTYTOT);
	pGroup31->AddSubItem(pPropT3a);
	pGroup31->AddSubItem(new CMFCPropertyGridProperty(_T("��Թ���"),_T("0.000 dB"),_T("������Թ��ʴ�С"),MFCPROPERTYTOFE));

	/*CMFCPropertyGridProperty* */pPropT4 = new CMFCPropertyGridProperty(_T("����"),_T("6 Mbps"),_T("������������֮һ��6��9��12��18��24��36��48��54 Mbps"),MFCPROPERTYTSO);
	pPropT4->AddOption(_T("6 Mbps"));  
	pPropT4->AddOption(_T("9 Mbps")); 
	pPropT4->AddOption(_T("12 Mbps"));  
	pPropT4->AddOption(_T("18 Mbps"));
	pPropT4->AddOption(_T("24 Mbps"));  
	pPropT4->AddOption(_T("36 Mbps"));
	pPropT4->AddOption(_T("48 Mbps"));  
	pPropT4->AddOption(_T("54 Mbps"));
	pPropT4->AllowEdit(FALSE);
	pGroup32->AddSubItem(pPropT4);
	
	/*CMFCPropertyGridProperty **/pPropT6 = new CMFCPropertyGridProperty(_T("���뷽ʽ"),_T("�������"),_T("���ڱ��뷽ʽ��˵��"),MFCPROPERTYTST);
	pPropT6->Enable(FALSE);
	pGroup32->AddSubItem(pPropT6);
	/*CMFCPropertyGridProperty **/pPropT7 = new CMFCPropertyGridProperty(_T("����"),_T("1/2"),_T("��ǰ�����µı�������"),MFCPROPERTYTSFR);
	pPropT7->Enable(FALSE);
	pGroup32->AddSubItem(pPropT7);
	/*CMFCPropertyGridProperty **/pPropT5 = new CMFCPropertyGridProperty(_T("���Ʒ�ʽ"),_T("BPSK"),_T("��ǰ�����µĵ��Ʒ�ʽ"),MFCPROPERTYTSSD);
	pPropT5->Enable(FALSE);
	pPropT5->SetData(100);
	pGroup32->AddSubItem(pPropT5);
	///*CMFCPropertyGridProperty**/ pPropT8 = new CMFCPropertyGridProperty(_T("��֯"),_T("On"),_T("���ý�֯��״̬��On/Off"),MFCPROPERTYTSFE);
	//pPropT8->AddOption(_T("On"));  
	//pPropT8->AddOption(_T("Off")); 
	//pPropT8->AllowEdit(FALSE);
	//pGroup32->AddSubItem(pPropT8);

	/*CMFCPropertyGridProperty**/ pPropT9 = new CMFCPropertyGridProperty(_T("OFDM ��Ƶ��"),_T("On"),_T("����OFDM��Ƶ����״̬��On/Off"),MFCPROPERTYTSSX);
	pPropT9->AddOption(_T("On"));  
	pPropT9->AddOption(_T("Off")); 
	pPropT9->AllowEdit(FALSE);
	pGroup32->AddSubItem(pPropT9);

	pPropT017 = new CMFCPropertyGridProperty(_T("��Ƶ����ʼֵ"),_T("93"),_T("������Ƶ����ֵ0-127"),MFCPROPERTYTSSE);
	pGroup32->AddSubItem(pPropT017);
	pPropT3b=new CMFCPropertyGridProperty(_T("���ز���"),_T("52"),_T("�������ز�����"),MFCPROPERTYTSET);
	pGroup32->AddSubItem(pPropT3b);
	pPropT3b->Enable(FALSE);
	/*pGroup33->AddSubItem(new CMFCPropertyGridProperty(_T("��������"),_T("PN9"),_T("˵����������"),MFCPROPERTYTTO));*/
	p_data_source = new CMFCPropertyGridProperty("����Դ","PN9","ѡ������Դ������",MFCPROPERTYTTO);
	p_data_source->AddOption("PN9");
	p_data_source->AddOption("PN15");
	p_data_source->AddOption("ALL0");
	p_data_source->AddOption("���ļ���ȡ");
	p_data_source->AllowEdit(FALSE);
	pGroup33->AddSubItem(p_data_source);

	p_data_filepath = new CMFCPropertyGridPropertyButton2("�ļ�·��","","ѡ������Դ�ļ����ڵ�·��",MFCPROPERTYTTS);
	p_data_filepath->Show(FALSE);
	pGroup33->AddSubItem(p_data_filepath);

	p_date_max_len = new CMFCPropertyGridProperty("���س���","80","���ø��صĳ��ȣ���λΪByte��",MFCPROPERTYTTT);
	pGroup33->AddSubItem(p_date_max_len);

	/*pPropT10 = new CMFCPropertyGridProperty(_T("PSDU"),_T("2960 symbols"),_T("PSDU�Ĵ�С"));
	pPropT10->Enable(FALSE);
	pGroup33->AddSubItem(pPropT10);
	pPropT11 = new CMFCPropertyGridProperty(_T("PPDU"),_T("3201 symbols"),_T("PPDU�Ĵ�С"));
	pPropT11->Enable(FALSE);
	pGroup33->AddSubItem(pPropT11);*/

	/*CMFCPropertyGridProperty **/pPropT12 = new CMFCPropertyGridProperty(_T("MACͷ��"),_T("Ĭ��"),_T("����MACͷ��"),MFCPROPERTYTTFR);
	pPropT12->AddOption(_T("Ĭ��"));  
	pPropT12->AddOption(_T("����")); 
	pPropT12->AllowEdit(FALSE);
	pGroup33->AddSubItem(pPropT12);
	
	/*CMFCPropertyGridProperty**/ pPropT13 = new CMFCPropertyGridProperty(_T("FCS"),_T("On"),_T("����MAC FCS��״̬��On/Off"),MFCPROPERTYTTFE);
	pPropT13->AddOption(_T("On"));  
	pPropT13->AddOption(_T("Off")); 
	pPropT13->AllowEdit(FALSE);
	pGroup33->AddSubItem(pPropT13);

	pPropT14 = new CMFCPropertyGridProperty(_T("�˲���"),_T("��"),_T("�����˲���������"),MFCPROPERTYTFO);
	pPropT14->AddOption("��");  
	pPropT14->AddOption("��˹�˲���");
	pPropT14->AddOption("���������˲���");
	pPropT14->AddOption("�����ͨ�˲���");
	pPropT14->AddOption("�û��Զ���");
	pGroup34->AddSubItem(pPropT14);
	lp_filter_len = new CMFCPropertyGridProperty("�˲�������","30","���õ�ͨ�˲�������",LPFILTERLEN);
	lp_filter_len->Show(FALSE);
	pGroup34->AddSubItem(lp_filter_len);
	lp_filter_wn = new CMFCPropertyGridProperty("�˲���ͨ��","0.24","�����˲���ͨ�� Wn",LPFILTERWN);
	lp_filter_wn->Show(FALSE);
	pGroup34->AddSubItem(lp_filter_wn);

	gauss_filter_len = new CMFCPropertyGridProperty("�˲�������","30","���õ�ͨ�˲�������",GAUSSFILTERLEN);
	gauss_filter_len->Show(FALSE);
	pGroup34->AddSubItem(gauss_filter_len);
	gauss_filter_BT = new CMFCPropertyGridProperty("BT","0.5","�����˲���ͨ�� BT",GAUSSFILTERBT);
	gauss_filter_BT->Show(FALSE);
	pGroup34->AddSubItem(gauss_filter_BT);

	cosine_filter_len = new CMFCPropertyGridProperty("�˲�������","30","���õ�ͨ�˲�������",COSINEFILTERLEN);
	cosine_filter_len->Show(FALSE);
	pGroup34->AddSubItem(cosine_filter_len);
	cosine_filter_alpha = new CMFCPropertyGridProperty("alpha","0.24","�����˲���alpha",COSINEFILTERALPHA);
	cosine_filter_alpha->Show(FALSE);
	pGroup34->AddSubItem(cosine_filter_alpha);
	filter_user = new CMFCPropertyGridPropertyButton("�˲���ϵ��","","�����û��Զ����˲���ϵ��",FILTERUSERDEFINE);
	filter_user->Show(FALSE);
	pGroup34->AddSubItem(filter_user);
	pPropT15 = new CMFCPropertyGridProperty(_T("���ڳ���"),_T("8"),_T("�����˲������ڵĳ��ȣ����ڳ��Ȳ��ܳ���һ��OFDM���ŵĳ���"),MFCPROPERTYTFS);
	pGroup34->AddSubItem(pPropT15);

	/*CMFCPropertyGridProperty *pPropT16 = new CMFCPropertyGridProperty(_T("�ŵ�ģ��"),_T("��"),_T("��/�����ŵ�ģ�͵�����"),MFCPROPERTYTTNS);
	pPropT16->AddOption(_T("��"));  
	pPropT16->AddOption(_T("ѡ��")); 
	pPropT16->AllowEdit(FALSE);
	pGroup35->AddSubItem(pPropT16);*/

	pPropT16 = new CMFCPropertyGridProperty(_T("�ŵ�״̬"),_T("off"),_T("�����ŵ�״̬���ź��Ƿ񾭹��ŵ�"),PPROPCHANNEL4);
	pPropT16->AddOption("on");
	pPropT16->AddOption("off");
	pGroup35->AddSubItem(pPropT16);

	pPropT17 = new CMFCPropertyGridProperty(_T("�ŵ��ྶ��"),_T("4"),_T("���öྶ�ŵ��жྶ��"),PPROPCHANNEL1);
	pGroup35->AddSubItem(pPropT17);
	
	pPropT18 = new CMFCPropertyGridProperty(_T("�ź���Ƶ"),_T("2.412"),_T("�ŵ���Ƶ���ã���λ GHz"),PPROPCHANNEL2);
	pGroup35->AddSubItem(pPropT18);
	
	pPropT19 = new CMFCPropertyGridProperty(_T("�ƶ��ٶ�"),_T("30"),_T("�ƶ��ٶ����ã���λ km/h"),PPROPCHANNEL3);
	pGroup35->AddSubItem(pPropT19);

	///*CMFCPropertyGridProperty* */pPropT20 = new CMFCPropertyGridProperty(_T("Eb/N0"),_T("0.00 dB"),_T("����SINR��ֵ��С"),PPROPCHANNEL4);
	//pGroup35->AddSubItem(pPropT20);

/*
	pGroup33->Expand(FALSE);*/
	pGroup34->Expand(TRUE);
	pGroup35->Expand(TRUE);

	m_MFCPropertyGridThree.AddProperty(pGroup31);
	m_MFCPropertyGridThree.AddProperty(pGroup32);
	m_MFCPropertyGridThree.AddProperty(pGroup33);
	m_MFCPropertyGridThree.AddProperty(pGroup34);
	m_MFCPropertyGridThree.AddProperty(pGroup35);

	m_MFCPropertyGridThree.EnableDescriptionArea(TRUE);
	m_MFCPropertyGridThree.SetCustomColors(RGB(250,250,250),RGB(0,0,0),RGB(230,230,230),RGB(100,100,100),RGB(230,230,230),RGB(0,0,0),RGB(220,220,220));
	m_MFCPropertyGridThree.ShowWindow(TRUE);
	
	//11nЭ��
	m_MFCPropertyGridThreeN.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP| WS_BORDER,rc,this,2004);
	m_MFCPropertyGridThreeN.EnableHeaderCtrl(FALSE,_T("����"),_T("ֵ"));
	m_MFCPropertyGridThreeN.SetVSDotNetLook();
	m_MFCPropertyGridThreeN.MarkModifiedProperties();
	m_MFCPropertyGridThreeN.SetAlphabeticMode(false); 
	m_MFCPropertyGridThreeN.SetShowDragContext();

	//pGroup36 = new CMFCPropertyGridProperty(_T("1.ģʽѡ��"));
	pGroup37 = new CMFCPropertyGridProperty(_T("���ݰ�"));
	pGroup38 = new CMFCPropertyGridProperty(_T("���Ʊ���"));
	pGroup39 = new CMFCPropertyGridProperty(_T("�غ�����"));
	pGroup40 = new CMFCPropertyGridProperty(_T("Ƶ�׿���"));
	pGroup41 = new CMFCPropertyGridProperty(_T("�ŵ�"));

	pPropT21 = new CMFCPropertyGridProperty(_T("����"),_T("0"),_T("ȡֵΪ0��1��0��ʾ���ݰ���PPDU����1��ʾ�����ݰ���Ĭ��Ϊ0"),MFCPROPERTYOFIN);  
	pPropT21->AddOption(_T("0"));  
	pPropT21->AddOption(_T("1"));
	pGroup37->AddSubItem(pPropT21);
	pPropT211 = new CMFCPropertyGridProperty(_T("���ݸ���"),_T("20"),_T("�������ݰ�����"),MFCPROPERTYOFINN);
	pGroup37->AddSubItem(pPropT211);
	pPropT22 = new CMFCPropertyGridProperty(_T("MCS������"),_T("10"),_T("ȡֵΪ0-76��Ĭ��10"),MFCPROPERTYOSIN);  
	//pPropT22->AddOption(_T("1"));  
	//pPropT22->AddOption(_T("..."));
	pGroup38->AddSubItem(pPropT22);

	pPropT23a = new CMFCPropertyGridProperty(_T("  ���Ʒ�ʽ��1"),_T("QPSK"),_T("����������ȡֵ"));
	pPropT23a->Enable(FALSE);
	pGroup38->AddSubItem(pPropT23a);
	pPropT23b = new CMFCPropertyGridProperty(_T("  ���Ʒ�ʽ��2"),_T("QPSK"),_T("����������ȡֵ"));
	pPropT23b->Enable(FALSE);
	pPropT23b->Show(FALSE);
	pGroup38->AddSubItem(pPropT23b);
	pPropT23c = new CMFCPropertyGridProperty(_T("  ���Ʒ�ʽ��3"),_T("QPSK"),_T("����������ȡֵ"));
	pPropT23c->Enable(FALSE);
	pPropT23c->Show(FALSE);
	pGroup38->AddSubItem(pPropT23c);
	pPropT23d = new CMFCPropertyGridProperty(_T("  ���Ʒ�ʽ��4"),_T("QPSK"),_T("����������ȡֵ"));
	pPropT23d->Enable(FALSE);
	pPropT23d->Show(FALSE);
	pGroup38->AddSubItem(pPropT23d);

	pPropT24 = new CMFCPropertyGridProperty(_T("����"),_T("3/4"),_T("����������ȡֵ"));  
	pPropT24->Enable(FALSE);
	pGroup38->AddSubItem(pPropT24);
	pPropT25 = new CMFCPropertyGridProperty(_T("��������"),_T("39.0Mbps"),_T("����������ȡֵ"));  
	pPropT25->Enable(FALSE);
	pGroup38->AddSubItem(pPropT25);
	pPropT25a = new CMFCPropertyGridProperty(_T("�ռ�����(Nss)"),_T("2"),_T("����������ȡֵ"));  
	pPropT25a->Enable(FALSE);
	pGroup38->AddSubItem(pPropT25a);
	pPropT25c = new CMFCPropertyGridProperty(_T("��ʱ����(Nsts)"),_T("2"),_T("NssΪ1,Nstsȡֵ1-2;NssΪ2,Nstsȡֵ2-4;NssΪ3,Nstsȡֵ3-4"),MFCPROPERTYOFINN1); 
	//pPropT25b->Enable(FALSE);
	pGroup38->AddSubItem(pPropT25c);
	pPropT25b = new CMFCPropertyGridProperty(_T("��ʱ����(STBC)"),_T("0"),_T("����Nss,Nstsȡֵ,ΪNsts-Nss"),MFCPROPERTYOFINN2); 
	pPropT25b->Enable(FALSE);
	pGroup38->AddSubItem(pPropT25b);
	/*pPropT26 = new CMFCPropertyGridProperty(_T("����������Ŀ"),_T("1"),_T("ȡֵΪ1-4��Ĭ��1"),MFCPROPERTYOSEN);  
	pPropT26->AddOption(_T("1"));  
	pPropT26->AddOption(_T("2"));
	pPropT26->AddOption(_T("3"));  
	pPropT26->AddOption(_T("4"));
	pGroup38->AddSubItem(pPropT26);*/
	pPropT25d = new CMFCPropertyGridProperty(_T("Ness"),_T("0"),_T("Ness��Nsts�ĺ�С�ڵ���������,Ness����Neltf�ĸ���:NessΪ0,Neltfȡֵ0;NessΪ1,Neltfȡֵ1;NessΪ2,Neltfȡֵ2;NessΪ3,Neltfȡֵ4"),MFCPROPERTYOFINN3); 
	//pPropT25b->Enable(FALSE);
	pGroup38->AddSubItem(pPropT25d);
	pPropT28 = new CMFCPropertyGridProperty(_T("�������"),_T("Off"),_T("Off��ʾ���汣�������On��ʾ�̱��������Ĭ��Ϊ��."),MFCPROPERTYOEIN);  
	pPropT28->AddOption(_T("On"));  
	pPropT28->AddOption(_T("Off"));
	pGroup38->AddSubItem(pPropT28);
	pPropT288 = new CMFCPropertyGridProperty(_T("ʱ��Ӵ�"),_T("Off"),_T("On:��ʾ�Ӵ���Off:��ʾ�޼Ӵ���Ĭ��ΪOff."),MFCPROPERTYOEINN);  
	pPropT288->AddOption(_T("On"));  
	pPropT288->AddOption(_T("Off"));
	pGroup38->AddSubItem(pPropT288);
	/*pPropT29 = new CMFCPropertyGridProperty(_T("��������"),_T("Off"),_T("On:��ʾ�в������Σ�Off:��ʾ�޲������Ρ�Ĭ��ΪOff."),MFCPROPERTYOEIN);  
	pPropT29->AddOption(_T("On"));  
	pPropT29->AddOption(_T("Off"));
	pGroup38->AddSubItem(pPropT29);*/
	pPropT30 = new CMFCPropertyGridProperty(_T("�ռ�ӳ�����"),_T("ֱ��ӳ��"),_T("�ռ�ӳ����ƣ�ֱ��ӳ��Ϳռ���չ"),MFCPROPERTYONIN);  
	pPropT30->AddOption(_T("ֱ��ӳ��"));  
	pPropT30->AddOption(_T("�ռ���չ"));  
	//pPropT30->AddOption(_T("2"));
	//pPropT30->AddOption(_T("4"));  
	//pPropT30->AddOption(_T("5"));
	pGroup38->AddSubItem(pPropT30);
	pPropT31 = new CMFCPropertyGridProperty(_T("�ŵ�����"),_T("BCC"),_T("BCC��ʾ��0����LDPC��ʾ��1����Ĭ��Ϊ0"),MFCPROPERTYS0N);
	pPropT31->AddOption(_T("LDPC"));  
	pPropT31->AddOption(_T("BCC"));
	pGroup38->AddSubItem(pPropT31);
	pPropT32 = new CMFCPropertyGridProperty(_T("��֯"),_T("On"),_T("BCC��ʽ����ѡ����أ�LDPC��ʽ�£��أ����ɱ༭"),MFCPROPERTYSSN);
	pPropT32->AddOption(_T("On"));  
	pPropT32->AddOption(_T("Off"));
	pGroup38->AddSubItem(pPropT32);
	pPropT32a = new CMFCPropertyGridProperty(_T("������"),_T("On"),_T("Off��ʾ���ء���On��ʾ��������Ĭ��ΪOn"),MFCPROPERTYSSN1);
	pPropT32a->AddOption(_T("On"));  
	pPropT32a->AddOption(_T("Off"));
	pGroup38->AddSubItem(pPropT32a);
	
	pPropT27 = new CMFCPropertyGridProperty(_T("�����ʼֵ"),_T("93"),_T("�����ʼֵ���ã���Χ0-127"),MFCPROPERTYSSNN);  
	pGroup38->AddSubItem(pPropT27);
	pPropT33 = new CMFCPropertyGridProperty(_T("�ۺ�MPDU"),_T("off"),_T("Off��ʾ���ء���On��ʾ��������Ĭ��Ϊoff"),MFCPROPERTYSTN);
	pPropT33->AddOption(_T("on"));  
	pPropT33->AddOption(_T("off"));
	pGroup39->AddSubItem(pPropT33);
	pPropT34 = new CMFCPropertyGridProperty(_T("Smoothing"),_T("Off"),_T("off��ʾ���ء���on��ʾ��������Ĭ��Ϊoff"),MFCPROPERTYSFN);
	pPropT34->AddOption(_T("on"));  
	pPropT34->AddOption(_T("off"));
	pGroup39->AddSubItem(pPropT34);
	pPropT35 = new CMFCPropertyGridProperty(_T("Sounding"),_T("Off"),_T("off��ʾ���ء���on��ʾ��������Ĭ��Ϊoff"),MFCPROPERTYSFIN);
	pPropT35->AddOption(_T("on"));  
	pPropT35->AddOption(_T("off"));
	pGroup39->AddSubItem(pPropT35);

	pPropT36 = new CMFCPropertyGridProperty("����Դ","PN9","ѡ������Դ������",MFCPROPERTYSSIN);
	pPropT36->AddOption("PN9");
	pPropT36->AddOption("PN15");
	pPropT36->AddOption("ALL0");
	pPropT36->AddOption("���ļ���ȡ");
	pPropT36->AllowEdit(FALSE);
	pGroup39->AddSubItem(pPropT36);

	
	pPropT37 = new CMFCPropertyGridProperty(_T("���ݳ���"),_T("80"),_T("Ĭ��1-1000��ʮ�������֣��û�����."),MFCPROPERTYSSEN);
	pGroup39->AddSubItem(pPropT37);
	p_data_filepath_n = new CMFCPropertyGridProperty("�ļ�·��","","ѡ������Դ�ļ����ڵ�·��",NFILEPATH);
	p_data_filepath_n->Show(FALSE);
	pGroup39->AddSubItem(p_data_filepath_n);
	//�����˲���
	fitertype_n = new CMFCPropertyGridProperty(_T("�˲���"),_T("��"),_T("�����˲���������"),NMFCPROPERTYTFO);
	fitertype_n->AddOption("��");  
	fitertype_n->AddOption("��˹�˲���");
	fitertype_n->AddOption("���������˲���");
	fitertype_n->AddOption("�����ͨ�˲���");
	fitertype_n->AddOption("�û��Զ���");
	pGroup40->AddSubItem(fitertype_n);
	lp_filter_len_n = new CMFCPropertyGridProperty("�˲�������","30","���õ�ͨ�˲�������",NLPFILTERLEN);
	lp_filter_len_n->Show(FALSE);
	pGroup40->AddSubItem(lp_filter_len_n);
	lp_filter_wn_n = new CMFCPropertyGridProperty("�˲���ͨ��","0.24","�����˲���ͨ�� Wn",NLPFILTERWN);
	lp_filter_wn_n->Show(FALSE);
	pGroup40->AddSubItem(lp_filter_wn_n);

	gauss_filter_len_n = new CMFCPropertyGridProperty("�˲�������","30","���õ�ͨ�˲�������",NGAUSSFILTERLEN);
	gauss_filter_len_n->Show(FALSE);
	pGroup40->AddSubItem(gauss_filter_len_n);
	gauss_filter_BT_n = new CMFCPropertyGridProperty("BT","0.5","�����˲���ͨ�� BT",NGAUSSFILTERBT);
	gauss_filter_BT_n->Show(FALSE);
	pGroup40->AddSubItem(gauss_filter_BT_n);

	cosine_filter_len_n = new CMFCPropertyGridProperty("�˲�������","30","���õ�ͨ�˲�������",NCOSINEFILTERLEN);
	cosine_filter_len_n->Show(FALSE);
	pGroup40->AddSubItem(cosine_filter_len_n);
	cosine_filter_alpha_n = new CMFCPropertyGridProperty("alpha","0.24","�����˲���alpha",NCOSINEFILTERALPHA);
	cosine_filter_alpha_n->Show(FALSE);
	pGroup40->AddSubItem(cosine_filter_alpha_n);
	filter_user_n = new CMFCPropertyGridPropertyButton("�˲���ϵ��","","�����û��Զ����˲���ϵ��",NFILTERUSERDEFINE);
	filter_user_n->Show(FALSE);
	pGroup40->AddSubItem(filter_user_n);
	pPropT38 = new CMFCPropertyGridProperty(_T("ʱ��Ӵ�"),_T("1"),_T("��0����ʾ���Ӵ�����1����ʾ�Ӵ�"),MFCPROPERTYOFN);  
	pPropT38->AddOption(_T("0"));  
	pPropT38->AddOption(_T("1"));
	pGroup40->AddSubItem(pPropT38);

	pPropT39 = new CMFCPropertyGridProperty(_T("�ŵ�״̬"),_T("off"),_T("���ء��򡮿�����Ĭ��Ϊ��"),MFCPROPERTYSEIN);
	pPropT39->AddOption(_T("on"));  
	pPropT39->AddOption(_T("off"));
	pGroup41->AddSubItem(pPropT39);
	pPropT40 = new CMFCPropertyGridProperty(_T("�ŵ�����"),_T("A"),_T("A��B��C��D��E��F��Ӧ��ͬ��Ӧ�ó���"),CHANNELTYPE);
	pPropT40->AddOption(_T("A"));  
	pPropT40->AddOption(_T("B"));
	pPropT40->AddOption(_T("C"));  
	pPropT40->AddOption(_T("D"));
	pPropT40->AddOption(_T("E"));  
	pPropT40->AddOption(_T("F"));
	pGroup41->AddSubItem(pPropT40);

	numofNt = new CMFCPropertyGridProperty("����������","1","���÷������ߵ���Ŀ",NUMOFTXANNEA);
	pGroup41->AddSubItem(numofNt);
	numofNr = new CMFCPropertyGridProperty("�ն�������","1","�����ն����ߵ���Ŀ",NUMOFRXANNEA);
	pGroup41->AddSubItem(numofNr);
	pPropT41 = new CMFCPropertyGridProperty(_T("�ƶ��ٶ�"),_T("30"),_T("�ƶ��ٶȣ���λkm/h"),MFCPROPERTYTON);
	pGroup41->AddSubItem(pPropT41);
	pPropT42 = new CMFCPropertyGridProperty(_T("�ز�Ƶ��"),_T("2.412"),_T("�ز�Ƶ�ʣ���λGHz"),MFCPROPERTYTSN);
	pGroup41->AddSubItem(pPropT42);

	//pGroup39->Expand(FALSE);
	pGroup40->Expand(TRUE);
	pGroup41->Expand(TRUE);
	
	//m_MFCPropertyGridThreeN.AddProperty(pGroup36);
	m_MFCPropertyGridThreeN.AddProperty(pGroup37);
	m_MFCPropertyGridThreeN.AddProperty(pGroup38);
	m_MFCPropertyGridThreeN.AddProperty(pGroup39);
	m_MFCPropertyGridThreeN.AddProperty(pGroup40);
	m_MFCPropertyGridThreeN.AddProperty(pGroup41);


	m_MFCPropertyGridThreeN.EnableDescriptionArea(TRUE);
	m_MFCPropertyGridThreeN.SetDescriptionRows(5);
	m_MFCPropertyGridThreeN.SetCustomColors(RGB(250,250,250),RGB(0,0,0),RGB(230,230,230),RGB(100,100,100),RGB(230,230,230),RGB(0,0,0),RGB(220,220,220));
	m_MFCPropertyGridThreeN.ShowWindow(FALSE);
	
	//11nЭ��Legacyģʽ
	m_MFCPropertyGridThreeNL.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP /*| WS_BORDER*/,rc,this,2005);
	m_MFCPropertyGridThreeNL.EnableHeaderCtrl(FALSE,_T("����"),_T("ֵ"));
	m_MFCPropertyGridThreeNL.EnableDescriptionArea();
	m_MFCPropertyGridThreeNL.SetVSDotNetLook();
	m_MFCPropertyGridThreeNL.MarkModifiedProperties();
	m_MFCPropertyGridThreeNL.SetAlphabeticMode(false); 
	m_MFCPropertyGridThreeNL.SetShowDragContext();

	pGroup47 = new CMFCPropertyGridProperty(_T("���Ʊ���"));
	pGroup48 = new CMFCPropertyGridProperty(_T("�غ�����"));
	pGroup49 = new CMFCPropertyGridProperty(_T("Ƶ�׿���"));
	pGroup50 = new CMFCPropertyGridProperty(_T("�ŵ�"));


	pPropT44 = new CMFCPropertyGridProperty(_T("��������"),_T("6 Mbps"),_T("ѡ����������"),MFCPROPERTYOSIN);  
	pPropT44->AddOption(_T("6 Mbps"));  
	pPropT44->AddOption(_T("9 Mbps")); 
	pPropT44->AddOption(_T("12 Mbps"));  
	pPropT44->AddOption(_T("18 Mbps"));
	pPropT44->AddOption(_T("24 Mbps"));  
	pPropT44->AddOption(_T("36 Mbps"));
	pPropT44->AddOption(_T("48 Mbps"));  
	pPropT44->AddOption(_T("54 Mbps"));
	pPropT44->AllowEdit(FALSE);
	pGroup47->AddSubItem(pPropT44);
	pPropT45 = new CMFCPropertyGridProperty(_T("���Ʒ�ʽ"),_T("BPSK"),_T("����������ȡֵ"));
	pPropT45->Enable(FALSE);
	pGroup47->AddSubItem(pPropT45);
	pPropT46 = new CMFCPropertyGridProperty(_T("����"),_T("1/2"),_T("����������ȡֵ"));  
	pPropT46->Enable(FALSE);
	pGroup47->AddSubItem(pPropT46);
	pPropT47 = new CMFCPropertyGridProperty(_T("������"),_T("On"),_T("����������"),MFCPROPERTYOSENL1);  
	pPropT47->Enable(FALSE);
	pGroup47->AddSubItem(pPropT47);
	pPropT48 = new CMFCPropertyGridProperty(_T("�����ʼֵ"),_T("93"),_T("ȡֵ0-127��Ĭ��93.��ֵ���û�����"),MFCPROPERTYOSENL);  
	pGroup47->AddSubItem(pPropT48);
	pPropT49 = new CMFCPropertyGridProperty(_T("�ŵ�����"),_T("BCC"),_T("�ŵ����뷽ʽ��BCC�����ɱ༭"));  
	pPropT49->Enable(FALSE);
	pGroup47->AddSubItem(pPropT49);
	pPropT50 = new CMFCPropertyGridProperty(_T("��֯"),_T("On"),_T("Ĭ��Ϊ��"),MFCPROPERTYOEINL);  
	pPropT50->Enable(FALSE);
	pGroup47->AddSubItem(pPropT50);
	/*pPropT56 = new CMFCPropertyGridProperty(_T("ʱ��Ӵ�"),_T("off"),_T("��off����ʾ���Ӵ�����on����ʾ�Ӵ�"),MFCPROPERTYOFL);  
	pPropT56->AddOption(_T("on"));  
	pPropT56->AddOption(_T("off"));
	pGroup47->AddSubItem(pPropT56);*/
	/*pPropT51 = new CMFCPropertyGridProperty(_T("�ۺ�MPDU"),_T("off"),_T("off��ʾ���ء���on��ʾ��������Ĭ��Ϊ0"),MFCPROPERTYSTL);
	pPropT51->AddOption(_T("on"));  
	pPropT51->AddOption(_T("off"));
	pGroup48->AddSubItem(pPropT51);*/
	pPropT52 = new CMFCPropertyGridProperty(_T("Smoothing"),_T("off"),_T("off��ʾ���ء���on��ʾ��������Ĭ��Ϊ0"),MFCPROPERTYSFL);
	pPropT52->AddOption(_T("on"));  
	pPropT52->AddOption(_T("off"));
	pGroup48->AddSubItem(pPropT52);
	pPropT53 = new CMFCPropertyGridProperty(_T("Not Sounding"),_T("off"),_T("off��ʾ���ء���on��ʾ��������Ĭ��Ϊ0"),MFCPROPERTYSFIL);
	pPropT53->AddOption(_T("on"));  
	pPropT53->AddOption(_T("off"));
	pGroup48->AddSubItem(pPropT53);
	

	/*pPropT54 = new CMFCPropertyGridProperty(_T("���ݳ���"),_T("--"),_T("1-65535���û�����."),MFCPROPERTYSSIL);
	pGroup48->AddSubItem(pPropT54);
	pPropT55 = new CMFCPropertyGridProperty(_T("����"),_T("--"),_T("Ĭ��1-1000��ʮ�������֣��û�����."),MFCPROPERTYSSEL);
	pGroup48->AddSubItem(pPropT55);*/

	//����Դ�ؼ�
	pPropT54 = new CMFCPropertyGridProperty("����Դ","PN9","ѡ������Դ������",NLDATASOURCE);
	pPropT54->AddOption("PN9");
	pPropT54->AddOption("PN15");
	pPropT54->AddOption("ALL0");
	pPropT54->AddOption("���ļ���ȡ");
	pPropT54->AllowEdit(FALSE);
	pGroup48->AddSubItem(pPropT54);


	p_data_filepath_nl = new CMFCPropertyGridPropertyButton2("�ļ�·��","","ѡ������Դ�ļ����ڵ�·��",MFCPROPERTYOFL);
	p_data_filepath_nl->Show(FALSE);
	pGroup48->AddSubItem(p_data_filepath_nl);

	pPropT55 = new CMFCPropertyGridProperty(_T("���ݳ���"),_T("80"),_T("Ĭ��1-1000��ʮ�������֣��û�����."),MFCPROPERTYSSEL);
	pGroup48->AddSubItem(pPropT55);

	
	
	fitertype_nl = new CMFCPropertyGridProperty(_T("�˲���"),_T("��"),_T("�����˲���������"),NLMFCPROPERTYTFO);
	fitertype_nl->AddOption("��");  
	fitertype_nl->AddOption("��˹�˲���");
	fitertype_nl->AddOption("���������˲���");
	fitertype_nl->AddOption("�����ͨ�˲���");
	fitertype_nl->AddOption("�û��Զ���");
	pGroup49->AddSubItem(fitertype_nl);
	lp_filter_len_nl = new CMFCPropertyGridProperty("�˲�������","30","���õ�ͨ�˲�������",NLLPFILTERLEN);
	lp_filter_len_nl->Show(FALSE);
	pGroup49->AddSubItem(lp_filter_len_nl);
	lp_filter_wn_nl = new CMFCPropertyGridProperty("�˲���ͨ��","0.24","�����˲���ͨ�� Wn",NLLPFILTERWN);
	lp_filter_wn_nl->Show(FALSE);
	pGroup49->AddSubItem(lp_filter_wn_nl);

	gauss_filter_len_nl = new CMFCPropertyGridProperty("�˲�������","30","���õ�ͨ�˲�������",NLGAUSSFILTERLEN);
	gauss_filter_len_nl->Show(FALSE);
	pGroup49->AddSubItem(gauss_filter_len_nl);
	gauss_filter_BT_nl = new CMFCPropertyGridProperty("BT","0.5","�����˲���ͨ�� BT",NLGAUSSFILTERBT);
	gauss_filter_BT_nl->Show(FALSE);
	pGroup49->AddSubItem(gauss_filter_BT_nl);

	cosine_filter_len_nl = new CMFCPropertyGridProperty("�˲�������","30","���õ�ͨ�˲�������",NLCOSINEFILTERLEN);
	cosine_filter_len_nl->Show(FALSE);
	pGroup49->AddSubItem(cosine_filter_len_nl);
	cosine_filter_alpha_nl = new CMFCPropertyGridProperty("alpha","0.24","�����˲���alpha",NLCOSINEFILTERALPHA);
	cosine_filter_alpha_nl->Show(FALSE);
	pGroup49->AddSubItem(cosine_filter_alpha_nl);
	filter_user_nl = new CMFCPropertyGridPropertyButton("�˲���ϵ��","","�����û��Զ����˲���ϵ��",NLFILTERUSERDEFINE);
	filter_user_nl->Show(FALSE);
	pGroup49->AddSubItem(filter_user_nl);
	pPropT15 = new CMFCPropertyGridProperty(_T("���ڳ���"),_T("8"),_T("�����˲������ڵĳ��ȣ����ڳ��Ȳ��ܳ���һ��OFDM���ŵĳ���"),MFCPROPERTYTFS);
	pGroup49->AddSubItem(pPropT15);

	pPropT57 = new CMFCPropertyGridProperty(_T("�ŵ�״̬"),_T("off"),_T("���ء��򡮿�����Ĭ��Ϊ��"),CHANNELSTATEL);
	pPropT57->AddOption(_T("on"));  
	pPropT57->AddOption(_T("off"));
	pGroup50->AddSubItem(pPropT57);
	pPropT58 = new CMFCPropertyGridProperty(_T("����ѡ��"),_T("A"),_T("A��B��C��D��E��F��User Defined"),CHANNELTYPEL);
	pPropT58->AddOption(_T("A"));  
	pPropT58->AddOption(_T("B"));
	pPropT58->AddOption(_T("C"));  
	pPropT58->AddOption(_T("D"));
	pPropT58->AddOption(_T("E"));  
	pPropT58->AddOption(_T("F")); 
	pGroup50->AddSubItem(pPropT58);
	pPropT59 = new CMFCPropertyGridProperty(_T("����������"),_T("1"),_T("�����������Ŀ"),NUMOFTXANNEAL);
	pPropT59->AddOption("1");
	pPropT59->AddOption("2");
	pPropT59->AddOption("3");
	pPropT59->AddOption("4");
	pGroup50->AddSubItem(pPropT59);
	pPropT60 = new CMFCPropertyGridProperty(_T("�ն�������"),_T("2"),_T("�ն����ߵ���Ŀ"),NUMOFRXANNEAL);
	pPropT60->AddOption("1");
	pPropT60->AddOption("2");
	pPropT60->AddOption("3");
	pPropT60->AddOption("4");
	pGroup50->AddSubItem(pPropT60);
	carrierfreq = new CMFCPropertyGridProperty(_T("�ź���Ƶ"),_T("2.412"),_T("�ź���Ƶ GHz"),CARRIERFREQ);
	pGroup50->AddSubItem(carrierfreq);
	mobilespeed = new CMFCPropertyGridProperty(_T("�ƶ����ٶ�"),_T("30"),_T("�ƶ��ٶ� Km/h"),MOBILESPEEDL);
	pGroup50->AddSubItem(mobilespeed);


	m_MFCPropertyGridThreeNL.AddProperty(pGroup47);
	m_MFCPropertyGridThreeNL.AddProperty(pGroup48);
	m_MFCPropertyGridThreeNL.AddProperty(pGroup49);
	m_MFCPropertyGridThreeNL.AddProperty(pGroup50);

	m_MFCPropertyGridThreeNL.EnableDescriptionArea(TRUE);
	m_MFCPropertyGridThreeNL.SetDescriptionRows(5);
	m_MFCPropertyGridThreeNL.SetCustomColors(RGB(250,250,250),RGB(0,0,0),RGB(230,230,230),RGB(100,100,100),RGB(230,230,230),RGB(0,0,0),RGB(220,220,220));
	m_MFCPropertyGridThreeNL.ShowWindow(FALSE);
	
	//11bЭ��
	m_MFCPropertyGridThreeB.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP /*| WS_BORDER*/,rc,this,2006);
	m_MFCPropertyGridThreeB.EnableHeaderCtrl(FALSE,_T("����"),_T("ֵ"));
	m_MFCPropertyGridThreeB.EnableDescriptionArea();
	m_MFCPropertyGridThreeB.SetVSDotNetLook();
	m_MFCPropertyGridThreeB.MarkModifiedProperties();
	m_MFCPropertyGridThreeB.SetAlphabeticMode(false); 
	m_MFCPropertyGridThreeB.SetShowDragContext();

	pGroup42 = new CMFCPropertyGridProperty(_T("�ز�����"));
	pGroup43 = new CMFCPropertyGridProperty(_T("���Ʊ���"));
	pGroup44 = new CMFCPropertyGridProperty(_T("�غ�����"));
	pGroup46 =new CMFCPropertyGridProperty("Ƶ�׿���");
	pGroup45 = new CMFCPropertyGridProperty(_T("�ŵ�"));

	pPropT61 = new CMFCPropertyGridProperty(_T("Э��"),_T("IEEE 802.11b"),_T("IEEE 802.11ϵ��֮һ��11a/b/g/n"));
	pPropT61->Enable(FALSE);
	pGroup42->AddSubItem(pPropT61);
	pPropT62=new CMFCPropertyGridProperty(_T("֡��"),_T("20"),_T("���������룬Ĭ��20֡"),MFCPROPERTYOOB);
	pGroup42->AddSubItem(pPropT62);
	pPropT63=new CMFCPropertyGridProperty(_T("֡����"),_T("20.0"),_T("���������룬��λ��s"),MFCPROPERTYOSB);
	pGroup42->AddSubItem(pPropT63);
	pPropT64 = new CMFCPropertyGridProperty(_T("Ƶ��ƫ��"),_T("+0.000000Hz"),_T("���������룬Ĭ��+0.000000Hz"),MFCPROPERTYOTB);
	pGroup42->AddSubItem(pPropT64);
	pPropT65 = new CMFCPropertyGridProperty(_T("��Թ���"),_T("+0.00dB"),_T("���������룬�ز�0Ĭ��0.00dB���������ز������÷�Χ+50dB~-10dB������0.01dB"),MFCPROPERTYOFB);
	pGroup42->AddSubItem(pPropT65);

	pPropT66 = new CMFCPropertyGridProperty(_T("����ģʽ"),_T("DSSS"),_T("802.11bЭ���в���DSSS����ģʽ"));
	pPropT66->Enable(FALSE);
	pGroup43->AddSubItem(pPropT66);
	pPropT67 = new CMFCPropertyGridProperty(_T("��������"),_T("1 Mbps"),_T("������ѡ 1Mbps��2Mbps��5.5Mbps��11Mbps"),MFCPROPERTYOFIB);
	pPropT67->AddOption(_T("1 Mbps"));  
	pPropT67->AddOption(_T("2 Mbps"));
	pPropT67->AddOption(_T("5.5 Mbps"));  
	pPropT67->AddOption(_T("11 Mbps"));
	pGroup43->AddSubItem(pPropT67);
	pPropT68 = new CMFCPropertyGridProperty(_T("���Ʒ�ʽ"),_T("DBPSK"),_T("DBPSK����������Ϊ1Mbps��DQPSK����������Ϊ2Mbps��CCK/PBCC����������Ϊ5.5Mbps��11Mbps"),MFCPROPERTYOSIB);
	pPropT68->AddOption(_T("CCK"));  
	pPropT68->AddOption(_T("PBCC"));
	pPropT68->Enable(FALSE);
	pGroup43->AddSubItem(pPropT68);
	pPropT69 = new CMFCPropertyGridProperty(_T("����"),_T("On"),_T("������ѡOn/Off/��ͷ����"),MFCPROPERTYOSEB);
	pPropT69->AddOption(_T("On"));  
	pPropT69->AddOption(_T("Off"));
	pPropT69->AddOption(_T("��ͷ����"));
	pGroup43->AddSubItem(pPropT69);
	//pPropT690 = new CMFCPropertyGridProperty(_T("�����ʼֵ"),_T("93"),_T("ȡֵ0-127��Ĭ��93.��ֵ���û�����"),MFCPROPERTYOSENL690);  
	//pGroup43->AddSubItem(pPropT690);
	pPropT70 = new CMFCPropertyGridProperty(_T("ǰ��������"),_T("��"),_T("Ĭ�ϣ�����Long������������Ϊ1Mbps��������ѡ: ��/�̣�Long/Short����������Ϊ2/5.5/11Mbps(DSSS)��"),MFCPROPERTYOEIB);
	pPropT70->AddOption(_T("��"));  
	pPropT70->AddOption(_T("��"));
	pPropT70->Enable(FALSE);
	pGroup43->AddSubItem(pPropT70);

	p_data_source_b = new CMFCPropertyGridProperty("����Դ","PN9","ѡ������Դ������",BDATASOURCE);
	p_data_source_b->AddOption("PN9");
	p_data_source_b->AddOption("PN15");
	p_data_source_b->AddOption("ALL0");
	p_data_source_b->AddOption("���ļ���ȡ");
	p_data_source_b->AllowEdit(FALSE);
	pGroup44->AddSubItem(p_data_source_b);

	p_data_filepath_b = new CMFCPropertyGridProperty("�ļ�·��","","ѡ������Դ�ļ����ڵ�·��",BFILEPATH);
	p_data_filepath_b->Show(FALSE);
	pGroup44->AddSubItem(p_data_filepath_b);

	pPropT72 = new CMFCPropertyGridProperty("���س���","80","���ø��صĳ��ȣ���λΪByte��",MFCPROPERTYONIB);
	pGroup44->AddSubItem(pPropT72);
	pPropT73 = new CMFCPropertyGridProperty(_T("MACͷ��"),_T("30 Bytes"),_T("Ĭ��ֵ"));
	pPropT59->Enable(FALSE);
	pGroup44->AddSubItem(pPropT73);
	pPropT74 = new CMFCPropertyGridProperty(_T("MAC FCS"),_T("4 Bytes"),_T("Ĭ��ֵ"));
	pPropT74->Enable(FALSE);
	pGroup44->AddSubItem(pPropT74);

	fitertype = new CMFCPropertyGridProperty(_T("�˲���"),_T("��"),_T("�����˲���������"),BMFCPROPERTYTFO);
	fitertype->AddOption("��");  
	fitertype->AddOption("��˹�˲���");
	fitertype->AddOption("���������˲���");
	fitertype->AddOption("�����ͨ�˲���");
	fitertype->AddOption("�û��Զ���");
	pGroup46->AddSubItem(fitertype);
	lp_filter_len_b = new CMFCPropertyGridProperty("�˲�������","30","���õ�ͨ�˲�������",BLPFILTERLEN);
	lp_filter_len_b->Show(FALSE);
	pGroup46->AddSubItem(lp_filter_len_b);
	lp_filter_wn_b = new CMFCPropertyGridProperty("�˲���ͨ��","0.24","�����˲���ͨ�� Wn",BLPFILTERWN);
	lp_filter_wn_b->Show(FALSE);
	pGroup46->AddSubItem(lp_filter_wn_b);

	gauss_filter_len_b = new CMFCPropertyGridProperty("�˲�������","30","���õ�ͨ�˲�������",BGAUSSFILTERLEN);
	gauss_filter_len_b->Show(FALSE);
	pGroup46->AddSubItem(gauss_filter_len_b);
	gauss_filter_BT_b = new CMFCPropertyGridProperty("BT","0.5","�����˲���ͨ�� BT",BGAUSSFILTERBT);
	gauss_filter_BT_b->Show(FALSE);
	pGroup46->AddSubItem(gauss_filter_BT_b);

	cosine_filter_len_b = new CMFCPropertyGridProperty("�˲�������","30","���õ�ͨ�˲�������",BCOSINEFILTERLEN);
	cosine_filter_len_b->Show(FALSE);
	pGroup46->AddSubItem(cosine_filter_len_b);
	cosine_filter_alpha_b = new CMFCPropertyGridProperty("alpha","0.24","�����˲���alpha",BCOSINEFILTERALPHA);
	cosine_filter_alpha_b->Show(FALSE);
	pGroup46->AddSubItem(cosine_filter_alpha_b);
	filter_user_b = new CMFCPropertyGridPropertyButton("�˲���ϵ��","","�����û��Զ����˲���ϵ��",BFILTERUSERDEFINE);
	filter_user_b->Show(FALSE);
	pGroup46->AddSubItem(filter_user_b);
	pPropT15 = new CMFCPropertyGridProperty(_T("���ڳ���"),_T("8"),_T("�����˲������ڵĳ��ȣ����ڳ��Ȳ��ܳ���һ��OFDM���ŵĳ���"),MFCPROPERTYTFS);
	pGroup46->AddSubItem(pPropT15);
	pPropT16_b = new CMFCPropertyGridProperty(_T("�ŵ�״̬"),_T("off"),_T("�����ŵ�״̬���ź��Ƿ񾭹��ŵ�"),BPPROPCHANNEL4);
	pPropT16_b->AddOption("on");
	pPropT16_b->AddOption("off");
	pGroup45->AddSubItem(pPropT16_b);

	pPropT17_b = new CMFCPropertyGridProperty(_T("�ŵ��ྶ��"),_T("1"),_T("�ŵ�����1"),BPPROPCHANNEL1);
	pPropT17_b->Enable(FALSE);
	pPropT17_b->SetValue("1");
	//m_configBIndex->NumOfTaps = 1 ;
	pGroup45->AddSubItem(pPropT17_b);

	pPropT18_b = new CMFCPropertyGridProperty(_T("�ź���Ƶ"),_T("2.412"),_T("�ŵ���Ƶ���ã���λ GHz"),BPPROPCHANNEL2);
	pGroup45->AddSubItem(pPropT18_b);

	pPropT19_b = new CMFCPropertyGridProperty(_T("�ƶ��ٶ�"),_T("30"),_T("�ƶ��ٶ����ã���λ km/h"),BPPROPCHANNEL3);
	pGroup45->AddSubItem(pPropT19_b);
	m_MFCPropertyGridThreeB.AddProperty(pGroup42);
	m_MFCPropertyGridThreeB.AddProperty(pGroup43);
	m_MFCPropertyGridThreeB.AddProperty(pGroup44);
	m_MFCPropertyGridThreeB.AddProperty(pGroup46);
	m_MFCPropertyGridThreeB.AddProperty(pGroup45);

	m_MFCPropertyGridThreeB.EnableDescriptionArea(TRUE);
	m_MFCPropertyGridThreeB.SetDescriptionRows(5);
	m_MFCPropertyGridThreeB.SetCustomColors(RGB(250,250,250),RGB(0,0,0),RGB(230,230,230),RGB(100,100,100),RGB(230,230,230),RGB(0,0,0),RGB(220,220,220));
	m_MFCPropertyGridThreeB.ShowWindow(FALSE);



	//11gЭ��
	m_MFCPropertyGridThreeG.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP /*| WS_BORDER*/,rc,this,2007);
	m_MFCPropertyGridThreeG.EnableHeaderCtrl(FALSE,_T("����"),_T("ֵ"));
	m_MFCPropertyGridThreeG.EnableDescriptionArea();
	m_MFCPropertyGridThreeG.SetVSDotNetLook();
	m_MFCPropertyGridThreeG.MarkModifiedProperties();
	m_MFCPropertyGridThreeG.SetAlphabeticMode(false); 
	m_MFCPropertyGridThreeG.SetShowDragContext();

	pGroup51 = new CMFCPropertyGridProperty(_T("�ز�����"));
	pGroup52 = new CMFCPropertyGridProperty(_T("���Ʊ���"));
	pGroup53 = new CMFCPropertyGridProperty(_T("�غ�����"));
	pGroup55 = new CMFCPropertyGridProperty("Ƶ�׿���");
	pGroup54 = new CMFCPropertyGridProperty(_T("�ŵ�"));


	pPropT75 = new CMFCPropertyGridProperty(_T("Э��"),_T("IEEE 802.11g"),_T("IEEE 802.11ϵ��֮һ��11a/b/g/n"));
	pPropT75->Enable(FALSE);
	pGroup51->AddSubItem(pPropT75);
	pPropT76=new CMFCPropertyGridProperty(_T("֡��"),_T("20"),_T("���������룬Ĭ��20֡"),MFCPROPERTYOOG);
	pGroup51->AddSubItem(pPropT76);
	pPropT77=new CMFCPropertyGridProperty(_T("֡����"),_T("10.0"),_T("���������룬��λ��s"),MFCPROPERTYOSG);
	pGroup51->AddSubItem(pPropT77);
	pPropT78 = new CMFCPropertyGridProperty(_T("Ƶ��ƫ��"),_T("+0.000000Hz"),_T("���������룬Ĭ��+0.000000Hz"),MFCPROPERTYOTG);
	pGroup51->AddSubItem(pPropT78);
	pPropT79 = new CMFCPropertyGridProperty(_T("��Թ���"),_T("+0.00dB"),_T("���������룬�ز�0Ĭ��0.00dB���������ز������÷�Χ+50dB~-10dB������0.01dB"),MFCPROPERTYOFG);
	pGroup51->AddSubItem(pPropT79);

	pPropT81 = new CMFCPropertyGridProperty(_T("��������"),_T("6 Mbps(OFDM)"),_T("������������֮һ��6��9��12��18��24��36��48��54��1��2��5.5��11��22��33Mbps"),MFCPROPERTYOFIG);	
	pPropT81->AddOption(_T("6 Mbps(OFDM)"));  
	pPropT81->AddOption(_T("9 Mbps(OFDM)"));
	pPropT81->AddOption(_T("12 Mbps(OFDM)"));  
	pPropT81->AddOption(_T("18 Mbps(OFDM)"));
	pPropT81->AddOption(_T("24 Mbps(OFDM)"));
	pPropT81->AddOption(_T("36 Mbps(OFDM)"));
	pPropT81->AddOption(_T("48 Mbps(OFDM)"));
	pPropT81->AddOption(_T("54 Mbps(OFDM)"));
	pPropT81->AddOption(_T("1 Mbps(DSSS)"));  
	pPropT81->AddOption(_T("2 Mbps(DSSS)"));
	pPropT81->AddOption(_T("5.5 Mbps(DSSS)"));  
	pPropT81->AddOption(_T("11 Mbps(DSSS)"));
	pPropT81->AddOption(_T("22 Mbps(DSSS)"));
	pPropT81->AddOption(_T("33 Mbps(DSSS)"));
	pGroup52->AddSubItem(pPropT81);

	/*CMFCPropertyGridProperty **/pPropT89 = new CMFCPropertyGridProperty(_T("���뷽ʽ"),_T("�������"),_T("���ڱ��뷽ʽ��˵��"),MFCPROPERTYTSTG);
	pPropT89->Enable(FALSE);
	pGroup52->AddSubItem(pPropT89);
	/*CMFCPropertyGridProperty **/pPropT90 = new CMFCPropertyGridProperty(_T("����"),_T("1/2"),_T("��ǰ�����µı�������"),MFCPROPERTYTSFRG);
	pPropT90->Enable(FALSE);
	pGroup52->AddSubItem(pPropT90);
	/*CMFCPropertyGridProperty **/pPropT95 = new CMFCPropertyGridProperty(_T("���Ʒ�ʽ"),_T("BPSK"),_T("��ǰ�����µĵ��Ʒ�ʽ"),MFCPROPERTYTSSDG);
	pPropT95->Enable(FALSE);
	//pPropT95->SetData(100);
	pGroup52->AddSubItem(pPropT95);
	/*CMFCPropertyGridProperty**/ pPropT91 = new CMFCPropertyGridProperty(_T("��֯"),_T("On"),_T("���ý�֯��״̬��On/Off"),MFCPROPERTYTSFEG);
	pPropT91->AddOption(_T("On"));  
	pPropT91->AddOption(_T("Off")); 
	pPropT91->AllowEdit(FALSE);
	pGroup52->AddSubItem(pPropT91);
	/*CMFCPropertyGridProperty**/pPropT83 = new CMFCPropertyGridProperty(_T("DSSS������"),_T("On"),_T("������ѡOn/Off/��ͷ����"),MFCPROPERTYOSEG);
	pPropT83->AddOption(_T("On"));  
	pPropT83->AddOption(_T("Off"));
	pPropT83->AddOption(_T("��ͷ����"));
	pPropT83->Show(FALSE);
	pGroup52->AddSubItem(pPropT83);
	/*CMFCPropertyGridProperty**/ pPropT92 = new CMFCPropertyGridProperty(_T("OFDM������"),_T("On"),_T("����OFDM��������״̬��On/Off"),MFCPROPERTYTSSXG);
	pPropT92->AddOption(_T("On"));  
	pPropT92->AddOption(_T("Off")); 
	pPropT92->AllowEdit(FALSE);
	pGroup52->AddSubItem(pPropT92);
	/*CMFCPropertyGridProperty**/pPropT93 = new CMFCPropertyGridProperty(_T("OFDM��������ʼֵ"),_T("93"),_T("������������ֵ"),MFCPROPERTYTSSEG);
	pGroup52->AddSubItem(pPropT93);
    /*CMFCPropertyGridProperty**/pPropT96 =new CMFCPropertyGridProperty(_T("���ز���"),_T("52"),_T("�������ز�����"),MFCPROPERTYTSETG);
	pGroup52->AddSubItem(pPropT96);
	pPropT96->Enable(FALSE);
	/*CMFCPropertyGridProperty**/pPropT94 = new CMFCPropertyGridProperty(_T("ǰ��������"),_T("OFDM"),_T("Ĭ�ϣ�OFDM������������Ϊ6/9/12/18/24/36/48/54Mbps��������ѡOFDM/��/�̣�����������Ϊ2/5.5/11/22/33Mbps��������ѡ��/��"),MFCPROPERTYOEIG);
	//pPropT94->AddOption(_T("OFDM"));
	//pPropT94->AddOption(_T("��"));  
	//pPropT94->AddOption(_T("��"));
	pGroup52->AddSubItem(pPropT94);

	p_data_source_g = new CMFCPropertyGridProperty("����Դ","PN9","ѡ������Դ������",GDATASOURCE);
	p_data_source_g->AddOption("PN9");
	p_data_source_g->AddOption("PN15");
	p_data_source_g->AddOption("ALL0");
	p_data_source_g->AddOption("���ļ���ȡ");
	p_data_source_g->AllowEdit(FALSE);
	pGroup53->AddSubItem(p_data_source_g);

	p_data_filepath_g = new CMFCPropertyGridProperty("�ļ�·��","","ѡ������Դ�ļ����ڵ�·��",GFILEPATH);
	p_data_filepath_g->Show(FALSE);
	pGroup53->AddSubItem(p_data_filepath_g);

	pPropT86 = new CMFCPropertyGridProperty("���س���","80","���ø��صĳ��ȣ���λΪByte��",MFCPROPERTYONIG);
	pGroup53->AddSubItem(pPropT86);
	pPropT87 = new CMFCPropertyGridProperty(_T("MACͷ��"),_T("30 Bytes"),_T("Ĭ��ֵ"));
	pPropT59->Enable(FALSE);
	pGroup53->AddSubItem(pPropT87);
	pPropT88 = new CMFCPropertyGridProperty(_T("MAC FCS"),_T("4 Bytes"),_T("Ĭ��ֵ"));
	pPropT88->Enable(FALSE);
	pGroup53->AddSubItem(pPropT88);

	fitertype_g = new CMFCPropertyGridProperty(_T("�˲���"),_T("��"),_T("�����˲���������"),GMFCPROPERTYTFO);
	fitertype_g->AddOption("��");  
	fitertype_g->AddOption("��˹�˲���");
	fitertype_g->AddOption("���������˲���");
	fitertype_g->AddOption("�����ͨ�˲���");
	fitertype_g->AddOption("�û��Զ���");
	pGroup55->AddSubItem(fitertype_g);
	lp_filter_len_g = new CMFCPropertyGridProperty("�˲�������","30","���õ�ͨ�˲�������",GLPFILTERLEN);
	lp_filter_len_g->Show(FALSE);
	pGroup55->AddSubItem(lp_filter_len_g);
	lp_filter_wn_g = new CMFCPropertyGridProperty("�˲���ͨ��","0.24","�����˲���ͨ�� Wn",GLPFILTERWN);
	lp_filter_wn_g->Show(FALSE);
	pGroup55->AddSubItem(lp_filter_wn_g);

	gauss_filter_len_g = new CMFCPropertyGridProperty("�˲�������","30","���õ�ͨ�˲�������",GGAUSSFILTERLEN);
	gauss_filter_len_g->Show(FALSE);
	pGroup55->AddSubItem(gauss_filter_len_g);
	gauss_filter_BT_g = new CMFCPropertyGridProperty("BT","0.5","�����˲���ͨ�� BT",GGAUSSFILTERBT);
	gauss_filter_BT_g->Show(FALSE);
	pGroup55->AddSubItem(gauss_filter_BT_g);

	cosine_filter_len_g = new CMFCPropertyGridProperty("�˲�������","30","���õ�ͨ�˲�������",GCOSINEFILTERLEN);
	cosine_filter_len_g->Show(FALSE);
	pGroup55->AddSubItem(cosine_filter_len_g);
	cosine_filter_alpha_g = new CMFCPropertyGridProperty("alpha","0.24","�����˲���alpha",GCOSINEFILTERALPHA);
	cosine_filter_alpha_g->Show(FALSE);
	pGroup55->AddSubItem(cosine_filter_alpha_g);
	filter_user_g = new CMFCPropertyGridPropertyButton("�˲���ϵ��","","�����û��Զ����˲���ϵ��",GFILTERUSERDEFINE);
	filter_user_g->Show(FALSE);
	pGroup55->AddSubItem(filter_user_g);
	pPropT15 = new CMFCPropertyGridProperty(_T("���ڳ���"),_T("8"),_T("�����˲������ڵĳ��ȣ����ڳ��Ȳ��ܳ���һ��OFDM���ŵĳ���"),MFCPROPERTYTFS);
	pGroup55->AddSubItem(pPropT15);
	pPropT16_g = new CMFCPropertyGridProperty(_T("�ŵ�״̬"),_T("off"),_T("�����ŵ�״̬���ź��Ƿ񾭹��ŵ�"),GPPROPCHANNEL4);
	pPropT16_g->AddOption("on");
	pPropT16_g->AddOption("off");
	pGroup54->AddSubItem(pPropT16_g);

	pPropT17_g = new CMFCPropertyGridProperty(_T("�ŵ��ྶ��"),_T("4"),_T("���öྶ�ŵ��жྶ��"),GPPROPCHANNEL1);
	pGroup54->AddSubItem(pPropT17_g);

	pPropT18_g = new CMFCPropertyGridProperty(_T("�ź���Ƶ"),_T("2.412"),_T("�ŵ���Ƶ���ã���λ GHz"),GPPROPCHANNEL2);
	pGroup54->AddSubItem(pPropT18_g);

	pPropT19_g = new CMFCPropertyGridProperty(_T("�ƶ��ٶ�"),_T("30"),_T("�ƶ��ٶ����ã���λ km/h"),GPPROPCHANNEL3);
	pGroup54->AddSubItem(pPropT19_g);
	m_MFCPropertyGridThreeG.AddProperty(pGroup51);
	m_MFCPropertyGridThreeG.AddProperty(pGroup52);
	m_MFCPropertyGridThreeG.AddProperty(pGroup53);
	m_MFCPropertyGridThreeG.AddProperty(pGroup55);
	m_MFCPropertyGridThreeG.AddProperty(pGroup54);

	m_MFCPropertyGridThreeG.EnableDescriptionArea(TRUE);
	m_MFCPropertyGridThreeG.SetDescriptionRows(5);
	m_MFCPropertyGridThreeG.SetCustomColors(RGB(250,250,250),RGB(0,0,0),RGB(230,230,230),RGB(100,100,100),RGB(230,230,230),RGB(0,0,0),RGB(220,220,220));
	m_MFCPropertyGridThreeG.ShowWindow(FALSE);

	CWnd *pWnd = GetTopWindow();  
	while (NULL != pWnd)  
	{  
		pWnd->SetFont(&m_font);  
		pWnd = pWnd->GetNextWindow();  
	}  
	
	//MPDU����
	m_MpduInfoList.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);//List�ķ��
	m_MpduInfoList.DeleteAllItems();
	m_MpduInfoList.InsertColumn(0,_T("Mpdus"),LVCFMT_LEFT,65);
	m_MpduInfoList.InsertColumn(1,_T("��������"),LVCFMT_CENTER,84);
	m_MpduInfoList.InsertColumn(2,_T("����Դ����(bytes)"),LVCFMT_CENTER,110);
	m_MpduInfoList.InsertColumn(3,_T("MAC Header"),LVCFMT_CENTER,105);
	m_MpduInfoList.InsertColumn(4,_T("MAC FCS"),LVCFMT_CENTER,90);
	m_MpduInfoList.InsertColumn(5,_T("MPDU ����"),LVCFMT_CENTER,90);
	m_MpduInfoList.InsertColumn(6,"A-MPDU��֡����",LVCFMT_CENTER,135);
	m_MpduInfoList.InsertItem(0,_T("Mpdu 0"));
	m_MpduInfoList.SetItemText(0,1,_T("PN9"));
	m_MpduInfoList.SetItemText(0,2,"1024Byte(s)");
	m_MpduInfoList.SetItemText(0,3,"On");
	m_MpduInfoList.SetItemText(0,4,_T("On"));
	m_MpduInfoList.SetItemText(0,5,_T("1058Byte(s)"));//�����
	m_MpduInfoList.SetItemText(0,6,"1062Byte(s)");
	m_MpduInfoList.ShowWindow(FALSE);

	m_MPDUAdd.EnableWindow(FALSE);
	m_MPDUDelete.EnableWindow(FALSE);
	Point();
	update();
	m_finished_ini = TRUE;
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CTabProtocolConfig::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	// TODO: �ڴ˴������Ϣ����������
	if (IsWindowVisible() || m_finished_ini)
	{
		m_MFCPropertyGridThree.MoveWindow(10,10,cx-32,cy-65);
		m_MFCPropertyGridThreeB.MoveWindow(10,10,cx-32,cy-65);
		m_MFCPropertyGridThreeG.MoveWindow(10,10,cx-32,cy-65);
		m_MFCPropertyGridThreeNL.MoveWindow(10,10,cx-32,cy-65);
		
		if (m_configIndex->ProtocolModel==OneN){
			
				m_MpduInfoList.MoveWindow(10,25,cx-32,cy/4.0);
				m_MFCPropertyGridThreeN.MoveWindow(10,27+cy/4.0,cx-32,cy-25-cy/4.0);

		}
    }
}

LRESULT CTabProtocolConfig::OnPropertyChanged(__in WPARAM wparam,__in LPARAM lparam)
{
	CMFCPropertyGridProperty* pProp = (CMFCPropertyGridProperty*)lparam; 
	data_and_graph* m_data_and_graph =&(((CMainFrame*)AfxGetMainWnd())->m_pass_to_thread);
	CTabCarrier &m_carrier=((CTabParent*)(((CMainFrame*)AfxGetMainWnd())->m_mainSplitter.GetPane(0,0)))->m_tabCarrier;
	
	COleVariant t = pProp->GetValue(); //�ı�֮���ֵ
	CString d;
	d = t.bstrVal;      //��COleVariant��CString 

	switch(wparam)
	{
	case MFCPROPERTYGRIDTHREE://11a
		switch(pProp->GetData())
		{
		case MFCPROPERTYTOS://֡��
			{
				int num_of_frame =atoi(d);
				if (num_of_frame<1)
				{
					num_of_frame=1;
					pPropT2->SetValue("1");
				}
				if (num_of_frame>2000)
				{
					num_of_frame=2000;
					pPropT2->SetValue("2000");
				}

				m_data_and_graph->m_configAIndex->num_of_frame=num_of_frame;
			}
			break;
		case MFCPROPERTYTOT://֡����,4��s��Ӧ80������
			{
				double num_of_zeros =atof(d);
				if (num_of_zeros<=0)
				{
					num_of_zeros=0;
					pPropT3a->SetValue("0");
				}
				if (num_of_zeros>100000)
				{
					num_of_zeros=100000;
					pPropT3a->SetValue("100000");
				}
				int x=(int)floor(num_of_zeros*20);
				m_data_and_graph->m_configAIndex->num_of_zeros=x;
			}
			break;
		case MFCPROPERTYTOFR:
			{
				float FrequencyOffset=atof(d);
				if(FrequencyOffset > 58000)
				{
					SetFocus()->MessageBox("��ǰ���������Ƶ��ƫ��Ϊ+/-58MHz");
					pPropT3->SetValue("58000");
					//pPropZ6_d->SetValue("58000");
					m_data_and_graph->m_configAIndex->FrequencyOffset = 58000*1000;
					//m_data_and_graph->m_configAIndex->FrequencyOffset = 58000*1000;
				}
				else if(FrequencyOffset < -58000)
				{
					SetFocus()->MessageBox("��ǰ���������Ƶ��ƫ��Ϊ+/-58MHz");
					pPropT3->SetValue("-58000");
					//pPropZ6_d->SetValue("-58000");
					m_data_and_graph->m_configAIndex->FrequencyOffset = -58000*1000;
					//Protocol_para_d->para.FrequencyOffset = -58000*1000;
				}

				else{
					m_data_and_graph->m_configAIndex->FrequencyOffset = FrequencyOffset*1000;
					//Protocol_para_d->para.FrequencyOffset = FrequencyOffset*1000;
				}
			}
			break;
		case MFCPROPERTYTSO:
			if (d ==_T("6 Mbps"))
			{

				m_configAIndex->EZOA_Encoding = BPSK_1_2;
				m_configIndex->EZOA_Encoding = BPSK_1_2;
				m_configAIndex->DataRate =6;
				pPropT5->SetValue((COleVariant)_T("BPSK"));
				pPropT7->SetValue((COleVariant)_T("1/2"));
				/*pPropT10->SetValue((COleVariant)_T("2980 symbols"));
				pPropT11->SetValue((COleVariant)_T("3201 symbols"));*/

			}
			else if (d == _T("9 Mbps"))
			{

				m_configAIndex->EZOA_Encoding = BPSK_3_4;
				m_configIndex->EZOA_Encoding = BPSK_3_4;
				m_configAIndex->DataRate =9;

				pPropT5->SetValue((COleVariant)_T("BPSK"));
				pPropT7->SetValue((COleVariant)_T("3/4"));
				/*pPropT10->SetValue((COleVariant)_T("2000 symbols"));
				pPropT11->SetValue((COleVariant)_T("2241 symbols"));*/
			}
			else if (d == _T("12 Mbps"))
			{

				m_configAIndex->EZOA_Encoding = QPSK_1_2;
				m_configIndex->EZOA_Encoding = QPSK_1_2;
				m_configAIndex->DataRate =12;

				pPropT5->SetValue((COleVariant)_T("QPSK"));
				pPropT7->SetValue((COleVariant)_T("1/2"));
				/*pPropT10->SetValue((COleVariant)_T("1600 symbols"));
				pPropT11->SetValue((COleVariant)_T("1841 symbols"));*/
			}
			else if (d == _T("18 Mbps"))
			{

				m_configAIndex->EZOA_Encoding = QPSK_3_4;
				m_configIndex->EZOA_Encoding = QPSK_3_4;
				m_configAIndex->DataRate =18;

				pPropT5->SetValue((COleVariant)_T("QPSK"));
				pPropT7->SetValue((COleVariant)_T("3/4"));
				/*pPropT10->SetValue((COleVariant)_T("1600 symbols"));
				pPropT11->SetValue((COleVariant)_T("1841 symbols"));*/
			}
			else if (d == _T("24 Mbps"))
			{

				m_configAIndex->EZOA_Encoding =QAM16_1_2;
				m_configIndex->EZOA_Encoding =QAM16_1_2;
				m_configAIndex->DataRate =24;

				pPropT5->SetValue((COleVariant)_T("16-QAM"));
				pPropT7->SetValue((COleVariant)_T("1/2"));
				/*pPropT10->SetValue((COleVariant)_T("1600 symbols"));
				pPropT11->SetValue((COleVariant)_T("1841 symbols"));*/
			}
			else if (d == _T("36 Mbps"))
			{

				m_configAIndex->EZOA_Encoding = QAM16_3_4;
				m_configIndex->EZOA_Encoding = QAM16_3_4;
				m_configAIndex->DataRate =36;

				pPropT5->SetValue((COleVariant)_T("16-QAM"));
				pPropT7->SetValue((COleVariant)_T("3/4"));
				/*pPropT10->SetValue((COleVariant)_T("1600 symbols"));
				pPropT11->SetValue((COleVariant)_T("1841 symbols"));*/
			}
			else if (d == _T("48 Mbps"))
			{

				m_configAIndex->EZOA_Encoding =QAM64_2_3;
				m_configIndex->EZOA_Encoding =QAM64_2_3;
				m_configAIndex->DataRate =48;

				pPropT5->SetValue((COleVariant)_T("64-QAM"));
				pPropT7->SetValue((COleVariant)_T("2/3"));
				/*pPropT10->SetValue((COleVariant)_T("1600 symbols"));
				pPropT11->SetValue((COleVariant)_T("1841 symbols"));*/
			}
			else if (d == _T("54 Mbps"))
			{

				m_configAIndex->EZOA_Encoding = QAM64_3_4;
				m_configIndex->EZOA_Encoding = QAM64_3_4;
				m_configAIndex->DataRate =54;

				pPropT5->SetValue((COleVariant)_T("64-QAM"));
				pPropT7->SetValue((COleVariant)_T("3/4"));
				/*pPropT10->SetValue((COleVariant)_T("1600 symbols"));
				pPropT11->SetValue((COleVariant)_T("1841 symbols"));*/
			}

			break;
		case MFCPROPERTYTSSX:
			{
				if (d==_T("On"))
				{
					pPropT9->SetValue((COleVariant)_T("On"));
					m_configAIndex->scrambler_state_OFDM=true;
				}
				else if (d==_T("Off"))
				{
					pPropT9->SetValue((COleVariant)_T("Off"));
					m_configAIndex->scrambler_state_OFDM=false;
				}
			}
			/*if (d == _T("On"))
			{
				//����ҲҪ���ѡ�m_configIndex->OFDMScramblerState = ON; ��һ��Ĳ�������
				pPropT17->Enable(TRUE);
			}
			else
				pPropT17->Enable(FALSE);*/
			break;
		case MFCPROPERTYTTFR:
			//if (d == _T("����"))
			//{
			//	if (m_macHeaderDlgIndex.DoModal() == IDOK)
			//	{
			//	}//ʾ������
			//	pPropT12->SetValue((COleVariant)m_macHeaderDlgIndex.str);
			//}
			break;
		case MFCPROPERTYTTO:
			{
				if (0 == d.Compare("PN9"))
				{
					//PN9����
					m_configAIndex->source_mode = 0;
					p_data_filepath->Show(FALSE);
				}else if (0 == d.Compare("PN15"))
				{
					//PN15����
					m_configAIndex->source_mode = 1;
					p_data_filepath->Show(FALSE);
				}else if (0 == d.Compare("ALL0"))
				{
					// ȫ0����
					m_configAIndex->source_mode = 2;
					p_data_filepath->Show(FALSE);
				}else {
					m_configAIndex->source_mode = 3;
					p_data_filepath->Show(TRUE);
				}
				break;
			}
		case MFCPROPERTYTTT:
			{
				d.Remove(' ');
				int temp_len;
				temp_len = atoi(d.GetBuffer());
				if (temp_len < 0)
					temp_len = 0;
				else if (temp_len > m_configAIndex->datainmaxlen)
					temp_len = m_configAIndex->datainmaxlen;
				m_configAIndex->source_length = temp_len;
				d.Format("%d",temp_len);
				pProp->SetValue((COleVariant)d);
				break;
			}
		case MFCPROPERTYTTS:
			{
				//char * temp_filename;
				d.Remove(' ');
				if (PathFileExists(d))
				{
					//delete[] m_configAIndex->filepath;
					//temp_filename = new char[d.GetLength() + 1];
					//strcpy(temp_filename,d.GetBuffer());
					m_configAIndex->filepath = d;
					pProp->SetValue((COleVariant)d);
				}else {
					MessageBox("�ļ������ڣ�");
					pProp->SetValue("");
				}
				break;
			}
		case MFCPROPERTYTSSE:
			{
				CString str = pPropT017->GetValue();
				int  scramSeed = atoi(str);
				if (scramSeed > 127){
					pPropT017->SetValue("127");
					scramSeed = 127 ;//�������ĳ�ʼֵ����0-127
				}
				if (scramSeed < 0){
					pPropT017->SetValue("0");
					scramSeed = 0 ;//�������ĳ�ʼֵ����0-127
				}
				if (scramSeed==0 && str!="0")
				{
					MessageBox("����Чֵ��","����"); 
					pPropT017->SetValue("93");
					scramSeed = 93 ;//�������ĳ�ʼֵ����0-127
				}
				m_data_and_graph->m_configAIndex->scramble_state_initial= scramSeed;
				break;
			}
		case PPROPCHANNEL4:
			{
				m_configAIndex->add_channel = d == "on" ? TRUE : FALSE;
				break;
			}
			
		case PPROPCHANNEL1:
			{
				double numoftaps = atof(d.GetBuffer());
				m_configAIndex->NumOfTaps = numoftaps ;
				break;
			}
		case PPROPCHANNEL2:
			{
				double carrierfreq = atof(d.GetBuffer());
				m_configAIndex->carrierfreq =carrierfreq * 1e9;
				break;
			}
		case PPROPCHANNEL3:
			{
				double mobilespeed = atof(d.GetBuffer());
				m_configAIndex->mobilespeed = mobilespeed;
				break;
			}
		case MFCPROPERTYTFO:
			{
				CString str = pProp->GetValue();
				if(str == "�û��Զ���")
				{
					lp_filter_len->Show(FALSE);
					lp_filter_wn->Show(FALSE);
					gauss_filter_BT->Show(FALSE);
					gauss_filter_len->Show(FALSE);
					cosine_filter_alpha->Show(FALSE);
					cosine_filter_len->Show(FALSE);
					filter_user->Show(TRUE);
					m_configAIndex->filter_para.filtertype =  userdefined;
				}
				if(str =="�����ͨ�˲���")
				{
					lp_filter_len->Show(TRUE);
					lp_filter_wn->Show(TRUE);
					gauss_filter_BT->Show(FALSE);
					gauss_filter_len->Show(FALSE);
					cosine_filter_alpha->Show(FALSE);
					cosine_filter_len->Show(FALSE);
					filter_user->Show(FALSE);
					m_configAIndex->filter_para.filtertype =  lpfilter;
				}
				if(str == "��˹�˲���")
				{
					lp_filter_len->Show(FALSE);
					lp_filter_wn->Show(FALSE);
					gauss_filter_BT->Show(TRUE);
					gauss_filter_len->Show(TRUE);
					cosine_filter_alpha->Show(FALSE);
					cosine_filter_len->Show(FALSE);
					filter_user->Show(FALSE);
					m_configAIndex->filter_para.filtertype =  gaussfilter;
				}
				if( str == "���������˲���")
				{
					lp_filter_len->Show(FALSE);
					lp_filter_wn->Show(FALSE);
					gauss_filter_BT->Show(FALSE);
					gauss_filter_len->Show(FALSE);
					cosine_filter_alpha->Show(TRUE);
					cosine_filter_len->Show(TRUE);
					filter_user->Show(FALSE);
					m_configAIndex->filter_para.filtertype =  cosfilter;
				}
				break;
			}
		case LPFILTERLEN:
			{
				CString str = pProp->GetValue();
				m_configAIndex->filter_para.lppara.length = atoi(str);
				break;
			}
		case LPFILTERWN:
			{
				CString str = pProp->GetValue();
				m_configAIndex->filter_para.lppara.wn = atof(str);
				break;
			}
		case GAUSSFILTERLEN:
			{
				CString str = pProp->GetValue();
				m_configAIndex->filter_para.gausspara.length = atoi(str);
				break;
			}
		case GAUSSFILTERBT:
			{
				CString str = pProp->GetValue();
				m_configAIndex->filter_para.gausspara.BT = atof(str);
				break;
			}
		case COSINEFILTERLEN:
			{
				CString str = pProp->GetValue();
				m_configAIndex->filter_para.cosinepara.length = atoi(str);
				break;
			}
		case COSINEFILTERALPHA:
			{
				CString str = pProp->GetValue();
				m_configAIndex->filter_para.cosinepara.alpha = atof(str);
				break;
			}
		default:
			break;
		}
		break;

	case MFCPROPERTYGRIDTHREEB: //11b
		switch(pProp->GetData())
		{
			//11b�ɲ�����Ӧ����ԴID���ڽ������ҵ���Ӧ����ԴID
		
		case MFCPROPERTYOOB://֡��
			{
				int num_of_frame =atoi(d);
				if (num_of_frame<1)
				{
					num_of_frame=1;
					pPropT62->SetValue("1");
				}
				if (num_of_frame>2000)
				{
					num_of_frame=2000;
					pPropT62->SetValue("2000");
				}
				m_data_and_graph->m_configBIndex->num_of_frame=num_of_frame;
			}
			break;
		case MFCPROPERTYOSB://֡����
			{
				double num_of_zeros =atof(d);
				if (num_of_zeros<=0)
				{
					num_of_zeros=0;
					pPropT63->SetValue("0");
				}
				if (num_of_zeros>100000)
				{
					num_of_zeros=100000;
					pPropT63->SetValue("100000");
				}
				int x=(int)floor(num_of_zeros*11);
				m_data_and_graph->m_configBIndex->num_of_zeros=x;
			}
			break;
		case MFCPROPERTYOTB:
			{
				float FrequencyOffset=atof(d);
				if(FrequencyOffset > 58000)
				{
					SetFocus()->MessageBox("��ǰ���������Ƶ��ƫ��Ϊ+/-58MHz");
					pPropT3->SetValue("58000");
					//pPropZ6_d->SetValue("58000");
					m_data_and_graph->m_configBIndex->FrequencyOffset = 58000*1000;
					//m_data_and_graph->m_configAIndex->FrequencyOffset = 58000*1000;
				}
				else if(FrequencyOffset < -58000)
				{
					SetFocus()->MessageBox("��ǰ���������Ƶ��ƫ��Ϊ+/-58MHz");
					pPropT3->SetValue("-58000");
					//pPropZ6_d->SetValue("-58000");
					m_data_and_graph->m_configBIndex->FrequencyOffset = -58000*1000;
					//Protocol_para_d->para.FrequencyOffset = -58000*1000;
				}

				else{
					m_data_and_graph->m_configBIndex->FrequencyOffset = FrequencyOffset*1000;
					//Protocol_para_d->para.FrequencyOffset = FrequencyOffset*1000;
				}
			}
			break;
		case MFCPROPERTYOFIB:
			if (d ==_T("1 Mbps"))
			{
				m_configBIndex->modulation_type = DBPSK_1Mbps;
				m_configBIndex->EZOB_Encoding = DBPSK_1M;
				pPropT68->SetValue((COleVariant)_T("DBPSK"));
				pPropT68->Enable(FALSE);
				pPropT70->SetValue((COleVariant)_T("��"));
				pPropT70->Enable(FALSE);
				m_configBIndex->preamble_type=longPreamble;
			}
			else if (d == _T("2 Mbps"))
			{

				m_configBIndex->modulation_type = DQPSK_2Mbps;
				m_configBIndex->EZOB_Encoding = DQPSK_2M;
				pPropT68->SetValue((COleVariant)_T("DQPSK"));
				pPropT68->Enable(FALSE);
				pPropT70->Enable(TRUE);
				//pPropT70->SetValue((COleVariant)_T("��"));

			}
			else if (d == _T("5.5 Mbps"))
			{
				m_configBIndex->data_rate = _55Mbps;
				m_configBIndex->modulation_type = CCK55_55Mbps;
				m_configBIndex->EZOB_Encoding = CCK_5_5M;
				pPropT68->SetValue((COleVariant)_T("CCK"));
				pPropT68->Enable(TRUE);
				pPropT70->Enable(TRUE);
			}
			else if (d == _T("11 Mbps"))
			{
				m_configBIndex->data_rate = _11Mbps;
				m_configBIndex->modulation_type = CCK11_11Mpbs;
				m_configBIndex->EZOB_Encoding = CCK_11M;
				pPropT68->SetValue((COleVariant)_T("CCK"));
				pPropT68->Enable(TRUE);
				pPropT70->Enable(TRUE);
			}

			break;
		case MFCPROPERTYOSIB://���Ʒ�ʽ��ֻ��5.5M ��11M����ʱ������ѡ��PBCC����CCK
			if(d==_T("PBCC"))
			{
				pPropT68->SetValue((COleVariant)_T("PBCC"));
				if (m_configBIndex->data_rate == _55Mbps)
				{
					m_configBIndex->EZOB_Encoding = PBCC_5_5M;
				} 
				else
				{
					m_configBIndex->EZOB_Encoding = PBCC_11M;
				}
				
			}
			else if(d==_T("CCK"))
			{
				pPropT68->SetValue((COleVariant)_T("CCK"));
				if (m_configBIndex->data_rate == _55Mbps)
				{
					m_configBIndex->EZOB_Encoding = CCK_5_5M;
				} 
				else
				{
					m_configBIndex->EZOB_Encoding = CCK_11M;
				}

			}
			break;
			/*
			else if(d==_T("CCK"))
			{
			pPropT95->SetValue((COleVariant)_T("CCK"));
			
			}
			}
			break;
			*/
		case MFCPROPERTYOEIB:
			if (d==_T("��"))
			{
				pPropT70->SetValue((COleVariant)_T("��"));
				m_configBIndex->preamble_type=longPreamble;

			}
			else if(d==_T("��"))
			{
				pPropT70->SetValue((COleVariant)_T("��"));
				m_configBIndex->preamble_type=shortPreamble;
			}
			break;
		case MFCPROPERTYOSEB:
			if (d==_T("On"))
			{
				pPropT69->SetValue((COleVariant)_T("On"));
				m_configBIndex->scrambler_state=ON;
			}
			else if (d==_T("Off"))
			{
				pPropT69->SetValue((COleVariant)_T("Off"));
				m_configBIndex->scrambler_state=OFF;
			}
			else if (d==_T("��ͷ����"))
			{
				pPropT69->SetValue((COleVariant)_T("��ͷ����"));
				m_configBIndex->scrambler_state=Preamble_only;
			}
			break;
		case MFCPROPERTYOSENL690:
			{
				CString str = pPropT690->GetValue();
				int  scramSeed = atoi(str);
				if (scramSeed > 127){
					pPropT690->SetValue("127");
					scramSeed = 127 ;//�������ĳ�ʼֵ����0-127
				}
				if (scramSeed < 0){
					pPropT690->SetValue("0");
					scramSeed = 0 ;//�������ĳ�ʼֵ����0-127
				}
				if (scramSeed==0 && str!="0")
				{
					MessageBox("����Чֵ��","����"); 
					pPropT690->SetValue("93");
					scramSeed = 93 ;//�������ĳ�ʼֵ����0-127
				}
				//m_data_and_graph->m_configBIndex->scramSeed = scramSeed;
				break;
			}
		case BDATASOURCE:
			{
				if (0 == d.Compare("PN9"))
				{
					//PN9����
					m_configBIndex->source_mode = 0;
					p_data_filepath_b->Show(FALSE);
				}else if (0 == d.Compare("PN15"))
				{
					//PN15����
					m_configBIndex->source_mode = 1;
					p_data_filepath_b->Show(FALSE);
				}else if (0 == d.Compare("ALL0"))
				{
					// ȫһ����
					m_configBIndex->source_mode = 2;
					p_data_filepath_b->Show(FALSE);
				}else {
					m_configBIndex->source_mode = 3;
					p_data_filepath_b->Show(TRUE);
				}
				break;
			}
		case MFCPROPERTYONIB:
			{
				d.Remove(' ');
				int temp_len;
				temp_len = atoi(d.GetBuffer());
				if (temp_len < 0)
					temp_len = 0;
				else if (temp_len > m_configBIndex->datainmaxlen)
					temp_len = m_configBIndex->datainmaxlen;
				m_configBIndex->source_length = temp_len;
				d.Format("%d",temp_len);
				pProp->SetValue((COleVariant)d);
				break;
			}
		case BFILEPATH:
			{
				char * temp_filename;
				d.Remove(' ');
				if (PathFileExists(d))
				{
					delete[] m_configBIndex->filepath;
					temp_filename = new char[d.GetLength() + 1];
					strcpy(temp_filename,d.GetBuffer());
					m_configBIndex->filepath = temp_filename;
					pProp->SetValue((COleVariant)d);
				}else {
					MessageBox("�ļ������ڣ�");
					pProp->SetValue("");
				}
				break;
			}
		case BPPROPCHANNEL4:
			{
				m_configBIndex->add_channel = d == "on" ? TRUE : FALSE;
				break;
			}

		case BPPROPCHANNEL1:
			{
				//double numoftaps = atof(d.GetBuffer());
				CString str = pPropT17_b->GetValue();
				int  numoftaps = atoi(str);
				if (numoftaps>20)
				{
					pPropT17_b->SetValue(20.0);
					numoftaps=20;
				}
				if (numoftaps<0)
				{
					pPropT17_b->SetValue(0.0);
					numoftaps=0;
				}
				if (numoftaps==0 && d.GetBuffer()!="0")
				{
					MessageBox("����Чֵ��","����");
					pPropT17_b->SetValue(0.0);
					numoftaps=0.0;
				}
				m_configBIndex->NumOfTaps = numoftaps ;

				break;
			}
		case BPPROPCHANNEL2:
			{
				double carrierfreq = atof(d.GetBuffer());
				m_configBIndex->carrierfreq =carrierfreq * 1e9;
				break;
			}
		case BPPROPCHANNEL3:
			{
				double mobilespeed = atof(d.GetBuffer());
				m_configBIndex->mobilespeed = mobilespeed;
				break;
			}
		case BMFCPROPERTYTFO:
			{
				CString str = pProp->GetValue();
				if(str == "�û��Զ���")
				{
					lp_filter_len_b->Show(FALSE);
					lp_filter_wn_b->Show(FALSE);
					gauss_filter_BT_b->Show(FALSE);
					gauss_filter_len_b->Show(FALSE);
					cosine_filter_alpha_b->Show(FALSE);
					cosine_filter_len_b->Show(FALSE);
					filter_user_b->Show(TRUE);
					m_configBIndex->filter_para.filtertype =  userdefined;
				}
				if(str =="�����ͨ�˲���")
				{
					lp_filter_len_b->Show(TRUE);
					lp_filter_wn_b->Show(TRUE);
					gauss_filter_BT_b->Show(FALSE);
					gauss_filter_len_b->Show(FALSE);
					cosine_filter_alpha_b->Show(FALSE);
					cosine_filter_len_b->Show(FALSE);
					filter_user_b->Show(FALSE);
					m_configBIndex->filter_para.filtertype =  lpfilter;
				}
				if(str == "��˹�˲���")
				{
					lp_filter_len_b->Show(FALSE);
					lp_filter_wn_b->Show(FALSE);
					gauss_filter_BT_b->Show(TRUE);
					gauss_filter_len_b->Show(TRUE);
					cosine_filter_alpha_b->Show(FALSE);
					cosine_filter_len_b->Show(FALSE);
					filter_user_b->Show(FALSE);
					m_configBIndex->filter_para.filtertype =  gaussfilter;
				}
				if( str == "���������˲���")
				{
					lp_filter_len_b->Show(FALSE);
					lp_filter_wn_b->Show(FALSE);
					gauss_filter_BT_b->Show(FALSE);
					gauss_filter_len_b->Show(FALSE);
					cosine_filter_alpha_b->Show(TRUE);
					cosine_filter_len_b->Show(TRUE);
					filter_user_b->Show(FALSE);
					m_configBIndex->filter_para.filtertype =  cosfilter;
				}
				break;
			}
		case BLPFILTERLEN:
			{
				CString str = pProp->GetValue();
				m_configBIndex->filter_para.lppara.length = atoi(str);
				break;
			}
		case BLPFILTERWN:
			{
				CString str = pProp->GetValue();
				m_configBIndex->filter_para.lppara.wn = atof(str);
				break;
			}
		case BGAUSSFILTERLEN:
			{
				CString str = pProp->GetValue();
				m_configBIndex->filter_para.gausspara.length = atoi(str);
				break;
			}
		case BGAUSSFILTERBT:
			{
				CString str = pProp->GetValue();
				m_configBIndex->filter_para.gausspara.BT = atof(str);
				break;
			}
		case BCOSINEFILTERLEN:
			{
				CString str = pProp->GetValue();
				m_configBIndex->filter_para.cosinepara.length = atoi(str);
				break;
			}
		case BCOSINEFILTERALPHA:
			{
				CString str = pProp->GetValue();
				m_configBIndex->filter_para.cosinepara.alpha = atof(str);
				break;
			}
		default:
			break;
		}
		break;
	case MFCPROPERTYGRIDTHREEG: //11g
		switch(pProp->GetData())
		{
		case MFCPROPERTYOOG://֡��
			{

				int num_of_frame =atoi(d);
				if (num_of_frame<1)
				{
					num_of_frame=1;
					pPropT76->SetValue("1");
				}
				if (num_of_frame>2000)
				{
					num_of_frame=2000;
					pPropT76->SetValue("2000");
				}

				m_data_and_graph->m_configGIndex->num_of_frame=num_of_frame;

			}
			break;
		case MFCPROPERTYOSG://֡����
			{
				double num_of_zeros =atof(d);
				if (num_of_zeros<=0)
				{
					num_of_zeros=0;
					pPropT77->SetValue("0");
				}
				if (num_of_zeros>100000)
				{
					num_of_zeros=100000;
					pPropT77->SetValue("100000");
				}
				int x=(int)floor(num_of_zeros*20);
				m_data_and_graph->m_configGIndex->num_of_zeros=x;
			}
			break;
		case MFCPROPERTYOTG:
			{
				float FrequencyOffset=atof(d);
				if(FrequencyOffset > 58000)
				{
					SetFocus()->MessageBox("��ǰ���������Ƶ��ƫ��Ϊ+/-58MHz");
					pPropT3->SetValue("58000");
					//pPropZ6_d->SetValue("58000");
					m_data_and_graph->m_configGIndex->FrequencyOffset = 58000*1000;
					//m_data_and_graph->m_configAIndex->FrequencyOffset = 58000*1000;
				}
				else if(FrequencyOffset < -58000)
				{
					SetFocus()->MessageBox("��ǰ���������Ƶ��ƫ��Ϊ+/-58MHz");
					pPropT3->SetValue("-58000");
					//pPropZ6_d->SetValue("-58000");
					m_data_and_graph->m_configGIndex->FrequencyOffset = -58000*1000;
					//Protocol_para_d->para.FrequencyOffset = -58000*1000;
				}

				else{
					m_data_and_graph->m_configGIndex->FrequencyOffset = FrequencyOffset*1000;
					//Protocol_para_d->para.FrequencyOffset = FrequencyOffset*1000;
				}
			}
			break;
		case MFCPROPERTYOFIG:
			if (d ==_T("6 Mbps(OFDM)")||d == _T("9 Mbps(OFDM)")||d == _T("12 Mbps(OFDM)")||d == _T("18 Mbps(OFDM)")||d == _T("24 Mbps(OFDM)")||d == _T("36 Mbps(OFDM)")||d == _T("48 Mbps(OFDM)")||d == _T("54 Mbps(OFDM)"))
			{				
				pPropT89->Show(TRUE);//���뷽ʽ
				pPropT90->Show(TRUE);//����
				pPropT91->Show(TRUE);//��֯
				pPropT92->Show(TRUE);//OFDM������
				pPropT93->Show(TRUE);//OFDM��������ʼֵ
				pPropT96->Show(TRUE);//OFDM���ز���
				pPropT83->Show(FALSE);//DSSS Scrambler
				//pPropT94->AddOption(_T("OFDM"));
				pPropT94->SetValue((COleVariant)_T("OFDM"));
				pPropT94->Enable(TRUE);
				pPropT17_g->Enable(TRUE);
				pPropT17_g->SetValue("4");
				m_configGIndex->NumOfTaps = 4 ;

				if (d ==_T("6 Mbps(OFDM)"))
				{
					pPropT94->AddOption(_T("��"));  
					pPropT94->AddOption(_T("��"));
					pPropT94->AddOption(_T("OFDM"));
					m_configGIndex->EZOG_Encoding = BPSK_1_2;
					m_configGIndex->data_rate =  _6Mbps;
					m_configGIndex->preamble_type = OFDMPreamble; 
					m_configGIndex->scrambler_state = ON;
					m_configGIndex->modulation_type = BPSK_1_2_;

					//m_configGIndex->EZOG_Encoding = BPSK_1_2;

					pPropT95->SetValue((COleVariant)_T("BPSK"));
					pPropT90->SetValue((COleVariant)_T("1/2"));
					//pPropT86->SetValue((COleVariant)_T("2980 symbols"));
					
				}
				else if (d == _T("9 Mbps(OFDM)"))
				{
					pPropT94->AddOption(_T("��"));  
					pPropT94->AddOption(_T("��"));
					pPropT94->AddOption(_T("OFDM"));
					m_configGIndex->EZOG_Encoding = BPSK_3_4;
					m_configGIndex->data_rate =  _9Mbps;
					m_configGIndex->preamble_type = OFDMPreamble; 
					m_configGIndex->modulation_type = BPSK_1_2_;
					//m_configGIndex->EZOG_Encoding =BPSK_3_4;							
					pPropT95->SetValue((COleVariant)_T("BPSK"));
					pPropT90->SetValue((COleVariant)_T("3/4"));
					//pPropT86->SetValue((COleVariant)_T("2000 symbols"));
					
				}
				else if (d == _T("12 Mbps(OFDM)"))
				{
					pPropT94->AddOption(_T("��"));  
					pPropT94->AddOption(_T("��"));
					pPropT94->AddOption(_T("OFDM"));
					m_configGIndex->EZOG_Encoding = QPSK_1_2;							
					m_configGIndex->data_rate =  _12Mbps;
					m_configGIndex->preamble_type = OFDMPreamble; 
					m_configGIndex->EZOG_Encoding = QPSK_1_2;
					pPropT95->SetValue((COleVariant)_T("QPSK"));
					pPropT90->SetValue((COleVariant)_T("1/2"));
					//pPropT86->SetValue((COleVariant)_T("1600 symbols"));
					
				}
				else if (d == _T("18 Mbps(OFDM)"))
				{
					pPropT94->AddOption(_T("��"));  
					pPropT94->AddOption(_T("��"));
					pPropT94->AddOption(_T("OFDM"));
					//m_configGIndex->EZOG_Encoding = QPSK_3_4;
					m_configGIndex->EZOG_Encoding = QPSK_3_4;
					m_configGIndex->data_rate =  _18Mbps;
					m_configGIndex->preamble_type = OFDMPreamble; 
					m_configGIndex->modulation_type = QPSK_3_4_;
					pPropT95->SetValue((COleVariant)_T("QPSK"));
					pPropT90->SetValue((COleVariant)_T("3/4"));
					//pPropT86->SetValue((COleVariant)_T("1600 symbols"));
					
				}
				else if (d == _T("24 Mbps(OFDM)"))
				{
					//m_configGIndex->EZOG_Encoding = QAM16_1_2;
					pPropT94->AddOption(_T("��"));  
					pPropT94->AddOption(_T("��"));
					pPropT94->AddOption(_T("OFDM"));
					m_configGIndex->EZOG_Encoding =QAM16_1_2;
					m_configGIndex->data_rate =  _24Mbps;
					m_configGIndex->preamble_type = OFDMPreamble; 
					m_configGIndex->modulation_type =  QAM16_1_2_;

					pPropT95->SetValue((COleVariant)_T("16-QAM"));
					pPropT90->SetValue((COleVariant)_T("1/2"));
					//pPropT86->SetValue((COleVariant)_T("1600 symbols"));
					
				}
				else if (d == _T("36 Mbps(OFDM)"))
				{
					pPropT94->AddOption(_T("��"));  
					pPropT94->AddOption(_T("��"));
					pPropT94->AddOption(_T("OFDM"));
					//m_configGIndex->EZOG_Encoding = QAM16_3_4;
					m_configGIndex->EZOG_Encoding = QAM16_3_4;
					m_configGIndex->data_rate =  _36Mbps;
					m_configGIndex->preamble_type = OFDMPreamble; 
					m_configGIndex->modulation_type = QAM16_3_4_;
					pPropT95->SetValue((COleVariant)_T("16-QAM"));
					pPropT90->SetValue((COleVariant)_T("3/4"));
					//pPropT86->SetValue((COleVariant)_T("1600 symbols"));
					
				}
				else if (d == _T("48 Mbps(OFDM)"))
				{
					pPropT94->AddOption(_T("��"));  
					pPropT94->AddOption(_T("��"));
					pPropT94->AddOption(_T("OFDM"));
					//m_configIndex->EZOA_Encoding = QAM64_2_3;
					m_configGIndex->EZOG_Encoding =QAM64_2_3;
					m_configGIndex->data_rate =  _48Mbps;
					m_configGIndex->preamble_type = OFDMPreamble; 
					m_configGIndex->modulation_type = QAM64_2_3_;

					pPropT95->SetValue((COleVariant)_T("64-QAM"));
					pPropT90->SetValue((COleVariant)_T("2/3"));
					//pPropT86->SetValue((COleVariant)_T("1600 symbols"));
					
				}
				else if (d == _T("54 Mbps(OFDM)"))
				{
					pPropT94->AddOption(_T("��"));  
					pPropT94->AddOption(_T("��"));
					pPropT94->AddOption(_T("OFDM"));
					//m_configIndex->EZOA_Encoding = QAM64_3_4;
					m_configGIndex->EZOG_Encoding = QAM64_3_4;
					m_configGIndex->data_rate =  _54Mbps;
					m_configGIndex->preamble_type = OFDMPreamble; 
					m_configGIndex->modulation_type = QAM64_3_4_;

					pPropT95->SetValue((COleVariant)_T("64-QAM"));
					pPropT90->SetValue((COleVariant)_T("3/4"));
					//pPropT86->SetValue((COleVariant)_T("1600 symbols"));
					
				}				
			}

			else if (d ==_T("1 Mbps(DSSS)")|| d == _T("2 Mbps(DSSS)")||d == _T("11 Mbps(DSSS)")||d == _T("5.5 Mbps(DSSS)")||d == _T("22 Mbps(DSSS)")||d == _T("33 Mbps(DSSS)"))
			{
				pPropT89->Show(FALSE);//���뷽ʽ
				pPropT90->Show(FALSE);//����
				pPropT91->Show(FALSE);//��֯
				pPropT92->Show(FALSE);//OFDM������
				pPropT93->Show(FALSE);//OFDM��������ʼֵ
				pPropT96->Show(FALSE);//OFDM���ز���
				pPropT83->Show(TRUE);//DSSS Scrambler
				pPropT17_g->Enable(FALSE);
				pPropT17_g->SetValue("1");
				m_configGIndex->NumOfTaps = 1 ;

				//pPropT94->AddOption(_T("OFDM"));
				if (d ==_T("1 Mbps(DSSS)"))
				{
					m_configGIndex->EZOG_Encoding = DBPSK_1M;
					m_configGIndex->modulation_type = DBPSK_1Mbps;
					m_configGIndex->data_rate =  _1Mbps;
					m_configGIndex->preamble_type = longPreamble; 

					//m_configGIndex->modulation_type = DBPSK_1Mbps;
					
					pPropT95->SetValue((COleVariant)_T("DBPSK"));
					pPropT95->Enable(FALSE);
					pPropT94->SetValue((COleVariant)_T("��"));
					pPropT94->Enable(FALSE);


				}					

				else if (d == _T("2 Mbps(DSSS)"))
				{
					m_configGIndex->EZOG_Encoding = DQPSK_2M;
					m_configGIndex->modulation_type = DQPSK_2Mbps;
					m_configGIndex->data_rate =  _2Mbps;
					m_configGIndex->preamble_type = longPreamble; 
					pPropT94->RemoveAllOptions();
					pPropT95->SetValue((COleVariant)_T("DQPSK"));
					pPropT95->Enable(FALSE);
					pPropT94->SetValue((COleVariant)_T("��"));
					pPropT94->AddOption(_T("��"));
					pPropT94->AddOption(_T("��"));
					pPropT94->Enable(TRUE);
					


				}
				else if (d == _T("5.5 Mbps(DSSS)"))
				{
					m_configGIndex->EZOG_Encoding = CCK_5_5M;
					m_configGIndex->modulation_type = CCK55_55Mbps;
					m_configGIndex->data_rate =  _55Mbps;
					m_configGIndex->preamble_type = longPreamble; 


					pPropT94->RemoveAllOptions();
					pPropT95->Enable(TRUE);
					pPropT95->SetValue((COleVariant)_T("CCK"));
					pPropT95->AddOption(_T("CCK"));
					pPropT95->AddOption(_T("PBCC"));						
					pPropT94->SetValue((COleVariant)_T("��"));
					pPropT94->AddOption(_T("��"));
					pPropT94->AddOption(_T("��"));
					pPropT94->Enable(TRUE);

				}
				else if (d == _T("11 Mbps(DSSS)"))
				{
					m_configGIndex->EZOG_Encoding = CCK_11M;
					m_configGIndex->modulation_type = CCK11_11Mpbs;
					m_configGIndex->data_rate =  _11Mbps;
					m_configGIndex->preamble_type = longPreamble; 
					pPropT94->RemoveAllOptions();
					pPropT95->Enable(TRUE);
					pPropT95->SetValue((COleVariant)_T("CCK"));
					pPropT95->AddOption(_T("CCK"));
					pPropT95->AddOption(_T("PBCC"));
					pPropT94->SetValue((COleVariant)_T("��"));
					pPropT94->AddOption(_T("��"));
					pPropT94->AddOption(_T("��"));
					pPropT94->Enable(TRUE);
				}
				else if (d == _T("22 Mbps(DSSS)"))
				{
					m_configGIndex->EZOG_Encoding = PBCC_22M;
					m_configGIndex->modulation_type = PBCC22_22Mbps;
					m_configGIndex->data_rate =  _22Mbps;
					m_configGIndex->preamble_type = longPreamble; 
					pPropT94->RemoveAllOptions();
					pPropT95->SetValue((COleVariant)_T("PBCC"));
					pPropT95->Enable(FALSE);
					pPropT94->SetValue((COleVariant)_T("��"));
					pPropT94->AddOption(_T("��"));
					pPropT94->AddOption(_T("��"));
					pPropT94->Enable(TRUE);
				}
				else if (d == _T("33 Mbps(DSSS)"))
				{
					m_configGIndex->EZOG_Encoding = PBCC_33M;
					m_configGIndex->modulation_type = PBCC33_33Mbps;
					m_configGIndex->data_rate =  _22Mbps;
					m_configGIndex->preamble_type = longPreamble; 
					pPropT94->RemoveAllOptions();
					pPropT95->SetValue((COleVariant)_T("PBCC"));
					pPropT95->Enable(FALSE);
					pPropT94->SetValue((COleVariant)_T("��"));
					pPropT94->AddOption(_T("��"));
					pPropT94->AddOption(_T("��"));
					pPropT94->Enable(TRUE);
				}
			}
			break;
			case MFCPROPERTYTSSDG:
				{
				if(d==_T("PBCC"))
				{
					pPropT95->SetValue((COleVariant)_T("PBCC"));
					if (m_configGIndex->data_rate == _55Mbps)
					{
						m_configGIndex->EZOG_Encoding = PBCC_5_5M;
					} 
					else
					{
						m_configGIndex->EZOG_Encoding = PBCC_11M;
					}

				}
				else if(d==_T("CCK"))
				{
					pPropT95->SetValue((COleVariant)_T("CCK"));
					if (m_configGIndex->data_rate == _55Mbps)
					{
						m_configGIndex->EZOG_Encoding = CCK_5_5M;
					} 
					else
					{
						m_configGIndex->EZOG_Encoding = CCK_11M;
					}
				}
				}
				break;
			case GMFCPROPERTYTFO:
				{
					CString str = pProp->GetValue();
					if(str == "�û��Զ���")
					{
						lp_filter_len_g->Show(FALSE);
						lp_filter_wn_g->Show(FALSE);
						gauss_filter_BT_g->Show(FALSE);
						gauss_filter_len_g->Show(FALSE);
						cosine_filter_alpha_g->Show(FALSE);
						cosine_filter_len_g->Show(FALSE);
						filter_user_g->Show(TRUE);
						m_configGIndex->filter_para.filtertype =  userdefined;
					}
					if(str =="�����ͨ�˲���")
					{
						lp_filter_len_g->Show(TRUE);
						lp_filter_wn_g->Show(TRUE);
						gauss_filter_BT_g->Show(FALSE);
						gauss_filter_len_g->Show(FALSE);
						cosine_filter_alpha_g->Show(FALSE);
						cosine_filter_len_g->Show(FALSE);
						filter_user_g->Show(FALSE);
						m_configGIndex->filter_para.filtertype =  lpfilter;
					}
					if(str == "��˹�˲���")
					{
						lp_filter_len_g->Show(FALSE);
						lp_filter_wn_g->Show(FALSE);
						gauss_filter_BT_g->Show(TRUE);
						gauss_filter_len_g->Show(TRUE);
						cosine_filter_alpha_g->Show(FALSE);
						cosine_filter_len_g->Show(FALSE);
						filter_user_g->Show(FALSE);
						m_configGIndex->filter_para.filtertype =  gaussfilter;
					}
					if( str == "���������˲���")
					{
						lp_filter_len_g->Show(FALSE);
						lp_filter_wn_g->Show(FALSE);
						gauss_filter_BT_g->Show(FALSE);
						gauss_filter_len_g->Show(FALSE);
						cosine_filter_alpha_g->Show(TRUE);
						cosine_filter_len_g->Show(TRUE);
						filter_user_g->Show(FALSE);
						m_configGIndex->filter_para.filtertype =  cosfilter;
					}
					break;
				}
			case GLPFILTERLEN:
				{
					CString str = pProp->GetValue();
					m_configGIndex->filter_para.lppara.length = atoi(str);
					break;
				}
			case GLPFILTERWN:
				{
					CString str = pProp->GetValue();
					m_configGIndex->filter_para.lppara.wn = atof(str);
					break;
				}
			case GGAUSSFILTERLEN:
				{
					CString str = pProp->GetValue();
					m_configGIndex->filter_para.gausspara.length = atoi(str);
					break;
				}
			case GGAUSSFILTERBT:
				{
					CString str = pProp->GetValue();
					m_configGIndex->filter_para.gausspara.BT = atof(str);
					break;
				}
			case GCOSINEFILTERLEN:
				{
					CString str = pProp->GetValue();
					m_configGIndex->filter_para.cosinepara.length = atoi(str);
					break;
				}
			case GCOSINEFILTERALPHA:
				{
					CString str = pProp->GetValue();
					m_configGIndex->filter_para.cosinepara.alpha = atof(str);
					break;
				}
		case MFCPROPERTYOEIG:
			{
				if (d==(_T("OFDM")))
				{
					pPropT83->Show(FALSE);//DSSS Scrambler Hide
					m_configGIndex->preamble_type=OFDMPreamble;
				}
				else if (d==(_T("��")))
				{
					pPropT83->Show(TRUE);//DSSS Scrambler
					m_configGIndex->preamble_type=longPreamble;
				}
				else if (d==(_T("��")))
				{
					pPropT83->Show(TRUE);//DSSS Scrambler
					m_configGIndex->preamble_type=shortPreamble;
				}
				
			}


			break;
		case MFCPROPERTYOSEG:
			{
				if (d==_T("On"))
				{
					pPropT83->SetValue((COleVariant)_T("On"));
					m_configGIndex->scrambler_state=ON;
				}
				else if (d==_T("Off"))
				{
					pPropT83->SetValue((COleVariant)_T("Off"));
					m_configGIndex->scrambler_state=OFF;
				}
				else if (d==_T("��ͷ����"))
				{
					pPropT83->SetValue((COleVariant)_T("��ͷ����"));
					m_configGIndex->scrambler_state=Preamble_only;
				}
			}
			break;
		case MFCPROPERTYTSSXG:
			{
				if (d==_T("On"))
				{
					pPropT92->SetValue((COleVariant)_T("On"));
					m_configGIndex->scrambler_state_OFDM=true;
				}
				else if (d==_T("Off"))
				{
					pPropT92->SetValue((COleVariant)_T("Off"));
					m_configGIndex->scrambler_state_OFDM=false;
				}
			}
			break;
		case MFCPROPERTYTSSEG:
			{
				CString str = pPropT93->GetValue();
				int  scramSeed = atoi(str);
				if (scramSeed > 127){
					pPropT93->SetValue("127");
					scramSeed = 127 ;//�������ĳ�ʼֵ����0-127
				}
				if (scramSeed < 0){
					pPropT93->SetValue("0");
					scramSeed = 0 ;//�������ĳ�ʼֵ����0-127
				}
				if (scramSeed==0 && str!="0")
				{
					MessageBox("����Чֵ��","����"); 
					pPropT93->SetValue("93");
					scramSeed = 93 ;//�������ĳ�ʼֵ����0-127
				}
				m_data_and_graph->m_configGIndex->scramble_state_initial = scramSeed;
			}
			break;
		case GDATASOURCE:
			{
				if (0 == d.Compare("PN9"))
				{
					//PN9����
					m_configGIndex->source_mode = 0;
					p_data_filepath_g->Show(FALSE);
				}else if (0 == d.Compare("PN15"))
				{
					//PN15����
					m_configGIndex->source_mode = 1;
					p_data_filepath_g->Show(FALSE);
				}else if (0 == d.Compare("ALL0"))
				{
					// ȫһ����
					m_configGIndex->source_mode = 2;
					p_data_filepath_g->Show(FALSE);
				}else {
					m_configGIndex->source_mode = 3;
					p_data_filepath_g->Show(TRUE);
				}
				break;
			}
		case MFCPROPERTYONIG:
			{
				d.Remove(' ');
				int temp_len;
				temp_len = atoi(d.GetBuffer());
				if (temp_len < 0)
					temp_len = 0;
				else if (temp_len > m_configGIndex->datainmaxlen)
					temp_len = m_configGIndex->datainmaxlen;
				m_configGIndex->source_length = temp_len;
				d.Format("%d",temp_len);
				pProp->SetValue((COleVariant)d);
				break;
			}
		case GFILEPATH:
			{
				char * temp_filename;
				d.Remove(' ');
				if (PathFileExists(d))
				{
					delete[] m_configGIndex->filepath;
					temp_filename = new char[d.GetLength() + 1];
					strcpy(temp_filename,d.GetBuffer());
					m_configGIndex->filepath = temp_filename;
					pProp->SetValue((COleVariant)d);
				}else {
					MessageBox("�ļ������ڣ�");
					pProp->SetValue("");
				}
				break;
			}
		case GPPROPCHANNEL4:
			{
				m_configGIndex->add_channel = d == "on" ? TRUE : FALSE;
				break;
			}

		case GPPROPCHANNEL1:
			{
				double numoftaps = atof(d.GetBuffer());
				m_configGIndex->NumOfTaps = numoftaps ;
				break;
			}
		case GPPROPCHANNEL2:
			{
				double carrierfreq = atof(d.GetBuffer());
				m_configGIndex->carrierfreq =carrierfreq * 1e9;
				break;
			}
		case GPPROPCHANNEL3:
			{
				double mobilespeed = atof(d.GetBuffer());
				m_configGIndex->mobilespeed = mobilespeed;
				break;
			}
		default:
			break;
		}

		break;
	case MFCPROPERTYGRIDTHREEN://11n HT 
			switch(pProp->GetData())
		{
		case MFCPROPERTYOSIN://������0~76
			{
				CString str;
				int mcs=0;
				str =pProp->GetValue();
				mcs =atoi(str);
				if (mcs>76)
				{
					pPropT22->SetValue("76");
					mcs=76;
				}
				if (mcs<0)
				{
					pPropT22->SetValue("0");
					mcs=0;
				}
				if (mcs==0 && str!="0")
				{
					pPropT22->SetValue("10");
					mcs=10;
					MessageBox("����Чֵ","����");
				}
				m_data_and_graph->m_configNIndex->mcs =mcs;
				if(m_data_and_graph->m_configNIndex->BandWidth =="20")
				{
					if(mcs==32)
					{
						m_data_and_graph->m_configNIndex->BandWidth ="40";
						m_carrier.pPropS20->SetValue((COleVariant)_T("40MHz"));
						m_carrier.pPropS20->Enable(FALSE);
					}
				    else
					{
						m_data_and_graph->m_configNIndex->BandWidth ="20";
						m_carrier.pPropS20->SetValue((COleVariant)_T("20MHz"));
						m_carrier.pPropS20->Enable(TRUE);
					}
				}
				else
				{
					m_data_and_graph->m_configNIndex->BandWidth ="40";
					m_carrier.pPropS20->SetValue((COleVariant)_T("40MHz"));
					m_carrier.pPropS20->Enable(TRUE);
				}

				//����Nss�����Ʒ�ʽ��������������
				pPropT23b->Show(FALSE);
				pPropT23c->Show(FALSE);
				pPropT23d->Show(FALSE);
				switch (mcs)
				{
				case 0:
					{
						pPropT23a->SetValue("BPSK");
						pPropT25a->SetValue("1");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
						    {
								pPropT25->SetValue("6.5Mbps");
						    } 
						    else
						    {
                                pPropT25->SetValue("13.5Mbps");
						    }
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("7.2Mbps");
							} 
							else
							{
								pPropT25->SetValue("15.0Mbps");
							}
						}
					}
					break;
				case 1:
					{
						pPropT23a->SetValue("QPSK");
						pPropT25a->SetValue("1");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("13.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("27.0Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("14.4Mbps");
							} 
							else
							{
								pPropT25->SetValue("30.0Mbps");
							}
						}
					}
					break;
				case 2:
					{
						pPropT23a->SetValue("QPSK");
						pPropT25a->SetValue("1");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("19.5Mbps");
							} 
							else
							{
								pPropT25->SetValue("40.5Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("21.7Mbps");
							} 
							else
							{
								pPropT25->SetValue("45.0Mbps");
							}
						}
					}
					break;
				case 3:
					{
						pPropT23a->SetValue("16QAM");
						pPropT25a->SetValue("1");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("26.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("54.0Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("28.9Mbps");
							} 
							else
							{
								pPropT25->SetValue("60.0Mbps");
							}
						}
					}
					break;
				case 4:
					{
						pPropT23a->SetValue("16QAM");
						pPropT25a->SetValue("1");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("39.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("81.0Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("43.3Mbps");
							} 
							else
							{
								pPropT25->SetValue("90.0Mbps");
							}
						}
					}
					break;
				case 5:
					{
						pPropT23a->SetValue("64QAM");
						pPropT25a->SetValue("1");
						pPropT24->SetValue("2/3");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("52.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("108.0Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("57.8Mbps");
							} 
							else
							{
								pPropT25->SetValue("120.0Mbps");
							}
						}
					}
					break;
				case 6:
					{
						pPropT23a->SetValue("64QAM");
						pPropT25a->SetValue("1");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("58.5Mbps");
							} 
							else
							{
								pPropT25->SetValue("121.5Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("65.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("135.0Mbps");
							}
						}
					}
					break;
				case 7:
					{
						pPropT23a->SetValue("64QAM");
						pPropT25a->SetValue("1");
						pPropT24->SetValue("5/6");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("65.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("135.0Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("72.2Mbps");
							} 
							else
							{
								pPropT25->SetValue("150.0Mbps");
							}
						}
					}
					break;
				case 8:
					{
						pPropT23a->SetValue("BPSK");
						pPropT25a->SetValue("2");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("13.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("27.0Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("14.4Mbps");
							} 
							else
							{
								pPropT25->SetValue("30.0Mbps");
							}
						}
					}
					break;
				case 9:
					{
						pPropT23a->SetValue("QPSK");
						pPropT25a->SetValue("2");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("26.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("54.0Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("28.9Mbps");
							} 
							else
							{
								pPropT25->SetValue("60.0Mbps");
							}
						}
					}
					break;
				case 10:
					{
						pPropT23a->SetValue("QPSK");
						pPropT25a->SetValue("2");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("39.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("81.0Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("43.3Mbps");
							} 
							else
							{
								pPropT25->SetValue("90.0Mbps");
							}
						}
					}
					break;
				case 11:
					{
						pPropT23a->SetValue("16QAM");
						pPropT25a->SetValue("2");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("52.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("108.0Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("57.8Mbps");
							} 
							else
							{
								pPropT25->SetValue("120.0Mbps");
							}
						}
					}
					break;
				case 12:
					{
						pPropT23a->SetValue("16QAM");
						pPropT25a->SetValue("2");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("78.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("162.0Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("86.7Mbps");
							} 
							else
							{
								pPropT25->SetValue("180.0Mbps");
							}
						}
					}
					break;
				case 13:
					{
						pPropT23a->SetValue("64QAM");
						pPropT25a->SetValue("2");
						pPropT24->SetValue("2/3");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("104.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("216.0Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("115.6Mbps");
							} 
							else
							{
								pPropT25->SetValue("240.0Mbps");
							}
						}
					}
					break;
				case 14:
					{
						pPropT23a->SetValue("64QAM");
						pPropT25a->SetValue("2");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("117.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("243.0Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("130.3Mbps");
							} 
							else
							{
								pPropT25->SetValue("270.0Mbps");
							}
						}
					}
					break;
				case 15:
					{
						pPropT23a->SetValue("64QAM");
						pPropT25a->SetValue("2");
						pPropT24->SetValue("5/6");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("130.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("270.0Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("144.4Mbps");
							} 
							else
							{
								pPropT25->SetValue("300.0Mbps");
							}
						}
					}
					break;
				case 16:
					{
						pPropT23a->SetValue("BPSK");
						pPropT25a->SetValue("3");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("19.5Mbps");
							} 
							else
							{
								pPropT25->SetValue("40.5Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("21.7Mbps");
							} 
							else
							{
								pPropT25->SetValue("45.0Mbps");
							}
						}
					}
					break;
				case 17:
					{
						pPropT23a->SetValue("QPSK");
						pPropT25a->SetValue("3");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("39.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("81.0Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("43.3Mbps");
							} 
							else
							{
								pPropT25->SetValue("90.0Mbps");
							}
						}
					}
					break;
				case 18:
					{
						pPropT23a->SetValue("QPSK");
						pPropT25a->SetValue("3");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("58.5Mbps");
							} 
							else
							{
								pPropT25->SetValue("121.5Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("65.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("135.0Mbps");
							}
						}
					}
					break;
				case 19:
					{
						pPropT23a->SetValue("16QAM");
						pPropT25a->SetValue("3");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("78.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("162.0Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("86.7Mbps");
							} 
							else
							{
								pPropT25->SetValue("180.0Mbps");
							}
						}
					}
					break;
				case 20:
					{
						pPropT23a->SetValue("16QAM");
						pPropT25a->SetValue("3");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("117.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("243.0Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("130.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("270.0Mbps");
							}
						}
					}
					break;
				case 21:
					{
						pPropT23a->SetValue("64QAM");
						pPropT25a->SetValue("3");
						pPropT24->SetValue("2/3");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("156.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("324.0Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("173.3Mbps");
							} 
							else
							{
								pPropT25->SetValue("360.0Mbps");
							}
						}
					}
					break;
				case 22:
					{
						pPropT23a->SetValue("64QAM");
						pPropT25a->SetValue("3");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("175.5Mbps");
							} 
							else
							{
								pPropT25->SetValue("364.5Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("195.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("405.0Mbps");
							}
						}
					}
					break;
				case 23:
					{
						pPropT23a->SetValue("64QAM");
						pPropT25a->SetValue("3");
						pPropT24->SetValue("5/6");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("195.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("405.0Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("216.7Mbps");
							} 
							else
							{
								pPropT25->SetValue("450.0Mbps");
							}
						}
					}
					break;
				case 24:
					{
						pPropT23a->SetValue("BPSK");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("26.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("54.0Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("28.9Mbps");
							} 
							else
							{
								pPropT25->SetValue("60.0Mbps");
							}
						}
					}
					break;
				case 25:
					{
						pPropT23a->SetValue("QPSK");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("52.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("108.0Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("57.8Mbps");
							} 
							else
							{
								pPropT25->SetValue("120.0Mbps");
							}
						}
					}
					break;
				case 26:
					{
						pPropT23a->SetValue("QPSK");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("78.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("162.0Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("86.7Mbps");
							} 
							else
							{
								pPropT25->SetValue("180.0Mbps");
							}
						}
					}
					break;
				case 27:
					{
						pPropT23a->SetValue("16QAM");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("104.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("216.0Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("115.6Mbps");
							} 
							else
							{
								pPropT25->SetValue("240.0Mbps");
							}
						}
					}
					break;
				case 28:
					{
						pPropT23a->SetValue("16QAM");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("156.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("324.0Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("173.3Mbps");
							} 
							else
							{
								pPropT25->SetValue("360.0Mbps");
							}
						}
					}
					break;
				case 29:
					{
						pPropT23a->SetValue("64QAM");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("2/3");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("208.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("432.0Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("231.1Mbps");
							} 
							else
							{
								pPropT25->SetValue("480.0Mbps");
							}
						}
					}
					break;
				case 30:
					{
						pPropT23a->SetValue("64QAM");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("234.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("486.0Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("260.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("540.0Mbps");
							}
						}
					}
					break;
				case 31:
					{
						pPropT23a->SetValue("64QAM");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("5/6");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("260.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("540.0Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("288.9Mbps");
							} 
							else
							{
								pPropT25->SetValue("600.0Mbps");
							}
						}
					}
					break;
				case 32:
					{
						pPropT23a->SetValue("BPSK");
						pPropT25a->SetValue("1");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							
								pPropT25->SetValue("6.0Mbps");
						
						} 
						else
						{
							
							
								pPropT25->SetValue("6.7Mbps");
							
						}
					}
					break;
				case 33:
					{
						pPropT23a->SetValue("16QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("QPSK");
						pPropT25a->SetValue("2");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("39Mbps");
							} 
							else
							{
								pPropT25->SetValue("81Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("43.3Mbps");
							} 
							else
							{
								pPropT25->SetValue("90Mbps");
							}
						}
					}
					break;
				case 34:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("QPSK");
						pPropT25a->SetValue("2");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("52Mbps");
							} 
							else
							{
								pPropT25->SetValue("108Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("57.8Mbps");
							} 
							else
							{
								pPropT25->SetValue("120Mbps");
							}
						}
					}
					break;
				case 35:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("16QAM");
						pPropT25a->SetValue("2");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("65Mbps");
							} 
							else
							{
								pPropT25->SetValue("135Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("72.2Mbps");
							} 
							else
							{
								pPropT25->SetValue("150Mbps");
							}
						}
					}
					break;
				case 36:
					{
						pPropT23a->SetValue("16QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("QPSK");
						pPropT25a->SetValue("2");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("58.5Mbps");
							} 
							else
							{
								pPropT25->SetValue("121.5Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("65.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("135Mbps");
							}
						}
					}
					break;
				case 37:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("QPSK");
						pPropT25a->SetValue("2");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("78Mbps");
							} 
							else
							{
								pPropT25->SetValue("162Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("86.7Mbps");
							} 
							else
							{
								pPropT25->SetValue("180Mbps");
							}
						}
					}
					break;
				case 38:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("16QAM");
						pPropT25a->SetValue("2");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("97.5Mbps");
							} 
							else
							{
								pPropT25->SetValue("202.5Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("108.3Mbps");
							} 
							else
							{
								pPropT25->SetValue("225Mbps");
							}
						}
					}
					break;
				case 39:
					{
						pPropT23a->SetValue("16QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("QPSK");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("QPSK");
						pPropT25a->SetValue("3");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("52Mbps");
							} 
							else
							{
								pPropT25->SetValue("108Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("57.8Mbps");
							} 
							else
							{
								pPropT25->SetValue("120Mbps");
							}
						}
					}
					break;
				case 40:
					{
						pPropT23a->SetValue("16QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("16QAM");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("QPSK");
						pPropT25a->SetValue("3");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("65Mbps");
							} 
							else
							{
								pPropT25->SetValue("135Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("72.2Mbps");
							} 
							else
							{
								pPropT25->SetValue("150Mbps");
							}
						}
					}
					break;
				case 41:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("QPSK");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("QPSK");
						pPropT25a->SetValue("3");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("65Mbps");
							} 
							else
							{
								pPropT25->SetValue("135Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("72.2Mbps");
							} 
							else
							{
								pPropT25->SetValue("150Mbps");
							}
						}
					}
					break;
				case 42:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("16QAM");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("QPSK");
						pPropT25a->SetValue("3");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("78Mbps");
							} 
							else
							{
								pPropT25->SetValue("162Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("86.7Mbps");
							} 
							else
							{
								pPropT25->SetValue("180Mbps");
							}
						}
					}
					break;
				case 43:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("16QAM");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("16QAM");
						pPropT25a->SetValue("3");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("91Mbps");
							} 
							else
							{
								pPropT25->SetValue("189Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("101.1Mbps");
							} 
							else
							{
								pPropT25->SetValue("210Mbps");
							}
						}
					}
					break;
				case 44:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("64QAM");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("QPSK");
						pPropT25a->SetValue("3");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("91Mbps");
							} 
							else
							{
								pPropT25->SetValue("189Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("101Mbps");
							} 
							else
							{
								pPropT25->SetValue("210Mbps");
							}
						}
					}
					break;
				case 45:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("64QAM");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("16QAM");
						pPropT25a->SetValue("3");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("104Mbps");
							} 
							else
							{
								pPropT25->SetValue("216Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("115.6Mbps");
							} 
							else
							{
								pPropT25->SetValue("240Mbps");
							}
						}
					}
					break;
				case 46:
					{
						pPropT23a->SetValue("16QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("QPSK");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("QPSK");
						pPropT25a->SetValue("3");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("78Mbps");
							} 
							else
							{
								pPropT25->SetValue("162Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("86.7Mbps");
							} 
							else
							{
								pPropT25->SetValue("180Mbps");
							}
						}
					}
					break;
				case 47:
					{
						pPropT23a->SetValue("16QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("16QAM");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("QPSK");
						pPropT25a->SetValue("3");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("97.5Mbps");
							} 
							else
							{
								pPropT25->SetValue("202.5Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("108.3Mbps");
							} 
							else
							{
								pPropT25->SetValue("225Mbps");
							}
						}
					}
					break;
				case 48:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("QPSK");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("QPSK");
						pPropT25a->SetValue("3");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("97.5Mbps");
							} 
							else
							{
								pPropT25->SetValue("202.5Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("108.3Mbps");
							} 
							else
							{
								pPropT25->SetValue("225Mbps");
							}
						}
					}
					break;
				case 49:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("16QAM");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("QPSK");
						pPropT25a->SetValue("3");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("117Mbps");
							} 
							else
							{
								pPropT25->SetValue("243Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("130.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("270Mbps");
							}
						}
					}
					break;
				case 50:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("16QAM");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("16QAM");
						pPropT25a->SetValue("3");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("136.5Mbps");
							} 
							else
							{
								pPropT25->SetValue("283.5Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("151.7Mbps");
							} 
							else
							{
								pPropT25->SetValue("315Mbps");
							}
						}
					}
					break;
				case 51:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("64QAM");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("QPSK");
						pPropT25a->SetValue("3");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("136.5Mbps");
							} 
							else
							{
								pPropT25->SetValue("283.5Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("151.7Mbps");
							} 
							else
							{
								pPropT25->SetValue("315Mbps");
							}
						}
					}
					break;
				case 52:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("64QAM");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("16QAM");
						pPropT25a->SetValue("3");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("156Mbps");
							} 
							else
							{
								pPropT25->SetValue("324Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("173.3Mbps");
							} 
							else
							{
								pPropT25->SetValue("360Mbps");
							}
						}
					}
					break;
				case 53:
					{
						pPropT23a->SetValue("16QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("QPSK");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("QPSK");
						pPropT23d->Show(TRUE);
						pPropT23d->SetValue("QPSK");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("65Mbps");
							} 
							else
							{
								pPropT25->SetValue("135Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("72.2Mbps");
							} 
							else
							{
								pPropT25->SetValue("150Mbps");
							}
						}
					}
					break;
				case 54:
					{
						pPropT23a->SetValue("16QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("16QAM");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("QPSK");
						pPropT23d->Show(TRUE);
						pPropT23d->SetValue("QPSK");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("78Mbps");
							} 
							else
							{
								pPropT25->SetValue("162Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("86.7Mbps");
							} 
							else
							{
								pPropT25->SetValue("180Mbps");
							}
						}
					}
					break;
				case 55:
					{
						pPropT23a->SetValue("16QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("16QAM");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("16QAM");
						pPropT23d->Show(TRUE);
						pPropT23d->SetValue("QPSK");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("91Mbps");
							} 
							else
							{
								pPropT25->SetValue("189Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("101.1Mbps");
							} 
							else
							{
								pPropT25->SetValue("210Mbps");
							}
						}
					}
					break;
				case 56:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("QPSK");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("QPSK");
						pPropT23d->Show(TRUE);
						pPropT23d->SetValue("QPSK");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("78Mbps");
							} 
							else
							{
								pPropT25->SetValue("162Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("86.7Mbps");
							} 
							else
							{
								pPropT25->SetValue("180Mbps");
							}
						}
					}
					break;
				case 57:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("16QAM");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("QPSK");
						pPropT23d->Show(TRUE);
						pPropT23d->SetValue("QPSK");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("91Mbps");
							} 
							else
							{
								pPropT25->SetValue("189Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("101.1Mbps");
							} 
							else
							{
								pPropT25->SetValue("210Mbps");
							}
						}
					}
					break;
				case 58:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("16QAM");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("16QAM");
						pPropT23d->Show(TRUE);
						pPropT23d->SetValue("QPSK");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("104Mbps");
							} 
							else
							{
								pPropT25->SetValue("216Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("115.6Mbps");
							} 
							else
							{
								pPropT25->SetValue("240Mbps");
							}
						}
					}
					break;
				case 59:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("16QAM");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("16QAM");
						pPropT23d->Show(TRUE);
						pPropT23d->SetValue("16QAM");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("130Mbps");
							} 
							else
							{
								pPropT25->SetValue("270Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("144.4Mbps");
							} 
							else
							{
								pPropT25->SetValue("300Mbps");
							}
						}
					}
					break;
				case 60:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("QPSK");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("QPSK");
						pPropT23d->Show(TRUE);
						pPropT23d->SetValue("QPSK");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("104Mbps");
							} 
							else
							{
								pPropT25->SetValue("216Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("115.6Mbps");
							} 
							else
							{
								pPropT25->SetValue("240Mbps");
							}
						}
					}
					break;
				case 61:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("16QAM");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("16QAM");
						pPropT23d->Show(TRUE);
						pPropT23d->SetValue("QPSK");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("117Mbps");
							} 
							else
							{
								pPropT25->SetValue("243Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("130.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("270Mbps");
							}
						}
					}
					break;
				case 62:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("16QAM");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("16QAM");
						pPropT23d->Show(TRUE);
						pPropT23d->SetValue("16QAM");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("130Mbps");
							} 
							else
							{
								pPropT25->SetValue("270Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("144.4Mbps");
							} 
							else
							{
								pPropT25->SetValue("300Mbps");
							}
						}
					}
					break;
				case 63:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("64QAM");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("64QAM");
						pPropT23d->Show(TRUE);
						pPropT23d->SetValue("QPSK");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("130Mbps");
							} 
							else
							{
								pPropT25->SetValue("270Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("144.4Mbps");
							} 
							else
							{
								pPropT25->SetValue("300Mbps");
							}
						}
					}
					break;
				case 64:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("64QAM");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("64QAM");
						pPropT23d->Show(TRUE);
						pPropT23d->SetValue("16QAM");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("1/2");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("143Mbps");
							} 
							else
							{
								pPropT25->SetValue("297Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("158.9Mbps");
							} 
							else
							{
								pPropT25->SetValue("330Mbps");
							}
						}
					}
					break;
				case 65:
					{
						pPropT23a->SetValue("16QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("QPSK");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("QPSK");
						pPropT23d->Show(TRUE);
						pPropT23d->SetValue("QPSK");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("97.5Mbps");
							} 
							else
							{
								pPropT25->SetValue("202.5Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("108.3Mbps");
							} 
							else
							{
								pPropT25->SetValue("225Mbps");
							}
						}
					}
					break;
				case 66:
					{
						pPropT23a->SetValue("16QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("16QAM");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("QPSK");
						pPropT23d->Show(TRUE);
						pPropT23d->SetValue("QPSK");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("117Mbps");
							} 
							else
							{
								pPropT25->SetValue("243Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("130.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("270Mbps");
							}
						}
					}
					break;
				case 67:
					{
						pPropT23a->SetValue("16QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("16QAM");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("16QAM");
						pPropT23d->Show(TRUE);
						pPropT23d->SetValue("QPSK");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("136.5Mbps");
							} 
							else
							{
								pPropT25->SetValue("283.5Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("151.7Mbps");
							} 
							else
							{
								pPropT25->SetValue("315Mbps");
							}
						}
					}
					break;
				case 68:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("QPSK");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("QPSK");
						pPropT23d->Show(TRUE);
						pPropT23d->SetValue("QPSK");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("117Mbps");
							} 
							else
							{
								pPropT25->SetValue("243Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("130.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("270Mbps");
							}
						}
					}
					break;
				case 69:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("16QAM");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("QPSK");
						pPropT23d->Show(TRUE);
						pPropT23d->SetValue("QPSK");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("136.5Mbps");
							} 
							else
							{
								pPropT25->SetValue("283.5Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("151.7Mbps");
							} 
							else
							{
								pPropT25->SetValue("315Mbps");
							}
						}
					}
					break;
				case 70:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("16QAM");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("16QAM");
						pPropT23d->Show(TRUE);
						pPropT23d->SetValue("QPSK");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("156Mbps");
							} 
							else
							{
								pPropT25->SetValue("324Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("173.3Mbps");
							} 
							else
							{
								pPropT25->SetValue("360Mbps");
							}
						}
					}
					break;
				case 71:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("16QAM");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("16QAM");
						pPropT23d->Show(TRUE);
						pPropT23d->SetValue("16QAM");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("175.5Mbps");
							} 
							else
							{
								pPropT25->SetValue("364.5Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("195.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("405Mbps");
							}
						}
					}
					break;
				case 72:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("64QAM");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("QPSK");
						pPropT23d->Show(TRUE);
						pPropT23d->SetValue("QPSK");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("156Mbps");
							} 
							else
							{
								pPropT25->SetValue("324Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("173.3Mbps");
							} 
							else
							{
								pPropT25->SetValue("360Mbps");
							}
						}
					}
					break;
				case 73:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("64QAM");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("16QAM");
						pPropT23d->Show(TRUE);
						pPropT23d->SetValue("QPSK");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("175.5Mbps");
							} 
							else
							{
								pPropT25->SetValue("364.5Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("195.0Mbps");
							} 
							else
							{
								pPropT25->SetValue("405Mbps");
							}
						}
					}
					break;
				case 74:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("64QAM");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("16QAM");
						pPropT23d->Show(TRUE);
						pPropT23d->SetValue("16QAM");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("195Mbps");
							} 
							else
							{
								pPropT25->SetValue("405Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("216.7Mbps");
							} 
							else
							{
								pPropT25->SetValue("450Mbps");
							}
						}
					}
					break;
				case 75:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("64QAM");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("64QAM");
						pPropT23d->Show(TRUE);
						pPropT23d->SetValue("QPSK");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("195Mbps");
							} 
							else
							{
								pPropT25->SetValue("405Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("216.7Mbps");
							} 
							else
							{
								pPropT25->SetValue("450Mbps");
							}
						}
					}
					break;
				case 76:
					{
						pPropT23a->SetValue("64QAM");
						pPropT23b->Show(TRUE);
						pPropT23b->SetValue("64QAM");
						pPropT23c->Show(TRUE);
						pPropT23c->SetValue("64QAM");
						pPropT23d->Show(TRUE);
						pPropT23d->SetValue("16QAM");
						pPropT25a->SetValue("4");
						pPropT24->SetValue("3/4");
						if (m_data_and_graph->m_configNIndex->Short_GI==0)
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("214.5Mbps");
							} 
							else
							{
								pPropT25->SetValue("445.5Mbps");
							}
						} 
						else
						{
							if (m_data_and_graph->m_configNIndex->BandWidth =="20")
							{
								pPropT25->SetValue("238.3Mbps");
							} 
							else
							{
								pPropT25->SetValue("495Mbps");
							}
						}
					}
					break;
				}
				if (mcs<=7||mcs==32)
				{
					m_data_and_graph->m_configNIndex->Nss=1;
					m_data_and_graph->m_configNIndex->num_of_sts = 1;
					pPropT25c->SetValue("1");
					m_data_and_graph->m_configNIndex->STBC=0;
					pPropT25b->SetValue("0");

					int num_of_antenna;//������
					num_of_antenna =m_data_and_graph->m_configNIndex->Nt;//�������ߵ���Ŀ
					
					if(m_data_and_graph->m_configNIndex->Nt==1)
					{
						numofNt->SetValue("1");
					}
					
					switch(m_data_and_graph->m_configNIndex->ieeeQ)
					{
					case 0:
						{  m_data_and_graph->m_configNIndex->Nt=1;
						numofNt->SetValue("1");
						break;
						}
					case 1:break;
					case 2:break;
					case 3:break;
					case 5:break;
					case 4:
						{
							if(num_of_antenna<2)
							{  m_data_and_graph->m_configNIndex->Nt=2;
							numofNt->SetValue("2");
							}
							break;
						}
					}
				} 
				else if((mcs>=8 && mcs<=15)||(mcs>=33&&mcs<=38))
				{
					m_data_and_graph->m_configNIndex->Nss=2;
					m_data_and_graph->m_configNIndex->num_of_sts = 2;
					pPropT25c->SetValue("2");
					m_data_and_graph->m_configNIndex->STBC=0;
					pPropT25b->SetValue("0");
				}
				else if ((mcs>=16 && mcs<=23)||(mcs>=39&&mcs<=52))
				{
					m_data_and_graph->m_configNIndex->Nss=3;
					m_data_and_graph->m_configNIndex->num_of_sts = 3;
					pPropT25c->SetValue("3");
					m_data_and_graph->m_configNIndex->STBC=0;
					pPropT25b->SetValue("0");
				}
				else
				{
					m_data_and_graph->m_configNIndex->Nss=4;
					m_data_and_graph->m_configNIndex->num_of_sts = 4;
					pPropT25c->SetValue("4");
					m_data_and_graph->m_configNIndex->STBC=0;
					pPropT25b->SetValue("0");
				}
				/*
				//���ÿ�ʱ���ĸ���
				if(mcs<=7||mcs==32)
				{   
					int num_of_antenna;//������
					int num_of_sts;//��ʱ����
					num_of_sts=1;
					m_carrier.pPropS22->SetValue("1");
					num_of_antenna =m_data_and_graph->m_configNIndex->Nt;//�������ߵ���Ŀ
					switch(m_data_and_graph->m_configNIndex->ieeeQ)
					{
		              case 0:
						  {  m_data_and_graph->m_configNIndex->Nt=num_of_sts;
						     numofNt->SetValue("1");
							 break;
						  }
					  case 1:break;
					  case 2:break;
					  case 3:break;
					  case 5:break;
					  case 4:
						  {
							  if(num_of_antenna<2)
								{  m_data_and_graph->m_configNIndex->Nt=2;
							      numofNt->SetValue("2");
							    }
							  break;
						  }
					}
				}
				if((mcs>=8 && mcs<=15)||(mcs>=33&&mcs<=38))
				{
					int num_of_antenna;//������
					int num_of_sts;//��ʱ����
					num_of_sts=2;
					m_carrier.pPropS22->SetValue("2");
					num_of_antenna =m_data_and_graph->m_configNIndex->Nt;
					switch(m_data_and_graph->m_configNIndex->ieeeQ)
					{
					case 0:
						{  m_data_and_graph->m_configNIndex->Nt=num_of_sts;
						   numofNt->SetValue("2");
						break;
						}
					case 1:break;
					case 2:break;
					case 3:break;
					case 5:break;
					case 4:
						{
							if(num_of_antenna<3)
							{  m_data_and_graph->m_configNIndex->Nt=3;
							   numofNt->SetValue("3");
							}
							break;
						}
					}
				}
				if((mcs>=16 && mcs<=23)||(mcs>=39&&mcs<=52))
				{
					int num_of_antenna;//������
					int num_of_sts;//��ʱ����
					num_of_sts=3;
					m_carrier.pPropS22->SetValue("3");
					num_of_antenna =m_data_and_graph->m_configNIndex->Nt;
					switch(m_data_and_graph->m_configNIndex->ieeeQ)
					{
					case 0:
						{  m_data_and_graph->m_configNIndex->Nt=num_of_sts;
						   numofNt->SetValue("3");
						break;
						}
					case 1:break;
					case 2:break;
					case 3:break;
					case 5:break;
					case 4:
						{
							if(num_of_antenna<4)
							{  m_data_and_graph->m_configNIndex->Nt=4;
							   numofNt->SetValue("4");
							}
							break;
						}
					}
				}
				if((mcs>=24 && mcs<=31)||((mcs>=53&&mcs<=76)))
				{
					int num_of_antenna;//������
					int num_of_sts;//��ʱ����
					num_of_sts=4;
					m_carrier.pPropS22->SetValue("4");
					num_of_antenna =m_data_and_graph->m_configNIndex->Nt;
					switch(m_data_and_graph->m_configNIndex->ieeeQ)
					{
					case 0:
						{  m_data_and_graph->m_configNIndex->Nt=num_of_sts;
						   numofNt->SetValue("4");
						   break;
						}
					case 1:break;
					case 2:break;
					case 3:break;
					case 5:break;
					case 4:
						{
							if(num_of_antenna<4)
							{  m_data_and_graph->m_configNIndex->Nt=4;
							   numofNt->SetValue("4");
							}

							break;
						}
					}
				}*/
              break;
			  }
	    case MFCPROPERTYOFINN1://��ʱ����
		    {
				CString str = pPropT25c->GetValue();
				int  Nsts = atoi(str);

				//int STBC=0;
				switch(m_data_and_graph->m_configNIndex->Nss)
				{
				case 1:
					{
						if(Nsts>2)
						{
							Nsts=2;
							pPropT25c->SetValue("2");
						}
						if (Nsts<1)
						{
							Nsts=1;
							pPropT25c->SetValue("1");
						}
					}
					break;
				case 2:
					{
						if(Nsts>4)
						{
							Nsts=4;
							pPropT25c->SetValue("4");
						}
						if (Nsts<2)
						{
							Nsts=2;
							pPropT25c->SetValue("2");
						}
					}
					break;
				case 3:
					{
						if(Nsts>4)
						{
							Nsts=4;
							pPropT25c->SetValue("4");
						}
						if (Nsts<3)
						{
							Nsts=3;
							pPropT25c->SetValue("3");
						}
					}
					break;
				case 4:
					{
						if(Nsts>4)
						{
							Nsts=4;
							pPropT25c->SetValue("4");
						}
						if (Nsts<4)
						{
							Nsts=4;
							pPropT25c->SetValue("4");
						}
					}
					break;

				}
				m_data_and_graph->m_configNIndex->num_of_sts = Nsts;
				m_data_and_graph->m_configNIndex->STBC = m_data_and_graph->m_configNIndex->num_of_sts - m_data_and_graph->m_configNIndex->Nss;
				switch(m_data_and_graph->m_configNIndex->STBC)
				{
				case 0:
					{
						pPropT25b->SetValue("0");
					}
					break;
				case 1:
					{
						pPropT25b->SetValue("1");
					}
					break;
				case 2:
					{
						pPropT25b->SetValue("2");
					}
					break;
				}
				if (m_data_and_graph->m_configNIndex->Nt<m_data_and_graph->m_configNIndex->num_of_sts)
				{
					char str[10];
					itoa(m_data_and_graph->m_configNIndex->num_of_sts,str,10);
					m_data_and_graph->m_configNIndex->Nt=m_data_and_graph->m_configNIndex->num_of_sts;
					m_carrier.pPropS21->SetValue(str);
				}
				if (m_data_and_graph->m_configNIndex->Nt>m_data_and_graph->m_configNIndex->num_of_sts)
				{
					pPropT30->Enable(FALSE);
					pPropT30->SetValue("�ռ���չ");
					m_data_and_graph->m_configNIndex->ieeeQ =4;
				}else
				{
					pPropT30->Enable(TRUE);
					pPropT30->SetValue("ֱ��ӳ��");
					m_data_and_graph->m_configNIndex->ieeeQ =0;
				}
				int top = m_data_and_graph->m_configNIndex->Nt-m_data_and_graph->m_configNIndex->num_of_sts;
				char stra[10];
				itoa(top,stra,10);
				if (m_data_and_graph->m_configNIndex->Ness>top)
				{
					pPropT25d->SetValue(stra);
					m_data_and_graph->m_configNIndex->Ness=top;
				}
		    }
			break;
		case MFCPROPERTYOFINN3://Ness
			{
				CString str = pPropT25d->GetValue();
				int  Ness = atoi(str);
				int  Nt = m_data_and_graph->m_configNIndex->Nt;
				int  top ;
				top = Nt-m_data_and_graph->m_configNIndex->num_of_sts;
				char stra[10];
				itoa(top,stra,10);
				if (Ness>top)
				{
					pPropT25d->SetValue(stra);
					Ness=top;
				}
				m_data_and_graph->m_configNIndex->Ness=Ness;
			}
			break;
		case MFCPROPERTYSSIN:
			{
				if (0 == d.Compare("PN9"))
				{
					//PN9����
					m_configNIndex->source_mode = 0;
					p_data_filepath_n->Show(FALSE);
				}else if (0 == d.Compare("PN15"))
				{
					//PN15����
					m_configNIndex->source_mode = 1;
					p_data_filepath_n->Show(FALSE);
				}else if (0 == d.Compare("ALL0"))
				{
					// ȫһ����
					m_configNIndex->source_mode = 2;
					p_data_filepath_n->Show(FALSE);
				}else {
					m_configNIndex->source_mode = 3;
					p_data_filepath_n->Show(TRUE);
				}
				break;
			}
		case MFCPROPERTYSSEN:
			{
				int len=atoi(d);
				if (len<1)
				{
					len=1;
					pPropT37->SetValue("1");
				}
				if (len>1000)
				{
					len=1000;
					pPropT37->SetValue("1000");
				}
				
				m_configNIndex->source_length = len;
				break;
			}
		case MFCPROPERTYSSN://��֯
			{
				
				if (m_data_and_graph->m_configNIndex->LDPC_Coding==0)//BCC
				{
				
				    CString str =pPropT32->GetValue();
				    if(str =="On")
				    {
						pPropT32->SetValue((COleVariant)_T("On"));
						pPropT32->Enable(TRUE);
						m_data_and_graph->m_configNIndex->interleave_state=true;
				    } 
				    else
				    {
						pPropT32->SetValue((COleVariant)_T("Off"));
						pPropT32->Enable(TRUE);
						m_data_and_graph->m_configNIndex->interleave_state=false;
				    }
				}
				else      //LDPC
				{
					pPropT32->SetValue((COleVariant)_T("Off"));
					pPropT32->Enable(FALSE);
					m_data_and_graph->m_configNIndex->interleave_state=false;
				}
			}
			break;
		case MFCPROPERTYSSN1://������
			{
				CString str =pPropT32a->GetValue();
				if(str =="On")
				{
					pPropT32a->SetValue((COleVariant)_T("On"));

					m_data_and_graph->m_configNIndex->scrambler=true;
				} 
				else
				{
					pPropT32a->SetValue((COleVariant)_T("Off"));

					m_data_and_graph->m_configNIndex->scrambler=false;
				}
			}
			break;
		case MFCPROPERTYSSNN:
			{
				/*CString str =pPropT32->GetValue();
				if(str=="LDPC")
					m_data_and_graph->m_configNIndex->LDPC_Coding =1;
				else
					m_data_and_graph->m_configNIndex->LDPC_Coding =0;
				break;*/
				CString str = pPropT27->GetValue();
				int  scramSeed = atoi(str);
				if (scramSeed > 127){
					pPropT27->SetValue("127");
					scramSeed = 127 ;//�������ĳ�ʼֵ����0-127
				}
				if (scramSeed < 0){
					pPropT27->SetValue("0");
					scramSeed = 0 ;//�������ĳ�ʼֵ����0-127
				}
				if (scramSeed==0 && str!="0")
				{
					MessageBox("����Чֵ��","����"); 
					pPropT27->SetValue("93");
					scramSeed = 93 ;//�������ĳ�ʼֵ����0-127
				}
				m_data_and_graph->m_configNIndex->scramSeed = scramSeed;
				break;
			}
		case MFCPROPERTYOEINN:
			{
				CString str =pPropT288->GetValue();
				if(str=="On")
                      m_data_and_graph->m_configNIndex->win =1;
				else
					  m_data_and_graph->m_configNIndex->win=0;
				break;
			}
	    case MFCPROPERTYONIN:
			{
				int ieeeQ;
				int mcs;
				mcs = m_data_and_graph->m_configNIndex->mcs;
				CString str;
				str = pPropT30->GetValue();
				ieeeQ = str =="ֱ��ӳ��"? 0:4;
				m_data_and_graph->m_configNIndex->ieeeQ =ieeeQ;
				//���ÿ�ʱ���ĸ���
				if(mcs<=7||mcs==32)
				{   
					int num_of_antenna;//������
					int num_of_sts;//��ʱ����
					num_of_sts=1;
					num_of_antenna =m_data_and_graph->m_configNIndex->Nt;
					switch(ieeeQ)
					{
					case 0:
						{  m_data_and_graph->m_configNIndex->Nt=num_of_sts;
						   m_carrier.pPropS21->SetValue("1");
						   break;
						}
					case 4:
						{
							if(num_of_antenna<2)
							{  m_data_and_graph->m_configNIndex->Nt=2;
							   m_carrier.pPropS21->SetValue("2");
							}
							break;
						}
					}
				}
				if((mcs>=8 && mcs<=15)||(mcs>=33&&mcs<=38))
				{
					int num_of_antenna;//������
					int num_of_sts;//��ʱ����
					num_of_sts=2;
					num_of_antenna =m_data_and_graph->m_configNIndex->Nt;
					switch(ieeeQ)
					{
					case 0:
						{  m_data_and_graph->m_configNIndex->Nt=num_of_sts;
						   m_carrier.pPropS21->SetValue("2");
						break;
						}
					case 4:
						{
							if(num_of_antenna<3)
							{  m_data_and_graph->m_configNIndex->Nt=3;
							   m_carrier.pPropS21->SetValue("3");
							}
							break;
						}
					}
				}
				if((mcs>=16 && mcs<=23)||(mcs>=39&&mcs<=52))
				{
					int num_of_antenna;//������
					int num_of_sts;//��ʱ����
					num_of_sts=3;
					num_of_antenna =m_data_and_graph->m_configNIndex->Nt;
					switch(ieeeQ)
					{
					case 0:
						{  m_data_and_graph->m_configNIndex->Nt=num_of_sts;
						   m_carrier.pPropS21->SetValue("3");
						break;
						}
					case 4:
						{
							if(num_of_antenna<4)
							{  m_data_and_graph->m_configNIndex->Nt=4;
							m_carrier.pPropS21->SetValue("4");
							}
							break;
						}
					}
				}
				if((mcs>=24 && mcs<=31)||((mcs>=53&&mcs<=76)))
				{
					int num_of_antenna;//������
					int num_of_sts;//��ʱ����
					num_of_sts=4;
					num_of_antenna =m_data_and_graph->m_configNIndex->Nt;
					switch(ieeeQ)
					{
					case 0:
						{  m_data_and_graph->m_configNIndex->Nt=num_of_sts;
						m_carrier.pPropS21->SetValue("4");
						break;
						}
					case 4:
						{
							if(num_of_antenna<4)
							{  m_data_and_graph->m_configNIndex->Nt=4;
							   m_carrier.pPropS21->SetValue("4");
							}

							break;
						}
					}
				}
				break;
			}
		case MFCPROPERTYSTN:
			{ CString str;
			  str = pProp->GetValue();
			  if(str =="on"){
				  m_data_and_graph->m_configNIndex->aggregation =1;
				  m_MPDUAdd.EnableWindow(TRUE);
				  m_MPDUDelete.EnableWindow(TRUE);
			  }

			  else{
				  m_data_and_graph->m_configNIndex->aggregation =0;
				  m_MPDUAdd.EnableWindow(FALSE);
				  m_MPDUDelete.EnableWindow(FALSE);
			  }
             
			  break;
			}
		case MFCPROPERTYSFIN:
			{
				CString str;
				str = pProp->GetValue();
				if(str =="on")
					m_data_and_graph->m_configNIndex->sounding =1;
				else
					m_data_and_graph->m_configNIndex->sounding =0;
				break;
			}
		case MFCPROPERTYSFN:
			{
				CString str;
				str = pProp->GetValue();
				if(str =="on")
					m_data_and_graph->m_configNIndex->smoothing =1;
				else
					m_data_and_graph->m_configNIndex->smoothing =0;
				break;
			}
			
		case MFCPROPERTYS0N:
			{
				CString str;
				str = pProp->GetValue();
				if(str =="BCC")
				{
					m_data_and_graph->m_configNIndex->LDPC_Coding =0;
					pPropT32->SetValue((COleVariant)_T("On"));
					pPropT32->Enable(TRUE);
					m_data_and_graph->m_configNIndex->interleave_state=true;
				}
				else
					{
						m_data_and_graph->m_configNIndex->LDPC_Coding =1;
						pPropT32->SetValue((COleVariant)_T("Off"));
						pPropT32->Enable(FALSE);
						m_data_and_graph->m_configNIndex->interleave_state=false;
				    }
				break;
			}
		case MFCPROPERTYOFINN:
			{
				CString str;
				int datalen;
				str = pProp->GetValue();
				datalen =atoi(str);
				m_data_and_graph->m_configNIndex->datalength =datalen;
				break;
			}
		case MFCPROPERTYOEIN:
			{
				CString str =pPropT28->GetValue();
				if(str =="On")
					m_data_and_graph->m_configNIndex->Short_GI =1;
				else
					m_data_and_graph->m_configNIndex->Short_GI =0;
				break;
			}
		case MFCPROPERTYSEIN:
			{
				CString str = pPropT39->GetValue();
				m_data_and_graph->m_configNIndex->add_channel = str =="on" ? TRUE : FALSE;
				break;
			}
		case CHANNELTYPE:
			{
				CString str = pPropT40->GetValue();
				char ch = str.GetAt(0);
				m_data_and_graph->m_configNIndex->channel_type = ch ;
				break;
			}
		case NUMOFTXANNEA:
			{
				CString str = numofNt->GetValue();
				int numoftxannea = atoi(str);
				m_data_and_graph->m_configNIndex->Nt = numoftxannea;



				break;
			}
		case NUMOFRXANNEA:
			{
				CString str = numofNr->GetValue();
				int numofrxannea = atoi(str);
				m_data_and_graph->m_configNIndex->Nr = numofrxannea;
				break;
			}
		case MFCPROPERTYTON:
			{
				CString str = pPropT41->GetValue();
				double mobilespeed = atof(str);
				m_data_and_graph->m_configNIndex->mobilespeed = mobilespeed;
				break;
			}
		case MFCPROPERTYTSN:
			{
				CString str = pPropT42->GetValue();
				double carrierfreq = atof(str);
				m_data_and_graph->m_configNIndex->carrierfreq = carrierfreq * 1e9;
				break;
			}
		case NMFCPROPERTYTFO:
			{
				CString str = pProp->GetValue();
				if(str == "�û��Զ���")
				{
					lp_filter_len_n->Show(FALSE);
					lp_filter_wn_n->Show(FALSE);
					gauss_filter_BT_n->Show(FALSE);
					gauss_filter_len_n->Show(FALSE);
					cosine_filter_alpha_n->Show(FALSE);
					cosine_filter_len_n->Show(FALSE);
					filter_user_n->Show(TRUE);
					m_configNIndex->filter_para.filtertype =  userdefined;
				}
				if(str =="�����ͨ�˲���")
				{
					lp_filter_len_n->Show(TRUE);
					lp_filter_wn_n->Show(TRUE);
					gauss_filter_BT_n->Show(FALSE);
					gauss_filter_len_n->Show(FALSE);
					cosine_filter_alpha_n->Show(FALSE);
					cosine_filter_len_n->Show(FALSE);
					filter_user_n->Show(FALSE);
					m_configNIndex->filter_para.filtertype =  lpfilter;
				}
				if(str == "��˹�˲���")
				{
					lp_filter_len_n->Show(FALSE);
					lp_filter_wn_n->Show(FALSE);
					gauss_filter_BT_n->Show(TRUE);
					gauss_filter_len_n->Show(TRUE);
					cosine_filter_alpha_n->Show(FALSE);
					cosine_filter_len_n->Show(FALSE);
					filter_user_n->Show(FALSE);
					m_configNIndex->filter_para.filtertype =  gaussfilter;
				}
				if( str == "���������˲���")
				{
					lp_filter_len_n->Show(FALSE);
					lp_filter_wn_n->Show(FALSE);
					gauss_filter_BT_n->Show(FALSE);
					gauss_filter_len_n->Show(FALSE);
					cosine_filter_alpha_n->Show(TRUE);
					cosine_filter_len_n->Show(TRUE);
					filter_user_n->Show(FALSE);
					m_configNIndex->filter_para.filtertype =  cosfilter;
				}
				break;
			}
		case NLPFILTERLEN:
			{
				CString str = pProp->GetValue();
				m_configNIndex->filter_para.lppara.length = atoi(str);
				break;
			}
		case NLPFILTERWN:
			{
				CString str = pProp->GetValue();
				m_configNIndex->filter_para.lppara.wn = atof(str);
				break;
			}
		case NGAUSSFILTERLEN:
			{
				CString str = pProp->GetValue();
				m_configNIndex->filter_para.gausspara.length = atoi(str);
				break;
			}
		case NGAUSSFILTERBT:
			{
				CString str = pProp->GetValue();
				m_configNIndex->filter_para.gausspara.BT = atof(str);
				break;
			}
		case NCOSINEFILTERLEN:
			{
				CString str = pProp->GetValue();
				m_configNIndex->filter_para.cosinepara.length = atoi(str);
				break;
			}
		case NCOSINEFILTERALPHA:
			{
				CString str = pProp->GetValue();
				m_configNIndex->filter_para.cosinepara.alpha = atof(str);
				break;
			}
		default:
			break;
		}
		break;
	case MFCPROPERTYGRIDTHREENL://11nl Legacy
		switch(pProp->GetData())
		{
		case MFCPROPERTYOSIN://������0~7
			{
				CString str = pPropT44->GetValue();
				if(str=="6 Mbps"){
					pPropT45->SetValue("BPSK");
					pPropT46->SetValue("1/2");
					m_data_and_graph->m_configNIndex->mcs =0;
				} 
				if(str=="9 Mbps"){
					pPropT45->SetValue("BPSK");
					pPropT46->SetValue("3/4");
					m_data_and_graph->m_configNIndex->mcs =1;
				} 
				if(str=="12 Mbps"){
					pPropT45->SetValue("QPSK");
					pPropT46->SetValue("1/2");
					m_data_and_graph->m_configNIndex->mcs =2;
				} 
				if(str=="18 Mbps"){
					pPropT45->SetValue("QPSK");
					pPropT46->SetValue("3/4");
					m_data_and_graph->m_configNIndex->mcs =3;
				} 
				if(str=="24 Mbps"){
					pPropT45->SetValue("16QAM");
					pPropT46->SetValue("1/2");
					m_data_and_graph->m_configNIndex->mcs =4;
				} 
				if(str=="36 Mbps"){
					pPropT45->SetValue("16QAM");
					pPropT46->SetValue("3/4");
					m_data_and_graph->m_configNIndex->mcs =5;
				} 
				if(str=="48 Mbps"){
					pPropT45->SetValue("64QAM");
					pPropT46->SetValue("2/3");
					m_data_and_graph->m_configNIndex->mcs =6;
				} 
				if(str=="54 Mbps"){
					pPropT45->SetValue("64QAM");
					pPropT46->SetValue("3/4");
					m_data_and_graph->m_configNIndex->mcs =7;
				} 
                break;
			}
		case MFCPROPERTYOSENL:
			{
			   CString str = pPropT48->GetValue();
			   int  scramSeed = atoi(str);
			   if (scramSeed > 127){
				   pPropT48->SetValue("127");
				   scramSeed = 127 ;//�������ĳ�ʼֵ����0-127
			   }
			   if (scramSeed < 0){
				   pPropT48->SetValue("0");
				   scramSeed = 0 ;//�������ĳ�ʼֵ����0-127
			   }
			   if (scramSeed==0 && str!="0")
			   {
				   MessageBox("����Чֵ��","����"); 
				   pPropT48->SetValue("93");
				   scramSeed = 93 ;//�������ĳ�ʼֵ����0-127
			   }
			   m_data_and_graph->m_configNIndex->scramSeed = scramSeed;
			   break;
			}
		case MFCPROPERTYSTL:
			{ 
				CString str;
			    str = pProp->GetValue();
			   if(str =="on")
				  m_data_and_graph->m_configNIndex->aggregation =1;
			   else
				  m_data_and_graph->m_configNIndex->aggregation =0;
			   break;
			}
		case MFCPROPERTYSFIL:
			{
				CString str;
				str = pProp->GetValue();
				if(str =="on")
					m_data_and_graph->m_configNIndex->sounding =1;
				else
					m_data_and_graph->m_configNIndex->sounding =0;
				break;
			}
		case MFCPROPERTYSFL:
			{
				CString str;
				str = pProp->GetValue();
				if(str =="on")
					m_data_and_graph->m_configNIndex->smoothing =1;
				else
					m_data_and_graph->m_configNIndex->smoothing =0;
				break;
			}
		case MFCPROPERTYOFL:
			{
				CString str;
				str = pProp->GetValue();
				if(str =="on")
					m_data_and_graph->m_configNIndex->win =1;
				else
					m_data_and_graph->m_configNIndex->win =0;
				break;
			}
		case CHANNELSTATEL:
			{
				CString str = pProp->GetValue();
				m_data_and_graph->m_configNIndex->add_channel = str =="on" ? TRUE : FALSE;
				break;
			}
		case CHANNELTYPEL:
			{
				CString str = pPropT40->GetValue();
				char ch = str.GetAt(0);
				m_data_and_graph->m_configNIndex->channel_type = ch ;
				break;
			}
		case NUMOFTXANNEAL:
			{
				CString str = numofNt->GetValue();
				int numoftxannea = atoi(str);
				m_data_and_graph->m_configNIndex->Nt = numoftxannea;
				break;
			}
		case NUMOFRXANNEAL:
			{
				CString str = numofNr->GetValue();
				int numofrxannea = atoi(str);
				m_data_and_graph->m_configNIndex->Nr = numofrxannea;
				break;
			}
		case MOBILESPEEDL:
			{
				CString str = pPropT41->GetValue();
				double mobilespeed = atof(str);
				m_data_and_graph->m_configNIndex->mobilespeed = mobilespeed;
				break;
			}
		case CARRIERFREQ:
			{
				CString str = pPropT42->GetValue();
				double carrierfreq = atof(str);
				m_data_and_graph->m_configNIndex->carrierfreq = carrierfreq * 1e9;
				break;
			}
		case MFCPROPERTYSSEL:
			{
				int len=atoi(d);
				if (len<1)
				{
					len=1;
					pPropT55->SetValue("1");
				}
				if (len>1000)
				{
					len=1000;
					pPropT55->SetValue("1000");
				}

				m_configNIndex->source_length = len;
				break;
			}
			break;
		case NLDATASOURCE:
			{
				if (0 == d.Compare("PN9"))
				{
					//PN9����
					m_configNIndex->source_mode = 0;
					p_data_filepath_nl->Show(FALSE);
				}else if (0 == d.Compare("PN15"))
				{
					//PN15����
					m_configNIndex->source_mode = 1;
					p_data_filepath_nl->Show(FALSE);
				}else if (0 == d.Compare("ALL0"))
				{
					// ȫһ����
					m_configNIndex->source_mode = 2;
					p_data_filepath_nl->Show(FALSE);
				}else {
					m_configNIndex->source_mode = 3;
					p_data_filepath_nl->Show(TRUE);
				}
			 break;
			}
		case NLMFCPROPERTYTFO:
			{
				CString str = pProp->GetValue();
				if(str == "�û��Զ���")
				{
					lp_filter_len_nl->Show(FALSE);
					lp_filter_wn_nl->Show(FALSE);
					gauss_filter_BT_nl->Show(FALSE);
					gauss_filter_len_nl->Show(FALSE);
					cosine_filter_alpha_nl->Show(FALSE);
					cosine_filter_len_nl->Show(FALSE);
					filter_user_nl->Show(TRUE);
					m_configNIndex->filter_para.filtertype =  userdefined;
				}
				if(str =="�����ͨ�˲���")
				{
					lp_filter_len_nl->Show(TRUE);
					lp_filter_wn_nl->Show(TRUE);
					gauss_filter_BT_nl->Show(FALSE);
					gauss_filter_len_nl->Show(FALSE);
					cosine_filter_alpha_nl->Show(FALSE);
					cosine_filter_len_nl->Show(FALSE);
					filter_user_nl->Show(FALSE);
					m_configNIndex->filter_para.filtertype =  lpfilter;
				}
				if(str == "��˹�˲���")
				{
					lp_filter_len_nl->Show(FALSE);
					lp_filter_wn_nl->Show(FALSE);
					gauss_filter_BT_nl->Show(TRUE);
					gauss_filter_len_nl->Show(TRUE);
					cosine_filter_alpha_nl->Show(FALSE);
					cosine_filter_len_nl->Show(FALSE);
					filter_user_nl->Show(FALSE);
					m_configNIndex->filter_para.filtertype =  gaussfilter;
				}
				if( str == "���������˲���")
				{
					lp_filter_len_nl->Show(FALSE);
					lp_filter_wn_nl->Show(FALSE);
					gauss_filter_BT_nl->Show(FALSE);
					gauss_filter_len_nl->Show(FALSE);
					cosine_filter_alpha_nl->Show(TRUE);
					cosine_filter_len_nl->Show(TRUE);
					filter_user_nl->Show(FALSE);
					m_configNIndex->filter_para.filtertype =  cosfilter;
				}
				break;
			}
		case NLLPFILTERLEN:
			{
				CString str = pProp->GetValue();
				m_configNIndex->filter_para.lppara.length = atoi(str);
				break;
			}
		case NLLPFILTERWN:
			{
				CString str = pProp->GetValue();
				m_configNIndex->filter_para.lppara.wn = atof(str);
				break;
			}
		case NLGAUSSFILTERLEN:
			{
				CString str = pProp->GetValue();
				m_configNIndex->filter_para.gausspara.length = atoi(str);
				break;
			}
		case NLGAUSSFILTERBT:
			{
				CString str = pProp->GetValue();
				m_configNIndex->filter_para.gausspara.BT = atof(str);
				break;
			}
		case NLCOSINEFILTERLEN:
			{
				CString str = pProp->GetValue();
				m_configNIndex->filter_para.cosinepara.length = atoi(str);
				break;
			}
		case NLCOSINEFILTERALPHA:
			{
				CString str = pProp->GetValue();
				m_configNIndex->filter_para.cosinepara.alpha = atof(str);
				break;
			}
		default:
			break;
		}
		break;
	default:
		break;
	}
	//m_dlgSecondUpdate->update();
	return 0;  
}  

void CTabProtocolConfig::update()
{
	switch (m_configIndex->ProtocolModel)
	{
	case OneA:
		m_MFCPropertyGridThree.ShowWindow(TRUE);
		m_MFCPropertyGridThreeN.ShowWindow(FALSE);
		m_MFCPropertyGridThreeB.ShowWindow(FALSE);
		m_MFCPropertyGridThreeNL.ShowWindow(FALSE);
		m_MFCPropertyGridThreeG.ShowWindow(FALSE);
		m_MpduInfoList.ShowWindow(FALSE);
		m_MPDUAdd.ShowWindow(FALSE);
		m_MPDUDelete.ShowWindow(FALSE);
		break;
	case OneB:
		m_MFCPropertyGridThree.ShowWindow(FALSE);
		m_MFCPropertyGridThreeN.ShowWindow(FALSE);
		m_MFCPropertyGridThreeB.ShowWindow(TRUE);
		m_MFCPropertyGridThreeNL.ShowWindow(FALSE);
		m_MFCPropertyGridThreeG.ShowWindow(FALSE);
		m_MpduInfoList.ShowWindow(FALSE);
		m_MPDUAdd.ShowWindow(FALSE);
		m_MPDUDelete.ShowWindow(FALSE);
		break;
	case OneG:
		m_MFCPropertyGridThree.ShowWindow(FALSE);
		m_MFCPropertyGridThreeN.ShowWindow(FALSE);
		m_MFCPropertyGridThreeB.ShowWindow(FALSE);
		m_MFCPropertyGridThreeNL.ShowWindow(FALSE);
		m_MFCPropertyGridThreeG.ShowWindow(TRUE);
		m_MpduInfoList.ShowWindow(FALSE);
		m_MPDUAdd.ShowWindow(FALSE);
		m_MPDUDelete.ShowWindow(FALSE);
		break;
	case OneN:
		m_MFCPropertyGridThree.ShowWindow(FALSE);
		m_MFCPropertyGridThreeN.ShowWindow(TRUE);
		m_MFCPropertyGridThreeB.ShowWindow(FALSE);
		m_MFCPropertyGridThreeNL.ShowWindow(FALSE);
		m_MFCPropertyGridThreeG.ShowWindow(FALSE);
		m_MpduInfoList.ShowWindow(TRUE);
		m_MPDUAdd.ShowWindow(TRUE);
		m_MPDUDelete.ShowWindow(TRUE);
		break;
	case OneNL:
		m_MFCPropertyGridThree.ShowWindow(FALSE);
		m_MFCPropertyGridThreeN.ShowWindow(FALSE);
		m_MFCPropertyGridThreeB.ShowWindow(FALSE);
		m_MFCPropertyGridThreeNL.ShowWindow(TRUE);
		m_MFCPropertyGridThreeG.ShowWindow(FALSE);
		m_MpduInfoList.ShowWindow(FALSE);
		m_MPDUAdd.ShowWindow(FALSE);
		m_MPDUDelete.ShowWindow(FALSE);
		break;
	}
}
void CTabProtocolConfig::Point(){
	data_and_graph* m_pass_to_thread =&(((CMainFrame*)AfxGetMainWnd())->m_pass_to_thread);
	m_configAIndex = m_pass_to_thread->m_configAIndex;
	m_configBIndex = m_pass_to_thread->m_configBIndex;
	m_configGIndex = m_pass_to_thread->m_configGIndex;
	m_configNIndex = m_pass_to_thread->m_configNIndex;
}
BOOL CMFCPropertyGridPropertyButton::HasButton() const{
	return TRUE;
}
void CMFCPropertyGridPropertyButton::OnClickButton(CPoint point){
	CString FilePathName;
	CFileDialog dlg(TRUE,NULL, NULL,OFN_FORCESHOWHIDDEN,
		(LPCTSTR)_TEXT("txt files (*.txt)|*.txt||"),NULL);
	if(dlg.DoModal()==IDOK)
	{
		FilePathName=dlg.GetPathName(); //�ļ�����������FilePathName��
		CStdioFile m_file(FilePathName,CFile::modeRead);  
		CString contents;
		int protocol = ((CMainFrame*)AfxGetMainWnd())->m_pass_to_thread.m_configIndex->ProtocolModel;
		((CTabParent*)((CMainFrame*)AfxGetMainWnd())->m_mainSplitter.GetPane(0,0))->m_tabProtocolConfig.filter_user->SetValue(FilePathName);
		((CMainFrame*)AfxGetMainWnd())->m_pass_to_thread.m_configAIndex->filter_para.filepath =FilePathName;
		switch(protocol)
		{
		case OneA:
			{
				vector<double> &filter = ((CMainFrame*)AfxGetMainWnd())->m_pass_to_thread.m_configAIndex->filter_user;
				while (m_file.ReadString(contents))  
				{  
					double temp = 0.0;  
					temp=atof(contents);  
					filter.push_back(temp);
				}   
				break;
			}
		case OneB:
			{
				vector<double> &filter = ((CMainFrame*)AfxGetMainWnd())->m_pass_to_thread.m_configBIndex->filter_user;
				while (m_file.ReadString(contents))  
				{  
					double temp = 0.0;  
					temp=atof(contents);  
					filter.push_back(temp);
				}   
				break;
			}
		case OneG:
			{
				vector<double> &filter = ((CMainFrame*)AfxGetMainWnd())->m_pass_to_thread.m_configGIndex->filter_user;
				while (m_file.ReadString(contents))  
				{  
					double temp = 0.0;  
					temp=atof(contents);  
					filter.push_back(temp);
				}   
				break;
			}
		case OneNL:
		case OneN:
			{
				vector<double> &filter = ((CMainFrame*)AfxGetMainWnd())->m_pass_to_thread.m_configNIndex->filter_user;
				while (m_file.ReadString(contents))  
				{  
					double temp = 0.0;  
					temp=atof(contents);  
					filter.push_back(temp);
				}   
				break;
			}
		}
		m_file.Close(); 
	}

}
// CTabProtocolConfig �Ի���

BOOL CMFCPropertyGridPropertyButton2::HasButton() const{
	return TRUE;
}
void CMFCPropertyGridPropertyButton2::OnClickButton(CPoint point){
	CString FilePathName;
	CFileDialog dlg(TRUE,NULL, NULL,OFN_FORCESHOWHIDDEN,
		(LPCTSTR)_TEXT("txt files (*.txt)|*.txt||"),NULL);
	if(dlg.DoModal()==IDOK)
	{
		FilePathName=dlg.GetPathName(); //�ļ�����������FilePathName��
		((CMainFrame*)AfxGetMainWnd())->m_pass_to_thread.m_configAIndex->filepath = FilePathName;
		((CTabParent*)((CMainFrame*)AfxGetMainWnd())->m_mainSplitter.GetPane(0,0))->m_tabProtocolConfig.p_data_filepath->SetValue(FilePathName);
	}
}
void CTabProtocolConfig::OnBnClickedMpdudelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION pos=m_MpduInfoList.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		AfxMessageBox(_T("��ѡ���б��е�<MPDU>��Ŀ"));
		return;
	}else
	{
		int nItem = m_MpduInfoList.GetNextSelectedItem(pos);
		if (nItem == 0)
			return;
		else
		{
			NumOfMPDU -= 1;
			m_MpduInfoList.DeleteItem(nItem);
			vector<MpduPara>::iterator iter = m_configNIndex->mpdus.begin();
			m_configNIndex->mpdus.erase(iter+nItem);
	        int activeItem = m_MpduInfoList.GetItemCount();
			CString str;
			for (int i = 0;i<activeItem;i++){
				str.Format("Mpdu %d",i);
				m_MpduInfoList.SetItemText(i,0,str);
			}
		}
	}
}
void CTabProtocolConfig::OnBnClickedMpduadd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NumOfMPDU+=1;
	//MpduPara* Para_mpdu;
	//Para_mpdu->numOFmpdus+=1;
	m_configNIndex->num_of_mpdus+=1;
	int nrow;
	CString Mpdus;
	Mpdus.Format("Mpdu %d",NumOfMPDU);
	nrow = m_MpduInfoList.InsertItem(NumOfMPDU+1,Mpdus);
	m_MpduInfoList.SetItemText(nrow,1,"PN9");
	m_MpduInfoList.SetItemText(nrow,2,"1024Byte(s)");
	m_MpduInfoList.SetItemText(nrow,3,"On");
	m_MpduInfoList.SetItemText(nrow,4,"On");
	m_MpduInfoList.SetItemText(nrow,5,"1058Byte(s)");
	m_MpduInfoList.SetItemText(nrow,6,"1062Byte(s)");
	MpduPara mpdu;
	m_configNIndex->mpdus.push_back(mpdu);
	
}
void CTabProtocolConfig::OnDblclkListMpdu(NMHDR *pNMHDR, LRESULT *pResult){
	m_mpdu_general = new CMPDUGeneral();
	//��ǰѡ�е�MPDU
	POSITION pos=m_MpduInfoList.GetFirstSelectedItemPosition();
	int nItem = m_MpduInfoList.GetNextSelectedItem(pos);
	m_mpdu_general->Index = nItem;
	m_mpdu_general->DoModal();
	delete m_mpdu_general;
}