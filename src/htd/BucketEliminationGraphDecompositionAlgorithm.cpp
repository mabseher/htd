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
#include <htd/GraphLabeling.hpp>
#include <htd/ILabelingFunction.hpp>
#include <htd/OrderingAlgorithmFactory.hpp>
#include <htd/GraphDecompositionFactory.hpp>
#include <htd/NamedMultiGraph.hpp>

#include <algorithm>
#include <array>
#include <cstdarg>
#include <memory>
#include <stack>
#include <stdexcept>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

htd::BucketEliminationGraphDecompositionAlgorithm::BucketEliminationGraphDecompositionAlgorithm(void) : labelingFunctions_(), postProcessingOperations_()
{

}

htd::BucketEliminationGraphDecompositionAlgorithm::BucketEliminationGraphDecompositionAlgorithm(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) : labelingFunctions_(), postProcessingOperations_()
{
    setManipulationOperations(manipulationOperations);
}

htd::BucketEliminationGraphDecompositionAlgorithm::~BucketEliminationGraphDecompositionAlgorithm()
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

htd::IGraphDecomposition * htd::BucketEliminationGraphDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph) const
{
    return computeDecomposition(graph, std::vector<htd::IDecompositionManipulationOperation *>());
}

htd::IGraphDecomposition * htd::BucketEliminationGraphDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const
{
    htd::IMutableGraphDecomposition * ret = computeMutableDecomposition(graph);

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
        for (const auto & operation : postProcessingOperations_)
        {
            operation->apply(*ret);
        }

        for (const auto & operation : postProcessingOperations)
        {
            operation->apply(*ret);
        }

        for (const auto & labelingFunction : labelingFunctions_)
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

    return computeDecomposition(graph, manipulationOperations);
}

void htd::BucketEliminationGraphDecompositionAlgorithm::setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
{
    labelingFunctions_.clear();

    postProcessingOperations_.clear();

    addManipulationOperations(manipulationOperations);
}

void htd::BucketEliminationGraphDecompositionAlgorithm::addManipulationOperation(htd::IDecompositionManipulationOperation * manipulationOperation)
{
    htd::ILabelingFunction * labelingFunction = dynamic_cast<htd::ILabelingFunction *>(manipulationOperation);

    if (labelingFunction != nullptr)
    {
        labelingFunctions_.push_back(labelingFunction);
    }

    htd::IGraphDecompositionManipulationOperation * newManipulationOperation = dynamic_cast<htd::IGraphDecompositionManipulationOperation *>(manipulationOperation);

    if (newManipulationOperation != nullptr)
    {
        postProcessingOperations_.push_back(newManipulationOperation);
    }
}

void htd::BucketEliminationGraphDecompositionAlgorithm::addManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
{
    for (htd::IDecompositionManipulationOperation * operation : manipulationOperations)
    {
        htd::ILabelingFunction * labelingFunction = dynamic_cast<htd::ILabelingFunction *>(operation);

        if (labelingFunction != nullptr)
        {
            labelingFunctions_.push_back(labelingFunction);
        }

        htd::IGraphDecompositionManipulationOperation * manipulationOperation = dynamic_cast<htd::IGraphDecompositionManipulationOperation *>(operation);

        if (manipulationOperation != nullptr)
        {
            postProcessingOperations_.push_back(manipulationOperation);
        }
    }
}

htd::BucketEliminationGraphDecompositionAlgorithm * htd::BucketEliminationGraphDecompositionAlgorithm::clone(void) const
{
    std::vector<htd::IDecompositionManipulationOperation *> manipulationOperations;

    for (const auto & labelingFunction : labelingFunctions_)
    {
        manipulationOperations.push_back(labelingFunction->clone());
    }

    for (const auto & postProcessingOperation : postProcessingOperations_)
    {
        manipulationOperations.push_back(postProcessingOperation->clone());
    }

    return new htd::BucketEliminationGraphDecompositionAlgorithm(manipulationOperations);
}

