#include"BeeColony.h"
#include"Bee.h"
#include <algorithm>
#include<iostream>
#include<ctime>
#include <cstdlib>
//#include"OptimalRecord.h"
using namespace std;
void BeeColony::init(int tcNum, int faultNum, vector<double> et)
{	
	this->tcNum = tcNum;
	this->faultNum = faultNum;

	for (int i = 1; i <= tcNum; ++i)
	{
		TestCase tc(i,et[i]);
		tc.fcBinary.resize(faultNum);
		tcList.push_back(tc);		
	}		
}
void BeeColony::sendEmployedBees(int n)
{
	
	for (int i = 1; i <= n; ++i)
	{	
		Bee bee(beeNum++, randomTC(),faultNum);
		beeList.push_back(bee);
		
	}
}
void BeeColony::print()
{
	for (int i = 0; i != beeList.size(); ++i)
	{
		cout << beeList[i];
	}
}
void BeeColony::printReduction()
{
	for (int i = 0; i != beeList.size(); ++i)
	{
		if (beeList[i].isCoverAll())
		cout << beeList[i];
	}
}

void BeeColony::explorePath()
{	
	for (int i = 0; i != beeList.size();++i)
	{
		Bee *bee = &beeList[i];
		
		while (true)
		{			
		
			TestCase tc = randomTC();				
			if (!bee->isContainded(tc) && bee->isImproved(tc))
			{					
				bee->memoryTastCase(tc);		
				break;
			}
		}
		if (bee->isCoverAll())
		{
			found = true;
			break;
		}	
		
	}
	//cout << "explorePath" << endl;
	//print();
}
TestCase BeeColony::randomTC()
{	
	TestCase tc = tcList[rdm.getrandom(tcNum-1)];
	return tc;
}
void BeeColony::search()
{	
	sendEmployedBees(tcNum/2);
	while (!found)
	{
		explorePath();
		crossOver();
	}
	//print();
	printReduction();
	optimalStatistics();

	reset();
}
void BeeColony::optimalStatistics()
{
	for (int i = 0; i != beeList.size(); ++i)
	{
		if (beeList[i].isCoverAll())	
			optimalSet.insert(beeList[i].exploreList);		
	}
}
//void BeeColony::optimalFilter()
//{	
//	set<vector<int>>::iterator it;
//	vector<OptimalRecord> recordList;
//	multimap<vector<int>, OptimalRecord> group;
//	for (it = optimalSet.begin(); it != optimalSet.end(); ++it)
//	{
//		OptimalRecord record(*it,CalcAPFD(faultNum,*it));
//		recordList.push_back(record);
//		group.insert(make_pair(record.sortedList,record));//分组
//	}	
//	
//
//}
void BeeColony::reset()
{
	found = false;
	beeList.clear();
	beeNum = 0;
}
void BeeColony::abandonPath(Bee *bee)
{
	bee->totalET = 0;
	bee->totalFC = 0;
	bee->faultNum = 0;
	bee->totalFcBinary.reset();
	bee->exploreList.clear();
//	cout << "clear:bee" << bee->NO << endl;
	//print();
}
void BeeColony::crossOver()
{	
	if (found) return;
	sort(beeList.begin(), beeList.end());
	double maxET = (*(beeList.end() - 1)).getTotalET();
	Bee b1 = beeList[0];
	Bee b2 = beeList[1];
	
	vector<int> lst1(b1.exploreList);
	vector<int> lst2(b2.exploreList);
	if (b1.exploreList.size() > 1)
	{	
	
		if (b1==b2)
		{
			abandonPath(&beeList[0]);
			abandonPath(&beeList[1]);	
		
			return;
		}
			
		//crossover
				
		lst1[0] = b2.exploreList[0];
		lst2[0] = b1.exploreList[0];	

		//如果交叉后出现重复的序列，例如1,2,1；将重复项恢复
		for (int i = 1; i != lst1.size(); ++i)
		{
			if (lst1[i] == lst1[0])
			{
				lst1[i] = b2.exploreList[i];
			}
			if (lst2[i] == lst2[0])
			{
				lst2[i] = b1.exploreList[i];
			}
		}

		//t1,t7,t8和t1,t8,t7交叉不产生新个体
		if (lst1 == b2.exploreList) return;//没有产生新个体	
	
		double et = 0;
		FaultBit fb;
		fb.resize(faultNum);
		for (int i = 0; i != lst1.size(); ++i)
		{
	
			et += tcList[lst1[i]-1].ET;			
			fb |= tcList[lst1[i]-1].fcBinary;
		}
	
		if ((et < maxET)&(beeNum < tcNum))
		{	
		
			Bee newBee1(beeNum++, et, fb.count(), fb, lst1,faultNum);
			beeList.push_back(newBee1);
			if (newBee1.isCoverAll())
			{
				found = true;				
			}
		}
	
		et = 0;
		fb.reset();
		for (int i = 0; i != lst2.size(); ++i)
		{
			et += tcList[lst2[i]-1].ET;			
			fb |= tcList[lst2[i]-1].fcBinary;
		}
	
		if ((et < maxET)&(beeNum < tcNum))
		{	
			Bee newBee2(beeNum++, et, fb.count(), fb, lst2,faultNum);
			beeList.push_back(newBee2);
			if (newBee2.isCoverAll())
			{
				found = true;
			}
		}
	}

}
bool BeeColony::isExistPath(Bee bee)
{
	for (int i = 0; i != beeList.size(); ++i)
	{
		if (bee == beeList[i]) return true;
	}
	return false;
}
double BeeColony::CalcAPFD( int faultNum, vector<int> exporeList)
{
	//Order 1,2,3,4,5
	int min,tcNo,tcNum=exporeList.size();
	int sum(0);
	for (int tf = 1; tf <= faultNum; ++tf)
	{
		min = tcNum;//默认最大
		for (int i = 0; i != exporeList.size(); ++i)
		{
			tcNo = exporeList[i];
			if (tcList[tcNo - 1].fcBinary[faultNum - tf] == 1 && (i+1)<min) min = i+1;
		}
		sum += min;
	}

	double apfd = 1 - 1.0*sum / (tcNum*faultNum) + 1.0 / (2 * tcNum);
	return apfd;
}

void BeeColony::printAPFD()
{
	set<vector<int>>::iterator it;
	for (it = optimalSet.begin(); it != optimalSet.end(); ++it)
	{
		cout << CalcAPFD(faultNum, *it) << endl;
	}
}
