#ifndef SIGNALSOURCE_H
#define SIGNALSOURCE_H

/*******************************************************************
 *  �ļ�����: SignalSource.h
 *  ��Ҫ����: 
 *    ������������ 4 ����Դ(PN9 PN15 ȫ0 ���ļ���),
 *    ��������,�����vector<int>���͵�Դ,����׼�ĸ�ʽӦ�����BYTEԴ
 *   
 *  ��������: 2016.06.21
 *  ����: xingxin
 *  ˵��: ������������Դ�����д,��ԭ���������߼��������ʽ�����Ż�
 ******************************************************************/

#include <fstream>
#include <vector>
using namespace std;

/** 
 *  ��������: ����ѡȡ��ģʽ�����ݳ��ȵ���Ϣ������Դ
 *  @param mode ����ģʽѡ��(0:PN9 1:PN15 2:All0 3:�ļ���ȡ)
 *  @param length ���ݳ���(01����λ��)
 *  @param seed ���������
 *  @param filename ������ɾ���·����ʶ���ļ�·��,�ļ��Ƽ�ʹ��ASCII��ʽ����,���ⲻ��Ҫ�Ķ�ȡ�鷳
 *   
 *  @return src ����vector<int>������Դ
 */  
vector<int> GenerateSource(int mode=0,int length=64, int seed=10, const char* filename=NULL);

/** 
 *  ��������: ����PN9��Դ
 *  @param length ���ݳ���(01����λ��)
 *  @param seed ���������
 *   
 *  @return src ����vector<int>������Դ
 */  
vector<int> PN9(int length = 64, int seed = 10);

/** 
 *  ��������: ����PN15��Դ
 *  @param length ���ݳ���(01����λ��)
 *  @param seed ���������
 *   
 *  @return src ����vector<int>������Դ
 */  
vector<int> PN15(int length = 64, int seed = 10);

/** 
 *  ��������: ����ȫ0��Դ
 *  @param length ���ݳ���(01����λ��)
 *   
 *  @return src ����vector<int>������Դ
 */  
vector<int> All0(int length = 64);

/** 
 *  ��������: ���ɴ��ļ���ȡ����Դ
 *  @param length ���ݳ���(01����λ��)
 *  @param filename ������ɾ���·����ʶ���ļ�·��,�ļ��Ƽ�ʹ��ASCII��ʽ����,���ⲻ��Ҫ�Ķ�ȡ�鷳
 *   
 *  @return src ����vector<int>������Դ
 */  
vector<int> FromFile(int length=64, const char* filename=NULL);

#endif