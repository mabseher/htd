/* 
 * File:   TemplateInstantiations.hpp
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

#ifndef HTD_HTD_TEMPLATEINSTANTIATIONS_HPP
#define HTD_HTD_TEMPLATEINSTANTIATIONS_HPP

#include <htd/PreprocessorDefinitions.hpp>

#include <htd/Vertex.hpp>
#include <htd/Hyperedge.hpp>

extern template class HTD_API htd::ConstIterator<htd::vertex_t>;
extern template class HTD_API htd::ConstCollection<htd::vertex_t>;

extern template class HTD_API htd::ConstIterator<htd::Hyperedge>;
extern template class HTD_API htd::ConstCollection<htd::Hyperedge>;

#endif /* HTD_HTD_TEMPLATEINSTANTIATIONS_HPP */
