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

#include <algorithm>
#include <stack>
#include <stdexcept>

/*
struct Node
{
    int id;

    int index;

    int lowlink;

    Node * caller;

    unsigned int vindex;
};
*/

htd::TarjanStronglyConnectedComponentAlgorithm::TarjanStronglyConnectedComponentAlgorithm(void)
{

}

htd::TarjanStronglyConnectedComponentAlgorithm::~TarjanStronglyConnectedComponentAlgorithm()
{

}

void htd::TarjanStronglyConnectedComponentAlgorithm::determineComponents(const htd::IMultiHypergraph & graph, std::vector<std::vector<htd::vertex_t>> & target) const
{
    //TODO Implement!
    HTD_UNUSED(graph)
    HTD_UNUSED(target)
}

void htd::TarjanStronglyConnectedComponentAlgorithm::determineComponents(const htd::IDirectedMultiGraph & graph, std::vector<std::vector<htd::vertex_t>> & target) const
{
    //TODO Implement!
    HTD_UNUSED(graph)
    HTD_UNUSED(target)
}

void htd::TarjanStronglyConnectedComponentAlgorithm::determineComponent(const htd::IMultiHypergraph & graph, htd::vertex_t startingVertex, std::vector<htd::vertex_t> & target) const
{
    //TODO Implement!
    HTD_UNUSED(graph)
    HTD_UNUSED(target)
    HTD_UNUSED(startingVertex)
}

void htd::TarjanStronglyConnectedComponentAlgorithm::determineComponent(const htd::IDirectedMultiGraph & graph, htd::vertex_t startingVertex, std::vector<htd::vertex_t> & target) const
{
    HTD_UNUSED(graph)
    HTD_UNUSED(target)
    HTD_UNUSED(startingVertex)
}

htd::TarjanStronglyConnectedComponentAlgorithm * htd::TarjanStronglyConnectedComponentAlgorithm::clone(void) const
{
    return new TarjanStronglyConnectedComponentAlgorithm();
}

#endif /* HTD_HTD_TARJANSTRONGLYCONNECTEDCOMPONENTALGORITHM_CPP */
