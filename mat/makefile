all : MySmartPointers

MySmartPointers: MySharedPointer.o MyMain.o
	g++ -o MySmartPointers MyMain.o 
	valgrind --leak-check=yes ./MySmartPointers


MyMain.o: main.cpp
	g++ -c main.cpp -o MyMain.o -std=c++11 

MySharedPointer.o: MySharedPointer.cpp
	g++ -c -o MySharedPointer.o MySharedPointer.cpp -std=c++11 


clean:
	rm MySmartPointers MySharedPointer.o MyMain.o



