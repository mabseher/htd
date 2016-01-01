/* 
 * File:   DepthFirstConnectedComponentAlgorithm.cpp
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

#ifndef HTD_HTD_DEPTHFIRSTCONNECTEDCOMPONENTALGORITHM_CPP
#define	HTD_HTD_DEPTHFIRSTCONNECTEDCOMPONENTALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/DepthFirstConnectedComponentAlgorithm.hpp>
#include <htd/VectorAdapter.hpp>

htd::DepthFirstConnectedComponentAlgorithm::DepthFirstConnectedComponentAlgorithm(void)
{

}

htd::DepthFirstConnectedComponentAlgorithm::~DepthFirstConnectedComponentAlgorithm()
{

}

htd::Collection<htd::Collection<htd::vertex_t>> htd::DepthFirstConnectedComponentAlgorithm::determineComponents(const htd::IHypergraph & graph) const
{
    htd::VectorAdapter<htd::Collection<htd::vertex_t>> ret;

    //TODO Implement!
    HTD_UNUSED(graph);

    return ret;
}

htd::DepthFirstConnectedComponentAlgorithm * htd::DepthFirstConnectedComponentAlgorithm::clone(void) const
{
    return new DepthFirstConnectedComponentAlgorithm();
}

#endif /* HTD_HTD_DEPTHFIRSTCONNECTEDCOMPONENTALGORITHM_CPP */
