/*
 * File:   MultiGraphFactory.hpp
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

#ifndef HTD_HTD_MULTIGRAPHFACTORY_HPP
#define HTD_HTD_MULTIGRAPHFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableMultiGraph.hpp>

namespace htd
{
    /**
     *  Factory class for the default implementation of the IMutableMultiGraph interface.
     */
    class MultiGraphFactory
    {
        public:
            /**
             *  Destructor of the factory class.
             */
            ~MultiGraphFactory();

            /**
             *  Access the singleton instance of the factory class.
             *
             *  @return The singleton instance of the factory class.
             */
            static MultiGraphFactory & instance(void);

            htd::IMutableMultiGraph * getMultiGraph(void);

            htd::IMutableMultiGraph * getMultiGraph(std::size_t initialSize);

            htd::IMutableMultiGraph * getMultiGraph(const htd::IMultiGraph & original);

            void setConstructionTemplate(htd::IMutableMultiGraph * original);

            htd::IMutableMultiGraph & accessMutableMultiGraph(htd::IMultiGraph & original);

            const htd::IMutableMultiGraph & accessMutableMultiGraph(const htd::IMultiGraph & original);

        private:
            htd::IMutableMultiGraph * constructionTemplate_;

            MultiGraphFactory(void);

            MultiGraphFactory(const MultiGraphFactory & original);

            MultiGraphFactory & operator=(const MultiGraphFactory & original);
    };
}

#endif /* HTD_HTD_MULTIGRAPHFACTORY_HPP */
