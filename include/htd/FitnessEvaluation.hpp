/* 
 * File:   FitnessEvaluation.hpp
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

#ifndef HTD_HTD_FITNESSEVALUATION_HPP
#define HTD_HTD_FITNESSEVALUATION_HPP

#include <htd/Globals.hpp>

#include <ostream>
#include <vector>

namespace htd
{
    /**
     *  Class for the storage of results of fitness functions for decompositions.
     *
     *  The fitness values are stored according to their priority in different levels. Each fitness
     *  evaluation must have at least one level (Level 0) and two evaluations are comparable if and
     *  only if they have the same number of levels.
     *
     *  A lower level means higher priority and a higher number at lower levels always dominates the
     *  values at higher levels, that is, when we look at the following two fitness evaluations, the
     *  first one is considered better than the second one as its second level has assigned a higher
     *  number:
     *  1. Evaluation: 1,2,0 (Fitness: 1@@L0, 2@@L1, 0@@L2)
     *  2. Evaluation: 1,1,5 (Fitness: 1@@L0, 1@@L1, 5@@L2)
     */
    class FitnessEvaluation
    {
        public:
            /**
             *  Constructor for a fitness evaluation.
             *
             *  @param[in] levels   The number of levels of the new fitness evaluation.
             *  @param[in] ...      The values (of type double) of the new fitness evaluation sorted by level in ascending order.
             */
            HTD_API FitnessEvaluation(int levels, ...);

            /**
             *  Constructor for a fitness evaluation.
             *
             *  @param[in] values   The values of the new fitness evaluation sorted by level in ascending order.
             */
            HTD_API FitnessEvaluation(const std::vector<double> & values);

            /**
             *  Constructor for a fitness evaluation.
             *
             *  @param[in] values   The values of the new fitness evaluation sorted by level in ascending order.
             */
            HTD_API FitnessEvaluation(std::vector<double> && values);

            /**
             *  Destructor for a fitness evaluation.
             */
            HTD_API virtual ~FitnessEvaluation();

            /**
             *  Getter for the number of levels of the fitness evaluation.
             *
             *  @return The number of levels of the fitness evaluation.
             */
            HTD_API std::size_t levelCount(void) const HTD_NOEXCEPT;

            /**
             *  Getter for the fitness values of the fitness evaluation.
             *
             *  @return The fitness values of the fitness evaluation.
             */
            HTD_API const std::vector<double> & values(void) const HTD_NOEXCEPT;

            /**
             *  Access the fitness value at the specific level of the fitness evaluation.
             *
             *  @param[in] level    The level of the fitness value.
             *
             *  @return The fitness value at the specific level of the fitness evaluation.
             */
            HTD_API double at(htd::index_t level) const;

            /**
             *  Access the fitness value at the specific level of the fitness evaluation.
             *
             *  @param[in] level    The level of the fitness value.
             *
             *  @return The fitness value at the specific level of the fitness evaluation.
             */
            HTD_API double operator[](htd::index_t level) const;

            /**
             *  Less-than operator for a fitness evaluation.
             *
             *  @param[in] rhs  The fitness evaluation at the right-hand side of the operator.
             *
             *  @return True if the vector returned by the values() is lexicographically smaller than rhs.values(), false otherwise.
             */
            HTD_API bool operator<(const FitnessEvaluation & rhs) const HTD_NOEXCEPT;

            /**
             *  Greater-than operator for a fitness evaluation.
             *
             *  @param[in] rhs  The fitness evaluation at the right-hand side of the operator.
             *
             *  @return True if the vector returned by the values() is lexicographically greater than rhs.values(), false otherwise.
             */
            HTD_API bool operator>(const FitnessEvaluation & rhs) const HTD_NOEXCEPT;

            /**
             *  Equality operator for a fitness evaluation.
             *
             *  @param[in] rhs  The fitness evaluation at the right-hand side of the operator.
             *
             *  @return True if the vector returned by the values() is equal to rhs.values(), false otherwise.
             */
            HTD_API bool operator==(const FitnessEvaluation & rhs) const HTD_NOEXCEPT;

            /**
             *  Inequality operator for a fitness evaluation.
             *
             *  @param[in] rhs  The fitness evaluation at the right-hand side of the operator.
             *
             *  @return True if the vector returned by the values() is unequal to rhs.values(), false otherwise.
             */
            HTD_API bool operator!=(const FitnessEvaluation & rhs) const HTD_NOEXCEPT;

            /**
             *  Create a deep copy of the current fitness evaluation.
             *
             *  @return A new FitnessEvaluation object identical to the current fitness evaluation.
             */
            HTD_API FitnessEvaluation * clone(void) const;

        private:
            /**
             *  The values of the fitness evaluation sorted by level in ascending order.
             */
            std::vector<double> values_;
    };
}

namespace std
{
    std::ostream & operator<<(std::ostream & stream, const htd::FitnessEvaluation & input);
}

#endif /* HTD_HTD_FITNESSEVALUATION_HPP */
