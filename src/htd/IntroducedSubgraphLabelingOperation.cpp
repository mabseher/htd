/*
 * File:   IntroducedSubgraphLabelingOperation.cpp
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

#ifndef HTD_HTD_INTRODUCEDSUBGRAPHLABELINGOPERATION_CPP
#define	HTD_HTD_INTRODUCEDSUBGRAPHLABELINGOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/IntroducedSubgraphLabelingOperation.hpp>
#include <htd/PostOrderTreeTraversal.hpp>
#include <htd/VectorAdapter.hpp>

#include <algorithm>
#include <unordered_map>
#include <vector>
#include <stdexcept>

htd::IntroducedSubgraphLabelingOperation::IntroducedSubgraphLabelingOperation(const htd::IMultiHypergraph & graph) : graph_(graph)
{

}

htd::IntroducedSubgraphLabelingOperation::~IntroducedSubgraphLabelingOperation()
{

}

void htd::IntroducedSubgraphLabelingOperation::apply(htd::IMutablePathDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::IntroducedSubgraphLabelingOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(decomposition);
    HTD_UNUSED(labelingFunctions);

    throw std::logic_error("void htd::IntroducedSubgraphLabelingOperation::apply(htd::IMutablePathDecomposition &, const std::vector<htd::ILabelingFunction *> &) const: NOT IMPLEMENTED!");
}

void htd::IntroducedSubgraphLabelingOperation::apply(htd::IMutableTreeDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::IntroducedSubgraphLabelingOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(decomposition);
    HTD_UNUSED(labelingFunctions);

    throw std::logic_error("void htd::IntroducedSubgraphLabelingOperation::apply(htd::IMutablePathDecomposition &, const std::vector<htd::ILabelingFunction *> &) const: NOT IMPLEMENTED!");
}

htd::IntroducedSubgraphLabelingOperation * htd::IntroducedSubgraphLabelingOperation::clone(void) const
{
    return new htd::IntroducedSubgraphLabelingOperation(graph_);
}

#endif /* HTD_HTD_INTRODUCEDSUBGRAPHLABELINGOPERATION_CPP */
