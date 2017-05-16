/*
 * File:   BucketEliminationGraphDecompositionAlgorithm.cpp
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

#ifndef HTD_HTD_BUCKETELIMINATIONGRAPHDECOMPOSITIONALGORITHM_CPP
#define HTD_HTD_BUCKETELIMINATIONGRAPHDECOMPOSITIONALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/BucketEliminationGraphDecompositionAlgorithm.hpp>
#include <htd/ILabelingFunction.hpp>
#include <htd/OrderingAlgorithmFactory.hpp>
#include <htd/GraphDecompositionFactory.hpp>
#include <htd/IWidthLimitableOrderingAlgorithm.hpp>
#include <htd/GraphPreprocessorFactory.hpp>
#include <htd/IGraphPreprocessor.hpp>

#include <algorithm>
#include <cstdarg>
#include <functional>
#include <memory>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

/**
 *  Private implementation details of class htd::BucketEliminationGraphDecompositionAlgorithm.
 */
struct htd::BucketEliminationGraphDecompositionAlgorithm::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager   The management instance to which the current object instance belongs.
     */
    Implementation(const htd::LibraryInstance * const manager) : managementInstance_(manager), orderingAlgorithm_(manager->orderingAlgorithmFactory().createInstance()), labelingFunctions_(), postProcessingOperations_(), compressionEnabled_(true), computeInducedEdges_(true)
    {

    }

    virtual ~Implementation()
    {
        delete orderingAlgorithm_;

        for (auto & labelingFunction : labelingFunctions_)
        {
            delete labelingFunction;
        }

        for (auto & postProcessingOperation : postProcessingOperations_)
        {
            delete postProcessingOperation;
        }
    }

    /**
     *  The management instance to which the current object instance belongs.
     */
    const htd::LibraryInstance * managementInstance_;

    /**
     *  The ordering algorithm which shall be used to compute the vertex elimination ordering.
     */
    htd::IOrderingAlgorithm * orderingAlgorithm_;

    /**
     *  The labeling functions which are applied after the decomposition was computed.
     */
    std::vector<htd::ILabelingFunction *> labelingFunctions_;

    /**
     *  The manipuation operations which are applied after the decomposition was computed.
     */
    std::vector<htd::IGraphDecompositionManipulationOperation *> postProcessingOperations_;

    /**
     *  A boolean flag indicating whether the computed decompositions shall contain only subset-maximal bags.
     */
    bool compressionEnabled_;

    /**
     *  A boolean flag indicating whether the hyperedges induced by a respective bag shall be computed.
     */
    bool computeInducedEdges_;

    /**
     *  Compute a new mutable graph decompostion of the given graph.
     *
     *  @param[in] graph    The graph which shall be decomposed.
     *  @param[in] ordering The vertex ordering which shall be used to compute the decomposition.
     *
     *  @return A mutable graph decompostion of the given graph based on the provided vertex ordering.
     */
    htd::IMutableGraphDecomposition * computeMutableDecomposition(const htd::IMultiHypergraph & graph, const std::vector<htd::vertex_t> & ordering) const;

    /**
     *  Compute a new mutable graph decompostion of the given graph.
     *
     *  @param[in] graph                The graph which shall be decomposed.
     *  @param[in] preprocessedGraph    The input graph in preprocessed format.
     *  @param[in] maxBagSize           The upper bound for the maximum bag size of the decomposition.
     *  @param[in] maxIterationCount    The maximum number of iterations resulting in a higher maximum bag size than maxBagSize after which a null-pointer is returned.
     *
     *  @return A pair consisting of a mutable graph decompostion of the given graph or a null-pointer in case that no decomposition with a appropriate maximum bag size could be found after maxIterationCount iterations and the number of iterations actually needed to find the decomposition at hand.
     */
    std::pair<htd::IMutableGraphDecomposition *, std::size_t> computeMutableDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph, std::size_t maxBagSize, std::size_t maxIterationCount) const;

    /**
     *  Get the vertex which is ranked first in the vertex elimination ordering.
     *
     *  @param[in] vertices         The set of vertices which shall be investigated.
     *  @param[in] ordering         The vertex elimination ordering.
     *  @param[in] vertexIndices    The indices of the vertices in the vertex elimination ordering.
     *
     *  @return The vertex which is ranked first in the vertex elimination ordering.
     */
    htd::vertex_t getMinimumVertex(const std::vector<htd::vertex_t> & vertices, const std::vector<htd::vertex_t> & ordering, const std::vector<htd::index_t> & vertexIndices) const;

    /**
     *  Get the vertex which is ranked first in the vertex elimination ordering.
     *
     *  @param[in] vertices         The set of vertices which shall be investigated.
     *  @param[in] ordering         The vertex elimination ordering.
     *  @param[in] vertexIndices    The indices of the vertices in the vertex elimination ordering.
     *  @param[in] excludedVertex   The vertex which shall be ignored during the determination of the first vertex in the ordering.
     *
     *  @return The vertex which is ranked first in the vertex elimination ordering.
     */
    htd::vertex_t getMinimumVertex(const std::vector<htd::vertex_t> & vertices, const std::vector<htd::vertex_t> & ordering, const std::vector<htd::index_t> & vertexIndices, htd::vertex_t excludedVertex) const;

    /**
     *  Compress the given decomposition by retaining only subset-maximal bags.
     *
     *  @param[in] startingVertex       The starting vertex.
     *  @param[in] neighbors            The neighborhood relation which shall be updated.
     *  @param[in] bagContent           The bag contents which might be swapped during the traversal.
     *  @param[in] unvisitedVertices    The set of unvisited vertices which is updated during the traversal.
     *  @param[in] relevantVertices     The set of relevant vertices which will be updated where relevance refers to subset-maximality.
     *  @param[in] inducedEdges         A vector holding the indices of the edges which are induced by the bag content associated with a vertex.
     *  @param[in] edgeTarget           A vector holding the first target node for each edge.
     */
    void compressDecomposition(htd::vertex_t startingVertex,
                               std::vector<std::vector<htd::vertex_t>> & neighbors,
                               std::vector<std::vector<htd::vertex_t>> & bagContent,
                               std::unordered_set<htd::vertex_t> & unvisitedVertices,
                               std::vector<htd::vertex_t> & relevantVertices,
                               std::vector<std::vector<htd::index_t>> & inducedEdges,
                               std::vector<htd::index_t> & edgeTarget) const;

    /**
     *  Compress the given decomposition by retaining only subset-maximal bags.
     *
     *  If the bag of the vertex is a subset of the bag of its parent, the vertex is removed. If the bag of
     *  the vertex is a superset of the bag of its parent, the bag contents are swapped and the vertex is
     *  removed. Otherwise, the decomposition is left unchanged.
     *
     *  @param[in] vertex           The vertex.
     *  @param[in] parent           The parent of the vertex during the traversal.
     *  @param[in] neighbors        The neighborhood relation which shall be updated.
     *  @param[in] bagContent       The bag contents which might be swapped during the traversal.
     *  @param[in] relevantVertices The set of relevant vertices which will be updated where relevance refers to subset-maximality.
     *  @param[in] inducedEdges     A vector holding the indices of the edges which are induced by the bag content associated with a vertex.
     *  @param[in] edgeTarget       A vector holding the first target node for each edge.
     */
    void compressDecomposition(htd::vertex_t vertex, htd::vertex_t parent,
                               std::vector<std::vector<htd::vertex_t>> & neighbors,
                               std::vector<std::vector<htd::vertex_t>> & bagContent,
                               std::vector<htd::vertex_t> & relevantVertices,
                               std::vector<std::vector<htd::index_t>> & inducedEdges,
                               std::vector<htd::index_t> & edgeTarget) const;

    /**
     *  Update the given decomposition by performing pre-order traversal.
     *
     *  @param[in] graph                    The graph from which the decomposition was computed.
     *  @param[in] decomposition            The decomposition which shall be updated.
     *  @param[in] startingVertex           The starting vertex.
     *  @param[in] neighbors                The neighborhood relation which shall be used.
     *  @param[in] bagContent               The bag contents.
     *  @param[in] unvisitedVertices        The set of unvisited vertices which is updated during the traversal.
     *  @param[in] inducedEdges             A vector holding the indices of the edges which are induced by the bag content associated with a vertex.
     *  @param[in] decompositionVertices    A mapping between the vertices and their counterparts in the decomposition.
     *
     *  @note The bag contents and the induced edges are moved into the decomposition during this operation.
     */
    void updateDecomposition(const htd::IMultiHypergraph & graph,
                             htd::IMutableGraphDecomposition & decomposition,
                             htd::vertex_t startingVertex,
                             const std::vector<std::vector<htd::vertex_t>> & neighbors,
                             std::vector<std::vector<htd::vertex_t>> & bagContent,
                             std::vector<std::vector<htd::index_t>> & inducedEdges,
                             std::unordered_set<htd::vertex_t> & unvisitedVertices,
                             std::unordered_map<htd::vertex_t, htd::vertex_t> & decompositionVertices) const;

    /**
     *  Check whether two sets are subset-maximal with respect to the other set.
     *
     *  @param[in] set1 The first set.
     *  @param[in] set2 The second set.
     *
     *  @return This function returns -1 if the first set is a superset of or identical to the second set.
     *  If the second set is a proper superset of the first set, the return value is 1. Otherwise, the
     *  return value is 0.
     */
    int is_maximal(const std::vector<htd::vertex_t> & set1, const std::vector<htd::vertex_t> & set2) const;

    /**
     *  Distribute a given edge, identified by its index, in the decomposition so that the information about induced edges is updated.
     *
     *  @param[in] edgeIndex        The index of the edge which shall be distributed.
     *  @param[in] edge             The sorted elements of the edge which shall be distributed.
     *  @param[in] startBucket      The identifier of the node from which the process shall start.
     *  @param[in] buckets          The available buckets.
     *  @param[in] neighbors        The neighbors of the buckets.
     *  @param[in] inducedEdges     The set of edge indices induced by a bucket.
     *  @param[in] lastAssignedEdge The identifier of the last edge which was assigned to a bucket.
     *  @param[in] originStack      The stack instance used for backtracking.
     */
    void distributeEdge(htd::index_t edgeIndex,
                        const std::vector<htd::vertex_t> & edge,
                        htd::vertex_t startBucket,
                        const std::vector<std::vector<htd::vertex_t>> & buckets,
                        const std::vector<std::vector<htd::vertex_t>> & neighbors,
                        std::vector<std::vector<htd::index_t>> & inducedEdges,
                        std::vector<htd::id_t> & lastAssignedEdge,
                        std::stack<htd::vertex_t> & originStack) const;

    /**
     *  Distribute a given edge, identified by its index, in the decomposition so that the information about induced edges is updated.
     *
     *  @param[in] edgeIndex        The index of the edge which shall be distributed.
     *  @param[in] vertex1          The first vertex (i.e., the one with lower ID) of the edge which shall be distributed.
     *  @param[in] vertex2          The second vertex (i.e., the one with higher ID) of the edge which shall be distributed.
     *  @param[in] startBucket      The identifier of the node from which the process shall start.
     *  @param[in] buckets          The available buckets.
     *  @param[in] neighbors        The neighbors of the buckets.
     *  @param[in] inducedEdges     The set of edge indices induced by a bucket.
     *  @param[in] lastAssignedEdge The identifier of the last edge which was assigned to a bucket.
     *  @param[in] originStack      The stack instance used for backtracking.
     */
    void distributeEdge(htd::index_t edgeIndex,
                        htd::vertex_t vertex1,
                        htd::vertex_t vertex2,
                        htd::vertex_t startBucket,
                        const std::vector<std::vector<htd::vertex_t>> & buckets,
                        const std::vector<std::vector<htd::vertex_t>> & neighbors,
                        std::vector<std::vector<htd::index_t>> & inducedEdges,
                        std::vector<htd::id_t> & lastAssignedEdge,
                        std::stack<htd::vertex_t> & originStack) const;

    /**
     *  Compute the set union of two sets and store the result in the first set.
     *
     *  @param[in,out] set1         The first set
     *  @param[in] set2             The second set.
     *  @param[in] ignoredVertex    The vertex which shall be ignored if it occurs in the second set.
     */
    void set_union(std::vector<htd::vertex_t> & set1,
                   const std::vector<htd::vertex_t> & set2,
                   htd::vertex_t ignoredVertex) const
    {
        std::vector<htd::vertex_t> tmp;
        tmp.reserve(set2.size());

        auto first1 = set1.begin();
        auto first2 = set2.begin();

        auto last1 = set1.end();
        auto last2 = set2.end();

        while (first1 != last1 && first2 != last2)
        {
            if (*first1 < *first2)
            {
                ++first1;
            }
            else if (*first2 < *first1)
            {
                if (*first2 != ignoredVertex)
                {
                    tmp.push_back(*first2);
                }

                ++first2;
            }
            else
            {
                ++first1;

                //Skip common value in set 2.
                ++first2;
            }
        }

        std::copy_if(first2, last2, std::back_inserter(tmp), [&](const htd::vertex_t vertex) { return vertex != ignoredVertex; });

        if (!tmp.empty())
        {
            htd::inplace_merge(set1, tmp);
        }
    }
};

