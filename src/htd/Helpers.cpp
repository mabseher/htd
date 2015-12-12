/* 
 * File:   Helpers.hpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015, Michael Abseher
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

#ifndef HTD_HTD_HELPERS_CPP
#define	HTD_HTD_HELPERS_CPP

#include <htd/BucketEliminationTreeDecompositionAlgorithm.hpp>
#include <htd/Helpers.hpp>
#include <htd/HypertreeDecompositionAlgorithm.hpp>
#include <htd/IMutableGraph.hpp>
#include <htd/IOrderingAlgorithm.hpp>
#include <htd/IMutableHypergraph.hpp>
#include <htd/IMutableDirectedGraph.hpp>
#include <htd/IMutableLabeledTree.hpp>
#include <htd/ILabeledTree.hpp>
#include <htd/ITreeDecomposition.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/ITreeDecompositionAlgorithm.hpp>
#include <htd/Hypergraph.hpp>
#include <htd/Graph.hpp>
#include <htd/DirectedGraph.hpp>
#include <htd/TreeDecomposition.hpp>
#include <htd/HypertreeDecomposition.hpp>
#include <htd/ISetCoverAlgorithm.hpp>
#include <htd/SetCoverAlgorithm.hpp>
#include <htd/MinFillOrderingAlgorithm.hpp>

void htd::print(bool input)
{
    if (input)
    {
        std::cout << "true";
    }
    else
    {
        std::cout << "false";
    }
}

template < >
void htd::print<std::string>(const std::string & input)
{
    std::cout << "\"" << input << "\"";
}

htd::IMutableGraph * htd::getDefaultGraph(void)
{
    return new htd::Graph();
}

htd::IMutableGraph * htd::getDefaultGraph(std::size_t size)
{
    return new htd::Graph(size);
}

htd::IMutableHypergraph * htd::getDefaultHypergraph(void)
{
    return new htd::Hypergraph();
}

htd::IMutableHypergraph * htd::getDefaultHypergraph(std::size_t size)
{
    return new htd::Hypergraph(size);
}

htd::IMutableDirectedGraph * htd::getDefaultDirectedGraph(void)
{
    return new htd::DirectedGraph();
}

htd::IMutableDirectedGraph * htd::getDefaultDirectedGraph(std::size_t size)
{
    return new htd::DirectedGraph(size);
}

htd::ITreeDecompositionAlgorithm * htd::getDefaultTreeDecompositionAlgorithm(const htd::IOrderingAlgorithm & orderingAlgorithm)
{
    return new htd::BucketEliminationTreeDecompositionAlgorithm(orderingAlgorithm);
}

htd::IMutableTreeDecomposition * htd::getDefaultTreeDecomposition(void)
{
    return new htd::TreeDecomposition();
}

htd::IMutableTreeDecomposition * htd::getDefaultTreeDecomposition(const htd::ITreeDecomposition & decomposition)
{
    return new htd::TreeDecomposition(decomposition);
}

htd::IMutableHypertreeDecomposition * htd::getDefaultHypertreeDecomposition(void)
{
    return new htd::HypertreeDecomposition();
}

htd::IMutableHypertreeDecomposition * htd::getDefaultHypertreeDecomposition(const htd::ITreeDecomposition & decomposition)
{
    return new htd::HypertreeDecomposition(decomposition);
}

htd::IMutableHypertreeDecomposition * htd::getDefaultHypertreeDecomposition(const htd::IHypertreeDecomposition & decomposition)
{
    return new htd::HypertreeDecomposition(decomposition);
}

htd::IHypertreeDecompositionAlgorithm * htd::getDefaultHypertreeDecompositionAlgorithm(const htd::ITreeDecompositionAlgorithm & treeDecompositionAlgorithm, const htd::ISetCoverAlgorithm & setCoverAlgorithm)
{
    return new htd::HypertreeDecompositionAlgorithm(treeDecompositionAlgorithm, setCoverAlgorithm);
}

htd::IOrderingAlgorithm * htd::getDefaultOrderingAlgorithm(void)
{
    return new htd::MinFillOrderingAlgorithm();
}

htd::ISetCoverAlgorithm * htd::getDefaultSetCoverAlgorithm(void)
{
    return new htd::SetCoverAlgorithm();
}

#endif /* HTD_HTD_HELPERS_CPP */
