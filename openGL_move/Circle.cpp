#include "Circle.h"

#include <math.h>

Circle::Circle(int size, int offsetX, int offsetY)
    : Figure(size, offsetX, offsetY) {}

void Circle::draw() {
  // glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_LINE_LOOP);
  // glColor3f((rand() % 255 + 100) / 255.0f, (rand() % 255 + 100) / 255.0f,
  //           (rand() % 255 + 100) / 255.0f);

  int segments = 750;
  for (int i = 0; i < segments; ++i) {
    GLfloat alpha = 2.0f * 3.14159f * (GLfloat)i / (GLfloat)segments;

    GLfloat dx = m_size * cosf(alpha);
    GLfloat dy = m_size * sinf(alpha);

    GLfloat xVert = dx + m_offsetX;
    GLfloat yVert = dy + m_offsetY;
    windowCoordsToVertex(xVert, yVert, 800, 600);
    glVertex2f(xVert, yVert);
  }
  glEnd();
}

bool Circle::isInnerPoint(int x, int y) {
  return (x - m_offsetX) * (x - m_offsetX) +
             (y - m_offsetY) * (y - m_offsetY) <=
         m_size * m_size;
}
