
// eiTemplateView.h : CeiTemplateView ��Ľӿ�
//

#pragma once

#include "eiTemplateDoc.h"

class CeiTemplateView : public CView
{
protected: // �������л�����
	CeiTemplateView();
	DECLARE_DYNCREATE(CeiTemplateView)

// ����
public:
	CeiTemplateDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CeiTemplateView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
};

#ifndef _DEBUG  // eiTemplateView.cpp �еĵ��԰汾
inline CeiTemplateDoc* CeiTemplateView::GetDocument() const
   { return reinterpret_cast<CeiTemplateDoc*>(m_pDocument); }
#endif

