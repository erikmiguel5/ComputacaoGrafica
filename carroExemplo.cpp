#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.1415

GLfloat angle = 60, fAspect;

int rot_y = 0; float trans_x = 0.0; float trans_z= 0.0;
float velocidade = 0.0;

void Inicializa(void){
  glClearColor (1.0, 1.0, 1.0, 0.0);
  glEnable(GL_DEPTH_TEST);//z-buffer
  glColor3f(0.0, 1.0, 0.0);//cor verde

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(65, 1, 0.5, 500);

 }

void Piso (float escala, float altura){
 glColor3f(0.0, 1.0, 0.0);
 glPushMatrix();
   glTranslatef(0.0, altura, 0.0);
   glScalef(escala, escala, escala);
   glBegin(GL_QUADS);//v�rtices ligados no anti-hor�rio
    glVertex3f(100.0, 0.0, 100.0);
    glVertex3f(-100.0, 0.0, 100.0);
    glVertex3f(-100.0, 0.0, -100.0);
    glVertex3f(100.0, 0.0, -100.0);
   glEnd();
 glPopMatrix();
}

void Carro(int rot_y,float trans_x,float trans_z){
glPushMatrix();
    glTranslatef(trans_x,0.0,trans_z);//depois da rota��o, transla��o
    glRotatef(rot_y,0.0,1.0,0.0);//depois da escala, rota��o
    glPushMatrix();
      glScalef(1.0,1.0,2.0); //escala em (0,0,0)
      glColor3f(1.0,0.0,0.0);
      glutSolidCube(1.0);
    glPopMatrix();
    glColor3f(0.0,0.0,1.0);
    glTranslatef(0, 0, 1.5);
    glutSolidCube(1.0);
glPopMatrix();
}

void Desenha(void){
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0,3,-13, 0,0,0, 0,1,0);

  Piso(1.0, -2.0);
  Carro(rot_y,trans_x,trans_z);
  glutSwapBuffers();
}




void AlteraTamanhoJanela (int w, int h){
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  if(h == 0) h = 1;

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(65, (GLfloat) w/(GLfloat) h, 0.5, 500);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0,3,-13, 0,0,0, 0,1,0); // Especifica posi��o do observador e do alvo
}

void Teclado(unsigned char key, int x, int y){
  if(key == 's' || key == 'S'){ //anti-hor�rio
    rot_y= (rot_y + 5) % 360;
    glutPostRedisplay();
  }
  else if(key == 'd' || key == 'D'){ //hor�rio
    rot_y= (rot_y - 5) % 360;
    glutPostRedisplay();
  }
  else if(key == 'e' || key == 'E'){ //hor�rio
    if (velocidade == 0.0) velocidade = 0.5;
    else velocidade = 0.0;
    //trans_x += velocidade;
    //trans_z += velocidade;
    trans_x += velocidade*sin(rot_y*PI/180);
    trans_z += velocidade*cos(rot_y*PI/180);

    glutPostRedisplay();
  }
}

int main(int argc, char** argv){
  glutInit(&argc, argv);

  glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

  glutInitWindowSize (800, 800);

  glutInitWindowPosition (0, 0);

  glutCreateWindow ("Computa��o Gr�fica: Carro");

  Inicializa();

  glutDisplayFunc(Desenha);

  //glutReshapeFunc(AlteraTamanhoJanela);

  glutKeyboardFunc(Teclado);

  glutMainLoop();
  return 0;
}
