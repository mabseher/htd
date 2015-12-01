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
#include <htd/HypertreeDecompositionAlgorithmImpl.hpp>
#include <htd/IMutableGraph.hpp>
#include <htd/IOrderingAlgorithm.hpp>
#include <htd/IMutableHypergraph.hpp>
#include <htd/IMutableDirectedGraph.hpp>
#include <htd/IMutableLabeledTree.hpp>
#include <htd/ILabeledTree.hpp>
#include <htd/ITreeDecomposition.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/ITreeDecompositionAlgorithm.hpp>
#include <htd/MutableHypergraphImpl.hpp>
#include <htd/MutableGraphImpl.hpp>
#include <htd/MutableDirectedGraphImpl.hpp>
#include <htd/MutableTreeDecompositionImpl.hpp>
#include <htd/MutableHypertreeDecompositionImpl.hpp>
#include <htd/ISetCoverAlgorithm.hpp>
#include <htd/SetCoverAlgorithmImpl.hpp>
#include <htd/MutableHypergraphImpl.hpp>
#include <htd/MinFillOrderingAlgorithmImpl.hpp>

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

htd::IMutableGraph * htd::getDefaultMutableGraphImplementation(std::size_t size)
{
    return new htd::MutableGraphImpl(size);
}

htd::IMutableHypergraph * htd::getDefaultMutableHypergraphImplementation(std::size_t size)
{
    return new htd::MutableHypergraphImpl(size);
}

htd::IMutableDirectedGraph * htd::getDefaultMutableDirectedGraphImplementation(std::size_t size)
{
    return new htd::MutableDirectedGraphImpl(size);
}

htd::ITreeDecompositionAlgorithm * htd::getDefaultTreeDecompositionAlgorithm(const htd::IOrderingAlgorithm & orderingAlgorithm)
{
    return new htd::BucketEliminationTreeDecompositionAlgorithm(orderingAlgorithm);
}

htd::IMutableLabeledTree * htd::getDefaultMutableLabeledTreeImplementation(void)
{
    return new htd::MutableTreeDecompositionImpl();
}
    
htd::IMutableLabeledTree * htd::getDefaultMutableLabeledTreeImplementation(const htd::ILabeledTree & decomposition)
{
    return new htd::MutableTreeDecompositionImpl(decomposition);
}

htd::IMutableTreeDecomposition * htd::getDefaultMutableTreeDecompositionImplementation(void)
{
    return new htd::MutableTreeDecompositionImpl();
}

htd::IMutableTreeDecomposition * htd::getDefaultMutableTreeDecompositionImplementation(const htd::ITreeDecomposition & decomposition)
{
    return new htd::MutableTreeDecompositionImpl(decomposition);
}

htd::IMutableHypertreeDecomposition * htd::getDefaultMutableHypertreeDecompositionImplementation(void)
{
    return new htd::MutableHypertreeDecompositionImpl();
}

htd::IMutableHypertreeDecomposition * htd::getDefaultMutableHypertreeDecompositionImplementation(const htd::ITreeDecomposition & decomposition)
{
    return new htd::MutableHypertreeDecompositionImpl(decomposition);
}

htd::IMutableHypertreeDecomposition * htd::getDefaultMutableHypertreeDecompositionImplementation(const htd::IHypertreeDecomposition & decomposition)
{
    return new htd::MutableHypertreeDecompositionImpl(decomposition);
}

htd::IHypertreeDecompositionAlgorithm * htd::getDefaultHypertreeDecompositionAlgorithm(const htd::ITreeDecompositionAlgorithm & treeDecompositionAlgorithm)
{
    return new htd::HypertreeDecompositionAlgorithmImpl(treeDecompositionAlgorithm);
}

htd::IOrderingAlgorithm * htd::getDefaultOrderingAlgorithmImplementation(void)
{
    return new htd::MinFillOrderingAlgorithmImpl();
}

htd::ISetCoverAlgorithm * htd::getDefaultSetCoverAlgorithmImplementation(void)
{
    return new htd::SetCoverAlgorithmImpl();
}

#endif /* HTD_HTD_HELPERS_CPP */
