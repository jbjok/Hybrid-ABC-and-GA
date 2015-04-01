#ifndef OPTIMAL_RECORD_H
#define OPTIMAL_RECORD_H

#include<vector>
#include<algorithm>
using namespace std;
class OptimalRecord
{
	
public:
	vector<int> sortedList;
	vector<int> unsortedList;
	double apfd;
	OptimalRecord();
	OptimalRecord(vector<int> list,double apfd);
	bool operator==(OptimalRecord& record);
	bool operator < (OptimalRecord& record);
	
};
#endif