/*
 * File:   JoinNodeNormalizationOperation.cpp
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

#ifndef HTD_HTD_JOINNODENORMALIZATIONOPERATION_CPP
#define	HTD_HTD_JOINNODENORMALIZATIONOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/JoinNodeNormalizationOperation.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/Collection.hpp>

#include <algorithm>

htd::JoinNodeNormalizationOperation::JoinNodeNormalizationOperation(void) : identicalParent_(false)
{

}

htd::JoinNodeNormalizationOperation::JoinNodeNormalizationOperation(bool identicalParent) : identicalParent_(identicalParent)
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
    const htd::ConstCollection<htd::vertex_t> & joinNodeCollection = decomposition.joinNodes();

    for (htd::vertex_t node : joinNodeCollection)
    {
        const std::vector<htd::vertex_t> & bag = decomposition.bagContent(node);

        DEBUGGING_CODE(
        std::cout << "JOIN NODE: " << node << std::endl;
        std::cout << "   ";
        htd::print(bag, false);
        std::cout << std::endl << std::endl;
        )

        const htd::FilteredHyperedgeCollection & inducedHyperedges = decomposition.inducedHyperedges(node);

        if (identicalParent_)
        {
            if (decomposition.bagContent(decomposition.parent(node)) != bag)
            {
                htd::vertex_t newParent = decomposition.addParent(node);

                decomposition.setBagContent(newParent, bag);

                decomposition.setInducedHyperedges(newParent, inducedHyperedges);

                for (auto & labelingFunction : labelingFunctions)
                {
                    htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newParent);

                    htd::ILabel * newLabel = labelingFunction->computeLabel(bag, *labelCollection);

                    delete labelCollection;

                    decomposition.setVertexLabel(labelingFunction->name(), newParent, newLabel);
                }
            }
        }

        htd::vertex_container children;

        const htd::ConstCollection<htd::vertex_t> & childContainer = decomposition.children(node);

        std::copy(childContainer.begin(), childContainer.end(), std::back_inserter(children));

        for (htd::vertex_t child : children)
        {
            if (decomposition.bagContent(child) != bag)
            {
                DEBUGGING_CODE(
                std::cout << "   ADDING INTERMEDIATE NODE BETWEEN NODES " << node << " AND " << child << " ..." << std::endl;
                std::cout << "      BAG CONTENT: ";
                htd::print(bag, false);
                std::cout << std::endl << std::endl;
                )

                htd::vertex_t intermediateVertex = decomposition.addParent(child);

                decomposition.setBagContent(intermediateVertex, bag);

                decomposition.setInducedHyperedges(intermediateVertex, inducedHyperedges);

                for (auto & labelingFunction : labelingFunctions)
                {
                    htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(intermediateVertex);

                    htd::ILabel * newLabel = labelingFunction->computeLabel(bag, *labelCollection);

                    delete labelCollection;

                    decomposition.setVertexLabel(labelingFunction->name(), intermediateVertex, newLabel);
                }
            }
        }
    }
}

htd::JoinNodeNormalizationOperation * htd::JoinNodeNormalizationOperation::clone(void) const
{
    return new htd::JoinNodeNormalizationOperation(identicalParent_);
}

#endif /* HTD_HTD_JOINNODENORMALIZATIONOPERATION_CPP */
