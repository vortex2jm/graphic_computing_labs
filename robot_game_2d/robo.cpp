#include "robo.h"
#include <math.h>
#include "util.h"

void Robo::DesenhaRect(GLint height, GLint width, GLfloat R, GLfloat G, GLfloat B)
{
  glColor3f(R, G, B);
  glBegin(GL_POLYGON);
    glVertex3f(-(width/2), 0.0, 0.0);
    glVertex3f((width/2) ,0.0, 0.0);
    glVertex3f((width/2) ,height, 0.0);
    glVertex3f(-(width/2) ,height, 0.0);
  glEnd();
}

void Robo::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{
  glColor3f(R, G, B);
  glPointSize(3.0);
  glBegin(GL_POINTS);
    for(int i=0; i<360; i+=20){
      GLfloat rad = i * M_PI / 180.0;
      GLfloat x = radius * cos(rad);
      GLfloat y = radius * sin(rad);
      glVertex3f(x, y, 0);
    }
  glEnd();
}

void Robo::DesenhaRoda(GLfloat x, GLfloat y, GLfloat thetaWheel, GLfloat R, GLfloat G, GLfloat B)
{
  glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(thetaWheel, 0 ,0 , 1);
    Robo::DesenhaCirc(radiusWheel, R, G, B);
  glPopMatrix();
}

void Robo::DesenhaBraco(GLfloat x, GLfloat y, GLfloat theta1, GLfloat theta2, GLfloat theta3)
{ 
  glPushMatrix();
    
    glTranslatef(x, y, 0);
    glRotatef(theta1, 0, 0, 1);
    Robo::DesenhaRect(paddleHeight, paddleWidth, 0, 0, 1);

    glTranslatef(0, paddleHeight, 0);
    glRotatef(theta2, 0, 0, 1);
    Robo::DesenhaRect(paddleHeight, paddleWidth, 1, 1, 0);
    
    glTranslatef(0, paddleHeight, 0);
    glRotatef(theta3, 0, 0, 1);
    Robo::DesenhaRect(paddleHeight, paddleWidth, 0, 1, 0);
  
  glPopMatrix();
  // In this case, we could use loadIdentity 
}

void Robo::DesenhaRobo(GLfloat x, GLfloat y, GLfloat thetaWheel, GLfloat theta1, GLfloat theta2, GLfloat theta3)
{
  glPushMatrix();
    glTranslatef(x, y, 0.0);
    Robo::DesenhaRect(baseHeight, baseWidth, 1, 0 ,0);
    Robo::DesenhaBraco(0, baseHeight, theta1, theta2, theta3);
    Robo::DesenhaRoda(-(baseWidth/2), 0, thetaWheel, 1, 1, 1);
    Robo::DesenhaRoda((baseWidth/2), 0, thetaWheel, 1, 1, 1);
  glPopMatrix();
}

void Robo::RodaBraco1(GLfloat inc)
{
  Robo::gTheta1 += inc;
}

void Robo::RodaBraco2(GLfloat inc)
{
  Robo::gTheta2 += inc;
}

void Robo::RodaBraco3(GLfloat inc)
{
  Robo::gTheta3 += inc;
}

void Robo::MoveEmX(GLfloat dx)
{
  Robo::gX += dx;
  gThetaWheel -= dx;
}

Tiro* Robo::Atira()
{
  float point[2] = { 0, paddleHeight };
  matrix_tools::rotatePoint2f(point, gTheta3);
  matrix_tools::translatePoint2f(point, 0, paddleHeight);
  matrix_tools::rotatePoint2f(point, gTheta2);
  matrix_tools::translatePoint2f(point, 0, paddleHeight);
  matrix_tools::rotatePoint2f(point, gTheta1);
  matrix_tools::translatePoint2f(point, 0, baseHeight);
  matrix_tools::translatePoint2f(point, Robo::gX, Robo::gY);
  
  float base_vector[2] = { 0, 0 };
  matrix_tools::rotatePoint2f(base_vector, gTheta3);
  matrix_tools::translatePoint2f(base_vector, 0, paddleHeight);
  matrix_tools::rotatePoint2f(base_vector, gTheta2);
  matrix_tools::translatePoint2f(base_vector, 0, paddleHeight);
  matrix_tools::rotatePoint2f(base_vector, gTheta1);
  matrix_tools::translatePoint2f(base_vector, 0, baseHeight);
  matrix_tools::translatePoint2f(base_vector, Robo::gX, Robo::gY);
  
  // Calculating normalized direction vector
  float directionVector[2] = { point[0] - base_vector[0], point[1] - base_vector[1] };
  float directionVectorNorm = sqrt(pow(directionVector[0],2) + pow(directionVector[1], 2));
  float normalizedDirectionVector[2] = { directionVector[0]/directionVectorNorm, directionVector[1]/directionVectorNorm };
  
  return new Tiro(point, normalizedDirectionVector);
}
