/* 
 * File:   ISetCoverAlgorithm.hpp
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

#ifndef HTD_HTD_ISETCOVERALGORITHM_HPP
#define HTD_HTD_ISETCOVERALGORITHM_HPP

#include <htd/Globals.hpp>
#include <htd/ConstCollection.hpp>
#include <htd/LibraryInstance.hpp>

#include <vector>

namespace htd
{
    /**
     * Interface for algorithms which solve the set-cover problem.
     */
    class ISetCoverAlgorithm
    {
        public:
            virtual ~ISetCoverAlgorithm() = 0;

            /**
             *  Getter for the associated management class.
             *
             *  @return The associated management class.
             */
            virtual const htd::LibraryInstance * managementInstance(void) const HTD_NOEXCEPT = 0;

            /**
             *  Set a new management class for the library object.
             *
             *  @param[in] manager   The new management class for the library object.
             */
            virtual void setManagementInstance(const htd::LibraryInstance * const manager) = 0;

            /**
             *  Determine the connected components of the given graph.
             *
             *  @param[in] elements     The set of elements which must be covered.
             *  @param[in] containers   The collection of containers which are available for covering the given elements.
             *  @param[out] target      The target vector to which the indices of the covering containers shall be appended.
             *
             *  @note The vector 'elements' and all vectors stored in the argument 'containers' must be sorted and must not contain duplicates, otherwise the result of this method is undefined.
             */
            virtual void computeSetCover(const std::vector<htd::id_t> & elements, const std::vector<std::vector<htd::id_t>> & containers, std::vector<htd::index_t> & target) const = 0;

            /**
             *  Determine the connected components of the given graph.
             *
             *  @param[in] elements     The set of elements which must be covered.
             *  @param[in] containers   The collection of containers which are available for covering the given elements.
             *  @param[out] target      The target vector to which the indices of the covering containers shall be appended.
             *
             *  @note The collection 'elements' and all vectors stored in the argument 'containers' must be sorted and must not contain duplicates, otherwise the result of this method is undefined.
             */
            virtual void computeSetCover(const htd::ConstCollection<htd::id_t> & elements, const htd::ConstCollection<std::vector<htd::id_t>> & containers, std::vector<htd::index_t> & target) const = 0;

            /**
             *  Create a deep copy of the current set-cover algorithm.
             *
             *  @return A new ISetCoverAlgorithm object identical to the current set-cover algorithm.
             */
            virtual ISetCoverAlgorithm * clone(void) const = 0;
    };

    inline htd::ISetCoverAlgorithm::~ISetCoverAlgorithm() { }
}

#endif /* HTD_HTD_ISETCOVERALGORITHM_HPP */
