/*
 * File:   HyperedgePointerDeque.cpp
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

#ifndef HTD_HTD_HYPEREDGEPOINTERDEQUE_CPP
#define HTD_HTD_HYPEREDGEPOINTERDEQUE_CPP

#include <htd/Globals.hpp>
#include <htd/HyperedgePointerDeque.hpp>

#include <htd/ConstPointerIteratorWrapper.hpp>

#include <htd/Algorithm.hpp>

htd::HyperedgePointerDeque::HyperedgePointerDeque(const std::deque<htd::Hyperedge *> & baseCollection) : baseCollection_(std::make_shared<std::deque<htd::Hyperedge *>>(baseCollection))
{

}

htd::HyperedgePointerDeque::HyperedgePointerDeque(std::deque<htd::Hyperedge *> && baseCollection) : baseCollection_(std::make_shared<std::deque<htd::Hyperedge *>>(std::move(baseCollection)))
{

}

htd::HyperedgePointerDeque::HyperedgePointerDeque(const std::shared_ptr<std::deque<htd::Hyperedge *>> & baseCollection) : baseCollection_(baseCollection)
{

}

htd::HyperedgePointerDeque::HyperedgePointerDeque(const htd::HyperedgePointerDeque & original) : baseCollection_(original.baseCollection_)
{

}

htd::HyperedgePointerDeque::HyperedgePointerDeque(htd::HyperedgePointerDeque && original) : baseCollection_(std::move(original.baseCollection_))
{

}

htd::HyperedgePointerDeque::~HyperedgePointerDeque()
{

}

bool htd::HyperedgePointerDeque::empty(void) const
{
    return baseCollection_->empty();
}

std::size_t htd::HyperedgePointerDeque::size(void) const
{
    return baseCollection_->size();
}

const htd::Hyperedge & htd::HyperedgePointerDeque::at(htd::index_t index) const
{
    return *(baseCollection_->at(index));
}

htd::ConstIterator<htd::Hyperedge> htd::HyperedgePointerDeque::begin(void) const
{
    return static_cast<htd::ConstIteratorBase<htd::Hyperedge> *>(new htd::ConstPointerIteratorWrapper<std::deque<htd::Hyperedge *>::const_iterator, htd::Hyperedge>(baseCollection_->begin()));
}

htd::ConstIterator<htd::Hyperedge> htd::HyperedgePointerDeque::end(void) const
{
    return static_cast<htd::ConstIteratorBase<htd::Hyperedge> *>(new htd::ConstPointerIteratorWrapper<std::deque<htd::Hyperedge *>::const_iterator, htd::Hyperedge>(baseCollection_->end()));
}

const htd::Hyperedge & htd::HyperedgePointerDeque::operator[](htd::index_t index) const
{
    return *(baseCollection_->at(index));
}

bool htd::HyperedgePointerDeque::operator==(const htd::IHyperedgeCollection & rhs) const
{
    return rhs.size() == baseCollection_->size() && htd::equal(rhs.begin(), rhs.end(), begin(), end());
}

bool htd::HyperedgePointerDeque::operator!=(const htd::IHyperedgeCollection & rhs) const
{
    return rhs.size() != baseCollection_->size() || !htd::equal(rhs.begin(), rhs.end(), begin(), end());
}

htd::HyperedgePointerDeque * htd::HyperedgePointerDeque::clone(void) const
{
    return new htd::HyperedgePointerDeque(baseCollection_);
}

#endif /* HTD_HTD_HYPEREDGEPOINTERDEQUE_CPP */
