// GraphCCDF.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "GraphCCDF.h"


// CGraphCCDF

IMPLEMENT_DYNCREATE(CGraphCCDF, CFormView)

CGraphCCDF::CGraphCCDF()
	: CFormView(CGraphCCDF::IDD)
{
	m_firstCreate = TRUE;
	m_show_id =1;//Ĭ����ʾ��һ������
}

CGraphCCDF::~CGraphCCDF()
{
}

void CGraphCCDF::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_CCDF, m_ccdf[0]);
	DDX_Control(pDX, IDC_STATIC_CCDF2, m_ccdf[1]);
	DDX_Control(pDX, IDC_STATIC_CCDF3, m_ccdf[2]);
	DDX_Control(pDX, IDC_STATIC_CCDF4, m_ccdf[3]);
	DDX_Control(pDX, IDC_COMBO_CCDF, m_comboCCDF);

}

BEGIN_MESSAGE_MAP(CGraphCCDF, CFormView)
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_COMBO_CCDF, &CGraphCCDF::OnSelchangeComboCcdf)
END_MESSAGE_MAP()

//BEGIN_EASYSIZE_MAP(CGraphCCDF)
//	EASYSIZE(IDC_ICON_CCDF,ES_BORDER,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,0)
//	EASYSIZE(IDC_COMBO_CCDF,IDC_ICON_CCDF,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,0)
//	EASYSIZE(IDC_CHECK_GAUSSIAN,IDC_COMBO_CCDF,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,0)
//	EASYSIZE(IDC_CHECK_REF,IDC_CHECK_GAUSSIAN,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,0)
//	EASYSIZE(IDC_STATIC_CCDF,ES_BORDER,IDC_ICON_CCDF,ES_BORDER,ES_BORDER,0)
//END_EASYSIZE_MAP
// CGraphCCDF ���

#ifdef _DEBUG
void CGraphCCDF::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CGraphCCDF::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CGraphCCDF ��Ϣ�������


void CGraphCCDF::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	// TODO: �ڴ˴������Ϣ����������
	/************************************************************************/
	/* CFormView��CDialog�಻ͬ����easysize��ĳ�ʼ������û����initialDialog*/
	/* �����,������Ҫ��onsize������һ�ε��õ�ʱ���ʼ���ú꣬���ڳ�ʼ���ú�*/
	/* ֮���onsize�н��гߴ�仯����Ӧ����									*/
	/* ��:CGraphWAVE�ڴ˴���ʵ�ַ�����ͬ�����Ǳߵĺ����в���׸��			*/
	/************************************************************************/
	//if (m_firstCreate && /*IsWindowVisible()&&*/ GetWindow(GW_CHILD)!=NULL)
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
		SetScrollSizes(MM_TEXT,CSize(0,0));
		CRect rc;
		GetClientRect(&rc);
		//ʵ�����ŵķ��������ڴ��ڳߴ��С��ʱ��������ʾ
		if (rc.Height()<75 || rc.Width()<40)
		{
			m_ccdf[0].ShowWindow(SW_HIDE);
			m_ccdf[1].ShowWindow(SW_HIDE);
			m_ccdf[2].ShowWindow(SW_HIDE);
			m_ccdf[3].ShowWindow(SW_HIDE);
		}else{
			switch(m_show_id){
			case 1:
				{
					m_ccdf[0].ShowWindow(SW_SHOW);
					m_ccdf[0].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_ccdf[0].Invalidate();
					m_ccdf[1].ShowWindow(SW_HIDE);
					m_ccdf[1].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_ccdf[1].Invalidate();
					m_ccdf[2].ShowWindow(SW_HIDE);
					m_ccdf[2].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_ccdf[2].Invalidate();
					m_ccdf[3].ShowWindow(SW_HIDE);
					m_ccdf[3].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_ccdf[3].Invalidate();
					break;
				}
			case 2:
				{
					m_ccdf[0].ShowWindow(SW_HIDE);
					m_ccdf[0].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_ccdf[0].Invalidate();
					m_ccdf[1].ShowWindow(SW_SHOW);
					m_ccdf[1].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_ccdf[1].Invalidate();
					m_ccdf[2].ShowWindow(SW_HIDE);
					m_ccdf[2].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_ccdf[2].Invalidate();
					m_ccdf[3].ShowWindow(SW_HIDE);
					m_ccdf[3].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_ccdf[3].Invalidate();
					break;
				   }
			case 3:
				{
					m_ccdf[0].ShowWindow(SW_HIDE);
					m_ccdf[0].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_ccdf[0].Invalidate();
					m_ccdf[1].ShowWindow(SW_HIDE);
					m_ccdf[1].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_ccdf[1].Invalidate();
					m_ccdf[2].ShowWindow(SW_SHOW);
					m_ccdf[2].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_ccdf[2].Invalidate();
					m_ccdf[3].ShowWindow(SW_HIDE);
					m_ccdf[3].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_ccdf[3].Invalidate();
					break;
				}
			case 4:
				{
					m_ccdf[0].ShowWindow(SW_HIDE);
					m_ccdf[0].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_ccdf[0].Invalidate();
					m_ccdf[1].ShowWindow(SW_HIDE);
					m_ccdf[1].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_ccdf[1].Invalidate();
					m_ccdf[2].ShowWindow(SW_HIDE);
					m_ccdf[2].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_ccdf[2].Invalidate();
					m_ccdf[3].ShowWindow(SW_SHOW);
					m_ccdf[3].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
					m_ccdf[3].Invalidate();
					break;
				}
			}
			
		}
		//ʵ�����ŵķ����������������ſ��ƺ����б�������ͼ�ĸ߶ȹ�С
		//m_ccdf.MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
		//m_ccdf.Invalidate();
	}
	CFormView::ShowScrollBar(SB_BOTH, false);
}


void CGraphCCDF::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	m_comboCCDF.SetCurSel(0);
	CRect rc;
	GetClientRect(&rc);
	m_ccdf[0].ShowWindow(SW_SHOW);
	m_ccdf[0].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
	m_ccdf[1].ShowWindow(SW_HIDE);
	m_ccdf[1].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
	m_ccdf[2].ShowWindow(SW_HIDE);
	m_ccdf[2].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
	m_ccdf[3].ShowWindow(SW_HIDE);
	m_ccdf[3].MoveWindow(3,28,rc.Width()-4,rc.Height()-29);
}


void CGraphCCDF::OnSelchangeComboCcdf()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ����������ѡ��ͬCCDFͼ�л��Ĵ���
	switch(m_comboCCDF.GetCurSel())
	{
	case 0:
		m_ccdf[m_show_id-1].burstflag();
		break;
	case 1:
		m_ccdf[m_show_id-1].waveflag();
		break;
	}
}
