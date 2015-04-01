#ifndef _TESTCASE_H
#define _TESTCASE_H
#include "utility.h"
#include<string>
#include<bitset>
using namespace std;
class TestCase
{	
public:	
	int NO;
	FaultBit fcBinary;//fault list represented by binary 
	int FC;//number of fault converaged
	double ET;//exectute time
	double SQ;//source' quality
	TestCase();	
	TestCase(int no);
	TestCase(int no, double et);
	TestCase(int no, int fc, int et);
	//void initBinary(std::string s);
};

#endif