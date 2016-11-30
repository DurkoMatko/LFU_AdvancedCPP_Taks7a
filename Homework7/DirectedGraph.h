#ifndef DIRECTED_GRAPH_H_INCLUDED
#define DIRECTED_GRAPH_H_INCLUDED

#include "Graph.h"

class DirectedGraph : virtual public Graph {
	public:
		DirectedGraph();
		DirectedGraph(unsigned n, bool isConnected);
		void addEdge(int firstVertex, int secondVertex);			//not weighted so distance = 1 (1 step)
	protected:
	private:
};


#endif //DIRECTED_GRAPH_H_INCLUDED