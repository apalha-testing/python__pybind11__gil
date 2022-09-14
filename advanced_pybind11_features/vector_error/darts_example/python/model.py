import vector_error as vector_error

#Create a mesh
mesh = vector_error.conn_mesh()

#Call the (only) method to be sure to initialize the attribute
mesh.init()

#get the attribute
comp = mesh.composition
print(comp)

#resize the vector (attribute)
mesh.composition.resize(12) # <-- here is the error
