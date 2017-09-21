// W.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "W.h"
#include "math.h"

// CW

IMPLEMENT_DYNAMIC(CW, CStatic)

CW::CW()
{
	
	m_PowerFlg           = FALSE;//���ѡ��Ĳ�������0:����; 1:I+Q; 2:I|Q; 3:Ƶ��
	m_SpectrumFlg        = FALSE;
	m_IandQFlg           = FALSE;
	m_IorQFlg            = FALSE;

	controlRunDraw       = FALSE;
	m_ValueXRange        = 12;//X�����߸���
	m_ValueYRange        = 7;//Y����߸���

	I_Data               =NULL;
	Q_Data               =NULL;
	pPointArrayPower     = NULL;
	pPointArrayPowerIndex= NULL;
	pPointArraySpectrum  = NULL;
	pPointArraySpectrumIndex  = NULL;
	pPointArrayIndexA    = NULL;
	pPointArrayIndexB    = NULL;

	m_dDimY	             = 5.0;//y��̶ȵ�λ
	m_dDimX	             = 1.0;//x��̶ȵ�λ
	m_ScaleValueYRange   = -(m_dDimY*m_ValueYRange);//Y����ʼֵ
	m_ScaleValueXRange   = 0;//X����ʼֵ
	m_ScaleValueXEnd     = 0;//X�����ֵ
	m_ScaleValueYEnd     = 0;//Y�����ֵ
	m_IQ_range           = 1;

	m_RealYRange         =m_dDimY*m_ValueYRange;

	m_RealBaseYLine      = 0;//Y����ʵֵ���߳�ʼ��
	m_RealBaseYLine2     = 0;
	m_RealValuenSize     = 0;//�������ߵ�����ʼ��
	BWL                  = 0;
	BWR                  = 0;
	BW					 = 20;

	m_BkBrush.CreateSolidBrush(RGB(0,0,0));//��������ɫ
	m_CurveBrush.CreateSolidBrush(RGB(0,0,0));//�����ߣ���ɫ
	m_PenDarkLine.CreatePen(PS_SOLID,0,RGB(0x55,0x55,0x55));//�����ߣ�����
	m_PenBrightLine.CreatePen(PS_SOLID,0,RGB(0xff,0xff,0xff));//�����ߣ�����

	m_PenCurveA.CreatePen(PS_SOLID,1,RGB(255,100,0));//���߻���
	m_PenCurveB.CreatePen(PS_SOLID,1,RGB(0,0,255));//���߻���
	m_PenCurvePower.CreatePen(PS_SOLID,1,RGB(220,220,0));//Power����
	m_PenCurveSpec.CreatePen(PS_SOLID,1,RGB(0,128,0));//Ƶ�׻���

	m_FontAxis.CreateFont(18,0,0,0,FW_THIN,FALSE,FALSE,FALSE,DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T("΢���ź�"));

}

CW::~CW()
{
}

BEGIN_MESSAGE_MAP(CW, CStatic)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CW ��Ϣ�������
// WM_ERASEBKGND
BOOL CW::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect rect;
	GetClientRect(&rect);//��ȡ�û�����
	pDC->FillRect(&rect,&m_BkBrush);//Draw ��ɫ�����ײ�
	return CStatic::OnEraseBkgnd(pDC);
}

//OnPaint()�е���Update()
void CW::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	CRect rc;
	GetClientRect(&rc);//��ȡ�û�����
	rc.InflateRect(0,0,0,0);//curve panel////curve panelȷ����ʾ��Ĵ�С��λ��
	m_rectCurve = rc;//��ʾ����
	//curve areaȷ����������Ĵ�С���������ϡ��ҡ���
	m_rectCurve.InflateRect(-60,-40,-5,-30);
	//��ʼ�������
	CDC *pDC = GetDC();//��ȡ��ǰCwnd Client��DC
	ValueTransform(pDC);//����ת��
	DrawGrid(pDC);//����
	DrawAxis(pDC);//�̶�
	DrawXYtitle(pDC);//����
	if (controlRunDraw)
	{
		Update();          //��������
	}

	// ��Ϊ��ͼ��Ϣ���� CStatic::OnPaint()
}

