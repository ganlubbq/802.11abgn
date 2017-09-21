
// MainFrm.h : CMainFrame 类的接口
//

#pragma once

#include "C.h"
#include "W.h"
// 下面的三个类是主框架上动态创建的三个视图
#include "TabParent.h"
#include "GraphCCDF.h"
#include "GraphWAVE.h"
// 协议实现的函数
#include "protocol/11a/ProtocolA.h"
#include "protocol/11b/ProtocolB.h"
#include "protocol/11g/ProtocolG.h"
#include "protocol/11n/InterfaceClass.h"

// 系统配置向导
#include "SysConfigWizard.h"
#include "config.h"
#include "config_hard.h"
#include <string>
#include <map>
//mac配置
#include "Cframe.h"
#include "CframeConfig.h"
#include "CframeB.h"
#include "CframeconfigB.h"
#include "CframeG.h"
#include "CframeconfigG.h"
typedef struct dPic         //包含了图像绘制、配置参数等具体实现的实例
{
	CGraphCCDF* p_graphCCDF;
	CGraphWAVE* p_graphWAVE;

	config      *m_configIndex;
	configA     *m_configAIndex;
	configB     *m_configBIndex;
	configG     *m_configGIndex;
	configN     *m_configNIndex;
	config_hard *m_confighard;
	CProgressCtrl *m_progress; //进度条指示
	int file_size;          //定义生成文件的大小，写数据的时候要用到

}data_and_graph;
class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:
	//分割窗口相关的三个变量
	CMySplitterWnd m_mainSplitter;
	CMySplitterWnd m_rightSplitter;
	BOOL m_bInitSplitter;
	BOOL m_STC_type;

	CWinThread *draw_thread_id;	//生成信号和绘制图线的线程
	data_and_graph m_pass_to_thread;//传递给线程的结构体

	config		*m_configIndex;
	//仪器连接相关的变量
	int m_num_instr;
	ViSession defaultRM;
	ViSession vi[8];
	BOOL b_instr_connected;
// 操作
public:
	void SaveConfigA();
	void SaveConfigB();
	void SaveConfigG();
	void SaveConfigN();
	void SaveConfigNL();
	void Write(CString filepath);
	void ConfigEdit(CString protocol,CString para_name,CString para_value);
// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	string *protocoltype; //协议类型
	CString userfilepath;
	map<string,string> para;
	map<string,string> para_hard;//仪器连接相关参数
// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CToolBar          m_wndToolBar;    //工具栏
	CStatusBar        m_wndStatusBar;  //状态栏
	CProgressCtrl	  m_progress;      //进度栏
// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

//消息响应函数
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

UINT ThreadFune(LPVOID lpParam);	//生成信号，绘制图线的线程