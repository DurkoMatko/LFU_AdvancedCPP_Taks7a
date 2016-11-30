#include <iostream>
#include <algorithm>
#include <typeinfo>
#include <functional>

void PerformOperation(std::function<void ()> f){
	f();
}

int main(){
	std::vector<int> vector = {1,2,3,4,5,6,7,8,9};
	int v = 5;

	//passing all variables by reference
	auto iterator = std::find_if(vector.begin(),vector.end(),[&](int element){
		for(auto &a : vector){
				return a+element == v;
		}
	});
	std::cout << *iterator << std::endl;


	//passing all variables by value
	iterator = std::find_if(vector.begin(),vector.end(),[=](int element){
		for(auto &a : vector){
				return a+element == v;
		}
	});
	std::cout << *iterator << std::endl;


	//passing v and vector variables by value
	iterator = std::find_if(vector.begin(),vector.end(),[v,vector](int element){
		for(auto &a : vector){
				return a+element == v;
		}
	});
	std::cout << *iterator << std::endl;



	//passing v and vector variables by reference
	iterator = std::find_if(vector.begin(),vector.end(),[&v,&vector](int element){
		for(auto &a : vector){
				return a+element == v;
		}
	});
	std::cout << *iterator << std::endl;


	//function with lambda function as parameter
	PerformOperation(   [&vector](){std::cout << vector[0] << std::endl;}  );

	return EXIT_SUCCESS;
}