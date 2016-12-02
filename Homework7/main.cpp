
#include "Graph.cpp"
#include "WeightedGraph.cpp"
#include "DirectedGraph.cpp"
#include "DirectedWeightedGraph.cpp"
#include <iostream>

//test if pointer recognizes the derived class from base class (dynamic binding)
void test(Graph* g){
	std::cout << *g <<std::endl;
	std::cout <<"MinPath from fcn:" << g->minPath(2,5) << std::endl;
}

int main(){
	/*
	//testing not connected graph
	Graph g(5,false);	//not connected graph with 5 vertexes
	g.addVertex(30);
	g.addEdge(3,30);
	g.addEdge(3,32);
	std::cout << g;
	std::cout <<"Connected: "<< g.isConnected() <<std::endl;


	//testing connected graph
	std::cout << "\n\n\nConnected graph" <<std::endl;
	Graph gConnected(7,true);
	std::cout << gConnected;
	std::cout <<"Connected: "<< gConnected.isConnected() <<std::endl;


	
	//testing const graph
	std::cout << "\n\n\nConst graph" <<std::endl;
	const Graph gConst(4,true);
	std::cout << gConst;

	//testing copy constructor
	std::cout << "\n\n\nCopied graph" <<std::endl;
	Graph gCopied(g);
	std::cout << gCopied;

	//testing copy assignment operator
	std::cout << "\n\n\nCopy-assigned graph" <<std::endl;
	gCopied = g;
	std::cout << gCopied;

	//testing move constructor
	std::cout << "\n\n\nMoved graph" <<std::endl;
	Graph gMoved = std::move(g);
	std::cout << gMoved;

	//testing move assignment constructor
	std::cout << "\n\n\nMove-assigned graph" <<std::endl;
	gMoved = std::move(gConnected);
	std::cout << gMoved;
	


	std::cout << "\n\n\nWeighted graph" <<std::endl;
	WeightedGraph weighted;
	weighted.addVertex(1);
	weighted.addVertex(2);
	weighted.addVertex(3);
	weighted.addVertex(4);
	weighted.addVertex(5);
	weighted.addVertex(6);
	weighted.addEdge(1,6,14);
	weighted.addEdge(1,2,7);
	weighted.addEdge(1,3,9);
	weighted.addEdge(2,3,10);
	weighted.addEdge(2,4,14);
	weighted.addEdge(6,3,2);
	weighted.addEdge(3,4,11);
	weighted.addEdge(6,5,9);
	weighted.addEdge(4,5,6);
	std::cout << weighted  <<std::endl;
	if(weighted.getWeight(6,5)==weighted.getWeight(5,6))
		std::cout << "True" << std::endl;

	std::cout <<"Connected: "<< weighted.isConnected() <<std::endl;
	std::cout <<"MinPath: " << weighted.minPath(5,2) << std::endl;
	std::cout <<"MinPath: " << weighted.minPath(2,5) << std::endl;


	std::cout << "\n\n\nWeighted moved graph" <<std::endl;
	Graph gMoved2 = std::move(weighted);
	std::cout << gMoved2;


	std::cout << "\n\n\nDirected graph" <<std::endl;
	DirectedGraph directed;
	directed.addVertex(1);
	directed.addVertex(2);
	directed.addVertex(3);
	directed.addVertex(4);
	directed.addVertex(5);
	directed.addVertex(6);
	directed.addEdge(1,6);
	directed.addEdge(1,2);
	directed.addEdge(1,3);
	directed.addEdge(2,3);
	directed.addEdge(2,4);
	directed.addEdge(6,3);
	directed.addEdge(3,4);
	directed.addEdge(6,5);
	directed.addEdge(4,5);
	std::cout << directed  <<std::endl;
	std::cout <<"MinPath: " << directed.minPath(1,5) << std::endl;	   // 5 is reachable but can't reach
	std::cout <<"MinPath: " << directed.minPath(5,1) << std::endl;	   // 5 is reachable but can't reach


	std::cout << "\n\n\nDirected & weighted graph" <<std::endl;
	DirectedWeightedGraph directedWeighted;
	directedWeighted.addVertex(1);
	directedWeighted.addVertex(2);
	directedWeighted.addVertex(3);
	directedWeighted.addVertex(4);
	directedWeighted.addVertex(5);
	directedWeighted.addVertex(6);
	directedWeighted.addEdge(1,6,14);
	directedWeighted.addEdge(1,2,7);
	directedWeighted.addEdge(1,3,9);
	directedWeighted.addEdge(2,3,10);
	directedWeighted.addEdge(2,4,14);
	directedWeighted.addEdge(6,3,2);
	directedWeighted.addEdge(3,4,11);
	directedWeighted.addEdge(6,5,9);
	directedWeighted.addEdge(4,5,6);
	if(directedWeighted.getWeight(5,6)==directedWeighted.getWeight(6,5))
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;
	std::cout << directedWeighted  <<std::endl;

	std::cout <<"MinPath: " << directed.minPath(1,5) << std::endl;	   // 5 is reachable but can't reach
	std::cout <<"MinPath: " << directed.minPath(5,1) << std::endl;	   // 5 is reachable but can't reach



	Graph graph2 = directedWeighted;				//OK
	Graph graph3 = weighted;						//OK
	WeightedGraph weighted2 = directedWeighted;		//OK
	WeightedGraph *tesst = new DirectedWeightedGraph(5,true);  //OK
	//DirectedGraph directed2 = weighted;					//error
	//DirectedGraph directed3 = directedWeighted;			//error
	//WeightedGraph weighted3 = directed;					//error
	//DirectedWeightedGraph directedWeighted2 = directed;   //error
	

	std::cout << "TEST FUNCTION" <<std::endl;

	DirectedWeightedGraph *g = new DirectedWeightedGraph;
	g->addVertex(1);
	g->addVertex(2);
	g->addVertex(3);
	g->addVertex(4);
	g->addVertex(5);
	g->addVertex(6);
	g->addEdge(1,6,14);
	g->addEdge(1,2,7);
	g->addEdge(1,3,9);
	g->addEdge(2,3,10);
	g->addEdge(2,4,14);
	g->addEdge(6,3,2);
	g->addEdge(3,4,11);
	g->addEdge(6,5,9);
	g->addEdge(4,5,6);
	test(g);
	delete g;


	DirectedGraph *g2 = new DirectedGraph;
	g2->addVertex(1);
	g2->addVertex(2);
	g2->addVertex(3);
	g2->addVertex(4);
	g2->addVertex(5);
	g2->addVertex(6);
	g2->addEdge(1,6);
	g2->addEdge(1,2);
	g2->addEdge(1,3);
	g2->addEdge(2,3);
	g2->addEdge(2,4);
	g2->addEdge(6,3);
	g2->addEdge(3,4);
	g2->addEdge(6,5);
	g2->addEdge(4,5);
	test(g2);
	delete g2;


	std::cout << "\n\nCONSTRUCTOR TESTINg" <<std::endl;
	
	WeightedGraph weighted4(10,true);
	std::cout << weighted4 <<std::endl;

	DirectedGraph directed4(7,true);
	std::cout << directed4 <<std::endl;

	DirectedWeightedGraph directedWeighted3(7,true);
	std::cout << directedWeighted3 <<std::endl;
*/

	WeightedGraph weighted4(10,true);

	std::cout << "LAMBDA FUNCTIONS" <<std::endl;
	std::cout << "printEdgesLongerThan" <<std::endl;
	weighted4.printEdgesLongerThan(100);

	std::cout << "\n\nprintAccordingToPredicate" <<std::endl;
	auto minWeightLambda = [] (const std::map<int,std::list<std::pair<int, int>>>& adjacencyList, const int& desiredWeight) {
		for(const auto& vertexEdgesPair : adjacencyList){
			std::cout << "Vertice " << vertexEdgesPair.first << ":" << std::endl;
			for(const auto& edge : vertexEdgesPair.second){
				//print only if the weight of edge is bigger than chosen value
				if(edge.second > desiredWeight)
					std::cout  << "\t" << edge.first << "-" << edge.second << std::endl;
			}
			std::cout  << std::endl;
		}
    };
    weighted4.printAccordingToPredicate(std::bind(minWeightLambda,std::placeholders::_1,100));


    std::cout << "\n\nprintAccordingToPredicate2" <<std::endl;
    int minWeight = 100;
    auto minWeightLambda2 =  [&minWeight](const std::map<int,std::list<std::pair<int, int>>>& adjacencyList){
    	for(const auto& vertexEdgesPair : adjacencyList){
			std::cout << "Vertice " << vertexEdgesPair.first << ":" << std::endl;
			for(const auto& edge : vertexEdgesPair.second){
				//print only if the weight of edge is bigger than chosen value
				if(edge.second > minWeight)
					std::cout  << "\t" << edge.first << "-" << edge.second << std::endl;
			}
			std::cout  << std::endl;
		}
    };
    weighted4.printAccordingToPredicate2(minWeightLambda2);

    std::cout << "\n\nprintPrimeNumberEdges" <<std::endl;
	weighted4.printPrimeNumberEdges();
    //weighted4.printAccordingToPredicate(std::bind(minWeightForVertex,std::placeholders::_1,100));

	return EXIT_SUCCESS;
}
