/*
 * File:   Hyperedge.hpp
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

#ifndef HTD_HTD_HYPEREDGE_HPP
#define HTD_HTD_HYPEREDGE_HPP

#include <htd/Globals.hpp>
#include <htd/ConstCollection.hpp>

#include <vector>
#include <memory>

namespace htd
{
    /**
     *  Class for the efficient storage of hyperedges.
     */
    class Hyperedge
    {
        public:
            /**
             *  The data type of the elements of a hyperedge.
             */
            typedef htd::vertex_t value_type;

            /**
             *  Constructor for a hyperedge.
             *
             *  @param[in] id       The ID of the constructed hyperedge.
             *  @param[in] vertex   The single endpoint of the constructed hyperedge.
             */
            HTD_API Hyperedge(htd::id_t id, htd::vertex_t vertex) HTD_NOEXCEPT;

            /**
             *  Constructor for a hyperedge.
             *
             *  @param[in] id       The ID of the constructed hyperedge.
             *  @param[in] vertex1  The first endpoint of the constructed hyperedge.
             *  @param[in] vertex2  The second endpoint of the constructed hyperedge.
             */
            HTD_API Hyperedge(htd::id_t id, htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_NOEXCEPT;

            /**
             *  Constructor for a hyperedge.
             *
             *  @param[in] id       The ID of the constructed hyperedge.
             *  @param[in] elements The endpoints of the constructed hyperedge.
             */
            HTD_API Hyperedge(htd::id_t id, const std::vector<htd::vertex_t> & elements) HTD_NOEXCEPT;

            /**
             *  Constructor for a hyperedge.
             *
             *  @param[in] id               The ID of the constructed hyperedge.
             *  @param[in] elements         The endpoints of the constructed hyperedge.
             *  @param[in] sortedElements   The endpoints of the constructed hyperedge sorted in ascending order without duplicates.
             */
            HTD_API Hyperedge(htd::id_t id, const std::vector<htd::vertex_t> & elements, const std::vector<htd::vertex_t> & sortedElements) HTD_NOEXCEPT;

            /**
             *  Constructor for a hyperedge.
             *
             *  @param[in] id       The ID of the constructed hyperedge.
             *  @param[in] elements The endpoints of the constructed hyperedge.
             */
            HTD_API Hyperedge(htd::id_t id, std::vector<htd::vertex_t> && elements) HTD_NOEXCEPT;

            /**
             *  Constructor for a hyperedge.
             *
             *  @param[in] id               The ID of the constructed hyperedge.
             *  @param[in] elements         The endpoints of the constructed hyperedge.
             *  @param[in] sortedElements   The endpoints of the constructed hyperedge sorted in ascending order without duplicates.
             */
            HTD_API Hyperedge(htd::id_t id, std::vector<htd::vertex_t> && elements, std::vector<htd::vertex_t> && sortedElements) HTD_NOEXCEPT;

            /**
             *  Constructor for a hyperedge.
             *
             *  @param[in] id       The ID of the constructed hyperedge.
             *  @param[in] elements The endpoints of the constructed hyperedge.
             */
            HTD_API Hyperedge(htd::id_t id, const htd::ConstCollection<htd::vertex_t> & elements) HTD_NOEXCEPT;

            /**
             *  Copy constructor for a hyperedge.
             *
             *  @param[in] original  The original hyperedge.
             */
            HTD_API Hyperedge(const Hyperedge & original) HTD_NOEXCEPT;

            /**
             *  Move constructor for a hyperedge.
             *
             *  @param[in] original  The original hyperedge.
             */
            HTD_API Hyperedge(Hyperedge && original) HTD_NOEXCEPT;

            /**
             *  Destructor for a Hyperedge object.
             */
            HTD_API virtual ~Hyperedge() HTD_NOEXCEPT;

            /**
             *  Getter for the ID of the hyperedge.
             *
             *  @return The ID of the hyperedge.
             */
            HTD_API htd::id_t id(void) const HTD_NOEXCEPT;

            /**
             *  Setter for the ID of the hyperedge.
             *
             *  @param[in] newId    The new ID of the hyperedge.
             */
            HTD_API void setId(htd::id_t newId) HTD_NOEXCEPT;

            /**
             *  Set the endpoints of the hyperedge.
             *
             *  @param[in] vertex1  The first endpoint of the updated hyperedge.
             *  @param[in] vertex2  The second endpoint of the updated hyperedge.
             */
            HTD_API void setElements(htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_NOEXCEPT;

            /**
             *  Set the endpoints of the hyperedge.
             *
             *  @param[in] elements The new endpoints of the updated hyperedge.
             */
            HTD_API void setElements(const std::vector<htd::vertex_t> & elements) HTD_NOEXCEPT;

            /**
             *  Set the endpoints of the hyperedge.
             *
             *  @param[in] elements The new endpoints of the updated hyperedge.
             */
            HTD_API void setElements(std::vector<htd::vertex_t> && elements) HTD_NOEXCEPT;

            /**
             *  Set the endpoints of the hyperedge.
             *
             *  @param[in] elements The new endpoints of the updated hyperedge.
             */
            HTD_API void setElements(const htd::ConstCollection<htd::vertex_t> & elements) HTD_NOEXCEPT;

            /**
             *  Getter for the elements of the hyperedge.
             *
             *  @return The elements of the hyperedge.
             */
            HTD_API const std::vector<htd::vertex_t> & elements(void) const HTD_NOEXCEPT;

            /**
             *  Getter for the elements of the hyperedge in ascending order without duplicates.
             *
             *  @return The elements of the hyperedge in ascending order without duplicates.
             */
            HTD_API const std::vector<htd::vertex_t> & sortedElements(void) const HTD_NOEXCEPT;

            /**
             *  Check whether the hyperedge contains no elements.
             *
             *  @return True if the hyperedge contains no elements, false otherwise.
             */
            HTD_API bool empty(void) const HTD_NOEXCEPT;

            /**
             *  Getter for the number of elements of the hyperedge.
             *
             *  @return The number of elements of the hyperedge.
             */
            HTD_API std::size_t size(void) const HTD_NOEXCEPT;

            /**
             *  Check whether the hyperedge contains a specific vertex.
             *
             *  @param[in] vertex   The specific vertex to test for existence.
             *
             *  @return True if the hyperedge contains the specific vertex, false otherwise.
             */
            HTD_API bool contains(htd::vertex_t vertex) const HTD_NOEXCEPT;

            /**
             *  Erase a specific vertex from the hyperedge in case the vertex is contained in the hyperedge.
             *
             *  @param[in] vertex   The specific vertex which shall be removed.
             */
            HTD_API void erase(htd::vertex_t vertex) HTD_NOEXCEPT;

            /**
             *  Getter for a const_iterator pointing to the first element in the hyperedge.
             *
             *  @return A const_iterator pointing to the first element in the hyperedge.
             */
            HTD_API std::vector<htd::vertex_t>::const_iterator begin(void) const HTD_NOEXCEPT;

            /**
             *  Getter for a const_iterator pointing to the end of the elements in the hyperedge.
             *
             *  @return A const_iterator pointing to the end of the elements in the hyperedge.
             */
            HTD_API std::vector<htd::vertex_t>::const_iterator end(void) const HTD_NOEXCEPT;

            /**
             *  Access the element at the specific position within the hyperedge.
             *
             *  @param[in] index    The position of the element.
             *
             *  @return The element at the specific position.
             */
            HTD_API const htd::vertex_t & at(htd::index_t index) const;

            /**
             *  Access the element at the specific position within the hyperedge.
             *
             *  @param[in] index    The position of the element.
             *
             *  @return The element at the specific position.
             */
            HTD_API const htd::vertex_t & operator[](htd::index_t index) const;

            /**
             *  Copy assignment operator for a hyperedge.
             *
             *  @param[in] original  The original hyperedge.
             */
            HTD_API Hyperedge & operator=(const Hyperedge & original);

            /**
             *  Move assignment operator for a hyperedge.
             *
             *  @param[in] original  The original hyperedge.
             */
            HTD_API Hyperedge & operator=(Hyperedge && original) HTD_NOEXCEPT;

            /**
             *  Less-than operator for a hyperedge.
             *
             *  @param[in] rhs  The hyperedge at the right-hand side of the operator.
             *
             *  @return True if the vector returned by the elements() is lexicographically smaller than
             *          rhs.elements() or if the elements are equal and id() is smaller than rhs.id(),
             *          false otherwise.
             */
            HTD_API bool operator<(const Hyperedge & rhs) const;

            /**
             *  Greater-than operator for a hyperedge.
             *
             *  @param[in] rhs  The hyperedge at the right-hand side of the operator.
             *
             *  @return True if the vector returned by the elements() is lexicographically greater than
             *          rhs.elements() or if the elements are equal and id() is greater than rhs.id(),
             *          false otherwise.
             */
            HTD_API bool operator>(const Hyperedge & rhs) const;

            /**
             *  Equality operator for a hyperedge.
             *
             *  @param[in] rhs  The hyperedge at the right-hand side of the operator.
             *
             *  @return True if the vector returned by the elements() is equal to rhs.elements(), false otherwise.
             */
            HTD_API bool operator==(const Hyperedge & rhs) const;

            /**
             *  Equality operator for a hyperedge.
             *
             *  @param[in] rhs  The hyperedge elements at the right-hand side of the operator.
             *
             *  @return True if the vector returned by the elements() is equal to rhs, false otherwise.
             */
            HTD_API bool operator==(const std::vector<htd::vertex_t> & rhs) const;

            /**
             *  Inequality operator for a hyperedge.
             *
             *  @param[in] rhs  The hyperedge at the right-hand side of the operator.
             *
             *  @return True if the vector returned by the elements() is unequal to rhs.elements(), false otherwise.
             */
            HTD_API bool operator!=(const Hyperedge & rhs) const;

            /**
             *  Inequality operator for a hyperedge.
             *
             *  @param[in] rhs  The hyperedge elements at the right-hand side of the operator.
             *
             *  @return True if the vector returned by the elements() is unequal to rhs, false otherwise.
             */
            HTD_API bool operator!=(const std::vector<htd::vertex_t> & rhs) const;

            /**
             *  Forward declaration of internal class for storing the element information of a hyperedge.
             */
            class IElementInformation;

        private:
            htd::id_t id_;

            std::unique_ptr<IElementInformation> content_;
    };
}

#endif /* HTD_HTD_HYPEREDGE_HPP */
