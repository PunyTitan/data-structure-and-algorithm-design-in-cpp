#include <iostream>

template <typename Object>
class Collection
{
public:
	Collection(Object dataA[], int len)
	{
		length = len;
		max = length;
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

	Collection(const Object & item)
	{	
		copyObject(item);
	}

	const Object & operator=(const Object & item)
	{
		if(data != NULL)
			delete[] data;
		copyObject(item);

		return *this;
	}

	template <typename Comparable>
	const Object & findMax(Comparable isLessThan)
	{
		int maxIndex = 0;
		for (int i=0; i<length; i++)
		{
			if(isLessThan(data[maxIndex], data[i]))
				maxIndex = i;
		}
		return data[maxIndex];
	}

	template <typename Comparable>
	const Object & findMin(Comparable isLessThan)
	{
		int minIndex = 0;
		for (int i=0; i<length; i++)
		{
			if(isLessThan(data[i], data[minIndex]))
				minIndex = i;
		}
		return data[minIndex];
	}

private:
	int length;
	int max;
	Object *data;

	void copyObject(const Object & item)
	{
		length = item.length;
		max = length;
		data = new Object[length];
		for(int i = 0; i<length; i++)
		{
			data[i] = item.data[i];
		}
	}	
};