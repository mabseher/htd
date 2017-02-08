/* 
 * File:   HypertreeDecomposition.hpp
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

#ifndef HTD_HTD_HYPERTREEDECOMPOSITION_HPP
#define HTD_HTD_HYPERTREEDECOMPOSITION_HPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/TreeDecomposition.hpp>
#include <htd/IMutableHypertreeDecomposition.hpp>

MSVC_PRAGMA_WARNING_PUSH
MSVC_PRAGMA_DISABLE_WARNING_C4250

namespace htd
{
    /**
     *  Default implementation of the IMutableHypertreeDecomposition interface.
     */
    class HypertreeDecomposition : public htd::TreeDecomposition, public virtual htd::IMutableHypertreeDecomposition
    {
        public:
            /**
             *  Constructor for a hypertree decomposition.
             *
             *  @param[in] manager   The management instance to which the new hypertree decomposition belongs.
             */
            HTD_API HypertreeDecomposition(const htd::LibraryInstance * const manager);

            /**
             *  Copy constructor for a hypertree decomposition.
             *
             *  @param[in] original  The original hypertree decomposition.
             */
            HTD_API HypertreeDecomposition(const htd::HypertreeDecomposition & original);

            /**
             *  Copy constructor for a hypertree decomposition.
             *
             *  @param[in] original  The original labeled tree.
             */
            HTD_API HypertreeDecomposition(const htd::ITree & original);

            /**
             *  Copy constructor for a hypertree decomposition.
             *
             *  @param[in] original  The original labeled tree.
             */
            HTD_API HypertreeDecomposition(const htd::ILabeledTree & original);

            /**
             *  Copy constructor for a hypertree decomposition.
             *
             *  @param[in] original  The original tree decomposition.
             */
            HTD_API HypertreeDecomposition(const htd::ITreeDecomposition & original);

            /**
             *  Copy constructor for a hypertree decomposition.
             *
             *  @param[in] original  The original hypertree decomposition.
             */
            HTD_API HypertreeDecomposition(const htd::IHypertreeDecomposition & original);

            HTD_API virtual ~HypertreeDecomposition();

            HTD_API void removeVertex(htd::vertex_t vertex) HTD_OVERRIDE;

            HTD_API void removeSubtree(htd::vertex_t subtreeRoot) HTD_OVERRIDE;

            HTD_API htd::vertex_t insertRoot(void) HTD_OVERRIDE;

            HTD_API htd::vertex_t insertRoot(const std::vector<htd::vertex_t> & bagContent, const htd::FilteredHyperedgeCollection & inducedEdges) HTD_OVERRIDE;

            HTD_API htd::vertex_t insertRoot(std::vector<htd::vertex_t> && bagContent, htd::FilteredHyperedgeCollection && inducedEdges) HTD_OVERRIDE;

            HTD_API htd::vertex_t addChild(htd::vertex_t vertex) HTD_OVERRIDE;

            HTD_API htd::vertex_t addChild(htd::vertex_t vertex, const std::vector<htd::vertex_t> & bagContent, const htd::FilteredHyperedgeCollection & inducedEdges) HTD_OVERRIDE;

            HTD_API htd::vertex_t addChild(htd::vertex_t vertex, std::vector<htd::vertex_t> && bagContent, htd::FilteredHyperedgeCollection && inducedEdges) HTD_OVERRIDE;

            HTD_API htd::vertex_t addParent(htd::vertex_t vertex) HTD_OVERRIDE;

            HTD_API htd::vertex_t addParent(htd::vertex_t vertex, const std::vector<htd::vertex_t> & bagContent, const htd::FilteredHyperedgeCollection & inducedEdges) HTD_OVERRIDE;

            HTD_API htd::vertex_t addParent(htd::vertex_t vertex, std::vector<htd::vertex_t> && bagContent, htd::FilteredHyperedgeCollection && inducedEdges) HTD_OVERRIDE;

            HTD_API void removeChild(htd::vertex_t vertex, htd::vertex_t child) HTD_OVERRIDE;

            HTD_API const std::vector<htd::Hyperedge> & coveringEdges(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API void setCoveringEdges(htd::vertex_t vertex, const std::vector<htd::Hyperedge> & content) HTD_OVERRIDE;

            HTD_API void setCoveringEdges(htd::vertex_t vertex, const htd::ConstCollection<htd::Hyperedge> & content) HTD_OVERRIDE;

            HTD_API std::size_t minimumCoveringEdgeAmount(void) const HTD_OVERRIDE;

            HTD_API std::size_t maximumCoveringEdgeAmount(void) const HTD_OVERRIDE;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            HTD_API HypertreeDecomposition * clone(void) const HTD_OVERRIDE;
#else
            HTD_API HypertreeDecomposition * clone(void) const;

            HTD_API htd::ITree * cloneTree(void) const HTD_OVERRIDE;

            HTD_API htd::IGraph * cloneGraph(void) const HTD_OVERRIDE;

            HTD_API htd::IMultiGraph * cloneMultiGraph(void) const HTD_OVERRIDE;

            HTD_API htd::IHypergraph * cloneHypergraph(void) const HTD_OVERRIDE;

            HTD_API htd::IMultiHypergraph * cloneMultiHypergraph(void) const HTD_OVERRIDE;

            HTD_API htd::ILabeledTree * cloneLabeledTree(void) const HTD_OVERRIDE;

            HTD_API htd::ILabeledGraph * cloneLabeledGraph(void) const HTD_OVERRIDE;

            HTD_API htd::ILabeledMultiGraph * cloneLabeledMultiGraph(void) const HTD_OVERRIDE;

            HTD_API htd::ILabeledHypergraph * cloneLabeledHypergraph(void) const HTD_OVERRIDE;

            HTD_API htd::ILabeledMultiHypergraph * cloneLabeledMultiHypergraph(void) const HTD_OVERRIDE;

            HTD_API htd::ITreeDecomposition * cloneTreeDecomposition(void) const HTD_OVERRIDE;

            HTD_API htd::IGraphDecomposition * cloneGraphDecomposition(void) const HTD_OVERRIDE;

            HTD_API htd::IHypertreeDecomposition * cloneHypertreeDecomposition(void) const HTD_OVERRIDE;

            HTD_API htd::IMutableTree * cloneMutableTree(void) const HTD_OVERRIDE;

            HTD_API htd::IMutableLabeledTree * cloneMutableLabeledTree(void) const HTD_OVERRIDE;

            HTD_API htd::IMutableTreeDecomposition * cloneMutableTreeDecomposition(void) const HTD_OVERRIDE;

            HTD_API htd::IMutableHypertreeDecomposition * cloneMutableHypertreeDecomposition(void) const HTD_OVERRIDE;
#endif

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            HTD_API HypertreeDecomposition & operator=(const htd::ITree & original) HTD_OVERRIDE;

            HTD_API HypertreeDecomposition & operator=(const htd::ILabeledTree & original) HTD_OVERRIDE;

            HTD_API HypertreeDecomposition & operator=(const htd::ITreeDecomposition & original) HTD_OVERRIDE;

            HTD_API HypertreeDecomposition & operator=(const htd::IHypertreeDecomposition & original) HTD_OVERRIDE;
#else
            HTD_API HypertreeDecomposition & operator=(const htd::ITree & original);

            HTD_API HypertreeDecomposition & operator=(const htd::ILabeledTree & original);

            HTD_API HypertreeDecomposition & operator=(const htd::ITreeDecomposition & original);

            HTD_API HypertreeDecomposition & operator=(const htd::IHypertreeDecomposition & original);

            HTD_API void assign(const htd::ITree & original) HTD_OVERRIDE;

            HTD_API void assign(const htd::ILabeledTree & original) HTD_OVERRIDE;

            HTD_API void assign(const htd::ITreeDecomposition & original) HTD_OVERRIDE;

            HTD_API void assign(const htd::IHypertreeDecomposition & original) HTD_OVERRIDE;
#endif

        private:
            std::unordered_map<htd::vertex_t, std::vector<htd::Hyperedge>> coveringEdges_;
    };
}

MSVC_PRAGMA_WARNING_POP

#endif /* HTD_HTD_HYPERTREEDECOMPOSITION_HPP */
