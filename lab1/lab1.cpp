#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdio.h>

#define TAMANHO_JANELA 750

void init();
void idle();
void display();
void keyUp(unsigned char key, int x, int y);
void keyPress(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);

// Global variables
float gX=0;
float gY=0;
int keyStatus[256];

int main(int argc, char** argv){
   glutInit(&argc, argv);
   
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (TAMANHO_JANELA, TAMANHO_JANELA); 
   glutInitWindowPosition (540, 100);
   
   glutCreateWindow ("hello world");   
   init ();

   glutIdleFunc(idle);
   glutMouseFunc(mouse);
   glutKeyboardUpFunc(keyUp);   
   glutKeyboardFunc(keyPress);
   glutDisplayFunc(display); 
   glutMainLoop();
   
   return 0;
}

// Callbacks =======
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
   gX = (float)x/TAMANHO_JANELA -0.25;
   gY = (float)y/TAMANHO_JANELA -0.25;

   // Debug
   printf("X: %d, Y: %d\n gX: %lf, gY: %lf\n", x, y, gX, gY);
}
