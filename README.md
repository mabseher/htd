# htd

[![License](http://img.shields.io/badge/license-GPLv3-blue.svg)](https://www.gnu.org/copyleft/gpl.html)
[![Build Status Travis-CI](https://travis-ci.org/mabseher/htd.svg?branch=master)](https://travis-ci.org/mabseher/htd)
[![Build Status AppVeyor](https://ci.appveyor.com/api/projects/status/9pam14xyi946p21u/branch/master?svg=true)](https://ci.appveyor.com/project/mabseher/htd/branch/master)
[![Coverity Status](https://scan.coverity.com/projects/8163/badge.svg)](https://scan.coverity.com/projects/mabseher-htd)
[![Code Coverage Status](https://coveralls.io/repos/github/mabseher/htd/badge.svg?branch=master&update=1)](https://coveralls.io/github/mabseher/htd?branch=master)

**A small but efficient C++ library for computing (customized) tree and hypertree decompositions.**

**htd** is a library which does not only compute tree decompositions, it also allows to fully customize them via (custom) manipulations, labelings and optimize them based on a user-provided fitness function. The library provides efficient implementations of well-established techniques for computing tree decompositions (like bucket-elimination based on a vertex elimination ordering of the input graph) and it is optimized for large (hyper)graphs. At the current stage, **htd** is able to decompose graphs containing millions of vertices and several hundreds of thousands of (hyper)edges efficiently. 

For almost each class used in the library, **htd** provides an interface and a corresponding factory class allowing to directly influence the process of generating decompositions without having to re-invent the wheel at any place. That is, if one for instance develops a new heuristic for vertex elimination orderings there is absolutely no need to change anything in the remainder of the library in order to test its influence on the quality of bucket-elimination. (In fact, one does not even need to re-compile **htd** for such a modification as long as all interfaces are implemented properly by the new algorithm and as long as the algorithm is made available to **htd** via the corresponding factory class.)

## BUILD PROCESS

For instructions about the build process, please read the `INSTALL.md` file.

## USAGE

### Using htd via command-line interface

For using **htd** via the command-line interface there is the front-end application **htd_main**. **htd_main** provides access to basic functionality of **htd**.

A program call for **htd_main** is of the following form:

`./htd_main [-h] [-v] [-s <SEED>] [--type <DECOMPOSITION_TYPE>] [--input <FORMAT>] [--instance <PATH>] [--output <FORMAT>] [--print-progress] [--strategy <ALGORITHM>] [--preprocessing <STRATEGY>] [--triangulation-minimization] [--opt <CRITERION>] [--iterations <LIMIT>] [--patience <AMOUNT>] < $FILE`

Options are organized in the following groups:

* General Options:
  * `--help, -h :                      Print usage information and exit.`
  * `--version, -v :                   Print version information and exit.`
  * `--seed, -s <seed> :               Set the seed for the random number generator to <seed>.`

* Decomposition Options:
  * `--type <type> :                   Compute a graph decomposition of type <type>.`
    * `Permitted Values:`
      * `.) tree      : Compute a tree decomposition of the input graph. (default)`
      * `.) hypertree : Compute a hypertree decomposition of the input graph.`

* Input-Specific Options:
  * `--input <format> :                Assume that the input graph is given in format <format>.`
    * `Permitted Values:`
      * `.) gr  : Use the input format 'gr'. (default)`
      * `.) lp  : Use the input format 'lp'.`
      * `.) hgr : Use the input format 'hgr'.`

    (See [FORMATS](https://github.com/mabseher/htd/blob/master/FORMATS.md) for information about the available input formats.)
  * `--instance <instance> :           Read the input graph from file <instance>.`

* Output-Specific Options:
  * `--output <format> :               Set the output format of the decomposition to <format>.`
    * `Permitted Values:`
      * `.) td    : Use the output format 'td'. (default)`
      * `.) human : Provide a human-readable output of the decomposition.`
      * `.) width : Provide only the maximum bag size of the decomposition.`

    (See [FORMATS](https://github.com/mabseher/htd/blob/master/FORMATS.md) for information about the available output formats.)
  * `--print-progress :                Print decomposition progress.`

* Algorithm Options:
  * `--strategy <algorithm> :          Set the decomposition strategy which shall be used to <algorithm>.`
    * `Permitted Values:`
      * `.) random                   : Use a random vertex ordering.`
      * `.) min-fill                 : Minimum fill ordering algorithm (default)`
      * `.) min-degree               : Minimum degree ordering algorithm`
      * `.) min-separator            : Minimum separating vertex set heuristic`
      * `.) max-cardinality          : Maximum cardinality search ordering algorithm`
      * `.) max-cardinality-enhanced : Enhanced maximum cardinality search ordering algorithm (MCS-M)`
      * `.) challenge                : Use a combination of different decomposition strategies.`
  * `--preprocessing <strategy> :      Set the preprocessing strategy which shall be used to <strategy>.`
    * `Permitted Values:`
      * `.) none     : Do not preprocess the input graph.`
      * `.) simple   : Use simple preprocessing capabilities.`
      * `.) advanced : Use advanced preprocessing capabilities.`
      * `.) full     : Use the full set of preprocessing capabilities.`
  * `--triangulation-minimization :    Apply triangulation minimization approach.`

* Optimization Options:
  * `--opt <criterion> :               Iteratively compute a decomposition which optimizes <criterion>.`
    * `Permitted Values:`
      * `.) none  : Do not perform any optimization. (default)`
      * `.) width : Minimize the maximum bag size of the computed decomposition.`
  * `--iterations <count> :            Set the number of iterations to be performed during optimization to <count> (0 = infinite). (Default: 10)`
  * `--patience <amount>:              Terminate the algorithm if more than <amount> iterations did not lead to an improvement (-1 = infinite). (Default: -1)`

### Using htd as a developer

The following example code uses the most important features of **htd**. 

A full API documentation can be generated via `make doc` (requires [Doxygen](http://www.doxygen.org/)):

```cpp
#include <htd/main.hpp>

#include <csignal>
#include <memory>
#include <chrono>

//Create a management instance of the 'htd' library in order to allow centralized configuration.
std::unique_ptr<htd::LibraryInstance> manager(htd::createManagementInstance(htd::Id::FIRST));

/**
 *  Sample fitness function which minimizes width and height of the decomposition.
 *
 *  Width is of higher priority than height, i.e., at first, the width is minimized
 *  and if two decompositions have the same width, the one of lower height is chosen.
 */
class FitnessFunction : public htd::ITreeDecompositionFitnessFunction
{
    public:
        FitnessFunction(void)
        {

        }

        ~FitnessFunction()
        {

        }

        htd::FitnessEvaluation * fitness(const htd::IMultiHypergraph & graph,
                                         const htd::ITreeDecomposition & decomposition) const
        {
            HTD_UNUSED(graph)

            /**
              * Here we specify the fitness evaluation for a given decomposition.
              * In this case, we select the maximum bag size and the height.
              */
            return new htd::FitnessEvaluation(2,
                                              -(double)(decomposition.maximumBagSize()),
                                              -(double)(decomposition.height()));
        }

        FitnessFunction * clone(void) const
        {
            return new FitnessFunction();
        }
};

/**
 * Signal handling procedure.
 */
void handleSignal(int signal)
{
    switch (signal)
    {
        case SIGINT:
        case SIGTERM:
        {
            manager->terminate();

            break;
        }
        default:
        {
            break;
        }
    }

    std::signal(signal, handleSignal);
}

int main(int, const char * const * const)
{
    std::signal(SIGINT, handleSignal);
    std::signal(SIGTERM, handleSignal);

    std::srand(0);

    // Create a new graph instance which can handle (multi-)hyperedges.
    htd::IMutableMultiHypergraph * graph =
        manager->multiHypergraphFactory().createInstance();

    /**
     *  Add five vertices to the sample graph.
     *  The vertices of a graph are numbered
     *  in ascending order starting from 1.
     */
    graph->addVertices(5);

    // Add two edges to the graph.
    graph->addEdge(1, 2);
    graph->addEdge(2, 3);

    // Add a hyperedge to the graph.
    graph->addEdge(std::vector<htd::vertex_t> { 5, 4, 3 });

    // Create an instance of the fitness function.
    FitnessFunction fitnessFunction;

    /**
     *  This operation changes the root of a given decomposition so that the provided
     *  fitness function is maximized. When no fitness function is provided to the
     *  constructor, the constructed optimization operation does not perform any
     *  optimization and only applies provided manipulations.
     */
    htd::TreeDecompositionOptimizationOperation * operation =
        new htd::TreeDecompositionOptimizationOperation(manager.get(), fitnessFunction);

    /**
     *  Set the previously created management instance to support graceful termination.
     */
    operation->setManagementInstance(manager.get());

    /**
     *  Set the vertex selections strategy (default = exhaustive).
     *
     *  In this case, we want to select (at most) 10 vertices of the input decomposition randomly.
     */
    operation->setVertexSelectionStrategy(new htd::RandomVertexSelectionStrategy(10));

    /**
     *  Set desired manipulations. In this case we want a nice (= normalized) tree decomposition.
     */
    operation->addManipulationOperation(new htd::NormalizationOperation(manager.get()));

    /**
     *  Optionally, we can set the vertex elimination algorithm.
     *  We decide to use the min-degree heuristic in this case.
     */
    manager->orderingAlgorithmFactory()
        .setConstructionTemplate(new htd::MinDegreeOrderingAlgorithm(manager.get()));

    // Get the default tree decomposition algorithm. One can also choose a custom one.
    htd::ITreeDecompositionAlgorithm * baseAlgorithm =
        manager->treeDecompositionAlgorithmFactory().createInstance();

    /**
     *  Set the optimization operation as manipulation operation in order
     *  to choose the optimal root reducing height of the tree decomposition.
     */
    baseAlgorithm->addManipulationOperation(operation);

    /**
     *  Create a new instance of htd::IterativeImprovementTreeDecompositionAlgorithm based
     *  on the base algorithm and the fitness function. Note that the fitness function can
     *  be an arbiraty one and can differ from the one used in the optimization operation.
     */
    htd::IterativeImprovementTreeDecompositionAlgorithm algorithm(manager.get(),
                                                                  baseAlgorithm,
                                                                  fitnessFunction);

    /**
     *  Set the maximum number of iterations after which the best decomposition with
     *  respect to the fitness function shall be returned. Use value 1 to make the
     *  iterative algorithm return the first decomposition found.
     */
    algorithm.setIterationCount(10);

    /**
     *  Set the maximum number of iterations without improvement after which the algorithm returns
     *  best decomposition with respect to the fitness function found so far. A limit of 0 aborts
     *  the algorithm after the first non-improving solution has been found, i.e. the algorithm
     *  will perform a simple hill-climbing approach.
     */
    algorithm.setNonImprovementLimit(3);

    // Record the optimal maximal bag size of the tree decomposition to allow printing the progress.
    std::size_t optimalBagSize = (std::size_t)-1;

    /**
     *  Compute the decomposition. Note that the additional, optional parameter of the function
     *  computeDecomposition() in case of htd::IterativeImprovementTreeDecompositionAlgorithm
     *  can be used to intercept every new decomposition. In this case we output some
     *  intermediate information upon perceiving an improved decompostion.
     */
    htd::ITreeDecomposition * decomposition =
        algorithm.computeDecomposition(*graph, [&](const htd::IMultiHypergraph & graph,
                                                   const htd::ITreeDecomposition & decomposition,
                                                   const htd::FitnessEvaluation & fitness)
    {
        // Disable warnings concerning unused variables.
        HTD_UNUSED(graph)
        HTD_UNUSED(decomposition)

        std::size_t bagSize = -fitness.at(0);

        /**
         *  After each improvement we print the current optimal
         *  width + 1 and the time when the decomposition was found.
         */
        if (bagSize < optimalBagSize)
        {
            optimalBagSize = bagSize;

            std::chrono::milliseconds::rep msSinceEpoch =
                std::chrono::duration_cast<std::chrono::milliseconds>
                        (std::chrono::system_clock::now().time_since_epoch()).count();

            std::cout << "c status " << optimalBagSize << " " << msSinceEpoch << std::endl;
        }
    });

    // If a decomposition was found we want to print it to stdout.
    if (decomposition != nullptr)
    {
        /**
         *  Check whether the algorithm indeed computed a valid decomposition.
         *
         *  algorithm.isSafelyInterruptible() for decomposition algorithms allows to
         *  find out if the algorithm is safely interruptible. If the getter returns
         *  true, the algorithm guarantees that the computed decomposition is indeed
         *  a valid one and that all manipulations and all labelings were applied
         *  successfully.
         */
        if (!manager->isTerminated() || algorithm.isSafelyInterruptible())
        {
            // Print the height of the decomposition to stdout.
            std::cout << decomposition->height() << std::endl;
            
            // Print the size of the largest bag of the decomposition to stdout.
            std::cout << decomposition->maximumBagSize() << std::endl;
        }

        delete decomposition;
    }

    delete graph;

    return 0;
}
```

## LICENSE

**htd** is released under the GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007.

A copy of the license should be provided with the system, otherwise see [http://www.gnu.org/licenses/](http://www.gnu.org/licenses/).
