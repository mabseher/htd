/* 
 * File:   ISetCoverAlgorithm.hpp
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

#ifndef HTD_HTD_ISETCOVERALGORITHM_HPP
#define	HTD_HTD_ISETCOVERALGORITHM_HPP

#include <htd/Globals.hpp>

namespace htd
{
    class ISetCoverAlgorithm
    {
        public:
            virtual ~ISetCoverAlgorithm() = 0;
            
            virtual void computeSetCover(const htd::vertex_container & vertices, const std::vector<htd::vertex_container> & containers, std::vector<htd::vertex_container> & result) const = 0;

            virtual ISetCoverAlgorithm * clone(void) const = 0;
    };

    inline htd::ISetCoverAlgorithm::~ISetCoverAlgorithm() { }
}

#endif /* HTD_HTD_ISETCOVERALGORITHM_HPP */
