
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once

#include "C.h"
#include "W.h"
// �������������������϶�̬������������ͼ
#include "TabParent.h"
#include "GraphCCDF.h"
#include "GraphWAVE.h"
// Э��ʵ�ֵĺ���
#include "protocol/11a/ProtocolA.h"
#include "protocol/11b/ProtocolB.h"
#include "protocol/11g/ProtocolG.h"
#include "protocol/11n/InterfaceClass.h"

// ϵͳ������
#include "SysConfigWizard.h"
#include "config.h"
#include "config_hard.h"
#include <string>
#include <map>
//mac����
#include "Cframe.h"
#include "CframeConfig.h"
#include "CframeB.h"
#include "CframeconfigB.h"
#include "CframeG.h"
#include "CframeconfigG.h"
typedef struct dPic         //������ͼ����ơ����ò����Ⱦ���ʵ�ֵ�ʵ��
{
	CGraphCCDF* p_graphCCDF;
	CGraphWAVE* p_graphWAVE;

	config      *m_configIndex;
	configA     *m_configAIndex;
	configB     *m_configBIndex;
	configG     *m_configGIndex;
	configN     *m_configNIndex;
	config_hard *m_confighard;
	CProgressCtrl *m_progress; //������ָʾ
	int file_size;          //���������ļ��Ĵ�С��д���ݵ�ʱ��Ҫ�õ�

}data_and_graph;
class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:
	//�ָ����ص���������
	CMySplitterWnd m_mainSplitter;
	CMySplitterWnd m_rightSplitter;
	BOOL m_bInitSplitter;
	BOOL m_STC_type;

	CWinThread *draw_thread_id;	//�����źźͻ���ͼ�ߵ��߳�
	data_and_graph m_pass_to_thread;//���ݸ��̵߳Ľṹ��

	config		*m_configIndex;
	//����������صı���
	int m_num_instr;
	ViSession defaultRM;
	ViSession vi[8];
	BOOL b_instr_connected;
// ����
public:
	void SaveConfigA();
	void SaveConfigB();
	void SaveConfigG();
	void SaveConfigN();
	void SaveConfigNL();
	void Write(CString filepath);
	void ConfigEdit(CString protocol,CString para_name,CString para_value);
// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	string *protocoltype; //Э������
	CString userfilepath;
	map<string,string> para;
	map<string,string> para_hard;//����������ز���
// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CToolBar          m_wndToolBar;    //������
	CStatusBar        m_wndStatusBar;  //״̬��
	CProgressCtrl	  m_progress;      //������
// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

//��Ϣ��Ӧ����
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnTest();
	afx_msg void OnHelpDoc();
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnMainRun();
	afx_msg void OnSystemConfigWiz();
	afx_msg void OnHardwareConnectionWiz();
	afx_msg void OnMainDownload();
	afx_msg void ConfigRead(); 
	afx_msg void ConfigSaveAs();
	afx_msg void CongfigSave();
	afx_msg void FileNew();
	afx_msg void antenna_1();
	afx_msg void antenna_2();
	afx_msg void antenna_3();
	afx_msg void antenna_4();
	afx_msg void OnUpdate_antenna_1(CCmdUI *pCmdUI);
	afx_msg void OnUpdate_antenna_2(CCmdUI *pCmdUI);
	afx_msg void OnUpdate_antenna_3(CCmdUI *pCmdUI);
	afx_msg void OnUpdate_antenna_4(CCmdUI *pCmdUI);
	afx_msg void OnFrame11a();
	afx_msg void On11aConfig();
	afx_msg void On11bPicture();
	afx_msg void On11bConfig();
	afx_msg void On11gPicture();
	afx_msg void On11gConfig();
};

UINT ThreadFune(LPVOID lpParam);	//�����źţ�����ͼ�ߵ��߳