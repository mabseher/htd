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

htd::Hyperedge::Hyperedge(htd::id_t id) : written_(true), id_(id), elements_(std::make_shared<std::vector<htd::vertex_t>>())
{

}

htd::Hyperedge::Hyperedge(htd::id_t id, htd::vertex_t vertex1, htd::vertex_t vertex2) : written_(true), id_(id), elements_(std::make_shared<std::vector<htd::vertex_t>>())
{
    elements_->push_back(vertex1);
    elements_->push_back(vertex2);
}

htd::Hyperedge::Hyperedge(htd::id_t id, const std::vector<htd::vertex_t> & elements) : written_(true), id_(id), elements_(std::make_shared<std::vector<htd::vertex_t>>(elements.begin(), elements.end()))
{

}

htd::Hyperedge::Hyperedge(htd::id_t id, std::vector<htd::vertex_t> && elements) HTD_NOEXCEPT : written_(true), id_(id), elements_(std::make_shared<std::vector<htd::vertex_t>>())
{
    std::swap(elements, *elements_);
}

htd::Hyperedge::Hyperedge(htd::id_t id, const htd::ConstCollection<htd::vertex_t> & elements) : written_(true), id_(id), elements_(std::make_shared<std::vector<htd::vertex_t>>(elements.begin(), elements.end()))
{

}

htd::Hyperedge::Hyperedge(const htd::Hyperedge & original) : written_(false), id_(original.id_), elements_(original.elements_)
{

}

htd::Hyperedge::Hyperedge(htd::Hyperedge && original) HTD_NOEXCEPT : written_(original.written_), id_(original.id_), elements_(std::move(original.elements_))
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

htd::Collection<htd::vertex_t> htd::Hyperedge::elements()
{
    if (!written_)
    {
        elements_ = std::make_shared<std::vector<htd::vertex_t>>(*elements_);

        written_ = true;
    }

    return htd::Collection<htd::vertex_t>::getInstance(*elements_);
}

htd::ConstCollection<htd::vertex_t> htd::Hyperedge::elements() const
{
    return htd::ConstCollection<htd::vertex_t>::getInstance(*elements_);
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
    return std::find(elements_->begin(), elements_->end(), vertex) != elements_->end();
}

void htd::Hyperedge::push_back(htd::vertex_t vertex)
{
    if (!written_)
    {
        elements_ = std::make_shared<std::vector<htd::vertex_t>>(*elements_);

        written_ = true;
    }

    elements_->push_back(vertex);
}

void htd::Hyperedge::erase(htd::vertex_t vertex)
{
    if (!written_)
    {
        elements_ = std::make_shared<std::vector<htd::vertex_t>>(*elements_);

        written_ = true;
    }

    elements_->erase(std::remove(elements_->begin(), elements_->end(), vertex), elements_->end());
}

htd::Iterator<htd::vertex_t> htd::Hyperedge::begin(void)
{
    if (!written_)
    {
        elements_ = std::make_shared<std::vector<htd::vertex_t>>(*elements_);

        written_ = true;
    }

    return htd::Iterator<htd::vertex_t>(elements_->begin());
}

const htd::ConstIterator<htd::vertex_t> htd::Hyperedge::begin(void) const
{
    return htd::ConstIterator<htd::vertex_t>(elements_->begin());
}

htd::Iterator<htd::vertex_t> htd::Hyperedge::end(void)
{
    if (!written_)
    {
        elements_ = std::make_shared<std::vector<htd::vertex_t>>(*elements_);

        written_ = true;
    }

    return htd::Iterator<htd::vertex_t>(elements_->end());
}

const htd::ConstIterator<htd::vertex_t> htd::Hyperedge::end(void) const
{
    return htd::ConstIterator<htd::vertex_t>(elements_->end());
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

    return *this;
}

htd::Hyperedge & htd::Hyperedge::operator=(htd::Hyperedge && original) HTD_NOEXCEPT
{
    id_ = original.id_;

    written_ = original.written_;

    elements_ = std::move(original.elements_);

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
    return rhs.id_ == id_ && *(rhs.elements_) == *elements_;
}

bool htd::Hyperedge::operator!=(const htd::Hyperedge & rhs) const
{
    return rhs.id_ != id_ || *(rhs.elements_) != *elements_;
}

#endif /* HTD_HTD_HYPEREDGE_CPP */
