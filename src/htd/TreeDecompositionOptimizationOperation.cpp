/*
 * File:   TreeDecompositionOptimizationOperation.cpp
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

#ifndef HTD_HTD_TREEDECOMPOSITIONOPTIMIZATIONOPERATION_CPP
#define HTD_HTD_TREEDECOMPOSITIONOPTIMIZATIONOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/TreeDecompositionOptimizationOperation.hpp>
#include <htd/ExhaustiveVertexSelectionStrategy.hpp>
#include <htd/CompressionOperation.hpp>

#include <algorithm>
#include <stack>
#include <unordered_set>

/**
 *  Private implementation details of class htd::TreeDecompositionOptimizationOperation.
 */
struct htd::TreeDecompositionOptimizationOperation::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager  The management instance to which the current object instance belongs.
     */
    Implementation(const htd::LibraryInstance * const manager)
        : managementInstance_(manager), enforceNaiveOptimization_(false), strategy_(nullptr), fitnessFunction_(nullptr), manipulationOperations_()
    {

    }

    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager                  The management instance to which the current object instance belongs.
     *  @param[in] fitnessFunction          The fitness function which is used to determine the quality of tree decompositions.
     *  @param[in] enforceNaiveOptimization A boolean flag to enforce that each iteration of the optimization algorithm starts from scratch with a copy of the given decomposition.
     */
    Implementation(const htd::LibraryInstance * const manager, htd::ITreeDecompositionFitnessFunction * fitnessFunction, bool enforceNaiveOptimization)
        : managementInstance_(manager), enforceNaiveOptimization_(enforceNaiveOptimization), strategy_(new htd::ExhaustiveVertexSelectionStrategy()), fitnessFunction_(fitnessFunction), manipulationOperations_()
    {

    }

    virtual ~Implementation()
    {
        if (strategy_ != nullptr)
        {
            delete strategy_;
        }

        if (fitnessFunction_ != nullptr)
        {
            delete fitnessFunction_;
        }

        for (htd::ITreeDecompositionManipulationOperation * operation : manipulationOperations_)
        {
            delete operation;
        }
    }

    /**
     *  The management instance to which the current object instance belongs.
     */
    const htd::LibraryInstance * managementInstance_;

    /**
     *  A boolean flag to enforce that each iteration of the optimization
     *  algorithm starts from scratch with a copy of the given decomposition.
     */
    bool enforceNaiveOptimization_;

    /**
     *  The strategy defining which vertices shall be considered as root of the tree decomposition.
     */
    htd::IVertexSelectionStrategy * strategy_;

    /**
     *  The fitness function which is used to determine the quality of tree decompositions.
     */
    htd::ITreeDecompositionFitnessFunction * fitnessFunction_;

    /**
     *  The manipuation operations which are applied after the decomposition was computed.
     */
    std::vector<htd::ITreeDecompositionManipulationOperation *> manipulationOperations_;

    /**
     *  Check whether a manipulation operation does not involve any operations which make it impossible
     *  to undo the operation for the path between the new and the old root by just deleting the added
     *  vertices adjacent to the path between the new and the old root.
     *
     *  @param[in] manipulationOperation    The manipulation operation which shall be checked.
     *
     *  @return True if the operation allows for efficient undoing, false otherwise.
     */
    bool isSafeOperation(const htd::ITreeDecompositionManipulationOperation & manipulationOperation) const;

    /**
     *  Select the optimal root of the given decomposition when no manipulation operations are involved.
     *
     *  @param[in] graph            The graph which was decomposed.
     *  @param[in] decomposition    The tree decomposition which shall be optimized.
     */
    void quickOptimization(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition) const;

    /**
     *  Select the optimal root of the given decomposition when complex manipulation operations are involved.
     *
     *  @param[in] graph                The graph which was decomposed.
     *  @param[in] decomposition        The tree decomposition which shall be optimized.
     *  @param[in] labelingFunctions    A vector of labeling functions which shall be applied after the modifications.
     */
    void naiveOptimization(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const;

    /**
     *  Select the optimal root of the given decomposition when no complex manipulation operations are involved.
     *
     *  @param[in] graph                The graph which was decomposed.
     *  @param[in] decomposition        The tree decomposition which shall be optimized.
     *  @param[in] labelingFunctions    A vector of labeling functions which shall be applied after the modifications.
     */
    void intelligentOptimization(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const;

    /**
     *  Remove all vertices which were created by manipulation operations and which are reachable via a given vertex by only visiting created nodes.
     *
     *  @param[in] decomposition        The tree decomposition which shall be cleaned.
     *  @param[in] start                The vertex from which the removal process shall begin.
     *  @param[in] lastRegularVertex    The identifier of the last regular vertex which shall remain in the decomposition. All vertices
     *                                  with higher ID are subject to removal when they are reachable from the starting vertex by only
     *                                  visiting created nodes.
     */
    void removeCreatedNodes(htd::IMutableTreeDecomposition & decomposition, htd::vertex_t start, htd::vertex_t lastRegularVertex) const;
};

htd::TreeDecompositionOptimizationOperation::TreeDecompositionOptimizationOperation(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{

}

htd::TreeDecompositionOptimizationOperation::TreeDecompositionOptimizationOperation(const htd::LibraryInstance * const manager, htd::ITreeDecompositionFitnessFunction * fitnessFunction, bool enforceNaiveOptimization) : implementation_(new Implementation(manager, fitnessFunction, enforceNaiveOptimization))
{

}

htd::TreeDecompositionOptimizationOperation::~TreeDecompositionOptimizationOperation()
{

}

void htd::TreeDecompositionOptimizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition) const
{
    apply(graph, decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::TreeDecompositionOptimizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    apply(graph, decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>(), createdVertices, removedVertices);
}

void htd::TreeDecompositionOptimizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    if (decomposition.vertexCount() > 0)
    {
        htd::CompressionOperation compressionOperation(managementInstance());

        compressionOperation.apply(graph, decomposition);

        for (const htd::ILabelingFunction * labelingFunction : labelingFunctions)
        {
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            htd::ILabelingFunction * clone = labelingFunction->clone();
#else
            htd::ILabelingFunction * clone = labelingFunction->cloneLabelingFunction();
#endif

            clone->setManagementInstance(managementInstance());

            for (htd::vertex_t vertex : decomposition.vertices())
            {
                htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(vertex);

                htd::ILabel * newLabel = clone->computeLabel(decomposition.bagContent(vertex), *labelCollection);

                delete labelCollection;

                decomposition.setVertexLabel(clone->name(), vertex, newLabel);
            }
        }

        if (implementation_->fitnessFunction_ != nullptr)
        {
            if (implementation_->manipulationOperations_.empty())
            {
                implementation_->quickOptimization(graph, decomposition);
            }
            else
            {
                bool isSafe = !implementation_->enforceNaiveOptimization_;

                for (auto it = implementation_->manipulationOperations_.begin(); isSafe && it != implementation_->manipulationOperations_.end(); ++it)
                {
                    isSafe = implementation_->isSafeOperation(*(*it));
                }

                if (isSafe)
                {
                    implementation_->intelligentOptimization(graph, decomposition, labelingFunctions);
                }
                else
                {
                    implementation_->naiveOptimization(graph, decomposition, labelingFunctions);
                }
            }
        }
        else
        {
            for (const htd::ITreeDecompositionManipulationOperation * operation : implementation_->manipulationOperations_)
            {
                operation->apply(graph, decomposition, labelingFunctions);
            }
        }
    }
}

void htd::TreeDecompositionOptimizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    HTD_UNUSED(relevantVertices)
    HTD_UNUSED(createdVertices)
    HTD_UNUSED(removedVertices)

    apply(graph, decomposition, labelingFunctions);
}