/*************************************************
// ������: 
// ������������:
// �������: 
// �������:
// Called By: 
// ����˵��:
// �޸�����: 2017/04/20��10:51:42
*************************************************/
void CW::ValueTransform(CDC *pDC)
{
	m_RatioX = m_rectCurve.Width()/m_ValueXRange;//����X�����
	m_RatioY = m_rectCurve.Height()/m_ValueYRange;//����Y�����
	m_RatioY_IorQ=((double)(m_rectCurve.Height()-30))/m_IQ_range/4.0;
	m_BaseXline = m_rectCurve.left;
	m_BaseYline = m_rectCurve.bottom;//XY�����
	m_RealValueXInterval = 1.0*m_rectCurve.Width()/(double)m_RealValuenSize;////��ʵ���X������λֵ
	m_FFT_RealValueXInterval=1.0*m_rectCurve.Width()/(double)m_FFT_AllNum;//FFT��
}
//�����������
void CW::DrawGrid(CDC *pDC)
{
	CPen *pOldPen = pDC->SelectObject(&m_PenDarkLine);//����m_PenDarkLineΪĬ�ϻ���	

	if(m_PowerFlg||m_SpectrumFlg)
	{
		int i;
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.top);
		pDC->LineTo(m_rectCurve.left,m_rectCurve.bottom);
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.top);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.top);//�ð��߹��������������Ա�Ч��

		pDC->MoveTo(m_rectCurve.left,m_rectCurve.bottom);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom);	//���ƺ������

		int nPosY;

		//������
		for(i=1;i<m_ValueYRange;i++)
		{
			nPosY = m_BaseYline-i*m_RatioY;
			if(nPosY<m_rectCurve.bottom)
			{
				pDC->MoveTo(m_rectCurve.left,nPosY);
				pDC->LineTo(m_rectCurve.right,nPosY);
			}
		}

		//������
		for(i=1;i<=m_ValueXRange;i++)
		{
			if(m_rectCurve.left+i*m_RatioX<m_rectCurve.right)//����һ���жϣ��������ұߵ���λ�ò�������ͼ����
			{
				pDC->MoveTo(m_rectCurve.left+i*m_RatioX,m_rectCurve.top);
				pDC->LineTo(m_rectCurve.left+i*m_RatioX,m_rectCurve.bottom);
			}
		}

		//Y��ĸ���С����
		for(i=1;i<=m_ValueYRange*2;i++)
		{
			if (m_rectCurve.top+i*m_RatioY*0.5<m_rectCurve.bottom)
			{
				pDC->MoveTo(m_BaseXline,m_rectCurve.top+i*m_RatioY*0.5);
				pDC->LineTo(m_BaseXline+4,m_rectCurve.top+i*m_RatioY*0.5);
			}
		}
		//X�Ḩ��С����
		for(i=1;i<=m_ValueXRange*2;i++)
		{
			if(m_rectCurve.left+0.5*i*m_RatioX<m_rectCurve.right)
			{
				pDC->MoveTo(m_rectCurve.left+0.5*i*m_RatioX,m_BaseYline-4);
				pDC->LineTo(m_rectCurve.left+0.5*i*m_RatioX,m_BaseYline);
			}
		}

		//�����߹��������������Ա�Ч��
		pDC->SelectObject(&m_PenBrightLine);//������
		pDC->MoveTo(m_rectCurve.right,m_rectCurve.top);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom);
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.bottom);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom);

		pDC->SelectObject(&pOldPen);//�ͷŻ���
	}
	else if (m_IandQFlg)
	{
		int m;
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.top);
		pDC->LineTo(m_rectCurve.left,m_rectCurve.bottom);
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.top);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.top);//�ð��߹��������������Ա�Ч��

		pDC->MoveTo(m_rectCurve.left,m_BaseYline);
		pDC->LineTo(m_rectCurve.right,m_BaseYline);	//���ƺ������

		int nPosYM;

		//Y��ĸ���С����
		for(m=1;m<=7;m++)
		{
			pDC->MoveTo(m_BaseXline,m_BaseYline-m*(m_rectCurve.Height()/8));
			pDC->LineTo(m_BaseXline+4,m_BaseYline-m*(m_rectCurve.Height()/8));
		}
		//X�Ḩ��С����
		for(m=1;m<=m_ValueXRange*2;m++)
		{
			if(m_rectCurve.left+0.5*m*m_RatioX<m_rectCurve.right)
			{
				pDC->MoveTo(m_rectCurve.left+0.5*m*m_RatioX,m_BaseYline-4);
				pDC->LineTo(m_rectCurve.left+0.5*m*m_RatioX,m_BaseYline);
			}
		}

		//������
		for(m=1;m<4;m++)
		{
			nPosYM = m_BaseYline-m*(m_rectCurve.Height()/4);
			if(nPosYM<m_rectCurve.bottom)
			{
				pDC->MoveTo(m_rectCurve.left,nPosYM);
				pDC->LineTo(m_rectCurve.right,nPosYM);
			}
		}

		//������
		for(m=1;m<=m_ValueXRange;m++)
		{
			if(m_rectCurve.left+m*m_RatioX<m_rectCurve.right)
			{
				pDC->MoveTo(m_rectCurve.left+m*m_RatioX,m_rectCurve.top);
				pDC->LineTo(m_rectCurve.left+m*m_RatioX,m_rectCurve.bottom);
			}
		}

		//�����߹��������������Ա�Ч��	
		pDC->SelectObject(&m_PenBrightLine);//������
		pDC->MoveTo(m_rectCurve.right,m_rectCurve.top);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom);
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.bottom);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom);

		pDC->SelectObject(&pOldPen);//�ͷŻ���
	}
	else
	{
		// I/Q �������30������
		//�²�����
		pDC->MoveTo(m_rectCurve.left,m_BaseYline);
		pDC->LineTo(m_rectCurve.left,m_BaseYline-m_rectCurve.Height()/2+15);
		pDC->MoveTo(m_rectCurve.left,m_BaseYline-m_rectCurve.Height()/2+15);
		pDC->LineTo(m_rectCurve.right,m_BaseYline-m_rectCurve.Height()/2+15);//�ð��߹��������������Ա�Ч��

		pDC->MoveTo(m_rectCurve.left,m_BaseYline);
		pDC->LineTo(m_rectCurve.right,m_BaseYline);	//���ƺ������

		//�ϲ�����
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.top);
		pDC->LineTo(m_rectCurve.left,m_rectCurve.top+m_rectCurve.Height()/2-15);
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.top);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.top);//�ð��߹��������������Ա�Ч��

		pDC->MoveTo(m_rectCurve.left,m_rectCurve.top+m_rectCurve.Height()/2-15);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.top+m_rectCurve.Height()/2-15);	//���ƺ������*/

		//�²����� ������
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.bottom-(m_rectCurve.Height()-30)/4);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom-(m_rectCurve.Height()-30)/4);

		//�²����� ������
		for(int i=1;i<=m_ValueXRange;i++)
		{
			if(m_rectCurve.left+i*m_RatioX<m_rectCurve.right)
			{
				pDC->MoveTo(m_rectCurve.left+i*m_RatioX,m_BaseYline);
				pDC->LineTo(m_rectCurve.left+i*m_RatioX,m_BaseYline-m_rectCurve.Height()/2+15);
			}
		}

		//�ϲ����� ������
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.top+(m_rectCurve.Height()-30)/4);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.top+(m_rectCurve.Height()-30)/4);

		//�ϲ����� ������
		for(int j=1;j<=m_ValueXRange;j++)
		{
			if(m_rectCurve.left+j*m_RatioX<m_rectCurve.right)
			{
				pDC->MoveTo(m_rectCurve.left+j*m_RatioX,m_rectCurve.top);
				pDC->LineTo(m_rectCurve.left+j*m_RatioX,m_rectCurve.top+2*((m_rectCurve.Height()-30)/4));
			}
		}

		//�����߹��������������Ա�Ч��	
		//�²�����
		pDC->SelectObject(&m_PenBrightLine);
		pDC->MoveTo(m_rectCurve.right,m_BaseYline-m_rectCurve.Height()/2+15);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom);
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.bottom);
		pDC->LineTo(m_rectCurve.right,m_rectCurve.bottom);
		//�ϲ�����
		pDC->SelectObject(&m_PenBrightLine);
		pDC->MoveTo(m_rectCurve.right,m_rectCurve.top+2*((m_rectCurve.Height()-30)/4));
		pDC->LineTo(m_rectCurve.right,m_rectCurve.top);
		pDC->MoveTo(m_rectCurve.left,m_rectCurve.top+2*((m_rectCurve.Height()-30)/4));
		pDC->LineTo(m_rectCurve.right,m_rectCurve.top+2*((m_rectCurve.Height()-30)/4));	

		pDC->SelectObject(&pOldPen);//�ͷŻ���
	}
}

