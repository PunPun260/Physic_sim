#include <GL/gl.h>
#include <cmath>
#include <iostream>
#include <GLFW/glfw3.h>

float screenHeight = 600.0f;
float screenWidth = 800.0f;

GLFWwindow * StartGLFW();

int main () {
    GLFWwindow * window = StartGLFW();
    
    float centerX = screenWidth / 2.0f;
    float centerY = screenHeight / 2.0f;
    float radius = 50.0f;
    int res = 100; 

    while (!glfwWindowShouldClose(window)) {
	   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	   
	   glBegin(GL_TRIANGLE_FAN);
	   glVertex2d(centerX, centerY);

	   for (int i = 0; i <= res; ++i) {
		  float angle = 2.0f * M_PI * i / res;
		  float x = centerX + cos(angle) * radius;
		  float y = centerY + sin(angle) * radius;
		  glVertex2d(x, y);
	   } 

	   glEnd();


	   glfwSwapBuffers(window);
	   glfwPollEvents();
    }

    return 0;
}

GLFWwindow * StartGLFW() {
    if (!glfwInit()) {
	   std::cerr << "FAIL IT INIT GLFW D:> \n";
	   return nullptr;
    }
    GLFWwindow * window = glfwCreateWindow(800, 600, "OWO? OWWIE", NULL, NULL);
    glfwMakeContextCurrent(window);
    glOrtho(0, screenWidth, 0, screenHeight, -1, 1);
    glEnable(GL_DEPTH_TEST);
    return window;
}



