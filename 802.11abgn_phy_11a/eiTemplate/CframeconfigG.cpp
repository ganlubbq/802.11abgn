// CframeconfigG.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "CframeconfigG.h"
#include "afxdialogex.h"
#include "CframeGeneralG.h"

// CframeconfigG �Ի���

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


// CframeconfigG ��Ϣ�������


void CframeconfigG::OnBnClickedConfigButtonG()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect,RGB(255,255,255));
}


BOOL CframeconfigG::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ComFramediag.ResetContent();
	m_ComFramediag.AddString("General");
	m_ComFramediag.AddString("RTS");
	m_ComFramediag.AddString("CTS");
	m_ComFramediag.SetCurSel(1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CframeconfigG::OnCbnSelchangeConfigSelectG()
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
