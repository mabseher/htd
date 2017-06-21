/*
 * File:   LpFormatImporter.cpp
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

#ifndef HTD_IO_LPFORMATIMPORTER_CPP
#define HTD_IO_LPFORMATIMPORTER_CPP

#include <htd_io/LpFormatImporter.hpp>

#include <fstream>
#include <iostream>
#include <string>

/**
 *  Private implementation details of class htd_io::LpFormatImporter.
 */
struct htd_io::LpFormatImporter::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager   The management instance to which the current object instance belongs.
     */
    Implementation(const htd::LibraryInstance * const manager) : managementInstance_(manager)
    {

    }

    virtual ~Implementation()
    {

    }

    /**
     *  The management instance to which the current object instance belongs.
     */
    const htd::LibraryInstance * managementInstance_;

    /**
     *  Remove all leading and trailing whitespaces from a given string.
     *
     *  @param[in] value    The string which shall be trimmed.
     */
    void trim(std::string & value);
};

htd_io::LpFormatImporter::LpFormatImporter(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{

}

htd_io::LpFormatImporter::~LpFormatImporter(void)
{

}

htd::NamedMultiHypergraph<std::string, std::string> * htd_io::LpFormatImporter::import(const std::string & path) const
{
    std::ifstream stream(path);

    return import(stream);
}

htd::NamedMultiHypergraph<std::string, std::string> * htd_io::LpFormatImporter::import(std::istream & stream) const
{
    bool error = false;

    htd::NamedMultiHypergraph<std::string, std::string> * ret = new htd::NamedMultiHypergraph<std::string, std::string>(implementation_->managementInstance_);

    const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

    if (stream.good())
    {
        std::string line;

        std::size_t nextPosition = 0;
        
        std::size_t startPosition = 0;
        
        std::size_t finishPosition = 0;
        
        while (!error && std::getline(stream, line) && !managementInstance.isTerminated())
        {
            finishPosition = 0;
            
            startPosition = line.find("edge(");
            
            if (startPosition == 0)
            {
                startPosition = startPosition + std::string("edge(").length();
                
                finishPosition = line.find(").", startPosition);
                
                if (finishPosition == line.length() - 2)
                {
                    line.erase(finishPosition, std::string(").").length());
                    line.erase(0, startPosition);
                    
                    std::vector<std::string> hyperedge;
                    
                    nextPosition = line.find(",");
                    
                    while (nextPosition != std::string::npos)
                    {
                        std::string element = line.substr(0, nextPosition);

                        this->implementation_->trim(element);

                        hyperedge.push_back(element);
                        
                        line.erase(0, nextPosition + 1);
                        
                        nextPosition = line.find(",");
                    }

                    this->implementation_->trim(line);

                    if (line.length() > 0)
                    {
                        hyperedge.push_back(line);
                    }

                    if (hyperedge.size() > 0)
                    {
                        ret->addEdge(hyperedge);
                    }
                }
            }
            else
            {
                startPosition = line.find("vertex(");

                if (startPosition == 0)
                {
                    startPosition = startPosition + std::string("vertex(").length();

                    finishPosition = line.find(").", startPosition);

                    if (finishPosition == line.length() - 2)
                    {
                        line.erase(finishPosition, std::string(").").length());
                        line.erase(0, startPosition);

                        this->implementation_->trim(line);

                        ret->addVertex(line);
                    }
                }
            }
        }
    }
    else
    {
        error = true;
    }

    if (error)
    {
        delete ret;

        ret = nullptr;
    }
    
    return ret;
}

void htd_io::LpFormatImporter::Implementation::trim(std::string & value)
{
    value.erase(0, value.find_first_not_of(" \t\n\r\f\v"));
    value.erase(value.find_last_not_of(" \t\n\r\f\v") + 1);
}

#endif /* HTD_IO_LPFORMATIMPORTER_CPP */
