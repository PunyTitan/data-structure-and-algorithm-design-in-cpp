#include <iostream>
#include <vector>


template<typename Object>
class Queue
{
public:
	Queue(int cap):head(-1), rear(-1), size(0), capacity(cap)
	{
		que = new Object[capacity];
	}

	~Queue()
	{
		while(size != 0)
			deque();
	}

	void enque(const Object & obj)
	{
		if(size == 0)
			head = rear = 0;
		else if(size != capacity)
			rear = rear+1==capacity ? 0 : rear+1;
		else
		{
			std::cout<<"Error: (enque)The capacity of the queue is not enough."<<std::endl;
			return;
		}

		++size;
		que[rear] = obj;
	}

	Object deque()
	{
		int old_head = head;
		if(size == 0)
			std::cout<<"Error: (deque)The queue is empty."<<std::endl;
		else
			head = head+1==capacity ? 0 : head+1;

		--size;
		return que[old_head];
	}

private:
	Object * que;
	int head;
	int rear;
	int size;
	int capacity;
};

int main(int argc, char const *argv[])
{
	Queue<int> test(3);
	test.enque(1);
	test.enque(3);
	test.enque(6);
	std::cout<<test.deque()<<std::endl;
	test.enque(8);
	std::cout<<test.deque()<<std::endl;
	test.enque(9);
	std::cout<<test.deque()<<std::endl;
	std::cout<<test.deque()<<std::endl;
	std::cout<<test.deque()<<std::endl;
	return 0;
}
