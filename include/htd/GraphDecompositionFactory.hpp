/*
 * File:   GraphDecompositionFactory.hpp
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

#ifndef HTD_HTD_GRAPHDECOMPOSITIONFACTORY_HPP
#define HTD_HTD_GRAPHDECOMPOSITIONFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableGraphDecomposition.hpp>
#include <htd/IGraphDecomposition.hpp>

namespace htd
{
    class GraphDecompositionFactory
    {
        public:
            ~GraphDecompositionFactory();

            static GraphDecompositionFactory & instance(void);

            htd::IMutableGraphDecomposition * getGraphDecomposition(void);

            htd::IMutableGraphDecomposition * getGraphDecomposition(const htd::IGraphDecomposition & original);

            void setConstructionTemplate(htd::IMutableGraphDecomposition * original);

            htd::IMutableGraphDecomposition & accessMutableGraphDecomposition(htd::IGraphDecomposition & original);

            const htd::IMutableGraphDecomposition & accessMutableGraphDecomposition(const htd::IGraphDecomposition & original);

        private:
            htd::IMutableGraphDecomposition * constructionTemplate_;

            GraphDecompositionFactory(void);

            GraphDecompositionFactory(const GraphDecompositionFactory & original);

            GraphDecompositionFactory & operator=(const GraphDecompositionFactory & original);
    };
}

#endif /* HTD_HTD_GRAPHDECOMPOSITIONFACTORY_HPP */
