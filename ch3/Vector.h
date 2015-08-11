#include <iostream>

template<typename Object>
class Vector
{
public:
	Vector(int initialSize = 0):sizeV(initialSize), capacityV(initialSize+DEFAULT_CAPACITY)
	{
		head = new Object[capacityV];
		tail = head + initialSize;
	}

	Vector(const Vector & rhs):head(NULL), tail(NULL)
	{
		operator=(rhs);
	}

	~Vector()
	{
		delete [] head;
	}

	const Vector & operator=(const Vector & rhs)
	{
		if(this != &rhs)
		{
			delete [] head;
			sizeV = rhs.size();
			capacityV = rhs.capacityV;

			head = new Object[capacityV];
			tail = head + sizeV;

			for(int i=0; i<size(); ++i)
				head[i] = rhs.head[i];
		}
		
		return *this;
	}

	Object & operator[](int ind)
	{
		if(ind>=0 && ind<size())
			return head[ind];
		else
			return head[0];
	}

	const Object & operator[](int ind) const
	{
		if(ind>=0 && ind<size())
			return head[ind];
		else
			return head[0];
	}

	void push_back(const Object & obj)
	{
		if(sizeV == capacityV)
			resize(capacityV *= 2);
		head[sizeV++] = obj;
		++tail;
	}

	void pop_back()
	{
		--sizeV;
	}	

	void resize(int new_capacity)
	{
		std::cout<<"resize called\n";

		Object * original = head;

		if(new_capacity>=capacityV)
			head = new Object[new_capacity];
		tail = head + sizeV;		

		for(int i=0; i<sizeV; ++i)
			head[i] = original[i];

		delete [] original;
	}

	typedef Object* iterator;
	typedef const Object* constant_iterator; 

	constant_iterator begin() const
	{
		return head;
	}

	iterator begin()
	{
		return head;
	}

	constant_iterator end() const
	{
		return tail;
	}

	iterator end()
	{
		return tail;
	}

	int size() const
	{
		return sizeV;
	}

	int capacity() const
	{
		return capacityV;
	}

	bool empty() const
	{
		return size() == 0;
	}

	void print() const
	{
		for(constant_iterator itr = begin(); itr != end(); ++itr)
			std::cout<<*itr<<" ";
		std::cout<<"\n";
	}

	iterator insert(const Object & obj, iterator itr)
	{
		if(sizeV == capacityV)
			resize(capacityV *= 2);
		for(iterator mod_itr = end(); mod_itr != itr; --mod_itr)
			*mod_itr = *(mod_itr-1);
		*itr = obj;
		++sizeV;
		++tail;
		return itr+1;
	}

	//return the iterator of the element after the deleted one.
	iterator erase(iterator itr)
	{
		for(iterator mod_itr = itr; mod_itr+1 != end(); ++mod_itr)
			*mod_itr = *(mod_itr+1);
		
		--sizeV;
		--tail;
		return itr;
	}

	//return the iterator of the element after the last deleted one.
	iterator erase(iterator from, iterator to)
	{
		int offset = to-from;

		if(offset <= 0)
		{
			std::cout<<"The second parameter should be larger that the first.\n";
			return from;
		}

		for(; from+offset != end() && from != to; ++from)
			*from = *(from+offset);

		sizeV -= offset;
		tail -= offset;

		return from;			

	}

	enum {DEFAULT_CAPACITY = 16};

private:

	int sizeV;
	int capacityV;
	Object * head;
	Object * tail;

	
};

/*
key points:
The public constructor of constant_iterator/iterator should not take a parameter. The constructor that takes a parameter should be protected. (out side range cannot initialize it by a pointer)
*/