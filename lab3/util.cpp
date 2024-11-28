#include "util.h"
#include <math.h>

namespace matrix_tools {
  void translatePoint2f(float point[2], float offSetX, float offSetY)
  {
    point[0] += offSetX;
    point[1] += offSetY;
  }

  void rotatePoint2f(float point[2], float angle)
  { 
    float x = point[0];
    float y = point[1];
    
    float angleRad = angle * M_PI / 180;

    point[0] = (cos(angleRad) * x) + (-sin(angleRad) * y);
    point[1] = (sin(angleRad) * x) + (cos(angleRad) * y);
  }
}
