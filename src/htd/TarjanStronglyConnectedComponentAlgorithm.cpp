/* 
 * File:   TarjanStronglyConnectedComponentAlgorithm.cpp
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

#ifndef HTD_HTD_TARJANSTRONGLYCONNECTEDCOMPONENTALGORITHM_CPP
#define	HTD_HTD_TARJANSTRONGLYCONNECTEDCOMPONENTALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/TarjanStronglyConnectedComponentAlgorithm.hpp>
#include <htd/VectorAdapter.hpp>

#include <algorithm>
#include <stack>
#include <stdexcept>

struct Node
{
    int id;

    int index;

    int lowlink;

    Node * caller;

    unsigned int vindex;
};

htd::TarjanStronglyConnectedComponentAlgorithm::TarjanStronglyConnectedComponentAlgorithm(void)
{

}

htd::TarjanStronglyConnectedComponentAlgorithm::~TarjanStronglyConnectedComponentAlgorithm()
{

}

htd::ConstCollection<htd::ConstCollection<htd::vertex_t>> htd::TarjanStronglyConnectedComponentAlgorithm::determineComponents(const htd::IHypergraph & graph) const
{
    htd::VectorAdapter<htd::ConstCollection<htd::vertex_t>> ret;

    //TODO Implement!
    HTD_UNUSED(graph)

    return htd::ConstCollection<htd::ConstCollection<htd::vertex_t>>::getInstance(ret);
}

htd::ConstCollection<htd::ConstCollection<htd::vertex_t>> htd::TarjanStronglyConnectedComponentAlgorithm::determineComponents(const htd::IDirectedGraph & graph) const
{
    htd::VectorAdapter<htd::ConstCollection<htd::vertex_t>> ret;

    //TODO Implement!
    HTD_UNUSED(graph)

    return htd::ConstCollection<htd::ConstCollection<htd::vertex_t>>::getInstance(ret);
}

htd::ConstCollection<htd::vertex_t> htd::TarjanStronglyConnectedComponentAlgorithm::determineComponent(const htd::IHypergraph & graph, htd::vertex_t startingVertex) const
{
    if (!graph.isVertex(startingVertex))
    {
        throw std::logic_error("htd::ConstCollection<htd::vertex_t> htd::TarjanStronglyConnectedComponentAlgorithm::determineComponent(const htd::IHypergraph &, htd::vertex_t) const");
    }

    htd::VectorAdapter<htd::vertex_t> ret;

    //TODO Implement!

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::ConstCollection<htd::vertex_t> htd::TarjanStronglyConnectedComponentAlgorithm::determineComponent(const htd::IDirectedGraph & graph, htd::vertex_t startingVertex) const
{
    if (!graph.isVertex(startingVertex))
    {
        throw std::logic_error("htd::ConstCollection<htd::vertex_t> htd::TarjanStronglyConnectedComponentAlgorithm::determineComponent(const htd::IDirectedGraph &, htd::vertex_t) const");
    }

    htd::VectorAdapter<htd::vertex_t> ret;

    //TODO Implement!

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::TarjanStronglyConnectedComponentAlgorithm * htd::TarjanStronglyConnectedComponentAlgorithm::clone(void) const
{
    return new TarjanStronglyConnectedComponentAlgorithm();
}

#endif /* HTD_HTD_TARJANSTRONGLYCONNECTEDCOMPONENTALGORITHM_CPP */
