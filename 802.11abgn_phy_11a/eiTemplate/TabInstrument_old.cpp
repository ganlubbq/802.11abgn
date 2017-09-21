// TabInstrument.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "TabInstrument.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include <iostream>
#include <regex>

using namespace std;

// CTabInstrument �Ի���

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


// CTabInstrument ��Ϣ�������


BOOL CTabInstrument::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_combo_instrument_index.SetCurSel(0);
	CRect rc;
	GetClientRect(&rc);
	rc.left += 10;
	rc.top += 45;
	m_MFCPropertyGrid_INSTRUMENT.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,rc,this,PROPERTYGRID_INSTRUMENT_CONFIG);
	m_MFCPropertyGrid_INSTRUMENT.EnableHeaderCtrl(FALSE,"����","ֵ");
	m_MFCPropertyGrid_INSTRUMENT.EnableDescriptionArea();
	m_MFCPropertyGrid_INSTRUMENT.SetDescriptionRows(5);
	m_MFCPropertyGrid_INSTRUMENT.SetVSDotNetLook();
	m_MFCPropertyGrid_INSTRUMENT.MarkModifiedProperties();
	m_MFCPropertyGrid_INSTRUMENT.SetAlphabeticMode(false); 
	m_MFCPropertyGrid_INSTRUMENT.SetShowDragContext();

	/************************************************************************/
	/* ��������ҳ��ĸ���������Ĵ���                                       */
	/************************************************************************/
	p_group_Configuration = new CMFCPropertyGridProperty("������Ϣ",INSTR_GROUP_CONFIG);
	p_group_Basic = new CMFCPropertyGridProperty("��������",INSTR_GROUP_BASIC);
	p_group_IQ = new CMFCPropertyGridProperty("IQ",INSTR_GROUP_IQ);
	p_group_ALC = new CMFCPropertyGridProperty("ALC",INSTR_GROUP_ALC);
	p_group_ARB = new CMFCPropertyGridProperty("���Ⲩ",INSTR_GROUP_ARB);
	p_group_Trigger = new CMFCPropertyGridProperty("����",INSTR_GROUP_TRIGGER);
	p_group_Marker = new CMFCPropertyGridProperty("���",INSTR_GROUP_MARKER);
	p_group_RT_Noise = new CMFCPropertyGridProperty("ʵʱ����",INSTR_GROUP_RT_NOISE);

	//1:������Ϣ��
	p_instrument_name = new CMFCPropertyGridProperty("�����ͺ�","ei41","��ʾ��ǰ������Ӧ�������ͺ�",INSTR_INSTRUMENT_NAME);
	p_instrument_name->Enable(FALSE);
	p_group_Configuration->AddSubItem(p_instrument_name);

	//2:����������
	p_frequency = new CMFCPropertyGridProperty("Ƶ��","2.412000000 GHz","����Ƶ��ֵ����Χ: 10MHz - 10GHz",INSTR_FREQUENCY);
	p_group_Basic->AddSubItem(p_frequency);
	p_amplitude = new CMFCPropertyGridProperty("����","-30.00 dBm","���������ֵ,��Χ��--����λ��dBm",INSTR_AMPLITUDE);
	p_group_Basic->AddSubItem(p_amplitude);
	p_RF_output = new CMFCPropertyGridProperty("��Ƶ���","Off","�򿪻�ر���Ƶ���\r\nѡ�On | Off\r\nĬ��ֵ��Off",INSTR_RF_OUTPUT);
	p_RF_output->AddOption("On");
	p_RF_output->AddOption("Off");
	p_RF_output->AllowEdit(FALSE);
	p_group_Basic->AddSubItem(p_RF_output);

	//3:IQ��
	p_IQ_adjustments = new CMFCPropertyGridProperty("I/Q ����","Off","����I/Q������״̬��On/Off",INSTR_IQ_ADJUSTMENTS);
	p_IQ_adjustments->AddOption("On");  
	p_IQ_adjustments->AddOption("Off"); 
	p_IQ_adjustments->AllowEdit(FALSE);
	p_group_IQ->AddSubItem(p_IQ_adjustments);
	p_I_offset = new CMFCPropertyGridProperty("I ƫ��","0.0000 %","����I·����ֵ���ٷֱ�ֵ\r\n����I/Q����ΪOnʱ��Ч",INSTR_I_OFFSET);
	p_I_offset->Enable(FALSE);
	p_group_IQ->AddSubItem(p_I_offset);
	p_Q_offset = new CMFCPropertyGridProperty("Q ƫ��","0.0000 %","����Q·����ֵ���ٷֱ�ֵ\r\n����I/Q����ΪOnʱ��Ч",INSTR_Q_OFFSET);
	p_Q_offset->Enable(FALSE);
	p_group_IQ->AddSubItem(p_Q_offset);
	p_IQ_gain_balance = new CMFCPropertyGridProperty("I/Q ����ƽ��","0.00 dB","����I/Q����ƽ��ֵ����λ:dB",INSTR_IQ_GAIN_BALANCE);
	p_IQ_gain_balance->Enable(FALSE);
	p_group_IQ->AddSubItem(p_IQ_gain_balance);
	p_quadrature_angle_adjustment = new CMFCPropertyGridProperty("����ƫ��","0.00 Deg","���������Ƕȣ���λ:Deg",INSTR_QUADRATURE_ANGLE_ADJUST);
	p_quadrature_angle_adjustment->Enable(FALSE);
	p_group_IQ->AddSubItem(p_quadrature_angle_adjustment);

	//4:ALC��
	p_ALC = new CMFCPropertyGridProperty("ALC","On","����ALC��״̬��On/Off",INSTR_ALC);
	p_ALC->AddOption("On");  
	p_ALC->AddOption("Off"); 
	p_ALC->AllowEdit(FALSE);
	p_group_ALC->AddSubItem(p_ALC);
	p_ALC_bandwidth = new CMFCPropertyGridProperty("ALC ����","�Զ�","ѡ��ALC����\r\nѡ��Զ���100 Hz,1 KHz,10 KHz,100 KHz",INSTR_ALC_BANDWIDTH);
	p_ALC_bandwidth->AddOption("�Զ�");
	p_ALC_bandwidth->AddOption("100Hz");
	p_ALC_bandwidth->AddOption("1KHz"); 
	p_ALC_bandwidth->AddOption("10KHz");
	p_ALC_bandwidth->AddOption("100KHz");
	p_ALC_bandwidth->AllowEdit(FALSE);
	p_group_ALC->AddSubItem(p_ALC_bandwidth);
	p_power_search_ref = new CMFCPropertyGridProperty("�����ο�","�̶�","ѡ����������״̬\r\nѡ��̶�������",INSTR_POWER_SEARCH_REF);
	p_power_search_ref->AddOption("�̶�");
	p_power_search_ref->AddOption("����");
	p_power_search_ref->AllowEdit(FALSE);
	p_power_search_ref->Enable(FALSE);
	p_group_ALC->AddSubItem(p_power_search_ref);
	p_RF_during_power_search = new CMFCPropertyGridProperty("�������","����","����RF��״̬������/��Сֵ",INSTR_RF_DURING_POWER_SEARCH);
	p_RF_during_power_search->AddOption("����");  
	p_RF_during_power_search->AddOption("��Сֵ"); 
	p_RF_during_power_search->AllowEdit(FALSE);
	p_RF_during_power_search->Enable(FALSE);
	p_group_ALC->AddSubItem(p_RF_during_power_search);
	p_power_search_method = new CMFCPropertyGridProperty("������ʽ","�ֶ�","���ù��������ķ�ʽ���ֶ�/�Զ�",INSTR_POWER_SEARCH_METHOD);
	p_power_search_method->AddOption("�ֶ�");  
	p_power_search_method->AddOption("�Զ�"); 
	p_group_ALC->AddSubItem(p_power_search_method);

	//5:���Ⲩ��
	p_ARB_clock_type = new CMFCPropertyGridProperty("ʱ������","�ڲ�","��������ʱ�ӵ����ͣ��ڲ�/�ⲿ",INSTR_ARB_CLOCK_TYPE);
	p_ARB_clock_type->AddOption("�ڲ�");
	p_ARB_clock_type->AddOption("�ⲿ");
	p_group_ARB->AddSubItem(p_ARB_clock_type);
	p_ARB_samp_clock = new CMFCPropertyGridProperty("����ʱ��","�Զ�","���ò���ʱ�ӵķ�ʽ���Զ�/�ֶ�",INSTR_ARB_SAMP_CLOCK);
	p_ARB_samp_clock->AddOption("�Զ�");
	p_ARB_samp_clock->AddOption("�ֶ�");
	p_group_ARB->AddSubItem(p_ARB_samp_clock);
	p_ARB_clock_freq = new CMFCPropertyGridProperty("����Ƶ��","200MHz","���ò���ʱ�ӵ�Ƶ��",INSTR_ARB_CLOCK_FREQ);
	p_group_ARB->AddSubItem(p_ARB_clock_freq);

	//6:������
	p_trigger_mod = new CMFCPropertyGridProperty("����ģʽ","����","���ô���ģʽ������|����|���ζ�|�ſ�",INSTR_TRIGGRT_MOD);
	p_trigger_mod->AddOption("����");
	p_trigger_mod->AddOption("����");
	p_trigger_mod->AddOption("���ζ�");
	p_trigger_mod->AddOption("�ſ�");
	p_group_Trigger->AddSubItem(p_trigger_mod);
	p_trigger_source = new CMFCPropertyGridProperty("����Դ","������","���ô���Դ��������|����|�ⲿ",INSTR_TRIGGRT_SRC);
	p_trigger_source->AddOption("������");
	p_trigger_source->AddOption("����");
	p_trigger_source->AddOption("�ⲿ");
	p_group_Trigger->AddSubItem(p_trigger_source);
	p_trigger_slope = new CMFCPropertyGridProperty("����","��","���ô������ԣ���|��",INSTR_TRIGGRT_SLOPE);
	p_trigger_slope->AddOption("��");
	p_trigger_slope->AddOption("��");
	p_group_Trigger->AddSubItem(p_trigger_slope);
	p_trigger_delay_active = new CMFCPropertyGridProperty("�ӳٿ���","��ʱ��","�򿪻�ر��ӳٿ��أ��ӳٿ�|�ӳٹ�",INSTR_TRIGGRT_DELAY_ACTIVE);
	p_trigger_delay_active->AddOption("�ӳٿ�");
	p_trigger_delay_active->AddOption("�ӳٹ�");
	p_group_Trigger->AddSubItem(p_trigger_delay_active);
	p_trigger_delay = new CMFCPropertyGridProperty("�����ӳ�","100us","���ô����ӳ�",INSTR_TRIGGRT_DELAY);
	p_group_Trigger->AddSubItem(p_trigger_delay);
	p_trigger_cont_type = new CMFCPropertyGridProperty("����","�Զ�","���������������ͣ��Զ�|����|ʵʱ",INSTR_TRIGGRT_CONT_TYPE);
	p_trigger_cont_type->AddOption("�Զ�");
	p_trigger_cont_type->AddOption("����");
	p_trigger_cont_type->AddOption("ʵʱ");
	p_group_Trigger->AddSubItem(p_trigger_cont_type);
	p_trigger_sing_type = new CMFCPropertyGridProperty("����","�����ظ�����","���õ��δ������ͣ������ظ�����|�����ظ�����|ʵʱ�ظ�����",INSTR_TRIGGRT_SING_TYPE);
	p_trigger_sing_type->AddOption("�����ظ�����");
	p_trigger_sing_type->AddOption("�����ظ�����");
	p_trigger_sing_type->AddOption("ʵʱ�ظ�����");
	p_trigger_sing_type->Enable(FALSE);
	p_group_Trigger->AddSubItem(p_trigger_sing_type);
	p_trigger_sadv_type = new CMFCPropertyGridProperty("���ζ�","����","���ò��ζδ������ͣ�����|����",INSTR_TRIGGRT_SADV_TYPE);
	p_trigger_sadv_type->AddOption("����");
	p_trigger_sadv_type->AddOption("����");
	p_trigger_sadv_type->Enable(FALSE);
	p_group_Trigger->AddSubItem(p_trigger_sadv_type);
	p_trigger_gate_type = new CMFCPropertyGridProperty("�ſ�","����Ч","�����ſش������ͣ�����Ч|����Ч",INSTR_TRIGGRT_GATE_TYPE);
	p_trigger_gate_type->AddOption("����Ч");
	p_trigger_gate_type->AddOption("����Ч");
	p_trigger_gate_type->Enable(FALSE);
	p_group_Trigger->AddSubItem(p_trigger_gate_type);

	//7:�����
	p_marker_state = new CMFCPropertyGridProperty("��ǿ���","On","���ñ�ǿ��أ�On/Off",INSTR_MARKER_STATE);
	p_marker_state->AddOption("On");
	p_marker_state->AddOption("Off");
	p_group_Marker->AddSubItem(p_marker_state);
	p_marker_xiaoyin = new CMFCPropertyGridProperty("��Ƶ��������","On","������Ƶ�����������أ�On/Off",INSTR_MARKER_XIAOYIN);
	p_marker_xiaoyin->AddOption("On");
	p_marker_xiaoyin->AddOption("Off");
	p_group_Marker->AddSubItem(p_marker_xiaoyin);
	p_marker_ALC_hold = new CMFCPropertyGridProperty("ALC����","On","����ALC���ֿ��أ�On/Off",INSTR_MARKER_ALC_HOLD);
	p_marker_ALC_hold->AddOption("On");
	p_marker_ALC_hold->AddOption("Off");
	p_group_Marker->AddSubItem(p_marker_ALC_hold);
	p_marker_no_1 = new CMFCPropertyGridProperty("���1����","On","���ñ��1���أ�On/Off",INSTR_MARKER_NO_1);
	p_marker_no_1->AddOption("��");
	p_marker_no_1->AddOption("��");
	p_marker_polar_no_1 = new CMFCPropertyGridProperty("���1����","��","���ñ��1���ԣ���/��",INSTR_MARKER_POLAR_NO_1);
	p_marker_polar_no_1->AddOption("��");
	p_marker_polar_no_1->AddOption("��");
	p_marker_no_2 = new CMFCPropertyGridProperty("���2����","On","���ñ��2���أ�On/Off",INSTR_MARKER_NO_2);
	p_marker_no_2->AddOption("��");
	p_marker_no_2->AddOption("��");
	p_marker_polar_no_2 = new CMFCPropertyGridProperty("���2����","��","���ñ��2���ԣ���/��",INSTR_MARKER_POLAR_NO_2);
	p_marker_polar_no_2->AddOption("��");
	p_marker_polar_no_2->AddOption("��");
	p_marker_no_3 = new CMFCPropertyGridProperty("���3����","On","���ñ��3���أ�On/Off",INSTR_MARKER_NO_3);
	p_marker_no_3->AddOption("��");
	p_marker_no_3->AddOption("��");
	p_marker_polar_no_3 = new CMFCPropertyGridProperty("���3����","��","���ñ��3���ԣ���/��",INSTR_MARKER_POLAR_NO_3);
	p_marker_polar_no_3->AddOption("��");
	p_marker_polar_no_3->AddOption("��");
	p_marker_no_4 = new CMFCPropertyGridProperty("���4����","On","���ñ��4���أ�On/Off",INSTR_MARKER_NO_4);
	p_marker_no_4->AddOption("��");
	p_marker_no_4->AddOption("��");
	p_marker_polar_no_4 = new CMFCPropertyGridProperty("���4����","��","���ñ��4���ԣ���/��",INSTR_MARKER_POLAR_NO_4);
	p_marker_polar_no_4->AddOption("��");
	p_marker_polar_no_4->AddOption("��");
	p_group_Marker->AddSubItem(p_marker_no_1);
	p_group_Marker->AddSubItem(p_marker_no_2);
	p_group_Marker->AddSubItem(p_marker_no_3);
	p_group_Marker->AddSubItem(p_marker_no_4);
	p_group_Marker->AddSubItem(p_marker_polar_no_1);
	p_group_Marker->AddSubItem(p_marker_polar_no_2);
	p_group_Marker->AddSubItem(p_marker_polar_no_3);
	p_group_Marker->AddSubItem(p_marker_polar_no_4);

	//8:ʵʱ������
	p_rt_noise_state = new CMFCPropertyGridProperty("��������","Off","����ʵʱ�����Ŀ���״̬��On/Off",INSTR_RT_NOISE);
	p_rt_noise_state->AddOption("On");
	p_rt_noise_state->AddOption("Off");
	p_rt_noise_state->AllowEdit(FALSE);
	p_group_RT_Noise->AddSubItem(p_rt_noise_state);
	p_carrier_to_noise_ratio = new CMFCPropertyGridProperty("�ز������","20.00 dB","���������",INSTR_CARRIER_TO_NOISE_RATIO);
	p_group_RT_Noise->AddSubItem(p_carrier_to_noise_ratio);
	p_carrier_bandwidth = new CMFCPropertyGridProperty("�ز�����","20.00 Mhz","�����ز��Ĵ���",INSTR_CARRIER_BANDWIDTH);
	p_group_RT_Noise->AddSubItem(p_carrier_bandwidth);
	p_noise_bandwidth = new CMFCPropertyGridProperty("��������","20.00 Mhz","���������Ĵ���",INSTR_NOISE_BANDWIDTH);
	p_group_RT_Noise->AddSubItem(p_noise_bandwidth);

	//p_group_RT_Noise->Expand(FALSE);


	/************************************************************************/
	/* ��������������뵽�����б�ҳ����                                     */
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
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CTabInstrument::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialogEx::OnOK();
}


