/* 
 * File:   GraphPreprocessor.hpp
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

#ifndef HTD_HTD_GRAPHPREPROCESSOR_HPP
#define HTD_HTD_GRAPHPREPROCESSOR_HPP

#include <htd/Globals.hpp>
#include <htd/IGraphPreprocessor.hpp>
#include <htd/IWidthLimitableOrderingAlgorithm.hpp>

namespace htd
{
    /**
     *  Preprocessor for graphs.
     */
    class GraphPreprocessor : public htd::IGraphPreprocessor
    {
        public:
            /**
             *  Constructor for a graph preprocessor.
             *
             *  @param[in] manager   The management instance to which the new preprocessor belongs.
             */
            HTD_API GraphPreprocessor(const htd::LibraryInstance * const manager);
            
            HTD_API virtual ~GraphPreprocessor();

            HTD_API htd::IPreprocessedGraph * prepare(const htd::IMultiHypergraph & graph) const HTD_NOEXCEPT HTD_OVERRIDE;

            /**
             *  Set the preprocessing strategy which shall be used.
             *
             *  @param[in] level    The level of preprocessing which shall be applied. (0: none, 1: simple, 2: advanced, 3: full, 4 or more: full + retain only largest biconnected component)
             */
            HTD_API void setPreprocessingStrategy(std::size_t level);

            HTD_API const htd::LibraryInstance * managementInstance(void) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API void setManagementInstance(const htd::LibraryInstance * const manager) HTD_OVERRIDE;

            /**
             *  Getter for the number of iterations which shall be performed (0=infinite).
             *
             *  @return The number of iterations which shall be performed.
             */
            HTD_API std::size_t iterationCount(void) const;

            /**
             *  Set the number of iterations which shall be performed (0=infinite).
             *
             *  @param[in] iterationCount   The number of iterations which shall be performed.
             */
            HTD_API void setIterationCount(std::size_t iterationCount);

            /**
             *  Getter for the maximum number of iterations without improvement after which the algorithm shall terminate (0=return after first non-improving decomposition was found).
             *
             *  @note The current non-improvement count is reset to 0 after each iteration resulting in an improved decomposition.
             *
             *  @return The maximum number of iterations without improvement after which the algorithm shall terminate.
             */
            HTD_API std::size_t nonImprovementLimit(void) const;

            /**
             *  Set the maximum number of iterations without improvement after which the algorithm shall terminate (0=return after first non-improving decomposition was found).
             *
             *  @note The current non-improvement count is reset to 0 after each iteration resulting in an improved decomposition.
             *
             *  @param[in] nonImprovementLimit  The maximum number of iterations without improvement after which the algorithm shall terminate.
             */
            HTD_API void setNonImprovementLimit(std::size_t nonImprovementLimit);

            /**
             *  Set the ordering algorithm which shall be used to compute the vertex elimination
             *  ordering of the remainder of the input graph when only the largest biconnected
             *  component is retained.
             *
             *  @param[in] algorithm    The ordering algorithm which shall be used to compute the vertex elimination ordering.
             *
             *  @note When calling this method the control over the memory region of the ordering algorithm is transferred to the
             *  preprocessor. Deleting the ordering algorithm provided to this method outside the preprocessor or assigning the
             *  same ordering algorithm multiple times will lead to undefined behavior.
             */
            HTD_API void setOrderingAlgorithm(htd::IWidthLimitableOrderingAlgorithm * algorithm);

            /**
             *  Create a deep copy of the current graph preprocessor.
             *
             *  @return A new GraphPreprocessor object identical to the current graph preprocessor.
             */
            HTD_API GraphPreprocessor * clone(void) const HTD_OVERRIDE;

        protected:
            /**
             *  Copy assignment operator for a graph preprocessor.
             *
             *  @note This operator is protected to prevent assignments to an already initialized preprocessor.
             */
            GraphPreprocessor & operator=(const GraphPreprocessor &) { return *this; }

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_HTD_GRAPHPREPROCESSOR_HPP */
