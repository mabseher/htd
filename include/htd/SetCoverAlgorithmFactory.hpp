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

            htd::ISetCoverAlgorithm * getSetCoverAlgorithm(void);

            void setConstructionTemplate(htd::ISetCoverAlgorithm * original);

        private:
            htd::ISetCoverAlgorithm * constructionTemplate_;

            SetCoverAlgorithmFactory(void);

            SetCoverAlgorithmFactory(const SetCoverAlgorithmFactory & original);

            SetCoverAlgorithmFactory & operator=(const SetCoverAlgorithmFactory & original);
    };
}

#endif /* HTD_HTD_SETCOVERALGORITHMFACTORY_HPP */
