#include <iostream>
#include <math.h>

using namespace std;

double factorial(double base, int expo) 
{
	double result = 1;
	int numberOfBits = (int)log2(expo) + 1;
	double * elems = new double[numberOfBits];
	int * elemIndexs = new int[numberOfBits];

	elems[0] = base;
	for(int i=0; i+1<numberOfBits; i++)
		elems[i+1] = elems[i]*elems[i];

	for(int i=0; i<numberOfBits; i++)
	{
		elemIndexs[i] = expo%2;
		expo /= 2;
	}

	for(int i=0; i<numberOfBits; i++)
	{
		if(elemIndexs[i] == 1)
			result *= elems[i];
	}

	return result;
}

int main(int argc, char const *argv[])
{
	
	double base = 3;
	int expo = 7;

	cout<<factorial(base, expo)<<endl;

	return 0;
}