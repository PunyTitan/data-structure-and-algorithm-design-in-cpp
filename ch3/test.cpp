#include <iostream>
#include "Vector.h"
#include <windows.h>

using namespace std;

int main(int argc, char const *argv[])
{
	Vector<int> testV;
	testV.push_back(2);
	testV.push_back(3);
	testV.push_back(5);
	testV.push_back(2);
	testV.push_back(3);
	testV.push_back(5);
	testV.push_back(2);
	testV.push_back(3);
	testV.push_back(5);
	testV.push_back(2);
	testV.push_back(3);
	testV.push_back(5);
	testV.push_back(2);
	testV.push_back(3);
	testV.push_back(5);
	testV.push_back(2);
	testV.push_back(3);
	testV.push_back(5);
	testV.push_back(2);
	testV.push_back(3);
	testV.push_back(5);
	testV.push_back(2);
	testV.push_back(3);
	testV.push_back(5);
	testV.print();

	Vector<int>::iterator itr = testV.begin();
	cout<<*itr<<endl;
	cout<<*(++itr)<<endl;
	cout<<"size: "<<testV.size()<<endl;
	cout<<"capacity: "<<testV.capacity()<<endl;
	
	return 0;
}