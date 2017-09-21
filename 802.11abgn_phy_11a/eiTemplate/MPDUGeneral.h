#pragma once
#include "afxwin.h"
#include "define_param.h"
#include "CframeConfig.h"
#include "MpduPara.h"
// CMPDUGeneral 对话框

class CMPDUGeneral : public CDialog
{
	DECLARE_DYNAMIC(CMPDUGeneral)

public:
	CMPDUGeneral(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMPDUGeneral();

// 对话框数据
	enum { IDD = IDD_MPDU_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnPropertyChanged(__in WPARAM wparam,__in LPARAM lparam);
	CFont m_font;
public:
	CMFCPropertyGridCtrl p_mpdu_config;
	CMFCPropertyGridProperty* pGroup;
	CMFCPropertyGridProperty* p_data_type;
	CMFCPropertyGridProperty* p_user_file;
	CMFCPropertyGridProperty* p_data_source_len;
	CMFCPropertyGridProperty* p_mac_header;
	CMFCPropertyGridProperty* p_mac_header_text;
	CMFCPropertyGridProperty* p_mac_fcs;
	CMFCPropertyGridProperty* p_mpdu_len;
	CMFCPropertyGridProperty* p_A_mpdu_len;
	CMFCPropertyGridProperty* p_ISN;
	CMFCPropertyGridProperty* p_SNI;
	CMFCPropertyGridProperty* p_IFN;
	CStatic m_mpdu_index;
	int     Index;
	MpduPara* Para_mpdu;//每个MPDU配置界面对应的MPDU参数
};
class CMFCPropertyGridPropertyButton3 : public CMFCPropertyGridProperty
{
public:  
	CMFCPropertyGridPropertyButton3(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
		LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL, LPCTSTR lpszValidChars = NULL):  
	CMFCPropertyGridProperty(strName,varValue,lpszDescr,dwData)  
	{}  

	virtual ~CMFCPropertyGridPropertyButton3()  
	{}  

	virtual BOOL HasButton() const;  
	virtual void OnClickButton(CPoint point);  
	CframeConfig* m_frame;
protected:  
private:  
};
class CMFCPropertyGridPropertyButton4 : public CMFCPropertyGridProperty
{
public:  
	CMFCPropertyGridPropertyButton4(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
		LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL, LPCTSTR lpszValidChars = NULL):  
	CMFCPropertyGridProperty(strName,varValue,lpszDescr,dwData)  
	{}  

	virtual ~CMFCPropertyGridPropertyButton4()  
	{}  

	virtual BOOL HasButton() const;  

	virtual void OnClickButton(CPoint point);  
protected:  
private:  
};
