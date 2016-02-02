/* 
 * File:   BucketEliminationTreeDecompositionAlgorithm.cpp
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

#ifndef HTD_HTD_BUCKETELIMINATIONTREEDECOMPOSITIONALGORITHM_CPP
#define	HTD_HTD_BUCKETELIMINATIONTREEDECOMPOSITIONALGORITHM_CPP


#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/BucketEliminationTreeDecompositionAlgorithm.hpp>
#include <htd/BucketEliminationGraphDecompositionAlgorithm.hpp>
#include <htd/ConnectedComponentAlgorithmFactory.hpp>
#include <htd/GraphDecompositionFactory.hpp>
#include <htd/TreeDecompositionFactory.hpp>
#include <htd/GraphLabeling.hpp>
#include <htd/ILabelingFunction.hpp>
#include <htd/CompressionOperation.hpp>
#include <htd/OrderingAlgorithmFactory.hpp>
#include <htd/BreadthFirstGraphTraversal.hpp>

#include <algorithm>
#include <cstdarg>
#include <memory>
#include <stack>
#include <stdexcept>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

htd::BucketEliminationTreeDecompositionAlgorithm::BucketEliminationTreeDecompositionAlgorithm(bool compressed) : compressed_(compressed), labelingFunctions_(), postProcessingOperations_()
{

}

htd::BucketEliminationTreeDecompositionAlgorithm::BucketEliminationTreeDecompositionAlgorithm(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations, bool compressed) : compressed_(compressed), labelingFunctions_(), postProcessingOperations_()
{
    setManipulationOperations(manipulationOperations);
}

htd::BucketEliminationTreeDecompositionAlgorithm::~BucketEliminationTreeDecompositionAlgorithm()
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

htd::ITreeDecomposition * htd::BucketEliminationTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph) const
{
    return computeDecomposition(graph, std::vector<htd::IDecompositionManipulationOperation *>());
}

htd::ITreeDecomposition * htd::BucketEliminationTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const
{
    htd::IMutableTreeDecomposition * ret = computeMutableDecomposition(graph);

    std::vector<htd::ILabelingFunction *> labelingFunctions;

    std::vector<htd::ITreeDecompositionManipulationOperation *> postProcessingOperations;

    for (htd::IDecompositionManipulationOperation * operation : manipulationOperations)
    {
        htd::ILabelingFunction * labelingFunction = dynamic_cast<htd::ILabelingFunction *>(operation);

        if (labelingFunction != nullptr)
        {
            labelingFunctions.push_back(labelingFunction);
        }

        htd::ITreeDecompositionManipulationOperation * manipulationOperation = dynamic_cast<htd::ITreeDecompositionManipulationOperation *>(operation);

        if (manipulationOperation != nullptr)
        {
            postProcessingOperations.push_back(manipulationOperation);
        }
    }

    if (ret != nullptr)
    {
        if (compressed_)
        {
            htd::CompressionOperation compressionOperation;

            compressionOperation.apply(*ret);
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

        for (const auto & operation : postProcessingOperations_)
        {
            operation->apply(*ret);
        }

        for (const auto & operation : postProcessingOperations)
        {
            operation->apply(*ret);
        }
    }

    return ret;
}

htd::ITreeDecomposition * htd::BucketEliminationTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, int manipulationOperationCount, ...) const
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

void htd::BucketEliminationTreeDecompositionAlgorithm::setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
{
    labelingFunctions_.clear();

    postProcessingOperations_.clear();

    addManipulationOperations(manipulationOperations);
}

void htd::BucketEliminationTreeDecompositionAlgorithm::addManipulationOperation(htd::IDecompositionManipulationOperation * manipulationOperation)
{
    htd::ILabelingFunction * labelingFunction = dynamic_cast<htd::ILabelingFunction *>(manipulationOperation);

    if (labelingFunction != nullptr)
    {
        labelingFunctions_.push_back(labelingFunction);
    }

    htd::ITreeDecompositionManipulationOperation * newManipulationOperation = dynamic_cast<htd::ITreeDecompositionManipulationOperation *>(manipulationOperation);

    if (newManipulationOperation != nullptr)
    {
        postProcessingOperations_.push_back(newManipulationOperation);
    }
}

void htd::BucketEliminationTreeDecompositionAlgorithm::addManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
{
    for (htd::IDecompositionManipulationOperation * operation : manipulationOperations)
    {
        htd::ILabelingFunction * labelingFunction = dynamic_cast<htd::ILabelingFunction *>(operation);

        if (labelingFunction != nullptr)
        {
            labelingFunctions_.push_back(labelingFunction);
        }

        htd::ITreeDecompositionManipulationOperation * manipulationOperation = dynamic_cast<htd::ITreeDecompositionManipulationOperation *>(operation);

        if (manipulationOperation != nullptr)
        {
            postProcessingOperations_.push_back(manipulationOperation);
        }
    }
}

htd::BucketEliminationTreeDecompositionAlgorithm * htd::BucketEliminationTreeDecompositionAlgorithm::clone(void) const
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

    return new htd::BucketEliminationTreeDecompositionAlgorithm(manipulationOperations, compressed_);
}

htd::IMutableTreeDecomposition * htd::BucketEliminationTreeDecompositionAlgorithm::computeMutableDecomposition(const htd::IMultiHypergraph & graph) const
{
    htd::IMutableTreeDecomposition * ret = htd::TreeDecompositionFactory::instance().getTreeDecomposition();

    std::size_t size = graph.vertexCount();

    if (size > 0)
    {
        htd::BucketEliminationGraphDecompositionAlgorithm graphDecompositionAlgorithm;

        htd::IGraphDecomposition * graphDecomposition = graphDecompositionAlgorithm.computeDecomposition(graph);

        if (graphDecomposition == nullptr)
        {
            throw std::logic_error("htd::IMutableTreeDecomposition * htd::BucketEliminationTreeDecompositionAlgorithm::computeMutableDecomposition(const htd::IHypergraph &) const");
        }

        htd::IMutableGraphDecomposition & mutableGraphDecomposition = htd::GraphDecompositionFactory::instance().accessMutableGraphDecomposition(*graphDecomposition);

        if (mutableGraphDecomposition.edgeCount() + 1 != mutableGraphDecomposition.vertexCount() || mutableGraphDecomposition.isolatedVertexCount() > 0)
        {
            htd::IConnectedComponentAlgorithm * connectedComponentAlgorithm = htd::ConnectedComponentAlgorithmFactory::instance().getConnectedComponentAlgorithm();

            if (connectedComponentAlgorithm == nullptr)
            {
                throw std::logic_error("htd::IMutableTreeDecomposition * htd::BucketEliminationTreeDecompositionAlgorithm::computeMutableDecomposition(const htd::IHypergraph &) const");
            }

            htd::ConstCollection<htd::ConstCollection<htd::vertex_t>> components = connectedComponentAlgorithm->determineComponents(*graphDecomposition);

            delete connectedComponentAlgorithm;

            std::size_t componentCount = components.size();

            if (componentCount > 1)
            {
                for (htd::index_t index = 0; index < componentCount - 1; ++index)
                {
                    const htd::ConstCollection<htd::vertex_t> & component1 = components[index];
                    const htd::ConstCollection<htd::vertex_t> & component2 = components[index + 1];

                    htd::vertex_t vertex1 = component1[rand() % component1.size()];
                    htd::vertex_t vertex2 = component2[rand() % component2.size()];

                    mutableGraphDecomposition.addEdge(vertex1, vertex2);
                }
            }
        }

        htd::vertex_t node = htd::Vertex::UNKNOWN;

        std::unordered_map<int, int> vertexMapping;

        htd::BreadthFirstGraphTraversal graphTraversal;

        const htd::ConstCollection<htd::vertex_t> & vertexCollection = graphDecomposition->vertices();

        graphTraversal.traverse(*graphDecomposition, vertexCollection[rand() % vertexCollection.size()], [&](htd::vertex_t vertex, htd::vertex_t predecessor, std::size_t distanceFromStartingVertex)
        {
            HTD_UNUSED(distanceFromStartingVertex)

            if (predecessor == htd::Vertex::UNKNOWN)
            {
                node = ret->insertRoot();
            }
            else
            {
                node = ret->addChild(vertexMapping.at(predecessor));
            }

            vertexMapping[vertex] = node;

            ret->setVertexLabel(htd::ITreeDecomposition::BAG_LABEL_IDENTIFIER, node, mutableGraphDecomposition.transferVertexLabel(htd::IGraphDecomposition::BAG_LABEL_IDENTIFIER, vertex));
        });

        delete graphDecomposition;
    }
    else
    {
        ret->insertRoot();
    }

    return ret;
}

#endif /* HTD_HTD_BUCKETELIMINATIONTREEDECOMPOSITIONALGORITHM_CPP */
