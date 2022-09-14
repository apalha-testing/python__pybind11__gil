#!/bin/bash

# Define your environment
PYTHON_LIBRARY_DIR="/opt/homebrew/Caskroom/miniforge/base/envs/onset_darts/lib/python3.8"
PYTHON_EXECUTABLE="/opt/homebrew/Caskroom/miniforge/base/envs/onset_darts/bin/python"

# Set the compilers to gcc instead of clang
printf "\n-----------------------------------------------------\n"
printf "Setting your compilers to gcc-11 and g++-11...\n"
printf "-----------------------------------------------------\n"
export CC=gcc-11
export CXX=g++-11

# Build the cpp code
printf "\n\n-----------------------------------------------------\n"
printf "Building cpp code...\n"
printf "-----------------------------------------------------\n"
cd cpp
mkdir build
cd build
cmake ..
make

# Build the python interface code
printf "\n\n-----------------------------------------------------\n"
printf "Building python interface code...\n"
printf "-----------------------------------------------------\n"
cd ../../
mkdir build
cd build
cmake .. -DPYTHON_LIBRARY_DIR=$PYTHON_LIBRARY_DIR -DPYTHON_EXECUTABLE=$PYTHON_EXECUTABLE
make

# Now copy the python example and run it
printf "\n\n-----------------------------------------------------\n"
printf "Running example...\n"
printf "-----------------------------------------------------\n"
cp ../tests/interpolator.py ./
#python interpolator.py
