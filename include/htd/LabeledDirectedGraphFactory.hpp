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

            /**
             *  Create a new IMutableLabeledDirectedGraph object.
             *
             *  @return A new IMutableLabeledDirectedGraph object.
             */
            htd::IMutableLabeledDirectedGraph * getLabeledDirectedGraph(void);

            /**
             *  Create a new IMutableLabeledDirectedGraph object.
             *
             *  @param[in] initialSize  The initial size of the created graph.
             *
             *  @return A new IMutableLabeledDirectedGraph object of the given size.
             */
            htd::IMutableLabeledDirectedGraph * getLabeledDirectedGraph(std::size_t initialSize);

            /**
             *  Create a new IMutableLabeledDirectedGraph object.
             *
             *  @param[in] original The original labeled directed graph acting as template for the created graph.
             *
             *  @return A new IMutableLabeledDirectedGraph object identical to the given original graph.
             */
            htd::IMutableLabeledDirectedGraph * getLabeledDirectedGraph(const htd::ILabeledDirectedGraph & original);

            /**
             *  Create a new IMutableLabeledDirectedGraph object.
             *
             *  @param[in] original The original labeled directed multi-graph acting as template for the created graph.
             *
             *  @return A new IMutableLabeledDirectedGraph object identical to the given original graph.
             */
            htd::IMutableLabeledDirectedGraph * getLabeledDirectedGraph(const htd::ILabeledDirectedMultiGraph & original);

            /**
             *  Set the default implementation of the IMutableLabeledDirectedGraph interface.
             *
             *  @param[in] original The new default implementation of the IMutableLabeledDirectedGraph interface.
             */
            void setConstructionTemplate(htd::IMutableLabeledDirectedGraph * original);

            /**
             *  Access the mutable interface of a given labeled directed graph.
             *
             *  @return The mutable interface of the given labeled directed graph.
             */
            htd::IMutableLabeledDirectedGraph & accessMutableLabeledDirectedGraph(htd::ILabeledDirectedGraph & original);

            /**
             *  Access the mutable interface of a given labeled directed graph.
             *
             *  @return The mutable interface of the given labeled directed graph.
             */
            const htd::IMutableLabeledDirectedGraph & accessMutableLabeledDirectedGraph(const htd::ILabeledDirectedGraph & original);

        private:
            /**
             *  A pointer to a clean instance of the default implementation.
             */
            htd::IMutableLabeledDirectedGraph * constructionTemplate_;

            /**
             *  Constructor for the factory class.
             *
             *  @note This constructor is private to prevent creating multiple instances of the factory.
             */
            LabeledDirectedGraphFactory(void);

            /**
             *  Copy constructor for the factory class.
             *
             *  @note This constructor is private to prevent creating multiple instances of the factory.
             */
            LabeledDirectedGraphFactory(const LabeledDirectedGraphFactory & original);

            /**
             *  Copy assignment operator for the factory class.
             *
             *  @note This operator is private to prevent assignments to the factory class.
             */
            LabeledDirectedGraphFactory & operator=(const LabeledDirectedGraphFactory & original);
    };
}

#endif /* HTD_HTD_LABELEDDIRECTEDGRAPHFACTORY_HPP */
