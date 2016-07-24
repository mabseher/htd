/*
 * File:   ILabelingFunction.hpp
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

#ifndef HTD_HTD_ILABELINGFUNCTION_HPP
#define	HTD_HTD_ILABELINGFUNCTION_HPP

#include <htd/Globals.hpp>
#include <htd/ConstCollection.hpp>
#include <htd/ILabel.hpp>
#include <htd/ILabelCollection.hpp>
#include <htd/IDecompositionManipulationOperation.hpp>

#include <string>

namespace htd
{
    /**
     * Interface for algorithms which compute corresponding labels for a decomposition node based on its bag content.
     */
    class ILabelingFunction : public virtual htd::IDecompositionManipulationOperation
    {
        public:
            virtual ~ILabelingFunction() = 0;

            /**
             *  Get the name of the label which will be generated by the labeling function.
             *
             *  @return The name of the label which will be generated by the labeling function.
             */
            virtual std::string name() const = 0;

            /**
             *  Compute a new label based on a set of vertices (e.g., the bag of a graph decomposition) and labels previously computed on the same set of vertices.
             *
             *  @param[in] vertices The set of input vertices sorted in ascending order.
             *  @param[in] labels   The collection of previously computed labels.
             *
             *  @return A new label based on the given set of vertices.
             */
            virtual htd::ILabel * computeLabel(const std::vector<htd::vertex_t> & vertices, const htd::ILabelCollection & labels) const = 0;

            /**
             *  Compute a new label based on a set of vertices (e.g., the bag of a graph decomposition) and labels previously computed on the same set of vertices.
             *
             *  @param[in] vertices The set of input vertices sorted in ascending order.
             *  @param[in] labels   The collection of previously computed labels.
             *
             *  @return A new label based on the given set of vertices.
             */
            virtual htd::ILabel * computeLabel(const htd::ConstCollection<htd::vertex_t> & vertices, const htd::ILabelCollection & labels) const = 0;

            /**
             *  Create a deep copy of the current labeling function.
             *
             *  @return A new ILabelingFunction object identical to the current labeling function.
             */
            virtual ILabelingFunction * clone(void) const HTD_OVERRIDE = 0;
    };

    inline htd::ILabelingFunction::~ILabelingFunction() { }
}

#endif /* HTD_HTD_ILABELINGFUNCTION_HPP */
