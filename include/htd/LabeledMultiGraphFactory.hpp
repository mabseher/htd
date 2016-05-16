/*
 * File:   LabeledMultiGraphFactory.hpp
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

#ifndef HTD_HTD_LABELEDMULTIGRAPHFACTORY_HPP
#define HTD_HTD_LABELEDMULTIGRAPHFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableLabeledMultiGraph.hpp>

namespace htd
{
    /**
     *  Factory class for the default implementation of the IMutableLabeledMultiGraph interface.
     */
    class LabeledMultiGraphFactory
    {
        public:
            /**
             *  Destructor of the factory class.
             */
            ~LabeledMultiGraphFactory();

            /**
             *  Access the singleton instance of the factory class.
             *
             *  @return The singleton instance of the factory class.
             */
            static LabeledMultiGraphFactory & instance(void);

            htd::IMutableLabeledMultiGraph * getLabeledMultiGraph(void);

            htd::IMutableLabeledMultiGraph * getLabeledMultiGraph(std::size_t initialSize);

            htd::IMutableLabeledMultiGraph * getLabeledMultiGraph(const htd::ILabeledMultiGraph & original);

            /**
             *  Set the default implementation of the IMutableLabeledMultiGraph interface.
             *
             *  @param[in] original The new default implementation of the IMutableLabeledMultiGraph interface.
             */
            void setConstructionTemplate(htd::IMutableLabeledMultiGraph * original);

            htd::IMutableLabeledMultiGraph & accessMutableLabeledMultiGraph(htd::ILabeledMultiGraph & original);

            const htd::IMutableLabeledMultiGraph & accessMutableLabeledMultiGraph(const htd::ILabeledMultiGraph & original);

        private:
            /**
             *  A pointer to a clean instance of the default implementation.
             */
            htd::IMutableLabeledMultiGraph * constructionTemplate_;

            LabeledMultiGraphFactory(void);

            LabeledMultiGraphFactory(const LabeledMultiGraphFactory & original);

            LabeledMultiGraphFactory & operator=(const LabeledMultiGraphFactory & original);
    };
}

#endif /* HTD_HTD_LABELEDMULTIGRAPHFACTORY_HPP */
