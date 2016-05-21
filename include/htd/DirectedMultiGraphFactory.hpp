/*
 * File:   DirectedMultiGraphFactory.hpp
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

#ifndef HTD_HTD_DIRECTEDMULTIGRAPHFACTORY_HPP
#define HTD_HTD_DIRECTEDMULTIGRAPHFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableDirectedMultiGraph.hpp>

namespace htd
{
    /**
     *  Factory class for the default implementation of the IMutableDirectedMultiGraph interface.
     */
    class DirectedMultiGraphFactory
    {
        public:
            /**
             *  Destructor of the factory class.
             */
            ~DirectedMultiGraphFactory();

            /**
             *  Access the singleton instance of the factory class.
             *
             *  @return The singleton instance of the factory class.
             */
            static DirectedMultiGraphFactory & instance(void);

            /**
             *  Create a new IMutableDirectedMultiGraph object.
             *
             *  @return A new IMutableDirectedMultiGraph object.
             */
            htd::IMutableDirectedMultiGraph * getDirectedMultiGraph(void);

            /**
             *  Create a new IMutableDirectedMultiGraph object.
             *
             *  @param[in] initialSize  The initial size of the created graph.
             *
             *  @return A new IMutableDirectedMultiGraph object of the given size.
             */
            htd::IMutableDirectedMultiGraph * getDirectedMultiGraph(std::size_t initialSize);

            /**
             *  Create a new IMutableDirectedMultiGraph object.
             *
             *  @param[in] original The original directed multi-graph acting as template for the created graph.
             *
             *  @return A new IMutableDirectedMultiGraph object identical to the given original graph.
             */
            htd::IMutableDirectedMultiGraph * getDirectedMultiGraph(const htd::IDirectedMultiGraph & original);

            /**
             *  Set the default implementation of the IMutableDirectedMultiGraph interface.
             *
             *  @param[in] original The new default implementation of the IMutableDirectedMultiGraph interface.
             */
            void setConstructionTemplate(htd::IMutableDirectedMultiGraph * original);

            /**
             *  Access the mutable interface of a given directed multi-graph.
             *
             *  @return The mutable interface of the given directed multi-graph.
             */
            htd::IMutableDirectedMultiGraph & accessMutableDirectedMultiGraph(htd::IDirectedMultiGraph & original);

            /**
             *  Access the mutable interface of a given directed multi-graph.
             *
             *  @return The mutable interface of the given directed multi-graph.
             */
            const htd::IMutableDirectedMultiGraph & accessMutableDirectedMultiGraph(const htd::IDirectedMultiGraph & original);

        private:
            /**
             *  A pointer to a clean instance of the default implementation.
             */
            htd::IMutableDirectedMultiGraph * constructionTemplate_;

            DirectedMultiGraphFactory(void);

            DirectedMultiGraphFactory(const DirectedMultiGraphFactory & original);

            DirectedMultiGraphFactory & operator=(const DirectedMultiGraphFactory & original);
    };
}

#endif /* HTD_HTD_DIRECTEDMULTIGRAPHFACTORY_HPP */
