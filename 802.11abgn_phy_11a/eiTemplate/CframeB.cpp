// CframeB.cpp : 实现文件
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "CframeB.h"
#include "afxdialogex.h"


// CframeB 对话框

IMPLEMENT_DYNAMIC(CframeB, CDialog)

CframeB::CframeB(CWnd* pParent /*=NULL*/)
	: CDialog(CframeB::IDD, pParent)
{
	m_pic_framediag1 =(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_FRAME_1),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
	m_pic_framediag2 = (HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_FRAME_2),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
	m_pic_framediag3 = (HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_FRAME_3),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
}

CframeB::~CframeB()
{
}

void CframeB::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FRAME_SELECT_B, m_ComFramediag);
	DDX_Control(pDX, IDC_PICTURE_B, m_pic_framediag);
}


BEGIN_MESSAGE_MAP(CframeB, CDialog)
	ON_CBN_SELCHANGE(IDC_FRAME_SELECT_B, &CframeB::OnCbnSelchangeFrameSelectB)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CframeB 消息处理程序


BOOL CframeB::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ComFramediag.SetCurSel(1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CframeB::OnCbnSelchangeFrameSelectB()
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


void CframeB::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	CRect   rect;    
	GetClientRect(rect);  
	dc.FillSolidRect(rect,RGB(255,255,255));   //设置为白色背景
}
