
// eiTemplateView.cpp : CeiTemplateView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "eiTemplate.h"
#endif

#include "eiTemplateDoc.h"
#include "eiTemplateView.h"
#include "MySplitterWnd.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CeiTemplateView

IMPLEMENT_DYNCREATE(CeiTemplateView, CView)

BEGIN_MESSAGE_MAP(CeiTemplateView, CView)
	ON_WM_SIZE()
	ON_WM_SIZING()
END_MESSAGE_MAP()

// CeiTemplateView ����/����

CeiTemplateView::CeiTemplateView()
{
	// TODO: �ڴ˴���ӹ������

}

CeiTemplateView::~CeiTemplateView()
{
}

BOOL CeiTemplateView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CeiTemplateView ����

void CeiTemplateView::OnDraw(CDC* /*pDC*/)
{
	CeiTemplateDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CeiTemplateView ���

#ifdef _DEBUG
void CeiTemplateView::AssertValid() const
{
	CView::AssertValid();
}

void CeiTemplateView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CeiTemplateDoc* CeiTemplateView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CeiTemplateDoc)));
	return (CeiTemplateDoc*)m_pDocument;
}
#endif //_DEBUG


// CeiTemplateView ��Ϣ�������


void CeiTemplateView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	//MessageBox("size��");
}


void CeiTemplateView::OnSizing(UINT fwSide, LPRECT pRect)
{
	CView::OnSizing(fwSide, pRect);

	// TODO: �ڴ˴������Ϣ����������
	//MessageBox("sizing��");
}
