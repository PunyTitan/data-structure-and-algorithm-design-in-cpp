//3.11

#include <iostream>

template<typename Object>
class ListOnlyHead
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
	public:
		const_iterator():current(NULL)
		{}

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

	 	//3.14
	 	const_iterator operator+(int k)
	 	{
	 		if(k<=0)
	 		{
	 			std::cout<<"Error: k should be larger than 0\n";
	 		}
	 		Node * ptr = current;
	 		for(; k!=0; --k)
	 		{
	 			if(ptr->next == NULL)
	 			{
	 				std::cout<<"Error: out of bound. return the last element\n";
	 				return const_iterator(ptr);
	 			}
	 			ptr = ptr->next;
	 		}

	 		return const_iterator(ptr);
	 	}


	 	/*const_iterator operator--()
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
	 	}*/

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
		Object & retrieve() const
		{
			return current->item;
		}

		friend class ListOnlyHead<Object>;

	};

	class iterator:public const_iterator
	{
	public:
		iterator():const_iterator(NULL)
		{}

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

		/*iterator operator--()
	 	{
	 		iterator itr = iterator(head);

	 		while(itr.current->next != this->current)
	 			++itr;
	 		return itr;
	 	}

	 	iterator operator--(int)
	 	{
	 		iterator itr = *this;
	 		--(*this);
	 		return itr;
	 	}*/

		Object & operator*()
		{
			return this->retrieve();
		}

		const Object & operator*() const
		{
			return const_iterator::operator*();
		}

	protected:
		iterator(Node * ptr):const_iterator(ptr)
		{}
		
		friend class ListOnlyHead<Object>;
	};

	ListOnlyHead()
	{
		init();
	}

	~ListOnlyHead()
	{
		clear();
		delete head;
	}

	void init()
	{
		head = new Node();
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
		++sizeV;
		return iterator(ptr);
	}

	//erase the position after the iterator, different from the insert in double linked list because of complexity
	iterator erase(iterator itr)
	{
		Node * ptr = itr.current->next;
		itr.current->next = ptr->next;

		delete ptr;
		--sizeV;

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
		Node * ptr;
		for(ptr = head; ptr->next!=NULL; ptr = ptr->next);
		return const_iterator(ptr);
	}

	iterator beforeEnd()
	{
		Node * ptr;
		for(ptr = head; ptr->next!=NULL; ptr = ptr->next);
		return iterator(ptr);
	}

	bool empty()
	{
		return size() == 0;
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

	//3.11 a
	int size()
	{
		return sizeV;
	}

	//3.11 b
	void print()
	{
		const_iterator end_itr = beforeEnd();
		for(const_iterator itr = begin(); itr != end_itr; ++itr)
		{
			std::cout<<*itr<<" ";
		}
		std::cout<<*end_itr<<std::endl;
	}

	//3.11 c
	iterator check(const Object & obj)
	{
		iterator end_itr = beforeEnd();
		for(iterator itr = begin(); itr != beforeEnd(); ++itr)
		{
			if(*itr == obj)
				return itr;
		}
		if(*end_itr == obj)
			return end_itr;

		return iterator(head);
	}

	const_iterator check(const Object & obj) const
	{
		const_iterator end_itr = beforeEnd();
		for(const_iterator itr = begin(); itr != beforeEnd; ++itr)
		{
			if(*itr == obj)
				return itr;
		}
		if(*end_itr == obj)
			return end_itr;

		return const_iterator(head);
	}

	//3.11 d
	bool check_insert(const Object & obj)
	{
		iterator itr = check(obj);

		if(itr == beforeBegin())
		{
			push_back(obj);
			return true;
		}

		return false;
	}

	//3.11 e
	bool check_erase(const Object & obj)
	{
		iterator erase_itr = begin();
		iterator befErase_itr = iterator(head);
		iterator end_itr = beforeEnd();
		bool returnVal = false;

		while(erase_itr != end_itr)
		{
			if(*erase_itr == obj)
			{
				erase(befErase_itr);
				erase_itr = iterator(befErase_itr.current->next);
				returnVal = true;
			}
			else
			{
				++erase_itr;
				++befErase_itr;
			}
		}

		if(*erase_itr == obj)
			erase(befErase_itr);

		return returnVal;
	}

	//3.12
	void insertByOrder(const Object & obj)
	{
		insert(obj, getPosition(obj));
	}

	//3.12
	iterator getPosition(const Object & obj)
	{
		Node * ptr = head;

		for(; ptr->next!=NULL; ptr = ptr->next)
		{
			if(ptr->next->item > obj)
				return iterator(ptr);
		}

		return iterator(ptr);
	}

private:
	int sizeV;
	Node * head;
};

