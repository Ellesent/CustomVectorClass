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
	MyVector(int size = 1)
	{
		values = new  T[size];
		numElements = 0;
		this->size = size;
	}

	int getSize()
	{
		return size;
	}

	int getNumElements()
	{
		return numElements;
	}

	typedef const T * const_iterator;
	typedef T* iterator;
	
	iterator begin() 
	{
		return &values[0];
	}

	iterator end()
	{
		return &values[numElements];
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

		for (int i = index; i < numElements; i++)
		{  
			values[i] = values[i + 1];
		}
		numElements--;
		
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

		cout << endl;
	}

	// Insert element at a specific index
	void insertAt(unsigned long index, T value)
	{
		if (numElements >= size)
		{
			increase_size(size * 2);
		}

			
		for (int i = index; i <= numElements + 1; i++)
		{
				T hold = values[i];
				values[i] = value;
				value = hold;
		}

		numElements++;

	}

	// reset the vector
	void reset()
	{
		values = NULL;
		delete[] values;
		numElements = 0;
		values = new T[size];

	}

	// Append vector onto this vector
	void append(MyVector &vector)
	{
		if ((numElements + vector.getNumElements()) > size)
		{
			increase_size(size * 2 + vector.getNumElements());
		}

		for (int i = 0; i < vector.numElements; i ++)
		{
			push_back(vector[i]);
		}
	}

	// Sort the Vector - 1 is sort descending, otherwise sort ascending (standard is 0)
	void sort(function<int(T, T)> compare, int order)
	{
		// Do descending sort order

		if (order == 1)
		{
			for (int j = 0; j < numElements - 1; j++)
			{
				for (int i = 0; i < numElements - 1; i++)
				{
					T greater = compare(values[i], values[i + 1]);

					if (greater == values[i + 1])
					{
						T hold = values[i];
						values[i] = values[i + 1];
						values[i + 1] = hold;

					}
				}
			}
		}

		// do ascending order
		else
		{
			for (int j = 0; j < numElements - 1; j++)
			{
				for (int i = 0; i < numElements - 1; i++)
				{
					T greater = compare(values[i], values[i + 1]);

					if (greater == values[i])
					{
						T hold = values[i];
						values[i] = values[i + 1];
						values[i + 1] = hold;

					}
				}
			}
		}
	}

	// Reverse the Vector
	void reverse()
	{
		T *newArray = new T[size];

		for (int i = 0; i < numElements; i++)
		{
			newArray[i] = values[numElements - i - 1];
		}
		delete[] values;
		values = newArray;
	}

	// Allow vector indexes to be accessed with brackets
	T& operator[](int i)
	{
		if (i >= numElements)
		{
			throw exception("Out of Bounds");
		}
		return values[i];
	}

};

// Prototypes
void printInt(int i);
void printChar(char c);
int intCompare(int x, int y);

const int SORT_ASCENDING = 0;
const int SORT_DESCENDING = 1;
int main()
{
	MyVector<int> test;

	// Test adding to the vector
	test.push_back(4);
	test.push_front(5);
	test.push_back(2);
	test.push_front(1);
	test.push_back(6);

	cout << "Printing intial Vector..." << endl << endl;
	test.print(0, 10, printInt);

	
	// test removing at certain location
	test.removeAt(1);
	cout << "Printing vector when index 1 is removed..." << endl << endl;
	test.print(0, 10, printInt);

	//Test popping from Vector and returning last item
	int pop = test.pop();
	cout << "Testing popping from bottom of vector and returning that element..." << endl << endl;
	cout << "From Pop: " << pop << endl << endl;
	test.print(0, 10, printInt);

	//Test inserting at a certain index
	test.insertAt(2, 10);
	
	cout << "Testing inserting the number 10 at index 2..." << endl << endl;
	test.print(0, 10, printInt);

	// Testing append using second vector
	MyVector<int> append; 

	append.push_front(100);
	append.push_back(101);
	append.push_back(100);
	append.push_back(8);
	append.push_back(1001);
	append.push_front(99);

	cout << "Printing second vector" << endl << endl;
	append.print(0, 10, printInt);

	test.append(append);

	cout << "Printing original vector with second vector appended to it" << endl << endl;
	test.print(0, 50, printInt);

	//Testing descending sort on first vector
	test.sort(intCompare, SORT_DESCENDING);

	cout << "Printing the first vector in descending order..." << endl << endl;
	test.print(0, 50, printInt);

	//Testing ascending order on a new vector
	MyVector<int> sort;
	sort.push_back(565);
	sort.push_front(1001);
	sort.push_back(2);
	sort.push_back(68);
	sort.push_front(5678);
	sort.push_back(42);

	cout << "Printing new vector..." << endl << endl;
	sort.print(0, 50, printInt);
	cout << "Printing new vector in ascending order..." << endl << endl;
	sort.sort(intCompare, SORT_ASCENDING);
	sort.print(0, 50, printInt);

	//Testing reversing the sorted vector
	cout << "Reversing the sorted vector..." << endl << endl;
	sort.reverse();
	sort.print(0, 50, printInt);


	//Testing resetting the vector
	test.reset();
	cout << "Resetting the vector (nothing should be printed)" << endl << endl;
	test.print(0, 10, printInt);



    return 0;
}

// Function for printing Ints
void printInt(int i)
{
	cout << i << endl;
}
void printChar(char c)
{
	cout << c << endl;
}

// Compare that returns the biggest number
int intCompare(int x, int y)
{
	if (x > y)
	{
		return x;
	}

	else
	{
		return y;
	}
}


