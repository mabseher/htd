/* 
 * File:   GraphPreprocessor.hpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015-2017, Michael Abseher
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

#ifndef HTD_HTD_GRAPHPREPROCESSOR_HPP
#define HTD_HTD_GRAPHPREPROCESSOR_HPP

#include <htd/Globals.hpp>
#include <htd/LibraryInstance.hpp>
#include <htd/IGraphPreprocessor.hpp>

namespace htd
{
    /**
     *  Preprocessor for graphs.
     */
    class GraphPreprocessor : public htd::IGraphPreprocessor
    {
        public:
            /**
             *  Constructor for a graph preprocessor.
             *
             *  @param[in] manager   The management instance to which the new preprocessor belongs.
             */
            HTD_API GraphPreprocessor(const htd::LibraryInstance * const manager);
            
            HTD_API virtual ~GraphPreprocessor();

            HTD_API htd::IPreprocessedGraph * prepare(const htd::IMultiHypergraph & graph) const HTD_NOEXCEPT HTD_OVERRIDE;

            /**
             *  Set the preprocessing strategy which shall be used.
             *
             *  @param[in] level    The level of preprocessing which shall be applied. (0: none, 1: simple, 2: advanced, 3 or more: full)
             */
            HTD_API void setPreprocessingStrategy(std::size_t level);

            HTD_API const htd::LibraryInstance * managementInstance(void) const HTD_NOEXCEPT  HTD_OVERRIDE;

            HTD_API void setManagementInstance(const htd::LibraryInstance * const manager)  HTD_OVERRIDE;

            /**
             *  Create a deep copy of the current graph preprocessor.
             *
             *  @return A new GraphPreprocessor object identical to the current graph preprocessor.
             */
            HTD_API GraphPreprocessor * clone(void) const HTD_OVERRIDE;

        protected:
            /**
             *  Copy assignment operator for a graph preprocessor.
             *
             *  @note This operator is protected to prevent assignments to an already initialized preprocessor.
             */
            GraphPreprocessor & operator=(const GraphPreprocessor &) { return *this; }

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_HTD_GRAPHPREPROCESSOR_HPP */
