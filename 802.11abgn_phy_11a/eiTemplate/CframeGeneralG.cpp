// CframeGeneralG.cpp : 实现文件
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "CframeGeneralG.h"
#include "afxdialogex.h"
#include "define_param.h"

// CframeGeneralG 对话框

IMPLEMENT_DYNAMIC(CframeGeneralG, CDialog)

CframeGeneralG::CframeGeneralG(CWnd* pParent /*=NULL*/)
	: CDialog(CframeGeneralG::IDD, pParent)
{

}

CframeGeneralG::~CframeGeneralG()
{
}

void CframeGeneralG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CframeGeneralG, CDialog)
END_MESSAGE_MAP()


// CframeGeneralG 消息处理程序


BOOL CframeGeneralG::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rc;
	GetClientRect(&rc);
	//rc.bottom = 100;
	rc.left = 0;
	//rc.right = 100;
	rc.top = 0;
	m_MFCPropertyGrid_Mac_General.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,rc,this,IDD_GENERAL);
	m_MFCPropertyGrid_Mac_General.EnableHeaderCtrl(FALSE,_T("参数"),_T("值"));
	m_MFCPropertyGrid_Mac_General.EnableDescriptionArea();
	m_MFCPropertyGrid_Mac_General.SetDescriptionRows(3);
	m_MFCPropertyGrid_Mac_General.SetVSDotNetLook();
	m_MFCPropertyGrid_Mac_General.MarkModifiedProperties();
	m_MFCPropertyGrid_Mac_General.SetAlphabeticMode(false); 
	m_MFCPropertyGrid_Mac_General.SetShowDragContext();

	/************************GENERAL**************************/
	pGroup_General = new CMFCPropertyGridProperty(_T("General"));
	m_MFCPropertyGrid_Mac_General.AddProperty(pGroup_General);
	pProp1 = new CMFCPropertyGridProperty(_T("帧控制"),_T("0000"),_T("frame control"));
	pGroup_General->AddSubItem(pProp1);
	pProp2 = new CMFCPropertyGridProperty(_T("Duration ID"),_T("0000"),_T("Duration ID"));
	pGroup_General->AddSubItem(pProp2);
	pProp3 = new CMFCPropertyGridProperty(_T("地址1"),_T("0000000000000000"),_T("address1"));
	pGroup_General->AddSubItem(pProp3);
	pProp4 = new CMFCPropertyGridProperty(_T("地址2"),_T("0000000000000000"),_T("address2"));
	pGroup_General->AddSubItem(pProp4);
	pProp5 = new CMFCPropertyGridProperty(_T("地址3"),_T("0000000000000000"),_T("address3"));
	pGroup_General->AddSubItem(pProp5);
	pProp6 = new CMFCPropertyGridProperty(_T("Seq Control"),_T("0000"),_T("Seq Control"));
	pGroup_General->AddSubItem(pProp6);
	pProp7 = new CMFCPropertyGridProperty(_T("地址4"),_T("0000000000000000"),_T("adress4"));
	pGroup_General->AddSubItem(pProp7);
	pProp8 = new CMFCPropertyGridProperty(_T("Qos Control"),_T("0000"),_T("Qos Control"));
	pGroup_General->AddSubItem(pProp8);
	pProp9 = new CMFCPropertyGridProperty(_T("HT Control"),_T("0000"),_T("HT Control"));
	pGroup_General->AddSubItem(pProp9);

	pGroup_RTS = new CMFCPropertyGridProperty("RTS");
	m_MFCPropertyGrid_Mac_General.AddProperty(pGroup_RTS);
	pProp10 = new CMFCPropertyGridProperty(_T("帧控制"),_T("0000"),_T("frame control"));
	pGroup_RTS->AddSubItem(pProp10);
	pProp11 = new CMFCPropertyGridProperty(_T("Duration ID"),_T("0000"),_T("Duration ID"));
	pGroup_RTS->AddSubItem(pProp11);
	pProp12 = new CMFCPropertyGridProperty(_T("RA"),_T("000000000000"),_T("RA"));
	pGroup_RTS->AddSubItem(pProp12);
	pProp13 = new CMFCPropertyGridProperty(_T("TA"),_T("000000000000"),_T("TA"));
	pGroup_RTS->AddSubItem(pProp13);

	pGroup_CTS = new CMFCPropertyGridProperty("CTS");
	m_MFCPropertyGrid_Mac_General.AddProperty(pGroup_CTS);
	pProp14 = new CMFCPropertyGridProperty(_T("帧控制"),_T("0000"),_T("frame control"));
	pGroup_CTS->AddSubItem(pProp14);
	pProp15 = new CMFCPropertyGridProperty(_T("Duration ID"),_T("0000"),_T("Duration ID"));
	pGroup_CTS->AddSubItem(pProp15);
	pProp16 = new CMFCPropertyGridProperty(_T("RA"),_T("000000000000"),_T("RA"));
	pGroup_CTS->AddSubItem(pProp16);

	switch(frametype){
	case General:
		pGroup_General->Show(TRUE);
		pGroup_RTS->Show(FALSE);
		pGroup_CTS->Show(FALSE);
		break;
	case RTS:
		pGroup_General->Show(FALSE);
		pGroup_RTS->Show(TRUE);
		pGroup_CTS->Show(FALSE);
		break;
	case CTS:
		pGroup_General->Show(FALSE);
		pGroup_RTS->Show(FALSE);
		pGroup_CTS->Show(TRUE);
		break;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
