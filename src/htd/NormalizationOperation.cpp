/*
 * File:   NormalizationOperation.cpp
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

#ifndef HTD_HTD_NORMALIZATIONOPERATION_CPP
#define	HTD_HTD_NORMALIZATIONOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/NormalizationOperation.hpp>
#include <htd/SemiNormalizationOperation.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/ExchangeNodeReplacementOperation.hpp>
#include <htd/LimitMaximumForgottenVerticesCountOperation.hpp>
#include <htd/LimitMaximumIntroducedVerticesCountOperation.hpp>

htd::NormalizationOperation::NormalizationOperation(void)
{

}

htd::NormalizationOperation::~NormalizationOperation()
{

}

void htd::NormalizationOperation::apply(htd::IMutableTreeDecomposition & decomposition) const
{
    htd::SemiNormalizationOperation::apply(decomposition);

    htd::ExchangeNodeReplacementOperation exchangeNodeReplacementOperation;

    exchangeNodeReplacementOperation.apply(decomposition);

    htd::LimitMaximumForgottenVerticesCountOperation limitMaximumForgottenVerticesCountOperation(1);

    limitMaximumForgottenVerticesCountOperation.apply(decomposition);

    htd::LimitMaximumIntroducedVerticesCountOperation limitMaximumIntroducedVerticesCountOperation(1);

    limitMaximumIntroducedVerticesCountOperation.apply(decomposition);
}

void htd::NormalizationOperation::apply(htd::IMutableTreeDecomposition & decomposition, bool emptyRoot, bool emptyLeaves) const
{
    htd::SemiNormalizationOperation::apply(decomposition, emptyRoot, emptyLeaves);

    htd::ExchangeNodeReplacementOperation exchangeNodeReplacementOperation;

    exchangeNodeReplacementOperation.apply(decomposition);

    htd::LimitMaximumForgottenVerticesCountOperation limitMaximumForgottenVerticesCountOperation(1);

    limitMaximumForgottenVerticesCountOperation.apply(decomposition);

    htd::LimitMaximumIntroducedVerticesCountOperation limitMaximumIntroducedVerticesCountOperation(1);

    limitMaximumIntroducedVerticesCountOperation.apply(decomposition);
}

#endif /* HTD_HTD_NORMALIZATIONOPERATION_CPP */