////��ֵ�̶ȱ��
void CW::DrawAxis(CDC *pDC)
{
	CFont *pOldFont;
	int j,nPosY;
	CString str;
	pOldFont = pDC->SelectObject(&m_FontAxis);//���õ�ǰ����Ĭ��ΪAxis���������壩
	//����Ĭ����ɫΪ��ɫ��������ɫ��,Ĭ������Ϊ͸��,Ĭ���ı�ģʽ���Ҷ��룬���߶��룩
	pDC->SetTextColor(RGB(255,255,255));
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextAlign(TA_RIGHT|TA_BASELINE);

	if (m_PowerFlg)
	{
		//Y����ʼֵ
		if (abs(m_ScaleValueYRange)<1)
			str.Format(_T("%.1fdB"),m_ScaleValueYRange);
		else
			str.Format(_T("%.0fdB"),m_ScaleValueYRange);
		pDC->TextOut(m_BaseXline-6,m_BaseYline,str);

		//������
		for(j=1;j<=m_ValueYRange;j++)
		{
			if(m_BaseYline-j*m_RatioY<=m_rectCurve.bottom)
			{
				if(abs(m_dDimY)<1)
					str.Format(_T("%.1fdB"),j*m_dDimY+m_ScaleValueYRange);
				else
					str.Format(_T("%.0f"),j*m_dDimY+m_ScaleValueYRange);
				pDC->TextOut(m_rectCurve.left-6,m_BaseYline-j*m_RatioY+6,str);
			}

			/**********************************************************************/
            //��¼�̶�ֵΪ0�ĵ��λ��
			/**********************************************************************/
			if (j*m_dDimY+m_ScaleValueYRange==0)
			{
				m_RealBaseYLine = m_BaseYline-j*m_RatioY;
			}
		}

		//������
		//X����ʼֵ
		if (abs(m_ScaleValueXRange)<1&&m_ScaleValueXRange!=0)
			str.Format(_T("%.1f"),m_ScaleValueXRange);
		else
			str.Format(_T("%.0f"),m_ScaleValueXRange);
		pDC->TextOut(m_BaseXline+5,m_BaseYline+15,str);
	}
	else if (m_SpectrumFlg)
	{
		//Y����ʼֵ
		if (abs(m_ScaleValueYRange)<1)
			str.Format(_T("%.1fdB"),m_ScaleValueYRange);
		else
			str.Format(_T("%.0fdB"),m_ScaleValueYRange);
		pDC->TextOut(m_BaseXline-6,m_BaseYline,str);

		//������
		for(j=1;j<=m_ValueYRange;j++)
		{
			if(m_BaseYline-j*m_RatioY<=m_rectCurve.bottom)
			{
				if(abs(m_dDimY)<1)
					str.Format(_T("%.1fdB"),j*m_dDimY+m_ScaleValueYRange);
				else
					str.Format(_T("%.0f"),j*m_dDimY+m_ScaleValueYRange);
				pDC->TextOut(m_rectCurve.left-6,m_BaseYline-j*m_RatioY+6,str);
			}//���ȿ̶ȵı�ʾ��ʽ
			/**********************************************************************/
			//��¼�̶�ֵΪ0�ĵ��λ��
			/**********************************************************************/
			if (j*m_dDimY+m_ScaleValueYRange==0)
			{
				m_RealBaseYLine = m_BaseYline-j*m_RatioY;
			}
		}

		//������
		//X����ʼֵ
		if (abs(m_ScaleValueXRange)<1&&m_ScaleValueXRange!=0)
			str.Format(_T("%.1f"),m_ScaleValueXRange);
		else
			str.Format(_T("%.0f"),m_ScaleValueXRange);
		pDC->TextOut(m_BaseXline+5,m_BaseYline+15,str);

		//X�����ֵ
		double span =0.0;
		if (controlRunDraw){
			 span = BW/((BWR-BWL)*1.0/m_FFT_AllNum);
			 str.Format("%.2fM",span);
		}
		else{
			str.Format("0");
		}
		pDC->TextOut(m_BaseXline+m_rectCurve.Width()-6,m_BaseYline+15,str);
	}
	else if (m_IandQFlg)
	{
		//������
		CString str_1,str_2,str_3,str_4;
		str_1.Format("%.1f",m_IQ_range);
		str_2.Format("-%.1f",m_IQ_range);
		str_3.Format("%.2f",m_IQ_range/2);
		str_4.Format("-%.2f",m_IQ_range/2);
		pDC->TextOut(m_BaseXline-6,m_BaseYline,str_2);
		pDC->TextOut(m_BaseXline-6,m_BaseYline-m_rectCurve.Height()/4+4,str_4);
		pDC->TextOut(m_BaseXline-6,m_BaseYline-m_rectCurve.Height()/2,_T("0"));
		pDC->TextOut(m_BaseXline-6,m_BaseYline-3*(m_rectCurve.Height()/4)+4,str_3);
		pDC->TextOut(m_BaseXline-6,m_BaseYline-m_rectCurve.Height()+4,str_1);
		//������
		//X����ʼֵ
		if (abs(m_ScaleValueXRange)<1&&m_ScaleValueXRange!=0)
			str.Format(_T("%.1f"),m_ScaleValueXRange);
		else
			str.Format(_T("%.0f"),m_ScaleValueXRange);
		pDC->TextOut(m_BaseXline+5,m_BaseYline+15,str);
		//X�����ֵ
		str.Format("%.0f",m_ScaleValueXEnd);
		pDC->TextOut(m_BaseXline+m_rectCurve.Width()-10,m_BaseYline+15,str);
		/**********************************************************************/
		//��¼�̶�ֵΪ0�ĵ��λ��
		/**********************************************************************/
		m_RealBaseYLine = m_rectCurve.bottom-m_rectCurve.Height()/2;
	}
	else //�ڳ�ʼ����Ϊm_IorQFlg==false�¿����Ȼ���I/Q����
	{
		nPosY = m_BaseYline-m_rectCurve.Height()/2-20;

		CString str_1,str_2;
		str_1.Format("%.1f",m_IQ_range);
		str_2.Format("-%.1f",m_IQ_range);
		double m_IorQ=(m_rectCurve.Height()-30)/4;
		//�²�Q������
		pDC->TextOut(m_BaseXline-6,m_BaseYline+3,str_2);
		pDC->TextOut(m_BaseXline-6,m_BaseYline-m_IorQ+3,_T("0"));
		pDC->TextOut(m_BaseXline-6,m_BaseYline-2*m_IorQ+3,str_1);

		//�ϲ�I������
		pDC->TextOut(m_BaseXline-6,m_BaseYline-2*m_IorQ-30+3,str_2);
		pDC->TextOut(m_BaseXline-6,m_BaseYline-3*m_IorQ-30+3,_T("0"));
		pDC->TextOut(m_BaseXline-6,m_BaseYline-4*m_IorQ-30+3,str_1);

		//������
		//X����ʼֵ
		if (abs(m_ScaleValueXRange)<1&&m_ScaleValueXRange!=0)
			str.Format(_T("%.1f"),m_ScaleValueXRange);
		else
			str.Format(_T("%.0f"),m_ScaleValueXRange);
		pDC->TextOut(m_BaseXline+5,m_BaseYline+15,str);
		//X�����ֵ
		//Q
		str.Format("%.0f",m_ScaleValueXEnd);
		pDC->TextOut(m_BaseXline+m_rectCurve.Width()-10,m_BaseYline+15,str);
		//I
		str.Format("%.0f",m_ScaleValueXEnd);
		pDC->TextOut(m_BaseXline+m_rectCurve.Width()-10,m_BaseYline-2*m_IorQ-30+15,str);
		//Y����ʵֵ����
		m_RealBaseYLine = m_BaseYline-3*m_IorQ-30;
		m_RealBaseYLine2 = m_BaseYline-m_IorQ;
	}
	
}

