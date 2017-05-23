/* 
 * File:   HypertreeDecompositionAlgorithm.cpp
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

#ifndef HTD_HTD_HYPERTREEDECOMPOSITIONALGORITHM_CPP
#define HTD_HTD_HYPERTREEDECOMPOSITIONALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>

#include <htd/HypertreeDecompositionAlgorithm.hpp>
#include <htd/TreeDecompositionAlgorithmFactory.hpp>
#include <htd/IMutableHypertreeDecomposition.hpp>
#include <htd/HypertreeDecompositionFactory.hpp>
#include <htd/SetCoverAlgorithmFactory.hpp>
#include <htd/PostOrderTreeTraversal.hpp>
#include <htd/GraphPreprocessorFactory.hpp>
#include <htd/IGraphPreprocessor.hpp>

#include <cstdarg>
#include <stdexcept>
#include <unordered_set>
#include <vector>

/**
 *  Private implementation details of class htd::HypertreeDecompositionAlgorithm.
 */
struct htd::HypertreeDecompositionAlgorithm::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager   The management instance to which the current object instance belongs.
     */
    Implementation(const htd::LibraryInstance * const manager) : managementInstance_(manager), labelingFunctions_(), postProcessingOperations_(), computeInducedEdges_(true)
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
    std::vector<htd::ITreeDecompositionManipulationOperation *> postProcessingOperations_;

    /**
     *  A boolean flag indicating whether the hyperedges induced by a respective bag shall be computed.
     */
    bool computeInducedEdges_;

    /**
     *  Set the hyperedges covering the bags of the hypertree decomposition.
     *
     *  @param[in] graph            The graph which was decomposed.
     *  @param[in] decomposition    The hypertree decomposition which shall be updated.
     */
    void setCoveringEdges(const htd::IMultiHypergraph & graph, htd::IMutableHypertreeDecomposition & decomposition) const;
};

htd::HypertreeDecompositionAlgorithm::HypertreeDecompositionAlgorithm(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{

}

htd::HypertreeDecompositionAlgorithm::HypertreeDecompositionAlgorithm(const htd::LibraryInstance * const manager, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) : implementation_(new Implementation(manager))
{
    setManipulationOperations(manipulationOperations);
}

htd::HypertreeDecompositionAlgorithm::~HypertreeDecompositionAlgorithm()
{

}

htd::IHypertreeDecomposition * htd::HypertreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph) const
{
    return computeDecomposition(graph, std::vector<htd::IDecompositionManipulationOperation *>());
}

htd::IHypertreeDecomposition * htd::HypertreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const
{
    htd::IGraphPreprocessor * preprocessor = implementation_->managementInstance_->graphPreprocessorFactory().createInstance();

    htd::IPreprocessedGraph * preprocessedGraph = preprocessor->prepare(graph);

    htd::IHypertreeDecomposition * ret = computeDecomposition(graph, *preprocessedGraph, manipulationOperations);

    delete preprocessedGraph;

    return ret;
}

htd::IHypertreeDecomposition * htd::HypertreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph) const
{
    return computeDecomposition(graph, preprocessedGraph, std::vector<htd::IDecompositionManipulationOperation *>());
}

htd::IHypertreeDecomposition * htd::HypertreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const
{
    htd::IMutableHypertreeDecomposition * ret = nullptr;

    htd::ITreeDecompositionAlgorithm * algorithm = managementInstance()->treeDecompositionAlgorithmFactory().createInstance();

    HTD_ASSERT(algorithm != nullptr)

    algorithm->setComputeInducedEdgesEnabled(implementation_->computeInducedEdges_);

    htd::ITreeDecomposition * treeDecomposition = algorithm->computeDecomposition(graph, preprocessedGraph);

    delete algorithm;

    ret = managementInstance()->hypertreeDecompositionFactory().createInstance(*treeDecomposition);

    HTD_ASSERT(ret != nullptr)

    implementation_->setCoveringEdges(graph, *ret);

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

htd::IHypertreeDecomposition * htd::HypertreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph, int manipulationOperationCount, ...) const
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

void htd::HypertreeDecompositionAlgorithm::setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
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

void htd::HypertreeDecompositionAlgorithm::addManipulationOperation(htd::IDecompositionManipulationOperation * manipulationOperation)
{
    bool assigned = false;

    htd::ILabelingFunction * labelingFunction = dynamic_cast<htd::ILabelingFunction *>(manipulationOperation);

    if (labelingFunction != nullptr)
    {
        implementation_->labelingFunctions_.emplace_back(labelingFunction);

        assigned = true;
    }

    htd::ITreeDecompositionManipulationOperation * newManipulationOperation = dynamic_cast<htd::ITreeDecompositionManipulationOperation *>(manipulationOperation);

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

void htd::HypertreeDecompositionAlgorithm::addManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
{
    for (htd::IDecompositionManipulationOperation * operation : manipulationOperations)
    {
        addManipulationOperation(operation);
    }
}

bool htd::HypertreeDecompositionAlgorithm::isSafelyInterruptible(void) const
{
    return false;
}

bool htd::HypertreeDecompositionAlgorithm::isComputeInducedEdgesEnabled(void) const
{
    return implementation_->computeInducedEdges_;
}

void htd::HypertreeDecompositionAlgorithm::setComputeInducedEdgesEnabled(bool computeInducedEdgesEnabled)
{
    implementation_->computeInducedEdges_ = computeInducedEdgesEnabled;
}

const htd::LibraryInstance * htd::HypertreeDecompositionAlgorithm::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::HypertreeDecompositionAlgorithm::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::HypertreeDecompositionAlgorithm * htd::HypertreeDecompositionAlgorithm::clone(void) const
{
    htd::HypertreeDecompositionAlgorithm * ret = new htd::HypertreeDecompositionAlgorithm(managementInstance());

    for (htd::ILabelingFunction * labelingFunction : implementation_->labelingFunctions_)
    {
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        ret->addManipulationOperation(labelingFunction->clone());
#else
        ret->addManipulationOperation(labelingFunction->cloneLabelingFunction());
#endif
    }

    for (htd::ITreeDecompositionManipulationOperation * postProcessingOperation : implementation_->postProcessingOperations_)
    {
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        ret->addManipulationOperation(postProcessingOperation->clone());
#else
        ret->addManipulationOperation(postProcessingOperation->cloneTreeDecompositionManipulationOperation());
#endif
    }

    ret->setManagementInstance(managementInstance());

    return ret;
}

void htd::HypertreeDecompositionAlgorithm::Implementation::setCoveringEdges(const htd::IMultiHypergraph & graph, htd::IMutableHypertreeDecomposition & decomposition) const
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

    htd::ISetCoverAlgorithm * setCoverAlgorithm = managementInstance_->setCoverAlgorithmFactory().createInstance();

    htd::PostOrderTreeTraversal traversal;

    std::vector<htd::vertex_t> forgottenVertices;

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
            std::size_t forgottenVertexCount = forgottenVertices.size();

            decomposition.copyForgottenVerticesTo(parent, forgottenVertices, vertex);

            std::inplace_merge(forgottenVertices.begin(), forgottenVertices.begin() + forgottenVertexCount, forgottenVertices.end());

            if (forgottenVertices.size() > 0)
            {
                htd::index_t index = 0;

                for (std::vector<htd::id_t> & container : relevantContainers)
                {
                    if (!std::includes(forgottenVertices.begin(), forgottenVertices.end(), container.begin(), container.end()))
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
