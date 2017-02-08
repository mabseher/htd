/* 
 * File:   VectorAdapterIteratorWrapper.hpp
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

#ifndef HTD_HTD_VECTORADAPTERITERATORWRAPPER_HPP
#define HTD_HTD_VECTORADAPTERITERATORWRAPPER_HPP

#include <htd/Globals.hpp>

#include <htd/IteratorBase.hpp>
#include <htd/IteratorWrapper.hpp>

#include <iterator>
#include <memory>

namespace htd
{
    /**
     *  Implementation of a wrapper for iterators of immutable objects of type VectorAdapter.
     */
    template <typename Iter, typename T = typename Iter::value_type, class Allocator = std::allocator<T>>
    class VectorAdapterIteratorWrapper : public htd::IteratorWrapper<Iter, T>
    {
        public:
            /**
             *  Constructor for an iterator wrapper.
             *
             *  @param[in] collection   The underlying vector at which the iterator points.
             *  @param[in] baseIterator The underlying iterator which shall be wrapped.
             */
            VectorAdapterIteratorWrapper(std::shared_ptr<std::vector<T, Allocator>> collection, Iter baseIterator) : htd::IteratorWrapper<Iter, T>(baseIterator), collection_(collection)
            {

            }

            /**
             *  Copy constructor for an iterator wrapper.
             *
             *  @param[in] original  The original iterator wrapper.
             */
            VectorAdapterIteratorWrapper(const VectorAdapterIteratorWrapper<Iter, T> & original) : htd::IteratorWrapper<Iter, T>(original), collection_(original.collection_)
            {

            }

            virtual ~VectorAdapterIteratorWrapper()
            {

            }

        private:
            std::shared_ptr<std::vector<T, Allocator>> collection_;
    };
}

#endif /* HTD_HTD_VECTORADAPTERITERATORWRAPPER_HPP */
