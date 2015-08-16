#include <iostream>

template<typename Object>
class Queue
{
private:
	struct Node{
		Object data;
		Node * next;
		Node(const Object & obj, Node * ptr):data(obj), next(ptr)
		{}
	};

public:
	Queue()
	{
		rear = head = NULL;
		size = 0;
	}

	~Queue()
	{
		while(size != 0)
			deque();
	}

	void enque(const Object & obj)
	{	
		if(size == 0)
			rear = head = new Node(obj, NULL);
		else
			rear = rear->next = new Node(obj, NULL);
		
		++size;
	}

	Object deque()
	{		
		Object old_head_data = head->data;
		Node * old_head = head;
		head = head->next;
		delete old_head;
		
		--size;

		if(size == 0)
			rear = NULL;

		return old_head_data;
	}

private:
	Node * head;
	Node * rear;
	int size;

};

int main(int argc, char const *argv[])
{
	Queue<int> test;

	test.enque(3);
	test.enque(5);
	test.enque(7);
	test.enque(8);

	std::cout<<test.deque()<<std::endl;
	std::cout<<test.deque()<<std::endl;
	std::cout<<test.deque()<<std::endl;
	std::cout<<test.deque()<<std::endl;
	
	return 0;
}