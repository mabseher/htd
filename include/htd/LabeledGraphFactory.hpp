/*
 * File:   LabeledGraphFactory.hpp
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

#ifndef HTD_HTD_LABELEDGRAPHFACTORY_HPP
#define HTD_HTD_LABELEDGRAPHFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableLabeledGraph.hpp>

namespace htd
{
    class LabeledGraphFactory
    {
        public:
            ~LabeledGraphFactory();

            static LabeledGraphFactory & instance(void);

            htd::IMutableLabeledGraph * getLabeledGraph(void);

            htd::IMutableLabeledGraph * getLabeledGraph(std::size_t initialSize);

            htd::IMutableLabeledGraph * getLabeledGraph(const htd::ILabeledGraph & original);

            void setConstructionTemplate(htd::IMutableLabeledGraph * original);

            htd::IMutableLabeledGraph & accessMutableLabeledGraph(htd::ILabeledGraph & original);

            const htd::IMutableLabeledGraph & accessMutableLabeledGraph(const htd::ILabeledGraph & original);

        private:
            htd::IMutableLabeledGraph * constructionTemplate_;

            LabeledGraphFactory(void);

            LabeledGraphFactory(const LabeledGraphFactory & original);

            LabeledGraphFactory & operator=(const LabeledGraphFactory & original);
    };
}

#endif /* HTD_HTD_LABELEDGRAPHFACTORY_HPP */
