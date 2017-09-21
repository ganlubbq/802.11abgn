// TabCarrier.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "TabCarrier.h"
#include "afxdialogex.h"
#include "TabMac.h"
#include "TabProtocolConfig.h"
#include "TabParent.h"
#include "MainFrm.h"

// CTabCarrier �Ի���

IMPLEMENT_DYNAMIC(CTabCarrier, CDialog)

CTabCarrier::CTabCarrier(CWnd* pParent /*=NULL*/)
	: CDialog(CTabCarrier::IDD, pParent)
{
	m_finished_ini = FALSE;
	m_font.CreatePointFont(100,"΢���ź�");
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


// CTabCarrier ��Ϣ�������


void CTabCarrier::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	// CDialog::OnOK();
}


BOOL CTabCarrier::OnInitDialog()
{
	CDialog::OnInitDialog();
	//�ı���ʾ��Ϣ

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rc;
	GetClientRect(&rc);
	//rc.bottom += 20;
	rc.left += 10;
	//rc.right += 10;
	rc.top += 10;

	//11a/b/gЭ�����
	m_MFCPropertyGridTwo.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,rc,this,2001);
	m_MFCPropertyGridTwo.EnableHeaderCtrl(FALSE,_T("����"),_T("ֵ"));
	m_MFCPropertyGridTwo.EnableDescriptionArea();
	m_MFCPropertyGridTwo.SetDescriptionRows(5);
	m_MFCPropertyGridTwo.SetVSDotNetLook();
	m_MFCPropertyGridTwo.MarkModifiedProperties();
	m_MFCPropertyGridTwo.SetAlphabeticMode(false); 
	m_MFCPropertyGridTwo.SetShowDragContext();

	pGroup11 = new CMFCPropertyGridProperty(_T("��������"));
	pGroup12 = new CMFCPropertyGridProperty(_T("���ο���"));
	pGroup13 = new CMFCPropertyGridProperty(_T("OFDM����"));
	
