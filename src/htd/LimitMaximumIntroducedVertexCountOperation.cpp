/*
 * File:   LimitMaximumIntroducedVertexCountOperation.cpp
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

#ifndef HTD_HTD_LIMITMAXIMUMINTRODUCEDVERTEXCOUNTOPERATION_CPP
#define	HTD_HTD_LIMITMAXIMUMINTRODUCEDVERTEXCOUNTOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/LimitMaximumIntroducedVertexCountOperation.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/Collection.hpp>
#include <htd/VertexContainerLabel.hpp>

#include <algorithm>
#include <stdexcept>

//TODO Remove
#include <iostream>
#include <iterator>
#include <htd/Helpers.hpp>

htd::LimitMaximumIntroducedVertexCountOperation::LimitMaximumIntroducedVertexCountOperation(std::size_t limit) : limit_(limit)
{
  
}
  
htd::LimitMaximumIntroducedVertexCountOperation::~LimitMaximumIntroducedVertexCountOperation()
{
  
}
    
void htd::LimitMaximumIntroducedVertexCountOperation::apply(htd::IMutableTreeDecomposition & decomposition) const
{
    htd::vertex_container introduceNodes;

    const htd::Collection<htd::vertex_t> introduceNodeCollection = decomposition.introduceNodes();

    std::copy(introduceNodeCollection.begin(), introduceNodeCollection.end(), std::back_inserter(introduceNodes));

    for (htd::vertex_t node : introduceNodes)
    {
        htd::vertex_container bagContent;

        htd::Collection<htd::vertex_t> bag = decomposition.bagContent(node);

        std::copy(std::begin(bag), std::end(bag), std::back_inserter(bagContent));

        std::size_t introducedVertexCount = decomposition.introducedVertexCount(node);

        if (introducedVertexCount > limit_)
        {
            htd::vertex_container introducedVertices;

            const htd::Collection<htd::vertex_t> introducedVertexCollection = decomposition.introducedVertices(node);

            std::copy(introducedVertexCollection.begin(), introducedVertexCollection.end(), std::back_inserter(introducedVertices));

            std::size_t remainder = introducedVertexCount % limit_;

            introducedVertexCount -= remainder;

            std::size_t intermediatedVertexCount = introducedVertexCount / limit_;

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

            if (children.empty())
            {
                auto start = introducedVertices.begin();
                auto finish = introducedVertices.begin() + (remainder > 0 ? remainder : limit_);

                htd::vertex_t newNode = decomposition.addChild(node);

                decomposition.setLabel(htd::ITreeDecomposition::BAG_LABEL_IDENTIFIER, newNode, new htd::VertexContainerLabel(htd::vertex_container(start, finish)));

                if (intermediatedVertexCount > 0)
                {
                    std::advance(finish, limit_);

                    for (htd::index_t index = 0; index < intermediatedVertexCount; index++)
                    {
                        newNode = decomposition.addParent(newNode);

                        decomposition.setLabel(htd::ITreeDecomposition::BAG_LABEL_IDENTIFIER, newNode, new htd::VertexContainerLabel(htd::vertex_container(start, finish)));

                        if (index < introducedVertexCount + limit_)
                        {
                            std::advance(finish, limit_);
                        }
                    }
                }
            }
            else if (children.size() == 1)
            {
                htd::vertex_t child = children[0];

                auto start = introducedVertices.begin();
                auto finish = introducedVertices.begin() + (remainder > 0 ? remainder : limit_);

                htd::vertex_t newNode = decomposition.addParent(child);

                std::vector<htd::vertex_t> newContent;

                htd::Collection<htd::vertex_t> bagContent = decomposition.bagContent(child);

                std::set_union(bagContent.begin(), bagContent.end(), start, finish, std::back_inserter(newContent));

                decomposition.setLabel(htd::ITreeDecomposition::BAG_LABEL_IDENTIFIER, newNode, new htd::VertexContainerLabel(newContent));

                if (intermediatedVertexCount > 0)
                {
                    std::advance(start, limit_);
                    std::advance(finish, limit_);

                    for (htd::index_t index = 0; index < intermediatedVertexCount; index++)
                    {
                        newNode = decomposition.addParent(newNode);

                        for (auto it = start; it != finish; it++)
                        {
                            newContent.push_back(*it);
                        }

                        decomposition.setLabel(htd::ITreeDecomposition::BAG_LABEL_IDENTIFIER, newNode, new htd::VertexContainerLabel(newContent));

                        if (index < introducedVertexCount + limit_)
                        {
                            std::advance(start, limit_);
                            std::advance(finish, limit_);
                        }
                    }
                }
            }
            else
            {
                throw std::logic_error("void htd::LimitMaximumIntroducedVertexCountOperation::apply(htd::IMutableTreeDecomposition &) const");
            }
        }
    }
}

#endif /* HTD_HTD_LIMITMAXIMUMINTRODUCEDVERTEXCOUNTOPERATION_CPP */
