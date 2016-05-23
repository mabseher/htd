/* 
 * File:   ILabeledPath.hpp
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

#ifndef HTD_HTD_ILABELEDPATH_HPP
#define	HTD_HTD_ILABELEDPATH_HPP

#include <htd/Globals.hpp>
#include <htd/ILabeledTree.hpp>
#include <htd/IPath.hpp>

namespace htd
{
    /**
     * Interface for classes which represent labeled paths.
     */
    class ILabeledPath : public virtual htd::ILabeledTree, public virtual htd::IPath
    {
        public:
            virtual ~ILabeledPath() = 0;

            /**
             *  Create a deep copy the current labeled path.
             *
             *  @return A new ILabeledPath object identical to the current labeled path.
             */
            virtual ILabeledPath * clone(void) const = 0;
    };

    inline htd::ILabeledPath::~ILabeledPath() { }
}

#endif /* HTD_HTD_ILABELEDPATH_HPP */
