#include <bits/stdc++.h>
#include <GL/glut.h>
#include "../include/graph-graphics.h"
using namespace std;

int *color; // holds the colors of nodes
int *ecolor; //holds the colors of edges for final shortest path display
map< int, vector< pair<int, int > > > adjlist; // maps node number to a vector containing node numbers of neighbours
vector< vector<int > > edges;  // to store edges and sort them by weight

int vt=0; // no of vertices drawn
size_t n=0 , e=0; // no of nodes and edges
pair< int , int> *coordinates; // array of coordinates of nodes
int *distance;

void display(); // prototype

bool done=false; //to display the result if the algo is done running
set<int> MST; // set to maintain members of MST

bool compare(vector<int> a, vector<int> b)  
{  
    return (a[2]>b[2]);	
}
void EraseEdge(int u,int v)
{
	int count=0;
	for(auto a: adjlist[u])
	{
		if(a.first == v)
			break;
		else
			count++;
	}
	adjlist[u].erase(adjlist[u].begin()+count);
	return;
}
void krushkal() // dijkstra algo
{
	sort(edges.begin(),edges.end(),compare); // sort in ascending order
	cout<<"done sorting";
	vector<int> temp;
	temp = edges.back();
	edges.pop_back();
	MST.insert(temp[0]);
	MST.insert(temp[1]);
	while(!edges.empty())
	{
		temp= edges.back();
		edges.pop_back();
		if(MST.count(temp[1]) == 0)
		{
			MST.insert(temp[1]);
		}
		else // else, there's a cycle. delete that expensive cyclic edge
		{
			EraseEdge(temp[0],temp[1]);
		}
	}
	done=true;
	//display();
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
        cout<<"\nRunning Krushkal\n";
		krushkal();
		//done=true;
    }
}
void display()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.3f, 0.8f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(!done)
    {
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
	}
	else //dijkstra is done. now display the result
	{
		cout<<"\n Done. Displaying result.\n";
		for(auto a : MST)
		{
			color[a] = GREEN;
		}
		/*for(int i=0;i<vt;i++)
	    {
	        str=to_string(::distance[i]);
	        drawCircle(color[i],coordinates[i]);
	    }*/
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
	cout<<"Enter the number of nodes in the graph"; nl
	cin>>n;
	color =  new int[n];
	::distance =  new int[n];
	coordinates= new pair< int ,int > [n];
	cout<<"Enter the number of edges in the graph"; nl
	cin>>e;
	ecolor = new int[n];
	cout<<"Enter the edges of the graph (u --> v) pairs and their weight w"; nl
	size_t u,v,w;
	vector<int> w_edge;
	for(int i=0;i<e;i++)
	{
		cin>>u>>v>>w;
		w_edge.push_back(u);
		w_edge.push_back(v);
		w_edge.push_back(w);
		adjlist[u].push_back(make_pair(v,w));
		edges.push_back(w_edge);
	}
	/**/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Dijkstra");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutReshapeFunc(handleResize);
	glutMainLoop();
	return 0;
}
