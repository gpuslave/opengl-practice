
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Circle.h"
// #include "pch.h"

using namespace std;

static int windowX = 800;
static int windowY = 600;

Circle circle(100, 400, 300);

void renderPrimitives();

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);

int main() {
  srand(time(nullptr));
  // glColor3f(1.0, 1.0, 0.0);

  if (!glfwInit()) {
    return -1;
  }
  GLFWwindow* window =
      glfwCreateWindow(windowX, windowY, "Test OpenGL", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSwapInterval(0);

  glfwSetMouseButtonCallback(window, mouseButtonCallback);
  glfwSetCursorPosCallback(window, cursorPosCallback);

  /*glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glfwSwapBuffers(window);*/

  while (!glfwWindowShouldClose(window)) {
    renderPrimitives();

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  // Destroying a window and freeing resources
  glfwDestroyWindow(window);
  glfwMakeContextCurrent(nullptr);
  glfwTerminate();
  return 0;
}

void renderPrimitives() {
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  circle.draw();
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
  if (button != GLFW_MOUSE_BUTTON_RIGHT) {
    return;
  }

  double x(0.0), y(0.0);
  glfwGetCursorPos(window, &x, &y);

  if (!circle.isInnerPoint(x, y)) {
    if (action == GLFW_PRESS) {
      circle.moveTo(x, y);
      cout << "Move to\n";
    }
  } else {
    if (action == GLFW_RELEASE) {
      circle.stopDragging(x, y);
      cout << "Stop dragging\n";
    }

    if (action == GLFW_PRESS) {
      if (circle.isInnerPoint(x, y)) {
        circle.startDragging(x, y);
        cout << "Start dragging\n";
      }
    }
  }

  // if (action == GLFW_RELEASE) {
  //   circle.stopDragging(x, y);
  //   cout << "Stop dragging\n";
  // }

  // if (action == GLFW_PRESS) {
  //   circle.moveTo(x, y);
  //   cout << "Move to\n";
  // }

  // if (action == GLFW_PRESS) {
  //   if (circle.isInnerPoint(x, y)) {
  //     circle.startDragging(x, y);
  //     cout << "Start dragging\n";
  //   }
  // }

  // if (action != GLFW_PRESS) {
  //   circle.stopDragging(x, y);
  //   return;
  // }

  // if (circle.isInnerPoint(x, y)) {
  //   circle.startDragging(x, y);
  // } else {
  //   circle.move(x, y);
  // }
}

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
  if (circle.isDragging()) {
    circle.drag(xpos, ypos);
    cout << "Dragging\n";
  }
}