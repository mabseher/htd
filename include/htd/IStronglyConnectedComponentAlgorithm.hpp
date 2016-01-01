/* 
 * File:   IStronglyConnectedComponentAlgorithm.hpp
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

#ifndef HTD_HTD_ISTRONGLYCONNECTEDCOMPONENTALGORITHM_HPP
#define	HTD_HTD_ISTRONGLYCONNECTEDCOMPONENTALGORITHM_HPP

#include <htd/Globals.hpp>
#include <htd/Collection.hpp>
#include <htd/IDirectedGraph.hpp>
#include <htd/IConnectedComponentAlgorithm.hpp>

namespace htd
{
    class IStronglyConnectedComponentAlgorithm : public virtual htd::IConnectedComponentAlgorithm
    {
        public:
            virtual ~IStronglyConnectedComponentAlgorithm() = 0;
            
            using htd::IConnectedComponentAlgorithm::determineComponents;

            virtual htd::Collection<htd::Collection<htd::vertex_t>> determineComponents(const htd::IDirectedGraph & graph) const = 0;

            virtual IStronglyConnectedComponentAlgorithm * clone(void) const = 0;
    };

    inline htd::IStronglyConnectedComponentAlgorithm::~IStronglyConnectedComponentAlgorithm() { }
}

#endif /* HTD_HTD_ISTRONGLYCONNECTEDCOMPONENTALGORITHM_HPP */
