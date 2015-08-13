#include <iostream>
#include <typeinfo>

template<typename Object>
class listDouble
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
		listDouble<Object> *currentList;


		const_iterator(Node *ptr, listDouble<Object> * lst):current(ptr), currentList(lst)
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

	friend class listDouble<Object>;
	};

	/*
	In this class, I use this->current instead of current because the compiler cannot handle template well in this condition. (Or we can say that the compiler has its design choice)
	Related explaination: http://gcc.gnu.org/onlinedocs/gcc/Name-lookup.html
	*/
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
		iterator(Node *ptr, listDouble<Object> *lst):const_iterator(ptr, lst)
		{}

		friend class listDouble<Object>;

	};

	class const_reverse_iterator
	{
	public:
		const_reverse_iterator():current(NULL)
		{}

		const_reverse_iterator & operator++()
		{
			current = current->left;
			return *this;
		}

		const_reverse_iterator operator++(int)
		{
			const_reverse_iterator rtr_itr = *this;
			++(*this);
			return rtr_itr;
		}

		const_reverse_iterator & operator--()
		{
			current = current->right;
			return *this;
		}

		const_reverse_iterator operator--(int)
		{
			const_reverse_iterator rtr_itr = *this;
			--(*this);
			return rtr_itr;
		}

		const Object & operator*() const
		{
			return retrieve();
		}

		bool operator==(const const_reverse_iterator & rhs) const
		{
			if(current == rhs.current)
				return true;
			else
				return false;
		}

		bool operator!=(const const_reverse_iterator & rhs) const
		{
			return !(*this == rhs);
		}

	protected:
		Node *current;
		listDouble<Object> *currentList;


		const_reverse_iterator(Node *ptr, listDouble<Object> * lst):current(ptr), currentList(lst)
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

	friend class listDouble<Object>;
	};

	class reverse_iterator : public const_reverse_iterator
	{
		public:
		reverse_iterator()
		{}

		reverse_iterator & operator++()
		{
			this->current = this->current->left;
			return *this;
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator rtr_itr = *(this->current);
			++(*this);
			return rtr_itr;
		}

		reverse_iterator & operator--()
		{
			this->current = this->current->right;
			return *this;
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator rtr_itr = *(this->current);
			--(*this);
			return rtr_itr;
		}

		Object & operator*()
		{
			return this->retrieve();
		}

		const Object & operator*() const
		{
			return const_reverse_iterator::operator*();
		}


	protected:
		reverse_iterator(Node *ptr, listDouble<Object> *lst):const_reverse_iterator(ptr, lst)
		{}

		friend class listDouble<Object>;

	};

	listDouble()
	{
		init();
	}

	//Initialized by array
	listDouble(const Object * ar_begin, const Object * ar_end)
	{
		init();
		while(ar_begin != ar_end)
		{
			this->push_back(*ar_begin);
			++ar_begin;
		}
	}

	~listDouble()
	{
		clear();
		delete head;
		delete tail;
	}

	const listDouble & operator=(const listDouble & rhs)
	{
		if(this == &rhs)
			return *this;
		
		clear();

		for(const_iterator rhs_begin = rhs.begin(); begin != rhs.end(); ++rhs_begin)
		{
			push_back(*rhs_begin);
		}
	}

	listDouble(const listDouble & rhs)
	{
		init();
		*this = rhs;
	}

	const_iterator begin() const
	{
		return const_iterator(head->right, this);
	}

	iterator begin()
	{
		return iterator(head->right, this);
	}

	const_iterator end() const
	{
		return const_iterator(tail, this);
	}

	iterator end()
	{
		return iterator(tail, this);
	}

	reverse_iterator rBegin()
	{	
		return reverse_iterator(tail->left, this);
	}

	reverse_iterator rEnd()
	{
		return reverse_iterator(head, this);
	}

	const_reverse_iterator rBegin() const
	{	
		return const_reverse_iterator(tail->left, this);
	}

	const_reverse_iterator rEnd() const
	{
		return const_reverse_iterator(head, this);
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
		return insert(obj, end());
	}

	iterator push_front(const Object & obj)
	{
		return insert(obj, begin());
	}

	void pop_front()
	{
		erase(begin());
	}

	void pop_back()
	{
		erase(--end());
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
		return *--end();
	}

	Object & back()
	{
		return *--end();
	}

	iterator insert(const Object & obj, iterator itr)
	{
		Node *ptr = itr.current;
		++sizeV;
		return iterator(ptr->left = ptr->left->right = new Node(obj, ptr->left, ptr), this);
	}

	iterator erase(iterator itr)
	{
		Node *ptr = itr.current;
		ptr->left->right = ptr->right;
		ptr->right->left = ptr->left;
		iterator rtr_itr(ptr->right, this);
		delete ptr;
		--sizeV;

		return rtr_itr;
	}

	iterator erase(iterator from, iterator to)
	{
		while(from != to)
		{
			from = erase(from);
		}
	}

	void swap(iterator left_item, iterator right_item)
	{
		Node * left_ptr = left_item.current;
		Node * right_ptr = right_item.current;

		left_ptr->right = right_ptr->right;
		right_ptr->left = left_ptr->left;
		left_ptr->left = right_ptr;
		right_ptr->right = left_ptr;
	}

	void print() 
	{
		for(const_iterator begin_itr=begin(); begin_itr!=end(); ++begin_itr)
			std::cout<<*begin_itr<<" ";
		std::cout<<"\n";
	}

	void reverse_print() 
	{
		const_reverse_iterator itr = rBegin();

		for(; itr!=rEnd(); ++itr)
		{
			std::cout<<*itr<<" ";
		}
		std::cout<<std::endl;
	}

	//not used by developer. It is a function to verify that "this" in a member function marked "const" has different type compared to ones without "const"
	void testThis() const
	{
		std::cout<<typeid(this).name()<<std::endl;
	}

	void splice(iterator position, listDouble<Object> & lst)
	{
		position.assertIsValid();
		if(this == &lst)
		{
			std::cout<<"The inputed list should not be the same.\n";
			return;
		}

		if(position.currentList != this)
		{
			std::cout<<"The iterator is not match with the list\n";
			return;
		}

		sizeV += lst.size();

		Node * ptr = position.current;
		ptr->left->right = lst.head->right;
		lst.head->right->left = ptr->left;
		ptr->left = lst.tail->left;
		lst.tail->left->right = ptr;

		//this statement is crucial for O(1)!!
		lst.init();
	}


private:

	int sizeV;
	Node *head;
	Node *tail;

	void init()
	{
		sizeV = 0;
		head = new Node;
		tail = new Node;

		head->right = tail;
		tail->left = head;
	}
	
};

/*
key points:

1. Functions, which will return an item in the collection, should be implemented with an accessor and a modifier.
2. Two kinds of iterator, so two kinds of begin() and end()
3. The usage of friend in iterator class
4. The constructor of const_iterator with zero parameter should initialize the pointer to NULL
5. operator++ in const_iterator should return itself, not a pointer
6. when you implement a new operator*() function in iterator, you should also implement a operator*() const, because the original one will be hidden otherwise.
7. notice the difference between the return value of operator++() and operator++(int)
8. The inheritance in the template class is special, two diff variables: dependent var and independent var
9. the operator* in iterator is necessary, otherwise we cannot simply type *itr
10. in begin() and end(), remember to use iterator/const_iterator to package them, and it's very important to figure out when to use pointer & when to use iterator in this class
11. Do not forget to change the sizeV when you add or delete any item in the list!!
*/

