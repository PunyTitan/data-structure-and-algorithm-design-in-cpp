#include <iostream>

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

		const Object & operator*() const
		{
			return retrieve();
		}

		bool operator==(const const_iterator & rhs) const
		{
			if(current == rhs.current)
				return true;
		}

		bool operator!=(const const_iterator & rhs) const
		{
			return !(*this == rhs);
		}


	protected:
		Node *current;

		const_iterator(Node *ptr):current(ptr)
		{}

		Object & retrieve() const
		{
			return current->item;
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

		Object & operator*()
		{
			return this->retrieve();
		}

		const Object & operator*() const
		{
			return const_iterator::operator*();
		}


	protected:
		iterator(Node *ptr):const_iterator(ptr)
		{}

		friend class listDouble<Object>;

	};

	listDouble()
	{

	}

	~listDouble()
	{

	}

	const listDouble & operator=(const listDouble & rhs)
	{

	}

	listDouble(const listDouble & rhs)
	{

	}

	void init()
	{

	}

	const_iterator begin() const
	{

	}

	iterator begin()
	{

	}

	const_iterator end() const
	{

	}

	iterator end()
	{

	}

	int size() const
	{
		return sizeV;
	}
	bool empty() const
	{

	}

	void clear()
	{

	}

	iterator push_back(const Object & obj)
	{

	}

	iterator push_front(const Object & obj)
	{

	}

	void pop_front()
	{

	}

	void pop_back()
	{

	}

	const Object & front() const
	{

	}

	Object & front()
	{

	}

	const Object & back() const
	{

	}

	Object & back()
	{

	}

	iterator insert(const Object & obj, iterator itr)
	{

	}

	iterator erase(iterator itr)
	{

	}

	iterator erase(iterator begin, iterator end)
	{

	}


private:

	int sizeV;
	Node *head;
	Node *tail;
	
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

*/

