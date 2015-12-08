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
            std::cout << "VIOLATION: " << node << std::endl << std::endl;

            htd::vertex_container forgottenVertices;
            htd::vertex_container rememberedVertices;

            decomposition.getForgottenVertices(node, forgottenVertices);
            decomposition.getRememberedVertices(node, rememberedVertices);

            std::cout << "FORGOTTEN: ";
            htd::print(forgottenVertices, false);
            std::cout << std::endl;

            std::cout << "REMEMBERED: ";
            htd::print(rememberedVertices, false);
            std::cout << std::endl;

            std::size_t remainder = forgottenVertexCount % limit_;

            forgottenVertexCount -= remainder;

            std::size_t intermediatedVerticesCount = forgottenVertexCount / limit_;

            if (intermediatedVerticesCount > 0)
            {
                intermediatedVerticesCount--;
            }

            std::cout << "SPLIT: " << remainder << " + " << intermediatedVerticesCount << " x " << limit_ << std::endl << std::endl;

            //TODO Implement
        }
    }
}

#endif /* HTD_HTD_LIMITMAXIMUMFORGOTTENVERTICESCOUNTOPERATION_CPP */
