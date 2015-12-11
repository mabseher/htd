/*
 * File:   LimitMaximumForgottenVerticesCountOperation.cpp
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

#ifndef HTD_HTD_LIMITMAXIMUMFORGOTTENVERTICESCOUNTOPERATION_CPP
#define	HTD_HTD_LIMITMAXIMUMFORGOTTENVERTICESCOUNTOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/LimitMaximumForgottenVerticesCountOperation.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/VertexContainerLabel.hpp>

//TODO Remove
#include <iostream>
#include <htd/Helpers.hpp>

htd::LimitMaximumForgottenVerticesCountOperation::LimitMaximumForgottenVerticesCountOperation(std::size_t limit) : limit_(limit)
{
  
}
  
htd::LimitMaximumForgottenVerticesCountOperation::~LimitMaximumForgottenVerticesCountOperation()
{
  
}
    
void htd::LimitMaximumForgottenVerticesCountOperation::apply(htd::IMutableTreeDecomposition & decomposition) const
{
    htd::vertex_container forgetNodes;

    decomposition.getForgetNodes(forgetNodes);

    for (htd::vertex_t node : forgetNodes)
    {
        htd::vertex_container bagContent;

        htd::Collection<htd::vertex_t> bag = decomposition.bagContent(node);

        std::copy(std::begin(bag), std::end(bag), std::back_inserter(bagContent));

        std::size_t forgottenVertexCount = decomposition.forgottenVertexCount(node);

        if (forgottenVertexCount > limit_)
        {
            htd::vertex_container forgottenVertices;
            htd::vertex_container rememberedVertices;

            decomposition.getForgottenVertices(node, forgottenVertices);
            decomposition.getRememberedVertices(node, rememberedVertices);

            std::size_t remainder = forgottenVertexCount % limit_;

            forgottenVertexCount -= remainder;

            std::size_t intermediatedVerticesCount = forgottenVertexCount / limit_;

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

            if (children.size() == 1)
            {
                htd::vertex_t child = children[0];

                auto start = forgottenVertices.end() - limit_;
                auto finish = forgottenVertices.end();

                htd::vertex_t newNode = decomposition.addParent(child);

                std::vector<htd::vertex_t> newContent;

                htd::Collection<htd::vertex_t> bagContent = decomposition.bagContent(child);

                std::set_difference(bagContent.begin(), bagContent.end(), start, finish, std::back_inserter(newContent));

                decomposition.setLabel(htd::ITreeDecomposition::BAG_LABEL_IDENTIFIER, newNode, new htd::VertexContainerLabel(newContent));

                if (intermediatedVerticesCount > 0)
                {
                    start = start - limit_;
                    finish = finish - limit_;

                    for (htd::index_t index = 0; index < intermediatedVerticesCount; index++)
                    {
                        htd::Collection<htd::vertex_t> bagContent2 = decomposition.bagContent(newNode);

                        newNode = decomposition.addParent(newNode);

                        newContent.clear();

                        std::set_difference(bagContent2.begin(), bagContent2.end(), start, finish, std::back_inserter(newContent));

                        decomposition.setLabel(htd::ITreeDecomposition::BAG_LABEL_IDENTIFIER, newNode, new htd::VertexContainerLabel(newContent));

                        if (index < forgottenVertexCount + limit_)
                        {
                            start = start - limit_;
                            finish = finish - limit_;
                        }
                    }
                }
            }
            else
            {
                throw std::logic_error("void htd::LimitMaximumIntroducedVerticesCountOperation::apply(htd::IMutableTreeDecomposition &) const");

                //TODO Implement also for multiple children
                /*
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
                */
            }
        }
    }
}

#endif /* HTD_HTD_LIMITMAXIMUMFORGOTTENVERTICESCOUNTOPERATION_CPP */
