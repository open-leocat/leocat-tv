#pragma once

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>

namespace Plutonium {
	const char enginename[] = "Plutonium 1.0";
	
	void APIENTRY onError(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message, const void *userParam) {
		if(id == 131169 || id == 131185 || id == 131218 || id == 131204) {
			return;
		}
		
		switch(severity) {
			case GL_DEBUG_SEVERITY_HIGH: std::cout << "[Fatal Error] (" << id << "): " <<  message << std::endl;
			case GL_DEBUG_SEVERITY_MEDIUM: std::cout << "[Error] (" << id << "): " <<  message << std::endl;
			case GL_DEBUG_SEVERITY_LOW: std::cout << "[Warning] (" << id << "): " <<  message << std::endl;
			case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "[Notification] (" << id << "): " <<  message << std::endl;
		}
	}
	
	void onResize(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}
	
	struct Renderer {
		
		void clear() {
			glClear(GL_COLOR_BUFFER_BIT);
		}
		
	};
	
	struct Engine {
		
		int initEngine(void (*_init)(void), void (*_update)(void), void (*_render)(void)) {
			std::cout << "Starting " << enginename << "..." << std::endl;
			
			glfwWindowHint(GLFW_SAMPLES, 4); //4x antialiasing
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			
			GLFWwindow* window;
			
			if (!glfwInit()) {
				std::cout << "Couldn't initialize GLFW!" << std::endl;
				return -1;
			}
			
			window = glfwCreateWindow(640, 480, enginename, NULL, NULL);
			if (!window) {
				std::cout << "Couldn't initialize the window!" << std::endl;
				glfwTerminate();
				return -1;
			}
			
			glfwMakeContextCurrent(window);
			gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
			glfwSwapInterval(1);
			
			glfwSetWindowSizeCallback(window, onResize);
			
			if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
				std::cout << "Couldn't initialize GLAD!" << std::endl;
				return -1;
			}
			
			std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "." << std::endl;
			std::cout << "Succesfully initialized GLFW version: " << glfwGetVersionString() << "." << std::endl;
			
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(onError, nullptr);
			
			_init();
			
			while(!glfwWindowShouldClose(window)) {
				
				_update();
				_render();
				
				glfwSwapBuffers(window);
				glfwPollEvents();
			}
			
			glfwTerminate();
			
			return 0;
		}
		
	};
}