#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include "funs.h"
#include <string>
#include <iostream>
#define COLUMNS 50
#define FPS 60
using namespace std;

int rposx=15;
int score=0;
int lives=9;
bool over=false;
int enemypos=rand()%(COLUMNS-30)+3;
int missileposx=rposx;
int missileposx1;
int index1=50;
int index=4;

void display();
void timer(int);
void reshape(int,int);
void keyboard(int key,int x,int y);
void drawgrid();
void unit(int x,int y);
void drawsq(int x,int y);
void drawrocket(int,int);
void drawmissiles(int x);
void generateenemy(int );
void drawenemy(int,int);
void drawscore();
void drawborder();
void printhearts(int);
void drawheart(int,int);
void gameover();
void type(int);
void print(int,int,int);


int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500,500);
    glutCreateWindow("GAME");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);
    glutTimerFunc(0,timer,0);
    glutMainLoop();
    return 0;

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    //drawgrid();
    drawrocket(rposx,1);
    drawscore();
    drawborder();
    drawmissiles(missileposx);
    generateenemy(enemypos);
    if((index1==index || index1+1==index || index1-1==index) && (missileposx==enemypos || missileposx==enemypos+1 || missileposx== enemypos-1))
    {
        index=0;
        index1=0;
        score++;
    }
    if(index1==1)
    {
        lives--;
    }
    if(lives==0)
    {
        over=true;
    }
    cout<<lives/3<<" "<<score<<endl;
    glutSwapBuffers();
}