htd::IMutableGraphDecomposition * htd::BucketEliminationGraphDecompositionAlgorithm::computeMutableDecomposition(const htd::IMultiHypergraph & graph) const
{
    htd::IMutableGraphDecomposition * ret = htd::GraphDecompositionFactory::instance().getGraphDecomposition();

    std::size_t size = graph.vertexCount();

    if (size > 0)
    {
        htd::IOrderingAlgorithm * algorithm = htd::OrderingAlgorithmFactory::instance().getOrderingAlgorithm();

        if (algorithm == nullptr)
        {
            throw std::logic_error("htd::IMutableGraphDecomposition * htd::BucketEliminationGraphDecompositionAlgorithm::computeMutableDecomposition(const htd::IHypergraph &) const");
        }

        const htd::ConstCollection<htd::vertex_t> & ordering = algorithm->computeOrdering(graph);

        delete algorithm;

        std::unordered_map<htd::vertex_t, htd::index_t> indices(size);

        std::unordered_map<htd::vertex_t, htd::vertex_container> buckets(size);

        DEBUGGING_CODE(std::cout << "Ordering:" << std::endl;
        for (htd::vertex_t vertex : ordering)
        {
            std::cout << vertex << std::endl;
        })

        std::size_t index = 0;

        for (htd::vertex_t vertex : ordering)
        {
            indices[vertex] = index++;

            buckets[vertex].push_back(vertex);
        }

        for (const htd::Hyperedge & edge : graph.hyperedges())
        {
            switch (edge.size())
            {
                case 1:
                {
                    break;
                }
                case 2:
                {
                    htd::vertex_t vertex1 = edge[0];
                    htd::vertex_t vertex2 = edge[1];

                    if (vertex1 != vertex2)
                    {
                        if (indices.at(vertex1) < indices.at(vertex2))
                        {
                            auto & selectedBucket = buckets[vertex1];

                            auto position = std::lower_bound(selectedBucket.begin(), selectedBucket.end(), vertex2);

                            if (position == selectedBucket.end() || *position != vertex2)
                            {
                                selectedBucket.insert(position, vertex2);
                            }
                        }
                        else
                        {
                            auto & selectedBucket = buckets[vertex2];

                            auto position = std::lower_bound(selectedBucket.begin(), selectedBucket.end(), vertex1);

                            if (position == selectedBucket.end() || *position != vertex1)
                            {
                                selectedBucket.insert(position, vertex1);
                            }
                        }
                    }

                    break;
                }
                default:
                {
                    htd::vertex_container elements;

                    edge.copyTo(elements);

                    std::sort(elements.begin(), elements.end());

                    elements.erase(std::unique(elements.begin(), elements.end()), elements.end());

                    htd::vertex_t minimumVertex = getMinimumVertex(elements, indices);

                    auto & selectedBucket = buckets[minimumVertex];

                    std::vector<htd::vertex_t> newBucketContent;
                    newBucketContent.reserve(selectedBucket.size());

                    std::set_union(selectedBucket.begin(), selectedBucket.end(), elements.begin(), elements.end(), std::back_inserter(newBucketContent));

                    std::swap(selectedBucket, newBucketContent);

                    break;
                }
            }
        }

        DEBUGGING_CODE(std::cout << std::endl << "Buckets:" << std::endl;
        for (std::size_t index = 0; index < size; index++)
        {
            std::cout << "   Bucket " << index + htd::Vertex::FIRST << ": ";
            htd::print(buckets[index], false);
            std::cout << std::endl;
        }

        std::cout << std::endl << "Relevant Buckets:" << std::endl;
        for (htd::id_t bucket : relevantBuckets)
        {
            std::cout << "   Bucket " << bucket << ": ";
            htd::print(buckets[bucket], false);
            std::cout << std::endl;
        }

        std::cout << std::endl << "Connections:" << std::endl;
        )

        htd::NamedMultiGraph<htd::vertex_t, htd::id_t> result;

        for (htd::vertex_t selection : ordering)
        {
            DEBUGGING_CODE(std::cout << std::endl << "   Processing bucket " << selection << " ..." << std::endl;)

            const htd::vertex_container & bucket = buckets[selection];

            if (bucket.size() > 1)
            {
                DEBUGGING_CODE(
                    std::cout << "      Bucket " << selection << ": ";
                    htd::print(bucket, false);
                    std::cout << std::endl;
                )

                htd::vertex_t minimumVertex = getMinimumVertex(bucket, indices, selection);

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

                auto & selectedBucket = buckets[minimumVertex];

                std::vector<htd::vertex_t> newBucketContent;
                newBucketContent.reserve(selectedBucket.size() + bucket.size());

                htd::set_union(selectedBucket, bucket, selection, newBucketContent);

                std::swap(selectedBucket, newBucketContent);

                result.addEdge(selection, minimumVertex);
            }
            else
            {
                result.addVertex(selection);
            }
        }

        DEBUGGING_CODE(std::cout << std::endl << "Buckets:" << std::endl;
        for (std::size_t index = 0; index < size; index++)
        {
            std::cout << "   Bucket " << index + htd::Vertex::FIRST << ": ";
            htd::print(buckets[index], false);
            std::cout << std::endl;
        })

        *ret = result.internalGraph();

        for (htd::vertex_t vertex : result.vertices())
        {
            ret->setBagContent(result.lookupVertex(vertex), std::move(buckets[vertex]));
        }
    }

    return ret;
}

