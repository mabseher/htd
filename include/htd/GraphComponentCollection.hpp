/* 
 * File:   GraphComponentCollection.hpp
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

#ifndef HTD_HTD_GRAPHCOMPONENTCOLLECTION_HPP
#define	HTD_HTD_GRAPHCOMPONENTCOLLECTION_HPP

#include <htd/Globals.hpp>
#include <htd/VectorAdapter.hpp>

namespace htd
{
    class GraphComponentCollection
    {
        public:
            GraphComponentCollection(void);

            ~GraphComponentCollection();
            
            std::size_t componentCount(void) const;

            htd::ConstCollection<htd::vertex_t> componentAtPosition(htd::index_t index) const;

            void addComponent(const htd::ConstCollection<htd::vertex_t> & component);

        private:
            std::vector<htd::VectorAdapter<htd::vertex_t>> components_;
    };
}

#endif /* HTD_HTD_IGRAPHCOMPONENTCOLLECTION_HPP */
