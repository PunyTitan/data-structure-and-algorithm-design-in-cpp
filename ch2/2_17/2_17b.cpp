#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>

using namespace std;

int posSumSubseq(vector<int> & a)
{
	int smallest = numeric_limits<int>::max();
	int sum = 0;

	for(int i=0; i<a.size(); i++)
	{
		sum += a[i];
		a[i] = sum;
	}

	sort(a.begin(), a.end());

	for(int i=0; i<a.size()-1; i++)
	{
		sum = a[i+1] - a[i];
		if (sum<smallest)
			smallest = sum;
	}

	return smallest;
}

int main(int argc, char const *argv[])
{
	int a[10] = {2,3,5,7,-1,-4,51,-2,-6,1};
	vector<int> aVec(a, a + sizeof(a)/sizeof(a[0]));

	cout<<posSumSubseq(aVec);	
	return 0;
}