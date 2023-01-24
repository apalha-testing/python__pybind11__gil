"""
This file is the same as python/model.py
I had to create it here to import (relatively)
vector_error.so located in build.


This is a python file in which I create an object from a class
defined in C++.
The C++ code has been exposed using pybind11.
"""

import build.vector_error as vector_error

def create_mesh():
	"""
	Creates a mesh calling the constructor in C++.

	:returns: Object conn_mesh initialized to default values.
	"""
	return vector_error.conn_mesh()


#Create a mesh
mesh = vector_error.conn_mesh()

#Call the (only) method to be sure to initialize the attribute
mesh.init()

#get the attribute
comp = mesh.composition
print(comp)

#resize the vector (attribute)
mesh.composition.resize(12) # <-- here is the error
