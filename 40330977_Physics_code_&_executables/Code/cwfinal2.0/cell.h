#pragma once
// Math constants
#define _USE_MATH_DEFINES
#include <cmath>  
#include <random>

// Std. Includes
#include <string>
#include <time.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_operation.hpp>
#include "glm/ext.hpp"

// Other Libs
#include "SOIL2/SOIL2.h"

// project includes
#include "Application.h"
#include "Shader.h"
#include "Mesh.h"
#include "Sphere.h"

class cell
{
public:
	cell();
	~cell();

	bool cell::sphcoltest();

	std::vector<Sphere*> getlist() { return spcell; }

	void resizer(const int &size) { spcell.resize(size); }

	void getlistel(Sphere* s) { spcell.push_back(s); }

	void clearsphere() { spcell.clear(); }

private:
	std::vector<Sphere*> spcell;
};

