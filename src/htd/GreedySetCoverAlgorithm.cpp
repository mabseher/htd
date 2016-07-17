/* 
 * File:   GreedySetCoverAlgorithm.cpp
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

#ifndef HTD_HTD_GREEDYSETCOVERALGORITHM_CPP
#define	HTD_HTD_GREEDYSETCOVERALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/GreedySetCoverAlgorithm.hpp>
#include <htd/VectorAdapter.hpp>

#include <algorithm>
#include <numeric>

htd::GreedySetCoverAlgorithm::GreedySetCoverAlgorithm(void) : htd::LibraryObject()
{
    
}
            
htd::GreedySetCoverAlgorithm::~GreedySetCoverAlgorithm()
{
    
}

void htd::GreedySetCoverAlgorithm::computeSetCover(const std::vector<htd::id_t> & elements, const std::vector<std::vector<htd::id_t>> & containers, std::vector<htd::index_t> & target) const
{
    if (!elements.empty())
    {
        std::vector<htd::id_t> relevantElements(elements.begin(), elements.end());

        std::vector<htd::id_t> newRelevantElements;

        std::vector<htd::index_t> relevantContainers(containers.size());

        std::vector<htd::index_t> newRelevantContainers;

        std::vector<htd::index_t> irrelevantContainers;

        std::vector<htd::index_t> result;

        std::size_t bestOverlap = 1;

        std::iota(relevantContainers.begin(), relevantContainers.end(), 0);

        while (!relevantElements.empty() && bestOverlap > 0)
        {
            htd::index_t bestPosition = 0;

            bestOverlap = 0;

            for (htd::index_t containerIndex : relevantContainers)
            {
                const std::vector<htd::id_t> & container = containers[containerIndex];

                std::size_t currentOverlap = htd::set_intersection_size(relevantElements.begin(), relevantElements.end(), container.begin(), container.end());

                if (currentOverlap == 0)
                {
                    irrelevantContainers.push_back(containerIndex);
                }
                else if (currentOverlap > bestOverlap)
                {
                    bestOverlap = currentOverlap;

                    bestPosition = containerIndex;
                }
            }

            if (bestOverlap > 0)
            {
                result.push_back(bestPosition);

                const std::vector<htd::id_t> & selectedContainer = containers[bestPosition];

                newRelevantElements.clear();

                htd::set_difference(relevantElements, selectedContainer, newRelevantElements);

                std::swap(relevantElements, newRelevantElements);

                if (irrelevantContainers.size() > 0)
                {
                    irrelevantContainers.insert(std::lower_bound(irrelevantContainers.begin(), irrelevantContainers.end(), bestPosition), bestPosition);

                    std::set_difference(relevantContainers.begin(), relevantContainers.end(), irrelevantContainers.begin(), irrelevantContainers.end(), std::back_inserter(newRelevantContainers));

                    relevantContainers.swap(newRelevantContainers);

                    newRelevantContainers.clear();

                    irrelevantContainers.clear();
                }
                else
                {
                    relevantContainers.erase(std::lower_bound(relevantContainers.begin(), relevantContainers.end(), bestPosition));
                }
            }
        }

        std::sort(result.begin(), result.end());

        std::copy(result.begin(), result.end(), std::back_inserter(target));
    }
}

void htd::GreedySetCoverAlgorithm::computeSetCover(const htd::ConstCollection<htd::id_t> & elements, const htd::ConstCollection<std::vector<htd::id_t>> & containers, std::vector<htd::index_t> & target) const
{
    if (!elements.empty())
    {
        computeSetCover(std::vector<htd::id_t>(elements.begin(), elements.end()), std::vector<std::vector<htd::id_t>>(containers.begin(), containers.end()), target);
    }
}

htd::GreedySetCoverAlgorithm * htd::GreedySetCoverAlgorithm::clone(void) const
{
    return new htd::GreedySetCoverAlgorithm();
}

#endif /* HTD_HTD_GREEDYSETCOVERALGORITHM_CPP */
