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
    /**
     *  Factory class for the default implementation of the IMutableLabeledGraph interface.
     */
    class LabeledGraphFactory
    {
        public:
            /**
             *  Constructor for the factory class.
             */
            HTD_API LabeledGraphFactory(const htd::LibraryInstance * const manager);

            /**
             *  Copy constructor for the factory class.
             */
            HTD_API LabeledGraphFactory(const LabeledGraphFactory & original);

            /**
             *  Copy assignment operator for the factory class.
             */
            HTD_API LabeledGraphFactory & operator=(const LabeledGraphFactory & original);

            /**
             *  Destructor of the factory class.
             */
            HTD_API virtual ~LabeledGraphFactory();

            /**
             *  Create a new IMutableLabeledGraph object.
             *
             *  @return A new IMutableLabeledGraph object.
             */
            HTD_API htd::IMutableLabeledGraph * getLabeledGraph(void) const;

            /**
             *  Create a new IMutableLabeledGraph object.
             *
             *  @param[in] initialSize  The initial size of the created graph.
             *
             *  @return A new IMutableLabeledGraph object of the given size.
             */
            HTD_API htd::IMutableLabeledGraph * getLabeledGraph(std::size_t initialSize) const;

            /**
             *  Create a new IMutableLabeledGraph object.
             *
             *  @param[in] original The original labeled graph acting as template for the created graph.
             *
             *  @return A new IMutableLabeledGraph object identical to the given original graph.
             */
            HTD_API htd::IMutableLabeledGraph * getLabeledGraph(const htd::ILabeledGraph & original) const;

            /**
             *  Create a new IMutableLabeledGraph object.
             *
             *  @param[in] original The original labeled multi-graph acting as template for the created graph.
             *
             *  @return A new IMutableLabeledGraph object identical to the given original graph.
             */
            HTD_API htd::IMutableLabeledGraph * getLabeledGraph(const htd::ILabeledMultiGraph & original) const;

            /**
             *  Set the default implementation of the IMutableLabeledGraph interface.
             *
             *  @note When calling this method the control over the memory regions of the object instance of the original implementation
             *  is transferred to the factory class. Deleting the object instance provided to this method outside the factory class or
             *  assigning the same object instance multiple times will lead to undefined behavior.
             *
             *  @param[in] original The new default implementation of the IMutableLabeledGraph interface.
             */
            HTD_API void setConstructionTemplate(htd::IMutableLabeledGraph * original);

            /**
             *  Access the mutable interface of a given labeled graph.
             *
             *  @return The mutable interface of the given labeled graph.
             */
            HTD_API htd::IMutableLabeledGraph & accessMutableLabeledGraph(htd::ILabeledGraph & original) const;

            /**
             *  Access the mutable interface of a given labeled graph.
             *
             *  @return The mutable interface of the given labeled graph.
             */
            HTD_API const htd::IMutableLabeledGraph & accessMutableLabeledGraph(const htd::ILabeledGraph & original) const;

        private:
            /**
             *  A pointer to a clean instance of the default implementation.
             */
            htd::IMutableLabeledGraph * constructionTemplate_;
    };
}

#endif /* HTD_HTD_LABELEDGRAPHFACTORY_HPP */
