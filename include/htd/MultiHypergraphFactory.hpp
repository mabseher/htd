/*
 * File:   MultiHypergraphFactory.hpp
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

#ifndef HTD_HTD_MULTIHYPERGRAPHFACTORY_HPP
#define HTD_HTD_MULTIHYPERGRAPHFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableMultiHypergraph.hpp>

namespace htd
{
    class MultiHypergraphFactory
    {
        public:
            ~MultiHypergraphFactory();

            static MultiHypergraphFactory & instance(void);

            htd::IMutableMultiHypergraph * getMultiHypergraph(void);

            htd::IMutableMultiHypergraph * getMultiHypergraph(std::size_t initialSize);

            htd::IMutableMultiHypergraph * getMultiHypergraph(const htd::IMultiHypergraph & original);

            void setConstructionTemplate(htd::IMutableMultiHypergraph * original);

            htd::IMutableMultiHypergraph & accessMutableMultiHypergraph(htd::IMultiHypergraph & original);

            const htd::IMutableMultiHypergraph & accessMutableMultiHypergraph(const htd::IMultiHypergraph & original);

        private:
            htd::IMutableMultiHypergraph * constructionTemplate_;

            MultiHypergraphFactory(void);

            MultiHypergraphFactory(const MultiHypergraphFactory & original);

            MultiHypergraphFactory & operator=(const MultiHypergraphFactory & original);
    };
}

#endif /* HTD_HTD_MULTIHYPERGRAPHFACTORY_HPP */
