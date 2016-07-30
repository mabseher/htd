/*
 * File:   LpFormatImporter.cpp
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

#ifndef HTD_HTD_LPFORMATIMPORTER_CPP
#define	HTD_HTD_LPFORMATIMPORTER_CPP

#include <htd/LpFormatImporter.hpp>

#include <fstream>
#include <iostream>
#include <string>

/**
 *  Private implementation details of class htd::LpFormatImporter.
 */
struct htd::LpFormatImporter::Implementation
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
};

htd::LpFormatImporter::LpFormatImporter(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{

}

htd::LpFormatImporter::~LpFormatImporter(void)
{

}

htd::NamedMultiHypergraph<std::string, std::string> * htd::LpFormatImporter::import(const std::string & path) const
{
    std::ifstream stream(path);

    return import(stream);
}

htd::NamedMultiHypergraph<std::string, std::string> * htd::LpFormatImporter::import(std::istream & stream) const
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
                        hyperedge.push_back(line.substr(0, nextPosition));
                        
                        line.erase(0, nextPosition + 1);
                        
                        nextPosition = line.find(",");
                    }
                    
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

#endif /* HTD_HTD_LPFORMATIMPORTER_CPP */
