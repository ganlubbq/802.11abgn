
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "Splash.h"
#include "htmlhelp.h"
#include "eiTemplateView.h"
#include "protocol/11n/channel.h"
#include "libs/SignalSource.h"
#include "func.h"

//11n滤波
#include "filterfuncn.h"
#include <complex>

#include "MainFrm.h"
#include <iostream>
#include <fstream>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_TEST, &CMainFrame::OnTest)
	ON_COMMAND(ID_OPEN_FILE,&CMainFrame::ConfigRead)
	ON_COMMAND(ID_FILE_NEW,&CMainFrame::FileNew)
	ON_COMMAND(ID_SAVE,&CMainFrame::CongfigSave)
	ON_COMMAND(ID_SAVE_FILE_AS,&CMainFrame::ConfigSaveAs)
	ON_COMMAND(ID_HELP_DOC, &CMainFrame::OnHelpDoc)
	ON_COMMAND(ID_MAIN_RUN, &CMainFrame::OnMainRun)
	ON_COMMAND(ID_SYSTEM_CONFIG_WIZ, &CMainFrame::OnSystemConfigWiz)
	ON_COMMAND(ID_HARDWARE_CONNECTION_WIZ, &CMainFrame::OnHardwareConnectionWiz)
	ON_COMMAND(ID_MAIN_DOWNLOAD,&CMainFrame::OnMainDownload)
	ON_COMMAND(ID_ANTENNA_1, &CMainFrame::antenna_1)
	ON_COMMAND(ID_ANTENNA_2, &CMainFrame::antenna_2)
	ON_COMMAND(ID_ANTENNA_3, &CMainFrame::antenna_3)
	ON_COMMAND(ID_ANTENNA_4, &CMainFrame::antenna_4)
	ON_UPDATE_COMMAND_UI(ID_ANTENNA_1, &CMainFrame::OnUpdate_antenna_1)
	ON_UPDATE_COMMAND_UI(ID_ANTENNA_2, &CMainFrame::OnUpdate_antenna_2)
	ON_UPDATE_COMMAND_UI(ID_ANTENNA_3, &CMainFrame::OnUpdate_antenna_3)
	ON_UPDATE_COMMAND_UI(ID_ANTENNA_4, &CMainFrame::OnUpdate_antenna_4)
	ON_COMMAND(ID_11A_PICTURE, &CMainFrame::OnFrame11a)
	ON_COMMAND(ID_11A_CONFIG, &CMainFrame::On11aConfig)
	ON_COMMAND(ID_11B_PICTURE, &CMainFrame::On11bPicture)
	ON_COMMAND(ID_11B_CONFIG, &CMainFrame::On11bConfig)
	ON_COMMAND(ID_11G_PICTURE, &CMainFrame::On11gPicture)
	ON_COMMAND(ID_11G_CONFIG, &CMainFrame::On11gConfig)
END_MESSAGE_MAP()

/************************************************************************/
/* 状态栏中的几个选项资源标识                                           */
/************************************************************************/
static UINT indicators[]=
{
	ID_SEPARATOR,			//状态行指示器
	IDS_INSTRUMENT_STATE,	//仪器连接状态
	IDS_ERROR_INDICAROR,	//错误指示
	IDS_PROGRESS,			//进度条
};


// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
	m_bInitSplitter = FALSE;
	m_pass_to_thread.m_configAIndex = new configA();
	m_pass_to_thread.m_configBIndex = new configB();
	m_pass_to_thread.m_configGIndex = new configG();
	m_pass_to_thread.m_configNIndex = new configN(); 
	m_pass_to_thread.m_confighard = new config_hard();
	m_configIndex = new config();
	m_pass_to_thread.m_configIndex  = m_configIndex;
	m_pass_to_thread.m_progress = &m_progress;   //主框架进度栏指针传入线程
	b_instr_connected = FALSE;
	m_num_instr = 1;
	m_bAutoMenuEnable = false;
	m_STC_type =FALSE;
	userfilepath="None";
	protocoltype = new string[5];
	protocoltype[0]="11a";protocoltype[1]="11b";protocoltype[2]="11g";protocoltype[3]="11n";protocoltype[4]="11nl";
}

CMainFrame::~CMainFrame()
{
	delete m_configIndex;
	/************************************************************************/
	/* 关闭与仪器的连接                                                     */
	/************************************************************************/
	for (int i = 0;i<m_num_instr;i++)
	{
		viClose(vi[i]);
	}
	viClose(defaultRM);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	/************************************************************************/
	/*添加工具栏                                                            */
	/************************************************************************/
	//创建工具栏
	if (!m_wndToolBar.CreateEx(this,TBSTYLE_FLAT,WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}
	/*为工具栏设置背景颜色***************************************************/
	//SetClassLong 替换工具栏背景画刷
	HBRUSH newBr=CreateSolidBrush(RGB(237,239,252));//RGB(237,239,252)
	SetClassLong(m_wndToolBar.m_hWnd,GCL_HBRBACKGROUND,(long)newBr);
	/*为工具栏添加自定义的图片，包括正常状态的图片，禁用的图片和激活的图片***/
	CImageList m_imgToolBar;//工具栏图标列表
	m_imgToolBar.Create(16,15,ILC_COLOR32|ILC_MASK,0,0);
	m_imgToolBar.Add(AfxGetApp()->LoadIcon(IDI_TOOLNEW_1));
	m_imgToolBar.Add(AfxGetApp()->LoadIcon(IDI_TOOLNEW_2));
	m_imgToolBar.Add(AfxGetApp()->LoadIcon(IDI_TOOLNEW_3));
	m_imgToolBar.Add(AfxGetApp()->LoadIcon(IDI_TOOLNEW_4));
	m_imgToolBar.Add(AfxGetApp()->LoadIcon(IDI_TOOLNEW_5));
	m_imgToolBar.Add(AfxGetApp()->LoadIcon(IDI_TOOLNEW_6));
	m_imgToolBar.Add(AfxGetApp()->LoadIcon(IDI_TOOLNEW_7));
	m_imgToolBar.Add(AfxGetApp()->LoadIcon(IDI_TOOLNEW_8));

	m_wndToolBar.GetToolBarCtrl().SetImageList(&m_imgToolBar);
	m_wndToolBar.GetToolBarCtrl().SetHotImageList(&m_imgToolBar);
	m_wndToolBar.GetToolBarCtrl().SetDisabledImageList(&m_imgToolBar);
	//调用detach可以保证在局部变量m_imgToolBar销毁时不会出现内存问题
	m_imgToolBar.Detach();
	m_wndToolBar.ShowWindow(SW_SHOW);
	
	/************************************************************************/
	/* 添加状态栏(工作状态指示，仪器连接情况，错误信息，进度条)             */
	/************************************************************************/
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	m_wndStatusBar.SetPaneInfo(0,ID_SEPARATOR,SBPS_NORMAL,150);	//设置状态栏第一栏为工作状态指示
	m_wndStatusBar.SetPaneInfo(1,IDS_INSTRUMENT_STATE,SBPS_NORMAL,150);	//设置状态栏第二栏为仪器连接指示
	m_wndStatusBar.SetPaneInfo(2,IDS_ERROR_INDICAROR,SBPS_STRETCH ,0);	//设置状态栏第三栏为错误提示，为保证状态栏占据空间的完整，设为可拉伸的属性
	m_wndStatusBar.SetPaneInfo(3,IDS_PROGRESS,SBPS_NORMAL,200);	//设置状态栏最后一栏为进度条栏，准备放进度条在里面
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);	//显示状态栏



	/***********************在状态栏上创建进度条*****************************/
	CRect rect_progress;
	m_wndStatusBar.GetItemRect(3,&rect_progress);    //获取进度栏的大小
	m_progress.Create(WS_CHILD|WS_VISIBLE|PBS_SMOOTH,rect_progress,&m_wndStatusBar,IDC_PROGRESS);
	m_progress.SetRange(0,6);
	m_progress.SetStep(1);//步进
	m_progress.SetPos(0);//当前位置

	/************************************************************************/
	/* 设置主框架窗口的标题                                                 */
	/************************************************************************/
	SetWindowText("IEEE 802.11a/b/g/n信号生成软件");

	/************************************************************************/
	/* 启动欢迎界面（调试时请注释下面两句）                                 */
	/************************************************************************/
	//CSplashWnd::ShowSplashScreen(this);
	//Sleep(2000);//欢迎界面的持续时间是2秒

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);
	//居中窗口
	CenterWindow();
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式
	cs.style &= ~FWS_ADDTOTITLE; //指定窗口标题
	cs.cx = 1127;
	cs.cy = 712;
	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序
//改写 CFrameWnd::OnCreateClient
// 创建客户区
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类
	CRect cr; 
	GetClientRect( &cr);

	//将整个框架的客户区分为一行两列
	if ( !m_mainSplitter.CreateStatic( this, 1, 2 ,WS_CHILD/*|WS_BORDER*/|WS_VISIBLE) )
	{ 
		MessageBox( "Error setting up main splitter frames!", "Init Error!", MB_OK | MB_ICONERROR ); 
		return FALSE; 
	}
	//将第二列再分为两行一列，这样就形成了框架上的三个子块
	if ( !m_rightSplitter.CreateStatic( &m_mainSplitter, 2, 1 ,WS_CHILD/*|WS_BORDER*/|WS_VISIBLE,m_mainSplitter.IdFromRowCol(0,1)) )
	{ 
		MessageBox( "Error setting up right splitter frames!", "Init Error!", MB_OK | MB_ICONERROR ); 
		return FALSE; 
	}
	/************************************************************************/
	/* 为每个子显示区域生成相应的视图类                                     */
	/************************************************************************/
	//左侧的配置界面
	if ( !m_mainSplitter.CreateView(0, 0, RUNTIME_CLASS(CTabParent), CSize(500, cr.Height()), pContext ) ) 
	{ 
		MessageBox( "Error setting up splitter frames!", "Init Error!", MB_OK | MB_ICONERROR );
		return FALSE; 
	}
	//右上方的CCDF图
	if ( !m_rightSplitter.CreateView(0, 0, RUNTIME_CLASS(CGraphCCDF), CSize(cr.Width()-500, 300/*cr.Height()/2*/), pContext ) ) 
	{ 
		MessageBox( "Error setting up splitter frames!", "Init Error!", MB_OK | MB_ICONERROR );
		return FALSE; 
	}
	//右侧下方的波形图
	if ( !m_rightSplitter.CreateView( 1, 0, RUNTIME_CLASS(CGraphWAVE), CSize(cr.Width()-400, 300/*cr.Height()/2*/), pContext ) ) 
	{ 
		MessageBox( "Error setting up splitter frames!", "Init Error!", MB_OK | MB_ICONERROR );
		return FALSE;
	}

	m_bInitSplitter = TRUE;
	return TRUE;
}

//改写OnSize()适应框架窗口尺寸变化
void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);
	/************************************************************************/
	/*本函数实现了主框架缩放时右侧波形图的按比例缩放和图像最小值的定义和保护*/
	/************************************************************************/
	//最小化会使客户区宽高为0，所以这里必须跳过
	if (nType == SIZE_MINIMIZED)	
	{
		return;
	}
	/************************************************************************/
	//左右分割窗口的控制(定义左侧面板的最小宽度为200，右侧面板的最小宽度为35)
	/************************************************************************/
	int widthLeft = 0;	//左侧面板的宽度
	int widthLeftMin = 0;
	int widthRight = 0;	//右侧面板的宽度
	int widthRightMin = 0;
	//左右两个分割窗口的最小宽度控制

	if ( m_rightSplitter.GetSafeHwnd() != NULL && m_bInitSplitter )
	{
		m_mainSplitter.GetColumnInfo(0,widthLeft,widthLeftMin);//获取当前的宽度和最小宽度
		m_mainSplitter.GetColumnInfo(1,widthRight,widthRightMin);
		if (widthLeft<=200)
		{
			m_mainSplitter.SetColumnInfo(0,200,0);
			m_mainSplitter.SetColumnInfo(1,cx-11-200,0);
		}
		if (widthRight<=35)
		{
			m_mainSplitter.SetColumnInfo(0,cx-11-35,0);
			m_mainSplitter.SetColumnInfo(1,35,0);
		}

		//redisplay the splitter window after adjusting row or column size
		m_mainSplitter.RecalcLayout();
	}
	/************************************************************************/
	//上下分割面板的控制（定义上下面板的高度最小值均为30）
	/************************************************************************/
	int heightRightTop = 0;		//右上方面板的高度
	int heightRightTopMin = 0;
	int heightRightBottom = 0;	//右下方面板的高度
	int heightRightBottomMin = 0;
	//上下两个分割面板的比例控制
	double x = m_rightSplitter.m_splitterScale;	//取出当前窗口分割的比例
	if ( m_rightSplitter.GetSafeHwnd() != NULL && m_bInitSplitter )
	{
		m_rightSplitter.SetRowInfo(0,(int)((cy-54)*x),0);
		m_rightSplitter.SetRowInfo(1,cy-(int)((cy-54)*x),0);
		m_rightSplitter.RecalcLayout();
	}
	//上下两个分割面板的最小高度控制
	if ( m_rightSplitter.GetSafeHwnd() != NULL && m_bInitSplitter )
	{
		m_rightSplitter.GetRowInfo(0,heightRightTop,heightRightTopMin);
		m_rightSplitter.GetRowInfo(1,heightRightBottom,heightRightBottomMin);
		if (heightRightTop<=30)
		{
			m_rightSplitter.SetRowInfo(0,30,0);
			m_rightSplitter.SetRowInfo(1,cy-54-30,0);
		}
		if (heightRightBottom<=30)
		{
			m_rightSplitter.SetRowInfo(0,cy-54-30,0);
			m_rightSplitter.SetRowInfo(1,30,0);
		}
		m_rightSplitter.RecalcLayout();
	}
}


void CMainFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// 不为绘图消息调用 CFrameWnd::OnPaint()
	/************************************************************************/
	/*重绘或者移动状态栏上的进度条                                            */
	/************************************************************************/
	CRect rect_progress;
	m_wndStatusBar.GetItemRect(3,&rect_progress);
	if (!m_progress.m_hWnd)
		m_progress.Create(WS_CHILD|WS_VISIBLE|PBS_SMOOTH,rect_progress,&m_wndStatusBar,IDC_PROGRESS);
	else
		m_progress.MoveWindow(rect_progress);
}



void CMainFrame::OnHelpDoc()//打开帮助文档
{
	/************************************************************************/
	/*下面这种方法也凑合，但是相当于在本程序之外又打开了一个帮助文档实例，有*/
	/*失软件著作的专业性													*/
	/************************************************************************/
	//::ShellExecute(NULL, "open", "test.chm", NULL, NULL, SW_SHOW);
	
	/************************************************************************/
	/*在安装软件的时候可以将帮助文档的路径写入注册表替换现在直接调用文件名的*/
	/*方法，这样会使帮助文档作为应用程序的一部分打开，应用程序关闭的时候帮助*/
	/*随之关闭，体现了软件的专业性											*/
	/************************************************************************/
	//::HtmlHelp(this->m_hWnd,"help.chm",HH_DISPLAY_TOPIC,NULL);
	::HtmlHelp(this->m_hWnd,"11abgnhelp.chm",HH_DISPLAY_TOPIC,NULL);
}


/************************************************************************/
/* 设置主框架窗口缩放的最小尺寸                                       */
/************************************************************************/
void CMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = 650;
	lpMMI->ptMinTrackSize.y = 300;
}


void CMainFrame::OnTest()//测试接口
{
	//ConfigRead();
	
	////微电子所测试要求格式探索
	//char temp[32] = "";
	//CString str="";
	//itoa(1023,temp,2);
	//str.Format("%010s",temp);
	//MessageBox(str);

	/************************************************************************/
	/* 测试仪器连接和数据读取                                               */
	/************************************************************************/
	//ViStatus error_no = 0;
	//ViUInt32 cnt = 0;
	//ViUInt32  length_max = 100;
	//ViSession testRM;
	//ViSession test_vi;
	//char ch[256] = "";
	//double freq = 0;
	//error_no = viOpenDefaultRM(&testRM);
	//Sleep(10);
	//error_no = viOpen(testRM,"TCPIP0::172.141.114.253::5001::SOCKET",VI_NULL,VI_NULL,&test_vi);
	//Sleep(10);
	////error_no = viOpen(testRM,"TCPIP0::127.0.0.1::5001::SOCKET",VI_NULL,VI_NULL,&test_vi);
	//error_no = viSetAttribute(test_vi,VI_ATTR_TMO_VALUE,2000);
	//Sleep(10);
	//error_no = viSetAttribute(test_vi,VI_ATTR_TERMCHAR_EN,VI_TRUE);
	//Sleep(10);
	//error_no = viSetAttribute(test_vi,VI_ATTR_TERMCHAR,'\n');
	//Sleep(10);
	////error_no = viPrintf(test_vi,"*RST\n");//写仪器参数
	////Sleep(100);

	////error_no = viWrite(test_vi,(ViBuf)"FREQ?\n",length_max,&cnt);//写查询命令
	////Sleep(100);
	////error_no = viRead(test_vi,(ViBuf)ch,length_max,&cnt);//读取相应的数据

	////error_no = viPrintf(test_vi,"FREQ?\n");//写查询命令
	////error_no = viScanf(test_vi,"%t",ch);
	//
	////ch[cnt] = '\0';
	////error_no = viWrite(test_vi,(ViBuf)"FREQ 1GHZ\n",length_max,&cnt);
	////error_no = viWrite(test_vi,(ViBuf)"POW 10dBm\n",length_max,&cnt);
	////error_no = viWrite(test_vi,(ViBuf)"OUTP ON\n",length_max,&cnt);
	////error_no = viWrite(test_vi,(ViBuf)"POW:ALC:STAT OFF\n",length_max,&cnt);

	////error_no = viQueryf(test_vi,"POW?\n","%t",ch);
	////error_no = viQueryf(test_vi,"FREQ?\n","%t",ch);
	////error_no = viQueryf(test_vi,"OUTP?\n","%t",ch);
	////error_no = viQueryf(test_vi,"*IDN?\n","%t",ch);
	////MessageBox(ch);
	////error_no = viQueryf(test_vi,"POW:ALC:STAT?\n","%t",ch);

	///************************************************************************/
	///* 文件传输                                                             */
	///************************************************************************/
	//INT32 NMBYTE = 13060;
	//INT32 nBlockNum = 2 * NMBYTE;
	//char *SendData = NULL;
	//UINT64 response = 0;
	//INT32 nReadByte = 0;

	////do 
	////{
	////	nBlockNum -= NMBYTE;
	////	if (nBlockNum<=0)
	////	{
	////		break;
	////	}
	////	SendData = new char[nBlockNum];
	////} while (SendData == NULL);

	////
	////memset(SendData,0,nBlockNum);

	////CFile filedata;
	////CString CFilename = _T("NewSignalData.seg");
	////filedata.Open(CFilename.GetBuffer(),CFile::modeRead);
	////error_no = viWrite(test_vi,(ViBuf)"MEMORY:DATA NewSignalData2.seg,#513060\n",39,&cnt);///////////
	////filedata.SeekToBegin();
	////nReadByte = filedata.Read((void*)SendData,nBlockNum);
	////error_no = viWrite(test_vi,(unsigned char*)SendData,13060,&cnt);
	//
	//Sleep(100);
	////error_no = viWrite(test_vi,(ViBuf)"RADIO:ARB:SEQUENCE NONE,NewSignalData1.seg,1,NONE\n",100,&cnt);
	////error_no = viWrite(test_vi,(ViBuf)"RADIO:ARB:SEQUENCE wlan,NewSignalData0.seg,1,NONE,NewSignalData1.seg,1,NONE,NewSignalData2.seg,1,NONE,NewSignalData3.seg,1,NONE\n",100,&cnt);
	////error_no = viWrite(test_vi,(ViBuf)"RADIO:ARB:SEQUENCE wlan,NewSignalData0.seg,1,NONE\n",100,&cnt);
	////error_no = viWrite(test_vi,(ViBuf)"RADIO:ARB:SEQUENCE wlan,NewSignalData0.seg,1,NONE,NewSignalData1.seg,1,NONE,NewSignalData2.seg,1,NONE,NewSignalData3.seg,1,NONE\n",1000,&cnt);
	//error_no = viWrite(test_vi,(ViBuf)"RADIO:ARB:SEQUENCE NONE,NewSignalData0.seg,10,NONE,NewSignalData1.seg,1,NONE,NewSignalData2.seg,1,M1,NewSignalData3.seg,1,M1M2\n",1000,&cnt);
	//error_no = viWrite(test_vi,(ViBuf)"RADIO:ARB:STATE ON\n",19,&cnt);//下载并播放
	//Sleep(100);



	//error_no = viClear(test_vi);
	//Sleep(10);
	//error_no = viClose(test_vi);
	//Sleep(10);
	//error_no = viClose(testRM);
	////sprintf(str,"%d",GetSystemMetrics(SM_CXSIZEFRAME));//获取分隔条的宽度
	////MessageBox(str);
	////((CGraphWAVE*)m_rightSplitter.GetPane(1,0))->Run();
}



void CMainFrame::OnMainRun()
{
	// TODO: 在此添加命令处理程序代码
	m_pass_to_thread.p_graphCCDF = (CGraphCCDF*)(m_rightSplitter.GetPane(0,0));
	m_pass_to_thread.p_graphWAVE = (CGraphWAVE*)(m_rightSplitter.GetPane(1,0));
	draw_thread_id = AfxBeginThread(ThreadFune,&m_pass_to_thread);
}





