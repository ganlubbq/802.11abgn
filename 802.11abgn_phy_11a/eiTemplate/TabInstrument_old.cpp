// TabInstrument.cpp : 实现文件
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "TabInstrument.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include <iostream>
#include <regex>

using namespace std;

// CTabInstrument 对话框

IMPLEMENT_DYNAMIC(CTabInstrument, CDialogEx)

CTabInstrument::CTabInstrument(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTabInstrument::IDD, pParent)
{
	m_finished_ini = FALSE;
	send_command_enabled = FALSE;
	//vi = 0;
}

CTabInstrument::~CTabInstrument()
{
}

void CTabInstrument::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_INSTRUMENT_INDEX, m_combo_instrument_index);
}


BEGIN_MESSAGE_MAP(CTabInstrument, CDialogEx)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_UPDATE_TO_INSTRUMENT, &CTabInstrument::OnClickedBtnUpdateToInstrument)
	ON_BN_CLICKED(IDC_BTN_UPDATE_FROM_INSTRUMENT, &CTabInstrument::OnClickedBtnUpdateFromInstrument)
	ON_BN_CLICKED(IDC_BTN_POWER_SEARCH, &CTabInstrument::OnClickedBtnPowerSearch)
	ON_BN_CLICKED(IDC_BTN_DC_CAL, &CTabInstrument::OnClickedBtnDcCal)
	ON_BN_CLICKED(IDC_BTN_RESET, &CTabInstrument::OnClickedBtnReset)
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED,OnPropertyChanged)
	ON_CBN_SELCHANGE(IDC_COMBO_INSTRUMENT_INDEX, &CTabInstrument::OnSelchangeComboInstrumentIndex)
END_MESSAGE_MAP()


// CTabInstrument 消息处理程序


