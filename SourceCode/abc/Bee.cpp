#include "Bee.h"
#include<bitset>
#include<algorithm>
using namespace std;

Bee::Bee(int no):NO(no){}

double Bee::getTotalET(){ return totalET; }
bool Bee::isImproved(TestCase tc)
{
	FaultBit fb=totalFcBinary|tc.fcBinary;
	return fb.count()>totalFcBinary.count();
}
bool Bee::isCoverAll()
{	
	return totalFcBinary.count()==faultNum;
}
void  Bee::memoryTastCase(TestCase tc)
{
	totalET += tc.ET;
	totalFcBinary=totalFcBinary | tc.fcBinary;
	totalFC = totalFcBinary.count(); 
	exploreList.push_back(tc.NO);
}
bool Bee::isContainded(TestCase tc)
{
	vector<int>::iterator iter;
	iter=find(exploreList.begin(),exploreList.end(),tc.NO);
	return (iter !=exploreList.end());
}
bool Bee::operator< (Bee &bee) 
{
	return totalET < bee.getTotalET();
}
bool Bee::operator == (Bee& bee)
{
	vector<int> lst(exploreList);
	sort(lst.begin(), lst.end());
	vector<int> lst2(bee.exploreList);
	sort(lst2.begin(), lst2.end());
	return lst == lst2;
}
//bool Bee::operator<<()
Bee::Bee(int no, double et, int fc, FaultBit fb, vector<int> tcList, int fn) :NO(no), totalET(et), totalFC(fc), totalFcBinary(fb), exploreList(tcList),faultNum(fn)
{	}
Bee::Bee(int no, TestCase tc, int fn) : NO(no)
{
	faultNum = fn;
	totalET = tc.ET;
	totalFC = tc.FC;
	totalFcBinary = tc.fcBinary;
	exploreList.push_back(tc.NO);
}
ostream& operator << (ostream& output, Bee& bee)
{
	output << "bee" << bee.NO << ",et=" << bee.totalET << ",fc=" << bee.totalFC;
	output << ",tcList:";
	for (int i = 0; i != bee.exploreList.size(); ++i)
		output << bee.exploreList[i] << " ";
	output << endl;
	output<<"binary=" << bee.totalFcBinary << endl;
	
	return output;
}