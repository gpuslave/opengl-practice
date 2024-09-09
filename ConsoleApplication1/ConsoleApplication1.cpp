#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <tuple>
#include <utility>
#include <variant>

using namespace std;

static int windowX = 800;
static int windowY = 600;
static GLfloat currentColor[3] = {1.0f, 1.0f, 1.0f};

static std::tuple<double, double>* coords[2];

void windowCoordsToVertex(double& x, double& y);

void drawLine(GLFWwindow* window);

void setCoordinate(const double& x, const double& y, GLFWwindow* window);

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

void key_callback(GLFWwindow* window, int key, int scancode, int action,
                  int mods);

int main() {
  srand(time(nullptr));
  glColor3f(1.0, 1.0, 1.0);
  for (int i = 0; i < 2; ++i) {
    coords[i] = nullptr;
  }

  // Initialize GLFW
  if (!glfwInit()) {
    std::cerr << "Не удалось инициализировать GLFW" << std::endl;
    return -1;
  }

  // Create GLFW window
  GLFWwindow* window =
      glfwCreateWindow(windowX, windowY, "Test OpenGL", nullptr, nullptr);
  if (!window) {
    std::cerr << "Не удалось создать окно GLFW" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(0);

  // Callbacks
  glfwSetMouseButtonCallback(window, mouseButtonCallback);
  glfwSetKeyCallback(window, key_callback);

  // Background color
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glfwSwapBuffers(window);  // If something breaks - this line is the reason >_<

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    // Window update

    // glfwWaitEvents() --- It puts the thread to sleep until at least one event
    // has been received and then processes all received events. This saves a
    // great deal of CPU cycles and is useful for, for example, editing tools.
    glfwWaitEvents();

     //glfwPollEvents(); 
  }

  // Destroying a window and freeing resources
  glfwDestroyWindow(window);
  glfwMakeContextCurrent(nullptr);
  glfwTerminate();

  return 0;
}

void windowCoordsToVertex(double& x, double& y) {
  double xHalf = windowX / 2.;
  double yHalf = windowY / 2.;
  x -= xHalf;
  y -= yHalf;
  y *= -1;
  x /= xHalf;
  y /= yHalf;
}

void drawLine(GLFWwindow* window) {
  glClear(GL_COLOR_BUFFER_BIT);

  glfwSwapBuffers(window);

  glBegin(GL_LINES);
  glColor3f(currentColor[0], currentColor[1], currentColor[2]);
  for (const tuple<double, double>* pair : coords) {
    glVertex2d(std::get<0>(*pair), std::get<1>(*pair));
  }
  glEnd();

  glfwSwapBuffers(window);

  for (int i = 0; i < 2; ++i) {
    delete coords[i];
    coords[i] = nullptr;
  }
}

void setCoordinate(const double& x, const double& y, GLFWwindow* window) {
  for (int i = 0; i < 2; ++i) {
    if (coords[i] == nullptr) {
      coords[i] = new tuple<double, double>(x, y);
      if (i != 1) {
        return;
      }
    }
  }

  drawLine(window);
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
  if (action != 1) {
    return;
  }

  double x(0.0), y(0.0);

  glfwGetCursorPos(window, &x, &y);
  windowCoordsToVertex(x, y);
  setCoordinate(x, y, window);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action,
                  int mods) {
  // Pressing "c" changes the color of the next drawn line (actually variable
  // currentColor)
  if (key == GLFW_KEY_C && action == GLFW_PRESS) {
    currentColor[0] = float(rand() % 101) / 100;
    currentColor[1] = float(rand() % 101) / 100;
    currentColor[2] = float(rand() % 101) / 100;
    cout << "Color: " << currentColor[0] * 255 << " " << currentColor[1] * 255
         << " " << currentColor[2] * 255 << endl;
  }
}
