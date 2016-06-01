/*
 * File:   Option.hpp
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

#ifndef HTD_CLI_OPTION_HPP
#define	HTD_CLI_OPTION_HPP

#include <string>

namespace htd_cli
{
    class Option
    {
        public:
            Option(const std::string & name, const std::string & description);

            Option(const std::string & name, const std::string & description, char shortName);

            virtual ~Option();

            const std::string & name(void) const;

            const std::string & description(void) const;

            bool hasShortName(void) const;

            char shortName(void) const;

            bool used(void) const;

            void setUsed(void);

            virtual void printHelp(std::ostream & stream, std::size_t maxNameLength = 0) const;

            static std::string getCommandLineRepresentation(char name);

            static std::string getCommandLineRepresentation(const std::string & name);

        protected:
            bool used_;

            char shortName_;

            std::string name_;

            std::string description_;
    };
}

#endif /* HTD_CLI_OPTION_HPP */
