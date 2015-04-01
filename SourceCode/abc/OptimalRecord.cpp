#include"OptimalRecord.h"

OptimalRecord::OptimalRecord(vector<int> list, double apfd) :unsortedList(list), sortedList(list),apfd(apfd)
{	
	sort(sortedList.begin(), sortedList.end());
}
bool OptimalRecord::operator == (OptimalRecord& record)
{	return this->sortedList == record.sortedList;
}
bool OptimalRecord::operator < (OptimalRecord& record)
{
	return this->apfd < record.apfd;
}