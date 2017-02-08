/*
 * File:   IDecompositionManipulationOperation.hpp
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

#ifndef HTD_HTD_IDECOMPOSITIONMANIPULATIONOPERATION_HPP
#define HTD_HTD_IDECOMPOSITIONMANIPULATIONOPERATION_HPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>

namespace htd
{
    /**
     * Interface for algorithms which manipulate a given decomposition.
     */
    class IDecompositionManipulationOperation
    {
        public:
            virtual ~IDecompositionManipulationOperation() = 0;

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

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Create a deep copy of the current decomposition manipulation operation.
             *
             *  @return A new IDecompositionManipulationOperation object identical to the current decomposition manipulation operation.
             */
            virtual IDecompositionManipulationOperation * clone(void) const = 0;
#else
            /**
             *  Create a deep copy of the current decomposition manipulation operation.
             *
             *  @return A new IDecompositionManipulationOperation object identical to the current decomposition manipulation operation.
             */
            virtual IDecompositionManipulationOperation * cloneDecompositionManipulationOperation(void) const = 0;
#endif
    };
    
    inline htd::IDecompositionManipulationOperation::~IDecompositionManipulationOperation() { }
}

#endif /* HTD_HTD_IDECOMPOSITIONMANIPULATIONOPERATION_HPP */
