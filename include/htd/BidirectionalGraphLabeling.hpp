/*
 * File:   BidirectionalGraphLabeling.hpp
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

#ifndef HTD_HTD_BIDIRECTIONALGRAPHLABELING_HPP
#define	HTD_HTD_BIDIRECTIONALGRAPHLABELING_HPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>

#include <htd/IBidirectionalGraphLabeling.hpp>
#include <htd/ILabel.hpp>

#include <unordered_map>

namespace htd
{
    class BidirectionalGraphLabeling : public virtual htd::IBidirectionalGraphLabeling
    {
        public:
            BidirectionalGraphLabeling(void);

            ~BidirectionalGraphLabeling();

            std::size_t vertexLabelCount(void) const HTD_OVERRIDE;

            std::size_t hyperedgeLabelCount(void) const HTD_OVERRIDE;

            bool hasLabel(htd::vertex_t vertex) const HTD_OVERRIDE;

            bool hasLabel(const htd::hyperedge_t & edge) const HTD_OVERRIDE;

            const htd::ILabel & label(htd::vertex_t vertex) const HTD_OVERRIDE;

            const htd::ILabel & label(const htd::hyperedge_t & edge) const HTD_OVERRIDE;

            void setLabel(htd::vertex_t vertex, htd::ILabel * label) HTD_OVERRIDE;

            void setLabel(const htd::hyperedge_t & edge, htd::ILabel * label) HTD_OVERRIDE;

            void swapLabels(htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_OVERRIDE;

            void swapLabels(const htd::hyperedge_t & edge1, const htd::hyperedge_t & edge2) HTD_OVERRIDE;

            void removeLabel(htd::vertex_t vertex) HTD_OVERRIDE;

            void removeLabel(const htd::hyperedge_t & edge) HTD_OVERRIDE;

            void clear(void) HTD_OVERRIDE;

            bool isVertexLabel(const htd::ILabel & label) const HTD_OVERRIDE;

            bool isHyperedgeLabel(const htd::ILabel & label) const HTD_OVERRIDE;

            htd::vertex_t lookupVertex(const htd::ILabel & label) const HTD_OVERRIDE;

            const htd::hyperedge_t & lookupHyperedge(const htd::ILabel & label) const HTD_OVERRIDE;

            BidirectionalGraphLabeling * clone(void) const HTD_OVERRIDE;

        private:
            class ILabelPointerHashFunction
            {
                public:
                    std::size_t operator()(const htd::ILabel * data) const
                    {
                        return data->hash();
                    }
            };

            class ILabelPointerEqualityFunction
            {
                public:
                    bool operator()(const htd::ILabel * data1, const htd::ILabel * data2) const
                    {
                        return *data1 == *data2;
                    }
            };

            std::unordered_map<htd::vertex_t, htd::ILabel *> vertexLabels_;

            std::unordered_map<htd::hyperedge_t, htd::ILabel *> hyperedgeLabels_;

            std::unordered_map<const htd::ILabel *, htd::vertex_t, ILabelPointerHashFunction, ILabelPointerEqualityFunction> vertexLabelsReverseMap_;

            std::unordered_map<const htd::ILabel *, htd::hyperedge_t, ILabelPointerHashFunction, ILabelPointerEqualityFunction> hyperedgeLabelsReverseMap_;

    };
}

#endif /* HTD_HTD_BIDIRECTIONALGRAPHLABELING_HPP */
