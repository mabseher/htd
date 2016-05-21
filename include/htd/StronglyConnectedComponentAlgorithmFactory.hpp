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
             *  Destructor of the factory class.
             */
            ~StronglyConnectedComponentAlgorithmFactory();

            /**
             *  Access the singleton instance of the factory class.
             *
             *  @return The singleton instance of the factory class.
             */
            static StronglyConnectedComponentAlgorithmFactory & instance(void);

            /**
             *  Create a new IStronglyConnectedComponentAlgorithm object.
             *
             *  @return A new IStronglyConnectedComponentAlgorithm object.
             */
            htd::IStronglyConnectedComponentAlgorithm * getStronglyConnectedComponentAlgorithm(void);

            /**
             *  Set the default implementation of the IStronglyConnectedComponentAlgorithm interface.
             *
             *  @param[in] original The new default implementation of the IStronglyConnectedComponentAlgorithm interface.
             */
            void setConstructionTemplate(htd::IStronglyConnectedComponentAlgorithm * original);

        private:
            /**
             *  A pointer to a clean instance of the default implementation.
             */
            htd::IStronglyConnectedComponentAlgorithm * constructionTemplate_;

            StronglyConnectedComponentAlgorithmFactory(void);

            StronglyConnectedComponentAlgorithmFactory(const StronglyConnectedComponentAlgorithmFactory & original);

            StronglyConnectedComponentAlgorithmFactory & operator=(const StronglyConnectedComponentAlgorithmFactory & original);
    };
}

#endif /* HTD_HTD_STRONGLYCONNECTEDCOMPONENTALGORITHMFACTORY_HPP */
