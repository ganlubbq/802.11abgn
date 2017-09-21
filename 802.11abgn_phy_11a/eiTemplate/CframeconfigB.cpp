// CframeconfigB.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "CframeconfigB.h"
#include "afxdialogex.h"
#include "CframeGeneralB.h"
#include "define_param.h"
// CframeconfigB �Ի���

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


// CframeconfigB ��Ϣ�������


void CframeconfigB::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	CRect   rect;    
	GetClientRect(rect);  
	dc.FillSolidRect(rect,RGB(255,255,255));   //����Ϊ��ɫ����
}


BOOL CframeconfigB::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_ComFramediag.ResetContent();
	m_ComFramediag.AddString("General");
	m_ComFramediag.AddString("RTS");
	m_ComFramediag.AddString("CTS");
	m_ComFramediag.SetCurSel(1);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CframeconfigB::OnCbnSelchangeConfigSelectB()
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


void CframeconfigB::OnBnClickedButtonConfig()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