void reshape(int x,int y)
{
    glViewport(0,0,x,y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,COLUMNS,0,COLUMNS,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int)
{
    if(!over)
        glutPostRedisplay();
    else
        gameover();
    glutTimerFunc((1000/FPS),timer,0);
}

void keyboard(int key,int x,int y)
{
    switch(key)
    {
        case GLUT_KEY_LEFT:
            if(rposx<5){}
            else
            {
            rposx-=2;
            }
            break;
        case GLUT_KEY_RIGHT:
            if(rposx>COLUMNS-24){}
            else
            {
            rposx+=2;
            }
            break;
    }
}

void drawgrid()
{
    for(int x=0;x<COLUMNS;x++)
    {
        for(int y=0;y<COLUMNS;y++)
        {
            unit(x,y);
        }
    }
}

void unit(int x,int y)
{
    if(x==0 || y==0 || x==COLUMNS-1 || y==COLUMNS-1)
        glColor3d(1.0,0.0,0.0);
    else
        glColor3d(1.0,1.0,1.0);
    glBegin(GL_LINE_LOOP);
        glVertex2d(x,y);
        glVertex2d(x,y+1);
        glVertex2d(x+1,y+1);
        glVertex2d(x+1,y);
    glEnd();
}


void drawsq(int x,int y,double r,double b,double g)
{
    glColor3d(r,b,g);
    glBegin(GL_POLYGON);
    glVertex2d(x,y);
    glVertex2d(x,y+1);
    glVertex2d(x+1,y+1);
    glVertex2d(x+1,y);
    glEnd();
}

void drawrocket(int x,int y)
{
    drawsq(x,y,0.0,0.0,1.0);
    drawsq(x,y+1,0.0,0.0,1.0);
    drawsq(x-1,y,0.0,0.0,1.0);
    drawsq(x+1,y,0.0,0.0,1.0);
}

void drawmissiles(int x)
{
    drawsq(x,index,1.0,0.3,0.3);
    index++;
    if(index>COLUMNS)
    {
        index=4;
        missileposx=rposx;
    }
}

void generateenemy(int x)
{
    drawenemy(x,index1);
    if(index%2==0)
    index1--;
    if(index1==0)
    {
        index1=50;
        enemypos=rand()%(COLUMNS-30)+3;
    }
}

void drawenemy(int x,int y)
{
    drawsq(x,y,1.0,1.0,1.0);
    drawsq(x-1,y,1.0,rand()%1,rand()%1);
    drawsq(x+1,y,1.0,rand()%1,rand()%1);
    drawsq(x,y+1,1.0,rand()%1,rand()%1);
    drawsq(x,y-1,1.0,rand()%1,rand()%1);
}


void drawscore()
{
    glColor3d(0.0,0.0,1.0);
    //draw s
    glBegin(GL_LINE_LOOP);
    glVertex2d(36,45);
    glVertex2d(35,45);
    glVertex2d(35,44);
    glVertex2d(36,44);
    glVertex2d(36,43);
    glVertex2d(35,43);
    glVertex2d(36,43);
    glVertex2d(36,44);
    glVertex2d(35,44);
    glVertex2d(35,45);
    glEnd();

    //draw c
    glBegin(GL_LINE_LOOP);
    glVertex2d(38,45);
    glVertex2d(37,45);
    glVertex2d(37,43);
    glVertex2d(38,43);
    glVertex2d(37,43);
    glVertex2d(37,45);
    glEnd();

    //draw o
    glBegin(GL_LINE_LOOP);
    glVertex2d(39,45);
    glVertex2d(40,45);
    glVertex2d(40,43);
    glVertex2d(39,43);
    glEnd();

    //draw r
    glBegin(GL_LINE_LOOP);
    glVertex2d(41,45);
    glVertex2d(41,43);
    glVertex2d(41,44);
    glVertex2d(42,43);
    glVertex2d(41,44);
    glVertex2d(42,44);
    glVertex2d(42,45);
    glEnd();

    //draw e
    glBegin(GL_LINE_LOOP);
    glVertex2d(44,45);
    glVertex2d(43,45);
    glVertex2d(43,44);
    glVertex2d(44,44);
    glVertex2d(43,44);
    glVertex2d(43,43);
    glVertex2d(44,43);
    glVertex2d(43,43);
    glVertex2d(43,45);
    glEnd();

    //draw dash
    glBegin(GL_LINE_LOOP);
    glVertex2d(45,44);
    glVertex2d(46,44);
    glEnd();

    printhearts(lives/3);

    glColor3d(1.0,0.0,0.0);
    type(score);
}

void drawborder()
{
    glColor3d(1.0,1.0,1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2d(1,0);
    glVertex2d(1,50);
    glVertex2d(30,50);
    glVertex2d(30,0);
    glEnd();
}

void gameover()
{
    glClear(GL_COLOR_BUFFER_BIT);
    char text[30]="GAME OVER";
    int len=strlen(text);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0,600,0,600,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(220,300);

    for(int i=0;i<len;i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,text[i]);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glutSwapBuffers();
}

void type(int x)
{
    int ones,tens;
    tens=x%10;
    ones=x/10;
    print(ones,47,43);
    print(tens,49,43);
}

void print(int a,int x,int y)
{
    if(a==1)
    {
        glBegin(GL_LINES);
            glVertex2d(x+1,y+2);
            glVertex2d(x+1,y);
        glEnd();

    }
    if(a==2)
    {
        glBegin(GL_LINES);
            glVertex2d(x,y+2);
            glVertex2d(x+1,y+2);
            glVertex2d(x+1,y+2);
            glVertex2d(x+1,y+1);
            glVertex2d(x+1,y+1);
            glVertex2d(x,y+1);
            glVertex2d(x,y+1);
            glVertex2d(x,y);
            glVertex2d(x,y);
            glVertex2d(x+1,y);
        glEnd();
    }
    if(a==3)
    {
        glBegin(GL_LINES);
            glVertex2d(x,y);
            glVertex2d(x+1,y);
            glVertex2d(x+1,y);
            glVertex2d(x+1,y+2);
            glVertex2d(x,y+1);
            glVertex2d(x+1,y+1);
            glVertex2d(x,y+2);
            glVertex2d(x+1,y+2);
        glEnd();
    }
    if(a==4)
    {
        glBegin(GL_LINES);
            glVertex2d(x+1,y);
            glVertex2d(x+1,y+2);
            glVertex2d(x,y+1);
            glVertex2d(x+1,y+1);
            glVertex2d(x,y+2);
            glVertex2d(x,y+1);
        glEnd();
    }
    if(a==5)
    {
        glBegin(GL_LINES);
            glVertex2d(x,y+2);
            glVertex2d(x+1,y+2);
            glVertex2d(x,y+2);
            glVertex2d(x,y+1);
            glVertex2d(x,y+1);
            glVertex2d(x+1,y+1);
            glVertex2d(x+1,y+1);
            glVertex2d(x+1,y);
            glVertex2d(x+1,y);
            glVertex2d(x,y);
        glEnd();
    }
    if(a==6)
    {
        glBegin(GL_LINES);
            glVertex2d(x,y);
            glVertex2d(x,y+2);
            glVertex2d(x,y);
            glVertex2d(x+1,y);
            glVertex2d(x+1,y);
            glVertex2d(x+1,y+1);
            glVertex2d(x+1,y+1);
            glVertex2d(x,y+1);
            glVertex2d(x,y+2);
            glVertex2d(x+1,y+2);
        glEnd();
    }
    if(a==7)
    {
        glBegin(GL_LINES);
            glVertex2d(x,y+2);
            glVertex2d(x+1,y+2);
            glVertex2d(x+1,y+2);
            glVertex2d(x+1,y);
        glEnd();
    }
    if(a==8)
    {
        glBegin(GL_LINES);
            glVertex2d(x,y);
            glVertex2d(x+1,y);
            glVertex2d(x,y+1);
            glVertex2d(x+1,y+1);
            glVertex2d(x,y+2);
            glVertex2d(x+1,y+2);
            glVertex2d(x,y);
            glVertex2d(x,y+2);
            glVertex2d(x+1,y);
            glVertex2d(x+1,y+2);
        glEnd();
    }
    if(a==9)
    {
        glBegin(GL_LINES);
            glVertex2d(x,y);
            glVertex2d(x+1,y);
            glVertex2d(x,y+1);
            glVertex2d(x+1,y+1);
            glVertex2d(x,y+2);
            glVertex2d(x+1,y+2);
            glVertex2d(x,y+1);
            glVertex2d(x,y+2);
            glVertex2d(x+1,y);
            glVertex2d(x+1,y+2);
        glEnd();
    }
    if(a==0)
    {
        glBegin(GL_LINES);
            glVertex2d(x,y);
            glVertex2d(x+1,y);
            glVertex2d(x,y+2);
            glVertex2d(x+1,y+2);
            glVertex2d(x,y);
            glVertex2d(x,y+2);
            glVertex2d(x+1,y);
            glVertex2d(x+1,y+2);
        glEnd();
    }
}


void printhearts(int l)
{
    if(l>=1)
        drawheart(44,39);
    if(l>=2)
        drawheart(37,39);
    if(l>=3)
        drawheart(30,39);
}

void drawheart(int x,int y)
{
    glColor3d(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
        glVertex2d(x+3,y);
        glVertex2d(x+6,y+2);
        glVertex2d(x+5,y+3);
        glVertex2d(x+4,y+3);
        glVertex2d(x+3,y+2);
        glVertex2d(x+2,y+3);
        glVertex2d(x+1,y+3);
        glVertex2d(x,y+2);
    glEnd();
}
