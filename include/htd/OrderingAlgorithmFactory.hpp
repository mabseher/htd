/*
 * File:   OrderingAlgorithmFactory.hpp
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

#ifndef HTD_HTD_ORDERINGALGORITHMFACTORY_HPP
#define HTD_HTD_ORDERINGALGORITHMFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IOrderingAlgorithm.hpp>

namespace htd
{
    /**
     *  Factory class for the default implementation of the IOrderingAlgorithm interface.
     */
    class HTD_API OrderingAlgorithmFactory
    {
        public:
            /**
             *  Constructor for the factory class.
             */
            OrderingAlgorithmFactory(const htd::LibraryInstance * const manager);

            /**
             *  Copy constructor for the factory class.
             */
            OrderingAlgorithmFactory(const OrderingAlgorithmFactory & original);

            /**
             *  Copy assignment operator for the factory class.
             */
            OrderingAlgorithmFactory & operator=(const OrderingAlgorithmFactory & original);

            /**
             *  Destructor of the factory class.
             */
            virtual ~OrderingAlgorithmFactory();

            /**
             *  Create a new IOrderingAlgorithm object.
             *
             *  @return A new IOrderingAlgorithm object.
             */
            htd::IOrderingAlgorithm * getOrderingAlgorithm(void) const;

            /**
             *  Create a new IOrderingAlgorithm object.
             *
             *  @param[in] manager   The management instance which shall be assigned to the new IOrderingAlgorithm object.
             *
             *  @return A new IOrderingAlgorithm object.
             */
            htd::IOrderingAlgorithm * getOrderingAlgorithm(const htd::LibraryInstance * const manager) const;

            /**
             *  Set the default implementation of the IOrderingAlgorithm interface.
             *
             *  @note When calling this method the control over the memory regions of the object instance of the original implementation
             *  is transferred to the factory class. Deleting the object instance provided to this method outside the factory class or
             *  assigning the same object instance multiple times will lead to undefined behavior.
             *
             *  @param[in] original The new default implementation of the IOrderingAlgorithm interface.
             */
            void setConstructionTemplate(htd::IOrderingAlgorithm * original);

        private:
            /**
             *  A pointer to a clean instance of the default implementation.
             */
            htd::IOrderingAlgorithm * constructionTemplate_;
    };
}

#endif /* HTD_HTD_ORDERINGALGORITHMFACTORY_HPP */
