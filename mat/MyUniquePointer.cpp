#include "MyUniquePointer.h"
#include <stddef.h>
#include <string>
#include <iostream>


//bit shift operator overload instead of printGraph() method
std::ostream& operator<<(std::ostream& os,const MyUniquePointer& g)
{
    os << "MyUniquePointer pointing to "  << *g.pointer << " of size " << *g.rows << "x" << *g.cols << std::endl;
    return os;
}

//move assign operator
MyUniquePointer &MyUniquePointer::operator=(MyUniquePointer&& ptr) noexcept{
	//if pointer is already pointing somewhere
	if(this->pointer!=nullptr){
		std::cout << "move assign operator from size  " << *this->rows << "x" << *this->cols << " to  " << *ptr.rows << "x" << *ptr.cols <<std::endl;
		//"unpoint" from previous value
		this->clear();
	}
	else
		std::cout << "move assign operator from unassigned to size " << *this->rows << "x" << *this->cols <<std::endl;

	//point to new place
	this->pointer = ptr.pointer;
	this->pointer[0] = ptr.pointer[0];
	this->rows = ptr.rows;
	this->cols = ptr.cols;

	//delete source
	ptr.pointer[0] = nullptr;
	ptr.pointer=nullptr;

	return *this;
}


MyUniquePointer::MyUniquePointer() : pointer(nullptr),rows(nullptr),cols(nullptr) {
	//const
	std::cout << "Default MyUniquePointer constructor " <<std::endl;
}

MyUniquePointer::MyUniquePointer(int rowws,int columns) :  rows(new int(rowws)), cols(new int(columns)){
	//const
	pointer = new int*[*cols];
	pointer[0] = new int[*cols * *rows];
	for (int i = 1; i < *cols; i++)
	    pointer[i] = pointer[i-1] + *rows;
	std::cout << "constructing MyUniquePointer od size " << *rows << " x " << *cols <<std::endl;
}

//move constructor
MyUniquePointer::MyUniquePointer(MyUniquePointer&& ptr) noexcept{
	std::cout << "MyUniquePointer move constructor ";
	this->clear();
	this->pointer = ptr.pointer;
	this->pointer[0] = ptr.pointer[0];
	this->rows = ptr.rows;
	this->cols = ptr.cols;
	ptr.pointer[0] = nullptr;
	ptr.pointer = nullptr;
}


MyUniquePointer::~MyUniquePointer() noexcept{
	std::cout << "MyUniquePointer destructor "<<  std::endl;
	this->clear();
}


void MyUniquePointer::clear(){
	delete[] pointer[0];
	delete[] pointer;
	delete this->rows;
	delete this->cols;
	//pointer[0] = nullptr;
	//pointer = nullptr;
}
void MyUniquePointer::reset(int rows, int cols){
    std::cout << "MyUniquePointer being reseted from " << *this->rows << "x"<< *this->cols << " to " << rows <<"x" <<cols <<std::endl; 
	this->clear();
	
	//forget about last one
	this->rows = new int(rows);
	this->cols = new int(cols);
	pointer = new int*[cols];
	pointer[0] = new int[cols * rows];
	for (int i = 1; i < cols; i++)
	    pointer[i] = pointer[i-1] + rows;

}

void MyUniquePointer::reset(){
	this->clear();
	this->pointer[0] = nullptr;
	this->pointer = nullptr;
}