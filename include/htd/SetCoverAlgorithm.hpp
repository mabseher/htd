/* 
 * File:   SetCoverAlgorithm.hpp
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

#ifndef HTD_HTD_SETCOVERALGORITHM_HPP
#define HTD_HTD_SETCOVERALGORITHM_HPP

#include <htd/Globals.hpp>
#include <htd/ISetCoverAlgorithm.hpp>

#include <vector>

namespace htd
{
    /**
     * Implementation of the ISetCoverAlgorithm interface based on exhaustive search via a branch-and-bound approach.
     */
    class SetCoverAlgorithm : public virtual htd::ISetCoverAlgorithm
    {
        public:
            /**
             *  Constructor for a new set-cover algorithm of type SetCoverAlgorithm.
             *
             *  @param[in] manager   The management instance to which the new algorithm belongs.
             */
            HTD_API SetCoverAlgorithm(const htd::LibraryInstance * const manager);
            
            HTD_API virtual ~SetCoverAlgorithm();
            
            HTD_API void computeSetCover(const std::vector<htd::id_t> & elements, const std::vector<std::vector<htd::id_t>> & containers, std::vector<htd::index_t> & target) const HTD_OVERRIDE;

            HTD_API void computeSetCover(const htd::ConstCollection<htd::id_t> & elements, const htd::ConstCollection<std::vector<htd::id_t>> & containers, std::vector<htd::index_t> & target) const HTD_OVERRIDE;

            HTD_API const htd::LibraryInstance * managementInstance(void) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API void setManagementInstance(const htd::LibraryInstance * const manager) HTD_OVERRIDE;

            HTD_API SetCoverAlgorithm * clone(void) const HTD_OVERRIDE;

        protected:
            /**
             *  Copy assignment operator for a set cover algorithm.
             *
             *  @note This operator is protected to prevent assignments to an already initialized algorithm.
             */
            SetCoverAlgorithm & operator=(const SetCoverAlgorithm &) { return *this; }

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_HTD_SETCOVERALGORITHM_HPP */