void CTabInstrument::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	// TODO: �ڴ˴������Ϣ����������
	if (IsWindowVisible() || m_finished_ini)
	{
		m_MFCPropertyGrid_INSTRUMENT.MoveWindow(10,45,cx-32,cy-65);
		//m_MFCPropertyGrid_INSTRUMENT.Invalidate();
	}
	
}


void CTabInstrument::OnClickedBtnUpdateToInstrument()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ViUInt32  retCnt = 0;
	ViUInt32  maxlen = 100;
	ViStatus  status = 0;

	CString str;
	CString str_temp;
	/************************************************************************/
	/* ƴ�ӳ̿�������͵�����                                             */
	/************************************************************************/
	//1��������Ϣ

	//2����������
	str_temp = (CString)p_frequency->GetValue();
	str_temp.Remove(' ');
	str.Format("FREQ %s\n",str_temp);
	status = viWrite(vi,ViBuf(str.GetBuffer()),maxlen,&retCnt);//����Ƶ��(100k--67G)
	instr_params[m_combo_instrument_index.GetCurSel()].frequency = str_temp;
	Sleep(10);

	str_temp = p_amplitude->GetValue();
	str_temp.Remove(' ');
	str.Format("POW %s\n",str_temp);
	status = viWrite(vi,ViBuf(str.GetBuffer()),maxlen,&retCnt);//���ù���(-135dBm--30dBm)  Ĭ��0dbm
	instr_params[m_combo_instrument_index.GetCurSel()].amplitude = str_temp;
	Sleep(10);

	str_temp = p_RF_output->GetValue();
	str.Format("OUTP %s\n",str_temp);
	status = viWrite(vi,ViBuf(str.GetBuffer()),maxlen,&retCnt);//��Ƶ���� OUTP ON|OFF 1|0  Ĭ�Ϲ�
	instr_params[m_combo_instrument_index.GetCurSel()].RF_output = str_temp;
	Sleep(10);
	//3��IQ����
	//4��ALC����
	str_temp = p_ALC->GetValue();
	str.Format("POW:ALC:STAT %s\n",str_temp);
	status = viWrite(vi,ViBuf(str.GetBuffer()),maxlen,&retCnt);//��·״̬ POW:ALC:STAT ON(�ջ�)|OFF�������� Ĭ�ϱջ�
	instr_params[m_combo_instrument_index.GetCurSel()].ALC = str_temp;
	Sleep(10);
	//5��Dual ARB����
	//6��Dual ARB ��ǹ��߲���
	//7��Dual ARB ����������
	//8��ʵʱ��������
}


