// O(N min(N, M))

#include <iostream>
#include "listDouble.h"

template<typename Object>
void  josephus(listDouble<Object> & lst, int m, int n)
{	
	int step;
	listDouble<int>::iterator itr = lst.begin();

	while(!lst.empty())
	{

		step = m>=n ? m%n : m;
		if(step>n/2)
		{			
			for(step = n-step; step>0; --step)
			{
				if(itr == lst.begin())
					itr = lst.end();
				--itr;
			}			
		}
		else
		{
			for(; step>0; --step)
			{
				++itr;
				if(itr == lst.end())
					itr = lst.begin();
			}			
		}
		std::cout<<*itr<<" ";
		itr = lst.erase(itr);
		if(itr == lst.end())
			itr = lst.begin();
		--n;
		
	}
}

int main(int argc, char const *argv[])
{
	int M = 3;
	int N = 11;
	int test[11] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	//int test[5] = {1, 2, 3, 4, 5};
	listDouble<int> testL(test, test+sizeof(test)/sizeof(test[0]));

	josephus(testL, M, N);

	return 0;
}