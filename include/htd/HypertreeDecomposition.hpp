/* 
 * File:   HypertreeDecomposition.hpp
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

#ifndef HTD_HTD_HYPERTREEDECOMPOSITION_HPP
#define	HTD_HTD_HYPERTREEDECOMPOSITION_HPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/TreeDecomposition.hpp>
#include <htd/IMutableHypertreeDecomposition.hpp>

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
            HypertreeDecomposition(const htd::LibraryInstance * const manager);

            /**
             *  Copy constructor for a hypertree decomposition.
             *
             *  @param[in] original  The original tree decomposition.
             */
            HypertreeDecomposition(const htd::ITreeDecomposition & original);

            /**
             *  Copy constructor for a hypertree decomposition.
             *
             *  @param[in] original  The original hypertree decomposition.
             */
            HypertreeDecomposition(const htd::IHypertreeDecomposition & original);

            virtual ~HypertreeDecomposition();

            const std::vector<htd::Hyperedge> & coveringEdges(htd::vertex_t vertex) const HTD_OVERRIDE;

            void setCoveringEdges(htd::vertex_t vertex, const std::vector<htd::Hyperedge> & content) HTD_OVERRIDE;

            void setCoveringEdges(htd::vertex_t vertex, const htd::ConstCollection<htd::Hyperedge> & content) HTD_OVERRIDE;

            std::size_t minimumCoveringEdgeAmount(void) const HTD_OVERRIDE;

            std::size_t maximumCoveringEdgeAmount(void) const HTD_OVERRIDE;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            HypertreeDecomposition * clone(void) const HTD_OVERRIDE;
#else
            HypertreeDecomposition * clone(void) const;

            htd::ITree * cloneTree(void) const HTD_OVERRIDE;

            htd::IGraph * cloneGraph(void) const HTD_OVERRIDE;

            htd::IMultiGraph * cloneMultiGraph(void) const HTD_OVERRIDE;

            htd::IHypergraph * cloneHypergraph(void) const HTD_OVERRIDE;

            htd::IMultiHypergraph * cloneMultiHypergraph(void) const HTD_OVERRIDE;

            htd::ILabeledTree * cloneLabeledTree(void) const HTD_OVERRIDE;

            htd::ILabeledGraph * cloneLabeledGraph(void) const HTD_OVERRIDE;

            htd::ILabeledMultiGraph * cloneLabeledMultiGraph(void) const HTD_OVERRIDE;

            htd::ILabeledHypergraph * cloneLabeledHypergraph(void) const HTD_OVERRIDE;

            htd::ILabeledMultiHypergraph * cloneLabeledMultiHypergraph(void) const HTD_OVERRIDE;

            htd::ITreeDecomposition * cloneTreeDecomposition(void) const HTD_OVERRIDE;

            htd::IGraphDecomposition * cloneGraphDecomposition(void) const HTD_OVERRIDE;

            htd::IHypertreeDecomposition * cloneHypertreeDecomposition(void) const HTD_OVERRIDE;

            htd::IMutableTree * cloneMutableTree(void) const HTD_OVERRIDE;

            htd::IMutableLabeledTree * cloneMutableLabeledTree(void) const HTD_OVERRIDE;

            htd::IMutableTreeDecomposition * cloneMutableTreeDecomposition(void) const HTD_OVERRIDE;

            htd::IMutableHypertreeDecomposition * cloneMutableHypertreeDecomposition(void) const HTD_OVERRIDE;
#endif

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            HypertreeDecomposition & operator=(const htd::ITree & original) HTD_OVERRIDE;

            HypertreeDecomposition & operator=(const htd::ILabeledTree & original) HTD_OVERRIDE;

            HypertreeDecomposition & operator=(const htd::ITreeDecomposition & original) HTD_OVERRIDE;

            HypertreeDecomposition & operator=(const htd::IHypertreeDecomposition & original) HTD_OVERRIDE;
#else
            HypertreeDecomposition & operator=(const htd::ITree & original);

            HypertreeDecomposition & operator=(const htd::ILabeledTree & original);

            HypertreeDecomposition & operator=(const htd::ITreeDecomposition & original);

            HypertreeDecomposition & operator=(const htd::IHypertreeDecomposition & original);

            void assign(const htd::ITree & original) HTD_OVERRIDE;

            void assign(const htd::ILabeledTree & original) HTD_OVERRIDE;

            void assign(const htd::ITreeDecomposition & original) HTD_OVERRIDE;

            void assign(const htd::IHypertreeDecomposition & original) HTD_OVERRIDE;
#endif
        private:
            std::unordered_map<htd::vertex_t, std::vector<htd::Hyperedge>> coveringEdges_;
    };
}

#endif /* HTD_HTD_HYPERTREEDECOMPOSITION_HPP */
