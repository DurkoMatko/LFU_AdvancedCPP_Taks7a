#include "Graph.h"
#include <iostream>
#include <map>
#include <list>
#include <set>
#include <queue>
#include <stdexcept>
#include <vector>
#include <cstddef>
#include <random>
#include <climits>
#include <limits.h>

int test(Graph g){
	
}

struct NameAlreadyUsedException: public std::exception{
  virtual const char* what() const throw(){
    return "Vertice id already in use";
  }
};

struct GraphNotConnected: public std::exception{
  virtual const char* what() const throw(){
    return "The graph is not connected";
  }
};


//bit shift operator overload instead of printGraph() method
std::ostream& operator<<(std::ostream& os, Graph& g)
{
    g.print(os);
    return os;
}

//bit shift operator overload instead of printGraph() method
std::ostream& operator<<(std::ostream& os, const Graph& g)
{
	os <<"This graph is const" << std::endl;
    g.print(os);
    return os;
}

void Graph::print(std::ostream& os) const{
    //here I have to iterate keys - because user can add vertex with random ID
	for(auto iter = adjacencyList.cbegin(); iter != adjacencyList.cend(); ++iter){		
		os << "Vertice " << iter->first << ":" << std::endl;
		//iterate list of ints representing edges to other vertices
		for(const auto& one : adjacencyList.at(iter->first)){
			os << "\t" << one.first <<  std::endl;
		}
		os << std::endl;
	}
}

Graph::Graph()
{
    std::cout << "Base graph class constructor " << std::endl;
}

