#ifndef MY_SHARED_PTR
#define MY_SHARED_PTR

#include <stddef.h>
#include <string>
#include <iostream>

class MySharedPointer{
	public:
		MySharedPointer();
		MySharedPointer(int rowws, int columns);
		MySharedPointer(MySharedPointer& ptr);		//copy constructor
		MySharedPointer(MySharedPointer&& g) noexcept; //move constructor
		virtual ~MySharedPointer() noexcept;
		void IncreaseReferences();
		void reset();
		//void reset(int* matrix);
		friend std::ostream& operator<<(std::ostream& os,const MySharedPointer& g);		//needs to be friend cuz it's defined outside of class and needs to access ajacencyList
		MySharedPointer& operator=(const MySharedPointer& ptr) noexcept;		//copy assign
		MySharedPointer& operator=(MySharedPointer&& g) noexcept;				//move assign
	private:
		void clear();
		int **pointer;
		int *rows;
		int *cols;
		int *refs;
};



#endif // MY_SHARED_PTR