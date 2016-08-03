/*
 * File:   SetCoverAlgorithmFactory.hpp
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

#ifndef HTD_HTD_SETCOVERALGORITHMFACTORY_HPP
#define HTD_HTD_SETCOVERALGORITHMFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/ISetCoverAlgorithm.hpp>

namespace htd
{
    /**
     *  Factory class for the default implementation of the ISetCoverAlgorithm interface.
     */
    class SetCoverAlgorithmFactory
    {
        public:
            /**
             *  Constructor for the factory class.
             */
            HTD_API SetCoverAlgorithmFactory(const htd::LibraryInstance * const manager);

            /**
             *  Copy constructor for the factory class.
             */
            HTD_API SetCoverAlgorithmFactory(const SetCoverAlgorithmFactory & original);

            /**
             *  Copy assignment operator for the factory class.
             */
            HTD_API SetCoverAlgorithmFactory & operator=(const SetCoverAlgorithmFactory & original);

            /**
             *  Destructor of the factory class.
             */
            HTD_API virtual ~SetCoverAlgorithmFactory();

            /**
             *  Create a new ISetCoverAlgorithm object.
             *
             *  @return A new ISetCoverAlgorithm object.
             */
            HTD_API htd::ISetCoverAlgorithm * getSetCoverAlgorithm(void) const;

            /**
             *  Create a new ISetCoverAlgorithm object.
             *
             *  @param[in] manager   The management instance which shall be assigned to the new ISetCoverAlgorithm object.
             *
             *  @return A new ISetCoverAlgorithm object.
             */
            HTD_API htd::ISetCoverAlgorithm * getSetCoverAlgorithm(const htd::LibraryInstance * const manager) const;

            /**
             *  Set the default implementation of the ISetCoverAlgorithm interface.
             *
             *  @note When calling this method the control over the memory regions of the object instance of the original implementation
             *  is transferred to the factory class. Deleting the object instance provided to this method outside the factory class or
             *  assigning the same object instance multiple times will lead to undefined behavior.
             *
             *  @param[in] original The new default implementation of the ISetCoverAlgorithm interface.
             */
            HTD_API void setConstructionTemplate(htd::ISetCoverAlgorithm * original);

        private:
            /**
             *  A pointer to a clean instance of the default implementation.
             */
            htd::ISetCoverAlgorithm * constructionTemplate_;
    };
}

#endif /* HTD_HTD_SETCOVERALGORITHMFACTORY_HPP */
