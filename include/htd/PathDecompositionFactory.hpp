/*
 * File:   PathDecompositionFactory.hpp
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

#ifndef HTD_PATHDECOMPOSITIONFACTORY_HPP
#define HTD_PATHDECOMPOSITIONFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IMutablePathDecomposition.hpp>
#include <htd/IPathDecomposition.hpp>

namespace htd
{
    class PathDecompositionFactory
    {
        public:
            ~PathDecompositionFactory();

            static PathDecompositionFactory & instance(void);

            htd::IMutablePathDecomposition * getPathDecomposition(void);

            htd::IMutablePathDecomposition * getPathDecomposition(const htd::IPathDecomposition & original);

            void setConstructionTemplate(htd::IMutablePathDecomposition * original);

            htd::IMutablePathDecomposition & accessMutablePathDecomposition(htd::IPathDecomposition & original);

            const htd::IMutablePathDecomposition & accessMutablePathDecomposition(const htd::IPathDecomposition & original);

        private:
            htd::IMutablePathDecomposition * constructionTemplate_;

            PathDecompositionFactory(void);

            PathDecompositionFactory(const PathDecompositionFactory & original);

            PathDecompositionFactory & operator=(const PathDecompositionFactory & original);
    };
}

#endif /* HTD_PATHDECOMPOSITIONFACTORY_HPP */
