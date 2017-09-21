#pragma once

#include "eiTemplateDoc.h"
#include "W.h"


// CGraphWAVE ������ͼ

class CGraphWAVE : public CFormView
{
	DECLARE_DYNCREATE(CGraphWAVE)
	//DECLARE_EASYSIZE;
protected:
	CGraphWAVE();	// ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CGraphWAVE();

public:
	enum { IDD = IDD_DIALOG_WAVE };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

// ��Ϣ����
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeComboWave();
	virtual void OnInitialUpdate();
	
	CComboBox	m_comboWAVE;
	CW m_wave[4];
	int m_show_id;
};