htd::BucketEliminationGraphDecompositionAlgorithm::BucketEliminationGraphDecompositionAlgorithm(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{

}

htd::BucketEliminationGraphDecompositionAlgorithm::BucketEliminationGraphDecompositionAlgorithm(const htd::LibraryInstance * const manager, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) : implementation_(new Implementation(manager))
{
    setManipulationOperations(manipulationOperations);
}

htd::BucketEliminationGraphDecompositionAlgorithm::~BucketEliminationGraphDecompositionAlgorithm()
{

}

htd::IGraphDecomposition * htd::BucketEliminationGraphDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph) const
{
    return computeDecomposition(graph, std::vector<htd::IDecompositionManipulationOperation *>());
}

htd::IGraphDecomposition * htd::BucketEliminationGraphDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const
{
    return computeDecomposition(graph, manipulationOperations, (std::size_t)-1, 1).first;
}

std::pair<htd::IGraphDecomposition *, std::size_t> htd::BucketEliminationGraphDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, std::size_t maxBagSize, std::size_t maxIterationCount) const
{
    return computeDecomposition(graph, std::vector<htd::IDecompositionManipulationOperation *>(), maxBagSize, maxIterationCount);
}

std::pair<htd::IGraphDecomposition *, std::size_t> htd::BucketEliminationGraphDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations, std::size_t maxBagSize, std::size_t maxIterationCount) const
{
    htd::IGraphPreprocessor * preprocessor = implementation_->managementInstance_->graphPreprocessorFactory().createInstance();

    htd::IPreprocessedGraph * preprocessedGraph = preprocessor->prepare(graph);

    std::pair<htd::IGraphDecomposition *, std::size_t> ret =
        computeDecomposition(graph, *preprocessedGraph, manipulationOperations, maxBagSize, maxIterationCount);

    delete preprocessedGraph;
    delete preprocessor;

    return ret;
}

