#include <iostream>

// need this for pair template
//
#include <utility>
using namespace std;

#include "Graph.h"

int main() {
// G has 5 vertices numbered 0 thru 4
  Graph G(5);
  cout << "created graph with 5 vertexes" << endl;
  // add some edges
  G.addEdge(3, 4);
  G.addEdge(1, 4);
  G.addEdge(0, 3);

  // dump out data structure
  cout<< "dumping G"<<endl;
  G.dump() ;

  cout<<"dumping H"<<endl<<endl;
  Graph I(5);
  I.dump();

  Graph H(G);
  H.dump();
}