Graph::Graph(unsigned n, bool isConnected)
{
	std::cout << "Base graph class constructor with parameters" << std::endl;
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
	//generate rest of edges (connected graph) resp. all edges(unconnected graph) randomly
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

//copy constructor
Graph::Graph(const Graph& g) noexcept{
	adjacencyList.insert(g.adjacencyList.begin(),g.adjacencyList.end());
}

//move constructor
Graph::Graph(Graph&& g) noexcept{
	adjacencyList.insert(g.adjacencyList.begin(),g.adjacencyList.end());
	g.adjacencyList.clear();
}

//copy assign operator
Graph &Graph::operator=(const Graph& g) noexcept{		
	//clear previous data
	adjacencyList.clear();
	adjacencyList.insert(g.adjacencyList.begin(),g.adjacencyList.end());
	return *this;
}

//move assign operator
Graph &Graph::operator=(Graph&& g) noexcept{
	adjacencyList.clear();
    adjacencyList.insert(g.adjacencyList.begin(),g.adjacencyList.end());
	g.adjacencyList.clear();
    return *this;
}

Graph::~Graph()
{
	//dtor
}

bool Graph::vertexExists(int node) const{
	return adjacencyList.find(node) != adjacencyList.end();
}

bool Graph::edgeExists(int firstVertex,int secondVertex) const{
	for(auto& pair : adjacencyList.at(firstVertex)){
		if(pair.first == secondVertex)
			return true;
	}
	return false;
}

void Graph::addVertex(int id){
	try{
		//create new edge list for new vertex	
		if(!adjacencyList.insert(std::make_pair(id, std::list<std::pair<int, int>>())).second){				
			throw NameAlreadyUsedException();
		}
	}
	catch(const NameAlreadyUsedException& e){													//catch exception
		std::cerr << e.what() << " - id: " <<  id << std::endl;
	}
}


std::vector<int> Graph::getVertices(){
	//return all keys of adjacencyList map 
	std::vector<int> vertices;
	for (auto& pair : adjacencyList){
    	vertices.emplace_back(pair.first);
	}
	return vertices;
}

//dist always = 1
void Graph::addEdge(int firstVertex, int secondVertex){
	try{
		if(this->vertexExists(firstVertex) && this->vertexExists(secondVertex)){
			adjacencyList.at(firstVertex).push_back(std::make_pair(secondVertex,1));
			adjacencyList.at(secondVertex).push_back(std::make_pair(firstVertex,1));	
		}
		else{
			throw std::out_of_range("Vertex does not exist");	
		}
	}
	catch(const std::out_of_range& oor){
		std::cerr << "Out of Range error - addEdge(" << firstVertex << ", " << secondVertex << ") " << oor.what() <<  '\n';
	}
}


bool Graph::isConnected() const{
	//BFS implementation
	std::queue<int> Q;	
	//set is more effective then vector in looking up if contains an element
	std::set<int> visited;	
	//nodes currently or previously in queue in queue
	std::set<int> queued;	
	//random node	
	auto it = adjacencyList.begin();
	std::advance(it, rand() % adjacencyList.size());
	Q.push(it->first);

	//while queue is not empty and I haven't visited all vertices
	while(!Q.empty() && visited.size() != adjacencyList.size()){
		int current = Q.front();
		Q.pop();
		visited.insert(current);

		//get list of neighbors for currend vertex and iterate over them
		for(auto neighborIterator = adjacencyList.at(current).begin(); neighborIterator != adjacencyList.at(current).end(); ++neighborIterator){
			//if neigbor wasn't visited or isn't aready in queue,then add it to queue
			if(visited.find(neighborIterator->first) == visited.end() &&
			   queued.find(neighborIterator->first) == queued.end()){
			   		//add to queue
					Q.push(neighborIterator->first);
					queued.insert(neighborIterator->first);
			}
		}
	}

	//return if all vertexes have been visited
	return visited.size() == adjacencyList.size();
}

void Graph::search(int firstVertex,int secondVertex) const{
	//throws exception if the graph is not connected
	if(!this->isConnected())
		throw GraphNotConnected();

	//queue of pair<parent (from), child (to)>
	std::queue<std::pair<int,int>> Q;	
	Q.push(std::make_pair(firstVertex,firstVertex));
	//set is more effective then vector in looking up if contains an element
	std::set<int> visited;	
	std::set<int> queued;		//already in queue
	std::map<int,int> reconstructMap;		//child-parent map to reconstruct path
	int current;

	//while queue is not empty and I haven't visited all vertices
	while(!Q.empty() && current!=secondVertex){
		current = Q.front().second;
		Q.pop();
		visited.insert(current);
		//get list of neighbors for currend vertex and iterate over it
		for(auto neighborIterator = adjacencyList.at(current).begin(); neighborIterator != adjacencyList.at(current).end(); ++neighborIterator){
			//if neigbor wasn't visited or isn't aready in queue,then add it to queue
			if(visited.find(neighborIterator->first) == visited.end() &&
			   queued.find(neighborIterator->first) == queued.end()){
			   		//add to queue
					Q.push(std::make_pair(current,neighborIterator->first));
					reconstructMap[neighborIterator->first] = current;
					queued.insert(neighborIterator->first);
			}
		}
	}

	//reconstruct path
	std::vector<int> pathTaken;
	pathTaken.push_back(current);
	while(current!=firstVertex){
		current=reconstructMap.at(current);
		pathTaken.push_back(current);
	}
	//reverse iterate and print path
	std::cout << "Path from " << firstVertex << " to " << secondVertex << std::endl;
	for (auto it = pathTaken.rbegin(); it != pathTaken.rend(); ++it){
    	std::cout << *it;
    	if(*it != secondVertex)
    		std::cout << "->";
	}
	std::cout << std::endl;
}


int Graph::minPath(int source,int target) const{
	//create map of minimal distances to all nodes
	std::map<int,int> min_edgeCount;
	for(const auto &listElement : adjacencyList){
		min_edgeCount[listElement.first] = INT_MAX;
	}

	min_edgeCount[ source ] = 0;
	//map of <target,distance> pairs
	std::map<int,int> active_vertices;
	active_vertices.insert( std::make_pair(source,0) );

	while (!active_vertices.empty()) {
		//get first node in "queue" to inspect its edges
		int current = active_vertices.begin()->first;
		if (current == target) {
			return min_edgeCount[current];
		}
		//delete current visited one
		active_vertices.erase(current);

		//loop edges for current node
		for (const auto &edge : adjacencyList.at(current)){
			//if steps to current node + one more step < so far possible minSteps to inspected edge, then overwrite to new value
			if( (min_edgeCount[current] + edge.second) < min_edgeCount[edge.first]){
				min_edgeCount[edge.first] = min_edgeCount[current] + edge.second;
				//insert or overwrite
				active_vertices[edge.first] = min_edgeCount[edge.first];
			}
		}
	}

	return -1;
}
