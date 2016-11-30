#include "WeightedGraph.h"
#include <iostream>
#include <stdexcept>
#include <climits>
#include <limits.h>
#include <algorithm>

struct NameAlreadyUsedException2: public std::exception{
  virtual const char* what() const throw(){
    return "Vertice id already in use";
  }
};


WeightedGraph::WeightedGraph()
{
    std::cout << "Derived weighted constructor without parameters" <<std::endl;
}

WeightedGraph::WeightedGraph(unsigned n, bool isConnected) : Graph(n,isConnected){
	std::cout << "Derived weighted constructor with parameters" <<std::endl;

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

void WeightedGraph::print(std::ostream& os) const{
    //here I have to iterate keys - because user can add vertex with random ID
	for(auto iter = adjacencyList.cbegin(); iter != adjacencyList.cend(); ++iter){		
		os << "Vertice " << iter->first << ":" << std::endl;
		//iterate list of pairs representing edges to other vertices
		for(const auto& onePair : adjacencyList.at(iter->first)){
			os << "\t" << onePair.first << "-" << onePair.second << std::endl;
		}
		os << std::endl;
	}
}

void WeightedGraph::addEdge(int firstVertex, int secondVertex,int dist){
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

int WeightedGraph::getWeight(int v, int w) const{
	if(this->vertexExists(v) && this->vertexExists(w)){
		for(const auto& edge : adjacencyList.at(v)){
			if(edge.first == w){
				return edge.second;
			}
		}
	}
	else
		return -1;
}


void WeightedGraph::printEdgesLongerThan(int desiredWeight) const{
	std::for_each(adjacencyList.begin(), adjacencyList.end(),
				 [&](const std::pair<int,std::list<std::pair<int, int>>>& vertexEdgesPair){
					 	std::cout << "Vertice " << vertexEdgesPair.first << ":" << std::endl;
						//iterate list of pairs representing edges to other vertices
						for(const auto& edge : vertexEdgesPair.second){
							//print only if the weight of edge is bigger than chosen value
							if(edge.second > desiredWeight)
								std::cout  << "\t" << edge.first << "-" << edge.second << std::endl;
						}
						std::cout  << std::endl;
				 }
	);
}

void WeightedGraph::printPrimeNumberEdges() const{
	//loop over each vertex
	for(const auto& vertexEdgesPair : adjacencyList){
		std::cout << "Vertice " << vertexEdgesPair.first << ":" << std::endl;
		//for each edge of current vertex
		std::for_each(adjacencyList.at(vertexEdgesPair.first).begin(), adjacencyList.at(vertexEdgesPair.first).end(),
			[&](const std::pair<int,int>& edge){
				int isPrime=true;
				//if at least once divided by some value with leftovers that it's not a prime
				for(int i = 2; i <= edge.second / 2; ++i){
				    if(edge.second % i == 0){
				        isPrime = false;
				        break;
				    }
				}
				if (isPrime)
					std::cout  << "\t" << edge.first << "-" << edge.second << std::endl;
			}
		);
	}
}