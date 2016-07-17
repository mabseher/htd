/*
 * File:   LibraryObject.cpp
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

#ifndef HTD_HTD_LIBRARYOBJECT_CPP
#define HTD_HTD_LIBRARYOBJECT_CPP

#include <htd/LibraryObject.hpp>

htd::LibraryObject::LibraryObject(void) : instance_()
{

}

htd::LibraryObject::LibraryObject(const std::shared_ptr<htd::LibraryInstance> & instance) : instance_(instance)
{

}

htd::LibraryObject::~LibraryObject()
{

}

bool htd::LibraryObject::isManaged(void) const HTD_NOEXCEPT
{
    return instance_ != nullptr;
}

bool htd::LibraryObject::isTerminated(void) const HTD_NOEXCEPT
{
    return instance_ != nullptr && instance_->isTerminated();
}

const std::shared_ptr<htd::LibraryInstance> & htd::LibraryObject::managementInstance(void) const HTD_NOEXCEPT
{
    return instance_;
}

void htd::LibraryObject::setManagementInstance(const std::shared_ptr<htd::LibraryInstance> & instance)
{
    instance_ = instance;
}

#endif /* HTD_HTD_LIBRARYOBJECT_CPP */
