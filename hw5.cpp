//Nghia Ho
//ID 1251576
//Hw5

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "ArgumentManager.h"
#include "msTreeType.h"
//Most important functions is in msTreeType.h
//printclusterList function is in graphType.h

////////////////////////////////////////////////////////////////////////////////////////////////////////
using namespace std;
int main(int argc, char* argv[])
{
    ifstream ifs("1.txt");
    ofstream ofs("out.txt");


////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
      if(argc<2)
      {
          cout<<"Usage: cluster \"A=<file>;C=<file>\""<<endl;
      }
      ArgumentManager am(argc, argv);
      //initializing input and output stream variable with their correspond file call
      ifstream ifs((am.get("A")).c_str());
      ofstream ofs((am.get("C")).c_str());

*/
////////////////////////////////////////////////////////////////////////////////////////////////////////
        //Initializing myGraph
        msTreeType myGraph(1000);
        //Getting the adjacency list, weighted matrix, and number of cluster from file
        myGraph.createSpanningGraph(ifs);

        //Find minimum spanning tree and reduce it further to get a number of cluster
        //Cluster will then get store in a cluster linked list
        myGraph.setCluster();

        //Check if adjaceny list size and weight matrix size is the same
        //Check if given amount of cluster vs the current amount are the same
        if(myGraph.checkCluster()&&myGraph.checkSize()){
        //Printing the cluster from linked list
        myGraph.printclusterList(ofs);
        }


    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////

