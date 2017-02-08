/* 
 * File:   IPath.hpp
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

#ifndef HTD_HTD_IPATH_HPP
#define HTD_HTD_IPATH_HPP

#include <htd/Globals.hpp>
#include <htd/ITree.hpp>

namespace htd
{
    /**
     * Interface for classes which represent paths.
     */
    class IPath : public virtual htd::ITree
    {
        public:
            virtual ~IPath() = 0;

            /**
             *  Access the leaf node of the path.
             *
             *  @return The leaf node of the path.
             */
            virtual htd::vertex_t leaf(void) const = 0;

            /**
             *  Access the child of a vertex.
             *
             *  @param[in] vertex   The vertex for which the child shall be returned.
             *
             *  @return The child of the vertex.
             */
            virtual htd::vertex_t child(htd::vertex_t vertex) const = 0;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Create a deep copy of the current path.
             *
             *  @return A new IPath object identical to the current path.
             */
            virtual IPath * clone(void) const HTD_OVERRIDE = 0;
#else
            /**
             *  Create a deep copy of the current path.
             *
             *  @return A new IPath object identical to the current path.
             */
            virtual IPath * clonePath(void) const = 0;
#endif
    };

    inline htd::IPath::~IPath() { }
}

#endif /* HTD_HTD_IPATH_HPP */
