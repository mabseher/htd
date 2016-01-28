/*
 * File:   SortedVertexSet.cpp
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

#ifndef HTD_HTD_SORTEDVERTEXSET_CPP
#define	HTD_HTD_SORTEDVERTEXSET_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>

#include <htd/SortedVertexSet.hpp>

#include <algorithm>
#include <stdexcept>

htd::SortedVertexSet::SortedVertexSet(void) : size_(0), capacity_(Container::MAXIMUM_CONTAINER_SIZE), first_(new Container(nullptr, nullptr)), last_(first_)
{

}

htd::SortedVertexSet::~SortedVertexSet()
{
    Container * container = nullptr;

    while (last_ != nullptr)
    {
        container = last_->prev_;

        delete last_;

        last_ = container;
    }
}

std::size_t htd::SortedVertexSet::size(void) const
{
    return size_;
}

std::size_t htd::SortedVertexSet::capacity(void) const
{
    return capacity_;
}

void htd::SortedVertexSet::insert(htd::vertex_t vertex)
{
    Container * container = first_;

    while (container->next_ != nullptr && container->next_->elements_[0] <= vertex)
    {
        container = container->next_;
    }

    if (container->size_ == Container::MAXIMUM_CONTAINER_SIZE && container->elements_[Container::MAXIMUM_CONTAINER_SIZE - 1] < vertex)
    {
        if (container->next_ != nullptr)
        {
            container = container->next_;
        }
        else
        {
            Container * newContainer = new Container(container, container->next_);

            if (newContainer->next_ == nullptr)
            {
                last_ = newContainer;
            }

            container = newContainer;

            capacity_ += Container::MAXIMUM_CONTAINER_SIZE;
        }
    }

    insert(vertex, container);
}

void htd::SortedVertexSet::insert(htd::vertex_t vertex, Container * container)
{
    std::array<htd::vertex_t, Container::MAXIMUM_CONTAINER_SIZE> & elements = container->elements_;

    if (container->size_ < Container::MAXIMUM_CONTAINER_SIZE)
    {
        auto position = std::lower_bound(elements.begin(), elements.begin() + container->size_, vertex);

        if (position == elements.begin() + container->size_ || *position != vertex)
        {
            if (position < elements.begin() + container->size_)
            {
                std::copy_backward(position, elements.begin() + container->size_, elements.begin() + container->size_ + 1);
            }

            *position = vertex;

            container->size_++;

            ++size_;
        }
    }
    else
    {
        auto position = std::lower_bound(elements.begin(), elements.end(), vertex);

        if (*position != vertex)
        {
            if (container->next_ != nullptr && container->next_->size_ < Container::MAXIMUM_CONTAINER_SIZE)
            {
                std::size_t nextSize = container->next_->size_;

                std::array<htd::vertex_t, Container::MAXIMUM_CONTAINER_SIZE> & nextElements = container->next_->elements_;

                std::copy_backward(nextElements.begin(), nextElements.begin() + nextSize, nextElements.begin() + nextSize + 1);

                nextElements[0] = elements[Container::MAXIMUM_CONTAINER_SIZE - 1];

                container->next_->size_++;

                std::copy_backward(position, elements.begin() + Container::MAXIMUM_CONTAINER_SIZE - 1, elements.begin() + Container::MAXIMUM_CONTAINER_SIZE);

                *position = vertex;
            }
            else if (container->prev_ != nullptr && container->prev_->size_ < Container::MAXIMUM_CONTAINER_SIZE)
            {
                std::array<htd::vertex_t, Container::MAXIMUM_CONTAINER_SIZE> & prevElements = container->prev_->elements_;

                prevElements[container->prev_->size_] = elements[0];

                container->prev_->size_++;

                std::copy(elements.begin() + 1, position, elements.begin());

                *(--position) = vertex;
            }
            else
            {
                Container * newContainer = new Container(container, container->next_);

                std::array<htd::vertex_t, Container::MAXIMUM_CONTAINER_SIZE> & nextElements = newContainer->elements_;

                nextElements[0] = elements[Container::MAXIMUM_CONTAINER_SIZE - 1];

                newContainer->size_++;

                std::copy_backward(position, elements.begin() + Container::MAXIMUM_CONTAINER_SIZE - 1, elements.begin() + Container::MAXIMUM_CONTAINER_SIZE);

                *position = vertex;

                if (newContainer->next_ == nullptr)
                {
                    last_ = newContainer;
                }

                capacity_ += Container::MAXIMUM_CONTAINER_SIZE;
            }

            ++size_;
        }
    }
}

void htd::SortedVertexSet::erase(htd::vertex_t vertex)
{
    Container * container = first_;

    while (container->next_ != nullptr && container->next_->elements_[0] <= vertex)
    {
        container = container->next_;
    }

    erase(vertex, container);
}

htd::SortedVertexSet::Container * htd::SortedVertexSet::erase(htd::vertex_t vertex, Container * container)
{
    std::array<htd::vertex_t, Container::MAXIMUM_CONTAINER_SIZE> & elements = container->elements_;

    Container * ret = container;

    if (container->size_ > 0 && container->elements_[container->size_ - 1] >= vertex)
    {
        auto position = std::lower_bound(elements.begin(), elements.begin() + container->size_, vertex);

        if (*position == vertex)
        {
            if (position < elements.begin() + container->size_)
            {
                std::copy(position + 1, elements.begin() + container->size_, position);
            }

            container->size_--;

            --size_;

            if (container->size_ == 0)
            {
                if (container->prev_ == nullptr && container->next_ != nullptr)
                {
                    first_ = container->next_;
                    first_->prev_ = nullptr;

                    delete container;

                    capacity_ -= Container::MAXIMUM_CONTAINER_SIZE;

                    ret = first_;
                }
                else if (container->next_ == nullptr && container->prev_ != nullptr)
                {
                    last_ = container->prev_;
                    last_->next_ = nullptr;

                    delete container;

                    capacity_ -= Container::MAXIMUM_CONTAINER_SIZE;

                    ret = last_;
                }
                else if (container->next_ != nullptr && container->prev_ != nullptr)
                {
                    Container * tmp = container;

                    container->prev_->next_ = tmp->next_;
                    container->next_->prev_ = tmp->prev_;

                    ret = tmp->next_;

                    delete container;

                    capacity_ -= Container::MAXIMUM_CONTAINER_SIZE;
                }
            }
            else if (container->prev_ != nullptr && container->prev_->size_ + container->size_ <= Container::MAXIMUM_CONTAINER_SIZE)
            {
                std::copy(elements.begin(), elements.begin() + container->size_, container->prev_->elements_.begin() + container->prev_->size_);

                container->prev_->size_ += container->size_;

                ret = container->prev_;

                if (container->next_ == nullptr)
                {
                    last_ = container->prev_;
                    last_->next_ = nullptr;
                }
                else
                {
                    Container * tmp = container;

                    container->prev_->next_ = tmp->next_;
                    container->next_->prev_ = tmp->prev_;
                }

                delete container;

                capacity_ -= Container::MAXIMUM_CONTAINER_SIZE;
            }
            else if (container->next_ != nullptr && container->next_->size_ + container->size_ <= Container::MAXIMUM_CONTAINER_SIZE)
            {
                std::array<htd::vertex_t, Container::MAXIMUM_CONTAINER_SIZE> & nextElements = container->next_->elements_;

                std::copy_backward(nextElements.begin(), nextElements.begin() + container->next_->size_, nextElements.begin() + container->next_->size_ + container->size_);

                std::copy(elements.begin(), elements.begin() + container->size_, nextElements.begin());

                container->next_->size_ += container->size_;

                ret = container->next_;

                if (container->prev_ == nullptr)
                {
                    first_ = container->next_;
                    first_->prev_ = nullptr;
                }
                else
                {
                    Container * tmp = container;

                    container->prev_->next_ = tmp->next_;
                    container->next_->prev_ = tmp->prev_;
                }

                delete container;

                capacity_ -= Container::MAXIMUM_CONTAINER_SIZE;
            }
        }
    }

    return ret;
}

void htd::SortedVertexSet::merge(const std::vector<htd::vertex_t> & input)
{
    merge(htd::ConstCollection<htd::vertex_t>::getInstance(input));
}

void htd::SortedVertexSet::merge(const htd::ConstCollection<htd::vertex_t> & input)
{
    Container * container = first_;

    for (htd::vertex_t vertex : input)
    {
        while (container->next_ != nullptr && container->next_->elements_[0] <= vertex)
        {
            container = container->next_;
        }

        if (container->size_ == Container::MAXIMUM_CONTAINER_SIZE && container->elements_[Container::MAXIMUM_CONTAINER_SIZE - 1] < vertex)
        {
            if (container->next_ != nullptr && container->next_->size_ < Container::MAXIMUM_CONTAINER_SIZE)
            {
                container = container->next_;
            }
            else
            {
                Container * newContainer = new Container(container, container->next_);

                if (newContainer->next_ == nullptr)
                {
                    last_ = newContainer;
                }

                container = newContainer;

                capacity_ += Container::MAXIMUM_CONTAINER_SIZE;
            }
        }

        insert(vertex, container);
    }
}

void htd::SortedVertexSet::erase(const std::vector<htd::vertex_t> & input)
{
    erase(htd::ConstCollection<htd::vertex_t>::getInstance(input));
}

void htd::SortedVertexSet::erase(const htd::ConstCollection<htd::vertex_t> & input)
{
    Container * container = first_;

    for (htd::vertex_t vertex : input)
    {
        while (container->next_ != nullptr && container->next_->elements_[0] <= vertex)
        {
            container = container->next_;
        }

        if (container->size_ == 1 && container->elements_[0] == vertex)
        {
            Container * tmp = container;

            if (container->prev_ == nullptr && container->next_ != nullptr)
            {
                first_ = container->next_;
                first_->prev_ = nullptr;

                container = tmp->next_;

                delete tmp;

                capacity_ -= Container::MAXIMUM_CONTAINER_SIZE;
            }
            else if (container->next_ == nullptr && container->prev_ != nullptr)
            {
                last_ = container->prev_;
                last_->next_ = nullptr;

                container = tmp->next_;

                delete tmp;

                capacity_ -= Container::MAXIMUM_CONTAINER_SIZE;
            }
            else if (container->next_ != nullptr && container->prev_ != nullptr)
            {
                container->prev_->next_ = tmp->next_;
                container->next_->prev_ = tmp->prev_;

                container = tmp->next_;

                delete tmp;

                capacity_ -= Container::MAXIMUM_CONTAINER_SIZE;
            }
        }
        else if (container->size_ > 1)
        {
            container = erase(vertex, container);
        }
    }
}

void htd::SortedVertexSet::shrink(void)
{
    Container * container = first_;

    while (container != last_)
    {
        std::size_t size = container->size_;

        if (size < Container::MAXIMUM_CONTAINER_SIZE)
        {
            Container * nextContainer = container->next_;

            if (nextContainer != nullptr)
            {
                std::size_t nextSize = nextContainer->size_;

                std::array<htd::vertex_t, Container::MAXIMUM_CONTAINER_SIZE> & elements = container->elements_;
                std::array<htd::vertex_t, Container::MAXIMUM_CONTAINER_SIZE> & nextElements = container->next_->elements_;

                if (size + nextSize <= Container::MAXIMUM_CONTAINER_SIZE)
                {
                    std::copy(nextElements.begin(), nextElements.begin() + nextSize, elements.begin() + size);

                    container->size_ += nextSize;

                    if (container->next_->next_ == nullptr)
                    {
                        last_ = container;
                        last_->next_ = nullptr;

                        delete nextContainer;

                        capacity_ -= Container::MAXIMUM_CONTAINER_SIZE;
                    }
                    else
                    {
                        Container * tmp = nextContainer;

                        nextContainer->prev_->next_ = tmp->next_;
                        nextContainer->next_->prev_ = tmp->prev_;

                        delete nextContainer;

                        capacity_ -= Container::MAXIMUM_CONTAINER_SIZE;
                    }
                }
                else
                {
                    std::size_t transferSize = Container::MAXIMUM_CONTAINER_SIZE - size;

                    std::copy(nextElements.begin(), nextElements.begin() + transferSize, elements.begin() + size);

                    container->size_ = Container::MAXIMUM_CONTAINER_SIZE;

                    std::copy_backward(nextElements.begin() + transferSize, nextElements.begin() + nextSize, nextElements.begin() + nextSize - transferSize);

                    container->next_->size_ -= transferSize;

                    container = container->next_;
                }
            }
        }
        else
        {
            container = container->next_;
        }
    }
}

void htd::SortedVertexSet::clear(void)
{
    Container * container = last_;

    while (container->prev_ != nullptr)
    {
        container = last_->prev_;

        delete last_;

        last_ = container;
    }
}

htd::SortedVertexSet::Container::Container(Container * prev, Container * next) : size_(0), prev_(prev), next_(next), elements_()
{
    if (prev_ != nullptr)
    {
        prev_->next_ = this;
    }

    if (next_ != nullptr)
    {
        next_->prev_ = this;
    }
}

htd::SortedVertexSet::Container::~Container()
{

}

htd::SortedVertexSet::SortedVertexSetConstIterator htd::SortedVertexSet::begin(void) const
{
    return htd::SortedVertexSet::SortedVertexSetConstIterator(first_, 0);
}

htd::SortedVertexSet::SortedVertexSetConstIterator htd::SortedVertexSet::end(void) const
{
    return htd::SortedVertexSet::SortedVertexSetConstIterator(last_, last_->size_);
}

htd::SortedVertexSet::SortedVertexSetConstIterator::SortedVertexSetConstIterator(void) : container_(nullptr), position_(0)
{

}

htd::SortedVertexSet::SortedVertexSetConstIterator::SortedVertexSetConstIterator(Container * container) : container_(container), position_(0)
{

}

htd::SortedVertexSet::SortedVertexSetConstIterator::SortedVertexSetConstIterator(Container * container, htd::index_t position) : container_(container), position_(position)
{

}

htd::SortedVertexSet::SortedVertexSetConstIterator::SortedVertexSetConstIterator(const htd::SortedVertexSet::SortedVertexSetConstIterator & original) : container_(original.container_), position_(original.position_)
{

}

htd::SortedVertexSet::SortedVertexSetConstIterator::SortedVertexSetConstIterator(htd::SortedVertexSet::SortedVertexSetConstIterator && original) : container_(original.container_), position_(original.position_)
{

}

htd::SortedVertexSet::SortedVertexSetConstIterator::~SortedVertexSetConstIterator()
{

}

htd::SortedVertexSet::SortedVertexSetConstIterator & htd::SortedVertexSet::SortedVertexSetConstIterator::operator++(void)
{
    if (container_->next_ != nullptr && position_ + 1 >= container_->size_)
    {
        container_ = container_->next_;

        position_ = 0;
    }
    else
    {
        ++position_;
    }

    return *this;
}

htd::SortedVertexSet::SortedVertexSetConstIterator htd::SortedVertexSet::SortedVertexSetConstIterator::operator++(int)
{
    htd::SortedVertexSet::SortedVertexSetConstIterator ret(*this);

    operator++();

    return ret;
}

htd::SortedVertexSet::SortedVertexSetConstIterator & htd::SortedVertexSet::SortedVertexSetConstIterator::operator+=(std::size_t positions)
{
    positions += position_;

    position_ = 0;

    while (container_->next_ != nullptr && position_ + positions >= container_->size_)
    {
        positions -= container_->size_;

        container_ = container_->next_;

        position_ = 0;
    }

    position_ += positions;

    return *this;
}

htd::SortedVertexSet::SortedVertexSetConstIterator & htd::SortedVertexSet::SortedVertexSetConstIterator::operator--(void)
{
    if (position_ == 0)
    {
        container_ = container_->prev_;

        position_ = container_->size_ - 1;
    }
    else
    {
        --position_;
    }

    return *this;
}

htd::SortedVertexSet::SortedVertexSetConstIterator htd::SortedVertexSet::SortedVertexSetConstIterator::operator--(int)
{
    htd::SortedVertexSet::SortedVertexSetConstIterator ret(*this);

    operator--();

    return ret;
}

htd::SortedVertexSet::SortedVertexSetConstIterator & htd::SortedVertexSet::SortedVertexSetConstIterator::operator-=(std::size_t positions)
{
    positions += container_->size_ - position_ - 1;

    position_ = container_->size_ - 1;

    while (container_->prev_ != nullptr && position_ - positions >= container_->size_)
    {
        positions -= container_->size_;

        container_ = container_->prev_;

        position_ = container_->size_ - 1;
    }

    position_ -= positions;

    return *this;
}

std::size_t htd::SortedVertexSet::SortedVertexSetConstIterator::operator-(const htd::SortedVertexSet::SortedVertexSetConstIterator & rhs)
{
    std::size_t ret = 0;

    Container * tmp = rhs.container_;

    while (tmp != container_ && tmp != nullptr)
    {
        ret += tmp->size_;

        tmp = tmp->next_;
    }

    if (tmp != container_)
    {
        throw std::logic_error("std::size_t htd::SortedVertexSet::SortedVertexSetConstIterator::operator-(const htd::SortedVertexSet::SortedVertexSetConstIterator &)");
    }

    ret += position_ - rhs.position_;

    return ret;
}

const htd::vertex_t * htd::SortedVertexSet::SortedVertexSetConstIterator::operator->(void) const
{
    return &(container_->elements_[position_]);
}

const htd::vertex_t & htd::SortedVertexSet::SortedVertexSetConstIterator::operator*(void) const
{
    return container_->elements_[position_];
}

bool htd::SortedVertexSet::SortedVertexSetConstIterator::operator==(const htd::SortedVertexSet::SortedVertexSetConstIterator & rhs) const
{
    return container_ == rhs.container_ && position_ == rhs.position_;
}

bool htd::SortedVertexSet::SortedVertexSetConstIterator::operator!=(const htd::SortedVertexSet::SortedVertexSetConstIterator & rhs) const
{
    return container_ != rhs.container_ || position_ != rhs.position_;
}

htd::SortedVertexSet::SortedVertexSetConstIterator & htd::SortedVertexSet::SortedVertexSetConstIterator::operator=(const htd::SortedVertexSet::SortedVertexSetConstIterator & original)
{
    container_ = original.container_;

    position_ = original.position_;

    return *this;
}

htd::SortedVertexSet::SortedVertexSetConstIterator & htd::SortedVertexSet::SortedVertexSetConstIterator::operator=(htd::SortedVertexSet::SortedVertexSetConstIterator && original)
{
    container_ = original.container_;

    position_ = original.position_;

    return *this;
}

#endif /* HTD_HTD_SORTEDVERTEXSET_CPP */
