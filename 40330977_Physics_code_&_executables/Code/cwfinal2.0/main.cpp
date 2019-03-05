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
#include "cell.h"
//#include "mesh.cpp"

#include <iostream>
#include <list>

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

const int particlenum = 5750;
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
	plane.scale(glm::vec3(500.0f, 5.0f, 500.0f));
	Shader lambert = Shader("resources/shaders/physics.vert", "resources/shaders/physicsgreen.frag");
	plane.setShader(lambert);
	
	int rows = 20;
	int cols = 20;
	

	cell* grid[20][20];

	for (unsigned int q = 0; q < 20; q++) {
		for (unsigned int l = 0; l < 20; l++) {
			
			cell* c = new cell();
			grid[q][l] = c;
		}
	}

	

	
	

	

	std::vector<Sphere*> sphereholder;
	Mesh m = Mesh::Mesh("resources/models/sphere2.obj");
	Shader rsphShader = Shader("resources/shaders/physics.vert", "resources/shaders/physicsred.frag");
	Shader ysphShader = Shader("resources/shaders/physics.vert", "resources/shaders/physicsyellow.frag");
	float j = 0.0f;
	for (unsigned int i = 0; i < particlenum; i++) {
		Sphere* s = new Sphere();
		s->setMesh(m);
		if (i < particlenum/2) {
			s->getmesh().setShader(rsphShader);
		}
		else{ s->getmesh().setShader(ysphShader); }
		s->scale(1.0f);
		s->setMass(1.0f);
		s->translate(glm::vec3(0.0f, 1.0f, j));
		j = j + 1.0f;
		sphereholder.push_back(s);
	}

	
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
	std::uniform_real_distribution<> dis(-499.0f, 499.0f);
	std::random_device posez;
	std::mt19937 gen1(posez());

	std::random_device posex1;
	std::mt19937 genx(posex());
	std::random_device posez1;
	std::mt19937 geny(posez());

	std::vector<int> xcheck;
	std::vector<int> zcheck;
	
	
	for (int n = 0; n < particlenum; ++n) {
		
		float xer = dis(posex);
		float zer = dis(posez);
		if (std::find(xcheck.begin(), xcheck.end(), xer) != xcheck.end() || std::find(zcheck.begin(), zcheck.end(), zer) != zcheck.end()) {
			xer += dis(posex);
			xer /= 2.0f;
			zer += dis(posez);
			zer /= 2.0f;
			xcheck.push_back(xer);
			zcheck.push_back(zer);
			sphereholder[n]->setPos(glm::vec3(xer, 1.0f, zer ));
		}
		else {
			xcheck.push_back(xer);
			zcheck.push_back(zer);
			sphereholder[n]->setPos(glm::vec3(xer , 1.0f, zer ));
		}
		
	}

	std::random_device ranvelx;
	std::mt19937 gen2(ranvelx());
	std::uniform_real_distribution<> dis1(-20, 20);
	std::random_device ranvelz;
	std::mt19937 gen3(ranvelz());

	for (int n = 0; n < particlenum; ++n) {
		sphereholder[n]->setVel(glm::vec3(dis1(ranvelx), 0.0f, dis1(ranvelz)));
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
		app.showFPS();
		/*
		**	SIMULATION
		*/
		while (accumulator >= dt)
		{
			
			


			glm::vec3 pos1 = glm::vec3(0.0f,0.0f,0.0f);
			glm::vec3 pos2 = glm::vec3(0.0f,0.0f,0.0f);

			for (unsigned int j = 0; j < particlenum; j++) {
				pos = sphereholder[j]->getPos();
				pos = pos + dt * sphereholder[j]->getVel();
				sphereholder[j]->setPos(pos);
				sphereholder[j]->setbound(sphereholder[j]->getPos());
			}

			for (unsigned int k = 0; k < 20; k++) {
				for (unsigned int l = 0; l < 20; l++) {
					grid[k][l]->clearsphere();
				}
			}

			int col;
			int row;
			int col1;
			int row1;
			int col2;
			int row2;
			int col3;
			int row3;

			for (unsigned int k = 0; k < particlenum; k++) {
				col = sphereholder[k]->celltestcol(sphereholder[k]->gett());
				row = sphereholder[k]->celltestrow(sphereholder[k]->gett());
				grid[col][row]->getlistel(sphereholder[k]);

				col1 = sphereholder[k]->celltestcol(sphereholder[k]->getb());
				row1 = sphereholder[k]->celltestrow(sphereholder[k]->getb());
				if (col == col1 && row == row1) {
					continue;
				}
				else{ grid[col1][row1]->getlistel(sphereholder[k]); }

				col2 = sphereholder[k]->celltestcol(sphereholder[k]->getl());
				row2 = sphereholder[k]->celltestrow(sphereholder[k]->getl());
				if ((col == col2 && row == row2) || (col1 == col2 && row1 == row2)) {
					continue;
				}
				else { grid[col2][row2]->getlistel(sphereholder[k]); }

				col3 = sphereholder[k]->celltestcol(sphereholder[k]->getr());
				row3 = sphereholder[k]->celltestrow(sphereholder[k]->getr());
				if ((col == col3 && row == row3) || (col1 == col3 && row1 == row3) || (col2 == col3 && row2 == row3)) {
					continue;
				}
				else { grid[col3][row3]->getlistel(sphereholder[k]); }

			}

			

			

			for (unsigned int k = 0; k < 20; k++) {
				for (unsigned int l = 0; l < 20; l++) {
					grid[k][l]->sphcoltest();
				}
			}

			


			//Collision detection flag ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

			//for (int i = 0; i < particlenum; i++) {
			//	for (int j = 0; j < particlenum; j++) {
			//		if (i != j) {
			//			if (sphereholder[i].TestSphere(sphereholder[j]) == true) {
			//				std::cout << "collision! " << std::endl;
			//				glm::vec3 d = sphereholder[i].getPos() - sphereholder[j].getPos();
			//				float dist2 = glm::dot(d, d);
			//				//float dister = d.length();
			//				float difference = 2.0f*sphereholder[i].getradius() - dist2;
			//				//float difference = dister - 2.0f*sphereholder[i].getradius();
			//				glm::vec3 anorm = sphereholder[j].getPos() - sphereholder[i].getPos();
			//				anorm = glm::normalize(anorm);
			//				//glm::vec3 bnorm = -anorm;
			//				//difference *= 0.75f;
			//				sphereholder[i].setPos(sphereholder[i].getPos() - difference*anorm);
			//				sphereholder[j].setPos(sphereholder[j].getPos() + difference*anorm);
			//				std::cout << "pos " << glm::to_string(sphereholder[i].getPos());
			//				std::cout << "prevel " << glm::to_string(sphereholder[i].getVel());
			//				float s1 = glm::dot(sphereholder[i].getVel(), anorm);
			//				float s2 = glm::dot(sphereholder[j].getVel(), anorm);
			//				float op = (2.0f*(s1-s2)) / (sphereholder[i].getMass() + sphereholder[j].getMass());
			//				glm::vec3 newvel1 = sphereholder[i].getVel() - op * sphereholder[j].getMass() * anorm;
			//				glm::vec3 newvel2 = sphereholder[j].getVel() + op * sphereholder[i].getMass() * anorm;
			//				sphereholder[i].setVel(newvel1*0.9f);
			//				sphereholder[j].setVel(newvel2*0.9f);
			//				std::cout << "postvel " << glm::to_string(sphereholder[i].getVel());
			//			}
			//		}
			//	}
			//}


			for (int a = 0; a < 20; a++) {
				for (auto &s : grid[0][a]->getlist()) {
					pos = s->getPos();
					if (pos[0] <= -500.0f) {
						vel1 = s->getVel();
						vel1 *= glm::vec3(-1.0f, 1.0f, 1.0f);
						s->setVel(vel1);
					}
				}
				for (auto &s : grid[19][a]->getlist()) {
					pos = s->getPos();
					if (pos[0] >= 500.0f) {
						vel1 = s->getVel();
						vel1 *= glm::vec3(-1.0f, 1.0f, 1.0f);
						s->setVel(vel1);
					}
				}
				for (auto &s : grid[a][0]->getlist()) {
					pos = s->getPos();
					if (pos[2] <= -500.0f) {
						vel1 = s->getVel();
						vel1 *= glm::vec3(1.0f, 1.0f, -1.0f);
						s->setVel(vel1);
					}
				}
				for (auto &s : grid[a][19]->getlist()) {
					pos = s->getPos();
					if (pos[2] >= 500.0f) {
						vel1 = s->getVel();
						vel1 *= glm::vec3(1.0f, 1.0f, -1.0f);
						s->setVel(vel1);
					}
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
			app.draw(sphereholder[k]->getmesh());
		}
		

		app.display();
	}
	

	app.terminate();

	return EXIT_SUCCESS;
}