BOOL CTabInstrument::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_combo_instrument_index.SetCurSel(0);
	CRect rc;
	GetClientRect(&rc);
	rc.left += 10;
	rc.top += 45;
	m_MFCPropertyGrid_INSTRUMENT.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,rc,this,PROPERTYGRID_INSTRUMENT_CONFIG);
	m_MFCPropertyGrid_INSTRUMENT.EnableHeaderCtrl(FALSE,"参数","值");
	m_MFCPropertyGrid_INSTRUMENT.EnableDescriptionArea();
	m_MFCPropertyGrid_INSTRUMENT.SetDescriptionRows(5);
	m_MFCPropertyGrid_INSTRUMENT.SetVSDotNetLook();
	m_MFCPropertyGrid_INSTRUMENT.MarkModifiedProperties();
	m_MFCPropertyGrid_INSTRUMENT.SetAlphabeticMode(false); 
	m_MFCPropertyGrid_INSTRUMENT.SetShowDragContext();

	/************************************************************************/
	/* 仪器配置页面的各个配置组的创建                                       */
	/************************************************************************/
	p_group_Configuration = new CMFCPropertyGridProperty("仪器信息",INSTR_GROUP_CONFIG);
	p_group_Basic = new CMFCPropertyGridProperty("基本配置",INSTR_GROUP_BASIC);
	p_group_IQ = new CMFCPropertyGridProperty("IQ",INSTR_GROUP_IQ);
	p_group_ALC = new CMFCPropertyGridProperty("ALC",INSTR_GROUP_ALC);
	p_group_ARB = new CMFCPropertyGridProperty("任意波",INSTR_GROUP_ARB);
	p_group_Trigger = new CMFCPropertyGridProperty("触发",INSTR_GROUP_TRIGGER);
	p_group_Marker = new CMFCPropertyGridProperty("标记",INSTR_GROUP_MARKER);
	p_group_RT_Noise = new CMFCPropertyGridProperty("实时噪声",INSTR_GROUP_RT_NOISE);

	//1:仪器信息组
	p_instrument_name = new CMFCPropertyGridProperty("仪器型号","ei41","显示当前索引对应的仪器型号",INSTR_INSTRUMENT_NAME);
	p_instrument_name->Enable(FALSE);
	p_group_Configuration->AddSubItem(p_instrument_name);

	//2:基本配置组
	p_frequency = new CMFCPropertyGridProperty("频率","2.412000000 GHz","设置频率值，范围: 10MHz - 10GHz",INSTR_FREQUENCY);
	p_group_Basic->AddSubItem(p_frequency);
	p_amplitude = new CMFCPropertyGridProperty("功率","-30.00 dBm","设置振幅的值,范围：--，单位：dBm",INSTR_AMPLITUDE);
	p_group_Basic->AddSubItem(p_amplitude);
	p_RF_output = new CMFCPropertyGridProperty("射频输出","Off","打开或关闭射频输出\r\n选项：On | Off\r\n默认值：Off",INSTR_RF_OUTPUT);
	p_RF_output->AddOption("On");
	p_RF_output->AddOption("Off");
	p_RF_output->AllowEdit(FALSE);
	p_group_Basic->AddSubItem(p_RF_output);

	//3:IQ组
	p_IQ_adjustments = new CMFCPropertyGridProperty("I/Q 调理","Off","设置I/Q调整的状态：On/Off",INSTR_IQ_ADJUSTMENTS);
	p_IQ_adjustments->AddOption("On");  
	p_IQ_adjustments->AddOption("Off"); 
	p_IQ_adjustments->AllowEdit(FALSE);
	p_group_IQ->AddSubItem(p_IQ_adjustments);
	p_I_offset = new CMFCPropertyGridProperty("I 偏置","0.0000 %","设置I路补偿值，百分比值\r\n设置I/Q调整为On时有效",INSTR_I_OFFSET);
	p_I_offset->Enable(FALSE);
	p_group_IQ->AddSubItem(p_I_offset);
	p_Q_offset = new CMFCPropertyGridProperty("Q 偏置","0.0000 %","设置Q路补偿值，百分比值\r\n设置I/Q调整为On时有效",INSTR_Q_OFFSET);
	p_Q_offset->Enable(FALSE);
	p_group_IQ->AddSubItem(p_Q_offset);
	p_IQ_gain_balance = new CMFCPropertyGridProperty("I/Q 增益平衡","0.00 dB","设置I/Q增益平衡值，单位:dB",INSTR_IQ_GAIN_BALANCE);
	p_IQ_gain_balance->Enable(FALSE);
	p_group_IQ->AddSubItem(p_IQ_gain_balance);
	p_quadrature_angle_adjustment = new CMFCPropertyGridProperty("正交偏离","0.00 Deg","设置正交角度，单位:Deg",INSTR_QUADRATURE_ANGLE_ADJUST);
	p_quadrature_angle_adjustment->Enable(FALSE);
	p_group_IQ->AddSubItem(p_quadrature_angle_adjustment);

	//4:ALC组
	p_ALC = new CMFCPropertyGridProperty("ALC","On","设置ALC的状态：On/Off",INSTR_ALC);
	p_ALC->AddOption("On");  
	p_ALC->AddOption("Off"); 
	p_ALC->AllowEdit(FALSE);
	p_group_ALC->AddSubItem(p_ALC);
	p_ALC_bandwidth = new CMFCPropertyGridProperty("ALC 带宽","自动","选择ALC带宽\r\n选项：自动，100 Hz,1 KHz,10 KHz,100 KHz",INSTR_ALC_BANDWIDTH);
	p_ALC_bandwidth->AddOption("自动");
	p_ALC_bandwidth->AddOption("100Hz");
	p_ALC_bandwidth->AddOption("1KHz"); 
	p_ALC_bandwidth->AddOption("10KHz");
	p_ALC_bandwidth->AddOption("100KHz");
	p_ALC_bandwidth->AllowEdit(FALSE);
	p_group_ALC->AddSubItem(p_ALC_bandwidth);
	p_power_search_ref = new CMFCPropertyGridProperty("搜索参考","固定","选择功率搜索的状态\r\n选项：固定，调制",INSTR_POWER_SEARCH_REF);
	p_power_search_ref->AddOption("固定");
	p_power_search_ref->AddOption("调制");
	p_power_search_ref->AllowEdit(FALSE);
	p_power_search_ref->Enable(FALSE);
	p_group_ALC->AddSubItem(p_power_search_ref);
	p_RF_during_power_search = new CMFCPropertyGridProperty("搜索输出","正常","设置RF的状态：正常/最小值",INSTR_RF_DURING_POWER_SEARCH);
	p_RF_during_power_search->AddOption("正常");  
	p_RF_during_power_search->AddOption("最小值"); 
	p_RF_during_power_search->AllowEdit(FALSE);
	p_RF_during_power_search->Enable(FALSE);
	p_group_ALC->AddSubItem(p_RF_during_power_search);
	p_power_search_method = new CMFCPropertyGridProperty("搜索方式","手动","设置功率搜索的方式：手动/自动",INSTR_POWER_SEARCH_METHOD);
	p_power_search_method->AddOption("手动");  
	p_power_search_method->AddOption("自动"); 
	p_group_ALC->AddSubItem(p_power_search_method);

	//5:任意波组
	p_ARB_clock_type = new CMFCPropertyGridProperty("时钟类型","内部","设置仪器时钟的类型：内部/外部",INSTR_ARB_CLOCK_TYPE);
	p_ARB_clock_type->AddOption("内部");
	p_ARB_clock_type->AddOption("外部");
	p_group_ARB->AddSubItem(p_ARB_clock_type);
	p_ARB_samp_clock = new CMFCPropertyGridProperty("采样时钟","自动","设置采样时钟的方式：自动/手动",INSTR_ARB_SAMP_CLOCK);
	p_ARB_samp_clock->AddOption("自动");
	p_ARB_samp_clock->AddOption("手动");
	p_group_ARB->AddSubItem(p_ARB_samp_clock);
	p_ARB_clock_freq = new CMFCPropertyGridProperty("采样频率","200MHz","设置采样时钟的频率",INSTR_ARB_CLOCK_FREQ);
	p_group_ARB->AddSubItem(p_ARB_clock_freq);

	//6:触发组
	p_trigger_mod = new CMFCPropertyGridProperty("触发模式","连续","设置触发模式：连续|单次|波形段|门控",INSTR_TRIGGRT_MOD);
	p_trigger_mod->AddOption("连续");
	p_trigger_mod->AddOption("单次");
	p_trigger_mod->AddOption("波形段");
	p_trigger_mod->AddOption("门控");
	p_group_Trigger->AddSubItem(p_trigger_mod);
	p_trigger_source = new CMFCPropertyGridProperty("触发源","触发键","设置触发源：触发键|总线|外部",INSTR_TRIGGRT_SRC);
	p_trigger_source->AddOption("触发键");
	p_trigger_source->AddOption("总线");
	p_trigger_source->AddOption("外部");
	p_group_Trigger->AddSubItem(p_trigger_source);
	p_trigger_slope = new CMFCPropertyGridProperty("极性","正","设置触发极性：正|负",INSTR_TRIGGRT_SLOPE);
	p_trigger_slope->AddOption("正");
	p_trigger_slope->AddOption("负");
	p_group_Trigger->AddSubItem(p_trigger_slope);
	p_trigger_delay_active = new CMFCPropertyGridProperty("延迟开关","延时开","打开或关闭延迟开关：延迟开|延迟关",INSTR_TRIGGRT_DELAY_ACTIVE);
	p_trigger_delay_active->AddOption("延迟开");
	p_trigger_delay_active->AddOption("延迟关");
	p_group_Trigger->AddSubItem(p_trigger_delay_active);
	p_trigger_delay = new CMFCPropertyGridProperty("触发延迟","100us","设置触发延迟",INSTR_TRIGGRT_DELAY);
	p_group_Trigger->AddSubItem(p_trigger_delay);
	p_trigger_cont_type = new CMFCPropertyGridProperty("连续","自动","设置连续触发类型：自动|触发|实时",INSTR_TRIGGRT_CONT_TYPE);
	p_trigger_cont_type->AddOption("自动");
	p_trigger_cont_type->AddOption("触发");
	p_trigger_cont_type->AddOption("实时");
	p_group_Trigger->AddSubItem(p_trigger_cont_type);
	p_trigger_sing_type = new CMFCPropertyGridProperty("单次","忽略重复触发","设置单次触发类型：忽略重复触发|缓冲重复触发|实时重复触发",INSTR_TRIGGRT_SING_TYPE);
	p_trigger_sing_type->AddOption("忽略重复触发");
	p_trigger_sing_type->AddOption("缓冲重复触发");
	p_trigger_sing_type->AddOption("实时重复触发");
	p_trigger_sing_type->Enable(FALSE);
	p_group_Trigger->AddSubItem(p_trigger_sing_type);
	p_trigger_sadv_type = new CMFCPropertyGridProperty("波形段","单次","设置波形段触发类型：单次|连续",INSTR_TRIGGRT_SADV_TYPE);
	p_trigger_sadv_type->AddOption("单次");
	p_trigger_sadv_type->AddOption("连续");
	p_trigger_sadv_type->Enable(FALSE);
	p_group_Trigger->AddSubItem(p_trigger_sadv_type);
	p_trigger_gate_type = new CMFCPropertyGridProperty("门控","低有效","设置门控触发类型：低有效|高有效",INSTR_TRIGGRT_GATE_TYPE);
	p_trigger_gate_type->AddOption("低有效");
	p_trigger_gate_type->AddOption("高有效");
	p_trigger_gate_type->Enable(FALSE);
	p_group_Trigger->AddSubItem(p_trigger_gate_type);

	//7:标记组
	p_marker_state = new CMFCPropertyGridProperty("标记开关","On","设置标记开关：On/Off",INSTR_MARKER_STATE);
	p_marker_state->AddOption("On");
	p_marker_state->AddOption("Off");
	p_group_Marker->AddSubItem(p_marker_state);
	p_marker_xiaoyin = new CMFCPropertyGridProperty("射频脉冲消隐","On","设置射频脉冲消隐开关：On/Off",INSTR_MARKER_XIAOYIN);
	p_marker_xiaoyin->AddOption("On");
	p_marker_xiaoyin->AddOption("Off");
	p_group_Marker->AddSubItem(p_marker_xiaoyin);
	p_marker_ALC_hold = new CMFCPropertyGridProperty("ALC保持","On","设置ALC保持开关：On/Off",INSTR_MARKER_ALC_HOLD);
	p_marker_ALC_hold->AddOption("On");
	p_marker_ALC_hold->AddOption("Off");
	p_group_Marker->AddSubItem(p_marker_ALC_hold);
	p_marker_no_1 = new CMFCPropertyGridProperty("标记1开关","On","设置标记1开关：On/Off",INSTR_MARKER_NO_1);
	p_marker_no_1->AddOption("开");
	p_marker_no_1->AddOption("关");
	p_marker_polar_no_1 = new CMFCPropertyGridProperty("标记1极性","正","设置标记1极性：正/负",INSTR_MARKER_POLAR_NO_1);
	p_marker_polar_no_1->AddOption("正");
	p_marker_polar_no_1->AddOption("负");
	p_marker_no_2 = new CMFCPropertyGridProperty("标记2开关","On","设置标记2开关：On/Off",INSTR_MARKER_NO_2);
	p_marker_no_2->AddOption("开");
	p_marker_no_2->AddOption("关");
	p_marker_polar_no_2 = new CMFCPropertyGridProperty("标记2极性","正","设置标记2极性：正/负",INSTR_MARKER_POLAR_NO_2);
	p_marker_polar_no_2->AddOption("正");
	p_marker_polar_no_2->AddOption("负");
	p_marker_no_3 = new CMFCPropertyGridProperty("标记3开关","On","设置标记3开关：On/Off",INSTR_MARKER_NO_3);
	p_marker_no_3->AddOption("开");
	p_marker_no_3->AddOption("关");
	p_marker_polar_no_3 = new CMFCPropertyGridProperty("标记3极性","正","设置标记3极性：正/负",INSTR_MARKER_POLAR_NO_3);
	p_marker_polar_no_3->AddOption("正");
	p_marker_polar_no_3->AddOption("负");
	p_marker_no_4 = new CMFCPropertyGridProperty("标记4开关","On","设置标记4开关：On/Off",INSTR_MARKER_NO_4);
	p_marker_no_4->AddOption("开");
	p_marker_no_4->AddOption("关");
	p_marker_polar_no_4 = new CMFCPropertyGridProperty("标记4极性","正","设置标记4极性：正/负",INSTR_MARKER_POLAR_NO_4);
	p_marker_polar_no_4->AddOption("正");
	p_marker_polar_no_4->AddOption("负");
	p_group_Marker->AddSubItem(p_marker_no_1);
	p_group_Marker->AddSubItem(p_marker_no_2);
	p_group_Marker->AddSubItem(p_marker_no_3);
	p_group_Marker->AddSubItem(p_marker_no_4);
	p_group_Marker->AddSubItem(p_marker_polar_no_1);
	p_group_Marker->AddSubItem(p_marker_polar_no_2);
	p_group_Marker->AddSubItem(p_marker_polar_no_3);
	p_group_Marker->AddSubItem(p_marker_polar_no_4);

	//8:实时噪声组
	p_rt_noise_state = new CMFCPropertyGridProperty("噪声开关","Off","设置实时噪声的开关状态：On/Off",INSTR_RT_NOISE);
	p_rt_noise_state->AddOption("On");
	p_rt_noise_state->AddOption("Off");
	p_rt_noise_state->AllowEdit(FALSE);
	p_group_RT_Noise->AddSubItem(p_rt_noise_state);
	p_carrier_to_noise_ratio = new CMFCPropertyGridProperty("载波信噪比","20.00 dB","设置信噪比",INSTR_CARRIER_TO_NOISE_RATIO);
	p_group_RT_Noise->AddSubItem(p_carrier_to_noise_ratio);
	p_carrier_bandwidth = new CMFCPropertyGridProperty("载波带宽","20.00 Mhz","设置载波的带宽",INSTR_CARRIER_BANDWIDTH);
	p_group_RT_Noise->AddSubItem(p_carrier_bandwidth);
	p_noise_bandwidth = new CMFCPropertyGridProperty("噪声带宽","20.00 Mhz","设置噪声的带宽",INSTR_NOISE_BANDWIDTH);
	p_group_RT_Noise->AddSubItem(p_noise_bandwidth);

	//p_group_RT_Noise->Expand(FALSE);


	/************************************************************************/
	/* 将各组配置项加入到属性列表页面中                                     */
	/************************************************************************/
	m_MFCPropertyGrid_INSTRUMENT.AddProperty(p_group_Configuration);
	m_MFCPropertyGrid_INSTRUMENT.AddProperty(p_group_Basic);
	m_MFCPropertyGrid_INSTRUMENT.AddProperty(p_group_IQ);
	m_MFCPropertyGrid_INSTRUMENT.AddProperty(p_group_ALC);
	m_MFCPropertyGrid_INSTRUMENT.AddProperty(p_group_ARB);
	m_MFCPropertyGrid_INSTRUMENT.AddProperty(p_group_Trigger);
	m_MFCPropertyGrid_INSTRUMENT.AddProperty(p_group_Marker);
	m_MFCPropertyGrid_INSTRUMENT.AddProperty(p_group_RT_Noise);

	m_MFCPropertyGrid_INSTRUMENT.SetCustomColors(RGB(250,250,250),RGB(0,0,0),RGB(230,230,230),RGB(100,100,100),RGB(230,230,230),RGB(0,0,0),RGB(220,220,220));
	m_MFCPropertyGrid_INSTRUMENT.ShowWindow(SW_SHOW);

	m_finished_ini = TRUE;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CTabInstrument::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CTabInstrument::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码
	if (IsWindowVisible() || m_finished_ini)
	{
		m_MFCPropertyGrid_INSTRUMENT.MoveWindow(10,45,cx-32,cy-65);
		//m_MFCPropertyGrid_INSTRUMENT.Invalidate();
	}
	
}