htd::vertex_t htd::BucketEliminationGraphDecompositionAlgorithm::getMinimumVertex(const std::vector<htd::vertex_t> & vertices, const std::unordered_map<htd::vertex_t, htd::index_t> & vertexIndices) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    switch (vertices.size())
    {
        case 0:
        {
            throw std::out_of_range("htd::BucketEliminationGraphDecompositionAlgorithm::getMinimumVertex(const htd::Collection<htd::vertex_t> &, const std::unordered_map<htd::vertex_t, htd::index_t> &) const");
        }
        case 1:
        {
            ret = vertices[0];

            break;
        }
        case 2:
        {
            if (vertexIndices.at(vertices[0]) <= vertexIndices.at(vertices[1]))
            {
                ret = vertices[0];
            }
            else
            {
                ret = vertices[1];
            }

            break;
        }
        default:
        {
            std::size_t minimum = (std::size_t)-1;

            std::size_t currentIndex = (std::size_t)-1;

            for (htd::vertex_t vertex : vertices)
            {
                currentIndex = vertexIndices.at(vertex);

                if (currentIndex < minimum)
                {
                    ret = vertex;

                    minimum = currentIndex;
                }
            }

            break;
        }
    }

    return ret;
}

htd::vertex_t htd::BucketEliminationGraphDecompositionAlgorithm::getMinimumVertex(const std::vector<htd::vertex_t> & vertices, const std::unordered_map<htd::vertex_t, htd::index_t> & vertexIndices, htd::vertex_t excludedVertex) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    switch (vertices.size())
    {
        case 0:
        {
            throw std::out_of_range("htd::BucketEliminationGraphDecompositionAlgorithm::getMinimumVertex(const htd::Collection<htd::vertex_t> &, const std::unordered_map<htd::vertex_t, htd::index_t> &, htd::vertex_t) const");
        }
        case 1:
        {
            if (vertices[0] == excludedVertex)
            {
                throw std::out_of_range("htd::BucketEliminationGraphDecompositionAlgorithm::getMinimumVertex(const htd::Collection<htd::vertex_t> &, const std::unordered_map<htd::vertex_t, htd::index_t> &, htd::vertex_t) const");
            }

            ret = vertices[0];

            break;
        }
        case 2:
        {
            if (vertices[0] == excludedVertex)
            {
                ret = vertices[1];
            }
            else if (vertices[1] == excludedVertex)
            {
                ret = vertices[0];
            }
            else if (vertexIndices.at(vertices[0]) <= vertexIndices.at(vertices[1]))
            {
                ret = vertices[0];
            }
            else
            {
                ret = vertices[1];
            }

            break;
        }
        default:
        {
            std::size_t minimum = (std::size_t)-1;

            std::size_t currentIndex = (std::size_t)-1;

            for (htd::vertex_t vertex : vertices)
            {
                if (vertex != excludedVertex)
                {
                    currentIndex = vertexIndices.at(vertex);

                    if (currentIndex < minimum)
                    {
                        ret = vertex;

                        minimum = currentIndex;
                    }
                }
            }

            break;
        }
    }

    return ret;
}

#endif /* HTD_HTD_BUCKETELIMINATIONGRAPHDECOMPOSITIONALGORITHM_CPP */
