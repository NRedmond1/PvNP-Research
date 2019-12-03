#include <iostream>
using namespace std;
#include "edgeCover.h"

  /**************************************
   *  Nathan Redmond                    *
   *  COSC 320 edgeCover Research       *
   *  modified: 02 May 2019             *
   **************************************/

  void print_menu(){
    system("clear");
    cout << "-----------------------------------" << endl;
    cout << "|  1) Enter Vertex                |" << endl;
    cout << "|  2) Enter Edge                  |" << endl;
    cout << "|  3) Read From File              |" << endl;
    cout << "|  4) Read From File with edges   |" << endl;
    cout << "|  5) Print                       |" << endl;
    cout << "|  6) Find Edge COVER             |" << endl;
    cout << "-----------------------------------" << endl;
  }

  int main(){

    edgeCover my_graph;
    bool running = true;
    int menuInput = 0, vertexInput = 0, edgeInput = 0, edgeOutput = 0;
    char result;
    while( running ){
      print_menu();
      cin >> menuInput;
      cin.clear();
      if( menuInput == 1 ){
        int numVec = 0;
        cout << "How many verticies do you want to input? ";
        cin >> numVec;
        for( int i = 0; i < numVec; i++ ){
          cout << "Enter number to add: ";
          cin >> vertexInput;
          my_graph.addVertex(vertexInput);
        }

        cout << endl << "continue? (y or n): ";
        cin >> result;
        if( result != 'y' )
          running = false;
      }
      else if( menuInput == 2 ){
        int numEdge = 0;
        cout << "How many edges do you want to input? ";
        cin >> numEdge;
        for( int i = 0; i < numEdge; i++ ){
          cout << "Enter vertex from: ";
          cin >> edgeInput;
          cout << "Enter vertex to: ";
          cin >> edgeOutput;
          my_graph.addEdge(edgeInput, edgeOutput);
        }

        cout << endl << "continue? (y or n): ";
        cin >> result;
        if( result != 'y' )
          running = false;
      }
      else if( menuInput == 3 ){
        int data, data2;
        char trash;
        string neighbors;
        ifstream infile;
        infile.open("test3.txt", ios::in);
        while( infile ){
          infile >> data;
          infile >> trash;
          getline(infile, neighbors);
          stringstream ss(neighbors);
          while( ss >> data2 ){
            my_graph.addEdge(data, data2);
          }
        }

        cout << endl << "continue? (y or n): ";
        cin >> result;
        if( result != 'y' )
          running = false;
      }
      else if( menuInput == 4 ){
	       int data, data2;
         ifstream infile;
         infile.open("athletes_edges_data.txt", ios::in);
         while( infile ){
           infile >> data;
           infile >> data2;
	         my_graph.addEdge(data, data2);
	       }
      }
      else if( menuInput == 5 ){
        my_graph.print();

        cout << endl << "continue? (y or n): ";
        cin >> result;
        if( result != 'y' )
          running = false;
      }
      else if( menuInput == 6 ){
        my_graph.findEdgeCover();

        cout << endl << "continue? (y or n): ";
        cin >> result;
        if( result != 'y' )
          running = false;
      }
      else
        cout << "please try again." << endl;
    }
  return 0;
}
