#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_interpolate(py::module &);

namespace mcl {

PYBIND11_MODULE(interpolate, m) {
    // Optional docstring
    m.doc() = "Interpolate library";

    init_interpolate(m);
}
}
