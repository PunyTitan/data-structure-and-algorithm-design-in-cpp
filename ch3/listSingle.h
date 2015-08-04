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

		Object & operator*()
		{
			return retrieve();
		}

		const Object & operator*() const
		{
			return const_iterator::operator*();
		}

	protected:

		Object & retrieve()
		{
			return this->current->item;
		}
		
	};

	listSingle();
	~listSingle();
	
private:
	int sizeV;
	Node * head;
	Node * tail;
};


/*
key points:

1. In constructor, remember to add default value for the data members, usually you will need it.
2. Mark "const" to accessors
*/