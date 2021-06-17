#pragma once
#include <iostream>

#include <GLFW\glfw3.h>



void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

//key callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void window_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

