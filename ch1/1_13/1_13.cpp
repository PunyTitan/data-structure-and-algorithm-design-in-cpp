#include <iostream>
#include <string>
#include "Collection.h"

using namespace std;

int main(int argc, char const *argv[])
{	
	int a[5] = {1,2,3,4,6};
	std::string str[3] = {"hello", "not", "world"};

	Collection<int> testInt(a, 5);
	Collection<std::string> testString(str, 3);

	cout<<testInt.isEmpty()<<endl;
	cout<<testInt.contains(6)<<endl;
	cout<<testInt.remove()<<endl;
	cout<<testInt.contains(6)<<endl;
	testInt.insert(10);
	cout<<testInt.contains(10)<<endl;
	testString.makeEmpty();
	cout<<testString.isEmpty()<<endl;

	return 0;
}