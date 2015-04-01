#include<vector>
#include<set>
#include<map>
#include"TestCase.h"
#include "Bee.h"

using namespace std;
using namespace boost;
class BeeColony
{
	//int foodNumber = 10;
	//int colonySize = foodNumber*2;

	
	
	
public :

	MyRandom rdm;
	vector<TestCase> tcList;
	
	vector<Bee> beeList;
	int globalBeeNum = 1;
	int tcNum;
	int faultNum;
	int beeNum=0;
	bool found = false;
	set<vector<int>> optimalSet;
	void init(int tcNum, int faultNum,vector<double> et);//初始化测试用例的数据和蜂群数据
	void sendEmployedBees(int n);
	TestCase randomTC();
	void calculorProbabilities();	
	void crossOver();	
	void explorePath();
	bool isExistPath(Bee bee);
	void print();
	void printReduction();
	void printAPFD();
	void search();
	void reset();
	void abandonPath(Bee* bee);
	//记录所有能够覆盖所有缺陷的测试用例序列
	void optimalStatistics();
	//计算所有的最优解的APFD，合并重复不同序的测试用例序列，只保留最大的APFD的序列
	//void optimalFilter();

	
	double CalcAPFD(int faultNum, vector<int> exporeList);
 };