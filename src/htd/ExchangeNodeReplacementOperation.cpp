/*
 * File:   ExchangeNodeReplacementOperation.cpp
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

#ifndef HTD_HTD_EXCHANGENODEREPLACEMENTOPERATION_CPP
#define	HTD_HTD_EXCHANGENODEREPLACEMENTOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/ExchangeNodeReplacementOperation.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/VertexContainerLabel.hpp>

//TODO Remove
#include <iostream>
#include <htd/Helpers.hpp>

htd::ExchangeNodeReplacementOperation::ExchangeNodeReplacementOperation(void)
{
  
}
  
htd::ExchangeNodeReplacementOperation::~ExchangeNodeReplacementOperation()
{
  
}
    
void htd::ExchangeNodeReplacementOperation::apply(htd::IMutableTreeDecomposition & decomposition) const
{
    htd::vertex_container forgetNodes;
    htd::vertex_container exchangeNodes;
    htd::vertex_container introduceNodes;

    decomposition.getForgetNodes(forgetNodes);
    decomposition.getIntroduceNodes(introduceNodes);

    std::cout << "FORGET NODES:    ";
    htd::print(forgetNodes, false);
    std::cout << std::endl;

    std::cout << "INTRODUCE NODES: ";
    htd::print(introduceNodes, false);
    std::cout << std::endl;

    std::set_intersection(forgetNodes.begin(), forgetNodes.end(), introduceNodes.begin(), introduceNodes.end(), std::back_inserter(exchangeNodes));

    for (htd::vertex_t node : exchangeNodes)
    {
        htd::vertex_container bagContent;

        htd::Collection<htd::vertex_t> bag = decomposition.bagContent(node);

        std::copy(std::begin(bag), std::end(bag), std::back_inserter(bagContent));

        DEBUGGING_CODE(
        std::cout << "EXCHANGE NODE: " << node << std::endl;
        std::cout << "   ";
        htd::print(bagContent, false);
        std::cout << std::endl << std::endl;
        )

        htd::vertex_container children;

        decomposition.getChildren(node, children);

        for (htd::vertex_t child : children)
        {
            htd::vertex_container rememberedVertices;

            decomposition.getRememberedVertices(node, rememberedVertices, child);

            if (rememberedVertices != bagContent)
            {
                DEBUGGING_CODE(
                std::cout << "   ADDING INTERMEDIATE NODE BETWEEN NODES " << node << " AND " << child << " ..." << std::endl;
                std::cout << "      BAG CONTENT: ";
                htd::print(rememberedVertices, false);
                std::cout << std::endl << std::endl;
                )

                htd::vertex_t intermediateVertex = decomposition.addParent(child);

                decomposition.setLabel(htd::ITreeDecomposition::BAG_LABEL_IDENTIFIER, intermediateVertex, new htd::VertexContainerLabel(htd::vertex_container(rememberedVertices.begin(), rememberedVertices.end())));
            }
        }
    }
}

#endif /* HTD_HTD_EXCHANGENODEREPLACEMENTOPERATION_CPP */
