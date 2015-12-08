/* 
 * File:   ILabeledHypergraph.hpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015, Michael Abseher
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
#define	HTD_HTD_ILABELEDHYPERGRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/IHypergraph.hpp>
#include <htd/ILabel.hpp>
#include <htd/IGraphLabeling.hpp>
#include <htd/ILabelingCollection.hpp>

#include <string>

namespace htd
{
    class ILabeledHypergraph : public virtual htd::IHypergraph
    {
        public:
            virtual ~ILabeledHypergraph() = 0;

            virtual const htd::ILabelingCollection & labelings(void) const = 0;

            virtual std::size_t labelCount(void) const = 0;

            virtual htd::Collection<std::string> labelNames(void) const = 0;

            virtual const std::string & labelName(htd::index_t index) const = 0;

            virtual const htd::ILabel & label(const std::string & labelName, htd::vertex_t vertex) const = 0;

            virtual const htd::ILabel & label(const std::string & labelName, const htd::hyperedge_t & edge) const = 0;

            virtual ILabeledHypergraph * clone(void) const = 0;
    };

    inline htd::ILabeledHypergraph::~ILabeledHypergraph() { }
}

#endif /* HTD_HTD_ILABELEDHYPERGRAPH_HPP */
