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


	// create particle
	//Mesh particle1 = Mesh::Mesh(Mesh::QUAD);
	Particle particle0 = Particle();
	Particle particle1 = Particle();
	Particle particle2 = Particle();
	//scale it down (x.1), translate it up by 2.5 and rotate it by 90 degrees around the x axis
	particle0.translate(glm::vec3(0.0f, 2.5f, 0.0f));
	particle1.translate(glm::vec3(1.0f, 2.5f, 0.0f));
	particle2.translate(glm::vec3(2.0f, 2.5f, 0.0f));
	//particle1.scale(glm::vec3(.1f, .1f, .1f));
	//particle1.rotate((GLfloat) M_PI_2, glm::vec3(1.0f, 0.0f, 0.0f));
	particle0.getmesh().setShader(Shader("resources/shaders/solid.vert", "resources/shaders/solid_blue.frag"));
	particle1.getmesh().setShader(Shader("resources/shaders/solid.vert", "resources/shaders/solid_blue.frag"));
	particle2.getmesh().setShader(Shader("resources/shaders/solid.vert", "resources/shaders/solid_blue.frag"));
	
	// create demo objects (a cube and a sphere)
	Mesh sphere = Mesh::Mesh("resources/models/sphere.obj");
	sphere.translate(glm::vec3(-1.0f, 1.0f, 0.0f));
	sphere.setShader(lambert);
	Mesh cube = Mesh::Mesh("resources/models/cube.obj");
	cube.translate(glm::vec3(1.0f, .5f, 0.0f));
	cube.setShader(lambert);

	// time
	GLfloat firstFrame = (GLfloat) glfwGetTime();
	glm::vec3 g = glm::vec3(0.0f, -9.8f, 0.0f);
	//float m = 1.0f;
	glm::vec3 vel = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 vel1 = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 p1y;
	glm::vec3 p2y;
	float h = 2.6f;
	glm::vec3 fd = glm::vec3(0.95f, 0.95f, 0.95f);
	glm::vec3 wind = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 pos1 = particle1.getPos();
	glm::vec3 pos2 = particle2.getPos();
	// Game loop
	while (!glfwWindowShouldClose(app.getWindow()))
	{
		// Set frame time
		GLfloat currentFrame = (GLfloat)  glfwGetTime() - firstFrame;
		// the animation can be sped up or slowed down by multiplying currentFrame by a factor.
		currentFrame *= 1.5f;
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		/*
		**	INTERACTION
		*/
		// Manage interaction
		app.doMovement(deltaTime);


		/*
		**	SIMULATION
		*/
		//pos1 = pos1 + vel * deltaTime;
		//particle1.setPos(pos1);
		glm::vec3 a = (g +wind)/ particle1.getMass();
		//a *= fd;
		particle1.setAcc(a);
		vel = vel + deltaTime * a;
		particle1.setVel(vel);

		
		glm::vec3 a1 = (g + wind) / particle2.getMass();
		particle2.setAcc(a1);
		vel1 = vel1 + deltaTime * a1;
		particle2.setVel(vel1);
		pos2 = pos2 + vel1 * deltaTime;
		particle2.setPos(pos2);
		

		p1y = particle1.getPos();


		if (p1y[1] <= 0.0f || p1y[1] >= h)
		{
			vel *= glm::vec3(0.98f, -0.98f, 0.98f);
			//vel *= glm::vec3(1.0f, -1.0f, 1.0f);

			particle1.setVel(vel);
		}
		else if(p1y[0] <= -1.0f || p1y[0] >= 1.0f)
		{
			vel *= glm::vec3(-0.98f, 0.98f, 0.98f);
			//vel *= glm::vec3(-1.0f, 1.0f, 1.0f);
			particle1.setVel(vel);
		}
		else if (p1y[2] <= -1.0f || p1y[2] >= 1.0f)
		{
			vel *= glm::vec3(0.98f, 0.98f, -0.98f);
			//vel *= glm::vec3(1.0f, 1.0f, -1.0f);
			particle1.setVel(vel);
		}

		p2y = particle2.getPos();


		if (p2y[1] <= 0.0f || p2y[1] >= h)
		{
			vel1 *= glm::vec3(0.98f, -0.98f, 0.98f);
			//vel1 *= glm::vec3(1.0f, 1.0f, 1.0f);
			particle2.setVel(vel1);
		}
		else if (p2y[0] <= -1.0f || p2y[0] >= 1.0f)
		{
			vel1 *= glm::vec3(-0.98f, 0.98f, 0.98f);
			//vel1 *= glm::vec3(1.0f, 1.0f, 1.0f);
			particle2.setVel(vel1);
		}
		else if (p2y[2] <= -1.0f || p2y[2] >= 1.0f)
		{
			vel1 *= glm::vec3(0.98f, 0.98f, -0.98f);
			//vel1 *= glm::vec3(1.0f, 1.0f, 1.0f);
			particle2.setVel(vel1);
		}

		particle1.translate(deltaTime*particle1.getVel());

		/*
		**	RENDER 
		*/		
		// clear buffer
		app.clear();
		// draw groud plane
		app.draw(plane);
		// draw particles
		app.draw(particle0.getmesh());
		app.draw(particle1.getmesh());
		app.draw(particle2.getmesh());	
		

		// draw demo objects
		//app.draw(cube);
		//app.draw(sphere);

		app.display();
	}

	app.terminate();

	return EXIT_SUCCESS;
}

