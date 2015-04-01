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
	void init(int tcNum, int faultNum,vector<double> et);//��ʼ���������������ݺͷ�Ⱥ����
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
	//��¼�����ܹ���������ȱ�ݵĲ�����������
	void optimalStatistics();
	//�������е����Ž��APFD���ϲ��ظ���ͬ��Ĳ����������У�ֻ��������APFD������
	//void optimalFilter();

	
	double CalcAPFD(int faultNum, vector<int> exporeList);
 };