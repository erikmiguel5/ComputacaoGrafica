#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "CarregarArquivo2.cpp"
#define Pi 3.1415

#define PI 3.1415

using namespace std;

CarregarArquivo corpo;
CarregarArquivo eixoFrontal;
CarregarArquivo eixoTraseiro;
CarregarArquivo janela;
CarregarArquivo meteoro;

float  rotX = 0;
int rotY = 0;
float obsZ = 0;
float trans_x = 0;
float trans_z = 0;
float velocidade = 0;
int rotTraseiro = 0;
float lookx = 0;
float looky = 18;
float lookz = -40;
float centerx = 0;
float centery = 0;
float centerz = 0;

float meteorox = 1;
float meteoroy = 3;
float meteoroz = 1;

int placarGeral = 0;
int placarU;
int placarD;
int placarC = 0;

char *skin[9] ={"car0.bmp","car1.bmp","car2.bmp","car3.bmp","car4.bmp","car5.bmp","car6.bmp","car7.bmp","car8.bmp"};
int contSkin = 0;

GLubyte meteoroTextura[256][256][3];
GLubyte janelaTextura[256][256][3];
GLubyte chaoTextura[256][256][3];
GLubyte carroTextura[256][256][3];
GLubyte pneuTextura[256][256][3];
GLuint meteoro_id,janela_id, carro_id, chao_id, pneu_id;

int cam = 0;

void
print_stroke_string(void* font, char* s)
{
   if (s && strlen(s)) {
      while (*s) {
         glutStrokeCharacter(font, *s);
         s++;
      }
   }
}


void DefineIluminacao (void)
{
    GLfloat luzAmbiente[4]= {0.4,0.4,0.4,1.0};
    GLfloat luzDifusa[4]= {1,1,1,1.0}; // "cor"
    GLfloat luzEspecular[4]= {1.0, 1.0, 1.0, 1.0}; // "brilho"
    GLfloat posicaoLuz[4]= {0.0, 0.0, 15.0, 1.0};
// Capacidade de brilho do material
    GLfloat especularidade[4]= {1.0,1.0,1.0,1.0};
    GLint especMaterial = 60;
// Define a reflet�ncia do material
    glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
// Define a concentra��o do brilho
    glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
// Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
// Define os par�metros da luz de n�mero 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );
}


