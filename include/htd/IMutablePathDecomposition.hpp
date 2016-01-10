/* 
 * File:   IMutablePathDecomposition.hpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015-2016, Michael Abseher
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

#ifndef HTD_HTD_IMUTABLEPATHDECOMPOSITION_HPP
#define	HTD_HTD_IMUTABLEPATHDECOMPOSITION_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableLabeledPath.hpp>
#include <htd/IPathDecomposition.hpp>

namespace htd
{
    class IMutablePathDecomposition : public virtual htd::IMutableLabeledPath, public virtual htd::IPathDecomposition
    {
        public:
            virtual ~IMutablePathDecomposition() = 0;

            virtual void setBagContent(htd::vertex_t vertex, const std::vector<htd::vertex_t> & content) = 0;

            virtual void setBagContent(htd::vertex_t vertex, const htd::ConstCollection<htd::vertex_t> & content) = 0;

            virtual IMutablePathDecomposition * clone(void) const = 0;

            virtual IMutablePathDecomposition & operator=(const htd::IPath & original) = 0;

            virtual IMutablePathDecomposition & operator=(const htd::ILabeledPath & original) = 0;

            virtual IMutablePathDecomposition & operator=(const htd::IPathDecomposition & original) = 0;
    };

    inline htd::IMutablePathDecomposition::~IMutablePathDecomposition() { }
}

#endif /* HTD_HTD_IMUTABLEPATHDECOMPOSITION_HPP */
