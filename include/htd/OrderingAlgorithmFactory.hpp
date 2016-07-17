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
    class OrderingAlgorithmFactory
    {
        public:
            /**
             *  Destructor of the factory class.
             */
            ~OrderingAlgorithmFactory();

            /**
             *  Access the singleton instance of the factory class.
             *
             *  @return The singleton instance of the factory class.
             */
            static OrderingAlgorithmFactory & instance(void);

            /**
             *  Create a new IOrderingAlgorithm object.
             *
             *  @return A new IOrderingAlgorithm object.
             */
            htd::IOrderingAlgorithm * getOrderingAlgorithm(void) const;

            /**
             *  Create a new IOrderingAlgorithm object.
             *
             *  @param[in] instance The management instance which shall be assigned to the new IOrderingAlgorithm object.
             *
             *  @return A new IOrderingAlgorithm object.
             */
            htd::IOrderingAlgorithm * getOrderingAlgorithm(const std::shared_ptr<htd::LibraryInstance> & instance) const;

            /**
             *  Set the default implementation of the IOrderingAlgorithm interface.
             *
             *  @param[in] original The new default implementation of the IOrderingAlgorithm interface.
             */
            void setConstructionTemplate(htd::IOrderingAlgorithm * original);

        private:
            /**
             *  A pointer to a clean instance of the default implementation.
             */
            htd::IOrderingAlgorithm * constructionTemplate_;

            /**
             *  Constructor for the factory class.
             *
             *  @note This constructor is private to prevent creating multiple instances of the factory.
             */
            OrderingAlgorithmFactory(void);

            /**
             *  Copy constructor for the factory class.
             *
             *  @note This constructor is private to prevent creating multiple instances of the factory.
             */
            OrderingAlgorithmFactory(const OrderingAlgorithmFactory & original);

            /**
             *  Copy assignment operator for the factory class.
             *
             *  @note This operator is private to prevent assignments to the factory class.
             */
            OrderingAlgorithmFactory & operator=(const OrderingAlgorithmFactory & original);
    };
}

#endif /* HTD_HTD_ORDERINGALGORITHMFACTORY_HPP */