htd::IGraphDecomposition * htd::BucketEliminationGraphDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph) const
{
    return computeDecomposition(graph, preprocessedGraph, std::vector<htd::IDecompositionManipulationOperation *>());
}

htd::IGraphDecomposition * htd::BucketEliminationGraphDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const
{
    return computeDecomposition(graph, preprocessedGraph, manipulationOperations, (std::size_t)-1, 1).first;
}

std::pair<htd::IGraphDecomposition *, std::size_t> htd::BucketEliminationGraphDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph, std::size_t maxBagSize, std::size_t maxIterationCount) const
{
    return computeDecomposition(graph, preprocessedGraph, std::vector<htd::IDecompositionManipulationOperation *>(), maxBagSize, maxIterationCount);
}

std::pair<htd::IGraphDecomposition *, std::size_t> htd::BucketEliminationGraphDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations, std::size_t maxBagSize, std::size_t maxIterationCount) const
{
    std::pair<htd::IMutableGraphDecomposition *, std::size_t> ret = implementation_->computeMutableDecomposition(graph, preprocessedGraph, maxBagSize, maxIterationCount);

    htd::IMutableGraphDecomposition * decomposition = ret.first;

    if (decomposition != nullptr)
    {
        std::vector<htd::ILabelingFunction *> labelingFunctions;

        std::vector<htd::IGraphDecompositionManipulationOperation *> postProcessingOperations;

        for (htd::IDecompositionManipulationOperation * operation : manipulationOperations)
        {
            htd::ILabelingFunction * labelingFunction = dynamic_cast<htd::ILabelingFunction *>(operation);

            if (labelingFunction != nullptr)
            {
                labelingFunctions.push_back(labelingFunction);
            }

            htd::IGraphDecompositionManipulationOperation * manipulationOperation = dynamic_cast<htd::IGraphDecompositionManipulationOperation *>(operation);

            if (manipulationOperation != nullptr)
            {
                postProcessingOperations.push_back(manipulationOperation);
            }
        }

        for (const auto & operation : implementation_->postProcessingOperations_)
        {
            operation->apply(graph, *decomposition);
        }

        for (const auto & operation : postProcessingOperations)
        {
            operation->apply(graph, *decomposition);
        }

        for (const auto & labelingFunction : implementation_->labelingFunctions_)
        {
            for (htd::vertex_t vertex : decomposition->vertices())
            {
                htd::ILabelCollection * labelCollection = decomposition->labelings().exportVertexLabelCollection(vertex);

                htd::ILabel * newLabel = labelingFunction->computeLabel(decomposition->bagContent(vertex), *labelCollection);

                delete labelCollection;

                decomposition->setVertexLabel(labelingFunction->name(), vertex, newLabel);
            }
        }

        for (const auto & labelingFunction : labelingFunctions)
        {
            for (htd::vertex_t vertex : decomposition->vertices())
            {
                htd::ILabelCollection * labelCollection = decomposition->labelings().exportVertexLabelCollection(vertex);

                htd::ILabel * newLabel = labelingFunction->computeLabel(decomposition->bagContent(vertex), *labelCollection);

                delete labelCollection;

                decomposition->setVertexLabel(labelingFunction->name(), vertex, newLabel);
            }
        }

        for (auto & labelingFunction : labelingFunctions)
        {
            delete labelingFunction;
        }

        for (auto & postProcessingOperation : postProcessingOperations)
        {
            delete postProcessingOperation;
        }
    }
    else
    {
        for (htd::IDecompositionManipulationOperation * operation : manipulationOperations)
        {
            delete operation;
        }
    }

    return ret;
}

