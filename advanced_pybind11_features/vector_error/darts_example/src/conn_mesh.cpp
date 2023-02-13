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

int conn_mesh::get_sum(int a, int b)
{
	return a + b;
}

int conn_mesh::get_diff(int a, int b)
{
	return a - b;
}
