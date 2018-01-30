
#ifndef H_msTree
#define H_msTree
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cfloat>
#include <string>
#include <sstream>
#include "graphType.h"
using namespace std;

class msTreeType: public graphType
{
public:
    void createSpanningGraph(ifstream &infile);
    //Function that store the adjacency lists into a graph,
    //its weight matrix into an array, and the number cluster
    //required into cluster variable
    void minimumSpanning(int sVertex);
    //Function to create a minimum spanning tree with
    //root as sVertex.
    void setCluster();
    //Function that reduce the minimum spanning tree even further to get
    //a set amount of clusters
    //Function also insert that amount of cluster into clusterList linked list
    void printTreeAndWeight();
    //Function to print minimum spanning tree
    bool checkCluster();
    //Function that check if given amount of cluster vs the current amount are the same
    bool checkSize();
    //Function that check if graph size vs matrix size are the same
    bool emptyline(string line);
    //Function that check if line is empty
    msTreeType(int size = 0);
    //Constructor
    //gSize = 0; maxSize = size;
    //Initialize graph and clusterList
    //Initialize weights, edges, and edgeWeight dynamic array

    ~msTreeType();
    //Destructor
    //The storage occupied by the vertices and the arrays
    //weights, edges, and edgeWeights is deallocated.

protected:
    int myCluster=0;//current cluster
    int wSize;//weights size
    int source;//source node
    int **weights;//array to store weights
    int *edges;//array to store edges
    int *edgeWeights;//array to store edgeWeights
};
//Function that check if graph size vs matrix size are the same
bool msTreeType::checkSize()
{
 if(gSize==wSize){
    return true;
 }
 else{
    return false;
 }
}
//Function that check if given amount of cluster vs the current amount are the same
bool msTreeType::checkCluster(){
    //cout<<"Given cluster: "<<cluster<<endl;
    //cout<<"My cluster: "<<myCluster<<endl;
    if(cluster==myCluster){
        return true;
    }
    else{
        return false;
    }
 }
//Function that check if line is empty
  bool msTreeType::emptyline(string line)
    {
        //condiditon for empty line is "" and " "
        if(line==""||line==" ")
        {
            return true;
        }
        else
        {
            return false;
        }
    }
//Function that store the adjacency lists into a graph,
//its weight matrix into an array, and the number cluster
//required into cluster variable
void msTreeType::createSpanningGraph(ifstream &infile)
{
	if (!infile)
	{
		cout << "Cannot open input file." << endl;
		return;
	}

//First paragraph
//setting a counter to count line for gSize
    int counter=0;
    int num;
    string line;
    //getline loop until you find an empty line
	while(getline(infile,line))
	{
	    if(!emptyline(line)){
	    stringstream ss(line);
        //stream line from getline into num and insert that into graph
        while(ss>>num){
                graph[counter].insertLast(num);
        }
        counter++;
	    }
	    else{
            break;
	    }
	}
	gSize=counter;//storing line counter into gSize

//Second paragraph
//Setting counter back to 0 to count row in the array for wSize
//Setting otherCounter to count the number of column in the array here
    counter=0;
    int otherCounter;
    int weight;
    //getline loop until you find an empty line
	while(getline(infile,line))
	{
	    if(!emptyline(line)){
	    stringstream ss(line);
	    //stream line from getline into weight and insert that into weights array
	    otherCounter=0;
        while(ss>>weight){
        if(weight!=-999){
			weights[counter][otherCounter] = weight;
            otherCounter++;
            }
            else{
                weights[counter][otherCounter]=999999;//Setting all -999 value to large number so minimum spanning tree would erase it
                otherCounter++;
            }
        }
        counter++;
	    }
	    else{
            break;
	    }
	}
	if(counter!=otherCounter){//if rows and column doesnt equal to each other, set wSize=-999 which ensure the print function won't print anything
        wSize=-999;
	}
	else{
	wSize=counter;
	}

//Third paragraph
//inserting remaining number into cluster
	infile>>cluster;


} //createWeightedGraph

