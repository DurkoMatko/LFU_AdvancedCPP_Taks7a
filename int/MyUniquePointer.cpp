#include "MyUniquePointer.h"
#include <stddef.h>
#include <string>
#include <iostream>


//bit shift operator overload instead of printGraph() method
std::ostream& operator<<(std::ostream& os,const MyUniquePointer& g)
{
    os << "MyUniquePointer pointing to " << *g.pointer << std::endl;
    return os;
}

//move assign operator
MyUniquePointer &MyUniquePointer::operator=(MyUniquePointer&& ptr) noexcept{
	//if pointer is already pointing somewhere
	if(this->pointer){
		std::cout << "move assign operator from " << *this->pointer << " to " << *ptr.pointer <<std::endl;
		//"unpoint" from previous value
		delete this->pointer;
	}
	else
		std::cout << "move assign operator from unassigned to " << *ptr.pointer <<std::endl;

	//point to new place
	this->pointer = ptr.pointer;
	//delete source
	ptr.pointer=nullptr;

	return *this;
}


MyUniquePointer::MyUniquePointer() : pointer(nullptr) {
	//const
	std::cout << "Default MyUniquePointer constructor " <<std::endl;
}

MyUniquePointer::MyUniquePointer(int *matrix) :  pointer(matrix){
	//const
	std::cout << "constructing MyUniquePointer for " << *matrix <<std::endl;
}

//move constructor
MyUniquePointer::MyUniquePointer(MyUniquePointer&& ptr) noexcept{
	std::cout << "MyUniquePointer move constructor ";
	this->pointer = ptr.pointer;
	ptr.pointer = nullptr;
}


MyUniquePointer::~MyUniquePointer() noexcept{
	std::cout << "MyUniquePointer destructor "<<  std::endl;
	delete pointer;
}

void MyUniquePointer::reset(int* matrix){
	//if they point to the same memory - no need to do anything cuz they already share the pointed object
	if(this->pointer == matrix){
		return;
	}
	std::cout << "MyUniquePointer being reseted from " << *this->pointer << " to " << *matrix <<std::endl;
	//forget about last one
	delete this->pointer;;
	//point to new one
	this->pointer = matrix;
}

void MyUniquePointer::reset(){
	delete this->pointer;
	this->pointer = nullptr;
}