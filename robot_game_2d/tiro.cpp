#include "tiro.h"
#include <math.h>
#define DISTANCIA_MAX 500

void Tiro::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{
  glColor3f(R, G, B);
  glBegin(GL_TRIANGLE_FAN);
    for(float i=0; i<360; i+=0.1){
      GLfloat rad = i * M_PI / 180.0;
      GLfloat x = radius * cos(rad);
      GLfloat y = radius * sin(rad);
      glVertex3f(x, y, 0); 
    }
  glEnd();
}

void Tiro::DesenhaTiro(GLfloat x, GLfloat y)
{
  glPushMatrix();
    glTranslatef(x, y, 0);
    Tiro::DesenhaCirc(radiusTiro, 1, 1, 1);  
  glPopMatrix();
}

void Tiro::Move(GLdouble timeDiff)
{
  GLdouble auxVec[2] = { 
    Tiro::directionVector[0] * Tiro::gVel * timeDiff,   // Distance = velocity * time
    Tiro::directionVector[1] * Tiro::gVel * timeDiff 
  };

  gX += auxVec[0];
  gY += auxVec[1];
}

bool Tiro::Valido()
{
  return !(Tiro::gX > DISTANCIA_MAX or Tiro::gY > DISTANCIA_MAX);
}
