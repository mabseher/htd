/*
 * File:   LimitChildCountOperation.cpp
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

#ifndef HTD_HTD_LIMITCHILDCOUNTOPERATION_CPP
#define	HTD_HTD_LIMITCHILDCOUNTOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/LimitChildCountOperation.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/Collection.hpp>
#include <htd/VertexContainerLabel.hpp>

#include <algorithm>
#include <stdexcept>

//TODO Remove
#include <iostream>
#include <iterator>
#include <htd/Helpers.hpp>

htd::LimitChildCountOperation::LimitChildCountOperation(std::size_t limit) : limit_(limit)
{

}

htd::LimitChildCountOperation::~LimitChildCountOperation()
{

}

void htd::LimitChildCountOperation::apply(htd::IMutableTreeDecomposition & decomposition) const
{
    htd::vertex_container joinNodes;

    decomposition.getJoinNodes(joinNodes);

    for (htd::vertex_t node : joinNodes)
    {
        std::size_t childCount = decomposition.childCount(node);

        if (childCount > limit_)
        {
            htd::vertex_t newNode = decomposition.addChild(node);

            htd::Collection<htd::vertex_t> bagContent = decomposition.bagContent(node);

            decomposition.setLabel(htd::ITreeDecomposition::BAG_LABEL_IDENTIFIER, newNode, new htd::VertexContainerLabel(htd::vertex_container(bagContent.begin(), bagContent.end())));

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

            const htd::Collection<htd::vertex_t> childContainer = decomposition.children(node);

            std::copy(childContainer.begin(), childContainer.end(), std::back_inserter(children));

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

                    htd::print(newChildren2);
                    std::cout << std::endl;

                    newNode = decomposition.addParent(newNode);

                    decomposition.setLabel(htd::ITreeDecomposition::BAG_LABEL_IDENTIFIER, newNode, new htd::VertexContainerLabel(htd::vertex_container(bagContent.begin(), bagContent.end())));

                    for (auto it = start; it != finish; ++it)
                    {
                        decomposition.setParent(*it, newNode);
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

#endif /* HTD_HTD_LIMITCHILDCOUNTOPERATION_CPP */
