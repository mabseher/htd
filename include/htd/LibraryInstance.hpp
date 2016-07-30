/*
 * File:   LibraryInstance.hpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 *
 * Copyright 2015-2016, Michael Abseher
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

#include <functional>
#include <map>
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
     *  Central management class of a library instance.
     */
    class HTD_API LibraryInstance
    {
        public:
            /**
             *  Constructor for a new management instance.
             *
             *  @param[in] id   The identifier of the new management instance.
             */
            LibraryInstance(htd::id_t id);

            /**
             *  Destructor for a management instance.
             */
            virtual ~LibraryInstance();

            /**
             *  Initialize all factory classes corresponding to the management instance.
             *
             *  @param[in] manager   A shared pointer to the current management instance.
             */
            void initializeFactoryClasses(const htd::LibraryInstance * const manager);

            /**
             *  Getter for the ID of the management instance.
             *
             *  @return The ID of the management instance.
             */
            htd::id_t id(void) const;

            /**
             *  Check whether the terminate(int) function was called.
             *
             *  @return True if the terminate(int) function was called, false otherwise.
             */
            bool isTerminated(void) const;

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
            void terminate(void);

            /**
             *  Reset the current management instance.
             *
             *  Calling this method sets the value of isTerminated() back to false.
             *  This allows to re-run the library's algorithms after terminate()
             *  was called.
             */
            void reset(void);

            /**
             *  Register a new signal handler.
             *
             *  @param[in] handler  A callback function which shall be called on arrival of a new signal.
             *
             *  @return The ID of the new signal handler.
             */
            htd::id_t registerSignalHandler(const std::function<void(int)> & handler);

            /**
             *  Unregister an existing signal handler.
             *
             *  @param[in] handlerId    The ID of the signal handler which shall be removed.
             */
            void unregisterSignalHandler(htd::id_t handlerId);

            /**
             *  Access the factory class for the default implementation of the htd::IConnectedComponentAlgorithm interface.
             */
            htd::ConnectedComponentAlgorithmFactory & connectedComponentAlgorithmFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IConnectedComponentAlgorithm interface.
             */
            const htd::ConnectedComponentAlgorithmFactory & connectedComponentAlgorithmFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::IMutableDirectedGraph interface.
             */
            htd::DirectedGraphFactory & directedGraphFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IMutableDirectedGraph interface.
             */
            const htd::DirectedGraphFactory & directedGraphFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::IMutableDirectedMultiGraph interface.
             */
            htd::DirectedMultiGraphFactory & directedMultiGraphFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IMutableDirectedMultiGraph interface.
             */
            const htd::DirectedMultiGraphFactory & directedMultiGraphFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::IGraphDecompositionAlgorithm interface.
             */
            htd::GraphDecompositionAlgorithmFactory & graphDecompositionAlgorithmFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IGraphDecompositionAlgorithm interface.
             */
            const htd::GraphDecompositionAlgorithmFactory & graphDecompositionAlgorithmFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::IGraphDecomposition interface.
             */
            htd::GraphDecompositionFactory & graphDecompositionFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IGraphDecomposition interface.
             */
            const htd::GraphDecompositionFactory & graphDecompositionFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::IGraph interface.
             */
            htd::GraphFactory & graphFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IGraph interface.
             */
            const htd::GraphFactory & graphFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::IHypergraph interface.
             */
            htd::HypergraphFactory & hypergraphFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IHypergraph interface.
             */
            const htd::HypergraphFactory & hypergraphFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::IHypertreeDecompositionAlgorithm interface.
             */
            htd::HypertreeDecompositionAlgorithmFactory & hypertreeDecompositionAlgorithmFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IHypertreeDecompositionAlgorithm interface.
             */
            const htd::HypertreeDecompositionAlgorithmFactory & hypertreeDecompositionAlgorithmFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::IHypertreeDecomposition interface.
             */
            htd::HypertreeDecompositionFactory & hypertreeDecompositionFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IHypertreeDecomposition interface.
             */
            const htd::HypertreeDecompositionFactory & hypertreeDecompositionFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledDirectedGraph interface.
             */
            htd::LabeledDirectedGraphFactory & labeledDirectedGraphFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledDirectedGraph interface.
             */
            const htd::LabeledDirectedGraphFactory & labeledDirectedGraphFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledDirectedMultiGraph interface.
             */
            htd::LabeledDirectedMultiGraphFactory & labeledDirectedMultiGraphFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledDirectedMultiGraph interface.
             */
            const htd::LabeledDirectedMultiGraphFactory & labeledDirectedMultiGraphFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledGraph interface.
             */
            htd::LabeledGraphFactory & labeledGraphFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledGraph interface.
             */
            const htd::LabeledGraphFactory & labeledGraphFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledHypergraph interface.
             */
            htd::LabeledHypergraphFactory & labeledHypergraphFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledHypergraph interface.
             */
            const htd::LabeledHypergraphFactory & labeledHypergraphFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledMultiGraph interface.
             */
            htd::LabeledMultiGraphFactory & labeledMultiGraphFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledMultiGraph interface.
             */
            const htd::LabeledMultiGraphFactory & labeledMultiGraphFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledMultiHypergraph interface.
             */
            htd::LabeledMultiHypergraphFactory & labeledMultiHypergraphFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledMultiHypergraph interface.
             */
            const htd::LabeledMultiHypergraphFactory & labeledMultiHypergraphFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledPath interface.
             */
            htd::LabeledPathFactory & labeledPathFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledPath interface.
             */
            const htd::LabeledPathFactory & labeledPathFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledTree interface.
             */
            htd::LabeledTreeFactory & labeledTreeFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::ILabeledTree interface.
             */
            const htd::LabeledTreeFactory & labeledTreeFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::IMultiGraph interface.
             */
            htd::MultiGraphFactory & multiGraphFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IMultiGraph interface.
             */
            const htd::MultiGraphFactory & multiGraphFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::IMultiHypergraph interface.
             */
            htd::MultiHypergraphFactory & multiHypergraphFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IMultiHypergraph interface.
             */
            const htd::MultiHypergraphFactory & multiHypergraphFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::IOrderingAlgorithm interface.
             */
            htd::OrderingAlgorithmFactory & orderingAlgorithmFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IOrderingAlgorithm interface.
             */
            const htd::OrderingAlgorithmFactory & orderingAlgorithmFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::IPathDecompositionAlgorithm interface.
             */
            htd::PathDecompositionAlgorithmFactory & pathDecompositionAlgorithmFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IPathDecompositionAlgorithm interface.
             */
            const htd::PathDecompositionAlgorithmFactory & pathDecompositionAlgorithmFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::IPathDecomposition interface.
             */
            htd::PathDecompositionFactory & pathDecompositionFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IPathDecomposition interface.
             */
            const htd::PathDecompositionFactory & pathDecompositionFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::ISetCoverAlgorithm interface.
             */
            htd::SetCoverAlgorithmFactory & setCoverAlgorithmFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::ISetCoverAlgorithm interface.
             */
            const htd::SetCoverAlgorithmFactory & setCoverAlgorithmFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::IStronglyConnectedComponentAlgorithm interface.
             */
            htd::StronglyConnectedComponentAlgorithmFactory & stronglyConnectedComponentAlgorithmFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::IStronglyConnectedComponentAlgorithm interface.
             */
            const htd::StronglyConnectedComponentAlgorithmFactory & stronglyConnectedComponentAlgorithmFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::ITreeDecompositionAlgorithm interface.
             */
            htd::TreeDecompositionAlgorithmFactory & treeDecompositionAlgorithmFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::ITreeDecompositionAlgorithm interface.
             */
            const htd::TreeDecompositionAlgorithmFactory & treeDecompositionAlgorithmFactory(void) const;

            /**
             *  Access the factory class for the default implementation of the htd::ITreeDecomposition interface.
             */
            htd::TreeDecompositionFactory & treeDecompositionFactory(void);

            /**
             *  Access the factory class for the default implementation of the htd::ITreeDecomposition interface.
             */
            const htd::TreeDecompositionFactory & treeDecompositionFactory(void) const;

        private:
            HTD_IMPLEMENTATION Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_HTD_LIBRARYINSTANCE_HPP */
