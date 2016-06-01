/*
 * File:   Choice.hpp
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

#ifndef HTD_CLI_CHOICE_HPP
#define	HTD_CLI_CHOICE_HPP

#include <htd_cli/SingleValueOption.hpp>

#include <vector>

namespace htd_cli
{
    class Choice : public htd_cli::SingleValueOption
    {
        public:
            Choice(const std::string & name, const std::string & description, const std::string & valuePlaceholder);

            Choice(const std::string & name, const std::string & description, const std::string & valuePlaceholder, char shortName);

            ~Choice();

            void addPossibility(const std::string & value, const std::string & description);

            bool hasDefaultValue(void);

            void setDefaultValue(const std::string & value);

            const std::string & value(void) const HTD_OVERRIDE;

            void registerValue(const std::string & value) HTD_OVERRIDE;

            void printHelp(std::ostream & stream, std::size_t maxNameLength) const HTD_OVERRIDE;

        private:
            struct Possibility
            {
                std::string value;

                std::string description;

                Possibility(const std::string & value, const std::string & description) : value(value), description(description)
                {

                }
            };

            std::string defaultValue_;

            std::size_t maxPossibilityNameLength_;

            std::vector<Possibility> possibilities_;
    };
}

#endif /* HTD_CLI_CHOICE_HPP */
