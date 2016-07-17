/*
 * File:   LibraryInstance.cpp
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

#ifndef HTD_HTD_LIBRARYINSTANCE_CPP
#define HTD_HTD_LIBRARYINSTANCE_CPP

#include <htd/LibraryInstance.hpp>

#include <csignal>

htd::LibraryInstance::LibraryInstance(htd::id_t id) : id_(id), nextHandlerId_(htd::Id::FIRST), terminated_(false), signalHandlers_()
{

}

htd::LibraryInstance::~LibraryInstance()
{

}

htd::id_t htd::LibraryInstance::id(void) const
{
    return id_;
}

bool htd::LibraryInstance::isTerminated(void) const
{
    return terminated_;
}

void htd::LibraryInstance::terminate(void)
{
    terminated_ = true;

    for (const auto & signalHandler : signalHandlers_)
    {
        signalHandler.second(SIGTERM);
    }
}

void htd::LibraryInstance::reset(void)
{
    terminated_ = false;
}

htd::id_t htd::LibraryInstance::registerSignalHandler(const std::function<void(int)> & handler)
{
    signalHandlers_[nextHandlerId_] = handler;

    return nextHandlerId_++;
}

void htd::LibraryInstance::unregisterSignalHandler(htd::id_t handlerId)
{
    signalHandlers_.erase(handlerId);
}

#endif /* HTD_HTD_LIBRARYINSTANCE_CPP */
