/*
 * File:   FitnessEvaluation.cpp
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

#ifndef HTD_HTD_FITNESSEVALUATION_CPP
#define HTD_HTD_FITNESSEVALUATION_CPP

#include <htd/Helpers.hpp>
#include <htd/FitnessEvaluation.hpp>

#include <cstdarg>

htd::FitnessEvaluation::FitnessEvaluation(int levels, ...) : values_(levels)
{
    HTD_ASSERT(levels > 0)

    va_list arguments;

    va_start(arguments, levels);

    for (int index = 0; index < levels; index++)
    {
        values_[index] = va_arg(arguments, double);
    }

    va_end(arguments);
}

htd::FitnessEvaluation::FitnessEvaluation(const std::vector<double> & values) : values_(values)
{

}

htd::FitnessEvaluation::FitnessEvaluation(std::vector<double> && values) : values_(std::move(values))
{

}

htd::FitnessEvaluation::~FitnessEvaluation()
{

}

std::size_t htd::FitnessEvaluation::levelCount(void) const HTD_NOEXCEPT
{
    return values_.size();
}

const std::vector<double> & htd::FitnessEvaluation::values(void) const HTD_NOEXCEPT
{
    return values_;
}

double htd::FitnessEvaluation::at(htd::index_t level) const
{
    return values_[level];
}

double htd::FitnessEvaluation::operator[](htd::index_t level) const
{
    return values_[level];
}

bool htd::FitnessEvaluation::operator<(const htd::FitnessEvaluation & rhs) const HTD_NOEXCEPT
{
    HTD_ASSERT(rhs.levelCount() == levelCount())

    return values_ < rhs.values();
}

bool htd::FitnessEvaluation::operator>(const htd::FitnessEvaluation & rhs) const HTD_NOEXCEPT
{
    HTD_ASSERT(rhs.levelCount() == levelCount())

    return values_ > rhs.values();
}

bool htd::FitnessEvaluation::operator==(const htd::FitnessEvaluation & rhs) const HTD_NOEXCEPT
{
    return values_ == rhs.values();
}

bool htd::FitnessEvaluation::operator!=(const htd::FitnessEvaluation & rhs) const HTD_NOEXCEPT
{
    return values_ != rhs.values();
}

htd::FitnessEvaluation * htd::FitnessEvaluation::clone(void) const
{
    return new FitnessEvaluation(values_);
}

std::ostream & std::operator<<(std::ostream & stream, const htd::FitnessEvaluation & input)
{
    htd::index_t index = 0;

    while (index < input.levelCount() - 1)
    {
        stream << input[index] << " @ " << index << ", ";

        ++index;
    }

    stream << input[index] << " @ " << index;

    return stream;
}

#endif /* HTD_HTD_FITNESSEVALUATION_CPP */
