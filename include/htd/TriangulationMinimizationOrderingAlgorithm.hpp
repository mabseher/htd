/* 
 * File:   TriangulationMinimizationOrderingAlgorithm.hpp
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

#ifndef HTD_HTD_TRIANGULATIONMINIMIZATIONORDERINGALGORITHM_HPP
#define HTD_HTD_TRIANGULATIONMINIMIZATIONORDERINGALGORITHM_HPP

#include <htd/Globals.hpp>
#include <htd/IOrderingAlgorithm.hpp>

namespace htd
{
    /**
     *  Implementation of the IOrderingAlgorithm interface which operates by
     *  computing a minimal triangulation based on a given vertex elimination
     *  ordering algorithm.
     */
    class TriangulationMinimizationOrderingAlgorithm : public virtual htd::IOrderingAlgorithm
    {
        public:
            /**
             *  Constructor for a new ordering algorithm of type TriangulationMinimizationOrderingAlgorithm.
             *
             *  @param[in] manager   The management instance to which the new algorithm belongs.
             */
            HTD_API TriangulationMinimizationOrderingAlgorithm(const htd::LibraryInstance * const manager);

            /**
             *  Copy constructor for a htd::TriangulationMinimizationOrderingAlgorithm object.
             *
             *  @param[in] original The original htd::TriangulationMinimizationOrderingAlgorithm object.
             */
            HTD_API TriangulationMinimizationOrderingAlgorithm(const htd::TriangulationMinimizationOrderingAlgorithm & original);

            HTD_API virtual ~TriangulationMinimizationOrderingAlgorithm();
            
            HTD_API htd::IVertexOrdering * computeOrdering(const htd::IMultiHypergraph & graph) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API htd::IVertexOrdering * computeOrdering(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API const htd::LibraryInstance * managementInstance(void) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API void setManagementInstance(const htd::LibraryInstance * const manager) HTD_OVERRIDE;

            /**
             *  Set the ordering algorithm which shall be used to compute the initial vertex elimination ordering.
             *
             *  @param[in] algorithm    The ordering algorithm which shall be used to compute the initial vertex elimination ordering.
             *
             *  @note When calling this method the control over the memory region of the initial ordering algorithm is transferred to the
             *  ordering algorithm. Deleting the ordering algorithm provided to this method outside the current ordering algorithm or
             *  assigning the same ordering algorithm multiple times will lead to undefined behavior.
             */
            HTD_API void setOrderingAlgorithm(htd::IOrderingAlgorithm * algorithm);

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            HTD_API TriangulationMinimizationOrderingAlgorithm * clone(void) const HTD_OVERRIDE;
#else
            HTD_API TriangulationMinimizationOrderingAlgorithm * clone(void) const;

            HTD_API htd::IOrderingAlgorithm * cloneOrderingAlgorithm(void) const HTD_OVERRIDE;
#endif

        protected:
            /**
             *  Copy assignment operator for an ordering algorithm.
             *
             *  @note This operator is protected to prevent assignments to an already initialized algorithm.
             */
            TriangulationMinimizationOrderingAlgorithm & operator=(const TriangulationMinimizationOrderingAlgorithm &) { return *this; }

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_HTD_TRIANGULATIONMINIMIZATIONORDERINGALGORITHM_HPP */
