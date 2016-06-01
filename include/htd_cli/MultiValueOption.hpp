/*
 * File:   MultiValueOption.hpp
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

#ifndef HTD_CLI_MULTIVALUEOPTION_HPP
#define	HTD_CLI_MULTIVALUEOPTION_HPP

#include <htd_cli/ValueOption.hpp>

#include <htd/Globals.hpp>

#include <vector>

namespace htd_cli
{
    class MultiValueOption : public htd_cli::ValueOption
    {
        public:
            MultiValueOption(const std::string & name, const std::string & description, const std::string & valuePlaceholder);

            MultiValueOption(const std::string & name, const std::string & description, const std::string & valuePlaceholder, char shortName);

            ~MultiValueOption();

            const std::vector<std::string> & values(void) const;

            void registerValue(const std::string & value) HTD_OVERRIDE;

            void printHelp(std::ostream & stream, std::size_t maxNameLength) const HTD_OVERRIDE;

        private:
            std::vector<std::string> values_;
    };
}

#endif /* HTD_CLI_MULTIVALUEOPTION_HPP */
