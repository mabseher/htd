/*
 * File:   LabeledDirectedMultiGraphFactory.hpp
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

#ifndef HTD_HTD_LABELEDDIRECTEDMULTIGRAPHFACTORY_HPP
#define HTD_HTD_LABELEDDIRECTEDMULTIGRAPHFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableLabeledDirectedMultiGraph.hpp>

namespace htd
{
    /**
     *  Factory class for the default implementation of the IMutableLabeledDirectedMultiGraph interface.
     */
    class LabeledDirectedMultiGraphFactory
    {
        public:
            /**
             *  Destructor of the factory class.
             */
            ~LabeledDirectedMultiGraphFactory();

            /**
             *  Access the singleton instance of the factory class.
             *
             *  @return The singleton instance of the factory class.
             */
            static LabeledDirectedMultiGraphFactory & instance(void);

            /**
             *  Create a new IMutableLabeledDirectedMultiGraph object.
             *
             *  @return A new IMutableLabeledDirectedMultiGraph object.
             */
            htd::IMutableLabeledDirectedMultiGraph * getLabeledDirectedMultiGraph(void);

            /**
             *  Create a new IMutableLabeledDirectedMultiGraph object.
             *
             *  @param[in] initialSize  The initial size of the created graph.
             *
             *  @return A new IMutableLabeledDirectedMultiGraph object of the given size.
             */
            htd::IMutableLabeledDirectedMultiGraph * getLabeledDirectedMultiGraph(std::size_t initialSize);

            /**
             *  Create a new IMutableLabeledDirectedMultiGraph object.
             *
             *  @param[in] original The original labeled directed multi-graph acting as template for the created graph.
             *
             *  @return A new IMutableLabeledDirectedMultiGraph object identical to the given original graph.
             */
            htd::IMutableLabeledDirectedMultiGraph * getLabeledDirectedMultiGraph(const htd::ILabeledDirectedMultiGraph & original);

            /**
             *  Set the default implementation of the IMutableLabeledDirectedMultiGraph interface.
             *
             *  @param[in] original The new default implementation of the IMutableLabeledDirectedMultiGraph interface.
             */
            void setConstructionTemplate(htd::IMutableLabeledDirectedMultiGraph * original);

            /**
             *  Access the mutable interface of a given labeled directed multi-graph.
             *
             *  @return The mutable interface of the given labeled directed multi-graph.
             */
            htd::IMutableLabeledDirectedMultiGraph & accessMutableLabeledDirectedMultiGraph(htd::ILabeledDirectedMultiGraph & original);

            /**
             *  Access the mutable interface of a given labeled directed multi-graph.
             *
             *  @return The mutable interface of the given labeled directed multi-graph.
             */
            const htd::IMutableLabeledDirectedMultiGraph & accessMutableLabeledDirectedMultiGraph(const htd::ILabeledDirectedMultiGraph & original);

        private:
            /**
             *  A pointer to a clean instance of the default implementation.
             */
            htd::IMutableLabeledDirectedMultiGraph * constructionTemplate_;

            /**
             *  Constructor for the factory class.
             *
             *  @note This constructor is private to prevent creating multiple instances of the factory.
             */
            LabeledDirectedMultiGraphFactory(void);

            /**
             *  Copy constructor for the factory class.
             *
             *  @note This constructor is private to prevent creating multiple instances of the factory.
             */
            LabeledDirectedMultiGraphFactory(const LabeledDirectedMultiGraphFactory & original);

            /**
             *  Copy assignment operator for the factory class.
             *
             *  @note This operator is private to prevent assignments to the factory class.
             */
            LabeledDirectedMultiGraphFactory & operator=(const LabeledDirectedMultiGraphFactory & original);
    };
}

#endif /* HTD_HTD_LABELEDDIRECTEDMULTIGRAPHFACTORY_HPP */
