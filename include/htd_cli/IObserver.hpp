/*
 * File:   IObserver.hpp
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

#ifndef HTD_CLI_IOBSERVER_HPP
#define HTD_CLI_IOBSERVER_HPP

#include <htd_cli/PreprocessorDefinitions.hpp>

namespace htd_cli
{
    /**
     *  Interface for observers which can be used in the context of the class htd::OptionManager.
     */
    class IObserver
    {
        public:
            virtual ~IObserver() = 0;

            /**
             *  Notify the observer instance.
             */
            virtual void notify(void) = 0;
    };

    inline htd_cli::IObserver::~IObserver() { }
}

#endif /* HTD_CLI_IOBSERVER_HPP */
