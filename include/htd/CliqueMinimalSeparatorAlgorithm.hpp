/*
 * File:   CliqueMinimalSeparatorAlgorithm.hpp
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

#ifndef HTD_HTD_CLIQUEMINIMALSEPARATORALGORITHM_HPP
#define HTD_HTD_CLIQUEMINIMALSEPARATORALGORITHM_HPP

#include <htd/IGraphSeparatorAlgorithm.hpp>

namespace htd
{
    /**
     *  Implementation of the IGraphSeparatorAlgorithm interface computing clique minimal separators.
     */
    class CliqueMinimalSeparatorAlgorithm : public htd::IGraphSeparatorAlgorithm
    {
        public:
            /**
             *  Constructor for a new clique minimal separator algorithm.
             *
             *  @param[in] manager  The management instance to which the new manipulation operation belongs..
             */
            HTD_API CliqueMinimalSeparatorAlgorithm(const htd::LibraryInstance * const manager);

            /**
             *  Destructor of a clique minimal separator algorithm.
             */
            HTD_API virtual ~CliqueMinimalSeparatorAlgorithm();

            HTD_API std::vector<htd::vertex_t> * computeSeparator(const htd::IGraphStructure & graph) const HTD_OVERRIDE;

            HTD_API const htd::LibraryInstance * managementInstance(void) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API void setManagementInstance(const htd::LibraryInstance * const manager) HTD_OVERRIDE;

            HTD_API CliqueMinimalSeparatorAlgorithm * clone(void) const HTD_OVERRIDE;

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_HTD_CLIQUEMINIMALSEPARATORALGORITHM_HPP */
