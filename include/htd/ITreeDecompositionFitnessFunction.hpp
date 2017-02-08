/*
 * File:   ITreeDecompositionFitnessFunction.hpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015-2017, Michael Abseher
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

#ifndef HTD_HTD_ITREEDECOMPOSITIONFITNESSFUNCTION_HPP
#define HTD_HTD_ITREEDECOMPOSITIONFITNESSFUNCTION_HPP

#include <htd/Globals.hpp>
#include <htd/ITreeDecomposition.hpp>
#include <htd/FitnessEvaluation.hpp>

namespace htd
{
    /**
     * Interface for algorithms which compute the fitness value of a given tree decomposition.
     */
    class ITreeDecompositionFitnessFunction
    {
        public:
            virtual ~ITreeDecompositionFitnessFunction() = 0;

            /**
             *  Compute the fitness evaluation of a given tree decomposition.
             *
             *  @param[in] graph            The graph from which the decomposition was computed.
             *  @param[in] decomposition    The tree decomposition which's fitness shall be computed.
             *
             *  @return The fitness evaluation of the given tree decomposition.
             */
            virtual htd::FitnessEvaluation * fitness(const htd::IMultiHypergraph & graph, const htd::ITreeDecomposition & decomposition) const = 0;

            /**
             *  Create a deep copy of the current fitness function.
             *
             *  @return A new ITreeDecompositionFitnessFunction object identical to the current fitness function.
             */
            virtual ITreeDecompositionFitnessFunction * clone(void) const = 0;
    };

    inline htd::ITreeDecompositionFitnessFunction::~ITreeDecompositionFitnessFunction() { }
}

#endif /* HTD_HTD_ITREEDECOMPOSITIONFITNESSFUNCTION_HPP */
