/* 
 * File:   DepthFirstConnectedComponentAlgorithm.cpp
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

#ifndef HTD_HTD_DEPTHFIRSTCONNECTEDCOMPONENTALGORITHM_CPP
#define	HTD_HTD_DEPTHFIRSTCONNECTEDCOMPONENTALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/DepthFirstConnectedComponentAlgorithm.hpp>
#include <htd/GraphComponentCollection.hpp>
#include <htd/ConstCollection.hpp>

#include <algorithm>
#include <stack>

htd::DepthFirstConnectedComponentAlgorithm::DepthFirstConnectedComponentAlgorithm(void)
{

}

htd::DepthFirstConnectedComponentAlgorithm::~DepthFirstConnectedComponentAlgorithm()
{

}

htd::GraphComponentCollection htd::DepthFirstConnectedComponentAlgorithm::determineComponents(const htd::IHypergraph & graph) const
{
    htd::GraphComponentCollection ret;

    const htd::ConstCollection<htd::vertex_t> & vertexCollection = graph.vertices();

    if (vertexCollection.size() > 0)
    {
        std::stack<htd::vertex_t> originStack;

        std::unordered_set<htd::vertex_t> unvisitedVertices(vertexCollection.begin(), vertexCollection.end());

        while (unvisitedVertices.size() > 0)
        {
            std::vector<htd::vertex_t> component;

            originStack.push(*(unvisitedVertices.begin()));

            while (!originStack.empty())
            {
                component.push_back(originStack.top());
                unvisitedVertices.erase(originStack.top());

                for (htd::vertex_t neighbor : graph.neighbors(originStack.top()))
                {
                    if (unvisitedVertices.count(neighbor) == 1)
                    {
                        originStack.push(neighbor);
                    }
                }

                originStack.pop();
            }

            std::sort(component.begin(), component.end());

            ret.addComponent(htd::ConstCollection<htd::vertex_t>(component));
        }
    }

    return ret;
}

htd::DepthFirstConnectedComponentAlgorithm * htd::DepthFirstConnectedComponentAlgorithm::clone(void) const
{
    return new DepthFirstConnectedComponentAlgorithm();
}

#endif /* HTD_HTD_DEPTHFIRSTCONNECTEDCOMPONENTALGORITHM_CPP */
