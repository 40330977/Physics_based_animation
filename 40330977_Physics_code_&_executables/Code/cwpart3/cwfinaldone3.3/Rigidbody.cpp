#include "Rigidbody.h"



Rigidbody::Rigidbody()
{
}


Rigidbody::~Rigidbody()
{
}

glm::vec3 Rigidbody::impulse(float e,  glm::vec3 &normal,   glm::vec3 &totalverts, bool a, glm::vec3 &pos) {
	glm::vec3 r1 = totalverts - getPos();
	
	float invmass = 1.0f / getMass();
	glm::vec3 r1xn = glm::cross(r1, normal);
	glm::vec3 ir1xn = getInvInertia() * r1xn;
	glm::vec3 ir1xnxr1 = glm::cross(ir1xn, r1);
	float matmap = glm::dot(normal, ir1xnxr1);
	float bottom = invmass + matmap;
	glm::vec3 vr = getVel() + glm::cross(getAngVel(), r1);
	float top = -1.0f*((1.0f + e)*glm::dot(vr, normal));
	float jr = top / bottom;
	//jr *= 1.0f;
	glm::vec3 vel = (jr / getMass())*normal;
	//vel *= glm::vec3(1.2f, 1.2f, 1.2f);
	
	
	glm::vec3 angvel = jr * getInvInertia()*(glm::cross(r1, normal));
	//angvel *= glm::vec3(1.2f, 1.2f, 1.2f);
	
	if (a == false) 
	{
		std::cout << "imp vel" << std::endl;
		std::cout << glm::to_string(vel) << std::endl;
		return vel;
	}
	else { 
		std::cout << "imp ang vel" << std::endl;
		std::cout << glm::to_string(angvel) << std::endl;
		return angvel; }

	//return jr;
}

glm::vec3 Rigidbody::jr(float e, glm::vec3 &normal, glm::vec3 &totalverts) {
	//glm::vec3 r1 = glm::mat3(getmesh().getModel())*totalverts - getPos();
	glm::vec3 r1 = totalverts - getPos();
	float invmass = 1 / getMass();
	glm::vec3 r1xn = glm::cross(r1, normal);
	glm::vec3 ir1xn = getInvInertia() * r1xn;
	glm::vec3 ir1xnxr1 = glm::cross(ir1xn, r1);
	float matmap = glm::dot(ir1xnxr1, normal);
	float bottom = invmass + matmap;
	glm::vec3 top = -(1 + e)*(getVel()* normal);
	glm::vec3 jr = top / bottom;
	/*glm::vec3 vel = (jr / getMass())*normal;
	glm::vec3 angvel = jr * getInvInertia()*(glm::cross(r1, normal));
	if (a == false)
	{
		return vel;
	}
	else { return angvel; }*/

	return jr;
}

void Rigidbody::scale(const glm::vec3 &vect) {
	getmesh().scale(vect);
	glm::mat4 translator = getScale();
	float width = translator[0][0] * 2.0f;
	float height = translator[1][1] * 2.0f;
	float depth = translator[2][2] * 2.0f;
	glm::mat3 Inertia = glm::mat3(1.0);
	Inertia[0][0] = (1.0f / 12.0f) * getMass() * (height*height + depth * depth);
	Inertia[1][1] = (1.0f / 12.0f) * getMass()* (width*width + depth * depth);
	Inertia[2][2] = (1.0f / 12.0f) * getMass()* (width*width + height * height);
	glm::mat3 invinn1 = glm::inverse(Inertia);
	setInvInertia(invinn1);
}

glm::vec3 Rigidbody::instimp(glm::vec3 &totalverts, bool a, glm::vec3 j) {
	glm::vec3 r1 = glm::mat3(getmesh().getModel())*totalverts - getPos();
	//glm::vec3 vel = getVel() + j / getMass();
	glm::vec3 vel = glm::vec3(j / getMass());
	//glm::vec3 angvel = getAngVel() + getInvInertia()*(glm::cross(r1, j));
	glm::vec3 angvel = getInvInertia()*(glm::cross(r1, j));
	//glm::vec3 angvel = angvel + getInvInertia()*(r1*j);
	std::cout << "impvel" << std::endl;
	std::cout << glm::to_string(vel) << std::endl;
	std::cout << "impangvel" << std::endl;
	std::cout << glm::to_string(angvel) << std::endl;
	if (a == false)
	{
		return vel;
	}
	else { return angvel; }
}

glm::vec3 Rigidbody::instimp1(glm::vec3 &totalverts, bool a, glm::vec3 j) {
	//glm::vec3 r1 = glm::mat3(getmesh().getModel())*totalverts - getPos();
	glm::vec3 r1 = glm::vec3(totalverts - getPos());
	//glm::vec3 vel = getVel() + j / getMass();
	glm::vec3 vel = glm::vec3(j / getMass())*glm::vec3(0.0f,1.0f,0.0f);
	//glm::vec3 angvel = getAngVel() + getInvInertia()*(glm::cross(r1, j));
	glm::vec3 angvel = j*getInvInertia()*(glm::cross(r1, glm::vec3(0.0f,1.0f,0.0f)));
	//glm::vec3 angvel = angvel + getInvInertia()*(r1*j);
	std::cout << "impvel" << std::endl;
	std::cout << glm::to_string(vel) << std::endl;
	std::cout << "impangvel" << std::endl;
	std::cout << glm::to_string(angvel) << std::endl;
	if (a == false)
	{
		return vel;
	}
	else { return angvel; }
}