//Function that reduce the minimum spanning tree even further to get
//a set amount of clusters
//Function also insert that amount of cluster into clusterList linked list
void msTreeType::setCluster(){
    minimumSpanning(0);//create a minimum spanning tree at 0 to start
        int maxWeight=0;
        int maxIndex;
    for(int i=0;i<cluster-1;i++){//double for loop to find set current max weight to -999
        maxWeight=0;
        maxIndex=0;
        for(int j=0;j<gSize;j++){
        if(maxWeight<edgeWeights[j]){
            maxWeight=edgeWeights[j];
            maxIndex=j;

        }
        }
    edgeWeights[maxIndex]=-999;
    }

//searchGraph search the list array for duplicates
//searchGraph function can be found in graphType.h
//-999 edgeWeigths are ignored
//insert function insert item sorted
//insert function can be found in unorderedLinkedList.h
    int myCounter;
    for(int i=0;i<cluster;i++){
        for(int k=0;k<gSize;k++){
        if(!searchGraph(k)){
            clusterList[i].insert(k);//first Index value get inserted here
            myCluster++;
            break;
        }
	}
        for(int l=0;l<gSize;l++){
    	for (int j = 0; j < gSize; j++)
        {
		if (edgeWeights[j]!=-999)//highest edgeWeights[j] was set to -999 earlier are now ignored
		{
            if(!searchGraph(edges[j])&&searchGraph(j))
                {
            clusterList[i].insert(edges[j]);//graph insertion
            }
            if(searchGraph(edges[j])&&!searchGraph(j))
                {
            clusterList[i].insert(j);//graph insertion
            }
		}
	}
        }
}
}

//Function to create a minimum spanning tree with
//root as sVertex.
void msTreeType::minimumSpanning(int sVertex)
{
	int startVertex, endVertex;
	int minWeight;

	source = sVertex;

	bool *mstv;
    	mstv = new bool[gSize];

	for (int j = 0; j < gSize; j++)
	{
		mstv[j] = false;
		edges[j] = source;
		edgeWeights[j] = weights[source][j];
	}

	mstv[source] = true;
	edgeWeights[source] = 0;

	for (int i = 0; i < gSize - 1; i++)
	{
		minWeight = 999999;

		for (int j = 0; j < gSize; j++)
			if (mstv[j])
				for (int k = 0; k < gSize; k++)
					if (!mstv[k] && weights[j][k] < minWeight)
					{
						endVertex = k;
						startVertex = j;
						minWeight = weights[j][k];
					}
		mstv[endVertex] = true;
		edges[endVertex] = startVertex;
		edgeWeights[endVertex] = minWeight;
	} //end for
} //end minimumSpanning

//Function to print minimum spanning tree
void msTreeType::printTreeAndWeight()
{
	int treeWeight = 0;

	cout << "Source Vertex: " << source << endl;
	cout << "Edges    Weight" << endl;

	for (int j = 0; j < gSize; j++)
	{
		if (edges[j] != j)
		{
			treeWeight = treeWeight + edgeWeights[j];
			cout << "("<<edges[j] << ", " << j << ")    "
				 << edgeWeights[j] << endl;
		}
	}

	cout << endl;
	cout << "A minimum spanning tree weight: "
		 << treeWeight << endl;
} //end printTreeAndWeight


//Constructor
//gSize = 0; maxSize = size;
//Initialize graph and clusterList
//Initialize weights, edges, and edgeWeight dynamic array
msTreeType::msTreeType(int size)
           :graphType(size)
{
    weights = new int*[size];

    for (int i = 0; i < size; i++)
        weights[i] = new int[size];

    edges  = new int[size];

    edgeWeights = new int[size];
    //smallestWeight = new int[size];
    graph = new unorderedLinkedList<int>[size];
    clusterList=new unorderedLinkedList<int>[size];
}

//Destructor
//The storage occupied by the vertices and the arrays
//weights, edges, and edgeWeights is deallocated.
msTreeType::~msTreeType()
{
    for (int i = 0; i < gSize; i++)
       delete [] weights[i];

    delete [] weights;
    delete [] edges;
    delete edgeWeights;
    //delete smallestWeight;
}

#endif
