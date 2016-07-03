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
#include <vector>

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

void htd::CompressionOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices) const
{
    HTD_UNUSED(relevantVertices)

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
                const std::vector<htd::vertex_t> & currentBag = decomposition.bagContent(vertex);
                const std::vector<htd::vertex_t> & parentBag = decomposition.bagContent(parent);

                std::pair<std::size_t, std::size_t> result = htd::symmetric_difference_sizes(currentBag.begin(), currentBag.end(), parentBag.begin(), parentBag.end());

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

void htd::CompressionOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(relevantVertices)

    apply(decomposition, labelingFunctions);
}

void htd::CompressionOperation::apply(htd::IMutableTreeDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::CompressionOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    apply(decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>(), createdVertices, removedVertices);
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
                const std::tuple<std::size_t, std::size_t, std::size_t> & result = htd::analyze_sets(decomposition.bagContent(vertex), decomposition.bagContent(parent));

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

void htd::CompressionOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    HTD_UNUSED(relevantVertices)
    HTD_UNUSED(createdVertices)
    HTD_UNUSED(removedVertices)

    apply(decomposition, labelingFunctions);
}

bool htd::CompressionOperation::isLocalOperation(void) const
{
    return true;
}

bool htd::CompressionOperation::createsTreeNodes(void) const
{
    return false;
}

bool htd::CompressionOperation::removesTreeNodes(void) const
{
    return true;
}

bool htd::CompressionOperation::modifiesBagContents(void) const
{
    return false;
}

htd::CompressionOperation * htd::CompressionOperation::clone(void) const
{
    return new htd::CompressionOperation();
}

#endif /* HTD_HTD_COMPRESSIONOPERATION_CPP */
