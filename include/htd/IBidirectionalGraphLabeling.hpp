/*
 * File:   IBidirectionalGraphLabeling.hpp
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

#ifndef HTD_HTD_IBIDIRECTIONALGRAPHLABELING_HPP
#define	HTD_HTD_IBIDIRECTIONALGRAPHLABELING_HPP

#include <htd/Globals.hpp>

#include <htd/IGraphLabeling.hpp>
#include <htd/ILabel.hpp>

namespace htd
{
    class IBidirectionalGraphLabeling : public virtual htd::IGraphLabeling
    {
        public:
            virtual ~IBidirectionalGraphLabeling() = 0;

            virtual bool isVertexLabel(const htd::ILabel & label) const = 0;

            virtual bool isHyperedgeLabel(const htd::ILabel & label) const = 0;

            virtual htd::vertex_t lookupVertex(const htd::ILabel & label) const = 0;

            virtual const htd::hyperedge_t & lookupHyperedge(const htd::ILabel & label) const = 0;

            virtual IBidirectionalGraphLabeling * clone(void) const = 0;
    };
    
    inline htd::IBidirectionalGraphLabeling::~IBidirectionalGraphLabeling() { }
}

#endif /* HTD_HTD_IBIDIRECTIONALGRAPHLABELING_HPP */
