/* 
 * File:   IMutableLabeledPath.hpp
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

#ifndef HTD_HTD_IMUTABLELABELEDPATH_HPP
#define	HTD_HTD_IMUTABLELABELEDPATH_HPP

#include <htd/Globals.hpp>
#include <htd/IMutablePath.hpp>
#include <htd/ILabeledPath.hpp>

namespace htd
{
    class IMutableLabeledPath : public virtual htd::ILabeledPath, public virtual htd::IMutablePath
    {
        public:
            virtual ~IMutableLabeledPath() = 0;

            virtual void setVertexLabel(const std::string & labelName, htd::vertex_t vertex, htd::ILabel * label) = 0;

            virtual void setEdgeLabel(const std::string & labelName, htd::id_t edgeId, htd::ILabel * label) = 0;

            virtual void removeVertexLabel(const std::string & labelName, htd::vertex_t vertex) = 0;

            virtual void removeEdgeLabel(const std::string & labelName, htd::id_t edgeId) = 0;

            virtual void swapVertexLabels(htd::vertex_t vertex1, htd::vertex_t vertex2) = 0;

            virtual void swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2) = 0;

            virtual void swapVertexLabel(const std::string & labelName, htd::vertex_t vertex1, htd::vertex_t vertex2) = 0;

            virtual void swapEdgeLabel(const std::string & labelName, htd::id_t edgeId1, htd::id_t edgeId2) = 0;

            virtual htd::ILabel * transferVertexLabel(const std::string & labelName, htd::vertex_t vertex) = 0;

            virtual htd::ILabel * transferEdgeLabel(const std::string & labelName, htd::id_t edgeId) = 0;

            /**
             *  Create a deep copy the current mutable labeled path.
             *
             *  @return A new IMutableLabeledPath object identical to the current mutable labeled path.
             */
            virtual IMutableLabeledPath * clone(void) const = 0;

            /**
             *  Copy assignment operator for a mutable labeled path.
             *
             *  @param[in] original  The original labeled path.
             */
            virtual IMutableLabeledPath & operator=(const htd::ILabeledPath & original) = 0;
    };

    inline htd::IMutableLabeledPath::~IMutableLabeledPath() { }
}

#endif /* HTD_HTD_IMUTABLELABELEDPATH_HPP */
