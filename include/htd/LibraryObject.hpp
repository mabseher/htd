/*
 * File:   LibraryObject.hpp
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

#ifndef HTD_HTD_LIBRARYOBJECT_HPP
#define HTD_HTD_LIBRARYOBJECT_HPP

#include <htd/Globals.hpp>

#include <htd/LibraryInstance.hpp>

#include <memory>

namespace htd
{
    /**
     *  Abstract class for interaction with the management class of a library instance.
     */
    class LibraryObject
    {
        public:
            /**
             *  Constructor for a new library object.
             */
            LibraryObject(void);

            /**
             *  Constructor for a new library object.
             *
             *  @param[in] instance The management class for the new library object.
             */
            LibraryObject(const std::shared_ptr<htd::LibraryInstance> & instance);

            /**
             *  Destructor for a management instance.
             */
            ~LibraryObject();

            /**
             *  Check whether the library object has an associated management class.
             *
             *  @return True if the library object has an associated management class, false otherwise.
             */
            bool isManaged(void) const HTD_NOEXCEPT;

            /**
             *  Check whether running computations shall be aborted as soon as possible.
             *
             *  @return True if running computations shall be aborted as soon as possible, false otherwise.
             */
            bool isTerminated(void) const HTD_NOEXCEPT;

            /**
             *  Getter for the associated management class.
             *
             *  @return The associated management class.
             */
            const std::shared_ptr<htd::LibraryInstance> & managementInstance(void) const HTD_NOEXCEPT;

            /**
             *  Set a new management class for the library object.
             *
             *  @param[in] instance The new management class for the library object.
             */
            void setManagementInstance(const std::shared_ptr<htd::LibraryInstance> & instance);

        private:
            std::shared_ptr<htd::LibraryInstance> instance_;
    };
}

#endif /* HTD_HTD_LIBRARYOBJECT_HPP */
