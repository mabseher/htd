/*
 * File:   LabeledMultiGraphFactory.hpp
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

#ifndef HTD_HTD_LABELEDMULTIGRAPHFACTORY_HPP
#define HTD_HTD_LABELEDMULTIGRAPHFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableLabeledMultiGraph.hpp>

namespace htd
{
    /**
     *  Factory class for the default implementation of the IMutableLabeledMultiGraph interface.
     */
    class HTD_API LabeledMultiGraphFactory
    {
        public:
            /**
             *  Destructor of the factory class.
             */
            ~LabeledMultiGraphFactory();

            /**
             *  Access the singleton instance of the factory class.
             *
             *  @return The singleton instance of the factory class.
             */
            static LabeledMultiGraphFactory & instance(void);

            /**
             *  Create a new IMutableLabeledMultiGraph object.
             *
             *  @return A new IMutableLabeledMultiGraph object.
             */
            htd::IMutableLabeledMultiGraph * getLabeledMultiGraph(void);

            /**
             *  Create a new IMutableLabeledMultiGraph object.
             *
             *  @param[in] initialSize  The initial size of the created graph.
             *
             *  @return A new IMutableLabeledMultiGraph object of the given size.
             */
            htd::IMutableLabeledMultiGraph * getLabeledMultiGraph(std::size_t initialSize);

            /**
             *  Create a new IMutableLabeledMultiGraph object.
             *
             *  @param[in] original The original labeled multi-graph acting as template for the created graph.
             *
             *  @return A new IMutableLabeledMultiGraph object identical to the given original graph.
             */
            htd::IMutableLabeledMultiGraph * getLabeledMultiGraph(const htd::ILabeledMultiGraph & original);

            /**
             *  Set the default implementation of the IMutableLabeledMultiGraph interface.
             *
             *  @note When calling this method the control over the memory regions of the object instance of the original implementation
             *  is transferred to the factory class. Deleting the object instance provided to this method outside the factory class or
             *  assigning the same object instance multiple times will lead to undefined behavior.
             *
             *  @param[in] original The new default implementation of the IMutableLabeledMultiGraph interface.
             */
            void setConstructionTemplate(htd::IMutableLabeledMultiGraph * original);

            /**
             *  Access the mutable interface of a given labeled multi-graph.
             *
             *  @return The mutable interface of the given labeled multi-graph.
             */
            htd::IMutableLabeledMultiGraph & accessMutableLabeledMultiGraph(htd::ILabeledMultiGraph & original);

            /**
             *  Access the mutable interface of a given labeled multi-graph.
             *
             *  @return The mutable interface of the given labeled multi-graph.
             */
            const htd::IMutableLabeledMultiGraph & accessMutableLabeledMultiGraph(const htd::ILabeledMultiGraph & original);

        private:
            /**
             *  A pointer to a clean instance of the default implementation.
             */
            htd::IMutableLabeledMultiGraph * constructionTemplate_;

            /**
             *  Constructor for the factory class.
             *
             *  @note This constructor is private to prevent creating multiple instances of the factory.
             */
            LabeledMultiGraphFactory(void);

            /**
             *  Copy constructor for the factory class.
             *
             *  @note This constructor is private to prevent creating multiple instances of the factory.
             */
            LabeledMultiGraphFactory(const LabeledMultiGraphFactory & original);

            /**
             *  Copy assignment operator for the factory class.
             *
             *  @note This operator is private to prevent assignments to the factory class.
             */
            LabeledMultiGraphFactory & operator=(const LabeledMultiGraphFactory & original);
    };
}

#endif /* HTD_HTD_LABELEDMULTIGRAPHFACTORY_HPP */
