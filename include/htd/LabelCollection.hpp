/*
 * File:   LabelCollection.hpp
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

#ifndef HTD_HTD_LABELCOLLECTION_HPP
#define	HTD_HTD_LABELCOLLECTION_HPP

#include <htd/Globals.hpp>
#include <htd/ILabelCollection.hpp>
#include <htd/ILabel.hpp>

#include <unordered_map>
#include <string>
#include <vector>

namespace htd
{
    class LabelCollection : public virtual htd::ILabelCollection
    {
        public:
            LabelCollection(void);
	    
            ~LabelCollection();

            std::size_t labelCount(void) const HTD_OVERRIDE;

            const htd::Collection<std::string> labelNames(void) const HTD_OVERRIDE;

            const std::string & labelName(htd::index_t index) const HTD_OVERRIDE;

            htd::ILabel & label(const std::string & labelName) HTD_OVERRIDE;

            const htd::ILabel & label(const std::string & labelName) const HTD_OVERRIDE;

            void setLabel(const std::string & labelName, htd::ILabel * label) HTD_OVERRIDE;

            void removeLabel(const std::string & labelName) HTD_OVERRIDE;

            LabelCollection * clone(void) const HTD_OVERRIDE;

        private:
            std::vector<std::string> labelNames_;

            std::unordered_map<std::string, htd::ILabel *> content_;
    };
}

#endif /* HTD_HTD_LABELCOLLECTION_HPP */
