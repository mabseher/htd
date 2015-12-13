/*
 * File:   HyperedgeContainerLabel.cpp
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

#ifndef HTD_HTD_HYPEREDGECONTAINERLABEL_CPP
#define	HTD_HTD_HYPEREDGECONTAINERLABEL_CPP

#include <htd/HyperedgeContainerLabel.hpp>

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>

htd::HyperedgeContainerLabel::HyperedgeContainerLabel(void) : container_()
{

}

htd::HyperedgeContainerLabel::HyperedgeContainerLabel(const htd::hyperedge_container & data) : container_(data)
{

}

htd::HyperedgeContainerLabel::HyperedgeContainerLabel(const htd::Iterator<htd::hyperedge_t> begin, const htd::Iterator<htd::hyperedge_t> end) : container_(begin, end)
{

}

htd::HyperedgeContainerLabel::~HyperedgeContainerLabel()
{

}

std::size_t htd::HyperedgeContainerLabel::hash(void) const
{
    std::size_t ret = 7;

    std::hash<htd::hyperedge_t> hash_function;

    for (htd::hyperedge_t edge : container_)
    {
        std::hash_combine(ret, hash_function(edge));
    }

    return ret;
}

htd::HyperedgeContainerLabel * htd::HyperedgeContainerLabel::clone(void) const
{
    return new htd::HyperedgeContainerLabel(container_);
}

bool htd::HyperedgeContainerLabel::operator==(const htd::ILabel & other) const
{
    const htd::HyperedgeContainerLabel * o = dynamic_cast<const htd::HyperedgeContainerLabel *>(&other);

    return o != nullptr && container_ == o->container();
}

bool htd::HyperedgeContainerLabel::operator==(const htd::HyperedgeContainerLabel & other) const
{
    return container_ == other.container();
}

std::size_t htd::HyperedgeContainerLabel::size(void) const
{
    return container_.size();
}

htd::hyperedge_container & htd::HyperedgeContainerLabel::container(void)
{
    return container_;
}

const htd::hyperedge_container & htd::HyperedgeContainerLabel::container(void) const
{
    return container_;
}

#endif /* HTD_HTD_VERTEXCONTAINERLABEL_CPP */
