#pragma once
#include "config.h"
#include "protocol/11a/configA.h"
#include "protocol/11b/configB.h"
#include "protocol/11g/configG.h"
#include "protocol/11n/InterfaceClass.h"
#include "afxwin.h"
#include "MPDUGeneral.h"
// CTabProtocolConfig 对话框

class CTabProtocolConfig : public CDialog
{
	DECLARE_DYNAMIC(CTabProtocolConfig)

public:
	CTabProtocolConfig(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTabProtocolConfig();

// 对话框数据
	enum { IDD = IDD_TAB_PROTOCOL_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnPropertyChanged(__in WPARAM wparam,__in LPARAM lparam);
	void update();//显示列表更新
	void Point();
	BOOL m_finished_ini;
public:
	config		*m_configIndex;
	configA     *m_configAIndex;
	configB     *m_configBIndex;
	configG     *m_configGIndex;
	configN     *m_configNIndex;
	CFont       m_font;
	CListCtrl   m_MpduInfoList;
	int         nMPDU;            //统计MPDU个数
	//11a
	CMFCPropertyGridCtrl     m_MFCPropertyGridThree;
	CMFCPropertyGridProperty *pGroup31;//载波信息
	CMFCPropertyGridProperty *pGroup32;//调制编码
	CMFCPropertyGridProperty *pGroup33;//载荷配置
	CMFCPropertyGridProperty *pGroup34;//频谱控制
	CMFCPropertyGridProperty *pGroup35;//信道

	CMFCPropertyGridProperty *pPropT1;//协议名称
	CMFCPropertyGridProperty *pPropT2;//帧数
	CMFCPropertyGridProperty *pPropT3;//频率偏移
	CMFCPropertyGridProperty *pPropT3a;//帧间间隔
	CMFCPropertyGridProperty *pPropT3b;//子载波数量
	CMFCPropertyGridProperty *pPropT4;//速率
	CMFCPropertyGridProperty *pPropT5;//调制方式
	CMFCPropertyGridProperty *pPropT6;//编码方式
	CMFCPropertyGridProperty *pPropT7;//码率
	CMFCPropertyGridProperty *pPropT8;//交织
	CMFCPropertyGridProperty *pPropT9;//OFDM扰频器
	CMFCPropertyGridProperty *pPropT10;//PSDU
	CMFCPropertyGridProperty *pPropT11;//PPDU
	CMFCPropertyGridProperty *pPropT12;//MAC	
	CMFCPropertyGridProperty *pPropT13;//FCS
	CMFCPropertyGridProperty *pPropT14;//滤波器
	CMFCPropertyGridProperty *filter_user;//用户自定义滤波器
	CMFCPropertyGridProperty *lp_filter_len;
	CMFCPropertyGridProperty *lp_filter_wn;
	CMFCPropertyGridProperty *gauss_filter_len;
	CMFCPropertyGridProperty *gauss_filter_BT;
	CMFCPropertyGridProperty *cosine_filter_len;
	CMFCPropertyGridProperty *cosine_filter_alpha;
	CMFCPropertyGridProperty *pPropT15;//窗口长度
	CMFCPropertyGridProperty *pPropT16;//信道状态
    CMFCPropertyGridProperty *pPropT17;//信道多径数
	CMFCPropertyGridProperty *pPropT18;//信道载频
	CMFCPropertyGridProperty *pPropT19;//移动速度
	CMFCPropertyGridProperty *pPropT20;//Eb/N0
	CMFCPropertyGridProperty *pPropT017;//OFDM扰码器初始值
	CMFCPropertyGridProperty *p_data_source;//数据源
	CMFCPropertyGridProperty *p_data_filepath;//文件路径
	CMFCPropertyGridProperty *p_date_max_len;//数据最大长度
	//11n
	CMFCPropertyGridCtrl     m_MFCPropertyGridThreeN;
	CMFCPropertyGridProperty *pGroup36;//数据包
	CMFCPropertyGridProperty *pGroup37;//调制编码
	CMFCPropertyGridProperty *pGroup38;//载荷配置
	CMFCPropertyGridProperty *pGroup39;//频谱控制
	CMFCPropertyGridProperty *pGroup40;//信道
	CMFCPropertyGridProperty *pGroup41;

	CMFCPropertyGridProperty *pPropT21;//类型
	CMFCPropertyGridProperty *pPropT211;//数据个数
	CMFCPropertyGridProperty *pPropT22;//MCS索引号
	CMFCPropertyGridProperty *pPropT23a;//调制方式流1
	CMFCPropertyGridProperty *pPropT23b;//调制方式流2
	CMFCPropertyGridProperty *pPropT23c;//调制方式流3
	CMFCPropertyGridProperty *pPropT23d;//调制方式流4
	CMFCPropertyGridProperty *pPropT24;//码率
	CMFCPropertyGridProperty *pPropT25;//数据速率
	CMFCPropertyGridProperty *pPropT25a;//Nss
	CMFCPropertyGridProperty *pPropT25b;//STBC
	CMFCPropertyGridProperty *pPropT25c;//Nsts
	CMFCPropertyGridProperty *pPropT25d;//Ness
	CMFCPropertyGridProperty *pPropT26;//传输天线数目
	CMFCPropertyGridProperty *pPropT27;//扩展空间流
	CMFCPropertyGridProperty *pPropT28;//保护间隔
	CMFCPropertyGridProperty *pPropT288;//时域加窗
	CMFCPropertyGridProperty *pPropT29;//波束赋形
	CMFCPropertyGridProperty *pPropT30;//空间映射机制
	CMFCPropertyGridProperty *pPropT31;//信道编码
	CMFCPropertyGridProperty *pPropT32;//交织
	CMFCPropertyGridProperty *pPropT32a;//扰码
	CMFCPropertyGridProperty *pPropT33;//聚合MPDU
	CMFCPropertyGridProperty *pPropT34;//Smoothing
	CMFCPropertyGridProperty *pPropT35;//Sounding
	CMFCPropertyGridProperty *pPropT36;//数据长度
	CMFCPropertyGridProperty *pPropT37;//数据
	CMFCPropertyGridProperty *pPropT38;//时域加窗
	CMFCPropertyGridProperty *pPropT39;//信道模型
	CMFCPropertyGridProperty *pPropT40;//场景选择
	CMFCPropertyGridProperty *pPropT41;////衰落类型
	CMFCPropertyGridProperty *pPropT42;//载波频率
	CMFCPropertyGridProperty *numofNr;
	CMFCPropertyGridProperty *numofNt;
	CMFCPropertyGridProperty *p_data_filepath_n;//文件路径
	CMFCPropertyGridProperty *fitertype_n;
	CMFCPropertyGridProperty *lp_filter_len_n;
	CMFCPropertyGridProperty *lp_filter_wn_n;
	CMFCPropertyGridProperty *gauss_filter_len_n;
	CMFCPropertyGridProperty *gauss_filter_BT_n;
	CMFCPropertyGridProperty *cosine_filter_len_n;
	CMFCPropertyGridProperty *cosine_filter_alpha_n;
	CMFCPropertyGridProperty *filter_user_n;

	//11nLegacy模式
	CMFCPropertyGridCtrl     m_MFCPropertyGridThreeNL;
	CMFCPropertyGridProperty *pGroup47;//调制编码
	CMFCPropertyGridProperty *pGroup48;//载荷配置
	CMFCPropertyGridProperty *pGroup49;//频谱控制
	CMFCPropertyGridProperty *pGroup50;//信道

	CMFCPropertyGridProperty *pPropT43;//类型
	CMFCPropertyGridProperty *pPropT44;//MCS索引号
	CMFCPropertyGridProperty *pPropT45;//调制方式
	CMFCPropertyGridProperty *pPropT46;//码率
	CMFCPropertyGridProperty *pPropT47;//数据速率
	CMFCPropertyGridProperty *pPropT48;//扰码初始值
	CMFCPropertyGridProperty *pPropT49;//信道编码
	CMFCPropertyGridProperty *pPropT50;//交织
	CMFCPropertyGridProperty *pPropT51;//聚合MPDU
	CMFCPropertyGridProperty *pPropT52;//Smoothing
	CMFCPropertyGridProperty *pPropT53;//Sounding
	CMFCPropertyGridProperty *pPropT54;//数据源
	CMFCPropertyGridProperty *pPropT55;//数据长度
	CMFCPropertyGridProperty *pPropT56;//时域加窗
	CMFCPropertyGridProperty *pPropT57;//信道模型
	CMFCPropertyGridProperty *pPropT58;//场景选择
	CMFCPropertyGridProperty *pPropT59;//衰落类型
	CMFCPropertyGridProperty *pPropT60;//载波频率
	CMFCPropertyGridProperty *p_data_filepath_nl;//文件路径
	CMFCPropertyGridProperty *mobilespeed;
	CMFCPropertyGridProperty *carrierfreq;
	CMFCPropertyGridProperty *fitertype_nl;
	CMFCPropertyGridProperty *lp_filter_len_nl;
	CMFCPropertyGridProperty *lp_filter_wn_nl;
	CMFCPropertyGridProperty *gauss_filter_len_nl;
	CMFCPropertyGridProperty *gauss_filter_BT_nl;
	CMFCPropertyGridProperty *cosine_filter_len_nl;
	CMFCPropertyGridProperty *cosine_filter_alpha_nl;
	CMFCPropertyGridProperty *filter_user_nl;

	//11b
	CMFCPropertyGridCtrl     m_MFCPropertyGridThreeB;
	CMFCPropertyGridProperty *pGroup42;//载波参数
	CMFCPropertyGridProperty *pGroup43;//调制编码
	CMFCPropertyGridProperty *pGroup44;//载荷配置
	CMFCPropertyGridProperty *pGroup45;//信道
	CMFCPropertyGridProperty *pGroup46;

	CMFCPropertyGridProperty *pPropT61;//协议名称
	CMFCPropertyGridProperty *pPropT62;//帧数
	CMFCPropertyGridProperty *pPropT63;//帧间隔
	CMFCPropertyGridProperty *pPropT64;//频率偏移
	CMFCPropertyGridProperty *pPropT65;//相对功率
	CMFCPropertyGridProperty *pPropT66;//传输模式
	CMFCPropertyGridProperty *pPropT67;//数据速率
	CMFCPropertyGridProperty *pPropT68;//调试方式
	CMFCPropertyGridProperty *pPropT69;//扰码
	CMFCPropertyGridProperty *pPropT690;//扰码初始值
	CMFCPropertyGridProperty *pPropT70;//前导码类型
	//CMFCPropertyGridProperty *pPropT71;//MPDU长度
	CMFCPropertyGridProperty *pPropT72;//数据长度
	CMFCPropertyGridProperty *pPropT73;//MAC头部
	CMFCPropertyGridProperty *pPropT74;//MAC FCS
	CMFCPropertyGridProperty *fitertype;
	CMFCPropertyGridProperty *lp_filter_len_b;
	CMFCPropertyGridProperty *lp_filter_wn_b;
	CMFCPropertyGridProperty *gauss_filter_len_b;
	CMFCPropertyGridProperty *gauss_filter_BT_b;
	CMFCPropertyGridProperty *cosine_filter_len_b;
	CMFCPropertyGridProperty *cosine_filter_alpha_b;
	CMFCPropertyGridProperty *filter_user_b;
	
	//11g
	CMFCPropertyGridCtrl     m_MFCPropertyGridThreeG;
	CMFCPropertyGridProperty *pGroup51;//载波参数
	CMFCPropertyGridProperty *pGroup52;//调制编码 对应11a
	CMFCPropertyGridProperty *pGroup55;//调制编码 对应11b
	CMFCPropertyGridProperty *pGroup53;//载荷配置
	CMFCPropertyGridProperty *pGroup54;//信道

	CMFCPropertyGridProperty *pPropT75;//协议名称
	CMFCPropertyGridProperty *pPropT76;//帧数
	CMFCPropertyGridProperty *pPropT77;//帧间隔
	CMFCPropertyGridProperty *pPropT78;//频率偏移
	CMFCPropertyGridProperty *pPropT79;//相对功率
	CMFCPropertyGridProperty *pPropT80;//传输模式
	CMFCPropertyGridProperty *p_data_source_g;//MPDU长度
	CMFCPropertyGridProperty *p_data_filepath_g;
	CMFCPropertyGridProperty *pPropT16_g;
	CMFCPropertyGridProperty *pPropT17_g;
	CMFCPropertyGridProperty *pPropT18_g;
	CMFCPropertyGridProperty *pPropT19_g;
	CMFCPropertyGridProperty *fitertype_g;
	CMFCPropertyGridProperty *lp_filter_len_g;
	CMFCPropertyGridProperty *lp_filter_wn_g;
	CMFCPropertyGridProperty *gauss_filter_len_g;
	CMFCPropertyGridProperty *gauss_filter_BT_g;
	CMFCPropertyGridProperty *cosine_filter_len_g;
	CMFCPropertyGridProperty *cosine_filter_alpha_g;
	CMFCPropertyGridProperty *filter_user_g;
	//调制编码 对应11b
	CMFCPropertyGridProperty *pPropT81;//数据速率
	CMFCPropertyGridProperty *pPropT82;//调制方式
	CMFCPropertyGridProperty *pPropT83;//扰码
	CMFCPropertyGridProperty *pPropT84;//前导码类型
	CMFCPropertyGridProperty *p_data_source_b;//MPDU长度
	CMFCPropertyGridProperty *p_data_filepath_b;
	CMFCPropertyGridProperty *pPropT86;//数据长度
	CMFCPropertyGridProperty *pPropT87;//MAC头部
	CMFCPropertyGridProperty *pPropT88;//MAC FCS
	CMFCPropertyGridProperty *pPropT16_b;
	CMFCPropertyGridProperty *pPropT17_b;
	CMFCPropertyGridProperty *pPropT18_b;
	CMFCPropertyGridProperty *pPropT19_b;
	//调制编码 对应11a
	CMFCPropertyGridProperty *pPropT89;//编码方式 
	CMFCPropertyGridProperty *pPropT90;//码率
	CMFCPropertyGridProperty *pPropT91;//交织
	CMFCPropertyGridProperty *pPropT92;//OFDM扰码器
	CMFCPropertyGridProperty *pPropT93;//OFDM扰码器初始值
	CMFCPropertyGridProperty *pPropT94;//前导码类型
	CMFCPropertyGridProperty *pPropT95;//调制方式
	CMFCPropertyGridProperty *pPropT96;//子载波数

public:
	CButton m_MPDUAdd;
	CButton m_MPDUDelete;
	int     NumOfMPDU;
	CMPDUGeneral* m_mpdu_general;
	afx_msg void OnBnClickedMpdudelete();
	afx_msg void OnBnClickedMpduadd();
	afx_msg void OnDblclkListMpdu(NMHDR *pNMHDR, LRESULT *pResult);
};
class CMFCPropertyGridPropertyButton : public CMFCPropertyGridProperty
{
public:  
	CMFCPropertyGridPropertyButton(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
		LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL, LPCTSTR lpszValidChars = NULL):  
	CMFCPropertyGridProperty(strName,varValue,lpszDescr,dwData)  
	{}  

	virtual ~CMFCPropertyGridPropertyButton()  
	{}  

	virtual BOOL HasButton() const;  

	virtual void OnClickButton(CPoint point);  
protected:  
private:  
};
class CMFCPropertyGridPropertyButton2 : public CMFCPropertyGridProperty
{
public:  
	CMFCPropertyGridPropertyButton2(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
		LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL, LPCTSTR lpszValidChars = NULL):  
	CMFCPropertyGridProperty(strName,varValue,lpszDescr,dwData)  
	{}  

	virtual ~CMFCPropertyGridPropertyButton2()  
	{}  

	virtual BOOL HasButton() const;  

	virtual void OnClickButton(CPoint point);  
protected:  
private:  
};
