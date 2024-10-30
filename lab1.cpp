#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#define TAMANHO_JANELA 750

void init();
void idle();
void display();
void keyUp(unsigned char key, int x, int y);
void keyPress(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);


float gX=0;
float gY=0;
int keyStatus[256];

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (TAMANHO_JANELA, TAMANHO_JANELA); 
   glutInitWindowPosition (540, 100);
   
   glutCreateWindow ("hello world");
   
   init ();

   glutMouseFunc(mouse);
   glutKeyboardUpFunc(keyUp);   
   glutKeyboardFunc(keyPress);
   glutDisplayFunc(display); 
   glutMainLoop();
   
   return 0;
}


// ====================================================================
void display(void)
{
   /* Limpar todos os pixels  */
   glClear (GL_COLOR_BUFFER_BIT);

   /* Define cor dos vértices com os valores R, G e B variando de 0.0 a 1.0 */
   glColor3f (1.0, 0, 0);
   /* Desenhar um polígono branco (retângulo) */
   glBegin(GL_POLYGON);
      glVertex3f (0.25+gX, 0.25+gY, 0.0);
      glVertex3f (0.75+gX, 0.25+gY, 0.0);
      glVertex3f (0.75+gX, 0.75+gY, 0.0);
      glVertex3f (0.25+gX, 0.75+gY, 0.0);
   glEnd();

   idle();

   /* Desenhar no frame buffer! */
   glutSwapBuffers(); //Funcao apropriada para janela double buffer
}


void init (void) 
{
  /* selecionar cor de fundo (preto) */
  glClearColor (0.0, 0.0, 0.0, 0.0);

  /* inicializar sistema de visualizacao */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

// Part 1
// void keyPress(unsigned char key, int x, int y)
// {
//    switch (key)
//    {
//    case 'w':
//       gY+=0.01;      
//       break;

//    case 'a':
//       gX-=0.01;
//       break;

//    case 's':
//       gY-=0.01;
//       break;

//    case 'd':
//       gX+=0.01;
//       break;

//    default:
//       break;
//    }

//    glutPostRedisplay();
// }


//================================================
// Part 2
void keyPress(unsigned char key, int x, int y)
{
   keyStatus[key] = 1;  
}

void keyUp(unsigned char key, int x, int y)
{
   keyStatus[key] = 0;
   glutPostRedisplay();
}

void idle()
{
   if(keyStatus['a']) gX-=0.01;
   if(keyStatus['d']) gX+=0.01;
   if(keyStatus['s']) gY-=0.01;
   if(keyStatus['w']) gY+=0.01;
}

// Part 3=========================================
void mouse(int button, int state, int x, int y)
{
   gX = x/TAMANHO_JANELA;
   gY = y/TAMANHO_JANELA;
   glutPostRedisplay();
}
