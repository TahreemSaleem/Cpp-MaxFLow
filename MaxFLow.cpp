#include <iostream>
#include <utility>
#include <queue>
#include <list>
using namespace std;

class Graph
{
private:
	int nV;
	list <pair<int, int>> *adjList;
public:
	Graph(int nV);
	void display();
	void addEdge(int a, int b, int w);
	bool BFS(list<pair<int, int>> *rGraph, int s, int t, int *p);
	int fordFulkerson(int s, int t);
};
Graph::Graph(int nV)
{
	this->nV = nV;
	adjList = new list<pair<int, int>>[nV];	//adjacency list of size 'nV'
}
void Graph::display()
{
	list<pair<int, int>>::iterator j;
	for (int i = 0; i<nV; i++){
		cout << i << "-> ";
		for (j = adjList[i].begin(); j != adjList[i].end(); ++j)
			cout << (*j).first << "(" << (*j).second << ")" << " ";
		cout << endl;
	}

}
void Graph::addEdge(int u, int v, int w)
{
	adjList[u].push_back(pair<int, int>(v, w)); // Add u to v’s list along with edge weight w

}


bool Graph::BFS(list<pair<int, int>> *list1, int s, int t, int *p)	//BFS
{
	bool *visited = new bool[nV];	// Created a visited array and marked all the vertices as not visited
	for (int i = 0; i < nV; i++)
		visited[i] = false;

	queue <int> q;		//created a queue
	q.push(s);
	visited[s] = true;		//source has been visited
	p[s] = s;
	list<pair<int, int>>::iterator it;	//an iterator for traversing list


	while (!q.empty())
	{
		s = q.front();		//new source = front of queue
		q.pop();			//pop the front element
		for (it = list1[s].begin(); it != list1[s].end(); it++)		//traversing the s'th node of the list 
		{
			if ((!visited[(*it).first]) && (*it).second > 0)		//if the weight is more then zero and node has parent s and not vivisted
			{
				q.push((*it).first);			//push it into the queue
				p[(*it).first] = s;
				visited[(*it).first] = true;
			}
		}
	}
	return (visited[t] == true);	// If we reached sink in BFS starting from s, then return true
}//BFS() ends here


int Graph::fordFulkerson(int s, int t)
{
	int u, v, w;
	list<pair<int, int>> *adjList1 = new list<pair<int, int>>[nV];

	adjList1 = adjList;

	list<pair<int, int> >::iterator it;		//an iterator for traversing the adjacency list horizontally

	int *p = new int[nV];  // This array is filled by BFS and to store path from source to sink

	int max_flow = 0;   // to store max flow


	while (BFS(adjList1, s, t, p))
	{
		int path_flow = INT_MAX;	//initially, path flow infinity
		for (v = t; v != s; v = p[v])		//path filled by BFS
		{
			u = p[v];
			for (it = adjList1[u].begin(); it != adjList1[u].end(); it++)
			{
				if ((*it).first == v)
					w = (*it).second;	//v's w
			}//internal for ends here
			path_flow = min(path_flow, w);	//minimum residual capacity
		}//for ends here
		for (v = t; v != s; v = p[v])
		{
			u = p[v];	//u = pof v
			for (it = adjList[u].begin(); it != adjList1[u].end(); it++)
			{
				if ((*it).first == v)
				{
					(*it).second -= path_flow;
				}
			}
		}
		max_flow += path_flow;		// Add path flow to max flow
	}
	return max_flow;	// Return the overall flow
}



int main()
{
	Graph g(8);
	g.addEdge(0, 1, 10);
	g.addEdge(0, 2, 5);
	g.addEdge(0, 3, 15);
	g.addEdge(1, 4, 9);
	g.addEdge(1, 5, 15);
	g.addEdge(1, 2, 4);
	g.addEdge(2, 5, 8);
	g.addEdge(2, 3, 4);
	g.addEdge(3, 6, 30);
	g.addEdge(4, 5, 15);
	g.addEdge(4, 7, 10);
	g.addEdge(5, 7, 10);
	g.addEdge(5, 6, 15);
	g.addEdge(6, 2, 6);
	g.addEdge(6, 7, 10);
	
	
	cout << "The maximum  flow is  " <<g.fordFulkerson(0,5) << endl;
	return 0;
}

 

