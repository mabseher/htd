/* 
 * File:   BreadthFirstGraphTraversal.hpp
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

#ifndef HTD_HTD_BREADTHFIRSTGRAPHTRAVERSAL_HPP
#define	HTD_HTD_BREADTHFIRSTGRAPHTRAVERSAL_HPP

#include <htd/Globals.hpp>
#include <htd/IGraphTraversal.hpp>

namespace htd
{
    class BreadthFirstGraphTraversal : public virtual htd::IGraphTraversal
    {
        public:
            BreadthFirstGraphTraversal(void);

            ~BreadthFirstGraphTraversal();
            
            void traverse(const htd::IHypergraph & graph, htd::vertex_t startingVertex, const std::function<void(htd::vertex_t, htd::vertex_t, std::size_t)> & targetFunction) const HTD_OVERRIDE;
    };
}

#endif /* HTD_HTD_BREADTHFIRSTGRAPHTRAVERSAL_HPP */
