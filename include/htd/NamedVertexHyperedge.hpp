/* 
 * File:   NamedVertexHyperedge.hpp
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

#ifndef HTD_HTD_NAMEDVERTEXHYPEREDGE_HPP
#define HTD_HTD_NAMEDVERTEXHYPEREDGE_HPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/Iterator.hpp>
#include <htd/ConstIterator.hpp>
#include <htd/Collection.hpp>
#include <htd/ConstCollection.hpp>

#include <vector>

namespace htd
{
    /**
     *  Class for the efficient storage of hyperedges of named graph types.
     */
    template<typename VertexNameType>
    class NamedVertexHyperedge
    {
            public:
            /**
             *  The data type of the elements of a hyperedge of a named graph.
             */
            typedef VertexNameType value_type;

            /**
             *  Constructor for a hyperedge without endpoints.
             *
             *  @param[in] id   The ID of the constructed hyperedge.
             */
            NamedVertexHyperedge(htd::id_t id) : id_(id), elements_()
            {

            }

            /**
             *  Constructor for a hyperedge.
             *
             *  @param[in] id       The ID of the constructed hyperedge.
             *  @param[in] vertex1  The first endpoint of the constructed hyperedge.
             *  @param[in] vertex2  The second endpoint of the constructed hyperedge.
             */
            NamedVertexHyperedge(htd::id_t id, const VertexNameType & vertex1, const VertexNameType & vertex2) : id_(id), elements_()
            {
                elements_.push_back(vertex1);
                elements_.push_back(vertex2);
            }

            /**
             *  Constructor for a hyperedge.
             *
             *  @param[in] id       The ID of the constructed hyperedge.
             *  @param[in] elements The endpoints of the constructed hyperedge.
             */
            NamedVertexHyperedge(htd::id_t id, const std::vector<VertexNameType> & elements) : id_(id), elements_(elements.begin(), elements.end())
            {

            }

            /**
             *  Constructor for a hyperedge.
             *
             *  @param[in] id       The ID of the constructed hyperedge.
             *  @param[in] elements The endpoints of the constructed hyperedge.
             */
            NamedVertexHyperedge(htd::id_t id, std::vector<VertexNameType> && elements) : id_(id), elements_(std::move(elements))
            {

            }

            /**
             *  Constructor for a hyperedge.
             *
             *  @param[in] id       The ID of the constructed hyperedge.
             *  @param[in] elements The endpoints of the constructed hyperedge.
             */
            NamedVertexHyperedge(htd::id_t id, const htd::ConstCollection<VertexNameType> & elements) : id_(id), elements_(elements.begin(), elements.end())
            {

            }

            /**
             *  Destructor for a NamedVertexHyperedge object.
             */
            virtual ~NamedVertexHyperedge()
            {

            }

            /**
             *  Getter for the ID of the hyperedge.
             *
             *  @return The ID of the hyperedge.
             */
            htd::id_t id(void) const
            {
                return id_;
            }

            /**
             *  Getter for the elements of the hyperedge.
             *
             *  @return The elements of the hyperedge.
             */
            std::vector<VertexNameType> & elements(void)
            {
                return elements_;
            }

            /**
             *  Getter for the elements of the hyperedge.
             *
             *  @return The elements of the hyperedge.
             */
            const std::vector<VertexNameType> & elements(void) const
            {
                return elements_;
            }

            /**
             *  Check whether the hyperedge contains no elements.
             *
             *  @return True if the hyperedge contains no elements, false otherwise.
             */
            bool empty(void) const
            {
                return elements_.empty();
            }

            /**
             *  Getter for the number of elements of the hyperedge.
             *
             *  @return The number of elements of the hyperedge.
             */
            std::size_t size(void) const
            {
                return elements_.size();
            }

            /**
             *  Check whether the hyperedge contains a specific vertex.
             *
             *  @param[in] vertex   The specific vertex to test for existence.
             *
             *  @return True if the hyperedge contains the specific vertex, false otherwise.
             */
            bool containsVertex(const VertexNameType & vertex) const
            {
                return std::find(elements_.begin(), elements_.end(), vertex) != elements_.end();
            }

            /**
             *  Erase a specific vertex from the hyperedge in case the vertex is contained in the hyperedge.
             *
             *  @param[in] vertex   The specific vertex which shall be removed.
             */
            void erase(const VertexNameType & vertex)
            {
                elements_.erase(std::remove(elements_.begin(), elements_.end(), vertex), elements_.end());
            }

            /**
             *  Getter for a const_iterator pointing to the first element in the hyperedge.
             *
             *  @return A const_iterator pointing to the first element in the hyperedge.
             */
            typename std::vector<VertexNameType>::const_iterator begin(void) const
            {
                return elements_.begin();
            }

            /**
             *  Getter for a const_iterator pointing to the end of the elements in the hyperedge.
             *
             *  @return A const_iterator pointing to the end of the elements in the hyperedge.
             */
            typename std::vector<VertexNameType>::const_iterator end(void) const
            {
                return elements_.end();
            }

            /**
             *  Access the element at the specific position within the hyperedge.
             *
             *  @param[in] index    The position of the element.
             *
             *  @return The element at the specific position.
             */
            const VertexNameType & operator[](htd::index_t index) const
            {
                return elements_.at(index);
            }

            /**
             *  Copy assignment operator for a hyperedge.
             *
             *  @param[in] original  The original hyperedge.
             */
            NamedVertexHyperedge & operator=(const NamedVertexHyperedge & original)
            {
                id_ = original.id_;

                elements_ = original.elements_;

                return *this;
            }

            /**
             *  Less-than operator for a hyperedge.
             *
             *  @param[in] rhs  The hyperedge at the right-hand side of the operator.
             *
             *  @return True if the vector returned by the elements() is lexicographically smaller than
             *          rhs.elements() or if the elements are equal and id() is smaller than rhs.id(),
             *          false otherwise.
             */
            bool operator<(const NamedVertexHyperedge & rhs) const
            {
                return std::tie(elements_, id_) < std::tie(rhs.elements_, rhs.id_);
            }

            /**
             *  Greater-than operator for a hyperedge.
             *
             *  @param[in] rhs  The hyperedge at the right-hand side of the operator.
             *
             *  @return True if the vector returned by the elements() is lexicographically greater than
             *          rhs.elements() or if the elements are equal and id() is greater than rhs.id(),
             *          false otherwise.
             */
            bool operator>(const NamedVertexHyperedge & rhs) const
            {
                return std::tie(elements_, id_) > std::tie(rhs.elements_, rhs.id_);
            }

            /**
             *  Equality operator for a hyperedge.
             *
             *  @param[in] rhs  The hyperedge at the right-hand side of the operator.
             *
             *  @return True if the vector returned by the elements() is equal to rhs.elements(), false otherwise.
             */
            bool operator==(const NamedVertexHyperedge & rhs) const
            {
                return rhs.id_ == id_ && rhs.elements_ == elements_;
            }

            /**
             *  Inequality operator for a hyperedge.
             *
             *  @param[in] rhs  The hyperedge at the right-hand side of the operator.
             *
             *  @return True if the vector returned by the elements() is unequal to rhs.elements(), false otherwise.
             */
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