void Inicializa(void){
  glClearColor (1.0, 1.0, 1.0, 0.0); //fundo branco
  // Habilita a defini��o da cor do material a partir da cor corrente
  glEnable(GL_COLOR_MATERIAL);
//Habilita o uso de ilumina��o
  glEnable(GL_LIGHTING);
// Habilita a luz de n�mero 0
  glEnable(GL_LIGHT0);
// Habilita o depth-buffering
  glEnable(GL_DEPTH_TEST);

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(95, 1, 0.5, 500);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0,4,-13, 0,0,0, 0,1,0);
  corpo.Carregar("corpo.obj");
  eixoFrontal.Carregar("eixoFrontal.obj");
  eixoTraseiro.Carregar("eixoTraseiro.obj");
  janela.Carregar("janela.obj");
  meteoro.Carregar("meteoro.obj");
  printf("Load ok");

    try
    {
        ifstream arq("a.bmp" ,ios::binary);
        char c;
        if(!arq)
            cout << "Erro ao abrir";

        for(int i = 0; i < 54 ; i++)//lena 122
            c = arq.get();
        for(int i = 0; i < 256 ; i++)
            for(int j = 0; j < 256 ; j++)
            {
                c = arq.get();
                meteoroTextura[i][j][2] = c;
                c =  arq.get();
                meteoroTextura[i][j][1] = c ;
                c =  arq.get();
                meteoroTextura[i][j][0] = c;
                //printf("%d %d %d \t",lena[i][j][0], lena[i][j][1], lena[i][j][2] );
            }

        arq.close();
        arq.clear();
    }
    catch(...)
    {
        cout << "Erro ao ler imagem" << endl;
    }
     glGenTextures(1,&meteoro_id);
     printf("%d", meteoro_id);
    // lena
    // Associa a textura aos comandos seguintes
    glBindTexture(GL_TEXTURE_2D, meteoro_id);

    // Envia a textura para uso pela OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB,GL_UNSIGNED_BYTE, meteoroTextura);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    try
    {
        ifstream arq("pneu.bmp" ,ios::binary);
        char c;
        if(!arq)
            cout << "Erro ao abrir";

        for(int i = 0; i < 54 ; i++)//lena 122
            c = arq.get();
        for(int i = 0; i < 256 ; i++)
            for(int j = 0; j < 256 ; j++)
            {
                c = arq.get();
                pneuTextura[i][j][2] = c;
                c =  arq.get();
                pneuTextura[i][j][1] = c ;
                c =  arq.get();
                pneuTextura[i][j][0] = c;
                //printf("%d %d %d \t",lena[i][j][0], lena[i][j][1], lena[i][j][2] );
            }

        arq.close();
        arq.clear();
    }
    catch(...)
    {
        cout << "Erro ao ler imagem" << endl;
    }
     glGenTextures(1,&pneu_id);
     printf("%d", pneu_id);
    // lena
    // Associa a textura aos comandos seguintes
    glBindTexture(GL_TEXTURE_2D, pneu_id);

    // Envia a textura para uso pela OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB,GL_UNSIGNED_BYTE, pneuTextura);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    try
    {
        ifstream arq(skin[contSkin] ,ios::binary);
        char c;
        if(!arq)
            cout << "Erro ao abrir";

        for(int i = 0; i < 54 ; i++)//lena 122
            c = arq.get();
        for(int i = 0; i < 256 ; i++)
            for(int j = 0; j < 256 ; j++)
            {
                c = arq.get();
                carroTextura[i][j][2] = c;
                c =  arq.get();
                carroTextura[i][j][1] = c ;
                c =  arq.get();
                carroTextura[i][j][0] = c;
                //printf("%d %d %d \t",lena[i][j][0], lena[i][j][1], lena[i][j][2] );
            }

        arq.close();
        arq.clear();
    }
    catch(...)
    {
        cout << "Erro ao ler imagem" << endl;
    }
     glGenTextures(1,&carro_id);
     printf("%d", carro_id);
    // lena
    // Associa a textura aos comandos seguintes
    glBindTexture(GL_TEXTURE_2D, carro_id);

    // Envia a textura para uso pela OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB,GL_UNSIGNED_BYTE, carroTextura);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

     try
    {
        ifstream arq("ja.bmp" ,ios::binary);
        char c;
        if(!arq)
            cout << "Erro ao abrir";

        for(int i = 0; i < 54 ; i++)//lena 122
            c = arq.get();
        for(int i = 0; i < 256 ; i++)
            for(int j = 0; j < 256 ; j++)
            {
                c = arq.get();
                janelaTextura[i][j][2] = c;
                c =  arq.get();
                janelaTextura[i][j][1] = c ;
                c =  arq.get();
                janelaTextura[i][j][0] = c;
                //printf("%d %d %d \t",lena[i][j][0], lena[i][j][1], lena[i][j][2] );
            }

        arq.close();
        arq.clear();
    }
    catch(...)
    {
        cout << "Erro ao ler imagem" << endl;
    }
     glGenTextures(1,&janela_id);
     printf("%d", janela_id);
    // lena
    // Associa a textura aos comandos seguintes
    glBindTexture(GL_TEXTURE_2D, janela_id);

    // Envia a textura para uso pela OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB,GL_UNSIGNED_BYTE, janelaTextura);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


    try
    {
        ifstream arq("terra.bmp" ,ios::binary);
        char c;
        if(!arq)
            cout << "Erro ao abrir";

        for(int i = 0; i < 54 ; i++)//lena 122
            c = arq.get();
        for(int i = 0; i < 256 ; i++)
            for(int j = 0; j < 256 ; j++)
            {
                c = arq.get();
                chaoTextura[i][j][2] = c;
                c =  arq.get();
                chaoTextura[i][j][1] = c ;
                c =  arq.get();
                chaoTextura[i][j][0] = c;
                //printf("%d %d %d \t",lena[i][j][0], lena[i][j][1], lena[i][j][2] );
            }

        arq.close();
        arq.clear();
    }
    catch(...)
    {
        cout << "Erro ao ler imagem" << endl;
    }
     glGenTextures(1,&chao_id);
     printf("%d", chao_id);
    // lena
    // Associa a textura aos comandos seguintes
    glBindTexture(GL_TEXTURE_2D, chao_id);

    // Envia a textura para uso pela OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB,GL_UNSIGNED_BYTE, chaoTextura);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


}



