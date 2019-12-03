#include <iostream>
using namespace std;
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>

/**************************************
 *  Nathan Redmond                    *
 *  COSC 320 edgeCover Research       *
 *  modified: 27 AUG 2019             *
 **************************************/

enum color_t{
    BLACK,
    WHITE,
    GRAY
};

class edgeCover{
private:
    map<int, vector<int>> verticies;
    map<int, vector<int>> verticiesCOPY;
public:
    void addVertex(int vert){
        auto iter = verticies.find(vert);
        if( iter == verticies.end() ){
          vector<int> newVector;
          verticies.insert(pair<int, vector<int>> (vert, newVector));
        }
    }

    void addEdge(int vert1, int vert2){
      addVertex(vert1);
      addVertex(vert2);
      if( vert1 == vert2 ){
        for( auto it = verticies[vert1].begin(); it < verticies[vert1].end(); it++ ){
          if( *it == vert1 )
              return;
        }
        verticies[vert1].push_back(vert1);
      }
      else{
        for( auto it = verticies[vert1].begin(); it < verticies[vert1].end(); it++ ){
          if( *it == vert2 )
              return;
        }
        verticies[vert1].push_back(vert2);
        verticies[vert2].push_back(vert1);
      }

    }

    void countNeighbors(int node, int& total){
      total = 0;
      for( auto it = verticies[node].begin(); it < verticies[node].end(); it++ ){
        total++;
      }
    }

    void countNeighbors2(int node, int& total){
      total = 0;
      for( auto it = verticiesCOPY[node].begin(); it < verticiesCOPY[node].end(); it++ ){
        total++;
      }
    }

    int findMinEdge(){
      int minEdge = 99, temp = 99, selectNode;
      for( auto it = verticies.begin(); it != verticies.end(); it++ ){
        if( !it->second.empty() )
          countNeighbors(it->first, temp);
        if(temp < minEdge){
          minEdge = temp;
          selectNode = it->first;
        }
      }
      return selectNode;
    }

    int findMaxEdge(){
      int maxEdge = 0, temp = 0, selectNode;
      for( auto it = verticies.begin(); it != verticies.end(); it++ ){
        if( !it->second.empty() )
          countNeighbors(it->first, temp);
        if(temp > maxEdge){
          maxEdge = temp;
          selectNode = it->first;
        }
      }
      return selectNode;
    }

    int findMaxEdge2(){
      int maxEdge = 0, temp = 0, selectNode;
      for( auto it = verticiesCOPY.begin(); it != verticiesCOPY.end(); it++ ){
        if( !it->second.empty() )
          countNeighbors2(it->first, temp);
        if(temp > maxEdge){
          maxEdge = temp;
          selectNode = it->first;
        }
      }
      return selectNode;
    }


    void findEdgeCover(){
      /*
          take node with least amount of neighbors
          add all of nodes neighbors to S.
          remove all edges connected from the graph.

          calculate node with least amount of edges agian until graph is empty.
      */

      verticiesCOPY = verticies;

      vector<int> COVER;
      int min = 99, max = 0, temp = 99, temp2 = 99;
      bool emp = false;

      while( !emp )
      {
        max = findMaxEdge();
        min = findMinEdge();
        countNeighbors(max, temp);
        countNeighbors(min, temp2);
        /*
            *****IDEA!!*****
            Run this algorithm then run and algorithm next that finds max and adds all its neighbors
            to a vector. Compare sizes of the vectors and take the smaller one. This should use original
            algorithm to solve most of the graphs, but the second algorithm for neural network looking graphs.
        */
        if( temp >= 2*temp2 && temp2 != 1 ){
          COVER.push_back(max);
          for( auto it = COVER.begin(); it < COVER.end(); it++ ){
            for( auto iter = verticies.begin(); iter != verticies.end(); iter++ ){
              for( auto iter2 = verticies[iter->first].begin(); iter2 < verticies[iter->first].end(); iter2++ ){
                if( *iter2 == *it )
                  verticies[iter->first].erase(iter2);
                if( iter->first == *it )
                  verticies[iter->first].clear();
              }
            }
          }
        }
        else if( temp2 == 0 ){
          COVER.push_back(min);
        }
        else{
          for( auto it = verticies[min].begin(); it < verticies[min].end(); it++ ){
            COVER.push_back(*it);
          }
          for( auto it = COVER.begin(); it < COVER.end(); it++ ){
            for( auto iter = verticies.begin(); iter != verticies.end(); iter++ ){
              for( auto iter2 = verticies[iter->first].begin(); iter2 < verticies[iter->first].end(); iter2++ ){
                if( *iter2 == *it )
                  verticies[iter->first].erase(iter2);
                if( iter->first == *it )
                  verticies[iter->first].clear();
              }
            }
          }
        }

        emp = true;
        for( auto travers = verticies.begin(); travers != verticies.end(); travers++ ){
          if( !travers->second.empty() )
            emp = false;
        }

      }
      /*
          *****INSERT SECOND ALGORITHM*****
      */
      vector<int> COVER_MAX;
      bool emp2 = false;
      while( !emp2 )
      {
        max = findMaxEdge2();
        countNeighbors2(max, temp);
        for( auto it = verticiesCOPY[max].begin(); it < verticiesCOPY[max].end(); it++ ){
          COVER_MAX.push_back(*it);
        }
        for( auto it = COVER_MAX.begin(); it < COVER_MAX.end(); it++ ){
          for( auto iter = verticies.begin(); iter != verticies.end(); iter++ ){
            for( auto iter2 = verticiesCOPY[iter->first].begin(); iter2 < verticiesCOPY[iter->first].end(); iter2++ ){
              if( *iter2 == *it )
                verticiesCOPY[iter->first].erase(iter2);
              if( iter->first == *it )
                verticiesCOPY[iter->first].clear();
            }
          }
        }
        emp2 = true;
        for( auto travers = verticiesCOPY.begin(); travers != verticiesCOPY.end(); travers++ ){
          if( !travers->second.empty() )
            emp = false;
        }
      }


      /*
            Printing out the smallest edge cover.
      */

      if( COVER.size() <= COVER_MAX.size() )
      {
        cout << "The min Edge Cover is: " << endl << "\t";
        for( auto it = COVER.begin(); it < COVER.end(); it++ ){
          cout << *it << " ";
        }
      }
      else
      {
        cout << "The min Edge Cover is: " << endl << "\t";
        for( auto it = COVER_MAX.begin(); it < COVER_MAX.end(); it++ ){
          cout << *it << " ";
        }
      }

    }

    void print(){
        for( auto it = verticies.begin(); it != verticies.end(); it++ ){
          cout << "Vertex[" << it->first << "] = ";
          for( auto iterat = it->second.begin(); iterat < it->second.end(); iterat++ ){
            cout << *iterat << "  ";
          }
          cout << endl;
        }
    }
};
