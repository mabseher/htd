#include <stdlib.h>
#include <iostream>

#include <htd/Globals.hpp>
#include <htd/IGraph.hpp>
#include <htd/IOrderingAlgorithm.hpp>
#include <htd/ILabeledTree.hpp>
#include <htd/Helpers.hpp>
#include <htd/Graph.hpp>
#include <htd/Hypergraph.hpp>
#include <htd/DirectedGraph.hpp>
#include <htd/BucketEliminationTreeDecompositionAlgorithm.hpp>
#include <htd/MinFillOrderingAlgorithm.hpp>
#include <htd/ITreeDecomposition.hpp>
#include <htd/ITreeDecompositionAlgorithm.hpp>

using namespace htd;


//TESTING FUNCTION
int main(){
    std::size_t size = 4;
    srand(5);
    DEBUGGING_CODE(std::cout << "Allocating graph of size " << size << " ..." << std::endl;)
      //htd::MutableDirectedGraphImpl graph(size);
    DEBUGGING_CODE(std::cout << "   FINISHED!" << std::endl << std::endl;)

      /*graph.addEdge(0,1);
    graph.addEdge(1,2);
    graph.addEdge(2,3);
      */

      //bug:

    //segfaults if we set a fixed size
    htd::Hypergraph graph(4);

    //graph.addVertex();
    //graph.addVertex();
    //graph.addVertex();
    //graph.addVertex();

    graph.addEdge(1,2);
    graph.addEdge(1,3);
    graph.addEdge(1,4);
    graph.addEdge(2,3);
    graph.addEdge(2,4);
    graph.addEdge(3,4);
   
    std::cout << "#vertices:" << graph.vertexCount() << "\t #edges:" << graph.edgeCount() << std::endl;
    
    //graph.addEdge(2,3);
    //graph.addEdge(4,3);


    //htd::MinFillOrderingAlgorithmImpl* o = new htd::MinFillOrderingAlgorithmImpl();
    htd::IOrderingAlgorithm* o = new htd::MinFillOrderingAlgorithm();
    //htd::IOrderingAlgorithm * o = htd::getDefaultOrderingAlgorithmImplementation();


    htd::BucketEliminationTreeDecompositionAlgorithm algo(*o);
    htd::ITreeDecomposition * decomp = algo.computeDecomposition(graph);

    std::cout << "width=" << decomp->maximumBagSize() << std::endl;
    
    return 0;
}
