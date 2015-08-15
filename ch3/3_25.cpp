#include <iostream>
#include <stack>

template<typename Object>
class MinStack
{
public:
	MinStack()
	{}
	~MinStack()
	{}

	void push(const Object & obj)
	{
		itemS.push(obj);
		if(minS.size() == 0)
			minS.push(obj);
		else if(obj<=minS.top())
			minS.push(obj);
	}

	void pop()
	{
		if(itemS.top() == minS.top())
			minS.pop();
		itemS.pop();
	}

	const Object & findMin()
	{
		return minS.top();
	}

private:
 	std::stack<Object> itemS;
	std::stack<Object> minS;
};

int main(int argc, char const *argv[])
{
	MinStack<int> test;
	test.push(10);
	test.push(8);
	test.push(7);
	test.push(5);
	test.push(0);
	test.push(0);
	test.push(8);

	std::cout<<test.findMin()<<std::endl;
	test.pop();
	std::cout<<test.findMin()<<std::endl;
	test.pop();
	std::cout<<test.findMin()<<std::endl;
	test.pop();
	std::cout<<test.findMin()<<std::endl;
	test.pop();
	std::cout<<test.findMin()<<std::endl;
	test.pop();

	return 0;
}

/*
Key point: you don't have to keep the order of the items. You can only delete the items in a certain order, that helps with the O(1) complexity.
*/