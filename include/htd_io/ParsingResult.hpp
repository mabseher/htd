/*
 * File:   ParsingResult.hpp
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

#ifndef HTD_IO_PARSINGRESULT_HPP
#define HTD_IO_PARSINGRESULT_HPP

#include <htd/Id.hpp>

namespace htd_io
{
    /**
     *  Datatype for parsing results.
     */
    typedef htd::id_t parsing_result_t;

    /**
     *  Enumeration of possible parsing results.
     */
    struct ParsingResult
    {
        public:
            /**
             *  The parsing result returned in the case that an error occurred during the parsing process.
             */
            static const htd_io::parsing_result_t ERROR = 0;

            /**
             *  The parsing result returned if (and only if) the parsing process was successful.
             */
            static const htd_io::parsing_result_t OK = 1;

        private:
            ParsingResult(void);
    };
}

#endif /* HTD_IO_PARSINGRESULT_HPP */
