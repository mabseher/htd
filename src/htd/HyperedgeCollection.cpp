/*
 * File:   HyperedgeCollection.cpp
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

#ifndef HTD_HTD_HYPEREDGECOLLECTION_CPP
#define	HTD_HTD_HYPEREDGECOLLECTION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>

#include <htd/HyperedgeCollection.hpp>

#include <algorithm>
#include <stdexcept>

htd::HyperedgeCollection::HyperedgeCollection(void) : baseCollection_(std::make_shared<std::vector<htd::Hyperedge>>())
{

}

htd::HyperedgeCollection::HyperedgeCollection(const std::vector<htd::Hyperedge> & baseCollection) : baseCollection_(std::make_shared<std::vector<htd::Hyperedge>>(baseCollection))
{

}

htd::HyperedgeCollection::HyperedgeCollection(std::vector<htd::Hyperedge> && baseCollection) : baseCollection_(std::make_shared<std::vector<htd::Hyperedge>>(std::move(baseCollection)))
{

}

htd::HyperedgeCollection::HyperedgeCollection(std::shared_ptr<std::vector<htd::Hyperedge>> baseCollection) : baseCollection_(baseCollection)
{

}

htd::HyperedgeCollection::~HyperedgeCollection()
{

}

std::size_t htd::HyperedgeCollection::size(void) const
{
    return baseCollection_->size();
}

bool htd::HyperedgeCollection::operator==(const htd::HyperedgeCollection & rhs) const
{
    return baseCollection_ == rhs.baseCollection_;
}

bool htd::HyperedgeCollection::operator!=(const htd::HyperedgeCollection & rhs) const
{
    return baseCollection_ != rhs.baseCollection_;
}

htd::HyperedgeCollection::HyperedgeCollectionConstIterator htd::HyperedgeCollection::begin(void) const
{
    return htd::HyperedgeCollection::HyperedgeCollectionConstIterator(*this, 0);
}

htd::HyperedgeCollection::HyperedgeCollectionConstIterator htd::HyperedgeCollection::end(void) const
{
    return htd::HyperedgeCollection::HyperedgeCollectionConstIterator(*this, baseCollection_->size());
}

htd::HyperedgeCollection::HyperedgeCollectionConstIterator::HyperedgeCollectionConstIterator(const HyperedgeCollection & collection, htd::index_t position) : baseCollection_(collection.baseCollection_), position_(position)
{

}

htd::HyperedgeCollection::HyperedgeCollectionConstIterator::HyperedgeCollectionConstIterator(const htd::HyperedgeCollection::HyperedgeCollectionConstIterator & original) : baseCollection_(original.baseCollection_), position_(original.position_)
{

}

htd::HyperedgeCollection::HyperedgeCollectionConstIterator::HyperedgeCollectionConstIterator(htd::HyperedgeCollection::HyperedgeCollectionConstIterator && original) : baseCollection_(std::move(original.baseCollection_)), position_(original.position_)
{

}

htd::HyperedgeCollection::HyperedgeCollectionConstIterator::~HyperedgeCollectionConstIterator()
{

}

htd::HyperedgeCollection::HyperedgeCollectionConstIterator & htd::HyperedgeCollection::HyperedgeCollectionConstIterator::operator++(void)
{
    ++position_;

    return *this;
}

htd::HyperedgeCollection::HyperedgeCollectionConstIterator htd::HyperedgeCollection::HyperedgeCollectionConstIterator::operator++(int)
{
    htd::HyperedgeCollection::HyperedgeCollectionConstIterator ret(*this);

    operator++();

    return ret;
}

htd::HyperedgeCollection::HyperedgeCollectionConstIterator & htd::HyperedgeCollection::HyperedgeCollectionConstIterator::operator+=(std::size_t positions)
{
    position_ += positions;

    return *this;
}

htd::HyperedgeCollection::HyperedgeCollectionConstIterator & htd::HyperedgeCollection::HyperedgeCollectionConstIterator::operator--(void)
{
    --position_;

    return *this;
}

htd::HyperedgeCollection::HyperedgeCollectionConstIterator htd::HyperedgeCollection::HyperedgeCollectionConstIterator::operator--(int)
{
    htd::HyperedgeCollection::HyperedgeCollectionConstIterator ret(*this);

    operator--();

    return ret;
}

htd::HyperedgeCollection::HyperedgeCollectionConstIterator & htd::HyperedgeCollection::HyperedgeCollectionConstIterator::operator-=(std::size_t positions)
{
    position_ -= positions;

    return *this;
}

std::size_t htd::HyperedgeCollection::HyperedgeCollectionConstIterator::operator-(const htd::HyperedgeCollection::HyperedgeCollectionConstIterator & rhs)
{
    if (baseCollection_ != rhs.baseCollection_)
    {
        throw std::logic_error("std::size_t htd::HyperedgeCollection::HyperedgeCollectionConstIterator::operator-(const htd::HyperedgeCollection::HyperedgeCollectionConstIterator &)");
    }

    return position_ - rhs.position_;
}

const htd::Hyperedge * htd::HyperedgeCollection::HyperedgeCollectionConstIterator::operator->(void) const
{
    return &(baseCollection_->at(position_));
}

const htd::Hyperedge & htd::HyperedgeCollection::HyperedgeCollectionConstIterator::operator*(void) const
{
    return baseCollection_->at(position_);
}

bool htd::HyperedgeCollection::HyperedgeCollectionConstIterator::operator==(const htd::HyperedgeCollection::HyperedgeCollectionConstIterator & rhs) const
{
    return baseCollection_ == rhs.baseCollection_ && position_ == rhs.position_;
}

bool htd::HyperedgeCollection::HyperedgeCollectionConstIterator::operator!=(const htd::HyperedgeCollection::HyperedgeCollectionConstIterator & rhs) const
{
    return baseCollection_ != rhs.baseCollection_ || position_ != rhs.position_;
}

htd::HyperedgeCollection::HyperedgeCollectionConstIterator & htd::HyperedgeCollection::HyperedgeCollectionConstIterator::operator=(const htd::HyperedgeCollection::HyperedgeCollectionConstIterator & original)
{
    baseCollection_ = original.baseCollection_;

    position_ = original.position_;

    return *this;
}

htd::HyperedgeCollection::HyperedgeCollectionConstIterator & htd::HyperedgeCollection::HyperedgeCollectionConstIterator::operator=(htd::HyperedgeCollection::HyperedgeCollectionConstIterator && original)
{
    baseCollection_ = original.baseCollection_;

    position_ = original.position_;

    return *this;
}

#endif /* HTD_HTD_HYPEREDGECOLLECTION_CPP */
