/*
 * File:   LibraryInstance.hpp
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

#ifndef HTD_HTD_LIBRARYINSTANCE_HPP
#define HTD_HTD_LIBRARYINSTANCE_HPP

#include <htd/Id.hpp>

#include <functional>
#include <map>
#include <memory>

namespace htd
{
    /**
     *  Central management class of a library instance.
     */
    class HTD_API LibraryInstance
    {
        public:
            /**
             *  Constructor for a new management instance.
             */
            LibraryInstance(htd::id_t id);

            /**
             *  Destructor for a management instance.
             */
            ~LibraryInstance();

            /**
             *  Getter for the ID of the management instance.
             *
             *  @return The ID of the management instance.
             */
            htd::id_t id(void) const;

            /**
             *  Check whether the terminate(int) function was called.
             *
             *  @return True if the terminate(int) function was called, false otherwise.
             */
            bool isTerminated(void) const;

            /**
             *  Send a termination signal to running algorithms of the library to allow them freeing allocated resources.
             *
             *  This call will pass the SIGTERM signal to each of the registered signal
             *  handlers and algorithms still running may decide to terminate gracefully.
             *
             *  @note After calling this method, no further algorithms from the library associated
             *  with the current library instance shall be run until the reset() method is called,
             *  otherwise the outcome of the algorithms is undefined!
             */
            void terminate(void);

            /**
             *  Reset the current management instance.
             *
             *  Calling this method sets the value of isTerminated() back to false.
             *  This allows to re-run the library's algorithms after terminate()
             *  was called.
             */
            void reset(void);

            /**
             *  Register a new signal handler.
             *
             *  @param[in] handler  A callback function which shall be called on arrival of a new signal.
             *
             *  @return The ID of the new signal handler.
             */
            htd::id_t registerSignalHandler(const std::function<void(int)> & handler);

            /**
             *  Unregister an existing signal handler.
             *
             *  @param[in] handlerId    The ID of the signal handler which shall be removed.
             */
            void unregisterSignalHandler(htd::id_t handlerId);
            
        private:
            htd::id_t id_;

            htd::id_t nextHandlerId_;

            bool terminated_;

            std::map<htd::id_t, std::function<void(int)>> signalHandlers_;
    };
}

#endif /* HTD_HTD_LIBRARYINSTANCE_HPP */
