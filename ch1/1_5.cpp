#include <iostream>

using namespace std;

int getOneCount(int);

int main(int argc, char const *argv[])
{
	cout<<1<<" "<<getOneCount(1)<<endl;
	cout<<2<<" "<<getOneCount(2)<<endl;
	cout<<14<<" "<<getOneCount(14)<<endl;
	cout<<-3<<" "<<getOneCount(-3)<<endl;
	cout<<0<<" "<<getOneCount(0)<<endl;
	cout<<-2<<" "<<getOneCount(-2)<<endl;
	cout<<127<<" "<<getOneCount(127)<<endl;
	cout<<-128<<" "<<getOneCount(-128)<<endl;
	return 0;
}

int getOneCount(int N)
{
	int count = 0;

	if( N>127 || N<-128 )
		return -1;

	if (N == 1)
		return 1;
	else if(N == -1)
		return 8;
	else if(N == -128)
		return 1;
	else if(N%2 == 1)
		return getOneCount(N/2)+1;
	else
		return getOneCount(N+1)-1;

	return count;
}