bool htd::TreeDecompositionOptimizationOperation::isLocalOperation(void) const
{
    return false;
}

bool htd::TreeDecompositionOptimizationOperation::createsTreeNodes(void) const
{
    bool ret = false;

    for (auto it = implementation_->manipulationOperations_.begin(); !ret && it != implementation_->manipulationOperations_.end(); ++it)
    {
        ret = (*it)->createsTreeNodes();
    }

    return ret;
}

bool htd::TreeDecompositionOptimizationOperation::removesTreeNodes(void) const
{
    bool ret = false;

    for (auto it = implementation_->manipulationOperations_.begin(); !ret && it != implementation_->manipulationOperations_.end(); ++it)
    {
        ret = (*it)->removesTreeNodes();
    }

    return ret;
}

bool htd::TreeDecompositionOptimizationOperation::modifiesBagContents(void) const
{
    bool ret = false;

    for (auto it = implementation_->manipulationOperations_.begin(); !ret && it != implementation_->manipulationOperations_.end(); ++it)
    {
        ret = (*it)->modifiesBagContents();
    }

    return ret;
}

bool htd::TreeDecompositionOptimizationOperation::createsSubsetMaximalBags(void) const
{
    bool ret = false;

    for (auto it = implementation_->manipulationOperations_.begin(); !ret && it != implementation_->manipulationOperations_.end(); ++it)
    {
        ret = (*it)->createsSubsetMaximalBags();
    }

    return ret;
}

