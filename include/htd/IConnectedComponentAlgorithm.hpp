/* 
 * File:   IConnectedComponentAlgorithm.hpp
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

#ifndef HTD_HTD_ICONNECTEDCOMPONENTALGORITHM_HPP
#define	HTD_HTD_ICONNECTEDCOMPONENTALGORITHM_HPP

#include <htd/Globals.hpp>
#include <htd/Collection.hpp>
#include <htd/IHypergraph.hpp>

namespace htd
{
    class IConnectedComponentAlgorithm
    {
        public:
            virtual ~IConnectedComponentAlgorithm() = 0;
            
            virtual htd::Collection<htd::Collection<htd::vertex_t>> determineComponents(const htd::IHypergraph & graph) const = 0;

            virtual IConnectedComponentAlgorithm * clone(void) const = 0;
    };

    inline htd::IConnectedComponentAlgorithm::~IConnectedComponentAlgorithm() { }
}

#endif /* HTD_HTD_ICONNECTEDCOMPONENTALGORITHM_HPP */
