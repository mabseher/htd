/* 
 * File:   Globals.hpp
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

#ifndef HTD_HTD_GLOBALS_HPP
#define HTD_HTD_GLOBALS_HPP

#include <htd/CompilerDetection.hpp>

#ifdef HTD_COMPILER_IS_MSVC
    #if HTD_COMPILER_IS_MSVC == 1
        #define HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    #endif
#endif

#if HTD_COMPILER_IS_MSVC == 1
    #define HTD_SYMBOL_EXPORT __declspec(dllexport)
    #define HTD_SYMBOL_IMPORT __declspec(dllimport)
    #define HTD_LOCAL
#else
    #if HTD_COMPILER_IS_GNU == 1 || HTD_COMPILER_IS_Clang == 1
        #define HTD_SYMBOL_EXPORT __attribute__ ((visibility ("default")))
        #define HTD_SYMBOL_IMPORT __attribute__ ((visibility ("default")))
        #define HTD_LOCAL  __attribute__ ((visibility ("hidden")))
    #else
        #define HTD_SYMBOL_EXPORT
        #define HTD_SYMBOL_IMPORT
        #define HTD_LOCAL
    #endif
#endif

#ifdef HTD_SHARED_LIB
  #ifdef htd_EXPORTS
    #define HTD_API HTD_SYMBOL_EXPORT
  #else
    #define HTD_API HTD_SYMBOL_IMPORT
  #endif
#else
  #define HTD_API
#endif

//#define HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE

#include <htd/Id.hpp>
#include <htd/State.hpp>
#include <htd/Vertex.hpp>
#include <htd/Library.hpp>

#include <cstdlib>

namespace htd
{
    /**
     *  Datatype for indices.
     */
    typedef std::size_t index_t;
}

#endif /* HTD_HTD_GLOBALS_HPP */
