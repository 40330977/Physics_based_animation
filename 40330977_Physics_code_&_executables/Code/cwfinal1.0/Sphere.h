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

	void setradius(const float &rad) { m_radius = rad; }

	float getradius() { return m_radius; }

	

private:
	float m_radius;
};

