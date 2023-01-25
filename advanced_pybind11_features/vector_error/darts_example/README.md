# vector_error example

This repo put in evidence an error obtained when calling the method `resize` on an object of type `vector<value_t>` called from pyhton.
The `value_t` data type is exposed via pybind11.

## Requirements

You can install `pybind11` on a conda environment:
```
conda install -c conda-forge pybind11
```
If you want to change the version of this header-only library you can simply replace the folder `pybind11` in the include path (obtain it via: `python -c "import pybind11; print(pybind11.get_include())"`). 

## Setup with CMake

We will start with the `CMake` based setup from a [previous introduction found here](https://github.com/smrfeld/cmake_cpp_pybind11_tutorial).

The `src` folder contains the source code in C++ and the binds in the subfolder `src/pybind11`. The folder `python` contains a python script with some code to test the behavior on that side. The example can be build as follows:

```
mkdir build
cd build
cmake .. -DPYTHON_LIBRARY_DIR="/path/to/site-packages" -DPYTHON_EXECUTABLE="/path/to/executable/python3"
make
```

for reference my paths are:

```
DPYTHON_LIBRARY_DIR="/opt/homebrew/Caskroom/miniforge/base/envs/onset_darts/lib/python3.8"
DPYTHON_EXECUTABLE="/opt/homebrew/Caskroom/miniforge/base/envs/onset_darts/bin/python"
```

Bare in mind that I am using a conda environment named `onset_darts` with python version 3.8.

To run the python example, copy the python file into the build directory: `cp python/model.py build`.

## Automated setup

Alternatively to Setup with CMake, run the script `full_build_and_test.sh` to build and run the python example file, and to generate documentation. Check that the specified versions of `gcc` and `g++` match your environment.

## About documentation

Information about docs implementation is in [docs/README.md](docs/README.md).

## Ask for help

Questions and remarks can be addressed to Luisa Orozco and/or Artur Palha.
