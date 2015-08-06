#include <iostream>
#include "listDouble.h"

template <typename Object>
int listUnion(const listDouble<Object> & lst1, const listDouble<Object> & lst2, listDouble<Object> & rtr_lst)
{
	if(!rtr_lst.empty())
		return -1;

	typename listDouble<Object>::const_iterator begin1 = lst1.begin(), begin2 = lst2.begin();
	while(begin1 != lst1.end() && begin2 != lst2.end())
	{
		if(*begin1 < *begin2)
			rtr_lst.push_back(*begin1++);
		else if(*begin1 > *begin2)
			rtr_lst.push_back(*begin2++);
		else
		{
			rtr_lst.push_back(*begin1);
			++begin1;
			++begin2;
		}
	}

	return 0;
}

int main(int argc, char const *argv[])
{
	listDouble<int> lst1;
	listDouble<int> lst2;
	listDouble<int> result;

	lst1.push_back(1);
	lst1.push_back(2);
	lst1.push_back(6);
	lst1.push_back(87);
	lst1.push_back(100);

	lst2.push_back(2);
	lst2.push_back(5);
	lst2.push_back(6);
	lst2.push_back(99);

	listUnion(lst1, lst2, result);
	result.print();

	return 0;
}