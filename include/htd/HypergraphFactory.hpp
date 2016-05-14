/*
 * File:   HypergraphFactory.hpp
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

#ifndef HTD_HTD_HYPERGRAPHFACTORY_HPP
#define HTD_HTD_HYPERGRAPHFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableHypergraph.hpp>

namespace htd
{
    /**
     *  Factory class for the default implementation of the IMutableHypergraph interface.
     */
    class HypergraphFactory
    {
        public:
            /**
             *  Destructor of the factory class.
             */
            ~HypergraphFactory();

            /**
             *  Access the singleton instance of the factory class.
             *
             *  @return The singleton instance of the factory class.
             */
            static HypergraphFactory & instance(void);

            htd::IMutableHypergraph * getHypergraph(void);

            htd::IMutableHypergraph * getHypergraph(std::size_t initialSize);

            htd::IMutableHypergraph * getHypergraph(const htd::IHypergraph & original);

            htd::IMutableHypergraph * getHypergraph(const htd::IMultiHypergraph & original);

            void setConstructionTemplate(htd::IMutableHypergraph * original);

            htd::IMutableHypergraph & accessMutableHypergraph(htd::IHypergraph & original);

            const htd::IMutableHypergraph & accessMutableHypergraph(const htd::IHypergraph & original);

        private:
            htd::IMutableHypergraph * constructionTemplate_;

            HypergraphFactory(void);

            HypergraphFactory(const HypergraphFactory & original);

            HypergraphFactory & operator=(const HypergraphFactory & original);
    };
}

#endif /* HTD_HTD_HYPERGRAPHFACTORY_HPP */
