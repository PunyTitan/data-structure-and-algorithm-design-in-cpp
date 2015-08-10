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
		~constant_iterator();

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

		const Object & retrieve()
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

		iterator & operator*()
		{
			return retrieve();
		}

		constant_iterator & operator*() const
		{
			return constant_iterator::retrieve();
		}


		
	protected:
		Object & retrieve()
		{
			return *(this->current);
		}

		friend class Vector<Object>;
	};

public:
	Vector()
	{

	}

	~Vector()
	{

	}

private:

	int sizeV;
	
	
};

/*
key points:
The public constructor of constant_iterator/iterator should not take a parameter. The constructor that takes a parameter should be protected. (out side range cannot initialize it by a pointer)
*/