// pate-Rinaldi__FinalHW.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <memory>
#include <functional>

using namespace std;

template <class T>
class MyVector
{
private:
	// Used to increase the size of the shared_ptr array when needed
	void increase_size(unsigned long newSize)
	{
		// Create a second array that is equal to the new size
		T * new_values = new T[newSize];

		for (int i = 0; i < size; i++)
		{
			new_values[i] = values[i];
		}

		// make the old array equal to the new array
		size = newSize;
		delete[] values;
		values = new_values;
	}

protected:
	T *values;
	int size;
	int numElements;

public:
	// Constructor with default size, or size can be passed in
	MyVector(int size = 100)
	{
		values = new  T[size];
		numElements = 0;
		this->size = size;
	}

	// Add an element to the end of the vector
	void push_back(T value)
	{
		
		if (numElements >= size)
		{
			increase_size(size * 2);
		}
		values[numElements] = value;

		numElements++;
		
	}

	// Add an element to the front of the vector
	void push_front(T value)
	{
		
		if (numElements >= size)
		{
			increase_size(size * 2);
		}

		for (int i = 0; i < size; i++)
		{
			if (values[i] != NULL)
			{
				T temp = values[i];
				values[i] = value;
				value = temp;
			}
		}

		numElements++;

		
	}

	// Remove element at certain index
	void removeAt(int index)
	{
		values[index] = NULL;

		numElements--;

		for (int i = index; i < numElements; i++)
		{
			values[index] = values[index + 1];
		}

		
	}

	// Pop last element from vector
	T pop()
	{
		T popVal = values[numElements - 1];
		values[numElements - 1] = NULL;
		numElements--;
		return popVal;
	}

	// Print stuff in Vector
	void print(unsigned long start, unsigned long count, function<void(T)> printItem)
	{
		unsigned long endIndex = start + count;
		for (unsigned long index = start; index < endIndex; index++)
		{
			if (index < numElements)
			{
				printItem(values[index]);
			}
		}
	}

	// Insert element at a specific index
	void insertAt(unsigned long index, T value)
	{
		if (numElements >= size)
		{
			increase_size(size * 2);
		}

		if (index < size)
		{
			
			for (int i = index; i < size; i++)
			{
				if (values[i] != NULL)
				{
					T hold = values[i];
					values[i] = value;
					value = hold;
				}
			}

			numElements++;

		}
	}

	// reset the vector
	void reset()
	{
		values->reset();
		values = new shared_ptr<T>[100];
	}

	// Append vector onto this vector
	void append(MyVector vector)
	{

	}

	// Sort the Vector
	T sort(function<int(T, T)> compare, int order)
	{

    }

	// Reverse the Vector
	void reverse()
	{

	}

	// Allow vector indexes to be accessed with brackets
	T& operator[](int i)
	{
		if (i < 0 || i >= n)
		{
			throw exception("Out of Bounds");
		}
		return values[i];
	}

};

void printInt(int i);
int main()
{
	MyVector<int> test;

	// Test adding to the vector
	test.push_back(4);
	test.push_front(5);
	test.push_back(2);
	test.push_front(1);
	test.push_back(6);

	test.insertAt(2, 10);
	// test printing the vector
	test.print(0, 10, printInt);

	//// test removing at certain location
	//test.removeAt(1);
	//test.print(0, 10, printInt);

	////Test popping from Vector and returning last item
	//int pop = test.pop();
	//cout << "From Pop: " << pop << endl << endl;
	//test.print(0, 10, printInt);

    return 0;
}

// Function for printing Ints
void printInt(int i)
{
	cout << i << endl;
}

