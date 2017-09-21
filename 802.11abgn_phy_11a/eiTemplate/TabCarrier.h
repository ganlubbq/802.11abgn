#pragma once
#include "config.h"

// CTabCarrier 对话框


class CTabCarrier : public CDialog
{
	DECLARE_DYNAMIC(CTabCarrier)

public:
	CTabCarrier(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTabCarrier();

// 对话框数据
	enum { IDD = IDD_TAB_CARRIER_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
	CMFCPropertyGridCtrl m_MFCPropertyGridTwo;//a/b/g协议参数列表
	CMFCPropertyGridProperty *pGroup11;//基本参数
	CMFCPropertyGridProperty *pGroup12;//波形控制
	CMFCPropertyGridProperty *pGroup13;//OFDM参数

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

	CMFCPropertyGridCtrl m_MFCPropertyGridTwoN;//n参数列表
	CMFCPropertyGridProperty *pGroup14;//基本参数
	CMFCPropertyGridProperty *pGroup15;//波形控制
	CMFCPropertyGridProperty *pGroup16;//模式选择

	CMFCPropertyGridProperty *pPropS15;//波形名称
	CMFCPropertyGridProperty *pPropS16;//总采样点数
	CMFCPropertyGridProperty *pPropS17;//过采样率
	CMFCPropertyGridProperty *pPropS18;//镜像频谱
	CMFCPropertyGridProperty *pPropS19;//正交角度调整
	CMFCPropertyGridProperty *pPropS19a;//频率偏移
	CMFCPropertyGridProperty *pPropS20;//I/Q平衡增益
	CMFCPropertyGridProperty *pPropS21;//协议名称
	CMFCPropertyGridProperty *pPropS22;//波形模式
	CMFCPropertyGridProperty *pPropS23;//带宽
	CMFCPropertyGridProperty *pPropS2300;//帧间间隔
	CMFCPropertyGridProperty *pPropS24;//天线数目
	CMFCPropertyGridProperty *pPropS25;//空时流数目
	CMFCPropertyGridProperty *pPropS26;//帧数目
	CMFCPropertyGridProperty *pPropS27;
	CMFCPropertyGridProperty *pPropS28;
	CMFCPropertyGridProperty *pPropS29;
	CMFCPropertyGridProperty* p_IQ_gain_balanceA;	//IQ平衡增益
	CMFCPropertyGridProperty* p_quadrature_angle_adjustmentA;	//正交角度调制
	CMFCPropertyGridProperty* p_IQ_gain_balanceN;	//IQ平衡增益
	CMFCPropertyGridProperty* p_quadrature_angle_adjustmentN;	//正交角度调制


};