void TeclasEspeciais (int tecla, int x, int y)
{
    switch (tecla)
    {
    case GLUT_KEY_LEFT:
        rotY = (rotY + 10) % 360;
        centery += 1;
        break;
    case GLUT_KEY_RIGHT:
        rotY = (rotY - 10) % 360;
        centery -=1;
        break;
    case GLUT_KEY_UP:
        rotTraseiro = (rotTraseiro + 5) % 360;
         if (velocidade == 0.0) velocidade = 4;
        else velocidade = 0.0;
        trans_x += velocidade*sin(rotY*PI/180);
        trans_z += velocidade*cos(rotY*PI/180);
        centerx++;
        break;
    case GLUT_KEY_DOWN:
         if (velocidade == 0.0) velocidade = -4;
        else velocidade = 0.0;
        trans_x -= velocidade*sin(rotY*PI/180)*(-1);
        trans_z -= velocidade*cos(rotY*PI/180)*(-1);
        centerx--;
        break;
    }


    glutPostRedisplay();
}

void Teclado(unsigned char key, int x, int y){
  if(key == 'a'){
    lookx++;
    glutPostRedisplay();
  }
  else if(key == 's'){
    looky++;
    glutPostRedisplay();
  }
  else if(key == 'd'){
    lookz++;
    glutPostRedisplay();
  }
  else if(key == 'A'){
    lookx--;
    glutPostRedisplay();
  }
  else if(key == 'S'){
    looky--;
    glutPostRedisplay();
  }
  else if(key == 'D'){
    lookz--;
    glutPostRedisplay();
  }
else if(key == 'c'){
    if(cam == 0) cam = 1;
    else cam = 0;
  }
if(key == 'x'){
    contSkin ++;
    if(contSkin == 9) contSkin = 0;

        try
    {
        ifstream arq(skin[contSkin] ,ios::binary);
        char c;
        if(!arq)
            cout << "Erro ao abrir";

        for(int i = 0; i < 54 ; i++)//lena 122
            c = arq.get();
        for(int i = 0; i < 256 ; i++)
            for(int j = 0; j < 256 ; j++)
            {
                c = arq.get();
                carroTextura[i][j][2] = c;
                c =  arq.get();
                carroTextura[i][j][1] = c ;
                c =  arq.get();
                carroTextura[i][j][0] = c;
                //printf("%d %d %d \t",lena[i][j][0], lena[i][j][1], lena[i][j][2] );
            }

        arq.close();
        arq.clear();
    }
    catch(...)
    {
        cout << "Erro ao ler imagem" << endl;
    }
     glGenTextures(1,&carro_id);
     printf("%d", carro_id);
    // lena
    // Associa a textura aos comandos seguintes
    glBindTexture(GL_TEXTURE_2D, carro_id);

    // Envia a textura para uso pela OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB,GL_UNSIGNED_BYTE, carroTextura);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    //glutPostRedisplay();
  }
printf("\nSkin:%d", contSkin);

}


