#include "DirectedGraph.h"
#include <iostream>
#include <climits>
#include <limits.h>


DirectedGraph::DirectedGraph()
{
    std::cout << "Derived directed graph constructor without parameters" <<std::endl;
}

//just to use overrided method addEdge()
DirectedGraph::DirectedGraph(unsigned n, bool isConnected){
	std::cout << "Derived directed graph constructor with parameters" <<std::endl;

	int vertex1,vertex2,dist,numberOfEdges;

	//define random generators needed
	std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> vertexChooser(0, n-1);
    if(isConnected){
    	// if connected, number of edges must be min n-1
    	std::uniform_int_distribution<> numberOfEdgesGenerator(n-1, n*(n-1)/2); 
    	numberOfEdges = numberOfEdgesGenerator(eng);
    }
    else{
    	// if not connected number of edges is not important
    	std::uniform_int_distribution<> numberOfEdgesGenerator(0, n*(n-1)/2); 
    	numberOfEdges = numberOfEdgesGenerator(eng);
    }
    
    //create n number of vertexes
	for(int i=0;i<n;i++){
		this->addVertex(i);
	}

	if(isConnected){
		/*start from vertex n.1 and always generate an edge for current index vertex*/	
	    for(int i=1;i<n;i++){
			vertex2 = vertexChooser(eng)%i;			//modulo needed to stay in bounds of already created vertices
			
	    	//vertexes of edge can't be the same && edge can't already be present in the graph
	    	while(i==vertex2 || this->edgeExists(i,vertex2)){
	    		vertex2 = vertexChooser(eng)%i;
	    	}
	    	
	    	this->addEdge(i,vertex2);

	    	//decrement number of left edges to generate
	    	numberOfEdges--;
		}
	}
    while(numberOfEdges>0){
    	vertex1 = vertexChooser(eng);
    	vertex2 = vertexChooser(eng);
    	
        //while chosen vertex1 already has edges to all vertexes, choose new vertex1
    	while(adjacencyList.at(vertex1).size()==n-1){
    		vertex1 = vertexChooser(eng);
    	}
    	//vertexes of edge can't be the same one && edge can't already be in the graph
    	while(vertex1==vertex2  || this->edgeExists(vertex1,vertex2)){
    		vertex2 = vertexChooser(eng);
    	}

    	//add edge between 2 randomly chosen edges
    	this->addEdge(vertex1,vertex2);

    	//decrement number of left edges to generate
    	numberOfEdges--;
    }
}


void DirectedGraph::addEdge(int firstVertex, int secondVertex){
	try{
		if(this->vertexExists(firstVertex) && this->vertexExists(secondVertex)){
			adjacencyList.at(firstVertex).push_back(std::make_pair(secondVertex,1));
			//adjacencyList.at(secondVertex).push_back(std::make_pair(firstVertex,dist));	
		}
		else{
			throw std::out_of_range("Vertex does not exist");	
		}
	}
	catch(const std::out_of_range& oor){
		std::cerr << "Out of Range error - addEdge(" << firstVertex << ", " << secondVertex << ") " << oor.what() <<  '\n';
	}
}