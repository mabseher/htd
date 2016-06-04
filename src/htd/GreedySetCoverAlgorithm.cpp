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

htd::GreedySetCoverAlgorithm::GreedySetCoverAlgorithm(void)
{
    
}
            
htd::GreedySetCoverAlgorithm::~GreedySetCoverAlgorithm()
{
    
}

void htd::GreedySetCoverAlgorithm::computeSetCover(const std::vector<htd::id_t> & elements, const std::vector<std::vector<htd::id_t>> & containers, std::vector<htd::index_t> & target) const
{
    computeSetCover(htd::ConstCollection<htd::id_t>::getInstance(elements), htd::ConstCollection<std::vector<htd::id_t>>::getInstance(containers), target);
}

void htd::GreedySetCoverAlgorithm::computeSetCover(const htd::ConstCollection<htd::id_t> & elements, const htd::ConstCollection<std::vector<htd::id_t>> & containers, std::vector<htd::index_t> & target) const
{
    if (!elements.empty())
    {
        std::vector<htd::id_t> relevantElements(elements.begin(), elements.end());

        std::vector<std::pair<htd::index_t, std::vector<htd::id_t>>> relevantContainers;

        std::vector<htd::index_t> irrelevantContainers;

        std::vector<htd::index_t> result;

        htd::index_t currentPosition = 0;

        for (const std::vector<htd::id_t> & container : containers)
        {
            relevantContainers.push_back(std::make_pair(currentPosition, container));

            ++currentPosition;
        }

        std::size_t bestOverlap = 1;

        while (!relevantElements.empty() && bestOverlap > 0)
        {
            htd::index_t bestPosition = 0;

            bestOverlap = 0;

            currentPosition = 0;

            irrelevantContainers.clear();

            for (const std::pair<htd::index_t, std::vector<htd::id_t>> & container : relevantContainers)
            {
                std::size_t currentOverlap = htd::set_intersection_size(relevantElements.begin(), relevantElements.end(), container.second.begin(), container.second.end());

                if (currentOverlap == 0)
                {
                    irrelevantContainers.push_back(container.first);
                }
                else if (currentOverlap > bestOverlap)
                {
                    bestOverlap = currentOverlap;

                    bestPosition = currentPosition;
                }

                ++currentPosition;
            }

            result.push_back(relevantContainers[bestPosition].first);

            const std::vector<htd::id_t> & selectedContainer = relevantContainers[bestPosition].second;

            std::vector<htd::vertex_t> newRelevantElements;

            htd::set_difference(relevantElements, selectedContainer, newRelevantElements);

            std::swap(relevantElements, newRelevantElements);

            relevantContainers.erase(relevantContainers.begin() + bestPosition);

            if (irrelevantContainers.size() > 0)
            {
                currentPosition = 0;

                relevantContainers.erase(std::remove_if(relevantContainers.begin(), relevantContainers.end(), [&](const std::pair<htd::index_t, std::vector<htd::id_t>> & container)
                {
                    bool ret = false;

                    if (currentPosition < irrelevantContainers.size() && container.first == irrelevantContainers[currentPosition])
                    {
                        ++currentPosition;

                        ret = true;
                    }

                    return ret;
                }), relevantContainers.end());
            }

            currentPosition = 0;
        }

        std::sort(result.begin(), result.end());

        std::copy(result.begin(), result.end(), std::back_inserter(target));
    }
}

htd::GreedySetCoverAlgorithm * htd::GreedySetCoverAlgorithm::clone(void) const
{
    return new htd::GreedySetCoverAlgorithm();
}

#endif /* HTD_HTD_GREEDYSETCOVERALGORITHM_CPP */
