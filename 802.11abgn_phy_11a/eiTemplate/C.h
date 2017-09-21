#pragma once

// CC
class CC : public CStatic
{
	DECLARE_DYNAMIC(CC)
public:
	CC();
	virtual ~CC();
private:
	double  m_ValueXRange;//X�����߸���10
	double  m_ValueYRange;//Y����߸���6
	

	double  m_RatioX;//X��̶Ⱥ�ʵ����ʾ�̶ȱ���
	double  m_RatioY;//Y��̶ȱ���
	int     m_BaseXline;//X��Ļ���ֵ
	int     m_BaseYline;//Y��Ļ���ֵ
	double  m_ScaleValueXRange;//X����ʼֵ0
	double  m_ScaleValueYRange;//Y����ʼֵ,0.000001
	
	double  m_ScaleValueYEnd;//�̶�ֵY�����ֵ1
	double  m_dDimX;//���ȿ̶ȼ����λ
	double  m_dDimY;

	int     m_RealBaseYLine;//��ʵֵY����

	float   m_RealValueXInterval;//��ʵ���X������λֵ
public:
	int  m_ScaleValueXEnd;//�̶�ֵX�����ֵ10
	int  m_AllNum;//X���ܵ��� double->int
	int     m_RealValuenSize;//��ʵ���ε���
	double  CCDFNumInter;
	double *pPointArrayWAVE;
	double *pPointArrayCCDF;
	POINT  *pPointArrayBURSTIndex;
	POINT  *pPointArrayWAVEIndex;
	double  m_maxCCDFX;//CCDF���ֵ
	double  m_maxWAVEX;
	double *sumCCDF;//���ڽ���CCDF����ֵ
private:
	CBrush  m_BkBrush;//��ɫ������ˢ
	CBrush  m_CurveBrush;//�����߻�ˢ
	CRect	m_rectCurve;//��������
	CPen    m_PenDarkLine;//���߻���
	CPen    m_PenBrightLine;//���߻���
	CFont   m_FontAxis;//��������
	CPen    m_PenCurveA;//burst���߻���
	CPen    m_PenCurveB;//wave
public:
	BOOL    controlRunDraw;//���Ʊ��
    BOOL    flag_wave;
	BOOL    flag_burst;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	void    ValueTransform(CDC *pDC);//�������豸�����ӳ��ת��
	void    DrawGrid(CDC *pDC);//������
	void    DrawAxis(CDC *pDC);//�̶�
	void    DrawXYtitle(CDC *pDC);//����
	void    DrawCurveA(CDC *pDC);//����	
	void    Update();//����ͼ��
	void    runDraw();//����
	void    waveflag();
	void    burstflag();
};


