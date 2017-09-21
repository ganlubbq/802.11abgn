// TabCarrier.cpp : 实现文件
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "TabCarrier.h"
#include "afxdialogex.h"
#include "TabMac.h"
#include "TabProtocolConfig.h"
#include "TabParent.h"
#include "MainFrm.h"

// CTabCarrier 对话框

IMPLEMENT_DYNAMIC(CTabCarrier, CDialog)

CTabCarrier::CTabCarrier(CWnd* pParent /*=NULL*/)
	: CDialog(CTabCarrier::IDD, pParent)
{
	m_finished_ini = FALSE;
	m_font.CreatePointFont(100,"微软雅黑");
}

CTabCarrier::~CTabCarrier()
{
}

void CTabCarrier::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTabCarrier, CDialog)
	ON_WM_SIZE()
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED,OnPropertyChanged)
END_MESSAGE_MAP()


// CTabCarrier 消息处理程序


void CTabCarrier::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	// CDialog::OnOK();
}


BOOL CTabCarrier::OnInitDialog()
{
	CDialog::OnInitDialog();
	//文本显示信息

	// TODO:  在此添加额外的初始化
	CRect rc;
	GetClientRect(&rc);
	//rc.bottom += 20;
	rc.left += 10;
	//rc.right += 10;
	rc.top += 10;

	//11a/b/g协议参数
	m_MFCPropertyGridTwo.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,rc,this,2001);
	m_MFCPropertyGridTwo.EnableHeaderCtrl(FALSE,_T("参数"),_T("值"));
	m_MFCPropertyGridTwo.EnableDescriptionArea();
	m_MFCPropertyGridTwo.SetDescriptionRows(5);
	m_MFCPropertyGridTwo.SetVSDotNetLook();
	m_MFCPropertyGridTwo.MarkModifiedProperties();
	m_MFCPropertyGridTwo.SetAlphabeticMode(false); 
	m_MFCPropertyGridTwo.SetShowDragContext();

	pGroup11 = new CMFCPropertyGridProperty(_T("基本参数"));
	pGroup12 = new CMFCPropertyGridProperty(_T("波形控制"));
	pGroup13 = new CMFCPropertyGridProperty(_T("OFDM参数"));
	
