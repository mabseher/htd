/*
 * File:   WeakNormalizationOperation.cpp
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

#ifndef HTD_HTD_WEAKNORMALIZATIONOPERATION_CPP
#define	HTD_HTD_WEAKNORMALIZATIONOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/WeakNormalizationOperation.hpp>
#include <htd/AddEmptyLeavesOperation.hpp>
#include <htd/AddEmptyRootOperation.hpp>
#include <htd/JoinNodeNormalizationOperation.hpp>

htd::WeakNormalizationOperation::WeakNormalizationOperation(void)
{

}

htd::WeakNormalizationOperation::WeakNormalizationOperation(bool emptyRoot, bool emptyLeaves, bool identicalJoinNodeParent) : emptyRoot_(emptyRoot), emptyLeaves_(emptyLeaves), identicalJoinNodeParent_(identicalJoinNodeParent)
{

}

htd::WeakNormalizationOperation::~WeakNormalizationOperation()
{

}

void htd::WeakNormalizationOperation::apply(htd::IMutablePathDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::WeakNormalizationOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    if (emptyRoot_)
    {
        htd::AddEmptyRootOperation addEmptyRootOperation;

        addEmptyRootOperation.apply(decomposition, labelingFunctions);
    }

    if (emptyLeaves_)
    {
        htd::AddEmptyLeavesOperation addEmptyLeavesOperation;

        addEmptyLeavesOperation.apply(decomposition, labelingFunctions);
    }
}

void htd::WeakNormalizationOperation::apply(htd::IMutableTreeDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::WeakNormalizationOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    if (emptyRoot_)
    {
        htd::AddEmptyRootOperation addEmptyRootOperation;

        addEmptyRootOperation.apply(decomposition, labelingFunctions);
    }

    if (emptyLeaves_)
    {
        htd::AddEmptyLeavesOperation addEmptyLeavesOperation;

        addEmptyLeavesOperation.apply(decomposition, labelingFunctions);
    }

    htd::JoinNodeNormalizationOperation joinNodeNormalizationOperation(identicalJoinNodeParent_);

    joinNodeNormalizationOperation.apply(decomposition, labelingFunctions);
}

htd::WeakNormalizationOperation * htd::WeakNormalizationOperation::clone(void) const
{
    return new htd::WeakNormalizationOperation(emptyRoot_, emptyLeaves_, identicalJoinNodeParent_);
}

#endif /* HTD_HTD_WEAKNORMALIZATIONOPERATION_CPP */