/*CMFCPropertyGridProperty **/pPropS1=new CMFCPropertyGridProperty(_T("��������"),_T("WLAN"),_T("IEEE 802.11ϵ��֮һ��11a/b/g"));
	pPropS1->Enable(FALSE);
	pGroup11->AddSubItem(pPropS1);
	/*CMFCPropertyGridProperty **/pPropS2=new CMFCPropertyGridProperty(_T("�ܲ�������"),_T("2641"),_T("��������Ŀ"),SAMPLELENGTHA);
	pPropS2->Enable(FALSE);
	pGroup11->AddSubItem(pPropS2);


	over_sample = new CMFCPropertyGridProperty(_T("��������"),_T("1"),"",OVERSAMPLEABG);
	pGroup12->AddSubItem(over_sample);

	/*CMFCPropertyGridProperty* */
	/*pPropS3 = new CMFCPropertyGridProperty(_T("����Ƶ��"),_T("Off"),_T("����Ƶ��״̬��ON��OFF"));
	pPropS3->AddOption(_T("On"));  
	pPropS3->AddOption(_T("Off"));     
	pPropS3->AllowEdit(FALSE);
	pGroup12->AddSubItem(pPropS3);*/
	p_quadrature_angle_adjustmentA = new CMFCPropertyGridProperty(_T("�����Ƕȵ���"),_T("0.00 Deg"),_T("��Χ��-90~+90"),CARRI_QUADRATURE_ANGLE_ADJUSTA);
	pGroup12->AddSubItem(p_quadrature_angle_adjustmentA);

	p_IQ_gain_balanceA = new CMFCPropertyGridProperty(_T("I/Qƽ������"), _T("0.00 dB"), _T("��Χ��-10~+10"),CARRI_IQ_BALANCE_GAINA);
	pGroup12->AddSubItem(p_IQ_gain_balanceA);


	pPropS6=new CMFCPropertyGridProperty(_T("��Ƭʱ��"), _T("50ns"), _T("chip duration,��Ƭʱ�䳤��"));
	pPropS6->Enable(FALSE);
	pGroup13->AddSubItem(pPropS6);
    pPropS7=new CMFCPropertyGridProperty(_T("Nsd"), _T("48"), _T("Number of data subcarriers,�������ز��ĸ���"));
	pPropS7->Enable(FALSE);
	pGroup13->AddSubItem(pPropS7);
	pPropS8=new CMFCPropertyGridProperty(_T("Nsp"), _T("4"), _T("Number of pilot subcarriers,��Ƶ���ز��ĸ���"));
	pPropS8->Enable(FALSE);
	pGroup13->AddSubItem(pPropS8);
	pPropS9=new CMFCPropertyGridProperty(_T("Nst"), _T("52"), _T("Nst=(Nsd+Nsp);Number of subcarriers,total �����ز��ĸ���"));
	pPropS9->Enable(FALSE);
	pGroup13->AddSubItem(pPropS9);
	pPropS10=new CMFCPropertyGridProperty(_T("��������"), _T("20MHz"), _T("�������ʵĴ�С"));
	pPropS10->Enable(FALSE);
	pGroup13->AddSubItem(pPropS10);
    pPropS11=new CMFCPropertyGridProperty(_T("OFDM���ż��"), _T("4us"), _T("���ż���ĳ���(80chip)"));
	pPropS11->Enable(FALSE);
	pGroup13->AddSubItem(pPropS11);
	pPropS12=new CMFCPropertyGridProperty(_T("ѭ��ǰ׺����"), _T("0.8us"), _T("��������ĳ���(16chip)"));
	pPropS12->Enable(FALSE);
	pGroup13->AddSubItem(pPropS12);
	pPropS13=new CMFCPropertyGridProperty(_T("���ز�Ƶ�ʼ��"), _T("0.3125MHz"), _T("���ز�Ƶ�ʼ��(20MHz/64)"));
	pPropS13->Enable(FALSE);
	pGroup13->AddSubItem(pPropS13);
	pPropS14=new CMFCPropertyGridProperty(_T("ѵ�����г���"), _T("16us"), _T("���ز�Ƶ�ʼ��(Tshort+Tlong)"));
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
	m_MFCPropertyGridTwoN.EnableHeaderCtrl(FALSE,_T("����"),_T("ֵ"));
	m_MFCPropertyGridTwoN.EnableDescriptionArea(TRUE);
	m_MFCPropertyGridTwoN.SetDescriptionRows(5);
	m_MFCPropertyGridTwoN.SetVSDotNetLook();
	m_MFCPropertyGridTwoN.MarkModifiedProperties();
	m_MFCPropertyGridTwoN.SetAlphabeticMode(false); 
	m_MFCPropertyGridTwoN.SetShowDragContext();

	pGroup14 = new CMFCPropertyGridProperty(_T("1.��������"));
	pGroup15 = new CMFCPropertyGridProperty(_T("2.���ο���"));
	pGroup16 = new CMFCPropertyGridProperty(_T("3.ģʽѡ��"));

	pPropS15=new CMFCPropertyGridProperty(_T("��������"),_T("WLAN"),_T("IEEE 802.11ϵ��֮һ��11a/b/g"));
	pPropS15->Enable(FALSE);
	pGroup14->AddSubItem(pPropS15);
	pPropS16=new CMFCPropertyGridProperty(_T("�ܲ�������"),_T("1280"),_T("��������Ŀ"),SAMPLELENGTH);
	pPropS16->Enable(FALSE);
	pGroup14->AddSubItem(pPropS16);

	over_sample_n = new CMFCPropertyGridProperty(_T("��������"),_T("1"),_T("���ڹ������ʵ�˵��"),OVERSAMPLEN);
	pGroup15->AddSubItem(over_sample_n);
	/*pPropS17 = new CMFCPropertyGridProperty(_T("����Ƶ��"),_T("Off"),_T("����Ƶ��״̬��ON��OFF"));
	pPropS17->AddOption(_T("On"));  
	pPropS17->AddOption(_T("Off"));     
	pPropS17->AllowEdit(FALSE);
	pGroup15->AddSubItem(pPropS17);*/
	//pGroup15->AddSubItem(new CMFCPropertyGridProperty(_T("�����Ƕȵ���"),_T("0.00 Deg"),_T("���ǲ�����˵��")));
	//pGroup15->AddSubItem(new CMFCPropertyGridProperty(_T("I/Qƽ������"), _T("0.00 dB"), _T("���ǲ�����˵��")));
	p_quadrature_angle_adjustmentN = new CMFCPropertyGridProperty(_T("�����Ƕȵ���"),_T("0.00 Deg"),_T("��Χ��-90~+90"),CARRI_QUADRATURE_ANGLE_ADJUSTN);
	pGroup15->AddSubItem(p_quadrature_angle_adjustmentN);

	p_IQ_gain_balanceN = new CMFCPropertyGridProperty(_T("I/Qƽ������"), _T("0.00 dB"), _T("��Χ��-10~+10"),CARRI_IQ_BALANCE_GAINN);
	pGroup15->AddSubItem(p_IQ_gain_balanceN);
	pPropS19a= new CMFCPropertyGridProperty(_T("Ƶ��ƫ��"),_T("+0.000000 Hz"),_T("����Ƶ��ƫ��"),MFCPROPERTYTOFRN);
	pGroup15->AddSubItem(pPropS19a);
	pPropS18 = new CMFCPropertyGridProperty(_T("Э��"),_T("IEEE 802.11n"),_T("IEEE 802.11ϵ��֮һ��11a/b/g/n"));
	pPropS18->Enable(FALSE);
	pGroup16->AddSubItem(pPropS18);
	pPropS19=new CMFCPropertyGridProperty(_T("����ģʽ"),_T("HT_MM"),_T("���β�����ģʽ:��1��Legacy��2��HT-MM��802.11n�Ļ�ϴ���ģʽ��HT-mixedmode����3��HT-GF��802.11n����Ұģʽ��HT-greenfield����4��non-HT-DUP"),MFCPROPERTYOON);
	pPropS19->AddOption(_T("HT_MM"));
	pPropS19->AddOption(_T("HT_GF")); 
	pPropS19->AddOption(_T("Legacy")); 
	//pPropS19->AddOption(_T("non-HT-DUP"));
	pGroup16->AddSubItem(pPropS19);
	pPropS20=new CMFCPropertyGridProperty(_T("����"),_T("20MHz"),_T("��ѡ20MHz��40MHz"),MFCPROPERTYOSN);
	pPropS20->AddOption(_T("20MHz"));  
	pPropS20->AddOption(_T("40MHz"));
	pGroup16->AddSubItem(pPropS20);
	pPropS21 = new CMFCPropertyGridProperty(_T("������Ŀ"),_T("2"),_T("LegacyģʽΪ1������ѡ��HTģʽΪ1-4"),MFCPROPERTYOTN);
	pPropS21->AddOption("1");pPropS21->AddOption("2");pPropS21->AddOption("3");pPropS21->AddOption("4");
	pPropS21->AllowEdit(FALSE);
	pGroup16->AddSubItem(pPropS21);
	/*pPropS22 = new CMFCPropertyGridProperty(_T("��ʱ����Ŀ"),_T("1"),_T("���ɱ༭���ɳ���������"),MFCPROPERTYOTNSTS);  
	pPropS22->Enable(FALSE);
	pGroup16->AddSubItem(pPropS22);*/
	pPropS23 = new CMFCPropertyGridProperty(_T("֡��Ŀ"),_T("20"),_T("Ĭ��Ϊ20"),MFCPROPERTYOTN1);  
	//pPropS23->Enable(FALSE);
	pGroup16->AddSubItem(pPropS23);
	pPropS2300 = new CMFCPropertyGridProperty(_T("֡����"),_T("10.0"),_T("��λ��s"),MFCPROPERTYOTN2);  
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
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CTabCarrier::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
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
	CString s = pProp->GetName();  //���ı�Ĳ�����  
	COleVariant t = pProp->GetValue(); //�ı�֮���ֵ
	int a = pProp->GetOptionCount();
	CString d;
	d = t.bstrVal;      //��COleVariant��CString 

	regex patten_iqgainbalance("^[-]?\\d+(\\.\\d*)?(dB)?(db)?$",regex::icase);	//������ʽ��֤�����Ƿ���ȷ
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
					SetFocus()->MessageBox("��ǰ���������Ƶ��ƫ��Ϊ+/-58MHz");
					pPropS19a->SetValue("58000");
					//pPropZ6_d->SetValue("58000");
					m_data_and_graph->m_configNIndex->FrequencyOffset = 58000*1000;
					//m_data_and_graph->m_configAIndex->FrequencyOffset = 58000*1000;
				}
				else if(FrequencyOffset < -58000)
				{
					SetFocus()->MessageBox("��ǰ���������Ƶ��ƫ��Ϊ+/-58MHz");
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
		case MFCPROPERTYOSN://����
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
					MessageBox("����Чֵ��","����");
				}

				m_data_and_graph->m_configNIndex->oversample_ratio =oversample;
				break;
			}
       case MFCPROPERTYOTN://������Ŀ��Legacy�����ɱ༭Ĭ��Ϊ1��HT��1-4����
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
					m_tabprotocolconfig.pPropT30->SetValue("�ռ���չ");
					m_data_and_graph->m_configNIndex->ieeeQ =4;
				}else
				{
					m_tabprotocolconfig.pPropT30->Enable(TRUE);
					m_tabprotocolconfig.pPropT30->SetValue("ֱ��ӳ��");
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
	   case MFCPROPERTYOTN1://֡��
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
	   case MFCPROPERTYOTN2://֡����,8��s��Ӧ160������
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
		   d.Remove(' ');//�Ƴ��ո�
		   match_result = regex_match(d.GetBuffer(),patten_quad_deg_ad);//������֤
		   double temp_deg;
		   temp_deg=m_data_and_graph->m_configNIndex->quan_angle_adjust;//p_ADParams��ad��ADParams��ʵ����ע��ÿ���˶�Ӧ�Ĳ�һ����
		   if (match_result)
		   {
			   double quad_angle_ad = atof(d);
			   if (quad_angle_ad > 90)
			   {
				   MessageBox("�����Ƕ���������");
				   quad_angle_ad = 90;
			   }
			   else if (quad_angle_ad < -90)
			   {
				   MessageBox("�����Ƕ���������");
				   quad_angle_ad = -90;
			   }
			   m_data_and_graph->m_configNIndex->quan_angle_adjust = quad_angle_ad;
			   //str_temp.Format(_T("%.2lf Deg"), quad_angle_ad);
			   //pProp->SetValue(str_temp);
		   }
		   else
		   {
			   MessageBox("�����Ƕ���������");
			   //str_temp.Format(_T("0 Deg"));
			   p_quadrature_angle_adjustmentN->SetValue("0 Deg");
			   // // 			
		   }
		   break;
	   case CARRI_IQ_BALANCE_GAINN:
		   d.Remove(' ');//�Ƴ��ո�
		   match_result = regex_match(d.GetBuffer(),patten_iqgainbalance);//������֤
		   double temp_db;
		   temp_db=m_data_and_graph->m_configNIndex->IQ_gain;
		   if (match_result)
		   {
			   double IQ_gain = atof(d);
			   if (IQ_gain > 10)
			   {	IQ_gain = 10;
			   MessageBox("I\Qƽ��������������");   
			   }
			   else if (IQ_gain < -10)
			   {	IQ_gain = -10;
			   MessageBox("I\Qƽ��������������");
			   }
			   m_data_and_graph->m_configNIndex->IQ_gain = IQ_gain;
			   //str_temp.Format(_T("%.2lf dB"), IQ_gain);
			   //pProp->SetValue(str_temp);
		   }
		   else
		   {
			   MessageBox("I\Qƽ��������������");
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
					MessageBox("����Чֵ��","����");
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
			  d.Remove(' ');//�Ƴ��ո�
			  match_result = regex_match(d.GetBuffer(),patten_quad_deg_ad);//������֤
			  double temp_deg;
			  temp_deg=m_data_and_graph->m_configAIndex->quan_angle_adjust;//p_ADParams��ad��ADParams��ʵ����ע��ÿ���˶�Ӧ�Ĳ�һ����
			  if (match_result)
			  {
				  double quad_angle_ad = atof(d);
				  if (quad_angle_ad > 90)
				  {
					  MessageBox("�����Ƕ���������");
					  quad_angle_ad = 90;
				  }
				  else if (quad_angle_ad < -90)
				  {
					  MessageBox("�����Ƕ���������");
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
				  MessageBox("�����Ƕ���������");
				  //str_temp.Format(_T("0 Deg"));
				  p_quadrature_angle_adjustmentA->SetValue("0 Deg");
				  // // 			
			  }
			  break;
		  case CARRI_IQ_BALANCE_GAINA:
			  d.Remove(' ');//�Ƴ��ո�
			  match_result = regex_match(d.GetBuffer(),patten_iqgainbalance);//������֤
			  double temp_db;
			  temp_db=m_data_and_graph->m_configAIndex->IQ_gain;
			  if (match_result)
			  {
				  double IQ_gain = atof(d);
				  if (IQ_gain > 10)
				  {	IQ_gain = 10;
				  MessageBox("I\Qƽ��������������");   
				  }
				  else if (IQ_gain < -10)
				  {	IQ_gain = -10;
				  MessageBox("I\Qƽ��������������");
				  }
				  m_data_and_graph->m_configAIndex->IQ_gain = IQ_gain;
				  m_data_and_graph->m_configBIndex->IQ_gain = IQ_gain;
				  m_data_and_graph->m_configGIndex->IQ_gain = IQ_gain;
				  //str_temp.Format(_T("%.2lf dB"), IQ_gain);
				  //pProp->SetValue(str_temp);
			  }
			  else
			  {
				  MessageBox("I\Qƽ��������������");
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

//�����ز�����ʵ��
//void CTabCarrier::OnBnClickedButton1()
//{
//	// TODO: Add your control notification handler code here
//	nCarrier=nCarrier+1;
//	if (nCarrier == 1)
//	{
//		m_CarrierInfoList.InsertItem(1,_T("�ز� 1"));
//		m_CarrierInfoList.SetItemText(1,1,_T("On"));
//		m_CarrierInfoList.SetItemText(1,2,textInfo(0,m_configIndex));
//		m_CarrierInfoList.SetItemText(1,3,textInfo(1,m_configIndex));
//		m_CarrierInfoList.SetItemText(1,4,_T(" 20.000 MHz"));
//		m_CarrierInfoList.SetItemText(1,5,_T("0.00 dB"));//�����
//
//		flg1 =true;
//	}
//	else if(nCarrier == 2)
//	{
//		if (carrierFlg)
//		{
//			m_CarrierInfoList.InsertItem(2,_T("�ز� 2"));
//			m_CarrierInfoList.SetItemText(2,1,_T("On"));
//			m_CarrierInfoList.SetItemText(2,2,textInfo(0,m_configIndex));
//			m_CarrierInfoList.SetItemText(2,3,textInfo(1,m_configIndex));
//			m_CarrierInfoList.SetItemText(2,4,_T("-20.000 MHz"));
//			m_CarrierInfoList.SetItemText(2,5,_T("0.00 dB"));//�����
//
//			flg2 = true;
//
//		}
//		else
//		{
//			m_CarrierInfoList.InsertItem(1,_T("�ز� 1"));
//			m_CarrierInfoList.SetItemText(1,1,_T("On"));
//			m_CarrierInfoList.SetItemText(1,2,textInfo(0,m_configIndex));
//			m_CarrierInfoList.SetItemText(1,3,textInfo(1,m_configIndex));
//			m_CarrierInfoList.SetItemText(1,4,_T(" 20.000 MHz"));
//			m_CarrierInfoList.SetItemText(1,5,_T("0.00 dB"));//�����
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

//ɾ���ز�����ʵ��
//void CTabCarrier::OnBnClickedButton2()
//{
//	// TODO: Add your control notification handler code here
//	POSITION pos=m_CarrierInfoList.GetFirstSelectedItemPosition();
//	if (pos == NULL)
//	{
//		AfxMessageBox(_T("��ѡ���б��е�<�ز�>��Ŀ"));
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
void CTabCarrier::update()//��������  ��Ҫ����
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
