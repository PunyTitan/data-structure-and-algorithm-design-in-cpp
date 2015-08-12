#include <iostream>

template<typename Object>
class listSingle
{
private: 
	struct Node
	{
		Object item;
		Node * next;

		Node(const Object & obj = Object(), Node * ptr = NULL)
		:item(obj), next(ptr)
		{}
	};
public:
	class const_iterator
	{
		const_iterator();
		~const_iterator();

	 	const_iterator operator++()
	 	{
	 		current = current->next;
	 		return *this;
	 	}

	 	const_iterator operator++(int)
	 	{
	 		const_iterator rtr_irt = *this;
	 		current = current->next;
	 		return rtr_irt;
	 	}

	 	const_iterator operator--()
	 	{
	 		const_iterator itr = beforeBegin();

	 		while(itr.current->next != current)
	 			++itr;
	 		return itr;
	 	}

	 	const_iterator operator--(int)
	 	{
	 		const_iterator itr = *this;
	 		--(*this);
	 		return itr;
	 	}

	 	const Object & operator*() const
	 	{
	 		return retrieve();
	 	}

	 	bool operator==(const const_iterator & rhs) const
	 	{
	 		if(current == rhs.current)
	 			return true;
	 		return false;
	 	}

	 	bool operator!=(const const_iterator & rhs) const
	 	{
	 		return !(*this == rhs);
	 	}


	protected:
		Node * current;

		const_iterator(Node * ptr)
		:current(ptr)
		{}

		//This retrive function is fetched from the book, however, I do not know why we should use it.
		const Object & retrieve()
		{
			return current->item;
		}

		friend class listSingle<Object>;

	};

	class iterator:public const_iterator
	{
	public:
		iterator();
		~iterator();

		iterator operator++()
		{
			this->current = this->current->next;
			return (*this);
		}

		iterator operator++(int)
		{
			iterator rtr_irt = *this;
			this->current = this->current->next;
			return rtr_irt;
		}

		iterator operator--()
	 	{
	 		iterator itr = beforeBegin();

	 		while(itr.current->next != this->current)
	 			++itr;
	 		return itr;
	 	}

	 	iterator operator--(int)
	 	{
	 		iterator itr = *this;
	 		--(*this);
	 		return itr;
	 	}

		Object & operator*()
		{
			return retrieve();
		}

		const Object & operator*() const
		{
			return const_iterator::operator*();
		}

	protected:
		iterator(Node * ptr):const_iterator(ptr)
		{}

		Object & retrieve()
		{
			return this->current->item;
		}
		
		friend class listSingle<Object>;
	};

	listSingle()
	{
		init();
	}

	~listSingle()
	{
		clear();
		delete head;
		delete tail;
	}

	void init()
	{
		head = new Node();
		tail = new Node();
		beforeTail = head;
		head->next = tail;
		sizeV = 0;
	}

	void clear()
	{
		while(!empty())
			pop_front();
	}

	//insert to the position after iterator, different from the insert in double linked list because of complexity
	iterator insert(const Object & obj, iterator itr)
	{
		Node * ptr = new Node(obj, itr.current->next);
		itr.current->next = ptr;
		if(itr.current == beforeTail)
			beforeTail = ptr;
		return iterator(ptr);
	}

	//erase the position after the iterator, different from the insert in double linked list because of complexity
	iterator erase(iterator itr)
	{
		Node * ptr = itr.current->next;
		itr.current->next = ptr->next;
		if(ptr == beforeTail)
			beforeTail = itr.current;
		delete ptr;

		return itr;
	}

	iterator erase(iterator from, iterator to)
	{
		while(from.current->next != to.current)
		{
			erase(from);
		}
	}

	const_iterator begin() const
	{
		return const_iterator(head->next);	
	}

	iterator begin()
	{	
		return iterator(head->next);
	}

	const_iterator end() const
	{
		return const_iterator(tail);
	}

	iterator end()
	{
		return iterator(tail);
	}	

	const_iterator beforeBegin() const
	{
		return const_iterator(head);
	}

	iterator beforeBegin()
	{
		return iterator(head);
	}

	const_iterator beforeEnd() const
	{
		return const_iterator(beforeTail);
	}

	iterator beforeEnd()
	{
		return iterator(beforeTail);
	}

	bool empty()
	{
		return size() == 0;
	}

	int size()
	{
		return sizeV;
	}

	void push_back(const Object & obj)
	{
		insert(obj, beforeEnd());
	}

	void push_front(const Object & obj)
	{
		insert(obj, beforeBegin());
	}

	//O(log(n))
	void pop_back()
	{
		erase(beforeEnd());
	}

	void pop_front()
	{
		erase(beforeBegin());
	}

	const Object & back()
	{
		return *(beforeEnd());
	}

	const Object & front()
	{
		return *(begin());
	}
	
private:
	int sizeV;
	Node * head;
	Node * tail;
	Node * beforeTail;
};


/*
key points:

1. In constructor, remember to add default value for the data members, usually you will need it.
2. Mark "const" to accessors
3. The iterator begin() function is not an accessor.
*/