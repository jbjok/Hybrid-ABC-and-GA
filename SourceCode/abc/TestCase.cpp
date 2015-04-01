#include "TestCase.h"
TestCase::TestCase(int no) :NO(no){}
TestCase::TestCase(int no, double et):NO(no),ET(et){}
TestCase::TestCase(int no, int fc, int et) :NO(no), FC(fc), ET(et), SQ(fc*1.0 / et){}
//void TestCase::initBinary(std::string s)
//{
//	bitset<MAX_FAULTS_SIZE> bs(s);
//	fcBinary = bs;
//}