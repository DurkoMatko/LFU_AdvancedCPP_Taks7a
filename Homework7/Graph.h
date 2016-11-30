#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <string>
#include <cstdio>
#include <list>
#include <map>
#include <vector>
#include <cstddef>
#include <random>

class Graph{
	public:
		Graph();
		Graph(unsigned n, bool isConnected);
		Graph(const Graph& g) noexcept;	//copy constructor
		Graph(Graph&& g) noexcept;   //move constructor
		virtual ~Graph() noexcept;
		bool vertexExists(int node) const;			//existNode
		bool edgeExists(int firstVertex,int secondVertex) const;
		void addVertex(int id);
		std::vector<int> getVertices();
		virtual void addEdge(int firstVertex, int secondVertex);
		bool isConnected() const;
		void search(int firstVertex, int secondVertex) const;
	    int minPath(int source,int target) const;
		virtual void print(std::ostream& os) const;							//virtual print method to distinguish between weighted and non-weighted print (used by << operator defined in base Graph)
		friend std::ostream& operator<<(std::ostream& os, const Graph& g);	//needs to be friend cuz it's defined outside of class and needs to access ajacencyList
		friend std::ostream& operator<<(std::ostream& os, Graph& g);		//needs to be friend cuz it's defined outside of class and needs to access ajacencyList
		Graph& operator=(const Graph& g) noexcept;
		Graph& operator=(Graph&& g) noexcept;

	protected:
		std::map<int,std::list<std::pair<int, int>>> adjacencyList;	
	private:
};


#endif // GRAPH_H_INCLUDED