UINT ThreadFune(LPVOID lpParam)
{
	CProtocolA protocolIndex;//IEEE 802.11a协议计算模块
	InterfaceClass InterfaceClassObject11n;//IEEE 802.11n协议计算模块
	CProtocolB protocolIndexB;//IEEE 802.11b 协议计算模块
	tx_11g_param protocolIndexG;//IEEE 802.11g协议计算模块

	data_and_graph *DataAndGraph = (data_and_graph *)lpParam;
	CC* p_ccdf = &(DataAndGraph->p_graphCCDF->m_ccdf[0]);
	CW* p_wave = &(DataAndGraph->p_graphWAVE->m_wave[0]);
	CProgressCtrl *m_progress = DataAndGraph->m_progress;

	int i,j,m,N=0,Num_of_space,m_AllNum,ScaleXend;
	double max_power;
	double max_spectrum;
	double max_ccdf;
	vector<complex<double>> data_in[4];
	//在绘图过程中禁用掉两个图像显示窗口上的comboBox
	DataAndGraph->p_graphCCDF->m_comboCCDF.EnableWindow(FALSE);
	DataAndGraph->p_graphWAVE->m_comboWAVE.EnableWindow(FALSE);
		
	/************************************************************************/
	/* 以下绘制图线的函数根据老版程序修改得来           */
	/************************************************************************/
	switch (DataAndGraph->m_configIndex->ProtocolModel)
	{
	case OneA:
		{
			m_progress->SetPos(0);
			vector<double> temp_filter(DataAndGraph->m_configAIndex->filter_user);
			/************************************************************************/
			/* 生成802.11a基带信号                                                     */
			/************************************************************************/
			//从界面传入参数
			protocolIndex.AprotocolConfig.EZOA_Encoding = DataAndGraph->m_configAIndex->EZOA_Encoding;
			protocolIndex.AprotocolConfig.ProtocolModel = DataAndGraph->m_configIndex->ProtocolModel;
			protocolIndex.AprotocolConfig.length = DataAndGraph->m_configAIndex->length;
			protocolIndex.AprotocolConfig.FrequencyOffset = DataAndGraph->m_configAIndex->FrequencyOffset;
			protocolIndex.AprotocolConfig.add_channel = DataAndGraph->m_configAIndex->add_channel;
			protocolIndex.AprotocolConfig.mobilespeed = DataAndGraph->m_configAIndex->mobilespeed;
			protocolIndex.AprotocolConfig.carrierfreq = DataAndGraph->m_configAIndex->carrierfreq;
			protocolIndex.AprotocolConfig.NumOfTaps = DataAndGraph->m_configAIndex->NumOfTaps;
			protocolIndex.AprotocolConfig.oversample_ratio = DataAndGraph->m_configAIndex->oversample_ratio;
			protocolIndex.AprotocolConfig.scrambler_state_OFDM = DataAndGraph->m_configAIndex->scrambler_state_OFDM;
			protocolIndex.AprotocolConfig.scramble_state_initial = DataAndGraph->m_configAIndex->scramble_state_initial;
			protocolIndex.AprotocolConfig.filter_para= DataAndGraph->m_configAIndex->filter_para;
			protocolIndex.AprotocolConfig.filter_user= DataAndGraph->m_configAIndex->filter_user;
			protocolIndex.AprotocolConfig.IQ_gain=DataAndGraph->m_configAIndex->IQ_gain;
			protocolIndex.AprotocolConfig.quan_angle_adjust=DataAndGraph->m_configAIndex->quan_angle_adjust;
			//配置数据源
			int data_bytelen = DataAndGraph->m_configAIndex->source_length;
			int data_inlen = DataAndGraph->m_configAIndex->source_length * 8;//输入01比特的长度
			//test
			//data_inlen=4000;
			vector<int> src = GenerateSource(DataAndGraph->m_configAIndex->source_mode,data_inlen,10,DataAndGraph->m_configAIndex->filepath.GetBuffer());

			//运行生成数据
			protocolIndex.Run(src,data_bytelen);
			m_progress->StepIt();

			//绘图
			int sig_len = protocolIndex.S_PPDU_length * protocolIndex.AprotocolConfig.oversample_ratio;
			int sig_len_idle = sig_len;
			//统计各天线的IQ范围
			double I_Q_range=0.0,temp,temp_i,temp_r;
			for(int i=0;i<sig_len;i++)
			{   
				temp_r = abs(protocolIndex.S_PPDU[i].real());
				temp_i = abs(protocolIndex.S_PPDU[i].imag());
				temp = temp_r > temp_i ? temp_r :temp_i;
				I_Q_range = temp > I_Q_range ? temp : I_Q_range;
			}
			int I_Q_base =INT( 32767/ I_Q_range );

			int interval_len =0;
			std::complex<double> I_Q[20000]={(0.0,0.0)};
			//基带数据导出

			
					//for (i = 0;i<sig_len;i++) 
					//	{
					//		of<<protocolIndexB.S_PPDU[i].real()<<","<<protocolIndexB.S_PPDU[i].imag()<<endl;
					//	}
					


			//ofstream of("11a_CETC41_20M.csv");
			int num_of_zeros=DataAndGraph->m_configAIndex->num_of_zeros;
			int num_of_frame=DataAndGraph->m_configAIndex->num_of_frame;
			ofstream of("11a.csv");
			for(int k = 0;k<num_of_frame;k++)
				{
					for (i = 0;i<sig_len;i++) 
			{
				of<<protocolIndex.S_PPDU[i].real()<<","<<protocolIndex.S_PPDU[i].imag()<<endl;
			}
					for(int m=0;m<num_of_zeros;m++)
						of << 0 << ","<< 0 << endl;
				}
			of.close();
			//CTabCarrier &m_carrier=((CTabParent*)(((CMainFrame*)AfxGetMainWnd())->m_mainSplitter.GetPane(0,0)))->m_tabCarrier;
			//char str[10];
			//m_carrier.pPropS2->SetValue(itoa(sig_len,str,10));
 			m_progress->StepIt();
			/************************************************************************/
			/* 生成 41 要求格式的信号文件                                           */
			/************************************************************************/
			CFile file;
			file.Open(_T("802_11a.seg"),CFile::modeCreate|CFile::modeWrite);
			CArchive ar(&file,CArchive::store);//写操作

			//256字节头部
			char ei41Name[8] = {'e','i','4','1','\0','\0','\0','\0'};//公司名称
			for (int i=0;i!=8;i++)
				ar<<ei41Name[i];
			
			INT64 timeFrequency = 20000000;//时钟频率
			ar<<timeFrequency;

			INT64 elementLength = sig_len+interval_len;//码元长度
			ar<<elementLength;

			INT64 samplePoints = 1;//过采样点数
			ar<<samplePoints;

			INT64 points = sig_len+interval_len;//样点个数
			ar<<points;

			INT64 cycleTime = points / timeFrequency * 1000;//周期 = 样点个数*时钟频率 毫秒为单位；
			ar<<cycleTime;

			INT64  padBits[26]={0};//填充208位字节
			for (int i =0;i!=26;i++)
				ar<<padBits[i];


			//基带信号数据段
			for (int i=0;i!=sig_len;i++)
			{
				ar<<(INT16)(protocolIndex.S_PPDU[i].real()*I_Q_base)<<(INT16)(protocolIndex.S_PPDU[i].imag()*I_Q_base);
			}
			/******interval******/
			for (int i=0;i<interval_len;i++)//这里50000是随便设置的数，可以根据应用场景自行调整
				ar<<static_cast<INT16>(0)<<static_cast<INT16>(0);

			ar.Close();
			file.Close();
		    
			DataAndGraph->file_size = 256 + (sig_len+interval_len) * 2 * 2 ; // 每个sig_len有2字节，一个长度对应实部和虚部两位，所以最后乘以4
			m_progress->StepIt();
			/************************************************************************/
			/* WAVE图绘制（I+Q、I|Q、power、Spectrum）                              */
			/************************************************************************/
			p_wave->m_RealValuenSize = sig_len;	//运行生成的数据长度
		    p_wave->m_ScaleValueXEnd =sig_len;

			//保存绘图数据
			p_wave->I_Data = new double[sig_len];
			p_wave->Q_Data = new double[sig_len];
			p_wave->m_IQ_range = I_Q_range;
			/**********I+Q 数据导入绘图类**********/
			for (int i=0;i<sig_len;i++)
			{  
				p_wave->I_Data[i]=protocolIndex.S_PPDU[i].real();
				p_wave->Q_Data[i]=protocolIndex.S_PPDU[i].imag();
				
			}
			/**********Power图的绘制**********/	
			p_wave->pPointArrayPower =(POINT *) new POINT[sig_len];
			
			max_power=0.0;//初始化
            //找到功率最大点
			for (int j=0;j<sig_len;j++)
			{
				double temp = pow(protocolIndex.S_PPDU[j].real(),2)+pow(protocolIndex.S_PPDU[j].imag(),2);
				if(temp>max_power)
				{
					max_power=temp;
				}	
			}
			//计算每个信号点相对于最大功率点的dB值
			for (j=0;j<sig_len;j++)
			{
				p_wave->pPointArrayPower[j].x=long(j);
				p_wave->pPointArrayPower[j].y=10*log10((pow(protocolIndex.S_PPDU[j].real(),2)+pow(protocolIndex.S_PPDU[j].imag(),2))/max_power);
			
			}
			/**********Spectrum的绘制**********/
			//数组转容器
			vector<complex<double>> data_in(sig_len);
			for (int m=0;m<sig_len;m++)
			{
				data_in[m]=protocolIndex.S_PPDU[m];
			}
			//FFT计算频谱
			N=FFT(data_in,sig_len);
			FFTShift(data_in);
			p_wave->pPointArraySpectrum =(POINT *) new POINT[N];
		

			p_wave->m_FFT_AllNum=N;
			
			//max_spectrum
			max_spectrum=0.0;
			for(int m=1;m<N;m++)
			{
				if(abs(data_in[m])>max_spectrum)
				max_spectrum=abs(data_in[m]);
			}	
			bool flag = TRUE;
			for (int m=0;m<N;m++)
			{
				p_wave->pPointArraySpectrum[m].x=long(m);
				p_wave->pPointArraySpectrum[m].y=10*log10(abs(data_in[m])/max_spectrum);
				if(p_wave->pPointArraySpectrum[m].y > -3){  //记录-3dB范围
					if(flag){
						p_wave->BWL = m;
						flag = FALSE;
					}
					else
						p_wave->BWR = m;
				}
			}
			data_in.clear();
			p_wave->IorQFlg();	//图像生成完毕后首先显示I|Q图像
			
			m_progress->StepIt();
			/************************************************************************/
			/* CCDF图的绘制 Burst                                                        */
			/************************************************************************/
			p_ccdf->m_RealValuenSize = sig_len;

			double *pPointArrayCCDF;
			
			//设定一个中间变量数组，存放实际数据的功率
			pPointArrayCCDF =(double*)new double[sig_len];//设定一个中间变量数组
		
				
			//CCDF设定一个数组，固定长度
			//确定间隔个数 == X轴总点数-1
			Num_of_space=(p_ccdf->m_AllNum)-1;
			m_AllNum=p_ccdf->m_AllNum;
			ScaleXend=p_ccdf->m_ScaleValueXEnd;
            p_ccdf->pPointArrayCCDF=(double*)new double[m_AllNum];//CCDF设定一个数组
			
			//计算功率
			for (i=0;i<sig_len;i++)
			{
				pPointArrayCCDF[i]=pow(protocolIndex.S_PPDU[i].real(),2)+pow(protocolIndex.S_PPDU[i].imag(),2);
			}
				
			max_ccdf=sumCCDF(p_ccdf->pPointArrayCCDF,pPointArrayCCDF,sig_len,ScaleXend,Num_of_space);
			p_ccdf->m_maxCCDFX=max_ccdf;

			

			delete[] pPointArrayCCDF;
			m_progress->StepIt();
			/************************************************************************/
			/* CCDF图的绘制 wave                                                        */
			/************************************************************************/
			p_ccdf->m_RealValuenSize = sig_len_idle;

			double *pPointArrayWAVE;

			//设定一个中间变量数组，存放实际数据的功率
			pPointArrayWAVE =(double*)new double[sig_len_idle];//设定一个中间变量数组
			p_ccdf->pPointArrayWAVE=(double*)new double[m_AllNum];//CCDF设定一个数组

			//计算功率
			for (int i=0;i<sig_len;i++)
			{
				pPointArrayWAVE[i]=pow(protocolIndex.S_PPDU[i].real(),2)+pow(protocolIndex.S_PPDU[i].imag(),2);
			}
			for (int i=sig_len;i<sig_len_idle;i++)
			{
				pPointArrayWAVE[i]=0;
			}
			max_ccdf=sumCCDF(p_ccdf->pPointArrayWAVE,pPointArrayWAVE,sig_len_idle,ScaleXend,Num_of_space);
			p_ccdf->m_maxWAVEX=max_ccdf;

			delete[] pPointArrayWAVE;
			//绘图完成清空协议生成的数据
			delete[] protocolIndex.S_PPDU;

			p_ccdf->burstflag();
			//流程结束
			int low,up;
			m_progress->GetRange(low,up);
			m_progress->SetPos(up);
			//在图像的绘制操作完成后，再使能两个图像上的comboBox
			DataAndGraph->p_graphCCDF->m_comboCCDF.SetCurSel(0);
			DataAndGraph->p_graphWAVE->m_comboWAVE.SetCurSel(0);
			DataAndGraph->p_graphCCDF->m_comboCCDF.EnableWindow(TRUE);
			DataAndGraph->p_graphWAVE->m_comboWAVE.EnableWindow(TRUE);
			break;
			}
		case OneB:
			{
				/************************************************************************/
				/* 生成802.11b基带信号                                                     */
				/************************************************************************/
				protocolIndexB.BprotocolConfig.EZOB_Encoding = DataAndGraph->m_configBIndex->EZOB_Encoding;//EZOB_Encoding 指的是11a的，有问题！
				protocolIndexB.BprotocolConfig.ProtocolModel = DataAndGraph->m_configIndex->ProtocolModel;
				protocolIndexB.BprotocolConfig.length = DataAndGraph->m_configBIndex->length;
				protocolIndexB.BprotocolConfig.FrequencyOffset = DataAndGraph->m_configBIndex->FrequencyOffset;
				protocolIndexB.BprotocolConfig.add_channel = DataAndGraph->m_configBIndex->add_channel;
				protocolIndexB.BprotocolConfig.mobilespeed = DataAndGraph->m_configBIndex->mobilespeed;
				protocolIndexB.BprotocolConfig.carrierfreq = DataAndGraph->m_configBIndex->carrierfreq;
				protocolIndexB.BprotocolConfig.NumOfTaps = DataAndGraph->m_configBIndex->NumOfTaps;
				protocolIndexB.BprotocolConfig.oversample_ratio = DataAndGraph->m_configBIndex->oversample_ratio;
				protocolIndexB.BprotocolConfig.filter_para= DataAndGraph->m_configBIndex->filter_para;
				protocolIndexB.BprotocolConfig.filter_user= DataAndGraph->m_configBIndex->filter_user;
				protocolIndexB.BprotocolConfig.scrambler_state= DataAndGraph->m_configBIndex->scrambler_state;
				protocolIndexB.BprotocolConfig.preamble_type= DataAndGraph->m_configBIndex->preamble_type;
				protocolIndexB.BprotocolConfig.IQ_gain=DataAndGraph->m_configBIndex->IQ_gain;
				protocolIndexB.BprotocolConfig.quan_angle_adjust=DataAndGraph->m_configBIndex->quan_angle_adjust;

				//从界面传入数据长度，以字节为单位，数据类型，
				int data_bytelen = DataAndGraph->m_configBIndex->source_length;
				int data_inlen = DataAndGraph->m_configBIndex->source_length * 8;//输入01比特的长度
				vector<int> src = GenerateSource(DataAndGraph->m_configBIndex->source_mode,data_inlen,10,DataAndGraph->m_configGIndex->filepath);
				protocolIndexB.Run(src,data_bytelen);//根据给定的协议参数生成波形数据
				int sig_len = protocolIndexB.S_PPDU_length * DataAndGraph->m_configBIndex->oversample_ratio;
				int sig_len_idle = sig_len;

				//统计各天线的IQ范围
				double I_Q_range=0.0,temp,temp_i,temp_r;
				for(int i=0;i<sig_len;i++)
				{   
					temp_r = abs(protocolIndexB.S_PPDU[i].real());
					temp_i = abs(protocolIndexB.S_PPDU[i].imag());
					temp = temp_r > temp_i ? temp_r :temp_i;
					if(temp>I_Q_range)
						I_Q_range =temp;
				}
				int I_Q_base =INT( 32767/ I_Q_range );
				int interval_len =0;
				int num_of_zeros=DataAndGraph->m_configBIndex->num_of_zeros;
				int num_of_frame=DataAndGraph->m_configBIndex->num_of_frame;
				//基带数据导出
				ofstream of("11b.csv");
				for(int k = 0;k<num_of_frame;k++)
				{
					for (i = 0;i<sig_len;i++) 
						{
							of<<protocolIndexB.S_PPDU[i].real()<<","<<protocolIndexB.S_PPDU[i].imag()<<endl;
						}
					for(int i=0;i<num_of_zeros;i++)
						of << 0 << ","<< 0 << endl;
				}
				of.close();
				//CTabCarrier &m_carrier=((CTabParent*)(((CMainFrame*)AfxGetMainWnd())->m_mainSplitter.GetPane(0,0)))->m_tabCarrier;
				//char str[10];
				//m_carrier.pPropS2->SetValue(itoa(sig_len,str,10));
				/************************************************************************/
				/* 生成 41 要求格式的信号文件                                           */
				/************************************************************************/
				CFile file;
				file.Open(_T("802_11b.seg"),CFile::modeCreate|CFile::modeWrite);
				CArchive ar(&file,CArchive::store);//写操作

				//256字节头部
				char ei41Name[8] = {'e','i','4','1','\0','\0','\0','\0'};//公司名称
				for (int i=0;i!=8;i++)
					ar<<ei41Name[i];
				/*int data_rate;
				int encoding =protocolIndexB.modulation_type;
				switch(encoding){
				case DBPSK_1Mbps:
				data_rate=1000000;break;
				case DQPSK_2Mbps:
				data_rate =2000000;break;
				case CCK55_55Mbps:
				data_rate =5500000;break;
				case CCK11_11Mpbs:
				data_rate=11000000;break;
				}*/
				//INT64 timeFrequency = data_rate;//时钟频率
				INT64 timeFrequency = 11000000;//时钟频率
				ar<<timeFrequency;

				INT64 elementLength = sig_len+interval_len;//码元长度
				ar<<elementLength;

				INT64 samplePoints = 1;//过采样点数
				ar<<samplePoints;

				INT64 points = sig_len+interval_len;//样点个数
				ar<<points;

				INT64 cycleTime = points / timeFrequency * 1000;//周期 = 样点个数*时钟频率 毫秒为单位；
				ar<<cycleTime;

				INT64  padBits[26]={0};//填充208位字节
				for (int i =0;i!=26;i++)
					ar<<padBits[i];


				
				//基带信号数据段
				for (int i=0;i!=sig_len;i++)
				{
					ar<<(INT16)(protocolIndexB.S_PPDU[i].real()*I_Q_base)<<(INT16)(protocolIndexB.S_PPDU[i].imag()*I_Q_base);
				}

				/******interval******/
				for (int i=0;i<interval_len;i++)//这里50000是随便设置的数，可以根据应用场景自行调整
					ar<<static_cast<INT16>(0)<<static_cast<INT16>(0);
				ar.Close();
				file.Close();

				DataAndGraph->file_size = 256 + (sig_len+interval_len) * 2 * 2; // 每个sig_len有2字节，一个长度对应实部和虚部两位，所以最后乘以4

				/************************************************************************/
				/* WAVE图绘制（I+Q、I|Q、power、Spectrum）                              */
				/******************************************************************   ******/
				p_wave->m_RealValuenSize = sig_len;	//运行生成的数据长度
				p_wave->m_ScaleValueXEnd =sig_len;
				//保存绘图数据
				p_wave->I_Data = new double[sig_len];
				p_wave->Q_Data = new double[sig_len];
				p_wave->m_IQ_range = I_Q_range;

				/**********I+Q 数据导入绘图类**********/
				for (int i=0;i<sig_len;i++)
				{
					
					p_wave->I_Data[i]=protocolIndexB.S_PPDU[i].real();
					p_wave->Q_Data[i]=protocolIndexB.S_PPDU[i].imag();
					
				}
				/**********Power图的绘制**********/
				p_wave->pPointArrayPower =(POINT *) new POINT[sig_len];//2*sig_len->sig_len
			   
				max_power=0.0;//初始化
				//找到功率最大点
				for (int j=0;j<sig_len;j++)
				{
					double temp = pow(protocolIndexB.S_PPDU[j].real(),2)+pow(protocolIndexB.S_PPDU[j].imag(),2);
					if(temp>max_power)
					{
						max_power=temp;
					}
				}			
				//计算每个信号点相对于最大功率点的dB值
				for (int j=0;j<sig_len;j++)//2*sig_len->sig_len
				{
					p_wave->pPointArrayPower[j].x=long(j);
					p_wave->pPointArrayPower[j].y=10*log10((pow(protocolIndexB.S_PPDU[j].real(),2)+pow(protocolIndexB.S_PPDU[j].imag(),2))/max_power);

				}
				/**********Spectrum的绘制**********/
				//数组转容器
                vector<complex<double>> data_in(sig_len);
				for (int m=0;m<sig_len;m++)
				{
					data_in[m]=protocolIndexB.S_PPDU[m];
				}
				//FFT计算频谱
				N=FFT(data_in,sig_len);
				FFTShift(data_in);
				p_wave->pPointArraySpectrum =(POINT *) new POINT[N];
				

				p_wave->m_FFT_AllNum=N;
				
				//max_spectrum
				max_spectrum=0.0;
				for(int m=0;m<N;m++)
				{
					if(abs(data_in[m])>max_spectrum)
						max_spectrum=abs(data_in[m]);
				}
				bool flag = TRUE;
				for (int m=0;m<N;m++)
				{
					p_wave->pPointArraySpectrum[m].x=long(m);
					p_wave->pPointArraySpectrum[m].y=10*log10(abs(data_in[m])/max_spectrum);
					if(p_wave->pPointArraySpectrum[m].y > -3){  //记录-3dB范围
						if(flag){
							p_wave->BWL = m;
							flag = FALSE;
						}
						else
							p_wave->BWR = m;
					}
				}
				data_in.clear();
				p_wave->IorQFlg();	//图像生成完毕后首先显示I|Q图像
				

				/************************************************************************/
				/* CCDF图的绘制                                                         */
				/************************************************************************/
				p_ccdf->m_RealValuenSize = sig_len;

				double *pPointArrayCCDF;
		       
				//设定一个中间变量数组，存放实际数据的功率
				pPointArrayCCDF =(double*)new double[sig_len];//设定一个中间变量数组
				

				//CCDF设定一个数组，固定长度
				//确定间隔个数 == X轴总点数-1
				Num_of_space=(p_ccdf->m_AllNum)-1;
				m_AllNum=p_ccdf->m_AllNum;
				ScaleXend=p_ccdf->m_ScaleValueXEnd;
				p_ccdf->pPointArrayCCDF=(double*)new double[m_AllNum];//CCDF设定一个数组
				//计算功率
				for (i=0;i<sig_len;i++)
				{
					pPointArrayCCDF[i]=pow(protocolIndexB.S_PPDU[i].real(),2)+pow(protocolIndexB.S_PPDU[i].imag(),2);
					
				}

				max_ccdf=sumCCDF(p_ccdf->pPointArrayCCDF,pPointArrayCCDF,sig_len,ScaleXend,Num_of_space);
				p_ccdf->m_maxCCDFX=int(max_ccdf);

				delete[] pPointArrayCCDF;
				
				/************************************************************************/
				/* CCDF图的绘制 wave                                                        */
				/************************************************************************/
				p_ccdf->m_RealValuenSize = sig_len_idle;

				double *pPointArrayWAVE;

				//设定一个中间变量数组，存放实际数据的功率
				pPointArrayWAVE =(double*)new double[sig_len_idle];//设定一个中间变量数组
				p_ccdf->pPointArrayWAVE=(double*)new double[m_AllNum];//CCDF设定一个数组

				//计算功率
				for (int i=0;i<sig_len;i++)
				{
					pPointArrayWAVE[i]=pow(protocolIndexB.S_PPDU[i].real(),2)+pow(protocolIndexB.S_PPDU[i].imag(),2);
				}
				for (int i=sig_len;i<sig_len_idle;i++)
				{
					pPointArrayWAVE[i]=0;
				}
				max_ccdf=sumCCDF(p_ccdf->pPointArrayWAVE,pPointArrayWAVE,sig_len_idle,ScaleXend,Num_of_space);
				p_ccdf->m_maxWAVEX=max_ccdf;

				delete[] pPointArrayWAVE;
				//清空协议生成数据
				delete[] protocolIndexB.S_PPDU;
				p_ccdf->burstflag();

				//在图像的绘制操作完成后，再使能两个图像上的comboBox
				DataAndGraph->p_graphCCDF->m_comboCCDF.SetCurSel(0);
				DataAndGraph->p_graphWAVE->m_comboWAVE.SetCurSel(0);
				DataAndGraph->p_graphCCDF->m_comboCCDF.EnableWindow(TRUE);
				DataAndGraph->p_graphWAVE->m_comboWAVE.EnableWindow(TRUE);

				break;
			}
		case OneG:
			{
				/************************************************************************/
				/* 生成802.11g基带信号                                                     */
				/************************************************************************/
				protocolIndexG.GprotocolConfig.EZOG_Encoding = DataAndGraph->m_configGIndex->EZOG_Encoding;
				protocolIndexG.GprotocolConfig.preamble_type = DataAndGraph->m_configGIndex->preamble_type;
				protocolIndexG.GprotocolConfig.scrambler_state = DataAndGraph->m_configGIndex->scrambler_state;
				protocolIndexG.GprotocolConfig.scrambler_state_OFDM = DataAndGraph->m_configGIndex->scrambler_state_OFDM;
				protocolIndexG.GprotocolConfig.scramble_state_initial = DataAndGraph->m_configGIndex->scramble_state_initial;
				protocolIndexG.GprotocolConfig.length = DataAndGraph->m_configGIndex->length;
				protocolIndexG.GprotocolConfig.FrequencyOffset = DataAndGraph->m_configGIndex->FrequencyOffset;
				protocolIndexG.GprotocolConfig.data_rate = DataAndGraph->m_configGIndex->data_rate;
				protocolIndexG.GprotocolConfig.modulation_type = DataAndGraph->m_configGIndex->modulation_type;
				protocolIndexG.GprotocolConfig.ProtocolModel = DataAndGraph->m_configGIndex->ProtocolModel;
				protocolIndexG.GprotocolConfig.add_channel = DataAndGraph->m_configGIndex->add_channel;
				protocolIndexG.GprotocolConfig.mobilespeed = DataAndGraph->m_configGIndex->mobilespeed;
				protocolIndexG.GprotocolConfig.carrierfreq = DataAndGraph->m_configGIndex->carrierfreq;
				protocolIndexG.GprotocolConfig.NumOfTaps = DataAndGraph->m_configGIndex->NumOfTaps;
				protocolIndexG.GprotocolConfig.oversample_ratio = DataAndGraph->m_configGIndex->oversample_ratio;
				protocolIndexG.GprotocolConfig.IQ_gain=DataAndGraph->m_configGIndex->IQ_gain;
				protocolIndexG.GprotocolConfig.quan_angle_adjust=DataAndGraph->m_configGIndex->quan_angle_adjust;
				//从界面传入数据长度，以字节为单位，数据类型，
				int data_bytelen = DataAndGraph->m_configGIndex->source_length;
				int data_inlen = DataAndGraph->m_configGIndex->source_length * 8;//输入01比特的长度
				vector<int> src = GenerateSource(DataAndGraph->m_configGIndex->source_mode,data_inlen,10,DataAndGraph->m_configGIndex->filepath);
				protocolIndexG.Run(src,data_bytelen);//根据给定的协议参数生成波形数据
				int sig_len = protocolIndexG.S_PPDU_length * DataAndGraph->m_configGIndex->oversample_ratio;
				int sig_len_idle=sig_len;
				double I_Q_range=0.0,temp,temp_i,temp_r;
				for(int i=0;i<sig_len;i++)
				{   
					temp_r = abs(protocolIndexG.S_PPDU[i].real());
					temp_i = abs(protocolIndexG.S_PPDU[i].imag());
					temp = temp_r > temp_i ? temp_r :temp_i;
					if(temp>I_Q_range)
						I_Q_range =temp;
				}
				int I_Q_base =INT( 32767/ I_Q_range );
				int interval_len =0;

				//int I_Q_base =0;
				int num_of_zeros=DataAndGraph->m_configGIndex->num_of_zeros;
				int num_of_frame=DataAndGraph->m_configGIndex->num_of_frame;
				ofstream of("11g.csv");
				for(int k = 0;k<num_of_frame;k++)
				{
					for (i = 0;i<sig_len;i++) 
						{
							of<<protocolIndexG.S_PPDU[i].real()<<","<<protocolIndexG.S_PPDU[i].imag()<<endl;
						}
					for(int i=0;i<num_of_zeros;i++)
						of << 0 << ","<< 0 << endl;
				}
				of.close();
				//CTabCarrier &m_carrier=((CTabParent*)(((CMainFrame*)AfxGetMainWnd())->m_mainSplitter.GetPane(0,0)))->m_tabCarrier;
				//char str[10];
				//m_carrier.pPropS2->SetValue(itoa(sig_len,str,10));
				//std::complex<double> I_Q[20000]={(0.0,0.0)};
				//ofstream of("11g_mcs0.txt");
				//for (i = 0;i<sig_len;i++)
				//{
				//	I_Q[i] = protocolIndexG.S_PPDU[i]*6.6564;
				//	of<<I_Q[i]<<endl;
				//}
				//of.close();
				/************************************************************************/
				/* 生成 41 要求格式的信号文件                                           */
				/************************************************************************/
				CFile file;
				file.Open(_T("802_11g.seg"),CFile::modeCreate|CFile::modeWrite);
				CArchive ar(&file,CArchive::store);//写操作

				//256字节头部
				char ei41Name[8] = {'e','i','4','1','\0','\0','\0','\0'};//公司名称
				for (int i=0;i!=8;i++)
					ar<<ei41Name[i];
		
				INT64 timeFrequency = 20000000;//时钟频率
				ar<<timeFrequency;

				INT64 elementLength = sig_len + interval_len;//码元长度
				ar<<elementLength;

				INT64 samplePoints = 1;//过采样点数
				ar<<samplePoints;

				INT64 points = sig_len + interval_len;//样点个数
				ar<<points;

				INT64 cycleTime = points / timeFrequency * 1000;//周期 = 样点个数*时钟频率 毫秒为单位；
				ar<<cycleTime;

				INT64  padBits[26]={0};//填充208位字节
				for (int i =0;i!=26;i++)
					ar<<padBits[i];

				//基带信号数据段
				for (int i=0;i!=sig_len;i++)
				{
					ar<<(INT16)(protocolIndexG.S_PPDU[i].real()*I_Q_base )<<(INT16)(protocolIndexG.S_PPDU[i].imag()*I_Q_base);
				}

				for (int i=0;i<interval_len;i++)//这里50000是随便设置的数，可以根据应用场景自行调整
					ar<<static_cast<INT16>(0)<<static_cast<INT16>(0);

				ar.Close();
				file.Close();

				/******interval******/
				
				DataAndGraph->file_size = 256 + (sig_len+interval_len) * 2 * 2; // 每个sig_len有2字节，一个长度对应实部和虚部两位，所以最后乘以4
				/************************************************************************/
				/* WAVE图绘制（I+Q、I|Q、power、Spectrum）                              */
				/************************************************************************/
				p_wave->m_RealValuenSize = sig_len;	//运行生成的数据长度
				p_wave->m_ScaleValueXEnd =sig_len;
				p_wave->pPointArray =(POINT *) new POINT[sig_len];	//设定一个数组
				p_wave->I_Data = new double[sig_len];
				p_wave->Q_Data = new double[sig_len];
				p_wave->m_IQ_range = I_Q_range;

				
				/**********I+Q 数据导入绘图类**********/
				
				for (int i=0;i<sig_len;i++)
				{
					p_wave->I_Data[i]=protocolIndexG.S_PPDU[i].real();//>pPointArray[i].x 改成 I_Data[i]
					p_wave->Q_Data[i]=protocolIndexG.S_PPDU[i].imag();
					
				}

				/**********Power图的绘制**********/
				p_wave->pPointArrayPower =(POINT *) new POINT[sig_len];//2*sig_len->sig_len
				
				max_power=0.0;//初始化

				for (int j=0;j<sig_len;j++)
				{
					double temp = pow(protocolIndexG.S_PPDU[j].real(),2)+pow(protocolIndexG.S_PPDU[j].imag(),2);
					if(temp>max_power)
					{
						max_power=temp;
					}
				}
				//计算每个信号点相对于最大功率点的dB值
				for (int j=0;j<sig_len;j++)//2*sig_len->sig_len
				{
					p_wave->pPointArrayPower[j].x=long(j);
					p_wave->pPointArrayPower[j].y=10*log10((pow(protocolIndexG.S_PPDU[j].real(),2)+pow(protocolIndexG.S_PPDU[j].imag(),2))/max_power);
					
				}
				/**********Spectrum的绘制**********/
				//数组转容器
				vector<complex<double>> data_in(sig_len);
				for (int m=0;m<sig_len;m++)
				{
					data_in[m]=protocolIndexG.S_PPDU[m];
				}
				//FFT计算频谱
				N=FFT(data_in,sig_len);
				FFTShift(data_in);
				p_wave->pPointArraySpectrum =(POINT *) new POINT[N];
			

				p_wave->m_FFT_AllNum=N;
				

				//max_spectrum
				max_spectrum=0.0;
				for(int m=0;m<N;m++)
				{
					if(abs(data_in[m])>max_spectrum)
						max_spectrum=abs(data_in[m]);
				}

				for (m=0;m<N;m++)
				{
					p_wave->pPointArraySpectrum[m].x=long(m);
					p_wave->pPointArraySpectrum[m].y=10*log10(abs(data_in[m])/max_spectrum);
				
				}
				data_in.clear();
				p_wave->IorQFlg();	//图像生成完毕后首先显示I|Q图像
				

				/************************************************************************/
				/* CCDF图的绘制 Burst                                                        */
				/************************************************************************/
				p_ccdf->m_RealValuenSize = sig_len;

				double *pPointArrayCCDF;

				//设定一个中间变量数组，存放实际数据的功率
				pPointArrayCCDF =(double*)new double[sig_len];//设定一个中间变量数组


				//CCDF设定一个数组，固定长度
				//确定间隔个数 == X轴总点数-1
				Num_of_space=(p_ccdf->m_AllNum)-1;
				m_AllNum=p_ccdf->m_AllNum;
				ScaleXend=p_ccdf->m_ScaleValueXEnd;
				p_ccdf->pPointArrayCCDF=(double*)new double[m_AllNum];//CCDF设定一个数组

				//计算功率
				for (int i=0;i<sig_len;i++)
				{
					pPointArrayCCDF[i]=pow(protocolIndexG.S_PPDU[i].real(),2)+pow(protocolIndexG.S_PPDU[i].imag(),2);
				}

				max_ccdf=sumCCDF(p_ccdf->pPointArrayCCDF,pPointArrayCCDF,sig_len,ScaleXend,Num_of_space);
				p_ccdf->m_maxCCDFX=max_ccdf;

				delete[] pPointArrayCCDF;

				/************************************************************************/
				/* CCDF图的绘制 wave                                                        */
				/************************************************************************/
				p_ccdf->m_RealValuenSize = sig_len_idle;

				double *pPointArrayWAVE;

				//设定一个中间变量数组，存放实际数据的功率
				pPointArrayWAVE =(double*)new double[sig_len_idle];//设定一个中间变量数组


				//CCDF设定一个数组，固定长度
				//确定间隔个数 == X轴总点数-1
				//Num_of_space=(p_ccdf->m_AllNum)-1;
				//m_AllNum=p_ccdf->m_AllNum;
				//ScaleXend=p_ccdf->m_ScaleValueXEnd;
				p_ccdf->pPointArrayWAVE=(double*)new double[m_AllNum];//CCDF设定一个数组

				//计算功率
				for (int i=0;i<sig_len;i++)
				{
					pPointArrayWAVE[i]=pow(protocolIndexG.S_PPDU[i].real(),2)+pow(protocolIndexG.S_PPDU[i].imag(),2);
				}
				for (int i=sig_len;i<sig_len_idle;i++)
				{
					pPointArrayWAVE[i]=0;
				}
				max_ccdf=sumCCDF(p_ccdf->pPointArrayWAVE,pPointArrayWAVE,sig_len_idle,ScaleXend,Num_of_space);
				p_ccdf->m_maxWAVEX=max_ccdf;

				delete[] pPointArrayWAVE;
				//绘图完成清空协议生成的数据
				delete[] protocolIndexG.S_PPDU;

				p_ccdf->burstflag();
				//在图像的绘制操作完成后，再使能两个图像上的comboBox
				DataAndGraph->p_graphCCDF->m_comboCCDF.SetCurSel(0);
				DataAndGraph->p_graphWAVE->m_comboWAVE.SetCurSel(0);
				DataAndGraph->p_graphCCDF->m_comboCCDF.EnableWindow(TRUE);
				DataAndGraph->p_graphWAVE->m_comboWAVE.EnableWindow(TRUE);

				
				break;
			}
		case OneNL:
		case OneN:
			{      
				/************************************************************************/
				/* 生成802.11n基带信号                                                     */
				/************************************************************************/
				//txvector 参数设置
				//一、	波形设置
				//InterfaceClass InterfaceClassObject;
				configN * m_configNIndex = DataAndGraph->m_configNIndex;
				InterfaceClassObject11n.txvector.format = DataAndGraph->m_configNIndex->txvector_format;
				InterfaceClassObject11n.txvector.scramSeed = DataAndGraph->m_configNIndex->scramSeed;
				//1、波形产生模式（FORMAT）
				//‘Legacy’、802.11a的继承模式
				//‘non_HT_DUP duplicate模式
				//‘HT-MM’ 802.11n的混合传输模式（HT-mixedmode）
				//‘HT-GF’ 802.11n的绿野模式（HT-greenfield）
				//默认HT-MM
				InterfaceClassObject11n.txvector.BW_str = DataAndGraph->m_configNIndex->BandWidth;
				int bandwidth = InterfaceClassObject11n.txvector.BW_str == "20" ? 20000000:40000000;
				//带宽（Bandwidth）
				//默认20MHz//可选参数 20、40
				InterfaceClassObject11n.txvector.N_TX =DataAndGraph->m_configNIndex->Nt ;//天线数目：Legacy模式为1，不可选；HT模式为1-4
				//InterfaceClassObject.txvector.N_sts //空时流数目（Nsts）：不可编辑，由程序计算得来
				InterfaceClassObject11n.txvector.NDP = 0;
				//数据包类型
				//NDP：空数据包，取值为0或1，0表示数据包（PPDU），1表示空数据包，默认为0
				InterfaceClassObject11n.txvector.applyWindow = DataAndGraph->m_configNIndex->win;
				//时域加窗（applyWindow）：‘0’表示不加窗，‘1’表示加窗；大概对应安捷伦的filter,默认为1

				//二、	协议参数
				//HT模式
				//1.调制编码
				InterfaceClassObject11n.txvector.MCS = DataAndGraph->m_configNIndex->mcs;//改为可调mcs
				//MCS索引 由用户输入，程序中有规定范围，0-76，默认1
				//InterfaceClassObject.txvector.N_ss  空间流数 由程序给出，但是需要在页面显示
				//调制方式，码率，数据速率   根据MCS索引显示，不可编辑
				InterfaceClassObject11n.txvector.numExtenSS = DataAndGraph->m_configNIndex->Ness;
				InterfaceClassObject11n.txvector.N_ss=DataAndGraph->m_configNIndex->Nss;
				//扩展空间流（NUM_EXTEN_SS）：设为0，目前修改无效，但应该处于可编辑状态
				InterfaceClassObject11n.txvector.STBC = DataAndGraph->m_configNIndex->STBC;
				InterfaceClassObject11n.txvector.N_sts = DataAndGraph->m_configNIndex->num_of_sts;
				InterfaceClassObject11n.txvector.Short_GI = DataAndGraph->m_configNIndex->Short_GI;
				//短保护间隔（shortGI）：取值0表示常规保护间隔，1表示短保护间隔。默认为0.界面可以用“关”表示0，“开”表示1.
				InterfaceClassObject11n.txvector.UseBF = 0;
				//波束赋形（Beamforming）：0表示没有Beamforming，1表示有。界面可以用‘是’表示1，‘否’表示0
				InterfaceClassObject11n.txvector.ieeeQ =DataAndGraph->m_configNIndex->ieeeQ;
				//空间映射机制（spatial mapping）：取值0，单位映射，最多支持4天线；1，IEEE一致映射；
				//2，波束赋形；4，FFT矩阵；5，直接映射。当波束赋形选择“是”时，此选项应为2.
				//InterfaceClassObject.txvector.TxBf
				//空间映射矩阵 对应显示出上述映射机制对应的映射矩阵。非配置
				InterfaceClassObject11n.txvector.scramSeed = DataAndGraph->m_configNIndex->scramSeed;
				//扰码初始值（scramble seed）:取值1-127，默认89.数值由用户输入。
				InterfaceClassObject11n.txvector.LDPC_Coding = DataAndGraph->m_configNIndex->LDPC_Coding;
				//信道编码方式：程序中的参数是LDPC_Coding，‘0’表示BCC，‘1’表示LDPC，界面上可以写BCC与LDPC，默认为0; 目前LDPC代码还需要调试
				InterfaceClassObject11n.txvector.interleave_state = DataAndGraph->m_configNIndex->interleave_state;
				//交织：BCC方式，可选择开与关；LDPC方式下，关，不可编辑,程序中没设置交织的开启参数，BCC编码时用，LDPC编码不用
				InterfaceClassObject11n.txvector.scrambler = DataAndGraph->m_configNIndex->scrambler;
				//扰码器
				//2、	载荷配置
				InterfaceClassObject11n.txvector.aggregation = DataAndGraph->m_configNIndex->aggregation;
				//聚合MPDU：0表示‘关’，1表示‘开’，默认为0
				InterfaceClassObject11n.txvector.smoothing = DataAndGraph->m_configNIndex->smoothing;
				//Smoothing：平滑，0表示‘关’，1表示‘开’，默认为0
				InterfaceClassObject11n.txvector.sounding = DataAndGraph->m_configNIndex->sounding;
				//Sounding：探测MPDU，0表示‘关’，1表示‘开’，默认为0
				
				//数据长度以bit位计数
				int DataLen=DataAndGraph->m_configNIndex->source_length * 8;

				int Numofmpdu=DataAndGraph->m_configNIndex->num_of_mpdus+1;//MPDU个数
				vector<int> src;

				if (DataAndGraph->m_configNIndex->aggregation==1)
				{
					vector<int> src_mpdu,srcn;
					vector<int> mpdu_header,mac_fcs,mpdu_pid,mpdu_dep;
					int mpdu_head,pid;
					for (int index=0;index<Numofmpdu;index++)
					{
						switch((&(DataAndGraph->m_configNIndex->mpdus[index]))->mac_Header)
						{
						    case 1:     //General
								mpdu_head=30 * 8;
						      break;
						    case 2:     //RTS
								mpdu_head=16 * 8;
							  break;
						    case 3:     //CTS
								mpdu_head=10 * 8;
						      break;
						}
		

					    for (int i=0;i<mpdu_head;i++)//MAC头
					    {
						    mpdu_header.push_back(0);
					    }

						int mpdu_data_len=((&(DataAndGraph->m_configNIndex->mpdus[index]))->DataSource_len) * 8;//负载长度
						src_mpdu = GenerateSource((&(DataAndGraph->m_configNIndex->mpdus[index]))->s_mode,mpdu_data_len,10,DataAndGraph->m_configNIndex->filepath);
						
						if ((&(DataAndGraph->m_configNIndex->mpdus[index]))->mac_FCS)
						{
						    for (int i=0;i<32;i++)//MAC-FCS
						    {
							    mac_fcs.push_back(0);
						    }
						}

						pid=(&(DataAndGraph->m_configNIndex->mpdus[index]))->A_Subframe_len-4-(&(DataAndGraph->m_configNIndex->mpdus[index]))->MPDU_len;
						pid=pid*8;
						for (int i=0;i<pid;i++)//填充字节
						{
							mpdu_pid.push_back(0);
						}

						int *mpdu_lengthtmp=num2bitsv(&(&(DataAndGraph->m_configNIndex->mpdus[index]))->MPDU_len, 1,12);
						int mpdu_length[12];
						for (int i=0;i<4;i++)//保留位
						{
							mpdu_dep.push_back(0);
						}
						for(int i=0;i<12;i++)
						{
							mpdu_length[i]=mpdu_lengthtmp[11-i];
							//crc_bits[i]=mcsbits[i];
							mpdu_dep.push_back(mpdu_length[i]);
						}
						vector<int> crc_bits(16);
						for (int i=0;i<16;i++)
						{
							crc_bits[i]=mpdu_dep[i];
						}
						int crc=crc8(crc_bits);
						int c[1]={crc};
						int *crc_b=num2bitsv(c,1,8);//crc转换
						for (int i=0;i<8;i++)
						{
							mpdu_dep.push_back(crc_b[i]);
						}
						mpdu_dep.push_back(0);//签名
						mpdu_dep.push_back(1);
						mpdu_dep.push_back(0);
						mpdu_dep.push_back(0);
						mpdu_dep.push_back(1);
						mpdu_dep.push_back(1);
						mpdu_dep.push_back(1);
						mpdu_dep.push_back(0);
						srcn.insert(srcn.end(),  mpdu_dep.begin(),  mpdu_dep.end());
						srcn.insert(srcn.end(),  mpdu_header.begin(),  mpdu_header.end());
						srcn.insert(srcn.end(),  src_mpdu.begin(),  src_mpdu.end());
						srcn.insert(srcn.end(),  mac_fcs.begin(),  mac_fcs.end());
						srcn.insert(srcn.end(),  mpdu_pid.begin(),  mpdu_pid.end());
						mpdu_dep.clear();
						mpdu_header.clear();
						src_mpdu.clear();
						mac_fcs.clear();
						mpdu_pid.clear();
					
					//src.push_back(src_mpdu);
					src.insert(src.end(),  srcn.begin(),  srcn.end());
					srcn.clear();
					}

				} 
				else
				{
					src = GenerateSource(DataAndGraph->m_configNIndex->source_mode,DataLen,10,DataAndGraph->m_configNIndex->filepath);
				}
				
				DataLen=src.size();
				InterfaceClassObject11n.DataGenerate(DataLen,src);// DataLen 应该是8的倍数	
				int sig_len =InterfaceClassObject11n.txSignal[0][0].size();
				DataAndGraph->m_configNIndex->length=sig_len;
				//导出数据
				/*ofstream of("11nGF.csv");
				//for(int i =0 ;i < DataAndGraph->m_configNIndex->Nr ;i++)
				for(int i =0 ;i < 2 ;i++)
				{
					if(i==0)
						of << "Y1"<<endl;
					else
						of << "Y2"<<endl;
					for(int cnt = 0;cnt<20;cnt++){
						for(int j =0 ;j < sig_len ;j++)
						{
							of << InterfaceClassObject11n.txSignal[0][i][j].real()<<","<<InterfaceClassObject11n.txSignal[0][i][j].imag()<<endl;
							//of << InterfaceClassObject11n.txSignal[0][2][j].real()<<","<<InterfaceClassObject11n.txSignal[0][2][j].imag()<<endl;
						}
						for(int idle=0;idle<100;idle++)
							of << 0<<","<<0<<endl;
					}

				}
				of.close();*/
				double   dt;//带宽的倒数
				if (bandwidth==20000000)
				{
					dt=1 / 20e6;
				} 
				else
				{
					dt=1 / 40e6;
				}
				vector<double> t;
				double Data_temp_real,Data_temp_imag;
				int i;
				for (i=0; i<sig_len; i++ )
				{
					t.push_back(i*dt);
				}  
				for(i=0;i<DataAndGraph->m_configNIndex->Nt;i++)
				{
					for (int j=0; j<sig_len; j++ )
				    {
					    Data_temp_real = cos(2*pi*DataAndGraph->m_configNIndex->FrequencyOffset*t[j]);
					    Data_temp_imag = sin(2*pi*DataAndGraph->m_configNIndex->FrequencyOffset*t[j]);
					    InterfaceClassObject11n.txSignal[0][i][j].real(InterfaceClassObject11n.txSignal[0][i][j].real()*Data_temp_real - InterfaceClassObject11n.txSignal[0][i][j].imag()*Data_temp_imag);
					    InterfaceClassObject11n.txSignal[0][i][j].imag(InterfaceClassObject11n.txSignal[0][i][j].real()*Data_temp_imag + InterfaceClassObject11n.txSignal[0][i][j].imag()*Data_temp_real);
				    }  
				}
				//CTabCarrier &m_carrier=((CTabParent*)(((CMainFrame*)AfxGetMainWnd())->m_mainSplitter.GetPane(0,0)))->m_tabCarrier;
				//char str[10];
				//m_carrier.pPropS2->SetValue(itoa(sig_len,str,10));
				if(DataAndGraph->m_configNIndex->add_channel)
				{
					int Nt=DataAndGraph->m_configNIndex->Nt;
					int Nr=DataAndGraph->m_configNIndex->Nr;
					double* Indata_r = new double[sig_len*Nt];
					double* Indata_i = new double[sig_len*Nt];
					//导入发端天线数据
					for(int i =0 ;i < sig_len ;i++)
					{
						for(int j =0 ;j < Nt ;j++)
						{
							Indata_r[j+i*Nt] = InterfaceClassObject11n.txSignal[0][j][i].real();
							Indata_i[j+i*Nt] = InterfaceClassObject11n.txSignal[0][j][i].imag();
						}

					}
					
					int uplink=1;
					int Nd=1;  
					int ml = 2;
					int NumOfChannels=Nr*Nt;
					int LengthOfBurst=sig_len;
					int FFT_size=64;   
					int LengthOfCpBurst=16;    
					double BW=bandwidth;    
					double SampleFreq=BW;  
					int NumOfFreq=8;
					double MobileSpeed=DataAndGraph->m_configNIndex->mobilespeed;
					double CarrierFrequency = DataAndGraph->m_configNIndex->carrierfreq;
					char Channel_Type= DataAndGraph->m_configNIndex->channel_type;
					double IntervalBetweenFrames=LengthOfBurst/SampleFreq;

					vector<double> An;
					vector<double> Bn;
					vector<double> Wn;

					double NumOfTaps;

					vector<double> RndPhase;
					double UpdateInterval = 0.0;
					double UpdatesPerBurst = 0.0;
					double dt = 1 / 20e6;

					vector<double> Path_Delay;
					vector<double> Path_Power;
					vector<double> Path_Average_Amp;
					vector<double> aglsprR;
					vector<double> aglR;
					vector<double> aglsprT;
					vector<double> aglT;

					double dR = 0.0;
					double dT = 0.0;

					vector<double> distypeR;
					vector<double> distypeT;

					double corrmodel = 0.0;
					double alf = 0.0;
					double fd = 0.0;
					double loson = 0.0;
					int SampleIndex = 0.0;

					vector<double> fore_data_pr(100,0);
					vector<double> fore_data_pi(100,0);
					vector<double> OutData_pr;
					vector<double> OutData_pi;
					vector<double> out_fading_pr;
					vector<double> out_fading_pi;

					Multipath_Channel_Init_80211n(An,Bn,Wn,NumOfTaps,RndPhase,
						UpdateInterval,UpdatesPerBurst,dt,Path_Delay,Path_Power,
						Path_Average_Amp,aglsprR,aglR,aglsprT,aglT,dR,dT,
						distypeR,distypeT,corrmodel,alf,fd,loson, 
						LengthOfBurst,IntervalBetweenFrames,MobileSpeed,CarrierFrequency,
						NumOfFreq,NumOfChannels,Channel_Type,uplink);

					corrj_channel(	Indata_r,Indata_i, An, Bn, Wn,
						RndPhase,  NumOfFreq,  UpdateInterval,  UpdatesPerBurst, 
						LengthOfBurst,  SampleIndex,  dt,  NumOfTaps, 
						Path_Delay,  Path_Average_Amp,  
						fore_data_pr,fore_data_pi, OutData_pr, 
						OutData_pi, out_fading_pr, out_fading_pi,
						Nr, Nt, aglsprR,aglR, aglsprT,aglT,
						dR, dT,distypeR,distypeT, corrmodel, alf,
						fd, loson, uplink);
					//channel end
					for(int i =0;i < Nr;i++)
						for(int j =0;j< LengthOfBurst;j++)
						{
							complex<double> temp;
							temp.real(OutData_pr[j*Nr+i]);
							temp.imag(OutData_pi[j*Nr+i]);
							InterfaceClassObject11n.txSignal[0][i][j] = temp;
						}
				}
						//过采滤波
						int over_ratio = m_configNIndex->oversample_ratio;
						if(over_ratio >1)
					{
							vector<complex<double>> after_oversample;
							after_oversample.resize(sig_len * over_ratio);
							complex<double> zero(0.0,0.0);
							//分天线过采滤波
							for(int k = 0;k < m_configNIndex->Nr; k++)
						{
								for(int i = 0; i < sig_len * over_ratio ; i++)
								{
									if( (i % over_ratio) == 0)
										after_oversample[i] = InterfaceClassObject11n.txSignal[0][k][ i/4 ];
									else
										after_oversample[i] = zero ;
								}

								switch(m_configNIndex->filter_para.filtertype)
								{
								case lpfilter:
									{
										vector<double> filter_coef = Lowpass_filter(m_configNIndex->filter_para.lppara.length,m_configNIndex->filter_para.lppara.wn);
										My_conv(after_oversample,filter_coef,sig_len * over_ratio);
										InterfaceClassObject11n.txSignal[0][k] = after_oversample;
										break;
									}
								case gaussfilter:
									{
										vector<double> filter_coef = Gauss_filter(m_configNIndex->filter_para.gausspara.length,m_configNIndex->filter_para.gausspara.BT);
										My_conv(after_oversample,filter_coef,sig_len * over_ratio);
										InterfaceClassObject11n.txSignal[0][k] = after_oversample;
										break;
									}
								case cosfilter:
									{
										vector<double> filter_coef = Root_raised_cosine(m_configNIndex->filter_para.cosinepara.alpha,m_configNIndex->filter_para.cosinepara.length);
										My_conv(after_oversample,filter_coef,sig_len * over_ratio);
										InterfaceClassObject11n.txSignal[0][k] = after_oversample;
										break;
									}
								case userdefined:
									{
										My_conv(after_oversample,m_configNIndex->filter_user,sig_len * over_ratio);
										InterfaceClassObject11n.txSignal[0][k] = after_oversample;
										break;
									}
								}
							}
														
				 }
				
                sig_len*= DataAndGraph->m_configNIndex->oversample_ratio;

				//加正交角度调整，IQ平衡增益
				double I_Q_max=0.0,I_data,Q_data=0.0;
				//double *I_gfsk=new double[sig_len];
				//double *Q_gfsk=new double[sig_len];
				double real_temp = 0;
				double imag_temp = 0;
				double IQ_gain = DataAndGraph->m_configNIndex->IQ_gain;//注意与自己的对应
				double qAngleAD = DataAndGraph->m_configNIndex->quan_angle_adjust;
				if(DataAndGraph->m_configNIndex->add_channel == false)//不加信道的时候如果改正交角度调整或IQ平衡增益就会做如下公式
				{
					for(int i =0 ;i < DataAndGraph->m_configNIndex->Nt ;i++)
					{
					    for (int j = 0; j < sig_len; ++j)
					    {
						    real_temp = InterfaceClassObject11n.txSignal[0][i][j].real() - pow(10,(IQ_gain/10))*sin(qAngleAD)*InterfaceClassObject11n.txSignal[0][i][j].imag();
						    imag_temp = pow(10,(IQ_gain/10))*cos(qAngleAD)*InterfaceClassObject11n.txSignal[0][i][j].imag();
						    InterfaceClassObject11n.txSignal[0][i][j].real(real_temp);
						    InterfaceClassObject11n.txSignal[0][i][j].imag(imag_temp);
					    }
					}
				}

				//导出数据
				int num_of_zeros=DataAndGraph->m_configNIndex->num_of_zeros;
				int num_of_frame=DataAndGraph->m_configNIndex->num_of_frame;
				ofstream of("11nGF.csv");
				//for(int i =0 ;i < DataAndGraph->m_configNIndex->Nr ;i++)
				for(int i =0 ;i < DataAndGraph->m_configNIndex->Nt ;i++)
				{
					if(i==0)
						of << "Y1"<<endl;
					else if(i==1)
						of << "Y2"<<endl;
					else if(i==2)
						of << "Y3"<<endl;
					else
						of << "Y4"<<endl;
					for(int cnt = 0;cnt<num_of_frame;cnt++){
						for(int j =0 ;j < sig_len ;j++)
						{
							of << InterfaceClassObject11n.txSignal[0][i][j].real()<<","<<InterfaceClassObject11n.txSignal[0][i][j].imag()<<endl;
							//of << InterfaceClassObject11n.txSignal[0][2][j].real()<<","<<InterfaceClassObject11n.txSignal[0][2][j].imag()<<endl;
						}
						for(int idle=0;idle<num_of_zeros;idle++)
							of << 0<<","<<0<<endl;
					}

				}
				of.close();

				int sig_len_idle=sig_len;
				int I_Q_base;
				int interval_len =0;
				
				/************************************************************************/
				/* 生成 41 要求格式的信号文件                                           */
				/************************************************************************/
				for(int k=0;k<DataAndGraph->m_configNIndex->Nt;k++){
					

					//统计各天线的IQ范围
					double I_Q_range=0.0,temp,temp_i,temp_r;
					for(int i=0;i<sig_len;i++)
					{   
						temp_r = abs(InterfaceClassObject11n.txSignal[0][k][i].real());
						temp_i = abs(InterfaceClassObject11n.txSignal[0][k][i].imag());
						temp = temp_r > temp_i ? temp_r :temp_i;
						if(temp>I_Q_range)
							I_Q_range =temp;
					}
					I_Q_base =(int)(32767/I_Q_range);
					CFile file;
					CString filename;
					filename.Format("802_11n_tx_%d.seg",k+1);
					file.Open(_T(filename),CFile::modeCreate|CFile::modeWrite);
					CArchive ar(&file,CArchive::store);//写操作

					//256字节头部
					char ei41Name[8] = {'e','i','4','1','\0','\0','\0','\0'};//公司名称
					for (int i=0;i!=8;i++)
						ar<<ei41Name[i];

					INT64 timeFrequency = bandwidth;//时钟频率
					//INT64 timeFrequency = 10000000;//时钟频率
					ar<<timeFrequency;

					INT64 elementLength = sig_len + interval_len;//码元长度
					ar<<elementLength;

					INT64 samplePoints = 1;//过采样点数
					ar<<samplePoints;

					INT64 points = sig_len + interval_len;//样点个数
					ar<<points;

					INT64 cycleTime = points / timeFrequency * 1000;//周期 = 样点个数*时钟频率 毫秒为单位；
					ar<<cycleTime;

					INT64  padBits[26]={0};//填充208位字节
					for (int i =0;i!=26;i++)
						ar<<padBits[i];

					//基带信号数据段
					for (int i=0;i!=sig_len;i++)
					{
						ar<<(INT16)(InterfaceClassObject11n.txSignal[0][k][i].real()*I_Q_base +32768)<<(INT16)(InterfaceClassObject11n.txSignal[0][k][i].imag()*I_Q_base +32768);
					}

					for (int i=0;i<interval_len;i++)//这里50000是随便设置的数，可以根据应用场景自行调整
						ar<<static_cast<INT16>(0)<<static_cast<INT16>(0);

					ar.Close();
					file.Close();
				}
				

				DataAndGraph->file_size = 256 + (sig_len+interval_len) * 2 * 2; // 每个sig_len有2字节，一个长度对应实部和虚部两位，所以最后乘以4
				/************************************************************************/
				/* WAVE图绘制（I+Q、I|Q、power、Spectrum）                              */
				/************************************************************************/
				int num_of_antenna =DataAndGraph->m_configNIndex->Nt;
				for(int k=0;k<num_of_antenna;k++)
				{
					//选择对应的视图
					p_wave =&(DataAndGraph->p_graphWAVE->m_wave[k]);
					p_ccdf =&(DataAndGraph->p_graphCCDF->m_ccdf[k]);

					p_wave->m_RealValuenSize = sig_len;	
					p_wave->m_ScaleValueXEnd =sig_len;

					p_wave->I_Data = new double[sig_len];
					p_wave->Q_Data = new double[sig_len];


					//统计各天线的IQ范围
					double I_Q_range=0.0,temp,temp_i,temp_r;
					for(int i=0;i<sig_len;i++)
					{   
						temp_r = abs(InterfaceClassObject11n.txSignal[0][k][i].real());
						temp_i = abs(InterfaceClassObject11n.txSignal[0][k][i].imag());
						temp = temp_r > temp_i ? temp_r :temp_i;
						if(temp>I_Q_range)
							I_Q_range =temp;
					}
					//设置范围，保留一位有效数字
					p_wave->m_IQ_range =((int)(I_Q_range*10))/10.0;

					/**********I+Q 数据导入绘图类**********/
					for (int i=0;i<sig_len;i++)
					{
						p_wave->I_Data[i]=InterfaceClassObject11n.txSignal[0][k][i].real();//>pPointArray[i].x 改成 I_Data[i]
						p_wave->Q_Data[i]=InterfaceClassObject11n.txSignal[0][k][i].imag();


					}
					/**********Power图的绘制**********/
					p_wave->pPointArrayPower =(POINT *) new POINT[sig_len];
					max_power=0.0;//初始化
					//找到功率最大点
					for (int j=0;j<sig_len;j++)
					{
						double temp = pow(InterfaceClassObject11n.txSignal[0][k][j].real(),2)+pow(InterfaceClassObject11n.txSignal[0][k][j].imag(),2);
						if(temp>max_power)
						{
							max_power=temp;
						}
					}			
					//计算每个信号点相对于最大功率点的dB值
					for (int j=0;j<sig_len;j++)
					{
						p_wave->pPointArrayPower[j].x=long(j);
						p_wave->pPointArrayPower[j].y=10*log10((pow(InterfaceClassObject11n.txSignal[0][k][j].real(),2)+pow(InterfaceClassObject11n.txSignal[0][k][j].imag(),2))/max_power);			

					}
					/**********Spectrum的绘制**********/
					//数组转容器
					data_in[k].resize(sig_len);
					for (int m=0;m<sig_len;m++)
					{
						data_in[k][m]=InterfaceClassObject11n.txSignal[0][k][m];
					}
					//FFT计算频谱
					N=FFT(data_in[k],sig_len);
					FFTShift(data_in[k]);
					p_wave->pPointArraySpectrum =(POINT *) new POINT[N];
					p_wave->m_FFT_AllNum=N;
				
					//max_spectrum
					max_spectrum=0.0;
					for(int m=0;m<sig_len;m++)//sig_len
					{
						if(abs(data_in[k][m])>max_spectrum)
							max_spectrum=abs(data_in[k][m]);
					}

					for(int m=0;m<N;m++)
					{
						p_wave->pPointArraySpectrum[m].x=long(m);
						p_wave->pPointArraySpectrum[m].y=10*log10(sqrt(abs(data_in[k][m])/max_spectrum));

					}
					p_wave->IorQFlg();	//图像生成完毕后首先显示I|Q图像
					data_in[k].clear();

					/************************************************************************/
					/* CCDF图的绘制                                                         */
					/************************************************************************/
					p_ccdf->m_RealValuenSize = sig_len;


					double *pPointArrayCCDF;

					//设定一个中间变量数组，存放实际数据的功率
					pPointArrayCCDF =(double*)new double[sig_len];


					//CCDF设定一个数组，固定长度
					//确定间隔个数 == X轴总点数-1
					Num_of_space=(p_ccdf->m_AllNum)-1;
					m_AllNum=p_ccdf->m_AllNum;
					ScaleXend=p_ccdf->m_ScaleValueXEnd;
					p_ccdf->pPointArrayCCDF=(double*)new double[m_AllNum];//CCDF设定一个数组

					//计算功率
					for (i=0;i<sig_len;i++)
					{
						pPointArrayCCDF[i]=pow(InterfaceClassObject11n.txSignal[0][k][i].real()/8,2)+pow(InterfaceClassObject11n.txSignal[0][k][i].imag()/8,2);

					}

					max_ccdf=sumCCDF(p_ccdf->pPointArrayCCDF,pPointArrayCCDF,sig_len,ScaleXend,Num_of_space);
					p_ccdf->m_maxCCDFX=max_ccdf;
			
					

					double *pPointArrayWAVE;

					//设定一个中间变量数组，存放实际数据的功率
					pPointArrayWAVE =(double*)new double[sig_len_idle];
					p_ccdf->pPointArrayWAVE=(double*)new double[m_AllNum];//CCDF设定一个数组

					//计算功率
					for (int i=0;i<sig_len;i++)
					{
						pPointArrayWAVE[i]=pow(InterfaceClassObject11n.txSignal[0][k][i].real()/8,2)+pow(InterfaceClassObject11n.txSignal[0][k][i].imag()/8,2);

					}
					for(int i=sig_len;i<sig_len_idle;i++){
						pPointArrayWAVE[i]=0.0;
					}
					max_ccdf=sumCCDF(p_ccdf->pPointArrayWAVE,pPointArrayWAVE,sig_len_idle,ScaleXend,Num_of_space);
					p_ccdf->m_maxWAVEX=max_ccdf;
					 
					p_ccdf->burstflag();
					delete[] pPointArrayCCDF;
					delete[] pPointArrayWAVE;
					InterfaceClassObject11n.txSignal[0][k].clear();

					//在图像的绘制操作完成后，再使能两个图像上的comboBox
					DataAndGraph->p_graphCCDF->m_comboCCDF.SetCurSel(0);
					DataAndGraph->p_graphWAVE->m_comboWAVE.SetCurSel(0);
					DataAndGraph->p_graphCCDF->m_comboCCDF.EnableWindow(TRUE);
					DataAndGraph->p_graphWAVE->m_comboWAVE.EnableWindow(TRUE);
				
				}
				DataAndGraph->p_graphCCDF->m_ccdf[0].ShowWindow(SW_SHOW);
				DataAndGraph->p_graphWAVE->m_wave[0].ShowWindow(SW_SHOW);
				DataAndGraph->p_graphCCDF->m_ccdf[1].ShowWindow(SW_HIDE);
				DataAndGraph->p_graphWAVE->m_wave[1].ShowWindow(SW_HIDE);
				DataAndGraph->p_graphCCDF->m_ccdf[2].ShowWindow(SW_HIDE);
				DataAndGraph->p_graphWAVE->m_wave[2].ShowWindow(SW_HIDE);
				DataAndGraph->p_graphCCDF->m_ccdf[3].ShowWindow(SW_HIDE);
				DataAndGraph->p_graphWAVE->m_wave[3].ShowWindow(SW_HIDE);

			   break;
			}
		
	  default:
		  break;
		}		
		return 0;
}

