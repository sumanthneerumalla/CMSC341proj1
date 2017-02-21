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

const Graph &Graph::operator=(const Graph &rhs) {
  if (this == &rhs) // this is a self assignment checker
  { return *this; }    // returns the pointer to the current object
  // otherwise copy

  //copied code from destructor to deallocate all dynamic memory
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

  //copied code from copy constructor to copy over new dynamic data

  //copy over member variable for size
  m_size = rhs.m_size;

  //allocate new dynamic array with that size
  m_adjLists = new AdjListNode *[m_size];

  //iterate through each array and copy over the linked list data.
  AdjListNode *curr2, *next2;

  for (int i = 0; i < m_size; ++i) {
    curr2 = rhs.m_adjLists[i];

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
  return *this;
}

Graph::NbIterator Graph::nbBegin(int v) {
  return Graph::NbIterator(this,v,false);
}
Graph::NbIterator Graph::nbEnd(int v) {
  return Graph::NbIterator(this,v,true);
}

Graph::AdjListNode::AdjListNode(int v, Graph::AdjListNode *ptr) {
  m_vertex = v;
  next = ptr;
}

Graph::NbIterator::NbIterator(Graph *Gptr, int v, bool isEnd) {
  m_Gptr = Gptr;
  m_source = v;
  //honestly i dont see the point of storing these variables if the iterator is just used for
  //comparing the mhwere variable

  //if isend is true we make an end constructor
  if (isEnd == true and Gptr != NULL and v != -1) {
    m_where = NULL;
  }
    //if it is end is not true we make a regular nbiterator, that starts at the beginning of the neighbor list
  else if (isEnd == false and Gptr != NULL and v != -1) {
    m_where = Gptr->m_adjLists[v];
  }
  else {
    m_where = NULL;
    //in any other circumstance, mwhere is not valid
  }

}
bool Graph::NbIterator::operator!=(const Graph::NbIterator &rhs) {
  if (m_where != rhs.m_where) {
    //if the addresses of the mwheres of each iterator are not the same, return true
    return true;
  }
  //otherwise return false
  return false;
}
void Graph::NbIterator::operator++(int dummy) {
  if (m_where->next != NULL) {
    //increment the pointer only if the next node isn't null
    m_where = m_where->next;
  }
}
int Graph::NbIterator::operator*() {
  return m_where->m_vertex;
}
