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
    /**
     *  Factory class for the default implementation of the IMutableDirectedGraph interface.
     */
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

            /**
             *  Create a new IMutableDirectedGraph object.
             *
             *  @return A new IMutableDirectedGraph object.
             */
            htd::IMutableDirectedGraph * getDirectedGraph(void);

            /**
             *  Create a new IMutableDirectedGraph object.
             *
             *  @param[in] initialSize  The initial size of the created graph.
             *
             *  @return A new IMutableDirectedGraph object of the given size.
             */
            htd::IMutableDirectedGraph * getDirectedGraph(std::size_t initialSize);

            /**
             *  Create a new IMutableDirectedGraph object.
             *
             *  @param[in] original The original directed graph acting as template for the created graph.
             *
             *  @return A new IMutableDirectedGraph object identical to the given original graph.
             */
            htd::IMutableDirectedGraph * getDirectedGraph(const htd::IDirectedGraph & original);

            /**
             *  Create a new IMutableDirectedGraph object.
             *
             *  @param[in] original The original directed multi-graph acting as template for the created graph.
             *
             *  @return A new IMutableDirectedGraph object identical to the given original graph.
             */
            htd::IMutableDirectedGraph * getDirectedGraph(const htd::IDirectedMultiGraph & original);

            /**
             *  Set the default implementation of the IMutableDirectedGraph interface.
             *
             *  @param[in] original The new default implementation of the IMutableDirectedGraph interface.
             */
            void setConstructionTemplate(htd::IMutableDirectedGraph * original);

            /**
             *  Access the mutable interface of a given directed graph.
             *
             *  @return The mutable interface of the given directed graph.
             */
            htd::IMutableDirectedGraph & accessMutableDirectedGraph(htd::IDirectedGraph & original);

            /**
             *  Access the mutable interface of a given directed graph.
             *
             *  @return The mutable interface of the given directed graph.
             */
            const htd::IMutableDirectedGraph & accessMutableDirectedGraph(const htd::IDirectedGraph & original);

        private:
            /**
             *  A pointer to a clean instance of the default implementation.
             */
            htd::IMutableDirectedGraph * constructionTemplate_;

            DirectedGraphFactory(void);

            DirectedGraphFactory(const DirectedGraphFactory & original);

            DirectedGraphFactory & operator=(const DirectedGraphFactory & original);
    };
}

#endif /* HTD_HTD_DIRECTEDGRAPHFACTORY_HPP */
