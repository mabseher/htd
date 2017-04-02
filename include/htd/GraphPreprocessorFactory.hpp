/*
 * File:   GraphPreprocessorFactory.hpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 *
 * Copyright 2015-2017, Michael Abseher
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

#ifndef HTD_HTD_GRAPHPREPROCESSORFACTORY_HPP
#define HTD_HTD_GRAPHPREPROCESSORFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/AlgorithmFactory.hpp>
#include <htd/IGraphPreprocessor.hpp>

namespace htd
{
    /**
     *  Factory class for the default implementation of the IMutableHypergraph interface.
     */
    class GraphPreprocessorFactory : public htd::AlgorithmFactory<htd::IGraphPreprocessor>
    {
        public:
            /**
             *  Constructor for the factory class.
             *
             *  @param[in] manager   The management instance to which the new factory class belongs.
             */
            HTD_API GraphPreprocessorFactory(const htd::LibraryInstance * const manager);

            /**
             *  Copy constructor for the factory class.
             *
             *  @param[in] original The original factory class which shall be copied.
             */
            HTD_API GraphPreprocessorFactory(const HypergraphFactory & original) = delete;

            /**
             *  Copy assignment operator for the factory class.
             *
             *  @param[in] original The original factory class which shall be copied.
             */
            HTD_API GraphPreprocessorFactory & operator=(const GraphPreprocessorFactory & original) = delete;

            /**
             *  Destructor of the factory class.
             */
            HTD_API virtual ~GraphPreprocessorFactory();

            /**
             *  Create a new IGraphPreprocessor object.
             *
             *  @return A new IGraphPreprocessor object.
             */
            HTD_API htd::IGraphPreprocessor * createInstance(void) const HTD_OVERRIDE;
    };
}

#endif /* HTD_HTD_GRAPHPREPROCESSORFACTORY_HPP */
