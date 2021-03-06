#pragma once


// CframeG 对话框

class CframeG : public CDialog
{
	DECLARE_DYNAMIC(CframeG)

public:
	CframeG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CframeG();

// 对话框数据
	enum { IDD = IDD_FRAME_G };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_pic_framediag;
	HBITMAP m_pic_framediag1;
	HBITMAP m_pic_framediag2;
	HBITMAP m_pic_framediag3;
	CComboBox m_ComFramediag;//下拉菜单选项控件
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeFrameSelectG();
};