htd::IGraphDecomposition * htd::BucketEliminationGraphDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, int manipulationOperationCount, ...) const
{
    va_list arguments;

    va_start(arguments, manipulationOperationCount);

    std::vector<htd::IDecompositionManipulationOperation *> manipulationOperations;

    for (int manipulationOperationIndex = 0; manipulationOperationIndex < manipulationOperationCount; manipulationOperationIndex++)
    {
        manipulationOperations.push_back(va_arg(arguments, htd::IDecompositionManipulationOperation *));
    }

    va_end(arguments);

    return computeDecomposition(graph, manipulationOperations);
}

htd::IGraphDecomposition * htd::BucketEliminationGraphDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph, int manipulationOperationCount, ...) const
{
    va_list arguments;

    va_start(arguments, manipulationOperationCount);

    std::vector<htd::IDecompositionManipulationOperation *> manipulationOperations;

    for (int manipulationOperationIndex = 0; manipulationOperationIndex < manipulationOperationCount; manipulationOperationIndex++)
    {
        manipulationOperations.push_back(va_arg(arguments, htd::IDecompositionManipulationOperation *));
    }

    va_end(arguments);

    return computeDecomposition(graph, preprocessedGraph, manipulationOperations);
}

void htd::BucketEliminationGraphDecompositionAlgorithm::setOrderingAlgorithm(htd::IOrderingAlgorithm * algorithm)
{
    HTD_ASSERT(algorithm != nullptr)

    delete implementation_->orderingAlgorithm_;

    implementation_->orderingAlgorithm_ = algorithm;
}

void htd::BucketEliminationGraphDecompositionAlgorithm::setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
{
    for (auto & labelingFunction : implementation_->labelingFunctions_)
    {
        delete labelingFunction;
    }

    for (auto & postProcessingOperation : implementation_->postProcessingOperations_)
    {
        delete postProcessingOperation;
    }

    implementation_->labelingFunctions_.clear();

    implementation_->postProcessingOperations_.clear();

    addManipulationOperations(manipulationOperations);
}

void htd::BucketEliminationGraphDecompositionAlgorithm::addManipulationOperation(htd::IDecompositionManipulationOperation * manipulationOperation)
{
    bool assigned = false;

    htd::ILabelingFunction * labelingFunction = dynamic_cast<htd::ILabelingFunction *>(manipulationOperation);

    if (labelingFunction != nullptr)
    {
        implementation_->labelingFunctions_.emplace_back(labelingFunction);

        assigned = true;
    }

    htd::IGraphDecompositionManipulationOperation * newManipulationOperation = dynamic_cast<htd::IGraphDecompositionManipulationOperation *>(manipulationOperation);

    if (newManipulationOperation != nullptr)
    {
        implementation_->postProcessingOperations_.emplace_back(newManipulationOperation);

        assigned = true;
    }

    if (!assigned)
    {
        delete manipulationOperation;
    }
}

void htd::BucketEliminationGraphDecompositionAlgorithm::addManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
{
    for (htd::IDecompositionManipulationOperation * operation : manipulationOperations)
    {
        addManipulationOperation(operation);
    }
}

bool htd::BucketEliminationGraphDecompositionAlgorithm::isSafelyInterruptible(void) const
{
    return false;
}

const htd::LibraryInstance * htd::BucketEliminationGraphDecompositionAlgorithm::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::BucketEliminationGraphDecompositionAlgorithm::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

bool htd::BucketEliminationGraphDecompositionAlgorithm::isCompressionEnabled(void) const
{
    return implementation_->compressionEnabled_;
}

void htd::BucketEliminationGraphDecompositionAlgorithm::setCompressionEnabled(bool compressionEnabled)
{
    implementation_->compressionEnabled_ = compressionEnabled;
}

bool htd::BucketEliminationGraphDecompositionAlgorithm::isComputeInducedEdgesEnabled(void) const
{
    return implementation_->computeInducedEdges_;
}

void htd::BucketEliminationGraphDecompositionAlgorithm::setComputeInducedEdgesEnabled(bool computeInducedEdgesEnabled)
{
    implementation_->computeInducedEdges_ = computeInducedEdgesEnabled;
}

htd::BucketEliminationGraphDecompositionAlgorithm * htd::BucketEliminationGraphDecompositionAlgorithm::clone(void) const
{
    htd::BucketEliminationGraphDecompositionAlgorithm * ret = new htd::BucketEliminationGraphDecompositionAlgorithm(implementation_->managementInstance_);

    ret->setCompressionEnabled(implementation_->compressionEnabled_);
    ret->setComputeInducedEdgesEnabled(implementation_->computeInducedEdges_);

    for (const auto & labelingFunction : implementation_->labelingFunctions_)
    {
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        ret->addManipulationOperation(labelingFunction->clone());
#else
        ret->addManipulationOperation(labelingFunction->cloneLabelingFunction());
#endif
    }

    for (const auto & postProcessingOperation : implementation_->postProcessingOperations_)
    {
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        ret->addManipulationOperation(postProcessingOperation->clone());
#else
        ret->addManipulationOperation(postProcessingOperation->cloneGraphDecompositionManipulationOperation());
#endif
    }

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    ret->setOrderingAlgorithm(implementation_->orderingAlgorithm_->clone());
#else
    ret->setOrderingAlgorithm(implementation_->orderingAlgorithm_->cloneOrderingAlgorithm());
#endif

    return ret;
}

