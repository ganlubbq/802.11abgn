#pragma once
#include "afxwin.h"


// Cframe 对话框

class Cframe : public CDialog
{
	DECLARE_DYNAMIC(Cframe)

public:
	Cframe(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Cframe();

// 对话框数据
	enum { IDD = IDD_FRAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CStatic m_pic_framediag;
	HBITMAP m_pic_framediag1;
	HBITMAP m_pic_framediag2;
	HBITMAP m_pic_framediag3;
	CComboBox m_ComFramediag;//下拉菜单选项控件
	afx_msg void OnCbnSelchangeFrameSeclect();
	afx_msg void OnPaint();
};
