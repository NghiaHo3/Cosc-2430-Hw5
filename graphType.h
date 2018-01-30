#include <iostream>
#include <fstream>
#include "unorderedLinkedList.h"
#include "linkedQueueType.h"
#include "msTreeType.h"

class graphType
{
	public:
		bool isEmpty() const;
		//Function to determine whether the graph is empty.
		void createGraph();
		//Function to create a graph.
		void clearGraph();
		//Function to clear graph.
		void printGraph(ofstream &ofs) const;
		//Function to print graph.
		void depthFirstTraversal();
		//Function to perform the depth first traversal of
		//the entire graph.
		void dftAtVertex(int vertex);
		//Function to perform the depth first traversal of
		//the graph at a node specified by the parameter vertex.
		void breadthFirstTraversal();
		//Function to perform the breadth first traversal of
		//the entire graph.
		graphType(int size = 0);
		//Constructor
		//Postcondition: gSize = 0; maxSize = size;
		// graph is an array of pointers to linked lists.
		~graphType();
		//Destructor
		//The storage occupied by the vertices is deallocated.
        void printclusterList(ofstream &ofs);
        //Function to printclusterList
		bool searchGraph(int searchItem);
		//Function to search graph array to duplicate
		int cluster=0;//cluster given
	protected:
		int maxSize; //maximum number of vertices
		int gSize; //current number of vertices
        unorderedLinkedList<int> *graph; //array to create
        unorderedLinkedList<int> *clusterList;
		//adjacency lists
	private:
		void dft(int v, bool visited[]);
		//Function to perform the depth first traversal of
		//the graph at a node specified by the parameter vertex.
		//This function is used by the public member functions
		//depthFirstTraversal and dftAtVertex.
		//Postcondition: Starting at vertex, the vertices are
		// printed using the depth first traversal algorithm.
};
//Function to printclusterList
void graphType::printclusterList(ofstream &ofs)
{
	for (int index = 0; index < cluster; index++)
	{
		clusterList[index].print(ofs);
		cout << endl;
		ofs<<endl;
	}
} //end printGraph

//Function to search graph array for duplicates
bool graphType::searchGraph(int searchItem){
    for(int i=0;i<gSize;i++){
        if(clusterList[i].search(searchItem)){
            return true;
        }
    }
return false;

}
//Function to check if graph is empty
bool graphType::isEmpty() const
{
	return (gSize == 0);
}
//Function to create graph
void graphType::createGraph()
{
	ifstream infile;
	char fileName[50];
	int vertex;
	int adjacentVertex;
	if (gSize != 0) //if the graph is not empty, make it empty
		clearGraph();
	cout << "Enter input file name: ";
	cin >> fileName;
	cout << endl;
	infile.open(fileName);
	if (!infile)
	{
		cout << "Cannot open input file." << endl;
		return;
	}
	infile >> gSize; //get the number of vertices
	for (int index = 0; index < gSize; index++)
	{
		infile >> vertex;
		infile >> adjacentVertex;
		while (adjacentVertex != -999)
		{
			graph[vertex].insertLast(adjacentVertex);
			infile >> adjacentVertex;
		} //end while
	} // end for
	//infile.close();
	}//end createGraph

//Function to clear graph
void graphType::clearGraph()
{
	for (int index = 0; index < gSize; index++)
		graph[index].destroyList();
	//gSize = 0;
} //end clearGraph

//Function to print graph
void graphType::printGraph(ofstream &ofs) const
{
	for (int index = 0; index < gSize; index++)
	{
		graph[index].print(ofs);
		cout << endl;
	}
} //end printGraph
//Constructor
graphType::graphType(int size)
{
	maxSize = size;
	gSize = 0;
}
//Destructor
graphType::~graphType()
{
	clearGraph();
}

//Function to perform the depth first traversal of
//the entire graph at specific node
void graphType::dft(int v, bool visited[])
{
	visited[v] = true;
	cout << " " << v << " "; //visit the vertex
	linkedListIterator<int> graphIt;
	//for each vertex adjacent to v
	for (graphIt = graph[v].begin(); graphIt != graph[v].end();	++graphIt)
	{
		int w = *graphIt;
		if (!visited[w])
			dft(w, visited);
	} //end while
} //end dft



//Function to perform the depth first traversal of
//the entire graph.
void graphType::depthFirstTraversal()
{
	bool *visited; //pointer to create the array to keep
	//track of the visited vertices
	visited = new bool[gSize];
	for (int index = 0; index < gSize; index++)
		visited[index] = false;
	//For each vertex that is not visited, do a depth
	//first traverssal
	for (int index = 0; index < gSize; index++)
		if (!visited[index])
			dft(index,visited);
	delete [] visited;
} //end depthFirstTraversal

//Function to perform the depth first traversal of
//the graph at a node specified by the parameter vertex.
void graphType::dftAtVertex(int vertex)
{
	bool *visited;
	visited = new bool[gSize];
	for (int index = 0; index < gSize; index++)
		visited[index] = false;
	dft(vertex, visited);
	delete [] visited;
} // end dftAtVertex

//Function to perform the breadth first traversal of
//the entire graph.
void graphType::breadthFirstTraversal()
{
	linkedQueueType<int> queue;
	bool *visited;
	visited = new bool[gSize];
	for (int ind = 0; ind < gSize; ind++)
		visited[ind] = false; //initialize the array
	//visited to false
	linkedListIterator<int> graphIt;
	for (int index = 0; index < gSize; index++)
		if (!visited[index])
		{
			queue.addQueue(index);
			visited[index] = true;
			cout << " " << index << " ";
			while (!queue.isEmptyQueue())
			{
				int u = queue.front();
				queue.deleteQueue();
				for (graphIt = graph[u].begin();
				graphIt != graph[u].end(); ++graphIt)
				{
					int w = *graphIt;
					if (!visited[w])
					{
						queue.addQueue(w);
						visited[w] = true;
						cout << " " << w << " ";
					}
				}
			} //end while
		}
	delete [] visited;
} //end breadthFirstTraversal