std::pair<htd::IMutableGraphDecomposition *, std::size_t> htd::BucketEliminationGraphDecompositionAlgorithm::Implementation::computeMutableDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph, std::size_t maxBagSize, std::size_t maxIterationCount) const
{
    htd::IMutableGraphDecomposition * ret = nullptr;

    htd::IWidthLimitableOrderingAlgorithm * widthLimitableAlgorithm = dynamic_cast<htd::IWidthLimitableOrderingAlgorithm *>(orderingAlgorithm_);

    std::size_t iterations = 0;

    if (widthLimitableAlgorithm == nullptr)
    {
        htd::IVertexOrdering * ordering = nullptr;

        do
        {
            ordering = orderingAlgorithm_->computeOrdering(graph, preprocessedGraph);

            if (ordering != nullptr)
            {
                if (ordering->sequence().size() == graph.vertexCount())
                {
                    ret = computeMutableDecomposition(graph, ordering->sequence());

                    HTD_ASSERT(ret != nullptr)

                    if (ret->maximumBagSize() > maxBagSize)
                    {
                        delete ret;

                        ret = nullptr;
                    }
                }

                delete ordering;
            }

            ++iterations;
        }
        while (ret == nullptr && iterations < maxIterationCount && !managementInstance_->isTerminated());
    }
    else
    {
        htd::IWidthLimitedVertexOrdering * ordering = widthLimitableAlgorithm->computeOrdering(graph, preprocessedGraph, maxBagSize, maxIterationCount);

        if (ordering != nullptr)
        {
            if (ordering->sequence().size() == graph.vertexCount())
            {
                ret = computeMutableDecomposition(graph, ordering->sequence());
            }

            iterations += ordering->requiredIterations();

            delete ordering;
        }
    }

    return std::make_pair(ret, iterations);
}

htd::IMutableGraphDecomposition * htd::BucketEliminationGraphDecompositionAlgorithm::Implementation::computeMutableDecomposition(const htd::IMultiHypergraph & graph, const std::vector<htd::vertex_t> & ordering) const
{
    const htd::LibraryInstance & managementInstance = *managementInstance_;

    htd::IMutableGraphDecomposition * ret = managementInstance.graphDecompositionFactory().createInstance();

    std::size_t size = graph.vertexCount();

    HTD_ASSERT(ordering.size() == size)

    if (size > 0)
    {
        if (!managementInstance.isTerminated())
        {
            htd::vertex_t lastVertex = graph.vertexAtPosition(size - 1);

            std::vector<htd::index_t> indices(lastVertex + 1);

            std::vector<std::vector<htd::vertex_t>> buckets(lastVertex + 1);

            std::vector<std::vector<htd::vertex_t>> neighbors(lastVertex + 1);

            std::vector<std::vector<htd::index_t>> inducedEdges(lastVertex + 1);

            std::vector<htd::index_t> edgeTarget(graph.edgeCount());

            std::vector<htd::vertex_t> relevantVertices;

            std::size_t index = 0;

            for (htd::vertex_t vertex : ordering)
            {
                indices[vertex] = index++;

                buckets[vertex].push_back(vertex);
            }

            std::size_t edgeCount = graph.edgeCount();

            const htd::ConstCollection<htd::Hyperedge> & hyperedges = graph.hyperedges();

            auto hyperedgePosition = hyperedges.begin();

            for (htd::index_t index = 0; index < edgeCount && !managementInstance.isTerminated(); ++index)
            {
                const std::vector<htd::vertex_t> & elements = hyperedgePosition->sortedElements();

                switch (elements.size())
                {
                    case 1:
                    {
                        htd::vertex_t vertex = elements[0];

                        edgeTarget[index] = vertex;

                        inducedEdges[vertex].push_back(index);

                        break;
                    }
                    case 2:
                    {
                        htd::vertex_t vertex1 = elements[0];
                        htd::vertex_t vertex2 = elements[1];

                        if (indices[vertex1] < indices[vertex2])
                        {
                            std::vector<htd::vertex_t> & selectedBucket = buckets[vertex1];

                            auto position = std::lower_bound(selectedBucket.begin(), selectedBucket.end(), vertex2);

                            if (position == selectedBucket.end() || *position != vertex2)
                            {
                                selectedBucket.insert(position, vertex2);
                            }

                            edgeTarget[index] = vertex1;

                            inducedEdges[vertex1].push_back(index);
                        }
                        else
                        {
                            std::vector<htd::vertex_t> & selectedBucket = buckets[vertex2];

                            auto position = std::lower_bound(selectedBucket.begin(), selectedBucket.end(), vertex1);

                            if (position == selectedBucket.end() || *position != vertex1)
                            {
                                selectedBucket.insert(position, vertex1);
                            }

                            edgeTarget[index] = vertex2;

                            inducedEdges[vertex2].push_back(index);
                        }

                        break;
                    }
                    default:
                    {
                        htd::vertex_t minimumVertex = getMinimumVertex(elements, ordering, indices);

                        htd::inplace_set_union(buckets[minimumVertex], elements);

                        edgeTarget[index] = minimumVertex;

                        inducedEdges[minimumVertex].push_back(index);

                        break;
                    }
                }

                ++hyperedgePosition;
            }

            for (auto it = ordering.begin(); it != ordering.end() && !managementInstance.isTerminated(); ++it)
            {
                htd::vertex_t selection = *it;

                DEBUGGING_CODE(std::cout << std::endl << "   Processing bucket " << selection << " ..." << std::endl;)

                const std::vector<htd::vertex_t> & bucket = buckets[selection];

                if (bucket.size() > 1)
                {
                    DEBUGGING_CODE(
                        std::cout << "      Bucket " << selection << ": ";
                        htd::print(bucket, false);
                        std::cout << std::endl;
                    )

                    htd::vertex_t minimumVertex = getMinimumVertex(bucket, ordering, indices, selection);

                    DEBUGGING_CODE(
                        std::cout << "      Minimum Vertex: " << minimumVertex << std::endl;

                        if (minimumVertex < selection)
                        {
                            std::cout << "      Connection: " << minimumVertex << " - " << selection << std::endl;
                        }
                        else
                        {
                            std::cout << "      Connection: " << selection << " - " << minimumVertex << std::endl;
                        }
                    )

                    std::vector<htd::vertex_t> & selectedBucket = buckets[minimumVertex];

                    this->set_union(selectedBucket, bucket, selection);

                    neighbors[selection].push_back(minimumVertex);
                    neighbors[minimumVertex].push_back(selection);
                }
            }

            std::unordered_set<htd::vertex_t> unvisitedVertices;

            if (compressionEnabled_)
            {
                unvisitedVertices.insert(ordering.begin(), ordering.end());

                while (!unvisitedVertices.empty())
                {
                    htd::vertex_t currentVertex = *(unvisitedVertices.begin());

                    compressDecomposition(currentVertex, neighbors, buckets, unvisitedVertices, relevantVertices, inducedEdges, edgeTarget);
                }
            }
            else
            {
                relevantVertices = ordering;
            }

            for (htd::vertex_t vertex : relevantVertices)
            {
                inducedEdges[vertex].clear();
            }

            if (computeInducedEdges_)
            {
                hyperedgePosition = hyperedges.begin();

                std::vector<htd::id_t> lastAssignedEdge(buckets.size() + 1, (htd::id_t)-1);

                std::stack<htd::vertex_t> originStack;

                for (index = 0; index < edgeCount && !managementInstance.isTerminated(); ++index)
                {
                    const std::vector<htd::vertex_t> & edgeElements = hyperedgePosition->sortedElements();

                    if (edgeElements.size() == 2)
                    {
                        distributeEdge(index, edgeElements[0], edgeElements[1], edgeTarget[index], buckets, neighbors, inducedEdges, lastAssignedEdge, originStack);
                    }
                    else
                    {
                        distributeEdge(index, edgeElements, edgeTarget[index], buckets, neighbors, inducedEdges, lastAssignedEdge, originStack);
                    }

                    ++hyperedgePosition;
                }
            }

            unvisitedVertices.insert(relevantVertices.begin(), relevantVertices.end());

            std::unordered_map<htd::vertex_t, htd::vertex_t> decompositionVertices;

            while (!unvisitedVertices.empty())
            {
                htd::vertex_t currentVertex = *(unvisitedVertices.begin());

                updateDecomposition(graph, *ret, currentVertex, neighbors, buckets, inducedEdges, unvisitedVertices, decompositionVertices);
            }
        }
    }
    else
    {
        if (!managementInstance.isTerminated())
        {
            ret->addVertex();
        }
    }

    /*
    for (htd::vertex_t vertex1 : ret->vertices())
    {
        for (htd::vertex_t vertex2 : ret->vertices())
        {
            if (vertex1 < vertex2)
            {
                const std::vector<htd::vertex_t> & bagContent1 = ret->bagContent(vertex1);
                const std::vector<htd::vertex_t> & bagContent2 = ret->bagContent(vertex2);

                if (std::includes(bagContent2.begin(), bagContent2.end(), bagContent1.begin(), bagContent1.end()))
                {
                    std::cout << "NOT MINIMAL:" << std::endl;
                    std::cout << "   VERTEX " << vertex1 << ":" << std::endl;
                    std::cout << "      " << bagContent1 << std::endl;
                    std::cout << "   VERTEX " << vertex2 << ":" << std::endl;
                    std::cout << "      " << bagContent2 << std::endl;
                    std::cout << std::endl;
                }
            }
        }
    }
    */

    return ret;
}