void Piso (float escala, float altura){
glColor3f(0.0, 1.0, 0.0);
 glEnable(GL_TEXTURE_2D);
 glBindTexture(GL_TEXTURE_2D, chao_id);
 glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
 glPushMatrix();
   glTranslatef(0.0, altura, 0.0); //translação depois da escala
   glScalef(escala, escala, escala); //escala na origem
   glBegin(GL_POLYGON);
    glNormal3f(0,-1,0);
    glTexCoord2f(0,0);
    glVertex3f(100.0, 0.0, 100.0);
    //glTexCoord2f(1,0);
    glTexCoord2f(10,0);
    glVertex3f(-100.0, 0.0, 100.0);
    //glTexCoord2f(1,1);
    glTexCoord2f(10,10);
    glVertex3f(-100.0, 0.0, -100.0);
    //glTexCoord2f(0,1);
    glTexCoord2f(0,10);
    glVertex3f(100.0, 0.0, -100.0);
   glEnd();
 glPopMatrix();
 glDisable(GL_TEXTURE_2D);
}

void corpoWireFrame(void)  {
    glPushMatrix();
    for (unsigned int j = 0; j < (corpo.faces).size(); ++j )
    {
        glBegin ( GL_LINE_LOOP );
         for (unsigned int i = 0; i < (corpo.faces[j]).size() ; ++i )        {
            GLfloat vert[3] = {(corpo.vertices[corpo.faces[j][i][0]][0]),(corpo.vertices[corpo.faces[j][i][0]][1]),(corpo.vertices[corpo.faces[j][i][0]][2])};
            GLfloat nor[3] =  {(corpo.normais[corpo.faces[j][i][2]][0]),(corpo.normais[corpo.faces[j][i][2]][1]),(corpo.normais[corpo.faces[j][i][2]][2])};
            glVertex3fv ( vert );
            glNormal3fv (nor);

         }
        glEnd( );
    }
    glPopMatrix();
}

void eixoFrontalWireFrame(void)  {
    glPushMatrix();
    for (unsigned int j = 0; j < (eixoFrontal.faces).size(); ++j )
    {
        glBegin ( GL_LINE_LOOP );
         for (unsigned int i = 0; i < (eixoFrontal.faces[j]).size() ; ++i )        {
            GLfloat vert[3] = {(eixoFrontal.vertices[eixoFrontal.faces[j][i][0]][0]),(eixoFrontal.vertices[eixoFrontal.faces[j][i][0]][1]),(eixoFrontal.vertices[eixoFrontal.faces[j][i][0]][2])};
            GLfloat nor[3] =  {(eixoFrontal.normais[eixoFrontal.faces[j][i][2]][0]),(eixoFrontal.normais[eixoFrontal.faces[j][i][2]][1]),(eixoFrontal.normais[eixoFrontal.faces[j][i][2]][2])};
            glVertex3fv ( vert );
            glNormal3fv (nor);

         }
        glEnd( );
    }
    glPopMatrix();
}

void eixoTraseiroWireFrame(void)  {
    glPushMatrix();
    for (unsigned int j = 0; j < (eixoTraseiro.faces).size(); ++j )
    {
        glBegin ( GL_LINE_LOOP );
         for (unsigned int i = 0; i < (eixoTraseiro.faces[j]).size() ; ++i )        {
            GLfloat vert[3] = {(eixoTraseiro.vertices[eixoTraseiro.faces[j][i][0]][0]),(eixoTraseiro.vertices[eixoTraseiro.faces[j][i][0]][1]),(eixoTraseiro.vertices[eixoTraseiro.faces[j][i][0]][2])};
            GLfloat nor[3] =  {(eixoTraseiro.normais[eixoTraseiro.faces[j][i][2]][0]),(eixoTraseiro.normais[eixoTraseiro.faces[j][i][2]][1]),(eixoTraseiro.normais[eixoTraseiro.faces[j][i][2]][2])};
            glVertex3fv ( vert );
            glNormal3fv (nor);

         }
        glEnd( );
    }
    glPopMatrix();
}

