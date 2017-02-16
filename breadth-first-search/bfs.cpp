#include <bits/stdc++.h>
#include <GL/glut.h>
#include "../include/graph-graphics.h"

int *color; // holds the colors of nodes
map<int, vector<int> > adjlist; // maps node number to a vector containing node numbers of neighbours
int vt=0; // no of vertices drawn
size_t n=0 , e=0; // no of nodes and edges
pair< int , int> *coordinates; // array of coordinates of nodes

void display(); // prototype


void BFS(int src) // bfs algo
{
	vector<int> neighbours = adjlist[src];
	cout<<"exploring neighbors of "<<src; nl
	queue<int> q;
	for( int i : neighbours)
	{
		if(color[i] == WHITE)
		{
			color[i]=GRAY;
			cout<<"greying node "<<i; nl
			display();
			q.push(i);
		}
	}
	while(!q.empty())
	{
		BFS(q.front());
		q.pop();		
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
				BFS(i);
			}
		}
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
	glutCreateWindow("Breadth First Search");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutReshapeFunc(handleResize);
	glutMainLoop();
	return 0;
}
