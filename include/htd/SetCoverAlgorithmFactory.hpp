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
             *  Destructor of the factory class.
             */
            ~SetCoverAlgorithmFactory();

            /**
             *  Access the singleton instance of the factory class.
             *
             *  @return The singleton instance of the factory class.
             */
            static SetCoverAlgorithmFactory & instance(void);

            /**
             *  Create a new ISetCoverAlgorithm object.
             *
             *  @return A new ISetCoverAlgorithm object.
             */
            htd::ISetCoverAlgorithm * getSetCoverAlgorithm(void) const;

            /**
             *  Create a new ISetCoverAlgorithm object.
             *
             *  @param[in] instance The management instance which shall be assigned to the new ISetCoverAlgorithm object.
             *
             *  @return A new ISetCoverAlgorithm object.
             */
            htd::ISetCoverAlgorithm * getSetCoverAlgorithm(const std::shared_ptr<htd::LibraryInstance> & instance) const;

            /**
             *  Set the default implementation of the ISetCoverAlgorithm interface.
             *
             *  @note When calling this method the control over the memory regions of the object instance of the original implementation
             *  is transferred to the factory class. Deleting the object instance provided to this method outside the factory class or
             *  assigning the same object instance multiple times will lead to undefined behavior.
             *
             *  @param[in] original The new default implementation of the ISetCoverAlgorithm interface.
             */
            void setConstructionTemplate(htd::ISetCoverAlgorithm * original);

        private:
            /**
             *  A pointer to a clean instance of the default implementation.
             */
            htd::ISetCoverAlgorithm * constructionTemplate_;

            /**
             *  Constructor for the factory class.
             *
             *  @note This constructor is private to prevent creating multiple instances of the factory.
             */
            SetCoverAlgorithmFactory(void);

            /**
             *  Copy constructor for the factory class.
             *
             *  @note This constructor is private to prevent creating multiple instances of the factory.
             */
            SetCoverAlgorithmFactory(const SetCoverAlgorithmFactory & original);

            /**
             *  Copy assignment operator for the factory class.
             *
             *  @note This operator is private to prevent assignments to the factory class.
             */
            SetCoverAlgorithmFactory & operator=(const SetCoverAlgorithmFactory & original);
    };
}

#endif /* HTD_HTD_SETCOVERALGORITHMFACTORY_HPP */