////XY���������
void CW::DrawXYtitle(CDC *pDC)//XY���������
{
	CFont *pOldFont;
	CString str;
	CString Titalstr;
	CString XMaxstr;
	CString Otherstr;

	pOldFont = pDC->SelectObject(&m_FontAxis);//���õ�ǰ����Ĭ��ΪAxis���������壩
	pDC->SetTextColor(RGB(255,255,255));//����Ĭ����ɫΪ��������ɫ��
	pDC->SetBkMode(TRANSPARENT);//����Ĭ������Ϊ͸��
	pDC->SetTextAlign(TA_LEFT|TA_TOP);//����Ĭ���ı�Ϊ����룬�ö�
	pDC->SetTextAlign(TA_CENTER|TA_TOP);

	
	if (m_PowerFlg)
	{
		//X�����
		pOldFont = pDC->SelectObject(&m_FontAxis);//���õ�ǰ����Ĭ��ΪAxis���������壩
		pDC->SetTextColor(RGB(255,255,0));//����Ĭ����ɫΪ��������ɫ��
		Titalstr=_T("����");
		pDC->TextOut(m_BaseXline+20,m_BaseYline-m_rectCurve.Height()-25,Titalstr);
	}
	else if (m_SpectrumFlg)
	{
		pOldFont = pDC->SelectObject(&m_FontAxis);//���õ�ǰ����Ĭ��ΪAxis���������壩
		pDC->SetTextColor(RGB(0,128,0));//����Ĭ����ɫΪ��������ɫ��
		Titalstr=_T("Ƶ��");
		pDC->TextOut(m_BaseXline+20,m_BaseYline-m_rectCurve.Height()-25,Titalstr);
	}
	else if (m_IandQFlg)
	{
		pOldFont = pDC->SelectObject(&m_FontAxis);//���õ�ǰ����Ĭ��ΪAxis���������壩
		pDC->SetTextColor(RGB(200,100,0));//����Ĭ����ɫΪ��������ɫ��
		Titalstr=_T("I");
		pDC->TextOut(m_BaseXline+10,m_BaseYline-m_rectCurve.Height()-20,Titalstr);

		pOldFont = pDC->SelectObject(&m_FontAxis);//���õ�ǰ����Ĭ��ΪAxis���������壩
		pDC->SetTextColor(RGB(255,255,255));//����Ĭ����ɫΪ��������ɫ��
		Titalstr=_T("+");
		pDC->TextOut(m_BaseXline+20,m_BaseYline-m_rectCurve.Height()-20,Titalstr);

		pOldFont = pDC->SelectObject(&m_FontAxis);//���õ�ǰ����Ĭ��ΪAxis���������壩
		pDC->SetTextColor(RGB(0,0,255));//����Ĭ����ɫΪ��������ɫ��
		Titalstr=_T("Q");
		pDC->TextOut(m_BaseXline+30,m_BaseYline-m_rectCurve.Height()-20,Titalstr);

	}
	else
	{
		pOldFont = pDC->SelectObject(&m_FontAxis);//���õ�ǰ����Ĭ��ΪAxis���������壩
		pDC->SetTextColor(RGB(200,100,0));//����Ĭ����ɫΪ��������ɫ��
		Titalstr=_T("I");
		pDC->TextOut(m_BaseXline+10,m_BaseYline-m_rectCurve.Height()-20,Titalstr);

		pOldFont = pDC->SelectObject(&m_FontAxis);//���õ�ǰ����Ĭ��ΪAxis���������壩
		pDC->SetTextColor(RGB(255,255,255));//����Ĭ����ɫΪ��������ɫ��
		Titalstr=_T("|");
		pDC->TextOut(m_BaseXline+20,m_BaseYline-m_rectCurve.Height()-20,Titalstr);

		pOldFont = pDC->SelectObject(&m_FontAxis);//���õ�ǰ����Ĭ��ΪAxis���������壩
		pDC->SetTextColor(RGB(0,0,255));//����Ĭ����ɫΪ��������ɫ��
		Titalstr=_T("Q");
		pDC->TextOut(m_BaseXline+30,m_BaseYline-m_rectCurve.Height()-20,Titalstr);
	}

}

