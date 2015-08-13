#include <iostream>

template<typename Object>
class listNo
{
private:
	struct Node
	{
		Object item;
		Node *left;
		Node *right;

		Node(const Object & obj = Object(), Node *lp = NULL, Node *rp = NULL)
		:item(obj), left(lp), right(rp){}
	};


public:

	class const_iterator
	{
	public:
		const_iterator():current(NULL)
		{}

		const_iterator & operator++()
		{
			current = current->right;
			return *this;
		}

		const_iterator operator++(int)
		{
			const_iterator rtr_itr = *this;
			++(*this);
			return rtr_itr;
		}

		const_iterator & operator--()
		{
			current = current->left;
			return *this;
		}

		const_iterator operator--(int)
		{
			const_iterator rtr_itr = *this;
			--(*this);
			return rtr_itr;
		}

		const Object & operator*() const
		{
			return retrieve();
		}

		bool operator==(const const_iterator & rhs) const
		{
			if(current == rhs.current)
				return true;
			else
				return false;
		}

		bool operator!=(const const_iterator & rhs) const
		{
			return !(*this == rhs);
		}

	protected:
		Node *current;
		listNo<Object> *currentList;


		const_iterator(Node *ptr, listNo<Object> * lst):current(ptr), currentList(lst)
		{}

		Object & retrieve() const
		{
			return current->item;
		}

		void assertIsValid()
		{
			if(current == NULL || currentList == NULL || current == currentList.head)
				std::cout<<"Error: the iterator is out of bound\n";	
		}

	friend class listNo<Object>;
	};

	class iterator : public const_iterator
	{
		public:
		iterator()
		{}

		iterator & operator++()
		{
			this->current = this->current->right;
			return *this;
		}

		iterator operator++(int)
		{
			iterator rtr_itr = *(this->current);
			++(*this);
			return rtr_itr;
		}

		iterator & operator--()
		{
			this->current = this->current->left;
			return *this;
		}

		iterator operator--(int)
		{
			iterator rtr_itr = *(this->current);
			--(*this);
			return rtr_itr;
		}

		Object & operator*()
		{
			return this->retrieve();
		}

		const Object & operator*() const
		{
			return const_iterator::operator*();
		}


	protected:
		iterator(Node *ptr, listNo<Object> *lst):const_iterator(ptr, lst)
		{}

		friend class listNo<Object>;

	};

	

	listNo()
	{
		init();
	}

	~listNo()
	{
		clear();
	}

	const listNo & operator=(const listNo & rhs)
	{
		if(this == &rhs)
			return *this;
		
		clear();

		Node * ptr;
		const_iterator rhs_itr = rhs.begin();
		const_iterator rhs_last = rhs.last();

		for(; rhs_itr!=rhs_last; ++rhs_itr)
		{
			++sizeV;
			if(rhs_itr == rhs.begin())
			{
				beginPtr = new Node(*rhs_itr, NULL, NULL);
				ptr = beginPtr;
			}
			else
			{
				ptr->right = new Node(*rhs_itr, ptr, NULL);
				ptr = ptr->right;
			}
		}
	}

	listNo(const listNo & rhs)
	{
		init();
		*this = rhs;
	}

	const_iterator begin() const
	{
		return const_iterator(beginPtr, this);
	}

	iterator begin()
	{
		return iterator(beginPtr, this);
	}

	const_iterator last() const
	{
		Node * ptr = beginPtr;
		if(empty())
			return const_iterator(beginPtr, this);
		
		while(ptr->right != NULL)
			ptr = ptr->right;

		return const_iterator(ptr, this);
	}

	iterator last()
	{
		Node * ptr = beginPtr;
		if(empty())
			return iterator(beginPtr, this);
		
		while(ptr->right != NULL)
			ptr = ptr->right;

		return iterator(ptr, this);
	}

	int size() const
	{
		return sizeV;
	}
	bool empty() const
	{
		return sizeV == 0;
	}

	void clear()
	{
		while(!empty())
		{
			pop_front();
		}
	}

	iterator push_back(const Object & obj)
	{
		Node * current_last = last();
		return iterator(current_last->right = new Node(obj, current_last, NULL), this);
	}

	iterator push_front(const Object & obj)
	{
		return iterator(beginPtr = new Node(obj, NULL, beginPtr), this);
	}

	void pop_front()
	{
		if(empty())
		{
			std::cout<<"Error: You cannot pop in an empty list!"<<std::endl;
			return;
		}
		--sizeV;
		Node * ptr = beginPtr;
		beginPtr = beginPtr->right;
		delete ptr;		
	}

	void pop_back()
	{
		if(empty())
		{
			std::cout<<"Error: You cannot pop in an empty list!"<<std::endl;
			return;
		}
		--sizeV;
		
		if(size() == 1)
		{
			delete beginPtr;
			beginPtr = NULL;
		}

		else
		{
			Node * secondlast_ptr = beginPtr;
			Node * last_ptr = last().current;

			while(secondlast_ptr->right != last_ptr)
				secondlast_ptr = secondlast_ptr->right;

			delete last_ptr;
			secondlast_ptr->right = NULL;			
		}

	}

	const Object & front() const
	{
		return *begin();
	}

	Object & front()
	{
		return *begin();
	}

	const Object & back() const
	{
		return *last();
	}

	Object & back()
	{
		return *last();
	}


	void print() 
	{
		const_iterator itr_last = last();
		for(const_iterator itr=begin(); itr!=itr_last; ++itr)
			std::cout<<*itr<<" ";
		std::cout<<"\n";
	}

	

private:

	int sizeV;
	Node * beginPtr;

	void init()
	{
		sizeV = 0;
		beginPtr = NULL;
	}
	
};

