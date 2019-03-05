#pragma once
#include "Rigidbody.h"
class Sphere :
	public Rigidbody
{
public:
	Sphere();
	~Sphere();

	float TestSphere(Sphere b);

	void scale(const float &scaler);

	int celltestcol(const glm::vec3 &bound);
	int celltestrow(const glm::vec3 &bound);

	void setradius(const float &rad) { m_radius = rad; }

	float getradius() { return m_radius; }

	void setbound(const glm::vec3 &pos) { 
		t = pos + glm::vec3(0.0f, 0.0f, 1.0f); 
		l = pos + glm::vec3(-1.0f, 0.0f, 0.0f);
		r = pos + glm::vec3(1.0f, 0.0f, 0.0f);
		b = pos + glm::vec3(0.0f, 0.0f, -1.0f);
	}
	
	glm::vec3 gett() { return t; }
	glm::vec3 getl() { return l; }
	glm::vec3 getr() { return r; }
	glm::vec3 getb() { return b; }
	

private:
	float m_radius;
	glm::vec3 t;
	glm::vec3 l;
	glm::vec3 r;
	glm::vec3 b;
};

