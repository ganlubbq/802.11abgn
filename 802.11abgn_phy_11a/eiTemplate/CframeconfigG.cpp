// CframeconfigG.cpp : 实现文件
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "CframeconfigG.h"
#include "afxdialogex.h"
#include "CframeGeneralG.h"

// CframeconfigG 对话框

IMPLEMENT_DYNAMIC(CframeconfigG, CDialogEx)

CframeconfigG::CframeconfigG(CWnd* pParent /*=NULL*/)
	: CDialogEx(CframeconfigG::IDD, pParent)
{
	m_pic_framediag1 =(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_FRAME_CONFIG_1),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
	m_pic_framediag2 = (HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_FRAME_CONFIG_2),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
	m_pic_framediag3 = (HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_FRAME_CONFIG_3),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
}

CframeconfigG::~CframeconfigG()
{
}

void CframeconfigG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONFIG_SELECT_G, m_ComFramediag);
	DDX_Control(pDX, IDC_CONFIG_PICTURE_G, m_pic_framediag);
}


BEGIN_MESSAGE_MAP(CframeconfigG, CDialogEx)
	ON_BN_CLICKED(IDC_CONFIG_BUTTON_G, &CframeconfigG::OnBnClickedConfigButtonG)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_CONFIG_SELECT_G, &CframeconfigG::OnCbnSelchangeConfigSelectG)
END_MESSAGE_MAP()


// CframeconfigG 消息处理程序


void CframeconfigG::OnBnClickedConfigButtonG()
{
	// TODO: 在此添加控件通知处理程序代码
	CframeGeneralG m_generalG;
	switch (m_ComFramediag.GetCurSel())
	{
	case 0:
		m_generalG.frametype = CTS;
		break;
	case 1:
		m_generalG.frametype=General;
		break;
	case 2:
		m_generalG.frametype=RTS;
		break;
	default:
		break;
	}
	m_generalG.DoModal();
}


void CframeconfigG::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect,RGB(255,255,255));
}


BOOL CframeconfigG::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ComFramediag.ResetContent();
	m_ComFramediag.AddString("General");
	m_ComFramediag.AddString("RTS");
	m_ComFramediag.AddString("CTS");
	m_ComFramediag.SetCurSel(1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CframeconfigG::OnCbnSelchangeConfigSelectG()
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
