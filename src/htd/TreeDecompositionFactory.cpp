/*
 * File:   TreeDecompositionFactory.cpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 *
 * Copyright 2015, Michael Abseher
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

#ifndef HTD_TREEDECOMPOSITIONFACTORY_CPP
#define HTD_TREEDECOMPOSITIONFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/TreeDecompositionFactory.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/TreeDecomposition.hpp>

#include <stdexcept>

htd::TreeDecompositionFactory::TreeDecompositionFactory(void)
{
    constructionTemplate_ = new htd::TreeDecomposition();
}

htd::TreeDecompositionFactory::~TreeDecompositionFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::TreeDecompositionFactory & htd::TreeDecompositionFactory::instance(void)
{
    static htd::TreeDecompositionFactory instance_;

    return instance_;
}

htd::IMutableTreeDecomposition * htd::TreeDecompositionFactory::getTreeDecomposition(void)
{
    return constructionTemplate_->clone();
}

//TODO Use construction template!
htd::IMutableTreeDecomposition * htd::TreeDecompositionFactory::getTreeDecomposition(const htd::ITreeDecomposition & original)
{
    htd::IMutableTreeDecomposition * ret = new htd::TreeDecomposition(original); //TODO constructionTemplate_->clone();

    //TODO Copy decomposition content!

    return ret;
}

void htd::TreeDecompositionFactory::setConstructionTemplate(htd::IMutableTreeDecomposition * original)
{
    if (original == nullptr)
    {
        throw std::logic_error("void htd::TreeDecompositionFactory::setConstructionTemplate(htd::IMutableTreeDecomposition *)");
    }

    if (original->vertexCount() > 0)
    {
        throw std::logic_error("void htd::TreeDecompositionFactory::setConstructionTemplate(htd::IMutableTreeDecomposition *)");
    }

    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }

    constructionTemplate_ = original;
}

#endif /* HTD_TREEDECOMPOSITIONFACTORY_CPP */