bool htd::TreeDecompositionOptimizationOperation::createsLocationDependendLabels(void) const
{
    bool ret = false;

    for (auto it = implementation_->manipulationOperations_.begin(); !ret && it != implementation_->manipulationOperations_.end(); ++it)
    {
        ret = (*it)->createsLocationDependendLabels();
    }

    return ret;
}

void htd::TreeDecompositionOptimizationOperation::setManipulationOperations(const std::vector<htd::ITreeDecompositionManipulationOperation *> & manipulationOperations)
{
    for (htd::ITreeDecompositionManipulationOperation * operation : implementation_->manipulationOperations_)
    {
        delete operation;
    }

    implementation_->manipulationOperations_.clear();

    std::copy(manipulationOperations.begin(), manipulationOperations.end(), std::back_inserter(implementation_->manipulationOperations_));
}

void htd::TreeDecompositionOptimizationOperation::addManipulationOperation(htd::ITreeDecompositionManipulationOperation * manipulationOperation)
{
    HTD_ASSERT(manipulationOperation != nullptr)

    implementation_->manipulationOperations_.emplace_back(manipulationOperation);
}

void htd::TreeDecompositionOptimizationOperation::addManipulationOperations(const std::vector<htd::ITreeDecompositionManipulationOperation *> & manipulationOperations)
{
    std::copy(manipulationOperations.begin(), manipulationOperations.end(), std::back_inserter(implementation_->manipulationOperations_));
}

void htd::TreeDecompositionOptimizationOperation::setVertexSelectionStrategy(htd::IVertexSelectionStrategy * strategy)
{
    HTD_ASSERT(strategy != nullptr)

    if (implementation_->strategy_ != nullptr)
    {
        delete implementation_->strategy_;
    }

    implementation_->strategy_ = strategy;
}

void htd::TreeDecompositionOptimizationOperation::Implementation::quickOptimization(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition) const
{
    const htd::ITreeDecompositionFitnessFunction & fitnessFunction = *fitnessFunction_;

    htd::vertex_t initialRoot = decomposition.root();

    htd::vertex_t optimalRoot = initialRoot;

    std::vector<htd::vertex_t> candidates;

    strategy_->selectVertices(decomposition, candidates);

    htd::FitnessEvaluation * optimalFitness = fitnessFunction.fitness(graph, decomposition);

    HTD_ASSERT(optimalFitness != nullptr)

    for (auto it = candidates.begin(); it != candidates.end() && !managementInstance_->isTerminated(); ++it)
    {
        htd::vertex_t vertex = *it;

        if (vertex != initialRoot)
        {
            decomposition.makeRoot(vertex);
        }

        htd::FitnessEvaluation * currentFitness = fitnessFunction.fitness(graph, decomposition);

        HTD_ASSERT(currentFitness != nullptr)

        if (*currentFitness > *optimalFitness)
        {
            delete optimalFitness;

            optimalFitness = currentFitness;

            optimalRoot = vertex;
        }
        else
        {
            delete currentFitness;
        }
    }

    decomposition.makeRoot(optimalRoot);

    delete optimalFitness;
}

void htd::TreeDecompositionOptimizationOperation::Implementation::naiveOptimization(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    const htd::ITreeDecompositionFitnessFunction & fitnessFunction = *fitnessFunction_;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableTreeDecomposition * localDecomposition = decomposition.clone();
#else
    htd::IMutableTreeDecomposition * localDecomposition = decomposition.cloneMutableTreeDecomposition();
#endif

    htd::vertex_t initialRoot = localDecomposition->root();

    std::vector<htd::vertex_t> candidates;

    strategy_->selectVertices(decomposition, candidates);

    std::vector<htd::ITreeDecompositionManipulationOperation *> clonedManipulationOperations;

    for (const htd::ITreeDecompositionManipulationOperation * operation : manipulationOperations_)
    {
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        htd::ITreeDecompositionManipulationOperation * clone = operation->clone();
#else
        htd::ITreeDecompositionManipulationOperation * clone = operation->cloneTreeDecompositionManipulationOperation();
#endif

        clone->setManagementInstance(managementInstance_);

        clonedManipulationOperations.push_back(clone);

        clone->apply(graph, *localDecomposition, labelingFunctions);
    }

    htd::vertex_t optimalRoot = initialRoot;

    htd::FitnessEvaluation * optimalFitness = fitnessFunction.fitness(graph, *localDecomposition);

    HTD_ASSERT(optimalFitness != nullptr)

    for (auto it = candidates.begin(); it != candidates.end() && !managementInstance_->isTerminated(); ++it)
    {
        htd::vertex_t vertex = *it;

        if (vertex != initialRoot)
        {
            delete localDecomposition;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            localDecomposition = decomposition.clone();
#else
            localDecomposition = decomposition.cloneMutableTreeDecomposition();
#endif

            localDecomposition->makeRoot(vertex);

            for (const htd::ITreeDecompositionManipulationOperation * operation : clonedManipulationOperations)
            {
                operation->apply(graph, *localDecomposition, labelingFunctions);
            }

            htd::FitnessEvaluation * currentFitness = fitnessFunction.fitness(graph, *localDecomposition);

            HTD_ASSERT(currentFitness != nullptr)

            if (*currentFitness > *optimalFitness)
            {
                delete optimalFitness;

                optimalFitness = currentFitness;

                optimalRoot = vertex;
            }
            else
            {
                delete currentFitness;
            }
        }
    }

    delete localDecomposition;

    decomposition.makeRoot(optimalRoot);

    for (const htd::ITreeDecompositionManipulationOperation * operation : clonedManipulationOperations)
    {
        operation->apply(graph, decomposition, labelingFunctions);

        delete operation;
    }

    delete optimalFitness;
}

