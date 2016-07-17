/*
 * File:   SemiNormalizationOperation.cpp
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

#ifndef HTD_HTD_SEMINORMALIZATIONOPERATION_CPP
#define	HTD_HTD_SEMINORMALIZATIONOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/SemiNormalizationOperation.hpp>
#include <htd/WeakNormalizationOperation.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/LimitChildCountOperation.hpp>

htd::SemiNormalizationOperation::SemiNormalizationOperation(void)
    : htd::WeakNormalizationOperation()
{

}

htd::SemiNormalizationOperation::SemiNormalizationOperation(bool emptyRoot, bool emptyLeaves, bool identicalJoinNodeParent)
    : htd::WeakNormalizationOperation(emptyRoot, emptyLeaves, identicalJoinNodeParent)
{

}

htd::SemiNormalizationOperation::~SemiNormalizationOperation()
{

}

void htd::SemiNormalizationOperation::apply(htd::IMutablePathDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::SemiNormalizationOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices) const
{
    apply(decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>());
}

void htd::SemiNormalizationOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    htd::WeakNormalizationOperation::apply(decomposition, labelingFunctions);
}

void htd::SemiNormalizationOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    htd::WeakNormalizationOperation::apply(decomposition, relevantVertices, labelingFunctions);
}

void htd::SemiNormalizationOperation::apply(htd::IMutableTreeDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::SemiNormalizationOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    apply(decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>(), createdVertices, removedVertices);
}

void htd::SemiNormalizationOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    htd::WeakNormalizationOperation::apply(decomposition, labelingFunctions);

    htd::LimitChildCountOperation limitChildCountOperation(2);

    limitChildCountOperation.setManagementInstance(managementInstance());

    limitChildCountOperation.apply(decomposition, labelingFunctions);
}

void htd::SemiNormalizationOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    std::size_t newVertexCount = 0;

    std::size_t oldCreatedVerticesCount = createdVertices.size();

    std::vector<htd::vertex_t> newRelevantVertices(relevantVertices.begin(), relevantVertices.end());

    htd::WeakNormalizationOperation::apply(decomposition, newRelevantVertices, labelingFunctions, createdVertices, removedVertices);

    newVertexCount = createdVertices.size() - oldCreatedVerticesCount;

    if (newVertexCount > 0)
    {
        std::copy(createdVertices.begin() + oldCreatedVerticesCount, createdVertices.end(), std::back_inserter(newRelevantVertices));

        oldCreatedVerticesCount = createdVertices.size();
    }

    htd::LimitChildCountOperation limitChildCountOperation(2);

    limitChildCountOperation.setManagementInstance(managementInstance());

    limitChildCountOperation.apply(decomposition, newRelevantVertices, labelingFunctions, createdVertices, removedVertices);
}

bool htd::SemiNormalizationOperation::isLocalOperation(void) const
{
    return true;
}

bool htd::SemiNormalizationOperation::createsTreeNodes(void) const
{
    return true;
}

bool htd::SemiNormalizationOperation::removesTreeNodes(void) const
{
    return false;
}

bool htd::SemiNormalizationOperation::modifiesBagContents(void) const
{
    return false;
}

bool htd::SemiNormalizationOperation::createsSubsetMaximalBags(void) const
{
    return false;
}

bool htd::SemiNormalizationOperation::createsLocationDependendLabels(void) const
{
    return false;
}

htd::SemiNormalizationOperation * htd::SemiNormalizationOperation::clone(void) const
{
    return new htd::SemiNormalizationOperation(emptyRootRequired(), emptyLeavesRequired(), identicalJoinNodeParentRequired());
}

#endif /* HTD_HTD_SEMINORMALIZATIONOPERATION_CPP */
