#include "MySharedPointer.cpp"
#include "MyUniquePointer.cpp"

MySharedPointer test(){
	return MySharedPointer(3,3);
};

MySharedPointer testMove(){
	return MySharedPointer(4,4);
};

MyUniquePointer testMoveUnique(){
	return MyUniquePointer(40,40);
};

int main(){


	MySharedPointer a (1,1);
	//copy constructor
	MySharedPointer b = a;

	MySharedPointer c (2,2);
	//copy assign operator
	c = a;

	std::cout << b;
	std::cout << a;

	//a.~MySharedPointer();   //Calling a destructor releases the resources owned by the object, but it does not release the memory allocated to the object itself
	c.reset();

	std::cout << b;

	std::cout <<std::endl<< "FUNCTION" <<std::endl;
	MySharedPointer d (test());
	MySharedPointer e = d;
	std::cout << e;


	//move assign operator
	std::cout <<std::endl<< "MOVE" <<std::endl;
	MySharedPointer f;
	f = testMove();
	e=f;
	std::cout << f;
	//e.reset(new int(10));
	std::cout << f;
	

	std::cout <<std::endl<< "UNIQUE POINTER" <<std::endl;
	MyUniquePointer z (10,10);
	std::cout << z;
	z.reset(20,20);

	MyUniquePointer x (testMoveUnique());
	std::cout << x;
	//x = std::move(z);

	//move assign operator
	//MyUniquePointer y;
	//y = testMoveUnique();
	//std::cout << y;
	//z.reset();

	std::cout <<std::endl<< "DESTRUCTORS" <<std::endl;
}