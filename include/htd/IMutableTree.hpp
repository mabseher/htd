/* 
 * File:   IMutableTree.hpp
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

#ifndef HTD_HTD_IMUTABLETREE_HPP
#define	HTD_HTD_IMUTABLETREE_HPP

#include <htd/Globals.hpp>
#include <htd/ITree.hpp>

namespace htd
{
    class IMutableTree : public virtual htd::ITree
    {
        public:
            virtual ~IMutableTree() = 0;
            
            virtual void removeVertex(htd::vertex_t vertex) = 0;
            
            virtual void removeSubtree(htd::vertex_t subtreeRoot) = 0;
            
            virtual htd::vertex_t insertRoot(void) = 0;
            
            virtual void removeRoot(void) = 0;
            
            virtual htd::vertex_t addChild(htd::vertex_t vertex) = 0;
            
            virtual void removeChild(htd::vertex_t vertex, htd::vertex_t child) = 0;

            virtual htd::vertex_t addParent(htd::vertex_t vertex) = 0;

            virtual IMutableTree * clone(void) const = 0;
    };

    inline htd::IMutableTree::~IMutableTree() { }
}

#endif /* HTD_HTD_IMUTABLETREE_HPP */
