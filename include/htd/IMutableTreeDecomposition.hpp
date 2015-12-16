/* 
 * File:   IMutableTreeDecomposition.hpp
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

#ifndef HTD_HTD_IMUTABLETREEDECOMPOSITION_HPP
#define	HTD_HTD_IMUTABLETREEDECOMPOSITION_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableLabeledTree.hpp>
#include <htd/ITreeDecomposition.hpp>

namespace htd
{
    class IMutableTreeDecomposition : public virtual htd::IMutableLabeledTree, public virtual htd::ITreeDecomposition
    {
        public:
            virtual ~IMutableTreeDecomposition() = 0;

            virtual void setBagContent(htd::vertex_t vertex, const htd::vertex_container & content) = 0;

            virtual void setBagContent(htd::vertex_t vertex, const htd::Collection<htd::vertex_t> & content) = 0;

            virtual IMutableTreeDecomposition * clone(void) const = 0;
    };

    inline htd::IMutableTreeDecomposition::~IMutableTreeDecomposition() { }
}

#endif /* HTD_HTD_IMUTABLETREEDECOMPOSITION_HPP */
