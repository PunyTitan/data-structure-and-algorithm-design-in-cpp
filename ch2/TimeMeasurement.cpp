#include <iostream>
#include <ctime>

using namespace std;

int main(int argc, char const *argv[])
{
	clock_t begin = clock();

	//running code, for example a nested loop
	int n = 100;
	int sum = 0;
	for(int i=0; i<n; i++)
		for(int j=1; j<i*i; j++)
			if(j%i==0)
				for(int k=0; k<j; k++)
					sum++;

	clock_t end = clock();

	double elapsedTime = (double)(end-begin)/CLOCKS_PER_SEC;

	cout<<"elapsedTime is: "<<elapsedTime<<endl;

	return 0;
}