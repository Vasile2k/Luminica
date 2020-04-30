#include <iostream>
#include <windows.h>
#include "EntryPoint.hpp"

#define STB_IMAGE_IMPLEMENTATION
#pragma warning(push)
#pragma warning(disable:6011)
#pragma warning(disable:6262)
#pragma warning(disable:6308)
#pragma warning(disable:26451)
#pragma warning(disable:28128)
#pragma warning(disable:28182)
#include "stb_image.h"
#pragma warning(pop)
#undef STB_IMAGE_IMPLEMENTATION

#define GLEW_STATIC
#include <GL/glew.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

void error_callback(int error, const char* description) {
	fprintf(stderr, "Error %d: %s\n", error, description);
}

entry_point {

    stbi_set_flip_vertically_on_load(false);

    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) {
        return -1;
    }

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* w = glfwCreateWindow(640, 480, "cacauo", NULL, NULL);

    glfwMakeContextCurrent(w);

    GLint err;
    if ((err = glewInit()) != GLEW_OK) {
		/* Problem: glewInit failed, something is seriously wrong. */
		std::cerr << glewGetErrorString(err);
        return -1;
    }

    while (!glfwWindowShouldClose(w)) {
        glfwPollEvents();
    }

    std::cout << "Cal" << std::endl;
    return 0;
}
