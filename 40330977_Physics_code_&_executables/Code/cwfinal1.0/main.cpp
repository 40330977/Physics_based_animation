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
#include <random>

// project includes
#include "Application.h"
#include "Shader.h"
#include "Mesh.h"
#include "Particle.h"
#include "Rigidbody.h"
#include "Sphere.h"
//#include "mesh.cpp"

#include <iostream>

//Roderick Ewles
//40330977
//19/12/2018

// time
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
double t = 0.0f;
const double dt = 0.01f;

Gravity g = Gravity(glm::vec3(0.0f, -9.8f, 0.0f));
//Hooke h = new Hooke()

const int particlenum = 20;
float total = 100;

// main function
int main()
{
	// create application
	Application app = Application::Application();
	app.initRender();
	Application::camera.setCameraPosition(glm::vec3(0.0f, 5.0f, 20.0f));
			
	// create ground plane
	Mesh plane = Mesh::Mesh(Mesh::QUAD);
	// scale it up x5
	plane.scale(glm::vec3(15.0f, 5.0f, 15.0f));
	Shader lambert = Shader("resources/shaders/physics.vert", "resources/shaders/physicsgreen.frag");
	plane.setShader(lambert);

	
	

	

	std::vector<Sphere> sphereholder;
	sphereholder.resize(particlenum);
	Mesh m = Mesh::Mesh("resources/models/sphere.obj");
	Shader rsphShader = Shader("resources/shaders/physics.vert", "resources/shaders/physicsred.frag");
	Shader ysphShader = Shader("resources/shaders/physics.vert", "resources/shaders/physicsyellow.frag");
	float j = 0.0f;
	for (unsigned int i = 0; i < particlenum; i++) {
		
		sphereholder.push_back(Sphere::Sphere());
		sphereholder[i].setMesh(m);
		if (i < particlenum/2) {
			sphereholder[i].getmesh().setShader(rsphShader);
		}
		else{ sphereholder[i].getmesh().setShader(ysphShader); }
		sphereholder[i].scale(0.5f);
		sphereholder[i].setMass(1.0f);
		sphereholder[i].translate(glm::vec3(0.0f, 1.0f, j));
		j = j + 1.0f;
	}

	
	
	// create demo objects (a cube and a sphere)
	Mesh sphere = Mesh::Mesh("resources/models/sphere.obj");
	sphere.translate(glm::vec3(-1.0f, 1.0f, 0.0f));
	sphere.setShader(lambert);
	Mesh cube = Mesh::Mesh("resources/models/cube.obj");
	cube.translate(glm::vec3(1.0f, .5f, 0.0f));
	cube.setShader(lambert);

	// time
	GLfloat firstFrame = (GLfloat) glfwGetTime();
	double currentTime = glfwGetTime();
	double accumulator = 0.0;
	//float m = 1.0f;
	glm::vec3 vel = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 vel1 = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 vel2 = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
	//glm::vec3 pos3 = glm::vec3(0.0f, 12.0f, 0.0f);
	//glm::vec3 pos4 = glm::vec3(0.0f, 10.0f, 0.0f);
	glm::vec3 p1y;
	float h = 5.0f;
	glm::vec3 fd = glm::vec3(0.99f, 0.99f, 0.99f);
	glm::vec3 wind = glm::vec3(-1.0f, 0.0f, -1.0f);
	float ks = 10.0;
	float kd = 20.0;
	float rest = 1.0;
	float ks3 = 100.0;
	float kd3 = 10.0;
	float rest3 = 1.0;
	float ks4 = 1.0;
	float kd4 = 1.0;
	float rest4 = 2.0;

	float e = 0.7f;
	glm::vec3 cuspos;
	
	std::random_device posex;
	std::mt19937 gen(posex());
	std::uniform_real_distribution<> dis(-15, 15);
	std::random_device posez;
	std::mt19937 gen1(posez());
	

	for (int n = 0; n < particlenum; ++n) {
		sphereholder[n].setPos(glm::vec3(dis(posex), 0.5f, dis(posez)));
	}

	std::random_device ranvelx;
	std::mt19937 gen2(ranvelx());
	std::uniform_real_distribution<> dis1(-20, 20);
	std::random_device ranvelz;
	std::mt19937 gen3(ranvelz());

	for (int n = 0; n < particlenum; ++n) {
		sphereholder[n].setVel(glm::vec3(dis1(ranvelx), 0.0f, dis1(ranvelz)));
	}
	


	// Game loop
	while (!glfwWindowShouldClose(app.getWindow()))
	{
		//vertcols.clear();
		// Set frame time
		GLfloat currentFrame = (GLfloat)  glfwGetTime() - firstFrame;
		// the animation can be sped up or slowed down by multiplying currentFrame by a factor.
		currentFrame *= 1.0f;
		double newTime = glfwGetTime();
		double frametime = newTime - currentTime;
		//frametime *= 2.5;
		currentTime = newTime;
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		accumulator += frametime;
		float tv = 0.0f;
		float tvd = 0.0f;
		/*
		**	INTERACTION
		*/
		// Manage interaction
		//app.doMovement(deltaTime);
		app.doMovement(dt);
		
		/*
		**	SIMULATION
		*/
		while (accumulator >= dt)
		{
			
			// apply forces
			
			

			glm::vec3 pos1 = glm::vec3(0.0f,0.0f,0.0f);
			glm::vec3 pos2 = glm::vec3(0.0f,0.0f,0.0f);

			for (unsigned int j = 0; j < particlenum; j++) {
				pos = sphereholder[j].getPos();
				pos = pos + dt * sphereholder[j].getVel();
				sphereholder[j].setPos(pos);
			}

			

			for (int i = 0; i < particlenum; i++) {
				for (int j = 0; j < particlenum; j++) {
					if (i != j) {
						if (sphereholder[i].TestSphere(sphereholder[j]) == true) {
							std::cout << "collision! " << std::endl;
							glm::vec3 d = sphereholder[i].getPos() - sphereholder[j].getPos();
							float dist2 = glm::dot(d, d);
							float difference = 2.0f*sphereholder[i].getradius() - dist2;
							glm::vec3 anorm = sphereholder[j].getPos() - sphereholder[i].getPos();
							anorm = glm::normalize(anorm);
							sphereholder[i].setPos(sphereholder[i].getPos() - (difference*anorm)/2.0f);
							sphereholder[j].setPos(sphereholder[j].getPos() + (difference*anorm)/2.0f);
							std::cout << "pos " << glm::to_string(sphereholder[i].getPos());
							std::cout << "prevel " << glm::to_string(sphereholder[i].getVel());
							float s1 = glm::dot(sphereholder[i].getVel(), anorm);
							float s2 = glm::dot(sphereholder[j].getVel(), anorm);
							float op = (2.0f*(s1-s2)) / (sphereholder[i].getMass() + sphereholder[j].getMass());
							glm::vec3 newvel1 = sphereholder[i].getVel() - op * sphereholder[j].getMass() * anorm;
							glm::vec3 newvel2 = sphereholder[j].getVel() + op * sphereholder[i].getMass() * anorm;
							sphereholder[i].setVel(newvel1*0.9f);
							sphereholder[j].setVel(newvel2*0.9f);
							std::cout << "postvel " << glm::to_string(sphereholder[i].getVel());
						}
					}
				}
			}

			for (auto &s: sphereholder) {
				pos = s.getPos();
				if (pos[0] <= -15.0f || pos[0] >= 15.0f) {
					vel1 = s.getVel();
					vel1 *= glm::vec3(-1.0f, 1.0f, 1.0f);
					s.setVel(vel1);
				}
				if (pos[2] <= -15.0f || pos[2] >= 15.0f) {
					vel1 = s.getVel();
					vel1 *= glm::vec3(1.0f, 1.0f, -1.0f);
					s.setVel(vel1);
				}
			}

	

			tv = 0.0f;
			tvd = 0.0f;


			accumulator -= dt;
			t += dt;
		}

		
		/*
		**	RENDER 
		*/		
		// clear buffer
		app.clear();
		// draw groud plane
		app.draw(plane);
		//app.draw(s1.getmesh());
		for (unsigned int k = 0; k < particlenum; k++) {
			app.draw(sphereholder[k].getmesh());
		}
		

		app.display();
	}


	app.terminate();

	return EXIT_SUCCESS;
}



