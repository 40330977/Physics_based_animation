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
