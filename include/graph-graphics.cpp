//#include <bits/stdc++.h>
#include "graph-graphics.h"
using namespace std;


string str; // to hold the node number to print on nodes
GLvoid *font_style = GLUT_BITMAP_HELVETICA_18;
GLubyte fillCol[3] = {255,255,255}; //interior color of node (white)
GLubyte borderCol[3] = {0,0,0}; // border color of node (black)
GLubyte fillColt[3];
GLubyte strcol[3]={230,100,80}; // string color of node number (red)

void drawstr(GLuint x, GLuint y, const char* format, int length)// draw string on screen
{
    glRasterPos2i(x, y);  
    for(int i=0; i<length; ++i)
    {
        glutBitmapCharacter(font_style, *(format+i) );
    }
}
void getPixel(int x, int y, GLubyte pixels[3])
{  
    glReadPixels(x,y,1.0,1.0,GL_RGB,GL_UNSIGNED_BYTE,pixels);  
} 

void setPixel(GLint x, GLint y) // set pixel as black
{
  glBegin(GL_POINTS);
   glColor3f(0,0,0);
   glVertex2i(x,y);
  glEnd();
}
void setPixelcol(int pointx, int pointy, GLubyte f[3]) // set a color pixel 
{  
       glBegin(GL_POINTS);  
           glColor3ubv(f);  
           glVertex2i(pointx,pointy);  
       glEnd();    
} 
void boundaryFill4(int x,int y,GLubyte fillColor[3],GLubyte borderColor[3])   //boundary fill algo
{  
    GLubyte interiorColor[3]; 
    GLubyte strintcol[3];   
    getPixel(x,y,interiorColor);  
    if(interiorColor[0]==strcol[0])
       {
          getPixel(x+1,y+1,strintcol);
          if(strintcol[0]!=fillColor[0])
          {
            boundaryFill4(x+1,y,fillColor,borderColor); 
          }
       }
    if((interiorColor[0]!=borderColor[0] && (interiorColor[1])!=borderColor[1] && (interiorColor[2])!=borderColor[2]) && (interiorColor[0]!=fillColor[0] && (interiorColor[1])!=fillColor[1] && (interiorColor[2])!=fillColor[2]))  
    {  
            setPixelcol(x,y,fillColor);
            if((interiorColor[0]!=strcol[0]) && (interiorColor[1]!=strcol[1]) && (interiorColor[2]!=strcol[2]) )
            { 
             boundaryFill4(x+1,y,fillColor,borderColor);  
             boundaryFill4(x-1,y,fillColor,borderColor);  
             boundaryFill4(x,y+1,fillColor,borderColor);  
             boundaryFill4(x,y-1,fillColor,borderColor);  
           } 
    }  
}


void drawCircle(int color,pair <int , int> center) // midpoint circle drawing algo
{
	int xCenter=center.first, yCenter=center.second, r=30;
	int x=0,y=r;
	int p = 3/2 - r;
	glColor3f( 0 ,0, 0);
	while(x<=y)
	{
		setPixel(xCenter+x,yCenter+y);
		setPixel(xCenter+y,yCenter+x);
		setPixel(xCenter-x,yCenter+y);
		setPixel(xCenter+y,yCenter-x);
		setPixel(xCenter-x,yCenter-y);
		setPixel(xCenter-y,yCenter-x);
		setPixel(xCenter+x,yCenter-y);
		setPixel(xCenter-y,yCenter+x);
		if (p<0)
			p += (2*x)+3;
		else 
		{ 
			p += (2*(x-y))+5;
			y -= 1;
		}
		x++;
	}
	if(color== WHITE)
	{
		fillColt[0]= 255;
		fillColt[1]= 255;
		fillColt[2]= 255;
	}
	if(color == GRAY)
	{
		fillColt[0]= 128;
		fillColt[1]= 128;
		fillColt[2]= 128;
	}
	if(color == BLACK)
	{
		fillColt[0]= 0;
		fillColt[1]= 0;
		fillColt[2]= 0;
	}
	glColor3ubv(strcol);
	drawstr(xCenter-5,yCenter-5, str.c_str(), str.length());
	boundaryFill4(xCenter+15,yCenter+15,fillColt,borderCol); 
}
void drawEdge(pair<int ,int> p, pair<int, int> q) // line drawing algo
{
    int x1,x2,y1,y2;
    x1= p.first;
    x2= q.first;
    y1= p.second;
    y2= q.second;

    int dx, dy, x, y, d, s1, s2, swap=0, temp;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    s1 = sign(x2-x1);
    s2 = sign(y2-y1);

    if(dy > dx)
    {
        temp = dx;
        dx = dy; 
        dy = temp;
        swap = 1;
    }

    d = 2 * dy - dx;
    x = x1;
    y = y1;

    int i;

    for(i = 1; i < dx; i++)
    {
        setPixel(x,y);

        while(d>=0)
        {
            d=d-2*dx;
            if(swap)
                x+=s1;
            else
                y+=s2;
        }

        d=d+2*dy;
        if(swap)
            y+=s2;
        else
            x+=s1;
    }
}
void handleResize(int w, int h)
{
    glMatrixMode(GL_PROJECTION);   // Transformations being applied to Projection Matrix
    glLoadIdentity();   // Always call after changing matrix
    glViewport(0,0,w,h);
    gluOrtho2D(0.0,700.0,0.0,700.0); // Here object is being moved along with window, wx & hy window size. Here clipping range is zNear=1,zFar=-200
    glMatrixMode(GL_MODELVIEW); // Transformations on ModelView Matrix(default)
}