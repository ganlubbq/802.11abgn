#ifndef SIGNALSOURCE_H
#define SIGNALSOURCE_H

/*******************************************************************
 *  文件名称: SignalSource.h
 *  简要描述: 
 *    用于配置生成 4 种信源(PN9 PN15 全0 从文件读),
 *    经过讨论,输出是vector<int>类型的源,更标准的格式应该输出BYTE源
 *   
 *  创建日期: 2016.06.21
 *  作者: xingxin
 *  说明: 根据刘海涛信源程序改写,对原程序生成逻辑和输出格式做了优化
 ******************************************************************/

#include <fstream>
#include <vector>
using namespace std;

/** 
 *  功能描述: 根据选取的模式和数据长度等信息生成信源
 *  @param mode 生成模式选择(0:PN9 1:PN15 2:All0 3:文件读取)
 *  @param length 数据长度(01比特位数)
 *  @param seed 随机数种子
 *  @param filename 最好是由绝对路径标识的文件路径,文件推荐使用ASCII格式保存,以免不必要的读取麻烦
 *   
 *  @return src 返回vector<int>型数据源
 */  
vector<int> GenerateSource(int mode=0,int length=64, int seed=10, const char* filename=NULL);

/** 
 *  功能描述: 生成PN9信源
 *  @param length 数据长度(01比特位数)
 *  @param seed 随机数种子
 *   
 *  @return src 返回vector<int>型数据源
 */  
vector<int> PN9(int length = 64, int seed = 10);

/** 
 *  功能描述: 生成PN15信源
 *  @param length 数据长度(01比特位数)
 *  @param seed 随机数种子
 *   
 *  @return src 返回vector<int>型数据源
 */  
vector<int> PN15(int length = 64, int seed = 10);

/** 
 *  功能描述: 生成全0信源
 *  @param length 数据长度(01比特位数)
 *   
 *  @return src 返回vector<int>型数据源
 */  
vector<int> All0(int length = 64);

/** 
 *  功能描述: 生成从文件读取的信源
 *  @param length 数据长度(01比特位数)
 *  @param filename 最好是由绝对路径标识的文件路径,文件推荐使用ASCII格式保存,以免不必要的读取麻烦
 *   
 *  @return src 返回vector<int>型数据源
 */  
vector<int> FromFile(int length=64, const char* filename=NULL);

#endif