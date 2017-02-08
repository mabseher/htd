/*
 * File:   AddEmptyRootOperation.cpp
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

#ifndef HTD_HTD_ADDEMPTYROOTOPERATION_CPP
#define HTD_HTD_ADDEMPTYROOTOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/AddEmptyRootOperation.hpp>

/**
 *  Private implementation details of class htd::AddEmptyRootOperation.
 */
struct htd::AddEmptyRootOperation::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager   The management instance to which the current object instance belongs.
     */
    Implementation(const htd::LibraryInstance * const manager) : managementInstance_(manager)
    {

    }

    virtual ~Implementation()
    {

    }

    /**
     *  The management instance to which the current object instance belongs.
     */
    const htd::LibraryInstance * managementInstance_;
};

htd::AddEmptyRootOperation::AddEmptyRootOperation(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{

}

htd::AddEmptyRootOperation::~AddEmptyRootOperation()
{

}

void htd::AddEmptyRootOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition) const
{
    apply(graph, decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::AddEmptyRootOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    apply(graph, decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>(), createdVertices, removedVertices);
}

void htd::AddEmptyRootOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(graph)

    htd::vertex_t root = decomposition.root();

    if (decomposition.bagSize(root) > 0)
    {
        htd::vertex_t newRoot = decomposition.addParent(root);

        for (auto & labelingFunction : labelingFunctions)
        {
            htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newRoot);

            const std::vector<htd::vertex_t> & bagContent = decomposition.bagContent(newRoot);

            htd::ILabel * newLabel = labelingFunction->computeLabel(bagContent, *labelCollection);

            delete labelCollection;

            decomposition.setVertexLabel(labelingFunction->name(), newRoot, newLabel);
        }
    }
}

void htd::AddEmptyRootOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    HTD_UNUSED(graph)
    HTD_UNUSED(removedVertices)

    bool rootVisited = false;

    for (auto it = relevantVertices.begin(); !rootVisited && it != relevantVertices.end(); ++it)
    {
        htd::vertex_t vertex = *it;

        if (decomposition.isRoot(vertex) && decomposition.bagSize(vertex) > 0)
        {
            htd::vertex_t newRoot = decomposition.addParent(vertex);

            for (auto & labelingFunction : labelingFunctions)
            {
                htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newRoot);

                const std::vector<htd::vertex_t> & bagContent = decomposition.bagContent(newRoot);

                htd::ILabel * newLabel = labelingFunction->computeLabel(bagContent, *labelCollection);

                delete labelCollection;

                decomposition.setVertexLabel(labelingFunction->name(), newRoot, newLabel);
            }

            createdVertices.push_back(newRoot);

            rootVisited = true;
        }
    }
}

void htd::AddEmptyRootOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition) const
{
    apply(graph, decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::AddEmptyRootOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    apply(graph, decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>(), createdVertices, removedVertices);
}

void htd::AddEmptyRootOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(graph)

    htd::vertex_t root = decomposition.root();

    if (decomposition.bagSize(root) > 0)
    {
        htd::vertex_t newRoot = decomposition.addParent(root);

        for (auto & labelingFunction : labelingFunctions)
        {
            htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newRoot);

            const std::vector<htd::vertex_t> & bagContent = decomposition.bagContent(newRoot);

            htd::ILabel * newLabel = labelingFunction->computeLabel(bagContent, *labelCollection);

            delete labelCollection;

            decomposition.setVertexLabel(labelingFunction->name(), newRoot, newLabel);
        }
    }
}

void htd::AddEmptyRootOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    HTD_UNUSED(graph)
    HTD_UNUSED(removedVertices)

    bool rootVisited = false;

    for (auto it = relevantVertices.begin(); !rootVisited && it != relevantVertices.end(); ++it)
    {
        htd::vertex_t vertex = *it;

        if (decomposition.isRoot(vertex) && decomposition.bagSize(vertex) > 0)
        {
            htd::vertex_t newRoot = decomposition.addParent(vertex);

            for (auto & labelingFunction : labelingFunctions)
            {
                htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newRoot);

                const std::vector<htd::vertex_t> & bagContent = decomposition.bagContent(newRoot);

                htd::ILabel * newLabel = labelingFunction->computeLabel(bagContent, *labelCollection);

                delete labelCollection;

                decomposition.setVertexLabel(labelingFunction->name(), newRoot, newLabel);
            }

            createdVertices.push_back(newRoot);

            rootVisited = true;
        }
    }
}

bool htd::AddEmptyRootOperation::isLocalOperation(void) const
{
    return true;
}

bool htd::AddEmptyRootOperation::createsTreeNodes(void) const
{
    return true;
}

bool htd::AddEmptyRootOperation::removesTreeNodes(void) const
{
    return false;
}

bool htd::AddEmptyRootOperation::modifiesBagContents(void) const
{
    return false;
}

bool htd::AddEmptyRootOperation::createsSubsetMaximalBags(void) const
{
    return false;
}

bool htd::AddEmptyRootOperation::createsLocationDependendLabels(void) const
{
    return false;
}

const htd::LibraryInstance * htd::AddEmptyRootOperation::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::AddEmptyRootOperation::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::AddEmptyRootOperation * htd::AddEmptyRootOperation::clone(void) const
{
    return new htd::AddEmptyRootOperation(managementInstance());
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IDecompositionManipulationOperation * htd::AddEmptyRootOperation::cloneDecompositionManipulationOperation(void) const
{
    return clone();
}

htd::IPathDecompositionManipulationOperation * htd::AddEmptyRootOperation::clonePathDecompositionManipulationOperation(void) const
{
    return clone();
}

htd::ITreeDecompositionManipulationOperation * htd::AddEmptyRootOperation::cloneTreeDecompositionManipulationOperation(void) const
{
    return clone();
}
#endif

#endif /* HTD_HTD_ADDEMPTYROOTOPERATION_CPP */
