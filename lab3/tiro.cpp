#include "tiro.h"
#include <math.h>
#define DISTANCIA_MAX 500

void Tiro::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{
  glColor3f(R, G, B);
  glBegin(GL_TRIANGLE_FAN);
    for(int i=0; i<360; i+=0.1){
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
    glLoadIdentity();
    glTranslatef(x, y, 0);
    Tiro::DesenhaCirc(radiusTiro, 1, 1, 1);  
  glPopMatrix();
}

void Tiro::Move()
{

}

bool Tiro::Valido()
{
  return true;
}