//系统配置向导响应函数
void CMainFrame::OnSystemConfigWiz()
{
	// TODO: 在此添加命令处理程序代码
	CSysConfigWizard wzd("系统配置向导",this,0);


	//将当前的连接信息传入向导，如果重新设置了连接信息，由向导将其关闭
	wzd.defaultRM = defaultRM;
	for (int i = 0;i<8;i++)
	{
		wzd.vi[i] = vi[i];
	}
	//下面是向导退出后的一些操作
	//向导完成退出且仪器连接成功
	if (ID_WIZFINISH == wzd.DoModal() && wzd.b_instr_connected)
	{
		b_instr_connected = TRUE;

		//从配置向导中导出变量
		m_num_instr = wzd.m_num_instruments;
		defaultRM = wzd.defaultRM;

		CTabInstrument* p_tab_instrument = &(((CTabParent*)m_mainSplitter.GetPane(0,0))->m_tabInstrument);
		p_tab_instrument->m_combo_instrument_index.ResetContent();//将仪器配置页的仪器索引清空
		p_tab_instrument->send_command_enabled = TRUE;//将仪器配置页实时更新仪器状态的功能打开

		CString str_temp = "";
		char ch[256] = "";
		ViStatus error_no = 0;
		ViUInt32 write_cnt = 0;
		ViUInt32 read_cnt = 0;
		for(int i = 0;i<m_num_instr;i++)
		{
			vi[i] = wzd.vi[i];

			str_temp.Format("%d",i+1);
			p_tab_instrument->m_combo_instrument_index.InsertString(i,str_temp);
            //写查询命令
			//  the location of a data block to be sent to device
			//  number of bytes to be written
			//  Represents the location of an integer (实际发送的字节数）
			error_no = viWrite(vi[i],(ViBuf)"FREQ?\n",256,&write_cnt);
			Sleep(10);
	
            //读取相应的数据
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);

			ch[read_cnt-1] = '\0';//将返回的'\n'置为'\0',避免回车键对配置的影响
			str_temp.Format("%sHz",ch);
			p_tab_instrument->instr_params[i].frequency = str_temp;


			error_no = viWrite(vi[i],(ViBuf)"POW?\n",256,&write_cnt);
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);
			ch[read_cnt-1] = '\0';
			str_temp.Format("%sdBm",ch);
			p_tab_instrument->instr_params[i].amplitude = str_temp;
			
			error_no = viWrite(vi[i],(ViBuf)"OUTP?\n",256,&write_cnt);
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s",ch);
			p_tab_instrument->instr_params[i].RF_output = atoi(str_temp.GetBuffer())==0 ? "OFF" : "ON";

			error_no = viWrite(vi[i],(ViBuf)"POW:ALC:STAT?\n",256,&write_cnt);
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s",ch);
			p_tab_instrument->instr_params[i].ALC = atoi(str_temp.GetBuffer())==0 ? "OFF" : "ON";
		}

		p_tab_instrument->m_combo_instrument_index.SetCurSel(0);
		p_tab_instrument->vi = vi[0];
		p_tab_instrument->p_frequency->SetValue((COleVariant)p_tab_instrument->instr_params[0].frequency);
		p_tab_instrument->p_amplitude->SetValue((COleVariant)p_tab_instrument->instr_params[0].amplitude);
		p_tab_instrument->p_RF_output->SetValue((COleVariant)p_tab_instrument->instr_params[0].RF_output);
		p_tab_instrument->p_ALC->SetValue((COleVariant)p_tab_instrument->instr_params[0].ALC);

	}
	else
	{
		b_instr_connected = FALSE;
	}
}


