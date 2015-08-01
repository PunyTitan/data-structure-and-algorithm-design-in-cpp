/*
Different from the question in the book, we assume j>i, not j>=i.
*/

#include <iostream>
#include <limits>

using namespace std;


int maxPlus(int * a, int length)
{
	int firstmaxItem = a[0];
	int secondmaxItem = numeric_limits<int>::min();

	for(int i=1; i<length; i++)
	{
		if(a[i]>firstmaxItem)
		{
			secondmaxItem = firstmaxItem;
			firstmaxItem = a[i];
		}
		else if(a[i]>secondmaxItem)
			secondmaxItem = a[i];
	}

	return firstmaxItem + secondmaxItem;
}

int maxMinus(int * a, int length)
{
	int subMax = numeric_limits<int>::min();
	int minItem = a[0];

	for(int i=1; i<length; i++)
	{
		subMax = max(a[i]-minItem, subMax);
		minItem = a[i]<minItem ? a[i] : minItem;
	}

	return subMax;
}


int maxTimes(int * a, int length)
{
	int maxItem = 1;
	int minItem = -1;
	int subMax = numeric_limits<int>::min();

	for(int i=1; i<length; i++)
	{
		if(a[i]>0)
		{
			subMax = max(subMax, maxItem*a[i]);
			maxItem = a[i]>maxItem ? a[i] : maxItem;
		}
		else if(a[i]<0)
		{
			subMax = max(subMax, minItem*a[i]);
			minItem = a[i]<minItem ? a[i] : minItem;
		}
		else
			subMax =a[i]>subMax ? a[i] : subMax;
	}

	return subMax;
}

double maxDivide(int * a, int length)
{
	double subMax = -1 * numeric_limits<double>::infinity();
	double minNegAbs = -1 * numeric_limits<double>::infinity();
	double minPosAbs = numeric_limits<double>::infinity();


	for(int i=0; i<length; i++)
	{
		if(a[i]>0)
		{
			subMax = max(subMax, a[i]/minPosAbs);
			minPosAbs = a[i]<minPosAbs ? a[i] : minPosAbs;
		}
		else if(a[i]<0)
		{
			subMax = max(subMax, a[i]/minNegAbs);
			minNegAbs = a[i]>minNegAbs ? a[i] : minNegAbs;
		}
		else
			subMax =a[i]>subMax ? a[i] : subMax;
	}

	return subMax;
}

int main(int argc, char const *argv[])
{	
	int test[10] = {2, 0,-6,7,5,7,2,8,-2,-9};

	cout<<"a[j] + a[i] = "<<maxPlus(test, 10)<<endl;
	cout<<"a[j] - a[i] = "<<maxMinus(test, 10)<<endl;
	cout<<"a[j] * a[i] = "<<maxTimes(test, 10)<<endl;
	cout<<"a[j] / a[i] = "<<maxDivide(test, 10)<<endl;
	
	return 0;
}