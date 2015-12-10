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

        DEBUGGING_CODE(
        std::cout << "FORGET NODE: " << node << std::endl;
        std::cout << "   ";
        htd::print(bagContent, false);
        std::cout << std::endl << "   FORGOTTEN VERTEX COUNT: " << forgottenVertexCount << std::endl << std::endl;
        )

        if (forgottenVertexCount > limit_)
        {
            DEBUGGING_CODE(std::cout << "VIOLATION: " << node << std::endl << std::endl;)

            htd::vertex_container forgottenVertices;
            htd::vertex_container rememberedVertices;

            decomposition.getForgottenVertices(node, forgottenVertices);
            decomposition.getRememberedVertices(node, rememberedVertices);

            DEBUGGING_CODE(
            std::cout << "FORGOTTEN: ";
            htd::print(forgottenVertices, false);
            std::cout << std::endl;

            std::cout << "REMEMBERED: ";
            htd::print(rememberedVertices, false);
            std::cout << std::endl;
            )

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

            if (children.empty())
            {
                auto start = forgottenVertices.begin();
                auto finish = forgottenVertices.end() - (remainder > 0 ? remainder : limit_);

                htd::vertex_t newNode = decomposition.addChild(node);

                decomposition.setLabel(htd::ITreeDecomposition::BAG_LABEL_IDENTIFIER, newNode, new htd::VertexContainerLabel(htd::vertex_container(start, finish)));

                if (intermediatedVerticesCount > 0)
                {
                    finish = finish - limit_;

                    for (htd::index_t index = 0; index < intermediatedVerticesCount; index++)
                    {
                        newNode = decomposition.addParent(newNode);

                        decomposition.setLabel(htd::ITreeDecomposition::BAG_LABEL_IDENTIFIER, newNode, new htd::VertexContainerLabel(htd::vertex_container(start, finish)));

                        if (index < forgottenVertexCount + limit_)
                        {
                            finish = finish - limit_;
                        }
                    }
                }
            }
            else if (children.size() == 1)
            {
                htd::vertex_t child = children[0];

                auto start = forgottenVertices.begin();
                auto finish = forgottenVertices.end() - (remainder > 0 ? remainder : limit_);

                htd::vertex_t newNode = decomposition.addParent(child);

                decomposition.setLabel(htd::ITreeDecomposition::BAG_LABEL_IDENTIFIER, newNode, new htd::VertexContainerLabel(htd::vertex_container(start, finish)));

                if (intermediatedVerticesCount > 0)
                {
                    finish = finish - limit_;

                    for (htd::index_t index = 0; index < intermediatedVerticesCount; index++)
                    {
                        newNode = decomposition.addParent(newNode);

                        decomposition.setLabel(htd::ITreeDecomposition::BAG_LABEL_IDENTIFIER, newNode, new htd::VertexContainerLabel(htd::vertex_container(start, finish)));

                        if (index < forgottenVertexCount + limit_)
                        {
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