void htd::TreeDecompositionOptimizationOperation::Implementation::intelligentOptimization(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    const htd::ITreeDecompositionFitnessFunction & fitnessFunction = *fitnessFunction_;

    htd::vertex_t initialRoot = decomposition.root();

    std::vector<htd::vertex_t> candidates;

    strategy_->selectVertices(decomposition, candidates);

    htd::vertex_t lastRegularVertex = decomposition.nextVertex() - 1;

    std::vector<htd::ITreeDecompositionManipulationOperation *> clonedManipulationOperations;

    for (const htd::ITreeDecompositionManipulationOperation * operation : manipulationOperations_)
    {
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        htd::ITreeDecompositionManipulationOperation * clone = operation->clone();
#else
        htd::ITreeDecompositionManipulationOperation * clone = operation->cloneTreeDecompositionManipulationOperation();
#endif

        clone->setManagementInstance(managementInstance_);

        clonedManipulationOperations.push_back(clone);

        clone->apply(graph, decomposition, labelingFunctions);
    }

    htd::vertex_t optimalRoot = initialRoot;

    htd::FitnessEvaluation * optimalFitness = fitnessFunction.fitness(graph, decomposition);

    HTD_ASSERT(optimalFitness != nullptr)

    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    for (auto it = candidates.begin(); it != candidates.end() && !managementInstance_->isTerminated(); ++it)
    {
        htd::vertex_t vertex = *it;

        if (vertex != initialRoot)
        {
            htd::vertex_t currentVertex = vertex;

            std::vector<htd::vertex_t> affectedVertices;

            while (!decomposition.isRoot(currentVertex))
            {
                htd::vertex_t nextVertex = decomposition.parent(currentVertex);

                if (currentVertex <= lastRegularVertex)
                {
                    affectedVertices.push_back(currentVertex);
                }

                currentVertex = nextVertex;
            }

            if (currentVertex <= lastRegularVertex)
            {
                affectedVertices.push_back(currentVertex);
            }

            for (htd::vertex_t affectedVertex : affectedVertices)
            {
                removeCreatedNodes(decomposition, affectedVertex, lastRegularVertex);
            }

            std::size_t newVertexCount = 0;

            std::size_t oldCreatedVerticesCount = createdVertices.size();

            decomposition.makeRoot(vertex);

            for (const htd::ITreeDecompositionManipulationOperation * operation : clonedManipulationOperations)
            {
                operation->apply(graph, decomposition, affectedVertices, labelingFunctions, createdVertices, removedVertices);

                newVertexCount = createdVertices.size() - oldCreatedVerticesCount;

                if (newVertexCount > 0)
                {
                    affectedVertices.insert(affectedVertices.end(), createdVertices.begin() + oldCreatedVerticesCount, createdVertices.end());

                    oldCreatedVerticesCount = createdVertices.size();
                }
            }

            htd::FitnessEvaluation * currentFitness = fitnessFunction.fitness(graph, decomposition);

            HTD_ASSERT(currentFitness != nullptr)

            if (*currentFitness > *optimalFitness)
            {
                delete optimalFitness;

                optimalFitness = currentFitness;

                optimalRoot = vertex;
            }
            else
            {
                delete currentFitness;
            }
        }
    }

    htd::vertex_t currentVertex = optimalRoot;

    std::vector<htd::vertex_t> affectedVertices;

    while (!decomposition.isRoot(currentVertex))
    {
        htd::vertex_t nextVertex = decomposition.parent(currentVertex);

        if (currentVertex <= lastRegularVertex)
        {
            affectedVertices.push_back(currentVertex);
        }

        currentVertex = nextVertex;
    }

    if (currentVertex <= lastRegularVertex)
    {
        affectedVertices.push_back(currentVertex);
    }

    for (htd::vertex_t affectedVertex : affectedVertices)
    {
        removeCreatedNodes(decomposition, affectedVertex, lastRegularVertex);
    }

    std::size_t newVertexCount = 0;

    std::size_t oldCreatedVerticesCount = createdVertices.size();

    decomposition.makeRoot(optimalRoot);

    for (const htd::ITreeDecompositionManipulationOperation * operation : clonedManipulationOperations)
    {
        operation->apply(graph, decomposition, affectedVertices, labelingFunctions, createdVertices, removedVertices);

        newVertexCount = createdVertices.size() - oldCreatedVerticesCount;

        if (newVertexCount > 0)
        {
            std::copy(createdVertices.begin() + oldCreatedVerticesCount, createdVertices.end(), std::back_inserter(affectedVertices));

            oldCreatedVerticesCount = createdVertices.size();
        }

        delete operation;
    }

    delete optimalFitness;
}

