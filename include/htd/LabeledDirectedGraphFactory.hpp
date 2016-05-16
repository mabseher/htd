/*
 * File:   LabeledDirectedGraphFactory.hpp
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

#ifndef HTD_HTD_LABELEDDIRECTEDGRAPHFACTORY_HPP
#define HTD_HTD_LABELEDDIRECTEDGRAPHFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableLabeledDirectedGraph.hpp>

namespace htd
{
    /**
     *  Factory class for the default implementation of the IMutableLabeledDirectedGraph interface.
     */
    class LabeledDirectedGraphFactory
    {
        public:
            /**
             *  Destructor of the factory class.
             */
            ~LabeledDirectedGraphFactory();

            /**
             *  Access the singleton instance of the factory class.
             *
             *  @return The singleton instance of the factory class.
             */
            static LabeledDirectedGraphFactory & instance(void);

            htd::IMutableLabeledDirectedGraph * getLabeledDirectedGraph(void);

            htd::IMutableLabeledDirectedGraph * getLabeledDirectedGraph(std::size_t initialSize);

            htd::IMutableLabeledDirectedGraph * getLabeledDirectedGraph(const htd::ILabeledDirectedGraph & original);

            htd::IMutableLabeledDirectedGraph * getLabeledDirectedGraph(const htd::ILabeledDirectedMultiGraph & original);

            /**
             *  Set the default implementation of the IMutableLabeledDirectedGraph interface.
             *
             *  @param[in] original The new default implementation of the IMutableLabeledDirectedGraph interface.
             */
            void setConstructionTemplate(htd::IMutableLabeledDirectedGraph * original);

            htd::IMutableLabeledDirectedGraph & accessMutableLabeledDirectedGraph(htd::ILabeledDirectedGraph & original);

            const htd::IMutableLabeledDirectedGraph & accessMutableLabeledDirectedGraph(const htd::ILabeledDirectedGraph & original);

        private:
            /**
             *  A pointer to a clean instance of the default implementation.
             */
            htd::IMutableLabeledDirectedGraph * constructionTemplate_;

            LabeledDirectedGraphFactory(void);

            LabeledDirectedGraphFactory(const LabeledDirectedGraphFactory & original);

            LabeledDirectedGraphFactory & operator=(const LabeledDirectedGraphFactory & original);
    };
}

#endif /* HTD_HTD_LABELEDDIRECTEDGRAPHFACTORY_HPP */
