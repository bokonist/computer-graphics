#include <bits/stdc++.h>
#include <GL/glut.h>
#include "../include/graph-graphics.h"
using namespace std;

int *color; // holds the colors of nodes
int *ecolor; //holds the colors of edges for final shortest path display
map< int, vector< pair<int, int > > > adjlist; // maps node number to a vector containing node numbers of neighbours
int vt=0; // no of vertices drawn
size_t n=0 , e=0; // no of nodes and edges
pair< int , int> *coordinates; // array of coordinates of nodes
int *distance;
int *predecessor;
void display(); // prototype
vector <int> shortest_path;
bool done=false; //to display the result if the algo is done running


struct compare  
 {  
   bool operator()(const int& l, const int& r)  
   {  
       return l > r;  
   }  
 };
priority_queue<int,vector<int>, compare > prio_queue; // min prio queue
void init_dijkstra(int source)
{
	/*memset(color, WHITE,n*sizeof(int));
	memset(::distance, INT_MAX ,n*sizeof(int));
	memset(::predecessor , -1 , n*sizeof(int)); // -1 stands for NIL*/
	for(int i=0;i<n;i++)
	{
		color[i]=WHITE;
		::distance[i]=INT_MAX;
		::predecessor[i]=-1;
	}
	::distance[source] = 0;
}
int findnode(int d)
{
	for (int i = 0; i < n; ++i)
	{
		if(::distance[i]==d)
			return i;
	}
}
void relax(int u, int v, int w)
{
	int temp = w + ::distance[u];
	if(::distance[v] > temp)
	{
		::distance[v] = temp;
		predecessor[v]=u;
	}
}
void updatePrioQueue(bool firstcall=false)
{
	while(!prio_queue.empty())
		prio_queue.pop();
	if(firstcall)
		prio_queue.push(::distance[0]);
	for (int i = 0; i < n; ++i)
	{
		if(color[i]==WHITE)
		{
			//cout<<"Node "<<i<<" is white\n";
			cout<<"Pushing "<<::distance[i]<<" to prio queue\n";
			prio_queue.push(::distance[i]);
		}
		cout<<endl;
	}
}
void dijkstra(int src) // dijkstra algo
{
	shortest_path.push_back(src);
	predecessor[src] = -1;
	updatePrioQueue(true);
	while(!prio_queue.empty())
	{
		int u_temp= findnode(prio_queue.top());
		cout<<"Extracting "<<prio_queue.top()<<" from prio queue\n";
		prio_queue.pop();
		shortest_path.push_back(u_temp);
		for(pair<int ,int > a : adjlist[u_temp])
		{
			relax( u_temp , a.first , a.second);
			color[u_temp]= GRAY;
			updatePrioQueue();
			display();
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
        cout<<"\nRunning Dijkstra\n";
        init_dijkstra(0);
        for(int i=0;i<n;i++)
		{
			if(color[i]==WHITE)
			{
				cout<<"greying node "<<i; nl
				color[i]=GRAY;
				display();
				dijkstra(i);
			}
		}
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
		for(auto a : shortest_path)
		{
			color[a] = GREEN;
		}
		for(int i=0;i<vt;i++)
	    {
	        str=to_string(::distance[i]);
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
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
	cout<<"Enter the number of nodes in the graph"; nl
	cin>>n;
	color =  new int[n];
	::distance = new int[n];
	predecessor = new int[n];
	coordinates= new pair< int ,int > [n];
	cout<<"Enter the number of edges in the graph"; nl
	cin>>e;
	ecolor = new int[n];
	cout<<"Enter the edges of the graph (u --> v) pairs and their weight w"; nl
	size_t u,v,w;
	for(int i=0;i<e;i++)
	{
		cin>>u>>v>>w;
		adjlist[u].push_back(make_pair(v,w));
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