//���Ʋ��κ���
void CW::DrawCurveA(CDC *pDC)
{
	CString str;
	//�����׻��ƹ���
	if (m_PowerFlg)
	{
		CPen *pOldPen = pDC->SelectObject(&m_PenCurvePower);//���õ�ǰ����Ϊm_PenCurveA

		pPointArrayPowerIndex =(POINT *) new POINT[m_RealValuenSize];//�趨һ������
		for (int i=0;i<m_RealValuenSize;i++)
		{
			pPointArrayPowerIndex[i].x = m_BaseXline+i*m_RealValueXInterval;
			pPointArrayPowerIndex[i].y = m_rectCurve.top+pPointArrayPower[i].y*(-m_rectCurve.Height()/m_RealYRange);
			
			if ( pPointArrayPowerIndex[i].y > m_rectCurve.bottom)
			{
				pPointArrayPowerIndex[i].y=m_rectCurve.bottom;
			}
		}
		
		pDC->Polyline(pPointArrayPowerIndex,m_RealValuenSize);//��������ߵĵ�ȫ�����Ƴ���
		pDC->SelectObject(pOldPen);//�ͷŻ���
		pDC->SelectClipRgn(NULL);//��������Ϊ��������

	}
	//Ƶ�׻��ƹ���
	else if (m_SpectrumFlg)
	{
		CPen *pOldPen = pDC->SelectObject(&m_PenCurveSpec);//���õ�ǰ����Ϊm_PenCurveA
		pPointArraySpectrumIndex =(POINT *) new POINT[m_FFT_AllNum];//�趨һ������
		for (int i=0;i<m_FFT_AllNum;i++)
		{
			pPointArraySpectrumIndex[i].x = m_BaseXline+i*m_FFT_RealValueXInterval;
			pPointArraySpectrumIndex[i].y = m_rectCurve.top+pPointArraySpectrum[i].y*(-m_rectCurve.Height()/m_RealYRange);
			
			if (pPointArraySpectrumIndex[i].y  > m_RealBaseYLine+m_rectCurve.Height())
			{
				pPointArraySpectrumIndex[i].y=m_rectCurve.bottom;
			}
		}
		
		pDC->Polyline(pPointArraySpectrumIndex,m_FFT_AllNum);//��������ߵĵ�ȫ�����Ƴ���
		pDC->SelectObject(pOldPen);//�ͷŻ���
		pDC->SelectClipRgn(NULL);
	}
	//I+Q���ƹ���
	else if (m_IandQFlg)
	{
		CPen *pOldPen = pDC->SelectObject(&m_PenCurveA);//���õ�ǰ����Ϊm_PenCurveA

		// I·��ͼ
		pPointArrayIndexA =(POINT *) new POINT[m_RealValuenSize];//�趨һ������

		for (int i=0;i<m_RealValuenSize;i++)
		{
			pPointArrayIndexA[i].x = m_BaseXline+i*m_RealValueXInterval;
			pPointArrayIndexA[i].y = m_RealBaseYLine+I_Data[i]*(-m_rectCurve.Height()/m_IQ_range/2.0);
			
		}
		
		pDC->Polyline(pPointArrayIndexA,m_RealValuenSize);//��������ߵĵ�ȫ�����Ƴ���
		pDC->SelectObject(pOldPen);//�ͷŻ���
		pDC->SelectClipRgn(NULL);

		CPen *pOldPenB = pDC->SelectObject(&m_PenCurveB);//���õ�ǰ����Ϊm_PenCurveB

		pPointArrayIndexB =(POINT *) new POINT[m_RealValuenSize];//�趨һ������
		for (int j=0;j<=m_RealValuenSize;j++)
		{
			pPointArrayIndexB[j].x = m_BaseXline+j*m_RealValueXInterval;
			pPointArrayIndexB[j].y = m_RealBaseYLine+Q_Data[j]*(-m_rectCurve.Height()/m_IQ_range/2.0);
			
		}
		
		pDC->Polyline(pPointArrayIndexB,m_RealValuenSize);//��������ߵĵ�ȫ�����Ƴ���
		pDC->SelectObject(pOldPenB);//�ͷŻ���
		pDC->SelectClipRgn(NULL);
	}
	//I|Q���ƹ���
	else
	{
		CPen *pOldPen = pDC->SelectObject(&m_PenCurveA);//���õ�ǰ����Ϊm_PenCurveA

		pPointArrayIndexA =(POINT *) new POINT[m_RealValuenSize];//�趨һ������

		for (int i=0;i<=m_RealValuenSize;i++)
		{
			pPointArrayIndexA[i].x = m_BaseXline+i*m_RealValueXInterval;
			pPointArrayIndexA[i].y = m_RealBaseYLine+I_Data[i]*(-m_RatioY_IorQ);
			if( pPointArrayIndexA[i].y >= m_rectCurve.top+2*((m_rectCurve.Height()-30)/4))
				pPointArrayIndexA[i].y =m_rectCurve.top+2*((m_rectCurve.Height()-30)/4)-2;
			if( pPointArrayIndexA[i].y <= m_rectCurve.top)
				pPointArrayIndexA[i].y =m_rectCurve.top+1;
		}
		
		pDC->Polyline(pPointArrayIndexA,m_RealValuenSize);//��������ߵĵ�ȫ�����Ƴ���
		pDC->SelectObject(pOldPen);//�ͷŻ���
		pDC->SelectClipRgn(NULL);

		CPen *pOldPenB = pDC->SelectObject(&m_PenCurveB);//���õ�ǰ����Ϊm_PenCurveB

		pPointArrayIndexB =(POINT *) new POINT[m_RealValuenSize];//�趨һ������
		for (int j=0;j<m_RealValuenSize;j++)
		{
			pPointArrayIndexB[j].x = m_BaseXline+j*m_RealValueXInterval;
			pPointArrayIndexB[j].y = m_RealBaseYLine2+Q_Data[j]*(-m_RatioY_IorQ);
			if( pPointArrayIndexB[j].y >= m_BaseYline)
				pPointArrayIndexB[j].y =m_BaseYline-1;
			/*if( pPointArrayIndexB[j].y <=  m_RealBaseYLine2-m_RatioY_IorQ)
			pPointArrayIndexB[j].y =m_RealBaseYLine2-m_RatioY_IorQ+1;*/
		}
		
		pDC->Polyline(pPointArrayIndexB,m_RealValuenSize);//��������ߵĵ�ȫ�����Ƴ���
		pDC->SelectObject(pOldPenB);//�ͷŻ���
		pDC->SelectClipRgn(NULL);
	}
}
//�϶����ڴ�С�ߴ�ʱ���߻��Ƹ��¹���
void CW::Update()
{
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);//��ȡ�ͻ�����

    //����ǰ��������Ϊλͼ����memDC��
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);//��������dc
	CBitmap bitmap,*pOldBmp;
   //�����µĿͻ�����С��������λͼ
	bitmap.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());
   //��λͼbitmap���ݸ�memDC
	pOldBmp = memDC.SelectObject(&bitmap);
   //���»���
	DrawGrid(&memDC);//���û�������
	DrawAxis(&memDC);//���û��ƿ̶�
	DrawXYtitle(&memDC);//����
	DrawCurveA(&memDC);//��������
	

    //��λͼ���Ƶ�dc��
	dc.BitBlt(m_rectCurve.left,m_rectCurve.top,m_rectCurve.Width(),m_rectCurve.Height(),
		&memDC,m_rectCurve.left,m_rectCurve.top,SRCCOPY);
	memDC.SelectObject(pOldBmp);//�ͷŵ�ǰλͼ	
}
//���������Ƿ���л��Ƶ��ⲿ�ӿں���
void CW::runDraw()
{
	controlRunDraw = TRUE;
	Invalidate();  //���ڸ���ʱ�ػ汳��
}
//��������ѡ��
void CW::PowerFlg()
{
	m_PowerFlg      = TRUE;
	m_SpectrumFlg   = FALSE;
	m_IandQFlg      = FALSE;
	m_IorQFlg       = FALSE;
	runDraw();
}
//Ƶ������ѡ��
void CW::SpectrumFlg()
{
	m_PowerFlg      = FALSE;
	m_SpectrumFlg   = TRUE;
	m_IandQFlg      = FALSE;
	m_IorQFlg       = FALSE;
	runDraw();
}
//I+Q����ѡ��
void CW::IandQFlg()
{
	m_PowerFlg      = FALSE;
	m_SpectrumFlg   = FALSE;
	m_IandQFlg      = TRUE;
	m_IorQFlg       = FALSE;
	runDraw();
}
//I|Q����ѡ��
void CW::IorQFlg()
{
	m_PowerFlg      = FALSE;
	m_SpectrumFlg   = FALSE;
	m_IandQFlg      = FALSE;
	m_IorQFlg       = TRUE;
	runDraw();
}
//����ڴ�
void CW::AllClear()
{
	delete []I_Data;//���յ�
	delete []Q_Data;
	delete []pPointArrayPower;
	delete []pPointArrayPowerIndex;
	delete []pPointArraySpectrum;
	delete []pPointArraySpectrumIndex;
	delete []pPointArrayIndexA;
	delete []pPointArrayIndexB;
	/*pPointArray = NULL;
	pPointArrayPower = NULL;//���յ�
	pPointArrayPowerIndex = NULL;
	pPointArraySpectrum = NULL;
	pPointArraySpectrumIndex = NULL;
	pPointArrayIndexA = NULL;
	pPointArrayIndexB = NULL;*/
}