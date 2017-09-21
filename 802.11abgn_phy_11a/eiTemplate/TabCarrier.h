#pragma once
#include "config.h"

// CTabCarrier �Ի���


class CTabCarrier : public CDialog
{
	DECLARE_DYNAMIC(CTabCarrier)

public:
	CTabCarrier(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabCarrier();

// �Ի�������
	enum { IDD = IDD_TAB_CARRIER_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	CFont    m_font;
	BOOL     m_finished_ini;
public:
	virtual BOOL OnInitDialog();
	void update();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnPropertyChanged(__in WPARAM wparam,__in LPARAM lparam);
public:
	config		*m_configIndex;
	CMFCPropertyGridCtrl m_MFCPropertyGridTwo;//a/b/gЭ������б�
	CMFCPropertyGridProperty *pGroup11;//��������
	CMFCPropertyGridProperty *pGroup12;//���ο���
	CMFCPropertyGridProperty *pGroup13;//OFDM����

	CMFCPropertyGridProperty *over_sample;
	CMFCPropertyGridProperty *over_sample_n;
	CMFCPropertyGridProperty *pPropS1;
	CMFCPropertyGridProperty *pPropS2;
	CMFCPropertyGridProperty *pPropS3;
	CMFCPropertyGridProperty *pPropS4;
	CMFCPropertyGridProperty *pPropS5;
	CMFCPropertyGridProperty *pPropS6;
	CMFCPropertyGridProperty *pPropS7;
	CMFCPropertyGridProperty *pPropS8;
	CMFCPropertyGridProperty *pPropS9;
	CMFCPropertyGridProperty *pPropS10;
	CMFCPropertyGridProperty *pPropS11;
	CMFCPropertyGridProperty *pPropS12;
	CMFCPropertyGridProperty *pPropS13;
	CMFCPropertyGridProperty *pPropS14;

	CMFCPropertyGridCtrl m_MFCPropertyGridTwoN;//n�����б�
	CMFCPropertyGridProperty *pGroup14;//��������
	CMFCPropertyGridProperty *pGroup15;//���ο���
	CMFCPropertyGridProperty *pGroup16;//ģʽѡ��

	CMFCPropertyGridProperty *pPropS15;//��������
	CMFCPropertyGridProperty *pPropS16;//�ܲ�������
	CMFCPropertyGridProperty *pPropS17;//��������
	CMFCPropertyGridProperty *pPropS18;//����Ƶ��
	CMFCPropertyGridProperty *pPropS19;//�����Ƕȵ���
	CMFCPropertyGridProperty *pPropS19a;//Ƶ��ƫ��
	CMFCPropertyGridProperty *pPropS20;//I/Qƽ������
	CMFCPropertyGridProperty *pPropS21;//Э������
	CMFCPropertyGridProperty *pPropS22;//����ģʽ
	CMFCPropertyGridProperty *pPropS23;//����
	CMFCPropertyGridProperty *pPropS2300;//֡����
	CMFCPropertyGridProperty *pPropS24;//������Ŀ
	CMFCPropertyGridProperty *pPropS25;//��ʱ����Ŀ
	CMFCPropertyGridProperty *pPropS26;//֡��Ŀ
	CMFCPropertyGridProperty *pPropS27;
	CMFCPropertyGridProperty *pPropS28;
	CMFCPropertyGridProperty *pPropS29;
	CMFCPropertyGridProperty* p_IQ_gain_balanceA;	//IQƽ������
	CMFCPropertyGridProperty* p_quadrature_angle_adjustmentA;	//�����Ƕȵ���
	CMFCPropertyGridProperty* p_IQ_gain_balanceN;	//IQƽ������
	CMFCPropertyGridProperty* p_quadrature_angle_adjustmentN;	//�����Ƕȵ���


};
