#include "stdafx.h"
#include "SignalSource.h"

vector<int> PN9(int length, int seed)
{
	// ȷ��������ӵķ�Χ��ȷ
	if (seed>511)
		seed = 511;
	else if (seed<0)
		seed =0;
	vector<int> src;

	int connection [] ={1,0,0,0,0,1,0,0,0,1};
	int M = 9;// sizeof(connection) / sizeof(connection[0])-1; //�Ĵ���λ��
	int con[9]={0};
	for(int i=0;i<M;i++)
		con[i]=connection[i+1]; //���ڼ���ĳ�ͷλ�� c1~c9

	int registers[9]={0}; //��10��������seedת�ɶ����Ʊ��أ���䵽�Ĵ����У���λ��䵽DMλ
	int j=M-1;
	while(seed)
	{
		registers[j]=seed%2;
		seed/=2;
		j--;
	}

	for(int i=0;i<length;i++)
	{
		int tmp=0;
		src.push_back(registers[M-1]); //�Ĵ���Mλ��ֵ��ΪPN9���е�һ������
		for(int m=0;m<M;m++)
			tmp += registers[m] * con[m];//�Ĵ������ͷϵ����λ��

		tmp = tmp % 2;  //ģ2����
		for(int n=M-1;n>0;n--)
			registers[n]=registers[n-1]; // �Ĵ�����λ
		registers[0]=tmp; //��tmp2��Ϊ������ֵ�����뵽�Ĵ����ĵ�һλi
	}

	return src;
}

vector<int> PN15(int length, int seed)
{
	// ���뱣��
	if (seed > 32767)
		seed = 32767;
	else if (seed<0)
		seed = 0;

	vector<int> src;

	int connection [] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1};//c14=1��c15=1
	int M = 15;// sizeof(connection) / sizeof(connection[0])-1; //�Ĵ���λ��

	int con[15]={0};
	for(int i=0;i<M;i++)
		con[i]=connection[i+1]; //���ڼ���ĳ�ͷλ��

	int registers[15]={0};
	int j = M-1;
	while(seed)
	{
		registers[j]=seed%2;
		seed/=2;
		j--;
	}

	for(int i = 0; i < length; i++)
	{
		int tmp=0;
		src.push_back(registers[M-1]); //�Ĵ���Mλ��ֵ��ΪPN9���е�һ������
		for(int m=0;m<M;m++)
			tmp+=registers[m]*con[m];    //�Ĵ������ͷϵ����λ��
		tmp=tmp%2;  //ģ2����
		for(int n=M-1;n>0;n--)
			registers[n]=registers[n-1]; // �Ĵ�����λ
		registers[0]=tmp; //��tmp2��Ϊ������ֵ�����뵽�Ĵ����ĵ�һλi
	}
	return src;
}

vector<int> All0(int length)
{
	vector<int> src;
	for (int i = 0; i < length; i++)
		src.push_back(0);
	return src;
}

vector<int> FromFile(int length, const char* filename)
{
	vector<int> src;

	ifstream file;
	file.open(filename);
	if (!file)
	{
		return src;
	}
		

	int count = 0;//ͳ���ļ�λ��
	char c = '0';
	while (file.get(c) && count<length) 
	{
		int temp = (c=='0') ? 0 : 1;
		src.push_back(temp);
		count++;
	}
	file.close();

	// ����λȫ������
	if (count < length)
		for (int i = count; i < length; i++)
			src.push_back(0);

	return src;
}

vector<int> GenerateSource(int mode,int length, int seed, const char* filename)
{
	//length=4000;//test
	vector<int> src;
	switch (mode)
	{
	case 0: //PN9
		src = PN9(length,seed);
		break;
	case 1: //PN15
		src = PN15(length,seed);
		break;
	case 2: //ALL0
		src = All0(length);
		break;
	case 3: //read file
		src = FromFile(length,filename);
		break;
	default: //PN9
		src = PN9(length,seed);
		break;
	}
	return src;
}