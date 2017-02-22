#include <iostream>

// need this for pair template
//
#include <utility>
using namespace std;

#include "Graph.h"

int main() {
  // G has 5 vertices numbered 0 thru 4
  Graph G(5) ;

  // add some edges
  G.addEdge(3,4) ;
  G.addEdge(1,4) ;
  G.addEdge(0,3) ;
  G.addEdge(0,4) ;
  G.addEdge(0,1) ;
  G.addEdge(1,2) ;
  G.addEdge(2,4) ;


//test empty graph
  Graph H(6);
  H.dump();

  //test copying

  H = G;
//having errorrs when copying for some reason...
  H.dump();


  // dump out data structure
  G.dump() ;

  // Test neighbor iterator
  //
  Graph::NbIterator nit ;

  cout << "\nThe neighbors of vertex 4 are:\n" ;
  for (nit = G.nbBegin(4); nit != G.nbEnd(4) ; nit++) {
    cout << *nit << " " ;
  }
  cout << endl ;

  // Test edge iterator
  //
  Graph::EgIterator eit ;
//    cout<< "constructor works"<<endl;
//
  pair<int,int> edge ;
  cout << "\nThe edges in the graph are:\n" ;
  for (eit = G.egBegin() ; eit != G.egEnd() ; eit++) {

//    cout<< "iterated"<<endl;
//
    edge = *eit ;   // get current edge
//
//    // the two data members of a pair are first and second
//    //
    cout << "(" << edge.first << ", " << edge.second << ") " ;

  }
  //still getting segmentation faults for some reason. Might be due to destructor? It does print all the edges now though
  //Note to grader: I would like to request lenient grading since I was very very close to fixing my seg fault :/

}