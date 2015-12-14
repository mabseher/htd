/* 
 * File:   HeuristicSetCoverAlgorithm.cpp
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

#ifndef HTD_HTD_HEURISTICSETCOVERALGORITHM_CPP
#define	HTD_HTD_HEURISTICSETCOVERALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/HeuristicSetCoverAlgorithm.hpp>

#include <cstdlib>
#include <algorithm>
#include <unordered_set>

htd::HeuristicSetCoverAlgorithm::HeuristicSetCoverAlgorithm(void)
{
    
}
            
htd::HeuristicSetCoverAlgorithm::~HeuristicSetCoverAlgorithm()
{
    
}

void htd::HeuristicSetCoverAlgorithm::computeSetCover(const htd::vertex_container& vertices, const std::vector<htd::vertex_container>& containers, std::vector<htd::vertex_container> & result) const
{
    std::vector<htd::id_t> relevantContainers;

    std::unordered_set<htd::id_t> remainder(vertices.begin(), vertices.end());

    std::vector<htd::HeuristicSetCoverAlgorithm::HistoryEntry> oldNeighborhood;

    std::vector<htd::HeuristicSetCoverAlgorithm::HistoryEntry> newNeighborhood;

    std::vector<std::vector<htd::id_t>> solutions;

    for (htd::index_t index = 0; index < containers.size(); index++)
    {
        if (htd::has_non_empty_set_intersection(vertices.begin(), vertices.end(), containers[index].begin(), containers[index].end()))
        {
            relevantContainers.push_back(index);
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

    newNeighborhood.push_back(htd::HeuristicSetCoverAlgorithm::HistoryEntry(std::vector<htd::id_t>(), remainder, relevantContainers));

    std::size_t oldSolutionCount = 0;

    std::size_t bestSolutionFitness = (std::size_t)-1;

    for (std::size_t iteration = 0; iteration < 3; iteration++)
    {
        std::size_t attempt = 0;

        while (solutions.size() == oldSolutionCount && (attempt < maximumAttempts || solutions.empty()))
        {
            std::swap(oldNeighborhood, newNeighborhood);

            newNeighborhood.clear();

            populateNeighborhood(containers, newNeighborhood, bestSolutionFitness, oldNeighborhood);

            for (auto & neighbor : newNeighborhood)
            {
                if (neighbor.remainder.empty())
                {
                    std::sort(neighbor.selection.begin(), neighbor.selection.end());

                    if (neighbor.selection.size() < bestSolutionFitness)
                    {
                        solutions.clear();

                        oldSolutionCount = 0;

                        bestSolutionFitness = neighbor.selection.size();
                    }

                    if (neighbor.selection.size() == bestSolutionFitness)
                    {
                        solutions.push_back(neighbor.selection);
                    }
                }
            }

            attempt++;
        }

        oldSolutionCount = solutions.size();
    }

    DEBUGGING_CODE(std::cout << std::endl;)

    if (solutions.size() > 0)
    {
        std::sort(solutions.begin(), solutions.end(), Compare());

        DEBUGGING_CODE(std::size_t count = 0;

        for (const std::vector<htd::id_t>& solution : solutions)
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

        std::cout << "Total solutions: " << count << std::endl << std::endl;
        )

        for (htd::id_t element : solutions[0])
        {
            result.push_back(containers[element]);
        }
    }
}

htd::HeuristicSetCoverAlgorithm * htd::HeuristicSetCoverAlgorithm::clone(void) const
{
    return new htd::HeuristicSetCoverAlgorithm();
}

void htd::HeuristicSetCoverAlgorithm::populateNeighborhood(const std::vector<htd::vertex_container>& containers, std::vector<htd::HeuristicSetCoverAlgorithm::HistoryEntry> & newNeighborhood, std::size_t bestSolutionFitness, const std::vector<htd::HeuristicSetCoverAlgorithm::HistoryEntry> & origin) const
{
    if (origin.size() > 0)
    {
        std::vector<htd::index_t> indices(origin.size());

        std::iota(indices.begin(), indices.end(), 0);

        std::shuffle(indices.begin(), indices.end(), std::default_random_engine());

        indices.resize(indices.size() / 2 + 1);

        for (htd::index_t index : indices)
        {
            populateNeighborhood(containers, newNeighborhood, bestSolutionFitness, origin[index]);
        }
    }

    std::size_t neighborhoodSize = newNeighborhood.size();

    if (neighborhoodSize > maximumTotalNeighborhoodSize)
    {
        std::sort(newNeighborhood.begin(), newNeighborhood.end(), Compare());

        if (maximumTotalNeighborhoodSize >= 5 * 2)
        {
            std::shuffle(newNeighborhood.begin() + maximumTotalNeighborhoodSize - 5, newNeighborhood.end(), std::default_random_engine());
        }

        newNeighborhood.resize(maximumTotalNeighborhoodSize);
    }
}

void htd::HeuristicSetCoverAlgorithm::populateNeighborhood(const std::vector<htd::vertex_container>& containers, std::vector<htd::HeuristicSetCoverAlgorithm::HistoryEntry> & newNeighborhood, std::size_t bestSolutionFitness, const htd::HeuristicSetCoverAlgorithm::HistoryEntry & individual) const
{
    std::vector<htd::index_t> indices1(individual.availableChoices.size());
    std::vector<htd::index_t> indices2(individual.selection.size());

    std::iota(indices1.begin(), indices1.end(), 0);
    std::iota(indices2.begin(), indices2.end(), 0);

    std::shuffle(indices1.begin(), indices1.end(), std::default_random_engine());
    std::shuffle(indices2.begin(), indices2.end(), std::default_random_engine());

    //TODO
    HTD_UNUSED(bestSolutionFitness);

    if (indices1.size() > maximumNeighborhoodSize)
    {
        indices1.resize(maximumNeighborhoodSize);
    }

    if (indices2.size() > maximumNeighborhoodSize)
    {
        indices2.resize(maximumNeighborhoodSize);
    }

    for (htd::index_t index : indices1)
    {
        htd::id_t newChoice = individual.availableChoices[index];

        auto & selectedContainer = containers[newChoice];

        newNeighborhood.push_back(htd::HeuristicSetCoverAlgorithm::HistoryEntry(individual.selection, individual.remainder, individual.availableChoices));

        auto & newEntry = newNeighborhood[newNeighborhood.size() - 1];

        for (htd::id_t element : selectedContainer)
        {
            newEntry.remainder.erase(element);
        }

        newEntry.selection.push_back(newChoice);

        auto position = std::find(newEntry.availableChoices.begin(), newEntry.availableChoices.end(), newChoice);

        if (position != newEntry.availableChoices.end())
        {
            newEntry.availableChoices.erase(position);
        }
    }

    for (htd::index_t index : indices2)
    {
        htd::id_t oldChoice = individual.selection[index];

        auto & selectedContainer = containers[oldChoice];

        newNeighborhood.push_back(htd::HeuristicSetCoverAlgorithm::HistoryEntry(individual.selection, individual.remainder, individual.availableChoices));

        auto & newEntry = newNeighborhood[newNeighborhood.size() - 1];

        std::unordered_set<htd::id_t> remainder(selectedContainer.begin(), selectedContainer.end());

        for (auto it1 = individual.selection.begin(); remainder.size() > 0 && it1 != individual.selection.end(); it1++)
        {
            htd::id_t selection = *it1;

            if (selection != oldChoice)
            {
                for (auto it2 = containers[selection].begin(); remainder.size() > 0 && it2 != containers[selection].end(); it2++)
                {
                    remainder.erase(*it2);
                }
            }
        }

        newEntry.remainder.insert(remainder.begin(), remainder.end());

        newEntry.availableChoices.push_back(oldChoice);

        auto position = std::find(newEntry.selection.begin(), newEntry.selection.end(), oldChoice);

        if (position != newEntry.selection.end())
        {
            newEntry.selection.erase(position);
        }
    }
}

#endif /* HTD_HTD_HEURISTICSETCOVERALGORITHM_CPP */
