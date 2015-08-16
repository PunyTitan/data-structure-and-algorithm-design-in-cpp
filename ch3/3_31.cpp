#include <iostream>

template<typename Object>
class Stack
{
private:
	struct Node{
		Object data;
		Node * next;
		Node(const Object & obj, Node * ptr):data(obj), next(ptr)
		{}
	};

public:
	Stack()
	{
		head = NULL;
		size = 0;
	}

	~Stack()
	{
		while(size != 0)
			pop();
	}

	void push(const Object & obj)
	{
		if(size == 0)
			head = new Node(obj, NULL);
		else
			head = new Node(obj, head);
		
		++size;

	}

	void pop()
	{
		if(size == 0)
		{
			std::cout<<"Error: You cannot pop an empty stack"<<std::endl;
			return;
		}
		Node * old_head = head;
		head = head->next;
		delete old_head;
		--size;
	}

	Object & top()
	{
		if(size == 0)
		{
			std::cout<<"Error: You cannot top an empty stack"<<std::endl;
		}
		return head->data;
	}

private:
	Node * head;
	int size;

};

int main(int argc, char const *argv[])
{
	Stack<int> test;
	test.push(3);
	test.push(5);
	test.push(6);
	test.push(0);

 	std::cout<<test.top()<<std::endl;
 	test.pop();
 	std::cout<<test.top()<<std::endl;
 	test.pop();
 	std::cout<<test.top()<<std::endl;
 	test.pop();
 	std::cout<<test.top()<<std::endl;
 	test.pop();
	return 0;
}