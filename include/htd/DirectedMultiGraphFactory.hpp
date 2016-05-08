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

            htd::IMutableDirectedMultiGraph * getDirectedMultiGraph(void);

            htd::IMutableDirectedMultiGraph * getDirectedMultiGraph(std::size_t initialSize);

            htd::IMutableDirectedMultiGraph * getDirectedMultiGraph(const htd::IDirectedMultiGraph & original);

            void setConstructionTemplate(htd::IMutableDirectedMultiGraph * original);

            htd::IMutableDirectedMultiGraph & accessMutableDirectedMultiGraph(htd::IDirectedMultiGraph & original);

            const htd::IMutableDirectedMultiGraph & accessMutableDirectedMultiGraph(const htd::IDirectedMultiGraph & original);

        private:
            htd::IMutableDirectedMultiGraph * constructionTemplate_;

            DirectedMultiGraphFactory(void);

            DirectedMultiGraphFactory(const DirectedMultiGraphFactory & original);

            DirectedMultiGraphFactory & operator=(const DirectedMultiGraphFactory & original);
    };
}

#endif /* HTD_HTD_DIRECTEDMULTIGRAPHFACTORY_HPP */
