/* 
 * File:   SetCoverAlgorithm.cpp
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

#ifndef HTD_HTD_SETCOVERALGORITHM_CPP
#define	HTD_HTD_SETCOVERALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/SetCoverAlgorithm.hpp>

#include <deque>
#include <iterator>
#include <queue>
#include <unordered_map>
#include <vector>

htd::SetCoverAlgorithm::SetCoverAlgorithm(void)
{
    
}
            
htd::SetCoverAlgorithm::~SetCoverAlgorithm()
{
    
}

void htd::SetCoverAlgorithm::computeSetCover(const htd::vertex_container& vertices, const std::vector<htd::vertex_container>& containers, std::vector<htd::vertex_container> & result) const
{
    htd::id_t next = 0;
    
    std::deque<HistoryEntry> history;

    std::vector<htd::id_t> relevantContainers;
    
    std::vector<htd::id_t> oldRelevantContainers;
    
    std::vector<std::vector<htd::id_t>> solutions;
    
    std::vector<htd::id_t> remainder(vertices);

    std::unordered_map<htd::id_t, std::size_t> additionalCoverage;

    std::size_t minimumCoverSize = (std::size_t)-1;

    for (htd::index_t index = 0; index < containers.size(); index++)
    {
        std::size_t coverage = htd::compute_set_intersection_size(remainder.begin(), remainder.end(), containers[index].begin(), containers[index].end());

        if (coverage > 0)
        {
            relevantContainers.push_back(index);

            additionalCoverage[index] = coverage;
        }
    }

    std::sort(relevantContainers.begin(), relevantContainers.end(), [&](htd::id_t container1, htd::id_t container2) { return containers[container1].size() > containers[container2].size(); });

    std::unordered_set<htd::id_t> dominatedContainers;

    for (auto it1 = relevantContainers.begin(); it1 < relevantContainers.end(); it1++)
    {
        htd::id_t container = *it1;

        for (auto it2 = it1 + 1; it2 < relevantContainers.end(); it2++)
        {
            if (std::includes(containers[container].begin(), containers[container].end(), containers[*it2].begin(), containers[*it2].end()))
            {
                dominatedContainers.insert(*it2);
            }
        }
    }

    std::sort(relevantContainers.begin(), relevantContainers.end());

    for (htd::id_t dominatedContainer : dominatedContainers)
    {
        auto position = std::lower_bound(relevantContainers.begin(), relevantContainers.end(), dominatedContainer);

        if (position != relevantContainers.end())
        {
            relevantContainers.erase(position);
        }
    }

    DEBUGGING_CODE(
    std::cout << "Set cover: " << std::endl << "   ";
    htd::print(vertices, false);
    std::cout << std::endl << std::endl;

    for (htd::index_t container : relevantContainers)
    {
        std::cout << "   Relevant container: " << container << "   (";
        htd::print(containers[container], false);
        std::cout << std::endl;
    })

    std::sort(relevantContainers.begin(), relevantContainers.end(), [&](htd::id_t left, htd::id_t right) { return additionalCoverage[left] > additionalCoverage[right]; });

    while (relevantContainers.size() > 0)
    {
        std::swap(relevantContainers, oldRelevantContainers);
        
        relevantContainers.clear();
        additionalCoverage.clear();

        if (history.size() < minimumCoverSize && next < oldRelevantContainers.size())
        {
            htd::id_t selected = next;

            history.push_back(HistoryEntry(selected, remainder, oldRelevantContainers));

            DEBUGGING_CODE(std::cout << "Selected: " << oldRelevantContainers[selected] << std::endl << "   ";)
            DEBUGGING_CODE(htd::print(containers[oldRelevantContainers[selected]], false);)
            DEBUGGING_CODE(std::cout << std::endl << std::endl;)

            for (htd::id_t vertex : containers[oldRelevantContainers[selected]])
            {
                std::vector<htd::id_t>::iterator position = std::find(remainder.begin(), remainder.end(), vertex);

                if (position != remainder.end())
                {
                    remainder.erase(position);
                }
            }

            next = 0;

            if (remainder.size() > 0)
            {
                DEBUGGING_CODE(
                for (htd::id_t vertex : remainder)
                {
                    std::cout << "Remaining: " << vertex << std::endl;
                }

                std::cout << std::endl;)

                htd::index_t index = 0;

                for (htd::id_t container : oldRelevantContainers)
                {
                    DEBUGGING_CODE(std::cout << "Container: " << container << "   ";)
                    DEBUGGING_CODE(htd::print(containers[container], false);)
                    DEBUGGING_CODE(std::cout << std::endl;)

                    std::size_t coverage = htd::compute_set_intersection_size(remainder.begin(), remainder.end(), containers[container].begin(), containers[container].end());

                    if (index > selected && coverage > 0)
                    {
                        DEBUGGING_CODE(std::cout << "Relevant container: " << container << "   ";)
                        DEBUGGING_CODE(htd::print(containers[container], false);)
                        DEBUGGING_CODE(std::cout << std::endl;)

                        relevantContainers.push_back(container);

                        additionalCoverage[container] = coverage;
                    }

                    index++;
                }

                if (relevantContainers.size() > 0)
                {
                    std::sort(relevantContainers.begin(), relevantContainers.end(), [&](htd::id_t left, htd::id_t right) { return additionalCoverage[left] > additionalCoverage[right]; });

                    DEBUGGING_CODE(std::cout << std::endl;)
                
                    next = 0;
                }
                else
                {
                    DEBUGGING_CODE(std::cout << "Backtracking ..." << std::endl;)

                    if (!history.empty())
                    {
                        next = history.back().selectedIndex + 1;

                        remainder = history.back().remainder;

                        relevantContainers = history.back().containers;

                        history.pop_back();

                        DEBUGGING_CODE(std::cout << "   Next container: " << next << std::endl;)
                        DEBUGGING_CODE(std::cout << "   Current remainder: ";)
                        DEBUGGING_CODE(htd::print(remainder, false);)
                        DEBUGGING_CODE(std::cout << std::endl;)

                        DEBUGGING_CODE(std::cout << "   Relevant containers: ";)
                        DEBUGGING_CODE(htd::print(relevantContainers, false);)
                        DEBUGGING_CODE(std::cout << std::endl << std::endl;)
                    }
                    else
                    {
                        DEBUGGING_CODE(std::cout << "   No backtracking history found ..." << std::endl << std::endl;)
                    }
                }
            }
            else
            {
                std::vector<htd::id_t> newSolution;

                newSolution.reserve(history.size());

                for (HistoryEntry& entry : history)
                {
                    newSolution.push_back(entry.containers[entry.selectedIndex]);
                }

                std::sort(newSolution.begin(), newSolution.end());

                DEBUGGING_CODE(std::cout << "Solution:   ";)
                DEBUGGING_CODE(htd::print(newSolution, false);)
                DEBUGGING_CODE(std::cout << std::endl << std::endl;)
                
                DEBUGGING_CODE(std::cout << "Backtracking ..." << std::endl;)

                solutions.push_back(newSolution);

                if (history.size() < minimumCoverSize)
                {
                    minimumCoverSize = history.size();
                }

                next = history.back().selectedIndex + 1;

                remainder = history.back().remainder;

                relevantContainers = history.back().containers;

                history.pop_back();

                DEBUGGING_CODE(std::cout << "   Next container: " << next << std::endl;)
                DEBUGGING_CODE(std::cout << "   Current remainder: ";)
                DEBUGGING_CODE(htd::print(remainder, false);)
                DEBUGGING_CODE(std::cout << std::endl;)

                DEBUGGING_CODE(std::cout << "   Relevant containers: ";)
                DEBUGGING_CODE(htd::print(relevantContainers, false);)
                DEBUGGING_CODE(std::cout << std::endl << std::endl;)
            }
        }
        else
        {
            DEBUGGING_CODE(std::cout << "Backtracking ..." << std::endl;)

            if (!history.empty())
            {
                next = history.back().selectedIndex + 1;

                remainder = history.back().remainder;

                relevantContainers = history.back().containers;

                history.pop_back();

                DEBUGGING_CODE(std::cout << "   Next container: " << next << std::endl;)
                DEBUGGING_CODE(std::cout << "   Current remainder: ";)
                DEBUGGING_CODE(htd::print(remainder, false);)
                DEBUGGING_CODE(std::cout << std::endl;)

                DEBUGGING_CODE(std::cout << "   Relevant containers: ";)
                DEBUGGING_CODE(htd::print(relevantContainers, false);)
                DEBUGGING_CODE(std::cout << std::endl << std::endl;)
            }
            else
            {
                DEBUGGING_CODE(std::cout << "   No backtracking history found ..." << std::endl << std::endl;)
            }
        }
    }
    
    if (solutions.size() > 0)
    {
        std::sort(solutions.begin(), solutions.end(), Compare());

        DEBUGGING_CODE(std::size_t count = 0;
        
        for (const std::vector<htd::id_t>& solution : solutions)
        {
            if (solution.size() == minimumCoverSize)
            {
                std::cout << "Solution: ";
                htd::print(solution, false);
                std::cout << std::endl;

                for (htd::id_t container : solution)
                {
                    std::cout << "   " << container << ":   Content: ";

                    htd::print(containers[container], false);
                    std::cout << std::endl;
                }

                std::cout << std::endl;
                
                count++;
            }
        }
        
        std::cout << "Total solutions: " << count << std::endl << std::endl;
        )
    
        for (htd::id_t element : solutions[0])
        {
            result.push_back(containers[element]);
        }
    }
}

#endif /* HTD_HTD_SETCOVERALGORITHM_CPP */
