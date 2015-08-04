#include <iostream>
#include "listDouble.h"

using namespace std;

template<typename Object, typename Iterator>
Iterator find(Iterator start, Iterator end, const Object & x)
{
	for(; start!=end; ++start)
	{
		if(*start == x)
			return start;
	}

	return end;
}

int main(int argc, char const *argv[])
{
	listDouble<int> testL;
	testL.push_back(5);
	testL.push_back(3);
	testL.push_back(2);
	testL.push_back(10);
	testL.push_back(-2);

	testL.print();

	listDouble<int>::const_iterator from = testL.begin();
	listDouble<int>::const_iterator to = testL.end();
	listDouble<int>::const_iterator ret_idx = find(++from, --to, 5);

	if(ret_idx != to)
		cout<<"The first found item :"<<*ret_idx<<endl;
	else
		cout<<"Item not founded"<<endl;

	return 0;
}