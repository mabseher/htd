/*
 * File:   LimitChildCountOperation.cpp
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

#ifndef HTD_HTD_LIMITCHILDCOUNTOPERATION_CPP
#define	HTD_HTD_LIMITCHILDCOUNTOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/LimitChildCountOperation.hpp>

#include <algorithm>
#include <stdexcept>
#include <iterator>

htd::LimitChildCountOperation::LimitChildCountOperation(std::size_t limit) : limit_(limit)
{

}

htd::LimitChildCountOperation::~LimitChildCountOperation()
{

}

void htd::LimitChildCountOperation::apply(htd::IMutableTreeDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::LimitChildCountOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    htd::vertex_container joinNodes;

    const htd::ConstCollection<htd::vertex_t> & joinNodeCollection = decomposition.joinNodes();

    std::copy(joinNodeCollection.begin(), joinNodeCollection.end(), std::back_inserter(joinNodes));

    for (htd::vertex_t node : joinNodes)
    {
        std::size_t childCount = decomposition.childCount(node);

        if (childCount > limit_)
        {
            htd::vertex_t newNode = decomposition.addChild(node);

            decomposition.setBagContent(newNode, decomposition.bagContent(node));

            for (auto & labelingFunction : labelingFunctions)
            {
                htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                htd::ILabel * newLabel = labelingFunction->computeLabel(decomposition.bagContent(newNode), *labelCollection);

                delete labelCollection;

                decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
            }

            std::size_t remainder = childCount % (limit_ - 1);

            childCount -= remainder;

            std::size_t intermediatedVertexCount = childCount / (limit_ - 1);

            if (intermediatedVertexCount > 0)
            {
                intermediatedVertexCount--;
            }

            if (remainder == 0)
            {
                intermediatedVertexCount--;
            }

            htd::vertex_container children;

            const htd::ConstCollection<htd::vertex_t> & childCollection = decomposition.children(node);

            std::copy(childCollection.begin(), childCollection.end(), std::back_inserter(children));

            std::size_t firstStep = remainder > 0 ? remainder : (limit_ - 1);

            auto start = children.begin();
            auto finish = children.begin() + firstStep;

            for (auto it = start; it != finish; ++it)
            {
                decomposition.setParent(*it, newNode);
            }

            if (intermediatedVertexCount > 0)
            {
                std::advance(start, firstStep);
                std::advance(finish, firstStep);

                for (htd::index_t index = 0; index < intermediatedVertexCount; index++)
                {
                    std::vector<htd::vertex_t> newChildren2;
                    std::copy(start, finish, std::back_inserter(newChildren2));

                    newNode = decomposition.addParent(newNode);

                    decomposition.setBagContent(newNode, decomposition.bagContent(node));

                    for (auto it = start; it != finish; ++it)
                    {
                        decomposition.setParent(*it, newNode);
                    }

                    for (auto & labelingFunction : labelingFunctions)
                    {
                        htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                        htd::ILabel * newLabel = labelingFunction->computeLabel(decomposition.bagContent(newNode), *labelCollection);

                        delete labelCollection;

                        decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                    }

                    if (index < childCount + (limit_ - 1))
                    {
                        std::advance(start, (limit_ - 1));
                        std::advance(finish, (limit_ - 1));
                    }
                }
            }
        }
    }
}

htd::LimitChildCountOperation * htd::LimitChildCountOperation::clone(void) const
{
    return new htd::LimitChildCountOperation(limit_);
}

#endif /* HTD_HTD_LIMITCHILDCOUNTOPERATION_CPP */
