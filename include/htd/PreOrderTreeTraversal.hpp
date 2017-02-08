/*
 * File:   PreOrderTreeTraversal.hpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015-2017, Michael Abseher
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

#ifndef HTD_HTD_PREORDERTREETRAVERSAL_HPP
#define HTD_HTD_PREORDERTREETRAVERSAL_HPP

#include <htd/Globals.hpp>
#include <htd/ITreeTraversal.hpp>

#include <functional>

namespace htd
{
    /**
     * Implementation of the ITreeTraversal interface traversing the tree in pre-order, that is, a node is visited before its children.
     */
    class PreOrderTreeTraversal : public virtual htd::ITreeTraversal
    {
        public:
            HTD_API PreOrderTreeTraversal(void);

            HTD_API virtual ~PreOrderTreeTraversal();

            HTD_API void traverse(const htd::IPath & path, const std::function<void(htd::vertex_t, htd::vertex_t, std::size_t)> & targetFunction) const HTD_OVERRIDE;

            HTD_API void traverse(const htd::IPath & path, const std::function<void(htd::vertex_t, htd::vertex_t, std::size_t)> & targetFunction, htd::vertex_t startingVertex) const HTD_OVERRIDE;

            HTD_API void traverse(const htd::ITree & tree, const std::function<void(htd::vertex_t, htd::vertex_t, std::size_t)> & targetFunction) const HTD_OVERRIDE;

            HTD_API void traverse(const htd::ITree & tree, const std::function<void(htd::vertex_t, htd::vertex_t, std::size_t)> & targetFunction, htd::vertex_t startingVertex) const HTD_OVERRIDE;
    };
}

#endif /* HTD_HTD_PREORDERTREETRAVERSAL_HPP */
