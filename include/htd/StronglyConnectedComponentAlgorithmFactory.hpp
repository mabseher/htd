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

#ifndef HTD_STRONGLYCONNECTEDCOMPONENTALGORITHMFACTORY_HPP
#define HTD_STRONGLYCONNECTEDCOMPONENTALGORITHMFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IStronglyConnectedComponentAlgorithm.hpp>

namespace htd
{
    class StronglyConnectedComponentAlgorithmFactory
    {
        public:
            ~StronglyConnectedComponentAlgorithmFactory();

            static StronglyConnectedComponentAlgorithmFactory & instance(void);

            htd::IStronglyConnectedComponentAlgorithm * getStronglyConnectedComponentAlgorithm(void);

            void setConstructionTemplate(htd::IStronglyConnectedComponentAlgorithm * original);

        private:
            htd::IStronglyConnectedComponentAlgorithm * constructionTemplate_;

            StronglyConnectedComponentAlgorithmFactory(void);

            StronglyConnectedComponentAlgorithmFactory(const StronglyConnectedComponentAlgorithmFactory & original);

            StronglyConnectedComponentAlgorithmFactory & operator=(const StronglyConnectedComponentAlgorithmFactory & original);
    };
}

#endif /* HTD_STRONGLYCONNECTEDCOMPONENTALGORITHMFACTORY_HPP */
