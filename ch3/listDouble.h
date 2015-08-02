#include <iostream>

template<typename Object>
class listDouble
{
public:

	class const_iterator
	{
		const_iterator()
		{}

		~const_iterator()
		{
			delete [] const_itr;
		}

		const_iterator operator++()
		{

		}

		const_iterator operator++(int)
		{

		}

		const Object & operator*() const
		{

		}

		bool operator==(const Object & rhs) const
		{

		}

		bool operator!=(const Object & rhs) const
		{

		}


	protected:
		Object* const_itr;

		const_iterator(Node *ptr):const_itr(ptr)
		{}

		Object & retrieve()
		{

		}

	friend class listDouble<Object>;
	};

	class iterator:const_iterator
	{

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
	struct Node
	{
		Object item;
		Node *left;
		Node *right;

		Node(const Object & obj = Object(), Node *lp = NULL, Node *rp = NULL)
		:item(obj), left(lp), right(rp){}
	};

	int sizeV;
	Node *head;
	Node *tail;
	
};

/*
key points:

Functions, which will return an item in the collection, should be implemented with an accessor and a modifier.
Two kinds of iterator, so two kinds of begin() and end()
The usage of friend in iterator class
*/

