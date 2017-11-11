
#include <GL/glew.h>
#include <GLUT/glut.h>
#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <iostream>

using namespace std;
int cnt = 0;
float level = 0;

void subdivide_dragon_out(float sx, float sy, float ex, float ey, int depth, float r, float g, float b);
void subdivide_dragon_in(float sx, float sy, float ex, float ey, int depth, float r, float g, float b);
void myinit(void)
{
    
    /* attributes */
    
    glClearColor(0.9, 1.0, 1.0, 1.0); /* white background */
    glColor3f(1.0, 0.0, 0.0); /* draw in red */
    
    /* set up viewing */
    /* 500 x 500 window with origin lower left */
    
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //gluOrtho2D(-250.0, 500.0, -250.0, 500.0);
    //glMatrixMode(GL_MODELVIEW);
}

void reshape(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluOrtho2D (0.0, (GLdouble) w, 0.0, (GLdouble) h);
    
}



void subdivide(float sx, float sy, float ex, float ey, int depth)
{
    //cout << "inside subdivide = " << cnt << "depth = " << depth << endl;
    //cnt++;
    
    if(depth==0)
    {
        
        glVertex2f(sx,sy);
        glColor3f(0.0, 0.0, 1.0);
        glVertex2f(ex,ey);
        glColor3f(0.0, 0.0, 1.0);

        
        return;
    }
    float r = sqrt((ex-sx)*(ex-sx) + (ey-sy)*(ey-sy) )/3.0f;
    float tempsx = sx+(ex-sx)/3.0f;
    float tempsy = sy+(ey-sy)/3.0f;
    float tempex = sx+2.0f*(ex-sx)/3.0f;
    float tempey = sy+2.0f*(ey-sy)/3.0f;
    float nextx = (tempex-tempsx)*cos(60.0f*3.14f/180.0f) - (tempey-tempsy)*sin(60.0f*3.14f/180.0f) + tempsx;
    float nexty = (tempex-tempsx)*sin(60.0f*3.14f/180.0f) + (tempey-tempsy)*cos(60.0f*3.14f/180.0f) + tempsy;

    
    subdivide(sx, sy, tempsx, tempsy, depth-1);
    subdivide(tempsx, tempsy, nextx, nexty, depth-1);
    subdivide(nextx, nexty, tempex, tempey, depth-1);
    subdivide(tempex, tempey, ex, ey, depth-1);
    
    
}

void snowflake()
{
    level = (level + 0.01);
    if(level>6)
        level=0;
    glBegin(GL_LINES);
    float r = 0.90f;
    float stheta = 90.0f;
    subdivide(r*cos(stheta*3.14/180.0f), r*sin(stheta*3.14/180.0f), r*cos((stheta-120.0f)*3.14/180.0f), r*sin((stheta-120.0f)*3.14/180.0f), (int)level);
    
    stheta -= 120.0f;
    
    subdivide(r*cos(stheta*3.14/180.0f), r*sin(stheta*3.14/180.0f), r*cos((stheta-120.0f)*3.14/180.0f), r*sin((stheta-120.0f)*3.14/180.0f), (int)level);
    
    stheta -= 120.0f;
    
    subdivide(r*cos(stheta*3.14/180.0f), r*sin(stheta*3.14/180.0f), r*cos((stheta-120.0f)*3.14/180.0f), r*sin((stheta-120.0f)*3.14/180.0f), (int)level);
    
    r = 0.45f;
    stheta = 270.0f;
    subdivide(r*cos(stheta*3.14/180.0f), r*sin(stheta*3.14/180.0f), r*cos((stheta-120.0f)*3.14/180.0f), r*sin((stheta-120.0f)*3.14/180.0f), (int)level);
    
    stheta -= 120.0f;
    
    subdivide(r*cos(stheta*3.14/180.0f), r*sin(stheta*3.14/180.0f), r*cos((stheta-120.0f)*3.14/180.0f), r*sin((stheta-120.0f)*3.14/180.0f), (int)level);
    
    stheta -= 120.0f;
    
    subdivide(r*cos(stheta*3.14/180.0f), r*sin(stheta*3.14/180.0f), r*cos((stheta-120.0f)*3.14/180.0f), r*sin((stheta-120.0f)*3.14/180.0f), (int)level);
    
    
    
    glEnd();

}

