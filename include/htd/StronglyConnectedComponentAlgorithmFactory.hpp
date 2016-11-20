/*
 * File:   StronglyConnectedComponentAlgorithmFactory.hpp
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

#ifndef HTD_HTD_STRONGLYCONNECTEDCOMPONENTALGORITHMFACTORY_HPP
#define HTD_HTD_STRONGLYCONNECTEDCOMPONENTALGORITHMFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IStronglyConnectedComponentAlgorithm.hpp>

namespace htd
{
    /**
     *  Factory class for the default implementation of the IStronglyConnectedComponentAlgorithm interface.
     */
    class StronglyConnectedComponentAlgorithmFactory
    {
        public:
            /**
             *  Constructor for the factory class.
             */
            HTD_API StronglyConnectedComponentAlgorithmFactory(const htd::LibraryInstance * const manager);

            /**
             *  Copy constructor for the factory class.
             *
             *  @param[in] original The original factory class which shall be copied.
             */
            HTD_API StronglyConnectedComponentAlgorithmFactory(const StronglyConnectedComponentAlgorithmFactory & original);

            /**
             *  Copy assignment operator for the factory class.
             *
             *  @param[in] original The original factory class which shall be copied.
             */
            HTD_API StronglyConnectedComponentAlgorithmFactory & operator=(const StronglyConnectedComponentAlgorithmFactory & original);

            /**
             *  Destructor of the factory class.
             */
            HTD_API virtual ~StronglyConnectedComponentAlgorithmFactory();

            /**
             *  Create a new IStronglyConnectedComponentAlgorithm object.
             *
             *  @return A new IStronglyConnectedComponentAlgorithm object.
             */
            HTD_API htd::IStronglyConnectedComponentAlgorithm * getStronglyConnectedComponentAlgorithm(void) const;

            /**
             *  Create a new IStronglyConnectedComponentAlgorithm object.
             *
             *  @param[in] manager   The management instance which shall be assigned to the new IStronglyConnectedComponentAlgorithm object.
             *
             *  @return A new IStronglyConnectedComponentAlgorithm object.
             */
            HTD_API htd::IStronglyConnectedComponentAlgorithm * getStronglyConnectedComponentAlgorithm(const htd::LibraryInstance * const manager) const;

            /**
             *  Set the default implementation of the IStronglyConnectedComponentAlgorithm interface.
             *
             *  @note When calling this method the control over the memory regions of the object instance of the original implementation
             *  is transferred to the factory class. Deleting the object instance provided to this method outside the factory class or
             *  assigning the same object instance multiple times will lead to undefined behavior.
             *
             *  @param[in] original The new default implementation of the IStronglyConnectedComponentAlgorithm interface.
             */
            HTD_API void setConstructionTemplate(htd::IStronglyConnectedComponentAlgorithm * original);

        private:
            /**
             *  A pointer to a clean instance of the default implementation.
             */
            htd::IStronglyConnectedComponentAlgorithm * constructionTemplate_;
    };
}

#endif /* HTD_HTD_STRONGLYCONNECTEDCOMPONENTALGORITHMFACTORY_HPP */