htd::vertex_t htd::BucketEliminationGraphDecompositionAlgorithm::Implementation::getMinimumVertex(const std::vector<htd::vertex_t> & vertices, const std::vector<htd::vertex_t> & ordering, const std::vector<htd::index_t> & vertexIndices) const
{
    std::size_t minimum = (std::size_t)-1;

    for (htd::vertex_t vertex : vertices)
    {
        minimum = std::min(minimum, vertexIndices[vertex]);
    }

    HTD_ASSERT(minimum < ordering.size())

    return ordering[minimum];
}

htd::vertex_t htd::BucketEliminationGraphDecompositionAlgorithm::Implementation::getMinimumVertex(const std::vector<htd::vertex_t> & vertices, const std::vector<htd::vertex_t> & ordering, const std::vector<htd::index_t> & vertexIndices, htd::vertex_t excludedVertex) const
{
    std::size_t minimum = (std::size_t)-1;

    for (htd::vertex_t vertex : vertices)
    {
        if (vertex != excludedVertex)
        {
            minimum = std::min(minimum, vertexIndices[vertex]);
        }
    }

    HTD_ASSERT(minimum < ordering.size())

    return ordering[minimum];
}

void htd::BucketEliminationGraphDecompositionAlgorithm::Implementation::compressDecomposition(htd::vertex_t startingVertex, 
                                                                                              std::vector<std::vector<htd::vertex_t>> & neighbors,
                                                                                              std::vector<std::vector<htd::vertex_t>> & bagContent,
                                                                                              std::unordered_set<htd::vertex_t> & unvisitedVertices,
                                                                                              std::vector<htd::vertex_t> & relevantVertices,
                                                                                              std::vector<std::vector<htd::index_t>> & inducedEdges,
                                                                                              std::vector<htd::index_t> & edgeTarget) const
{
    htd::vertex_t lastNode = htd::Vertex::UNKNOWN;

    htd::vertex_t peekNode = htd::Vertex::UNKNOWN;

    htd::vertex_t currentNode = startingVertex;

    htd::vertex_t currentParent = htd::Vertex::UNKNOWN;

    htd::index_t lastIndex = 0;

    htd::index_t peekIndex = 0;

    htd::index_t currentIndex = neighbors[currentNode].size() - 1;

    std::stack<std::tuple<htd::vertex_t, htd::index_t, htd::vertex_t>> parentStack;

    relevantVertices.push_back(startingVertex);

    while (!parentStack.empty() || currentNode != htd::Vertex::UNKNOWN)
    {
        if (currentNode != htd::Vertex::UNKNOWN)
        {
            if (currentIndex < neighbors[currentNode].size())
            {
                htd::vertex_t nextNode = neighbors[currentNode][currentIndex];

                if (nextNode != currentParent)
                {
                    parentStack.emplace(currentNode, currentIndex, currentParent);

                    currentParent = currentNode;

                    currentNode = nextNode;

                    currentIndex = neighbors[currentNode].size() - 1;
                }
                else
                {
                    --currentIndex;

                    if (currentIndex < neighbors[currentNode].size())
                    {
                        parentStack.emplace(currentNode, currentIndex, currentParent);

                        currentParent = currentNode;

                        currentNode = neighbors[currentNode][currentIndex];

                        currentIndex = neighbors[currentNode].size() - 1;
                    }
                    else
                    {
                        unvisitedVertices.erase(currentNode);

                        if (!parentStack.empty() && std::get<0>(parentStack.top()) != htd::Vertex::UNKNOWN)
                        {
                            compressDecomposition(currentNode, std::get<0>(parentStack.top()), neighbors, bagContent, relevantVertices, inducedEdges, edgeTarget);

                            std::get<1>(parentStack.top())--;
                        }

                        currentNode = htd::Vertex::UNKNOWN;
                    }
                }
            }
            else
            {
                unvisitedVertices.erase(currentNode);

                if (!parentStack.empty() && std::get<0>(parentStack.top()) != htd::Vertex::UNKNOWN)
                {
                    compressDecomposition(currentNode, std::get<0>(parentStack.top()), neighbors, bagContent, relevantVertices, inducedEdges, edgeTarget);

                    std::get<1>(parentStack.top())--;
                }

                currentNode = htd::Vertex::UNKNOWN;
            }
        }
        else
        {
            peekNode = std::get<0>(parentStack.top());
            peekIndex = std::get<1>(parentStack.top());

            if (peekIndex < neighbors[peekNode].size() && !(lastNode == peekNode && lastIndex == peekIndex))
            {
                htd::vertex_t nextNode = neighbors[peekNode][peekIndex];

                if (nextNode != std::get<2>(parentStack.top()))
                {
                    currentParent = peekNode;

                    currentNode = neighbors[peekNode][peekIndex];

                    currentIndex = neighbors[currentNode].size() - 1;
                }
                else
                {
                    lastNode = peekNode;
                    lastIndex = peekIndex;

                    currentNode = htd::Vertex::UNKNOWN;

                    parentStack.pop();

                    unvisitedVertices.erase(peekNode);

                    if (!parentStack.empty() && std::get<0>(parentStack.top()) != htd::Vertex::UNKNOWN)
                    {
                        compressDecomposition(peekNode, std::get<0>(parentStack.top()), neighbors, bagContent, relevantVertices, inducedEdges, edgeTarget);

                        std::get<1>(parentStack.top())--;
                    }
                }
            }
            else
            {
                lastNode = peekNode;
                lastIndex = peekIndex;

                currentNode = htd::Vertex::UNKNOWN;

                parentStack.pop();

                unvisitedVertices.erase(peekNode);

                if (!parentStack.empty() && std::get<0>(parentStack.top()) != htd::Vertex::UNKNOWN)
                {
                    compressDecomposition(peekNode, std::get<0>(parentStack.top()), neighbors, bagContent, relevantVertices, inducedEdges, edgeTarget);

                    std::get<1>(parentStack.top())--;
                }
            }
        }
    }
}

