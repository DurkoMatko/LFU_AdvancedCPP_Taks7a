#ifndef DIRECTED_WEIGHTED_GRAPH_H_INCLUDED
#define DIRECTED_WEIGHTED_GRAPH_H_INCLUDED

#include "WeightedGraph.h"
#include "DirectedGraph.h"

class DirectedWeightedGraph : public WeightedGraph, public DirectedGraph{
	public:
		DirectedWeightedGraph();
		DirectedWeightedGraph(unsigned n, bool isConnected);
		using WeightedGraph::print;		//to be sure weighted print is called and not directed
		void addEdge(int firstVertex, int secondVertex, int dist);
	protected:
	private:
};


#endif //DIRECTED_WEIGHTED_GRAPH_H_INCLUDED