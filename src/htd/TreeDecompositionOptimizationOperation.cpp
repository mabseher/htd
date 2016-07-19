/*
 * File:   TreeDecompositionOptimizationOperation.cpp
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

#ifndef HTD_HTD_TREEDECOMPOSITIONOPTIMIZATIONOPERATION_CPP
#define	HTD_HTD_TREEDECOMPOSITIONOPTIMIZATIONOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/TreeDecompositionOptimizationOperation.hpp>
#include <htd/ExhaustiveVertexSelectionStrategy.hpp>
#include <htd/CompressionOperation.hpp>

#include <algorithm>
#include <stack>
#include <unordered_set>

htd::TreeDecompositionOptimizationOperation::TreeDecompositionOptimizationOperation(void) : htd::LibraryObject(), enforceNaiveOptimization_(false), strategy_(), fitnessFunction_(), manipulationOperations_()
{

}

htd::TreeDecompositionOptimizationOperation::TreeDecompositionOptimizationOperation(const htd::ITreeDecompositionFitnessFunction & fitnessFunction) : htd::LibraryObject(), enforceNaiveOptimization_(false), strategy_(new htd::ExhaustiveVertexSelectionStrategy()), fitnessFunction_(fitnessFunction.clone()), manipulationOperations_()
{

}

htd::TreeDecompositionOptimizationOperation::TreeDecompositionOptimizationOperation(const htd::ITreeDecompositionFitnessFunction & fitnessFunction, bool enforceNaiveOptimization) : htd::LibraryObject(), enforceNaiveOptimization_(enforceNaiveOptimization), strategy_(new htd::ExhaustiveVertexSelectionStrategy()), fitnessFunction_(fitnessFunction.clone()), manipulationOperations_()
{

}

htd::TreeDecompositionOptimizationOperation::~TreeDecompositionOptimizationOperation()
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

void htd::TreeDecompositionOptimizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition) const
{
    apply(graph, decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::TreeDecompositionOptimizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    apply(graph, decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>(), createdVertices, removedVertices);
}

//TODO Remove!
//#define VERBOSE

//TODO Remove!
#include <htd/PreOrderTreeTraversal.hpp>

//TODO Remove!
void debug(const htd::ITreeDecomposition & decomposition)
{
    htd::PreOrderTreeTraversal traversal;

    traversal.traverse(decomposition, [&](htd::vertex_t vertex, htd::vertex_t parent, std::size_t distanceToRoot)
    {
        HTD_UNUSED(parent)

        for (htd::index_t index = 0; index < distanceToRoot; ++index)
        {
            std::cout << "   ";
        }

        std::cout << "NODE " << vertex << ": " << decomposition.bagContent(vertex) << std::endl;
    });

    std::cout << std::endl;
}

void htd::TreeDecompositionOptimizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    if (decomposition.vertexCount() > 0)
    {
        htd::CompressionOperation compressionOperation;

        compressionOperation.setManagementInstance(managementInstance());

        compressionOperation.apply(graph, decomposition);

        for (const htd::ILabelingFunction * labelingFunction : labelingFunctions)
        {
            htd::ILabelingFunction * clone = labelingFunction->clone();

            clone->setManagementInstance(managementInstance());

            for (htd::vertex_t vertex : decomposition.vertices())
            {
                htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(vertex);

                htd::ILabel * newLabel = clone->computeLabel(decomposition.bagContent(vertex), *labelCollection);

                delete labelCollection;

                decomposition.setVertexLabel(clone->name(), vertex, newLabel);
            }
        }

        if (fitnessFunction_ != nullptr)
        {
            if (manipulationOperations_.empty())
            {
                quickOptimization(graph, decomposition);
            }
            else
            {
                bool isSafe = !enforceNaiveOptimization_;

                for (auto it = manipulationOperations_.begin(); isSafe && it != manipulationOperations_.end(); ++it)
                {
                    isSafe = isSafeOperation(*(*it));
                }

                if (isSafe)
                {
                    intelligentOptimization(graph, decomposition, labelingFunctions);
                }
                else
                {
                    naiveOptimization(graph, decomposition, labelingFunctions);
                }
            }
        }
        else
        {
            for (const htd::ITreeDecompositionManipulationOperation * operation : manipulationOperations_)
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

    for (auto it = manipulationOperations_.begin(); !ret && it != manipulationOperations_.end(); ++it)
    {
        ret = (*it)->createsTreeNodes();
    }

    return ret;
}

bool htd::TreeDecompositionOptimizationOperation::removesTreeNodes(void) const
{
    bool ret = false;

    for (auto it = manipulationOperations_.begin(); !ret && it != manipulationOperations_.end(); ++it)
    {
        ret = (*it)->removesTreeNodes();
    }

    return ret;
}

bool htd::TreeDecompositionOptimizationOperation::modifiesBagContents(void) const
{
    bool ret = false;

    for (auto it = manipulationOperations_.begin(); !ret && it != manipulationOperations_.end(); ++it)
    {
        ret = (*it)->modifiesBagContents();
    }

    return ret;
}

bool htd::TreeDecompositionOptimizationOperation::createsSubsetMaximalBags(void) const
{
    bool ret = false;

    for (auto it = manipulationOperations_.begin(); !ret && it != manipulationOperations_.end(); ++it)
    {
        ret = (*it)->createsSubsetMaximalBags();
    }

    return ret;
}

bool htd::TreeDecompositionOptimizationOperation::createsLocationDependendLabels(void) const
{
    bool ret = false;

    for (auto it = manipulationOperations_.begin(); !ret && it != manipulationOperations_.end(); ++it)
    {
        ret = (*it)->createsLocationDependendLabels();
    }

    return ret;
}

void htd::TreeDecompositionOptimizationOperation::setManipulationOperations(const std::vector<htd::ITreeDecompositionManipulationOperation *> & manipulationOperations)
{
    manipulationOperations_.clear();

    std::copy(manipulationOperations.begin(), manipulationOperations.end(), std::back_inserter(manipulationOperations_));
}

void htd::TreeDecompositionOptimizationOperation::addManipulationOperation(htd::ITreeDecompositionManipulationOperation * manipulationOperation)
{
    manipulationOperations_.push_back(manipulationOperation);
}

void htd::TreeDecompositionOptimizationOperation::addManipulationOperations(const std::vector<htd::ITreeDecompositionManipulationOperation *> & manipulationOperations)
{
    std::copy(manipulationOperations.begin(), manipulationOperations.end(), std::back_inserter(manipulationOperations_));
}

void htd::TreeDecompositionOptimizationOperation::setVertexSelectionStrategy(htd::IVertexSelectionStrategy * strategy)
{
    HTD_ASSERT(strategy != nullptr)

    if (strategy_ != nullptr)
    {
        delete strategy_;
    }

    strategy_ = strategy;
}

void htd::TreeDecompositionOptimizationOperation::quickOptimization(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition) const
{
    const htd::ITreeDecompositionFitnessFunction & fitnessFunction = *fitnessFunction_;

    htd::vertex_t initialRoot = decomposition.root();

    htd::vertex_t optimalRoot = initialRoot;

    std::vector<htd::vertex_t> candidates;

    strategy_->selectVertices(decomposition, candidates);

    htd::FitnessEvaluation * optimalFitness = fitnessFunction.fitness(graph, decomposition);

    HTD_ASSERT(optimalFitness != nullptr)

    for (auto it = candidates.begin(); it != candidates.end() && !isTerminated(); ++it)
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

void htd::TreeDecompositionOptimizationOperation::naiveOptimization(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    const htd::ITreeDecompositionFitnessFunction & fitnessFunction = *fitnessFunction_;

    htd::IMutableTreeDecomposition * localDecomposition = decomposition.clone();

    htd::vertex_t initialRoot = localDecomposition->root();

    std::vector<htd::vertex_t> candidates;

    strategy_->selectVertices(decomposition, candidates);

    std::vector<htd::ITreeDecompositionManipulationOperation *> clonedManipulationOperations;

    for (const htd::ITreeDecompositionManipulationOperation * operation : manipulationOperations_)
    {
        htd::ITreeDecompositionManipulationOperation * clone = operation->clone();

        clone->setManagementInstance(managementInstance());

        clonedManipulationOperations.push_back(clone);

        clone->apply(graph, *localDecomposition, labelingFunctions);
    }

    htd::vertex_t optimalRoot = initialRoot;

    htd::FitnessEvaluation * optimalFitness = fitnessFunction.fitness(graph, *localDecomposition);

    HTD_ASSERT(optimalFitness != nullptr)

#ifdef VERBOSE
    //TODO
    debug(*localDecomposition);

    std::cout << "INITIAL FITNESS:     " << optimalFitness << "   (ROOT: " << optimalRoot << ")" << std::endl << std::endl << std::endl << std::endl;
#endif

    for (auto it = candidates.begin(); it != candidates.end() && !isTerminated(); ++it)
    {
        htd::vertex_t vertex = *it;

        if (vertex != initialRoot)
        {
            delete localDecomposition;

            localDecomposition = decomposition.clone();

            localDecomposition->makeRoot(vertex);

            for (const htd::ITreeDecompositionManipulationOperation * operation : clonedManipulationOperations)
            {
                operation->apply(graph, *localDecomposition, labelingFunctions);
            }

            htd::FitnessEvaluation * currentFitness = fitnessFunction.fitness(graph, *localDecomposition);

            HTD_ASSERT(currentFitness != nullptr)

#ifdef VERBOSE
            //TODO
            debug(*localDecomposition);

            std::cout << "CURRENT FITNESS:     " << currentFitness << "   (ROOT: " << vertex << ")" << std::endl;
#endif

            if (*currentFitness > *optimalFitness)
            {
                delete optimalFitness;

                optimalFitness = currentFitness;

                optimalRoot = vertex;

#ifdef VERBOSE
                std::cout << "NEW OPTIMAL FITNESS: " << optimalFitness << "   (ROOT: " << optimalRoot << ")" << std::endl;
#endif
            }
            else
            {
                delete currentFitness;
            }

#ifdef VERBOSE
            std::cout << std::endl << std::endl << std::endl;
#endif
        }
    }

    delete localDecomposition;

    decomposition.makeRoot(optimalRoot);

    for (const htd::ITreeDecompositionManipulationOperation * operation : clonedManipulationOperations)
    {
        operation->apply(graph, decomposition, labelingFunctions);

        delete operation;
    }

#ifdef VERBOSE
    //TODO
    debug(decomposition);

    std::cout << "OPTIMAL FITNESS:     " << optimalFitness << "   (ROOT: " << optimalRoot << ")" << std::endl << std::endl << std::endl << std::endl;
#endif

    delete optimalFitness;
}

void htd::TreeDecompositionOptimizationOperation::intelligentOptimization(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    const htd::ITreeDecompositionFitnessFunction & fitnessFunction = *fitnessFunction_;

    htd::vertex_t initialRoot = decomposition.root();

    std::vector<htd::vertex_t> candidates;

    strategy_->selectVertices(decomposition, candidates);

    htd::vertex_t lastRegularVertex = decomposition.nextVertex() - 1;

    std::vector<htd::ITreeDecompositionManipulationOperation *> clonedManipulationOperations;

    for (const htd::ITreeDecompositionManipulationOperation * operation : manipulationOperations_)
    {
        htd::ITreeDecompositionManipulationOperation * clone = operation->clone();

        clone->setManagementInstance(managementInstance());

        clonedManipulationOperations.push_back(clone);

        clone->apply(graph, decomposition, labelingFunctions);
    }

    htd::vertex_t optimalRoot = initialRoot;

    htd::FitnessEvaluation * optimalFitness = fitnessFunction.fitness(graph, decomposition);

    HTD_ASSERT(optimalFitness != nullptr)

#ifdef VERBOSE
    //TODO
    debug(decomposition);

    std::cout << "INITIAL FITNESS:     " << optimalFitness << "   (ROOT: " << optimalRoot << ")" << std::endl << std::endl << std::endl << std::endl;
#endif

    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    for (auto it = candidates.begin(); it != candidates.end() && !isTerminated(); ++it)
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
                    std::copy(createdVertices.begin() + oldCreatedVerticesCount, createdVertices.end(), std::back_inserter(affectedVertices));

                    oldCreatedVerticesCount = createdVertices.size();
                }
            }

            htd::FitnessEvaluation * currentFitness = fitnessFunction.fitness(graph, decomposition);

            HTD_ASSERT(currentFitness != nullptr)

#ifdef VERBOSE
            //TODO
            debug(decomposition);

            std::cout << "CURRENT FITNESS:     " << currentFitness << "   (ROOT: " << vertex << ")" << std::endl;
#endif

            if (*currentFitness > *optimalFitness)
            {
                delete optimalFitness;

                optimalFitness = currentFitness;

                optimalRoot = vertex;

#ifdef VERBOSE
                std::cout << "NEW OPTIMAL FITNESS: " << optimalFitness << "   (ROOT: " << optimalRoot << ")" << std::endl;
#endif
            }
            else
            {
                delete currentFitness;
            }

#ifdef VERBOSE
            std::cout << std::endl << std::endl << std::endl;
#endif
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

#ifdef VERBOSE
    //TODO
    debug(decomposition);

    std::cout << "OPTIMAL FITNESS:     " << optimalFitness << "   (ROOT: " << optimalRoot << ")" << std::endl << std::endl << std::endl << std::endl;
#endif

    delete optimalFitness;
}

bool htd::TreeDecompositionOptimizationOperation::isSafeOperation(const htd::ITreeDecompositionManipulationOperation & manipulationOperation) const
{
    return manipulationOperation.isLocalOperation() &&
           !manipulationOperation.removesTreeNodes() &&
           !manipulationOperation.modifiesBagContents() &&
           !manipulationOperation.createsSubsetMaximalBags() &&
           !manipulationOperation.createsLocationDependendLabels();
}

void htd::TreeDecompositionOptimizationOperation::removeCreatedNodes(htd::IMutableTreeDecomposition & decomposition, htd::vertex_t start, htd::vertex_t lastRegularVertex) const
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

    decomposition.copyNeighborsTo(neighbors, current);

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

        decomposition.copyNeighborsTo(neighbors, current);

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

htd::TreeDecompositionOptimizationOperation * htd::TreeDecompositionOptimizationOperation::clone(void) const
{
    htd::TreeDecompositionOptimizationOperation * ret = new htd::TreeDecompositionOptimizationOperation(*fitnessFunction_);

    for (const auto & manipulationOperation : manipulationOperations_)
    {
        ret->addManipulationOperation(manipulationOperation->clone());
    }

    ret->setManagementInstance(managementInstance());

    return ret;
}

#endif /* HTD_HTD_TREEDECOMPOSITIONOPTIMIZATIONOPERATION_CPP */
