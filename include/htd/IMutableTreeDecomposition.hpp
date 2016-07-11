/* 
 * File:   IMutableTreeDecomposition.hpp
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

#ifndef HTD_HTD_IMUTABLETREEDECOMPOSITION_HPP
#define	HTD_HTD_IMUTABLETREEDECOMPOSITION_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableLabeledTree.hpp>
#include <htd/ITreeDecomposition.hpp>
#include <htd/Label.hpp>

namespace htd
{
    /**
     * Interface for classes which represent mutable tree decompositions.
     */
    class IMutableTreeDecomposition : public virtual htd::IMutableLabeledTree, public virtual htd::ITreeDecomposition
    {
        public:
            using htd::IMutableTree::addChild;
            using htd::IMutableTree::addParent;

            using htd::ITreeDecomposition::bagContent;
            using htd::ITreeDecomposition::inducedHyperedges;

            /**
             *  Destructor for an IMutableTreeDecomposition object.
             */
            virtual ~IMutableTreeDecomposition() = 0;

            /**
             *  Add a new child to the given vertex.
             *
             *  @param[in] vertex       The vertex which shall get a new child.
             *  @param[in] bagContent   The bag content associated with the new vertex.
             *  @param[in] inducedEdges The collection of induced edges associated with the new vertex.
             *
             *  @return The ID of the new child.
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
             *  @note If the given vertex already has a parent, the old parent will be attached to the new vertex in order to keep the tree structure valid.
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
             *  @note If the given vertex already has a parent, the old parent will be attached to the new vertex in order to keep the tree structure valid.
             */
            virtual htd::vertex_t addParent(htd::vertex_t vertex, std::vector<htd::vertex_t> && bagContent, htd::FilteredHyperedgeCollection && inducedEdges) = 0;

            /**
             *  Access the bag content of a specific vertex.
             *
             *  @param[in] vertex   The vertex for which the bag content shall be returned.
             *
             *  @return The bag content of the specific vertex.
             */
            virtual std::vector<htd::vertex_t> & bagContent(htd::vertex_t vertex) = 0;

            /**
             *  Access the hyperedges induced by the bag content of a specific vertex.
             *
             *  @param[in] vertex   The vertex for which the induced hyperedges shall be returned.
             *
             *  @return The collection of hyperedges induced by the bag content of the specific vertex.
             */
            virtual htd::FilteredHyperedgeCollection & inducedHyperedges(htd::vertex_t vertex) = 0;

            /**
             *  Create a deep copy of the current mutable tree decomposition.
             *
             *  @return A new IMutableTreeDecomposition object identical to the current mutable tree decomposition.
             */
            virtual IMutableTreeDecomposition * clone(void) const = 0;

            /**
             *  Copy assignment operator for a mutable tree decomposition.
             *
             *  @param[in] original  The original tree.
             */
            virtual IMutableTreeDecomposition & operator=(const htd::ITree & original) = 0;

            /**
             *  Copy assignment operator for a mutable tree decomposition.
             *
             *  @param[in] original  The original labeled tree.
             */
            virtual IMutableTreeDecomposition & operator=(const htd::ILabeledTree & original) = 0;

            /**
             *  Copy assignment operator for a mutable tree decomposition.
             *
             *  @param[in] original  The original tree decomposition.
             */
            virtual IMutableTreeDecomposition & operator=(const htd::ITreeDecomposition & original) = 0;
    };

    inline htd::IMutableTreeDecomposition::~IMutableTreeDecomposition() { }
}

#endif /* HTD_HTD_IMUTABLETREEDECOMPOSITION_HPP */
