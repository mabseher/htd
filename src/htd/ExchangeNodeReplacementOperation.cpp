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
#include <htd/Collection.hpp>
#include <htd/VertexContainerLabel.hpp>

#include <algorithm>

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

    decomposition.getIntroduceNodes(introduceNodes);

    const htd::Collection<htd::vertex_t> forgetNodeCollection = decomposition.joinNodes();

    std::copy(forgetNodeCollection.begin(), forgetNodeCollection.end(), std::back_inserter(forgetNodes));

    std::set_intersection(forgetNodes.begin(), forgetNodes.end(), introduceNodes.begin(), introduceNodes.end(), std::back_inserter(exchangeNodes));

    for (htd::vertex_t node : exchangeNodes)
    {
        htd::vertex_container bagContent;

        htd::Collection<htd::vertex_t> bag = decomposition.bagContent(node);

        std::copy(std::begin(bag), std::end(bag), std::back_inserter(bagContent));

        htd::vertex_container children;

        const htd::Collection<htd::vertex_t> childContainer = decomposition.children(node);

        std::copy(childContainer.begin(), childContainer.end(), std::back_inserter(children));

        for (htd::vertex_t child : children)
        {
            htd::vertex_container rememberedVertices;

            decomposition.getRememberedVertices(node, rememberedVertices, child);

            if (rememberedVertices != bagContent)
            {
                htd::vertex_t intermediateVertex = decomposition.addParent(child);

                decomposition.setLabel(htd::ITreeDecomposition::BAG_LABEL_IDENTIFIER, intermediateVertex, new htd::VertexContainerLabel(htd::vertex_container(rememberedVertices.begin(), rememberedVertices.end())));
            }
        }
    }
}

#endif /* HTD_HTD_EXCHANGENODEREPLACEMENTOPERATION_CPP */
