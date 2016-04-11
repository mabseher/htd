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
    class Library
    {
        public:
            ~Library();

            static Library & instance(void);

            bool isAborted(void);

            void abort(int signal);
            
            void reset(void);

            htd::id_t registerSignalHandler(const std::function<void(int)> & handler);

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
