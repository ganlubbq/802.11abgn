// GraphWAVE.cpp : 实现文件
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "GraphWAVE.h"


// CGraphWAVE

IMPLEMENT_DYNCREATE(CGraphWAVE, CFormView)

	CGraphWAVE::CGraphWAVE()
	: CFormView(CGraphWAVE::IDD)
{
	 m_show_id=1;
	//m_firstCreate = TRUE;
}

CGraphWAVE::~CGraphWAVE()
{
}

//从对话框控件获取变量值
void CGraphWAVE::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_WAVE, m_comboWAVE);
	DDX_Control(pDX, IDC_STATIC_WAVE, m_wave[0]);
	DDX_Control(pDX, IDC_STATIC_WAVE2,m_wave[1]);
	DDX_Control(pDX, IDC_STATIC_WAVE3,m_wave[2]);
	DDX_Control(pDX, IDC_STATIC_WAVE4,m_wave[3]);
}

BEGIN_MESSAGE_MAP(CGraphWAVE, CFormView)
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_COMBO_WAVE, &CGraphWAVE::OnSelchangeComboWave)
END_MESSAGE_MAP()

//BEGIN_EASYSIZE_MAP(CGraphWAVE)
//	EASYSIZE(IDC_ICON_WAVE,ES_BORDER,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,0)
//	EASYSIZE(IDC_COMBO_WAVE,IDC_ICON_WAVE,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,0)
//	EASYSIZE(IDC_STATIC_WAVE,ES_BORDER,IDC_ICON_WAVE,ES_BORDER,ES_BORDER,0)
//END_EASYSIZE_MAP
// CGraphWAVE 诊断

#ifdef _DEBUG
void CGraphWAVE::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CGraphWAVE::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CGraphWAVE 消息处理程序


void CGraphWAVE::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	//if (m_firstCreate && IsWindowVisible()&& GetWindow(GW_CHILD)!=NULL)
	//{
	//	INIT_EASYSIZE;
	//	m_firstCreate = FALSE;
	//	SetScrollSizes(MM_TEXT,CSize(0,0));
	//	UPDATE_EASYSIZE;
	//}else if (!m_firstCreate)
	//{
	//	SetScrollSizes(MM_TEXT,CSize(0,0));
	//	UPDATE_EASYSIZE;
	//}
	if (IsWindowVisible() && GetWindow(GW_CHILD)!=NULL)
	{
		SetScrollSizes(MM_TEXT,CSize(0,0));//设置坐标映射方式，滚动栏大小
		CRect rc;
		GetClientRect(&rc);
		if (rc.Height()<60 || rc.Width()<40)
		{
			m_wave[0].ShowWindow(SW_HIDE);
			m_wave[1].ShowWindow(SW_HIDE);
			m_wave[2].ShowWindow(SW_HIDE);
			m_wave[3].ShowWindow(SW_HIDE);
		}else{
			switch(m_show_id){
			case 1:
				{
					m_wave[0].ShowWindow(SW_SHOW);
					m_wave[0].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_wave[0].Invalidate();//在WM_PAINT消息前发送WM_ERASEBKGND,擦除背景
					m_wave[1].ShowWindow(SW_HIDE);
					m_wave[1].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_wave[1].Invalidate();//在WM_PAINT消息前发送WM_ERASEBKGND,擦除背景
					m_wave[2].ShowWindow(SW_HIDE);
					m_wave[2].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_wave[2].Invalidate();//在WM_PAINT消息前发送WM_ERASEBKGND,擦除背景
					m_wave[3].ShowWindow(SW_HIDE);
					m_wave[3].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_wave[3].Invalidate();//在WM_PAINT消息前发送WM_ERASEBKGND,擦除背景
					break;
				}
			case 2:
				{
					m_wave[0].ShowWindow(SW_HIDE);
					m_wave[0].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_wave[0].Invalidate();//在WM_PAINT消息前发送WM_ERASEBKGND,擦除背景
					m_wave[1].ShowWindow(SW_SHOW);
					m_wave[1].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_wave[1].Invalidate();//在WM_PAINT消息前发送WM_ERASEBKGND,擦除背景
					m_wave[2].ShowWindow(SW_HIDE);
					m_wave[2].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_wave[2].Invalidate();//在WM_PAINT消息前发送WM_ERASEBKGND,擦除背景
					m_wave[3].ShowWindow(SW_HIDE);
					m_wave[3].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_wave[3].Invalidate();//在WM_PAINT消息前发送WM_ERASEBKGND,擦除背景
					break;
				}
			case 3:
				{
					m_wave[0].ShowWindow(SW_HIDE);
					m_wave[0].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_wave[0].Invalidate();//在WM_PAINT消息前发送WM_ERASEBKGND,擦除背景
					m_wave[1].ShowWindow(SW_HIDE);
					m_wave[1].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_wave[1].Invalidate();//在WM_PAINT消息前发送WM_ERASEBKGND,擦除背景
					m_wave[2].ShowWindow(SW_SHOW);
					m_wave[2].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_wave[2].Invalidate();//在WM_PAINT消息前发送WM_ERASEBKGND,擦除背景
					m_wave[3].ShowWindow(SW_HIDE);
					m_wave[3].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_wave[3].Invalidate();//在WM_PAINT消息前发送WM_ERASEBKGND,擦除背景
					break;
				}
			case 4:
				{
					m_wave[0].ShowWindow(SW_HIDE);
					m_wave[0].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_wave[0].Invalidate();//在WM_PAINT消息前发送WM_ERASEBKGND,擦除背景
					m_wave[1].ShowWindow(SW_HIDE);
					m_wave[1].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_wave[1].Invalidate();//在WM_PAINT消息前发送WM_ERASEBKGND,擦除背景
					m_wave[2].ShowWindow(SW_HIDE);
					m_wave[2].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_wave[2].Invalidate();//在WM_PAINT消息前发送WM_ERASEBKGND,擦除背景
					m_wave[3].ShowWindow(SW_SHOW);
					m_wave[3].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_wave[3].Invalidate();//在WM_PAINT消息前发送WM_ERASEBKGND,擦除背景
					break;
				}
			}
			
		}
	}
	CFormView::ShowScrollBar(SB_BOTH, false);
}


void CGraphWAVE::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	CRect rc;
	GetClientRect(&rc);
	m_wave[0].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
	m_wave[1].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
	m_wave[2].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
	m_wave[3].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
	m_wave[1].ShowWindow(SW_HIDE);
	m_wave[2].ShowWindow(SW_HIDE);
	m_wave[3].ShowWindow(SW_HIDE);
	// TODO: 在此添加专用代码和/或调用基类
	m_comboWAVE.SetCurSel(0);
}

//波形选择消息的响应函数
void CGraphWAVE::OnSelchangeComboWave()
{
	// TODO: 在此添加控件通知处理程序代码
	switch(m_comboWAVE.GetCurSel())
	{
	case 0:
		//processingStructure.m_ScopeImportIndex.runDraw();
		m_wave[m_show_id-1].IorQFlg();
		break;
	case 1:
		//processingStructure.m_ScopeImportIndex.runDraw();
		m_wave[m_show_id-1].IandQFlg();
		break;
	case 2:
		//processingStructure.m_ScopeImportIndex.runDraw();
		m_wave[m_show_id-1].PowerFlg();
		break;
	case 3:
		//processingStructure.m_ScopeImportIndex.runDraw();
		m_wave[m_show_id-1].SpectrumFlg();
		break;
	}
}