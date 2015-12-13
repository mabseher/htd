/*
 * File:   VertexContainerLabel.cpp
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

#ifndef HTD_HTD_VERTEXCONTAINERLABEL_CPP
#define	HTD_HTD_VERTEXCONTAINERLABEL_CPP

#include <htd/VertexContainerLabel.hpp>

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>

htd::VertexContainerLabel::VertexContainerLabel(void) : container_()
{

}

htd::VertexContainerLabel::VertexContainerLabel(const htd::vertex_container & data) : container_(data)
{

}

htd::VertexContainerLabel::VertexContainerLabel(const htd::Iterator<htd::vertex_t> begin, const htd::Iterator<htd::vertex_t> end) : container_(begin, end)
{

}

htd::VertexContainerLabel::~VertexContainerLabel()
{

}

std::size_t htd::VertexContainerLabel::hash(void) const
{
    std::hash<htd::vertex_container> hash_function;

    return hash_function(container_);
}

htd::VertexContainerLabel * htd::VertexContainerLabel::clone(void) const
{
    return new htd::VertexContainerLabel(container_);
}

bool htd::VertexContainerLabel::operator==(const htd::ILabel & other) const
{
    const htd::VertexContainerLabel * o = dynamic_cast<const htd::VertexContainerLabel *>(&other);

    return o != nullptr && container_ == o->container();
}

bool htd::VertexContainerLabel::operator==(const htd::VertexContainerLabel & other) const
{
    return container_ == other.container();
}

std::size_t htd::VertexContainerLabel::size(void) const
{
    return container_.size();
}

htd::vertex_container & htd::VertexContainerLabel::container(void)
{
    return container_;
}

const htd::vertex_container & htd::VertexContainerLabel::container(void) const
{
    return container_;
}

#endif /* HTD_HTD_VERTEXCONTAINERLABEL_CPP */