/*CMFCPropertyGridProperty **/pPropS1=new CMFCPropertyGridProperty(_T("波形名称"),_T("WLAN"),_T("IEEE 802.11系列之一：11a/b/g"));
	pPropS1->Enable(FALSE);
	pGroup11->AddSubItem(pPropS1);
	/*CMFCPropertyGridProperty **/pPropS2=new CMFCPropertyGridProperty(_T("总采样点数"),_T("2641"),_T("采样点数目"),SAMPLELENGTHA);
	pPropS2->Enable(FALSE);
	pGroup11->AddSubItem(pPropS2);


	over_sample = new CMFCPropertyGridProperty(_T("过采样率"),_T("1"),"",OVERSAMPLEABG);
	pGroup12->AddSubItem(over_sample);

	/*CMFCPropertyGridProperty* */
	/*pPropS3 = new CMFCPropertyGridProperty(_T("镜像频谱"),_T("Off"),_T("镜像频谱状态：ON或OFF"));
	pPropS3->AddOption(_T("On"));  
	pPropS3->AddOption(_T("Off"));     
	pPropS3->AllowEdit(FALSE);
	pGroup12->AddSubItem(pPropS3);*/
	p_quadrature_angle_adjustmentA = new CMFCPropertyGridProperty(_T("正交角度调整"),_T("0.00 Deg"),_T("范围：-90~+90"),CARRI_QUADRATURE_ANGLE_ADJUSTA);
	pGroup12->AddSubItem(p_quadrature_angle_adjustmentA);

	p_IQ_gain_balanceA = new CMFCPropertyGridProperty(_T("I/Q平衡增益"), _T("0.00 dB"), _T("范围：-10~+10"),CARRI_IQ_BALANCE_GAINA);
	pGroup12->AddSubItem(p_IQ_gain_balanceA);


	pPropS6=new CMFCPropertyGridProperty(_T("码片时间"), _T("50ns"), _T("chip duration,码片时间长度"));
	pPropS6->Enable(FALSE);
	pGroup13->AddSubItem(pPropS6);
    pPropS7=new CMFCPropertyGridProperty(_T("Nsd"), _T("48"), _T("Number of data subcarriers,数据子载波的个数"));
	pPropS7->Enable(FALSE);
	pGroup13->AddSubItem(pPropS7);
	pPropS8=new CMFCPropertyGridProperty(_T("Nsp"), _T("4"), _T("Number of pilot subcarriers,导频子载波的个数"));
	pPropS8->Enable(FALSE);
	pGroup13->AddSubItem(pPropS8);
	pPropS9=new CMFCPropertyGridProperty(_T("Nst"), _T("52"), _T("Nst=(Nsd+Nsp);Number of subcarriers,total 总子载波的个数"));
	pPropS9->Enable(FALSE);
	pGroup13->AddSubItem(pPropS9);
	pPropS10=new CMFCPropertyGridProperty(_T("抽样速率"), _T("20MHz"), _T("抽样速率的大小"));
	pPropS10->Enable(FALSE);
	pGroup13->AddSubItem(pPropS10);
    pPropS11=new CMFCPropertyGridProperty(_T("OFDM符号间隔"), _T("4us"), _T("符号间隔的长度(80chip)"));
	pPropS11->Enable(FALSE);
	pGroup13->AddSubItem(pPropS11);
	pPropS12=new CMFCPropertyGridProperty(_T("循环前缀长度"), _T("0.8us"), _T("保护间隔的长度(16chip)"));
	pPropS12->Enable(FALSE);
	pGroup13->AddSubItem(pPropS12);
	pPropS13=new CMFCPropertyGridProperty(_T("子载波频率间隔"), _T("0.3125MHz"), _T("子载波频率间隔(20MHz/64)"));
	pPropS13->Enable(FALSE);
	pGroup13->AddSubItem(pPropS13);
	pPropS14=new CMFCPropertyGridProperty(_T("训练序列长度"), _T("16us"), _T("子载波频率间隔(Tshort+Tlong)"));
	pPropS14->Enable(FALSE);
	pGroup13->AddSubItem(pPropS14);

	pGroup13->Show(TRUE);

	m_MFCPropertyGridTwo.AddProperty(pGroup11);
	m_MFCPropertyGridTwo.AddProperty(pGroup12);
	m_MFCPropertyGridTwo.AddProperty(pGroup13); 

	m_MFCPropertyGridTwo.EnableDescriptionArea(TRUE);
	m_MFCPropertyGridTwo.SetCustomColors(RGB(250,250,250),RGB(0,0,0),RGB(230,230,230),RGB(100,100,100),RGB(230,230,230),RGB(0,0,0),RGB(220,220,220));
	m_MFCPropertyGridTwo.ShowWindow(TRUE);

	m_MFCPropertyGridTwoN.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP /*| WS_BORDER*/,rc,this,2002);
	m_MFCPropertyGridTwoN.EnableHeaderCtrl(FALSE,_T("参数"),_T("值"));
	m_MFCPropertyGridTwoN.EnableDescriptionArea(TRUE);
	m_MFCPropertyGridTwoN.SetDescriptionRows(5);
	m_MFCPropertyGridTwoN.SetVSDotNetLook();
	m_MFCPropertyGridTwoN.MarkModifiedProperties();
	m_MFCPropertyGridTwoN.SetAlphabeticMode(false); 
	m_MFCPropertyGridTwoN.SetShowDragContext();

	pGroup14 = new CMFCPropertyGridProperty(_T("1.基本参数"));
	pGroup15 = new CMFCPropertyGridProperty(_T("2.波形控制"));
	pGroup16 = new CMFCPropertyGridProperty(_T("3.模式选择"));

	pPropS15=new CMFCPropertyGridProperty(_T("波形名称"),_T("WLAN"),_T("IEEE 802.11系列之一：11a/b/g"));
	pPropS15->Enable(FALSE);
	pGroup14->AddSubItem(pPropS15);
	pPropS16=new CMFCPropertyGridProperty(_T("总采样点数"),_T("1280"),_T("采样点数目"),SAMPLELENGTH);
	pPropS16->Enable(FALSE);
	pGroup14->AddSubItem(pPropS16);

	over_sample_n = new CMFCPropertyGridProperty(_T("过采样率"),_T("1"),_T("关于过采样率的说明"),OVERSAMPLEN);
	pGroup15->AddSubItem(over_sample_n);
	/*pPropS17 = new CMFCPropertyGridProperty(_T("镜像频谱"),_T("Off"),_T("镜像频谱状态：ON或OFF"));
	pPropS17->AddOption(_T("On"));  
	pPropS17->AddOption(_T("Off"));     
	pPropS17->AllowEdit(FALSE);
	pGroup15->AddSubItem(pPropS17);*/
	//pGroup15->AddSubItem(new CMFCPropertyGridProperty(_T("正交角度调整"),_T("0.00 Deg"),_T("这是参数的说明")));
	//pGroup15->AddSubItem(new CMFCPropertyGridProperty(_T("I/Q平衡增益"), _T("0.00 dB"), _T("这是参数的说明")));
	p_quadrature_angle_adjustmentN = new CMFCPropertyGridProperty(_T("正交角度调整"),_T("0.00 Deg"),_T("范围：-90~+90"),CARRI_QUADRATURE_ANGLE_ADJUSTN);
	pGroup15->AddSubItem(p_quadrature_angle_adjustmentN);

	p_IQ_gain_balanceN = new CMFCPropertyGridProperty(_T("I/Q平衡增益"), _T("0.00 dB"), _T("范围：-10~+10"),CARRI_IQ_BALANCE_GAINN);
	pGroup15->AddSubItem(p_IQ_gain_balanceN);
	pPropS19a= new CMFCPropertyGridProperty(_T("频率偏移"),_T("+0.000000 Hz"),_T("设置频率偏移"),MFCPROPERTYTOFRN);
	pGroup15->AddSubItem(pPropS19a);
	pPropS18 = new CMFCPropertyGridProperty(_T("协议"),_T("IEEE 802.11n"),_T("IEEE 802.11系列之一：11a/b/g/n"));
	pPropS18->Enable(FALSE);
	pGroup16->AddSubItem(pPropS18);
	pPropS19=new CMFCPropertyGridProperty(_T("波形模式"),_T("HT_MM"),_T("波形产生的模式:（1）Legacy（2）HT-MM，802.11n的混合传输模式（HT-mixedmode）（3）HT-GF，802.11n的绿野模式（HT-greenfield）（4）non-HT-DUP"),MFCPROPERTYOON);
	pPropS19->AddOption(_T("HT_MM"));
	pPropS19->AddOption(_T("HT_GF")); 
	pPropS19->AddOption(_T("Legacy")); 
	//pPropS19->AddOption(_T("non-HT-DUP"));
	pGroup16->AddSubItem(pPropS19);
	pPropS20=new CMFCPropertyGridProperty(_T("带宽"),_T("20MHz"),_T("可选20MHz、40MHz"),MFCPROPERTYOSN);
	pPropS20->AddOption(_T("20MHz"));  
	pPropS20->AddOption(_T("40MHz"));
	pGroup16->AddSubItem(pPropS20);
	pPropS21 = new CMFCPropertyGridProperty(_T("天线数目"),_T("2"),_T("Legacy模式为1，不可选；HT模式为1-4"),MFCPROPERTYOTN);
	pPropS21->AddOption("1");pPropS21->AddOption("2");pPropS21->AddOption("3");pPropS21->AddOption("4");
	pPropS21->AllowEdit(FALSE);
	pGroup16->AddSubItem(pPropS21);
	/*pPropS22 = new CMFCPropertyGridProperty(_T("空时流数目"),_T("1"),_T("不可编辑，由程序计算得来"),MFCPROPERTYOTNSTS);  
	pPropS22->Enable(FALSE);
	pGroup16->AddSubItem(pPropS22);*/
	pPropS23 = new CMFCPropertyGridProperty(_T("帧数目"),_T("20"),_T("默认为20"),MFCPROPERTYOTN1);  
	//pPropS23->Enable(FALSE);
	pGroup16->AddSubItem(pPropS23);
	pPropS2300 = new CMFCPropertyGridProperty(_T("帧间间隔"),_T("10.0"),_T("单位μs"),MFCPROPERTYOTN2);  
	//pPropS2300->Enable(FALSE);
	pGroup16->AddSubItem(pPropS2300);

	m_MFCPropertyGridTwoN.AddProperty(pGroup14);
	m_MFCPropertyGridTwoN.AddProperty(pGroup15);
	m_MFCPropertyGridTwoN.AddProperty(pGroup16); 


	m_MFCPropertyGridTwoN.SetCustomColors(RGB(250,250,250),RGB(0,0,0),RGB(230,230,230),RGB(100,100,100),RGB(230,230,230),RGB(0,0,0),RGB(220,220,220));
	m_MFCPropertyGridTwoN.ShowWindow(SW_SHOW);
	m_MFCPropertyGridTwoN.ShowWindow(FALSE);
	CWnd *pWnd = GetTopWindow();  
	while (NULL != pWnd)  
	{  
		pWnd->SetFont(&m_font);  
		pWnd = pWnd->GetNextWindow();  
	}  
	update();
	m_finished_ini = TRUE;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CTabCarrier::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (IsWindowVisible() || m_finished_ini)
	{
		m_MFCPropertyGridTwo.MoveWindow(10,10,cx-32,cy-65);
		m_MFCPropertyGridTwoN.MoveWindow(10,10,cx-32,cy-65);
	}
}
LRESULT CTabCarrier::OnPropertyChanged(__in WPARAM wparam,__in LPARAM lparam)
{
	CMFCPropertyGridProperty* pProp = (CMFCPropertyGridProperty*)lparam; 
	
	CTabParent*p_tabParent = (CTabParent*)(((CMainFrame*)(AfxGetMainWnd()))->m_mainSplitter.GetPane(0,0));
	data_and_graph* m_data_and_graph =&(((CMainFrame*)AfxGetMainWnd())->m_pass_to_thread);
	CTabProtocolConfig &m_tabprotocolconfig=((CTabParent*)(((CMainFrame*)AfxGetMainWnd())->m_mainSplitter.GetPane(0,0)))->m_tabProtocolConfig;
	int ID = (int) pProp->GetData(); 
	CString s = pProp->GetName();  //被改变的参数名  
	COleVariant t = pProp->GetValue(); //改变之后的值
	int a = pProp->GetOptionCount();
	CString d;
	d = t.bstrVal;      //从COleVariant到CString 

	regex patten_iqgainbalance("^[-]?\\d+(\\.\\d*)?(dB)?(db)?$",regex::icase);	//正则表达式验证输入是否正确
	regex patten_quad_deg_ad("^[-]?\\d+(\\.\\d*)?(deg)?$",regex::icase);
	bool match_result = false;

	switch(wparam)
	{
	case MFCPROPERTYGRIDSECONDN://11n
		{
			switch(pProp->GetData())
			{

			
		case MFCPROPERTYOON:
			{
				if (d=="Legacy")				
				{
					m_configIndex->ProtocolModel = OneNL;
					p_tabParent->m_tabProtocolConfig.update();
					m_data_and_graph->m_configNIndex->txvector_format=Legacy;
					pPropS20->Enable(FALSE);
					pPropS20->SetValue((COleVariant)_T("20MHz"));
					m_data_and_graph->m_configNIndex->BandWidth ="20";
				}
				else if(d=="HT_MM")
				{
					m_configIndex->ProtocolModel = OneN;
					p_tabParent->m_tabProtocolConfig.update();
					m_data_and_graph->m_configNIndex->txvector_format=HT_MM;
					pPropS20->Enable(TRUE);
					pPropS20->SetValue((COleVariant)_T("20MHz"));
					m_data_and_graph->m_configNIndex->BandWidth ="20";
				}
				else
				{
					m_configIndex->ProtocolModel = OneN;
					p_tabParent->m_tabProtocolConfig.update();
					m_data_and_graph->m_configNIndex->txvector_format=HT_GF;
					pPropS20->Enable(TRUE);
					pPropS20->SetValue((COleVariant)_T("20MHz"));
					m_data_and_graph->m_configNIndex->BandWidth ="20";
				}
				break;
			}
			break;
		case SAMPLELENGTH:
			{
				int length = m_data_and_graph->m_configNIndex->length;
				char str[10];
				pPropS16->SetValue(itoa(length,str,10));
			}
			break;
		case MFCPROPERTYTOFRN:
			{
				float FrequencyOffset=atof(d);
				if(FrequencyOffset > 58000)
				{
					SetFocus()->MessageBox("当前可设置最大频率偏移为+/-58MHz");
					pPropS19a->SetValue("58000");
					//pPropZ6_d->SetValue("58000");
					m_data_and_graph->m_configNIndex->FrequencyOffset = 58000*1000;
					//m_data_and_graph->m_configAIndex->FrequencyOffset = 58000*1000;
				}
				else if(FrequencyOffset < -58000)
				{
					SetFocus()->MessageBox("当前可设置最大频率偏移为+/-58MHz");
					pPropS19a->SetValue("-58000");
					//pPropZ6_d->SetValue("-58000");
					m_data_and_graph->m_configNIndex->FrequencyOffset = -58000*1000;
					//Protocol_para_d->para.FrequencyOffset = -58000*1000;
				}

				else{
					m_data_and_graph->m_configNIndex->FrequencyOffset = FrequencyOffset*1000;
					//Protocol_para_d->para.FrequencyOffset = FrequencyOffset*1000;
				}
			}
			break;
		case MFCPROPERTYOSN://带宽
	         { CString str;
			  str =pProp->GetValue();
			  m_data_and_graph->m_configNIndex->BandWidth =str;
			  if ((m_data_and_graph->m_configNIndex->BandWidth =="20MHz"||m_data_and_graph->m_configNIndex->BandWidth =="20") && m_data_and_graph->m_configNIndex->mcs!=32 )
			  {
				  pPropS20->SetValue((COleVariant)_T("20MHz"));
				  m_data_and_graph->m_configNIndex->BandWidth ="20";
			  } 
			  else
			  {
				  pPropS20->SetValue((COleVariant)_T("40MHz"));
				  m_data_and_graph->m_configNIndex->BandWidth ="40";
			  }
			  break;
			 }
			 break;
		case OVERSAMPLEN:
			{
				CString str;
				str =pProp->GetValue();
				int oversample = atoi(str);
				if (oversample>64)
				{
					over_sample_n->SetValue("64");
					oversample=64;
				}
				if (oversample<1)
				{
					over_sample_n->SetValue("1");
					oversample=1;
				}
				if (oversample==1 && str!="1")
				{
					over_sample_n->SetValue("1");
					oversample=1;
					MessageBox("非有效值！","警告");
				}

				m_data_and_graph->m_configNIndex->oversample_ratio =oversample;
				break;
			}
       case MFCPROPERTYOTN://天线数目，Legacy：不可编辑默认为1；HT：1-4可填
			{
				int num_of_antenna =atoi(d);
				m_data_and_graph->m_configNIndex->num_of_antenna =num_of_antenna;
				((CMainFrame*)AfxGetMainWnd())->m_STC_type=TRUE;

				m_data_and_graph->m_configNIndex->Nt=num_of_antenna;
				if (m_data_and_graph->m_configNIndex->Nt<m_data_and_graph->m_configNIndex->num_of_sts)
				{
					char str[10];
					itoa(m_data_and_graph->m_configNIndex->num_of_sts,str,10);
					m_data_and_graph->m_configNIndex->Nt=m_data_and_graph->m_configNIndex->num_of_sts;
					pPropS21->SetValue(str);
				}
				if (m_data_and_graph->m_configNIndex->Nt>m_data_and_graph->m_configNIndex->num_of_sts)
				{
					m_tabprotocolconfig.pPropT30->Enable(FALSE);
					m_tabprotocolconfig.pPropT30->SetValue("空间扩展");
					m_data_and_graph->m_configNIndex->ieeeQ =4;
				}else
				{
					m_tabprotocolconfig.pPropT30->Enable(TRUE);
					m_tabprotocolconfig.pPropT30->SetValue("直接映射");
					m_data_and_graph->m_configNIndex->ieeeQ =0;
				}
				int top = m_data_and_graph->m_configNIndex->Nt-m_data_and_graph->m_configNIndex->num_of_sts;
				char stra[10];
				itoa(top,stra,10);
				if (m_data_and_graph->m_configNIndex->Ness>top)
				{
					m_tabprotocolconfig.pPropT25d->SetValue(stra);
					m_data_and_graph->m_configNIndex->Ness=top;
				}
				//m_data_and_graph->m_configNIndex->Ness=Ness;
			}
			break;
	   case MFCPROPERTYOTN1://帧数
			{
				int num_of_frame =atoi(d);
				if (num_of_frame<1)
				{
					num_of_frame=1;
					pPropS23->SetValue("1");
				}
				if (num_of_frame>2000)
				{
					num_of_frame=2000;
					pPropS23->SetValue("2000");
				}

				m_data_and_graph->m_configNIndex->num_of_frame=num_of_frame;

			}
			break;
	   case MFCPROPERTYOTN2://帧间间隔,8μs对应160个复数
		   {
			   double num_of_zeros =atof(d);
			   if (num_of_zeros<=0)
			   {
				   num_of_zeros=0;
				   pPropS2300->SetValue("0");
			   }
			   if (num_of_zeros>100000)
			   {
				   num_of_zeros=100000;
				   pPropS2300->SetValue("100000");
			   }
			   int x=(int)floor(num_of_zeros*20);
			   m_data_and_graph->m_configNIndex->num_of_zeros=x;
		   }
		   break;
	   case CARRI_QUADRATURE_ANGLE_ADJUSTN:
		   d.Remove(' ');//移除空格
		   match_result = regex_match(d.GetBuffer(),patten_quad_deg_ad);//正则验证
		   double temp_deg;
		   temp_deg=m_data_and_graph->m_configNIndex->quan_angle_adjust;//p_ADParams是ad的ADParams的实例，注意每个人对应的不一样；
		   if (match_result)
		   {
			   double quad_angle_ad = atof(d);
			   if (quad_angle_ad > 90)
			   {
				   MessageBox("正交角度设置有误！");
				   quad_angle_ad = 90;
			   }
			   else if (quad_angle_ad < -90)
			   {
				   MessageBox("正交角度设置有误！");
				   quad_angle_ad = -90;
			   }
			   m_data_and_graph->m_configNIndex->quan_angle_adjust = quad_angle_ad;
			   //str_temp.Format(_T("%.2lf Deg"), quad_angle_ad);
			   //pProp->SetValue(str_temp);
		   }
		   else
		   {
			   MessageBox("正交角度设置有误！");
			   //str_temp.Format(_T("0 Deg"));
			   p_quadrature_angle_adjustmentN->SetValue("0 Deg");
			   // // 			
		   }
		   break;
	   case CARRI_IQ_BALANCE_GAINN:
		   d.Remove(' ');//移除空格
		   match_result = regex_match(d.GetBuffer(),patten_iqgainbalance);//正则验证
		   double temp_db;
		   temp_db=m_data_and_graph->m_configNIndex->IQ_gain;
		   if (match_result)
		   {
			   double IQ_gain = atof(d);
			   if (IQ_gain > 10)
			   {	IQ_gain = 10;
			   MessageBox("I\Q平衡增益设置有误！");   
			   }
			   else if (IQ_gain < -10)
			   {	IQ_gain = -10;
			   MessageBox("I\Q平衡增益设置有误！");
			   }
			   m_data_and_graph->m_configNIndex->IQ_gain = IQ_gain;
			   //str_temp.Format(_T("%.2lf dB"), IQ_gain);
			   //pProp->SetValue(str_temp);
		   }
		   else
		   {
			   MessageBox("I\Q平衡增益设置有误！");
			   //str_temp.Format (_T("0 dB"));
			   p_IQ_gain_balanceN->SetValue("0 dB");
		   }
		   break;

	   case MFCPROPERTYOTNSTS:
		   {

		   }
		   break;
			}
		}
		break;
		
		
	
		//break;
	case MFCPROPERTYGRIDSECOND://11abg
		switch(pProp->GetData())
		{
		  case OVERSAMPLEABG:
			{
				CString str = over_sample->GetValue();
				int oversample = atoi(str);
				if (oversample>64)
				{
					over_sample->SetValue("64");
					oversample=64;
				}
				if (oversample<1)
				{
					over_sample->SetValue("1");
					oversample=1;
				}
				if (oversample==1 && str!="1")
				{
					over_sample->SetValue("1");
					oversample=1;
					MessageBox("非有效值！","警告");
				}
				m_data_and_graph->m_configAIndex->oversample_ratio = oversample;
				m_data_and_graph->m_configBIndex->oversample_ratio = oversample;
				m_data_and_graph->m_configGIndex->oversample_ratio = oversample;
			}
			break;
		  case SAMPLELENGTHA:
			  {
				  int length;
				  switch (m_configIndex->ProtocolModel)
				  {
				      case OneA:
				          length = m_data_and_graph->m_configAIndex->length;
				      break;
					  case OneB:
				          length = m_data_and_graph->m_configBIndex->length;
					  break;
					  case OneG:
				          length = m_data_and_graph->m_configGIndex->length;
				      break;
				  }
				  char str[10];
				  pPropS2->SetValue(itoa(length,str,10));
			  }
			  break;
		  case CARRI_QUADRATURE_ANGLE_ADJUSTA:
			  d.Remove(' ');//移除空格
			  match_result = regex_match(d.GetBuffer(),patten_quad_deg_ad);//正则验证
			  double temp_deg;
			  temp_deg=m_data_and_graph->m_configAIndex->quan_angle_adjust;//p_ADParams是ad的ADParams的实例，注意每个人对应的不一样；
			  if (match_result)
			  {
				  double quad_angle_ad = atof(d);
				  if (quad_angle_ad > 90)
				  {
					  MessageBox("正交角度设置有误！");
					  quad_angle_ad = 90;
				  }
				  else if (quad_angle_ad < -90)
				  {
					  MessageBox("正交角度设置有误！");
					  quad_angle_ad = -90;
				  }
				  m_data_and_graph->m_configAIndex->quan_angle_adjust = quad_angle_ad;
				  m_data_and_graph->m_configBIndex->quan_angle_adjust = quad_angle_ad;
				  m_data_and_graph->m_configGIndex->quan_angle_adjust = quad_angle_ad;
				  //str_temp.Format(_T("%.2lf Deg"), quad_angle_ad);
				  //pProp->SetValue(str_temp);
			  }
			  else
			  {
				  MessageBox("正交角度设置有误！");
				  //str_temp.Format(_T("0 Deg"));
				  p_quadrature_angle_adjustmentA->SetValue("0 Deg");
				  // // 			
			  }
			  break;
		  case CARRI_IQ_BALANCE_GAINA:
			  d.Remove(' ');//移除空格
			  match_result = regex_match(d.GetBuffer(),patten_iqgainbalance);//正则验证
			  double temp_db;
			  temp_db=m_data_and_graph->m_configAIndex->IQ_gain;
			  if (match_result)
			  {
				  double IQ_gain = atof(d);
				  if (IQ_gain > 10)
				  {	IQ_gain = 10;
				  MessageBox("I\Q平衡增益设置有误！");   
				  }
				  else if (IQ_gain < -10)
				  {	IQ_gain = -10;
				  MessageBox("I\Q平衡增益设置有误！");
				  }
				  m_data_and_graph->m_configAIndex->IQ_gain = IQ_gain;
				  m_data_and_graph->m_configBIndex->IQ_gain = IQ_gain;
				  m_data_and_graph->m_configGIndex->IQ_gain = IQ_gain;
				  //str_temp.Format(_T("%.2lf dB"), IQ_gain);
				  //pProp->SetValue(str_temp);
			  }
			  else
			  {
				  MessageBox("I\Q平衡增益设置有误！");
				  //str_temp.Format (_T("0 dB"));
				  p_IQ_gain_balanceA->SetValue("0 dB");
			  }
			  break;

		}
		
		break;

	default:
		break;
	}
	return 0;  
	return 0;
}

