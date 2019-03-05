#include <iostream>
#include <cmath>
#include "Force.h"
#include "Body.h"
#include "glm/ext.hpp"

/*Force::Force()
{
}


Force::~Force()
{
}*/

glm::vec3 Force::apply(float mass, const glm::vec3 &pos, const glm::vec3 &vel) {
	return glm::vec3(0.0f);
}

/*
**GRAVITY
*/
glm::vec3 Gravity::apply(float mass, const glm::vec3 &pos, const glm::vec3 &vel) {
	//glm::vec3 a = m_gravity / mass;
	//return a;
	return m_gravity;
}

/*
**DRAG
*/
//glm::vec3 Drag::apply(float mass, const glm::vec3 &pos, const glm::vec3 &vel) {

//}

/*
**HOOKE'S LAW
*/
glm::vec3 Hooke::apply(float mass, const glm::vec3 &pos, const glm::vec3 &vel) {
	//complete
	//glm::vec3 differ = m_b1->getPos() - m_b2->getPos();
	glm::vec3 differ = m_b2->getPos() - m_b1->getPos();
	float lengthy = glm::length(differ);
	if (lengthy == 0) {
		return glm::vec3(0.0f);
	}
	else {

		glm::vec3 e = differ / lengthy;
		float v1 = glm::dot(e, m_b1->getVel());
		float v2 = glm::dot(e, m_b2->getVel());
		float fsd = -m_ks * (m_rest - lengthy) - m_kd*(v1 - v2);
		//glm::vec3 fsd = -m_ks * (differ - m_rest) - m_kd * (v1 - v2);
		glm::vec3 f1 = fsd * e;
		glm::vec3 f2 = -f1;

		//glm::vec3 a = f1 / mass;
		if (m_b1->getPos() == pos) {

			return f1;
		}
		else {
			return f2;
		}
	}

}


