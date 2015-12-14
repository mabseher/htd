/*
 * File:   DirectedGraphFactory.hpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 *
 * Copyright 2015, Michael Abseher
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

#ifndef HTD_DIRECTEDGRAPHFACTORY_HPP
#define HTD_DIRECTEDGRAPHFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableDirectedGraph.hpp>

namespace htd
{
    class DirectedGraphFactory
    {
        public:
            ~DirectedGraphFactory();

            static DirectedGraphFactory & instance(void);

            htd::IMutableDirectedGraph * getDirectedGraph(void);

            void setConstructionTemplate(htd::IMutableDirectedGraph * original);

        private:
            htd::IMutableDirectedGraph * constructionTemplate_;

            DirectedGraphFactory(void);

            DirectedGraphFactory(const DirectedGraphFactory & original);

            DirectedGraphFactory & operator =(const DirectedGraphFactory & original);
    };
}

#endif /* HTD_DIRECTEDGRAPHFACTORY_HPP */
