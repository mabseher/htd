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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

namespace py = boost::python;

namespace htd {
  void srand_1(unsigned int seed){
    srand (seed);
  }

  void srand_2(){
    srand (time(NULL));
  }

  void export_srand(){
    py::def("set_seed", htd::srand_1);
    py::def("set_seed2time", htd::srand_2);
  }
}
