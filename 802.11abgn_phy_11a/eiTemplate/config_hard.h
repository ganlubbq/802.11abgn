#ifndef CONFIG_HARD
#define CONFIG_HARD

class config_hard
{

  private:
  protected:
  public:
	  CString freq;//仪器载频 以GHz为例
	  CString power;//功率 以dbm为单位
	  CString   RF_state;//射频开关

	config_hard()
	{
		freq = "2.412GHz";
		power = "-30dBm";
		RF_state = "ON";
	};
	~config_hard(){};
};
#endif