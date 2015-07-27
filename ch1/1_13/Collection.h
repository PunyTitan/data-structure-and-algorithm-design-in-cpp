#include <iostream>

template <typename Object>
class Collection
{
public:
	Collection(Object dataA[], int len)
	{
		length = len;
		max = len;
		data = new Object[length];
		for(int i = 0; i<length; i++)
		{
			data[i] = dataA[i];
		}

	}

	Collection()
	{
		data = NULL;
		length = 0;
	}
	~Collection()
	{
		if (data != NULL)
		{
			delete[] data;
			data = NULL;
		}		
	}

	bool isEmpty()
	{
		return length == 0;
	}

	void makeEmpty()
	{
		length = 0;
	}

	void insert(Object item)
	{
		if (length == max)
			std::cout<<"Error: the collection is full."<<std::endl;
		else
		{
			data[length] = item;
			length++;
		}
	}

	Object remove()
	{
		if (isEmpty())
			std::cout<<"Error: the collection is empty."<<std::endl;
		else
		{
			length--;
			return data[length];
		}
	}

	bool contains(Object item)
	{
		for(int i = 0; i<length; i++)
		{
			if (data[i] == item)
				return true;
		}
		return false;
	}

private:
	int length;
	int max;
	Object *data;	
};