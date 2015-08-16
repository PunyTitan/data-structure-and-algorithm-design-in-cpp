#include <iostream>
#include <vector>
#include <algorithm>

struct Node
{
	int data;
	Node * next;

	Node(int obj, Node * ptr):data(obj), next(ptr)
	{}
};

//a 
bool loopA(Node * lst)
{
	//can use hashset with lookup time complexity O(1)
}

//b
bool loopB(Node * lst)
{	
	Node * ptr1, * ptr2;
	ptr1 = ptr2 = lst;
	while(ptr2 != NULL)
	{
		ptr1 = ptr1->next;
		ptr2 = ptr2->next;
		if(ptr2 == NULL)
			return false;
		ptr2 = ptr2->next;

		if(ptr1 == ptr2)
			return true;
	}
	return false;
}

int main(int argc, char const *argv[])
{
	Node * node1 = new Node(1, NULL);
	Node * node2 = new Node(2, NULL);
	Node * node3 = new Node(3, NULL);

	node1->next = node2;
	node2->next = node3;
	node3->next = node1;

	std::cout<<loopB(node1)<<std::endl;
	return 0;
}