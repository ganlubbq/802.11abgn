// TabProtocolConfig.cpp : 实现文件
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
	m_font.CreatePointFont(100,"微软雅黑");
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


// CTabProtocolConfig 消息处理程序


void CTabProtocolConfig::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}


BOOL CTabProtocolConfig::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//有关协议配置的指针传递到配置协议类
	//p_bluetoothparams = ((CMainFrame*)AfxGetMainWnd())->m_pass_to_thread.p_protocol_params;

	CRect rc;
	GetClientRect(&rc);
	//rc.bottom += 20;
	rc.left += 10;
	//rc.right += 10;
	rc.top += 10;

	//11a协议
	m_MFCPropertyGridThree.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP| WS_BORDER,rc,this,2003);
	m_MFCPropertyGridThree.EnableHeaderCtrl(FALSE,_T("参数"),_T("值"));
	m_MFCPropertyGridThree.EnableDescriptionArea();
	m_MFCPropertyGridThree.SetDescriptionRows(5);
	m_MFCPropertyGridThree.SetVSDotNetLook();
	m_MFCPropertyGridThree.MarkModifiedProperties();
	m_MFCPropertyGridThree.SetAlphabeticMode(false); 
	m_MFCPropertyGridThree.SetShowDragContext();

	pGroup31 = new CMFCPropertyGridProperty(_T("载波信息"),MFCPROPERTYTO);
	pGroup32 = new CMFCPropertyGridProperty(_T("调制编码"),MFCPROPERTYTO);
	pGroup33 = new CMFCPropertyGridProperty(_T("载荷配置"),MFCPROPERTYTO);
	pGroup34 = new CMFCPropertyGridProperty(_T("频谱控制"),MFCPROPERTYTO);
	pGroup35 = new CMFCPropertyGridProperty(_T("信道"));

	/*CMFCPropertyGridProperty **/pPropT1 = new CMFCPropertyGridProperty(_T("协议"),_T("IEEE 802.11a"),_T("IEEE 802.11系列之一：11a/b/g/n"),MFCPROPERTYTOO);
	pPropT1->Enable(FALSE);
	pGroup31->AddSubItem(pPropT1);
	/*CMFCPropertyGridProperty **/pPropT2 = new CMFCPropertyGridProperty(_T("帧数"),_T("20"),_T("设置数据帧的数目"),MFCPROPERTYTOS);
	//pPropT2->Enable(FALSE);
	pGroup31->AddSubItem(pPropT2);
	/*CMFCPropertyGridProperty **/pPropT3 = new CMFCPropertyGridProperty(_T("频率偏移"),_T("+0.000000 Hz"),_T("设置频率偏移"),MFCPROPERTYTOFR);
	//pPropT3->Enable(FALSE);
	pGroup31->AddSubItem(pPropT3);
	pPropT3a=new CMFCPropertyGridProperty(_T("空闲时间间隔"),_T("10.0"),_T("设置空闲时间间隔，单位μs"),MFCPROPERTYTOT);
	pGroup31->AddSubItem(pPropT3a);
	pGroup31->AddSubItem(new CMFCPropertyGridProperty(_T("相对功率"),_T("0.000 dB"),_T("设置相对功率大小"),MFCPROPERTYTOFE));

	/*CMFCPropertyGridProperty* */pPropT4 = new CMFCPropertyGridProperty(_T("速率"),_T("6 Mbps"),_T("设置数据速率之一：6、9、12、18、24、36、48、54 Mbps"),MFCPROPERTYTSO);
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
	
	/*CMFCPropertyGridProperty **/pPropT6 = new CMFCPropertyGridProperty(_T("编码方式"),_T("卷积编码"),_T("关于编码方式的说明"),MFCPROPERTYTST);
	pPropT6->Enable(FALSE);
	pGroup32->AddSubItem(pPropT6);
	/*CMFCPropertyGridProperty **/pPropT7 = new CMFCPropertyGridProperty(_T("码率"),_T("1/2"),_T("当前速率下的编码速率"),MFCPROPERTYTSFR);
	pPropT7->Enable(FALSE);
	pGroup32->AddSubItem(pPropT7);
	/*CMFCPropertyGridProperty **/pPropT5 = new CMFCPropertyGridProperty(_T("调制方式"),_T("BPSK"),_T("当前速率下的调制方式"),MFCPROPERTYTSSD);
	pPropT5->Enable(FALSE);
	pPropT5->SetData(100);
	pGroup32->AddSubItem(pPropT5);
	///*CMFCPropertyGridProperty**/ pPropT8 = new CMFCPropertyGridProperty(_T("交织"),_T("On"),_T("设置交织的状态：On/Off"),MFCPROPERTYTSFE);
	//pPropT8->AddOption(_T("On"));  
	//pPropT8->AddOption(_T("Off")); 
	//pPropT8->AllowEdit(FALSE);
	//pGroup32->AddSubItem(pPropT8);

	/*CMFCPropertyGridProperty**/ pPropT9 = new CMFCPropertyGridProperty(_T("OFDM 扰频器"),_T("On"),_T("设置OFDM扰频器的状态：On/Off"),MFCPROPERTYTSSX);
	pPropT9->AddOption(_T("On"));  
	pPropT9->AddOption(_T("Off")); 
	pPropT9->AllowEdit(FALSE);
	pGroup32->AddSubItem(pPropT9);

	pPropT017 = new CMFCPropertyGridProperty(_T("扰频器初始值"),_T("93"),_T("设置扰频器的值0-127"),MFCPROPERTYTSSE);
	pGroup32->AddSubItem(pPropT017);
	pPropT3b=new CMFCPropertyGridProperty(_T("子载波数"),_T("52"),_T("设置子载波数量"),MFCPROPERTYTSET);
	pGroup32->AddSubItem(pPropT3b);
	pPropT3b->Enable(FALSE);
	/*pGroup33->AddSubItem(new CMFCPropertyGridProperty(_T("数据类型"),_T("PN9"),_T("说明数据类型"),MFCPROPERTYTTO));*/
	p_data_source = new CMFCPropertyGridProperty("数据源","PN9","选择数据源的类型",MFCPROPERTYTTO);
	p_data_source->AddOption("PN9");
	p_data_source->AddOption("PN15");
	p_data_source->AddOption("ALL0");
	p_data_source->AddOption("从文件读取");
	p_data_source->AllowEdit(FALSE);
	pGroup33->AddSubItem(p_data_source);

	p_data_filepath = new CMFCPropertyGridPropertyButton2("文件路径","","选择数据源文件所在的路径",MFCPROPERTYTTS);
	p_data_filepath->Show(FALSE);
	pGroup33->AddSubItem(p_data_filepath);

	p_date_max_len = new CMFCPropertyGridProperty("负载长度","80","设置负载的长度（单位为Byte）",MFCPROPERTYTTT);
	pGroup33->AddSubItem(p_date_max_len);

	/*pPropT10 = new CMFCPropertyGridProperty(_T("PSDU"),_T("2960 symbols"),_T("PSDU的大小"));
	pPropT10->Enable(FALSE);
	pGroup33->AddSubItem(pPropT10);
	pPropT11 = new CMFCPropertyGridProperty(_T("PPDU"),_T("3201 symbols"),_T("PPDU的大小"));
	pPropT11->Enable(FALSE);
	pGroup33->AddSubItem(pPropT11);*/

	/*CMFCPropertyGridProperty **/pPropT12 = new CMFCPropertyGridProperty(_T("MAC头部"),_T("默认"),_T("设置MAC头部"),MFCPROPERTYTTFR);
	pPropT12->AddOption(_T("默认"));  
	pPropT12->AddOption(_T("设置")); 
	pPropT12->AllowEdit(FALSE);
	pGroup33->AddSubItem(pPropT12);
	
	/*CMFCPropertyGridProperty**/ pPropT13 = new CMFCPropertyGridProperty(_T("FCS"),_T("On"),_T("设置MAC FCS的状态：On/Off"),MFCPROPERTYTTFE);
	pPropT13->AddOption(_T("On"));  
	pPropT13->AddOption(_T("Off")); 
	pPropT13->AllowEdit(FALSE);
	pGroup33->AddSubItem(pPropT13);

	pPropT14 = new CMFCPropertyGridProperty(_T("滤波器"),_T("无"),_T("设置滤波器的类型"),MFCPROPERTYTFO);
	pPropT14->AddOption("无");  
	pPropT14->AddOption("高斯滤波器");
	pPropT14->AddOption("根升余弦滤波器");
	pPropT14->AddOption("理想低通滤波器");
	pPropT14->AddOption("用户自定义");
	pGroup34->AddSubItem(pPropT14);
	lp_filter_len = new CMFCPropertyGridProperty("滤波器长度","30","设置低通滤波器长度",LPFILTERLEN);
	lp_filter_len->Show(FALSE);
	pGroup34->AddSubItem(lp_filter_len);
	lp_filter_wn = new CMFCPropertyGridProperty("滤波器通带","0.24","设置滤波器通带 Wn",LPFILTERWN);
	lp_filter_wn->Show(FALSE);
	pGroup34->AddSubItem(lp_filter_wn);

	gauss_filter_len = new CMFCPropertyGridProperty("滤波器长度","30","设置低通滤波器长度",GAUSSFILTERLEN);
	gauss_filter_len->Show(FALSE);
	pGroup34->AddSubItem(gauss_filter_len);
	gauss_filter_BT = new CMFCPropertyGridProperty("BT","0.5","设置滤波器通带 BT",GAUSSFILTERBT);
	gauss_filter_BT->Show(FALSE);
	pGroup34->AddSubItem(gauss_filter_BT);

	cosine_filter_len = new CMFCPropertyGridProperty("滤波器长度","30","设置低通滤波器长度",COSINEFILTERLEN);
	cosine_filter_len->Show(FALSE);
	pGroup34->AddSubItem(cosine_filter_len);
	cosine_filter_alpha = new CMFCPropertyGridProperty("alpha","0.24","设置滤波器alpha",COSINEFILTERALPHA);
	cosine_filter_alpha->Show(FALSE);
	pGroup34->AddSubItem(cosine_filter_alpha);
	filter_user = new CMFCPropertyGridPropertyButton("滤波器系数","","允许用户自定义滤波器系数",FILTERUSERDEFINE);
	filter_user->Show(FALSE);
	pGroup34->AddSubItem(filter_user);
	pPropT15 = new CMFCPropertyGridProperty(_T("窗口长度"),_T("8"),_T("设置滤波器窗口的长度，窗口长度不能超过一个OFDM符号的长度"),MFCPROPERTYTFS);
	pGroup34->AddSubItem(pPropT15);

	/*CMFCPropertyGridProperty *pPropT16 = new CMFCPropertyGridProperty(_T("信道模型"),_T("无"),_T("无/设置信道模型的类型"),MFCPROPERTYTTNS);
	pPropT16->AddOption(_T("无"));  
	pPropT16->AddOption(_T("选择")); 
	pPropT16->AllowEdit(FALSE);
	pGroup35->AddSubItem(pPropT16);*/

	pPropT16 = new CMFCPropertyGridProperty(_T("信道状态"),_T("off"),_T("设置信道状态：信号是否经过信道"),PPROPCHANNEL4);
	pPropT16->AddOption("on");
	pPropT16->AddOption("off");
	pGroup35->AddSubItem(pPropT16);

	pPropT17 = new CMFCPropertyGridProperty(_T("信道多径数"),_T("4"),_T("设置多径信道中多径数"),PPROPCHANNEL1);
	pGroup35->AddSubItem(pPropT17);
	
	pPropT18 = new CMFCPropertyGridProperty(_T("信号载频"),_T("2.412"),_T("信道载频设置，单位 GHz"),PPROPCHANNEL2);
	pGroup35->AddSubItem(pPropT18);
	
	pPropT19 = new CMFCPropertyGridProperty(_T("移动速度"),_T("30"),_T("移动速度设置，单位 km/h"),PPROPCHANNEL3);
	pGroup35->AddSubItem(pPropT19);

	///*CMFCPropertyGridProperty* */pPropT20 = new CMFCPropertyGridProperty(_T("Eb/N0"),_T("0.00 dB"),_T("设置SINR的值大小"),PPROPCHANNEL4);
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
	
	//11n协议
	m_MFCPropertyGridThreeN.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP| WS_BORDER,rc,this,2004);
	m_MFCPropertyGridThreeN.EnableHeaderCtrl(FALSE,_T("参数"),_T("值"));
	m_MFCPropertyGridThreeN.SetVSDotNetLook();
	m_MFCPropertyGridThreeN.MarkModifiedProperties();
	m_MFCPropertyGridThreeN.SetAlphabeticMode(false); 
	m_MFCPropertyGridThreeN.SetShowDragContext();

	//pGroup36 = new CMFCPropertyGridProperty(_T("1.模式选择"));
	pGroup37 = new CMFCPropertyGridProperty(_T("数据包"));
	pGroup38 = new CMFCPropertyGridProperty(_T("调制编码"));
	pGroup39 = new CMFCPropertyGridProperty(_T("载荷配置"));
	pGroup40 = new CMFCPropertyGridProperty(_T("频谱控制"));
	pGroup41 = new CMFCPropertyGridProperty(_T("信道"));

	pPropT21 = new CMFCPropertyGridProperty(_T("类型"),_T("0"),_T("取值为0或1，0表示数据包（PPDU），1表示空数据包，默认为0"),MFCPROPERTYOFIN);  
	pPropT21->AddOption(_T("0"));  
	pPropT21->AddOption(_T("1"));
	pGroup37->AddSubItem(pPropT21);
	pPropT211 = new CMFCPropertyGridProperty(_T("数据个数"),_T("20"),_T("设置数据包个数"),MFCPROPERTYOFINN);
	pGroup37->AddSubItem(pPropT211);
	pPropT22 = new CMFCPropertyGridProperty(_T("MCS索引号"),_T("10"),_T("取值为0-76，默认10"),MFCPROPERTYOSIN);  
	//pPropT22->AddOption(_T("1"));  
	//pPropT22->AddOption(_T("..."));
	pGroup38->AddSubItem(pPropT22);

	pPropT23a = new CMFCPropertyGridProperty(_T("  调制方式流1"),_T("QPSK"),_T("根据索引号取值"));
	pPropT23a->Enable(FALSE);
	pGroup38->AddSubItem(pPropT23a);
	pPropT23b = new CMFCPropertyGridProperty(_T("  调制方式流2"),_T("QPSK"),_T("根据索引号取值"));
	pPropT23b->Enable(FALSE);
	pPropT23b->Show(FALSE);
	pGroup38->AddSubItem(pPropT23b);
	pPropT23c = new CMFCPropertyGridProperty(_T("  调制方式流3"),_T("QPSK"),_T("根据索引号取值"));
	pPropT23c->Enable(FALSE);
	pPropT23c->Show(FALSE);
	pGroup38->AddSubItem(pPropT23c);
	pPropT23d = new CMFCPropertyGridProperty(_T("  调制方式流4"),_T("QPSK"),_T("根据索引号取值"));
	pPropT23d->Enable(FALSE);
	pPropT23d->Show(FALSE);
	pGroup38->AddSubItem(pPropT23d);

	pPropT24 = new CMFCPropertyGridProperty(_T("码率"),_T("3/4"),_T("根据索引号取值"));  
	pPropT24->Enable(FALSE);
	pGroup38->AddSubItem(pPropT24);
	pPropT25 = new CMFCPropertyGridProperty(_T("数据速率"),_T("39.0Mbps"),_T("根据索引号取值"));  
	pPropT25->Enable(FALSE);
	pGroup38->AddSubItem(pPropT25);
	pPropT25a = new CMFCPropertyGridProperty(_T("空间流数(Nss)"),_T("2"),_T("根据索引号取值"));  
	pPropT25a->Enable(FALSE);
	pGroup38->AddSubItem(pPropT25a);
	pPropT25c = new CMFCPropertyGridProperty(_T("空时流数(Nsts)"),_T("2"),_T("Nss为1,Nsts取值1-2;Nss为2,Nsts取值2-4;Nss为3,Nsts取值3-4"),MFCPROPERTYOFINN1); 
	//pPropT25b->Enable(FALSE);
	pGroup38->AddSubItem(pPropT25c);
	pPropT25b = new CMFCPropertyGridProperty(_T("空时编码(STBC)"),_T("0"),_T("根据Nss,Nsts取值,为Nsts-Nss"),MFCPROPERTYOFINN2); 
	pPropT25b->Enable(FALSE);
	pGroup38->AddSubItem(pPropT25b);
	/*pPropT26 = new CMFCPropertyGridProperty(_T("传输天线数目"),_T("1"),_T("取值为1-4，默认1"),MFCPROPERTYOSEN);  
	pPropT26->AddOption(_T("1"));  
	pPropT26->AddOption(_T("2"));
	pPropT26->AddOption(_T("3"));  
	pPropT26->AddOption(_T("4"));
	pGroup38->AddSubItem(pPropT26);*/
	pPropT25d = new CMFCPropertyGridProperty(_T("Ness"),_T("0"),_T("Ness与Nsts的和小于等于天线数,Ness决定Neltf的个数:Ness为0,Neltf取值0;Ness为1,Neltf取值1;Ness为2,Neltf取值2;Ness为3,Neltf取值4"),MFCPROPERTYOFINN3); 
	//pPropT25b->Enable(FALSE);
	pGroup38->AddSubItem(pPropT25d);
	pPropT28 = new CMFCPropertyGridProperty(_T("保护间隔"),_T("Off"),_T("Off表示常规保护间隔，On表示短保护间隔。默认为关."),MFCPROPERTYOEIN);  
	pPropT28->AddOption(_T("On"));  
	pPropT28->AddOption(_T("Off"));
	pGroup38->AddSubItem(pPropT28);
	pPropT288 = new CMFCPropertyGridProperty(_T("时域加窗"),_T("Off"),_T("On:表示加窗，Off:表示无加窗。默认为Off."),MFCPROPERTYOEINN);  
	pPropT288->AddOption(_T("On"));  
	pPropT288->AddOption(_T("Off"));
	pGroup38->AddSubItem(pPropT288);
	/*pPropT29 = new CMFCPropertyGridProperty(_T("波束赋形"),_T("Off"),_T("On:表示有波束赋形，Off:表示无波束赋形。默认为Off."),MFCPROPERTYOEIN);  
	pPropT29->AddOption(_T("On"));  
	pPropT29->AddOption(_T("Off"));
	pGroup38->AddSubItem(pPropT29);*/
	pPropT30 = new CMFCPropertyGridProperty(_T("空间映射机制"),_T("直接映射"),_T("空间映射机制：直接映射和空间扩展"),MFCPROPERTYONIN);  
	pPropT30->AddOption(_T("直接映射"));  
	pPropT30->AddOption(_T("空间扩展"));  
	//pPropT30->AddOption(_T("2"));
	//pPropT30->AddOption(_T("4"));  
	//pPropT30->AddOption(_T("5"));
	pGroup38->AddSubItem(pPropT30);
	pPropT31 = new CMFCPropertyGridProperty(_T("信道编码"),_T("BCC"),_T("BCC表示‘0’，LDPC表示‘1’，默认为0"),MFCPROPERTYS0N);
	pPropT31->AddOption(_T("LDPC"));  
	pPropT31->AddOption(_T("BCC"));
	pGroup38->AddSubItem(pPropT31);
	pPropT32 = new CMFCPropertyGridProperty(_T("交织"),_T("On"),_T("BCC方式，可选择开与关；LDPC方式下，关，不可编辑"),MFCPROPERTYSSN);
	pPropT32->AddOption(_T("On"));  
	pPropT32->AddOption(_T("Off"));
	pGroup38->AddSubItem(pPropT32);
	pPropT32a = new CMFCPropertyGridProperty(_T("扰码器"),_T("On"),_T("Off表示‘关’，On表示‘开’，默认为On"),MFCPROPERTYSSN1);
	pPropT32a->AddOption(_T("On"));  
	pPropT32a->AddOption(_T("Off"));
	pGroup38->AddSubItem(pPropT32a);
	
	pPropT27 = new CMFCPropertyGridProperty(_T("扰码初始值"),_T("93"),_T("扰码初始值设置，范围0-127"),MFCPROPERTYSSNN);  
	pGroup38->AddSubItem(pPropT27);
	pPropT33 = new CMFCPropertyGridProperty(_T("聚合MPDU"),_T("off"),_T("Off表示‘关’，On表示‘开’，默认为off"),MFCPROPERTYSTN);
	pPropT33->AddOption(_T("on"));  
	pPropT33->AddOption(_T("off"));
	pGroup39->AddSubItem(pPropT33);
	pPropT34 = new CMFCPropertyGridProperty(_T("Smoothing"),_T("Off"),_T("off表示‘关’，on表示‘开’，默认为off"),MFCPROPERTYSFN);
	pPropT34->AddOption(_T("on"));  
	pPropT34->AddOption(_T("off"));
	pGroup39->AddSubItem(pPropT34);
	pPropT35 = new CMFCPropertyGridProperty(_T("Sounding"),_T("Off"),_T("off表示‘关’，on表示‘开’，默认为off"),MFCPROPERTYSFIN);
	pPropT35->AddOption(_T("on"));  
	pPropT35->AddOption(_T("off"));
	pGroup39->AddSubItem(pPropT35);

	pPropT36 = new CMFCPropertyGridProperty("数据源","PN9","选择数据源的类型",MFCPROPERTYSSIN);
	pPropT36->AddOption("PN9");
	pPropT36->AddOption("PN15");
	pPropT36->AddOption("ALL0");
	pPropT36->AddOption("从文件读取");
	pPropT36->AllowEdit(FALSE);
	pGroup39->AddSubItem(pPropT36);

	
	pPropT37 = new CMFCPropertyGridProperty(_T("数据长度"),_T("80"),_T("默认1-1000的十进制数字，用户输入."),MFCPROPERTYSSEN);
	pGroup39->AddSubItem(pPropT37);
	p_data_filepath_n = new CMFCPropertyGridProperty("文件路径","","选择数据源文件所在的路径",NFILEPATH);
	p_data_filepath_n->Show(FALSE);
	pGroup39->AddSubItem(p_data_filepath_n);
	//设置滤波器
	fitertype_n = new CMFCPropertyGridProperty(_T("滤波器"),_T("无"),_T("设置滤波器的类型"),NMFCPROPERTYTFO);
	fitertype_n->AddOption("无");  
	fitertype_n->AddOption("高斯滤波器");
	fitertype_n->AddOption("根升余弦滤波器");
	fitertype_n->AddOption("理想低通滤波器");
	fitertype_n->AddOption("用户自定义");
	pGroup40->AddSubItem(fitertype_n);
	lp_filter_len_n = new CMFCPropertyGridProperty("滤波器长度","30","设置低通滤波器长度",NLPFILTERLEN);
	lp_filter_len_n->Show(FALSE);
	pGroup40->AddSubItem(lp_filter_len_n);
	lp_filter_wn_n = new CMFCPropertyGridProperty("滤波器通带","0.24","设置滤波器通带 Wn",NLPFILTERWN);
	lp_filter_wn_n->Show(FALSE);
	pGroup40->AddSubItem(lp_filter_wn_n);

	gauss_filter_len_n = new CMFCPropertyGridProperty("滤波器长度","30","设置低通滤波器长度",NGAUSSFILTERLEN);
	gauss_filter_len_n->Show(FALSE);
	pGroup40->AddSubItem(gauss_filter_len_n);
	gauss_filter_BT_n = new CMFCPropertyGridProperty("BT","0.5","设置滤波器通带 BT",NGAUSSFILTERBT);
	gauss_filter_BT_n->Show(FALSE);
	pGroup40->AddSubItem(gauss_filter_BT_n);

	cosine_filter_len_n = new CMFCPropertyGridProperty("滤波器长度","30","设置低通滤波器长度",NCOSINEFILTERLEN);
	cosine_filter_len_n->Show(FALSE);
	pGroup40->AddSubItem(cosine_filter_len_n);
	cosine_filter_alpha_n = new CMFCPropertyGridProperty("alpha","0.24","设置滤波器alpha",NCOSINEFILTERALPHA);
	cosine_filter_alpha_n->Show(FALSE);
	pGroup40->AddSubItem(cosine_filter_alpha_n);
	filter_user_n = new CMFCPropertyGridPropertyButton("滤波器系数","","允许用户自定义滤波器系数",NFILTERUSERDEFINE);
	filter_user_n->Show(FALSE);
	pGroup40->AddSubItem(filter_user_n);
	pPropT38 = new CMFCPropertyGridProperty(_T("时域加窗"),_T("1"),_T("‘0’表示不加窗，‘1’表示加窗"),MFCPROPERTYOFN);  
	pPropT38->AddOption(_T("0"));  
	pPropT38->AddOption(_T("1"));
	pGroup40->AddSubItem(pPropT38);

	pPropT39 = new CMFCPropertyGridProperty(_T("信道状态"),_T("off"),_T("‘关’或‘开’，默认为关"),MFCPROPERTYSEIN);
	pPropT39->AddOption(_T("on"));  
	pPropT39->AddOption(_T("off"));
	pGroup41->AddSubItem(pPropT39);
	pPropT40 = new CMFCPropertyGridProperty(_T("信道类型"),_T("A"),_T("A、B、C、D、E、F对应不同的应用场景"),CHANNELTYPE);
	pPropT40->AddOption(_T("A"));  
	pPropT40->AddOption(_T("B"));
	pPropT40->AddOption(_T("C"));  
	pPropT40->AddOption(_T("D"));
	pPropT40->AddOption(_T("E"));  
	pPropT40->AddOption(_T("F"));
	pGroup41->AddSubItem(pPropT40);

	numofNt = new CMFCPropertyGridProperty("发端天线数","1","设置发端天线的数目",NUMOFTXANNEA);
	pGroup41->AddSubItem(numofNt);
	numofNr = new CMFCPropertyGridProperty("收端天线数","1","设置收端天线的数目",NUMOFRXANNEA);
	pGroup41->AddSubItem(numofNr);
	pPropT41 = new CMFCPropertyGridProperty(_T("移动速度"),_T("30"),_T("移动速度：单位km/h"),MFCPROPERTYTON);
	pGroup41->AddSubItem(pPropT41);
	pPropT42 = new CMFCPropertyGridProperty(_T("载波频率"),_T("2.412"),_T("载波频率：单位GHz"),MFCPROPERTYTSN);
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
	
	//11n协议Legacy模式
	m_MFCPropertyGridThreeNL.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP /*| WS_BORDER*/,rc,this,2005);
	m_MFCPropertyGridThreeNL.EnableHeaderCtrl(FALSE,_T("参数"),_T("值"));
	m_MFCPropertyGridThreeNL.EnableDescriptionArea();
	m_MFCPropertyGridThreeNL.SetVSDotNetLook();
	m_MFCPropertyGridThreeNL.MarkModifiedProperties();
	m_MFCPropertyGridThreeNL.SetAlphabeticMode(false); 
	m_MFCPropertyGridThreeNL.SetShowDragContext();

	pGroup47 = new CMFCPropertyGridProperty(_T("调制编码"));
	pGroup48 = new CMFCPropertyGridProperty(_T("载荷配置"));
	pGroup49 = new CMFCPropertyGridProperty(_T("频谱控制"));
	pGroup50 = new CMFCPropertyGridProperty(_T("信道"));


	pPropT44 = new CMFCPropertyGridProperty(_T("数据速率"),_T("6 Mbps"),_T("选择数据速率"),MFCPROPERTYOSIN);  
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
	pPropT45 = new CMFCPropertyGridProperty(_T("调制方式"),_T("BPSK"),_T("根据索引号取值"));
	pPropT45->Enable(FALSE);
	pGroup47->AddSubItem(pPropT45);
	pPropT46 = new CMFCPropertyGridProperty(_T("码率"),_T("1/2"),_T("根据索引号取值"));  
	pPropT46->Enable(FALSE);
	pGroup47->AddSubItem(pPropT46);
	pPropT47 = new CMFCPropertyGridProperty(_T("扰码器"),_T("On"),_T("扰码器开关"),MFCPROPERTYOSENL1);  
	pPropT47->Enable(FALSE);
	pGroup47->AddSubItem(pPropT47);
	pPropT48 = new CMFCPropertyGridProperty(_T("扰码初始值"),_T("93"),_T("取值0-127，默认93.数值由用户输入"),MFCPROPERTYOSENL);  
	pGroup47->AddSubItem(pPropT48);
	pPropT49 = new CMFCPropertyGridProperty(_T("信道编码"),_T("BCC"),_T("信道编码方式：BCC，不可编辑"));  
	pPropT49->Enable(FALSE);
	pGroup47->AddSubItem(pPropT49);
	pPropT50 = new CMFCPropertyGridProperty(_T("交织"),_T("On"),_T("默认为开"),MFCPROPERTYOEINL);  
	pPropT50->Enable(FALSE);
	pGroup47->AddSubItem(pPropT50);
	/*pPropT56 = new CMFCPropertyGridProperty(_T("时域加窗"),_T("off"),_T("‘off’表示不加窗，‘on’表示加窗"),MFCPROPERTYOFL);  
	pPropT56->AddOption(_T("on"));  
	pPropT56->AddOption(_T("off"));
	pGroup47->AddSubItem(pPropT56);*/
	/*pPropT51 = new CMFCPropertyGridProperty(_T("聚合MPDU"),_T("off"),_T("off表示‘关’，on表示‘开’，默认为0"),MFCPROPERTYSTL);
	pPropT51->AddOption(_T("on"));  
	pPropT51->AddOption(_T("off"));
	pGroup48->AddSubItem(pPropT51);*/
	pPropT52 = new CMFCPropertyGridProperty(_T("Smoothing"),_T("off"),_T("off表示‘关’，on表示‘开’，默认为0"),MFCPROPERTYSFL);
	pPropT52->AddOption(_T("on"));  
	pPropT52->AddOption(_T("off"));
	pGroup48->AddSubItem(pPropT52);
	pPropT53 = new CMFCPropertyGridProperty(_T("Not Sounding"),_T("off"),_T("off表示‘关’，on表示‘开’，默认为0"),MFCPROPERTYSFIL);
	pPropT53->AddOption(_T("on"));  
	pPropT53->AddOption(_T("off"));
	pGroup48->AddSubItem(pPropT53);
	

	/*pPropT54 = new CMFCPropertyGridProperty(_T("数据长度"),_T("--"),_T("1-65535，用户输入."),MFCPROPERTYSSIL);
	pGroup48->AddSubItem(pPropT54);
	pPropT55 = new CMFCPropertyGridProperty(_T("数据"),_T("--"),_T("默认1-1000的十进制数字，用户输入."),MFCPROPERTYSSEL);
	pGroup48->AddSubItem(pPropT55);*/

	//数据源控件
	pPropT54 = new CMFCPropertyGridProperty("数据源","PN9","选择数据源的类型",NLDATASOURCE);
	pPropT54->AddOption("PN9");
	pPropT54->AddOption("PN15");
	pPropT54->AddOption("ALL0");
	pPropT54->AddOption("从文件读取");
	pPropT54->AllowEdit(FALSE);
	pGroup48->AddSubItem(pPropT54);


	p_data_filepath_nl = new CMFCPropertyGridPropertyButton2("文件路径","","选择数据源文件所在的路径",MFCPROPERTYOFL);
	p_data_filepath_nl->Show(FALSE);
	pGroup48->AddSubItem(p_data_filepath_nl);

	pPropT55 = new CMFCPropertyGridProperty(_T("数据长度"),_T("80"),_T("默认1-1000的十进制数字，用户输入."),MFCPROPERTYSSEL);
	pGroup48->AddSubItem(pPropT55);

	
	
	fitertype_nl = new CMFCPropertyGridProperty(_T("滤波器"),_T("无"),_T("设置滤波器的类型"),NLMFCPROPERTYTFO);
	fitertype_nl->AddOption("无");  
	fitertype_nl->AddOption("高斯滤波器");
	fitertype_nl->AddOption("根升余弦滤波器");
	fitertype_nl->AddOption("理想低通滤波器");
	fitertype_nl->AddOption("用户自定义");
	pGroup49->AddSubItem(fitertype_nl);
	lp_filter_len_nl = new CMFCPropertyGridProperty("滤波器长度","30","设置低通滤波器长度",NLLPFILTERLEN);
	lp_filter_len_nl->Show(FALSE);
	pGroup49->AddSubItem(lp_filter_len_nl);
	lp_filter_wn_nl = new CMFCPropertyGridProperty("滤波器通带","0.24","设置滤波器通带 Wn",NLLPFILTERWN);
	lp_filter_wn_nl->Show(FALSE);
	pGroup49->AddSubItem(lp_filter_wn_nl);

	gauss_filter_len_nl = new CMFCPropertyGridProperty("滤波器长度","30","设置低通滤波器长度",NLGAUSSFILTERLEN);
	gauss_filter_len_nl->Show(FALSE);
	pGroup49->AddSubItem(gauss_filter_len_nl);
	gauss_filter_BT_nl = new CMFCPropertyGridProperty("BT","0.5","设置滤波器通带 BT",NLGAUSSFILTERBT);
	gauss_filter_BT_nl->Show(FALSE);
	pGroup49->AddSubItem(gauss_filter_BT_nl);

	cosine_filter_len_nl = new CMFCPropertyGridProperty("滤波器长度","30","设置低通滤波器长度",NLCOSINEFILTERLEN);
	cosine_filter_len_nl->Show(FALSE);
	pGroup49->AddSubItem(cosine_filter_len_nl);
	cosine_filter_alpha_nl = new CMFCPropertyGridProperty("alpha","0.24","设置滤波器alpha",NLCOSINEFILTERALPHA);
	cosine_filter_alpha_nl->Show(FALSE);
	pGroup49->AddSubItem(cosine_filter_alpha_nl);
	filter_user_nl = new CMFCPropertyGridPropertyButton("滤波器系数","","允许用户自定义滤波器系数",NLFILTERUSERDEFINE);
	filter_user_nl->Show(FALSE);
	pGroup49->AddSubItem(filter_user_nl);
	pPropT15 = new CMFCPropertyGridProperty(_T("窗口长度"),_T("8"),_T("设置滤波器窗口的长度，窗口长度不能超过一个OFDM符号的长度"),MFCPROPERTYTFS);
	pGroup49->AddSubItem(pPropT15);

	pPropT57 = new CMFCPropertyGridProperty(_T("信道状态"),_T("off"),_T("‘关’或‘开’，默认为关"),CHANNELSTATEL);
	pPropT57->AddOption(_T("on"));  
	pPropT57->AddOption(_T("off"));
	pGroup50->AddSubItem(pPropT57);
	pPropT58 = new CMFCPropertyGridProperty(_T("场景选择"),_T("A"),_T("A、B、C、D、E、F、User Defined"),CHANNELTYPEL);
	pPropT58->AddOption(_T("A"));  
	pPropT58->AddOption(_T("B"));
	pPropT58->AddOption(_T("C"));  
	pPropT58->AddOption(_T("D"));
	pPropT58->AddOption(_T("E"));  
	pPropT58->AddOption(_T("F")); 
	pGroup50->AddSubItem(pPropT58);
	pPropT59 = new CMFCPropertyGridProperty(_T("发端天线数"),_T("1"),_T("发射端天线数目"),NUMOFTXANNEAL);
	pPropT59->AddOption("1");
	pPropT59->AddOption("2");
	pPropT59->AddOption("3");
	pPropT59->AddOption("4");
	pGroup50->AddSubItem(pPropT59);
	pPropT60 = new CMFCPropertyGridProperty(_T("收端天线数"),_T("2"),_T("收端天线的数目"),NUMOFRXANNEAL);
	pPropT60->AddOption("1");
	pPropT60->AddOption("2");
	pPropT60->AddOption("3");
	pPropT60->AddOption("4");
	pGroup50->AddSubItem(pPropT60);
	carrierfreq = new CMFCPropertyGridProperty(_T("信号载频"),_T("2.412"),_T("信号载频 GHz"),CARRIERFREQ);
	pGroup50->AddSubItem(carrierfreq);
	mobilespeed = new CMFCPropertyGridProperty(_T("移动端速度"),_T("30"),_T("移动速度 Km/h"),MOBILESPEEDL);
	pGroup50->AddSubItem(mobilespeed);


	m_MFCPropertyGridThreeNL.AddProperty(pGroup47);
	m_MFCPropertyGridThreeNL.AddProperty(pGroup48);
	m_MFCPropertyGridThreeNL.AddProperty(pGroup49);
	m_MFCPropertyGridThreeNL.AddProperty(pGroup50);

	m_MFCPropertyGridThreeNL.EnableDescriptionArea(TRUE);
	m_MFCPropertyGridThreeNL.SetDescriptionRows(5);
	m_MFCPropertyGridThreeNL.SetCustomColors(RGB(250,250,250),RGB(0,0,0),RGB(230,230,230),RGB(100,100,100),RGB(230,230,230),RGB(0,0,0),RGB(220,220,220));
	m_MFCPropertyGridThreeNL.ShowWindow(FALSE);
	
	//11b协议
	m_MFCPropertyGridThreeB.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP /*| WS_BORDER*/,rc,this,2006);
	m_MFCPropertyGridThreeB.EnableHeaderCtrl(FALSE,_T("参数"),_T("值"));
	m_MFCPropertyGridThreeB.EnableDescriptionArea();
	m_MFCPropertyGridThreeB.SetVSDotNetLook();
	m_MFCPropertyGridThreeB.MarkModifiedProperties();
	m_MFCPropertyGridThreeB.SetAlphabeticMode(false); 
	m_MFCPropertyGridThreeB.SetShowDragContext();

	pGroup42 = new CMFCPropertyGridProperty(_T("载波参数"));
	pGroup43 = new CMFCPropertyGridProperty(_T("调制编码"));
	pGroup44 = new CMFCPropertyGridProperty(_T("载荷配置"));
	pGroup46 =new CMFCPropertyGridProperty("频谱控制");
	pGroup45 = new CMFCPropertyGridProperty(_T("信道"));

	pPropT61 = new CMFCPropertyGridProperty(_T("协议"),_T("IEEE 802.11b"),_T("IEEE 802.11系列之一：11a/b/g/n"));
	pPropT61->Enable(FALSE);
	pGroup42->AddSubItem(pPropT61);
	pPropT62=new CMFCPropertyGridProperty(_T("帧数"),_T("20"),_T("可自行输入，默认20帧"),MFCPROPERTYOOB);
	pGroup42->AddSubItem(pPropT62);
	pPropT63=new CMFCPropertyGridProperty(_T("帧间间隔"),_T("20.0"),_T("可自行输入，单位μs"),MFCPROPERTYOSB);
	pGroup42->AddSubItem(pPropT63);
	pPropT64 = new CMFCPropertyGridProperty(_T("频率偏移"),_T("+0.000000Hz"),_T("可自行输入，默认+0.000000Hz"),MFCPROPERTYOTB);
	pGroup42->AddSubItem(pPropT64);
	pPropT65 = new CMFCPropertyGridProperty(_T("相对功率"),_T("+0.00dB"),_T("可自行输入，载波0默认0.00dB，其他子载波可设置范围+50dB~-10dB，精度0.01dB"),MFCPROPERTYOFB);
	pGroup42->AddSubItem(pPropT65);

	pPropT66 = new CMFCPropertyGridProperty(_T("传输模式"),_T("DSSS"),_T("802.11b协议中采用DSSS传输模式"));
	pPropT66->Enable(FALSE);
	pGroup43->AddSubItem(pPropT66);
	pPropT67 = new CMFCPropertyGridProperty(_T("数据速率"),_T("1 Mbps"),_T("下拉可选 1Mbps、2Mbps、5.5Mbps、11Mbps"),MFCPROPERTYOFIB);
	pPropT67->AddOption(_T("1 Mbps"));  
	pPropT67->AddOption(_T("2 Mbps"));
	pPropT67->AddOption(_T("5.5 Mbps"));  
	pPropT67->AddOption(_T("11 Mbps"));
	pGroup43->AddSubItem(pPropT67);
	pPropT68 = new CMFCPropertyGridProperty(_T("调制方式"),_T("DBPSK"),_T("DBPSK，数据速率为1Mbps；DQPSK，数据速率为2Mbps；CCK/PBCC，数据速率为5.5Mbps或11Mbps"),MFCPROPERTYOSIB);
	pPropT68->AddOption(_T("CCK"));  
	pPropT68->AddOption(_T("PBCC"));
	pPropT68->Enable(FALSE);
	pGroup43->AddSubItem(pPropT68);
	pPropT69 = new CMFCPropertyGridProperty(_T("扰码"),_T("On"),_T("下拉可选On/Off/报头仅有"),MFCPROPERTYOSEB);
	pPropT69->AddOption(_T("On"));  
	pPropT69->AddOption(_T("Off"));
	pPropT69->AddOption(_T("报头仅有"));
	pGroup43->AddSubItem(pPropT69);
	//pPropT690 = new CMFCPropertyGridProperty(_T("扰码初始值"),_T("93"),_T("取值0-127，默认93.数值由用户输入"),MFCPROPERTYOSENL690);  
	//pGroup43->AddSubItem(pPropT690);
	pPropT70 = new CMFCPropertyGridProperty(_T("前导码类型"),_T("长"),_T("默认：长（Long），数据速率为1Mbps；下拉可选: 长/短（Long/Short，数据速率为2/5.5/11Mbps(DSSS)）"),MFCPROPERTYOEIB);
	pPropT70->AddOption(_T("长"));  
	pPropT70->AddOption(_T("短"));
	pPropT70->Enable(FALSE);
	pGroup43->AddSubItem(pPropT70);

	p_data_source_b = new CMFCPropertyGridProperty("数据源","PN9","选择数据源的类型",BDATASOURCE);
	p_data_source_b->AddOption("PN9");
	p_data_source_b->AddOption("PN15");
	p_data_source_b->AddOption("ALL0");
	p_data_source_b->AddOption("从文件读取");
	p_data_source_b->AllowEdit(FALSE);
	pGroup44->AddSubItem(p_data_source_b);

	p_data_filepath_b = new CMFCPropertyGridProperty("文件路径","","选择数据源文件所在的路径",BFILEPATH);
	p_data_filepath_b->Show(FALSE);
	pGroup44->AddSubItem(p_data_filepath_b);

	pPropT72 = new CMFCPropertyGridProperty("负载长度","80","设置负载的长度（单位为Byte）",MFCPROPERTYONIB);
	pGroup44->AddSubItem(pPropT72);
	pPropT73 = new CMFCPropertyGridProperty(_T("MAC头部"),_T("30 Bytes"),_T("默认值"));
	pPropT59->Enable(FALSE);
	pGroup44->AddSubItem(pPropT73);
	pPropT74 = new CMFCPropertyGridProperty(_T("MAC FCS"),_T("4 Bytes"),_T("默认值"));
	pPropT74->Enable(FALSE);
	pGroup44->AddSubItem(pPropT74);

	fitertype = new CMFCPropertyGridProperty(_T("滤波器"),_T("无"),_T("设置滤波器的类型"),BMFCPROPERTYTFO);
	fitertype->AddOption("无");  
	fitertype->AddOption("高斯滤波器");
	fitertype->AddOption("根升余弦滤波器");
	fitertype->AddOption("理想低通滤波器");
	fitertype->AddOption("用户自定义");
	pGroup46->AddSubItem(fitertype);
	lp_filter_len_b = new CMFCPropertyGridProperty("滤波器长度","30","设置低通滤波器长度",BLPFILTERLEN);
	lp_filter_len_b->Show(FALSE);
	pGroup46->AddSubItem(lp_filter_len_b);
	lp_filter_wn_b = new CMFCPropertyGridProperty("滤波器通带","0.24","设置滤波器通带 Wn",BLPFILTERWN);
	lp_filter_wn_b->Show(FALSE);
	pGroup46->AddSubItem(lp_filter_wn_b);

	gauss_filter_len_b = new CMFCPropertyGridProperty("滤波器长度","30","设置低通滤波器长度",BGAUSSFILTERLEN);
	gauss_filter_len_b->Show(FALSE);
	pGroup46->AddSubItem(gauss_filter_len_b);
	gauss_filter_BT_b = new CMFCPropertyGridProperty("BT","0.5","设置滤波器通带 BT",BGAUSSFILTERBT);
	gauss_filter_BT_b->Show(FALSE);
	pGroup46->AddSubItem(gauss_filter_BT_b);

	cosine_filter_len_b = new CMFCPropertyGridProperty("滤波器长度","30","设置低通滤波器长度",BCOSINEFILTERLEN);
	cosine_filter_len_b->Show(FALSE);
	pGroup46->AddSubItem(cosine_filter_len_b);
	cosine_filter_alpha_b = new CMFCPropertyGridProperty("alpha","0.24","设置滤波器alpha",BCOSINEFILTERALPHA);
	cosine_filter_alpha_b->Show(FALSE);
	pGroup46->AddSubItem(cosine_filter_alpha_b);
	filter_user_b = new CMFCPropertyGridPropertyButton("滤波器系数","","允许用户自定义滤波器系数",BFILTERUSERDEFINE);
	filter_user_b->Show(FALSE);
	pGroup46->AddSubItem(filter_user_b);
	pPropT15 = new CMFCPropertyGridProperty(_T("窗口长度"),_T("8"),_T("设置滤波器窗口的长度，窗口长度不能超过一个OFDM符号的长度"),MFCPROPERTYTFS);
	pGroup46->AddSubItem(pPropT15);
	pPropT16_b = new CMFCPropertyGridProperty(_T("信道状态"),_T("off"),_T("设置信道状态：信号是否经过信道"),BPPROPCHANNEL4);
	pPropT16_b->AddOption("on");
	pPropT16_b->AddOption("off");
	pGroup45->AddSubItem(pPropT16_b);

	pPropT17_b = new CMFCPropertyGridProperty(_T("信道多径数"),_T("1"),_T("信道径数1"),BPPROPCHANNEL1);
	pPropT17_b->Enable(FALSE);
	pPropT17_b->SetValue("1");
	//m_configBIndex->NumOfTaps = 1 ;
	pGroup45->AddSubItem(pPropT17_b);

	pPropT18_b = new CMFCPropertyGridProperty(_T("信号载频"),_T("2.412"),_T("信道载频设置，单位 GHz"),BPPROPCHANNEL2);
	pGroup45->AddSubItem(pPropT18_b);

	pPropT19_b = new CMFCPropertyGridProperty(_T("移动速度"),_T("30"),_T("移动速度设置，单位 km/h"),BPPROPCHANNEL3);
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



	//11g协议
	m_MFCPropertyGridThreeG.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP /*| WS_BORDER*/,rc,this,2007);
	m_MFCPropertyGridThreeG.EnableHeaderCtrl(FALSE,_T("参数"),_T("值"));
	m_MFCPropertyGridThreeG.EnableDescriptionArea();
	m_MFCPropertyGridThreeG.SetVSDotNetLook();
	m_MFCPropertyGridThreeG.MarkModifiedProperties();
	m_MFCPropertyGridThreeG.SetAlphabeticMode(false); 
	m_MFCPropertyGridThreeG.SetShowDragContext();

	pGroup51 = new CMFCPropertyGridProperty(_T("载波参数"));
	pGroup52 = new CMFCPropertyGridProperty(_T("调制编码"));
	pGroup53 = new CMFCPropertyGridProperty(_T("载荷配置"));
	pGroup55 = new CMFCPropertyGridProperty("频谱控制");
	pGroup54 = new CMFCPropertyGridProperty(_T("信道"));


	pPropT75 = new CMFCPropertyGridProperty(_T("协议"),_T("IEEE 802.11g"),_T("IEEE 802.11系列之一：11a/b/g/n"));
	pPropT75->Enable(FALSE);
	pGroup51->AddSubItem(pPropT75);
	pPropT76=new CMFCPropertyGridProperty(_T("帧数"),_T("20"),_T("可自行输入，默认20帧"),MFCPROPERTYOOG);
	pGroup51->AddSubItem(pPropT76);
	pPropT77=new CMFCPropertyGridProperty(_T("帧间间隔"),_T("10.0"),_T("可自行输入，单位μs"),MFCPROPERTYOSG);
	pGroup51->AddSubItem(pPropT77);
	pPropT78 = new CMFCPropertyGridProperty(_T("频率偏移"),_T("+0.000000Hz"),_T("可自行输入，默认+0.000000Hz"),MFCPROPERTYOTG);
	pGroup51->AddSubItem(pPropT78);
	pPropT79 = new CMFCPropertyGridProperty(_T("相对功率"),_T("+0.00dB"),_T("可自行输入，载波0默认0.00dB，其他子载波可设置范围+50dB~-10dB，精度0.01dB"),MFCPROPERTYOFG);
	pGroup51->AddSubItem(pPropT79);

	pPropT81 = new CMFCPropertyGridProperty(_T("数据速率"),_T("6 Mbps(OFDM)"),_T("设置数据速率之一：6、9、12、18、24、36、48、54、1、2、5.5、11、22、33Mbps"),MFCPROPERTYOFIG);	
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

	/*CMFCPropertyGridProperty **/pPropT89 = new CMFCPropertyGridProperty(_T("编码方式"),_T("卷积编码"),_T("关于编码方式的说明"),MFCPROPERTYTSTG);
	pPropT89->Enable(FALSE);
	pGroup52->AddSubItem(pPropT89);
	/*CMFCPropertyGridProperty **/pPropT90 = new CMFCPropertyGridProperty(_T("码率"),_T("1/2"),_T("当前速率下的编码速率"),MFCPROPERTYTSFRG);
	pPropT90->Enable(FALSE);
	pGroup52->AddSubItem(pPropT90);
	/*CMFCPropertyGridProperty **/pPropT95 = new CMFCPropertyGridProperty(_T("调制方式"),_T("BPSK"),_T("当前速率下的调制方式"),MFCPROPERTYTSSDG);
	pPropT95->Enable(FALSE);
	//pPropT95->SetData(100);
	pGroup52->AddSubItem(pPropT95);
	/*CMFCPropertyGridProperty**/ pPropT91 = new CMFCPropertyGridProperty(_T("交织"),_T("On"),_T("设置交织的状态：On/Off"),MFCPROPERTYTSFEG);
	pPropT91->AddOption(_T("On"));  
	pPropT91->AddOption(_T("Off")); 
	pPropT91->AllowEdit(FALSE);
	pGroup52->AddSubItem(pPropT91);
	/*CMFCPropertyGridProperty**/pPropT83 = new CMFCPropertyGridProperty(_T("DSSS扰码器"),_T("On"),_T("下拉可选On/Off/报头仅有"),MFCPROPERTYOSEG);
	pPropT83->AddOption(_T("On"));  
	pPropT83->AddOption(_T("Off"));
	pPropT83->AddOption(_T("报头仅有"));
	pPropT83->Show(FALSE);
	pGroup52->AddSubItem(pPropT83);
	/*CMFCPropertyGridProperty**/ pPropT92 = new CMFCPropertyGridProperty(_T("OFDM扰码器"),_T("On"),_T("设置OFDM扰码器的状态：On/Off"),MFCPROPERTYTSSXG);
	pPropT92->AddOption(_T("On"));  
	pPropT92->AddOption(_T("Off")); 
	pPropT92->AllowEdit(FALSE);
	pGroup52->AddSubItem(pPropT92);
	/*CMFCPropertyGridProperty**/pPropT93 = new CMFCPropertyGridProperty(_T("OFDM扰码器初始值"),_T("93"),_T("设置扰码器的值"),MFCPROPERTYTSSEG);
	pGroup52->AddSubItem(pPropT93);
    /*CMFCPropertyGridProperty**/pPropT96 =new CMFCPropertyGridProperty(_T("子载波数"),_T("52"),_T("设置子载波数量"),MFCPROPERTYTSETG);
	pGroup52->AddSubItem(pPropT96);
	pPropT96->Enable(FALSE);
	/*CMFCPropertyGridProperty**/pPropT94 = new CMFCPropertyGridProperty(_T("前导码类型"),_T("OFDM"),_T("默认：OFDM；当数据速率为6/9/12/18/24/36/48/54Mbps：下拉可选OFDM/长/短；当数据速率为2/5.5/11/22/33Mbps：下拉可选长/短"),MFCPROPERTYOEIG);
	//pPropT94->AddOption(_T("OFDM"));
	//pPropT94->AddOption(_T("长"));  
	//pPropT94->AddOption(_T("短"));
	pGroup52->AddSubItem(pPropT94);

	p_data_source_g = new CMFCPropertyGridProperty("数据源","PN9","选择数据源的类型",GDATASOURCE);
	p_data_source_g->AddOption("PN9");
	p_data_source_g->AddOption("PN15");
	p_data_source_g->AddOption("ALL0");
	p_data_source_g->AddOption("从文件读取");
	p_data_source_g->AllowEdit(FALSE);
	pGroup53->AddSubItem(p_data_source_g);

	p_data_filepath_g = new CMFCPropertyGridProperty("文件路径","","选择数据源文件所在的路径",GFILEPATH);
	p_data_filepath_g->Show(FALSE);
	pGroup53->AddSubItem(p_data_filepath_g);

	pPropT86 = new CMFCPropertyGridProperty("负载长度","80","设置负载的长度（单位为Byte）",MFCPROPERTYONIG);
	pGroup53->AddSubItem(pPropT86);
	pPropT87 = new CMFCPropertyGridProperty(_T("MAC头部"),_T("30 Bytes"),_T("默认值"));
	pPropT59->Enable(FALSE);
	pGroup53->AddSubItem(pPropT87);
	pPropT88 = new CMFCPropertyGridProperty(_T("MAC FCS"),_T("4 Bytes"),_T("默认值"));
	pPropT88->Enable(FALSE);
	pGroup53->AddSubItem(pPropT88);

	fitertype_g = new CMFCPropertyGridProperty(_T("滤波器"),_T("无"),_T("设置滤波器的类型"),GMFCPROPERTYTFO);
	fitertype_g->AddOption("无");  
	fitertype_g->AddOption("高斯滤波器");
	fitertype_g->AddOption("根升余弦滤波器");
	fitertype_g->AddOption("理想低通滤波器");
	fitertype_g->AddOption("用户自定义");
	pGroup55->AddSubItem(fitertype_g);
	lp_filter_len_g = new CMFCPropertyGridProperty("滤波器长度","30","设置低通滤波器长度",GLPFILTERLEN);
	lp_filter_len_g->Show(FALSE);
	pGroup55->AddSubItem(lp_filter_len_g);
	lp_filter_wn_g = new CMFCPropertyGridProperty("滤波器通带","0.24","设置滤波器通带 Wn",GLPFILTERWN);
	lp_filter_wn_g->Show(FALSE);
	pGroup55->AddSubItem(lp_filter_wn_g);

	gauss_filter_len_g = new CMFCPropertyGridProperty("滤波器长度","30","设置低通滤波器长度",GGAUSSFILTERLEN);
	gauss_filter_len_g->Show(FALSE);
	pGroup55->AddSubItem(gauss_filter_len_g);
	gauss_filter_BT_g = new CMFCPropertyGridProperty("BT","0.5","设置滤波器通带 BT",GGAUSSFILTERBT);
	gauss_filter_BT_g->Show(FALSE);
	pGroup55->AddSubItem(gauss_filter_BT_g);

	cosine_filter_len_g = new CMFCPropertyGridProperty("滤波器长度","30","设置低通滤波器长度",GCOSINEFILTERLEN);
	cosine_filter_len_g->Show(FALSE);
	pGroup55->AddSubItem(cosine_filter_len_g);
	cosine_filter_alpha_g = new CMFCPropertyGridProperty("alpha","0.24","设置滤波器alpha",GCOSINEFILTERALPHA);
	cosine_filter_alpha_g->Show(FALSE);
	pGroup55->AddSubItem(cosine_filter_alpha_g);
	filter_user_g = new CMFCPropertyGridPropertyButton("滤波器系数","","允许用户自定义滤波器系数",GFILTERUSERDEFINE);
	filter_user_g->Show(FALSE);
	pGroup55->AddSubItem(filter_user_g);
	pPropT15 = new CMFCPropertyGridProperty(_T("窗口长度"),_T("8"),_T("设置滤波器窗口的长度，窗口长度不能超过一个OFDM符号的长度"),MFCPROPERTYTFS);
	pGroup55->AddSubItem(pPropT15);
	pPropT16_g = new CMFCPropertyGridProperty(_T("信道状态"),_T("off"),_T("设置信道状态：信号是否经过信道"),GPPROPCHANNEL4);
	pPropT16_g->AddOption("on");
	pPropT16_g->AddOption("off");
	pGroup54->AddSubItem(pPropT16_g);

	pPropT17_g = new CMFCPropertyGridProperty(_T("信道多径数"),_T("4"),_T("设置多径信道中多径数"),GPPROPCHANNEL1);
	pGroup54->AddSubItem(pPropT17_g);

	pPropT18_g = new CMFCPropertyGridProperty(_T("信号载频"),_T("2.412"),_T("信道载频设置，单位 GHz"),GPPROPCHANNEL2);
	pGroup54->AddSubItem(pPropT18_g);

	pPropT19_g = new CMFCPropertyGridProperty(_T("移动速度"),_T("30"),_T("移动速度设置，单位 km/h"),GPPROPCHANNEL3);
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
	
	//MPDU配置
	m_MpduInfoList.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);//List的风格
	m_MpduInfoList.DeleteAllItems();
	m_MpduInfoList.InsertColumn(0,_T("Mpdus"),LVCFMT_LEFT,65);
	m_MpduInfoList.InsertColumn(1,_T("数据类型"),LVCFMT_CENTER,84);
	m_MpduInfoList.InsertColumn(2,_T("数据源长度(bytes)"),LVCFMT_CENTER,110);
	m_MpduInfoList.InsertColumn(3,_T("MAC Header"),LVCFMT_CENTER,105);
	m_MpduInfoList.InsertColumn(4,_T("MAC FCS"),LVCFMT_CENTER,90);
	m_MpduInfoList.InsertColumn(5,_T("MPDU 长度"),LVCFMT_CENTER,90);
	m_MpduInfoList.InsertColumn(6,"A-MPDU子帧长度",LVCFMT_CENTER,135);
	m_MpduInfoList.InsertItem(0,_T("Mpdu 0"));
	m_MpduInfoList.SetItemText(0,1,_T("PN9"));
	m_MpduInfoList.SetItemText(0,2,"1024Byte(s)");
	m_MpduInfoList.SetItemText(0,3,"On");
	m_MpduInfoList.SetItemText(0,4,_T("On"));
	m_MpduInfoList.SetItemText(0,5,_T("1058Byte(s)"));//添加行
	m_MpduInfoList.SetItemText(0,6,"1062Byte(s)");
	m_MpduInfoList.ShowWindow(FALSE);

	m_MPDUAdd.EnableWindow(FALSE);
	m_MPDUDelete.EnableWindow(FALSE);
	Point();
	update();
	m_finished_ini = TRUE;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CTabProtocolConfig::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码
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
	
	COleVariant t = pProp->GetValue(); //改变之后的值
	CString d;
	d = t.bstrVal;      //从COleVariant到CString 

	switch(wparam)
	{
	case MFCPROPERTYGRIDTHREE://11a
		switch(pProp->GetData())
		{
		case MFCPROPERTYTOS://帧数
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
		case MFCPROPERTYTOT://帧间间隔,4μs对应80个复数
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
					SetFocus()->MessageBox("当前可设置最大频率偏移为+/-58MHz");
					pPropT3->SetValue("58000");
					//pPropZ6_d->SetValue("58000");
					m_data_and_graph->m_configAIndex->FrequencyOffset = 58000*1000;
					//m_data_and_graph->m_configAIndex->FrequencyOffset = 58000*1000;
				}
				else if(FrequencyOffset < -58000)
				{
					SetFocus()->MessageBox("当前可设置最大频率偏移为+/-58MHz");
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
				//这里也要添加选项！m_configIndex->OFDMScramblerState = ON; 这一类的参数传递
				pPropT17->Enable(TRUE);
			}
			else
				pPropT17->Enable(FALSE);*/
			break;
		case MFCPROPERTYTTFR:
			//if (d == _T("设置"))
			//{
			//	if (m_macHeaderDlgIndex.DoModal() == IDOK)
			//	{
			//	}//示例窗口
			//	pPropT12->SetValue((COleVariant)m_macHeaderDlgIndex.str);
			//}
			break;
		case MFCPROPERTYTTO:
			{
				if (0 == d.Compare("PN9"))
				{
					//PN9序列
					m_configAIndex->source_mode = 0;
					p_data_filepath->Show(FALSE);
				}else if (0 == d.Compare("PN15"))
				{
					//PN15序列
					m_configAIndex->source_mode = 1;
					p_data_filepath->Show(FALSE);
				}else if (0 == d.Compare("ALL0"))
				{
					// 全0序列
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
					MessageBox("文件不存在！");
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
					scramSeed = 127 ;//扰码器的初始值设置0-127
				}
				if (scramSeed < 0){
					pPropT017->SetValue("0");
					scramSeed = 0 ;//扰码器的初始值设置0-127
				}
				if (scramSeed==0 && str!="0")
				{
					MessageBox("非有效值！","警告"); 
					pPropT017->SetValue("93");
					scramSeed = 93 ;//扰码器的初始值设置0-127
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
				if(str == "用户自定义")
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
				if(str =="理想低通滤波器")
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
				if(str == "高斯滤波器")
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
				if( str == "根升余弦滤波器")
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
			//11b可参数对应的资源ID，在界面里找到对应的资源ID
		
		case MFCPROPERTYOOB://帧数
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
		case MFCPROPERTYOSB://帧间间隔
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
					SetFocus()->MessageBox("当前可设置最大频率偏移为+/-58MHz");
					pPropT3->SetValue("58000");
					//pPropZ6_d->SetValue("58000");
					m_data_and_graph->m_configBIndex->FrequencyOffset = 58000*1000;
					//m_data_and_graph->m_configAIndex->FrequencyOffset = 58000*1000;
				}
				else if(FrequencyOffset < -58000)
				{
					SetFocus()->MessageBox("当前可设置最大频率偏移为+/-58MHz");
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
				pPropT70->SetValue((COleVariant)_T("长"));
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
				//pPropT70->SetValue((COleVariant)_T("长"));

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
		case MFCPROPERTYOSIB://调制方式，只有5.5M 和11M速率时，可以选择PBCC或者CCK
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
			if (d==_T("长"))
			{
				pPropT70->SetValue((COleVariant)_T("长"));
				m_configBIndex->preamble_type=longPreamble;

			}
			else if(d==_T("短"))
			{
				pPropT70->SetValue((COleVariant)_T("短"));
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
			else if (d==_T("报头仅有"))
			{
				pPropT69->SetValue((COleVariant)_T("报头仅有"));
				m_configBIndex->scrambler_state=Preamble_only;
			}
			break;
		case MFCPROPERTYOSENL690:
			{
				CString str = pPropT690->GetValue();
				int  scramSeed = atoi(str);
				if (scramSeed > 127){
					pPropT690->SetValue("127");
					scramSeed = 127 ;//扰码器的初始值设置0-127
				}
				if (scramSeed < 0){
					pPropT690->SetValue("0");
					scramSeed = 0 ;//扰码器的初始值设置0-127
				}
				if (scramSeed==0 && str!="0")
				{
					MessageBox("非有效值！","警告"); 
					pPropT690->SetValue("93");
					scramSeed = 93 ;//扰码器的初始值设置0-127
				}
				//m_data_and_graph->m_configBIndex->scramSeed = scramSeed;
				break;
			}
		case BDATASOURCE:
			{
				if (0 == d.Compare("PN9"))
				{
					//PN9序列
					m_configBIndex->source_mode = 0;
					p_data_filepath_b->Show(FALSE);
				}else if (0 == d.Compare("PN15"))
				{
					//PN15序列
					m_configBIndex->source_mode = 1;
					p_data_filepath_b->Show(FALSE);
				}else if (0 == d.Compare("ALL0"))
				{
					// 全一序列
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
					MessageBox("文件不存在！");
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
					MessageBox("非有效值！","警告");
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
				if(str == "用户自定义")
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
				if(str =="理想低通滤波器")
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
				if(str == "高斯滤波器")
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
				if( str == "根升余弦滤波器")
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
		case MFCPROPERTYOOG://帧数
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
		case MFCPROPERTYOSG://帧间间隔
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
					SetFocus()->MessageBox("当前可设置最大频率偏移为+/-58MHz");
					pPropT3->SetValue("58000");
					//pPropZ6_d->SetValue("58000");
					m_data_and_graph->m_configGIndex->FrequencyOffset = 58000*1000;
					//m_data_and_graph->m_configAIndex->FrequencyOffset = 58000*1000;
				}
				else if(FrequencyOffset < -58000)
				{
					SetFocus()->MessageBox("当前可设置最大频率偏移为+/-58MHz");
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
				pPropT89->Show(TRUE);//编码方式
				pPropT90->Show(TRUE);//码率
				pPropT91->Show(TRUE);//交织
				pPropT92->Show(TRUE);//OFDM扰码器
				pPropT93->Show(TRUE);//OFDM扰码器初始值
				pPropT96->Show(TRUE);//OFDM子载波数
				pPropT83->Show(FALSE);//DSSS Scrambler
				//pPropT94->AddOption(_T("OFDM"));
				pPropT94->SetValue((COleVariant)_T("OFDM"));
				pPropT94->Enable(TRUE);
				pPropT17_g->Enable(TRUE);
				pPropT17_g->SetValue("4");
				m_configGIndex->NumOfTaps = 4 ;

				if (d ==_T("6 Mbps(OFDM)"))
				{
					pPropT94->AddOption(_T("长"));  
					pPropT94->AddOption(_T("短"));
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
					pPropT94->AddOption(_T("长"));  
					pPropT94->AddOption(_T("短"));
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
					pPropT94->AddOption(_T("长"));  
					pPropT94->AddOption(_T("短"));
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
					pPropT94->AddOption(_T("长"));  
					pPropT94->AddOption(_T("短"));
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
					pPropT94->AddOption(_T("长"));  
					pPropT94->AddOption(_T("短"));
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
					pPropT94->AddOption(_T("长"));  
					pPropT94->AddOption(_T("短"));
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
					pPropT94->AddOption(_T("长"));  
					pPropT94->AddOption(_T("短"));
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
					pPropT94->AddOption(_T("长"));  
					pPropT94->AddOption(_T("短"));
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
				pPropT89->Show(FALSE);//编码方式
				pPropT90->Show(FALSE);//码率
				pPropT91->Show(FALSE);//交织
				pPropT92->Show(FALSE);//OFDM扰码器
				pPropT93->Show(FALSE);//OFDM扰码器初始值
				pPropT96->Show(FALSE);//OFDM子载波数
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
					pPropT94->SetValue((COleVariant)_T("长"));
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
					pPropT94->SetValue((COleVariant)_T("长"));
					pPropT94->AddOption(_T("长"));
					pPropT94->AddOption(_T("短"));
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
					pPropT94->SetValue((COleVariant)_T("长"));
					pPropT94->AddOption(_T("长"));
					pPropT94->AddOption(_T("短"));
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
					pPropT94->SetValue((COleVariant)_T("长"));
					pPropT94->AddOption(_T("长"));
					pPropT94->AddOption(_T("短"));
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
					pPropT94->SetValue((COleVariant)_T("长"));
					pPropT94->AddOption(_T("长"));
					pPropT94->AddOption(_T("短"));
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
					pPropT94->SetValue((COleVariant)_T("长"));
					pPropT94->AddOption(_T("长"));
					pPropT94->AddOption(_T("短"));
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
					if(str == "用户自定义")
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
					if(str =="理想低通滤波器")
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
					if(str == "高斯滤波器")
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
					if( str == "根升余弦滤波器")
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
				else if (d==(_T("长")))
				{
					pPropT83->Show(TRUE);//DSSS Scrambler
					m_configGIndex->preamble_type=longPreamble;
				}
				else if (d==(_T("短")))
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
				else if (d==_T("报头仅有"))
				{
					pPropT83->SetValue((COleVariant)_T("报头仅有"));
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
					scramSeed = 127 ;//扰码器的初始值设置0-127
				}
				if (scramSeed < 0){
					pPropT93->SetValue("0");
					scramSeed = 0 ;//扰码器的初始值设置0-127
				}
				if (scramSeed==0 && str!="0")
				{
					MessageBox("非有效值！","警告"); 
					pPropT93->SetValue("93");
					scramSeed = 93 ;//扰码器的初始值设置0-127
				}
				m_data_and_graph->m_configGIndex->scramble_state_initial = scramSeed;
			}
			break;
		case GDATASOURCE:
			{
				if (0 == d.Compare("PN9"))
				{
					//PN9序列
					m_configGIndex->source_mode = 0;
					p_data_filepath_g->Show(FALSE);
				}else if (0 == d.Compare("PN15"))
				{
					//PN15序列
					m_configGIndex->source_mode = 1;
					p_data_filepath_g->Show(FALSE);
				}else if (0 == d.Compare("ALL0"))
				{
					// 全一序列
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
					MessageBox("文件不存在！");
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
		case MFCPROPERTYOSIN://索引号0~76
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
					MessageBox("非有效值","警告");
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

				//设置Nss，调制方式，码率数据速率
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

					int num_of_antenna;//天线数
					num_of_antenna =m_data_and_graph->m_configNIndex->Nt;//发端天线的数目
					
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
				//设置空时流的个数
				if(mcs<=7||mcs==32)
				{   
					int num_of_antenna;//天线数
					int num_of_sts;//空时流数
					num_of_sts=1;
					m_carrier.pPropS22->SetValue("1");
					num_of_antenna =m_data_and_graph->m_configNIndex->Nt;//发端天线的数目
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
					int num_of_antenna;//天线数
					int num_of_sts;//空时流数
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
					int num_of_antenna;//天线数
					int num_of_sts;//空时流数
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
					int num_of_antenna;//天线数
					int num_of_sts;//空时流数
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
	    case MFCPROPERTYOFINN1://空时流数
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
					pPropT30->SetValue("空间扩展");
					m_data_and_graph->m_configNIndex->ieeeQ =4;
				}else
				{
					pPropT30->Enable(TRUE);
					pPropT30->SetValue("直接映射");
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
					//PN9序列
					m_configNIndex->source_mode = 0;
					p_data_filepath_n->Show(FALSE);
				}else if (0 == d.Compare("PN15"))
				{
					//PN15序列
					m_configNIndex->source_mode = 1;
					p_data_filepath_n->Show(FALSE);
				}else if (0 == d.Compare("ALL0"))
				{
					// 全一序列
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
		case MFCPROPERTYSSN://交织
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
		case MFCPROPERTYSSN1://扰码器
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
					scramSeed = 127 ;//扰码器的初始值设置0-127
				}
				if (scramSeed < 0){
					pPropT27->SetValue("0");
					scramSeed = 0 ;//扰码器的初始值设置0-127
				}
				if (scramSeed==0 && str!="0")
				{
					MessageBox("非有效值！","警告"); 
					pPropT27->SetValue("93");
					scramSeed = 93 ;//扰码器的初始值设置0-127
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
				ieeeQ = str =="直接映射"? 0:4;
				m_data_and_graph->m_configNIndex->ieeeQ =ieeeQ;
				//设置空时流的个数
				if(mcs<=7||mcs==32)
				{   
					int num_of_antenna;//天线数
					int num_of_sts;//空时流数
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
					int num_of_antenna;//天线数
					int num_of_sts;//空时流数
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
					int num_of_antenna;//天线数
					int num_of_sts;//空时流数
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
					int num_of_antenna;//天线数
					int num_of_sts;//空时流数
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
				if(str == "用户自定义")
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
				if(str =="理想低通滤波器")
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
				if(str == "高斯滤波器")
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
				if( str == "根升余弦滤波器")
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
		case MFCPROPERTYOSIN://索引号0~7
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
				   scramSeed = 127 ;//扰码器的初始值设置0-127
			   }
			   if (scramSeed < 0){
				   pPropT48->SetValue("0");
				   scramSeed = 0 ;//扰码器的初始值设置0-127
			   }
			   if (scramSeed==0 && str!="0")
			   {
				   MessageBox("非有效值！","警告"); 
				   pPropT48->SetValue("93");
				   scramSeed = 93 ;//扰码器的初始值设置0-127
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
					//PN9序列
					m_configNIndex->source_mode = 0;
					p_data_filepath_nl->Show(FALSE);
				}else if (0 == d.Compare("PN15"))
				{
					//PN15序列
					m_configNIndex->source_mode = 1;
					p_data_filepath_nl->Show(FALSE);
				}else if (0 == d.Compare("ALL0"))
				{
					// 全一序列
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
				if(str == "用户自定义")
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
				if(str =="理想低通滤波器")
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
				if(str == "高斯滤波器")
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
				if( str == "根升余弦滤波器")
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
		FilePathName=dlg.GetPathName(); //文件名保存在了FilePathName里
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
// CTabProtocolConfig 对话框

BOOL CMFCPropertyGridPropertyButton2::HasButton() const{
	return TRUE;
}
void CMFCPropertyGridPropertyButton2::OnClickButton(CPoint point){
	CString FilePathName;
	CFileDialog dlg(TRUE,NULL, NULL,OFN_FORCESHOWHIDDEN,
		(LPCTSTR)_TEXT("txt files (*.txt)|*.txt||"),NULL);
	if(dlg.DoModal()==IDOK)
	{
		FilePathName=dlg.GetPathName(); //文件名保存在了FilePathName里
		((CMainFrame*)AfxGetMainWnd())->m_pass_to_thread.m_configAIndex->filepath = FilePathName;
		((CTabParent*)((CMainFrame*)AfxGetMainWnd())->m_mainSplitter.GetPane(0,0))->m_tabProtocolConfig.p_data_filepath->SetValue(FilePathName);
	}
}
void CTabProtocolConfig::OnBnClickedMpdudelete()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos=m_MpduInfoList.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		AfxMessageBox(_T("请选中列表中的<MPDU>条目"));
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
	// TODO: 在此添加控件通知处理程序代码
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
	//当前选中的MPDU
	POSITION pos=m_MpduInfoList.GetFirstSelectedItemPosition();
	int nItem = m_MpduInfoList.GetNextSelectedItem(pos);
	m_mpdu_general->Index = nItem;
	m_mpdu_general->DoModal();
	delete m_mpdu_general;
}