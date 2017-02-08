/* 
 * File:   IMutablePathDecomposition.hpp
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

#ifndef HTD_HTD_IMUTABLEPATHDECOMPOSITION_HPP
#define HTD_HTD_IMUTABLEPATHDECOMPOSITION_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableLabeledPath.hpp>
#include <htd/IPathDecomposition.hpp>
#include <htd/Label.hpp>

namespace htd
{
    /**
     * Interface for classes which represent mutable path decompositions.
     */
    class IMutablePathDecomposition : public virtual htd::IMutableLabeledPath, public virtual htd::IPathDecomposition
    {
        public:
            using htd::IMutablePath::insertRoot;
            using htd::IMutablePath::addChild;
            using htd::IMutablePath::addParent;

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            using htd::IMutableLabeledPath::assign;
#endif

            /**
             *  Destructor for an IMutablePathDecomposition object.
             */
            virtual ~IMutablePathDecomposition() = 0;

            /**
             *  Insert the root of the path if it does not already exist.
             *
             *  @param[in] bagContent   The bag content associated with the new vertex.
             *  @param[in] inducedEdges The collection of induced edges associated with the new vertex.
             *
             *  @return The ID of the root of the path.
             */
            virtual htd::vertex_t insertRoot(const std::vector<htd::vertex_t> & bagContent, const htd::FilteredHyperedgeCollection & inducedEdges) = 0;

            /**
             *  Insert the root of the path if it does not already exist.
             *
             *  @param[in] bagContent   The bag content associated with the new vertex.
             *  @param[in] inducedEdges The collection of induced edges associated with the new vertex.
             *
             *  @return The ID of the root of the path.
             */
            virtual htd::vertex_t insertRoot(std::vector<htd::vertex_t> && bagContent, htd::FilteredHyperedgeCollection && inducedEdges) = 0;

            /**
             *  Add a new child to the given vertex.
             *
             *  @param[in] vertex       The vertex which shall get a new child.
             *  @param[in] bagContent   The bag content associated with the new vertex.
             *  @param[in] inducedEdges The collection of induced edges associated with the new vertex.
             *
             *  @return The ID of the new child.
             *
             *  @note If the given vertex already has a child, the old child will be attached to the new vertex in order to keep the path structure valid.
             */
            virtual htd::vertex_t addChild(htd::vertex_t vertex, const std::vector<htd::vertex_t> & bagContent, const htd::FilteredHyperedgeCollection & inducedEdges) = 0;

            /**
             *  Add a new child to the given vertex.
             *
             *  @param[in] vertex       The vertex which shall get a new child.
             *  @param[in] bagContent   The bag content associated with the new vertex.
             *  @param[in] inducedEdges The collection of induced edges associated with the new vertex.
             *
             *  @return The ID of the new child.
             *
             *  @note If the given vertex already has a child, the old child will be attached to the new vertex in order to keep the path structure valid.
             */
            virtual htd::vertex_t addChild(htd::vertex_t vertex, std::vector<htd::vertex_t> && bagContent, htd::FilteredHyperedgeCollection && inducedEdges) = 0;

            /**
             *  Add a new parent to the given vertex.
             *
             *  @param[in] vertex       The vertex which shall get a new parent.
             *  @param[in] bagContent   The bag content associated with the new vertex.
             *  @param[in] inducedEdges The collection of induced edges associated with the new vertex.
             *
             *  @return The ID of the new parent.
             *
             *  @note If the given vertex already has a parent, the old parent will be attached to the new vertex in order to keep the path structure valid.
             */
            virtual htd::vertex_t addParent(htd::vertex_t vertex, const std::vector<htd::vertex_t> & bagContent, const htd::FilteredHyperedgeCollection & inducedEdges) = 0;

            /**
             *  Add a new parent to the given vertex.
             *
             *  @param[in] vertex       The vertex which shall get a new parent.
             *  @param[in] bagContent   The bag content associated with the new vertex.
             *  @param[in] inducedEdges The collection of induced edges associated with the new vertex.
             *
             *  @return The ID of the new parent.
             *
             *  @note If the given vertex already has a parent, the old parent will be attached to the new vertex in order to keep the path structure valid.
             */
            virtual htd::vertex_t addParent(htd::vertex_t vertex, std::vector<htd::vertex_t> && bagContent, htd::FilteredHyperedgeCollection && inducedEdges) = 0;

            /**
             *  Access the bag content of a specific vertex.
             *
             *  @param[in] vertex   The vertex for which the bag content shall be returned.
             *
             *  @return The bag content of the specific vertex.
             */
            virtual std::vector<htd::vertex_t> & mutableBagContent(htd::vertex_t vertex) = 0;

            /**
             *  Access the hyperedges induced by the bag content of a specific vertex.
             *
             *  @param[in] vertex   The vertex for which the induced hyperedges shall be returned.
             *
             *  @return The collection of hyperedges induced by the bag content of the specific vertex.
             */
            virtual htd::FilteredHyperedgeCollection & mutableInducedHyperedges(htd::vertex_t vertex) = 0;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Create a deep copy of the current mutable path decomposition.
             *
             *  @return A new IMutablePathDecomposition object identical to the current mutable path decomposition.
             */
            virtual IMutablePathDecomposition * clone(void) const HTD_OVERRIDE = 0;
#else
            /**
             *  Create a deep copy of the current mutable path decomposition.
             *
             *  @return A new IMutablePathDecomposition object identical to the current mutable path decomposition.
             */
            virtual IMutablePathDecomposition * cloneMutablePathDecomposition(void) const = 0;
#endif

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Copy assignment operator for a mutable path decomposition.
             *
             *  @param[in] original  The original path.
             */
            virtual IMutablePathDecomposition & operator=(const htd::IPath & original) HTD_OVERRIDE = 0;

            /**
             *  Copy assignment operator for a mutable path decomposition.
             *
             *  @param[in] original  The original labeled path.
             */
            virtual IMutablePathDecomposition & operator=(const htd::ILabeledPath & original) HTD_OVERRIDE = 0;

            /**
             *  Copy assignment operator for a mutable path decomposition.
             *
             *  @param[in] original  The original path decomposition.
             */
            virtual IMutablePathDecomposition & operator=(const htd::IPathDecomposition & original) = 0;
#else
            /**
             *  Copy assignment operator for a mutable path decomposition.
             *
             *  @param[in] original  The original path decomposition.
             */
            virtual void assign(const htd::IPathDecomposition & original) = 0;
#endif
    };

    inline htd::IMutablePathDecomposition::~IMutablePathDecomposition() { }
}

#endif /* HTD_HTD_IMUTABLEPATHDECOMPOSITION_HPP */
