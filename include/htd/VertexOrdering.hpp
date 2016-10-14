/*
 * File:   VertexOrdering.hpp
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

#ifndef HTD_HTD_VERTEXORDERING_HPP
#define	HTD_HTD_VERTEXORDERING_HPP

#include <htd/Globals.hpp>

#include <memory>
#include <vector>

namespace htd
{
    /**
     * Storage class for orderings of graph vertices.
     */
    class VertexOrdering
    {
        public:
            /**
             *  Create a new vertex ordering.
             *
             *  @param[in] sequence     The sequence of vertices.
             *  @param[in] iterations   The number of iterations which was needed to find the sequence of vertices at hand.
             */
            HTD_API VertexOrdering(const std::vector<htd::vertex_t> & sequence, std::size_t iterations = 1);

            /**
             *  Create a new vertex ordering.
             *
             *  @param[in] sequence     The sequence of vertices.
             *  @param[in] iterations   The number of iterations which was needed to find the sequence of vertices at hand.
             */
            HTD_API VertexOrdering(std::vector<htd::vertex_t> && sequence, std::size_t iterations = 1);

            /**
             *  Copy constructor for a VertexOrdering object.
             *
             *  @param[in] original  The original VertexOrdering object.
             */
            HTD_API VertexOrdering(const VertexOrdering & original);

            /**
             *  Move constructor for a VertexOrdering object.
             *
             *  @param[in] original  The original VertexOrdering object.
             */
            HTD_API VertexOrdering(VertexOrdering && original);

            /**
             *  Destructor for a VertexOrdering object.
             */
            HTD_API virtual ~VertexOrdering();

            /**
             *  Getter for the sequence of vertices.
             *
             *  @return The sequence of vertices.
             */
            HTD_API const std::vector<htd::vertex_t> & sequence(void) const;

            /**
             *  Getter for the number of iterations which was needed to find the sequence of vertices at hand.
             *
             *  @return The number of iterations which was needed to find the sequence of vertices at hand.
             */
            HTD_API std::size_t requiredIterations(void) const;

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_HTD_VERTEXORDERING_HPP */