void CMainFrame::OnHardwareConnectionWiz()
{
	// TODO: 在此添加命令处理程序代码
	CSysConfigWizard wzd("系统配置向导",this,0);
	wzd.SetActivePage(2);

	/*if (ID_WIZFINISH == wzd.DoModal())
	{
	MessageBox("完成按钮点击");
	}*/
	if (ID_WIZFINISH == wzd.DoModal() && wzd.b_instr_connected)
	{
		b_instr_connected = TRUE;

		//从配置向导中导出变量
		m_num_instr = wzd.m_num_instruments;
		defaultRM = wzd.defaultRM;

		CTabInstrument* p_tab_instrument = &(((CTabParent*)m_mainSplitter.GetPane(0,0))->m_tabInstrument);
		p_tab_instrument->m_combo_instrument_index.ResetContent();//将仪器配置页的仪器索引清空
		p_tab_instrument->send_command_enabled = TRUE;//将仪器配置页实时更新仪器状态的功能打开

		CString str_temp = "";
		char ch[256] = "";
		ViStatus error_no = 0;
		ViUInt32 write_cnt = 0;
		ViUInt32 read_cnt = 0;
		for(int i = 0;i<m_num_instr;i++)
		{
			vi[i] = wzd.vi[i];

			str_temp.Format("%d",i+1);
			p_tab_instrument->m_combo_instrument_index.InsertString(i,str_temp);
			//写查询命令
			//  the location of a data block to be sent to device
			//  number of bytes to be written
			//  Represents the location of an integer (实际发送的字节数）
			error_no = viWrite(vi[i],(ViBuf)"FREQ?\n",256,&write_cnt);
			Sleep(10);

			//读取相应的数据
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);

			ch[read_cnt-1] = '\0';//将返回的'\n'置为'\0',避免回车键对配置的影响
			str_temp.Format("%sHz",ch);
			p_tab_instrument->instr_params[i].frequency = str_temp;


			error_no = viWrite(vi[i],(ViBuf)"POW?\n",256,&write_cnt);
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);
			ch[read_cnt-1] = '\0';
			str_temp.Format("%sdBm",ch);
			p_tab_instrument->instr_params[i].amplitude = str_temp;

			error_no = viWrite(vi[i],(ViBuf)"OUTP?\n",256,&write_cnt);
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s",ch);
			p_tab_instrument->instr_params[i].RF_output = atoi(str_temp.GetBuffer())==0 ? "OFF" : "ON";

			error_no = viWrite(vi[i],(ViBuf)"POW:ALC:STAT?\n",256,&write_cnt);
			Sleep(10);
			error_no = viRead(vi[i],(ViBuf)ch,256,&read_cnt);
			ch[read_cnt-1] = '\0';
			str_temp.Format("%s",ch);
			p_tab_instrument->instr_params[i].ALC = atoi(str_temp.GetBuffer())==0 ? "OFF" : "ON";
		}

		p_tab_instrument->m_combo_instrument_index.SetCurSel(0);
		p_tab_instrument->vi = vi[0];
		p_tab_instrument->p_frequency->SetValue((COleVariant)p_tab_instrument->instr_params[0].frequency);
		p_tab_instrument->p_amplitude->SetValue((COleVariant)p_tab_instrument->instr_params[0].amplitude);
		p_tab_instrument->p_RF_output->SetValue((COleVariant)p_tab_instrument->instr_params[0].RF_output);
		p_tab_instrument->p_ALC->SetValue((COleVariant)p_tab_instrument->instr_params[0].ALC);

	}
	else
	{
		b_instr_connected = FALSE;
	}
}

