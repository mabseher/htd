/* 
 * File:   HypertreeDecompositionAlgorithm.cpp
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

#ifndef HTD_HTD_HYPERTREEDECOMPOSITIONALGORITHM_CPP
#define	HTD_HTD_HYPERTREEDECOMPOSITIONALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>

#include <htd/HypertreeDecompositionAlgorithm.hpp>
#include <htd/TreeDecompositionAlgorithmFactory.hpp>
#include <htd/IMutableHypertreeDecomposition.hpp>
#include <htd/HypertreeDecompositionFactory.hpp>
#include <htd/SetCoverAlgorithmFactory.hpp>
#include <htd/PostOrderTreeTraversal.hpp>

#include <cstdarg>
#include <stdexcept>
#include <unordered_set>
#include <vector>

htd::HypertreeDecompositionAlgorithm::HypertreeDecompositionAlgorithm(void) : labelingFunctions_(), postProcessingOperations_()
{

}

htd::HypertreeDecompositionAlgorithm::HypertreeDecompositionAlgorithm(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) : labelingFunctions_(), postProcessingOperations_()
{
    setManipulationOperations(manipulationOperations);
}

htd::HypertreeDecompositionAlgorithm::~HypertreeDecompositionAlgorithm()
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

htd::IHypertreeDecomposition * htd::HypertreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph) const
{
    return computeDecomposition(graph, std::vector<htd::IDecompositionManipulationOperation *>());
}

htd::IHypertreeDecomposition * htd::HypertreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, int manipulationOperationCount, ...) const
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

htd::IHypertreeDecomposition * htd::HypertreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const
{
    htd::IMutableHypertreeDecomposition * ret = nullptr;

    htd::ITreeDecompositionAlgorithm * algorithm = htd::TreeDecompositionAlgorithmFactory::instance().getTreeDecompositionAlgorithm();

    HTD_ASSERT(algorithm != nullptr)

    htd::ITreeDecomposition * treeDecomposition = algorithm->computeDecomposition(graph);

    delete algorithm;

    ret = htd::HypertreeDecompositionFactory::instance().getHypertreeDecomposition(*treeDecomposition);

    HTD_ASSERT(ret != nullptr)

    setCoveringEdges(graph, *ret);

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

    for (auto & labelingFunction : labelingFunctions)
    {
        delete labelingFunction;
    }

    for (auto & postProcessingOperation : postProcessingOperations)
    {
        delete postProcessingOperation;
    }

    delete treeDecomposition;

    return ret;
}

void htd::HypertreeDecompositionAlgorithm::setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
{
    labelingFunctions_.clear();

    postProcessingOperations_.clear();

    addManipulationOperations(manipulationOperations);
}

void htd::HypertreeDecompositionAlgorithm::addManipulationOperation(htd::IDecompositionManipulationOperation * manipulationOperation)
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

void htd::HypertreeDecompositionAlgorithm::addManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
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

htd::HypertreeDecompositionAlgorithm * htd::HypertreeDecompositionAlgorithm::clone(void) const
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

    return new htd::HypertreeDecompositionAlgorithm(manipulationOperations);
}

void htd::HypertreeDecompositionAlgorithm::setCoveringEdges(const htd::IMultiHypergraph & graph, htd::IMutableHypertreeDecomposition & decomposition) const
{
    std::vector<htd::Hyperedge> relevantHyperedges;

    std::vector<htd::Hyperedge> newRelevantHyperedges;

    std::vector<std::vector<htd::id_t>> relevantContainers;

    std::vector<std::vector<htd::id_t>> newRelevantContainers;

    const htd::ConstCollection<htd::Hyperedge> & hyperedges = graph.hyperedges();

    std::size_t edgeCount = graph.edgeCount();

    auto it1 = hyperedges.begin();

    for (htd::index_t index1 = 0; index1 < edgeCount; ++index1)
    {
        const std::vector<htd::vertex_t> & elements1 = it1->sortedElements();

        bool maximal = true;

        auto it2 = it1;

        ++it2;

        for (htd::index_t index2 = index1 + 1; index2 < edgeCount; ++index2)
        {
            const std::vector<htd::vertex_t> & elements2 = it2->sortedElements();

            if (std::includes(elements2.begin(), elements2.end(), elements1.begin(), elements1.end()))
            {
                maximal = false;
            }

            ++it2;
        }

        if (maximal)
        {
            relevantHyperedges.push_back(*it1);

            relevantContainers.push_back(elements1);
        }

        ++it1;
    }

    htd::ISetCoverAlgorithm * setCoverAlgorithm = htd::SetCoverAlgorithmFactory::instance().getSetCoverAlgorithm();

    htd::PostOrderTreeTraversal traversal;

    traversal.traverse(decomposition, [&](htd::vertex_t vertex, htd::vertex_t parent, std::size_t depth)
    {
        HTD_UNUSED(depth)

        std::vector<htd::index_t> selectedIndices;

        setCoverAlgorithm->computeSetCover(decomposition.bagContent(vertex), relevantContainers, selectedIndices);

        std::vector<htd::Hyperedge> selectedHyperedges;

        for (htd::index_t selectedHyperedgeIndex : selectedIndices)
        {
            selectedHyperedges.push_back(relevantHyperedges.at(selectedHyperedgeIndex));
        }

        decomposition.setCoveringEdges(vertex, selectedHyperedges);

        if (parent != htd::Vertex::UNKNOWN)
        {
            std::vector<htd::vertex_t> forgottenVertices;

            decomposition.copyForgottenVerticesTo(forgottenVertices, parent, vertex);

            if (forgottenVertices.size() > 0)
            {
                htd::index_t index = 0;

                for (std::vector<htd::id_t> & container : relevantContainers)
                {
                    if (!htd::has_non_empty_set_intersection(container.begin(), container.end(), forgottenVertices.begin(), forgottenVertices.end()))
                    {
                        newRelevantContainers.push_back(std::move(container));
                        newRelevantHyperedges.push_back(std::move(relevantHyperedges.at(index)));
                    }

                    ++index;
                }

                relevantContainers.swap(newRelevantContainers);
                relevantHyperedges.swap(newRelevantHyperedges);

                newRelevantContainers.clear();
                newRelevantHyperedges.clear();
            }
        }
    });

    delete setCoverAlgorithm;
}

#endif /* HTD_HTD_HYPERTREEDECOMPOSITIONALGORITHM_CPP */
