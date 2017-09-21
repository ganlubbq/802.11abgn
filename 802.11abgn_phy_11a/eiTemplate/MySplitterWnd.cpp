// MySplitterWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "MySplitterWnd.h"


// CMySplitterWnd

IMPLEMENT_DYNAMIC(CMySplitterWnd, CSplitterWnd)

CMySplitterWnd::CMySplitterWnd()
{
	m_splitterScale = 0.5; //���������ָ����1:1
}

CMySplitterWnd::~CMySplitterWnd()
{
}


BEGIN_MESSAGE_MAP(CMySplitterWnd, CSplitterWnd)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CMySplitterWnd ��Ϣ�������


void CMySplitterWnd::OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rectArg)
{
	// TODO: �ڴ����ר�ô����/����û���

	CSplitterWnd::OnDrawSplitter(pDC, nType, rectArg);
	if(pDC==NULL)
	{
		RedrawWindow(rectArg,NULL,RDW_INVALIDATE|RDW_NOCHILDREN);
		return;
	}
	if (nType == splitBar)
		pDC->FillSolidRect(rectArg,RGB(237,239,252));
	if (GetRowCount()==2)	//�ж�������ұߵ������ӷָ�ڣ���ʵʱ�������ǰ��������������ռ�ı���
	{
		CRect rc_top,rc_bottom;
		GetPane(0,0)->GetClientRect(&rc_top);
		GetPane(1,0)->GetClientRect(&rc_bottom);
		m_splitterScale = (double)rc_top.Height() / ((double)rc_top.Height() + (double)rc_bottom.Height());
	}
}



void CMySplitterWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	/************************************************************************/
	/*��������ƶ���Ϣ�����Ŀ�������Ʒָ��������÷�Χ����Ϊ���ǵ����������*/
	/*�ָ�����ɣ���������һ���ָ�Ϊһ��һ���ָ�Ϊ���У�ͨ����ȡ�ָ��������*/
	/*�������жϵ�ǰ����Ӧ�˺���������ߵķָ�ڻ����ұߵķָ�ڣ��Ӷ���*/
	/*һ����������λ�ý����ƶ�������										*/
	/*��ǰ�汾�涨���ָ�����Ȳ���С��200���Ҳ������ָ���ĸ߶Ȳ���С��30 */
	/************************************************************************/
	if (GetRowCount()==1)	//ֻ��һ�У����������ָ��
	{
		CRect rect;
		GetClientRect(&rect);
		if (point.x<=200 || point.x>=rect.Width()-35)
		{
			CWnd::OnMouseMove(nFlags,point);
			return;
		}
	}
	if (GetRowCount()==2)	//�����У��������ұߵ��ӷָ��
	{
		CRect rect;
		GetClientRect(&rect);
		if (point.y<=30 || point.y>=(rect.Height()-30))
		{
			CWnd::OnMouseMove(nFlags,point);
			return;
		}
	}
	CSplitterWnd::OnMouseMove(nFlags, point);
}
