#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cmath>

float screenHeight = 800.0f;
float screenWidth = 1300.0f;

GLFWwindow * StartGLFW();

class Object {
    public:
	   std::vector<float> position;
	   std::vector<float> velocity;
	   float radius;
	   int res;
	   Object(std::vector<float> position, std::vector<float> velocity, float radius, int res){
		  this->position = position;
		  this->velocity = velocity;
		  this->radius = radius;
		  this->res = res;
	   }

	   void accelerate (float x, float y) {
		  this->velocity[0] += pow(x, 1.0f/2.0f);
		  this->velocity[1] += pow(y, 1.0f/2.0f);
	   };
	   void updatePos () {
		  this->position[0] += this->velocity[0];
		  this->position[1] += this->velocity[1];
	   };
	   
	   void DrawCircle() {
		  glBegin(GL_TRIANGLE_FAN);
		  glVertex2d(this->position[0], this->position[1]);

		  for (int i = 0; i <= this->res; ++i) {
			 float angle = 2.0f * M_PI * i / res;
			 float x = this->position[0] + cos(angle) * radius;
			 float y = this->position[1] + sin(angle) * radius;
			 glVertex2d(x, y);
		  } 

		  glEnd();

	   };
	   float CheckCollision(const Object& other) {
            float dx = other.position[0] - this->position[0];
            float dy = other.position[1] - this->position[1];
            float dz = other.position[2] - this->position[2];
            float distance = std::pow(dx*dx + dy*dy + dz*dz, (1.0f/2.0f));
            if (other.radius + this->radius > distance){
                return -0.2f;
            }
            return 1.0f;
        };

};

int main () {
    GLFWwindow * window = StartGLFW();
    
    float centerX = screenWidth / 2.0f;
    float centerY = screenHeight / 2.0f;
    float radius = 50.0f;
    int res = 100; 
    int timestamp = 0;
    
    std::vector<Object> objs = {
	   Object(std::vector<float>{200.0f, 50.f}, std::vector<float>{0.0f, 14.0f}, 50.0f, 50),
    };

    while (!glfwWindowShouldClose(window)) {
	   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	   timestamp++;

	   std::cout<<timestamp;
	   for (auto& obj: objs) {
		  if (timestamp == 1) obj.updatePos();
		  obj.accelerate(0, -10.0f);
		  if (timestamp != 1) obj.updatePos();
		  if (obj.position[0] < obj.radius || obj.position[0] > screenWidth - obj.radius) {
			 if (obj.position[0] < obj.radius) obj.position[0] = obj.radius;
			 else obj.position[0] = screenWidth - obj.radius;
			 obj.velocity[0] *= -0.95; 
		  } 
		  if (obj.position[1] < obj.radius || obj.position[1] > screenHeight - obj.radius) {
			 if (obj.position[1] < obj.radius) obj.position[1] = obj.radius;
			 else obj.position[1] = screenHeight - obj.radius;
			 obj.velocity[1] *= -0.95;  
		  }

		  obj.DrawCircle(); 
		  std::cout << "\tOBJ >> X=" << obj.position[0] << "\tY=" << obj.position[1] << "\t";
	   }
    
	   std::cout << "\n";
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
    GLFWwindow * window = glfwCreateWindow(screenWidth, screenHeight, "OWO? OWWIE", NULL, NULL);
    glfwMakeContextCurrent(window);
    glOrtho(0, screenWidth, 0, screenHeight, -1, 1);
    glEnable(GL_DEPTH_TEST);
    return window;
}


