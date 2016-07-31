/* 
 * File:   PreprocessorDefinitions.hpp
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

#ifndef HTD_HTD_PREPROCESSORDEFINITIONS_HPP
#define HTD_HTD_PREPROCESSORDEFINITIONS_HPP

#include <htd/CompilerDetection.hpp>

#include <cassert>

#ifdef HTD_COMPILER_IS_MSVC
    #if HTD_COMPILER_IS_MSVC == 1
        #define HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    #endif
#endif

#if HTD_COMPILER_IS_MSVC == 1
    #define HTD_SYMBOL_EXPORT __declspec(dllexport)
    #define HTD_SYMBOL_IMPORT __declspec(dllimport)
    #define HTD_LOCAL_SYMBOL
    #define HTD_IMPLEMENTATION_EXPORT struct __declspec(dllexport)
    #define HTD_IMPLEMENTATION_IMPORT extern struct __declspec(dllimport)
#else
    #if HTD_COMPILER_IS_GNU == 1 || HTD_COMPILER_IS_Clang == 1
        #define HTD_SYMBOL_EXPORT __attribute__ ((visibility ("default")))
        #define HTD_SYMBOL_IMPORT __attribute__ ((visibility ("default")))
        #define HTD_LOCAL_SYMBOL  __attribute__ ((visibility ("hidden")))
        #define HTD_IMPLEMENTATION_EXPORT struct __attribute__ ((visibility ("default")))
        #define HTD_IMPLEMENTATION_IMPORT extern struct __attribute__ ((visibility ("default")))
    #else
        #define HTD_SYMBOL_EXPORT
        #define HTD_SYMBOL_IMPORT
        #define HTD_LOCAL_SYMBOL
        #define HTD_IMPLEMENTATION_EXPORT struct
        #define HTD_IMPLEMENTATION_IMPORT struct
    #endif
#endif

#ifdef HTD_SHARED_LIBRARY
    #ifdef htd_EXPORTS
        #define HTD_API HTD_SYMBOL_EXPORT
        #define HTD_IMPLEMENTATION HTD_IMPLEMENTATION_EXPORT
    #else
        #define HTD_API HTD_SYMBOL_IMPORT
        #define HTD_IMPLEMENTATION HTD_IMPLEMENTATION_IMPORT
    #endif
    #define HTD_LOCAL HTD_LOCAL_SYMBOL
#else
    #define HTD_API
    #define HTD_LOCAL
    #define HTD_IMPLEMENTATION struct
#endif

//#define HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE

#define HTD_UNUSED(x) (void)(x);

#ifdef NDEBUG
    #define HTD_ASSERT(x)
#else
    #define HTD_ASSERT(x) assert(x);
#endif

#ifdef NDEBUG
    #define DEBUGGING_CODE(x)
#else
    #ifdef HTD_DEBUG_OUTPUT
        #define DEBUGGING_CODE(x) x
    #else
        #define DEBUGGING_CODE(x)
    #endif
#endif

#ifdef NDEBUG
    #define DEBUGGING_CODE_LEVEL2(x) 
#else
    #ifndef DEBUG2
        #define DEBUGGING_CODE_LEVEL2(x) 
    #else
        #define DEBUGGING_CODE_LEVEL2(x) x
    #endif
#endif

#endif /* HTD_HTD_PREPROCESSORDEFINITIONS_HPP */
