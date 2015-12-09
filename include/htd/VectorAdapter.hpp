/* 
 * File:   VectorAdapter.hpp
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

#ifndef HTD_HTD_VECTORADAPTER_HPP
#define HTD_HTD_VECTORADAPTER_HPP

#include <htd/Globals.hpp>

#include <htd/Collection.hpp>
#include <htd/Iterator.hpp>
#include <htd/VectorAdapterIteratorWrapper.hpp>

#include <memory>
#include <vector>

namespace htd
{
    template <typename T>
    class VectorAdapter : public htd::Collection<T>
    {
        public:
            typedef T value_type;

            VectorAdapter<T>(void) : container_(std::make_shared<std::vector<T>>())
            {

            }

            VectorAdapter<T>(const std::vector<T> & collection) : container_(std::make_shared<std::vector<T>>(collection))
            {

            }

            virtual ~VectorAdapter()
            {

            }

            std::vector<T> & container()
            {
                return *container_;
            }

            const std::vector<T> & container() const
            {
                return *container_;
            }

            htd::Iterator<T> begin(void)
            {
                return htd::VectorAdapterIteratorWrapper<typename std::vector<T>::iterator, T>(container_, container_->begin());
            }

            const htd::Iterator<T> begin(void) const
            {
                return htd::VectorAdapterIteratorWrapper<typename std::vector<T>::const_iterator, T>(container_, container_->begin());
            }

            htd::Iterator<T> end(void)
            {
                return htd::VectorAdapterIteratorWrapper<typename std::vector<T>::iterator, T>(container_, container_->end());
            }

            const htd::Iterator<T> end(void) const
            {
                return htd::VectorAdapterIteratorWrapper<typename std::vector<T>::const_iterator, T>(container_, container_->end());
            }

        private:
            std::shared_ptr<std::vector<T>> container_;
    };
}

#endif /* HTD_HTD_VECTORADAPTER_HPP */
