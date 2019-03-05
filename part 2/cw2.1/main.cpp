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
#include "Particle.h"


// time
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
double t = 0.0f;
const double dt = 0.01f;

Gravity g = Gravity(glm::vec3(0.0f, -9.8f, 0.0f));
//Hooke h = new Hooke()

float particlenum = 10;

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
	plane.scale(glm::vec3(5.0f, 5.0f, 5.0f));
	Shader lambert = Shader("resources/shaders/physics.vert", "resources/shaders/physics.frag");
	plane.setShader(lambert);

	std::vector<Particle> ParticleHolder(particlenum);
	Shader color = Shader("resources/shaders/solid.vert", "resources/shaders/solid_blue.frag");
	glm::vec3 translator = glm::vec3(0.0f, 16.0f, 0.0f);
	for (unsigned int i = 0; i < particlenum; i++) {
		ParticleHolder.push_back(Particle::Particle());
		ParticleHolder[i].getmesh().setShader(color);
		translator = translator - glm::vec3(1.0f, 0.0f, 0.0f);
		ParticleHolder[i].translate(translator);

	}
	Particle particlef = Particle();
	particlef.translate(glm::vec3(-10.0f, 16.0f, 0.0f));
	particlef.getmesh().setShader(Shader("resources/shaders/solid.vert", "resources/shaders/solid_blue.frag"));
	// create particle
	
	
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

	

	

	
	for (unsigned int z1 = 1; z1 < particlenum - 1; z1++) {
		
		Hooke* h = new Hooke(&ParticleHolder[z1], &ParticleHolder[z1 + 1], ks, kd, rest);
		Hooke* h1 = new Hooke(&ParticleHolder[z1], &ParticleHolder[z1 - 1], ks, kd, rest);
		ParticleHolder[z1].addForce(&g);
		ParticleHolder[z1].addForce(h);
		ParticleHolder[z1].addForce(h1);
	}
	
	
	


	// Game loop
	while (!glfwWindowShouldClose(app.getWindow()))
	{
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
			for (unsigned int q = 0; q < particlenum; q++) {
				
					ParticleHolder[q].setAcc(ParticleHolder[q].applyForces(ParticleHolder[q].getPos(), ParticleHolder[q].getVel(), t, dt));
				
			}

			

			
			// integrate

			for (unsigned int j = 0; j < particlenum; j++) {
				vel = ParticleHolder[j].getVel();
				vel = vel + dt * ParticleHolder[j].getAcc();
				//vel *= 1.0f;
				ParticleHolder[j].setVel(vel);
				pos = ParticleHolder[j].getPos();
				pos = pos + dt * ParticleHolder[j].getVel();
				ParticleHolder[j].setPos(pos);
			}
			


			// collision detection
			//p1y = particle1.getPos();


			/*if (p1y[1] <= 0.0f || p1y[1] >= h)
			{
				vel *= glm::vec3(0.95f, -0.95f, 0.95f);
				particle1.setPos(glm::vec3(0.0f, 0.0f, 0.0f));
				particle1.setVel(vel);
			}
			else if (p1y[0] <= -1.0f || p1y[0] >= 1.0f)
			{
				vel *= glm::vec3(-0.95f, 0.95f, 0.95f);
				particle1.setVel(vel);
			}
			else if (p1y[2] <= -1.0f || p1y[2] >= 1.0f)
			{
				vel *= glm::vec3(0.95f, 0.95f, -0.95f);
				particle1.setVel(vel);
			}*/
			accumulator -= dt;
			t += dt;
		}

		//particle1.translate(deltaTime*particle1.getVel());
		//particle1.translate(dt*particle1.getVel());
		//particle3.translate(dt*particle3.getVel());
		//particle4.translate(dt*particle4.getVel());
		for (unsigned int w = 0; w < particlenum; w++) {
			//if (w != 0 || w != 9) {
				ParticleHolder[w].translate(dt*ParticleHolder[w].getVel());
			//}
		}
		

		/*
		**	RENDER 
		*/		
		// clear buffer
		app.clear();
		// draw groud plane
		app.draw(plane);
		// draw particles
		for (unsigned int k = 0; k < particlenum; k++) {
			app.draw(ParticleHolder[k].getmesh());
		}
		/*app.draw(ParticleHolder[0].getmesh());
		app.draw(ParticleHolder[1].getmesh());
		app.draw(ParticleHolder[2].getmesh());
		app.draw(ParticleHolder[3].getmesh());*/
		app.draw(particlef.getmesh());
		

		// draw demo objects
		//app.draw(cube);
		//app.draw(sphere);

		app.display();
	}

	app.terminate();

	return EXIT_SUCCESS;
}

