#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>
#include "globals.h"
#include "conn_mesh.h"

namespace py = pybind11;

//from py_globals.h in darts-engines
PYBIND11_MAKE_OPAQUE(std::vector<value_t>);

//Definition of pybind module
PYBIND11_MODULE(vector_error, m) {
    // Optional docstring
    m.doc() = "Vector error example";

    // vector exposure
    py::bind_vector<std::vector<value_t>>(m, "value_vector", py::module_local(true), py::buffer_protocol())
    .def(py::pickle(
      [](const std::vector<value_t> &p) { // __getstate__
        py::tuple t(p.size());
        for (int i = 0; i < p.size(); i++)
          t[i] = p[i];

        return t;
      },
      [](py::tuple t) { // __setstate__
        std::vector<value_t> p(t.size());

        for (int i = 0; i < p.size(); i++)
          p[i] = t[i].cast<value_t>();

        //p.setExtra(t[1].cast<int>());

        return p;
      }));

    //Class conn_mesh exposure
    py::class_<conn_mesh>(m, "conn_mesh", "Class")
      .def(py::init<>()) //constructor
      .def("init", &conn_mesh::init, "init method") //method
      .def_readwrite("composition", &conn_mesh::composition); //attribute
}
