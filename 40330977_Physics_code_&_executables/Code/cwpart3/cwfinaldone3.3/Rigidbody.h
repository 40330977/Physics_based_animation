#pragma once
#include "Body.h"
//#include "Mesh.h"
class Rigidbody :
	public Body
{
public:
	Rigidbody();
	~Rigidbody();

	glm::vec3 impulse(float e,  glm::vec3 & normal,  glm::vec3 & totalverts, bool a, glm::vec3 &pos);

	glm::vec3 jr(float e, glm::vec3 & normal, glm::vec3 & totalverts);

	void scale(const glm::vec3 & vect);

	glm::vec3 instimp(glm::vec3 & totalverts, bool a, glm::vec3 j);

	glm::vec3 instimp1(glm::vec3 & totalverts, bool a, glm::vec3 j);

	//set and get methods
	void setAngVel(const glm::vec3 &omega) { m_angVel = omega; }
	void setAngAccl(const glm::vec3 &alpha) { m_angAccl = alpha; }
	void setInvInertia(const glm::mat3 &invInertia) { m_invInertia = invInertia; }

	glm::vec3 getAngVel() { return m_angVel; }
	glm::vec3 getAngAcc() { return m_angAccl; }
	glm::mat3 getInvInertia() { return m_invInertia; }
	//void scale(glm::vec3 vect);

private:
	float m_density;
	glm::mat3 m_invInertia;
	glm::vec3 m_angVel;
	glm::vec3 m_angAccl;
	
};

