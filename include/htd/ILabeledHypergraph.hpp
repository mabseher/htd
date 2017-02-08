/* 
 * File:   ILabeledHypergraph.hpp
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

#ifndef HTD_HTD_ILABELEDHYPERGRAPH_HPP
#define HTD_HTD_ILABELEDHYPERGRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/IHypergraph.hpp>
#include <htd/ILabeledMultiHypergraph.hpp>

#include <string>

namespace htd
{
    /**
     * Interface for classes which represent labeled hypergraphs.
     */
    class ILabeledHypergraph : public virtual htd::IHypergraph, public virtual htd::ILabeledMultiHypergraph
    {
        public:
            virtual ~ILabeledHypergraph() = 0;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Create a deep copy of the current labeled hypergraph.
             *
             *  @return A new ILabeledHypergraph object identical to the current labeled hypergraph.
             */
            virtual ILabeledHypergraph * clone(void) const HTD_OVERRIDE = 0;
#else
            /**
             *  Create a deep copy of the current labeled hypergraph.
             *
             *  @return A new ILabeledHypergraph object identical to the current labeled hypergraph.
             */
            virtual ILabeledHypergraph * cloneLabeledHypergraph(void) const = 0;
#endif
    };

    inline htd::ILabeledHypergraph::~ILabeledHypergraph() { }
}

#endif /* HTD_HTD_ILABELEDHYPERGRAPH_HPP */