//增加载波函数实现
//void CTabCarrier::OnBnClickedButton1()
//{
//	// TODO: Add your control notification handler code here
//	nCarrier=nCarrier+1;
//	if (nCarrier == 1)
//	{
//		m_CarrierInfoList.InsertItem(1,_T("载波 1"));
//		m_CarrierInfoList.SetItemText(1,1,_T("On"));
//		m_CarrierInfoList.SetItemText(1,2,textInfo(0,m_configIndex));
//		m_CarrierInfoList.SetItemText(1,3,textInfo(1,m_configIndex));
//		m_CarrierInfoList.SetItemText(1,4,_T(" 20.000 MHz"));
//		m_CarrierInfoList.SetItemText(1,5,_T("0.00 dB"));//添加行
//
//		flg1 =true;
//	}
//	else if(nCarrier == 2)
//	{
//		if (carrierFlg)
//		{
//			m_CarrierInfoList.InsertItem(2,_T("载波 2"));
//			m_CarrierInfoList.SetItemText(2,1,_T("On"));
//			m_CarrierInfoList.SetItemText(2,2,textInfo(0,m_configIndex));
//			m_CarrierInfoList.SetItemText(2,3,textInfo(1,m_configIndex));
//			m_CarrierInfoList.SetItemText(2,4,_T("-20.000 MHz"));
//			m_CarrierInfoList.SetItemText(2,5,_T("0.00 dB"));//添加行
//
//			flg2 = true;
//
//		}
//		else
//		{
//			m_CarrierInfoList.InsertItem(1,_T("载波 1"));
//			m_CarrierInfoList.SetItemText(1,1,_T("On"));
//			m_CarrierInfoList.SetItemText(1,2,textInfo(0,m_configIndex));
//			m_CarrierInfoList.SetItemText(1,3,textInfo(1,m_configIndex));
//			m_CarrierInfoList.SetItemText(1,4,_T(" 20.000 MHz"));
//			m_CarrierInfoList.SetItemText(1,5,_T("0.00 dB"));//添加行
//
//			flg1 =true;
//		}
//	}
//
//	if (nCarrier > 2)
//	{
//		nCarrier = nCarrier-1;
//	}
//}

