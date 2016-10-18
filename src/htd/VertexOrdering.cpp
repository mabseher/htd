/*
 * File:   VertexOrdering.cpp
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

#ifndef HTD_HTD_VERTEXORDERING_CPP
#define HTD_HTD_VERTEXORDERING_CPP

#include <htd/VertexOrdering.hpp>

/**
 *  Private implementation details of class htd::VertexOrdering.
 */
struct htd::VertexOrdering::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] sequence     The sequence of vertices.
     *  @param[in] iterations   The number of iterations which was needed to find the sequence of vertices at hand.
     */
    Implementation(const std::vector<htd::vertex_t> & sequence, std::size_t iterations) : sequence_(sequence), iterations_(iterations)
    {

    }

    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] sequence     The sequence of vertices.
     *  @param[in] iterations   The number of iterations which was needed to find the sequence of vertices at hand.
     */
    Implementation(std::vector<htd::vertex_t> && sequence, std::size_t iterations) : sequence_(std::move(sequence)), iterations_(iterations)
    {

    }

    virtual ~Implementation()
    {

    }

    /**
     *  The sequence of vertices.
     */
    std::vector<htd::vertex_t> sequence_;

    /**
     *  The number of iterations which was needed to find the sequence of vertices at hand.
     */
    std::size_t iterations_;
};

htd::VertexOrdering::VertexOrdering(const std::vector<htd::vertex_t> & sequence, std::size_t iterations) : implementation_(new Implementation(sequence, iterations))
{

}

htd::VertexOrdering::VertexOrdering(std::vector<htd::vertex_t> && sequence, std::size_t iterations) : implementation_(new Implementation(std::move(sequence), iterations))
{

}

htd::VertexOrdering::VertexOrdering(const htd::VertexOrdering & original) : implementation_(new Implementation(*(original.implementation_)))
{

}

htd::VertexOrdering::VertexOrdering(htd::VertexOrdering && original) : implementation_(std::move(original.implementation_))
{

}

htd::VertexOrdering::~VertexOrdering()
{

}

const std::vector<htd::vertex_t> & htd::VertexOrdering::sequence(void) const
{
    return implementation_->sequence_;
}

std::size_t htd::VertexOrdering::requiredIterations(void) const
{
    return implementation_->iterations_;
}

#endif /* HTD_HTD_VERTEXORDERING_CPP */
