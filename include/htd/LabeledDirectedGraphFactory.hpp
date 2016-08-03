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
             *  Constructor for the factory class.
             */
            HTD_API LabeledDirectedGraphFactory(const htd::LibraryInstance * const manager);

            /**
             *  Copy constructor for the factory class.
             */
            HTD_API LabeledDirectedGraphFactory(const LabeledDirectedGraphFactory & original);

            /**
             *  Copy assignment operator for the factory class.
             */
            HTD_API LabeledDirectedGraphFactory & operator=(const LabeledDirectedGraphFactory & original);

            /**
             *  Destructor of the factory class.
             */
            HTD_API virtual ~LabeledDirectedGraphFactory();

            /**
             *  Create a new IMutableLabeledDirectedGraph object.
             *
             *  @return A new IMutableLabeledDirectedGraph object.
             */
            HTD_API htd::IMutableLabeledDirectedGraph * getLabeledDirectedGraph(void) const;

            /**
             *  Create a new IMutableLabeledDirectedGraph object.
             *
             *  @param[in] initialSize  The initial size of the created graph.
             *
             *  @return A new IMutableLabeledDirectedGraph object of the given size.
             */
            HTD_API htd::IMutableLabeledDirectedGraph * getLabeledDirectedGraph(std::size_t initialSize) const;

            /**
             *  Create a new IMutableLabeledDirectedGraph object.
             *
             *  @param[in] original The original labeled directed graph acting as template for the created graph.
             *
             *  @return A new IMutableLabeledDirectedGraph object identical to the given original graph.
             */
            HTD_API htd::IMutableLabeledDirectedGraph * getLabeledDirectedGraph(const htd::ILabeledDirectedGraph & original) const;

            /**
             *  Create a new IMutableLabeledDirectedGraph object.
             *
             *  @param[in] original The original labeled directed multi-graph acting as template for the created graph.
             *
             *  @return A new IMutableLabeledDirectedGraph object identical to the given original graph.
             */
            HTD_API htd::IMutableLabeledDirectedGraph * getLabeledDirectedGraph(const htd::ILabeledDirectedMultiGraph & original) const;

            /**
             *  Set the default implementation of the IMutableLabeledDirectedGraph interface.
             *
             *  @note When calling this method the control over the memory regions of the object instance of the original implementation
             *  is transferred to the factory class. Deleting the object instance provided to this method outside the factory class or
             *  assigning the same object instance multiple times will lead to undefined behavior.
             *
             *  @param[in] original The new default implementation of the IMutableLabeledDirectedGraph interface.
             */
            HTD_API void setConstructionTemplate(htd::IMutableLabeledDirectedGraph * original);

            /**
             *  Access the mutable interface of a given labeled directed graph.
             *
             *  @return The mutable interface of the given labeled directed graph.
             */
            HTD_API htd::IMutableLabeledDirectedGraph & accessMutableLabeledDirectedGraph(htd::ILabeledDirectedGraph & original) const;

            /**
             *  Access the mutable interface of a given labeled directed graph.
             *
             *  @return The mutable interface of the given labeled directed graph.
             */
            HTD_API const htd::IMutableLabeledDirectedGraph & accessMutableLabeledDirectedGraph(const htd::ILabeledDirectedGraph & original) const;

        private:
            /**
             *  A pointer to a clean instance of the default implementation.
             */
            htd::IMutableLabeledDirectedGraph * constructionTemplate_;
    };
}

#endif /* HTD_HTD_LABELEDDIRECTEDGRAPHFACTORY_HPP */
