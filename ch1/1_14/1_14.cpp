/*
This file cannot compile under C++11, just use elder version(98)
*/

#include <iostream>
#include <string>
#include <string.h>
#include "OrderedCollection.h"


using namespace std;


class caseSensitiveLess
{
public:
	bool operator()(const string & str1, const string & str2)
	{
		if(stricmp(str1.c_str(), str2.c_str())<0)
			return true;
		return false;
	}
};

int main(int argc, char const *argv[])
{	
	std::string str[4] = {"hello", "not", "world", "Zebra"};
	Collection<std::string> testString(str, 4);

	cout<<"Max is: "<<testString.findMax(caseSensitiveLess())<<endl;
	cout<<"Min is: "<<testString.findMin(caseSensitiveLess())<<endl;

	return 0;
}