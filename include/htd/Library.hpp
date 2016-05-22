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

#include <functional>
#include <map>
#include <memory>

namespace htd
{
    /**
     *  Central management class of the library.
     */
    class Library
    {
        public:
            ~Library();

            /**
             *  Access the singleton instance of the management class.
             *
             *  @return The singleton instance of the management class.
             */
            static Library & instance(void);

            /**
             *  Check whether the abort() function was called.
             *
             *  @return True if the abort() function was called, false otherwise.
             */
            bool isAborted(void);

            /**
             *  Send a termination signal to running algorithms of the library to allow them freeing allocated resources before termination.
             *
             *  @param[in] signal   The signal which shall be sent to each signal handler.
             */
            void abort(int signal);
            
            /**
             *  Reset the library, i.e. to re-initialize it after the abort() method was called.
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
            bool aborted_;

            htd::id_t nextHandlerId_;

            std::map<htd::id_t, std::function<void(int)>> signalHandlers_;

            Library(void);

            Library(const Library & original);

            Library & operator=(const Library & original);
    };
}

#endif /* HTD_HTD_LIBRARY_HPP */