void janelaWireFrame(void)  {
    glPushMatrix();
    for (unsigned int j = 0; j < (janela.faces).size(); ++j )
    {
        glBegin ( GL_LINE_LOOP );
         for (unsigned int i = 0; i < (janela.faces[j]).size() ; ++i )        {
            GLfloat vert[3] = {(janela.vertices[janela.faces[j][i][0]][0]),(janela.vertices[janela.faces[j][i][0]][1]),(janela.vertices[janela.faces[j][i][0]][2])};
            GLfloat nor[3] =  {(janela.normais[janela.faces[j][i][2]][0]),(janela.normais[janela.faces[j][i][2]][1]),(janela.normais[janela.faces[j][i][2]][2])};
            glVertex3fv ( vert );
            glNormal3fv (nor);

         }
        glEnd( );
    }
    glPopMatrix();
}

void meteoroWireFrame(void)  {
    glPushMatrix();
    for (unsigned int j = 0; j < (meteoro.faces).size(); ++j )
    {
        glBegin ( GL_LINE_LOOP );
         for (unsigned int i = 0; i < (meteoro.faces[j]).size() ; ++i )        {
            GLfloat vert[3] = {(meteoro.vertices[meteoro.faces[j][i][0]][0]),(meteoro.vertices[meteoro.faces[j][i][0]][1]),(meteoro.vertices[meteoro.faces[j][i][0]][2])};
            GLfloat nor[3] =  {(meteoro.normais[meteoro.faces[j][i][2]][0]),(meteoro.normais[meteoro.faces[j][i][2]][1]),(meteoro.normais[meteoro.faces[j][i][2]][2])};
            glVertex3fv ( vert );
            glNormal3fv (nor);

         }
        glEnd( );
    }
    glPopMatrix();
}

void corpoSolid(void)  {

     glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, carro_id);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glPushMatrix();

    for (unsigned int j = 0; j < (corpo.faces).size(); ++j )
    {
        glBegin ( GL_POLYGON );
        for (unsigned int i = 0; i < (corpo.faces[j]).size() ; ++i )        {
            GLfloat vert[3] = {(corpo.vertices[corpo.faces[j][i][0]][0]),(corpo.vertices[corpo.faces[j][i][0]][1]),(corpo.vertices[corpo.faces[j][i][0]][2])};
            GLfloat nor[3] =  {(corpo.normais[corpo.faces[j][i][2]][0]),(corpo.normais[corpo.faces[j][i][2]][1]),(corpo.normais[corpo.faces[j][i][2]][2])};
             GLfloat tex[2] = {corpo.texturas[corpo.faces[j][i][1]][0], corpo.texturas[corpo.faces[j][i][1]][1]};
            glTexCoord2fv(tex);
            glVertex3fv ( vert );
            glNormal3fv (nor);
        }
        glEnd( );
    }

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void eixoFrontalSolid(void)  {

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, pneu_id);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glPushMatrix();

    for (unsigned int j = 0; j < (eixoFrontal.faces).size(); ++j )
    {
        glBegin ( GL_POLYGON );
        for (unsigned int i = 0; i < (eixoFrontal.faces[j]).size() ; ++i )        {
            GLfloat vert[3] = {(eixoFrontal.vertices[eixoFrontal.faces[j][i][0]][0]),(eixoFrontal.vertices[eixoFrontal.faces[j][i][0]][1]),(eixoFrontal.vertices[eixoFrontal.faces[j][i][0]][2])};
            GLfloat nor[3] =  {(eixoFrontal.normais[eixoFrontal.faces[j][i][2]][0]),(eixoFrontal.normais[eixoFrontal.faces[j][i][2]][1]),(eixoFrontal.normais[eixoFrontal.faces[j][i][2]][2])};
             GLfloat tex[2] = {eixoFrontal.texturas[eixoFrontal.faces[j][i][1]][0], eixoFrontal.texturas[eixoFrontal.faces[j][i][1]][1]};
            glTexCoord2fv(tex);
            glVertex3fv ( vert );
            glNormal3fv (nor);
        }
        glEnd( );
    }

    glPopMatrix();
        glDisable(GL_TEXTURE_2D);
}

