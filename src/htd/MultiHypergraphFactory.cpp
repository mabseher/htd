/*
 * File:   MultiHypergraphFactory.cpp
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

#ifndef HTD_HTD_MULTIHYPERGRAPHFACTORY_CPP
#define HTD_HTD_MULTIHYPERGRAPHFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/MultiHypergraphFactory.hpp>
#include <htd/MultiHypergraph.hpp>

#include <stdexcept>

/**
 *  Private implementation details of class htd::MultiHypergraph.
 */
struct htd::MultiHypergraphFactory::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager   The management instance to which the current object instance belongs.
     */
    Implementation(const htd::LibraryInstance * const manager)
        : managementInstance_(manager), constructionTemplate_(new htd::MultiHypergraph(manager))
    {

    }

    virtual ~Implementation()
    {
        delete constructionTemplate_;
    }

    /**
     *  Copy constructor of the implementation details structure.
     *
     *  @param[in] original  The original implementation details structure.
     */
    Implementation(const Implementation & original)
        : managementInstance_(original.managementInstance_)
    {
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        constructionTemplate_ = original.constructionTemplate_->clone();
#else
        constructionTemplate_ = original.constructionTemplate_->cloneMutableMultiHypergraph();
#endif
    }

    /**
     *  The management instance to which the current object instance belongs.
     */
    const htd::LibraryInstance * managementInstance_;

    /**
     *  A pointer to a clean instance of the default implementation.
     */
    htd::IMutableMultiHypergraph * constructionTemplate_;
};

htd::MultiHypergraphFactory::MultiHypergraphFactory(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{

}

htd::MultiHypergraphFactory::MultiHypergraphFactory(const htd::MultiHypergraphFactory & original) : implementation_(new Implementation(*(original.implementation_)))
{

}

htd::MultiHypergraphFactory & htd::MultiHypergraphFactory::operator=(const htd::MultiHypergraphFactory & original)
{
    if (this != &original)
    {
        delete implementation_->constructionTemplate_;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        implementation_->constructionTemplate_ = original.implementation_->constructionTemplate_->clone();
#else
        implementation_->constructionTemplate_ = original.implementation_->constructionTemplate_->cloneMutableMultiHypergraph();
#endif
    }

    return *this;
}

htd::MultiHypergraphFactory::~MultiHypergraphFactory()
{

}

htd::IMutableMultiHypergraph * htd::MultiHypergraphFactory::getMultiHypergraph(void) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    return implementation_->constructionTemplate_->clone();
#else
    return implementation_->constructionTemplate_->cloneMutableMultiHypergraph();
#endif
}

htd::IMutableMultiHypergraph * htd::MultiHypergraphFactory::getMultiHypergraph(std::size_t initialSize) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableMultiHypergraph * ret = implementation_->constructionTemplate_->clone();
#else
    htd::IMutableMultiHypergraph * ret = implementation_->constructionTemplate_->cloneMutableMultiHypergraph();
#endif

    ret->addVertices(initialSize);

    return ret;
}

htd::IMutableMultiHypergraph * htd::MultiHypergraphFactory::getMultiHypergraph(const htd::IMultiHypergraph & original) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableMultiHypergraph * ret = implementation_->constructionTemplate_->clone();

    *ret = original;
#else
    htd::IMutableMultiHypergraph * ret = implementation_->constructionTemplate_->cloneMutableMultiHypergraph();

    ret->assign(original);
#endif

    return ret;
}

void htd::MultiHypergraphFactory::setConstructionTemplate(htd::IMutableMultiHypergraph * original)
{
    HTD_ASSERT(original != nullptr)
    HTD_ASSERT(original->vertexCount() == 0)

    if (implementation_->constructionTemplate_ != nullptr)
    {
        delete implementation_->constructionTemplate_;
    }

    implementation_->constructionTemplate_ = original;

    implementation_->constructionTemplate_->setManagementInstance(implementation_->managementInstance_);
}

htd::IMutableMultiHypergraph & htd::MultiHypergraphFactory::accessMutableMultiHypergraph(htd::IMultiHypergraph & original) const
{
    return *(dynamic_cast<htd::IMutableMultiHypergraph *>(&original));
}

const htd::IMutableMultiHypergraph & htd::MultiHypergraphFactory::accessMutableMultiHypergraph(const htd::IMultiHypergraph & original) const
{
    return *(dynamic_cast<const htd::IMutableMultiHypergraph *>(&original));
}

#endif /* HTD_HTD_MULTIHYPERGRAPHFACTORY_CPP */
