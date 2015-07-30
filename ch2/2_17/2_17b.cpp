#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>

using namespace std;

class Item
{
public:
	int value;
	int index;
};


bool cmp(const Item & i1, const Item & i2)
{
	return i1.value<i2.value;
}


int posSumSubseq(vector<Item> & a)
{
	int smallest = numeric_limits<int>::max();
	int sum = 0;

	if (a.size() == 0)
		return 0;	

	for(int i=0; i<a.size(); i++)
	{
		sum += a[i].value;
		a[i].value = sum;
	}

	sort(a.begin(), a.end(), cmp);

	for(int i=0; i<a.size(); i++)
		if(a[i].value<smallest)
			smallest = a[i].value;

	for(int i=0; i+1<a.size(); i++)
	{
		for (int j=i+1; j<a.size(); j++ )
		{
			if(a[i].index<a[j].index)
			{
				sum = a[j].value - a[i].value;
				break;
			}
		}
		if(sum<smallest)
			smallest = sum;		

	}

	return smallest;
}

int main(int argc, char const *argv[])
{
	int a[10] = {5,99,5,7,6,99,-97,8,5,7};
	Item aItem[10] = {};

	for(int i=0; i<sizeof(a)/sizeof(a[0]); i++)
	{
		aItem[i].value = a[i];
		aItem[i].index = i;
	}

	vector<Item> aVec(aItem, aItem + sizeof(aItem)/sizeof(aItem[0]));

	cout<<posSumSubseq(aVec);	
	return 0;
}