void CTabInstrument::OnClickedBtnUpdateFromInstrument()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CTabInstrument::OnClickedBtnPowerSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CTabInstrument::OnClickedBtnDcCal()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CTabInstrument::OnClickedBtnReset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CTabInstrument::OnSelchangeComboInstrumentIndex()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	/************************************************************************/
	/* ������ܻ�ȡvi������������������ʾ��������Ĳ���                   */
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

	int id_changed = pProp->GetData();//��ȡ��ǰֵ�����仯�����Ե�ID
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
				status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);//����Ƶ��(100k--67G)
				Sleep(10);
				status = viWrite(vi,(ViBuf)"FREQ?\n",256,&write_cnt);//��ѯʵ�ʵ�Ƶ��
				Sleep(10);
				status = viRead(vi,(ViBuf)ch,256,&read_cnt);//��ȡ�������ص�����
				ch[read_cnt-1] = '\0';
				str_temp.Format("%sHz",ch);
			}
			instr_params[m_combo_instrument_index.GetCurSel()].frequency = str_temp;
			pProp->SetValue(str_temp);
		}else{
			MessageBox("Ƶ����������");
		}
		break;
	case INSTR_AMPLITUDE:
		str_temp.Remove(' ');
		if (send_command_enabled)
		{
			str.Format("POW %s\n",str_temp);
			status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);//����Ƶ��(100k--67G)
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
			status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);//����Ƶ��(100k--67G)
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
			status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);//����Ƶ��(100k--67G)
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


