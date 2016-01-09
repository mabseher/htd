/* 
 * File:   NamedVertexHyperedge.hpp
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

#ifndef HTD_HTD_NAMEDVERTEXHYPEREDGE_HPP
#define	HTD_HTD_NAMEDVERTEXHYPEREDGE_HPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/Iterator.hpp>
#include <htd/ConstIterator.hpp>
#include <htd/Collection.hpp>
#include <htd/ConstCollection.hpp>

#include <vector>

namespace htd
{
    template<typename VertexNameType>
    class NamedVertexHyperedge
    {
        public:
            typedef VertexNameType value_type;

            NamedVertexHyperedge(htd::id_t id) : id_(id), elements_()
            {

            }

            NamedVertexHyperedge(htd::id_t id, const VertexNameType & vertex1, const VertexNameType & vertex2) : id_(id), elements_()
            {
                elements_.push_back(vertex1);
                elements_.push_back(vertex2);
            }

            NamedVertexHyperedge(htd::id_t id, const std::vector<VertexNameType> & elements) : id_(id), elements_(elements.begin(), elements.end())
            {

            }

            NamedVertexHyperedge(htd::id_t id, const htd::ConstCollection<VertexNameType> & elements) : id_(id), elements_(elements.begin(), elements.end())
            {

            }

            ~NamedVertexHyperedge()
            {

            }

            htd::id_t id() const
            {
                return id_;
            }

            htd::Collection<VertexNameType> elements()
            {
                return htd::Collection<VertexNameType>::getInstance(elements_);
            }

            htd::ConstCollection<VertexNameType> elements() const
            {
                return htd::ConstCollection<VertexNameType>::getInstance(elements_);
            }

            bool empty() const
            {
                return elements_.empty();
            }

            std::size_t size() const
            {
                return elements_.size();
            }

            bool containsVertex(const VertexNameType & vertex) const
            {
                return std::find(elements_.begin(), elements_.end(), vertex) != elements_.end();
            }

            void push_back(const VertexNameType & vertex)
            {
                elements_.push_back(vertex);
            }

            void erase(const VertexNameType & vertex)
            {
                elements_.erase(std::remove(elements_.begin(), elements_.end(), vertex), elements_.end());
            }

            htd::Iterator<VertexNameType> begin(void)
            {
                return htd::Iterator<VertexNameType>(elements_.begin());
            }

            const htd::ConstIterator<VertexNameType> begin(void) const
            {
                return htd::ConstIterator<VertexNameType>(elements_.begin());
            }

            htd::Iterator<VertexNameType> end(void)
            {
                return htd::Iterator<VertexNameType>(elements_.end());
            }

            const htd::ConstIterator<VertexNameType> end(void) const
            {
                return htd::ConstIterator<VertexNameType>(elements_.end());
            }

            const VertexNameType & operator[](htd::index_t index) const
            {
                htd::ConstIterator<VertexNameType> position = begin();

                std::advance(position, index);

                return *position;
            }

            NamedVertexHyperedge & operator=(const NamedVertexHyperedge & original)
            {
                id_ = original.id_;

                elements_ = original.elements_;

                return *this;
            }

            bool operator<(const NamedVertexHyperedge & rhs) const
            {
                return std::tie(elements_, id_) < std::tie(rhs.elements_, rhs.id_);
            }

            bool operator>(const NamedVertexHyperedge & rhs) const
            {
                return std::tie(elements_, id_) > std::tie(rhs.elements_, rhs.id_);
            }

            bool operator==(const NamedVertexHyperedge & rhs) const
            {
                return rhs.id_ == id_ && rhs.elements_ == elements_;
            }

            bool operator!=(const NamedVertexHyperedge & rhs) const
            {
                return rhs.id_ != id_ || rhs.elements_ != elements_;
            }

        private:
            htd::id_t id_;

            std::vector<VertexNameType> elements_;
    };
}

#endif /* HTD_HTD_NAMEDHYPERGRAPH_HPP */
