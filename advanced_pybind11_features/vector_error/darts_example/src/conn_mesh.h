#include <vector>
#include <string>
#include "globals.h"

//Class having an attribute of type vector<value_t>
class conn_mesh
{
	public:
		conn_mesh () {}; // default constructor
		std::vector<value_t> composition; //defining an attribute
		void init();
};