void CMainFrame::OnMainDownload()
{
	// TODO: 在此添加命令处理程序代码
	ViStatus error_no = 0;
	ViUInt32 cnt = 0;
	ViUInt32  length_max = 100;


	INT32 NMBYTE = m_pass_to_thread.file_size;

	//INT32 NMBYTE = 10000000;//申请10M的空间
	//INT32 nBlockNum = 2 * NMBYTE;
	char *SendData = NULL;
	UINT64 response = 0;
	INT32 nReadByte = 0;

	if (b_instr_connected)
	{
		do 
		{
		  SendData = new char[NMBYTE];
		} while (SendData == NULL);


		memset(SendData,0,NMBYTE);
		CFile filedata;
		switch(m_pass_to_thread.m_configIndex->ProtocolModel)
		{
		  case OneA:
		  { 
			  CString CFilename = _T("802_11a.seg");
		      filedata.Open(CFilename.GetBuffer(),CFile::modeRead);
			  char str[100] = {0};
			  int nums = 0;// 文件大小的位数
			  int temp = NMBYTE;
		      while(temp != 0)
		     {
			  temp = temp / 10;
			  nums++;
		      }
		   sprintf(str,"MEMORY:DATA 802_11a.seg,#%d%d\n",nums,NMBYTE);
		   error_no = viWrite(vi[0],(ViBuf)str,strlen(str),&cnt);///////////
		   filedata.SeekToBegin();
		   nReadByte = filedata.Read((void*)SendData,NMBYTE);//读取文件
		   error_no = viWrite(vi[0],(unsigned char*)SendData,NMBYTE,&cnt);//写入仪器
		   Sleep(100);
		   error_no = viWrite(vi[0],(ViBuf)"RADIO:ARB:SEQUENCE NONE,802_11a.seg,1,NONE\n",100,&cnt);//开启任意波
		   Sleep(300);
		   error_no = viWrite(vi[0],(ViBuf)"RADIO:ARB:STATE ON\n",19,&cnt);//下载并播放
		   Sleep(10);
		   break;
		  }

		case OneB:
			{
				CString CFilename = _T("802_11b.seg");
				filedata.Open(CFilename.GetBuffer(),CFile::modeRead);
				char str[100] = {0};
				int nums = 0;// 文件大小的位数
				int temp = NMBYTE;
				while(temp != 0)
				{
					temp = temp / 10;
					nums++;
				}
				sprintf(str,"MEMORY:DATA 802_11b.seg,#%d%d\n",nums,NMBYTE);
				error_no = viWrite(vi[0],(ViBuf)str,strlen(str),&cnt);///////////
				filedata.SeekToBegin();
				nReadByte = filedata.Read((void*)SendData,NMBYTE);//读取文件
				error_no = viWrite(vi[0],(unsigned char*)SendData,NMBYTE,&cnt);//写入仪器
				Sleep(100);
				error_no = viWrite(vi[0],(ViBuf)"RADIO:ARB:SEQUENCE NONE,802_11b.seg,1,NONE\n",100,&cnt);//开启任意波
				Sleep(300);
				error_no = viWrite(vi[0],(ViBuf)"RADIO:ARB:STATE ON\n",19,&cnt);//下载并播放
				Sleep(10);
				break;
			}
			
		case OneG:
			{
				CString CFilename = _T("802_11g.seg");
				filedata.Open(CFilename.GetBuffer(),CFile::modeRead);
				char str[100] = {0};
				int nums = 0;// 文件大小的位数
				int temp = NMBYTE;
				while(temp != 0)
				{
					temp = temp / 10;
					nums++;
				}
				sprintf(str,"MEMORY:DATA 802_11g.seg,#%d%d\n",nums,NMBYTE);
				error_no = viWrite(vi[0],(ViBuf)str,strlen(str),&cnt);///////////
				filedata.SeekToBegin();
				nReadByte = filedata.Read((void*)SendData,NMBYTE);//读取文件
				error_no = viWrite(vi[0],(unsigned char*)SendData,NMBYTE,&cnt);//写入仪器
				Sleep(100);
				error_no = viWrite(vi[0],(ViBuf)"RADIO:ARB:SEQUENCE NONE,802_11g.seg,1,NONE\n",100,&cnt);//开启任意波
				Sleep(300);
				error_no = viWrite(vi[0],(ViBuf)"RADIO:ARB:STATE ON\n",19,&cnt);//下载并播放
				Sleep(10);
				break;
			}
		case OneN:
			{
				CGraphCCDF* m_ccdf =((CGraphCCDF*)(m_rightSplitter.GetPane(0,0)));
				int m_show_id=m_ccdf->m_show_id;; 
				
					
				CString CFilename;
				CFilename.Format("802_11n_tx_%d.seg",m_show_id);
				filedata.Open(CFilename.GetBuffer(),CFile::modeRead);
				char str[100] = {0};
				int nums = 0;// 文件大小的位数
				int temp = NMBYTE;
				while(temp != 0)
				{
					temp = temp / 10;
					nums++;
				}
				sprintf(str,"MEMORY:DATA 802_11n_tx_%d.seg,#%d%d\n",m_show_id,nums,NMBYTE);
				error_no = viWrite(vi[0],(ViBuf)str,strlen(str),&cnt);///////////
				filedata.SeekToBegin();
				nReadByte = filedata.Read((void*)SendData,NMBYTE);//读取文件
				error_no = viWrite(vi[0],(unsigned char*)SendData,NMBYTE,&cnt);//写入仪器
				Sleep(100);
				sprintf(str,"RADIO:ARB:SEQUENCE NONE,802_11n_tx_%d.seg,1,NONE\n",m_show_id);
				error_no = viWrite(vi[0],(ViBuf)str,100,&cnt);//开启任意波
				Sleep(300);
				error_no = viWrite(vi[0],(ViBuf)"RADIO:ARB:STATE ON\n",19,&cnt);//下载并播放
				Sleep(10);
				break;
			}	
	}
	delete[] SendData;
	}
}
void CMainFrame::antenna_1()
{
	// TODO: 在此添加命令处理程序代码
	//MessageBox("天线1");
	 CGraphCCDF* m_ccdf =((CGraphCCDF*)(m_rightSplitter.GetPane(0,0)));
	 CGraphWAVE* m_wave =((CGraphWAVE*)(m_rightSplitter.GetPane(1,0)));
	 m_ccdf->m_show_id =1;
	 m_wave->m_show_id =1;
	 m_ccdf->m_ccdf[0].ShowWindow(SW_SHOW);
	 m_wave->m_wave[0].ShowWindow(SW_SHOW);
	 m_ccdf->m_ccdf[1].ShowWindow(SW_HIDE);
	 m_wave->m_wave[1].ShowWindow(SW_HIDE);
	 m_ccdf->m_ccdf[2].ShowWindow(SW_HIDE);
	 m_wave->m_wave[2].ShowWindow(SW_HIDE);
	 m_ccdf->m_ccdf[3].ShowWindow(SW_HIDE);
	 m_wave->m_wave[3].ShowWindow(SW_HIDE);
}


void CMainFrame::antenna_2()
{
	// TODO: 在此添加命令处理程序代码
	//MessageBox("天线2");
	CGraphCCDF* m_ccdf =((CGraphCCDF*)(m_rightSplitter.GetPane(0,0)));
	CGraphWAVE* m_wave =((CGraphWAVE*)(m_rightSplitter.GetPane(1,0)));
	m_ccdf->m_show_id =2;
	m_wave->m_show_id =2;
	m_ccdf->m_ccdf[0].ShowWindow(SW_HIDE);
	m_wave->m_wave[0].ShowWindow(SW_HIDE);
	m_ccdf->m_ccdf[1].ShowWindow(SW_SHOW);
	m_wave->m_wave[1].ShowWindow(SW_SHOW);
	m_ccdf->m_ccdf[2].ShowWindow(SW_HIDE);
	m_wave->m_wave[2].ShowWindow(SW_HIDE);
	m_ccdf->m_ccdf[3].ShowWindow(SW_HIDE);
	m_wave->m_wave[3].ShowWindow(SW_HIDE);
}

void CMainFrame::antenna_3()
{
	// TODO: 在此添加命令处理程序代码
	//MessageBox("天线2");
	CGraphCCDF* m_ccdf =((CGraphCCDF*)(m_rightSplitter.GetPane(0,0)));
	CGraphWAVE* m_wave =((CGraphWAVE*)(m_rightSplitter.GetPane(1,0)));
	m_ccdf->m_show_id =3;
	m_wave->m_show_id =3;
	m_ccdf->m_ccdf[0].ShowWindow(SW_HIDE);
	m_wave->m_wave[0].ShowWindow(SW_HIDE);
	m_ccdf->m_ccdf[1].ShowWindow(SW_HIDE);
	m_wave->m_wave[1].ShowWindow(SW_HIDE);
	m_ccdf->m_ccdf[2].ShowWindow(SW_SHOW);
	m_wave->m_wave[2].ShowWindow(SW_SHOW);
	m_ccdf->m_ccdf[3].ShowWindow(SW_HIDE);
	m_wave->m_wave[3].ShowWindow(SW_HIDE);
}

void CMainFrame::antenna_4()
{
	// TODO: 在此添加命令处理程序代码
	//MessageBox("天线2");
	CGraphCCDF* m_ccdf =((CGraphCCDF*)(m_rightSplitter.GetPane(0,0)));
	CGraphWAVE* m_wave =((CGraphWAVE*)(m_rightSplitter.GetPane(1,0)));
	m_ccdf->m_show_id =4;
	m_wave->m_show_id =4;
	m_ccdf->m_ccdf[0].ShowWindow(SW_HIDE);
	m_wave->m_wave[0].ShowWindow(SW_HIDE);
	m_ccdf->m_ccdf[1].ShowWindow(SW_HIDE);
	m_wave->m_wave[1].ShowWindow(SW_HIDE);
	m_ccdf->m_ccdf[2].ShowWindow(SW_HIDE);
	m_wave->m_wave[2].ShowWindow(SW_HIDE);
	m_ccdf->m_ccdf[3].ShowWindow(SW_SHOW);
	m_wave->m_wave[3].ShowWindow(SW_SHOW);
}

void CMainFrame::OnUpdate_antenna_1(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	int num_of_antenna =m_pass_to_thread.m_configNIndex->Nt;
	if(num_of_antenna>=1)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}


void CMainFrame::OnUpdate_antenna_2(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
    int num_of_antenna =m_pass_to_thread.m_configNIndex->Nt;
	if(num_of_antenna>=2)
		pCmdUI->Enable(TRUE);
	else
	    pCmdUI->Enable(FALSE);
}
void CMainFrame::OnUpdate_antenna_3(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	int num_of_antenna =m_pass_to_thread.m_configNIndex->Nt;
	if(num_of_antenna>=3)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}
void CMainFrame::OnUpdate_antenna_4(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	int num_of_antenna =m_pass_to_thread.m_configNIndex->Nt;
	if(num_of_antenna==4)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}
void CMainFrame::ConfigRead(){
	
	using namespace rapidxml;//不能省略
	//获取文件名
	CString FilePathName;
	CFileDialog dlg(TRUE,NULL, NULL,OFN_FORCESHOWHIDDEN,
		(LPCTSTR)_TEXT("xml files (*.xml)|*.xml||"),NULL);
	if(dlg.DoModal()==IDOK){
        FilePathName=dlg.GetPathName();
		userfilepath = FilePathName;
	}
		
	if (FilePathName=="")
		return;

	file<> fdoc(FilePathName);
	xml_document<> doc;
	doc.parse<0>(fdoc.data());
	 //获取根节点
	xml_node<>* p_root = doc.first_node()->first_node()->next_sibling();
	//遍历每一个配置参数
	for(xml_node<>* node = p_root->first_node();node;node=node->next_sibling()){
		for(xml_node<>* m_node = node->first_node();m_node;m_node=m_node->next_sibling())
		        ConfigEdit((CString)node->name(),(CString)m_node->name(),(CString)m_node->value());
	}
	
}


