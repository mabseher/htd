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
             *  Constructor for the factory class.
             */
            HTD_API LabeledDirectedMultiGraphFactory(const htd::LibraryInstance * const manager);

            /**
             *  Copy constructor for the factory class.
             *
             *  @param[in] original The original factory class which shall be copied.
             */
            HTD_API LabeledDirectedMultiGraphFactory(const LabeledDirectedMultiGraphFactory & original);

            /**
             *  Copy assignment operator for the factory class.
             *
             *  @param[in] original The original factory class which shall be copied.
             */
            HTD_API LabeledDirectedMultiGraphFactory & operator=(const LabeledDirectedMultiGraphFactory & original);

            /**
             *  Destructor of the factory class.
             */
            HTD_API virtual ~LabeledDirectedMultiGraphFactory();

            /**
             *  Create a new IMutableLabeledDirectedMultiGraph object.
             *
             *  @return A new IMutableLabeledDirectedMultiGraph object.
             */
            HTD_API htd::IMutableLabeledDirectedMultiGraph * getLabeledDirectedMultiGraph(void) const;

            /**
             *  Create a new IMutableLabeledDirectedMultiGraph object.
             *
             *  @param[in] initialSize  The initial size of the created graph.
             *
             *  @return A new IMutableLabeledDirectedMultiGraph object of the given size.
             */
            HTD_API htd::IMutableLabeledDirectedMultiGraph * getLabeledDirectedMultiGraph(std::size_t initialSize) const;

            /**
             *  Create a new IMutableLabeledDirectedMultiGraph object.
             *
             *  @param[in] original The original labeled directed multi-graph acting as template for the created graph.
             *
             *  @return A new IMutableLabeledDirectedMultiGraph object identical to the given original graph.
             */
            HTD_API htd::IMutableLabeledDirectedMultiGraph * getLabeledDirectedMultiGraph(const htd::ILabeledDirectedMultiGraph & original) const;

            /**
             *  Set the default implementation of the IMutableLabeledDirectedMultiGraph interface.
             *
             *  @note When calling this method the control over the memory regions of the object instance of the original implementation
             *  is transferred to the factory class. Deleting the object instance provided to this method outside the factory class or
             *  assigning the same object instance multiple times will lead to undefined behavior.
             *
             *  @param[in] original The new default implementation of the IMutableLabeledDirectedMultiGraph interface.
             */
            HTD_API void setConstructionTemplate(htd::IMutableLabeledDirectedMultiGraph * original);

            /**
             *  Access the mutable interface of a given labeled directed multi-graph.
             *
             *  @return The mutable interface of the given labeled directed multi-graph.
             */
            HTD_API htd::IMutableLabeledDirectedMultiGraph & accessMutableLabeledDirectedMultiGraph(htd::ILabeledDirectedMultiGraph & original) const;

            /**
             *  Access the mutable interface of a given labeled directed multi-graph.
             *
             *  @return The mutable interface of the given labeled directed multi-graph.
             */
            HTD_API const htd::IMutableLabeledDirectedMultiGraph & accessMutableLabeledDirectedMultiGraph(const htd::ILabeledDirectedMultiGraph & original) const;

        private:
            /**
             *  A pointer to a clean instance of the default implementation.
             */
            htd::IMutableLabeledDirectedMultiGraph * constructionTemplate_;
    };
}

#endif /* HTD_HTD_LABELEDDIRECTEDMULTIGRAPHFACTORY_HPP */
