/*
 * File:   ConnectedComponentAlgorithmFactory.hpp
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

#ifndef HTD_HTD_CONNECTEDCOMPONENTALGORITHMFACTORY_HPP
#define HTD_HTD_CONNECTEDCOMPONENTALGORITHMFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IConnectedComponentAlgorithm.hpp>

namespace htd
{
    /**
     *  Factory class for the default implementation of the IConnectedComponentAlgorithm interface.
     */
    class ConnectedComponentAlgorithmFactory
    {
        public:
            /**
             *  Destructor of the factory class.
             */
            ~ConnectedComponentAlgorithmFactory();

            /**
             *  Access the singleton instance of the factory class.
             *
             *  @return The singleton instance of the factory class.
             */
            static ConnectedComponentAlgorithmFactory & instance(void);

            /**
             *  Create a new IConnectedComponentAlgorithm object.
             *
             *  @return A new IConnectedComponentAlgorithm object.
             */
            htd::IConnectedComponentAlgorithm * getConnectedComponentAlgorithm(void) const;

            /**
             *  Create a new IConnectedComponentAlgorithm object.
             *
             *  @param[in] instance The management instance which shall be assigned to the new IConnectedComponentAlgorithm object.
             *
             *  @return A new IConnectedComponentAlgorithm object.
             */
            htd::IConnectedComponentAlgorithm * getConnectedComponentAlgorithm(const std::shared_ptr<htd::LibraryInstance> & instance) const;

            /**
             *  Set the default implementation of the IConnectedComponentAlgorithm interface.
             *
             *  @note When calling this method the control over the memory regions of the object instance of the original implementation
             *  is transferred to the factory class. Deleting the object instance provided to this method outside the factory class or
             *  assigning the same object instance multiple times will lead to undefined behavior.
             *
             *  @param[in] original The new default implementation of the IConnectedComponentAlgorithm interface.
             */
            void setConstructionTemplate(htd::IConnectedComponentAlgorithm * original);

        private:
            /**
             *  A pointer to a clean instance of the default implementation.
             */
            htd::IConnectedComponentAlgorithm * constructionTemplate_;

            /**
             *  Constructor for the factory class.
             *
             *  @note This constructor is private to prevent creating multiple instances of the factory.
             */
            ConnectedComponentAlgorithmFactory(void);

            /**
             *  Copy constructor for the factory class.
             *
             *  @note This constructor is private to prevent creating multiple instances of the factory.
             */
            ConnectedComponentAlgorithmFactory(const ConnectedComponentAlgorithmFactory & original);

            /**
             *  Copy assignment operator for the factory class.
             *
             *  @note This operator is private to prevent assignments to the factory class.
             */
            ConnectedComponentAlgorithmFactory & operator=(const ConnectedComponentAlgorithmFactory & original);
    };
}

#endif /* HTD_HTD_CONNECTEDCOMPONENTALGORITHMFACTORY_HPP */
