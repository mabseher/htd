/*
 * File:   AddEmptyRootOperation.cpp
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

#ifndef HTD_HTD_ADDEMPTYROOTOPERATION_CPP
#define	HTD_HTD_ADDEMPTYROOTOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/AddEmptyRootOperation.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/ITreeDecompositionManipulationOperation.hpp>

htd::AddEmptyRootOperation::AddEmptyRootOperation(void)
{

}

htd::AddEmptyRootOperation::~AddEmptyRootOperation()
{

}

void htd::AddEmptyRootOperation::apply(htd::IMutableTreeDecomposition & decomposition) const
{
    htd::vertex_t root = decomposition.root();

    if (decomposition.bagContent(root).size() > 0)
    {
        decomposition.addParent(root);
    }
}

#endif /* HTD_HTD_ADDEMPTYROOTOPERATION_CPP */
