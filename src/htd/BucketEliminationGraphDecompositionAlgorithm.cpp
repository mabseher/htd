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
#include <htd/NamedGraph.hpp>

#include <algorithm>
#include <array>
#include <cstdarg>
#include <memory>
#include <stack>
#include <stdexcept>
#include <tuple>
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

htd::IGraphDecomposition * htd::BucketEliminationGraphDecompositionAlgorithm::computeDecomposition(const htd::IHypergraph & graph) const
{
    return computeDecomposition(graph, std::vector<htd::IDecompositionManipulationOperation *>());
}

htd::IGraphDecomposition * htd::BucketEliminationGraphDecompositionAlgorithm::computeDecomposition(const htd::IHypergraph & graph, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const
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

htd::IGraphDecomposition * htd::BucketEliminationGraphDecompositionAlgorithm::computeDecomposition(const htd::IHypergraph & graph, int manipulationOperationCount, ...) const
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

    return new BucketEliminationGraphDecompositionAlgorithm(manipulationOperations);
}

htd::IMutableGraphDecomposition * htd::BucketEliminationGraphDecompositionAlgorithm::computeMutableDecomposition(const htd::IHypergraph & graph) const
{
    htd::IMutableGraphDecomposition * ret = nullptr;

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

        std::vector<htd::index_t> indices(size);

        //std::vector<htd::vertex_t> vertexLabels(size, htd::Vertex::UNKNOWN);

        std::vector<htd::vertex_container> buckets(size);

        std::vector<htd::id_t> relevantBuckets;

        std::unordered_set<htd::vertex_t> isolatedVertices(ordering.begin(), ordering.end());

        DEBUGGING_CODE(std::cout << "Ordering:" << std::endl;

        for (htd::vertex_t vertex : ordering)
        {
            std::cout << vertex << std::endl;
        })

        std::size_t index = 0;

        for (htd::vertex_t vertex : ordering)
        {
            indices[vertex - htd::Vertex::FIRST] = index++;
        }

        for (std::size_t index = 0; index < size; index++)
        {
            buckets[index].push_back(index + htd::Vertex::FIRST);
        }

        for (const htd::Hyperedge & edge : graph.hyperedges())
        {
            htd::vertex_container elements = htd::vertex_container(edge.begin(), edge.end());

            std::sort(elements.begin(), elements.end());

            elements.erase(std::unique(elements.begin(), elements.end()), elements.end());

            htd::vertex_t minimumVertex = getMinimumVertex(elements, indices);

            auto & selectedBucket = buckets[minimumVertex - htd::Vertex::FIRST];

            std::vector<htd::vertex_t> newBucketContent;
            newBucketContent.reserve(selectedBucket.size());

            /*
            if (vertexLabels[minimumVertex - htd::Vertex::FIRST] == htd::unknown_id)
            {
                relevantBuckets.push_back(minimumVertex);
            }
            */

            if (elements.size() > 1)
            {
                for (htd::vertex_t vertex : elements)
                {
                    isolatedVertices.erase(vertex);
                }
            }

            //vertexLabels[minimumVertex - htd::Vertex::FIRST] = minimumVertex;

            std::set_union(selectedBucket.begin(), selectedBucket.end(), elements.begin(), elements.end(), std::back_inserter(newBucketContent));

            std::swap(selectedBucket, newBucketContent);
        }

        if (isolatedVertices.size() > 0)
        {
            for (htd::vertex_t vertex : isolatedVertices)
            {
                relevantBuckets.push_back(vertex);
            }
        }

        //TODO
        relevantBuckets.clear();
        std::copy(ordering.begin(), ordering.end(), std::back_inserter(relevantBuckets));

        std::sort(relevantBuckets.begin(), relevantBuckets.end());

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
            htd::print(buckets[bucket - htd::Vertex::FIRST], false);
            std::cout << std::endl;
        }

        std::cout << std::endl << "Connections:" << std::endl;
        )

        std::array<htd::vertex_t, 1> filterSet;

        htd::NamedGraph<htd::vertex_t, htd::id_t> result;

        for (htd::index_t index = 0; index < size; index++)
        {
            htd::vertex_t selection = ordering[index];

            DEBUGGING_CODE(std::cout << std::endl << "   Processing bucket " << selection << " ..." << std::endl;)

            const htd::vertex_container & bucket = buckets[selection - htd::Vertex::FIRST];

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

                auto & selectedBucket = buckets[minimumVertex - htd::Vertex::FIRST];

                std::vector<htd::vertex_t> newBucketContent;
                newBucketContent.reserve(selectedBucket.size());

                filterSet[0] = selection;

                htd::filtered_set_union(selectedBucket.begin(), selectedBucket.end(), bucket.begin(), bucket.end(), filterSet.begin(), filterSet.end(), std::back_inserter(newBucketContent));

                std::swap(selectedBucket, newBucketContent);

                //TODO
                /*
                htd::id_t selectionLabel = labels[selection];
                htd::id_t minimumVertexLabel = labels[minimumVertex];

                if (minimumVertexLabel != htd::unknown_id && selectionLabel != htd::unknown_id)
                {
                    ++edgeCount;

                    result.addEdge(selectionLabel, minimumVertexLabel);
                }
                */

                result.addEdge(selection, minimumVertex);
            }
        }

        DEBUGGING_CODE(std::cout << std::endl << "Buckets:" << std::endl;
        for (std::size_t index = 0; index < size; index++)
        {
            std::cout << "   Bucket " << index + htd::Vertex::FIRST << ": ";
            htd::print(buckets[index], false);
            std::cout << std::endl;
        })

        DEBUGGING_CODE(std::cout << std::endl << "Relevant Buckets:" << std::endl;
        for (htd::id_t bucket : relevantBuckets)
        {
            std::cout << "   Bucket " << bucket << ": ";
            htd::print(buckets[bucket - htd::Vertex::FIRST], false);
            std::cout << std::endl;
        })

        //TODO Fill ret!
    }

    return ret;
}

