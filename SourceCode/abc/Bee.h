#ifndef _BEE_H
#define _BEE_H
#include<vector>
#include<unordered_set>
#include"TestCase.h"
#include"utility.h"
#include<boost\random.hpp>
using namespace std;
using namespace boost;
class  Bee
{
	//vector<TestCase> exploreList;

public:
	double totalET;
	int totalFC;
	int faultNum;
	FaultBit totalFcBinary;
	int NO;
	vector<int> exploreList;
	 Bee();	
	 Bee(int no);
	 Bee(int no, TestCase tc,int fn);
	 Bee(int no,double et,int fc,FaultBit binary, vector<int> tcList,int fn);
	 double getTotalET();
	// unordered_set<int> getExploreList();	 
	 bool isContainded(TestCase tc);
	 bool isImproved(TestCase tc);//�Ƿ�����˴��󸲸���
	 void memoryTastCase(TestCase tc);//����µĲ��������ļ����ܹ����Ӹ����ʣ����������·��
	 bool isCoverAll();//�Ƿ񸲸���ȫ���Ĵ���
	 bool operator< (Bee& bee);
	 friend ostream& operator<<(ostream& output, Bee& bee);
	 bool operator==(Bee& bee);
};
#endif

