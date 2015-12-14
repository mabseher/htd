/* 
 * File:   HeuristicSetCoverAlgorithm.hpp
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

#ifndef HTD_HTD_HEURISTICSETCOVERALGORITHM_HPP
#define	HTD_HTD_HEURISTICSETCOVERALGORITHM_HPP

#include <htd/Globals.hpp>
#include <htd/ISetCoverAlgorithm.hpp>

#include <vector>
#include <unordered_set>

namespace htd
{
    class HeuristicSetCoverAlgorithm : public virtual htd::ISetCoverAlgorithm
    {
        public:
            HeuristicSetCoverAlgorithm(void);
            
            ~HeuristicSetCoverAlgorithm();
            
            void computeSetCover(const htd::vertex_container& vertices, const std::vector<htd::vertex_container>& containers, std::vector<htd::vertex_container> & result) const HTD_OVERRIDE;

            HeuristicSetCoverAlgorithm * clone(void) const HTD_OVERRIDE;

        protected:
            HeuristicSetCoverAlgorithm & operator=(const HeuristicSetCoverAlgorithm &) { return *this; }


        private:

            const std::size_t maximumAttempts = 25;
            const std::size_t maximumNeighborhoodSize = 25;
            const std::size_t maximumTotalNeighborhoodSize = 100;

            struct HistoryEntry
            {
                std::vector<htd::id_t> selection;

                std::unordered_set<htd::id_t> remainder;

                std::vector<htd::id_t> availableChoices;

                HistoryEntry(void) : selection(), remainder(), availableChoices()
                {

                }

                HistoryEntry(const std::vector<htd::id_t>& selection, const std::unordered_set<htd::id_t>& remainder, std::vector<htd::id_t> availableChoices) : selection(selection), remainder(remainder), availableChoices(availableChoices)
                {

                }
            };

            class Compare
            {
                public:
                    bool operator() (const HistoryEntry & solution1, const HistoryEntry & solution2)
                    {
                        //TODO Use fitness function
                        return solution1.remainder.size() < solution2.remainder.size();
                    }

                    bool operator() (const std::vector<htd::id_t>& solution1, const std::vector<htd::id_t>& solution2)
                    {
                        return solution1.size() < solution2.size();
                    }
            };

            void populateNeighborhood(const std::vector<htd::vertex_container>& containers, std::vector<HistoryEntry> & newNeighborhood, std::size_t bestSolutionFitness, const std::vector<HistoryEntry> & origin) const;

            void populateNeighborhood(const std::vector<htd::vertex_container>& containers, std::vector<HistoryEntry> & newNeighborhood, std::size_t bestSolutionFitness, const HistoryEntry & individual) const;
    };
}

#endif /* HTD_HTD_HEURISTICSETCOVERALGORITHM_HPP */
