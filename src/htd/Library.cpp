/*
 * File:   Library.cpp
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

#ifndef HTD_HTD_LIBRARY_CPP
#define HTD_HTD_LIBRARY_CPP

#include <htd/Library.hpp>
#include <htd/Helpers.hpp>

#include <csignal>

htd::Library::Library(void) : nextInstanceId_(htd::Id::FIRST), managementInstances_()
{

}

htd::Library::~Library()
{
    for (auto & instance : managementInstances_)
    {
        if (!instance.second->isTerminated())
        {
            instance.second->terminate();
        }
    }
}

htd::Library & htd::Library::instance(void) HTD_NOEXCEPT
{
    static htd::Library instance_;

    return instance_;
}

void htd::Library::terminate(void) HTD_NOEXCEPT
{
    for (auto & instance : managementInstances_)
    {
        if (!instance.second->isTerminated())
        {
            instance.second->terminate();
        }
    }
}

void htd::Library::reset(void) HTD_NOEXCEPT
{
    for (auto & instance : managementInstances_)
    {
        instance.second.reset();
    }
}

std::shared_ptr<htd::LibraryInstance> htd::Library::createManagementInstance(void)
{
    std::shared_ptr<htd::LibraryInstance> ret = std::make_shared<htd::LibraryInstance>(nextInstanceId_);

    managementInstances_[nextInstanceId_] = ret;

    ++nextInstanceId_;

    return ret;
}

void htd::Library::removeManagementInstance(htd::id_t id)
{
    auto it = managementInstances_.find(id);

    HTD_ASSERT(it != managementInstances_.end())

    if (!it->second->isTerminated())
    {
        it->second->terminate();
    }
}

#endif /* HTD_HTD_LIBRARY_CPP */
