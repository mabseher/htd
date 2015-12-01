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

namespace py = boost::python;
#include <htd/ITreeDecomposition.hpp>

#include <PyITreeDecomposition.h>


namespace htd {
  //TODO: overhead, add iterator
  template<class T>
  py::list std_vector_to_py_list(std::vector<T> vector) {
    typename std::vector<T>::iterator iter;
    boost::python::list list;
    for (iter = vector.begin(); iter != vector.end(); ++iter) {
      list.append(*iter);
    }
    return list;
  }
  
  py::list vertices_(htd::ITreeDecomposition &decomposition) {
    htd::vertex_container vertices;
    decomposition.getVertices(vertices);
    return std_vector_to_py_list(vertices);
  }

  //TODO: bagContent -> smartPointer -> iterator
  py::list bags_(htd::ITreeDecomposition &decomposition, htd::vertex_t vertex) {
    htd::vertex_container bag;
    decomposition.getBagContent(vertex, bag);
    return std_vector_to_py_list(bag);
  }

  void export_ITreeDecomposition(){
    py::class_<htd::ITreeDecomposition, boost::noncopyable>("LTree", py::no_init)
      .def("vertices", &htd::vertices_)
      .def("bag_content", &htd::bags_);
  }
}
