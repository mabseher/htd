/*
 * File:   JoinNodeNormalizationOperation.cpp
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

#ifndef HTD_HTD_JOINNODENORMALIZATIONOPERATION_CPP
#define	HTD_HTD_JOINNODENORMALIZATIONOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/JoinNodeNormalizationOperation.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/Collection.hpp>

#include <algorithm>

//TODO Remove
#include <iostream>
#include <htd/Helpers.hpp>

htd::JoinNodeNormalizationOperation::JoinNodeNormalizationOperation(void)
{

}

htd::JoinNodeNormalizationOperation::~JoinNodeNormalizationOperation()
{

}

void htd::JoinNodeNormalizationOperation::apply(htd::IMutableTreeDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::JoinNodeNormalizationOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    htd::vertex_container joinNodes;

    const htd::Collection<htd::vertex_t> joinNodeCollection = decomposition.joinNodes();

    std::copy(joinNodeCollection.begin(), joinNodeCollection.end(), std::back_inserter(joinNodes));

    for (htd::vertex_t node : joinNodes)
    {
        htd::vertex_container bagContent;

        htd::Collection<htd::vertex_t> bag = decomposition.bagContent(node);

        std::copy(std::begin(bag), std::end(bag), std::back_inserter(bagContent));

        DEBUGGING_CODE(
        std::cout << "JOIN NODE: " << node << std::endl;
        std::cout << "   ";
        htd::print(bagContent, false);
        std::cout << std::endl << std::endl;
        )

        htd::vertex_container children;

        const htd::Collection<htd::vertex_t> childContainer = decomposition.children(node);

        std::copy(childContainer.begin(), childContainer.end(), std::back_inserter(children));

        for (htd::vertex_t child : children)
        {
            htd::vertex_container childBagContent;

            htd::Collection<htd::vertex_t> childBag = decomposition.bagContent(child);

            std::copy(std::begin(childBag), std::end(childBag), std::back_inserter(childBagContent));

            if (childBagContent != bagContent)
            {
                DEBUGGING_CODE(
                std::cout << "   ADDING INTERMEDIATE NODE BETWEEN NODES " << node << " AND " << child << " ..." << std::endl;
                std::cout << "      BAG CONTENT: ";
                htd::print(bagContent, false);
                std::cout << std::endl << std::endl;
                )

                htd::vertex_t intermediateVertex = decomposition.addParent(child);

                decomposition.setBagContent(intermediateVertex, htd::Collection<htd::vertex_t>(bagContent.begin(), bagContent.end()));

                for (auto & labelingFunction : labelingFunctions)
                {
                    htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(intermediateVertex);

                    htd::ILabel * newLabel = labelingFunction->computeLabel(htd::Collection<htd::vertex_t>(bagContent.begin(), bagContent.end()), *labelCollection);

                    delete labelCollection;

                    decomposition.setVertexLabel(labelingFunction->name(), intermediateVertex, newLabel);
                }
            }
        }
    }
}

htd::JoinNodeNormalizationOperation * htd::JoinNodeNormalizationOperation::clone(void) const
{
    return new htd::JoinNodeNormalizationOperation();
}

#endif /* HTD_HTD_JOINNODENORMALIZATIONOPERATION_CPP */
