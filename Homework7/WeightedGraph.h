#ifndef WEIGHTED_GRAPH_H_INCLUDED
#define WEIGHTED_GRAPH_H_INCLUDED

#include "Graph.h"

class WeightedGraph : virtual public Graph {
	public:
		WeightedGraph();
		WeightedGraph(unsigned n, bool isConnected);
		void print(std::ostream& os) const;
		void addEdge(int firstVertex, int secondVertex, int dist = 1);
		int getWeight(int v, int w) const;
		void printEdgesLongerThan(int desiredWeight) const;
		void printPrimeNumberEdges() const;
	protected:
	private:
};


#endif //WEIGHTED_GRAPH_H_INCLUDED