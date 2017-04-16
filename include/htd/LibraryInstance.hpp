/*
 * File:   LibraryInstance.hpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 *
 * Copyright 2015-2017, Michael Abseher
 *    E-Mail: <abseher@dbai.tuwien.ac.at>
 *
 * This file is part of htd.
 *
 * htd is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * htd is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
 * License for more details.

 * You should have received a copy of the GNU General Public License
 * along with htd.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef HTD_HTD_LIBRARYINSTANCE_HPP
#define HTD_HTD_LIBRARYINSTANCE_HPP

#include <htd/Id.hpp>

#include <memory>

namespace htd
{
    /**
     *  Forward declaration of factory class htd::ConnectedComponentAlgorithmFactory.
     */
    class ConnectedComponentAlgorithmFactory;

    /**
     *  Forward declaration of factory class htd::DirectedGraphFactory.
     */
    class DirectedGraphFactory;

    /**
     *  Forward declaration of factory class htd::DirectedMultiGraphFactory.
     */
    class DirectedMultiGraphFactory;

    /**
     *  Forward declaration of factory class htd::GraphDecompositionAlgorithmFactory.
     */
    class GraphDecompositionAlgorithmFactory;

    /**
     *  Forward declaration of factory class htd::GraphDecompositionFactory.
     */
    class GraphDecompositionFactory;

    /**
     *  Forward declaration of factory class htd::GraphFactory.
     */
    class GraphFactory;

    /**
     *  Forward declaration of factory class htd::HypergraphFactory.
     */
    class HypergraphFactory;

    /**
     *  Forward declaration of factory class htd::HypertreeDecompositionAlgorithmFactory.
     */
    class HypertreeDecompositionAlgorithmFactory;

    /**
     *  Forward declaration of factory class htd::HypertreeDecompositionFactory.
     */
    class HypertreeDecompositionFactory;

    /**
     *  Forward declaration of factory class htd::LabeledDirectedGraphFactory.
     */
    class LabeledDirectedGraphFactory;

    /**
     *  Forward declaration of factory class htd::LabeledDirectedMultiGraphFactory.
     */
    class LabeledDirectedMultiGraphFactory;

    /**
     *  Forward declaration of factory class htd::LabeledGraphFactory.
     */
    class LabeledGraphFactory;

    /**
     *  Forward declaration of factory class htd::LabeledHypergraphFactory.
     */
    class LabeledHypergraphFactory;

    /**
     *  Forward declaration of factory class htd::LabeledMultiGraphFactory.
     */
    class LabeledMultiGraphFactory;

    /**
     *  Forward declaration of factory class htd::LabeledMultiHypergraphFactory.
     */
    class LabeledMultiHypergraphFactory;

    /**
     *  Forward declaration of factory class htd::LabeledPathFactory.
     */
    class LabeledPathFactory;

    /**
     *  Forward declaration of factory class htd::LabeledTreeFactory.
     */
    class LabeledTreeFactory;

    /**
     *  Forward declaration of factory class htd::MultiGraphFactory.
     */
    class MultiGraphFactory;

    /**
     *  Forward declaration of factory class htd::MultiHypergraphFactory.
     */
    class MultiHypergraphFactory;

    /**
     *  Forward declaration of factory class htd::OrderingAlgorithmFactory.
     */
    class OrderingAlgorithmFactory;

    /**
     *  Forward declaration of factory class htd::PathDecompositionAlgorithmFactory.
     */
    class PathDecompositionAlgorithmFactory;

    /**
     *  Forward declaration of factory class htd::PathDecompositionFactory.
     */
    class PathDecompositionFactory;

    /**
     *  Forward declaration of factory class htd::SetCoverAlgorithmFactory.
     */
    class SetCoverAlgorithmFactory;

    /**
     *  Forward declaration of factory class htd::StronglyConnectedComponentAlgorithmFactory.
     */
    class StronglyConnectedComponentAlgorithmFactory;

    /**
     *  Forward declaration of factory class htd::TreeDecompositionAlgorithmFactory.
     */
    class TreeDecompositionAlgorithmFactory;

    /**
     *  Forward declaration of factory class htd::TreeDecompositionFactory.
     */
    class TreeDecompositionFactory;

    /**
     *  Forward declaration of factory class htd::GraphPreprocessorFactory.
     */
    class GraphPreprocessorFactory;

    /**
     *  Forward declaration of factory class htd::GraphSeparatorAlgorithmFactory.
     */
    class GraphSeparatorAlgorithmFactory;

    /**
     *  Central management class of a library instance.
     */
    class LibraryInstance
    {
        public:
            /**
             *  Constructor for a new management instance.
             *
             *  @param[in] id   The identifier of the new management instance.
             */
            HTD_API LibraryInstance(htd::id_t id);

            /**
             *  Destructor for a management instance.
             */
            HTD_API virtual ~LibraryInstance();

            /**
             *  Initialize all factory classes corresponding to the management instance.
             *
             *  @param[in] manager   A shared pointer to the current management instance.
             */
            HTD_API void initializeFactoryClasses(const htd::LibraryInstance * const manager);

            /**
             *  Getter for the ID of the management instance.
             *
             *  @return The ID of the management instance.
             */
            HTD_API htd::id_t id(void) const;

            /**
             *  Check whether the terminate(int) function was called.
             *
             *  @return True if the terminate(int) function was called, false otherwise.
             */
            HTD_API bool isTerminated(void) const;

            /**
             *  Send a termination signal to running algorithms of the library to allow them freeing allocated resources.
             *
             *  This call will pass the SIGTERM signal to each of the registered signal
             *  handlers and algorithms still running may decide to terminate gracefully.
             *
             *  @note After calling this method, no further algorithms from the library associated
             *  with the current library instance shall be run until the reset() method is called,
             *  otherwise the outcome of the algorithms is undefined!
             */
            HTD_API void terminate(void);

            /**
             *  Reset the current management instance.
             *
             *  Calling this method sets the value of isTerminated() back to false.
             *  This allows to re-run the library's algorithms after terminate()
             *  was called.
             */
            HTD_API void reset(void);

            /**
             *  Access the factory class for the default implementation of the htd::IConnectedComponentAlgorithm interface.
             */
            HTD_API htd::ConnectedComponentAlgorithmFactory & connectedComponentAlgorithmFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IConnectedComponentAlgorithm interface.
             */
            HTD_API const htd::ConnectedComponentAlgorithmFactory & connectedComponentAlgorithmFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::IMutableDirectedGraph interface.
             */
            HTD_API htd::DirectedGraphFactory & directedGraphFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IMutableDirectedGraph interface.
             */
            HTD_API const htd::DirectedGraphFactory & directedGraphFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::IMutableDirectedMultiGraph interface.
             */
            HTD_API htd::DirectedMultiGraphFactory & directedMultiGraphFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IMutableDirectedMultiGraph interface.
             */
            HTD_API const htd::DirectedMultiGraphFactory & directedMultiGraphFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::IGraphDecompositionAlgorithm interface.
             */
            HTD_API htd::GraphDecompositionAlgorithmFactory & graphDecompositionAlgorithmFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IGraphDecompositionAlgorithm interface.
             */
            HTD_API const htd::GraphDecompositionAlgorithmFactory & graphDecompositionAlgorithmFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::IGraphDecomposition interface.
             */
            HTD_API htd::GraphDecompositionFactory & graphDecompositionFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IGraphDecomposition interface.
             */
            HTD_API const htd::GraphDecompositionFactory & graphDecompositionFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::IGraph interface.
             */
            HTD_API htd::GraphFactory & graphFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IGraph interface.
             */
            HTD_API const htd::GraphFactory & graphFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::IHypergraph interface.
             */
            HTD_API htd::HypergraphFactory & hypergraphFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IHypergraph interface.
             */
            HTD_API const htd::HypergraphFactory & hypergraphFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::IHypertreeDecompositionAlgorithm interface.
             */
            HTD_API htd::HypertreeDecompositionAlgorithmFactory & hypertreeDecompositionAlgorithmFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IHypertreeDecompositionAlgorithm interface.
             */
            HTD_API const htd::HypertreeDecompositionAlgorithmFactory & hypertreeDecompositionAlgorithmFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::IHypertreeDecomposition interface.
             */
            HTD_API htd::HypertreeDecompositionFactory & hypertreeDecompositionFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IHypertreeDecomposition interface.
             */
            HTD_API const htd::HypertreeDecompositionFactory & hypertreeDecompositionFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledDirectedGraph interface.
             */
            HTD_API htd::LabeledDirectedGraphFactory & labeledDirectedGraphFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledDirectedGraph interface.
             */
            HTD_API const htd::LabeledDirectedGraphFactory & labeledDirectedGraphFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledDirectedMultiGraph interface.
             */
            HTD_API htd::LabeledDirectedMultiGraphFactory & labeledDirectedMultiGraphFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledDirectedMultiGraph interface.
             */
            HTD_API const htd::LabeledDirectedMultiGraphFactory & labeledDirectedMultiGraphFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledGraph interface.
             */
            HTD_API htd::LabeledGraphFactory & labeledGraphFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledGraph interface.
             */
            HTD_API const htd::LabeledGraphFactory & labeledGraphFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledHypergraph interface.
             */
            HTD_API htd::LabeledHypergraphFactory & labeledHypergraphFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledHypergraph interface.
             */
            HTD_API const htd::LabeledHypergraphFactory & labeledHypergraphFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledMultiGraph interface.
             */
            HTD_API htd::LabeledMultiGraphFactory & labeledMultiGraphFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledMultiGraph interface.
             */
            HTD_API const htd::LabeledMultiGraphFactory & labeledMultiGraphFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledMultiHypergraph interface.
             */
            HTD_API htd::LabeledMultiHypergraphFactory & labeledMultiHypergraphFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledMultiHypergraph interface.
             */
            HTD_API const htd::LabeledMultiHypergraphFactory & labeledMultiHypergraphFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledPath interface.
             */
            HTD_API htd::LabeledPathFactory & labeledPathFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledPath interface.
             */
            HTD_API const htd::LabeledPathFactory & labeledPathFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledTree interface.
             */
            HTD_API htd::LabeledTreeFactory & labeledTreeFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledTree interface.
             */
            HTD_API const htd::LabeledTreeFactory & labeledTreeFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::IMultiGraph interface.
             */
            HTD_API htd::MultiGraphFactory & multiGraphFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IMultiGraph interface.
             */
            HTD_API const htd::MultiGraphFactory & multiGraphFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::IMultiHypergraph interface.
             */
            HTD_API htd::MultiHypergraphFactory & multiHypergraphFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IMultiHypergraph interface.
             */
            HTD_API const htd::MultiHypergraphFactory & multiHypergraphFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::IOrderingAlgorithm interface.
             */
            HTD_API htd::OrderingAlgorithmFactory & orderingAlgorithmFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IOrderingAlgorithm interface.
             */
            HTD_API const htd::OrderingAlgorithmFactory & orderingAlgorithmFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::IPathDecompositionAlgorithm interface.
             */
            HTD_API htd::PathDecompositionAlgorithmFactory & pathDecompositionAlgorithmFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IPathDecompositionAlgorithm interface.
             */
            HTD_API const htd::PathDecompositionAlgorithmFactory & pathDecompositionAlgorithmFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::IPathDecomposition interface.
             */
            HTD_API htd::PathDecompositionFactory & pathDecompositionFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IPathDecomposition interface.
             */
            HTD_API const htd::PathDecompositionFactory & pathDecompositionFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::ISetCoverAlgorithm interface.
             */
            HTD_API htd::SetCoverAlgorithmFactory & setCoverAlgorithmFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::ISetCoverAlgorithm interface.
             */
            HTD_API const htd::SetCoverAlgorithmFactory & setCoverAlgorithmFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::IStronglyConnectedComponentAlgorithm interface.
             */
            HTD_API htd::StronglyConnectedComponentAlgorithmFactory & stronglyConnectedComponentAlgorithmFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IStronglyConnectedComponentAlgorithm interface.
             */
            HTD_API const htd::StronglyConnectedComponentAlgorithmFactory & stronglyConnectedComponentAlgorithmFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::ITreeDecompositionAlgorithm interface.
             */
            HTD_API htd::TreeDecompositionAlgorithmFactory & treeDecompositionAlgorithmFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::ITreeDecompositionAlgorithm interface.
             */
            HTD_API const htd::TreeDecompositionAlgorithmFactory & treeDecompositionAlgorithmFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::ITreeDecomposition interface.
             */
            HTD_API htd::TreeDecompositionFactory & treeDecompositionFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::ITreeDecomposition interface.
             */
            HTD_API const htd::TreeDecompositionFactory & treeDecompositionFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::IGraphPreprocessor interface.
             */
            HTD_API htd::GraphPreprocessorFactory & graphPreprocessorFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IGraphPreprocessor interface.
             */
            HTD_API const htd::GraphPreprocessorFactory & graphPreprocessorFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::IGraphSeparatorAlgorithm interface.
             */
            HTD_API htd::GraphSeparatorAlgorithmFactory & graphSeparatorAlgorithmFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IGraphSeparatorAlgorithm interface.
             */
            HTD_API const htd::GraphSeparatorAlgorithmFactory & graphSeparatorAlgorithmFactory(void) const;

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_HTD_LIBRARYINSTANCE_HPP */
