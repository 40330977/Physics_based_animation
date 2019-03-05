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

#include <iostream>


// time
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
double t = 0.0f;
const double dt = 0.01f;

Gravity g = Gravity(glm::vec3(0.0f, -9.8f, 0.0f));
//Hooke h = new Hooke()

float particlenum = 10;
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
	plane.scale(glm::vec3(5.0f, 5.0f, 5.0f));
	Shader lambert = Shader("resources/shaders/physics.vert", "resources/shaders/physics.frag");
	plane.setShader(lambert);

	std::vector<std::vector<Particle>> ParticleHolder;
	ParticleHolder.resize(particlenum);
	for (unsigned int k = 0; k < particlenum; k++) {
		ParticleHolder[k].resize(particlenum);
	}
	
	Shader color = Shader("resources/shaders/solid.vert", "resources/shaders/solid_blue.frag");
	glm::vec3 translator = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 translator1 = glm::vec3(0.0f, 1.0f, 1.0f);
	glm::vec3 translator2 = glm::vec3(0.0f, 1.0f, 2.0f);
	glm::vec3 translator3 = glm::vec3(0.0f, 1.0f, 3.0f);
	glm::vec3 translator4 = glm::vec3(0.0f, 1.0f, 4.0f);
	glm::vec3 translator5 = glm::vec3(0.0f, 1.0f, 5.0f);
	glm::vec3 translator6 = glm::vec3(0.0f, 1.0f, 6.0f);
	glm::vec3 translator7 = glm::vec3(0.0f, 1.0f, 7.0f);
	glm::vec3 translator8 = glm::vec3(0.0f, 1.0f, 8.0f);
	glm::vec3 translator9 = glm::vec3(0.0f, 1.0f, 9.0f);

	for (unsigned int i = 0; i < particlenum; i++) {
		
		for (unsigned int j = 0; j < particlenum; j++) {
			
			//Particle* new_particle = new Particle();
			ParticleHolder[i].push_back(Particle::Particle());
			//ParticleHolder[i][j] = *new_particle;
			ParticleHolder[i][j].getmesh().setShader(color);
			if (i ==0) {
				translator = translator - glm::vec3(1.0f, 0.0f, 0.0f);
				ParticleHolder[i][j].translate(translator);
			}
			if (i == 1) {
				translator1 = translator1 - glm::vec3(1.0f, 0.0f, 0.0f);
				ParticleHolder[i][j].translate(translator1);
			}
			if (i == 2) {
				translator2 = translator2 - glm::vec3(1.0f, 0.0f, 0.0f);
				ParticleHolder[i][j].translate(translator2);
			}
			if (i == 3) {
				translator3 = translator3 - glm::vec3(1.0f, 0.0f, 0.0f);
				ParticleHolder[i][j].translate(translator3);
			}
			if (i == 4) {
				translator4 = translator4 - glm::vec3(1.0f, 0.0f, 0.0f);
				ParticleHolder[i][j].translate(translator4);
			}
			if (i == 5) {
				translator5 = translator5 - glm::vec3(1.0f, 0.0f, 0.0f);
				ParticleHolder[i][j].translate(translator5);
			}
			if (i == 6) {
				translator6 = translator6 - glm::vec3(1.0f, 0.0f, 0.0f);
				ParticleHolder[i][j].translate(translator6);
			}
			if (i == 7) {
				translator7 = translator7 - glm::vec3(1.0f, 0.0f, 0.0f);
				ParticleHolder[i][j].translate(translator7);
			}
			if (i == 8) {
				translator8 = translator8 - glm::vec3(1.0f, 0.0f, 0.0f);
				ParticleHolder[i][j].translate(translator8);
			}
			if (i == 9) {
				translator9 = translator9 - glm::vec3(1.0f, 0.0f, 0.0f);
				ParticleHolder[i][j].translate(translator9);
			}
			
			
		}
		
		
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

	

	

	for (unsigned int r = 1; r < particlenum-1; r++) {
		for (unsigned int c = 1; c < particlenum-1; c++) {
			if ((r != 0 || r != 9) && (c != 0 || c != 9)) {
				std::cout << ParticleHolder.size() << " " << ParticleHolder[0].size() << " " << r << " " << c << std::endl;
				Hooke* h = new Hooke(&ParticleHolder[r][c], &ParticleHolder[r][c+1], ks, kd, rest);
				ParticleHolder[r][c].addForce(h);
				Hooke* h1 = new Hooke(&ParticleHolder[r][c], &ParticleHolder[r][c - 1], ks, kd, rest);
				ParticleHolder[r][c].addForce(h1);
				Hooke* h2 = new Hooke(&ParticleHolder[r][c], &ParticleHolder[r+1][c], ks, kd, rest);
				ParticleHolder[r][c].addForce(h2);
				Hooke* h3 = new Hooke(&ParticleHolder[r][c], &ParticleHolder[r - 1][c], ks, kd, rest);
				ParticleHolder[r][c].addForce(h3);
				ParticleHolder[r][c].addForce(&g);
			}
		}
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
				for (unsigned int p = 0; p < particlenum; p++) {
					
						ParticleHolder[q][p].setAcc(ParticleHolder[q][p].applyForces(ParticleHolder[q][p].getPos(), ParticleHolder[q][p].getVel(), t, dt));
					
				}
			}

			

			
			// integrate

			for (unsigned int j = 0; j < particlenum; j++) {
				for (unsigned int k = 0; k < particlenum; k++) {
					vel = ParticleHolder[j][k].getVel();
					vel = vel + dt * ParticleHolder[j][k].getAcc();
					//vel *= 1.0f;
					ParticleHolder[j][k].setVel(vel);
					pos = ParticleHolder[j][k].getPos();


					// collision detection
					/*if (pos[1] <= 0.0f || p1y[1] >= h)
					{
						vel *= glm::vec3(0.95f, -0.95f, 0.95f);
						//ParticleHolder[x].setPos(glm::vec3(0.0f, 0.0f, 0.0f));
						//ParticleHolder[x].setPos(p1y * glm::vec3(1.0f,0.0f,1.0f));
						ParticleHolder[j][k].setVel(vel);
					}*/

					pos = pos + dt * ParticleHolder[j][k].getVel();
					ParticleHolder[j][k].setPos(pos);
				}
			}
			


			
			
			
			accumulator -= dt;
			t += dt;
		}

		
		/*
		**	RENDER 
		*/		
		// clear buffer
		app.clear();
		// draw groud plane
		//app.draw(plane);
		// draw particles
		for(unsigned int j=0; j<particlenum; j++)
		for (unsigned int k = 0; k < particlenum; k++) {
			app.draw(ParticleHolder[j][k].getmesh());
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

