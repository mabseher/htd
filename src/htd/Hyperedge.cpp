/* 
 * File:   Hyperedge.cpp
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

#ifndef HTD_HTD_HYPEREDGE_CPP
#define	HTD_HTD_HYPEREDGE_CPP

#include <htd/Hyperedge.hpp>

htd::Hyperedge::Hyperedge(htd::id_t id, htd::vertex_t vertex1, htd::vertex_t vertex2) : written_(true), id_(id), elements_(std::make_shared<std::vector<htd::vertex_t>>()), sortedElements_(std::make_shared<std::vector<htd::vertex_t>>())
{
    elements_->reserve(2);

    elements_->push_back(vertex1);
    elements_->push_back(vertex2);

    if (vertex1 < vertex2)
    {
        sortedElements_->push_back(vertex1);
        sortedElements_->push_back(vertex2);
    }
    else if (vertex1 > vertex2)
    {
        sortedElements_->push_back(vertex2);
        sortedElements_->push_back(vertex1);
    }
    else
    {
        sortedElements_->push_back(vertex1);
    }
}

htd::Hyperedge::Hyperedge(htd::id_t id, const std::vector<htd::vertex_t> & elements) : written_(true), id_(id), elements_(std::make_shared<std::vector<htd::vertex_t>>(elements.begin(), elements.end())), sortedElements_(std::make_shared<std::vector<htd::vertex_t>>())
{
    elements_->shrink_to_fit();

    sortedElements_->reserve(elements_->size());

    switch (elements_->size())
    {
        case 0:
        {
            break;
        }
        case 1:
        {
            sortedElements_->push_back(elements_->at(0));

            break;
        }
        case 2:
        {
            htd::vertex_t vertex1 = elements_->at(0);
            htd::vertex_t vertex2 = elements_->at(1);

            if (vertex1 < vertex2)
            {
                sortedElements_->push_back(vertex1);
                sortedElements_->push_back(vertex2);
            }
            else if (vertex1 > vertex2)
            {
                sortedElements_->push_back(vertex2);
                sortedElements_->push_back(vertex1);
            }
            else
            {
                sortedElements_->push_back(vertex1);
            }

            break;
        }
        default:
        {
            std::copy(elements_->begin(), elements_->end(), std::back_inserter(*sortedElements_));

            std::sort(sortedElements_->begin(), sortedElements_->end());

            sortedElements_->erase(std::unique(sortedElements_->begin(), sortedElements_->end()), sortedElements_->end());

            break;
        }
    }
}

htd::Hyperedge::Hyperedge(htd::id_t id, std::vector<htd::vertex_t> && elements) HTD_NOEXCEPT : written_(true), id_(id), elements_(std::make_shared<std::vector<htd::vertex_t>>()), sortedElements_(std::make_shared<std::vector<htd::vertex_t>>())
{
    elements_->swap(elements);

    elements_->shrink_to_fit();

    sortedElements_->reserve(elements_->size());

    switch (elements_->size())
    {
        case 0:
        {
            break;
        }
        case 1:
        {
            sortedElements_->push_back(elements_->at(0));

            break;
        }
        case 2:
        {
            htd::vertex_t vertex1 = elements_->at(0);
            htd::vertex_t vertex2 = elements_->at(1);

            if (vertex1 < vertex2)
            {
                sortedElements_->push_back(vertex1);
                sortedElements_->push_back(vertex2);
            }
            else if (vertex1 > vertex2)
            {
                sortedElements_->push_back(vertex2);
                sortedElements_->push_back(vertex1);
            }
            else
            {
                sortedElements_->push_back(vertex1);
            }

            break;
        }
        default:
        {
            std::copy(elements_->begin(), elements_->end(), std::back_inserter(*sortedElements_));

            std::sort(sortedElements_->begin(), sortedElements_->end());

            sortedElements_->erase(std::unique(sortedElements_->begin(), sortedElements_->end()), sortedElements_->end());

            break;
        }
    }
}

htd::Hyperedge::Hyperedge(htd::id_t id, const htd::ConstCollection<htd::vertex_t> & elements) : written_(true), id_(id), elements_(std::make_shared<std::vector<htd::vertex_t>>(elements.begin(), elements.end())), sortedElements_(std::make_shared<std::vector<htd::vertex_t>>())
{
    elements_->shrink_to_fit();

    sortedElements_->reserve(elements_->size());

    switch (elements_->size())
    {
        case 0:
        {
            break;
        }
        case 1:
        {
            sortedElements_->push_back(elements_->at(0));

            break;
        }
        case 2:
        {
            htd::vertex_t vertex1 = elements_->at(0);
            htd::vertex_t vertex2 = elements_->at(1);

            if (vertex1 < vertex2)
            {
                sortedElements_->push_back(vertex1);
                sortedElements_->push_back(vertex2);
            }
            else if (vertex1 > vertex2)
            {
                sortedElements_->push_back(vertex2);
                sortedElements_->push_back(vertex1);
            }
            else
            {
                sortedElements_->push_back(vertex1);
            }

            break;
        }
        default:
        {
            std::copy(elements_->begin(), elements_->end(), std::back_inserter(*sortedElements_));

            std::sort(sortedElements_->begin(), sortedElements_->end());

            sortedElements_->erase(std::unique(sortedElements_->begin(), sortedElements_->end()), sortedElements_->end());

            break;
        }
    }
}

htd::Hyperedge::Hyperedge(const htd::Hyperedge & original) : written_(false), id_(original.id_), elements_(original.elements_), sortedElements_(original.sortedElements_)
{

}

htd::Hyperedge::Hyperedge(htd::Hyperedge && original) HTD_NOEXCEPT : written_(original.written_), id_(original.id_), elements_(std::move(original.elements_)), sortedElements_(std::move(original.sortedElements_))
{

}

htd::Hyperedge::~Hyperedge()
{

}

htd::id_t htd::Hyperedge::id() const
{
    return id_;
}

void htd::Hyperedge::setId(htd::id_t newId)
{
    id_ = newId;
}

const std::vector<htd::vertex_t> & htd::Hyperedge::elements() const
{
    return *elements_;
}

const std::vector<htd::vertex_t> & htd::Hyperedge::sortedElements() const
{
    return *sortedElements_;
}

bool htd::Hyperedge::empty() const
{
    return elements_->empty();
}

std::size_t htd::Hyperedge::size() const
{
    return elements_->size();
}

bool htd::Hyperedge::containsVertex(htd::vertex_t vertex) const
{
    return std::binary_search(sortedElements_->begin(), sortedElements_->end(), vertex);
}

void htd::Hyperedge::erase(htd::vertex_t vertex)
{
    if (!written_)
    {
        elements_ = std::make_shared<std::vector<htd::vertex_t>>(*elements_);

        sortedElements_ = std::make_shared<std::vector<htd::vertex_t>>(*sortedElements_);

        written_ = true;
    }

    elements_->erase(std::remove(elements_->begin(), elements_->end(), vertex), elements_->end());

    auto position = std::lower_bound(sortedElements_->begin(), sortedElements_->end(), vertex);

    if (position != sortedElements_->end())
    {
        sortedElements_->erase(position);
    }
}

std::vector<htd::vertex_t>::const_iterator htd::Hyperedge::begin(void) const
{
    return elements_->begin();
}

std::vector<htd::vertex_t>::const_iterator htd::Hyperedge::end(void) const
{
    return elements_->end();
}

const htd::vertex_t & htd::Hyperedge::operator[](htd::index_t index) const
{
    return elements_->at(index);
}

htd::Hyperedge & htd::Hyperedge::operator=(const htd::Hyperedge & original)
{
    id_ = original.id_;

    written_ = false;

    elements_ = original.elements_;

    sortedElements_ = original.sortedElements_;

    return *this;
}

htd::Hyperedge & htd::Hyperedge::operator=(htd::Hyperedge && original) HTD_NOEXCEPT
{
    id_ = original.id_;

    written_ = original.written_;

    elements_ = std::move(original.elements_);

    sortedElements_ = std::move(original.sortedElements_);

    return *this;
}

bool htd::Hyperedge::operator<(const htd::Hyperedge & rhs) const
{
    return std::tie(*elements_, id_) < std::tie(*(rhs.elements_), rhs.id_);
}

bool htd::Hyperedge::operator>(const htd::Hyperedge & rhs) const
{
    return std::tie(*elements_, id_) > std::tie(*(rhs.elements_), rhs.id_);
}

bool htd::Hyperedge::operator==(const htd::Hyperedge & rhs) const
{
    return *(rhs.elements_) == *elements_;
}

bool htd::Hyperedge::operator!=(const htd::Hyperedge & rhs) const
{
    return *(rhs.elements_) != *elements_;
}

#endif /* HTD_HTD_HYPEREDGE_CPP */
