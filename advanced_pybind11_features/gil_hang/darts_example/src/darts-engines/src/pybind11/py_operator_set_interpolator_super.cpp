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

#ifdef PYBIND11_ENABLED
#include <pybind11.h>
#include "py_globals.h"
#include <stl.h>

#include "py_interpolator_exposer.hpp"

namespace py = pybind11;

void pybind_operator_set_interpolator_super(py::module &m)
{
	// kinetics: NC + 1 (fluid acc) + (NC + 1)*NP (flux) + NC + 1 (kin) + NP (upsat) + NP * (NC + 1) (concentration) + 3 (rock) + 2 * NP (pc&G) + 1 (poro):
	// two phase: (2 * 3) * (N_DIMS - 1) + 2 * 4 + 1 + 7

	// N_DIMS = 1, 2, ..., N_DIMS_MAX
	const int N_DIMS_MAX = MAX_NC;

	// thermal problem: N_OPS = A * N_DIMS + B
	const int A = 6;
	const int B = 10;

	// thermal problem: N_OPS = A * N_DIMS + B, two phase
	const int Asat = 6;
	const int Bsat = 12;

	// single phase thermal: N_OPS = A * N_DIMS + B
	const int As = 4;
	const int Bs = 7;

	// isothermal problem: N_OPS = A * N_DIMS + B, three phases
	const int A1 = 8;
	const int B1 = 13;

  recursive_exposer_ndims_nops<interpolator_exposer, py::module, N_DIMS_MAX, A, B> e;
  recursive_exposer_ndims_nops<interpolator_exposer, py::module, N_DIMS_MAX, A1, B1> e1;
  recursive_exposer_ndims_nops<interpolator_exposer, py::module, N_DIMS_MAX, As, Bs> es;
  recursive_exposer_ndims_nops<interpolator_exposer, py::module, N_DIMS_MAX, Asat, Bsat> esat;
 
  e.expose(m);
  e1.expose(m);
  es.expose(m);
  esat.expose(m);
}

#endif //PYBIND11_ENABLED