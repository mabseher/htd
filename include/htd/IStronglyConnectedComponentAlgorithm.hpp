/* 
 * File:   IStronglyConnectedComponentAlgorithm.hpp
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

#ifndef HTD_HTD_ISTRONGLYCONNECTEDCOMPONENTALGORITHM_HPP
#define HTD_HTD_ISTRONGLYCONNECTEDCOMPONENTALGORITHM_HPP

#include <htd/Globals.hpp>

#include <htd/IConnectedComponentAlgorithm.hpp>
#include <htd/IDirectedMultiGraph.hpp>

namespace htd
{
    /**
     * Interface for algorithms which determine the strongly connected components of a given graph.
     */
    class IStronglyConnectedComponentAlgorithm : public htd::IConnectedComponentAlgorithm
    {
        public:
            using htd::IConnectedComponentAlgorithm::determineComponents;
            using htd::IConnectedComponentAlgorithm::determineComponent;

            virtual ~IStronglyConnectedComponentAlgorithm() = 0;

            /**
             *  Determine the strongly connected components of the given graph.
             *
             *  @param[in] graph     The graph which's components shall be determinded.
             *  @param[out] target   The target vector to which the determined components shall be appended.
             */
            virtual void determineComponents(const htd::IDirectedMultiGraph & graph, std::vector<std::vector<htd::vertex_t>> & target) const = 0;

            /**
             *  Determine the strongly connected component of the given graph where a given vertex resides.
             *
             *  @param[in] graph            The graph which's components shall be determinded.
             *  @param[in] startingVertex   The specific vertex from which the algorithm shall start.
             *  @param[out] target          The target vector to which the determined component shall be appended.
             */
            virtual void determineComponent(const htd::IDirectedMultiGraph & graph, htd::vertex_t startingVertex, std::vector<htd::vertex_t> & target) const = 0;

            /**
             *  Create a deep copy of the current strongly connected component algorithm.
             *
             *  @return A new IStronglyConnectedComponentAlgorithm object identical to the current strongly connected component algorithm.
             */
            virtual IStronglyConnectedComponentAlgorithm * clone(void) const HTD_OVERRIDE = 0;
    };

    inline htd::IStronglyConnectedComponentAlgorithm::~IStronglyConnectedComponentAlgorithm() { }
}

#endif /* HTD_HTD_ISTRONGLYCONNECTEDCOMPONENTALGORITHM_HPP */
