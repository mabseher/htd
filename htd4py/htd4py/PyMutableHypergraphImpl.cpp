/*
 This file is part of htd (htd Python API).

 htd, a tree decomposition library.

 htd4Py Copyright 2015
 Johannes K. Fichte, TU Wien, Austria

 htd Copyright 2015
 Michael Abseher, TU Wien, Austria

 htd4Py is free software: you can redistribute it and/or modify it
 under the terms of the GNU General Public License as published by the
 Free Software Foundation, either version 3 of the License, or (at
 your option) any later version.  htd4Py is distributed in the hope
 that it will be useful, but WITHOUT ANY WARRANTY; without even the
 implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE.  See the GNU General Public License for more details.  You
 should have received a copy of the GNU General Public License along
 with htd4Py.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <Python.h>
#include <boost/python.hpp>

#include <unordered_set>
#include <stdlib.h>
#include <htd/Globals.hpp>
#include <htd/MutableHypergraphImpl.hpp>

#include <PyMutableHypergraphImpl.h>

namespace py = boost::python;

//TODO: RuntimeError mapping
//  h.add_edge(0,1)
//  RuntimeError: void htd::MutableHypergraphImpl::addEdge(const htd::hyperedge_t &)

namespace htd {
  void (htd::MutableHypergraphImpl::*addEdge_)(htd::vertex_t, htd::vertex_t) = &htd::MutableHypergraphImpl::addEdge;
  std::size_t (htd::MutableHypergraphImpl::*edgeCount_1)(void) const = &htd::MutableHypergraphImpl::edgeCount;
  std::size_t (htd::MutableHypergraphImpl::*edgeCount_2)(htd::vertex_t) const = &htd::MutableHypergraphImpl::edgeCount;
  void (htd::MutableHypergraphImpl::*removeEdge_1)(htd::vertex_t, htd::vertex_t) = &htd::MutableHypergraphImpl::removeEdge;
  void (htd::MutableHypergraphImpl::*removeEdge_2)(const htd::edge_t &) = &htd::MutableHypergraphImpl::removeEdge;
  void (htd::MutableHypergraphImpl::*removeVertex_1)(htd::vertex_t) = &htd::MutableHypergraphImpl::removeVertex;
  void (htd::MutableHypergraphImpl::*removeVertex_2)(htd::vertex_t, bool) = &htd::MutableHypergraphImpl::removeVertex;

  void export_MutableHypergraphImpl(){
    py::class_<htd::MutableHypergraphImpl>("Hypergraph", py::init<std::size_t>())
      .def("add_edge", htd::addEdge_)
      .def("add_vertex", &htd::MutableHypergraphImpl::addVertex)
      .def("is_vertex", &htd::MutableHypergraphImpl::isVertex)
      .def("is_isolated_vertex", &htd::MutableHypergraphImpl::isIsolatedVertex)
      .def("num_edges", htd::edgeCount_1)
      .def("num_neighbors", &htd::MutableHypergraphImpl::neighborCount)
      .def("num_vertices", &htd::MutableHypergraphImpl::vertexCount)
      .def("num_isolated_vertices",&htd::MutableHypergraphImpl::isolatedVertexCount)
      .def("remove_edge", htd::removeEdge_1)
      .def("remove_vertex", htd::removeVertex_1);
  }
}
