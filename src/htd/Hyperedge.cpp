/*
 * File:   Hyperedge.cpp
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

#ifndef HTD_HTD_HYPEREDGE_CPP
#define HTD_HTD_HYPEREDGE_CPP

#include <htd/Hyperedge.hpp>

#include <htd/Helpers.hpp>

#include <algorithm>
#include <functional>

/**
 *  Interface for the element information of a hyperedge.
 */
class htd::Hyperedge::IElementInformation
{
    public:
        virtual ~IElementInformation() = 0;

        /**
         *  Set the endpoints of the hyperedge.
         *
         *  @param[in] vertex1  The first endpoint of the updated hyperedge.
         *  @param[in] vertex2  The second endpoint of the updated hyperedge.
         */
        virtual void setElements(htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_NOEXCEPT = 0;

        /**
         *  Set the endpoints of the hyperedge.
         *
         *  @param[in] elements The new endpoints of the updated hyperedge.
         */
        virtual void setElements(const std::vector<htd::vertex_t> & elements) HTD_NOEXCEPT = 0;

        /**
         *  Set the endpoints of the hyperedge.
         *
         *  @param[in] elements The new endpoints of the updated hyperedge.
         */
        virtual void setElements(std::vector<htd::vertex_t> && elements) HTD_NOEXCEPT = 0;

        /**
         *  Set the endpoints of the hyperedge.
         *
         *  @param[in] elements The new endpoints of the updated hyperedge.
         */
        virtual void setElements(const htd::ConstCollection<htd::vertex_t> & elements) HTD_NOEXCEPT = 0;

        /**
         *  Getter for the elements of the hyperedge.
         *
         *  @return The elements of the hyperedge.
         */
        virtual const std::vector<htd::vertex_t> & elements(void) const = 0;

        /**
         *  Getter for the elements of the hyperedge in ascending order without duplicates.
         *
         *  @return The elements of the hyperedge in ascending order without duplicates.
         */
        virtual const std::vector<htd::vertex_t> & sortedElements(void) const = 0;

        /**
         *  Check whether the hyperedge contains no elements.
         *
         *  @return True if the hyperedge contains no elements, false otherwise.
         */
        virtual bool empty(void) const = 0;

        /**
         *  Getter for the number of elements of the hyperedge.
         *
         *  @return The number of elements of the hyperedge.
         */
        virtual std::size_t size(void) const = 0;

        /**
         *  Check whether the hyperedge contains a specific vertex.
         *
         *  @param[in] vertex   The specific vertex to test for existence.
         *
         *  @return True if the hyperedge contains the specific vertex, false otherwise.
         */
        virtual bool contains(htd::vertex_t vertex) const = 0;

        /**
         *  Erase a specific vertex from the hyperedge in case the vertex is contained in the hyperedge.
         *
         *  @param[in] vertex   The specific vertex which shall be removed.
         */
        virtual void erase(htd::vertex_t vertex) = 0;

        /**
         *  Getter for a const_iterator pointing to the first element in the hyperedge.
         *
         *  @return A const_iterator pointing to the first element in the hyperedge.
         */
        virtual std::vector<htd::vertex_t>::const_iterator begin(void) const = 0;

        /**
         *  Getter for a const_iterator pointing to the end of the elements in the hyperedge.
         *
         *  @return A const_iterator pointing to the end of the elements in the hyperedge.
         */
        virtual std::vector<htd::vertex_t>::const_iterator end(void) const = 0;

        /**
         *  Access the element at the specific position within the hyperedge.
         *
         *  @param[in] index    The position of the element.
         *
         *  @return The element at the specific position.
         */
        virtual const htd::vertex_t & at(htd::index_t index) const = 0;

        /**
         *  Access the element at the specific position within the hyperedge.
         *
         *  @param[in] index    The position of the element.
         *
         *  @return The element at the specific position.
         */
        virtual const htd::vertex_t & operator[](htd::index_t index) const = 0;

        /**
         *  Create a deep copy of the current hyperedge element information.
         *
         *  @return A new IElementInformation object identical to the current hyperedge element information.
         */
        virtual IElementInformation * clone(void) const = 0;

        /**
         *  Check whether the element information is of type SortedElementInformation.
         *
         *  @return True if the element information is of type SortedElementInformation, false otherwise.
         */
        virtual bool isSortedElementInformation(void) const = 0;
};

inline htd::Hyperedge::IElementInformation::~IElementInformation() { }

/**
 *  Internal class for storing the element information of a hyperedge.
 *
 *  This internal class is only used when the elements are not sorted in ascending order.
 */
class ElementInformation : public htd::Hyperedge::IElementInformation
{
    public:
        /**
         *  Constructor for a hyperedge element information.
         *
         *  @param[in] vertex1  The first endpoint of the constructed hyperedge.
         *  @param[in] vertex2  The second endpoint of the constructed hyperedge.
         */
        ElementInformation(htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_NOEXCEPT : elements_(std::initializer_list<htd::vertex_t> { vertex1, vertex2 }), sortedElements_()
        {
            sortedElements_.push_back(vertex2);

            if (vertex1 > vertex2)
            {
                sortedElements_.push_back(vertex1);
            }
        }

        /**
         *  Constructor for a hyperedge element information.
         *
         *  @param[in] elements The endpoints of the constructed hyperedge.
         */
        ElementInformation(const std::vector<htd::vertex_t> & elements) HTD_NOEXCEPT : elements_(elements.begin(), elements.end()), sortedElements_()
        {
            elements_.shrink_to_fit();

            sortedElements_.reserve(elements_.size());

            if (elements_.size() == 2)
            {
                htd::vertex_t vertex1 = elements_[0];
                htd::vertex_t vertex2 = elements_[1];

                if (vertex1 > vertex2)
                {
                    sortedElements_.push_back(vertex2);
                    sortedElements_.push_back(vertex1);
                }
                else
                {
                    sortedElements_.push_back(vertex1);
                }
            }
            else
            {
                sortedElements_.insert(sortedElements_.end(), elements_.begin(), elements_.end());

                std::sort(sortedElements_.begin(), sortedElements_.end());

                sortedElements_.erase(std::unique(sortedElements_.begin(), sortedElements_.end()), sortedElements_.end());
            }
        }

        /**
         *  Constructor for a hyperedge element information.
         *
         *  @param[in] elements         The endpoints of the constructed hyperedge.
         *  @param[in] sortedElements   The endpoints of the constructed hyperedge sorted in ascending order without duplicates.
         */
        ElementInformation(const std::vector<htd::vertex_t> & elements, const std::vector<htd::vertex_t> & sortedElements) HTD_NOEXCEPT : elements_(elements), sortedElements_(sortedElements)
        {
            #ifndef NDEBUG
            std::vector<htd::vertex_t> tmp(elements_.begin(), elements_.end());

            std::sort(tmp.begin(), tmp.end());

            tmp.erase(std::unique(tmp.begin(), tmp.end()), tmp.end());

            HTD_ASSERT(sortedElements_ == tmp)
            #endif

            elements_.shrink_to_fit();

            sortedElements_.shrink_to_fit();
        }

        /**
         *  Constructor for a hyperedge element information.
         *
         *  @param[in] elements The endpoints of the constructed hyperedge.
         */
        ElementInformation(std::vector<htd::vertex_t> && elements) HTD_NOEXCEPT : elements_(std::move(elements)), sortedElements_()
        {
            elements_.shrink_to_fit();

            sortedElements_.reserve(elements_.size());

            if (elements_.size() == 2)
            {
                htd::vertex_t vertex1 = elements_[0];
                htd::vertex_t vertex2 = elements_[1];

                if (vertex1 > vertex2)
                {
                    sortedElements_.push_back(vertex2);
                    sortedElements_.push_back(vertex1);
                }
                else
                {
                    sortedElements_.push_back(vertex1);
                }
            }
            else
            {
                sortedElements_.insert(sortedElements_.end(), elements_.begin(), elements_.end());

                std::sort(sortedElements_.begin(), sortedElements_.end());

                sortedElements_.erase(std::unique(sortedElements_.begin(), sortedElements_.end()), sortedElements_.end());
            }
        }

        /**
         *  Constructor for a hyperedge element information.
         *
         *  @param[in] elements         The endpoints of the constructed hyperedge.
         *  @param[in] sortedElements   The endpoints of the constructed hyperedge sorted in ascending order without duplicates.
         */
        ElementInformation(std::vector<htd::vertex_t> && elements, std::vector<htd::vertex_t> && sortedElements) HTD_NOEXCEPT : elements_(std::move(elements)), sortedElements_(std::move(sortedElements))
        {
            #ifndef NDEBUG
            std::vector<htd::vertex_t> tmp(elements_.begin(), elements_.end());

            std::sort(tmp.begin(), tmp.end());

            tmp.erase(std::unique(tmp.begin(), tmp.end()), tmp.end());

            HTD_ASSERT(sortedElements_ == tmp)
            #endif

            elements_.shrink_to_fit();

            sortedElements_.shrink_to_fit();
        }

        /**
         *  Constructor for a hyperedge element information.
         *
         *  @param[in] elements The endpoints of the constructed hyperedge.
         */
        ElementInformation(const htd::ConstCollection<htd::vertex_t> & elements) HTD_NOEXCEPT : elements_(elements.begin(), elements.end()), sortedElements_()
        {
            elements_.shrink_to_fit();

            sortedElements_.reserve(elements_.size());

            if (elements.size() == 2)
            {
                htd::vertex_t vertex1 = elements_[0];
                htd::vertex_t vertex2 = elements_[1];

                if (vertex1 > vertex2)
                {
                    sortedElements_.push_back(vertex2);
                    sortedElements_.push_back(vertex1);
                }
                else
                {
                    sortedElements_.push_back(vertex1);
                }
            }
            else
            {
                sortedElements_.insert(sortedElements_.end(), elements_.begin(), elements_.end());

                std::sort(sortedElements_.begin(), sortedElements_.end());

                sortedElements_.erase(std::unique(sortedElements_.begin(), sortedElements_.end()), sortedElements_.end());
            }
        }

        void setElements(htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_NOEXCEPT HTD_OVERRIDE
        {
            elements_.clear();

            elements_.push_back(vertex1);
            elements_.push_back(vertex2);

            sortedElements_.clear();

            sortedElements_.push_back(vertex2);

            if (vertex1 > vertex2)
            {
                sortedElements_.push_back(vertex1);
            }
        }

        /**
         *  Set the endpoints of the hyperedge.
         *
         *  @param[in] elements The new endpoints of the updated hyperedge.
         */
        void setElements(const std::vector<htd::vertex_t> & elements) HTD_NOEXCEPT HTD_OVERRIDE
        {
            elements_.reserve(elements.size());

            elements_ = elements;

            sortedElements_.reserve(elements_.size());

            if (elements_.size() == 2)
            {
                htd::vertex_t vertex1 = elements_[0];
                htd::vertex_t vertex2 = elements_[1];

                if (vertex1 > vertex2)
                {
                    sortedElements_.push_back(vertex2);
                    sortedElements_.push_back(vertex1);
                }
                else
                {
                    sortedElements_.push_back(vertex1);
                }
            }
            else
            {
                sortedElements_.insert(sortedElements_.end(), elements_.begin(), elements_.end());

                std::sort(sortedElements_.begin(), sortedElements_.end());

                sortedElements_.erase(std::unique(sortedElements_.begin(), sortedElements_.end()), sortedElements_.end());
            }
        }

        /**
         *  Set the endpoints of the hyperedge.
         *
         *  @param[in] elements The new endpoints of the updated hyperedge.
         */
        void setElements(std::vector<htd::vertex_t> && elements) HTD_NOEXCEPT HTD_OVERRIDE
        {
            elements_.swap(elements);

            elements_.shrink_to_fit();

            sortedElements_.reserve(elements_.size());

            if (elements_.size() == 2)
            {
                htd::vertex_t vertex1 = elements_[0];
                htd::vertex_t vertex2 = elements_[1];

                if (vertex1 > vertex2)
                {
                    sortedElements_.push_back(vertex2);
                    sortedElements_.push_back(vertex1);
                }
                else
                {
                    sortedElements_.push_back(vertex1);
                }
            }
            else
            {
                sortedElements_.insert(sortedElements_.end(), elements_.begin(), elements_.end());

                std::sort(sortedElements_.begin(), sortedElements_.end());

                sortedElements_.erase(std::unique(sortedElements_.begin(), sortedElements_.end()), sortedElements_.end());
            }
        }

        void setElements(const htd::ConstCollection<htd::vertex_t> & elements) HTD_NOEXCEPT HTD_OVERRIDE
        {
            setElements(std::vector<htd::vertex_t>(elements.begin(), elements.end()));
        }

        const std::vector<htd::vertex_t> & elements(void) const HTD_OVERRIDE
        {
            return elements_;
        }

        const std::vector<htd::vertex_t> & sortedElements(void) const HTD_OVERRIDE
        {
            return sortedElements_;
        }

        bool empty(void) const HTD_OVERRIDE
        {
            return elements_.empty();
        }

        std::size_t size(void) const HTD_OVERRIDE
        {
            return elements_.size();
        }

        bool contains(htd::vertex_t vertex) const HTD_OVERRIDE
        {
            return std::binary_search(sortedElements_.begin(), sortedElements_.end(), vertex);
        }

        void erase(htd::vertex_t vertex) HTD_OVERRIDE
        {
            elements_.erase(std::remove(elements_.begin(), elements_.end(), vertex), elements_.end());

            auto position = std::lower_bound(sortedElements_.begin(), sortedElements_.end(), vertex);

            if (position != sortedElements_.end() && *position == vertex)
            {
                sortedElements_.erase(position);
            }
        }

        std::vector<htd::vertex_t>::const_iterator begin(void) const HTD_OVERRIDE
        {
            return elements_.begin();
        }

        std::vector<htd::vertex_t>::const_iterator end(void) const HTD_OVERRIDE
        {
            return elements_.end();
        }

        const htd::vertex_t & at(htd::index_t index) const HTD_OVERRIDE
        {
            return elements_.at(index);
        }

        const htd::vertex_t & operator[](htd::index_t index) const HTD_OVERRIDE
        {
            return elements_[index];
        }

        ElementInformation * clone(void) const HTD_OVERRIDE
        {
            return new ElementInformation(*this);
        }

        bool isSortedElementInformation(void) const HTD_OVERRIDE
        {
            return false;
        }

    private:
        std::vector<htd::vertex_t> elements_;

        std::vector<htd::vertex_t> sortedElements_;
};

/**
 *  Internal class for storing the element information of a hyperedge which's elements are already sorted and free of duplicates.
 */
class SortedElementInformation : public htd::Hyperedge::IElementInformation
{
    public:
        /**
         *  Constructor for a hyperedge element information.
         *
         *  @param[in] vertex   The single endpoint of the constructed hyperedge.
         */
        SortedElementInformation(htd::vertex_t vertex) HTD_NOEXCEPT : elements_(std::initializer_list<htd::vertex_t> { vertex })
        {

        }

        /**
         *  Constructor for a hyperedge element information.
         *
         *  @param[in] vertex1  The first endpoint of the constructed hyperedge.
         *  @param[in] vertex2  The second endpoint of the constructed hyperedge.
         */
        SortedElementInformation(htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_NOEXCEPT : elements_(std::initializer_list<htd::vertex_t> { vertex1, vertex2 })
        {

        }

        /**
         *  Constructor for a hyperedge element information.
         *
         *  @param[in] elements The endpoints of the constructed hyperedge.
         */
        SortedElementInformation(const std::vector<htd::vertex_t> & elements) HTD_NOEXCEPT : elements_(elements.begin(), elements.end())
        {
            elements_.shrink_to_fit();
        }

        /**
         *  Constructor for a hyperedge element information.
         *
         *  @param[in] elements The endpoints of the constructed hyperedge.
         */
        SortedElementInformation(std::vector<htd::vertex_t> && elements) HTD_NOEXCEPT : elements_(std::move(elements))
        {
            elements_.shrink_to_fit();
        }

        /**
         *  Constructor for a hyperedge element information.
         *
         *  @param[in] elements The endpoints of the constructed hyperedge.
         */
        SortedElementInformation(const htd::ConstCollection<htd::vertex_t> & elements) HTD_NOEXCEPT : elements_(elements.begin(), elements.end())
        {
            elements_.shrink_to_fit();
        }

        void setElements(htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_NOEXCEPT HTD_OVERRIDE
        {
            elements_.clear();

            elements_.push_back(vertex1);
            elements_.push_back(vertex2);
        }

        /**
         *  Set the endpoints of the hyperedge.
         *
         *  @param[in] elements The new endpoints of the updated hyperedge.
         */
        void setElements(const std::vector<htd::vertex_t> & elements) HTD_NOEXCEPT HTD_OVERRIDE
        {
            elements_.reserve(elements.size());

            elements_ = elements;
        }

        /**
         *  Set the endpoints of the hyperedge.
         *
         *  @param[in] elements The new endpoints of the updated hyperedge.
         */
        void setElements(std::vector<htd::vertex_t> && elements) HTD_NOEXCEPT HTD_OVERRIDE
        {
            elements_.swap(elements);

            elements_.shrink_to_fit();
        }

        void setElements(const htd::ConstCollection<htd::vertex_t> & elements) HTD_NOEXCEPT HTD_OVERRIDE
        {
            setElements(std::vector<htd::vertex_t>(elements.begin(), elements.end()));
        }

        const std::vector<htd::vertex_t> & elements(void) const HTD_OVERRIDE
        {
            return elements_;
        }

        const std::vector<htd::vertex_t> & sortedElements(void) const HTD_OVERRIDE
        {
            return elements_;
        }

        bool empty(void) const HTD_OVERRIDE
        {
            return elements_.empty();
        }

        std::size_t size(void) const HTD_OVERRIDE
        {
            return elements_.size();
        }

        bool contains(htd::vertex_t vertex) const HTD_OVERRIDE
        {
            return std::binary_search(elements_.begin(), elements_.end(), vertex);
        }

        void erase(htd::vertex_t vertex) HTD_OVERRIDE
        {
            auto position = std::lower_bound(elements_.begin(), elements_.end(), vertex);

            if (position != elements_.end() && *position == vertex)
            {
                elements_.erase(position);
            }
        }

        std::vector<htd::vertex_t>::const_iterator begin(void) const HTD_OVERRIDE
        {
            return elements_.begin();
        }

        std::vector<htd::vertex_t>::const_iterator end(void) const HTD_OVERRIDE
        {
            return elements_.end();
        }

        const htd::vertex_t & at(htd::index_t index) const HTD_OVERRIDE
        {
            return elements_.at(index);
        }

        const htd::vertex_t & operator[](htd::index_t index) const HTD_OVERRIDE
        {
            return elements_[index];
        }

        SortedElementInformation * clone(void) const HTD_OVERRIDE
        {
            return new SortedElementInformation(*this);
        }

        bool isSortedElementInformation(void) const HTD_OVERRIDE
        {
            return true;
        }

    private:
        std::vector<htd::vertex_t> elements_;
};

htd::Hyperedge::Hyperedge(htd::id_t id, htd::vertex_t vertex) HTD_NOEXCEPT : id_(id)
{
    content_.reset(new SortedElementInformation(vertex));
}

htd::Hyperedge::Hyperedge(htd::id_t id, htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_NOEXCEPT : id_(id)
{
    if (vertex1 < vertex2)
    {
        content_.reset(new SortedElementInformation(vertex1, vertex2));
    }
    else
    {
        content_.reset(new ElementInformation(vertex1, vertex2));
    }
}

htd::Hyperedge::Hyperedge(htd::id_t id, const std::vector<htd::vertex_t> & elements) HTD_NOEXCEPT : id_(id)
{
    if (htd::is_sorted_and_duplicate_free(elements.begin(), elements.end()))
    {
        content_.reset(new SortedElementInformation(elements));
    }
    else
    {
        content_.reset(new ElementInformation(elements));
    }
}

htd::Hyperedge::Hyperedge(htd::id_t id, const std::vector<htd::vertex_t> & elements, const std::vector<htd::vertex_t> & sortedElements) HTD_NOEXCEPT : id_(id)
{
    if (htd::is_sorted_and_duplicate_free(elements.begin(), elements.end()))
    {
        content_.reset(new SortedElementInformation(elements));
    }
    else
    {
        content_.reset(new ElementInformation(elements, sortedElements));
    }
}

htd::Hyperedge::Hyperedge(htd::id_t id, std::vector<htd::vertex_t> && elements) HTD_NOEXCEPT : id_(id)
{
    if (htd::is_sorted_and_duplicate_free(elements.begin(), elements.end()))
    {
        content_.reset(new SortedElementInformation(std::move(elements)));
    }
    else
    {
        content_.reset(new ElementInformation(std::move(elements)));
    }
}

htd::Hyperedge::Hyperedge(htd::id_t id, std::vector<htd::vertex_t> && elements, std::vector<htd::vertex_t> && sortedElements) HTD_NOEXCEPT : id_(id)
{
    if (htd::is_sorted_and_duplicate_free(elements.begin(), elements.end()))
    {
        content_.reset(new SortedElementInformation(std::move(elements)));
    }
    else
    {
        content_.reset(new ElementInformation(std::move(elements), std::move(sortedElements)));
    }
}

htd::Hyperedge::Hyperedge(htd::id_t id, const htd::ConstCollection<htd::vertex_t> & elements) HTD_NOEXCEPT : htd::Hyperedge::Hyperedge(id, std::vector<htd::vertex_t>(elements.begin(), elements.end()))
{

}

htd::Hyperedge::Hyperedge(const htd::Hyperedge & original) HTD_NOEXCEPT : id_(original.id_), content_(original.content_->clone())
{

}

htd::Hyperedge::Hyperedge(htd::Hyperedge && original) HTD_NOEXCEPT : id_(original.id_), content_(std::move(original.content_))
{

}

htd::Hyperedge::~Hyperedge() HTD_NOEXCEPT
{

}

htd::id_t htd::Hyperedge::id(void) const HTD_NOEXCEPT
{
    return id_;
}

void htd::Hyperedge::setId(htd::id_t newId) HTD_NOEXCEPT
{
    id_ = newId;
}

void htd::Hyperedge::setElements(htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_NOEXCEPT
{
    if (content_->isSortedElementInformation())
    {
        if (vertex1 < vertex2)
        {
            content_->setElements(vertex1, vertex2);
        }
        else
        {
            content_.reset(new ElementInformation(vertex1, vertex2));
        }
    }
    else
    {
        if (vertex1 < vertex2)
        {
            content_.reset(new SortedElementInformation(vertex1, vertex2));
        }
        else
        {
            content_->setElements(vertex1, vertex2);
        }
    }
}

void htd::Hyperedge::setElements(const std::vector<htd::vertex_t> & elements) HTD_NOEXCEPT
{
    bool sorted = htd::is_sorted_and_duplicate_free(elements.begin(), elements.end());

    if (content_->isSortedElementInformation())
    {
        if (sorted)
        {
            content_->setElements(elements);
        }
        else
        {
            content_.reset(new ElementInformation(elements));
        }
    }
    else
    {
        if (sorted)
        {
            content_.reset(new SortedElementInformation(elements));
        }
        else
        {
            content_->setElements(elements);
        }
    }
}

void htd::Hyperedge::setElements(std::vector<htd::vertex_t> && elements) HTD_NOEXCEPT
{
    bool sorted = htd::is_sorted_and_duplicate_free(elements.begin(), elements.end());

    if (content_->isSortedElementInformation())
    {
        if (sorted)
        {
            content_->setElements(std::move(elements));
        }
        else
        {
            content_.reset(new ElementInformation(std::move(elements)));
        }
    }
    else
    {
        if (sorted)
        {
            content_.reset(new SortedElementInformation(std::move(elements)));
        }
        else
        {
            content_->setElements(std::move(elements));
        }
    }
}

void htd::Hyperedge::setElements(const htd::ConstCollection<htd::vertex_t> & elements) HTD_NOEXCEPT
{
    setElements(std::vector<htd::vertex_t>(elements.begin(), elements.end()));
}

const std::vector<htd::vertex_t> & htd::Hyperedge::elements(void) const HTD_NOEXCEPT
{
    return content_->elements();
}

const std::vector<htd::vertex_t> & htd::Hyperedge::sortedElements(void) const HTD_NOEXCEPT
{
    return content_->sortedElements();
}

bool htd::Hyperedge::empty(void) const HTD_NOEXCEPT
{
    return content_->empty();
}

std::size_t htd::Hyperedge::size(void) const HTD_NOEXCEPT
{
    return content_->size();
}

bool htd::Hyperedge::contains(htd::vertex_t vertex) const HTD_NOEXCEPT
{
    return content_->contains(vertex);
}

void htd::Hyperedge::erase(htd::vertex_t vertex) HTD_NOEXCEPT
{
    content_->erase(vertex);
}

std::vector<htd::vertex_t>::const_iterator htd::Hyperedge::begin(void) const HTD_NOEXCEPT
{
    return content_->begin();
}

std::vector<htd::vertex_t>::const_iterator htd::Hyperedge::end(void) const HTD_NOEXCEPT
{
    return content_->end();
}

const htd::vertex_t & htd::Hyperedge::at(htd::index_t index) const
{
    return content_->at(index);
}

const htd::vertex_t & htd::Hyperedge::operator[](htd::index_t index) const
{
    return (*content_)[index];
}

htd::Hyperedge & htd::Hyperedge::operator=(const htd::Hyperedge & original)
{
    id_ = original.id_;

    content_.reset(original.content_->clone());

    return *this;
}

htd::Hyperedge & htd::Hyperedge::operator=(htd::Hyperedge && original) HTD_NOEXCEPT
{
    id_ = original.id_;

    content_ = std::move(original.content_);

    return *this;
}

bool htd::Hyperedge::operator<(const htd::Hyperedge & rhs) const
{
    return std::tie(content_->elements(), id_) < std::tie(rhs.content_->elements(), rhs.id_);
}

bool htd::Hyperedge::operator>(const htd::Hyperedge & rhs) const
{
    return std::tie(content_->elements(), id_) > std::tie(rhs.content_->elements(), rhs.id_);
}

bool htd::Hyperedge::operator==(const htd::Hyperedge & rhs) const
{
    return rhs.content_->elements() == content_->elements();
}

bool htd::Hyperedge::operator==(const std::vector<htd::vertex_t> & rhs) const
{
    return rhs == content_->elements();
}

bool htd::Hyperedge::operator!=(const htd::Hyperedge & rhs) const
{
    return rhs.content_->elements() != content_->elements();
}

bool htd::Hyperedge::operator!=(const std::vector<htd::vertex_t> & rhs) const
{
    return rhs != content_->elements();
}

#endif /* HTD_HTD_HYPEREDGE_CPP */