void htd::BucketEliminationGraphDecompositionAlgorithm::Implementation::compressDecomposition(htd::vertex_t vertex, htd::vertex_t parent,
                                                                                              std::vector<std::vector<htd::vertex_t>> & neighbors,
                                                                                              std::vector<std::vector<htd::vertex_t>> & bagContent,
                                                                                              std::vector<htd::vertex_t> & relevantVertices,
                                                                                              std::vector<std::vector<htd::index_t>> & inducedEdges,
                                                                                              std::vector<htd::index_t> & edgeTarget) const
{
    int result = is_maximal(bagContent[vertex], bagContent[parent]);

    if (result != 0)
    {
        if (result < 0)
        {
            bagContent[vertex].swap(bagContent[parent]);
        }

        std::vector<htd::vertex_t> & currentNeighborhood = neighbors[vertex];
        std::vector<htd::vertex_t> & parentNeighborhood = neighbors[parent];

        currentNeighborhood.erase(std::find(currentNeighborhood.begin(), currentNeighborhood.end(), parent));
        parentNeighborhood.erase(std::find(parentNeighborhood.begin(), parentNeighborhood.end(), vertex));

        parentNeighborhood.insert(parentNeighborhood.end(), currentNeighborhood.begin(), currentNeighborhood.end());

        for (htd::vertex_t neighbor : currentNeighborhood)
        {
            std::vector<htd::vertex_t> & currentNeighborhood2 = neighbors[neighbor];

            /* Because 'vertex' is a neighbor of 'neighbor', std::find will always find 'vertex' in 'currentNeighborhood2'. */
            // coverity[deref_iterator]
            *(std::find(currentNeighborhood2.begin(), currentNeighborhood2.end(), vertex)) = parent;
        }

        std::vector<htd::vertex_t>().swap(currentNeighborhood);

        std::vector<htd::index_t> & currentInducedEdges = inducedEdges[vertex];
        std::vector<htd::index_t> & parentInducedEdges = inducedEdges[parent];

        parentInducedEdges.insert(parentInducedEdges.end(), currentInducedEdges.begin(), currentInducedEdges.end());

        for (htd::index_t index : currentInducedEdges)
        {
            edgeTarget[index] = parent;
        }

        std::vector<htd::index_t>().swap(currentInducedEdges);
    }
    else
    {
        relevantVertices.push_back(vertex);
    }
}

int htd::BucketEliminationGraphDecompositionAlgorithm::Implementation::is_maximal(const std::vector<htd::vertex_t> & set1, const std::vector<htd::vertex_t> & set2) const
{
    int ret = 0;

    if (set1.size() >= set2.size())
    {
        if (std::includes(set1.begin(), set1.end(), set2.begin(), set2.end()))
        {
            ret = -1;
        }
    }
    else
    {
        if (std::includes(set2.begin(), set2.end(), set1.begin(), set1.end()))
        {
            ret = 1;
        }
    }

    return ret;
}

