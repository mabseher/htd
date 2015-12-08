/*
 * File:   LimitMaximumIntroducedVerticesCountOperation.cpp
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

#ifndef HTD_HTD_LIMITMAXIMUMINTRODUCEDVERTICESCOUNTOPERATION_CPP
#define	HTD_HTD_LIMITMAXIMUMINTRODUCEDVERTICESCOUNTOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/LimitMaximumIntroducedVerticesCountOperation.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/VertexContainerLabel.hpp>

//TODO Remove
#include <iostream>
#include <iterator>
#include <htd/Helpers.hpp>

htd::LimitMaximumIntroducedVerticesCountOperation::LimitMaximumIntroducedVerticesCountOperation(std::size_t limit) : limit_(limit)
{
  
}
  
htd::LimitMaximumIntroducedVerticesCountOperation::~LimitMaximumIntroducedVerticesCountOperation()
{
  
}
    
void htd::LimitMaximumIntroducedVerticesCountOperation::apply(htd::IMutableTreeDecomposition & decomposition) const
{
    htd::vertex_container introduceNodes;

    decomposition.getIntroduceNodes(introduceNodes);

    for (htd::vertex_t node : introduceNodes)
    {
        htd::vertex_container bagContent;

        htd::Collection<htd::vertex_t> bag = decomposition.bagContent(node);

        std::copy(std::begin(bag), std::end(bag), std::back_inserter(bagContent));

        std::size_t introducedVertexCount = decomposition.introducedVertexCount(node);

        DEBUGGING_CODE(
        std::cout << "INTRODUCE NODE: " << node << std::endl;
        std::cout << "   ";
        htd::print(bagContent, false);
        std::cout << std::endl << "   INTRODUCED VERTEX COUNT: " << introducedVertexCount << std::endl << std::endl;
        )

        if (introducedVertexCount > limit_)
        {
            std::cout << "VIOLATION: " << node << std::endl << std::endl;

            htd::vertex_container introducedVertices;
            htd::vertex_container rememberedVertices;

            decomposition.getIntroducedVertices(node, introducedVertices);
            decomposition.getRememberedVertices(node, rememberedVertices);

            std::size_t remainder = introducedVertexCount % limit_;

            introducedVertexCount -= remainder;

            std::size_t intermediatedVerticesCount = introducedVertexCount / limit_;

            if (intermediatedVerticesCount > 0)
            {
                intermediatedVerticesCount--;
            }

            if (remainder == 0)
            {
                intermediatedVerticesCount--;
            }

            htd::vertex_container children;

            decomposition.getChildren(node, children);

            if (children.empty())
            {
                auto start = introducedVertices.begin();
                auto finish = introducedVertices.begin() + (remainder > 0 ? remainder : limit_);

                htd::vertex_t newNode = decomposition.addChild(node);

                decomposition.setLabel(htd::ITreeDecomposition::BAG_LABEL_IDENTIFIER, newNode, new htd::VertexContainerLabel(htd::vertex_container(start, finish)));

                if (intermediatedVerticesCount > 0)
                {
                    std::advance(finish, limit_);

                    for (htd::index_t index = 0; index < intermediatedVerticesCount; index++)
                    {
                        newNode = decomposition.addIntermediateParent(newNode);

                        decomposition.setLabel(htd::ITreeDecomposition::BAG_LABEL_IDENTIFIER, newNode, new htd::VertexContainerLabel(htd::vertex_container(start, finish)));

                        if (index < introducedVertexCount + limit_)
                        {
                            std::advance(finish, limit_);
                        }
                    }
                }
            }
            else
            {
                //TODO Implement

                for (htd::vertex_t child : children)
                {
                    htd::vertex_container addedVertices;

                    decomposition.getIntroducedVertices(node, addedVertices, child);

                    if (addedVertices.size() <= limit_)
                    {
                        std::cout << "MOVEABLE: " << child << std::endl;
                    }
                    else
                    {
                        std::cout << "IMPORTANT: " << child << std::endl;
                    }
                }
            }
        }
    }
}

#endif /* HTD_HTD_LIMITMAXIMUMINTRODUCEDVERTICESCOUNTOPERATION_CPP */
