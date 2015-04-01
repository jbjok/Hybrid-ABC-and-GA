#ifndef _UTILITY_H
#define _UTILITY_H 
#include<bitset>
#include<ctime>
#include<cstdlib>
#include<vector>

#include<boost\dynamic_bitset.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/format.hpp>  
#include <boost/tokenizer.hpp> 
#include <boost/algorithm/string.hpp>  
#include <boost/lexical_cast.hpp>
using namespace boost;
using namespace std;
typedef boost::dynamic_bitset<> FaultBit;
std::vector<int> split(std::string str);
class MyRandom
{
	boost::random::mt19937 gen;
	public:
	int getrandom(int n);
};
#endif