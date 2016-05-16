/*
 * File:   LabeledMultiHypergraphFactory.hpp
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

#ifndef HTD_HTD_LABELEDMULTIHYPERGRAPHFACTORY_HPP
#define HTD_HTD_LABELEDMULTIHYPERGRAPHFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableLabeledMultiHypergraph.hpp>

namespace htd
{
    /**
     *  Factory class for the default implementation of the IMutableLabeledMultiHypergraph interface.
     */
    class LabeledMultiHypergraphFactory
    {
        public:
            /**
             *  Destructor of the factory class.
             */
            ~LabeledMultiHypergraphFactory();

            /**
             *  Access the singleton instance of the factory class.
             *
             *  @return The singleton instance of the factory class.
             */
            static LabeledMultiHypergraphFactory & instance(void);

            htd::IMutableLabeledMultiHypergraph * getLabeledMultiHypergraph(void);

            htd::IMutableLabeledMultiHypergraph * getLabeledMultiHypergraph(std::size_t initialSize);

            htd::IMutableLabeledMultiHypergraph * getLabeledMultiHypergraph(const htd::ILabeledMultiHypergraph & original);

            /**
             *  Set the default implementation of the IMutableLabeledMultiHypergraph interface.
             *
             *  @param[in] original The new default implementation of the IMutableLabeledMultiHypergraph interface.
             */
            void setConstructionTemplate(htd::IMutableLabeledMultiHypergraph * original);

            htd::IMutableLabeledMultiHypergraph & accessMutableLabeledMultiHypergraph(htd::ILabeledMultiHypergraph & original);

            const htd::IMutableLabeledMultiHypergraph & accessMutableLabeledMultiHypergraph(const htd::ILabeledMultiHypergraph & original);

        private:
            /**
             *  A pointer to a clean instance of the default implementation.
             */
            htd::IMutableLabeledMultiHypergraph * constructionTemplate_;

            LabeledMultiHypergraphFactory(void);

            LabeledMultiHypergraphFactory(const LabeledMultiHypergraphFactory & original);

            LabeledMultiHypergraphFactory & operator=(const LabeledMultiHypergraphFactory & original);
    };
}

#endif /* HTD_HTD_LABELEDMULTIHYPERGRAPHFACTORY_HPP */
