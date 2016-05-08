/* 
 * File:   IMutablePathDecomposition.hpp
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

#ifndef HTD_HTD_IMUTABLEPATHDECOMPOSITION_HPP
#define	HTD_HTD_IMUTABLEPATHDECOMPOSITION_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableLabeledPath.hpp>
#include <htd/IPathDecomposition.hpp>
#include <htd/Label.hpp>

namespace htd
{
    class IMutablePathDecomposition : public virtual htd::IMutableLabeledPath, public virtual htd::IPathDecomposition
    {
        public:
            using htd::IMutablePath::addChild;
            using htd::IMutablePath::addParent;

            using htd::IPathDecomposition::bagContent;
            using htd::IPathDecomposition::inducedHyperedges;

            /**
             *  Destructor for an IMutablePathDecomposition object.
             */
            virtual ~IMutablePathDecomposition() = 0;

            virtual htd::vertex_t addChild(htd::vertex_t vertex, const std::vector<htd::vertex_t> & bagContent, const htd::FilteredHyperedgeCollection & inducedEdges) = 0;

            virtual htd::vertex_t addChild(htd::vertex_t vertex, std::vector<htd::vertex_t> && bagContent, htd::FilteredHyperedgeCollection && inducedEdges) = 0;

            virtual htd::vertex_t addParent(htd::vertex_t vertex, const std::vector<htd::vertex_t> & bagContent, const htd::FilteredHyperedgeCollection & inducedEdges) = 0;

            virtual htd::vertex_t addParent(htd::vertex_t vertex, std::vector<htd::vertex_t> && bagContent, htd::FilteredHyperedgeCollection && inducedEdges) = 0;

            virtual std::vector<htd::vertex_t> & bagContent(htd::vertex_t vertex) = 0;

            virtual htd::FilteredHyperedgeCollection & inducedHyperedges(htd::vertex_t vertex) = 0;

            /**
             *  Create a deep copy the current mutable path decomposition.
             *
             *  @return A new IMutablePathDecomposition object identical to the current mutable path decomposition.
             */
            virtual IMutablePathDecomposition * clone(void) const = 0;

            /**
             *  Copy assignment operator for a mutable path decomposition.
             *
             *  @param[in] original  The original path.
             */
            virtual IMutablePathDecomposition & operator=(const htd::IPath & original) = 0;

            /**
             *  Copy assignment operator for a mutable path decomposition.
             *
             *  @param[in] original  The original labeled path.
             */
            virtual IMutablePathDecomposition & operator=(const htd::ILabeledPath & original) = 0;

            /**
             *  Copy assignment operator for a mutable path decomposition.
             *
             *  @param[in] original  The original path decomposition.
             */
            virtual IMutablePathDecomposition & operator=(const htd::IPathDecomposition & original) = 0;
    };

    inline htd::IMutablePathDecomposition::~IMutablePathDecomposition() { }
}

#endif /* HTD_HTD_IMUTABLEPATHDECOMPOSITION_HPP */