void htd::BucketEliminationGraphDecompositionAlgorithm::Implementation::distributeEdge(htd::index_t edgeIndex, const std::vector<htd::vertex_t> & edge, htd::vertex_t startBucket, const std::vector<std::vector<htd::vertex_t>> & buckets, const std::vector<std::vector<htd::vertex_t>> & neighbors, std::vector<std::vector<htd::index_t>> & inducedEdges, std::vector<htd::id_t> & lastAssignedEdge, std::stack<htd::vertex_t> & originStack) const
{
    long size = static_cast<long>(edge.size());

    htd::vertex_t currentBucket = startBucket;

    lastAssignedEdge[currentBucket] = static_cast<htd::id_t>(edgeIndex);

    inducedEdges[currentBucket].push_back(edgeIndex);

    htd::vertex_t firstVertex = edge[0];

    auto edgeBegin = edge.begin();
    auto edgeEnd = edge.end();

    for (htd::vertex_t neighbor : neighbors[currentBucket])
    {
        const std::vector<htd::vertex_t> & neighborBucketContent = buckets[neighbor];

        auto end = neighborBucketContent.end();

        auto position = std::lower_bound(neighborBucketContent.begin(), end, firstVertex);

        if (end - position >= size && std::includes(position, end, edgeBegin, edgeEnd))
        {
            originStack.push(neighbor);
        }
    }

    while (!originStack.empty())
    {
        htd::vertex_t lastBucket = currentBucket;

        currentBucket = originStack.top();

        originStack.pop();

        lastAssignedEdge[currentBucket] = static_cast<htd::id_t>(edgeIndex);

        inducedEdges[currentBucket].push_back(edgeIndex);

        for (htd::vertex_t neighbor : neighbors[currentBucket])
        {
            if (neighbor != lastBucket && lastAssignedEdge[neighbor] != edgeIndex)
            {
                const std::vector<htd::vertex_t> & neighborBucketContent = buckets[neighbor];

                auto end = neighborBucketContent.end();

                auto position = std::lower_bound(neighborBucketContent.begin(), end, firstVertex);

                if (end - position >= size && std::includes(position, end, edgeBegin, edgeEnd))
                {
                    originStack.push(neighbor);
                }
            }
        }
    }
}

void htd::BucketEliminationGraphDecompositionAlgorithm::Implementation::distributeEdge(htd::index_t edgeIndex, htd::vertex_t vertex1, htd::vertex_t vertex2, htd::vertex_t startBucket, const std::vector<std::vector<htd::vertex_t>> & buckets, const std::vector<std::vector<htd::vertex_t>> & neighbors, std::vector<std::vector<htd::index_t>> & inducedEdges, std::vector<htd::id_t> & lastAssignedEdge, std::stack<htd::vertex_t> & originStack) const
{
    htd::vertex_t currentBucket = startBucket;

    lastAssignedEdge[currentBucket] = static_cast<htd::id_t>(edgeIndex);

    inducedEdges[currentBucket].push_back(edgeIndex);

    for (htd::vertex_t neighbor : neighbors[currentBucket])
    {
        const std::vector<htd::vertex_t> & neighborBucketContent = buckets[neighbor];

        auto end = neighborBucketContent.end();

        auto position1 = std::lower_bound(neighborBucketContent.begin(), end, vertex1);

        if (position1 != end && *position1 == vertex1)
        {
            auto position2 = std::lower_bound(position1, end, vertex2);

            if (position2 != end && *position2 == vertex2)
            {
                originStack.push(neighbor);
            }
        }
    }

    while (!originStack.empty())
    {
        htd::vertex_t lastBucket = currentBucket;

        currentBucket = originStack.top();

        originStack.pop();

        lastAssignedEdge[currentBucket] = static_cast<htd::id_t>(edgeIndex);

        inducedEdges[currentBucket].push_back(edgeIndex);

        for (htd::vertex_t neighbor : neighbors[currentBucket])
        {
            if (neighbor != lastBucket && lastAssignedEdge[neighbor] != edgeIndex)
            {
                const std::vector<htd::vertex_t> & neighborBucketContent = buckets[neighbor];

                auto end = neighborBucketContent.end();

                auto position1 = std::lower_bound(neighborBucketContent.begin(), end, vertex1);

                if (position1 != end && *position1 == vertex1)
                {
                    auto position2 = std::lower_bound(position1, end, vertex2);

                    if (position2 != end && *position2 == vertex2)
                    {
                        originStack.push(neighbor);
                    }
                }
            }
        }
    }
}

void htd::BucketEliminationGraphDecompositionAlgorithm::Implementation::updateDecomposition(const htd::IMultiHypergraph & graph,
                                                                                            htd::IMutableGraphDecomposition & decomposition,
                                                                                            htd::vertex_t startingVertex,
                                                                                            const std::vector<std::vector<htd::vertex_t>> & neighbors,
                                                                                            std::vector<std::vector<htd::vertex_t>> & bagContent,
                                                                                            std::vector<std::vector<htd::index_t>> & inducedEdges,
                                                                                            std::unordered_set<htd::vertex_t> & unvisitedVertices,
                                                                                            std::unordered_map<htd::vertex_t, htd::vertex_t> & decompositionVertices) const
{
    htd::vertex_t currentNode = startingVertex;

    htd::index_t currentIndex = 0;

    std::stack<std::pair<htd::vertex_t, htd::index_t>> parentStack;

    while (!parentStack.empty() || currentNode != htd::Vertex::UNKNOWN)
    {
        if (currentNode != htd::Vertex::UNKNOWN)
        {
            if (currentIndex == 0)
            {
                htd::vertex_t decompositionVertex = decomposition.addVertex(std::vector<htd::vertex_t>(bagContent[currentNode]), graph.hyperedgesAtPositions(inducedEdges[currentNode]));

                decompositionVertices.emplace(currentNode, decompositionVertex);

                if (!parentStack.empty())
                {
                    decomposition.addEdge(decompositionVertices.at(parentStack.top().first), decompositionVertex);
                }

                unvisitedVertices.erase(currentNode);
            }

            if (currentIndex < neighbors[currentNode].size())
            {
                htd::vertex_t parent = htd::Vertex::UNKNOWN;

                if (!parentStack.empty())
                {
                    parent = parentStack.top().first;
                }

                htd::vertex_t nextNode = neighbors[currentNode][currentIndex];

                if (parent != nextNode)
                {
                    if (currentIndex < neighbors[currentNode].size())
                    {
                        parentStack.emplace(currentNode, currentIndex + 1);

                        currentNode = nextNode;

                        currentIndex = 0;
                    }
                }
                else
                {
                    ++currentIndex;

                    if (currentIndex < neighbors[currentNode].size())
                    {
                        parentStack.emplace(currentNode, currentIndex + 1);

                        currentNode = neighbors[currentNode][currentIndex];

                        currentIndex = 0;
                    }
                    else
                    {
                        currentNode = htd::Vertex::UNKNOWN;
                    }
                }
            }
            else
            {
                currentNode = htd::Vertex::UNKNOWN;
            }
        }
        else
        {
            currentNode = parentStack.top().first;

            currentIndex = parentStack.top().second;

            parentStack.pop();
        }
    }
}

#endif /* HTD_HTD_BUCKETELIMINATIONGRAPHDECOMPOSITIONALGORITHM_CPP */
