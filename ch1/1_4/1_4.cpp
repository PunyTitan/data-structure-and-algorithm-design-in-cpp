#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

void processFile(string);

int main()
{
	processFile("1_4_test1");
	return 0;
}

void processFile(string filename)
{	
	std::ifstream input( filename.c_str());

	//read file line by line
	for(string line; getline(input, line);)
	{
		//whether this line is a include statement
		if(regex_match(line, regex(".*#include <.+>")))
		{
			//extract the file name from the include statement
			string filenameNext = line.substr(line.find("<")+1 , line.find(">")-line.find("<")-1);
			processFile(filenameNext);
		}
		else
			cout<<line<<endl;
	}
}

/*
c_str()
regex_match(), regex()
substr(begin_index, len), find()
*/