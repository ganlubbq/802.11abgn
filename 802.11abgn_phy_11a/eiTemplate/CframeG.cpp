// CframeG.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "CframeG.h"
#include "afxdialogex.h"


// CframeG �Ի���

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


// CframeG ��Ϣ�������


void CframeG::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	CRect   rect;    
	GetClientRect(rect);  
	dc.FillSolidRect(rect,RGB(255,255,255));   //����Ϊ��ɫ����
}


BOOL CframeG::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ComFramediag.ResetContent();
	m_ComFramediag.AddString("General");
	m_ComFramediag.AddString("RTS");
	m_ComFramediag.AddString("CTS");
	m_ComFramediag.SetCurSel(1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CframeG::OnCbnSelchangeFrameSelectG()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
