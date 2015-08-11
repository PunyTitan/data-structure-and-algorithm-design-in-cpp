#include <iostream>

template<typename Object>
class Vector
{
private:
	class constant_iterator
	{
	public:
		constant_iterator():current(NULL)
		{}

		const Object & operator*() const
		{
			return retrieve();
		}

		constant_iterator & operator++()
		{
			++current;
			return *this;
		}

		constant_iterator operator++(int)
		{
			constant_iterator itr(current);
			++current;
			return itr;
		}

		bool operator==(const constant_iterator & rhs) const
		{
			if(current == rhs.current)
				return true;
			else
				return false;
		}

		bool operator!=(const constant_iterator & rhs) const
		{
			return !(*this == rhs);
		}


	protected:
		Object * current;

		constant_iterator(Object * ptr):current(ptr)
		{}

		Object & retrieve() const
		{
			return *current;
		}

		friend class Vector<Object>;
	};

	class iterator : public constant_iterator
	{
	public:
		iterator & operator++()
		{
			++(this->current);
			return *this;
		}

		iterator operator++(int)
		{
			iterator itr(this->current);
			++(this->current);
			return itr;
		}

		Object & operator*()
		{
			return this->retrieve();
		}

		const Object & operator*() const
		{
			return constant_iterator::operator*();
		}


		
	protected:
		iterator(Object * ptr):constant_iterator(ptr)
		{}

		friend class Vector<Object>;
	};

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

	constant_iterator begin() const
	{
		return constant_iterator(head);
	}

	iterator begin()
	{
		return iterator(head);
	}

	constant_iterator end() const
	{
		return constant_iterator(tail);
	}

	iterator end()
	{
		return iterator(tail);
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