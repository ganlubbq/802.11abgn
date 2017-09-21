// CframeG.cpp : 实现文件
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "CframeG.h"
#include "afxdialogex.h"


// CframeG 对话框

IMPLEMENT_DYNAMIC(CframeG, CDialog)

CframeG::CframeG(CWnd* pParent /*=NULL*/)
	: CDialog(CframeG::IDD, pParent)
{
	m_pic_framediag1 =(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_FRAME_1),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
	m_pic_framediag2 = (HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_FRAME_2),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
	m_pic_framediag3 = (HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_FRAME_3),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
}

CframeG::~CframeG()
{
}

void CframeG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FRAME_SELECT_G, m_ComFramediag);
	DDX_Control(pDX, IDC_PICTURE_G, m_pic_framediag);

}


BEGIN_MESSAGE_MAP(CframeG, CDialog)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_FRAME_SELECT_G, &CframeG::OnCbnSelchangeFrameSelectG)
END_MESSAGE_MAP()


// CframeG 消息处理程序


void CframeG::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	CRect   rect;    
	GetClientRect(rect);  
	dc.FillSolidRect(rect,RGB(255,255,255));   //设置为白色背景
}


BOOL CframeG::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ComFramediag.ResetContent();
	m_ComFramediag.AddString("General");
	m_ComFramediag.AddString("RTS");
	m_ComFramediag.AddString("CTS");
	m_ComFramediag.SetCurSel(1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CframeG::OnCbnSelchangeFrameSelectG()
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