void CMainFrame::ConfigEdit(CString protocol,CString para_name,CString para_value){
	CTabParent* p_tabParent = (CTabParent*)(m_mainSplitter.GetPane(0,0));//获取父页面指针
	CTabProtocolConfig *p_tabProtocolConfig = &(p_tabParent->m_tabProtocolConfig);
	CTabCarrier *p_tabcarrier = &(p_tabParent->m_tabCarrier);
	CTabInstrument *p_tabInstrument = &(p_tabParent->m_tabInstrument);
	if (protocol == "11a"){
		if (para_name == "DataRate"){
			switch(atoi(para_value)){
			case 6:
				m_pass_to_thread.m_configAIndex->EZOA_Encoding = BPSK_1_2;//物理层参数
				m_pass_to_thread.m_configIndex->EZOA_Encoding = BPSK_1_2;
				p_tabProtocolConfig->pPropT4->SetValue("6 Mbps");//界面更新
				p_tabProtocolConfig->pPropT5->SetValue("BPSK");
				p_tabProtocolConfig->pPropT7->SetValue("1/2");
				break;
			case 9:
				m_pass_to_thread.m_configAIndex->EZOA_Encoding = BPSK_3_4;
				m_pass_to_thread.m_configIndex->EZOA_Encoding = BPSK_3_4;
				p_tabProtocolConfig->pPropT4->SetValue("9 Mbps");
				p_tabProtocolConfig->pPropT5->SetValue("BPSK");
				p_tabProtocolConfig->pPropT7->SetValue("3/4");
				break;
			case 12:
				m_pass_to_thread.m_configAIndex->EZOA_Encoding = QPSK_1_2;
				m_pass_to_thread.m_configIndex->EZOA_Encoding = QPSK_1_2;
				p_tabProtocolConfig->pPropT4->SetValue("12 Mbps");
				p_tabProtocolConfig->pPropT5->SetValue("QPSK");
				p_tabProtocolConfig->pPropT7->SetValue("1/2");
				break;
			case 18:
				m_pass_to_thread.m_configAIndex->EZOA_Encoding = QPSK_3_4;
				m_pass_to_thread.m_configIndex->EZOA_Encoding = QPSK_3_4;
				p_tabProtocolConfig->pPropT4->SetValue("18 Mbps");
				p_tabProtocolConfig->pPropT5->SetValue("QPSK");
				p_tabProtocolConfig->pPropT7->SetValue("3/4");
				break;
			case 24:
				m_pass_to_thread.m_configAIndex->EZOA_Encoding = QAM16_1_2;
				m_pass_to_thread.m_configIndex->EZOA_Encoding = QAM16_1_2;
				p_tabProtocolConfig->pPropT4->SetValue("24 Mbps");
				p_tabProtocolConfig->pPropT5->SetValue("16-QAM");
				p_tabProtocolConfig->pPropT7->SetValue("1/2");
				break;
			case 36:
				m_pass_to_thread.m_configAIndex->EZOA_Encoding = QAM16_3_4;
				m_pass_to_thread.m_configIndex->EZOA_Encoding = QAM16_3_4;
				p_tabProtocolConfig->pPropT4->SetValue("36 Mbps");
				p_tabProtocolConfig->pPropT5->SetValue("16-QAM");
				p_tabProtocolConfig->pPropT7->SetValue("3/4");
				break;
			case 48:
				m_pass_to_thread.m_configAIndex->EZOA_Encoding = QAM64_2_3;
				m_pass_to_thread.m_configIndex->EZOA_Encoding = QAM64_2_3;
				p_tabProtocolConfig->pPropT4->SetValue("48 Mbps");
				p_tabProtocolConfig->pPropT5->SetValue("64-QAM");
				p_tabProtocolConfig->pPropT7->SetValue("2/3");
				break;
			case 54:
				m_pass_to_thread.m_configAIndex->EZOA_Encoding = QAM64_3_4;
				m_pass_to_thread.m_configIndex->EZOA_Encoding = QAM64_3_4;
				p_tabProtocolConfig->pPropT4->SetValue("64 Mbps");
				p_tabProtocolConfig->pPropT5->SetValue("64-QAM");
				p_tabProtocolConfig->pPropT7->SetValue("3/4");
				break;
			}
		}
		if(para_name == "source_mode"){
			switch(atoi(para_value)){
			case 0:
				m_pass_to_thread.m_configAIndex->source_mode = 0;
				p_tabProtocolConfig->p_data_source->SetValue("PN9");
				break;
			case 1:
				m_pass_to_thread.m_configAIndex->source_mode = 1;
				p_tabProtocolConfig->p_data_source->SetValue("PN15");
				break;
			case 2:
				m_pass_to_thread.m_configAIndex->source_mode = 2;
				p_tabProtocolConfig->p_data_source->SetValue("ALL0");
				break;
			case 3:
				m_pass_to_thread.m_configAIndex->source_mode = 3;
				p_tabProtocolConfig->p_data_source->SetValue("从文件读取");
				break;
			}
		}
		if(para_name=="filepath"){    
			char * temp_filename;
			temp_filename = new char[para_value.GetLength() + 1];
			strcpy(temp_filename,para_value.GetBuffer());
			m_pass_to_thread.m_configAIndex->filepath = temp_filename;
			p_tabProtocolConfig->p_data_filepath->SetValue(para_value);
			if (m_pass_to_thread.m_configAIndex->source_mode==3)
			  p_tabProtocolConfig->p_data_filepath->Show(TRUE);
		}
		if(para_name=="source_length"){
			int len = atoi(para_value);
			m_pass_to_thread.m_configAIndex->source_length = len;
			p_tabProtocolConfig->p_date_max_len->SetValue(para_value);
		}
		if(para_name=="add_channel"){
			m_pass_to_thread.m_configAIndex->add_channel = (para_value=="false" ? false:true);
			p_tabProtocolConfig->pPropT16->SetValue(para_value=="false"? "off":"on");
		}
		if(para_name=="NumofTaps"){

			m_pass_to_thread.m_configAIndex->NumOfTaps = atof(para_value);
			p_tabProtocolConfig->pPropT17->SetValue(para_value);
		}
		/*if(para_name=="MAX_Delay_Sample"){

		m_pass_to_thread.m_configAIndex->MAX_Delay_Sample = atof(para_value);
		p_tabProtocolConfig->pPropT18->SetValue(para_value);
		}*/
		if(para_name=="IQ_gain"){

			m_pass_to_thread.m_configAIndex->IQ_gain = atof(para_value);
			p_tabcarrier->p_IQ_gain_balanceA->SetValue(para_value);
		}
		if(para_name=="quan_angle_adjust"){

			m_pass_to_thread.m_configAIndex->quan_angle_adjust = atof(para_value);
			p_tabcarrier->p_quadrature_angle_adjustmentA->SetValue(para_value);
		}
		if(para_name=="mobilespeed"){

			m_pass_to_thread.m_configAIndex->mobilespeed = atof(para_value);
			p_tabProtocolConfig->pPropT19->SetValue(para_value);
		}
		if(para_name=="num_of_frame"){

			m_pass_to_thread.m_configAIndex->num_of_frame = atoi(para_value);
			p_tabProtocolConfig->pPropT2->SetValue(para_value);
		}
		if(para_name=="num_of_zeros"){

			m_pass_to_thread.m_configAIndex->num_of_zeros = atoi(para_value);
			double num = m_pass_to_thread.m_configAIndex->num_of_zeros/20;
			char str[10];
			sprintf(str,"%.4f",num);
			p_tabProtocolConfig->pPropT3a->SetValue(str);
		}
		if(para_name=="scramble_state_initial"){

			m_pass_to_thread.m_configAIndex->scramble_state_initial = atoi(para_value);
			p_tabProtocolConfig->pPropT017->SetValue(para_value);
		}
		if(para_name=="scrambler_state_OFDM"){
			m_pass_to_thread.m_configAIndex->scrambler_state_OFDM = (para_value=="false" ? false:true);
			p_tabProtocolConfig->pPropT9->SetValue(para_value=="false"? "off":"on");
		}
		if(para_name=="Data_ratio"){

			m_pass_to_thread.m_configAIndex->oversample_ratio = atoi(para_value);
			p_tabcarrier->over_sample->SetValue(para_value);
		}
		if(para_name=="filtertype"){
			if (para_value=="lpfilter"){
				m_pass_to_thread.m_configAIndex->filter_para.filtertype=lpfilter;
				p_tabProtocolConfig->pPropT14->SetValue("理想低通滤波器");
				if(m_pass_to_thread.m_configAIndex->oversample_ratio >1){
					p_tabProtocolConfig->lp_filter_wn->Show(TRUE);
					p_tabProtocolConfig->lp_filter_len->Show(TRUE);
					p_tabProtocolConfig->gauss_filter_BT->Show(FALSE);
					p_tabProtocolConfig->gauss_filter_len->Show(FALSE);
					p_tabProtocolConfig->cosine_filter_alpha->Show(FALSE);
					p_tabProtocolConfig->cosine_filter_len->Show(FALSE);
					p_tabProtocolConfig->filter_user->Show(FALSE);
				}
			}
			if (para_value =="gaussfilter")
			{
				m_pass_to_thread.m_configAIndex->filter_para.filtertype = gaussfilter;
				p_tabProtocolConfig->pPropT14->SetValue("高斯滤波器");
				if(m_pass_to_thread.m_configAIndex->oversample_ratio >1){
					p_tabProtocolConfig->lp_filter_wn->Show(FALSE);
					p_tabProtocolConfig->lp_filter_len->Show(FALSE);
					p_tabProtocolConfig->gauss_filter_BT->Show(TRUE);
					p_tabProtocolConfig->gauss_filter_len->Show(TRUE);
					p_tabProtocolConfig->cosine_filter_alpha->Show(FALSE);
					p_tabProtocolConfig->cosine_filter_len->Show(FALSE);
					p_tabProtocolConfig->filter_user->Show(FALSE);
				}
			}
			if (para_value =="cosfilter")
			{
				m_pass_to_thread.m_configAIndex->filter_para.filtertype = cosfilter;
				p_tabProtocolConfig->pPropT14->SetValue("根升余弦滤波器");
				if(m_pass_to_thread.m_configAIndex->oversample_ratio >1){
					p_tabProtocolConfig->lp_filter_wn->Show(FALSE);
					p_tabProtocolConfig->lp_filter_len->Show(FALSE);
					p_tabProtocolConfig->gauss_filter_BT->Show(FALSE);
					p_tabProtocolConfig->gauss_filter_len->Show(FALSE);
					p_tabProtocolConfig->cosine_filter_alpha->Show(TRUE);
					p_tabProtocolConfig->cosine_filter_len->Show(TRUE);
					p_tabProtocolConfig->filter_user->Show(FALSE);
				}
			}
			if (para_value=="userdefined"){
				m_pass_to_thread.m_configAIndex->filter_para.filtertype = userdefined;
				p_tabProtocolConfig->pPropT14->SetValue("用户自定义");
				if(m_pass_to_thread.m_configAIndex->oversample_ratio >1){
					p_tabProtocolConfig->lp_filter_wn->Show(FALSE);
					p_tabProtocolConfig->lp_filter_len->Show(FALSE);
					p_tabProtocolConfig->gauss_filter_BT->Show(FALSE);
					p_tabProtocolConfig->gauss_filter_len->Show(FALSE);
					p_tabProtocolConfig->cosine_filter_alpha->Show(FALSE);
					p_tabProtocolConfig->cosine_filter_len->Show(FALSE);
					p_tabProtocolConfig->filter_user->Show(TRUE);
				}
			}
		}
		if(para_name=="lppara_wn"){
			m_pass_to_thread.m_configAIndex->filter_para.lppara.wn = atof(para_value);
			p_tabProtocolConfig->lp_filter_wn->SetValue(para_value);

		}
		if(para_name=="lppara_len"){
			m_pass_to_thread.m_configAIndex->filter_para.lppara.length =atoi(para_value);
			p_tabProtocolConfig->lp_filter_len->SetValue(para_value);
		}
		if(para_name=="gausspara_BT"){
			m_pass_to_thread.m_configAIndex->filter_para.gausspara.BT = atof(para_value);
			p_tabProtocolConfig->gauss_filter_BT->SetValue(para_value);
		}
		if(para_name=="gausspara_len"){
			m_pass_to_thread.m_configAIndex->filter_para.gausspara.length = atoi(para_value);
			p_tabProtocolConfig->gauss_filter_len->SetValue(para_value);
		}
		if(para_name=="cosinepara_alpha"){
			m_pass_to_thread.m_configAIndex->filter_para.cosinepara.alpha = atof(para_value);
			p_tabProtocolConfig->cosine_filter_alpha->SetValue(para_value);
		}
		if(para_name=="cosinepara_len"){
			m_pass_to_thread.m_configAIndex->filter_para.cosinepara.length = atoi(para_value);
			p_tabProtocolConfig->cosine_filter_len->SetValue(para_value);
		}
		if(para_name=="filterpath"){
			m_pass_to_thread.m_configAIndex->filter_para.filepath = para_value;
			p_tabProtocolConfig->filter_user->SetValue(para_value);
		}
	}
	if (protocol == "11b"){
		if (para_name == "EZOB_Encoding"){
			switch(atoi(para_value)){
			case 8:
				m_pass_to_thread.m_configBIndex->EZOB_Encoding = DBPSK_1M;//物理层参数
				m_pass_to_thread.m_configBIndex->data_rate = _1Mbps;
				//m_pass_to_thread.m_configIndex->EZOA_Encoding = BPSK_1_2;
				p_tabProtocolConfig->pPropT67->SetValue("1 Mbps");//界面更新
				p_tabProtocolConfig->pPropT68->SetValue("DBPSK");
				p_tabProtocolConfig->pPropT68->Enable(FALSE);
				//p_tabProtocolConfig->pPropT7->SetValue("1/2");
				break;
			case 9:
				m_pass_to_thread.m_configBIndex->EZOB_Encoding = DQPSK_2M;
				m_pass_to_thread.m_configBIndex->data_rate = _2Mbps;
				//m_pass_to_thread.m_configIndex->EZOA_Encoding = BPSK_3_4;
				p_tabProtocolConfig->pPropT67->SetValue("2 Mbps");
				p_tabProtocolConfig->pPropT68->SetValue("DQPSK");
				p_tabProtocolConfig->pPropT68->Enable(FALSE);
				//p_tabProtocolConfig->pPropT7->SetValue("3/4");
				break;
			case 10:
				m_pass_to_thread.m_configBIndex->EZOB_Encoding = CCK_5_5M;
				m_pass_to_thread.m_configBIndex->data_rate = _55Mbps;
				//m_pass_to_thread.m_configIndex->EZOA_Encoding = QPSK_1_2;
				p_tabProtocolConfig->pPropT67->SetValue("5.5 Mbps");
				p_tabProtocolConfig->pPropT68->SetValue("CCK");
				p_tabProtocolConfig->pPropT68->Enable(TRUE);
				//p_tabProtocolConfig->pPropT7->SetValue("1/2");
				break;
			case 11:
				m_pass_to_thread.m_configBIndex->EZOB_Encoding = CCK_11M;
				//m_pass_to_thread.m_configIndex->EZOA_Encoding = QPSK_3_4;
				m_pass_to_thread.m_configBIndex->data_rate = _11Mbps;
				p_tabProtocolConfig->pPropT67->SetValue("11 Mbps");
				p_tabProtocolConfig->pPropT68->SetValue("CCK");
				p_tabProtocolConfig->pPropT68->Enable(TRUE);
				//p_tabProtocolConfig->pPropT7->SetValue("3/4");
				break;
			case 12:
				m_pass_to_thread.m_configBIndex->EZOB_Encoding = PBCC_5_5M;
				m_pass_to_thread.m_configBIndex->data_rate = _55Mbps;
				//m_pass_to_thread.m_configIndex->EZOA_Encoding = QAM16_1_2;
				p_tabProtocolConfig->pPropT67->SetValue("5.5 Mbps");
				p_tabProtocolConfig->pPropT68->SetValue("PBCC");
				p_tabProtocolConfig->pPropT68->Enable(TRUE);
				//p_tabProtocolConfig->pPropT7->SetValue("1/2");
				break;
			case 13:
				m_pass_to_thread.m_configBIndex->EZOB_Encoding = PBCC_11M;
				m_pass_to_thread.m_configBIndex->data_rate = _11Mbps;
				//m_pass_to_thread.m_configIndex->EZOA_Encoding = QAM16_3_4;
				p_tabProtocolConfig->pPropT67->SetValue("11 Mbps");
				p_tabProtocolConfig->pPropT68->SetValue("PBCC");
				p_tabProtocolConfig->pPropT68->Enable(TRUE);
				//p_tabProtocolConfig->pPropT7->SetValue("3/4");
				break;
			}
		}
		if(para_name == "source_mode"){
			switch(atoi(para_value)){
			case 0:
				m_pass_to_thread.m_configBIndex->source_mode = 0;
				p_tabProtocolConfig->p_data_source_b->SetValue("PN9");
				break;
			case 1:
				m_pass_to_thread.m_configBIndex->source_mode = 1;
				p_tabProtocolConfig->p_data_source_b->SetValue("PN15");
				break;
			case 2:
				m_pass_to_thread.m_configBIndex->source_mode = 2;
				p_tabProtocolConfig->p_data_source_b->SetValue("ALL0");
				break;
			case 3:
				m_pass_to_thread.m_configBIndex->source_mode = 3;
				p_tabProtocolConfig->p_data_source_b->SetValue("从文件读取");
				break;
			}
		}
		if(para_name=="filepath"){    
			char * temp_filename;
			temp_filename = new char[para_value.GetLength() + 1];
			strcpy(temp_filename,para_value.GetBuffer());
			m_pass_to_thread.m_configBIndex->filepath = temp_filename;
			p_tabProtocolConfig->p_data_filepath_b->SetValue(para_value);
			if (m_pass_to_thread.m_configBIndex->source_mode==3)
			  p_tabProtocolConfig->p_data_filepath_b->Show(TRUE);
		}
		if(para_name=="source_length"){
			int len = atoi(para_value);
			m_pass_to_thread.m_configBIndex->source_length = len;
			p_tabProtocolConfig->pPropT72->SetValue(para_value);
		}
		if(para_name=="add_channel"){
			m_pass_to_thread.m_configBIndex->add_channel = (para_value=="false" ? false:true);
			p_tabProtocolConfig->pPropT16_b->SetValue(para_value=="false"? "off":"on");
		}
		if(para_name=="NumofTaps"){

			m_pass_to_thread.m_configBIndex->NumOfTaps = atof(para_value);
			p_tabProtocolConfig->pPropT17_b->SetValue(para_value);
		}
		/*if(para_name=="MAX_Delay_Sample"){

		m_pass_to_thread.m_configAIndex->MAX_Delay_Sample = atof(para_value);
		p_tabProtocolConfig->pPropT18->SetValue(para_value);
		}*/
		if(para_name=="IQ_gain"){

			m_pass_to_thread.m_configBIndex->IQ_gain = atof(para_value);
			p_tabcarrier->p_IQ_gain_balanceA->SetValue(para_value);
		}
		if(para_name=="quan_angle_adjust"){

			m_pass_to_thread.m_configBIndex->quan_angle_adjust = atof(para_value);
			p_tabcarrier->p_quadrature_angle_adjustmentA->SetValue(para_value);
		}
		if(para_name=="mobilespeed"){

			m_pass_to_thread.m_configBIndex->mobilespeed = atof(para_value);
			p_tabProtocolConfig->pPropT19_b->SetValue(para_value);
		}
		if(para_name=="num_of_frame"){

			m_pass_to_thread.m_configBIndex->num_of_frame = atoi(para_value);
			p_tabProtocolConfig->pPropT62->SetValue(para_value);
		}
		if(para_name=="num_of_zeros"){

			m_pass_to_thread.m_configBIndex->num_of_zeros = atoi(para_value);
			double num = m_pass_to_thread.m_configBIndex->num_of_zeros/20;
			char str[10];
			sprintf(str,"%.4f",num);
			p_tabProtocolConfig->pPropT63->SetValue(str);
		}
		if(para_name=="scrambler_state"){
			switch(atoi(para_value)){
			case 0:
				m_pass_to_thread.m_configBIndex->scrambler_state = ON;
				p_tabProtocolConfig->pPropT69->SetValue("On");
				break;
			case 1:
				m_pass_to_thread.m_configBIndex->scrambler_state = OFF;
				p_tabProtocolConfig->pPropT69->SetValue("Off");
				break;
			case 2:
				m_pass_to_thread.m_configBIndex->scrambler_state = Preamble_only;
				p_tabProtocolConfig->pPropT69->SetValue("报头仅有");
				break;
			}
		}
		if(para_name=="preamble_type"){
			switch(atoi(para_value)){
			case 0:
				m_pass_to_thread.m_configBIndex->preamble_type = shortPreamble;
				p_tabProtocolConfig->pPropT70->SetValue("短");
				break;
			case 1:
				m_pass_to_thread.m_configBIndex->preamble_type = longPreamble;
				p_tabProtocolConfig->pPropT70->SetValue("长");
				break;
			case 2:
				m_pass_to_thread.m_configBIndex->preamble_type = OFDMPreamble;
				p_tabProtocolConfig->pPropT70->SetValue("OFDM");
				break;
			}
		}
		if(para_name=="Data_ratio"){

			m_pass_to_thread.m_configBIndex->oversample_ratio = atoi(para_value);
			p_tabcarrier->over_sample->SetValue(para_value);
		}
		if(para_name=="filtertype"){
			if (para_value=="lpfilter"){
				m_pass_to_thread.m_configBIndex->filter_para.filtertype=lpfilter;
				p_tabProtocolConfig->fitertype->SetValue("理想低通滤波器");
				if(m_pass_to_thread.m_configBIndex->oversample_ratio >1){
					p_tabProtocolConfig->lp_filter_wn_b->Show(TRUE);
					p_tabProtocolConfig->lp_filter_len_b->Show(TRUE);
					p_tabProtocolConfig->gauss_filter_BT_b->Show(FALSE);
					p_tabProtocolConfig->gauss_filter_len_b->Show(FALSE);
					p_tabProtocolConfig->cosine_filter_alpha_b->Show(FALSE);
					p_tabProtocolConfig->cosine_filter_len_b->Show(FALSE);
					p_tabProtocolConfig->filter_user_b->Show(FALSE);
				}
			}
			if (para_value =="gaussfilter")
			{
				m_pass_to_thread.m_configBIndex->filter_para.filtertype = gaussfilter;
				p_tabProtocolConfig->fitertype->SetValue("高斯滤波器");
				if(m_pass_to_thread.m_configBIndex->oversample_ratio >1){
					p_tabProtocolConfig->lp_filter_wn_b->Show(FALSE);
					p_tabProtocolConfig->lp_filter_len_b->Show(FALSE);
					p_tabProtocolConfig->gauss_filter_BT_b->Show(TRUE);
					p_tabProtocolConfig->gauss_filter_len_b->Show(TRUE);
					p_tabProtocolConfig->cosine_filter_alpha_b->Show(FALSE);
					p_tabProtocolConfig->cosine_filter_len_b->Show(FALSE);
					p_tabProtocolConfig->filter_user_b->Show(FALSE);
				}
			}
			if (para_value =="cosfilter")
			{
				m_pass_to_thread.m_configBIndex->filter_para.filtertype = cosfilter;
				p_tabProtocolConfig->fitertype->SetValue("根升余弦滤波器");
				if(m_pass_to_thread.m_configBIndex->oversample_ratio >1){
					p_tabProtocolConfig->lp_filter_wn_b->Show(FALSE);
					p_tabProtocolConfig->lp_filter_len_b->Show(FALSE);
					p_tabProtocolConfig->gauss_filter_BT_b->Show(FALSE);
					p_tabProtocolConfig->gauss_filter_len_b->Show(FALSE);
					p_tabProtocolConfig->cosine_filter_alpha_b->Show(TRUE);
					p_tabProtocolConfig->cosine_filter_len_b->Show(TRUE);
					p_tabProtocolConfig->filter_user_b->Show(FALSE);
				}
			}
			if (para_value=="userdefined"){
				m_pass_to_thread.m_configBIndex->filter_para.filtertype = userdefined;
				p_tabProtocolConfig->fitertype->SetValue("用户自定义");
				if(m_pass_to_thread.m_configBIndex->oversample_ratio >1){
					p_tabProtocolConfig->lp_filter_wn_b->Show(FALSE);
					p_tabProtocolConfig->lp_filter_len_b->Show(FALSE);
					p_tabProtocolConfig->gauss_filter_BT_b->Show(FALSE);
					p_tabProtocolConfig->gauss_filter_len_b->Show(FALSE);
					p_tabProtocolConfig->cosine_filter_alpha_b->Show(FALSE);
					p_tabProtocolConfig->cosine_filter_len_b->Show(FALSE);
					p_tabProtocolConfig->filter_user_b->Show(TRUE);
				}
			}
		}
		if(para_name=="lppara_wn"){
			m_pass_to_thread.m_configBIndex->filter_para.lppara.wn = atof(para_value);
			p_tabProtocolConfig->lp_filter_wn_b->SetValue(para_value);

		}
		if(para_name=="lppara_len"){
			m_pass_to_thread.m_configBIndex->filter_para.lppara.length =atoi(para_value);
			p_tabProtocolConfig->lp_filter_len_b->SetValue(para_value);
		}
		if(para_name=="gausspara_BT"){
			m_pass_to_thread.m_configBIndex->filter_para.gausspara.BT = atof(para_value);
			p_tabProtocolConfig->gauss_filter_BT_b->SetValue(para_value);
		}
		if(para_name=="gausspara_len"){
			m_pass_to_thread.m_configBIndex->filter_para.gausspara.length = atoi(para_value);
			p_tabProtocolConfig->gauss_filter_len_b->SetValue(para_value);
		}
		if(para_name=="cosinepara_alpha"){
			m_pass_to_thread.m_configBIndex->filter_para.cosinepara.alpha = atof(para_value);
			p_tabProtocolConfig->cosine_filter_alpha_b->SetValue(para_value);
		}
		if(para_name=="cosinepara_len"){
			m_pass_to_thread.m_configBIndex->filter_para.cosinepara.length = atoi(para_value);
			p_tabProtocolConfig->cosine_filter_len_b->SetValue(para_value);
		}
		if(para_name=="filterpath"){
			m_pass_to_thread.m_configBIndex->filter_para.filepath = para_value;
			p_tabProtocolConfig->filter_user_b->SetValue(para_value);
		}
	}
	if (protocol == "11g"){
		if (para_name == "EZOG_Encoding"){
			switch(atoi(para_value)){
			case 0:
				m_pass_to_thread.m_configGIndex->EZOG_Encoding = BPSK_1_2;//物理层参数
				m_pass_to_thread.m_configGIndex->data_rate = _6Mbps;
				//m_pass_to_thread.m_configIndex->EZOA_Encoding = BPSK_1_2;
				p_tabProtocolConfig->pPropT81->SetValue("6 Mbps(OFDM)");//界面更新
				p_tabProtocolConfig->pPropT95->SetValue((COleVariant)_T("BPSK"));
				p_tabProtocolConfig->pPropT90->SetValue((COleVariant)_T("1/2"));
				//p_tabProtocolConfig->pPropT7->SetValue("1/2");
				p_tabProtocolConfig->pPropT89->Show(TRUE);//编码方式
				p_tabProtocolConfig->pPropT90->Show(TRUE);//码率
				p_tabProtocolConfig->pPropT91->Show(TRUE);//交织
				p_tabProtocolConfig->pPropT92->Show(TRUE);//OFDM扰码器
				p_tabProtocolConfig->pPropT93->Show(TRUE);//OFDM扰码器初始值
				p_tabProtocolConfig->pPropT96->Show(TRUE);//OFDM子载波数
				p_tabProtocolConfig->pPropT83->Show(FALSE);//DSSS Scrambler
				//pPropT94->AddOption(_T("OFDM"));
				p_tabProtocolConfig->pPropT94->SetValue((COleVariant)_T("OFDM"));
				p_tabProtocolConfig->pPropT94->Enable(TRUE);
				p_tabProtocolConfig->pPropT17_g->Enable(TRUE);
				break;
			case 1:
				m_pass_to_thread.m_configGIndex->EZOG_Encoding = BPSK_3_4;//物理层参数
				m_pass_to_thread.m_configGIndex->data_rate = _9Mbps;
				//m_pass_to_thread.m_configIndex->EZOA_Encoding = BPSK_1_2;
				p_tabProtocolConfig->pPropT81->SetValue("9 Mbps(OFDM)");//界面更新
				p_tabProtocolConfig->pPropT95->SetValue((COleVariant)_T("BPSK"));
				p_tabProtocolConfig->pPropT90->SetValue((COleVariant)_T("3/4"));
				//p_tabProtocolConfig->pPropT7->SetValue("1/2");
				p_tabProtocolConfig->pPropT89->Show(TRUE);//编码方式
				p_tabProtocolConfig->pPropT90->Show(TRUE);//码率
				p_tabProtocolConfig->pPropT91->Show(TRUE);//交织
				p_tabProtocolConfig->pPropT92->Show(TRUE);//OFDM扰码器
				p_tabProtocolConfig->pPropT93->Show(TRUE);//OFDM扰码器初始值
				p_tabProtocolConfig->pPropT96->Show(TRUE);//OFDM子载波数
				p_tabProtocolConfig->pPropT83->Show(FALSE);//DSSS Scrambler
				//pPropT94->AddOption(_T("OFDM"));
				p_tabProtocolConfig->pPropT94->SetValue((COleVariant)_T("OFDM"));
				p_tabProtocolConfig->pPropT94->Enable(TRUE);
				p_tabProtocolConfig->pPropT17_g->Enable(TRUE);
				break;
			case 2:
				m_pass_to_thread.m_configGIndex->EZOG_Encoding = QPSK_1_2;//物理层参数
				m_pass_to_thread.m_configGIndex->data_rate = _12Mbps;
				//m_pass_to_thread.m_configIndex->EZOA_Encoding = BPSK_1_2;
				p_tabProtocolConfig->pPropT81->SetValue("12 Mbps(OFDM)");//界面更新
				p_tabProtocolConfig->pPropT95->SetValue((COleVariant)_T("QPSK"));
				p_tabProtocolConfig->pPropT90->SetValue((COleVariant)_T("1/2"));
				//p_tabProtocolConfig->pPropT7->SetValue("1/2");
				p_tabProtocolConfig->pPropT89->Show(TRUE);//编码方式
				p_tabProtocolConfig->pPropT90->Show(TRUE);//码率
				p_tabProtocolConfig->pPropT91->Show(TRUE);//交织
				p_tabProtocolConfig->pPropT92->Show(TRUE);//OFDM扰码器
				p_tabProtocolConfig->pPropT93->Show(TRUE);//OFDM扰码器初始值
				p_tabProtocolConfig->pPropT96->Show(TRUE);//OFDM子载波数
				p_tabProtocolConfig->pPropT83->Show(FALSE);//DSSS Scrambler
				//pPropT94->AddOption(_T("OFDM"));
				p_tabProtocolConfig->pPropT94->SetValue((COleVariant)_T("OFDM"));
				p_tabProtocolConfig->pPropT94->Enable(TRUE);
				p_tabProtocolConfig->pPropT17_g->Enable(TRUE);
				break;
			case 3:
				m_pass_to_thread.m_configGIndex->EZOG_Encoding = QPSK_3_4;//物理层参数
				m_pass_to_thread.m_configGIndex->data_rate = _18Mbps;
				//m_pass_to_thread.m_configIndex->EZOA_Encoding = BPSK_1_2;
				p_tabProtocolConfig->pPropT81->SetValue("18 Mbps(OFDM)");//界面更新
				p_tabProtocolConfig->pPropT95->SetValue((COleVariant)_T("QPSK"));
				p_tabProtocolConfig->pPropT90->SetValue((COleVariant)_T("3/4"));
				//p_tabProtocolConfig->pPropT7->SetValue("1/2");
				p_tabProtocolConfig->pPropT89->Show(TRUE);//编码方式
				p_tabProtocolConfig->pPropT90->Show(TRUE);//码率
				p_tabProtocolConfig->pPropT91->Show(TRUE);//交织
				p_tabProtocolConfig->pPropT92->Show(TRUE);//OFDM扰码器
				p_tabProtocolConfig->pPropT93->Show(TRUE);//OFDM扰码器初始值
				p_tabProtocolConfig->pPropT96->Show(TRUE);//OFDM子载波数
				p_tabProtocolConfig->pPropT83->Show(FALSE);//DSSS Scrambler
				//pPropT94->AddOption(_T("OFDM"));
				p_tabProtocolConfig->pPropT94->SetValue((COleVariant)_T("OFDM"));
				p_tabProtocolConfig->pPropT94->Enable(TRUE);
				p_tabProtocolConfig->pPropT17_g->Enable(TRUE);
				break;
			case 4:
				m_pass_to_thread.m_configGIndex->EZOG_Encoding = QAM16_1_2;//物理层参数
				m_pass_to_thread.m_configGIndex->data_rate = _24Mbps;
				//m_pass_to_thread.m_configIndex->EZOA_Encoding = BPSK_1_2;
				p_tabProtocolConfig->pPropT81->SetValue("24 Mbps(OFDM)");//界面更新
				p_tabProtocolConfig->pPropT95->SetValue((COleVariant)_T("16-QAM"));
				p_tabProtocolConfig->pPropT90->SetValue((COleVariant)_T("1/2"));
				//p_tabProtocolConfig->pPropT7->SetValue("1/2");
				p_tabProtocolConfig->pPropT89->Show(TRUE);//编码方式
				p_tabProtocolConfig->pPropT90->Show(TRUE);//码率
				p_tabProtocolConfig->pPropT91->Show(TRUE);//交织
				p_tabProtocolConfig->pPropT92->Show(TRUE);//OFDM扰码器
				p_tabProtocolConfig->pPropT93->Show(TRUE);//OFDM扰码器初始值
				p_tabProtocolConfig->pPropT96->Show(TRUE);//OFDM子载波数
				p_tabProtocolConfig->pPropT83->Show(FALSE);//DSSS Scrambler
				//pPropT94->AddOption(_T("OFDM"));
				p_tabProtocolConfig->pPropT94->SetValue((COleVariant)_T("OFDM"));
				p_tabProtocolConfig->pPropT94->Enable(TRUE);
				p_tabProtocolConfig->pPropT17_g->Enable(TRUE);
				break;
			case 5:
				m_pass_to_thread.m_configGIndex->EZOG_Encoding = QAM16_3_4;//物理层参数
				m_pass_to_thread.m_configGIndex->data_rate = _36Mbps;
				//m_pass_to_thread.m_configIndex->EZOA_Encoding = BPSK_1_2;
				p_tabProtocolConfig->pPropT81->SetValue("36 Mbps(OFDM)");//界面更新
				p_tabProtocolConfig->pPropT95->SetValue((COleVariant)_T("16-QAM"));
				p_tabProtocolConfig->pPropT90->SetValue((COleVariant)_T("3/4"));
				//p_tabProtocolConfig->pPropT7->SetValue("1/2");
				p_tabProtocolConfig->pPropT89->Show(TRUE);//编码方式
				p_tabProtocolConfig->pPropT90->Show(TRUE);//码率
				p_tabProtocolConfig->pPropT91->Show(TRUE);//交织
				p_tabProtocolConfig->pPropT92->Show(TRUE);//OFDM扰码器
				p_tabProtocolConfig->pPropT93->Show(TRUE);//OFDM扰码器初始值
				p_tabProtocolConfig->pPropT96->Show(TRUE);//OFDM子载波数
				p_tabProtocolConfig->pPropT83->Show(FALSE);//DSSS Scrambler
				//pPropT94->AddOption(_T("OFDM"));
				p_tabProtocolConfig->pPropT94->SetValue((COleVariant)_T("OFDM"));
				p_tabProtocolConfig->pPropT94->Enable(TRUE);
				p_tabProtocolConfig->pPropT17_g->Enable(TRUE);
				break;
			case 6:
				m_pass_to_thread.m_configGIndex->EZOG_Encoding = QAM64_2_3;//物理层参数
				m_pass_to_thread.m_configGIndex->data_rate = _48Mbps;
				//m_pass_to_thread.m_configIndex->EZOA_Encoding = BPSK_1_2;
				p_tabProtocolConfig->pPropT81->SetValue("48 Mbps(OFDM)");//界面更新
				p_tabProtocolConfig->pPropT95->SetValue((COleVariant)_T("64-QAM"));
				p_tabProtocolConfig->pPropT90->SetValue((COleVariant)_T("2/3"));
				//p_tabProtocolConfig->pPropT7->SetValue("1/2");
				p_tabProtocolConfig->pPropT89->Show(TRUE);//编码方式
				p_tabProtocolConfig->pPropT90->Show(TRUE);//码率
				p_tabProtocolConfig->pPropT91->Show(TRUE);//交织
				p_tabProtocolConfig->pPropT92->Show(TRUE);//OFDM扰码器
				p_tabProtocolConfig->pPropT93->Show(TRUE);//OFDM扰码器初始值
				p_tabProtocolConfig->pPropT96->Show(TRUE);//OFDM子载波数
				p_tabProtocolConfig->pPropT83->Show(FALSE);//DSSS Scrambler
				//pPropT94->AddOption(_T("OFDM"));
				p_tabProtocolConfig->pPropT94->SetValue((COleVariant)_T("OFDM"));
				p_tabProtocolConfig->pPropT94->Enable(TRUE);
				p_tabProtocolConfig->pPropT17_g->Enable(TRUE);
				break;
			case 7:
				m_pass_to_thread.m_configGIndex->EZOG_Encoding = QAM64_3_4;//物理层参数
				m_pass_to_thread.m_configGIndex->data_rate = _54Mbps;
				//m_pass_to_thread.m_configIndex->EZOA_Encoding = BPSK_1_2;
				p_tabProtocolConfig->pPropT81->SetValue("54 Mbps(OFDM)");//界面更新
				p_tabProtocolConfig->pPropT95->SetValue((COleVariant)_T("64-QAM"));
				p_tabProtocolConfig->pPropT90->SetValue((COleVariant)_T("3/4"));
				//p_tabProtocolConfig->pPropT7->SetValue("1/2");
				p_tabProtocolConfig->pPropT89->Show(TRUE);//编码方式
				p_tabProtocolConfig->pPropT90->Show(TRUE);//码率
				p_tabProtocolConfig->pPropT91->Show(TRUE);//交织
				p_tabProtocolConfig->pPropT92->Show(TRUE);//OFDM扰码器
				p_tabProtocolConfig->pPropT93->Show(TRUE);//OFDM扰码器初始值
				p_tabProtocolConfig->pPropT96->Show(TRUE);//OFDM子载波数
				p_tabProtocolConfig->pPropT83->Show(FALSE);//DSSS Scrambler
				//pPropT94->AddOption(_T("OFDM"));
				p_tabProtocolConfig->pPropT94->SetValue((COleVariant)_T("OFDM"));
				p_tabProtocolConfig->pPropT94->Enable(TRUE);
				p_tabProtocolConfig->pPropT17_g->Enable(TRUE);
				break;
			case 8:
				m_pass_to_thread.m_configGIndex->EZOG_Encoding = DBPSK_1M;//物理层参数
				m_pass_to_thread.m_configGIndex->data_rate = _1Mbps;
				//m_pass_to_thread.m_configIndex->EZOA_Encoding = BPSK_1_2;
				p_tabProtocolConfig->pPropT81->SetValue("1 Mbps(DSSS)");//界面更新
				p_tabProtocolConfig->pPropT95->SetValue((COleVariant)_T("DBPSK"));
				//p_tabProtocolConfig->pPropT7->SetValue("1/2");
				p_tabProtocolConfig->pPropT89->Show(FALSE);//编码方式
				p_tabProtocolConfig->pPropT90->Show(FALSE);//码率
				p_tabProtocolConfig->pPropT91->Show(FALSE);//交织
				p_tabProtocolConfig->pPropT92->Show(FALSE);//OFDM扰码器
				p_tabProtocolConfig->pPropT93->Show(FALSE);//OFDM扰码器初始值
				p_tabProtocolConfig->pPropT96->Show(FALSE);//OFDM子载波数
				p_tabProtocolConfig->pPropT83->Show(TRUE);//DSSS Scrambler
				p_tabProtocolConfig->pPropT17_g->Enable(FALSE);
				p_tabProtocolConfig->pPropT17_g->SetValue("1");
				m_pass_to_thread.m_configGIndex->NumOfTaps = 1 ;
				break;
			case 9:
				m_pass_to_thread.m_configGIndex->EZOG_Encoding = DQPSK_2M;
				m_pass_to_thread.m_configGIndex->data_rate = _2Mbps;
				//m_pass_to_thread.m_configIndex->EZOA_Encoding = BPSK_3_4;
				p_tabProtocolConfig->pPropT81->SetValue("2 Mbps(DSSS)");
				p_tabProtocolConfig->pPropT95->SetValue((COleVariant)_T("DQPSK"));
				//p_tabProtocolConfig->pPropT7->SetValue("3/4");
				p_tabProtocolConfig->pPropT89->Show(FALSE);//编码方式
				p_tabProtocolConfig->pPropT90->Show(FALSE);//码率
				p_tabProtocolConfig->pPropT91->Show(FALSE);//交织
				p_tabProtocolConfig->pPropT92->Show(FALSE);//OFDM扰码器
				p_tabProtocolConfig->pPropT93->Show(FALSE);//OFDM扰码器初始值
				p_tabProtocolConfig->pPropT96->Show(FALSE);//OFDM子载波数
				p_tabProtocolConfig->pPropT83->Show(TRUE);//DSSS Scrambler
				p_tabProtocolConfig->pPropT17_g->Enable(FALSE);
				p_tabProtocolConfig->pPropT17_g->SetValue("1");
				m_pass_to_thread.m_configGIndex->NumOfTaps = 1 ;
				break;
			case 10:
				m_pass_to_thread.m_configGIndex->EZOG_Encoding = CCK_5_5M;
				m_pass_to_thread.m_configGIndex->data_rate = _55Mbps;
				//m_pass_to_thread.m_configIndex->EZOA_Encoding = QPSK_1_2;
				p_tabProtocolConfig->pPropT81->SetValue("5.5 Mbps(DSSS)");
				p_tabProtocolConfig->pPropT95->SetValue((COleVariant)_T("CCK"));
				//p_tabProtocolConfig->pPropT7->SetValue("1/2");
				p_tabProtocolConfig->pPropT89->Show(FALSE);//编码方式
				p_tabProtocolConfig->pPropT90->Show(FALSE);//码率
				p_tabProtocolConfig->pPropT91->Show(FALSE);//交织
				p_tabProtocolConfig->pPropT92->Show(FALSE);//OFDM扰码器
				p_tabProtocolConfig->pPropT93->Show(FALSE);//OFDM扰码器初始值
				p_tabProtocolConfig->pPropT96->Show(FALSE);//OFDM子载波数
				p_tabProtocolConfig->pPropT83->Show(TRUE);//DSSS Scrambler
				p_tabProtocolConfig->pPropT17_g->Enable(FALSE);
				p_tabProtocolConfig->pPropT17_g->SetValue("1");
				m_pass_to_thread.m_configGIndex->NumOfTaps = 1 ;
				break;
			case 11:
				m_pass_to_thread.m_configGIndex->EZOG_Encoding = CCK_11M;
				//m_pass_to_thread.m_configIndex->EZOA_Encoding = QPSK_3_4;
				m_pass_to_thread.m_configGIndex->data_rate = _11Mbps;
				p_tabProtocolConfig->pPropT81->SetValue("11 Mbps(DSSS)");
				p_tabProtocolConfig->pPropT95->SetValue((COleVariant)_T("CCK"));
				//p_tabProtocolConfig->pPropT7->SetValue("3/4");
				p_tabProtocolConfig->pPropT89->Show(FALSE);//编码方式
				p_tabProtocolConfig->pPropT90->Show(FALSE);//码率
				p_tabProtocolConfig->pPropT91->Show(FALSE);//交织
				p_tabProtocolConfig->pPropT92->Show(FALSE);//OFDM扰码器
				p_tabProtocolConfig->pPropT93->Show(FALSE);//OFDM扰码器初始值
				p_tabProtocolConfig->pPropT96->Show(FALSE);//OFDM子载波数
				p_tabProtocolConfig->pPropT83->Show(TRUE);//DSSS Scrambler
				p_tabProtocolConfig->pPropT17_g->Enable(FALSE);
				p_tabProtocolConfig->pPropT17_g->SetValue("1");
				m_pass_to_thread.m_configGIndex->NumOfTaps = 1 ;
				break;
			case 12:
				m_pass_to_thread.m_configGIndex->EZOG_Encoding = PBCC_5_5M;
				m_pass_to_thread.m_configGIndex->data_rate = _55Mbps;
				//m_pass_to_thread.m_configIndex->EZOA_Encoding = QAM16_1_2;
				p_tabProtocolConfig->pPropT81->SetValue("5.5 Mbps(DSSS)");
				p_tabProtocolConfig->pPropT95->SetValue((COleVariant)_T("PBCC"));
				//p_tabProtocolConfig->pPropT7->SetValue("1/2");
				p_tabProtocolConfig->pPropT89->Show(FALSE);//编码方式
				p_tabProtocolConfig->pPropT90->Show(FALSE);//码率
				p_tabProtocolConfig->pPropT91->Show(FALSE);//交织
				p_tabProtocolConfig->pPropT92->Show(FALSE);//OFDM扰码器
				p_tabProtocolConfig->pPropT93->Show(FALSE);//OFDM扰码器初始值
				p_tabProtocolConfig->pPropT96->Show(FALSE);//OFDM子载波数
				p_tabProtocolConfig->pPropT83->Show(TRUE);//DSSS Scrambler
				p_tabProtocolConfig->pPropT17_g->Enable(FALSE);
				p_tabProtocolConfig->pPropT17_g->SetValue("1");
				m_pass_to_thread.m_configGIndex->NumOfTaps = 1 ;
				break;
			case 13:
				m_pass_to_thread.m_configGIndex->EZOG_Encoding = PBCC_11M;
				m_pass_to_thread.m_configGIndex->data_rate = _11Mbps;
				//m_pass_to_thread.m_configIndex->EZOA_Encoding = QAM16_3_4;
				p_tabProtocolConfig->pPropT81->SetValue("11 Mbps(DSSS)");
				p_tabProtocolConfig->pPropT95->SetValue((COleVariant)_T("PBCC"));
				//p_tabProtocolConfig->pPropT7->SetValue("3/4");
				p_tabProtocolConfig->pPropT89->Show(FALSE);//编码方式
				p_tabProtocolConfig->pPropT90->Show(FALSE);//码率
				p_tabProtocolConfig->pPropT91->Show(FALSE);//交织
				p_tabProtocolConfig->pPropT92->Show(FALSE);//OFDM扰码器
				p_tabProtocolConfig->pPropT93->Show(FALSE);//OFDM扰码器初始值
				p_tabProtocolConfig->pPropT96->Show(FALSE);//OFDM子载波数
				p_tabProtocolConfig->pPropT83->Show(TRUE);//DSSS Scrambler
				p_tabProtocolConfig->pPropT17_g->Enable(FALSE);
				p_tabProtocolConfig->pPropT17_g->SetValue("1");
				m_pass_to_thread.m_configGIndex->NumOfTaps = 1 ;
				break;
			case 14:
				m_pass_to_thread.m_configGIndex->EZOG_Encoding = PBCC_22M;//物理层参数
				m_pass_to_thread.m_configGIndex->data_rate = _22Mbps;
				//m_pass_to_thread.m_configIndex->EZOA_Encoding = BPSK_1_2;
				p_tabProtocolConfig->pPropT81->SetValue("22 Mbps(DSSS)");//界面更新
				p_tabProtocolConfig->pPropT95->SetValue((COleVariant)_T("PBCC"));
				//p_tabProtocolConfig->pPropT7->SetValue("1/2");
				p_tabProtocolConfig->pPropT89->Show(FALSE);//编码方式
				p_tabProtocolConfig->pPropT90->Show(FALSE);//码率
				p_tabProtocolConfig->pPropT91->Show(FALSE);//交织
				p_tabProtocolConfig->pPropT92->Show(FALSE);//OFDM扰码器
				p_tabProtocolConfig->pPropT93->Show(FALSE);//OFDM扰码器初始值
				p_tabProtocolConfig->pPropT96->Show(FALSE);//OFDM子载波数
				p_tabProtocolConfig->pPropT83->Show(TRUE);//DSSS Scrambler
				p_tabProtocolConfig->pPropT17_g->Enable(FALSE);
				p_tabProtocolConfig->pPropT17_g->SetValue("1");
				m_pass_to_thread.m_configGIndex->NumOfTaps = 1 ;
				break;
			}
		}
		if(para_name == "source_mode"){
			switch(atoi(para_value)){
			case 0:
				m_pass_to_thread.m_configGIndex->source_mode = 0;
				p_tabProtocolConfig->p_data_source_g->SetValue("PN9");
				break;
			case 1:
				m_pass_to_thread.m_configGIndex->source_mode = 1;
				p_tabProtocolConfig->p_data_source_g->SetValue("PN15");
				break;
			case 2:
				m_pass_to_thread.m_configGIndex->source_mode = 2;
				p_tabProtocolConfig->p_data_source_g->SetValue("ALL0");
				break;
			case 3:
				m_pass_to_thread.m_configGIndex->source_mode = 3;
				p_tabProtocolConfig->p_data_source_g->SetValue("从文件读取");
				break;
			}
		}
		if(para_name=="filepath"){    
			char * temp_filename;
			temp_filename = new char[para_value.GetLength() + 1];
			strcpy(temp_filename,para_value.GetBuffer());
			m_pass_to_thread.m_configGIndex->filepath = temp_filename;
			p_tabProtocolConfig->p_data_filepath_g->SetValue(para_value);
			if (m_pass_to_thread.m_configGIndex->source_mode==3)
			  p_tabProtocolConfig->p_data_filepath_g->Show(TRUE);
		}
		if(para_name=="source_length"){
			int len = atoi(para_value);
			m_pass_to_thread.m_configGIndex->source_length = len;
			p_tabProtocolConfig->pPropT86->SetValue(para_value);
		}
		if(para_name=="add_channel"){
			m_pass_to_thread.m_configGIndex->add_channel = (para_value=="false" ? false:true);
			p_tabProtocolConfig->pPropT16_g->SetValue(para_value=="false"? "off":"on");
		}
		if(para_name=="NumofTaps"){

			m_pass_to_thread.m_configGIndex->NumOfTaps = atof(para_value);
			p_tabProtocolConfig->pPropT17_g->SetValue(para_value);
		}
		/*if(para_name=="MAX_Delay_Sample"){

		m_pass_to_thread.m_configAIndex->MAX_Delay_Sample = atof(para_value);
		p_tabProtocolConfig->pPropT18->SetValue(para_value);
		}*/
		if(para_name=="IQ_gain"){

			m_pass_to_thread.m_configGIndex->IQ_gain = atof(para_value);
			p_tabcarrier->p_IQ_gain_balanceA->SetValue(para_value);
		}
		if(para_name=="quan_angle_adjust"){

			m_pass_to_thread.m_configGIndex->quan_angle_adjust = atof(para_value);
			p_tabcarrier->p_quadrature_angle_adjustmentA->SetValue(para_value);
		}
		if(para_name=="mobilespeed"){

			m_pass_to_thread.m_configGIndex->mobilespeed = atof(para_value);
			p_tabProtocolConfig->pPropT19_g->SetValue(para_value);
		}
		if(para_name=="num_of_frame"){

			m_pass_to_thread.m_configGIndex->num_of_frame = atoi(para_value);
			p_tabProtocolConfig->pPropT76->SetValue(para_value);
		}
		if(para_name=="num_of_zeros"){

			m_pass_to_thread.m_configGIndex->num_of_zeros = atoi(para_value);
			double num = m_pass_to_thread.m_configGIndex->num_of_zeros/20;
			char str[10];
			sprintf(str,"%.4f",num);
			p_tabProtocolConfig->pPropT77->SetValue(str);
		}
		if(para_name=="scrambler_state"){
			switch(atoi(para_value)){
			case 0:
				m_pass_to_thread.m_configGIndex->scrambler_state = ON;
				p_tabProtocolConfig->pPropT83->SetValue("On");
				break;
			case 1:
				m_pass_to_thread.m_configGIndex->scrambler_state = OFF;
				p_tabProtocolConfig->pPropT83->SetValue("Off");
				break;
			case 2:
				m_pass_to_thread.m_configGIndex->scrambler_state = Preamble_only;
				p_tabProtocolConfig->pPropT83->SetValue("报头仅有");
				break;
			}
		}
		if(para_name=="preamble_type"){
			switch(atoi(para_value)){
			case 0:
				m_pass_to_thread.m_configGIndex->preamble_type = shortPreamble;
				p_tabProtocolConfig->pPropT94->SetValue("短");
				break;
			case 1:
				m_pass_to_thread.m_configGIndex->preamble_type = longPreamble;
				p_tabProtocolConfig->pPropT94->SetValue("长");
				break;
			case 2:
				m_pass_to_thread.m_configGIndex->preamble_type = OFDMPreamble;
				p_tabProtocolConfig->pPropT94->SetValue("OFDM");
				break;
			}
		}
		if(para_name=="scramble_state_initial"){

			m_pass_to_thread.m_configGIndex->scramble_state_initial = atoi(para_value);
			p_tabProtocolConfig->pPropT93->SetValue(para_value);
		}
		if(para_name=="scrambler_state_OFDM"){
			m_pass_to_thread.m_configGIndex->scrambler_state_OFDM = (para_value=="false" ? false:true);
			p_tabProtocolConfig->pPropT92->SetValue(para_value=="false"? "off":"on");
		}
		if(para_name=="Data_ratio"){

			m_pass_to_thread.m_configGIndex->oversample_ratio = atoi(para_value);
			p_tabcarrier->over_sample->SetValue(para_value);
		}
		if(para_name=="filtertype"){
			if (para_value=="lpfilter"){
				m_pass_to_thread.m_configGIndex->filter_para.filtertype=lpfilter;
				p_tabProtocolConfig->fitertype->SetValue("理想低通滤波器");
				if(m_pass_to_thread.m_configGIndex->oversample_ratio >1){
					p_tabProtocolConfig->lp_filter_wn_g->Show(TRUE);
					p_tabProtocolConfig->lp_filter_len_g->Show(TRUE);
					p_tabProtocolConfig->gauss_filter_BT_g->Show(FALSE);
					p_tabProtocolConfig->gauss_filter_len_g->Show(FALSE);
					p_tabProtocolConfig->cosine_filter_alpha_g->Show(FALSE);
					p_tabProtocolConfig->cosine_filter_len_g->Show(FALSE);
					p_tabProtocolConfig->filter_user_g->Show(FALSE);
				}
			}
			if (para_value =="gaussfilter")
			{
				m_pass_to_thread.m_configGIndex->filter_para.filtertype = gaussfilter;
				p_tabProtocolConfig->fitertype->SetValue("高斯滤波器");
				if(m_pass_to_thread.m_configGIndex->oversample_ratio >1){
					p_tabProtocolConfig->lp_filter_wn_g->Show(FALSE);
					p_tabProtocolConfig->lp_filter_len_g->Show(FALSE);
					p_tabProtocolConfig->gauss_filter_BT_g->Show(TRUE);
					p_tabProtocolConfig->gauss_filter_len_g->Show(TRUE);
					p_tabProtocolConfig->cosine_filter_alpha_g->Show(FALSE);
					p_tabProtocolConfig->cosine_filter_len_g->Show(FALSE);
					p_tabProtocolConfig->filter_user_g->Show(FALSE);
				}
			}
			if (para_value =="cosfilter")
			{
				m_pass_to_thread.m_configGIndex->filter_para.filtertype = cosfilter;
				p_tabProtocolConfig->fitertype->SetValue("根升余弦滤波器");
				if(m_pass_to_thread.m_configGIndex->oversample_ratio >1){
					p_tabProtocolConfig->lp_filter_wn_g->Show(FALSE);
					p_tabProtocolConfig->lp_filter_len_g->Show(FALSE);
					p_tabProtocolConfig->gauss_filter_BT_g->Show(FALSE);
					p_tabProtocolConfig->gauss_filter_len_g->Show(FALSE);
					p_tabProtocolConfig->cosine_filter_alpha_g->Show(TRUE);
					p_tabProtocolConfig->cosine_filter_len_g->Show(TRUE);
					p_tabProtocolConfig->filter_user_g->Show(FALSE);
				}
			}
			if (para_value=="userdefined"){
				m_pass_to_thread.m_configGIndex->filter_para.filtertype = userdefined;
				p_tabProtocolConfig->fitertype->SetValue("用户自定义");
				if(m_pass_to_thread.m_configGIndex->oversample_ratio >1){
					p_tabProtocolConfig->lp_filter_wn_g->Show(FALSE);
					p_tabProtocolConfig->lp_filter_len_g->Show(FALSE);
					p_tabProtocolConfig->gauss_filter_BT_g->Show(FALSE);
					p_tabProtocolConfig->gauss_filter_len_g->Show(FALSE);
					p_tabProtocolConfig->cosine_filter_alpha_g->Show(FALSE);
					p_tabProtocolConfig->cosine_filter_len_g->Show(FALSE);
					p_tabProtocolConfig->filter_user_g->Show(TRUE);
				}
			}
		}
		if(para_name=="lppara_wn"){
			m_pass_to_thread.m_configGIndex->filter_para.lppara.wn = atof(para_value);
			p_tabProtocolConfig->lp_filter_wn_g->SetValue(para_value);

		}
		if(para_name=="lppara_len"){
			m_pass_to_thread.m_configGIndex->filter_para.lppara.length =atoi(para_value);
			p_tabProtocolConfig->lp_filter_len_g->SetValue(para_value);
		}
		if(para_name=="gausspara_BT"){
			m_pass_to_thread.m_configGIndex->filter_para.gausspara.BT = atof(para_value);
			p_tabProtocolConfig->gauss_filter_BT_g->SetValue(para_value);
		}
		if(para_name=="gausspara_len"){
			m_pass_to_thread.m_configGIndex->filter_para.gausspara.length = atoi(para_value);
			p_tabProtocolConfig->gauss_filter_len_g->SetValue(para_value);
		}
		if(para_name=="cosinepara_alpha"){
			m_pass_to_thread.m_configGIndex->filter_para.cosinepara.alpha = atof(para_value);
			p_tabProtocolConfig->cosine_filter_alpha_g->SetValue(para_value);
		}
		if(para_name=="cosinepara_len"){
			m_pass_to_thread.m_configGIndex->filter_para.cosinepara.length = atoi(para_value);
			p_tabProtocolConfig->cosine_filter_len_g->SetValue(para_value);
		}
		if(para_name=="filterpath"){
			m_pass_to_thread.m_configGIndex->filter_para.filepath = para_value;
			p_tabProtocolConfig->filter_user_g->SetValue(para_value);
		}
	}
	if (protocol == "11n"){

	}
	if(protocol =="Hardware"){
		if(para_name=="RF"){
			m_pass_to_thread.m_confighard->RF_state = para_value;
			if(para_value=="On" || para_value=="ON")
				p_tabInstrument->p_RF_output->SetValue("ON");
			else
				p_tabInstrument->p_RF_output->SetValue("OFF");
		}
		if(para_name=="carrier_freqz"){
			m_pass_to_thread.m_confighard->freq = para_value;
			p_tabInstrument->p_frequency->SetValue(para_value);
		}
		if(para_name=="power"){
			m_pass_to_thread.m_confighard->power = para_value;
			p_tabInstrument->p_amplitude->SetValue(para_value);
		}
		
	}
}

