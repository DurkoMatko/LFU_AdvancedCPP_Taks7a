#include "MySharedPointer.h"
#include <stddef.h>
#include <string>
#include <iostream>



//bit shift operator overload instead of printGraph() method
std::ostream& operator<<(std::ostream& os,const MySharedPointer& msp)
{
    os << "MySharedPointer pointing to "  << *msp.pointer << " of size " << *msp.rows << "x" << *msp.cols << "(refenenced " << *msp.refs << " times)" << std::endl;
    return os;
}

//copy assign operator
MySharedPointer &MySharedPointer::operator=(const MySharedPointer& ptr) noexcept{
	std::cout << "copy assign operator" << std::endl;

	//if they point to the same memory - no need to do anything cuz they already share the pointed object
	if(this->pointer == ptr.pointer){
		return *this;
	}
	this->clear();
	this->pointer = ptr.pointer;
	this->pointer[0] = ptr.pointer[0];
	this->rows = ptr.rows;
	this->cols = ptr.cols;
	this->refs = ptr.refs;
	*this->refs = *this->refs +1;
	return *this;
}

//move assign operator
MySharedPointer &MySharedPointer::operator=(MySharedPointer&& ptr) noexcept{
	std::cout << "move assign operator" <<std::endl;
	//"unpoint" from previous value
	if(refs != nullptr)		//if moving to yet unassigned empty pointer
		this->clear();
	//point to new place
	this->pointer = ptr.pointer;
	this->pointer[0] = ptr.pointer[0];
	this->refs = ptr.refs;
	this->cols = ptr.cols;
	this->rows = ptr.rows;
	//have to increase number of refs, cuz rvalue didn't do it
	this->IncreaseReferences();
	//delete source
	ptr.pointer=nullptr;

	return *this;
}


//nothing allocated - can get value later by copy/move and in both cases will just point to already allocated memory by other block of code
MySharedPointer::MySharedPointer() : pointer(nullptr),  refs(nullptr), rows(nullptr), cols(nullptr) {
	//const
	std::cout << "Default MySharedPointer constructor " <<std::endl;
}

MySharedPointer::MySharedPointer(int rowws, int columns) :  refs(new int(1)) , rows(new int(rowws)), cols(new int(columns)){
	//const
	pointer = new int*[*cols];
	pointer[0] = new int[*cols * *rows];
	for (int i = 1; i < *cols; i++)
	    pointer[i] = pointer[i-1] + *rows;
	std::cout << "constructing MySharedPointer of size " << *rows << " x " << *cols <<std::endl;
}

//copy constructor
MySharedPointer::MySharedPointer(MySharedPointer& ptr){
	std::cout <<"copy constructor" << std::endl;
	refs = ptr.refs;
	rows = ptr.rows;
	cols = ptr.cols;
	pointer = ptr.pointer;
	this->IncreaseReferences();
}

//move constructor
MySharedPointer::MySharedPointer(MySharedPointer&& g) noexcept{
	std::cout << "MySharedPointer move constructor";
}

//destructor
MySharedPointer::~MySharedPointer(){
	std::cout << "MySharedPointer destructor" <<  std::endl;
    clear();
}

void MySharedPointer::clear(){
	//if this is the last reference to the object, delete object itself and references counter as well
	if (!--*refs){
			std::cout <<"deleting int " << *pointer << " from heap" <<std::endl;
            delete[] pointer[0];
            delete[] pointer;
            delete refs;
            delete rows;
            delete cols;
            pointer[0] = nullptr;
            pointer = nullptr;
    }
}


void MySharedPointer::IncreaseReferences(){
	*refs = *refs +1;
}

/*
void MySharedPointer::reset(int **matrix){
	std::cout << "Reseting MySharedPointer from " << *this->pointer << " to " << *matrix << std::endl;

	//if they point to the same memory - no need to do anything cuz they already share the pointed object
	if(this->pointer == matrix){
		return;
	}
	//forget about last one
	this->clear();
	//point to new one
	this->pointer = matrix;
	this->pointer[0] = matrix[0]
	this->refs = new int(1);
}
*/
void MySharedPointer::reset(){
	this->clear();
}
