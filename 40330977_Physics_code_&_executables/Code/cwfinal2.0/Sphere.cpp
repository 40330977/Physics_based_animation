#include "Sphere.h"
#include "cell.h"




Sphere::Sphere()
{
}


Sphere::~Sphere()
{
}

int column;
int row;


void Sphere :: scale(const float &scaler) {
	glm::vec3 scaley = glm::vec3(scaler, scaler, scaler);
	getmesh().scale(scaley);
	setradius(scaler);
	
}

//glm::vec3 Sphere::TestSphere(Sphere b) {
float Sphere::TestSphere(Sphere b) {
	glm::vec3 d = getPos() - b.getPos();
	float dist2 = glm::dot(d, d);
	float radSum = getradius() + b.getradius();
	//if (dist2 <= radSum * radSum) {
	//	return dist2;
	//	//return d;
	//	
	//}
	//else { return 0.0f; }
	return dist2 <= radSum * radSum;
}

int Sphere::celltestcol(const glm::vec3 &bound) {
	
	
	if (bound[0] > -510.0f && bound[0] <= -450.0f) {
		column = 0;
	}
	if (bound[0] > -450.0f && bound[0] <= -400.0f) {
		column = 1;
	}
	if (bound[0] > -400.0f && bound[0] <= -350.0f) {
		column = 2;
	}
	if (bound[0] > -350.0f && bound[0] <= -300.0f) {
		column = 3;
	}
	if (bound[0] > -300.0f && bound[0] <= -250.0f) {
		column = 4;
	}
	if (bound[0] > -250.0f && bound[0] <= -200.0f) {
		column = 5;
	}
	if (bound[0] > -200.0f && bound[0] <= -150.0f) {
		column = 6;
	}
	if (bound[0] > -150.0f && bound[0] <= -100.0f) {
		column = 7;
	}
	if (bound[0] > -100.0f && bound[0] <= -50.0f) {
		column = 8;
	}
	if (bound[0] > -50.0f && bound[0] <= 0.0f) {
		column = 9;
	}
	if (bound[0] > 0.0f && bound[0] <= 50.0f) {
		column = 10;
	}
	if (bound[0] > 50.0f && bound[0] <= 100.0f) {
		column = 11;
	}
	if (bound[0] > 100.0f && bound[0] <= 150.0f) {
		column = 12;
	}
	if (bound[0] > 150.0f && bound[0] <= 200.0f) {
		column = 13;
	}
	if (bound[0] > 200.0f && bound[0] <= 250.0f) {
		column = 14;
	}
	if (bound[0] > 250.0f && bound[0] <= 300.0f) {
		column = 15;
	}
	if (bound[0] > 300.0f && bound[0] <= 350.0f) {
		column = 16;
	}
	if (bound[0] > 350.0f && bound[0] <= 400.0f) {
		column = 17;
	}
	if (bound[0] > 400.0f && bound[0] <= 450.0f) {
		column = 18;
	}
	if (bound[0] > 450.0f && bound[0] <= 510.0f) {
		column = 19;
	}

	return column;
	
}

int Sphere::celltestrow(const glm::vec3 &bound) {
	

	if (bound[2] > -510.0f && bound[2] <= -450.0f) {
		row = 0;
	}
	if (bound[2] > -450.0f && bound[2] <= -400.0f) {
		row = 1;
	}
	if (bound[2] > -400.0f && bound[2] <= -350.0f) {
		row = 2;
	}
	if (bound[2] > -350.0f && bound[2] <= -300.0f) {
		row = 3;
	}
	if (bound[2] > -300.0f && bound[2] <= -250.0f) {
		row = 4;
	}
	if (bound[2] > -250.0f && bound[2] <= -200.0f) {
		row = 5;
	}
	if (bound[2] > -200.0f && bound[2] <= -150.0f) {
		row = 6;
	}
	if (bound[2] > -150.0f && bound[2] <= -100.0f) {
		row = 7;
	}
	if (bound[2] > -100.0f && bound[2] <= -50.0f) {
		row = 8;
	}
	if (bound[2] > -50.0f && bound[2] <= 0.0f) {
		row = 9;
	}
	if (bound[2] > 0.0f && bound[2] <= 50.0f) {
		row = 10;
	}
	if (bound[2] > 50.0f && bound[2] <= 100.0f) {
		row = 11;
	}
	if (bound[2] > 100.0f && bound[2] <= 150.0f) {
		row = 12;
	}
	if (bound[2] > 150.0f && bound[2] <= 200.0f) {
		row = 13;
	}
	if (bound[2] > 200.0f && bound[2] <= 250.0f) {
		row = 14;
	}
	if (bound[2] > 250.0f && bound[2] <= 300.0f) {
		row = 15;
	}
	if (bound[2] > 300.0f && bound[2] <= 350.0f) {
		row = 16;
	}
	if (bound[2] > 350.0f && bound[2] <= 400.0f) {
		row = 17;
	}
	if (bound[2] > 400.0f && bound[2] <= 450.0f) {
		row = 18;
	}
	if (bound[2] > 450.0f && bound[2] <= 510.0f) {
		row = 19;
	}

	return row;
}