//写入 xml 
void CMainFrame::Write(CString filepath){
	if (m_configIndex->ProtocolModel==OneA)
	{
	using namespace rapidxml;//不能省略
	SaveConfigA();
	using namespace rapidxml;  
	xml_document<> doc;
	//根节点
	xml_node<>* rot = doc.allocate_node(node_pi,doc.allocate_string("version=\"1.0\" encoding=\"utf-8\" standalone=\"yes\""));
	doc.append_node(rot);
    //Application
	xml_node<>* Application = doc.allocate_node(node_element,"Application",NULL);
	Application->append_attribute(doc.allocate_attribute("Name","CETC41 Signal Studio for WLAN "));
	Application->append_attribute(doc.allocate_attribute("Version","1.0"));
	doc.append_node(Application);
	//Function
	xml_node<>* Function = doc.allocate_node(node_element,"Function","IEEE 802.11a\\b\\g\\n M*N MIMO");
	Application->append_node(Function);
	
	//待配置相关参数
	xml_node<>* parameter = doc.allocate_node(node_element,"Appparameters",NULL);
	Application->append_node(parameter);
	
	configA *m_configA = m_pass_to_thread.m_configAIndex;
	//按协议保存可配置参数
	xml_node<>* Protocol = doc.allocate_node(node_element,protocoltype[m_configA->ProtocolModel].data(),NULL);
	parameter->append_node(Protocol);

	auto map_it = para.cbegin();
	while(map_it != para.cend()){
		Protocol->append_node(doc.allocate_node(node_element,map_it->first.data(),map_it->second.data()));
		map_it++;
	}
	xml_node<>* Instrument = doc.allocate_node(node_element,"Hardware",NULL);
	parameter->append_node(Instrument);
	map_it = para_hard.cbegin();
	while(map_it != para_hard.cend()){
		Instrument->append_node(doc.allocate_node(node_element,map_it->first.data(),map_it->second.data()));
		map_it++;
	}
	ofstream out(filepath);
	out << doc;
	}else if (m_configIndex->ProtocolModel==OneB)
	{
		using namespace rapidxml;//不能省略
		SaveConfigB();
		using namespace rapidxml;  
		xml_document<> doc;
		//根节点
		xml_node<>* rot = doc.allocate_node(node_pi,doc.allocate_string("version=\"1.0\" encoding=\"utf-8\" standalone=\"yes\""));
		doc.append_node(rot);
		//Application
		xml_node<>* Application = doc.allocate_node(node_element,"Application",NULL);
		Application->append_attribute(doc.allocate_attribute("Name","CETC41 Signal Studio for WLAN "));
		Application->append_attribute(doc.allocate_attribute("Version","1.0"));
		doc.append_node(Application);
		//Function
		xml_node<>* Function = doc.allocate_node(node_element,"Function","IEEE 802.11a\\b\\g\\n M*N MIMO");
		Application->append_node(Function);

		//待配置相关参数
		xml_node<>* parameter = doc.allocate_node(node_element,"Appparameters",NULL);
		Application->append_node(parameter);

		configB *m_configB = m_pass_to_thread.m_configBIndex;
		//按协议保存可配置参数
		xml_node<>* Protocol = doc.allocate_node(node_element,protocoltype[m_configB->ProtocolModel].data(),NULL);
		parameter->append_node(Protocol);

		auto map_it = para.cbegin();
		while(map_it != para.cend()){
			Protocol->append_node(doc.allocate_node(node_element,map_it->first.data(),map_it->second.data()));
			map_it++;
		}
		xml_node<>* Instrument = doc.allocate_node(node_element,"Hardware",NULL);
		parameter->append_node(Instrument);
		map_it = para_hard.cbegin();
		while(map_it != para_hard.cend()){
			Instrument->append_node(doc.allocate_node(node_element,map_it->first.data(),map_it->second.data()));
			map_it++;
		}
		ofstream out(filepath);
		out << doc;
	}else if (m_configIndex->ProtocolModel==OneG)
	{
		using namespace rapidxml;//不能省略
		SaveConfigG();
		using namespace rapidxml;  
		xml_document<> doc;
		//根节点
		xml_node<>* rot = doc.allocate_node(node_pi,doc.allocate_string("version=\"1.0\" encoding=\"utf-8\" standalone=\"yes\""));
		doc.append_node(rot);
		//Application
		xml_node<>* Application = doc.allocate_node(node_element,"Application",NULL);
		Application->append_attribute(doc.allocate_attribute("Name","CETC41 Signal Studio for WLAN "));
		Application->append_attribute(doc.allocate_attribute("Version","1.0"));
		doc.append_node(Application);
		//Function
		xml_node<>* Function = doc.allocate_node(node_element,"Function","IEEE 802.11a\\b\\g\\n M*N MIMO");
		Application->append_node(Function);

		//待配置相关参数
		xml_node<>* parameter = doc.allocate_node(node_element,"Appparameters",NULL);
		Application->append_node(parameter);

		configG *m_configG = m_pass_to_thread.m_configGIndex;
		//按协议保存可配置参数
		xml_node<>* Protocol = doc.allocate_node(node_element,protocoltype[m_configG->ProtocolModel].data(),NULL);
		parameter->append_node(Protocol);

		auto map_it = para.cbegin();
		while(map_it != para.cend()){
			Protocol->append_node(doc.allocate_node(node_element,map_it->first.data(),map_it->second.data()));
			map_it++;
		}
		xml_node<>* Instrument = doc.allocate_node(node_element,"Hardware",NULL);
		parameter->append_node(Instrument);
		map_it = para_hard.cbegin();
		while(map_it != para_hard.cend()){
			Instrument->append_node(doc.allocate_node(node_element,map_it->first.data(),map_it->second.data()));
			map_it++;
		}
		ofstream out(filepath);
		out << doc;
	}else if (m_configIndex->ProtocolModel==OneN)
	{
		using namespace rapidxml;//不能省略
		SaveConfigN();
		using namespace rapidxml;  
		xml_document<> doc;
		//根节点
		xml_node<>* rot = doc.allocate_node(node_pi,doc.allocate_string("version=\"1.0\" encoding=\"utf-8\" standalone=\"yes\""));
		doc.append_node(rot);
		//Application
		xml_node<>* Application = doc.allocate_node(node_element,"Application",NULL);
		Application->append_attribute(doc.allocate_attribute("Name","CETC41 Signal Studio for WLAN "));
		Application->append_attribute(doc.allocate_attribute("Version","1.0"));
		doc.append_node(Application);
		//Function
		xml_node<>* Function = doc.allocate_node(node_element,"Function","IEEE 802.11a\\b\\g\\n M*N MIMO");
		Application->append_node(Function);

		//待配置相关参数
		xml_node<>* parameter = doc.allocate_node(node_element,"Appparameters",NULL);
		Application->append_node(parameter);

		configN *m_configN = m_pass_to_thread.m_configNIndex;
		//按协议保存可配置参数
		xml_node<>* Protocol = doc.allocate_node(node_element,protocoltype[m_configN->ProtocolModel].data(),NULL);
		parameter->append_node(Protocol);

		auto map_it = para.cbegin();
		while(map_it != para.cend()){
			Protocol->append_node(doc.allocate_node(node_element,map_it->first.data(),map_it->second.data()));
			map_it++;
		}
		xml_node<>* Instrument = doc.allocate_node(node_element,"Hardware",NULL);
		parameter->append_node(Instrument);
		map_it = para_hard.cbegin();
		while(map_it != para_hard.cend()){
			Instrument->append_node(doc.allocate_node(node_element,map_it->first.data(),map_it->second.data()));
			map_it++;
		}
		ofstream out(filepath);
		out << doc;
	}else if (m_configIndex->ProtocolModel==OneNL)
	{
		using namespace rapidxml;//不能省略
		SaveConfigNL();
		using namespace rapidxml;  
		xml_document<> doc;
		//根节点
		xml_node<>* rot = doc.allocate_node(node_pi,doc.allocate_string("version=\"1.0\" encoding=\"utf-8\" standalone=\"yes\""));
		doc.append_node(rot);
		//Application
		xml_node<>* Application = doc.allocate_node(node_element,"Application",NULL);
		Application->append_attribute(doc.allocate_attribute("Name","CETC41 Signal Studio for WLAN "));
		Application->append_attribute(doc.allocate_attribute("Version","1.0"));
		doc.append_node(Application);
		//Function
		xml_node<>* Function = doc.allocate_node(node_element,"Function","IEEE 802.11a\\b\\g\\n M*N MIMO");
		Application->append_node(Function);

		//待配置相关参数
		xml_node<>* parameter = doc.allocate_node(node_element,"Appparameters",NULL);
		Application->append_node(parameter);

		configN *m_configN = m_pass_to_thread.m_configNIndex;
		//按协议保存可配置参数
		xml_node<>* Protocol = doc.allocate_node(node_element,protocoltype[m_configN->ProtocolModel].data(),NULL);
		parameter->append_node(Protocol);

		auto map_it = para.cbegin();
		while(map_it != para.cend()){
			Protocol->append_node(doc.allocate_node(node_element,map_it->first.data(),map_it->second.data()));
			map_it++;
		}
		xml_node<>* Instrument = doc.allocate_node(node_element,"Hardware",NULL);
		parameter->append_node(Instrument);
		map_it = para_hard.cbegin();
		while(map_it != para_hard.cend()){
			Instrument->append_node(doc.allocate_node(node_element,map_it->first.data(),map_it->second.data()));
			map_it++;
		}
		ofstream out(filepath);
		out << doc;
	}
}
//保存参数类
void CMainFrame::SaveConfigA(){
	char str[10];
	CString filtertype[4]={"lpfilter","gaussfilter","cosfilter","userdefined"};
	configA *m_configA = m_pass_to_thread.m_configAIndex; 
	config_hard * m_configInstr = m_pass_to_thread.m_confighard;
	itoa(m_configA->oversample_ratio,str,10);para.insert(make_pair<string,string>("Data_ratio",str));
	itoa(m_configA->DataRate,str,10);para.insert(make_pair<string,string>("DataRate",str));
	itoa(m_configA->source_mode,str,10);para.insert(make_pair<string,string>("source_mode",str));
	itoa(m_configA->datainmaxlen,str,10);para.insert(make_pair<string,string>("datainmaxlen",str));
	itoa(m_configA->source_length,str,10);para.insert(make_pair<string,string>("source_length",str));
	itoa(m_configA->num_of_frame,str,10);para.insert(make_pair<string,string>("num_of_frame",str));
	itoa(m_configA->num_of_zeros,str,10);para.insert(make_pair<string,string>("num_of_zeros",str));
	itoa(m_configA->scramble_state_initial,str,10);para.insert(make_pair<string,string>("scramble_state_initial",str));
	//sprintf(str,"%.4f",m_configA->num_of_zeros);para.insert(make_pair<string,string>("num_of_zeros",str));
	sprintf(str,"%.4f",m_configA->IQ_gain);para.insert(make_pair<string,string>("IQ_gain",str));
	sprintf(str,"%.4f",m_configA->quan_angle_adjust);para.insert(make_pair<string,string>("quan_angle_adjust",str));
	para.insert(make_pair<string,string>("scrambler_state_OFDM",m_configA->scrambler_state_OFDM ? "ture":"false"));
	para.insert(make_pair<string,string>("filepath",(!m_configA->filepath.Remove('\n'))? "None":m_configA->filepath));
	para.insert(make_pair<string,string>("add_channel",m_configA->add_channel ? "ture":"false"));
	itoa((int)m_configA->NumOfTaps,str,10);para.insert(make_pair<string,string>("NumofTaps",str));
	itoa((int)m_configA->MAX_Delay_Sample,str,10);para.insert(make_pair<string,string>("MAX_Delay_Sample",str));
	para.insert(make_pair<string,string>("InData_Complex",m_configA->InData_Complex ? "Ture":"False"));
	sprintf(str,"%.0f",m_configA->mobilespeed);para.insert(make_pair<string,string>("mobilespeed",str));
	itoa(m_configA->DataRate,str,10);para.insert(make_pair<string,string>("DataRate",str));
	itoa(m_configA->DataRate,str,10);para.insert(make_pair<string,string>("DataRate",str));
	para.insert(make_pair<string,string>("filtertype",filtertype[m_configA->filter_para.filtertype].GetBuffer()));
	sprintf(str,"%.4f",m_configA->filter_para.lppara.wn);para.insert(make_pair<string,string>("lppara_wn",str));
	itoa(m_configA->filter_para.lppara.length,str,10);para.insert(make_pair<string,string>("lppara_len",str));
	sprintf(str,"%.4f",m_configA->filter_para.gausspara.BT);para.insert(make_pair<string,string>("gausspara_BT",str));
	itoa(m_configA->filter_para.gausspara.length,str,10);para.insert(make_pair<string,string>("gausspara_len",str));
	sprintf(str,"%.4f",m_configA->filter_para.cosinepara.alpha);para.insert(make_pair<string,string>("cosinepara_alpha",str));
	itoa(m_configA->filter_para.cosinepara.length,str,10);para.insert(make_pair<string,string>("cosinpara_len",str));
    para.insert(make_pair<string,string>("filterpath",m_configA->filter_para.filepath.GetBuffer()));
	//硬件相关参数
	para_hard.insert(make_pair<string,string>("carrier_freqz",m_configInstr->freq.GetBuffer()));
	para_hard.insert(make_pair<string,string>("power",m_configInstr->power.GetBuffer()));
	para_hard.insert(make_pair<string,string>("RF",m_configInstr->RF_state.GetBuffer()));
}
void CMainFrame::SaveConfigB(){
	char str[10];
	CString filtertype[4]={"lpfilter","gaussfilter","cosfilter","userdefined"};
	configB *m_configB = m_pass_to_thread.m_configBIndex; 
	config_hard * m_configInstr = m_pass_to_thread.m_confighard;
	itoa(m_configB->oversample_ratio,str,10);para.insert(make_pair<string,string>("Data_ratio",str));
	itoa(m_configB->data_rate,str,10);para.insert(make_pair<string,string>("data_rate",str));
	itoa(m_configB->EZOB_Encoding,str,10);para.insert(make_pair<string,string>("EZOB_Encoding",str));
	itoa(m_configB->source_mode,str,10);para.insert(make_pair<string,string>("source_mode",str));
	itoa(m_configB->scrambler_state,str,10);para.insert(make_pair<string,string>("scrambler_state",str));
	itoa(m_configB->preamble_type,str,10);para.insert(make_pair<string,string>("preamble_type",str));
    itoa(m_configB->num_of_frame,str,10);para.insert(make_pair<string,string>("num_of_frame",str));
	itoa(m_configB->num_of_zeros,str,10);para.insert(make_pair<string,string>("num_of_zeros",str));
	//itoa(m_configB->source_mode,str,10);para.insert(make_pair<string,string>("source_mode",str));
	//itoa(m_configA->datainmaxlen,str,10);para.insert(make_pair<string,string>("datainmaxlen",str));
	itoa(m_configB->source_length,str,10);para.insert(make_pair<string,string>("source_length",str));
	//itoa(m_configA->scramble_state_initial,str,10);para.insert(make_pair<string,string>("scramble_state_initial",str));
	//sprintf(str,"%.4f",m_configA->num_of_zeros);para.insert(make_pair<string,string>("num_of_zeros",str));
	sprintf(str,"%.4f",m_configB->IQ_gain);para.insert(make_pair<string,string>("IQ_gain",str));
	sprintf(str,"%.4f",m_configB->quan_angle_adjust);para.insert(make_pair<string,string>("quan_angle_adjust",str));
	//para.insert(make_pair<string,string>("scrambler_state",m_configB->scrambler_state ? "ture":"false"));
	para.insert(make_pair<string,string>("filepath",(!m_configB->filepath.Remove('\n'))? "None":m_configB->filepath));
	para.insert(make_pair<string,string>("add_channel",m_configB->add_channel ? "ture":"false"));
	itoa((int)m_configB->NumOfTaps,str,10);para.insert(make_pair<string,string>("NumofTaps",str));
	itoa((int)m_configB->MAX_Delay_Sample,str,10);para.insert(make_pair<string,string>("MAX_Delay_Sample",str));
	para.insert(make_pair<string,string>("InData_Complex",m_configB->InData_Complex ? "Ture":"False"));
	sprintf(str,"%.0f",m_configB->mobilespeed);para.insert(make_pair<string,string>("mobilespeed",str));
	//itoa(m_configA->DataRate,str,10);para.insert(make_pair<string,string>("DataRate",str));
	//itoa(m_configA->DataRate,str,10);para.insert(make_pair<string,string>("DataRate",str));
	para.insert(make_pair<string,string>("filtertype",filtertype[m_configB->filter_para.filtertype].GetBuffer()));
	sprintf(str,"%.4f",m_configB->filter_para.lppara.wn);para.insert(make_pair<string,string>("lppara_wn",str));
	itoa(m_configB->filter_para.lppara.length,str,10);para.insert(make_pair<string,string>("lppara_len",str));
	sprintf(str,"%.4f",m_configB->filter_para.gausspara.BT);para.insert(make_pair<string,string>("gausspara_BT",str));
	itoa(m_configB->filter_para.gausspara.length,str,10);para.insert(make_pair<string,string>("gausspara_len",str));
	sprintf(str,"%.4f",m_configB->filter_para.cosinepara.alpha);para.insert(make_pair<string,string>("cosinepara_alpha",str));
	itoa(m_configB->filter_para.cosinepara.length,str,10);para.insert(make_pair<string,string>("cosinpara_len",str));
	para.insert(make_pair<string,string>("filterpath",m_configB->filter_para.filepath.GetBuffer()));
	//硬件相关参数
	para_hard.insert(make_pair<string,string>("carrier_freqz",m_configInstr->freq.GetBuffer()));
	para_hard.insert(make_pair<string,string>("power",m_configInstr->power.GetBuffer()));
	para_hard.insert(make_pair<string,string>("RF",m_configInstr->RF_state.GetBuffer()));
}
void CMainFrame::SaveConfigG(){
	char str[10];
	CString filtertype[4]={"lpfilter","gaussfilter","cosfilter","userdefined"};
	configG *m_configG = m_pass_to_thread.m_configGIndex; 
	config_hard * m_configInstr = m_pass_to_thread.m_confighard;
	itoa(m_configG->oversample_ratio,str,10);para.insert(make_pair<string,string>("Data_ratio",str));
	itoa(m_configG->data_rate,str,10);para.insert(make_pair<string,string>("data_rate",str));
	itoa(m_configG->EZOG_Encoding,str,10);para.insert(make_pair<string,string>("EZOG_Encoding",str));
	itoa(m_configG->source_mode,str,10);para.insert(make_pair<string,string>("source_mode",str));
	itoa(m_configG->scrambler_state,str,10);para.insert(make_pair<string,string>("scrambler_state",str));
	itoa(m_configG->preamble_type,str,10);para.insert(make_pair<string,string>("preamble_type",str));
	itoa(m_configG->num_of_frame,str,10);para.insert(make_pair<string,string>("num_of_frame",str));
	itoa(m_configG->num_of_zeros,str,10);para.insert(make_pair<string,string>("num_of_zeros",str));
	//itoa(m_configB->source_mode,str,10);para.insert(make_pair<string,string>("source_mode",str));
	//itoa(m_configA->datainmaxlen,str,10);para.insert(make_pair<string,string>("datainmaxlen",str));
	itoa(m_configG->source_length,str,10);para.insert(make_pair<string,string>("source_length",str));
	itoa(m_configG->scramble_state_initial,str,10);para.insert(make_pair<string,string>("scramble_state_initial",str));
	//sprintf(str,"%.4f",m_configA->num_of_zeros);para.insert(make_pair<string,string>("num_of_zeros",str));
	sprintf(str,"%.4f",m_configG->IQ_gain);para.insert(make_pair<string,string>("IQ_gain",str));
	sprintf(str,"%.4f",m_configG->quan_angle_adjust);para.insert(make_pair<string,string>("quan_angle_adjust",str));
	para.insert(make_pair<string,string>("scrambler_state_OFDM",m_configG->scrambler_state_OFDM ? "ture":"false"));
	para.insert(make_pair<string,string>("filepath",(!m_configG->filepath.Remove('\n'))? "None":m_configG->filepath));
	para.insert(make_pair<string,string>("add_channel",m_configG->add_channel ? "ture":"false"));
	itoa((int)m_configG->NumOfTaps,str,10);para.insert(make_pair<string,string>("NumofTaps",str));
	itoa((int)m_configG->MAX_Delay_Sample,str,10);para.insert(make_pair<string,string>("MAX_Delay_Sample",str));
	para.insert(make_pair<string,string>("InData_Complex",m_configG->InData_Complex ? "Ture":"False"));
	sprintf(str,"%.0f",m_configG->mobilespeed);para.insert(make_pair<string,string>("mobilespeed",str));
	//itoa(m_configA->DataRate,str,10);para.insert(make_pair<string,string>("DataRate",str));
	//itoa(m_configA->DataRate,str,10);para.insert(make_pair<string,string>("DataRate",str));
	para.insert(make_pair<string,string>("filtertype",filtertype[m_configG->filter_para.filtertype].GetBuffer()));
	sprintf(str,"%.4f",m_configG->filter_para.lppara.wn);para.insert(make_pair<string,string>("lppara_wn",str));
	itoa(m_configG->filter_para.lppara.length,str,10);para.insert(make_pair<string,string>("lppara_len",str));
	sprintf(str,"%.4f",m_configG->filter_para.gausspara.BT);para.insert(make_pair<string,string>("gausspara_BT",str));
	itoa(m_configG->filter_para.gausspara.length,str,10);para.insert(make_pair<string,string>("gausspara_len",str));
	sprintf(str,"%.4f",m_configG->filter_para.cosinepara.alpha);para.insert(make_pair<string,string>("cosinepara_alpha",str));
	itoa(m_configG->filter_para.cosinepara.length,str,10);para.insert(make_pair<string,string>("cosinpara_len",str));
	para.insert(make_pair<string,string>("filterpath",m_configG->filter_para.filepath.GetBuffer()));
	//硬件相关参数
	para_hard.insert(make_pair<string,string>("carrier_freqz",m_configInstr->freq.GetBuffer()));
	para_hard.insert(make_pair<string,string>("power",m_configInstr->power.GetBuffer()));
	para_hard.insert(make_pair<string,string>("RF",m_configInstr->RF_state.GetBuffer()));
}
void CMainFrame::SaveConfigN(){
	char str[10];
	CString filtertype[4]={"lpfilter","gaussfilter","cosfilter","userdefined"};
	configN *m_configN = m_pass_to_thread.m_configNIndex; 
	config_hard * m_configInstr = m_pass_to_thread.m_confighard;
	itoa(m_configN->oversample_ratio,str,10);para.insert(make_pair<string,string>("Data_ratio",str));
	//itoa(m_configN->data_rate,str,10);para.insert(make_pair<string,string>("data_rate",str));
	itoa(m_configN->mcs,str,10);para.insert(make_pair<string,string>("mcs",str));
	itoa(m_configN->aggregation,str,10);para.insert(make_pair<string,string>("aggregation",str));
	itoa(m_configN->txvector_format,str,10);para.insert(make_pair<string,string>("txvector_format",str));
	itoa(m_configN->sounding,str,10);para.insert(make_pair<string,string>("sounding",str));
	itoa(m_configN->source_mode,str,10);para.insert(make_pair<string,string>("source_mode",str));	
	itoa(m_configN->smoothing,str,10);para.insert(make_pair<string,string>("smoothing",str));
	itoa(m_configN->STBC,str,10);para.insert(make_pair<string,string>("STBC",str));
	itoa(m_configN->Short_GI,str,10);para.insert(make_pair<string,string>("Short_GI",str));
	itoa(m_configN->num_of_antenna,str,10);para.insert(make_pair<string,string>("num_of_antenna",str));
	itoa(m_configN->Nss,str,10);para.insert(make_pair<string,string>("Nss",str));
	itoa(m_configN->num_of_sts,str,10);para.insert(make_pair<string,string>("num_of_sts",str));
	itoa(m_configN->LDPC_Coding,str,10);para.insert(make_pair<string,string>("LDPC_Coding",str));
	itoa(m_configN->win,str,10);para.insert(make_pair<string,string>("win",str));
	itoa(m_configN->ieeeQ,str,10);para.insert(make_pair<string,string>("ieeeQ",str));
	//itoa(m_configN->preamble_type,str,10);para.insert(make_pair<string,string>("preamble_type",str));
	itoa(m_configN->num_of_frame,str,10);para.insert(make_pair<string,string>("num_of_frame",str));
	itoa(m_configN->num_of_zeros,str,10);para.insert(make_pair<string,string>("num_of_zeros",str));
	//itoa(m_configB->source_mode,str,10);para.insert(make_pair<string,string>("source_mode",str));
	//itoa(m_configA->datainmaxlen,str,10);para.insert(make_pair<string,string>("datainmaxlen",str));
	itoa(m_configN->source_length,str,10);para.insert(make_pair<string,string>("source_length",str));
	itoa(m_configN->scramSeed,str,10);para.insert(make_pair<string,string>("scramSeed",str));
	//sprintf(str,"%.4f",m_configA->num_of_zeros);para.insert(make_pair<string,string>("num_of_zeros",str));
	sprintf(str,"%.4f",m_configN->IQ_gain);para.insert(make_pair<string,string>("IQ_gain",str));
	sprintf(str,"%.4f",m_configN->quan_angle_adjust);para.insert(make_pair<string,string>("quan_angle_adjust",str));
	para.insert(make_pair<string,string>("scrambler",m_configN->scrambler ? "ture":"false"));
	para.insert(make_pair<string,string>("filepath",((!m_configN->filepath.Remove('\n'))? "None":m_configN->filepath)));
	para.insert(make_pair<string,string>("add_channel",m_configN->add_channel ? "ture":"false"));
	para.insert(make_pair<string,string>("BandWidth",(m_configN->BandWidth.Compare(_T("20"))?"40":"20")));
	para.insert(make_pair<string,string>("interleave_state",m_configN->interleave_state ? "ture":"false"));
	//itoa((int)m_configN->NumOfTaps,str,10);para.insert(make_pair<string,string>("NumofTaps",str));
	//itoa((int)m_configN->MAX_Delay_Sample,str,10);para.insert(make_pair<string,string>("MAX_Delay_Sample",str));
	//para.insert(make_pair<string,string>("InData_Complex",m_configG->InData_Complex ? "Ture":"False"));
	sprintf(str,"%.0f",m_configN->mobilespeed);para.insert(make_pair<string,string>("mobilespeed",str));
	//itoa(m_configA->DataRate,str,10);para.insert(make_pair<string,string>("DataRate",str));
	//itoa(m_configA->DataRate,str,10);para.insert(make_pair<string,string>("DataRate",str));
	para.insert(make_pair<string,string>("filtertype",filtertype[m_configN->filter_para.filtertype].GetBuffer()));
	sprintf(str,"%.4f",m_configN->filter_para.lppara.wn);para.insert(make_pair<string,string>("lppara_wn",str));
	itoa(m_configN->filter_para.lppara.length,str,10);para.insert(make_pair<string,string>("lppara_len",str));
	sprintf(str,"%.4f",m_configN->filter_para.gausspara.BT);para.insert(make_pair<string,string>("gausspara_BT",str));
	itoa(m_configN->filter_para.gausspara.length,str,10);para.insert(make_pair<string,string>("gausspara_len",str));
	sprintf(str,"%.4f",m_configN->filter_para.cosinepara.alpha);para.insert(make_pair<string,string>("cosinepara_alpha",str));
	itoa(m_configN->filter_para.cosinepara.length,str,10);para.insert(make_pair<string,string>("cosinpara_len",str));
	para.insert(make_pair<string,string>("filterpath",m_configN->filter_para.filepath.GetBuffer()));
	//硬件相关参数
	para_hard.insert(make_pair<string,string>("carrier_freqz",m_configInstr->freq.GetBuffer()));
	para_hard.insert(make_pair<string,string>("power",m_configInstr->power.GetBuffer()));
	para_hard.insert(make_pair<string,string>("RF",m_configInstr->RF_state.GetBuffer()));
}
void CMainFrame::SaveConfigNL(){
}

