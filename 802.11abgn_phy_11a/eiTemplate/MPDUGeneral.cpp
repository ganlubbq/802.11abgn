// MPDUGeneral.cpp : 实现文件
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "MPDUGeneral.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "TabParent.h"
#include "CframeConfig.h"
#include "TabProtocolConfig.h"
#include "MpduPara.h"
// CMPDUGeneral 对话框
int NumOfMpdu;
IMPLEMENT_DYNAMIC(CMPDUGeneral, CDialog)

CMPDUGeneral::CMPDUGeneral(CWnd* pParent /*=NULL*/)
	: CDialog(CMPDUGeneral::IDD, pParent)
{
	m_font.CreatePointFont(100,"微软雅黑");
	
}

CMPDUGeneral::~CMPDUGeneral()
{
}

void CMPDUGeneral::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MPDU_INDEX, m_mpdu_index);
}


BEGIN_MESSAGE_MAP(CMPDUGeneral, CDialog)
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED,OnPropertyChanged)
END_MESSAGE_MAP()


// CMPDUGeneral 消息处理程序


BOOL CMPDUGeneral::OnInitDialog()
{
	CDialog::OnInitDialog();

	data_and_graph* m_pass_to_thread =&(((CMainFrame*)AfxGetMainWnd())->m_pass_to_thread);
	Para_mpdu = &(m_pass_to_thread->m_configNIndex->mpdus[Index]);
	NumOfMpdu = m_pass_to_thread->m_configNIndex->num_of_mpdus;
	CString strVal;
	CString str;
	str.Format("MPDU %d",Index);
	m_mpdu_index.MoveWindow(0,2,100,30);
	m_mpdu_index.SetWindowText(str);
	// TODO:  在此添加额外的初始化
	CRect rc;
	GetClientRect(&rc);
	rc.top+=25;
	p_mpdu_config.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,rc,this,IDD_MPDU_CONFIG);
	p_mpdu_config.EnableHeaderCtrl(FALSE,_T("参数"),_T("值"));
	p_mpdu_config.EnableDescriptionArea();
	p_mpdu_config.SetDescriptionRows(3);
	p_mpdu_config.SetVSDotNetLook();
	p_mpdu_config.MarkModifiedProperties();
	p_mpdu_config.SetAlphabeticMode(false); 
	p_mpdu_config.SetShowDragContext();

	pGroup = new CMFCPropertyGridProperty("MPDU 配置");
	strVal.Format("%d",Para_mpdu->A_Subframe_len);
	p_A_mpdu_len = new CMFCPropertyGridProperty("A-MPDU子帧长度",strVal,"单位：字节",ID_MAPU_AMPDULEN);
	p_A_mpdu_len->Enable(FALSE);
	pGroup->AddSubItem(p_A_mpdu_len);
	
	strVal.Format("%d",Para_mpdu->MPDU_len);
	p_mpdu_len = new CMFCPropertyGridProperty("MPDU长度",strVal,"单位：字节",ID_MPDU_MPDULEN);
	p_mpdu_len->Enable(FALSE);
	pGroup->AddSubItem(p_mpdu_len);
	
	switch(Para_mpdu->s_mode){
	case DPN9:
		strVal = "PN9";
		break;
	case DPN15:
		strVal = "PN15";
		break;
	case DALL0:
		strVal = "ALL0";
		break;
	case DUserFile:
		strVal = "用户自定义";
		break;
	}
	p_data_type = new CMFCPropertyGridProperty("数据类型",strVal,"三种可选数据类型：PN9，PN15,ALL0,用户自定义",ID_MPDU_DATATYPE);
	p_data_type->AddOption("PN9");
	p_data_type->AddOption("PN15");
	p_data_type->AddOption("ALL0");
	p_data_type->AddOption("用户自定义");
	pGroup->AddSubItem(p_data_type);
	
	p_user_file = new CMFCPropertyGridPropertyButton4("用户数据","","");
	p_user_file->Show(FALSE);
	pGroup->AddSubItem(p_user_file);
	
	strVal.Format("%d",Para_mpdu->DataSource_len);
	p_data_source_len = new CMFCPropertyGridProperty("数据长度",strVal,"单位：字节",ID_MPDU_SOURVEDATALEN);
	pGroup->AddSubItem(p_data_source_len);
	
	p_mac_header_text = new CMFCPropertyGridPropertyButton3("MAC Header说明","General","");
	pGroup->AddSubItem(p_mac_header_text);

	if (Para_mpdu->mac_Header==1)
	{
		strVal.Format("General");
		//p_mac_fcs->Enable(TRUE);
	} 
	else if (Para_mpdu->mac_Header==2)
	{
		strVal.Format("RTS");
		//p_mac_fcs->Enable(FALSE);
	}
	else
	{
		strVal.Format("CTS");
		//p_mac_fcs->Enable(FALSE);
	}
	p_mac_header = new CMFCPropertyGridProperty("MAC Header",strVal,"",ID_MPDU_MACHEADER);
	p_mac_header->AddOption("General");
	p_mac_header->AddOption("RTS");
	p_mac_header->AddOption("CTS");
	pGroup->AddSubItem(p_mac_header);
	
	if (Para_mpdu->mac_FCS)
	{
		strVal.Format("On");
	} 
	else
	{
		strVal.Format("Off");
	}
	p_mac_fcs = new CMFCPropertyGridProperty("MAC FCS",strVal,"",ID_MPDU_MACFCS);
	p_mac_fcs->AddOption("On");
	p_mac_fcs->AddOption("Off");
	//p_mac_fcs->Enable(TRUE);
	pGroup->AddSubItem(p_mac_fcs);
	if (Para_mpdu->mac_Header==1)
	{
		//strVal.Format("General");
		p_mac_fcs->Enable(TRUE);
	} 
	else if (Para_mpdu->mac_Header==2)
	{
		//strVal.Format("RTS");
		p_mac_fcs->Enable(FALSE);
	}
	else
	{
		//strVal.Format("CTS");
		p_mac_fcs->Enable(FALSE);
	}
	
	p_ISN = new CMFCPropertyGridProperty("递增序列号","On","");
	p_ISN->AllowEdit(FALSE);
	pGroup->AddSubItem(p_ISN);
	
	p_SNI = new CMFCPropertyGridProperty("序列号递增","1","");
	p_SNI->AllowEdit(FALSE);
	pGroup->AddSubItem(p_SNI);
	
	p_IFN = new CMFCPropertyGridProperty("递增分段号","On","");
	p_IFN->AllowEdit(FALSE);
	pGroup->AddSubItem(p_IFN);
	
	p_mpdu_config.AddProperty(pGroup);
	p_mpdu_config.SetCustomColors(RGB(250,250,250),RGB(0,0,0),RGB(230,230,230),RGB(100,100,100),RGB(230,230,230),RGB(0,0,0),RGB(220,220,220));
	
	CWnd *pWnd = GetTopWindow();  
	while (NULL != pWnd)  
	{  
		pWnd->SetFont(&m_font);  
		pWnd = pWnd->GetNextWindow();  
	}  
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

