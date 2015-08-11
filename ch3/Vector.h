#include <iostream>

template<typename Object>
class Vector
{
public:
	Vector(int initialSize = 0):sizeV(initialSize), capacity(initialSize+DEFAULT_CAPACITY)
	{
		head = new Object[capacity];
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
			capacity = rhs.capacity;

			head = new Object[capacity];
			tail = head + sizeV;

			for(int i=0; i<size(); ++i)
				head[i] = rhs.head[i];
		}
		
		return *this;
	}

	Object & operator[](int ind)
	{
		return head[ind];
	}

	const Object & operator[](int ind) const
	{
		return head[ind];
	}

	void push_back(const Object & obj)
	{
		if(sizeV == capacity)
			resize(capacity *= 2);
		head[sizeV++] = obj;
		++tail;
	}

	void pop_back()
	{
		--sizeV;
	}	

	void resize(int new_capacity)
	{
		Object * original = head;

		if(new_capacity>=capacity)
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

	enum {DEFAULT_CAPACITY = 16};

private:

	int sizeV;
	int capacity;
	Object * head;
	Object * tail;

	
};

/*
key points:
The public constructor of constant_iterator/iterator should not take a parameter. The constructor that takes a parameter should be protected. (out side range cannot initialize it by a pointer)
*/