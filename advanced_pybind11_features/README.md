# Advanced pybind11 features

[You can find the corresponding Medium article here.](https://medium.com/practical-coding/three-advanced-pybind11-features-for-wrapping-c-code-into-python-6dbcac169b93)

This repo details three advanced pybind11 features:
* Abstract base classes (ABC) and pure virtual methods.

The starting point for this project is a previous project found [here](https://github.com/smrfeld/cmake_cpp_pybind11_tutorial).

## Requirements

Obviously, you will need `pybind11`. On Mac:
```
brew install pybind11
```
will do it.

## Setup with CMake

We will start with the `CMake` based setup from a [previous introduction found here](https://github.com/smrfeld/cmake_cpp_pybind11_tutorial).

The directory structure is as follows:
```
/
|-- cpp
|    |-- CMakeLists.txt
|    |-- include
|    |       |-- interpolate
|    |       \-- interpolate_bits
|    |               \-- interpolate.hpp
|    |-- src
|         \-- interpolate.cpp
|
|-- python
|    |-- interpolate.cpp
|    \-- pybind_interpolate.cpp  
|
|-- CMakeLists.txt
\-- full_build_and_test.sh
```
The idea here is:
1. The inner `cpp` folder contains a `C++` project for a library. It can be built using the `CMakeLists.txt` as follows:
    ```
    cd cpp
    mkdir build
    cd build
    cmake ..
    make
    ```
2. The outer folder contains the wrapping code in the `python` library, and a second `CMakeLists.txt` for building the `python` library as follows:
    ```
    mkdir build
    cd build
    cmake .. -DPYTHON_LIBRARY_DIR="/path/to/site-packages" -DPYTHON_EXECUTABLE="/path/to/executable/python3"
    make
    ```
    My paths are:
    ```
    DPYTHON_LIBRARY_DIR="/opt/homebrew/Caskroom/miniforge/base/envs/onset_darts/lib/python3.8"
    DPYTHON_EXECUTABLE="/opt/homebrew/Caskroom/miniforge/base/envs/onset_darts/bin/python"
    ```
    Bare in mind that I am using a conda environment named `onset_darts` with python version 3.8.

3. To run the python example, the simplest things to do is to just copy the .py file into the `build` folder of the outer folder.

4. You can run the simple script `full_build_and_test.sh` to build and run the python example file.