void subdivide_dragon_in(float sx, float sy, float ex, float ey, int depth, float r, float g, float b)
{
    if(depth==0)
    {
        glVertex2f(sx,sy);
        glColor3f(r, g, b);
        glVertex2f(ex,ey);
        glColor3f(r, g, b);
        return;
    }
    float tempsx = sx;
    float tempsy = sy;
    float tempex = sx+sqrt(2.0f)*(ex-sx)/2.0f;
    float tempey = sy+sqrt(2.0f)*(ey-sy)/2.0f;
    float nextx = (tempex-tempsx)*cos(45.0f*3.14f/180.0f) - (tempey-tempsy)*sin(45.0f*3.14f/180.0f) + tempsx;
    float nexty = (tempex-tempsx)*sin(45.0f*3.14f/180.0f) + (tempey-tempsy)*cos(45.0f*3.14f/180.0f) + tempsy;

    subdivide_dragon_in( sx,  sy, nextx, nexty, depth-1,r,g,b);
    subdivide_dragon_out(nextx, nexty,  ex,  ey, depth-1,r,g,b);
    
}

void subdivide_dragon_out(float sx, float sy, float ex, float ey, int depth, float r, float g, float b)
{
    if(depth==0)
    {
        glVertex2f(sx,sy);
        glColor3f(r, g, b);
        glVertex2f(ex,ey);
        glColor3f(r, g, b);
        return;
    }
    
    float tempsx = sx;
    float tempsy = sy;
    float tempex = sx+sqrt(2.0f)*(ex-sx)/2.0f;
    float tempey = sy+sqrt(2.0f)*(ey-sy)/2.0f;
    float nextx = (tempex-tempsx)*cos(-45.0f*3.14f/180.0f) - (tempey-tempsy)*sin(-45.0f*3.14f/180.0f) + tempsx;
    float nexty = (tempex-tempsx)*sin(-45.0f*3.14f/180.0f) + (tempey-tempsy)*cos(-45.0f*3.14f/180.0f) + tempsy;
    
    subdivide_dragon_in( sx,  sy, nextx, nexty, depth-1,r,g,b);
    subdivide_dragon_out(nextx, nexty,  ex,  ey, depth-1,r,g,b);
    
    
}


void dragoncurve()
{
    level = (level + 0.015);
    if(level>16)
        level=0;
    
    glBegin(GL_LINES);
    //curve 1
    subdivide_dragon_in(0.0f,0.0f,0.0f,0.5f,level,1.0f,0.0f,0.0f);
    subdivide_dragon_out(0.0f,0.5f,0.5f,0.5f,level,1.0f,0.0f,0.0f);
    
    //curve2
    subdivide_dragon_in(0.0f,0.0f,0.5f,0.0f,level,0.0f,1.0f,0.0f);
    subdivide_dragon_out(0.5f,0.0f,0.5f,-0.5f,level,0.0f,1.0f,0.0f);
    
    //curve 3
    subdivide_dragon_in(0.0f,0.0f,0.0f,-0.5f,level,0.0f,0.0f,1.0f);
    subdivide_dragon_out(0.0f,-0.5f,-0.5f,-0.5f,level,0.0f,0.0f,1.0f);
    
    //curve4
    subdivide_dragon_in(0.0f,0.0f,-0.5f,0.0f,level,0.0f,0.0f,0.0f);
    subdivide_dragon_out(-0.5f,0.0f,-0.5f,0.5f,level,0.0f,0.0f,0.0f);
    
    //subdivide_dragon_in(0.0f,0.5f,0.0f,0.0f,11);
    //subdivide_dragon_out(0.0f,0.0f,0.5f,0.0f,11);
    
    glEnd();

}


void display( void )
{
    
 /* An arbitrary initial point inside traingle */
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  /*clear the window */
    /* plot new point */

    //snowflake();
    dragoncurve();
    
    glutSwapBuffers();
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    
    /* Standard GLUT initialization */
    
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); /* default, not needed */
    glutInitWindowSize(500, 500); /* 500 x 500 pixel window */
    glutInitWindowPosition(0, 0); /* place window top left on display */
    glutCreateWindow("Dragon Curve"); /* window title */
    glutDisplayFunc(display); /* display callback invoked when window opened */
    //glutReshapeFunc(reshape);
    glewExperimental = GL_TRUE;
    glewInit();
    
    myinit(); /* set attributes */
    
    glutMainLoop(); /* enter event loop */
    
    return 0;
}