LRESULT CMPDUGeneral::OnPropertyChanged(__in WPARAM wparam,__in LPARAM lparam)
{
	CMFCPropertyGridProperty* pProp = (CMFCPropertyGridProperty*)lparam; 
	CListCtrl* m_list = &(((CTabParent*)((CMainFrame*)AfxGetMainWnd())->m_mainSplitter.GetPane(0,0))->m_tabProtocolConfig.m_MpduInfoList);
	CTabProtocolConfig cTabProtocolConfig;
	int numOfmpdu=cTabProtocolConfig.NumOfMPDU;
	CString d = pProp->GetValue();
	CString strValue;
	switch(pProp->GetData()){
	case ID_MPDU_DATATYPE:
		if (d=="用户自定义"){
			p_user_file->Show(TRUE);
			m_list->SetItemText(Index,1,"用户自定义");
			Para_mpdu->s_mode = DUserFile;
		}	
		else
			p_user_file->Show(FALSE);
		if(d =="PN9"){
			m_list->SetItemText(Index,1,"PN9");
			Para_mpdu->s_mode = DPN9;
		}
			
		if(d =="PN15"){
			m_list->SetItemText(Index,1,"PN15");
			Para_mpdu->s_mode = DPN15;
		}
			
		if(d =="ALL0"){
			m_list->SetItemText(Index,1,"ALL0");
			Para_mpdu->s_mode = DALL0;
		}
		break;
	case ID_MPDU_MACHEADER:
		if (d=="General")
		{
			Para_mpdu->mac_Header = 1;
			p_mac_fcs->Enable(TRUE);
			Para_mpdu->mac_FCS = 1;
			p_mac_fcs->SetValue("On");
		}
		else if (d=="RTS")
		{
			Para_mpdu->mac_Header = 2;
			p_mac_fcs->Enable(FALSE);
			Para_mpdu->mac_FCS = 1;
			p_mac_fcs->SetValue("On");
		} 
		else
		{
			Para_mpdu->mac_Header = 3;
			p_mac_fcs->Enable(FALSE);
			Para_mpdu->mac_FCS = 1;
			p_mac_fcs->SetValue("On");
		}
		//break;
	case ID_MPDU_MACFCS://FCS
		    
		if (d == "On" || d == "RTS" || d == "CTS" || d == "General")
		{
			Para_mpdu->mac_FCS=1;
		} 
		else
		{
			Para_mpdu->mac_FCS=0;
		}
		//Para_mpdu->mac_FCS = d == "On" ? 1 : 0;
			//strValue.Format("%dByte(s)",mpdulen1);
		if (Para_mpdu->mac_FCS==1)
		{
			m_list->SetItemText(Index,4,"On");
		} 
		else
		{
			m_list->SetItemText(Index,4,"Off");
		}
			
			int mpdulen,a_subframelen,mpdulentmp;
			if (Para_mpdu->mac_FCS==1)//FCS On
			{
				if (Para_mpdu->mac_Header==1)
				{
					mpdulen=Para_mpdu->DataSource_len+34;
				} 
				else if (Para_mpdu->mac_Header==2)
				{
					mpdulen=Para_mpdu->DataSource_len+20;
				} 
				else
				{
					mpdulen=Para_mpdu->DataSource_len+14;
				}
			} 
			else                      //FCS Off
			{
				mpdulen=Para_mpdu->DataSource_len+30;
			}
			

			
			if (NumOfMpdu!=Index && mpdulen%4!=0)//此MPDU不在末尾
			{
				mpdulentmp=mpdulen+(4-mpdulen%4);//向上取整到4的倍数

			} 
			else
			{
				mpdulentmp=mpdulen;//不补充填充字节
			}
			a_subframelen=mpdulentmp+4;//加上分隔部分的4个字节

			char s[10];
			

			strValue.Format("%dByte(s)",mpdulen);
			m_list->SetItemText(Index,5,strValue);
			p_mpdu_len->SetValue(itoa(mpdulen,s,10));
			Para_mpdu->MPDU_len = mpdulen;

			strValue.Format("%dByte(s)",a_subframelen);
			m_list->SetItemText(Index,6,strValue);
			p_A_mpdu_len->SetValue(itoa(a_subframelen,s,10));
			Para_mpdu->A_Subframe_len = a_subframelen;
		break;
	case ID_MPDU_SOURVEDATALEN:
		//CTabProtocolConfig cTabProtocolConfig;
		//int numOfmpdu=cTabProtocolConfig.NumOfMPDU;
		int len = atoi(d);
		int mpdulen1,a_subframelen1,mpdulentmp1;
		if (Para_mpdu->mac_FCS==1)//FCS On
		{
			if (Para_mpdu->mac_Header==1)
			{
				mpdulen1=len+34;
			} 
			else if (Para_mpdu->mac_Header==2)
			{
				mpdulen1=len+20;
			} 
			else
			{
				mpdulen1=len+14;
			}
		} 
		else                      //FCS Off
		{
			mpdulen1=len+30;
		}
		

		
		if (NumOfMpdu!=Index && mpdulen1%4!=0)//此MPDU不在末尾
		{
			mpdulentmp1=mpdulen1+(4-mpdulen1%4);//向上取整到4的倍数

		} 
		else
		{
			mpdulentmp1=mpdulen1;//不补充填充字节
		}
		a_subframelen1=mpdulentmp1+4;//加上分隔部分的4个字节

		char s1[10];
		    strValue.Format("%sByte(s)",d);
		    m_list->SetItemText(Index,2,strValue);
		    Para_mpdu->DataSource_len = len;//数据源长度

		    strValue.Format("%dByte(s)",mpdulen1);
		    m_list->SetItemText(Index,5,strValue);
			p_mpdu_len->SetValue(itoa(mpdulen1,s1,10));
		    Para_mpdu->MPDU_len = mpdulen1;

		    strValue.Format("%dByte(s)",a_subframelen1);
		    m_list->SetItemText(Index,6,strValue);
			p_A_mpdu_len->SetValue(itoa(a_subframelen1,s1,10));
		    Para_mpdu->A_Subframe_len = a_subframelen1;
		break;
		/*case ID_MPDU_MPDULEN:
		strValue.Format("%sByte(s)",d);
		m_list->SetItemText(Index,5,strValue);
		break;
		case ID_MAPU_AMPDULEN:
		strValue.Format("%sByte(s)",d);
		m_list->SetItemText(Index,6,strValue);
		break;*/
	}
	
	return 0;
}

BOOL CMFCPropertyGridPropertyButton3::HasButton() const{
	return TRUE;
}
void CMFCPropertyGridPropertyButton3::OnClickButton(CPoint point){
	m_frame = new CframeConfig();
	m_frame->DoModal();
	delete m_frame;
}
 
BOOL CMFCPropertyGridPropertyButton4::HasButton() const{
	return TRUE;
}
void CMFCPropertyGridPropertyButton4::OnClickButton(CPoint point){
	CString FilePathName;
	CFileDialog dlg(TRUE,NULL, NULL,OFN_FORCESHOWHIDDEN,
		(LPCTSTR)_TEXT("txt files (*.txt)|*.txt||"),NULL);
	if(dlg.DoModal()==IDOK)
	{
		FilePathName=dlg.GetPathName(); //文件名保存在了FilePathName里
		((CMainFrame*)AfxGetMainWnd())->m_pass_to_thread.m_configAIndex->filepath = FilePathName;
		((CTabParent*)((CMainFrame*)AfxGetMainWnd())->m_mainSplitter.GetPane(0,0))->m_tabProtocolConfig.m_mpdu_general->p_user_file->SetValue(FilePathName);
	}
}