htd::vertex_t htd::BucketEliminationGraphDecompositionAlgorithm::getMinimumVertex(const std::vector<htd::vertex_t> & vertices, const std::vector<htd::index_t> & vertexIndices) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    if (vertices.size() > 0)
    {
        std::size_t minimum = (std::size_t)-1;

        std::size_t currentIndex = (std::size_t)-1;

        for (htd::vertex_t vertex : vertices)
        {
            currentIndex = vertexIndices[vertex - htd::Vertex::FIRST];

            if (currentIndex < minimum)
            {
                ret = vertex;

                minimum = currentIndex;
            }
        }
    }
    else
    {
        throw std::out_of_range("htd::BucketEliminationGraphDecompositionAlgorithm::getMinimumVertex(const htd::Collection<htd::vertex_t> &, const std::vector<htd::index_t> &) const");
    }

    return ret;
}

htd::vertex_t htd::BucketEliminationGraphDecompositionAlgorithm::getMinimumVertex(const std::vector<htd::vertex_t> & vertices, const std::vector<htd::index_t> & vertexIndices, htd::vertex_t excludedVertex) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    if (vertices.size() > 0)
    {
        std::size_t minimum = (std::size_t)-1;

        std::size_t currentIndex = (std::size_t)-1;

        for (htd::vertex_t vertex : vertices)
        {
            if (vertex != excludedVertex)
            {
                currentIndex = vertexIndices[vertex - htd::Vertex::FIRST];

                if (currentIndex < minimum)
                {
                    ret = vertex;

                    minimum = currentIndex;
                }
            }
        }
    }
    else
    {
        throw std::out_of_range("htd::BucketEliminationGraphDecompositionAlgorithm::getMinimumVertex(const htd::Collection<htd::vertex_t> &, const std::vector<htd::index_t> &, htd::vertex_t) const");
    }

    return ret;
}

#endif /* HTD_HTD_BUCKETELIMINATIONGRAPHDECOMPOSITIONALGORITHM_CPP */
