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

#include "Body.h"

Body::Body()
{
}


Body::~Body()
{
}

/* TRANSFORMATION METHODS */
void Body::translate(const glm::vec3 & vect) {
	m_pos = m_pos + vect;
	m_mesh.translate(vect);

}

void Body::rotate(float angle, const glm::vec3 & vect) {
	m_mesh.rotate(angle, vect);

}

void Body::scale(const glm::vec3 & vect) {
	m_mesh.scale(vect);

}

//Body();
	//~Body();