//保存
void CMainFrame::CongfigSave(){
	if (userfilepath=="None"){
		MessageBox("未打开已有配置文件！");
	}else{
		Write(userfilepath);
	}
}
//另存为
void CMainFrame::ConfigSaveAs(){
	CString filepath;
	CFileDialog dlg(FALSE, "xml", _T("config"));   
	dlg.m_ofn.lpstrTitle = "保存参数配置文件";  
	dlg.m_ofn.lpstrFilter = "xml files (*.xml)";
	if(dlg.DoModal()==IDOK)
		filepath=dlg.GetPathName();
	if (filepath==""){
		MessageBox("请指定文件路径");
			return;
	}
	Write(filepath);
}
void CMainFrame::FileNew(){
	return;
}

void CMainFrame::OnFrame11a()
{
	// TODO: 在此添加命令处理程序代码
	Cframe m_frame;
	m_frame.DoModal();
}


void CMainFrame::On11aConfig()
{
	// TODO: 在此添加命令处理程序代码
	CframeConfig m_frame_conf;
	m_frame_conf.DoModal();
}


void CMainFrame::On11bPicture()
{
	// TODO: 在此添加命令处理程序代码
	CframeB m_frame_b;
	m_frame_b.DoModal();
}


void CMainFrame::On11bConfig()
{
	// TODO: 在此添加命令处理程序代码
	CframeconfigB m_frame_conf_b;
	m_frame_conf_b.DoModal();
}


void CMainFrame::On11gPicture()
{
	// TODO: 在此添加命令处理程序代码
	CframeG m_frameg;
	m_frameg.DoModal();
}


void CMainFrame::On11gConfig()
{
	// TODO: 在此添加命令处理程序代码
	CframeconfigG m_config_G;
	m_config_G.DoModal();
}
