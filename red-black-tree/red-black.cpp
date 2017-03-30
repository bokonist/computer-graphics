#include <bits/stdc++.h>
#include <GL/glut.h>
#include "../include/graph-graphics.h"
using namespace std;
#define dbg(i) cout<<"\nbreak "<<i<<endl;

int vt=0; // no of vertices drawn
size_t n=0; // no of nodes and edges
pair< int , int> *coordinates; // array of coordinates of nodes

void display(); // prototype
bool NullPointer(auto *a)
{
	if(a == NULL)
		return true;
	else
		return false;
}

class node
{
	int color;
	int value;
	node *left;
	node *right;
	node *parent;
	node *uncle;
	node *grandfather;
	bool sentinel;
	node()
	{
		left = null;
		right = null;
		parent = null;
		uncle = null;
		grandfather = null;
		sentinel = false;
	}
	bool assignUncle()
	{
		if( !NullPointer(parent) && !NullPointer(parent->parent))
		{
			if(!NullPointer(parent -> parent -> left) && parent = parent -> parent -> left)
			{
				if(!NullPointer(parent->parent->right))
				{
					uncle = parent -> parent -> right;
					return true; 
				}
			}
			else if(!NullPointer(parent -> parent -> right) && parent = parent -> parent -> right)
			{
				if(!NullPointer(parent->parent->left))
				{
					uncle = parent -> parent -> left;
					return true; 
				}
			}
			else
				return false;
		}
		else
			return false;
	}
	bool assignGrandfather()
	{
		if(!NullPointer(parent) && !NullPointer(parent->parent))
		{
			grandfather = parent-> parent;
			return true;
		}
		else
			return false;
	}
}
node *root;

void mouse(int button, int state, int x, int y)  
{  
    if(vt!=n)
    {
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)   
        { 
            coordinates[vt].first = x;
            coordinates[vt].second = (700-y);
            cout<< coordinates[vt].first <<'\t'<<  coordinates[vt].second <<'\n';
            vt++;
            display();
        }
    }
    else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)   
    {
        cout<<"\nRunning Krushkal\n";
		krushkal();
		display();
    }
}
void display()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.3f, 0.8f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(int i=0;i<vt;i++)
    {
        str=to_string(i);
        drawCircle(color[i],coordinates[i]);
    }
    if(vt==n)
    {
        for(int i=0;i<n;i++)
        {
        	vector< pair <int ,int > > neighbours = adjlist[i];
        	for( pair<int ,int > j : neighbours)
        	{
        		drawEdge(coordinates[i],coordinates[j.first]);
        	}
        }
    }
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
	cout<<"Enter the Red-black tree elements (no duplicates) (enter x to stop)"; nl
	string val;
	cin>>val;
	n=0;
	while(val!= "x")
	{
		RB_INSERT(stoi(val.c_str()));
		n++;
	}
	coordinates= new pair< int ,int > [n]; // the coordinates of nodes
	/**/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(500, 100);
	glutCreateWindow("Red-black tree");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutReshapeFunc(handleResize);
	glutMainLoop();
	return 0;
}
