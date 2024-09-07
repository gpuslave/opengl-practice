#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <tuple>
#include <utility>
#include <variant>

using namespace std;
static int windowX;
static int windowY;

static std::tuple<double,double>* coords[2];

void windowCoordsToVertex(double& x, double& y)
{
	float xHalf = windowX / 2.;
	float yHalf = windowY / 2.;
	x -= xHalf;
	y -= yHalf;
	y *= -1;
	x /= xHalf;
	y /= yHalf;
}
void drawLine(GLFWwindow* window)
{
//	glClear(GL_COLOR_BUFFER_BIT);
	//glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

		glfwSwapBuffers(window);
	glBegin(GL_LINES);
	for (const tuple<double, double>* pair : coords)
	{
		glVertex2f(std::get<0>(*pair), std::get<1>(*pair));
	}
	glEnd();
//	glfwSwapBuffers(window);
		glfwSwapBuffers(window);

	for (int i = 0; i < 2; ++i)
	{
		delete coords[i];
		coords[i] = nullptr;
	}
}

void setCoordinate(const double& x, const double& y, GLFWwindow* window)
{
//	bool areCoordsFilled = false;

	for (int i = 0; i < 2; ++i)
	{
		if (coords[i] == nullptr)
		{
			//tuple<double, double> aboba;	
			coords[i] = new tuple<double,double> (x, y);
			if (i != 1)
			{
				return;
			}
		}
	}

	drawLine(window);
}



// Drawing the primitive
//void renderPrimitives();
// Handle user input
//void processInput(GLFWwindow* window);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

int main()
{
	for (int i = 0 ;i<2;++i)
	{
		coords[i] = nullptr;
	}

	// Initialize GLFW
	if (!glfwInit()) {
		std::cerr << "Не удалось инициализировать GLFW" << std::endl;
		return -1;
	}

	// Create a GLFW window
	windowX = 800;
	windowY = 600;
	GLFWwindow* window = glfwCreateWindow(windowX, windowY, "Test OpenGL", nullptr, nullptr);
	if (!window) {
		std::cerr << "Не удалось создать окно GLFW" << std::endl;
		glfwTerminate();
		return -1;
	}
//	glfwSwapInterval(1);
	glfwMakeContextCurrent(window);

	// Button mouse callback
	glfwSetMouseButtonCallback(window, mouseButtonCallback);

	// Main loop
	while (!glfwWindowShouldClose(window)) {
		// Input processing
	//	processInput(window);
		// Drawing the primitive
	//	renderPrimitives();

		// Window update
		glfwPollEvents();
	}

	// Destroying a window and freeing resources
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action != 1)
	{
		return;
	}
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	windowCoordsToVertex(x, y);
	setCoordinate(x, y,window);
}

