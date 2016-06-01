/*
 * File:   ValueOption.hpp
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

#ifndef HTD_CLI_VALUEOPTION_HPP
#define	HTD_CLI_VALUEOPTION_HPP

#include <htd_cli/Option.hpp>

namespace htd_cli
{
    class ValueOption : public htd_cli::Option
    {
        public:
            ValueOption(const std::string & name, const std::string & description, const std::string & valuePlaceholder);

            ValueOption(const std::string & name, const std::string & description, const std::string & valuePlaceholder, char shortName);

            ~ValueOption();

            virtual void registerValue(const std::string & value) = 0;

            const std::string & valuePlaceholder(void) const;

        private:
            std::string valuePlaceholder_;
    };
}

#endif /* HTD_CLI_VALUEOPTION_HPP */
