#include <stdlib.h>
#include <iostream>

#include <htd/Globals.hpp>
#include <htd/IGraph.hpp>
#include <htd/IOrderingAlgorithm.hpp>
#include <htd/ILabeledTree.hpp>
#include <htd/Helpers.hpp>
#include <htd/MutableGraphImpl.hpp>
#include <htd/MutableHypergraphImpl.hpp>
#include <htd/MutableDirectedGraphImpl.hpp>
#include <htd/BucketEliminationTreeDecompositionAlgorithm.hpp>
#include <htd/MinFillOrderingAlgorithmImpl.hpp>
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
    htd::MutableHypergraphImpl graph(0);

    graph.addVertex();
    graph.addVertex();
    graph.addVertex();
    graph.addVertex();

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
    htd::IOrderingAlgorithm* o = new htd::MinFillOrderingAlgorithmImpl();
    //htd::IOrderingAlgorithm * o = htd::getDefaultOrderingAlgorithmImplementation();


    htd::BucketEliminationTreeDecompositionAlgorithm algo(*o);
    htd::ILabeledTree * decomp = algo.computeDecomposition(graph);

    /*
    htd::BucketEliminationTreeDecompositionAlgorithm * dc = 
      new htd::BucketEliminationTreeDecompositionAlgorithm(*o);
    
    htd::ITreeDecomposition * decomp = 
    dc->computeDecomposition(graph);*/

    /*
  std::vector<std::string> v;
  decomp->labelNames(v);
  std::cout << "names:"<< &v << "\tlen:" << v.size() << std::endl;

  for (auto& e : v){
    std::cout<< "s:" << e << std::endl;
  }
    */

  //void (MutableGraphImpl::*computeOrderding)() = &htd::MinFillOrderingAlgorithmImpl::computeOrdering;
    /*MinFillOrderingAlgorithmImpl orderingAlgoirthm = new MinFillOrderingAlgorihtmImpl();
      htd::ITreeDecomposition * decomposition = decompositionAlgorithm.computeDecomposition(graph, orderingAlgorithm);*/
    
    //
    
    if (decomp != nullptr)
    {
        std::cout << std::endl;

        //printTreeDecomposition(*decomposition);

        delete decomp;
    }
    
    return 0;
}
