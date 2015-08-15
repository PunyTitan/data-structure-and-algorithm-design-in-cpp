#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

vector<string> split(string str, char delimiter)
{
	vector<string> rtr;
	string token;
	stringstream strS(str);

	while(getline(strS, token, delimiter))
	{
		rtr.push_back(token);
	}

	return rtr;
}


double calculateStr(string expn)
{
	vector<string> expnV = split(expn, ' ');
	double result;
	stack<double> numberS;
	double num1, num2;

	for(vector<string>::const_iterator itr = expnV.begin(); itr != expnV.end(); ++itr)
	{
		string token = *itr;
		result = atof(token.c_str());
		if(result != 0)
			numberS.push(result);
		else if(token[0] == '0')
			numberS.push(result);
		else
		{
			num1 = numberS.top();
			numberS.pop();
			num2 = numberS.top();
			numberS.pop();

			switch(token[0])
			{
				case '+': 
					numberS.push(num1 + num2);
					break;
				case '-':
					numberS.push(num2 - num1);
					break;
				case '*':
					numberS.push(num1 * num2);
					break;
				case '/':
					numberS.push(num2 / num1);
					break;
				default:
					std::cout<<"Error: Illegal input char."<<std::endl;
			}
		}
	}

	return numberS.top();
}

int main(int argc, char const *argv[])
{
	string test = "4.99 1.06 * 5.99 + 6.99 1.06 * +";
	cout<<calculateStr(test)<<endl;
	return 0;
}