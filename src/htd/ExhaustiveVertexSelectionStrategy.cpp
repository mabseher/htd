/*
 * File:   ExhaustiveVertexSelectionStrategy.cpp
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

#ifndef HTD_HTD_EXHAUSTIVEVERTEXSELECTIONSTRATEGY_CPP
#define HTD_HTD_EXHAUSTIVEVERTEXSELECTIONSTRATEGY_CPP

#include <htd/Globals.hpp>

#include <htd/ExhaustiveVertexSelectionStrategy.hpp>

#include <algorithm>

htd::ExhaustiveVertexSelectionStrategy::ExhaustiveVertexSelectionStrategy(void)
{

}

htd::ExhaustiveVertexSelectionStrategy::~ExhaustiveVertexSelectionStrategy()
{

}

void htd::ExhaustiveVertexSelectionStrategy::selectVertices(const htd::IMultiHypergraph & graph, std::vector<htd::vertex_t> & target) const
{
    const htd::ConstCollection<htd::vertex_t> & vertexCollection = graph.vertices();

    target.insert(target.end(), vertexCollection.begin(), vertexCollection.end());
}

htd::ExhaustiveVertexSelectionStrategy * htd::ExhaustiveVertexSelectionStrategy::clone(void) const
{
    return new htd::ExhaustiveVertexSelectionStrategy();
}

#endif /* HTD_HTD_EXHAUSTIVEVERTEXSELECTIONSTRATEGY_CPP */
