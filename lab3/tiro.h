#ifndef TIRO_H
#define	TIRO_H
#include <GL/gl.h>
#include <GL/glu.h>

#define radiusTiro 5

class Tiro {
    GLfloat gXInit; 
    GLfloat gYInit; 
    GLfloat gX; 
    GLfloat gY; 
    // GLfloat gDirectionAng;
    GLfloat gVel;
    GLfloat directionVector[2];
private:
    void DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void DesenhaTiro(GLfloat x, GLfloat y);
public:
    Tiro(GLfloat initPoint[2], GLfloat directVec[2]){
        gXInit = initPoint[0]; 
        gYInit = initPoint[1]; 
        gX = initPoint[0]; 
        gY = initPoint[1];
        // gDirectionAng = directionAng; 
        gVel = 0.2;
        directionVector[0] = directVec[0];
        directionVector[1] = directVec[1];
    };
    void Desenha(){ 
        DesenhaTiro(gX, gY);
    };
    void Move();
    bool Valido();
    void GetPos(GLfloat &xOut, GLfloat &yOut){
        xOut = gX;
        yOut = gY;
    };
};

#endif	/* TIRO_H */

