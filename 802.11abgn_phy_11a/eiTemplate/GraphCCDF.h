#pragma once

#include "eiTemplateDoc.h"
#include "C.h"

// CGraphCCDF ������ͼ

class CGraphCCDF : public CFormView
{
	DECLARE_DYNCREATE(CGraphCCDF)
	//DECLARE_EASYSIZE

protected:
	CGraphCCDF();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CGraphCCDF();

public:
	enum { IDD = IDD_DIALOG_CCDF };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeComboCcdf();
	virtual void OnInitialUpdate();

	BOOL      m_firstCreate;
	CComboBox m_comboCCDF;
	CC        m_ccdf[4];
	int       m_show_id;
	//CStatic m_ccdf;
};


