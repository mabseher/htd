/*
 * File:   HypergraphFactory.hpp
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

#ifndef HTD_HYPERGRAPHFACTORY_HPP
#define HTD_HYPERGRAPHFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableHypergraph.hpp>

namespace htd
{
    class HypergraphFactory
    {
        public:
            ~HypergraphFactory();

            static HypergraphFactory & instance(void);

            htd::IMutableHypergraph * getHypergraph(void);

            void setConstructionTemplate(htd::IMutableHypergraph * original);

        private:
            htd::IMutableHypergraph * constructionTemplate_;

            HypergraphFactory(void);

            HypergraphFactory(const HypergraphFactory & original);

            HypergraphFactory & operator =(const HypergraphFactory & original);
    };
}

#endif /* HTD_HYPERGRAPHFACTORY_HPP */
