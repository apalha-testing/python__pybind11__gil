#!/bin/bash

# Define your environment
PYTHON_LIBRARY_DIR="/opt/homebrew/Caskroom/miniforge/base/envs/onset_darts/lib/python3.8"
PYTHON_EXECUTABLE="/opt/homebrew/Caskroom/miniforge/base/envs/onset_darts/bin/python"

# Set the compilers to gcc instead of clang
printf "\n-----------------------------------------------------\n"
printf "Setting your compilers to gcc-11 and g++-11 in macOS, in linux should be gcc and g++\n"
printf "-----------------------------------------------------\n"
export CC=gcc-11
export CXX=g++-11

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

# Now copy the python example and run it
printf "\n-----------------------------------------------------\n"
printf "Running example...\n"
printf "\n-----------------------------------------------------\n"
cp ../python/model.py ./
python model.py
