/*
 * File:   CompressionOperation.cpp
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

#ifndef HTD_HTD_COMPRESSIONOPERATION_CPP
#define	HTD_HTD_COMPRESSIONOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/CompressionOperation.hpp>
#include <htd/PostOrderTreeTraversal.hpp>

#include <stack>

htd::CompressionOperation::CompressionOperation(void)
{

}

htd::CompressionOperation::~CompressionOperation()
{

}

void htd::CompressionOperation::apply(htd::IMutablePathDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::CompressionOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(labelingFunctions)

    if (decomposition.vertexCount() > 1)
    {
        htd::PostOrderTreeTraversal treeTraversal;

        treeTraversal.traverse(decomposition, [&](htd::vertex_t vertex, htd::vertex_t parent, std::size_t distanceToSubtreeRoot)
        {
            HTD_UNUSED(distanceToSubtreeRoot)

            if (parent != htd::Vertex::UNKNOWN)
            {
                const htd::ConstCollection<htd::vertex_t> & currentBag = decomposition.bagContent(vertex);
                const htd::ConstCollection<htd::vertex_t> & parentBag = decomposition.bagContent(parent);

                std::pair<std::size_t, std::size_t> result = compute_symmetric_difference_sizes(currentBag.begin(), currentBag.end(), parentBag.begin(), parentBag.end());

                if (result.first > 0 && result.second == 0)
                {
                    decomposition.removeVertex(vertex);
                }
                else if (result.first == 0 && result.second > 0)
                {
                    decomposition.swapVertexLabels(vertex, parent);

                    decomposition.removeVertex(vertex);
                }
            }
        });
    }
}

void htd::CompressionOperation::apply(htd::IMutableTreeDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::CompressionOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(labelingFunctions)

    if (decomposition.vertexCount() > 1)
    {
        htd::PostOrderTreeTraversal treeTraversal;

        treeTraversal.traverse(decomposition, [&](htd::vertex_t vertex, htd::vertex_t parent, std::size_t distanceToSubtreeRoot)
        {
            HTD_UNUSED(distanceToSubtreeRoot)

            if (parent != htd::Vertex::UNKNOWN)
            {
                const htd::ConstCollection<htd::vertex_t> & currentBag = decomposition.bagContent(vertex);
                const htd::ConstCollection<htd::vertex_t> & parentBag = decomposition.bagContent(parent);

                std::tuple<std::size_t, std::size_t, std::size_t> result = analyze_sets(currentBag, parentBag);

                if (std::get<0>(result) == 0)
                {
                    decomposition.removeVertex(vertex);
                }
                else if (std::get<2>(result) == 0)
                {
                    decomposition.swapVertexLabels(vertex, parent);

                    for (htd::vertex_t child : decomposition.children(vertex))
                    {
                        decomposition.setParent(child, parent);
                    }

                    decomposition.removeVertex(vertex);
                }
            }
        });
    }
}

htd::CompressionOperation * htd::CompressionOperation::clone(void) const
{
    return new htd::CompressionOperation();
}

std::tuple<std::size_t, std::size_t, std::size_t> htd::CompressionOperation::analyze_sets(const htd::ConstCollection<htd::vertex_t> & set1, const htd::ConstCollection<htd::vertex_t> & set2) const
{
    auto first1 = set1.begin();
    auto first2 = set2.begin();
    auto last1 = set1.end();
    auto last2 = set2.end();

    std::size_t count1 = set1.size();
    std::size_t count2 = set2.size();

    htd::index_t index1 = 0;
    htd::index_t index2 = 0;

    std::tuple<std::size_t, std::size_t, std::size_t> ret(0, 0, 0);

    while (index1 < count1 && index2 < count2)
    {
        auto value1 = *first1;
        auto value2 = *first2;

        if (value1 < value2)
        {
            std::get<0>(ret)++;

            index1++;
            ++first1;
        }
        else if (value2 < value1)
        {
            std::get<2>(ret)++;

            index2++;
            ++first2;
        }
        else
        {
            std::get<1>(ret)++;

            index1++;
            ++first1;

            //Skip common value in set 2.
            index2++;
            ++first2;
        }
    }

    if (index1 < count1)
    {
        std::get<0>(ret) += std::distance(first1, last1);
    }
    else if (index2 < count2)
    {
        std::get<2>(ret) += std::distance(first2, last2);
    }

    return ret;
}

#endif /* HTD_HTD_COMPRESSIONOPERATION_CPP */
