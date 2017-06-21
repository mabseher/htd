/*
 * File:   HgrFormatImporter.cpp
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

#ifndef HTD_IO_HGRFORMATIMPORTER_CPP
#define HTD_IO_HGRFORMATIMPORTER_CPP

#include <htd_io/HgrFormatImporter.hpp>

#include <htd/MultiHypergraphFactory.hpp>

#include <fstream>
#include <string>
#include <stdexcept>

/**
 *  Private implementation details of class htd_io::HgrFormatImporter.
 */
struct htd_io::HgrFormatImporter::Implementation
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

htd_io::HgrFormatImporter::HgrFormatImporter(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{

}

htd_io::HgrFormatImporter::~HgrFormatImporter(void)
{

}

htd::IMultiHypergraph * htd_io::HgrFormatImporter::import(const std::string & path) const
{
    std::ifstream stream(path);

    return import(stream);
}

htd::IMultiHypergraph * htd_io::HgrFormatImporter::import(std::istream & stream) const
{
    std::size_t vertexCount = 0;
    std::size_t edgeCount = 0;

    bool firstLine = true;

    bool error = false;

    htd::IMutableMultiHypergraph * ret = implementation_->managementInstance_->multiHypergraphFactory().createInstance();

    const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

    if (stream.good())
    {
        std::string line;

        while (!error && std::getline(stream, line) && !managementInstance.isTerminated())
        {
            if (line.empty())
            {
                error = true;
            }
            else
            {
                if (line[line.size() - 1] == '\r')
                {
                    line.pop_back();
                }

                if (line[0] != 'c')
                {
                    if (firstLine)
                    {
                        if (line.length() < 5 || line.compare(0, 5, "p tw ") != 0)
                        {
                            error = true;
                        }
                        else
                        {
                            line = line.substr(5);

                            std::size_t pos = 0;

                            vertexCount = std::stol(line, &pos);

                            if (line[pos] != ' ')
                            {
                                error = true;
                            }

                            line = line.substr(pos + 1);

                            edgeCount = std::stol(line, &pos);

                            if (pos != line.length())
                            {
                                error = true;
                            }

                            ret->addVertices(vertexCount);

                            firstLine = false;
                        }
                    }
                    else
                    {
                        std::size_t pos = 0;

                        std::vector<htd::vertex_t> vertices;

                        while (!error && pos != line.length())
                        {
                            vertices.push_back(std::stoul(line, &pos));

                            if (pos != line.length())
                            {
                                if (line[pos] != ' ')
                                {
                                    error = true;
                                }
                                else
                                {
                                    line = line.substr(pos + 1);

                                    pos = 0;
                                }
                            }
                        }

                        ret->addEdge(std::move(vertices));

                        edgeCount--;
                    }
                }
            }
        }

        if (edgeCount != 0 && !managementInstance.isTerminated())
        {
            error = true;
        }
    }
    else
    {
        error = true;
    }

    if (firstLine || error)
    {
        delete ret;

        ret = nullptr;
    }

    return ret;
}

#endif /* HTD_IO_HGRFORMATIMPORTER_CPP */
