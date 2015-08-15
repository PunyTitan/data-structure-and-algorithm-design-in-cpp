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

string inToPost(string str)
{
	stack<string> operatorS;
	vector<string> resultV;
	vector<string> inputV = split(str, ' ');
	double result;
	string token;
	string returnStr= "";

	for(vector<string>::const_iterator itr = inputV.begin(); itr != inputV.end(); ++itr)
	{
		token = *itr;
		result = atof(token.c_str());

		if(result != 0.0)
		{
			resultV.push_back(token);
		}
		else if(token[0] == 0)
		{
			resultV.push_back(token);
		}
		else
		{
			switch (token[0])
			{

				case '+':
				case '-':
					while(!operatorS.empty() && operatorS.top()!="(")
					{
						resultV.push_back(operatorS.top());
						operatorS.pop();
					}
					operatorS.push(token);
					break;
				case '*':
				case '/':
					while(!operatorS.empty() && operatorS.top()!="+" && operatorS.top()!="-" && operatorS.top()!="(")
					{
						resultV.push_back(operatorS.top());
						operatorS.pop();
					}
					operatorS.push(token);
					break;
				case '(':
					operatorS.push(token);
					break;
				case ')':
					while(operatorS.top() != "(")
					{
						resultV.push_back(operatorS.top());
						operatorS.pop();
					}
					operatorS.pop();
					break;
			}
		}
	}
	while(!operatorS.empty())
	{
		resultV.push_back(operatorS.top());
		operatorS.pop();
	}

	for(vector<string>::const_iterator itr = resultV.begin(); itr!=resultV.end(); ++itr)
		returnStr += *itr + " ";

	return returnStr.substr(0, returnStr.size()-1);
}

int main(int argc, char const *argv[])
{
	string test = "4.99 * 1.06 + 5.99 + 6.99 * 1.06"; 
	string test2 = "1 + 2 * 3 + ( 4 * 5 + 6 ) * 7";
	cout<<inToPost(test)<<endl;	
	cout<<inToPost(test2)<<endl;
	return 0;
}