void eixoTraseiroSolid(void)  {

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, pneu_id);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glPushMatrix();

    for (unsigned int j = 0; j < (eixoTraseiro.faces).size(); ++j )
    {
        glBegin ( GL_POLYGON );
        for (unsigned int i = 0; i < (eixoTraseiro.faces[j]).size() ; ++i )        {
            GLfloat vert[3] = {(eixoTraseiro.vertices[eixoTraseiro.faces[j][i][0]][0]),(eixoTraseiro.vertices[eixoTraseiro.faces[j][i][0]][1]),(eixoTraseiro.vertices[eixoTraseiro.faces[j][i][0]][2])};
            GLfloat nor[3] =  {(eixoTraseiro.normais[eixoTraseiro.faces[j][i][2]][0]),(eixoTraseiro.normais[eixoTraseiro.faces[j][i][2]][1]),(eixoTraseiro.normais[eixoTraseiro.faces[j][i][2]][2])};
             GLfloat tex[2] = {eixoTraseiro.texturas[eixoTraseiro.faces[j][i][1]][0], eixoTraseiro.texturas[eixoTraseiro.faces[j][i][1]][1]};
            glTexCoord2fv(tex);
            glVertex3fv ( vert );
            glNormal3fv (nor);
        }
        glEnd( );
    }

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void janelaSolid(void)  {

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, janela_id);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glPushMatrix();

    for (unsigned int j = 0; j < (janela.faces).size(); ++j )
    {
        glBegin ( GL_POLYGON );
        for (unsigned int i = 0; i < (janela.faces[j]).size() ; ++i )        {
            GLfloat vert[3] = {(janela.vertices[janela.faces[j][i][0]][0]),(janela.vertices[janela.faces[j][i][0]][1]),(janela.vertices[janela.faces[j][i][0]][2])};
            GLfloat nor[3] =  {(janela.normais[janela.faces[j][i][2]][0]),(janela.normais[janela.faces[j][i][2]][1]),(janela.normais[janela.faces[j][i][2]][2])};
            GLfloat tex[2] = {janela.texturas[janela.faces[j][i][1]][0], janela.texturas[janela.faces[j][i][1]][1]};
            glTexCoord2fv(tex);
            glVertex3fv ( vert );
            glNormal3fv (nor);
        }
        glEnd( );
    }

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void meteoroSolid(void)  {

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, meteoro_id);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glPushMatrix();

    for (unsigned int j = 0; j < (meteoro.faces).size(); ++j )
    {
        glBegin ( GL_POLYGON );
        for (unsigned int i = 0; i < (meteoro.faces[j]).size() ; ++i )        {
            GLfloat vert[3] = {(meteoro.vertices[meteoro.faces[j][i][0]][0]),(meteoro.vertices[meteoro.faces[j][i][0]][1]),(meteoro.vertices[meteoro.faces[j][i][0]][2])};
            GLfloat nor[3] =  {(meteoro.normais[meteoro.faces[j][i][2]][0]),(meteoro.normais[meteoro.faces[j][i][2]][1]),(meteoro.normais[meteoro.faces[j][i][2]][2])};
            GLfloat tex[2] = {meteoro.texturas[meteoro.faces[j][i][1]][0], meteoro.texturas[meteoro.faces[j][i][1]][1]};
            glTexCoord2fv(tex);
            glVertex3fv ( vert );

            glNormal3fv (nor);
        }
        glEnd( );
    }

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void posicionarMeteoro(){

        if(meteoroy > -1){
                meteoroy -= 0.5;
                //meteorox -= sin(1) -1;
                //meteoroz -= cos(1) -1;
        }
        else{
            meteorox = ((rand() % 20) + 1 - (rand() % 20));
            meteoroy = (rand() % 10) + 5;
            meteoroz = ((rand() % 20) + 1 - (rand() % 20));
        }
}

void gerarMeteoro(){
    DefineIluminacao();
    glPushMatrix();
    glScalef(4,4,4);
        glTranslatef(meteorox, meteoroy, meteoroz);

    glColor3f(1, 0.4, 0.4);
    meteoroSolid();
    glPopMatrix();


}

void Timer(int value)
{
    glutTimerFunc(50, Timer, value);
    glutPostRedisplay();
}

