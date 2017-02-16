#include <bits/stdc++.h>
#include <GL/glut.h>
#include "graph-graphics.h"

using namespace std;


int *color; // holds the colors of nodes
map<int, vector<int> > adjlist; // maps node number to a vector containing node numbers of neighbours
int vt=0; // no of vertices drawn
size_t n=0 , e=0; // no of nodes and edges
pair< int , int> *coordinates; // array of coordinates of nodes

/*string str; // to hold the node number to print on nodes
GLvoid *font_style = GLUT_BITMAP_HELVETICA_18;
GLubyte fillCol[3] = {255,255,255}; //interior color of node (white)
GLubyte borderCol[3] = {0,0,0}; // border color of node (black)
GLubyte fillColt[3];
GLubyte strcol[3]={230,100,80}; // string color of node number (red)*/
void display(); // prototype


void DFS(int src) // dfs algo
{
    cout<<"greying node "<<src; nl
    color[src]= GRAY;
    display();
    vector<int> neighbours = adjlist[src];
    cout<<"exploring neighbors of "<<src; nl
    stack<int> s;
    for( int i : neighbours)
    {
        if(color[i] == WHITE)
            s.push(i);
    }
    while(!s.empty())
    {
        DFS(s.top());
        s.pop();        
    }
    cout<<"blacking. completely visited "<<src; nl
    color[src]= BLACK;
    display();
}

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
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)   
    {
        cout<<"\nRunning BFS\n";
        for(int i=0;i<n;i++)
		{
			if(color[i]==WHITE)
			{
				cout<<"greying node "<<i; nl
				color[i]=GRAY;
				display();
				DFS(i);
			}
		}
    }
}
void display()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.6f, 0.9f, 1.0f);
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
        	vector<int> neighbours = adjlist[i];
        	for( int j : neighbours)
        	{
        		drawEdge(coordinates[i],coordinates[j]);
        	}
        }
    }
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
	cout<<"Enter the number of nodes in the graph"; nl
	cin>>n;
	color =  new int[n];
	coordinates= new pair< int ,int > [n];
	memset(color, WHITE,n*sizeof(int));
	cout<<"Enter the number of edges in the graph"; nl
	cin>>e;
	cout<<"Enter the edges of the graph (u --> v) pairs"; nl
	size_t u,v;
	for(int i=0;i<e;i++)
	{
		cin>>u>>v;
		adjlist[u].push_back(v);
	}
	/**/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Depth First Search");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutReshapeFunc(handleResize);
	glutMainLoop();
	return 0;
}
