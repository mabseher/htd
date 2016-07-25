/*
 * File:   GraphFactory.hpp
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

#ifndef HTD_HTD_GRAPHFACTORY_HPP
#define HTD_HTD_GRAPHFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableGraph.hpp>

namespace htd
{
    /**
     *  Factory class for the default implementation of the IMutableGraph interface.
     */
    class HTD_API GraphFactory
    {
        public:
            /**
             *  Destructor of the factory class.
             */
            ~GraphFactory();

            /**
             *  Access the singleton instance of the factory class.
             *
             *  @return The singleton instance of the factory class.
             */
            static GraphFactory & instance(void);

            /**
             *  Create a new IMutableGraph object.
             *
             *  @return A new IMutableGraph object.
             */
            htd::IMutableGraph * getGraph(void);

            /**
             *  Create a new IMutableGraph object.
             *
             *  @param[in] initialSize  The initial size of the created graph.
             *
             *  @return A new IMutableGraph object of the given size.
             */
            htd::IMutableGraph * getGraph(std::size_t initialSize);

            /**
             *  Create a new IMutableGraph object.
             *
             *  @param[in] original The original graph acting as template for the created graph.
             *
             *  @return A new IMutableGraph object identical to the given original graph.
             */
            htd::IMutableGraph * getGraph(const htd::IGraph & original);

            /**
             *  Create a new IMutableGraph object.
             *
             *  @param[in] original The original multi-graph acting as template for the created graph.
             *
             *  @return A new IMutableGraph object identical to the given original graph.
             */
            htd::IMutableGraph * getGraph(const htd::IMultiGraph & original);

            /**
             *  Set the default implementation of the IMutableGraph interface.
             *
             *  @note When calling this method the control over the memory regions of the object instance of the original implementation
             *  is transferred to the factory class. Deleting the object instance provided to this method outside the factory class or
             *  assigning the same object instance multiple times will lead to undefined behavior.
             *
             *  @param[in] original The new default implementation of the IMutableGraph interface.
             */
            void setConstructionTemplate(htd::IMutableGraph * original);

            /**
             *  Access the mutable interface of a given graph.
             *
             *  @return The mutable interface of the given graph.
             */
            htd::IMutableGraph & accessMutableGraph(htd::IGraph & original);

            /**
             *  Access the mutable interface of a given graph.
             *
             *  @return The mutable interface of the given graph.
             */
            const htd::IMutableGraph & accessMutableGraph(const htd::IGraph & original);

        private:
            /**
             *  A pointer to a clean instance of the default implementation.
             */
            htd::IMutableGraph * constructionTemplate_;

            /**
             *  Constructor for the factory class.
             *
             *  @note This constructor is private to prevent creating multiple instances of the factory.
             */
            GraphFactory(void);

            /**
             *  Copy constructor for the factory class.
             *
             *  @note This constructor is private to prevent creating multiple instances of the factory.
             */
            GraphFactory(const GraphFactory & original);

            /**
             *  Copy assignment operator for the factory class.
             *
             *  @note This operator is private to prevent assignments to the factory class.
             */
            GraphFactory & operator=(const GraphFactory & original);
    };
}

#endif /* HTD_HTD_GRAPHFACTORY_HPP */
