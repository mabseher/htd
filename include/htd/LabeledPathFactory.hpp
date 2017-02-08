/*
 * File:   LabeledPathFactory.hpp
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

#ifndef HTD_HTD_LABELEDPATHFACTORY_HPP
#define HTD_HTD_LABELEDPATHFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/GraphTypeFactory.hpp>
#include <htd/IMutableLabeledPath.hpp>

namespace htd
{
    /**
     *  Factory class for the default implementation of the IMutableLabeledPath interface.
     */
    class LabeledPathFactory : public htd::GraphTypeFactory<htd::ILabeledPath, htd::IMutableLabeledPath>
    {
        public:
            using htd::GraphTypeFactory<htd::ILabeledPath, htd::IMutableLabeledPath>::createInstance;

            /**
             *  Constructor for the factory class.
             *
             *  @param[in] manager   The management instance to which the new factory class belongs.
             */
            HTD_API LabeledPathFactory(const htd::LibraryInstance * const manager);

            /**
             *  Copy constructor for the factory class.
             *
             *  @param[in] original The original factory class which shall be copied.
             */
            HTD_API LabeledPathFactory(const LabeledPathFactory & original) = delete;

            /**
             *  Copy assignment operator for the factory class.
             *
             *  @param[in] original The original factory class which shall be copied.
             */
            HTD_API LabeledPathFactory & operator=(const LabeledPathFactory & original) = delete;

            /**
             *  Destructor of the factory class.
             */
            HTD_API virtual ~LabeledPathFactory();

            /**
             *  Create a new IMutableLabeledPath object.
             *
             *  @return A new IMutableLabeledPath object.
             */
            HTD_API htd::IMutableLabeledPath * createInstance(void) const HTD_OVERRIDE;
    };
}

#endif /* HTD_HTD_LABELEDPATHFACTORY_HPP */
