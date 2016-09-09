/*
 * File:   BucketEliminationGraphDecompositionAlgorithm.cpp
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

#ifndef HTD_HTD_BUCKETELIMINATIONGRAPHDECOMPOSITIONALGORITHM_CPP
#define	HTD_HTD_BUCKETELIMINATIONGRAPHDECOMPOSITIONALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/BucketEliminationGraphDecompositionAlgorithm.hpp>
#include <htd/BidirectionalGraphNaming.hpp>
#include <htd/ILabelingFunction.hpp>
#include <htd/OrderingAlgorithmFactory.hpp>
#include <htd/GraphDecompositionFactory.hpp>

#include <algorithm>
#include <array>
#include <cstdarg>
#include <functional>
#include <memory>
#include <stack>
#include <stdexcept>
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
    Implementation(const htd::LibraryInstance * const manager) : managementInstance_(manager), labelingFunctions_(), postProcessingOperations_()
    {

    }

    virtual ~Implementation()
    {
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
     *  The labeling functions which are applied after the decomposition was computed.
     */
    std::vector<htd::ILabelingFunction *> labelingFunctions_;

    /**
     *  The manipuation operations which are applied after the decomposition was computed.
     */
    std::vector<htd::IGraphDecompositionManipulationOperation *> postProcessingOperations_;

    /**
     *  Compute a new mutable graph decompostion of the given graph.
     *
     *  @param[in] graph    The graph which shall be decomposed.
     *
     *  @return A mutable graph decompostion of the given graph.
     */
    htd::IMutableGraphDecomposition * computeMutableDecomposition(const htd::IMultiHypergraph & graph) const;

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
            if (tmp.size() <= 8)
            {
                auto it = set1.begin();

                for (htd::vertex_t newVertex : tmp)
                {
                    it = set1.insert(std::lower_bound(it, set1.end(), newVertex), newVertex) + 1;
                }
            }
            else
            {
                htd::index_t middle = set1.size();

                set1.insert(set1.end(), tmp.begin(), tmp.end());

                std::inplace_merge(set1.begin(), set1.begin() + middle, set1.end());
            }
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
    htd::IMutableGraphDecomposition * ret = implementation_->computeMutableDecomposition(graph);

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

    if (ret != nullptr)
    {
        for (const auto & operation : implementation_->postProcessingOperations_)
        {
            operation->apply(graph, *ret);
        }

        for (const auto & operation : postProcessingOperations)
        {
            operation->apply(graph, *ret);
        }

        for (const auto & labelingFunction : implementation_->labelingFunctions_)
        {
            for (htd::vertex_t vertex : ret->vertices())
            {
                htd::ILabelCollection * labelCollection = ret->labelings().exportVertexLabelCollection(vertex);

                htd::ILabel * newLabel = labelingFunction->computeLabel(ret->bagContent(vertex), *labelCollection);

                delete labelCollection;

                ret->setVertexLabel(labelingFunction->name(), vertex, newLabel);
            }
        }

        for (const auto & labelingFunction : labelingFunctions)
        {
            for (htd::vertex_t vertex : ret->vertices())
            {
                htd::ILabelCollection * labelCollection = ret->labelings().exportVertexLabelCollection(vertex);

                htd::ILabel * newLabel = labelingFunction->computeLabel(ret->bagContent(vertex), *labelCollection);

                delete labelCollection;

                ret->setVertexLabel(labelingFunction->name(), vertex, newLabel);
            }
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

htd::BucketEliminationGraphDecompositionAlgorithm * htd::BucketEliminationGraphDecompositionAlgorithm::clone(void) const
{
    htd::BucketEliminationGraphDecompositionAlgorithm * ret = new htd::BucketEliminationGraphDecompositionAlgorithm(implementation_->managementInstance_);

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

    return ret;
}

htd::IMutableGraphDecomposition * htd::BucketEliminationGraphDecompositionAlgorithm::Implementation::computeMutableDecomposition(const htd::IMultiHypergraph & graph) const
{
    const htd::LibraryInstance & managementInstance = *managementInstance_;

    htd::IMutableGraphDecomposition * ret = managementInstance.graphDecompositionFactory().getGraphDecomposition();

    std::size_t size = graph.vertexCount();

    if (size > 0)
    {
        htd::IOrderingAlgorithm * algorithm = managementInstance.orderingAlgorithmFactory().getOrderingAlgorithm();

        HTD_ASSERT(algorithm != nullptr)

        std::vector<htd::vertex_t> ordering;

        algorithm->writeOrderingTo(graph, ordering);

        delete algorithm;

        if (!managementInstance.isTerminated())
        {
            htd::vertex_t lastVertex = graph.vertexAtPosition(size - 1);

            std::vector<htd::index_t> indices(lastVertex + 1);

            std::vector<std::vector<htd::vertex_t>> buckets(lastVertex + 1);

            std::vector<htd::vertex_t> superset(lastVertex + 1);

            std::vector<std::vector<htd::vertex_t>> neighbors(lastVertex + 1);

            std::vector<htd::vertex_t> edgeTarget(graph.edgeCount());

            std::size_t index = 0;

            for (htd::vertex_t vertex : ordering)
            {
                indices[vertex] = index++;

                superset[vertex] = vertex;

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
                        edgeTarget[index] = elements[0];

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
                        }

                        break;
                    }
                    default:
                    {
                        htd::vertex_t minimumVertex = getMinimumVertex(elements, ordering, indices);

                        htd::inplace_set_union(buckets[minimumVertex], elements);

                        edgeTarget[index] = minimumVertex;

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

                    if (selectedBucket.size() + 1 > bucket.size())
                    {
                        htd::vertex_t supersetVertex = superset[minimumVertex];

                        if (supersetVertex != minimumVertex)
                        {
                            const std::vector<htd::vertex_t> & supersetBucket = buckets[supersetVertex];

                            if (!std::includes(supersetBucket.begin(), supersetBucket.end(), selectedBucket.begin(), selectedBucket.end()))
                            {
                                superset[minimumVertex] = minimumVertex;
                            }
                        }
                    }
                    else
                    {
                        superset[minimumVertex] = superset[selection];
                    }
                }
            }

            std::deque<std::pair<htd::vertex_t, htd::vertex_t>> decompositionEdges;

            std::unordered_map<htd::vertex_t, htd::vertex_t> decompositionVertices;

            std::vector<htd::vertex_t> vertexNames;

            htd::vertex_t nextVertexId = htd::Id::FIRST;

            for (auto it = ordering.begin(); it != ordering.end() && !managementInstance.isTerminated(); ++it)
            {
                htd::vertex_t vertex = *it;

                const std::vector<htd::vertex_t> & currentNeighborhood = neighbors[vertex];

                if (superset[vertex] != vertex)
                {
                    switch (currentNeighborhood.size())
                    {
                        case 0:
                        {
                            break;
                        }
                        case 1:
                        {
                            std::vector<htd::vertex_t> & twoHopNeighborhood = neighbors[currentNeighborhood[0]];

                            twoHopNeighborhood.erase(std::find(twoHopNeighborhood.begin(), twoHopNeighborhood.end(), vertex));

                            break;
                        }
                        case 2:
                        {
                            htd::vertex_t neighbor1 = currentNeighborhood[0];
                            htd::vertex_t neighbor2 = currentNeighborhood[1];

                            std::vector<htd::vertex_t> & twoHopNeighborhood1 = neighbors[neighbor1];
                            std::vector<htd::vertex_t> & twoHopNeighborhood2 = neighbors[neighbor2];

                            *(std::find(twoHopNeighborhood1.begin(), twoHopNeighborhood1.end(), vertex)) = neighbor2;
                            *(std::find(twoHopNeighborhood2.begin(), twoHopNeighborhood2.end(), vertex)) = neighbor1;

                            if (superset[neighbor1] == neighbor1 && superset[neighbor2] == neighbor2)
                            {
                                std::pair<std::unordered_map<htd::vertex_t, htd::vertex_t>::iterator, bool> vertex1 = decompositionVertices.emplace(neighbor1, nextVertexId);

                                if (vertex1.second)
                                {
                                    vertexNames.push_back(neighbor1);

                                    ++nextVertexId;
                                }

                                std::pair<std::unordered_map<htd::vertex_t, htd::vertex_t>::iterator, bool> vertex2 = decompositionVertices.emplace(neighbor2, nextVertexId);

                                if (vertex2.second)
                                {
                                    vertexNames.push_back(neighbor2);

                                    ++nextVertexId;
                                }

                                decompositionEdges.emplace_back(vertex1.first->second, vertex2.first->second);
                            }

                            break;
                        }
                        default:
                        {
                            htd::vertex_t replacement = htd::Vertex::UNKNOWN;

                            std::vector<htd::vertex_t> & currentBucket = buckets[vertex];

                            for (auto it2 = currentNeighborhood.begin(); replacement == htd::Vertex::UNKNOWN && it2 != currentNeighborhood.end(); ++it2)
                            {
                                const std::vector<htd::vertex_t> & currentBucket2 = buckets[*it2];

                                if (currentBucket2.size() >= currentBucket.size() && std::includes(currentBucket2.begin(), currentBucket2.end(), currentBucket.begin(), currentBucket.end()))
                                {
                                    replacement = *it2;
                                }
                            }

                            std::vector<htd::vertex_t> & replacementNeighborhood = neighbors[replacement];

                            replacementNeighborhood.erase(std::find(replacementNeighborhood.begin(), replacementNeighborhood.end(), vertex));

                            std::copy_if(currentNeighborhood.begin(), currentNeighborhood.end(), std::back_inserter(replacementNeighborhood), [&](htd::vertex_t neighbor) { return neighbor != replacement; });

                            for (htd::vertex_t neighbor : currentNeighborhood)
                            {
                                if (neighbor != replacement)
                                {
                                    std::vector<htd::vertex_t> & currentNeighborhood2 = neighbors[neighbor];

                                    /* Because 'neighbor' is a neighbor of 'vertex', std::lower_bound will always find 'vertex' in 'currentNeighborhood2'. */
                                    // coverity[deref_iterator]
                                    *(std::find(currentNeighborhood2.begin(), currentNeighborhood2.end(), vertex)) = replacement;

                                    if (superset[replacement] == replacement && superset[neighbor] == neighbor)
                                    {
                                        std::pair<std::unordered_map<htd::vertex_t, htd::vertex_t>::iterator, bool> vertex1 = decompositionVertices.emplace(replacement, nextVertexId);

                                        if (vertex1.second)
                                        {
                                            vertexNames.push_back(replacement);

                                            ++nextVertexId;
                                        }

                                        std::pair<std::unordered_map<htd::vertex_t, htd::vertex_t>::iterator, bool> vertex2 = decompositionVertices.emplace(neighbor, nextVertexId);

                                        if (vertex2.second)
                                        {
                                            vertexNames.push_back(neighbor);

                                            ++nextVertexId;
                                        }

                                        decompositionEdges.emplace_back(vertex1.first->second, vertex2.first->second);
                                    }
                                }
                            }

                            break;
                        }
                    }

                    std::vector<htd::vertex_t>().swap(neighbors[vertex]);
                }
                else
                {
                    bool connected = false;

                    for (htd::vertex_t neighbor : currentNeighborhood)
                    {
                        if (indices[neighbor] > indices[vertex] && superset[neighbor] == neighbor)
                        {
                            std::pair<std::unordered_map<htd::vertex_t, htd::vertex_t>::iterator, bool> vertex1 = decompositionVertices.emplace(vertex, nextVertexId);

                            if (vertex1.second)
                            {
                                vertexNames.push_back(vertex);

                                ++nextVertexId;
                            }

                            std::pair<std::unordered_map<htd::vertex_t, htd::vertex_t>::iterator, bool> vertex2 = decompositionVertices.emplace(neighbor, nextVertexId);

                            if (vertex2.second)
                            {
                                vertexNames.push_back(neighbor);

                                ++nextVertexId;
                            }

                            decompositionEdges.emplace_back(vertex1.first->second, vertex2.first->second);

                            connected = true;
                        }
                    }

                    if (!connected)
                    {
                        std::pair<std::unordered_map<htd::vertex_t, htd::vertex_t>::iterator, bool> vertex1 = decompositionVertices.emplace(vertex, static_cast<htd::vertex_t>(vertexNames.size()) + 1);

                        if (vertex1.second)
                        {
                            vertexNames.push_back(vertex);

                            ++nextVertexId;
                        }
                    }
                }
            }

            std::vector<std::vector<htd::index_t>> inducedEdges(lastVertex + 1);

            hyperedgePosition = hyperedges.begin();

            std::vector<htd::id_t> lastAssignedEdge(buckets.size() + 1, (htd::id_t)-1);

            std::stack<htd::vertex_t> originStack;

            for (index = 0; index < edgeCount && !managementInstance.isTerminated(); ++index)
            {
                distributeEdge(index, hyperedgePosition->sortedElements(), superset[edgeTarget[index]], buckets, neighbors, inducedEdges, lastAssignedEdge, originStack);

                ++hyperedgePosition;
            }

            for (auto it2 = vertexNames.begin(); it2 != vertexNames.end() && !managementInstance.isTerminated(); ++it2)
            {
                ret->addVertex(std::move(buckets[*it2]), graph.hyperedgesAtPositions(std::move(inducedEdges[*it2])));
            }

            for (auto it2 = decompositionEdges.begin(); it2 != decompositionEdges.end() && !managementInstance.isTerminated(); ++it2)
            {
                if (it2->first < it2->second)
                {
                    ret->addEdge(it2->first, it2->second);
                }
                else
                {
                    ret->addEdge(it2->second, it2->first);
                }
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

    return ret;
}

htd::vertex_t htd::BucketEliminationGraphDecompositionAlgorithm::Implementation::getMinimumVertex(const std::vector<htd::vertex_t> & vertices, const std::vector<htd::vertex_t> & ordering, const std::vector<htd::index_t> & vertexIndices) const
{
    std::size_t minimum = (std::size_t)-1;

    for (htd::vertex_t vertex : vertices)
    {
        htd::index_t currentIndex = vertexIndices[vertex];

        if (currentIndex < minimum)
        {
            minimum = currentIndex;
        }
    }

    return ordering[minimum];
}

htd::vertex_t htd::BucketEliminationGraphDecompositionAlgorithm::Implementation::getMinimumVertex(const std::vector<htd::vertex_t> & vertices, const std::vector<htd::vertex_t> & ordering, const std::vector<htd::index_t> & vertexIndices, htd::vertex_t excludedVertex) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    if (vertices.size() == 2)
    {
        if (vertices[0] == excludedVertex)
        {
            ret = vertices[1];
        }
        else if (vertices[1] == excludedVertex)
        {
            ret = vertices[0];
        }
        else if (vertexIndices[vertices[0]] <= vertexIndices[vertices[1]])
        {
            ret = vertices[0];
        }
        else
        {
            ret = vertices[1];
        }
    }
    else
    {
        std::size_t minimum = (std::size_t)-1;

        for (htd::vertex_t vertex : vertices)
        {
            if (vertex != excludedVertex)
            {
                htd::index_t currentIndex = vertexIndices[vertex];

                if (currentIndex < minimum)
                {
                    minimum = currentIndex;
                }
            }
        }

        ret = ordering[minimum];
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

#endif /* HTD_HTD_BUCKETELIMINATIONGRAPHDECOMPOSITIONALGORITHM_CPP */
