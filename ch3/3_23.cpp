#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

int opLevel(string str)
{
	int quality;
	switch(str[0])
	{
		case '+':
		case '-':
			quality = 1;
			break;
		case '*':
		case '/':
			quality = 2;
			break;
		case '^':
			quality = 3;
			break;
		case ' ':
			quality = 0;
			break;
	}
	

	return quality;
}

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


//keep to stacks, one for expressions, one for the maximum operator in that expression(considering the parenthesis)
string postToIn(string str)
{
	stack<string> expS;
	stack<string> operS;
	vector<string> inputV = split(str, ' ');
	double result;
	string token, expr1, expr2, op1, op2;
	int parenthesis; 	//-1 for left, 0 for no, 1 for right

	for(vector<string>::const_iterator itr = inputV.begin(); itr != inputV.end(); ++itr)
	{
		token = *itr;
		result = atof(token.c_str());

		if(result != 0.0)
		{
			expS.push(token);
			operS.push(" ");
		}
		else if(token[0] == '0')
		{
			expS.push(token);
			operS.push(" ");
		}
		else
		{
			switch(token[0])
			{
				case '+':
				case '-':
					expr2 = expS.top();
					expS.pop();
					expr1 = expS.top();					
					expS.pop();
					expS.push(expr1 + " " + token + " " + expr2);
					
					op2 = operS.top();
					operS.pop();
					op1 = operS.top();
					operS.pop();
					operS.push(token);
					
					break;
				case '*':
				case '/':
				case '^':
					expr2 = expS.top();
					expS.pop();
					expr1 = expS.top();					
					expS.pop();					
					
					op2 = operS.top();
					operS.pop();
					op1 = operS.top();
					operS.pop();
					operS.push(token);

					if(op1 == " " && op2 == " ")
					{
						parenthesis = 0;
					}						
					else if(op1 == " ")
					{
						if(opLevel(op2)<opLevel(token))
							parenthesis = 1;						
						else
							parenthesis = 0;
					}
					else
					{
						if(opLevel(op1)<opLevel(token))
							parenthesis = -1;						
						else
							parenthesis = 0;
					}

					if(parenthesis == 1)
						expS.push(expr1 + " " + token + " ( " + expr2 + " )");
					else if(parenthesis == -1)
						expS.push("( " + expr1 + " ) " + token + " " + expr2);
					else
						expS.push(expr1 + " " + token + " " + expr2);					
					break;
				
			}
		}
	}

	if(expS.size() != 1)
		std::cout<<"Error: There are more than 1 final operations"<<std::endl;
	
	return expS.top();
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
		else if(token[0] == '0')
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
				case '^':
					while(!operatorS.empty() && operatorS.top()=="^")
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
	string test1 = "4.99 * 1.06 + 5.99 + 6.99 * 1.06"; 
	string test2 = "1 + 2 * 3 + ( 4 * 5 + 6 ) * 7";
	string test3 = "1 + 2 * 3 + ( 4 * 5 ^ 6 ) * 7";
	string test_1 = "4.99 1.06 * 5.99 + 6.99 1.06 * +";
	string test_2 = "1 2 3 * + 4 5 * 6 + 7 * +";
	string test_3 = "1 2 3 * + 4 5 6 ^ * 7 * +";

	cout<<inToPost(test1)<<endl;	
	cout<<inToPost(test2)<<endl;
	cout<<inToPost(test3)<<endl;

	cout<<postToIn(test_1)<<endl;	
	cout<<postToIn(test_2)<<endl;
	cout<<postToIn(test_3)<<endl;
	return 0;
}