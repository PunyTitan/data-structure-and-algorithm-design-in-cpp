#include <iostream>
#include <fstream>

int main()
{
	std::ifstream infile("pairs.txt");
	int a, b;

	while(infile>>a>>b)
	{
		std::cout<<a<<" "<<b<<std::endl;
	}

	return 0;
}