/*
 * File:   ExchangeNodeReplacementOperation.cpp
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

#ifndef HTD_HTD_EXCHANGENODEREPLACEMENTOPERATION_CPP
#define	HTD_HTD_EXCHANGENODEREPLACEMENTOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/ExchangeNodeReplacementOperation.hpp>

#include <algorithm>

htd::ExchangeNodeReplacementOperation::ExchangeNodeReplacementOperation(void)
{
  
}
  
htd::ExchangeNodeReplacementOperation::~ExchangeNodeReplacementOperation()
{
  
}

void htd::ExchangeNodeReplacementOperation::apply(htd::IMutablePathDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::ExchangeNodeReplacementOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    htd::vertex_container forgetNodes;
    htd::vertex_container exchangeNodes;
    htd::vertex_container introduceNodes;

    const htd::ConstCollection<htd::vertex_t> & forgetNodeCollection = decomposition.forgetNodes();
    const htd::ConstCollection<htd::vertex_t> & introduceNodeCollection = decomposition.introduceNodes();

    std::copy(forgetNodeCollection.begin(), forgetNodeCollection.end(), std::back_inserter(forgetNodes));
    std::copy(introduceNodeCollection.begin(), introduceNodeCollection.end(), std::back_inserter(introduceNodes));

    std::set_intersection(forgetNodes.begin(), forgetNodes.end(), introduceNodes.begin(), introduceNodes.end(), std::back_inserter(exchangeNodes));

    for (htd::vertex_t node : exchangeNodes)
    {
        const htd::ConstCollection<htd::vertex_t> & bag = decomposition.bagContent(node);

        htd::vertex_container children;

        const htd::ConstCollection<htd::vertex_t> & childContainer = decomposition.children(node);

        std::copy(childContainer.begin(), childContainer.end(), std::back_inserter(children));

        for (htd::vertex_t child : children)
        {
            const htd::ConstCollection<htd::vertex_t> & rememberedVertices = decomposition.rememberedVertices(node, child);

            if (bag.size() != rememberedVertices.size() || !std::equal(bag.begin(), bag.end(), rememberedVertices.begin()))
            {
                htd::vertex_t newVertex = decomposition.addParent(child);

                decomposition.setBagContent(newVertex, htd::ConstCollection<htd::vertex_t>(rememberedVertices));

                for (auto & labelingFunction : labelingFunctions)
                {
                    htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newVertex);

                    htd::ILabel * newLabel = labelingFunction->computeLabel(bag, *labelCollection);

                    delete labelCollection;

                    decomposition.setVertexLabel(labelingFunction->name(), newVertex, newLabel);
                }
            }
        }
    }
}

void htd::ExchangeNodeReplacementOperation::apply(htd::IMutableTreeDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}
    
void htd::ExchangeNodeReplacementOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    htd::vertex_container forgetNodes;
    htd::vertex_container exchangeNodes;
    htd::vertex_container introduceNodes;

    const htd::ConstCollection<htd::vertex_t> & forgetNodeCollection = decomposition.forgetNodes();
    const htd::ConstCollection<htd::vertex_t> & introduceNodeCollection = decomposition.introduceNodes();

    std::copy(forgetNodeCollection.begin(), forgetNodeCollection.end(), std::back_inserter(forgetNodes));
    std::copy(introduceNodeCollection.begin(), introduceNodeCollection.end(), std::back_inserter(introduceNodes));

    std::set_intersection(forgetNodes.begin(), forgetNodes.end(), introduceNodes.begin(), introduceNodes.end(), std::back_inserter(exchangeNodes));

    for (htd::vertex_t node : exchangeNodes)
    {
        const htd::ConstCollection<htd::vertex_t> & bag = decomposition.bagContent(node);

        htd::vertex_container children;

        const htd::ConstCollection<htd::vertex_t> & childContainer = decomposition.children(node);

        std::copy(childContainer.begin(), childContainer.end(), std::back_inserter(children));

        for (htd::vertex_t child : children)
        {
            const htd::ConstCollection<htd::vertex_t> & rememberedVertices = decomposition.rememberedVertices(node, child);

            if (bag.size() != rememberedVertices.size() || !std::equal(bag.begin(), bag.end(), rememberedVertices.begin()))
            {
                htd::vertex_t newVertex = decomposition.addParent(child);

                decomposition.setBagContent(newVertex, htd::ConstCollection<htd::vertex_t>(rememberedVertices));

                for (auto & labelingFunction : labelingFunctions)
                {
                    htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newVertex);

                    htd::ILabel * newLabel = labelingFunction->computeLabel(bag, *labelCollection);

                    delete labelCollection;

                    decomposition.setVertexLabel(labelingFunction->name(), newVertex, newLabel);
                }
            }
        }
    }
}

htd::ExchangeNodeReplacementOperation * htd::ExchangeNodeReplacementOperation::clone(void) const
{
    return new htd::ExchangeNodeReplacementOperation();
}

#endif /* HTD_HTD_EXCHANGENODEREPLACEMENTOPERATION_CPP */
