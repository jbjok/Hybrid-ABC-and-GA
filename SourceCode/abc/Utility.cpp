#include "Utility.h"
using namespace boost;

int MyRandom::getrandom(int n)
{
	boost::random::uniform_int_distribution<> dist(1, n);
	return dist(gen);
}
std::vector<int> split(std::string str)
{
	vector<int> result;
	tokenizer<> tok(str);
	for (tokenizer<>::iterator beg = tok.begin(); beg != tok.end(); ++beg)
	{
		int a = lexical_cast<int>(*beg);
		result.push_back(a);
	}

	return result;
}
