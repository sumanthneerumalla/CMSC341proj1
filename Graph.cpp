#include "Graph.h"
using namespace std;
#include <iostream>

Graph::Graph(int n) {
  if (n < 0 or n == 0) {
    throw std::out_of_range("Not possible to insert that number of vertices");
  }
  m_adjLists = new AdjListNode *[n];
  m_size = n;
}

Graph::Graph(const Graph &G) {
  //copy over member variable for size
  m_size = G.m_size;

  //allocate new dynamic array with that size
  m_adjLists = new AdjListNode *[m_size];

  //iterate through each array and copy over the linked list data.
  AdjListNode *curr2, *next2;

  for (int i = 0; i < m_size; ++i) {
    curr2 = G.m_adjLists[i];

    //iterate through each edge in the second graph, for each vertex
    while (curr2 != NULL) {
      //hold onto the next edge
      next2 = curr2->next;
      //avoid adding the same edge twice.
      if (i < curr2->m_vertex) {
        addEdge(i, curr2->m_vertex);
      }
      curr2 = next2;
    }
  }
}

Graph::~Graph() {
  //iterate through the array of linked list
  AdjListNode *curr, *next;
  for (int i = 0; i < m_size; ++i) {
    curr = m_adjLists[0];

    //use a while loop to delete each edge connection
    while (curr != NULL) {
      next = curr->next;
      delete curr;
      curr = next;
    }

  }

  //delete the array of pointers
  delete[] m_adjLists;
}

void Graph::addEdge(int u, int v) {
//add an edge to the first vertex
  AdjListNode *next;

  //hold onto the first item in the
  next = m_adjLists[u];
  m_adjLists[u] = new AdjListNode(v, next);

  cout << "added edge " << u << " to " << v << endl;

  next = m_adjLists[v];
  m_adjLists[v] = new AdjListNode(u, next);

//  cout << "added edge " << v << " to " << u << endl;

};

int Graph::size() {
  return m_size;
}
void Graph::dump() {
  //iterate through the array of linked list
  AdjListNode *curr, *next;

  cout << "Dump out graph (size = " << size() << "):" << endl;
  for (int i = 0; i < size(); ++i) {
    curr = m_adjLists[i];
    cout << "[ " << i << "]: ";
    //use a while loop to print out each edge connection
    while (curr != NULL) {
      next = curr->next;
      cout << curr->m_vertex << " ";
      curr = next;
    }
    cout << endl;

  }
}

Graph::AdjListNode::AdjListNode(int v, Graph::AdjListNode *ptr) {
  m_vertex = v;
  next = ptr;
}
