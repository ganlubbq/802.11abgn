#ifndef CONFIG_HARD
#define CONFIG_HARD

class config_hard
{

  private:
  protected:
  public:
	  CString freq;//������Ƶ ��GHzΪ��
	  CString power;//���� ��dbmΪ��λ
	  CString   RF_state;//��Ƶ����

	config_hard()
	{
		freq = "2.412GHz";
		power = "-30dBm";
		RF_state = "ON";
	};
	~config_hard(){};
};
#endif