void
imprimirPlacar()
{
    char string[10] = {'0','1','2','3','4','5','6','7','8','9'};
    char dezena[3][2];
    dezena[0][0] = '0';
   unsigned int i, j;
   unsigned int count;

   GLfloat x, y, ystep, yild, stroke_scale;
    placarU = (placarGeral%10);
    placarD = (placarGeral - (placarGeral%10))/10;
    if(placarD == 9){
        placarC++;
    }
    if(placarGeral == 99) placarGeral = 0;

   /* Draw the strings, according to the current mode and font. */
   glColor4f(0.0, 1.0, 0.0, 0.0);
   x = 5;
   y = 5;
   ystep  = 100.0;
   yild   = 20.0;


      stroke_scale = 0.04f;
      glMatrixMode(GL_MODELVIEW);
      glPushMatrix(); {
         glTranslatef(x+20, y+1*yild, 0.0);
         glRotatef(180,0,1,0);
         glColor3f(0, 0, 0);
         glScalef(stroke_scale, stroke_scale, stroke_scale);
         print_stroke_string(GLUT_STROKE_ROMAN, "Placar Colisao:");
    }
    glPopMatrix();

          glPushMatrix(); {
         glTranslatef(x+20, y+0.75*yild, 0.0);
        glRotatef(180,0,1,0);
         glScalef(stroke_scale, stroke_scale, stroke_scale);
         glutStrokeCharacter(GLUT_STROKE_ROMAN, string[placarC]);
    }
    glPopMatrix();

      glPushMatrix(); {
         glTranslatef(x+16, y+0.75*yild, 0.0);
         glRotatef(180,0,1,0);
         glScalef(stroke_scale, stroke_scale, stroke_scale);
         glutStrokeCharacter(GLUT_STROKE_ROMAN, string[placarD]);
    }
    glPopMatrix();
}

void detectarColisao(){
    int x = meteorox - trans_x;
    int y;
    int z = meteoroz - trans_z;

    //printf("\n x:%d z:%d  carro: x:%d y:%d", meteorox,meteoro, trans_x,trans_z);
    //printf("\n x:%d y:%d", x,y);

    if(x < 5 && x > -5 && meteoroy < 2){
            if(z < 10 && z > -10){
               placarGeral++;
            }

    }

}



void Desenha(void){
    printf("\n%s", skin[0]);

    detectarColisao();
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 80);

    posicionarMeteoro();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();




    if(cam == 0){
      gluLookAt(lookx,looky,lookz, 0, 0, 0, 0,1,0);
    }
    else if(cam == 1){
         gluLookAt(trans_x - 35 * sin(rotY * Pi / 180), 15, trans_z - 35 * cos(rotY * Pi / 180), trans_x, 0, trans_z, 0, 1, 0);
    }



  DefineIluminacao();
  Piso(1.0, -2.0); //se desenhar com altura=0.0 n�o vamos ver,
                    //pois o plano n�o tem espessura

  gerarMeteoro();




  glPushMatrix();
    glTranslatef(trans_x,0,trans_z);
    glRotatef(rotY,0,1,0);
    glScalef(2.0, 2.0, 2.0);
    glColor3f(0.45, 0.49, 0.48);
    //glRotatef(rotTraseiro,1,0,0);
    eixoTraseiroSolid();
    eixoFrontalSolid();
    glRotatef(0,1,0,0);
    corpoSolid();
    glColor3f(0.98, 0.98, 0.98);
    janelaSolid();
    glColor3f(0.3, 0.3, 0.3);

    glPopMatrix();

imprimirPlacar();


  glutSwapBuffers();
}


int main(int argc, char** argv){
  glutInit(&argc, argv);

  glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

  glutInitWindowSize (800, 800);

  glutInitWindowPosition (0, 0);

  glutCreateWindow ("Trabalho Pratico - Erik Miguel");

  Inicializa();
  Timer(0);
  glutDisplayFunc(Desenha);

  glutSpecialFunc(TeclasEspeciais);
  glutKeyboardFunc(Teclado);

  glutMainLoop();
  return 0;
}
