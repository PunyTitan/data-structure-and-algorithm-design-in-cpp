#include <iostream>
#include <limits>

using namespace std;


int max3(int a, int b, int c)
{
	int maxI = a;
	if(maxI<b)
		maxI = b;
	if(maxI<c)
		maxI = c;
	return maxI;
}

int min3(int a, int b, int c)
{
	int minI = a;
	if(minI>b)
		minI = b;
	if(minI>c)
		minI = c;
	return minI;
}


int largestSubseq(int *seq, int length)
{
	int *max = new int[length];
	int *min = new int[length];
	int max_value = numeric_limits<int>::min();

	max[0] = seq[0];
	min[0] = seq[0];

	for(int i=1; i<length; i++)
	{
		max[i] = max3(seq[i], max[i-1]*seq[i], min[i-1]*seq[i]);
		min[i] = min3(seq[i], max[i-1]*seq[i], min[i-1]*seq[i]);

		if(max[i]>max_value)
			max_value = max[i];
	}

	return max_value;

}

int main(int argc, char const *argv[])
{
	int a[10] = {5,2,-2,7,-2,2,-3,-1,5,-9};

	cout<<largestSubseq(a, 10)<<endl;

	return 0;
}