#pragma once
#include <math.h>
#include <iostream>

#include "Figure.h"
#include "pch.h"
#include "windowUtility.h"

class Circle : public Figure {
 public:
  explicit Circle(int size, int offsetX, int offsetY);

  void draw() override;
  bool isInnerPoint(int x, int y) override;

 private:
  int segments = 1;
};
