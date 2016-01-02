/* 
 * File:   GraphComponentCollection.cpp
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

#ifndef HTD_HTD_GRAPHCOMPONENTCOLLECTION_CPP
#define	HTD_HTD_GRAPHCOMPONENTCOLLECTION_CPP

#include <htd/Globals.hpp>
#include <htd/GraphComponentCollection.hpp>

#include <stdexcept>

htd::GraphComponentCollection::GraphComponentCollection(void) : components_()
{

}

htd::GraphComponentCollection::~GraphComponentCollection()
{

}
            
std::size_t htd::GraphComponentCollection::componentCount(void) const
{
    return components_.size();
}

htd::ConstCollection<htd::vertex_t> htd::GraphComponentCollection::componentAtPosition(htd::index_t index) const
{
    if (index >= components_.size())
    {
        throw std::out_of_range("const htd::ConstCollection<htd::vertex_t> & htd::GraphComponentCollection::componentAtPosition(htd::index_t) const");
    }

    return htd::ConstCollection<htd::vertex_t>(components_[index]);
}

void htd::GraphComponentCollection::addComponent(const htd::ConstCollection<htd::vertex_t> & component)
{
    components_.push_back(htd::VectorAdapter<htd::vertex_t>(component));
}

#endif /* HTD_HTD_GRAPHCOMPONENTCOLLECTION_CPP */
