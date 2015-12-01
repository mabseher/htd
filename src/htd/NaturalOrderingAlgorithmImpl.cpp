/* 
 * File:   NaturalOrderingAlgorithmImpl.cpp
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

#ifndef HTD_HTD_NATURALORDERINGALGORITHMIMPL_CPP
#define	HTD_HTD_NATURALORDERINGALGORITHMIMPL_CPP

#include <htd/Globals.hpp>
#include <htd/IGraph.hpp>
#include <htd/IHypergraph.hpp>
#include <htd/NaturalOrderingAlgorithmImpl.hpp>

#include <algorithm>
#include <cstdlib>
#include <set>
#include <vector>
#include <iterator>
#include <stdexcept>

htd::NaturalOrderingAlgorithmImpl::NaturalOrderingAlgorithmImpl(void)
{
    
}
            
htd::NaturalOrderingAlgorithmImpl::~NaturalOrderingAlgorithmImpl()
{
    
}

void htd::NaturalOrderingAlgorithmImpl::computeOrdering(const htd::IHypergraph & graph, std::vector<htd::vertex_t> & result) const
{
    std::vector<htd::vertex_t> ret;
    
    graph.getVertices(ret);
    
    std::sort(ret.begin(), ret.end());
    
    std::copy(ret.begin(), ret.end(), std::back_inserter(result));
}

#endif /* HTD_HTD_NATURALORDERINGALGORITHMIMPL_CPP */
