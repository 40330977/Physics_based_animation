#include "Sphere.h"



Sphere::Sphere()
{
}


Sphere::~Sphere()
{
}

void Sphere :: scale(const float &scaler) {
	glm::vec3 scaley = glm::vec3(scaler, scaler, scaler);
	getmesh().scale(scaley);
	setradius(scaler);
	
}

float Sphere::TestSphere(Sphere b) {
	glm::vec3 d = getPos() - b.getPos();
	float dist2 = glm::dot(d, d);
	float radSum = getradius() + b.getradius();
	return dist2 <= radSum * radSum;
}

void Sphere::Sleep(bool s) {
	if(s == true){
		setAngAccl(glm::vec3(0.0f, 0.0f, 0.0f));
		setAngVel(glm::vec3(0.0f, 0.0f, 0.0f));
		setVel(glm::vec3(0.0f, 0.0f, 0.0f));
	}
	if (s == false) {
		setAngAccl(getAngAcc());
		setAngVel(getAngVel());
		setVel(getVel());
	}
}
