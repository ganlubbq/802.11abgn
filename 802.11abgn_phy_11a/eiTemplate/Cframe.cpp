// Cframe.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "Cframe.h"
#include "afxdialogex.h"


// Cframe �Ի���

IMPLEMENT_DYNAMIC(Cframe, CDialog)

Cframe::Cframe(CWnd* pParent /*=NULL*/)
	: CDialog(Cframe::IDD, pParent)
{
	m_pic_framediag1 =(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_FRAME_1),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
	m_pic_framediag2 = (HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_FRAME_2),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
	m_pic_framediag3 = (HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_FRAME_3),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
}

Cframe::~Cframe()
{
}

void Cframe::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FRAME_SECLECT_A, m_ComFramediag);
	DDX_Control(pDX, IDC_PICTURE_A, m_pic_framediag);
}


BEGIN_MESSAGE_MAP(Cframe, CDialog)
	ON_CBN_SELCHANGE(IDC_FRAME_SECLECT_A, &Cframe::OnCbnSelchangeFrameSeclect)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// Cframe ��Ϣ�������


BOOL Cframe::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ComFramediag.SetCurSel(1);
	//m_pic_framediag.SetBitmap(m_pic_framediag1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void Cframe::OnCbnSelchangeFrameSeclect()
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


void Cframe::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	CRect   rect;    
	GetClientRect(rect);  
	dc.FillSolidRect(rect,RGB(255,255,255));   //����Ϊ��ɫ����
}
