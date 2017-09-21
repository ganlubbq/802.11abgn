// CframeConfig.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "CframeConfig.h"
#include "afxdialogex.h"
#include "FrameGeneral.h"
#include "define_param.h"

// CframeConfig �Ի���

IMPLEMENT_DYNAMIC(CframeConfig, CDialog)

CframeConfig::CframeConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CframeConfig::IDD, pParent)
{
	m_pic_framediag1 =(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_FRAME_CONFIG_1),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
	m_pic_framediag2 = (HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_FRAME_CONFIG_2),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
	m_pic_framediag3 = (HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_FRAME_CONFIG_3),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
}

CframeConfig::~CframeConfig()
{
}

void CframeConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONFIG_SELECT, m_ComFramediag);
	DDX_Control(pDX, IDC_CONFIG_PICTURE, m_pic_framediag);
}


BEGIN_MESSAGE_MAP(CframeConfig, CDialog)
	ON_CBN_SELCHANGE(IDC_CONFIG_SELECT, &CframeConfig::OnCbnSelchangeFrameSeclect)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CONFIG, &CframeConfig::OnBnClickedConfig)
END_MESSAGE_MAP()


// CframeConfig ��Ϣ�������
BOOL CframeConfig::OnInitDialog()
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

void CframeConfig::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	CRect   rect;    
	GetClientRect(rect);  
	dc.FillSolidRect(rect,RGB(255,255,255));   //����Ϊ��ɫ����
}
void CframeConfig::OnCbnSelchangeFrameSeclect()
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

void CframeConfig::OnBnClickedConfig()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFrameGeneral m_general;
	switch (m_ComFramediag.GetCurSel())
	{
	case 0:
		m_general.frametype = CTS;
		break;
	case 1:
		m_general.frametype=General;
		break;
	case 2:
		m_general.frametype=RTS;
		break;
	default:
		break;
	}
	m_general.DoModal();
}
