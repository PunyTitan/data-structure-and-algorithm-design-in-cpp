#include <iostream>
#include "Vector.h"
#include <windows.h>

using namespace std;

int main(int argc, char const *argv[])
{
	int count = 0;
	Vector<int> testV;

	for(int i = 0; i<20; i++)
		testV.push_back(count++);
	
	testV.print();

	cout<<"size: "<<testV.size()<<endl;
	cout<<"capacity: "<<testV.capacity()<<endl;

	testV.print();

	return 0;
}