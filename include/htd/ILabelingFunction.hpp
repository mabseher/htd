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
#include <htd/Collection.hpp>
#include <htd/ILabel.hpp>
#include <htd/ILabelCollection.hpp>
#include <htd/IDecompositionManipulationOperation.hpp>

#include <string>

namespace htd
{
    class ILabelingFunction : public virtual htd::IDecompositionManipulationOperation
    {
        public:
            virtual ~ILabelingFunction() = 0;
	    
            virtual std::string name() const = 0;

            virtual htd::ILabel * computeLabel(const htd::ConstCollection<htd::vertex_t> & vertices, const htd::ILabelCollection & labels) const = 0;
    };

    inline htd::ILabelingFunction::~ILabelingFunction() { }
}

#endif /* HTD_HTD_ILABELINGFUNCTION_HPP */