void CTabInstrument::OnClickedBtnUpdateToInstrument()
{
	// TODO: 在此添加控件通知处理程序代码
	ViUInt32  retCnt = 0;
	ViUInt32  maxlen = 100;
	ViStatus  status = 0;

	CString str;
	CString str_temp;
	/************************************************************************/
	/* 拼接程控命令并发送到仪器                                             */
	/************************************************************************/
	//1：仪器信息

	//2：基本配置
	str_temp = (CString)p_frequency->GetValue();
	str_temp.Remove(' ');
	str.Format("FREQ %s\n",str_temp);
	status = viWrite(vi,ViBuf(str.GetBuffer()),maxlen,&retCnt);//设置频率(100k--67G)
	instr_params[m_combo_instrument_index.GetCurSel()].frequency = str_temp;
	Sleep(10);

	str_temp = p_amplitude->GetValue();
	str_temp.Remove(' ');
	str.Format("POW %s\n",str_temp);
	status = viWrite(vi,ViBuf(str.GetBuffer()),maxlen,&retCnt);//设置功率(-135dBm--30dBm)  默认0dbm
	instr_params[m_combo_instrument_index.GetCurSel()].amplitude = str_temp;
	Sleep(10);

	str_temp = p_RF_output->GetValue();
	str.Format("OUTP %s\n",str_temp);
	status = viWrite(vi,ViBuf(str.GetBuffer()),maxlen,&retCnt);//射频开关 OUTP ON|OFF 1|0  默认关
	instr_params[m_combo_instrument_index.GetCurSel()].RF_output = str_temp;
	Sleep(10);
	//3：IQ部分
	//4：ALC部分
	str_temp = p_ALC->GetValue();
	str.Format("POW:ALC:STAT %s\n",str_temp);
	status = viWrite(vi,ViBuf(str.GetBuffer()),maxlen,&retCnt);//环路状态 POW:ALC:STAT ON(闭环)|OFF（开环） 默认闭环
	instr_params[m_combo_instrument_index.GetCurSel()].ALC = str_temp;
	Sleep(10);
	//5：Dual ARB部分
	//6：Dual ARB 标记工具部分
	//7：Dual ARB 触发器部分
	//8：实时噪声部分
}


