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
	m_font.CreatePointFont(100,"΢���ź�");
	memset(ch,0,256);
	
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
	p_RF_output = new CMFCPropertyGridProperty("��Ƶ���","ON","�򿪻�ر���Ƶ���\r\nѡ�ON | OFF\r\nĬ��ֵ��OFF",INSTR_RF_OUTPUT);
	p_RF_output->AddOption("ON");
	p_RF_output->AddOption("OFF");
	p_RF_output->AllowEdit(FALSE);
	p_group_Basic->AddSubItem(p_RF_output);

	//3:IQ��
	p_IQ_adjustments = new CMFCPropertyGridProperty("I/Q ����","OFF","����I/Q������״̬��ON/OFF",INSTR_IQ_ADJUSTMENTS);
	p_IQ_adjustments->AddOption("ON");  
	p_IQ_adjustments->AddOption("OFF"); 
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
	p_ALC = new CMFCPropertyGridProperty("ALC","ON","����ALC��״̬��ON/OFF",INSTR_ALC);
	p_ALC->AddOption("ON");  
	p_ALC->AddOption("OFF"); 
	p_ALC->AllowEdit(FALSE);
	p_group_ALC->AddSubItem(p_ALC);
	p_ALC_bandwidth = new CMFCPropertyGridProperty("ALC ����","�Զ�","ѡ��ALC����\r\nѡ��Զ���100 Hz,1 KHz,10 KHz,100 KHz",INSTR_ALC_BANDWIDTH);
	p_ALC_bandwidth->AddOption("�Զ�");
	p_ALC_bandwidth->AddOption("100Hz");
	p_ALC_bandwidth->AddOption("1kHz"); 
	p_ALC_bandwidth->AddOption("10kHz");
	p_ALC_bandwidth->AddOption("100kHz");
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
	p_power_search_method->AllowEdit(FALSE);
	p_power_search_method->Enable(FALSE);
	p_group_ALC->AddSubItem(p_power_search_method);

	//5:���Ⲩ��
	p_ARB_samp_clock = new CMFCPropertyGridProperty("����ʱ��","�ڲ�","���ò���ʱ�ӵ����ͣ��ڲ�/�ⲿ",INSTR_ARB_CLOCK_TYPE);
	p_ARB_samp_clock->AddOption("�ڲ�");
	p_ARB_samp_clock->AddOption("�ⲿ");
	p_ARB_samp_clock->AllowEdit(FALSE);
	p_group_ARB->AddSubItem(p_ARB_samp_clock);
	p_ARB_clock_type = new CMFCPropertyGridProperty("����ʱ��","�Զ���","���ò���ʱ�ӵķ�ʽ������/���/�Զ���",INSTR_ARB_SAMP_CLOCK);
	p_ARB_clock_type->AddOption("����");
	p_ARB_clock_type->AddOption("���");
	p_ARB_clock_type->AddOption("�Զ���");
	p_ARB_clock_type->AllowEdit(FALSE);
	p_group_ARB->AddSubItem(p_ARB_clock_type);
	p_ARB_clock_freq = new CMFCPropertyGridProperty("����Ƶ��","100MHz","���ò���ʱ�ӵ�Ƶ��",INSTR_ARB_CLOCK_FREQ);
	p_group_ARB->AddSubItem(p_ARB_clock_freq);

	//6:������
	p_trigger_mod = new CMFCPropertyGridProperty("����ģʽ","����","���ô���ģʽ������|����|�ſ�",INSTR_TRIGGRT_MOD);
	p_trigger_mod->AddOption("����");
	p_trigger_mod->AddOption("����");
	p_trigger_mod->AddOption("�ſ�");
	p_trigger_mod->AllowEdit(FALSE);
	p_group_Trigger->AddSubItem(p_trigger_mod);
	p_trigger_cont_type = new CMFCPropertyGridProperty("����","ʵʱ","���������������ͣ��Զ�|����|ʵʱ",INSTR_TRIGGRT_CONT_TYPE);
	p_trigger_cont_type->AddOption("�Զ�");
	p_trigger_cont_type->AddOption("����");
	p_trigger_cont_type->AddOption("ʵʱ");
	p_trigger_cont_type->AllowEdit(FALSE);
	p_group_Trigger->AddSubItem(p_trigger_cont_type);
	/*p_trigger_sing_type = new CMFCPropertyGridProperty("����","�����ظ�����","���õ��δ������ͣ������ظ�����|�����ظ�����|ʵʱ�ظ�����",INSTR_TRIGGRT_SING_TYPE);
	p_trigger_sing_type->AddOption("�����ظ�����");
	p_trigger_sing_type->AddOption("�����ظ�����");
	p_trigger_sing_type->AddOption("ʵʱ�ظ�����");
	p_trigger_sing_type->Enable(FALSE);
	p_group_Trigger->AddSubItem(p_trigger_sing_type);*/
	/*p_trigger_sadv_type = new CMFCPropertyGridProperty("���ζ�","����","���ò��ζδ������ͣ�����|����",INSTR_TRIGGRT_SADV_TYPE);
	p_trigger_sadv_type->AddOption("����");
	p_trigger_sadv_type->AddOption("����");
	p_trigger_sadv_type->Enable(FALSE);
	p_group_Trigger->AddSubItem(p_trigger_sadv_type);*/
	p_trigger_gate_type = new CMFCPropertyGridProperty("�ſ�","����Ч","�����ſش������ͣ�����Ч|����Ч",INSTR_TRIGGRT_GATE_TYPE);
	p_trigger_gate_type->AddOption("����Ч");
	p_trigger_gate_type->AddOption("����Ч");
	p_trigger_gate_type->Enable(FALSE);
	p_trigger_gate_type->AllowEdit(FALSE);
	p_group_Trigger->AddSubItem(p_trigger_gate_type);
	p_trigger_source = new CMFCPropertyGridProperty("����Դ","������","���ô���Դ��������|����|�ⲿ",INSTR_TRIGGRT_SRC);
	p_trigger_source->AddOption("������");
	p_trigger_source->AddOption("����");
	p_trigger_source->AddOption("�ⲿ");
	p_trigger_source->AllowEdit(FALSE);
	p_group_Trigger->AddSubItem(p_trigger_source);
	p_trigger_slope = new CMFCPropertyGridProperty("����","��","���ô������ԣ���|��",INSTR_TRIGGRT_SLOPE);
	p_trigger_slope->AddOption("��");
	p_trigger_slope->AddOption("��");
	p_trigger_slope->AllowEdit(FALSE);
	p_trigger_slope->Enable(FALSE);
	p_group_Trigger->AddSubItem(p_trigger_slope);
	p_trigger_delay_active = new CMFCPropertyGridProperty("�ӳٿ���","��","�򿪻�ر��ӳٿ��أ��ӳٿ�|�ӳٹ�",INSTR_TRIGGRT_DELAY_ACTIVE);
	p_trigger_delay_active->AddOption("��");
	p_trigger_delay_active->AddOption("��");
	p_trigger_delay_active->AllowEdit(FALSE);
	p_trigger_delay_active->Enable(FALSE);
	p_group_Trigger->AddSubItem(p_trigger_delay_active);
	p_trigger_delay = new CMFCPropertyGridProperty("�����ӳ�","0 bit","���ô����ӳ�",INSTR_TRIGGRT_DELAY);
	p_trigger_delay->Enable(FALSE);
	p_trigger_delay->Enable(FALSE);
	p_group_Trigger->AddSubItem(p_trigger_delay);

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
	p_rt_noise_state = new CMFCPropertyGridProperty("��������","OFF","����ʵʱ�����Ŀ���״̬��ON/OFF",INSTR_RT_NOISE);
	p_rt_noise_state->AddOption("ON");
	p_rt_noise_state->AddOption("OFF");
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
	CWnd *pWnd = GetTopWindow();  
	while (NULL != pWnd)  
	{  
		pWnd->SetFont(&m_font);  
		pWnd = pWnd->GetNextWindow();  
	}  
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
	Instr = (((CMainFrame*)AfxGetMainWnd())->m_pass_to_thread).m_confighard;
	int id_changed = pProp->GetData();//��ȡ��ǰֵ�����仯�����Ե�ID
	CString str_temp = pProp->GetValue();
	CString str = "";

	ViUInt32 retCnt = 0;
	ViStatus status = 0;
	ViUInt32 read_cnt = 0;
	ViUInt32 write_cnt = 0;
	regex patten_freq("^\\d+(\\.\\d*)?[kmg]?(hz)?$",regex::icase);//������ʽ��֤���ݸ�ʽ�Ƿ���ȷ
	regex patten_amp("^[-]?\\d+(\\.\\d*)?(dbm)?$",regex::icase);
	regex patten_iqoffset("^[-]?\\d+(\\.\\d*)?(\\%)?$",regex::icase);
	regex patten_iqgainbalance("^[-]?\\d+(\\.\\d*)?(db)?$",regex::icase);
	regex patten_quad_deg_ad("^[-]?\\d+(\\.\\d*)?(deg)?$",regex::icase);
	regex patten_trig_delay("^\\d+$",regex::icase);
	regex patten_arb_clock_freq("^\\d+(\\.\\d*)?[mk]?(hz)?$",regex::icase);
	regex patten_noise_band("^\\d+(\\.\\d*)?[mk]?(hz)?$",regex::icase);
	bool match_result = false;
	switch(id_changed)
	{
	case INSTR_FREQUENCY:
		str_temp.Remove(' ');//�Ƴ��ո�
		match_result = regex_match(str_temp.GetBuffer(),patten_freq);//������֤Ƶ��
		if (match_result)
		{
			if (send_command_enabled)
			{
				str.Format("FREQ %s\n",str_temp);
				status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);//����Ƶ��(100k--67G)
				Sleep(10);
				status = viWrite(vi,(ViBuf)"FREQ?\n",256,&write_cnt);//��ѯʵ�ʵ�Ƶ��,�������õ�Ƶ����ʵ�������ϵ�Ƶ�ʲ�һ��
				Sleep(10);
				status = viRead(vi,(ViBuf)ch,256,&read_cnt);//��ȡ�������ص����ݣ���ʾ�������
				ch[read_cnt-1] = '\0';
				double real_freq = atof(ch);
				str_temp.Format("%f MHz",real_freq/1000000);
			}
			instr_params[m_combo_instrument_index.GetCurSel()].frequency = str_temp;
			Instr->freq = str_temp;
			pProp->SetValue(str_temp);
		}
		else
		{
			MessageBox("Ƶ����������");
		}
		break;
	case INSTR_AMPLITUDE:
		str_temp.Remove(' ');
		match_result = regex_match(str_temp.GetBuffer(),patten_amp);//������֤����
		if (match_result)
		{
			if (send_command_enabled)
			{
				str.Format("POW %s\n",str_temp);
				status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);//����Ƶ��(100k--67G)
				Sleep(10);
				status = viWrite(vi,(ViBuf)"POW?\n",256,&write_cnt);//��ѯʵ�ʵ�Ƶ��
				Sleep(10);
				status = viRead(vi,(ViBuf)ch,256,&read_cnt);//��ȡ�������ص�����
				ch[read_cnt-1] = '\0';
				str_temp.Format("%s dBm",ch);
			}
			instr_params[m_combo_instrument_index.GetCurSel()].amplitude = str_temp;
			Instr->power = str_temp;
			pProp->SetValue(str_temp);
		}
		else
		{
			MessageBox("������������");
		}
		break;
	case INSTR_RF_OUTPUT:
		str_temp.Remove(' ');
		if (send_command_enabled)
		{
			str.Format("OUTP %s\n",str_temp);
			status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);//����Ƶ��(100k--67G)
			Sleep(10);
			status = viWrite(vi,(ViBuf)"OUTP?\n",256,&write_cnt);//��ѯʵ�ʵ�Ƶ��
			Sleep(10);
			status = viRead(vi,(ViBuf)ch,256,&read_cnt);//��ȡ�������ص�����
			ch[read_cnt-1] = '\0';
			if (ch[0] == '1')
			{
				str_temp.Format("%s","ON");
			}
			else
			{
				str_temp.Format("%s","OFF");
			}
		}
		instr_params[m_combo_instrument_index.GetCurSel()].RF_output = str_temp;
		Instr->RF_state = str_temp;
		pProp->SetValue(str_temp);
		Sleep(10);
		break;
	case INSTR_IQ_ADJUSTMENTS:
		str_temp.Remove(' ');
		if (str_temp == "ON")//����IQ_group������
		{
			p_I_offset->Enable(TRUE);
			p_Q_offset->Enable(TRUE);
			p_IQ_gain_balance->Enable(TRUE);
			p_quadrature_angle_adjustment->Enable(TRUE);
		}
		else
		{
			p_I_offset->Enable(FALSE);
			p_Q_offset->Enable(FALSE);
			p_IQ_gain_balance->Enable(FALSE);
			p_quadrature_angle_adjustment->Enable(FALSE);
		}
		if (send_command_enabled)
		{
			str.Format("DM:IQAD:STAT %s\n",str_temp);
			status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);
			Sleep(10);
			status = viWrite(vi,(ViBuf)"DM:IQAD:STAT?\n",256,&write_cnt);
			Sleep(10);
			status = viRead(vi,(ViBuf)ch,256,&read_cnt);//��ȡ�������ص�����
			ch[read_cnt-1] = '\0';
			if (ch[0] == '1')
			{
				str_temp.Format("%s","ON");
				/*p_I_offset->Enable(TRUE);
				p_Q_offset->Enable(TRUE);
				p_IQ_gain_balance->Enable(TRUE);
				p_quadrature_angle_adjustment->Enable(TRUE);*/
			}
			else
			{
				str_temp.Format("%s","OFF");
				/*p_I_offset->Enable(FALSE);
				p_Q_offset->Enable(FALSE);
				p_IQ_gain_balance->Enable(FALSE);
				p_quadrature_angle_adjustment->Enable(FALSE);*/
			}
		}
		instr_params[m_combo_instrument_index.GetCurSel()].IQ_ADJ = str_temp;
		pProp->SetValue(str_temp);
		Sleep(10);
		break;
	case INSTR_I_OFFSET:
		str_temp.Remove(' ');
		match_result = regex_match(str_temp.GetBuffer(),patten_iqoffset);
		if (match_result)
		{
			if (send_command_enabled)
			{
				str.Format("DM:IQAD:IOFF %s\n",str_temp);
				status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);//����Iƫ�ã�-50%~+50%��
				Sleep(10);
				status = viWrite(vi,(ViBuf)"DM:IQAD:IOFF?\n",256,&write_cnt);//��ѯʵ��Iƫ��
				Sleep(10);
				status = viRead(vi,(ViBuf)ch,256,&read_cnt);//��ȡ�������ص�����
				ch[read_cnt-1] = '\0';
				double real_i_offset = atof(ch);
				str_temp.Format("%.3f%s",real_i_offset,"%");
			}
			instr_params[m_combo_instrument_index.GetCurSel()].I_offset = str_temp;
			pProp->SetValue(str_temp);
		}
		else
		{
			MessageBox("Iƫ����������");
		}
		break;
	case INSTR_Q_OFFSET:
		str_temp.Remove(' ');
		match_result = regex_match(str_temp.GetBuffer(),patten_iqoffset);
		if (match_result)
		{
			if (send_command_enabled)
			{
				str.Format("DM:IQAD:QOFF %s\n",str_temp);
				status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);//����Qƫ�ã�-50%~+50%��
				Sleep(10);
				status = viWrite(vi,(ViBuf)"DM:IQAD:QOFF?\n",256,&write_cnt);
				Sleep(10);
				status = viRead(vi,(ViBuf)ch,256,&read_cnt);
				ch[read_cnt-1] = '\0';
				double real_q_offset = atof(ch);
				str_temp.Format("%.3f%s",real_q_offset,"%");
			}
			instr_params[m_combo_instrument_index.GetCurSel()].Q_offset = str_temp;
			pProp->SetValue(str_temp);
		}
		else
		{
			MessageBox("Qƫ����������");
		}
		break;
	case INSTR_IQ_GAIN_BALANCE:
		str_temp.Remove(' ');
		match_result = regex_match(str_temp.GetBuffer(),patten_iqgainbalance);
		if (match_result)
		{
			if (send_command_enabled)
			{
				str.Format("DM:IQAD:GAIN %s\n",str_temp);
				status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);//����IQ���棨-4db~+4db��
				Sleep(10);
				status = viWrite(vi,(ViBuf)"DM:IQAD:GAIN?\n",256,&write_cnt);
				Sleep(10);
				status = viRead(vi,(ViBuf)ch,256,&read_cnt);
				ch[read_cnt-1] = '\0';
				double real_iq_gb = atof(ch);
				str_temp.Format("%.2f%s",real_iq_gb,"dB");
			}
			instr_params[m_combo_instrument_index.GetCurSel()].IQ_gain_balance = str_temp;
			pProp->SetValue(str_temp);
		}
		else
		{
			MessageBox("I/Q����ƽ����������");
		}
		break;
	case INSTR_QUADRATURE_ANGLE_ADJUST:
		str_temp.Remove(' ');
		match_result = regex_match(str_temp.GetBuffer(),patten_quad_deg_ad);
		if (match_result)
		{
			if (send_command_enabled)
			{
				str.Format("DM:IQAD:QSK %s\n",str_temp);
				status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);//��������ƫ�루-10.00deg~+10.00deg��
				Sleep(10);
				status = viWrite(vi,(ViBuf)"DM:IQAD:QSK?\n",256,&write_cnt);
				Sleep(10);
				status = viRead(vi,(ViBuf)ch,256,&read_cnt);
				ch[read_cnt-1] = '\0';
				double real_quadeg = atof(ch);
				str_temp.Format("%.2f%s",real_quadeg,"deg");
			}
			instr_params[m_combo_instrument_index.GetCurSel()].quadrature_angle_adjustment = str_temp;
			pProp->SetValue(str_temp);
		}
		else
		{
			MessageBox("����ƫ����������");
		}
		break;
	case INSTR_ALC://��ѡ����Ʋ��迼���������
		str_temp.Remove(' ');
		if (str_temp == "OFF")
		{
			p_power_search_method->Enable(TRUE);
			p_power_search_ref->Enable(TRUE);
		}
		else
		{
			p_power_search_method->Enable(FALSE);
			p_power_search_ref->Enable(FALSE);
		}
		if (send_command_enabled)
		{
			str.Format("POW:ALC:STAT %s\n",str_temp);
			status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);
		}
		instr_params[m_combo_instrument_index.GetCurSel()].ALC = str_temp;
		pProp->SetValue(str_temp);
		Sleep(10);
		break;
	case INSTR_ALC_BANDWIDTH://��ѡ����Ʋ��迼���������
		str_temp.Remove(' ');
		if (send_command_enabled)
		{
			if (str_temp == "�Զ�")
			{
				str.Format("POW:ALC:BAND:AUTO %s\n","ON");
				status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);
				Sleep(10);
				status = viWrite(vi,(ViBuf)"POW:ALC:BAND:AUTO?\n",256,&write_cnt);
				Sleep(10);
				status = viRead(vi,(ViBuf)ch,256,&read_cnt);
				ch[read_cnt-1] = '\0';
				if (ch[0] == '1')
				{
					str_temp.Format("%s","�Զ�");
				}
				instr_params[m_combo_instrument_index.GetCurSel()].ALC_band = "ON";
			}
			else
			{
				str.Format("POW:ALC:BAND:AUTO %s\n","OFF");
				status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);//ALC������Ϊ�ֶ�
				str.Format("POW:ALC:BAND %s\n",str_temp);//�ֶ�����ALC����
				status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);
				Sleep(10);
				status = viWrite(vi,(ViBuf)"POW:ALC:BAND?\n",256,&write_cnt);
				Sleep(10);
				status = viRead(vi,(ViBuf)ch,256,&read_cnt);
				ch[read_cnt-1] = '\0';
				str_temp.Format("%s", ch);
				instr_params[m_combo_instrument_index.GetCurSel()].ALC_band = str_temp;
			}
		}
		pProp->SetValue(str_temp);
		Sleep(10);
		break;
	case INSTR_POWER_SEARCH_REF:
		str_temp.Remove(' ');
		if (send_command_enabled)
		{
			if (str_temp == "�̶�")
				str.Format("POW:ALC:SEAR:REF %s\n","FIX");
			else
				str.Format("POW:ALC:SEAR:REF %s\n","MOD");
			status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);
		}
		instr_params[m_combo_instrument_index.GetCurSel()].ALC_search_ref = str_temp;
		pProp->SetValue(str_temp);
		Sleep(10);
		break;
	case INSTR_POWER_SEARCH_METHOD:
		str_temp.Remove(' ');
		if (send_command_enabled)
		{
			if (str_temp == "�ֶ�")
				str.Format("POW:ALC:SEAR %s\n","OFF");
			else
				str.Format("POW:ALC:SEAR %s\n","ON");
			status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);
		}
		instr_params[m_combo_instrument_index.GetCurSel()].ALC = str_temp;
		pProp->SetValue(str_temp);
		Sleep(10);
		break;
	case INSTR_ARB_SAMP_CLOCK://��ѡ����Ʋ��迼���������
		str_temp.Remove(' ');
		if (str_temp == "�Զ���")
			p_ARB_clock_freq->Enable(TRUE);
		else
			p_ARB_clock_freq->Enable(FALSE);
		if (send_command_enabled)
		{
			if (str_temp == "���ı�")
			{
				str.Format("RAD:ARB:SEQ:CLOCK %s\n","CURR");
				status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);
				instr_params[m_combo_instrument_index.GetCurSel()].ARB_clock_type = "���ı�";
			}
			else if (str_temp == "���")
			{
				str.Format("RAD:ARB:SEQ:CLOCK %s\n","HIGH");
				status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);
				instr_params[m_combo_instrument_index.GetCurSel()].ARB_clock_type = "���";
			}
			else
			{
				str.Format("RAD:ARB:SEQ:CLOCK %s\n","CUST");
				status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);
				instr_params[m_combo_instrument_index.GetCurSel()].ARB_clock_type = "�Զ���";
			}
		}
		pProp->SetValue(str_temp);
		Sleep(10);
		break;
	case INSTR_ARB_CLOCK_FREQ:
		str_temp.Remove(' ');//�Ƴ��ո�
		match_result = regex_match(str_temp.GetBuffer(),patten_arb_clock_freq);//������֤Ƶ��
		if (match_result)
		{
			if (send_command_enabled)
			{
				str.Format("RAD:ARB:SCL:RATE %s\n",str_temp);
				status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);//����ARBʱ��Ƶ��(0.01MHz--200MHz)
				Sleep(10);
				status = viWrite(vi,(ViBuf)"RAD:ARB:SCL:RATE?\n",256,&write_cnt);
				Sleep(10);
				status = viRead(vi,(ViBuf)ch,256,&read_cnt);
				ch[read_cnt-1] = '\0';
				double real_arb_freq = atof(ch);
				str_temp.Format("%.6f MHz",real_arb_freq/1000000);
			}
			instr_params[m_combo_instrument_index.GetCurSel()].ARB_clock_freq = str_temp;
			pProp->SetValue(str_temp);
		}
		else
		{
			MessageBox("ʱ��Ƶ����������");
		}
		break;
	case INSTR_TRIGGRT_MOD://��ѡ����Ʋ��迼���������
		str_temp.Remove(' ');
		if (str_temp == "����")
		{
			p_trigger_cont_type->Enable(TRUE);
			p_trigger_gate_type->Enable(FALSE);
		}
		else if (str_temp == "�ſ�")
		{
			p_trigger_cont_type->Enable(FALSE);
			p_trigger_gate_type->Enable(TRUE);
		}
		else
		{
			p_trigger_cont_type->Enable(FALSE);
			p_trigger_gate_type->Enable(FALSE);
		}
		if (send_command_enabled)
		{
			if (str_temp == "����")
			{
				str.Format("RAD:CUST:TRIG:TYPE %s\n","CONT");
				status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);
				instr_params[m_combo_instrument_index.GetCurSel()].TRIG_mode = "����";
			}
			else if (str_temp == "�ſ�")
			{
				str.Format("RAD:CUST:TRIG:TYPE %s\n","GATE");
				status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);
				instr_params[m_combo_instrument_index.GetCurSel()].TRIG_mode = "�ſ�";
			}
			else
			{
				str.Format("RAD:CUST:TRIG:TYPE %s\n","SING");
				status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);
				instr_params[m_combo_instrument_index.GetCurSel()].TRIG_mode = "����";
			}
		}
		pProp->SetValue(str_temp);
		Sleep(10);
		break;
	case INSTR_TRIGGRT_CONT_TYPE://��ѡ����Ʋ��迼���������
		str_temp.Remove(' ');
		if (send_command_enabled)
		{
			if (str_temp == "�Զ�")
			{
				str.Format("RAD:CUST:TRIG:TYPE:CONT:TYPE %s\n","FREE");
				status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);
				instr_params[m_combo_instrument_index.GetCurSel()].TRIG_mode_cont = "�Զ�";
			}
			else if (str_temp == "����")
			{
				str.Format("RAD:CUST:TRIG:TYPE:CONT:TYPE %s\n","TRIG");
				status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);
				instr_params[m_combo_instrument_index.GetCurSel()].TRIG_mode_cont = "����";
			}
			else
			{
				str.Format("RAD:CUST:TRIG:TYPE:CONT:TYPE %s\n","RES");
				status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);
				instr_params[m_combo_instrument_index.GetCurSel()].TRIG_mode_cont = "ʵʱ";
			}
		}
		pProp->SetValue(str_temp);
		Sleep(10);
		break;
	case INSTR_TRIGGRT_GATE_TYPE://��ѡ����Ʋ��迼���������
		str_temp.Remove(' ');
		if (send_command_enabled)
		{
			if (str_temp == "����Ч")
			{
				str.Format("RAD:CUST:TRIG:TYPE:GATE:ACT %s\n","HIGH");
				status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);
				instr_params[m_combo_instrument_index.GetCurSel()].TRIG_mode_cont = "����Ч";
			}
			else
			{
				str.Format("RAD:CUST:TRIG:TYPE:GATE:ACT %s\n","LOW");
				status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);
				instr_params[m_combo_instrument_index.GetCurSel()].TRIG_mode_cont = "����Ч";
			}
		}
		pProp->SetValue(str_temp);
		Sleep(10);
		break;
	case INSTR_TRIGGRT_SRC://��ѡ����Ʋ��迼���������
		str_temp.Remove(' ');
		if (str_temp == "������")
		{
			p_trigger_slope->Enable(FALSE);
			p_trigger_delay_active->Enable(FALSE);
			p_trigger_delay->Enable(FALSE);
		}
		else if (str_temp == "����")
		{
			p_trigger_slope->Enable(FALSE);
			p_trigger_delay_active->Enable(FALSE);
			p_trigger_delay->Enable(FALSE);
		}
		else
		{
			p_trigger_slope->Enable(TRUE);
			p_trigger_delay_active->Enable(TRUE);
			p_trigger_delay->Enable(TRUE);
		}
		if (send_command_enabled)
		{
			if (str_temp == "������")
			{
				str.Format("RAD:CUST:TRIG:SOUR %s\n","KEY");
				status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);
				instr_params[m_combo_instrument_index.GetCurSel()].TRIG_source = "������";
			}
			else if (str_temp == "����")
			{
				str.Format("RAD:CUST:TRIG:SOUR %s\n","BUS");
				status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);
				instr_params[m_combo_instrument_index.GetCurSel()].TRIG_source = "����";
			}
			else
			{
				str.Format("RAD:CUST:TRIG:SOUR %s\n","EXT");
				status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);
				instr_params[m_combo_instrument_index.GetCurSel()].TRIG_source = "�ⲿ";
			}
		}
		pProp->SetValue(str_temp);
		Sleep(10);
		break;
	case INSTR_TRIGGRT_SLOPE:
		str_temp.Remove(' ');
		if (send_command_enabled)
		{
			if (str_temp == "��")
				str.Format("RAD:CUST:TRIG:EXT:SOUR:SLOP %s\n","POS");
			else
				str.Format("RAD:CUST:TRIG:EXT:SOUR:SLOP %s\n","NEG");
			status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);
		}
		instr_params[m_combo_instrument_index.GetCurSel()].TRIG_EXT_slope = str_temp;
		pProp->SetValue(str_temp);
		Sleep(10);
		break;
	case INSTR_TRIGGRT_DELAY_ACTIVE:
		str_temp.Remove(' ');
		if (str_temp == "��")
			p_trigger_delay->Enable(TRUE);
		else
			p_trigger_delay->Enable(FALSE);
		if (send_command_enabled)
		{
			if (str_temp == "��")
				str.Format("RAD:CUST:TRIG:EXT:DEL:STAT %s\n","ON");
			else
				str.Format("RAD:CUST:TRIG:EXT:DEL:STAT %s\n","OFF");
			//str.Format("RAD:CUST:TRIG:EXT:DEL:STAT %s\n",str_temp);
			status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);
		}
		instr_params[m_combo_instrument_index.GetCurSel()].TRIG_EXT_delay_switch = str_temp;
		pProp->SetValue(str_temp);
		Sleep(10);
		break;
	case INSTR_TRIGGRT_DELAY:
		str_temp.Remove(' ');
		match_result = regex_match(str_temp.GetBuffer(),patten_trig_delay);
		if (match_result)
		{
			if (send_command_enabled)
			{
				str.Format("RAD:CUST:TRIG:EXT:SOUR:DEL %s\n",str_temp);
				status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);//���ô����ӳ�:��С���㣬��λbit
				Sleep(10);
				status = viWrite(vi,(ViBuf)"RAD:CUST:TRIG:EXT:SOUR:DEL?\n",256,&write_cnt);
				Sleep(10);
				status = viRead(vi,(ViBuf)ch,256,&read_cnt);
				ch[read_cnt-1] = '\0';
				int real_trig_delay = atoi(ch);
				str_temp.Format("%d bit",real_trig_delay);
			}
			instr_params[m_combo_instrument_index.GetCurSel()].TRIG_EXT_delay = str_temp;
			pProp->SetValue(str_temp);
		}
		else
		{
			MessageBox("�����ӳ���������");
		}
		break;
	case INSTR_RT_NOISE:
		str_temp.Remove(' ');
		if (send_command_enabled)
		{
			if (str_temp == "OFF")
				str.Format("RAD:AWGN:ARB %s\n","OFF");
			else
				str.Format("RAD:AWGN:ARB %s\n","ON");
			status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);
		}
		instr_params[m_combo_instrument_index.GetCurSel()].AWGN_state = str_temp;
		pProp->SetValue(str_temp);
		Sleep(10);
		break;
	case INSTR_NOISE_BANDWIDTH:
		str_temp.Remove(' ');//�Ƴ��ո�
		match_result = regex_match(str_temp.GetBuffer(),patten_noise_band);
		if (match_result)
		{
			if (send_command_enabled)
			{
				str.Format("RAD:AWGN:ARB:BWID %s\n",str_temp);
				status = viWrite(vi,ViBuf(str.GetBuffer()),256,&retCnt);//������������(0.001Mhz~160Mhz)
				Sleep(10);
				status = viWrite(vi,(ViBuf)"RAD:AWGN:ARB:BWID?\n",256,&write_cnt);
				Sleep(10);
				status = viRead(vi,(ViBuf)ch,256,&read_cnt);
				ch[read_cnt-1] = '\0';
				double real_noise_band = atof(ch);
				str_temp.Format("%.9f Mhz",real_noise_band/1000000);
			}
			instr_params[m_combo_instrument_index.GetCurSel()].Noise_band = str_temp;
			pProp->SetValue(str_temp);
		}
		else
		{
			MessageBox("����������������");
		}
		break;
	default:
		break;
	}
	//SetFocus();

	//CString str;
	//str.Format("%d",pProp->GetData());

	//MessageBox(str);
	return 0;}


