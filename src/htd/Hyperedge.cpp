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

class htd::Hyperedge::ElementInformation
{
    public:
        ElementInformation(htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_NOEXCEPT  : elements_(std::initializer_list<htd::vertex_t> { vertex1, vertex2 }), sortedElements_()
        {
            if (vertex1 < vertex2)
            {
                sortedElements_.reserve(2);

                sortedElements_.emplace_back(vertex1);
                sortedElements_.emplace_back(vertex2);
            }
            else if (vertex1 > vertex2)
            {
                sortedElements_.reserve(2);

                sortedElements_.emplace_back(vertex2);
                sortedElements_.emplace_back(vertex1);
            }
            else
            {
                sortedElements_.emplace_back(vertex1);
            }
        }

        ElementInformation(const std::vector<htd::vertex_t> & elements) : elements_(elements.begin(), elements.end()), sortedElements_()
        {
            elements_.shrink_to_fit();

            sortedElements_.reserve(elements_.size());

            switch (elements_.size())
            {
                case 0:
                {
                    break;
                }
                case 1:
                {
                    sortedElements_.emplace_back(elements_.at(0));

                    break;
                }
                case 2:
                {
                    htd::vertex_t vertex1 = elements_.at(0);
                    htd::vertex_t vertex2 = elements_.at(1);

                    if (vertex1 < vertex2)
                    {
                        sortedElements_.emplace_back(vertex1);
                        sortedElements_.emplace_back(vertex2);
                    }
                    else if (vertex1 > vertex2)
                    {
                        sortedElements_.emplace_back(vertex2);
                        sortedElements_.emplace_back(vertex1);
                    }
                    else
                    {
                        sortedElements_.emplace_back(vertex1);
                    }

                    break;
                }
                default:
                {
                    std::copy(elements_.begin(), elements_.end(), std::back_inserter(sortedElements_));

                    std::sort(sortedElements_.begin(), sortedElements_.end());

                    sortedElements_.erase(std::unique(sortedElements_.begin(), sortedElements_.end()), sortedElements_.end());

                    break;
                }
            }
        }

        ElementInformation(std::vector<htd::vertex_t> && elements) HTD_NOEXCEPT : elements_(), sortedElements_()
        {
            elements_.swap(elements);

            elements_.shrink_to_fit();

            sortedElements_.reserve(elements_.size());

            switch (elements_.size())
            {
                case 0:
                {
                    break;
                }
                case 1:
                {
                    sortedElements_.emplace_back(elements_.at(0));

                    break;
                }
                case 2:
                {
                    htd::vertex_t vertex1 = elements_.at(0);
                    htd::vertex_t vertex2 = elements_.at(1);

                    if (vertex1 < vertex2)
                    {
                        sortedElements_.emplace_back(vertex1);
                        sortedElements_.emplace_back(vertex2);
                    }
                    else if (vertex1 > vertex2)
                    {
                        sortedElements_.emplace_back(vertex2);
                        sortedElements_.emplace_back(vertex1);
                    }
                    else
                    {
                        sortedElements_.emplace_back(vertex1);
                    }

                    break;
                }
                default:
                {
                    std::copy(elements_.begin(), elements_.end(), std::back_inserter(sortedElements_));

                    std::sort(sortedElements_.begin(), sortedElements_.end());

                    sortedElements_.erase(std::unique(sortedElements_.begin(), sortedElements_.end()), sortedElements_.end());

                    break;
                }
            }
        }

        ElementInformation(const htd::ConstCollection<htd::vertex_t> & elements) : elements_(elements.begin(), elements.end()), sortedElements_()
        {
            elements_.shrink_to_fit();

            sortedElements_.reserve(elements_.size());

            switch (elements.size())
            {
                case 0:
                {
                    break;
                }
                case 1:
                {
                    sortedElements_.emplace_back(elements_.at(0));

                    break;
                }
                case 2:
                {
                    htd::vertex_t vertex1 = elements_.at(0);
                    htd::vertex_t vertex2 = elements_.at(1);

                    if (vertex1 < vertex2)
                    {
                        sortedElements_.emplace_back(vertex1);
                        sortedElements_.emplace_back(vertex2);
                    }
                    else if (vertex1 > vertex2)
                    {
                        sortedElements_.emplace_back(vertex2);
                        sortedElements_.emplace_back(vertex1);
                    }
                    else
                    {
                        sortedElements_.emplace_back(vertex1);
                    }

                    break;
                }
                default:
                {
                    std::copy(elements_.begin(), elements_.end(), std::back_inserter(sortedElements_));

                    std::sort(sortedElements_.begin(), sortedElements_.end());

                    sortedElements_.erase(std::unique(sortedElements_.begin(), sortedElements_.end()), sortedElements_.end());

                    break;
                }
            }
        }

        void setElements(htd::vertex_t vertex1, htd::vertex_t vertex2)
        {
            elements_.clear();

            elements_.emplace_back(vertex1);
            elements_.emplace_back(vertex2);

            sortedElements_.clear();

            if (vertex1 < vertex2)
            {
                sortedElements_.reserve(2);

                sortedElements_.emplace_back(vertex1);
                sortedElements_.emplace_back(vertex2);
            }
            else if (vertex1 > vertex2)
            {
                sortedElements_.reserve(2);

                sortedElements_.emplace_back(vertex2);
                sortedElements_.emplace_back(vertex1);
            }
            else
            {
                sortedElements_.emplace_back(vertex1);
            }
        }

        void setElements(const std::vector<htd::vertex_t> & elements)
        {
            elements_.reserve(elements.size());

            elements_ = elements;

            sortedElements_.reserve(elements_.size());

            switch (elements_.size())
            {
                case 0:
                {
                    break;
                }
                case 1:
                {
                    sortedElements_.emplace_back(elements_.at(0));

                    break;
                }
                case 2:
                {
                    htd::vertex_t vertex1 = elements_.at(0);
                    htd::vertex_t vertex2 = elements_.at(1);

                    if (vertex1 < vertex2)
                    {
                        sortedElements_.emplace_back(vertex1);
                        sortedElements_.emplace_back(vertex2);
                    }
                    else if (vertex1 > vertex2)
                    {
                        sortedElements_.emplace_back(vertex2);
                        sortedElements_.emplace_back(vertex1);
                    }
                    else
                    {
                        sortedElements_.emplace_back(vertex1);
                    }

                    break;
                }
                default:
                {
                    std::copy(elements_.begin(), elements_.end(), std::back_inserter(sortedElements_));

                    std::sort(sortedElements_.begin(), sortedElements_.end());

                    sortedElements_.erase(std::unique(sortedElements_.begin(), sortedElements_.end()), sortedElements_.end());

                    break;
                }
            }
        }

        void setElements(std::vector<htd::vertex_t> && elements)
        {
            elements_.swap(elements);

            elements_.shrink_to_fit();

            sortedElements_.reserve(elements_.size());

            switch (elements_.size())
            {
                case 0:
                {
                    break;
                }
                case 1:
                {
                    sortedElements_.emplace_back(elements_.at(0));

                    break;
                }
                case 2:
                {
                    htd::vertex_t vertex1 = elements_.at(0);
                    htd::vertex_t vertex2 = elements_.at(1);

                    if (vertex1 < vertex2)
                    {
                        sortedElements_.emplace_back(vertex1);
                        sortedElements_.emplace_back(vertex2);
                    }
                    else if (vertex1 > vertex2)
                    {
                        sortedElements_.emplace_back(vertex2);
                        sortedElements_.emplace_back(vertex1);
                    }
                    else
                    {
                        sortedElements_.emplace_back(vertex1);
                    }

                    break;
                }
                default:
                {
                    std::copy(elements_.begin(), elements_.end(), std::back_inserter(sortedElements_));

                    std::sort(sortedElements_.begin(), sortedElements_.end());

                    sortedElements_.erase(std::unique(sortedElements_.begin(), sortedElements_.end()), sortedElements_.end());

                    break;
                }
            }
        }

        void setElements(const htd::ConstCollection<htd::vertex_t> & elements)
        {
            setElements(std::vector<htd::vertex_t>(elements.begin(), elements.end()));
        }

        const std::vector<htd::vertex_t> & elements(void) const
        {
            return elements_;
        }

        const std::vector<htd::vertex_t> & sortedElements(void) const
        {
            return sortedElements_;
        }

        bool empty(void) const
        {
            return elements_.empty();
        }

        std::size_t size(void) const
        {
            return elements_.size();
        }

        bool contains(htd::vertex_t vertex) const
        {
            return std::binary_search(sortedElements_.begin(), sortedElements_.end(), vertex);
        }

        void erase(htd::vertex_t vertex)
        {
            elements_.erase(std::remove(elements_.begin(), elements_.end(), vertex), elements_.end());

            auto position = std::lower_bound(sortedElements_.begin(), sortedElements_.end(), vertex);

            if (position != sortedElements_.end() && *position == vertex)
            {
                sortedElements_.erase(position);
            }
        }

        std::vector<htd::vertex_t>::const_iterator begin(void) const
        {
            return elements_.begin();
        }

        std::vector<htd::vertex_t>::const_iterator end(void) const
        {
            return elements_.end();
        }

        const htd::vertex_t & at(htd::index_t index) const
        {
            return elements_.at(index);
        }

        const htd::vertex_t & operator[](htd::index_t index) const
        {
            return elements_.at(index);
        }

    private:
        std::vector<htd::vertex_t> elements_;

        std::vector<htd::vertex_t> sortedElements_;
};

htd::Hyperedge::Hyperedge(htd::id_t id, htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_NOEXCEPT : id_(id), content_(new ElementInformation(vertex1, vertex2))
{

}

htd::Hyperedge::Hyperedge(htd::id_t id, const std::vector<htd::vertex_t> & elements) : id_(id), content_(new ElementInformation(elements))
{

}

htd::Hyperedge::Hyperedge(htd::id_t id, std::vector<htd::vertex_t> && elements) HTD_NOEXCEPT : id_(id), content_(new ElementInformation(std::move(elements)))
{

}

htd::Hyperedge::Hyperedge(htd::id_t id, const htd::ConstCollection<htd::vertex_t> & elements) : id_(id), content_(new ElementInformation(elements))
{

}

htd::Hyperedge::Hyperedge(const htd::Hyperedge & original) : id_(original.id_), content_(new ElementInformation(*(original.content_)))
{

}

htd::Hyperedge::Hyperedge(htd::Hyperedge && original) HTD_NOEXCEPT : id_(original.id_), content_(std::move(original.content_))
{

}

htd::Hyperedge::~Hyperedge()
{

}

htd::id_t htd::Hyperedge::id(void) const
{
    return id_;
}

void htd::Hyperedge::setId(htd::id_t newId)
{
    id_ = newId;
}

void htd::Hyperedge::setElements(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    content_->setElements(vertex1, vertex2);
}

void htd::Hyperedge::setElements(const std::vector<htd::vertex_t> & elements)
{
    content_->setElements(elements);
}

void htd::Hyperedge::setElements(std::vector<htd::vertex_t> && elements)
{
    content_->setElements(std::move(elements));
}

void htd::Hyperedge::setElements(const htd::ConstCollection<htd::vertex_t> & elements)
{
    content_->setElements(std::vector<htd::vertex_t>(elements.begin(), elements.end()));
}

const std::vector<htd::vertex_t> & htd::Hyperedge::elements(void) const
{
    return content_->elements();
}

const std::vector<htd::vertex_t> & htd::Hyperedge::sortedElements(void) const
{
    return content_->sortedElements();
}

bool htd::Hyperedge::empty(void) const
{
    return content_->empty();
}

std::size_t htd::Hyperedge::size(void) const
{
    return content_->size();
}

bool htd::Hyperedge::contains(htd::vertex_t vertex) const
{
    return content_->contains(vertex);
}

void htd::Hyperedge::erase(htd::vertex_t vertex)
{
    content_->erase(vertex);
}

std::vector<htd::vertex_t>::const_iterator htd::Hyperedge::begin(void) const
{
    return content_->begin();
}

std::vector<htd::vertex_t>::const_iterator htd::Hyperedge::end(void) const
{
    return content_->end();
}

const htd::vertex_t & htd::Hyperedge::at(htd::index_t index) const
{
    return content_->at(index);
}

const htd::vertex_t & htd::Hyperedge::operator[](htd::index_t index) const
{
    return content_->at(index);
}

htd::Hyperedge & htd::Hyperedge::operator=(const htd::Hyperedge & original)
{
    id_ = original.id_;

    content_.reset(new ElementInformation(*(original.content_)));

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
