//*************************************************************************
//    Copyright (c) 2018
//            Mark Khait         M.Khait@tudelft.nl
//            Denis Voskov    D.V.Voskov@tudelft.nl
//    Delft University of Technology, the Netherlands
//
//    This file is part of the Delft Advanced Research Terra Simulator (DARTS)
//
//    DARTS is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as
//    published by the Free Software Foundation, either version 3 of the
//    License, or (at your option) any later version.
//
//    DARTS is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public
//    License along with DARTS. If not, see <http://www.gnu.org/licenses/>.
// *************************************************************************

#include "py_globals.h"
namespace py = pybind11;

void pybind_globals(py::module &);
void pybind_evaluator_iface(py::module &);
void pybind_operator_set_from_files(py::module &);
void pybind_operator_set_interpolator_pz(py::module &);
void pybind_operator_set_interpolator_pz_sol(py::module &);
void pybind_operator_set_interpolator_pz_cap_gra(py::module &);
void pybind_operator_set_interpolator_pz_cap_gra_dif(py::module &);
void pybind_operator_set_interpolator_pz_dif(py::module &);
void pybind_operator_set_interpolator_pz_kin(py::module &);
void pybind_operator_set_interpolator_pzt_kin(py::module &);
void pybind_operator_set_interpolator_pz_kin_phi(py::module &);
void pybind_operator_set_interpolator_pz_kin_dif(py::module &);
void pybind_operator_set_interpolator_pz_kin_dif_np(py::module &);
void pybind_operator_set_interpolator_pze(py::module &);
void pybind_operator_set_interpolator_pze_dvelocity(py::module &);
void pybind_operator_set_interpolator_pze_gra(py::module &);
void pybind_operator_set_interpolator_pzt(py::module &);
void pybind_operator_set_interpolator_rates(py::module &);
void pybind_operator_set_interpolator_super(py::module &);
void pybind_operator_set_interpolator_super_elastic(py::module &);

class operator_set_gradient_evaluator_iface;

PYBIND11_MODULE(engines, m)
{
  m.doc() = "Delft Advanced Research Terra Simulator";
  //auto m1 = m.def_submodule("engines", "Collection of DARTS simulators based on OBL approach");
  py::bind_vector<std::vector<index_t>>(m, "index_vector", py::module_local(true), py::buffer_protocol())
      .def("resize",
          (void (std::vector<index_t>::*) (size_t count)) & std::vector<index_t>::resize,
          "changes the number of elements stored");
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
          })) \
      .def("resize",
          (void (std::vector<value_t>::*) (size_t count)) &std::vector<value_t>::resize,
          "changes the number of elements stored");
  py::bind_vector<std::vector<operator_set_gradient_evaluator_iface *>>(m, "op_vector");
  py::bind_map<std::map<std::string, timer_node>>(m, "timer_map");

  pybind_globals(m);

  pybind_evaluator_iface(m);

  pybind_operator_set_interpolator_pz(m);
  pybind_operator_set_interpolator_pz_sol(m);
  pybind_operator_set_interpolator_pz_cap_gra(m);
  pybind_operator_set_interpolator_pz_cap_gra_dif(m);
  pybind_operator_set_interpolator_pz_dif(m);
  pybind_operator_set_interpolator_pz_kin(m);
  pybind_operator_set_interpolator_pzt_kin(m);
  pybind_operator_set_interpolator_pz_kin_phi(m);
  pybind_operator_set_interpolator_pz_kin_dif(m);
  pybind_operator_set_interpolator_pz_kin_dif_np(m);
  pybind_operator_set_interpolator_pze(m);
  pybind_operator_set_interpolator_pze_dvelocity(m);
  pybind_operator_set_interpolator_pze_gra(m);
  pybind_operator_set_interpolator_pzt(m);
  pybind_operator_set_interpolator_rates(m);
  pybind_operator_set_interpolator_super(m);

}
