#include<iostream>
#include<bitset>
#include<ctime>
#include<cstdlib>
#include"BeeColony.h"
#include<fstream>
#include<string>
#include<vector>
#include<boost\dynamic_bitset.hpp> 
#include <boost/format.hpp>  
#include <boost/tokenizer.hpp> 
#include <boost/algorithm/string.hpp>  
#include <boost/lexical_cast.hpp>
#include <windows.h>  
using namespace boost;
using namespace std;
std::vector<int> split(std::string str);

int main()
{
	int maxCycle = 10;

	int tcNum;//read from file
	int faultNum ;//read from file	
	

	//读取和计算测试用例的执行时间
	vector<double> time;
	//ifstream etf("d:\\siemens\\example_et", ios::_Nocreate);
	ifstream etf("d:\\siemens\\replace_et", ios::_Nocreate);
	string buf;
	//读取执行测试用例数量和缺陷数量
	getline(etf, buf);
	tcNum = lexical_cast<int>(buf);
	getline(etf, buf);
	faultNum = lexical_cast<int>(buf);
	//读取用例执行时间
	while (etf)
	{
		if (getline(etf, buf))
		{
			double d = lexical_cast<double>(buf);			
			time.push_back(d);
		}
	}
	etf.close();
	double totalET = time[time.size() - 1] - time[0];//所有的测试用例执行时间
	for (int i = time.size()-1; i !=0; --i)	//time[0]是起始时间
		time[i] = time[i] - time[i-1];	
	
	
	//初始化蜂群的数据
	BeeColony bc;
	bc.init(tcNum, faultNum,time);
	
	//读取并初始化测试用例的覆盖信息
	//ifstream ifs("d:\\siemens\\example", ios::_Nocreate);
	ifstream ifs("d:\\siemens\\replace_fault", ios::_Nocreate);	
	int no = 0;
	while (ifs)
	{
		if (getline(ifs, buf))
		{
			if (buf[0] == 83)//S
			{				
				no++;//fault No
			}
			if (buf[0] ==9)//开始出现数据
			{				
				vector<int> vs = split(buf);			
				for (int i = 0; i != vs.size(); ++i)
				{					
					bc.tcList[vs[i] - 1].fcBinary[faultNum-no]= 1;//vs[i]表示读入的用例编号
				//	cout <<no<<"," <<vs[i] - 1 << endl;
				}					
			}				
		}
		
	}		
	ifs.close();
	
	//计算缺陷覆盖数量
	for (int i = 0; i != bc.tcList.size(); ++i)
		bc.tcList[i].FC = bc.tcList[i].fcBinary.count();
	
	

	//执行算法
	double start, end;
	double tmpET,sum(0);
	for (int i = 0; i != maxCycle; ++i)
	{
		cout << "round:" << i << endl;
		start = GetTickCount();	
		bc.search();
		end = GetTickCount();
		tmpET = (end - start) / 1000.0;
		sum += tmpET;
		cout << "ET=" <<tmpET << endl;
	}
	cout << "average ET:" << sum / maxCycle << endl;
	/*
	//bc.optimalStatistics();
	//打印所有解并找到执行时间最短的那个
	cout << "optimal number:" << bc.optimalSet.size() << endl;
	set<vector<int>>::iterator it,itMin;
	double et,etMin=100;
	for (it = bc.optimalSet.begin(); it != bc.optimalSet.end(); ++it)
	{
		et = 0;
		for (int i = 0; i != (*it).size(); ++i)
		{
			et += bc.tcList[(*it)[i] - 1].ET;
			cout << (*it)[i] << " ";			
		}
		if (et < etMin)
		{
			etMin = et;
			itMin = it;
		}
		cout << "ET=" << et << endl;
			//",APFD=" << bc.CalcAPFD(bc.faultNum, *it) << endl;
			
	}
	cout << "Optimal List:" << endl;
	int size = (*itMin).size();
	for (int i = 0; i !=size ; ++i)
	{	
		cout << (*itMin)[i] << " ";
	}
	cout << endl <<"Original ET="<<totalET<<",Optimized ET=" << etMin <<",Reduce by:"<<1.0-etMin/totalET<< endl;
	cout << "Original TC Size="<<tcNum<<",Optimized TC Size=" << size<<",Reduce by:"<<1.0-1.0*size/tcNum << endl;
	
	*/
	//bc.printAPFD();
}
//字符串分割函数
