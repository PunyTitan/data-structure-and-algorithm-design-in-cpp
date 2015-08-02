#include <iostream>
#include <list>

using namespace std;

template<typename Object>
void printLots(list<Object> items, list<int> indices)
{
	int indexOfL = 0;
	typename list<Object>::const_iterator itemsBegin = items.begin();


	for(list<int>::const_iterator indicesBegin = indices.begin(); indicesBegin != indices.end(); ++indicesBegin)
	{
		if(*indicesBegin >= items.size())
			break;
		while(itemsBegin != items.end())
		{
			if(indexOfL+1 == (*indicesBegin))
			{
				cout<<*itemsBegin<<" ";
				break;
			}
			++itemsBegin;
			++indexOfL;
		}
	}
}

int main(int argc, char const *argv[])
{
	int itemsA[10] = {2, 3, 5, 7, 8, 9, 10, 11, 12, 13};
	int indicesA[5] = {1, 2, 2, 9, 11};

	list<int> itemsL(itemsA, itemsA+sizeof(itemsA)/sizeof(itemsA[0]));
	list<int> indicesL(indicesA, indicesA+sizeof(indicesA)/sizeof(indicesA[0]));


	printLots(itemsL, indicesL);

	return 0;
}