void CTabInstrument::OnClickedBtnUpdateFromInstrument()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CTabInstrument::OnClickedBtnPowerSearch()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CTabInstrument::OnClickedBtnDcCal()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CTabInstrument::OnClickedBtnReset()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CTabInstrument::OnSelchangeComboInstrumentIndex()
{
	// TODO: 在此添加控件通知处理程序代码

	/************************************************************************/
	/* 从主框架获取vi变量并赋给自身，并显示这个仪器的参数                   */
	/************************************************************************/
	int instr_index = m_combo_instrument_index.GetCurSel();
	vi = ((CMainFrame*)AfxGetMainWnd())->vi[instr_index];
	p_frequency->SetValue((COleVariant)instr_params[instr_index].frequency);
	p_amplitude->SetValue((COleVariant)instr_params[instr_index].amplitude);
	p_RF_output->SetValue((COleVariant)instr_params[instr_index].RF_output);
	p_ALC->SetValue((COleVariant)instr_params[instr_index].ALC);

}

LRESULT CTabInstrument::OnPropertyChanged(__in WPARAM wparam,__in LPARAM lparam){
	CMFCPropertyGridProperty* pProp = (CMFCPropertyGridProperty*) lparam;

	int id_changed = pProp->GetData();//获取当前值发生变化的属性的ID
	CString str_temp = pProp->GetValue();
	CString str = "";
	ViUInt32 retCnt = 0;
	ViStatus status = 0;
	char ch[256] = "";
	ViUInt32 read_cnt = 0;
	ViUInt32 write_cnt = 0;
	regex patten("^\\d+(\\.\\d+)?[kmg]?(hz)?$",regex::icase);
	bool match_result = false;
	switch(id_changed)
	{
	case INSTR_FREQUENCY:
		str_temp.Remove(' ');
		match_result = regex_match(str_temp.GetBuffer(),patten);
		if (match_result)
		{
			if (send_command_enabled)
			{
				str.Format("FREQ %s\n",str_temp);
				status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);//设置频率(100k--67G)
				Sleep(10);
				status = viWrite(vi,(ViBuf)"FREQ?\n",256,&write_cnt);//查询实际的频率
				Sleep(10);
				status = viRead(vi,(ViBuf)ch,256,&read_cnt);//读取仪器返回的数据
				ch[read_cnt-1] = '\0';
				str_temp.Format("%sHz",ch);
			}
			instr_params[m_combo_instrument_index.GetCurSel()].frequency = str_temp;
			pProp->SetValue(str_temp);
		}else{
			MessageBox("频率设置有误！");
		}
		break;
	case INSTR_AMPLITUDE:
		str_temp.Remove(' ');
		if (send_command_enabled)
		{
			str.Format("POW %s\n",str_temp);
			status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);//设置频率(100k--67G)
		}
		instr_params[m_combo_instrument_index.GetCurSel()].amplitude = str_temp;
		pProp->SetValue(str_temp);
		Sleep(10);
		break;
	case INSTR_RF_OUTPUT:
		str_temp.Remove(' ');
		if (send_command_enabled)
		{
			str.Format("OUTP %s\n",str_temp);
			status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);//设置频率(100k--67G)
		}
		instr_params[m_combo_instrument_index.GetCurSel()].RF_output = str_temp;
		pProp->SetValue(str_temp);
		Sleep(10);
		break;
	case INSTR_ALC:
		str_temp.Remove(' ');
		if (send_command_enabled)
		{
			str.Format("POW:ALC:STAT %s\n",str_temp);
			status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);//设置频率(100k--67G)
		}
		instr_params[m_combo_instrument_index.GetCurSel()].ALC = str_temp;
		pProp->SetValue(str_temp);
		Sleep(10);
		break;
	default:
		break;
	}
	//SetFocus();

	//CString str;
	//str.Format("%d",pProp->GetData());

	//MessageBox(str);
	return 0;
}


