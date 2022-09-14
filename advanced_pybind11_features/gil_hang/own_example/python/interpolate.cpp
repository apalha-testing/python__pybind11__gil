#include "../cpp/include/interpolate_bits/interpolate.hpp"

#include <pybind11/stl.h>
#include <pybind11/pybind11.h>

#include <iostream>

namespace py = pybind11;

namespace interpolate {

class operator_set_evaluator_trampoline : public operator_set_evaluator {

public:

    using operator_set_evaluator::operator_set_evaluator;

    double evaluate(double value) {
      {
        std::cout << "Ready to acquire the gil ...\n";
        py::gil_scoped_acquire acquire;
        std::cout << "Acquired the gil ...\n";

        PYBIND11_OVERLOAD_PURE(
            double, /* Return type */
            operator_set_evaluator,      /* Parent class */
            evaluate,          /* Name of function in C++ (must match Python name) */
            value   /* args */
        );
      }
    }
};

}

void init_interpolate(py::module &m) {
  using namespace pybind11::literals;

    py::class_<interpolate::operator_set_evaluator, interpolate::operator_set_evaluator_trampoline> operator_set_evaluator(m, "operator_set_evaluator");
    operator_set_evaluator
    .def(py::init<>())
    .def("evaluate", &interpolate::operator_set_evaluator::evaluate, "Evaluate operator values", "value"_a); //, py::call_guard<py::gil_scoped_release>());

    py::class_<interpolate::multilinear_adaptive_cpu_interpolator, std::shared_ptr<interpolate::multilinear_adaptive_cpu_interpolator>>(m, "multilinear_adaptive_cpu_interpolator")
    .def(py::init<interpolate::operator_set_evaluator *>(), py::arg("supporting_point_evaluator_input"))
    .def("get_point_data",
         &interpolate::multilinear_adaptive_cpu_interpolator::get_point_data,
         py::arg("value"), py::call_guard<py::gil_scoped_release>());
}