//删除载波功能实现
//void CTabCarrier::OnBnClickedButton2()
//{
//	// TODO: Add your control notification handler code here
//	POSITION pos=m_CarrierInfoList.GetFirstSelectedItemPosition();
//	if (pos == NULL)
//	{
//		AfxMessageBox(_T("请选中列表中的<载波>条目"));
//		return;
//	}
//	else
//	{
//		int nItem = m_CarrierInfoList.GetNextSelectedItem(pos);
//		if (nItem == 0)
//			return;
//		else
//		{
//			m_CarrierInfoList.DeleteItem(nItem);
//			nCarrier=nCarrier-1;
//			if (nItem == 1)
//			{
//				carrierFlg = FALSE;
//				flg1 = false;
//			}
//			else
//			{
//				carrierFlg = TRUE;
//				flg2 = false;
//			}
//			if (nCarrier == 0)
//				carrierFlg = TRUE;
//		}
//	}
//}
void CTabCarrier::update()//参数更新  需要更新
{
	//switch()
	switch(m_configIndex->ProtocolModel)
	{
	case OneA:
		
		m_MFCPropertyGridTwo.ShowWindow(TRUE);
		m_MFCPropertyGridTwoN.ShowWindow(FALSE);///
		break;
	case OneB:
		m_MFCPropertyGridTwo.ShowWindow(TRUE);
		m_MFCPropertyGridTwoN.ShowWindow(FALSE);////
		break;
	case OneG:
		m_MFCPropertyGridTwo.ShowWindow(TRUE);
		m_MFCPropertyGridTwoN.ShowWindow(FALSE);/////ture false  xiugai!!!!!!
		break;
	case OneN:
		m_MFCPropertyGridTwo.ShowWindow(FALSE);
		m_MFCPropertyGridTwoN.ShowWindow(TRUE);////
		break;
	}
	Invalidate();
}
