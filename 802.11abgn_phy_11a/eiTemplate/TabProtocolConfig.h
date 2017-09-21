#pragma once
#include "config.h"
#include "protocol/11a/configA.h"
#include "protocol/11b/configB.h"
#include "protocol/11g/configG.h"
#include "protocol/11n/InterfaceClass.h"
#include "afxwin.h"
#include "MPDUGeneral.h"
// CTabProtocolConfig �Ի���

class CTabProtocolConfig : public CDialog
{
	DECLARE_DYNAMIC(CTabProtocolConfig)

public:
	CTabProtocolConfig(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabProtocolConfig();

// �Ի�������
	enum { IDD = IDD_TAB_PROTOCOL_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnPropertyChanged(__in WPARAM wparam,__in LPARAM lparam);
	void update();//��ʾ�б����
	void Point();
	BOOL m_finished_ini;
public:
	config		*m_configIndex;
	configA     *m_configAIndex;
	configB     *m_configBIndex;
	configG     *m_configGIndex;
	configN     *m_configNIndex;
	CFont       m_font;
	CListCtrl   m_MpduInfoList;
	int         nMPDU;            //ͳ��MPDU����
	//11a
	CMFCPropertyGridCtrl     m_MFCPropertyGridThree;
	CMFCPropertyGridProperty *pGroup31;//�ز���Ϣ
	CMFCPropertyGridProperty *pGroup32;//���Ʊ���
	CMFCPropertyGridProperty *pGroup33;//�غ�����
	CMFCPropertyGridProperty *pGroup34;//Ƶ�׿���
	CMFCPropertyGridProperty *pGroup35;//�ŵ�

	CMFCPropertyGridProperty *pPropT1;//Э������
	CMFCPropertyGridProperty *pPropT2;//֡��
	CMFCPropertyGridProperty *pPropT3;//Ƶ��ƫ��
	CMFCPropertyGridProperty *pPropT3a;//֡����
	CMFCPropertyGridProperty *pPropT3b;//���ز�����
	CMFCPropertyGridProperty *pPropT4;//����
	CMFCPropertyGridProperty *pPropT5;//���Ʒ�ʽ
	CMFCPropertyGridProperty *pPropT6;//���뷽ʽ
	CMFCPropertyGridProperty *pPropT7;//����
	CMFCPropertyGridProperty *pPropT8;//��֯
	CMFCPropertyGridProperty *pPropT9;//OFDM��Ƶ��
	CMFCPropertyGridProperty *pPropT10;//PSDU
	CMFCPropertyGridProperty *pPropT11;//PPDU
	CMFCPropertyGridProperty *pPropT12;//MAC	
	CMFCPropertyGridProperty *pPropT13;//FCS
	CMFCPropertyGridProperty *pPropT14;//�˲���
	CMFCPropertyGridProperty *filter_user;//�û��Զ����˲���
	CMFCPropertyGridProperty *lp_filter_len;
	CMFCPropertyGridProperty *lp_filter_wn;
	CMFCPropertyGridProperty *gauss_filter_len;
	CMFCPropertyGridProperty *gauss_filter_BT;
	CMFCPropertyGridProperty *cosine_filter_len;
	CMFCPropertyGridProperty *cosine_filter_alpha;
	CMFCPropertyGridProperty *pPropT15;//���ڳ���
	CMFCPropertyGridProperty *pPropT16;//�ŵ�״̬
    CMFCPropertyGridProperty *pPropT17;//�ŵ��ྶ��
	CMFCPropertyGridProperty *pPropT18;//�ŵ���Ƶ
	CMFCPropertyGridProperty *pPropT19;//�ƶ��ٶ�
	CMFCPropertyGridProperty *pPropT20;//Eb/N0
	CMFCPropertyGridProperty *pPropT017;//OFDM��������ʼֵ
	CMFCPropertyGridProperty *p_data_source;//����Դ
	CMFCPropertyGridProperty *p_data_filepath;//�ļ�·��
	CMFCPropertyGridProperty *p_date_max_len;//������󳤶�
	//11n
	CMFCPropertyGridCtrl     m_MFCPropertyGridThreeN;
	CMFCPropertyGridProperty *pGroup36;//���ݰ�
	CMFCPropertyGridProperty *pGroup37;//���Ʊ���
	CMFCPropertyGridProperty *pGroup38;//�غ�����
	CMFCPropertyGridProperty *pGroup39;//Ƶ�׿���
	CMFCPropertyGridProperty *pGroup40;//�ŵ�
	CMFCPropertyGridProperty *pGroup41;

	CMFCPropertyGridProperty *pPropT21;//����
	CMFCPropertyGridProperty *pPropT211;//���ݸ���
	CMFCPropertyGridProperty *pPropT22;//MCS������
	CMFCPropertyGridProperty *pPropT23a;//���Ʒ�ʽ��1
	CMFCPropertyGridProperty *pPropT23b;//���Ʒ�ʽ��2
	CMFCPropertyGridProperty *pPropT23c;//���Ʒ�ʽ��3
	CMFCPropertyGridProperty *pPropT23d;//���Ʒ�ʽ��4
	CMFCPropertyGridProperty *pPropT24;//����
	CMFCPropertyGridProperty *pPropT25;//��������
	CMFCPropertyGridProperty *pPropT25a;//Nss
	CMFCPropertyGridProperty *pPropT25b;//STBC
	CMFCPropertyGridProperty *pPropT25c;//Nsts
	CMFCPropertyGridProperty *pPropT25d;//Ness
	CMFCPropertyGridProperty *pPropT26;//����������Ŀ
	CMFCPropertyGridProperty *pPropT27;//��չ�ռ���
	CMFCPropertyGridProperty *pPropT28;//�������
	CMFCPropertyGridProperty *pPropT288;//ʱ��Ӵ�
	CMFCPropertyGridProperty *pPropT29;//��������
	CMFCPropertyGridProperty *pPropT30;//�ռ�ӳ�����
	CMFCPropertyGridProperty *pPropT31;//�ŵ�����
	CMFCPropertyGridProperty *pPropT32;//��֯
	CMFCPropertyGridProperty *pPropT32a;//����
	CMFCPropertyGridProperty *pPropT33;//�ۺ�MPDU
	CMFCPropertyGridProperty *pPropT34;//Smoothing
	CMFCPropertyGridProperty *pPropT35;//Sounding
	CMFCPropertyGridProperty *pPropT36;//���ݳ���
	CMFCPropertyGridProperty *pPropT37;//����
	CMFCPropertyGridProperty *pPropT38;//ʱ��Ӵ�
	CMFCPropertyGridProperty *pPropT39;//�ŵ�ģ��
	CMFCPropertyGridProperty *pPropT40;//����ѡ��
	CMFCPropertyGridProperty *pPropT41;////˥������
	CMFCPropertyGridProperty *pPropT42;//�ز�Ƶ��
	CMFCPropertyGridProperty *numofNr;
	CMFCPropertyGridProperty *numofNt;
	CMFCPropertyGridProperty *p_data_filepath_n;//�ļ�·��
	CMFCPropertyGridProperty *fitertype_n;
	CMFCPropertyGridProperty *lp_filter_len_n;
	CMFCPropertyGridProperty *lp_filter_wn_n;
	CMFCPropertyGridProperty *gauss_filter_len_n;
	CMFCPropertyGridProperty *gauss_filter_BT_n;
	CMFCPropertyGridProperty *cosine_filter_len_n;
	CMFCPropertyGridProperty *cosine_filter_alpha_n;
	CMFCPropertyGridProperty *filter_user_n;

	//11nLegacyģʽ
	CMFCPropertyGridCtrl     m_MFCPropertyGridThreeNL;
	CMFCPropertyGridProperty *pGroup47;//���Ʊ���
	CMFCPropertyGridProperty *pGroup48;//�غ�����
	CMFCPropertyGridProperty *pGroup49;//Ƶ�׿���
	CMFCPropertyGridProperty *pGroup50;//�ŵ�

	CMFCPropertyGridProperty *pPropT43;//����
	CMFCPropertyGridProperty *pPropT44;//MCS������
	CMFCPropertyGridProperty *pPropT45;//���Ʒ�ʽ
	CMFCPropertyGridProperty *pPropT46;//����
	CMFCPropertyGridProperty *pPropT47;//��������
	CMFCPropertyGridProperty *pPropT48;//�����ʼֵ
	CMFCPropertyGridProperty *pPropT49;//�ŵ�����
	CMFCPropertyGridProperty *pPropT50;//��֯
	CMFCPropertyGridProperty *pPropT51;//�ۺ�MPDU
	CMFCPropertyGridProperty *pPropT52;//Smoothing
	CMFCPropertyGridProperty *pPropT53;//Sounding
	CMFCPropertyGridProperty *pPropT54;//����Դ
	CMFCPropertyGridProperty *pPropT55;//���ݳ���
	CMFCPropertyGridProperty *pPropT56;//ʱ��Ӵ�
	CMFCPropertyGridProperty *pPropT57;//�ŵ�ģ��
	CMFCPropertyGridProperty *pPropT58;//����ѡ��
	CMFCPropertyGridProperty *pPropT59;//˥������
	CMFCPropertyGridProperty *pPropT60;//�ز�Ƶ��
	CMFCPropertyGridProperty *p_data_filepath_nl;//�ļ�·��
	CMFCPropertyGridProperty *mobilespeed;
	CMFCPropertyGridProperty *carrierfreq;
	CMFCPropertyGridProperty *fitertype_nl;
	CMFCPropertyGridProperty *lp_filter_len_nl;
	CMFCPropertyGridProperty *lp_filter_wn_nl;
	CMFCPropertyGridProperty *gauss_filter_len_nl;
	CMFCPropertyGridProperty *gauss_filter_BT_nl;
	CMFCPropertyGridProperty *cosine_filter_len_nl;
	CMFCPropertyGridProperty *cosine_filter_alpha_nl;
	CMFCPropertyGridProperty *filter_user_nl;

	//11b
	CMFCPropertyGridCtrl     m_MFCPropertyGridThreeB;
	CMFCPropertyGridProperty *pGroup42;//�ز�����
	CMFCPropertyGridProperty *pGroup43;//���Ʊ���
	CMFCPropertyGridProperty *pGroup44;//�غ�����
	CMFCPropertyGridProperty *pGroup45;//�ŵ�
	CMFCPropertyGridProperty *pGroup46;

	CMFCPropertyGridProperty *pPropT61;//Э������
	CMFCPropertyGridProperty *pPropT62;//֡��
	CMFCPropertyGridProperty *pPropT63;//֡���
	CMFCPropertyGridProperty *pPropT64;//Ƶ��ƫ��
	CMFCPropertyGridProperty *pPropT65;//��Թ���
	CMFCPropertyGridProperty *pPropT66;//����ģʽ
	CMFCPropertyGridProperty *pPropT67;//��������
	CMFCPropertyGridProperty *pPropT68;//���Է�ʽ
	CMFCPropertyGridProperty *pPropT69;//����
	CMFCPropertyGridProperty *pPropT690;//�����ʼֵ
	CMFCPropertyGridProperty *pPropT70;//ǰ��������
	//CMFCPropertyGridProperty *pPropT71;//MPDU����
	CMFCPropertyGridProperty *pPropT72;//���ݳ���
	CMFCPropertyGridProperty *pPropT73;//MACͷ��
	CMFCPropertyGridProperty *pPropT74;//MAC FCS
	CMFCPropertyGridProperty *fitertype;
	CMFCPropertyGridProperty *lp_filter_len_b;
	CMFCPropertyGridProperty *lp_filter_wn_b;
	CMFCPropertyGridProperty *gauss_filter_len_b;
	CMFCPropertyGridProperty *gauss_filter_BT_b;
	CMFCPropertyGridProperty *cosine_filter_len_b;
	CMFCPropertyGridProperty *cosine_filter_alpha_b;
	CMFCPropertyGridProperty *filter_user_b;
	
	//11g
	CMFCPropertyGridCtrl     m_MFCPropertyGridThreeG;
	CMFCPropertyGridProperty *pGroup51;//�ز�����
	CMFCPropertyGridProperty *pGroup52;//���Ʊ��� ��Ӧ11a
	CMFCPropertyGridProperty *pGroup55;//���Ʊ��� ��Ӧ11b
	CMFCPropertyGridProperty *pGroup53;//�غ�����
	CMFCPropertyGridProperty *pGroup54;//�ŵ�

	CMFCPropertyGridProperty *pPropT75;//Э������
	CMFCPropertyGridProperty *pPropT76;//֡��
	CMFCPropertyGridProperty *pPropT77;//֡���
	CMFCPropertyGridProperty *pPropT78;//Ƶ��ƫ��
	CMFCPropertyGridProperty *pPropT79;//��Թ���
	CMFCPropertyGridProperty *pPropT80;//����ģʽ
	CMFCPropertyGridProperty *p_data_source_g;//MPDU����
	CMFCPropertyGridProperty *p_data_filepath_g;
	CMFCPropertyGridProperty *pPropT16_g;
	CMFCPropertyGridProperty *pPropT17_g;
	CMFCPropertyGridProperty *pPropT18_g;
	CMFCPropertyGridProperty *pPropT19_g;
	CMFCPropertyGridProperty *fitertype_g;
	CMFCPropertyGridProperty *lp_filter_len_g;
	CMFCPropertyGridProperty *lp_filter_wn_g;
	CMFCPropertyGridProperty *gauss_filter_len_g;
	CMFCPropertyGridProperty *gauss_filter_BT_g;
	CMFCPropertyGridProperty *cosine_filter_len_g;
	CMFCPropertyGridProperty *cosine_filter_alpha_g;
	CMFCPropertyGridProperty *filter_user_g;
	//���Ʊ��� ��Ӧ11b
	CMFCPropertyGridProperty *pPropT81;//��������
	CMFCPropertyGridProperty *pPropT82;//���Ʒ�ʽ
	CMFCPropertyGridProperty *pPropT83;//����
	CMFCPropertyGridProperty *pPropT84;//ǰ��������
	CMFCPropertyGridProperty *p_data_source_b;//MPDU����
	CMFCPropertyGridProperty *p_data_filepath_b;
	CMFCPropertyGridProperty *pPropT86;//���ݳ���
	CMFCPropertyGridProperty *pPropT87;//MACͷ��
	CMFCPropertyGridProperty *pPropT88;//MAC FCS
	CMFCPropertyGridProperty *pPropT16_b;
	CMFCPropertyGridProperty *pPropT17_b;
	CMFCPropertyGridProperty *pPropT18_b;
	CMFCPropertyGridProperty *pPropT19_b;
	//���Ʊ��� ��Ӧ11a
	CMFCPropertyGridProperty *pPropT89;//���뷽ʽ 
	CMFCPropertyGridProperty *pPropT90;//����
	CMFCPropertyGridProperty *pPropT91;//��֯
	CMFCPropertyGridProperty *pPropT92;//OFDM������
	CMFCPropertyGridProperty *pPropT93;//OFDM��������ʼֵ
	CMFCPropertyGridProperty *pPropT94;//ǰ��������
	CMFCPropertyGridProperty *pPropT95;//���Ʒ�ʽ
	CMFCPropertyGridProperty *pPropT96;//���ز���

public:
	CButton m_MPDUAdd;
	CButton m_MPDUDelete;
	int     NumOfMPDU;
	CMPDUGeneral* m_mpdu_general;
	afx_msg void OnBnClickedMpdudelete();
	afx_msg void OnBnClickedMpduadd();
	afx_msg void OnDblclkListMpdu(NMHDR *pNMHDR, LRESULT *pResult);
};
class CMFCPropertyGridPropertyButton : public CMFCPropertyGridProperty
{
public:  
	CMFCPropertyGridPropertyButton(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
		LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL, LPCTSTR lpszValidChars = NULL):  
	CMFCPropertyGridProperty(strName,varValue,lpszDescr,dwData)  
	{}  

	virtual ~CMFCPropertyGridPropertyButton()  
	{}  

	virtual BOOL HasButton() const;  

	virtual void OnClickButton(CPoint point);  
protected:  
private:  
};
class CMFCPropertyGridPropertyButton2 : public CMFCPropertyGridProperty
{
public:  
	CMFCPropertyGridPropertyButton2(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
		LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL, LPCTSTR lpszValidChars = NULL):  
	CMFCPropertyGridProperty(strName,varValue,lpszDescr,dwData)  
	{}  

	virtual ~CMFCPropertyGridPropertyButton2()  
	{}  

	virtual BOOL HasButton() const;  

	virtual void OnClickButton(CPoint point);  
protected:  
private:  
};
