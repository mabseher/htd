/*
 * File:   FilteredHyperedgeCollection.cpp
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

#ifndef HTD_HTD_FILTEREDHYPEREDGECOLLECTION_CPP
#define	HTD_HTD_FILTEREDHYPEREDGECOLLECTION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>

#include <htd/FilteredHyperedgeCollection.hpp>

#include <algorithm>
#include <stdexcept>

htd::FilteredHyperedgeCollection::FilteredHyperedgeCollection(void) : written_(true), baseCollection_(std::make_shared<std::vector<htd::Hyperedge>>()), relevantIndices_(std::make_shared<std::vector<htd::index_t>>())
{

}

htd::FilteredHyperedgeCollection::FilteredHyperedgeCollection(const std::vector<htd::Hyperedge> & baseCollection, const std::vector<htd::index_t> & relevantIndices) : written_(true), baseCollection_(std::make_shared<std::vector<htd::Hyperedge>>(baseCollection)), relevantIndices_(std::make_shared<std::vector<htd::index_t>>(relevantIndices))
{

}

htd::FilteredHyperedgeCollection::FilteredHyperedgeCollection(std::vector<htd::Hyperedge> && baseCollection, std::vector<htd::index_t> && relevantIndices) : written_(true), baseCollection_(std::make_shared<std::vector<htd::Hyperedge>>(std::move(baseCollection))), relevantIndices_(std::make_shared<std::vector<htd::index_t>>(std::move(relevantIndices)))
{

}

htd::FilteredHyperedgeCollection::FilteredHyperedgeCollection(std::shared_ptr<std::vector<htd::Hyperedge>> baseCollection, const std::vector<htd::index_t> & relevantIndices) : written_(true), baseCollection_(baseCollection), relevantIndices_(std::make_shared<std::vector<htd::index_t>>(relevantIndices))
{

}

htd::FilteredHyperedgeCollection::FilteredHyperedgeCollection(std::shared_ptr<std::vector<htd::Hyperedge>> baseCollection, std::vector<htd::index_t> && relevantIndices) : written_(true), baseCollection_(baseCollection), relevantIndices_(std::make_shared<std::vector<htd::index_t>>(std::move(relevantIndices)))
{

}

htd::FilteredHyperedgeCollection::FilteredHyperedgeCollection(const htd::FilteredHyperedgeCollection & hyperedges) : written_(false), baseCollection_(hyperedges.baseCollection_), relevantIndices_(hyperedges.relevantIndices_)
{

}

htd::FilteredHyperedgeCollection::FilteredHyperedgeCollection(htd::FilteredHyperedgeCollection && hyperedges) : written_(hyperedges.written_), baseCollection_(std::move(hyperedges.baseCollection_)), relevantIndices_(std::move(hyperedges.relevantIndices_))
{

}

htd::FilteredHyperedgeCollection::~FilteredHyperedgeCollection()
{

}

std::size_t htd::FilteredHyperedgeCollection::size(void) const
{
    return relevantIndices_->size();
}

htd::FilteredHyperedgeCollection & htd::FilteredHyperedgeCollection::operator=(const htd::FilteredHyperedgeCollection & original)
{
    if (this != &original)
    {
        written_ = false;

        baseCollection_ = original.baseCollection_;

        relevantIndices_ = original.relevantIndices_;
    }

    return *this;
}

htd::FilteredHyperedgeCollection & htd::FilteredHyperedgeCollection::operator=(htd::FilteredHyperedgeCollection && original)
{
    written_ = original.written_;

    baseCollection_ = std::move(original.baseCollection_);

    relevantIndices_ = std::move(original.relevantIndices_);

    return *this;
}

bool htd::FilteredHyperedgeCollection::operator==(const htd::FilteredHyperedgeCollection & rhs) const
{
    return baseCollection_ == rhs.baseCollection_ && relevantIndices_ == rhs.relevantIndices_;
}

bool htd::FilteredHyperedgeCollection::operator!=(const htd::FilteredHyperedgeCollection & rhs) const
{
    return baseCollection_ != rhs.baseCollection_ || relevantIndices_ != rhs.relevantIndices_;
}

void htd::FilteredHyperedgeCollection::restrictTo(const std::vector<htd::vertex_t> & vertices)
{
    if (!written_)
    {
        relevantIndices_ = std::make_shared<std::vector<htd::index_t>>(*relevantIndices_);

        written_ = true;
    }

    relevantIndices_->erase(std::remove_if(relevantIndices_->begin(), relevantIndices_->end(), [&](htd::index_t index) {
        const std::vector<htd::vertex_t> & sortedElements = baseCollection_->at(index).sortedElements();

        return htd::has_non_empty_set_difference(sortedElements.begin(), sortedElements.end(), vertices.begin(), vertices.end());
    }), relevantIndices_->end());
}

htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator htd::FilteredHyperedgeCollection::begin(void) const
{
    return htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator(*this, 0);
}

htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator htd::FilteredHyperedgeCollection::end(void) const
{
    return htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator(*this, relevantIndices_->size());
}

htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator::FilteredHyperedgeCollectionConstIterator(const FilteredHyperedgeCollection & collection, htd::index_t position) : baseCollection_(collection.baseCollection_), relevantIndices_(collection.relevantIndices_), position_(position)
{

}

htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator::FilteredHyperedgeCollectionConstIterator(const htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator & original) : baseCollection_(original.baseCollection_), relevantIndices_(original.relevantIndices_), position_(original.position_)
{

}

htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator::FilteredHyperedgeCollectionConstIterator(htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator && original) : baseCollection_(std::move(original.baseCollection_)), relevantIndices_(std::move(original.relevantIndices_)), position_(original.position_)
{

}

htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator::~FilteredHyperedgeCollectionConstIterator()
{

}

htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator & htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator::operator++(void)
{
    ++position_;

    return *this;
}

htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator::operator++(int)
{
    htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator ret(*this);

    operator++();

    return ret;
}

htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator & htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator::operator+=(std::size_t positions)
{
    position_ += positions;

    return *this;
}

htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator & htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator::operator--(void)
{
    --position_;

    return *this;
}

htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator::operator--(int)
{
    htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator ret(*this);

    operator--();

    return ret;
}

htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator & htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator::operator-=(std::size_t positions)
{
    position_ -= positions;

    return *this;
}

std::size_t htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator::operator-(const htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator & rhs)
{
    if (baseCollection_ != rhs.baseCollection_ || relevantIndices_ != rhs.relevantIndices_)
    {
        throw std::logic_error("std::size_t htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator::operator-(const htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator &)");
    }

    return position_ - rhs.position_;
}

const htd::Hyperedge * htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator::operator->(void) const
{
    return &(baseCollection_->at(relevantIndices_->at(position_)));
}

const htd::Hyperedge & htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator::operator*(void) const
{
    return baseCollection_->at(relevantIndices_->at(position_));
}

bool htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator::operator==(const htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator & rhs) const
{
    return baseCollection_ == rhs.baseCollection_ && relevantIndices_ == rhs.relevantIndices_ && position_ == rhs.position_;
}

bool htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator::operator!=(const htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator & rhs) const
{
    return baseCollection_ != rhs.baseCollection_ || relevantIndices_ != rhs.relevantIndices_ || position_ != rhs.position_;
}

htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator & htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator::operator=(const htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator & original)
{
    baseCollection_ = original.baseCollection_;

    relevantIndices_ = original.relevantIndices_;

    position_ = original.position_;

    return *this;
}

htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator & htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator::operator=(htd::FilteredHyperedgeCollection::FilteredHyperedgeCollectionConstIterator && original)
{
    baseCollection_ = original.baseCollection_;

    relevantIndices_ = original.relevantIndices_;

    position_ = original.position_;

    return *this;
}

#endif /* HTD_HTD_FILTEREDHYPEREDGECOLLECTION_CPP */