bool htd::TreeDecompositionOptimizationOperation::Implementation::isSafeOperation(const htd::ITreeDecompositionManipulationOperation & manipulationOperation) const
{
    return manipulationOperation.isLocalOperation() &&
           !manipulationOperation.removesTreeNodes() &&
           !manipulationOperation.modifiesBagContents() &&
           !manipulationOperation.createsSubsetMaximalBags() &&
           !manipulationOperation.createsLocationDependendLabels();
}

void htd::TreeDecompositionOptimizationOperation::Implementation::removeCreatedNodes(htd::IMutableTreeDecomposition & decomposition, htd::vertex_t start, htd::vertex_t lastRegularVertex) const
{
    std::stack<htd::vertex_t> originStack;

    htd::vertex_t current = start;

    std::vector<htd::vertex_t> removableVertices;

    std::unordered_set<htd::vertex_t> visitedVertices;

    if (current > lastRegularVertex)
    {
        removableVertices.push_back(current);
    }

    visitedVertices.insert(current);

    std::vector<htd::vertex_t> neighbors;

    decomposition.copyNeighborsTo(current, neighbors);

    for (htd::vertex_t neighbor : neighbors)
    {
        if (neighbor > lastRegularVertex)
        {
            originStack.push(neighbor);
        }
    }

    while (!originStack.empty())
    {
        current = originStack.top();

        originStack.pop();

        if (current > lastRegularVertex)
        {
            removableVertices.push_back(current);
        }

        visitedVertices.insert(current);

        neighbors.clear();

        decomposition.copyNeighborsTo(current, neighbors);

        for (htd::vertex_t neighbor : neighbors)
        {
            if (neighbor > lastRegularVertex && visitedVertices.count(neighbor) == 0)
            {
                originStack.push(neighbor);
            }
        }
    }

    std::sort(removableVertices.begin(), removableVertices.end(), std::greater<htd::vertex_t>());

    for (htd::vertex_t vertex : removableVertices)
    {
        decomposition.removeVertex(vertex);
    }
}

const htd::LibraryInstance * htd::TreeDecompositionOptimizationOperation::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::TreeDecompositionOptimizationOperation::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::TreeDecompositionOptimizationOperation * htd::TreeDecompositionOptimizationOperation::clone(void) const
{
    htd::TreeDecompositionOptimizationOperation * ret = nullptr;

    if (implementation_->fitnessFunction_ == nullptr)
    {
        ret = new htd::TreeDecompositionOptimizationOperation(managementInstance());
    }
    else
    {
        ret = new htd::TreeDecompositionOptimizationOperation(managementInstance(), implementation_->fitnessFunction_->clone());
    }

    for (const htd::ITreeDecompositionManipulationOperation * manipulationOperation : implementation_->manipulationOperations_)
    {
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        ret->addManipulationOperation(manipulationOperation->clone());
#else
        ret->addManipulationOperation(manipulationOperation->cloneTreeDecompositionManipulationOperation());
#endif
    }

    return ret;
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IDecompositionManipulationOperation * htd::TreeDecompositionOptimizationOperation::cloneDecompositionManipulationOperation(void) const
{
    return clone();
}

htd::ITreeDecompositionManipulationOperation * htd::TreeDecompositionOptimizationOperation::cloneTreeDecompositionManipulationOperation(void) const
{
    return clone();
}
#endif

#endif /* HTD_HTD_TREEDECOMPOSITIONOPTIMIZATIONOPERATION_CPP */
