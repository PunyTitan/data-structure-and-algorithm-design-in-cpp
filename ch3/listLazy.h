#include <iostream>
#include <typeinfo>

template<typename Object>
class listLazy
{
private:
	struct Node
	{
		Object item;
		Node *left;
		Node *right;
		bool alive;

		Node(const Object & obj = Object(), Node *lp = NULL, Node *rp = NULL, bool al = true)
		:item(obj), left(lp), right(rp), alive(al){}
	};


public:

	class const_iterator
	{
	public:
		const_iterator():current(NULL)
		{}

		const_iterator findNextAlive() const
		{
			Node * ptr = current;

			while(ptr->right != tail)
			{
				ptr = ptr->right;
				if(ptr->alive)
					return *const_iterator(ptr, this);
			}

			return const_iterator(tail, this);
		}

		const_iterator findPrevAlive() const
		{
			Node * ptr = current;		

			while(ptr->left != head)
			{
				ptr = ptr->left;
				if(ptr->alive)
					return const_iterator(ptr, this);
			}	

			return const_iterator(head, this);
		}


		const_iterator & operator++()
		{
			Node * ptr = current;

			while(ptr->right != tail)
			{
				ptr = ptr->right;
				if(ptr->alive)
					break;
			}

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
			Node * ptr = current;		

			while(ptr->left != head)
			{
				ptr = ptr->left;
				if(ptr->alive)
					break;
			}	
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
		listLazy<Object> *currentList;


		const_iterator(Node *ptr, listLazy<Object> * lst):current(ptr), currentList(lst)
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

	friend class listLazy<Object>;
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

		iterator findNextAlive()
		{
			Node * ptr = this->current;

			while(ptr->right != tail)
			{
				ptr = ptr->right;
				if(ptr->alive)
					return *iterator(ptr, this);
			}

			return iterator(tail, this);
		}

		iterator findPrevAlive()
		{
			Node * ptr = this->current;		

			while(ptr->left != head)
			{
				ptr = ptr->left;
				if(ptr->alive)
					return iterator(ptr, this);
			}	

			return iterator(head, this);
		}

		iterator & operator++()
		{
			Node * ptr = this->current;

			while(ptr->right != tail)
			{
				ptr = ptr->right;
				if(ptr->alive)
					break;
			}

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
			Node * ptr = this->current;		

			while(ptr->left != head)
			{
				ptr = ptr->left;
				if(ptr->alive)
					break;
			}	
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
		iterator(Node *ptr, listLazy<Object> *lst):const_iterator(ptr, lst)
		{}

		friend class listLazy<Object>;

	};

	listLazy()
	{
		init();
	}

	~listLazy()
	{
		clear();
		delete head;
		delete tail;
	}

	const listLazy & operator=(const listLazy & rhs)
	{
		if(this == &rhs)
			return *this;
		
		clear();

		for(const_iterator rhs_begin = rhs.begin(); begin != rhs.end(); ++rhs_begin)
		{
			push_back(*rhs_begin);
		}
	}

	listLazy(const listLazy & rhs)
	{
		init();
		*this = rhs;
	}

	const_iterator begin() const
	{
		return const_iterator(head, this).findNextAlive();
	}

	iterator begin()
	{
		return iterator(head, this).findNextAlive();
	}

	const_iterator end() const
	{
		return const_iterator(tail, this);
	}

	iterator end()
	{
		return iterator(tail, this);
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
		return insert(obj, iterator(tail, this));
	}

	iterator push_front(const Object & obj)
	{
		return insert(obj, iterator(head->right, this));
	}

	void pop_front()
	{
		iterator begin_itr = iterator(head, this);
		erase(begin_itr.findNextAlive());
	}

	void pop_back()
	{
		iterator end_itr = iterator(tail, this);
		erase(end_itr.findPrevAlive());
	}

	const Object & front() const
	{
		const_iterator begin_itr = const_iterator(head, this);
		if(empty())
		{
			std::cout<<"Error: Empty list."<<std::endl;
			return *const_iterator(head, this);
		}			

		return *(begin_itr.findNextAlive());
	}

	Object & front()
	{
		iterator begin_itr = iterator(head, this);
		if(empty())
		{
			std::cout<<"Error: Empty list."<<std::endl;
			return *iterator(head, this);
		}			

		return *(begin_itr.findNextAlive());
	}

	const Object & back() const
	{
		const_iterator end_itr = const_iterator(tail, this);
		if(empty())
		{
			std::cout<<"Error: Empty list."<<std::endl;
			return *end_itr;
		}			

		return *(end_itr.findPrevAlive());
	}

	Object & back()
	{
		iterator end_itr = iterator(tail, this);
		if(empty())
		{
			std::cout<<"Error: Empty list."<<std::endl;
			return *end_itr;
		}			

		return *(end_itr.findPrevAlive());
	}

	iterator insert(const Object & obj, iterator itr)
	{
		Node *ptr = itr.current;
		if(ptr->left->alive)
		{
			++sizeV;
			return iterator(ptr->left = ptr->left->right = new Node(obj, ptr->left, ptr), this);
		}
		else
		{
			--deadV;
			++sizeV;
			ptr->left->item = obj;
			ptr->left->alive = true;
			return iterator(ptr->left, this);
		}
		
	}

	iterator erase(iterator itr)
	{
		Node *ptr = itr.current;

		if(ptr->alive)
		{
			--sizeV;
			++deadV;
			ptr->alive = false;	
		}
			
		iterator rtr_itr = itr.findNextAlive();


		if(sizeV == deadV && sizeV != 0)
			cleanDead();

		return rtr_itr;
	}


	iterator erase(iterator from, iterator to)
	{
		while(from != to)
		{
			from = erase(from);
		}
	}

	//O(n)
	void cleanDead()
	{
		Node * ptr = head->right;
		Node * del_ptr = NULL;
		while(ptr->right != tail)
		{
			if( !(ptr->right->alive) )
			{
				del_ptr = ptr->right;
				ptr->right = del_ptr->right;
				delete del_ptr;
			}
			else
				ptr = ptr->right;
		}

		/*aliveHead = head;
		aliveTail = tail;*/
	}

	void print() 
	{
		for(const_iterator begin_itr=begin(); begin_itr!=end(); ++begin_itr)
			std::cout<<*begin_itr<<" ";
		std::cout<<"\n";
	}

private:

	int sizeV;
	int deadV;
	Node *head;
	Node *tail;

	void init()
	{
		sizeV = 0;
		deadV = 0;
		head = new Node();
		tail = new Node();

		head.alive = true;
		tail.alive = true;

		head->right = tail;
		tail->left = head;
	}
	
};


/*
Weakpoint of this method:
1. When sizeV == 2 and deadV == 0, if will be costly to erase and insert alternatively
2, When both sizeV and deadV are large, it will be space wasteful

Strength of this method:
1. We can reuse the "deleted" node when insert
*/