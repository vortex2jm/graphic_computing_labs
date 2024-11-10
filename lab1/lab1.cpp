#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdio.h>

#define TAMANHO_JANELA 750

// Callbacks
void init();
void idle();
void display();
void keyUp(unsigned char key, int x, int y);
void keyPress(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void mouseMotion(int x, int y);


// Global variables
int keyStatus[256];
float gX=0, gY=0;
float mouseFixedX=0, mouseFixedY=0;
bool drag = false;


int main(int argc, char** argv){
   glutInit(&argc, argv);
   
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (TAMANHO_JANELA, TAMANHO_JANELA); 
   glutInitWindowPosition (540, 100);
   
   glutCreateWindow ("Square Game");   
   init ();

   glutKeyboardUpFunc(keyUp);   
   glutKeyboardFunc(keyPress);
   glutMouseFunc(mouse);
   glutMotionFunc(mouseMotion);
   
   glutDisplayFunc(display); 
   glutIdleFunc(idle);
   
   glutMainLoop();
   
   return 0;
}

// Callbacks impl =================================
void display(void){
   glClear (GL_COLOR_BUFFER_BIT);   // Clear pixels

   glColor3f (1.0, 0, 0);  

   glBegin(GL_POLYGON);
      glVertex3f (0.25+gX, 0.25+gY, 0.0);
      glVertex3f (0.75+gX, 0.25+gY, 0.0);
      glVertex3f (0.75+gX, 0.75+gY, 0.0);
      glVertex3f (0.25+gX, 0.75+gY, 0.0);
   glEnd();

   // Draw in frame buffer
   glutSwapBuffers(); // double buffer window
}

//================
void init (void) {
  // Background color
  glClearColor (0.0, 0.0, 0.0, 0.0);

  // Init system
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

//=============================================
void keyPress(unsigned char key, int x, int y){
   keyStatus[key] = 1;
   glutPostRedisplay();  
}

//=========================================
void keyUp(unsigned char key, int x, int y){
   keyStatus[key] = 0;
   glutPostRedisplay();
}

//=========
void idle(){
   if(keyStatus['a']) gX-=0.001;
   if(keyStatus['d']) gX+=0.001;
   if(keyStatus['s']) gY-=0.001;
   if(keyStatus['w']) gY+=0.001;
   glutPostRedisplay();
}

//============================================
void mouse(int button, int state, int x, int y)
{  
   y = TAMANHO_JANELA-y;
   
   //===================================
   // This chunk is for click motion
   // gX = (float)x/TAMANHO_JANELA -0.25;
   // gY = (float)y/TAMANHO_JANELA -0.25;
   //===================================

   if(button == GLUT_LEFT_BUTTON and state == GLUT_DOWN){

      float xPos = (float)x/TAMANHO_JANELA;
      float yPos = (float)y/TAMANHO_JANELA;
      
      if(xPos > 0.25+gX and xPos < 0.75+gX and yPos > 0.25+gY and yPos < 0.75+gY){  // If pointer is in range
         drag = true;
         mouseFixedX = xPos;
         mouseFixedY = yPos;
      }
   }
   if(button == GLUT_LEFT_BUTTON and state == GLUT_UP){
      drag = false;
   }
   glutPostRedisplay();
}

//==============================
void mouseMotion(int x, int y){
   if(drag){
      y = TAMANHO_JANELA - y;
      float xPos = (float)x/TAMANHO_JANELA;
      float yPos = (float)y/TAMANHO_JANELA;
      gX = xPos - mouseFixedX;
      gY = yPos - mouseFixedY;
   }
   glutPostRedisplay();
}
