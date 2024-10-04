#include "pch.h"
#include "windowUtility.h"

void windowCoordsToVertex(GLfloat& x, GLfloat& y, int windowX, int windowY) {
  GLfloat xHalf = windowX / 2.0f;
  GLfloat yHalf = windowY / 2.0f;
  x -= xHalf;
  y -= yHalf;
  y *= -1;
  x /= xHalf;
  y /= yHalf;
}