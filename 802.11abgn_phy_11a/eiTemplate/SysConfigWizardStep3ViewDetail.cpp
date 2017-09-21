// SysConfigWizardStep3ViewDetail.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "eiTemplate.h"
#include "SysConfigWizardStep3ViewDetail.h"
#include "afxdialogex.h"
#include "SysConfigWizard.h"
#include "SysConfigWizardStep3.h"

using namespace std;

// CSysConfigWizardStep3ViewDetail �Ի���

IMPLEMENT_DYNAMIC(CSysConfigWizardStep3ViewDetail, CDialog)

CSysConfigWizardStep3ViewDetail::CSysConfigWizardStep3ViewDetail(CWnd* pParent /*=NULL*/)
	: CDialog(CSysConfigWizardStep3ViewDetail::IDD, pParent)
{
	m_font_content.CreatePointFont(90,"΢���ź�");
	m_file_dir = "";
	m_file_name = "";
}

CSysConfigWizardStep3ViewDetail::~CSysConfigWizardStep3ViewDetail()
{
}

void CSysConfigWizardStep3ViewDetail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSysConfigWizardStep3ViewDetail, CDialog)
END_MESSAGE_MAP()


// CSysConfigWizardStep3ViewDetail ��Ϣ�������


BOOL CSysConfigWizardStep3ViewDetail::OnInitDialog()
{
	using namespace rapidxml;
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	/* ����ȷ����ť������*/
	CButton* p_btn_ok = ((CButton*)GetDlgItem(IDOK));
	p_btn_ok->SetFont(&m_font_content);
	//����������Ϣ��ʾ����
	CRect rc;
	GetClientRect(&rc);
	rc.bottom -= 35;
	rc.left += 1;
	rc.right -= 1;
	rc.top += 1;
	//������Tabҳ
	m_content_instr_config.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,rc,this,PROPERTYGRID_INSTRUMENT_CONFIG);
	m_content_instr_config.EnableHeaderCtrl(FALSE,"����","ֵ");
	m_content_instr_config.SetVSDotNetLook();
	m_content_instr_config.MarkModifiedProperties();
	m_content_instr_config.SetAlphabeticMode(false); 
	m_content_instr_config.SetShowDragContext();
	m_content_instr_config.SetFont(&m_font_content);

	CMFCPropertyGridProperty *p_group_info = new CMFCPropertyGridProperty("������Ϣ");

	/************************************************************************/
	/* ȷ����ǰѡ��������ļ����ڵ��ļ��к�·��                             */
	/************************************************************************/
	m_file_dir.Append(m_file_name);
	m_file_dir.Append(".xml");/*./user/Instr_Sel_%d/����1.xml*/
	//m_option_dir
	/************************************************************************/
	/* ����xml�ĵ��������ĵ�������ˢ����ʾҳ�������                        */
	/************************************************************************/
	CMFCPropertyGridProperty* p_instr_group_array[8];//���������Ϣ
	CMFCPropertyGridProperty* p_prop_name;//����
	CMFCPropertyGridProperty* p_prop_desc;//����
	CMFCPropertyGridProperty* p_prop_array_instr[5];//ÿ��������Ӧ��5��С��Ŀ
    
	//��׼rapidxml��ȡ
	file<> fdoc(m_file_dir.GetBuffer());
	xml_document<> doc;
	doc.parse<0>(fdoc.data());

	// ��ȡ���ڵ�
	xml_node<>* p_root = doc.first_node();
	// ���ڵ��һ���ڵ���InstrumentsInfo,���а����������ļ������ƺ����õ�����
	xml_node<>* p_instrinfo_node = p_root->first_node();
	// ��������
	xml_node<>* p_config_name = p_instrinfo_node->first_node();
	p_prop_name = new CMFCPropertyGridProperty("����",p_config_name->value());
	p_prop_name->Enable(FALSE);
	p_group_info->AddSubItem(p_prop_name);
	// ��������
	xml_node<>* p_config_desc = p_instrinfo_node->last_node();
	p_prop_desc = new CMFCPropertyGridProperty("����",p_config_desc->value());
	p_prop_desc->Enable(FALSE);
	p_group_info->AddSubItem(p_prop_desc);

	m_content_instr_config.AddProperty(p_group_info);

	// ��Ϊ�����������ɱ䣬����Ҫͨ������ķ����Զ�ȷ����������������
	// next_sibling()��ȡ��ͬ���㼶�е���һ���ڵ�
	CString content;
	int i=0;
	for (xml_node<> *node = p_instrinfo_node->next_sibling();node;node = node->next_sibling(),i++)
	{
		// ÿִ��һ��ѭ������Ҫ����һ�������ķ���

		content.Format("���� NO.%d �������飺",i+1);
		p_instr_group_array[i] = new CMFCPropertyGridProperty(content);
		// �����������Ͳ���̬��������
		xml_node<>* p_instr_type = node->first_node();
		p_prop_array_instr[0] = new CMFCPropertyGridProperty("��������",p_instr_type->value());
		p_prop_array_instr[0]->Enable(FALSE);
		p_instr_group_array[i]->AddSubItem(p_prop_array_instr[0]);
		// ������������״̬����̬��������
		xml_node<>* p_connection = p_instr_type->next_sibling();
		p_prop_array_instr[1] = new CMFCPropertyGridProperty("������Ϣ",p_connection->value());
		p_prop_array_instr[1]->Enable(FALSE);
		p_instr_group_array[i]->AddSubItem(p_prop_array_instr[1]);
		// ��������Model Number����̬��������
		xml_node<>* p_model_number = p_connection->next_sibling();
		p_prop_array_instr[2] = new CMFCPropertyGridProperty("Model Number",p_model_number->value());
		p_prop_array_instr[2]->Enable(FALSE);
		p_instr_group_array[i]->AddSubItem(p_prop_array_instr[2]);
		// ��������Serial Number����̬��������
		xml_node<>* p_serial_number = p_model_number->next_sibling();
		p_prop_array_instr[3] = new CMFCPropertyGridProperty("Serial Number",p_serial_number->value());
		p_prop_array_instr[3]->Enable(FALSE);
		p_instr_group_array[i]->AddSubItem(p_prop_array_instr[3]);
		// ��������Firmware Revision����̬��������
		xml_node<>* p_firmware_revision = p_serial_number->next_sibling();
		p_prop_array_instr[4] = new CMFCPropertyGridProperty("Firmware Revision",p_firmware_revision->value());
		p_prop_array_instr[4]->Enable(FALSE);
		p_instr_group_array[i]->AddSubItem(p_prop_array_instr[4]);

		m_content_instr_config.AddProperty(p_instr_group_array[i]);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
