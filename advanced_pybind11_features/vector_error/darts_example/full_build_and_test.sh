#!/bin/bash

# Define your environment
PYTHON_LIBRARY_DIR="/opt/homebrew/Caskroom/miniforge/base/envs/pybind/lib/python3.8"
PYTHON_EXECUTABLE="/opt/homebrew/Caskroom/miniforge/base/envs/pybind/bin/python"

# Set the compilers to gcc instead of clang
printf "\n-----------------------------------------------------\n"
printf "Setting your compilers to gcc-11 and g++-11 in macOS, in linux should be gcc and g++\n"
printf "-----------------------------------------------------\n"
export CC=gcc-12
export CXX=g++-12

# Build the example
printf "\n-----------------------------------------------------\n"
printf "Building python interface code...\n"
printf "-----------------------------------------------------\n"
if [ -d "./build" ]; then
	rm -rf build
fi
mkdir build
cd build
cmake .. -DPYTHON_LIBRARY_DIR=$PYTHON_LIBRARY_DIR -DPYTHON_EXECUTABLE=$PYTHON_EXECUTABLE
make

# Now copy the python example and run it.
# Have to run it within build because is where vector_error.so (from pybind11) is created
printf "\n-----------------------------------------------------\n"
printf "Running example..."
printf "\n-----------------------------------------------------\n"
cp ../python/model.py ./
python model.py

# Generating the documentation locally
printf "\n-----------------------------------------------------\n"
printf "Generating documentation"
printf "\n-----------------------------------------------------\n"
cd ../docs
make clean
make html
cd ../
