/*
 * File:   Library.hpp
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

#ifndef HTD_HTD_LIBRARY_HPP
#define HTD_HTD_LIBRARY_HPP

#include <htd/Globals.hpp>

#include <htd/LibraryInstance.hpp>

#include <functional>
#include <map>
#include <memory>
#include <unordered_map>

namespace htd
{
    /**
     *  Central management class of the library.
     */
    class HTD_API Library
    {
        public:
            ~Library();

            /**
             *  Access the singleton instance of the central management class.
             *
             *  @return The singleton instance of the central management class.
             */
            static Library & instance(void) HTD_NOEXCEPT;

            /**
             *  Send a termination signal to all management instances.
             *
             *  The management instances will pass the SIGTERM signal to each of their registered
             *  signal handlers and algorithms still running may decide to terminate gracefully
             *  when the corresponding management instance is terminated.
             *
             *  @note After calling this method, no further algorithms from the library shall be
             *  run until the reset() method is called, otherwise the outcome of the algorithms
             *  is undefined!
             */
            void terminate(void) HTD_NOEXCEPT;

            /**
             *  Reset all management instances.
             *
             *  Calling this method sets the value of htd::LibraryInstance::isTerminated() for each
             *  management instance created via this central management class back to false. This
             *  allows to re-run the library's algorithms after terminate() was called.
             */
            void reset(void) HTD_NOEXCEPT;

            /**
             *  Create a new management instance.
             *
             *  @return A shared pointer to a new management instance.
             */
            std::shared_ptr<htd::LibraryInstance> createManagementInstance(void);

            /**
             *  Removes an existing management instance.
             *
             *  @note This method calls the htd::LibraryInstance::terminate(void) method for the given management instance.
             *
             *  @param[in] id   The ID of the management instance which shall be removed.
             */
            void removeManagementInstance(htd::id_t id);

        private:
            htd::id_t nextInstanceId_;

            std::unordered_map<htd::id_t, std::shared_ptr<htd::LibraryInstance>> managementInstances_;

            Library(void);

            Library(const Library & original);

            Library & operator=(const Library & original);
    };
}

#endif /* HTD_HTD_LIBRARY_HPP */
