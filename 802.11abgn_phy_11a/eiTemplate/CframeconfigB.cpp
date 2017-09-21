// CframeconfigB.cpp : 实现文件
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "CframeconfigB.h"
#include "afxdialogex.h"
#include "CframeGeneralB.h"
#include "define_param.h"
// CframeconfigB 对话框

IMPLEMENT_DYNAMIC(CframeconfigB, CDialog)

CframeconfigB::CframeconfigB(CWnd* pParent /*=NULL*/)
	: CDialog(CframeconfigB::IDD, pParent)
{
	m_pic_framediag1 =(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_FRAME_CONFIG_1),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
	m_pic_framediag2 = (HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_FRAME_CONFIG_2),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
	m_pic_framediag3 = (HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_FRAME_CONFIG_3),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
}

CframeconfigB::~CframeconfigB()
{
}

void CframeconfigB::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONFIG_SELECT_B, m_ComFramediag);
	DDX_Control(pDX, IDC_CONFIG_PICTURE_B, m_pic_framediag);
}


BEGIN_MESSAGE_MAP(CframeconfigB, CDialog)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_CONFIG_SELECT_B, &CframeconfigB::OnCbnSelchangeConfigSelectB)
	ON_BN_CLICKED(IDC_BUTTON1, &CframeconfigB::OnBnClickedButtonConfig)
END_MESSAGE_MAP()


// CframeconfigB 消息处理程序


void CframeconfigB::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	CRect   rect;    
	GetClientRect(rect);  
	dc.FillSolidRect(rect,RGB(255,255,255));   //设置为白色背景
}


BOOL CframeconfigB::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_ComFramediag.ResetContent();
	m_ComFramediag.AddString("General");
	m_ComFramediag.AddString("RTS");
	m_ComFramediag.AddString("CTS");
	m_ComFramediag.SetCurSel(1);
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CframeconfigB::OnCbnSelchangeConfigSelectB()
{
	// TODO: 在此添加控件通知处理程序代码
	switch (m_ComFramediag.GetCurSel())
	{
	case 0:
		m_pic_framediag.SetBitmap(m_pic_framediag1);
		break;
	case 1:
		m_pic_framediag.SetBitmap(m_pic_framediag2);
		break;
	case 2:
		m_pic_framediag.SetBitmap(m_pic_framediag3);
		break;
	default:
		break;
	}
}


void CframeconfigB::OnBnClickedButtonConfig()
{
	// TODO: 在此添加控件通知处理程序代码
	CframeGeneralB m_frameGeneralB;
	switch (m_ComFramediag.GetCurSel())
	{
	case 0:
		m_frameGeneralB.frametype = CTS;
		break;
	case 1:
		m_frameGeneralB.frametype=General;
		break;
	case 2:
		m_frameGeneralB.frametype=RTS;
		break;
	default:
		break;
	}
	m_frameGeneralB.DoModal();
}
