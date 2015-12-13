/*
 * File:   VertexContainerLabel.hpp
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

#ifndef HTD_HTD_VERTEXCONTAINERLABEL_HPP
#define	HTD_HTD_VERTEXCONTAINERLABEL_HPP

#include <htd/Globals.hpp>
#include <htd/ILabel.hpp>
#include <htd/Iterator.hpp>

namespace htd
{
    class VertexContainerLabel : public virtual htd::ILabel
    {
        public:
            VertexContainerLabel(void);

            VertexContainerLabel(const htd::vertex_container & data);

            VertexContainerLabel(const htd::Iterator<htd::vertex_t> begin, const htd::Iterator<htd::vertex_t> end);

            ~VertexContainerLabel();

            std::size_t hash(void) const HTD_OVERRIDE;

            VertexContainerLabel * clone(void) const HTD_OVERRIDE;

            bool operator==(const htd::ILabel & other) const HTD_OVERRIDE;

            bool operator==(const VertexContainerLabel & other) const;

            std::size_t size(void) const;

            htd::vertex_container & container(void);

            const htd::vertex_container & container(void) const;

        private:
            htd::vertex_container container_;
    };
}

#endif /* HTD_HTD_VERTEXCONTAINERLABEL_HPP */
