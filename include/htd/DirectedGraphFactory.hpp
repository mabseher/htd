/*
 * File:   DirectedGraphFactory.hpp
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

#ifndef HTD_HTD_DIRECTEDGRAPHFACTORY_HPP
#define HTD_HTD_DIRECTEDGRAPHFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableDirectedGraph.hpp>

namespace htd
{
    class DirectedGraphFactory
    {
        public:
            /**
             *  Destructor of the factory class.
             */
            ~DirectedGraphFactory();

            /**
             *  Access the singleton instance of the factory class.
             *
             *  @return The singleton instance of the factory class.
             */
            static DirectedGraphFactory & instance(void);

            htd::IMutableDirectedGraph * getDirectedGraph(void);

            htd::IMutableDirectedGraph * getDirectedGraph(std::size_t initialSize);

            htd::IMutableDirectedGraph * getDirectedGraph(const htd::IDirectedGraph & original);

            htd::IMutableDirectedGraph * getDirectedGraph(const htd::IDirectedMultiGraph & original);

            void setConstructionTemplate(htd::IMutableDirectedGraph * original);

            htd::IMutableDirectedGraph & accessMutableDirectedGraph(htd::IDirectedGraph & original);

            const htd::IMutableDirectedGraph & accessMutableDirectedGraph(const htd::IDirectedGraph & original);

        private:
            htd::IMutableDirectedGraph * constructionTemplate_;

            DirectedGraphFactory(void);

            DirectedGraphFactory(const DirectedGraphFactory & original);

            DirectedGraphFactory & operator=(const DirectedGraphFactory & original);
    };
}

#endif /* HTD_HTD_DIRECTEDGRAPHFACTORY_HPP */
