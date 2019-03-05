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

class Body
{
public:

	//default constructor
	Body();
	~Body();


	/*
	** GET METHODS
	*/
	//mesh
	Mesh& getmesh() { return m_mesh; }

	// transform matrices
	glm::mat3 getTranslate() const { return m_mesh.getTranslate(); }
	glm::mat3 getRotate() const { return m_mesh.getRotate(); }
	glm::mat3 getScale() const { return m_mesh.getScale(); }

	// dynamic variables
	glm::vec3 & getAcc() { return m_acc; }
	glm::vec3 & getVel() { return m_vel; }
	glm::vec3 & getPos() { return m_pos; }

	// physical properties
	float getMass() const { return m_mass; }
	float getCor() { return m_cor; }

	/*
	** SET METHODS
	*/
	// mesh
	void setMesh(Mesh m) { m_mesh = m; }

	// dynamic variables
	void setAcc(const glm::vec3 & vect) { m_acc = vect; }
	void setVel(const glm::vec3 & vect) { m_vel = vect; }
	void setVel(int i, float v) { m_vel[i] = v; } // set the ith coordinate of the velocity vector
	void setPos(const glm::vec3 & vect) { m_pos = vect; m_mesh.setPos(vect); }
	void setPos(int i, float p) { m_pos[i] = p; m_mesh.setPos(i, p); } // set the ith coordinateof the position vector

	// physical properties
	void setCor(float cor) { m_cor = cor; }
	void setMass(float mass) { m_mass = mass; }

	/*
	 ** OTHER METHODS
	 */

	 // transformation methods
	void translate(const glm::vec3 & vect);
	void rotate(float angle, const glm::vec3 & vect);
	void scale(const glm::vec3 & vect);

private:
	Mesh m_mesh; // mesh used to represent the body

	float m_mass; // mass
	float m_cor; // coefficient of restitution

	glm::vec3 m_acc; // acceleration
	glm::vec3 m_vel; // velocity
	glm::vec3 m_pos; // position
};

