#include "DirectedWeightedGraph.h"
#include <iostream>

DirectedWeightedGraph::DirectedWeightedGraph()
{
    std::cout << "Derived directed & weighted graph constructor without parameters" <<std::endl;
}


DirectedWeightedGraph::DirectedWeightedGraph(unsigned n, bool isConnected) : DirectedGraph(n, isConnected){
	std::cout << "Derived directed & weighted graph constructor with parameters" <<std::endl;
	//define random generator needed
	std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distanceGenerator(1, 256);

	//add random values to already existing edges
	for(auto &nodeEdgesPair : adjacencyList){
		for(auto &edge : nodeEdgesPair.second){
			edge.second = distanceGenerator(eng);
		}
	}
}

void DirectedWeightedGraph::addEdge(int firstVertex, int secondVertex,int dist){
	try{
		if(this->vertexExists(firstVertex) && this->vertexExists(secondVertex)){
			adjacencyList.at(firstVertex).push_back(std::make_pair(secondVertex,dist));
			//adjacencyList.at(secondVertex).push_back(std::make_pair(firstVertex,dist));	
		}
		else{
			throw std::out_of_range("Vertex does not exist");	
		}
	}
	catch(const std::out_of_range& oor){
		std::cerr << "Out of Range error - addEdge(" << firstVertex << ", " << secondVertex << "," << dist << ") " << oor.what() <<  '\n';
	}
}


