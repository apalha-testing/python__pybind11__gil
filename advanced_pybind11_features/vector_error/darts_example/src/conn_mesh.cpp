#include <vector>
#include <string>
#include "globals.h"
#include "conn_mesh.h"

//Defining the init method of class conn_mesh
using namespace std;
void conn_mesh::init()
{
	composition.resize(10); //call of resize from C++
}
